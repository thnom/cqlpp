//
//  Copyright (C) 1994-2003  Seth Kurtzberg
//
// CQL++ This program is free software.  The copyright is reserved.
//
// The file COPYING included with the distribution specifies the license
// granted to users of CQL++.  You can also view the licensing terms
// at http://www.cql.com/copying.html
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See COPYING
// for more information
//
// If you did not receive the file COPYING which contains the terms of
// the license, and you do not have access to the world wide web, you
// can request a copy by the following email address:  support@cql.com.
// If you do not have access to email, you can obtain a copy by postal
// mail by writing to Machine Independent Software Corporation,
// 9663 East Voltaire Drive, Scottsdale, Arizona, 85260, USA
//


#include "CqlIsamInclude.h"


void DatabaseHandle::addToIndexIndex( Index *index )
{
	if( stack_.Indices()->AddIndexNode( errorManager_, index ) == CQL_FAILURE )
		throw MemoryIndexException( __FILE__, __LINE__ );
}


void DatabaseHandle::deleteFromIndexIndex( Index *index )
{
	//  Indices may be empty if no transaction is in progress
	if( stack_.Indices() )
	{
		if( stack_.Indices()->FindEqualKey( errorManager_, index ) != CQL_SUCCESS )
			throw MemoryIndexException( __FILE__, __LINE__ );

		if( stack_.Indices()->deleteIndexNode() == CQL_FAILURE )
			throw MemoryIndexException( __FILE__, __LINE__ );
	}
}


void DatabaseHandle::addToIsamIndex( IsamFile *isamFile )
{
	if( stack_.IsamFiles()->AddIndexNode( errorManager_, isamFile ) == CQL_FAILURE )
		throw MemoryIndexException( __FILE__, __LINE__ );
}


void DatabaseHandle::deleteFromIsamIndex( IsamFile *isamFile )
{
	//  IsamFiles() may be empty if no transaction is in progress
	if( stack_.IsamFiles() )
	{
		if( stack_.IsamFiles()->FindEqualKey( errorManager_, isamFile ) != CQL_SUCCESS )
			throw MemoryIndexException( __FILE__, __LINE__ );

		if( stack_.IsamFiles()->deleteIndexNode() == CQL_FAILURE )
			throw MemoryIndexException( __FILE__, __LINE__ );
	}
}


