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


LogAnalysisIndex::LogAnalysisIndex( void ) : MemoryIndex()
{
}


LogAnalysisIndex::~LogAnalysisIndex( void )
{
}


NI LogAnalysisIndex::AddIndexNode( UL transNo, UNI logNo, RECID pos )
{
	pMemoryIndexNode newNode;

	newNode = new LogAnalysisIndexNode( transNo, logNo, pos );
	return MemoryIndex::addIndexNode( newNode );
}


NI LogAnalysisIndex::FindEqualKey( UL transNo )
{
	NI returnCode;
	pMemoryIndexNode tempNode;

	tempNode = new LogAnalysisIndexNode( transNo, 0, 0 );
	if( !tempNode )
		throw MemoryIndexException( __FILE__, __LINE__ );

	returnCode = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return returnCode;
}


LogAnalysisIndexNode::LogAnalysisIndexNode( const UL transNo, const UNI logNo, const RECID logPos )
	: LogPositionIndexNode( "", logNo, logPos ),
	  transactionNumber( transNo )
{
}


LogAnalysisIndexNode::~LogAnalysisIndexNode( void )
{
}


CqlConstants::CompareResult LogAnalysisIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pLogAnalysisIndexNode tnode = ((pLogAnalysisIndexNode)node2);

	if( transactionNumber < tnode->transactionNumber )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( transactionNumber > tnode->transactionNumber )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


LogCreateIndex::LogCreateIndex( void ) : LogDeleteIndex()
{
}


LogCreateIndex::~LogCreateIndex( void )
{
}


pLogCreateIndexNode LogCreateIndex::CurrentNode( void )
{
	return ((pLogCreateIndexNode)MemoryIndex::currentNode());
}


NI LogCreateIndex::AddIndexNode( const CqlString& fName,
																 const CqlString& tName,
																 const bool confirm,
																 const UNI logNo,
																 const RECID logPos )
{
	pMemoryIndexNode newNode;

	newNode = new LogCreateIndexNode( fName, tName, confirm, logNo, logPos );
	return MemoryIndex::addIndexNode( newNode );
}


LogCreateIndexNode::LogCreateIndexNode( const CqlString& fName, const CqlString& tName, const bool confirm, const UNI logNo, const RECID logPos )
	: LogDeleteIndexNode( fName, confirm, logNo, logPos ),
	  temporaryName( tName )
{
}


LogCreateIndexNode::~LogCreateIndexNode( void )
{
}