void DatabaseHandle::writePageToDisk( TransactionPageIndexNode *tpage )
{
	RECID pos;
	BaseBufferPage *basePage = tpage->BasePage();
	BufferPage *lastPage, *prevPage;
	pPageChainElement lastElement, last2Element;
	pTransactionStackElement transStackEl;
	pTransactionPageIndex tpi;
	pTransactionPageIndexNode tpage2;
	bool doDiskWrite;

	//
	//  find end of page chain
	//
	lastElement = basePage->transactionPages().last();
	lastPage = lastElement->Page();
	last2Element = basePage->transactionPages().prev();
	if( last2Element )
	{
		prevPage = last2Element->Page();
		doDiskWrite = false;
	}
	else
	{
		prevPage = basePage->page();
		doDiskWrite = true;
	}

	dynamic_cast< EnvironmentHandle* >( hAEnv )->bringPageIntoMemory( prevPage );
	dynamic_cast< EnvironmentHandle* >( hAEnv )->bringPageIntoMemory( lastPage );

	if( doDiskWrite && stack_.size() > 1 )
	{
		if( transactionDebugging == CQL_YES )
		{
			*hAEnv << "Propagating transaction to interior, no page modification, for "
					  << tpage->FileMgr()->Name().text()
					  << ", page "
					  << lastPage->pageNumber()
					  << "\n";
		}

		//
		//  this is the outermost transaction for the page, but is not the outermost transaction
		//  for the user.  Therefore, we can't do this write step.  Instead, we propagate the page write
		//  to the next transaction in the stack_.
		//
		transStackEl = stack_.LastNestedTransaction();
		tpi = transStackEl->Tpi();
		if( tpi->MemoryIndex::findEqualKey( tpage ) != CQL_SUCCESS )
		{
			tpage2 = new TransactionPageIndexNode( tpage->FileNumber(),
												   tpage->PageNumber(),
												   tpage->FileMgr(),
												   tpage->BasePage() );
			if( !tpage2 )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			if( tpi->MemoryIndex::addIndexNode( tpage2 ) == CQL_FAILURE )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		if( tpage->FileMgr()->PropagationTransactionNumber() != stack_.CurrentTransaction() )
		{
			tpage->FileMgr()->IncrementPropagationCounter();
			tpage->FileMgr()->SetPropagationTransactionNumber( stack_.CurrentTransaction() );
		}
	}
	else
	{
		if( transactionDebugging == CQL_YES )
		{
			*hAEnv << "Shrinking page list for "
					  << tpage->FileMgr()->Name().text()
					  << " page "
					  << lastPage->pageNumber()
					  << ", list size="
					  << basePage->transactionPages().size()
					  << "\n";
		}

		memcpy( prevPage->base(), lastPage->base(), CQL_PAGE_SIZE );

		if( !tpage->FileMgr()->temporary() && doDiskWrite )
		{
			if( transactionDebugging == CQL_YES )
			{
				*hAEnv << "Writing page to disk for "
						  << tpage->FileMgr()->Name().text()
						  << " page "
						  << lastPage->pageNumber()
						  << "\n";
			}

			//
			//  this is the outermost incarnation of this page
			//
			pos = tpage->PageNumber() * CQL_PAGE_SIZE;
			tpage->FileMgr()->ClibFile().outputSeek( pos );
			tpage->FileMgr()->UpdateFileExtensionPage( tpage->PageNumber() );
			tpage->FileMgr()->ClibFile().write( prevPage->base(), CQL_PAGE_SIZE );
			tpage->FileMgr()->ClibFile().flush();
			// exception
			prevPage->clearUncommitted();
			prevPage->clearAdded();
		}

		basePage->transactionPages().DeleteLastElement();
		if( tpage->FileMgr()->PropagationCounter() > 0 )
			tpage->FileMgr()->DecrementPropagationCounter();
	}
}


void DatabaseHandle::flushToBuffers( void )
{
	pIsamFile ifile;

	for( ifile = openIsamFiles_.first(); ifile; ifile = openIsamFiles_.next() )
		ifile->flushDirtyRecords();
}


void DatabaseHandle::beginTransaction( void )
{
	if( csFunctionLogging )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "DatabaseHandle::BeginTransaction\n" );

	UL transactionNumber = dynamic_cast< EnvironmentHandle* >( hAEnv )->NewTransactionNumber();

	if( transactionDebugging == CQL_YES )
		*hAEnv << "Begin transaction, " << transactionNumber << "\n";

	if( stack_.TransactionPush( ((ErrorManager&)aErrorMan()), transactionNumber ) == CQL_FAILURE )
		throw TransactionException( __FILE__, __LINE__ );

	if( dynamic_cast< EnvironmentHandle* >( hAEnv )->TransBeginTransaction( stack_ ) == CQL_FAILURE )
		throw TransactionException( __FILE__, __LINE__ );

	flushToBuffers();
}


void DatabaseHandle::commitTransaction( void )
{
	pTransactionPageIndexNode tpage;
	pIndexIndexNode tindex;
	pIsamIndexNode tisam;
	NI rc;

	if( csFunctionLogging )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "DatabaseHande::CommitTransaction\n" );

	if( transactionDebugging == CQL_YES )
		*hAEnv << "Commit transaction, " << stack_.CurrentTransaction() << "\n";

	if( dynamic_cast< EnvironmentHandle* >( hAEnv )->StartCommitTransaction( stack_ ) == CQL_FAILURE )
		throw TransactionException( __FILE__, __LINE__ );

	if( stack_.Indices() )
	{
		for( rc = stack_.Indices()->firstNode(); rc == CQL_SUCCESS; rc = stack_.Indices()->nextNode() )
		{
			tindex = stack_.Indices()->CurrentNode();

			if( tindex->OpenIndex()->FlushDirtyNodes( *this ) == CQL_FAILURE )
			{
				stack_.TransactionPop( ((ErrorManager&)aErrorMan()) );
				throw TransactionException( __FILE__, __LINE__ );
			}

			//
			//  0 transaction counter can occur on create
			//
			if( tindex->OpenIndex()->TransactionCounter() )
				tindex->OpenIndex()->DecrementTransactionCounter();
		}
	}

	if( stack_.IsamFiles() )
	{
		for( rc = stack_.IsamFiles()->firstNode(); rc == CQL_SUCCESS; rc = stack_.IsamFiles()->nextNode() )
		{
			tisam = stack_.IsamFiles()->CurrentNode();
			
			//
			//  0 transaction counter can occur on create
			//
			if( ((pIsamFile)tisam->OpenIsam())->transactionCounter() )
				((pIsamFile)tisam->OpenIsam())->decrementTransactionCounter();
			AbstractTable *pAt = tisam->OpenIsam();
			pAt->flushDirtyRecords();
		}
	}

	if( stack_.Pages() )
	{
		while( ( rc = stack_.Pages()->firstNode()) == CQL_SUCCESS )
		{
			tpage = stack_.Pages()->CurrentNode();

			if( tpage->FileMgr()->IsOpen() != CQL_NO )
			{
				//  log old and/or new pages
				if( dynamic_cast< EnvironmentHandle* >( hAEnv )->LogPage( stack_, tpage ) == CQL_FAILURE )
				{
					stack_.TransactionPop( ((ErrorManager&)aErrorMan()) );
					throw TransactionException( __FILE__, __LINE__ );
				}

				try
				{
					writePageToDisk( tpage );
				}
				catch( ... )
				{
					stack_.TransactionPop( ((ErrorManager&)aErrorMan()) );
					throw;
				}
			}

			if( stack_.Pages()->deleteIndexNode() == CQL_FAILURE )
			{
				stack_.TransactionPop( ((ErrorManager&)aErrorMan()) );
				throw TransactionException( __FILE__, __LINE__ );
			}
		}
	}


	if( dynamic_cast< EnvironmentHandle* >( hAEnv )->EndCommitTransaction( stack_ ) == CQL_FAILURE )
	{
		stack_.TransactionPop( ((ErrorManager&)aErrorMan()) );
		throw TransactionException( __FILE__, __LINE__ );
	}

	stack_.TransactionPop( dynamic_cast< ErrorManager& >( aErrorMan() ) );
}


void DatabaseHandle::rollbackTransaction( void )
{
	if( stack_.size() == 0 )
		return;

	pIndexIndexNode tindex;
	pIsamIndexNode tisam;
	pTransactionPageIndexNode tpage;
	NI rc;

	if( csFunctionLogging )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "DatabaseHande::RollbackTransaction\n" );

	if( transactionDebugging == CQL_YES )
		*hAEnv << "Rollback transaction, " << stack_.CurrentTransaction() << "\n";

	if( dynamic_cast< EnvironmentHandle* >( hAEnv )->TransRollbackTransaction( stack_ ) == CQL_FAILURE )
	{
		stack_.TransactionPop( ((ErrorManager&)aErrorMan()) );
		throw TransactionException( __FILE__, __LINE__ );
	}

	if( stack_.Indices() )
	{
		for( rc = stack_.Indices()->firstNode(); rc == CQL_SUCCESS; rc = stack_.Indices()->nextNode() )
		{
			tindex = stack_.Indices()->CurrentNode();

			if( tindex->OpenIndex()->File().IsOpen() == CQL_NO )
				continue;

			//
			//  0 transaction counter can occur on create
			//
			if( tindex->OpenIndex()->TransactionCounter() )
				tindex->OpenIndex()->DecrementTransactionCounter();

			if( tindex->OpenIndex()->RollbackDirtyNodes() == CQL_FAILURE )
			{
				stack_.TransactionPop( ((ErrorManager&)aErrorMan()) );
				throw TransactionException( __FILE__, __LINE__ );
			}
		}
	}

	if( stack_.IsamFiles() )
	{
		for( rc = stack_.IsamFiles()->firstNode(); rc == CQL_SUCCESS; rc = stack_.IsamFiles()->nextNode() )
		{
			tisam = stack_.IsamFiles()->CurrentNode();

			if( ((pIsamFile)tisam->OpenIsam())->file()->IsOpen() == CQL_NO )
				continue;

			//
			//  0 transaction counter can occur on create
			//
			if( ((pIsamFile)tisam->OpenIsam())->transactionCounter() )
				((pIsamFile)tisam->OpenIsam())->decrementTransactionCounter();

			if( ((pIsamFile)tisam->OpenIsam())->rollbackDirtyRecords() == CQL_FAILURE )
				throw TransactionException( __FILE__, __LINE__ );
		}
	}

	if( stack_.Pages() )
	{
		while( ( rc = stack_.Pages()->firstNode() ) == CQL_SUCCESS )
		{
			tpage = stack_.Pages()->CurrentNode();

			if( tpage->FileMgr()->IsOpen() != CQL_NO )
			{
				if( transactionDebugging == CQL_YES )
					*hAEnv << "Shrinking page list for "
							  << tpage->FileMgr()->Name().text()
							  << " page "
							  << tpage->BasePage()->page()->pageNumber()
							  << ", list size="
							  << tpage->BasePage()->transactionPages().size() << "\n";
			
				try
				{
					tpage->BasePage()->rollback();
				}
				catch( ... )
				{
					stack_.TransactionPop( ((ErrorManager&)aErrorMan()) );
					throw ;
				}
			}

			if( stack_.Pages()->deleteIndexNode() == CQL_FAILURE )
			{
				stack_.TransactionPop( ((ErrorManager&)aErrorMan()) );
				throw TransactionException( __FILE__, __LINE__ );
			}
		}
	}

	stack_.TransactionPop( dynamic_cast< ErrorManager& >( aErrorMan() ) );
}