NI LogCreateIndexNode::RecoveryProcessing( EnvironmentHandle& dbenv, TransactionStack& stack, LogEntry& )
{
	if( transactionStartupDebugging == CQL_YES )
		*hAEnv << "LogCreateIndexNode::RecoveryProcessing" << "\n";

	if( dbenv.LogBeginReverseDeleteFile( stack, fileName(), TemporaryName(), LogNumber(), LogPosition() ) == CQL_FAILURE )
		return CQL_FAILURE;

	try
	{
		ClibFileManager::rename( fileName(), TemporaryName() );
	}
	catch( CqlException& ex )
	{
		dbenv.LogReverse( stack );
		throw ex;
	}

	if( dbenv.LogEndReverseDeleteFile( stack ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


LogDeleteIndex::LogDeleteIndex( void ) : MemoryIndex()
{
}


LogDeleteIndex::~LogDeleteIndex( void )
{
}


pLogDeleteIndexNode LogDeleteIndex::CurrentNode( void )
{
	return ((pLogDeleteIndexNode)MemoryIndex::currentNode());
}


NI LogDeleteIndex::AddIndexNode( const CqlString& fName, const bool confirmed, const UNI logNo, const RECID logPos )
{
	pMemoryIndexNode newNode;

	newNode = new LogDeleteIndexNode( fName, confirmed, logNo, logPos );
	return MemoryIndex::addIndexNode( newNode );
}


LogDeleteIndexNode::LogDeleteIndexNode( const CqlString& fName, const bool confirm, const UNI logNo, const RECID logPos )
	: LogPositionIndexNode( fName, logNo, logPos ),
	  confirmed( confirm )
{
}


LogDeleteIndexNode::~LogDeleteIndexNode( void )
{
}


CqlConstants::CompareResult LogDeleteIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pLogDeleteIndexNode tnode = ((pLogDeleteIndexNode)node2);

	return fileName().stringCompare( tnode->fileName() );
}


NI LogDeleteIndexNode::RecoveryProcessing( EnvironmentHandle& dbenv, TransactionStack& stack, LogEntry& )
{
	if( transactionStartupDebugging == CQL_YES )
		dbenv << "LogDeleteIndexNode::RecoveryProcessing" << "\n";

	if( dbenv.LogBeginReverseCreateFile( stack, fileName(), LogNumber(), LogPosition() ) == CQL_FAILURE )
		return CQL_FAILURE;

	try
	{
		ClibFileManager::deleteFile( fileName() );
	}
	catch( CqlException& ex )
	{
		dbenv.LogReverse( stack );
		throw ex;
	}

	if( dbenv.LogEndReverseCreateFile( stack ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


LogEntry::LogEntry( void )
	: command( ((enum LogCommands*)0) ),
	  dataLength( ((pUL)0) ),
	  entryBuffer( ((pUC)0) ),
	  fileName( ((pNC)0) ),
	  footerEntryLength( ((pUL)0) ),
	  logData( ((pUC)0) ),
	  logEntryLength( ((pUL)0) ),
	  pageNumber( ((pUL)0) ),
	  temporaryName( ((pNC)0) ),
	  transactionNumber( ((pUL)0) ),
	  undoFlag( ((pNI)0) ),
	  undoLog( ((pUNI)0) ),
	  undoPosition( ((pRECID)0) )
{
}


LogEntry::~LogEntry( void )
{
	if( entryBuffer )
	{
		delete [] entryBuffer;
		entryBuffer = ((pUC)0);
	}
}


NI LogEntry::SetBuffer( UL len )
{
	pUC pos;
	UL dataLen = len - ( sizeof( *logEntryLength )
						 + sizeof( *dataLength )
						 + sizeof( *command )
						 + sizeof( *transactionNumber )
						 + sizeof( *pageNumber)
						 + sizeof( *undoFlag )
						 + sizeof( *undoLog )
						 + sizeof( *undoPosition )
						 + CQL_MAXIMUM_FILE_NAME_LENGTH
						 + CQL_MAXIMUM_FILE_NAME_LENGTH
						 + sizeof( *footerEntryLength ) );

	if( entryBuffer )
		delete [] entryBuffer;

	entryBuffer = new UC[ len ];
	if( !entryBuffer )
		throw TransactionException( "Transaction log entry decoding error", EC_TRANSACTION_ERROR, __FILE__, __LINE__ );

	pos = entryBuffer;

	logEntryLength = ((pUL)pos);
	pos += sizeof( *logEntryLength );

	dataLength = ((pUL)pos);
	pos += sizeof( *dataLength );

	command = ((enum LogCommands *)pos);
	pos += sizeof( *command );

	transactionNumber = ((pUL)pos);
	pos += sizeof( *transactionNumber );

	pageNumber = ((pUL)pos);
	pos += sizeof( *pageNumber );

	undoFlag = ((pNI)pos);
	pos += sizeof( *undoFlag );

	undoLog = ((pUNI)pos);
	pos += sizeof( *undoLog );

	undoPosition = ((pRECID)pos);
	pos += sizeof( *undoPosition );

	fileName = ((pNC)pos);
	pos += CQL_MAXIMUM_FILE_NAME_LENGTH;

	temporaryName = ((pNC)pos);
	pos += CQL_MAXIMUM_FILE_NAME_LENGTH;

	logData = pos;
	pos += dataLen;

	footerEntryLength = ((pUL)pos);

	return CQL_SUCCESS;
}


NI LogEntry::Setup(
	TransactionStack& stack,
	enum LogCommands cmd,
	CqlString& fName,
	pUC data,
	UL dataLen,
	NI uFlag,
	UNI uLog,
	UL uPos,
	CqlString& tempName,
	NI zeroTransactionNumber )
{
	UL entrySize = sizeof( *logEntryLength )
		+ sizeof( *dataLength )
		+ sizeof( *command )
		+ sizeof( *transactionNumber )
		+ sizeof( *pageNumber )
		+ sizeof( *undoFlag )
		+ sizeof( *undoLog )
		+ sizeof( *undoPosition )
		+ CQL_MAXIMUM_FILE_NAME_LENGTH
		+ CQL_MAXIMUM_FILE_NAME_LENGTH
		+ dataLen
		+ sizeof( *footerEntryLength );

	if( SetBuffer( entrySize ) == CQL_FAILURE )
		return CQL_FAILURE;

	memset( entryBuffer, 0, ((UNI)entrySize) );

	*logEntryLength = entrySize;
	*footerEntryLength = entrySize;
	*command = cmd;

	//
	//  memset clears everything, so *transactionNumber is zero if we do nothing here
	//
	if( zeroTransactionNumber != CQL_YES )
		*transactionNumber = stack.CurrentTransaction();

	*undoFlag = uFlag;
	*undoLog = uLog;
	*undoPosition = uPos;

	if( dataLen )
	{
		memcpy( logData, data, ((UNI)dataLen) );
		*dataLength = dataLen;
	}

	strcpy( fileName, fName.text() );
	strcpy( temporaryName, tempName.text() );

	return CQL_SUCCESS;
}


LogPageIndex::LogPageIndex( void ) : MemoryIndex()
{
}


LogPageIndex::~LogPageIndex( void )
{
}


pLogPageIndexNode LogPageIndex::CurrentNode( void )
{
	return ((pLogPageIndexNode)MemoryIndex::currentNode() );
}


NI LogPageIndex::AddIndexNode( CqlString& fName, UL pageNo, UNI logNo, RECID logPos )
{
	pMemoryIndexNode newNode;

	newNode = new LogPageIndexNode( fName, pageNo, logNo, logPos );
	return MemoryIndex::addIndexNode( newNode );
}


NI LogPageIndex::FindEqualKey( CqlString& fName, UL pageNo )
{
	NI rc;
	pMemoryIndexNode tempNode;

	tempNode = new LogPageIndexNode( fName, pageNo );
	if( !tempNode )
		throw MemoryIndexException( __FILE__, __LINE__ );

	rc = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return rc;
}


LogPageIndexNode::LogPageIndexNode( const CqlString& fName, const UL pageNo, const UNI logNo, const RECID logPos )
	: LogPositionIndexNode( fName, logNo, logPos ),
	  pageNumber( pageNo )
{
}


LogPageIndexNode::~LogPageIndexNode( void )
{
}


NI LogPageIndexNode::RecoveryProcessing( EnvironmentHandle&, TransactionStack&, LogEntry &logEntry )
{
	RECID endPosition, pagePosition;
	pUC pageSpace, newPage = ((pUC)0);
	pUL diskRevision, logRevision = ((pUL)0);
	NI rc, newPageAllocated = CQL_NO;

	if( transactionStartupDebugging == CQL_YES )
		*hAEnv << "LogPageIndexNode::RecoveryProcessing" << "\n";

	pageSpace = new UC[ CQL_PAGE_SIZE ];
	if( !pageSpace )
		throw TransactionException( __FILE__, __LINE__ );
	memset( pageSpace, 0, CQL_PAGE_SIZE );

	//  open the file
	ClibFileManager clibFile;
	clibFile.open( fileName(), endPosition );

	rc = CQL_FAILURE;

	pagePosition = pageNumber * CQL_PAGE_SIZE;
	if( pagePosition > endPosition )
	{
		UL endPage;

		endPage = ( endPosition + 1 ) / CQL_PAGE_SIZE;
		try
		{
			clibFile.seekToEnd();
		}
		catch( CqlException& ex )
		{
			clibFile.close();
			if( newPageAllocated == CQL_YES )
				delete [] newPage;
			throw ex;
		}

		//  write pages 0 zeros to and including the page in the log
		try
		{
			while( endPage++ <= pageNumber )
				clibFile.write( ((void*)pageSpace), CQL_PAGE_SIZE );
		}
		catch( CqlException& ex )
		{
			clibFile.close();
			if( newPageAllocated == CQL_YES )
				delete [] newPage;
			throw ex;
		}

		endPosition = pagePosition - 1;
	}

	try
	{
		clibFile.outputSeek( pagePosition );
		clibFile.read( ((void*)pageSpace), CQL_PAGE_SIZE );
	}
	catch( CqlException& ex )
	{
		clibFile.close();
		if( newPageAllocated == CQL_YES )
			delete [] newPage;
		throw ex;
	}

	diskRevision = ((pUL)pageSpace);
	switch( logEntry.Command() )
	{
	case LogEntry::ADD_PAGE :
		newPage = logEntry.LogData();
		logRevision = ((pUL)newPage);
		break;

	case LogEntry::UPDATE_PAGE :
		newPage = logEntry.LogData() + CQL_PAGE_SIZE;
		logRevision = ((pUL)newPage);
		break;

	case LogEntry::DELETE_PAGE :
		newPage = ((pUC)0);
		if( *diskRevision != 0 )
		{
			newPage = new UC[ CQL_PAGE_SIZE ];
			if( !newPage )
				goto RecoveryEnd;
			memset( newPage, 0, CQL_PAGE_SIZE );
			newPageAllocated = CQL_YES;
		}
		break;

	default :
		goto RecoveryEnd;
	}

	if( !diskRevision || *diskRevision < *logRevision )
	{
		try
		{
			//  write the log page
			clibFile.outputSeek( pagePosition );
			clibFile.write( ((void*)newPage), CQL_PAGE_SIZE );
		}
		catch( CqlException& ex )
		{
			clibFile.close();
			if( newPageAllocated == CQL_YES )
				delete [] newPage;
			throw ex;
		}
	}

	rc = CQL_SUCCESS;

RecoveryEnd :

	clibFile.close();

	if( newPageAllocated == CQL_YES )
		delete [] newPage;

	return rc;
}


CqlConstants::CompareResult LogPageIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pLogPageIndexNode tnode = ((pLogPageIndexNode)node2);
	NI compareResult;

	compareResult = fileName().stringCompare( tnode->fileName() );
	if( compareResult < 0 )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( compareResult > 0 )
		return CqlConstants::THIS_GREATER_THAN_OTHER;

	if( pageNumber < tnode->pageNumber )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( pageNumber > tnode->pageNumber )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


//  this is called when an operation which has been logged fails (file creation or deletion)
LogPositionIndexNode::LogPositionIndexNode( const CqlString& fName, const UNI logNo, const RECID logPos )
	: MemoryIndexNode(),
	  fileName_( fName ),
	  logNumber( logNo ),
	  logPosition( logPos )
{
}


LogPositionIndexNode::~LogPositionIndexNode( void )
{
}


void LogPositionIndexNode::releaseMemory( void )
{
}


CqlConstants::CompareResult LogPositionIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pLogPositionIndexNode tnode = ((pLogPositionIndexNode)node2);

	if( logNumber < tnode->logNumber )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( logNumber > tnode->logNumber )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else if( logPosition < tnode->logPosition )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( logPosition > tnode->logPosition )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


LogUndoneIndex::LogUndoneIndex( void ) : MemoryIndex()
{
}


LogUndoneIndex::~LogUndoneIndex( void )
{
}


pLogPositionIndexNode LogUndoneIndex::CurrentNode( void )
{
	return ((pLogPositionIndexNode)MemoryIndex::currentNode());
}


NI LogUndoneIndex::AddIndexNode( UNI logNo, RECID logPos )
{
	pMemoryIndexNode newNode;

	newNode = new LogUndoneIndexNode( logNo, logPos );
	return MemoryIndex::addIndexNode( newNode );
}


NI LogUndoneIndex::FindEqualKey( UNI logNo, RECID logPos )
{
	NI rc;
	pMemoryIndexNode tempNode;

	tempNode = new LogUndoneIndexNode( logNo, logPos );
	if( !tempNode )
		throw MemoryIndexException( __FILE__, __LINE__ );

	rc = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return rc;
}


LogUndoneIndexNode::LogUndoneIndexNode( const UNI logNo, const RECID logPos ) : LogPositionIndexNode( "", logNo, logPos )
{
}


LogUndoneIndexNode::~LogUndoneIndexNode( void )
{
}


TransactionManager::~TransactionManager( void )
{
}


TransactionManager::TransactionManager( void )
	: LogEntry(),
	  waitees(),
	  waitors(),
	  pushbackFlag( CQL_NO ),
	  currentLog( 0 ),
	  currentLogNumber( 0 ),
	  currentPosition( 0 ),
	  endOfLogFile( 0 ),
	  logLog(),
	  logs( 0 ),
	  transactionCounter( 0 )
{
}


NI TransactionManager::ReadPreviousLogEntry( LogEntry &logEntry, ClibFileManager *curLog, pRECID logPos )
{
	RECID lpos;
	UL entryLength;

	if( *logPos == 0 )
		return CQL_NOT_FOUND;

	lpos = *logPos - sizeof( UL );
	curLog->inputSeek( lpos );
	curLog->read( ((void*)&entryLength), sizeof( UL ) );
	lpos -= ( entryLength - sizeof( UL ) );
	curLog->inputSeek( lpos );

	if( logEntry.SetBuffer( entryLength ) == CQL_FAILURE )
		return CQL_FAILURE;

	curLog->read( ((void*)logEntry.EntryBuffer()), ((UNI)entryLength) ) ;
	*logPos = lpos;
	return CQL_SUCCESS;
}


NI TransactionManager::ReadLogEntry( LogEntry &logEntry, ClibFileManager *log, RECID logPos )
{
	UL entryLength;

	log->inputSeek( logPos );
	log->read( ((void*)&entryLength), sizeof( UL ) );

	if( logEntry.SetBuffer( entryLength ) == CQL_FAILURE )
		return CQL_FAILURE;

	log->inputSeek( logPos );
	log->read( ((void*)logEntry.EntryBuffer()), ((UNI)entryLength) );
	return CQL_SUCCESS;
}


void TransactionManager::makeLogName( CqlString& result, const CqlString& nameBase, UNI logNum, const CqlString& initialDirectory )
{
	NC nameSpace[ 100 ];
	if( initialDirectory.length() )
		sprintf( nameSpace,
				 "%s/%s%d",
				 initialDirectory.text(),
				 nameBase.text(),
				 logNum );
	else
		sprintf( nameSpace, "%s%d", nameBase.text(), logNum );
	result = nameSpace;
}


pTransactionStackElement TransactionStack::LastNestedTransaction( void )
{
	return ((pTransactionStackElement)last());
}


pTransactionStackElement TransactionStack::PreviousNestedTransaction( void )
{
	return ((pTransactionStackElement)prev());
}


NI TransactionStack::TransactionPush( ErrorManager& em, UL tnum )
{
	pTransactionStackElement tse;

	tse = new TransactionStackElement( currentTransaction, pages, indices, isamFiles );
	if( !tse )
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );

	push( tse );

	pages = new TransactionPageIndex;
	if( !pages )
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );

	indices = new IndexIndex;
	if( !indices )
	{
		delete pages;
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );
	}

	isamFiles = new IsamIndex;
	if( !isamFiles )
	{
		delete indices;
		delete pages;
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );
	}

	currentTransaction = tnum;
	return CQL_SUCCESS;
}


NI TransactionStack::TransactionPop( ErrorManager& em )
{
	pTransactionStackElement tse;

	if( pages )
	{
		pages->destroyIndex();
		delete pages;
	}
	if( indices )
	{
		indices->destroyIndex();
		delete indices;
	}
	if( isamFiles )
	{
		isamFiles->destroyIndex();
		delete isamFiles;
	}

	tse = pop();
	if( !tse )
		return em.returnError( STACK_UNDERFLOW, __FILE__, __LINE__ );

	currentTransaction = tse->PreviousTransactionNumber();
	pages = tse->Tpi();
	indices = tse->Ii();
	isamFiles = tse->Ifiles();
	delete tse;
	return CQL_SUCCESS;
}


TransactionStack::~TransactionStack( void )
{
}


TransactionStack::TransactionStack( void ) : TransactionStackList(), currentTransaction( 0 ), pages( 0 ), indices( 0 ), isamFiles( 0 )
{
}


TransactionStackElement::TransactionStackElement( UL tnum, TransactionPageIndex *t, IndexIndex *i, IsamIndex *f )
	: TransactionStackElementListElement(),
	  previousTransactionNumber( tnum ),
	  tpi( t ),
	  ii( i ),
	  ifiles( f )
{
}


TransactionStackElement::~TransactionStackElement( void )
{
}