void DatabaseHandle::purgeTransactionInformationForIsamFile( AbstractTable *atable )
{
	pIsamFile iFile = dynamic_cast< IsamFile* >( atable );
	TransactionStackElement *tStackEl;

	if( csFunctionLogging )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "DatabaseHande::PurgeTransactionInformationForIsamFile\n" );

	switch( iFile->ttype() )
	{
	case CQL_CQL :
		break;

	default :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	//
	//  first get rid of pages which are part of the current transaction
	//  (index and file entries deleted by close)
	//
	if( stack_.Pages() )
	{
		if( stack_.Pages()->DeleteEntriesForFile( ((ErrorManager&)aErrorMan()),
												 ((US)iFile->file()->FileNumber()) ) == CQL_FAILURE )
			throw TransactionException( __FILE__, __LINE__ );
		if( stack_.Pages()->DeleteEntriesForFile( ((ErrorManager&)aErrorMan()),
												 ((US)iFile->index().File().FileNumber()) ) == CQL_FAILURE )
			throw TransactionException( __FILE__, __LINE__ );
	}

	if( stack_.Indices() )
		if( stack_.Indices()->DeleteEntryForIndex( ((ErrorManager&)aErrorMan()), &( iFile->index() ) ) == CQL_FAILURE )
			throw TransactionException( __FILE__, __LINE__ );

	if( stack_.IsamFiles() )
		if( stack_.IsamFiles()->DeleteEntryForIsamFile( ((ErrorManager&)aErrorMan()), iFile ) == CQL_FAILURE )
			throw TransactionException( __FILE__, __LINE__ );

	//
	//  now any other transactions on the stack
	//
	for( tStackEl = stack_.LastNestedTransaction(); tStackEl; tStackEl = stack_.PreviousNestedTransaction() )
	{
		if( tStackEl->Tpi() )
		{
			if( tStackEl->Tpi()->DeleteEntriesForFile( ((ErrorManager&)aErrorMan()),
													   ((US)iFile->file()->FileNumber()) ) == CQL_FAILURE )
				throw TransactionException( __FILE__, __LINE__ );
			if( tStackEl->Tpi()->DeleteEntriesForFile( ((ErrorManager&)aErrorMan()),
													   ((US)iFile->index().File().FileNumber()) ) == CQL_FAILURE )
				throw TransactionException( __FILE__, __LINE__ );
		}

		if( tStackEl->Ii() )
			if( tStackEl->Ii()->DeleteEntryForIndex( ((ErrorManager&)aErrorMan()), &( iFile->index() ) ) == CQL_FAILURE )
				throw TransactionException( __FILE__, __LINE__ );

		if( tStackEl->Ifiles() )
			if( tStackEl->Ifiles()->DeleteEntryForIsamFile( ((ErrorManager&)aErrorMan()), iFile ) == CQL_FAILURE )
				throw TransactionException( __FILE__, __LINE__ );
	}
}


DatabaseHandle::DatabaseHandle( const CqlString& uName,
								const CqlString& password,
								const CqlString& initialDirectory )
	: AbstractDatabaseHandle( uName, password, initialDirectory ),
	  errorManager_(),
	  openIsamFiles_(),
	  stack_(),
	  user_( 0 ),
	  userConfig_()
{
	CqlString _uName;
	if( uName.length() )
		_uName = uName;
	else
		_uName = "PUBLIC";

	CqlString _password;
	if( password != 0 && password.length() )
		_password = password;
	else
		_password = "";

	CqlString _initialDirectory;
	if( initialDirectory != 0 && initialDirectory.length() )
		_initialDirectory = initialDirectory;
	else
		_initialDirectory = Clib::sCurrentDirectory();

	//***********************  add check for null hAEnv here
	dynamic_cast< EnvironmentHandle* >( hAEnv )->GetUserId( &user_ );
}


DatabaseHandle::~DatabaseHandle( void )
{
	rollbackTransaction();
	dynamic_cast< EnvironmentHandle* >( hAEnv )->TransactionCleanup( *this );
	delete hAEnv;
}


void DatabaseHandle::disconnect( void )
{
}


UL DatabaseHandle::currentTransaction( void )
{
	return stack_.CurrentTransaction();
}


void DatabaseHandle::close( FileManager& fm )
{
	if( dynamic_cast< EnvironmentHandle* >( hAEnv )->Close( *this, fm ) == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );
}


FileManager* DatabaseHandle::open( CqlString& str )
{
	return dynamic_cast< EnvironmentHandle* >( hAEnv )->Open( *this, str );
}
