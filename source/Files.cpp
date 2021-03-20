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
#include <iostream>

FileManager::FileManager( DatabaseHandle& dbHandle, TableType _type )
	: BufferSpaceIndex(),
	  bufferOffset( 0 ),
	  bufferPointer( ((pUC)0) ),
	  clibFile(),
	  currentReadBufferPage( 0 ),
	  currentReadPosition( ((RECID)0) ),
	  currentWriteBufferPage( 0 ),
	  currentWritePosition( ((RECID)0) ),
	  endOfFile( ((RECID)0) ),
	  fileExtensionPage( 0 ),
	  fileNumber( 0 ),
	  hDb( &dbHandle ),
	  name(),
	  openCount( 0 ),
	  propagationCounter( 0 ),
	  propagationTransactionNumber( 0 ),
	  readPageNumber( 0 ),
	  transactionCounter( 0 ),
	  type_( _type ),
	  writePageNumber( 0 ),
	  isOpen( CQL_NO )
{
}


FileManager::~FileManager( void )
{
}


NI FileManager::Assign( FileManager& other )
{
	*( dynamic_cast< BufferSpaceIndex* >( this ) ) = other;
	bufferOffset = other.bufferOffset;
	bufferPointer = other.bufferPointer;

	clibFile = other.clibFile;

	if( other.currentReadBufferPage )
	{
		currentReadBufferPage = new BaseBufferPage( other.currentReadBufferPage->page() );
		if( !currentReadBufferPage )
			return ErrorMan().returnError( ALLOCATION, __FILE__, __LINE__ );

		*currentReadBufferPage = *other.currentReadBufferPage;
	}
	else
		currentReadBufferPage = 0;

	currentReadPosition = other.currentReadPosition;

	if( other.currentWriteBufferPage )
	{
		currentWriteBufferPage = new BaseBufferPage( other.currentWriteBufferPage->page() );
		if( !currentWriteBufferPage )
			return ErrorMan().returnError( ALLOCATION, __FILE__, __LINE__ );

		*currentWriteBufferPage = *other.currentWriteBufferPage;
	}
	else
		currentWriteBufferPage = 0;

	currentWritePosition = other.currentWritePosition;
	endOfFile = other.endOfFile;
	fileExtensionPage = other.fileExtensionPage;
	fileNumber = other.fileNumber;

	name = other.name;
	//exception

	openCount = other.openCount;
	propagationCounter = other.propagationCounter;
	readPageNumber = other.readPageNumber;
	transactionCounter = other.transactionCounter;
	writePageNumber = other.writePageNumber;
	isOpen = other.isOpen;
	type_ = other.type_;

	return CQL_SUCCESS;
}


NI FileManager::Close( BufferManager& )
{
	if( isOpen == ((BFT)CQL_NO) )
		return CQL_SUCCESS;

	isOpen = CQL_NO;

	if( fileDebugging )
		*hAEnv << "close of " << name.text() << "\n";

	if( !temporary() )
		clibFile.close();

	if( ReleasePagesForFile() == CQL_FAILURE )
		return CQL_FAILURE;

	name.reset();

	return CQL_SUCCESS;
}


NI FileManager::Create( CqlString& fname )
{
	name = fname;
	//exception

	if( fileDebugging )
		*hAEnv << "Create " << name.text() << "\n";

	if( temporary() == false && dynamic_cast< EnvironmentHandle* >( hAEnv )->LogBeginCreateFile( Stack(), name ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( !temporary() )
	{
		try
		{
			clibFile.create( name );
		}
		catch( CqlException& ex )
		{
			dynamic_cast< EnvironmentHandle* >( hAEnv )->LogReverse( Stack() );
			throw ex;
		}
	}

	if( temporary() == false && dynamic_cast< EnvironmentHandle* >( hAEnv )->LogEndCreateFile( Stack() ) == CQL_FAILURE )
		return CQL_FAILURE;

	fileNumber = static_cast< US >( dynamic_cast< EnvironmentHandle* >( hAEnv )->getFileNumber() );

	if( dynamic_cast< EnvironmentHandle* >( hAEnv )->AddIndexNode( ErrorMan(), fname, this ) == CQL_FAILURE )
		return CQL_FAILURE;

	isOpen = CQL_YES;
	openCount = 1;
	return CQL_SUCCESS;
}


void FileManager::deleteFile( const CqlString& fname )
{
	EnvironmentHandle *henv = dynamic_cast<EnvironmentHandle*>( hAEnv );
	henv->LogBeginDeleteFile( Stack(), fname );
	ClibFileManager::deleteFile( fname );
	henv->LogEndDeleteFile( Stack() );
}


NI FileManager::DeletePageFromIndex( UL pageNum )
{
	if( !findEqualKey( fileNumber, pageNum ) )
		return CQL_FAILURE;

	if( deleteIndexNode() == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


ErrorManager& FileManager::ErrorMan( void )
{
	return ((ErrorManager&)hDb->aErrorMan());
}


NI FileManager::InputSeek( RECID location )
{
	currentReadPosition = location;
	return Seek( location, &currentReadBufferPage, &readPageNumber );
}


NI FileManager::Open( CqlString& fname, TableType _type )
{
	name = fname;

	if( fileDebugging )
		*hAEnv << "Open, file " << name.text() << "\n";

	type_ = _type;

	if( !temporary() )
	{
		try
		{
			clibFile.open( name, endOfFile );
		}
		catch( CqlException& ex )
		{
			if( fileDebugging )
			{
				*hAEnv << "Open of " << name.text() << " failed" << "\n";
				*hAEnv << "Exception: " << ex << "\n";
			}

			//  This will eventually throw
			return CQL_FAILURE;
		}
	}

	fileExtensionPage = endOfFile / CQL_PAGE_SIZE;
	currentReadPosition = currentWritePosition = 0;
	fileNumber = static_cast< US >( dynamic_cast< EnvironmentHandle* >( hAEnv )->getFileNumber() );
	isOpen = CQL_YES;
	return CQL_SUCCESS;
}


//  OpenForAppend is never called for user files
NI FileManager::OpenForAppend( CqlString& fileName )
{
	clibFile.openForAppend( fileName, endOfFile );
	currentReadPosition = currentWritePosition = endOfFile;
	return CQL_SUCCESS;
}


NI FileManager::OutputSeek( RECID location )
{
	if( btreePrinting == CQL_YES )
		fprintf( stderr, "%s, %d, OutputSeek to %ld\n", __FILE__, __LINE__, location );

	currentWritePosition = location;
	return Seek( location, &currentWriteBufferPage, &writePageNumber );
}


NI FileManager::PurgePage( BaseBufferPage *basePage )
{
	if( currentReadBufferPage == basePage )
		currentReadBufferPage = 0;
	if( currentWriteBufferPage == basePage )
		currentWriteBufferPage = 0;

	//
	//  not found is an error in this case
	//
	bool rc = findEqualKey( fileNumber, basePage->page()->pageNumber() );
	if( !rc )
		return CQL_FAILURE;

	if( deleteIndexNode() == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


FileManager& FileManager::operator<<( const NI i )
{
	write( ((void*)&i), sizeof( i ) );
	return *this;
}


FileManager& FileManager::operator>>( NI& i )
{
	read( ((void*)&i), sizeof( i ) );
	return *this;
}


FileManager& FileManager::operator<<( const UNI ui )
{
	write( ((void*)&ui), sizeof( ui ) );
	return *this;
}


FileManager& FileManager::operator>>( UNI& ui )
{
	read( ((void*)&ui), sizeof( ui ) );
	return *this;
}


FileManager& FileManager::operator<<( const US us )
{
	write( ((void*)&us), sizeof( us ) );
	return *this;
}


FileManager& FileManager::operator>>( US& us )
{
	read( ((void*)&us), sizeof( us ) );
	return *this;
}


FileManager& FileManager::operator << ( const AbstractValue *cav )
{
	bool valueExists;
	if( !cav )
	{
		valueExists = false;
		*this << valueExists;
		return *this;
	}

	valueExists = true;
	*this << valueExists;

	AbstractValue *av = const_cast< AbstractValue* >( cav );
	*this << av->columnType();
	av->output( *this );
	return *this;
}


FileManager& FileManager::operator >> ( AbstractValue*& av )
{
	bool valueExists;
	*this >> valueExists;
	if( !valueExists )
	{
		av = 0;
		return *this;
	}
	CqlColumnTypes ctype;
	*this >> ctype;
	av = AbstractValue::createObject( ctype );
	av->input( *this );
	return *this;
}


FileManager& FileManager::operator << ( const CqlColumnTypes& _type )
{
	*this << _type.defaultValue()
		  << _type.notNull()
		  << _type.typeLength()
		  << _type.cTypeName()
		  << _type.typeType();

	return *this;
}


FileManager& FileManager::operator >> ( CqlColumnTypes& _type )
{
	AbstractValue *av;
	CqlColumnType ttype;
	UL tlength;
	bool nn;
	*this >> av >> nn >> tlength >> _type.typeName() >> ttype;
	_type.defaultValue( av );
	_type.typeLength( tlength );
	_type.typeType( ttype );
	if( nn )
		_type.setNotNull();
	else
		_type.clearNotNull();

	return *this;
}


FileManager& FileManager::operator<<( void*& ptr )
{
	write( ((void*)&ptr), sizeof( ptr ) );
	return *this;
}


FileManager& FileManager::operator>>( void*& ptr )
{
	read( ((void*)&ptr), sizeof( ptr ) );
	return *this;
}


FileManager& FileManager::operator<<( const D d )
{
	write( ((void*)&d), sizeof( d ) );
	return *this;
}


FileManager& FileManager::operator>>( D& d )
{
	read( ((void*)&d), sizeof( d ) );
	return *this;
}


FileManager& FileManager::operator<<( const UC uc )
{
	write( ((void*)&uc), sizeof( uc ) );
	return *this;
}


FileManager& FileManager::operator>>( UC& uc )
{
	read( ((void*)&uc), sizeof( uc ) );
	return *this;
}


FileManager& FileManager::operator<<( const AccessorTypes acType )
{
	write( ((void*)&acType), sizeof( acType ) );
	return *this;
}


FileManager& FileManager::operator>>( AccessorTypes& acType )
{
	read( ((void*)&acType), sizeof( acType ) );
	return *this;
}


FileManager& FileManager::operator<<( const L l )
{
	write( ((void*)&l), sizeof( l ) );
	return *this;
}


FileManager& FileManager::operator>>( L& l )
{
	read( ((void*)&l), sizeof( l ) );
	return *this;
}


FileManager& FileManager::operator<<( const F f )
{
	write( ((void*)&f), sizeof( f ) );
	return *this;
}


FileManager& FileManager::operator>>( F& f )
{
	read( ((void*)&f), sizeof( f ) );
	return *this;
}


FileManager& FileManager::operator<<( const DecimalValue& dv )
{
	write( ((void*)&dv), sizeof( dv ) );
	return *this;
}


FileManager& FileManager::operator>>( DecimalValue& dv )
{
	read( ((void*)&dv), sizeof( dv ) );
	return *this;
}


#ifndef CQL_BOOL_IS_INT

FileManager& FileManager::operator << ( const bool b )
{
	write( ((void*)&b), sizeof( b ) );
	return *this;
}


FileManager& FileManager::operator >> ( bool& b )
{
	read( ((void*)&b), sizeof( b ) );
	return *this;
}

#endif  //  ~CQL_BOOL_IS_INT


FileManager& FileManager::operator<<( const NC c )
{
	write( ((void*)&c), sizeof( c ) );
	return *this;
}


FileManager& FileManager::operator>>( NC& c )
{
	read( ((void*)&c), sizeof( c ) );
	return *this;
}


FileManager& FileManager::operator<<( const S s )
{
	write( ((void*)&s), sizeof( s ) );
	return *this;
}


FileManager& FileManager::operator>>( S& s )
{
	read( ((void*)&s), sizeof( s ) );
	return *this;
}


FileManager& FileManager::operator<<( const BigintValue& bv )
{
	write( ((void*)&bv), sizeof( bv ) );
	return *this;
}


FileManager& FileManager::operator>>( BigintValue& bv )
{
	read( ((void*)&bv), sizeof( bv ) );
	return *this;
}


FileManager& FileManager::operator<<( const UL ul )
{
	write( ((void*)&ul), sizeof( ul ) );
	return *this;
}


FileManager& FileManager::operator>>( UL& ul )
{
	read( ((void*)&ul), sizeof( ul ) );
	return *this;
}


FileManager& FileManager::operator<<( const DateValue& dv )
{
	write( ((void*)&dv), sizeof( dv ) );
	return *this;
}


FileManager& FileManager::operator>>( DateValue& dv )
{
	read( ((void*)&dv), sizeof( dv ) );
	return *this;
}


FileManager& FileManager::operator<<( const TimeValue& tv )
{
	write( ((void*)&tv), sizeof( tv ) );
	return *this;
}


FileManager& FileManager::operator>>( TimeValue& tv )
{
	read( ((void*)&tv), sizeof( tv ) );
	return *this;
}


FileManager& FileManager::operator << ( const CqlString& str )
{
	UL length = str.length();
	*this << length;
	write( ((void*)str.text()), length );
	return *this;
}


FileManager& FileManager::operator>>( CqlString& str )
{
	UL length;

	*this >> length;
	str.setString( length );
	read( ((void*)str.text()), length );
	return *this;
}


FileManager& FileManager::operator << ( const AbstractSegmentDescriptor *seg )
{
	AbstractSegmentDescriptor *ncseg = const_cast< AbstractSegmentDescriptor* >( seg );
	*this << ncseg->columnName() << seg->columnNumber() << seg->segmentNumber() << seg->segmentType();
	return *this;
}


FileManager& FileManager::operator << ( const SegmentType st )
{
	write( ((void*)&st), sizeof( st ) );
	return *this;
}


FileManager& FileManager::operator >> ( SegmentType& st )
{
	read( ((void*)&st), sizeof( st ) );
	return *this;
}


FileManager& FileManager::operator << ( const CqlColumnType cct )
{
	CqlColumnType ct = cct;
	write( reinterpret_cast< void* >( &ct ), sizeof( ct ) );
	return *this;
}


FileManager& FileManager::operator >> ( CqlColumnType& ct )
{
	read( reinterpret_cast< void* >( &ct ), sizeof( ct ) );
	return *this;
}


FileManager& FileManager::operator << ( const SignValues csv )
{
	SignValues sv = csv;
	write( reinterpret_cast< void* >( &sv ), sizeof( sv ) );
	return *this;
}


FileManager& FileManager::operator >> ( SignValues& sv )
{
	read( reinterpret_cast< void* >( &sv ), sizeof( sv ) );
	return *this;
}


FileManager& FileManager::operator >> ( AbstractSegmentDescriptor **seg )
{
	CqlString cname;
	SegmentType st;
	US cno;
	US segno;
	*this >> cname >> cno >> segno >> st;
	SegmentTypes stype( cname, cno, st );
	AbstractSegmentDescriptor *lseg = AbstractSegmentDescriptor::createObject( segno, stype );
	if( !lseg )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	*seg = lseg;
	return *this;
}


NI FileManager::ReleasePagesForFile( void )
{
	BaseBufferPage *basePage;

	for( basePage = firstNode(); basePage; basePage = nextNode() )
		dynamic_cast< EnvironmentHandle* >( hAEnv )->releasePage( basePage );

	destroyIndex();
	return CQL_SUCCESS;
}


NI FileManager::Seek( RECID location, BaseBufferPage **bp, pUL pno )
{
	UL pageNum;

	if( btreePrinting == CQL_YES )
		fprintf( stderr, "%s, %d, location %ld\n", __FILE__, __LINE__, location );

	pageNum = ((UL)location);
	pageNum /= CQL_LOGICAL_PAGE_SIZE;

	if( btreePrinting == CQL_YES )
		fprintf( stderr, "%s, %d, pageNum %lu\n", __FILE__, __LINE__, pageNum );

	if( (*bp) && *pno == pageNum )
		return CQL_SUCCESS;

	if( GetPage( pageNum, pno, bp ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


TransactionStack& FileManager::Stack( void )
{
	return hDb->stack();
}


void FileManager::UpdateFileExtensionPage( UL pno )
{
	if( pno >= fileExtensionPage )
		fileExtensionPage = pno + 1;
}


void FileManager::readLogicalPage( pUC dest, RECID pos )
{
	if( InputSeek( pos ) == CQL_FAILURE )
		throw FileSystemException( __FILE__, __LINE__ );

	read( dest, CQL_LOGICAL_PAGE_SIZE );
}


void FileManager::writeLock( RECID loc )
{
	currentWritePosition = loc;
	if( GetBufferPointerForWrite() == CQL_FAILURE )
		throw FileSystemException( __FILE__, __LINE__ );
}


void FileManager::IncrementTransactionCounterIfZero( void )
{
	if( transactionCounter == 0 )
		transactionCounter = 1;
}


void FileManager::read( void* userPtr, UNI amount )
{
	if( !amount )
		return;

	UNI amountFromThisBuffer;
	pUC ptr = ((pUC)userPtr);

	if( fileDebugging )
		*hAEnv << "read, file " << name.text() << " amount " << amount << "\n";

	if( GetBufferPointerForRead() == CQL_FAILURE )
		throw FileSystemException( __FILE__, __LINE__ );

	if( bufferOffset + amount < CQL_LOGICAL_PAGE_SIZE )
	{
		//  entire read is within this page
		memcpy( ptr, bufferPointer, amount );
		currentReadPosition += amount;
		return;
	}

	//  still here, so page boundary (or boundaries) are crossed

	//  read the rest of the current page
	amountFromThisBuffer = CQL_LOGICAL_PAGE_SIZE - bufferOffset;
	amount -= amountFromThisBuffer;
	memcpy( ptr, bufferPointer, amountFromThisBuffer );
	currentReadPosition += amountFromThisBuffer;
	ptr += amountFromThisBuffer;

	while( amount > CQL_LOGICAL_PAGE_SIZE )
	{
		if( GetBufferPointerForRead() == CQL_FAILURE )
			throw FileSystemException( __FILE__, __LINE__ );

		memcpy( ptr, bufferPointer, CQL_LOGICAL_PAGE_SIZE );
		currentReadPosition += CQL_LOGICAL_PAGE_SIZE;
		ptr += CQL_LOGICAL_PAGE_SIZE;
		amount -= CQL_LOGICAL_PAGE_SIZE;
	}

	if( amount )
	{
		if( GetBufferPointerForRead() == CQL_FAILURE )
			throw FileSystemException( __FILE__, __LINE__ );

		memcpy( ptr, bufferPointer, amount );
		currentReadPosition += amount;
	}
}


void FileManager::write( void* userPtr, UNI amount )
{
	if( !amount )
		return;

	UNI amountForThisBuffer;
	pUC ptr = ((pUC)userPtr);

	if( fileDebugging )
		*hAEnv << "write, file " << name.text() << " amount " << amount << "\n";

	if( GetBufferPointerForWrite() == CQL_FAILURE )
		throw FileSystemException( __FILE__, __LINE__ );

	if( bufferOffset + amount < CQL_LOGICAL_PAGE_SIZE )
	{
		//  entire write is within this page
		memcpy( bufferPointer, ptr, amount );
		currentWritePosition += amount;
		return;
	}

	//  still here, so page boundary (or boundaries) are crossed

	//  write into the rest of the current page
	amountForThisBuffer = CQL_LOGICAL_PAGE_SIZE - bufferOffset;
	amount -= amountForThisBuffer;
	memcpy( bufferPointer, ptr, amountForThisBuffer );
	currentWritePosition += amountForThisBuffer;
	ptr += amountForThisBuffer;

	while( amount > CQL_LOGICAL_PAGE_SIZE )
	{
		if( GetBufferPointerForWrite() == CQL_FAILURE )
			throw FileSystemException( __FILE__, __LINE__ );

		memcpy( bufferPointer, ptr, CQL_LOGICAL_PAGE_SIZE );
		currentWritePosition += CQL_LOGICAL_PAGE_SIZE;
		ptr += CQL_LOGICAL_PAGE_SIZE;
		amount -= CQL_LOGICAL_PAGE_SIZE;
	}

	if( amount )
	{
		if( GetBufferPointerForWrite() == CQL_FAILURE )
			throw FileSystemException( __FILE__, __LINE__ );

		memcpy( bufferPointer, ptr, amount );
		currentWritePosition += amount;
	}
}


NI FileManager::GetBufferPointerForWrite( void )
{
	NI rc;
	pLockIndexNode lockIndexNode;
	pDeadlockGraphIndexNode deadlockGraphIndexNode;
	BufferPage *lastPage;
	pPageChainElement lastElement;

	if( !currentWriteBufferPage || writePageNumber != ((UL)( currentWritePosition / ((RECID)CQL_LOGICAL_PAGE_SIZE) ) ) )
		if( GetWritePage( currentWritePosition / ((RECID)CQL_LOGICAL_PAGE_SIZE) ) == CQL_FAILURE )
			return CQL_FAILURE;

	lastElement = currentWriteBufferPage->transactionPages().last();
	if( lastElement )
		lastPage = lastElement->Page();
	else
		lastPage = currentWriteBufferPage->page();

	dynamic_cast< EnvironmentHandle* >( hAEnv )->bringPageIntoMemory( lastPage );

	if( currentWriteBufferPage->page()->uncommitted() )
	{
		if( lastPage->user() != hDb->user() )
		{
			//  can we wait for it?
			if( dynamic_cast< EnvironmentHandle* >( hAEnv )->Waitors().WaitingFor( ErrorMan(), lastPage->user(), hDb->user() ) == CQL_YES )
				return ErrorMan().returnError( CONCURRENCY, __FILE__, __LINE__ );
		}
		else if( lastPage->transactionNumber() != hDb->currentTransaction() )
		{
			if( bufferDebugging == CQL_YES )
				fprintf( stderr,
						 "%s, %d, calling lock page for file %s page number %ld\n",
						 __FILE__,
						 __LINE__,
						 name.text(),
						 writePageNumber );

			if( transactionDebugging == CQL_YES )
				*hAEnv << "Calling lock page for "
							   << name.text()
							   << " page "
							   << writePageNumber
							   << ", list size="
							   << currentWriteBufferPage->transactionPages().size()
							   << "\n";

			dynamic_cast< EnvironmentHandle* >( hAEnv )->lockPage( hDb->user(), currentWriteBufferPage, hDb->currentTransaction(), name.text() );
		}
	}
	else
	{
		if( bufferDebugging == CQL_YES )
			fprintf( stderr,
					 "%s, %d, calling lock page for file %s page number %ld\n",
					 __FILE__,
					 __LINE__,
					 name.text(),
					 writePageNumber );

		if( transactionDebugging == CQL_YES )
			*hAEnv << "Calling lock page for "
						   << name.text()
						   << " page "
						   << writePageNumber
						   << ", list size="
						   << currentWriteBufferPage->transactionPages().size()
						   << "\n";

		//  it is not uncommitted
		dynamic_cast< EnvironmentHandle* >( hAEnv )->lockPage( hDb->user(), currentWriteBufferPage, hDb->currentTransaction(), name.text() );
	}

	if( !hDb->stack().Pages() )
		throw NoTransactionException( __FILE__, __LINE__ );

	rc = hDb->stack().Pages()->FindEqualKey( fileNumber, writePageNumber );
	if( rc != CQL_SUCCESS )
	{
		if( rc == CQL_FAILURE )
			return CQL_FAILURE;

		if( hDb->stack().Pages()->AddIndexNode( ErrorMan(),
											   fileNumber,
											   writePageNumber,
											   this,
											   currentWriteBufferPage ) == CQL_FAILURE )
			return CQL_FAILURE;
	}

	for( rc = lastPage->firstNode(); rc == CQL_SUCCESS; rc = lastPage->nextNode() )
	{
		lockIndexNode = lastPage->CurrentNode();
		if( lockIndexNode->User() == hDb->user() )
			continue;

		if( dynamic_cast< EnvironmentHandle* >( hAEnv )->Waitors().AddIndexNode( ErrorMan(),
																				 hDb->user(),
																				 lockIndexNode->User(),
																				 &deadlockGraphIndexNode ) == CQL_FAILURE )
			return CQL_FAILURE;

		if( dynamic_cast< EnvironmentHandle* >( hAEnv )->Waitees().AddIndexNode( ErrorMan(),
																				 deadlockGraphIndexNode,
																				 lockIndexNode->User(),
																				 hDb->user() ) == CQL_FAILURE )
			return CQL_FAILURE;
	}

	bufferOffset = ((UNI)( ( currentWritePosition % ((UL)CQL_LOGICAL_PAGE_SIZE) ) ) );
	bufferPointer = dynamic_cast< EnvironmentHandle* >( hAEnv )->getDataPointer( currentWriteBufferPage, bufferOffset );
	return CQL_SUCCESS;
}


NI FileManager::GetBufferPointerForRead( void )
{
	if( !currentReadBufferPage || readPageNumber != ( currentReadPosition / ((UL)CQL_LOGICAL_PAGE_SIZE) ) )
		if( GetReadPage( currentReadPosition / ((UL)CQL_LOGICAL_PAGE_SIZE) ) == CQL_FAILURE )
			return CQL_FAILURE;

	bufferOffset = ((UNI)( ( currentReadPosition % ((UL)CQL_LOGICAL_PAGE_SIZE) ) ) );
	bufferPointer = dynamic_cast< EnvironmentHandle* >( hAEnv )->getDataPointer( currentReadBufferPage, bufferOffset );
	return CQL_SUCCESS;
}


NI FileManager::GetReadPage( UL pageNum )
{
	return GetPage( pageNum, &readPageNumber, &currentReadBufferPage );
}


NI FileManager::GetWritePage( UL pageNum )
{
	return GetPage( pageNum, &writePageNumber, &currentWriteBufferPage );
}


NI FileManager::GetPage( UL pageNum, pUL localPageNumber, BaseBufferPage **localCurrentPage )
{
	BufferPage *page;

	if( btreePrinting == CQL_YES )
		fprintf( stderr,
				 "%s, %d, file %s, fileNumber %d, page %ld, localPageNumber %lx\n",
				 __FILE__,
				 __LINE__,
				 name.text(),
				 fileNumber,
				 pageNum,
				 ((UL)localPageNumber) );

	*localPageNumber = pageNum;

	if( findEqualKey( fileNumber, pageNum ) )
	{
		*localCurrentPage = getCurrentPage();

		if( btreePrinting == CQL_YES )
			fprintf( stderr,
					 "%s, %d, using page from index, page is %lx, position=%ld\n",
					 __FILE__,
					 __LINE__,
					 ((UL)(*localCurrentPage)->page()),
					 (*localCurrentPage)->page()->filePosition() );

		return CQL_SUCCESS;
	}

	page = dynamic_cast< EnvironmentHandle* >( hAEnv )->getNewPage();
	page->pageNumber( pageNum );
	page->fileName( name.text() );
	page->user( hDb->user() );

	if( btreePrinting == CQL_YES )
		fprintf( stderr, "%s, %d, new page %lx\n", __FILE__, __LINE__, ((UL)page) );

	*localCurrentPage = new BaseBufferPage( page );
	if( !*localCurrentPage )
		return ErrorMan().returnError( ALLOCATION, __FILE__, __LINE__ );

	try
	{
		addIndexNode( fileNumber, pageNum, *localCurrentPage );
	}
	catch( ... )
	{
		dynamic_cast< EnvironmentHandle* >( hAEnv )->releasePage( *localCurrentPage );
		*localCurrentPage = 0;
		throw;
	}

	if( pageNum < fileExtensionPage )
	{
		if( btreePrinting == CQL_YES )
			fprintf( stderr, "%s, %d, reading page\n", __FILE__, __LINE__ );

		if( ReadCurrentPage( (*localCurrentPage)->page(), pageNum ) == CQL_FAILURE )
			return CQL_FAILURE;
	}

	return CQL_SUCCESS;
}


NI FileManager::ReadCurrentPage( BufferPage *page, UL pageNum )
{
	RECID physicalPosition;

	if( temporary() )
		return CQL_FAILURE;

	physicalPosition = pageNum * CQL_PAGE_SIZE;

	if( fileDebugging )
		*hAEnv << "Read current page, file " << name.text() << " position " << ((UNI)physicalPosition) << "\n";

	clibFile.inputSeek( physicalPosition );
	clibFile.read( reinterpret_cast< void* >( page->base() ), CQL_PAGE_SIZE );

	return CQL_SUCCESS;
}


FileManagerException::FileManagerException( CqlString& fname,
										    pNC message,
											ExceptionCodes _eCode,
											pNC fileName,
											NI _lineNumber,
											NI _osError )
	: AbstractTableException( message, _eCode, fileName, _lineNumber, _osError ),
	  fileName_( fname )
{
}


FileManagerException::~FileManagerException( void )
{
}


void FileManagerException::output( AbstractLogger& ) const
{
}


IsamFile::IsamFile( AbstractDatabaseHandle& adh )
	: IsamFileListElement(),
	  AbstractTable( adh ),
	  RecordIndex(),
	  createColumnList_(),
	  createKeyList_(),
	  currentColumn_( 0 ),
	  currentLength_( 0 ),
	  currentPosition_( ((RECID)0) ),
	  currentRecord_( ((pRecord)0) ),
	  currentRecordCached_( false ),
	  currentRecordPosition_( 0 ),
	  dataFetched_( false ),
	  file_( ((pFileManager)0) ),
	  fileOpen_( false ),
	  header_(),
	  index_(),
	  isamName_(),
	  temporary_( false ),
	  type_( CQL_CQL )
{
}


IsamFile::~IsamFile( void )
{
	if( fileOpen_ )
		close();

	currentColumn_ = 0;
	currentKey_ = 0;
	currentLength_ = 0;
	currentPosition_ = 0;

	if( currentRecord_ && !currentRecordCached_ )
	{
		delete currentRecord_;
		currentRecord_ = ((Record*)0);
	}

	file_ = ((pFileManager)0);
	header_.IsamFileHeader::~IsamFileHeader();
	index_.Index::~Index();
	isamName_.CqlString::~CqlString();

	numberOfKeys_ = 0;
	currentRecordCached_ = dataFetched_ = temporary_ = false;
	createColumnList_.destroy();
	createKeyList_.destroy();
}


void IsamFile::deleteIndexMember( US keyno )
{
	//
	//  First key number is used internally
	//
	keyno++;

	if( index_.DeleteIndexMember( hDb(), keyno ) == CQL_FAILURE )
		throw InternalErrorException( __FILE__, __LINE__ );
}


void IsamFile::addKey( IndexKeyDescriptor *key )
{
	if( index_.BeginKeyOperation( hDb(), key->keyNumber() ) == CQL_FAILURE )
		return;

	AbstractSegmentDescriptor *seg;

	for( seg = index_.CurrentKey()->segments().first(); seg; seg = index_.CurrentKey()->segments().next() )
		if( index_.SetSegment( hDb(), seg->column() ) == CQL_FAILURE )
			throw AbstractTableException( __FILE__, __LINE__ );

	index_.AddKey( hDb(), currentPosition_ );
}


void IsamFile::deleteKey( IndexKeyDescriptor *ikd )
{
	if( index_.BeginKeyOperation( hDb(), ikd->keyNumber() ) == CQL_FAILURE )
		return;

	AbstractSegmentDescriptor *seg;

	for( seg = ikd->segments().first(); seg; seg = ikd->segments().next() )
		if( index_.SetSegment( hDb(), seg->column() ) == CQL_FAILURE )
			return;

	index_.deleteKey( hDb(), ikd, currentPosition_ );
}


void IsamFile::addIndexMember( pAccessor acc )
{
	bool result;

	hAdb().beginTransaction();
	IndexKeyDescriptor *ikd = dynamic_cast< IndexKeyDescriptor*>( acc );
	if( index_.AddIndexMember( hDb(), ikd ) == CQL_FAILURE )
	{
		hAdb().rollbackTransaction();
		throw TableAccessException( __FILE__, __LINE__ );
	}

	//
	//  Now the new key exists.  We need to add a key for each row in the table.
	//

	beginIsamOperation( 0, CQL_YES );

	for( result = firstRow(); result; result = nextRow() )
		addKey( ikd );

	hAdb().commitTransaction();
}


NI IsamFile::findKeyColumns( pAccessor acc )
{
	IndexKeyDescriptor *keyDesc;
	keyDesc = dynamic_cast< IndexKeyDescriptor* >( acc );

	if( keyDesc->lengthIndex() )
	{
		//  need to generate pseudo-column for lengthIndex
		CqlColumnTypes ctype( CQL_INTEGER );
		AbstractColumnDescriptor *col = AbstractColumnDescriptor::createObject( ctype, 0, false );
		keyDesc->segments().first()->column( col );
		return CQL_SUCCESS;
	}

	AbstractSegmentDescriptor *seg;

	for( seg = keyDesc->segments().first(); seg; seg = keyDesc->segments().next() )
	{
		seg->column( baseTableColumns()[ seg->columnNumber() ] );
		ColumnToKeyMap *ctkm = new ColumnToKeyMap( keyDesc, seg );
		seg->column()->keyMapList().add( ctkm );
	}

	return CQL_SUCCESS;
}


void IsamFile::computeCurrentLength( void )
{
	currentLength_ = sizeof( UL );

	ColumnDescriptor *column;

	try
	{
		// FIXED: dynamic cast does not work with functions & in for stmt
		AbstractColumnDescriptor *acd;
		for( acd =  baseTableColumns().first(); acd; acd = baseTableColumns().next() )
		{
			column=dynamic_cast< ColumnDescriptor* >( acd );
			if( column->isNull() == CQL_YES )
				currentLength_++;
			else
				//  extra byte is for null indicator
				currentLength_ += ( 1 + column->streamLength() );
		}
	}
	//exception
	catch( ... )
	{
		//  do something
	}
}


AbstractType *IsamFile::getColumnValue( US _columnNumber )
{
	if( !dataFetched_ )
		fetchData();

	CqlColumnTypes ctype;
	bool nflag;

	getColumnInfo( _columnNumber, ctype, nflag );
	AbstractType *at = AbstractType::createObject( ctype );
	AbstractColumnDescriptor *column = columns()[ _columnNumber ];
	*at = column->value();
	return at;
}


void IsamFile::getNewRecordPosition( void )
{
	if( index_.BeginKeyOperation( hDb(), 0 ) == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );

	if( index_.SetSegment( hDb(), ((pUC)&currentLength_) ) == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );

	if( index_.findGreaterOrEqual( hDb() ) )
	{
		currentPosition_ = index_.CurrentKey()->CurrentNode()->CurrentElement()->Son();
		index_.deleteCurrentKey( hDb() );
	}
	else
	{
		if( header_.read( hDb(), file_ ) == CQL_FAILURE )
			throw TableAccessException( __FILE__, __LINE__ );
		currentPosition_ = header_.endOfFile();
		header_.endOfFile( currentPosition_ + currentLength_ );
		if( header_.write( hDb(), file_ ) == CQL_FAILURE )
			throw TableAccessException( __FILE__, __LINE__ );
	}
}


NI IsamFile::writeRecord( void )
{
	if( btreePrinting == CQL_YES )
		fprintf( stderr,
				 "%s, %d, currentPosition_ = %ld, currentLength_ = %ld\n",
				 __FILE__,
				 __LINE__,
				 currentPosition_,
				 currentLength_ );

	if( file_->OutputSeek( currentPosition_ ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( btreePrinting == CQL_YES )
		fprintf( stderr, "%s, %d, calling Write at %lx\n", __FILE__, __LINE__, ((UL)currentRecord_->buffer()) );

	file_->write( currentRecord_->buffer(), currentLength_ );

	hDb().addToIsamIndex( this );

	return CQL_SUCCESS;
}


NI IsamFile::writeRecord( pRecord rec )
{
	currentPosition_ = rec->Location();

	return writeRecord();
}


NI IsamFile::rollbackRecord( void )
{
	return CQL_SUCCESS;
}


NI IsamFile::rollbackRecord( pRecord )
{
	return CQL_SUCCESS;
}


void IsamFile::flushDirtyRecords( void )
{
	NI rc;
	pRecordIndexNode tnode;

	if( index_.FlushDirtyNodes( hDb() ) == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );

	for( rc = firstNode(); rc == CQL_SUCCESS; rc = nextNode() )
	{
		tnode = CurrentNode();

		if( tnode->CachedRecord()->Dirty() )
			if( writeRecord( tnode->CachedRecord() ) == CQL_FAILURE )
				throw TableAccessException( __FILE__, __LINE__ );

		if( tnode->CachedRecord() == currentRecord_ )
			currentRecord_ = ((pRecord)0);
	}

	destroyIndex();

	if( currentRecord_ )
	{
		delete currentRecord_;
		currentRecord_ = 0;
	}
}


NI IsamFile::rollbackDirtyRecords( void )
{
	NI rc;
	pRecordIndexNode tnode;

	for( rc = firstNode(); rc == CQL_SUCCESS; rc = nextNode() )
	{
		tnode = CurrentNode();

		if( tnode->CachedRecord()->Dirty() )
			if( rollbackRecord( tnode->CachedRecord() ) == CQL_FAILURE )
				return CQL_FAILURE;

		if( tnode->CachedRecord() == currentRecord_ )
			currentRecord_ = ((pRecord)0);
	}

	destroyIndex();

	if( currentRecord_ )
	{
		delete currentRecord_;
		currentRecord_ = ((pRecord)0);
	}

	return CQL_SUCCESS;
}


NI IsamFile::copyKeySegmentValues( void )
{
	pAbstractSegmentDescriptor seg;
	for( seg = currentKey_->segments().first(); seg; seg = currentKey_->segments().next() )
		if( index_.SetSegment( hDb(), seg->column() ) == CQL_FAILURE )
			return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI IsamFile::fetchData( void )
{
	if( FindEqualKey( hDb(), currentPosition_ ) == CQL_SUCCESS )
	{
		RecordIndexNode *recordNode = CurrentNode();

		if( currentRecord_ && !currentRecordCached_ )
			delete currentRecord_;

		currentRecord_ = recordNode->CachedRecord();
		currentRecordCached_ = true;
		currentRecordPosition_ = currentRecord_->Location();
		dataFetched_ = true;

		if( currentRecord_->InputCachedRecord( baseTableColumns() ) == CQL_FAILURE )
			return CQL_FAILURE;

		return CQL_SUCCESS;
	}

	if( file_->InputSeek( currentPosition_ ) == CQL_FAILURE )
		return hAdb().returnError( ISAM_DATA_INDEX_INCONSISTENCY, __FILE__, __LINE__ );

	if( currentRecord_ && !currentRecordCached_ )
		delete currentRecord_;

	currentRecord_ = new Record( hAdb(), currentPosition_ );
	if( !currentRecord_ )
		return CQL_FAILURE;
	currentRecordPosition_ = currentPosition_;
	currentRecordCached_ = false;

	if( currentRecord_->Read( hDb(), file_, baseTableColumns() ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( AddIndexNode( hDb(), currentPosition_, currentRecord_ ) == CQL_FAILURE )
		return CQL_FAILURE;
	currentRecordCached_ = true;

	dataFetched_ = true;
	return CQL_SUCCESS;
}


NI IsamFile::beginCurrentKeyOperation( void )
{
	if( !currentKey_ )
		throw NoCurrentKeyException( __FILE__, __LINE__ );

	if( index_.BeginKeyOperation( hDb(), currentKey_->keyNumber() ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


void IsamFile::setCurrentPosition( void )
{
	currentPosition_ = index_.CurrentKey()->CurrentNode()->CurrentElement()->Son();
}


void IsamFile::completeRowOperation( bool forceFetch )
{
	setCurrentPosition();

	AbstractColumnDescriptor *acolumn;

	//  If there are any bound columns, data needs to be fetched.
	bool needToFetchData = false;
	for( acolumn = columns().first(); !needToFetchData && acolumn; acolumn = columns().next() )
		if( acolumn->bc() )
			needToFetchData = true;

	if( needToFetchData || forceFetch )
		if( fetchData() == CQL_FAILURE )
			throw TableAccessException( __FILE__, __LINE__ );

	if( needToFetchData )
	{
		for( acolumn = columns().first(); acolumn; acolumn = columns().next() )
		{
			ColumnDescriptor *column = dynamic_cast< ColumnDescriptor* >( acolumn );
			if( column->bc() )
			{
				if( column->isNull() )
					column->bc()->setUserNullFlag();
				else
				{
					column->bc()->clearUserNullFlag();
					*column >> column->bc();
				}
			}
		}
	}
}


NI IsamFile::releaseCurrentPosition( void )
{
	if( index_.BeginKeyOperation( hDb(), 0 ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( index_.SetSegment( hDb(), ((pUC)&currentLength_) ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( index_.AddKey( hDb(), currentPosition_ ) == CQL_FAILURE )
		return CQL_FAILURE;

	hDb().addToIsamIndex( this );

	return CQL_SUCCESS;
}


void IsamFile::decrementTransactionCounter( void )
{
	if( file_ )
		file_->DecrementTransactionCounter();
}


void IsamFile::incrementTransactionCounter( void )
{
	if( file_ )
		file_->IncrementTransactionCounter();
}


UNI IsamFile::transactionCounter( void )
{
	if( file_ )
		return file_->TransactionCounter();
	else
		return 0;
}


void IsamFile::releaseResources( void )
{
	destroyIndexIndex();
	destroyIsamIndex();
}


AbstractTable& IsamFile::operator = ( AbstractTable& at )
{
	IsamFile& other = dynamic_cast< IsamFile& >( at );
	//
	//  First we take care of the AbstractTable members
	//
	baseTableColumns() = other.baseTableColumns();

	//
	//  Now the IsamFile members
	//
	if( other.currentColumn_ )
	{
		AbstractColumnDescriptor *acd = AbstractColumnDescriptor::createObject( other.currentColumn_->columnType(), other.currentColumn_->columnNumber(), other.currentColumn_->descending() );
		currentColumn_ = dynamic_cast< ColumnDescriptor* >( acd );
		*currentColumn_ = *other.currentColumn_;
	}
	else
		currentColumn_ = 0;

	currentLength_ = other.currentLength_;
	currentPosition_ = other.currentPosition_;

	if( other.currentRecord_ )
	{
		currentRecord_ = new Record( hAdb() );
		if( !currentRecord_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		currentRecord_->Assign( hDb(), *other.currentRecord_ );
	}
	else
		currentRecord_ = ((pRecord)0);

	currentRecordPosition_ = other.currentRecordPosition_;

	//
	//  we can't duplicate file_ here, because it would upset the open file_ count
	//  at the file_ manager level;  We just copy the pointer.  The pointer should probably
	//  not be used in the copied class.
	//
	file_ = other.file_;

	header_ = other.header_;

	index_.Assign( hDb(), other.index_ );

	isamName_ = other.isamName_;

	if( other.currentKey_ )
	{
		IndexKeyDescriptor *kd, *otherkd;
		// FIXED: dynamic cast does not work with functions & in for stmt
		Accessor *accKd, *accOtherKd;
		for( accOtherKd = other.keys().first(), accKd = keys().first(); accOtherKd; accOtherKd = other.keys().next(), accKd =  keys().next() )
		{
			otherkd = dynamic_cast< IndexKeyDescriptor* >( accOtherKd );
			kd = dynamic_cast< IndexKeyDescriptor* >( accKd );
			if( otherkd == other.currentKey_ )
			{
				currentKey_ = kd;
				break;
			}
		}
	}
	else
		currentKey_ = 0;

	numberOfKeys_ = other.numberOfKeys_;
	currentRecordCached_ = other.currentRecordCached_;
	dataFetched_ = other.dataFetched_;
	fileOpen_ = other.fileOpen_;
	temporary_ = other.temporary_;

	return *this;
}


void IsamFile::addColumn( const CqlColumnTypes ctype )
{
	ColumnDescriptor *column;

	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::AddColumn, type=%t, len=%u\n", ctype.typeType(), ctype.typeLength() );

	AbstractColumnDescriptor *acd = AbstractColumnDescriptor::createObject( ctype, header_.numberOfColumns(), CQL_NO );
	column = dynamic_cast< ColumnDescriptor* >( acd );
	baseTableColumns().add( column );
	header_.incrementNumberOfColumns();
}


void IsamFile::addColumn( const CqlString&, const CqlColumnTypes )
{
	throw AbstractTableException( "Not implemented", EC_NOT_IMPLEMENTED, __FILE__, __LINE__ );
}


void IsamFile::addRow( void )
{
	bool currentRecordAllocated = false;

	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::AddRow\n" );

	if( csFunctionLogging )
	{
		bool tcsFunctionLogging = csFunctionLogging;
		csFunctionLogging = 0;
		hAdb().beginTransaction();
		csFunctionLogging = tcsFunctionLogging;
	}
	else
		hAdb().beginTransaction();

	//  Process bound columns, and set others to null.
	AbstractColumnDescriptor *acolumn;
	for( acolumn = columns().first(); acolumn; acolumn = columns().next() )
	{
		ColumnDescriptor *column = dynamic_cast< ColumnDescriptor* >( acolumn );
		if( column->bc() )
		{
			if( column->bc()->userNullFlag() )
				column->setNullflag();
			else
			{
				*column << column->bc();
				column->clearNullflag();
			}
		}
		else
			column->setNullflag();
	}

	computeCurrentLength();

	getNewRecordPosition();

	if( currentRecord_ && !currentRecordCached_ )
		delete currentRecord_;

	currentRecord_ = new Record( hAdb(), currentPosition_ );
	if( !currentRecord_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	else
		currentRecordAllocated = true;
	currentRecordPosition_ = currentPosition_;

	if( currentRecord_->ConstructRecord( hDb(), baseTableColumns(), currentLength_ ) == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );

	if( writeRecord() == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );

	//  **************************** add key for length index_

	UNI loop;
	for( currentKey_ = keys().first(), currentKey_ = keys().next(), loop = 1; currentKey_; currentKey_ = keys().next(), loop++ )
	{
		try
		{
			addKey( dynamic_cast< IndexKeyDescriptor* >( currentKey_ ) );
		}
		catch( ... )
		{
			hAdb().rollbackTransaction();
			if( currentRecord_ )
			{
				delete currentRecord_;
				currentRecord_ = 0;
			}
			throw;
		}
	}

	bool tcsFunctionLogging = csFunctionLogging;
	csFunctionLogging = 0;
	hAdb().commitTransaction();
	csFunctionLogging = tcsFunctionLogging;

	if( currentRecord_ )
	{
		delete currentRecord_;
		currentRecord_ = 0;
	}

	tcsFunctionLogging = csFunctionLogging;

	csFunctionLogging = 0;
	checkPropagationFlags();
	csFunctionLogging = tcsFunctionLogging;
}


void IsamFile::createCommon1( const TableType type )
{
	type_ = type;
	AccessorTypes atype( CQL_TREE_INDEX );
	currentKey_ = Accessor::createObject( atype, 0 );
	IndexKeyDescriptor *ikd = dynamic_cast< IndexKeyDescriptor* >( currentKey_ );
	ikd->setLengthIndex();
	SegmentTypes stype;

	stype.columnNumber( 0 );
	stype.segmentType( CQL_ASCENDING );
	AbstractSegmentDescriptor *aseg = AbstractSegmentDescriptor::createObject( 0, stype );
	IndexSegmentDescriptor *seg = dynamic_cast< IndexSegmentDescriptor* >( aseg );
	CqlColumnTypes ctype( CQL_INTEGER );
	AbstractColumnDescriptor *cd = AbstractColumnDescriptor::createObject( ctype, 0 );
	seg->column( cd );
	ikd->segments().add( seg );
	ikd->maximumKeyLength( sizeof( RECID ) );
	ikd->numberOfSegments( 1 );
	index_.keys().add( ikd );
	numberOfKeys_ = 1;
}


void IsamFile::dataName( const CqlString& name )
{
	dataName_ = name + CQL_DATA_FILE_EXTENSION;
}


void IsamFile::indexName( const CqlString& name )
{
	indexName_ = name + CQL_INDEX_FILE_EXTENSION;
}


void IsamFile::createCommon2( const CqlString& name )
{
	currentKey_ = 0;

	//  Create the files

	//  name is the prefix.  Add endings for index_ and data files
	dataName( name );
	indexName( name );

	//  Try to create the datafile.  Error throws exception to caller
	file_ = new FileManager( hDb(), type_ );
	hDb().addToIsamIndex( this );
	file_->Create( dataName_ );
	header_.setup( hAEnv->machineId() );
	header_.write( hDb(), file_ );

	AbstractColumnDescriptor *acd;
	for( acd = baseTableColumns().first(); acd; acd = baseTableColumns().next() )
	{
		ColumnDescriptor *column = dynamic_cast< ColumnDescriptor* >( acd );
		column->write( hDb(), file_ );
	}

	//  Each segment needs to fill in its pointer to the column class object (except lengthIndex).
	for( currentKey_ = keys().first(), currentKey_ = keys().next(); currentKey_; currentKey_ = keys().next() )
		findKeyColumns( currentKey_ );

	//  Data file_ created.  Move on to index_ file_
	indexName( name );
	index_.indexName() = indexName_;
	index_.EndCreate( hDb(), type_ );
	setFileOpen();
	//
	//  transactionCounter needs to be 1 here because header_ was written, making it part of the current transaction
	//
	file_->SetTransactionCounter( 1 );
	hDb().openIsamFiles().add( this );
}


void IsamFile::create( const TableType type, const CqlString& name, CqlColumnTypes **columnDescriptors, AccessorTypes **keyDescriptors )
{
	type_ = type;
	if( type_ == CQL_CQL_TEMPORARY )
		temporary_ = true;

	AccessorTypes liatype( CQL_TREE_INDEX );
	currentKey_ = Accessor::createObject( liatype, 0 );
	IndexKeyDescriptor *ikd = dynamic_cast< IndexKeyDescriptor* >( currentKey_ );
	ikd->setLengthIndex();
	SegmentTypes stype;

	stype.columnNumber( 0 );
	stype.segmentType( CQL_ASCENDING );
	AbstractSegmentDescriptor *aseg = AbstractSegmentDescriptor::createObject( 0, stype );
	IndexSegmentDescriptor *seg = dynamic_cast< IndexSegmentDescriptor* >( aseg );
	CqlColumnTypes lictype( CQL_INTEGER );
	AbstractColumnDescriptor *cd = AbstractColumnDescriptor::createObject( lictype, 0 );
	seg->column( cd );
	ikd->segments().add( seg );
	ikd->maximumKeyLength( sizeof( RECID ) );
	ikd->numberOfSegments( 1 );
	index_.keys().add( ikd );
	numberOfKeys_ = 1;

	US numberOfColumns;
	CqlColumnTypes *ctype;
	for( numberOfColumns = 0, ctype = columnDescriptors[ numberOfColumns ]; ctype->typeType() != CQL_COLUMN_UNDEFINED_TYPE; numberOfColumns++, ctype = columnDescriptors[ numberOfColumns ] )
	{
		if( !ctype->valid() )
			throw CreateSequenceException( __FILE__, __LINE__ );

		AbstractColumnDescriptor *acd = AbstractColumnDescriptor::createObject( *ctype, numberOfColumns );
		ColumnDescriptor *column = dynamic_cast< ColumnDescriptor* >( acd );
		baseTableColumns().add( column );
	}

	if( numberOfColumns == 0 )
		throw CreateSequenceException( __FILE__, __LINE__ );

	header_.numberOfColumns( numberOfColumns );

	AccessorTypes *atype;
	US numberOfKeys;
	for( numberOfKeys = 0, atype = keyDescriptors[ numberOfKeys ]; atype->typeType() != CQL_ACCESSOR_UNDEFINED_TYPE; numberOfKeys++, atype = keyDescriptors[ numberOfKeys ] )
	{
		if( !atype->valid() )
			throw CreateSequenceException( __FILE__, __LINE__ );

		currentKey_ = Accessor::createObject( *atype, static_cast< US >( numberOfKeys + 1 ) );
		IndexKeyDescriptor *likd = dynamic_cast< IndexKeyDescriptor* >( currentKey_ );

		US numberOfSegments;
		SegmentTypes *lstype;
		for( numberOfSegments = 0, lstype = atype->segments()[ numberOfSegments ]; lstype->segmentType() != CQL_SEGMENT_UNDEFINED_TYPE; numberOfSegments++, lstype = atype->segments()[ numberOfSegments ] )
		{
			if( !lstype->valid() )
				throw CreateSequenceException( __FILE__, __LINE__ );

			AbstractSegmentDescriptor *asd = AbstractSegmentDescriptor::createObject( numberOfSegments, *lstype );
			IndexSegmentDescriptor *lseg = dynamic_cast< IndexSegmentDescriptor* >( asd );
			likd->segments().add( lseg );
			likd->maximumKeyLength( likd->maximumKeyLength() + baseTableColumns()[ lstype->columnNumber() ]->length() );
		}

		likd->numberOfSegments( numberOfSegments );
		index_.keys().add( likd );
	}

	currentKey_ = 0;

	//  Create the files

	//  name is the prefix.  Add endings for index_ and data files
	dataName( name );
	indexName( name );

	//  Try to create the datafile.  Error throws exception to caller
	file_ = new FileManager( hDb(), type_ );
	hDb().addToIsamIndex( this );
	file_->Create( dataName_ );
	header_.setup( hAEnv->machineId() );
	header_.write( hDb(), file_ );

	AbstractColumnDescriptor *acd;
	for( acd = baseTableColumns().first(); acd; acd = baseTableColumns().next() )
	{
		ColumnDescriptor *column = dynamic_cast< ColumnDescriptor* >( acd );
		column->write( hDb(), file_ );
	}

	//  Each segment needs to fill in its pointer to the column class object (except lengthIndex).
	for( currentKey_ = keys().first(), currentKey_ = keys().next(); currentKey_; currentKey_ = keys().next() )
		findKeyColumns( currentKey_ );

	//  Data file_ created.  Move on to index_ file_
	indexName( name );
	index_.indexName() = indexName_;
	index_.EndCreate( hDb(), type_ );
	setFileOpen();
	//
	//  transactionCounter needs to be 1 here because header_ was written, making it part of the current transaction
	//
	file_->SetTransactionCounter( 1 );
	hDb().openIsamFiles().add( this );
}


void IsamFile::beginIsamOperation( NI keyNo, NI /*forUpdate*/, NI preserveData )
{
	//  check for keyNo == -1

	if( csFunctionLogging )
	{
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::BeginIsamOperation, keyNo=%u, preserveData=%d\n", ((UL)keyNo), preserveData );

		if( preserveData == CQL_NO )
		{
			bool tempCsFunctionLogging = csFunctionLogging;

			csFunctionLogging = 0;
			beginRowOperation();
			csFunctionLogging = tempCsFunctionLogging;
		}
	}
	else if( preserveData == CQL_NO )
		beginRowOperation();

	//
	//  first key is used internally
	//
	keyNo++;
	currentKey_ = keys()[ ((US)keyNo) ];
	index_.segmentsToCompare( 0 );
}


void IsamFile::endIsamOperation( void )
{
}


void IsamFile::beginRowOperation( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::BeginRowOperation\n" );

	dataFetched_ = false;

	// FIXED: dynamic cast does not work with functions & in for stmt
	AbstractColumnDescriptor * acd;
	for( acd = baseTableColumns().first(); acd; acd =  baseTableColumns().next() )
	{
		ColumnDescriptor *column = dynamic_cast< ColumnDescriptor* >( acd );
		column->setNullflag();
	}

	acd = baseTableColumns().first();
	currentColumn_ = dynamic_cast< ColumnDescriptor* >( acd );
}


void IsamFile::close( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::Close\n" );

	if( btreePrinting == CQL_YES && file_->IsOpen() == CQL_YES )
		fprintf( stderr, "%s, %d, closing %s and %s\n", __FILE__, __LINE__, file_->Name().text(), index_.File().Name().text() );

#ifdef __CQL_ROLLBACK_ON_CLOSE
	if( file_->TransactionCounter() > 0 || index_.file_().TransactionCounter() > 0 )
		if( hAdb().PurgeTransactionInformationForIsamFile( this ) == CQL_FAILURE )
			throw CloseCalledWithPendingTransactionException( __FILE__, __LINE__ );
#else
	if( ( file_->TransactionCounter() > 0
		  || file_->PropagationCounter() > 0 )
		  || ( index_.File().TransactionCounter() > 0
		  || index_.File().PropagationCounter() > 0 ) )
	{
		if( !temporary_ )
			throw CloseCalledWithPendingTransactionException( __FILE__, __LINE__ );

		flushDirtyRecords();
		try
		{
			hDb().purgeTransactionInformationForIsamFile( this );
		}
		catch( ... )
		{
			throw CloseCalledWithPendingTransactionException( __FILE__, __LINE__ );
		}
	}
#endif

	if( index_.Close( hDb() ) == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );

	if( file_->IsOpen() == CQL_NO )
		return;

	hDb().close( *file_ );
	destroyIndex();
	currentRecord_ = ((pRecord)0);
	clearFileOpen();
	hDb().openIsamFiles().remove( this );
}


RECID IsamFile::currentPosition( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::CurrentPosition, pos=%d\n", currentPosition_ );

	return currentPosition_;
}


void IsamFile::deleteRow( void )
{
	pAccessor tkey;

	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::DeleteRow\n" );

	if( currentPosition_ == 0 )
		throw NoCurrentPositionException( __FILE__, __LINE__ );

	if( !dataFetched_ )
		if( fetchData() == CQL_FAILURE )
			throw TableAccessException( __FILE__, __LINE__ );

	bool tempCsFunctionLogging = csFunctionLogging;
	csFunctionLogging = 0;
	hAdb().beginTransaction();
	csFunctionLogging = tempCsFunctionLogging;

	bool firstTime;
	for( tkey = keys().first(), firstTime = true; tkey; tkey = keys().next() )
	{
		if( firstTime )
		{
			firstTime = false;
			tkey = keys().next();
			if( !tkey )
				break;
		}

		index_.deleteKey( hDb(), tkey, currentPosition_ );
	}

	if( releaseCurrentPosition() == CQL_FAILURE )
	{
		hAdb().rollbackTransaction();
		throw BtreeInconsistentException( __FILE__, __LINE__ );
	}

	tempCsFunctionLogging = csFunctionLogging;
	csFunctionLogging = 0;
	hAdb().commitTransaction();
	csFunctionLogging = tempCsFunctionLogging;
	tempCsFunctionLogging = csFunctionLogging;
	csFunctionLogging = 0;
	checkPropagationFlags();
	csFunctionLogging = tempCsFunctionLogging;
}


void IsamFile::establishPosition( RECID pos, US keyNo, bool forUpdate )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::EstablishPosition, pos=%d, keyNo=%u\n", pos, ((UL)keyNo) );

	beginIsamOperation( keyNo, forUpdate, CQL_YES );

	currentPosition_ = pos;
	fetchData();
	beginCurrentKeyOperation();

	bool result = index_.findEqual( ((DatabaseHandle&)hDb() ) );
	if( !result )
		throw TableAccessException( __FILE__, __LINE__ );
	completeRowOperation( false );

	while( index_.CurrentKey()->CurrentNode()->CurrentElement()->Son() != pos )
		if( !index_.nextKey( hDb() ) )
			throw InternalErrorException( __FILE__, __LINE__ );

	setCurrentPosition();
}


UNI IsamFile::resolveConditions( void )
{
	//  On entry, all predicates are in the allPredicates_ list.
	//  At exit, predicates to be used for access are in the masterPredicates_
	//  list, and others are in the slavePredicates_ list.

	cond().clearFindEndOfFile();

	//  Find predicates whose column is the first segment of a key
	//  Make separate lists for == and other predicates

	AccessCondition *candidateKey;
	ConditionPredicate *cpred;
	AccessConditionList candidateList;

	for( cpred = cond().predicates().first(); cpred; cpred = cond().predicates().next() )
	{
		if( cpred->op() == CQL_COP_NOT_EQUAL )
			continue;

		ColumnToKeyMap *ctkm;
		for( ctkm = cpred->bc()->col()->keyMapList().first(); ctkm; ctkm = cpred->bc()->col()->keyMapList().next() )
		{
			if( ctkm->segmentDescriptor()->segmentNumber() == 0 )
			{
				candidateKey = new AccessCondition;
				if( !candidateKey )
					throw MemoryAllocationException( __FILE__, __LINE__ );

				ConditionPredicate *copiedPred = new ConditionPredicate( *cpred );
				candidateKey->predicates().add( copiedPred );
				candidateKey->op( cpred->op() );
				candidateKey->access( ctkm->acc() );

				if( cpred->op() == CQL_COP_EQUAL )
				{
					if( ctkm->acc()->aqtypeType() == CQL_NO_DUPLICATES )
					{
						if( ctkm->acc()->numberOfSegments() == 1 )
						{
							//  unique == key with only one segment.
							if( cpred->realPredicate() )
								cpred->realPredicate()->setResolved();
							else
								cpred->setResolved();

							cond().access( candidateKey );
							return 1;
						}
					}
				}

				candidateList.add( candidateKey );
			}
		}
	}

	//  Try to lengthen uniques.
	for( candidateKey = candidateList.first(); candidateKey; candidateKey = candidateList.next() )
	{
		bool keyExhausted = false;

		while( !keyExhausted )
		{
			//  What is the next segment position in the key?
			UNI nextSegment = candidateKey->predicates().size();
			bool thisSegmentFound = false;
			for( cpred = cond().predicates().first(); !thisSegmentFound && cpred; cpred = cond().predicates().next() )
			{
				ConditionPredicateList possibleTrailingPredicates;

				if( cpred->op() != CQL_COP_EQUAL )
				{
					ConditionPredicate *copiedPred = new ConditionPredicate( *cpred );
					possibleTrailingPredicates.add( copiedPred );
					continue;
				}

				ColumnToKeyMap *ctkm;
				for( ctkm = cpred->bc()->col()->keyMapList().first(); ctkm; ctkm = cpred->bc()->col()->keyMapList().next() )
				{
					if( ctkm->acc() != candidateKey->access() )
						continue;

					if( ctkm->segmentDescriptor()->segmentNumber() == nextSegment )
					{
						ConditionPredicate *copiedPred = new ConditionPredicate( *cpred );
						candidateKey->predicates().add( copiedPred );
						//  List is secondary, so just set members to zero
						possibleTrailingPredicates.emptyListBase();
						thisSegmentFound = true;
						break;
					}
				}
			}

			if( thisSegmentFound )
			{
				if( candidateKey->predicates().size() == candidateKey->access()->numberOfSegments() )
				{
					//  We've resolved all segments
					if( candidateKey->access()->aqtypeType() == CQL_NO_DUPLICATES )
					{
						UNI segsToCompare;
						//  Found fully resolved unique key
						for( cpred = candidateKey->predicates().first(), segsToCompare = 0; cpred; cpred = candidateKey->predicates().next(), segsToCompare++ )
						{
							if( cpred->realPredicate() )
								cpred->realPredicate()->setResolved();
							else
								cpred->setResolved();
						}

						cond().access( candidateKey );
						return segsToCompare;
					}
					else
						keyExhausted = true;
				}
			}
			else
				keyExhausted = true;
		}
	}

	//  We didn't find a fully resolved unique key.  Proceed to estimate costs
	AccessCondition *bestKey = 0;

	for( candidateKey = candidateList.first(); candidateKey; candidateKey = candidateList.next() )
	{
		switch( candidateKey->op() )
		{
		case CQL_COP_EQUAL :
			computeCostEqual( candidateKey );
			break;

		case CQL_COP_GREATER :
			computeCostGreater( candidateKey );
			break;

		case CQL_COP_GREATER_OR_EQUAL :
			computeCostGreaterOrEqual( candidateKey );
			break;

		case CQL_COP_LESS :
			computeCostLess( candidateKey );
			break;

		case CQL_COP_LESS_OR_EQUAL :
			computeCostLessOrEqual( candidateKey );
			break;

		case CQL_COP_NOT_EQUAL :
			computeCostNotEqual( candidateKey );
			break;

		case CQL_COP_UNDEFINED :
			throw InternalErrorException( __FILE__, __LINE__ );
		}

		if( !bestKey )
			bestKey = candidateKey;
		else if( bestKey->cost() > candidateKey->cost() )
			bestKey = candidateKey;
	}

	if( !bestKey )
		return 0;

	UNI segsToCompare;
	for( cpred = bestKey->predicates().first(), segsToCompare = 0; cpred; cpred = bestKey->predicates().next(), segsToCompare++ )
	{
		if( cpred->realPredicate() )
			cpred->realPredicate()->setResolved();
		else
			cpred->setResolved();
	}

	cond().access( bestKey );
	return segsToCompare;
}


void IsamFile::getConditionValues( void )
{
	ConditionPredicate *cpred;
	for( cpred = cond().predicates().first(); cpred; cpred = cond().predicates().next() )
	{
		ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( cpred->bc()->col() );
		*cd << cpred->bc();
		cd->clearNullflag();
	}
}


void IsamFile::computeCostEqual( AccessCondition *candidateKey )
{
	index_.BeginKeyOperation( hDb(), candidateKey->access()->keyNumber() );
	getConditionValues();
	candidateKey->cost( index_.countEqual( dynamic_cast< DatabaseHandle& >( hDb() ) ) );
}


void IsamFile::computeCostGreater( AccessCondition *candidateKey )
{
	index_.BeginKeyOperation( hDb(), candidateKey->access()->keyNumber() );
	getConditionValues();
	candidateKey->cost( index_.countGreater( dynamic_cast< DatabaseHandle& >( hDb() ) ) );
}


void IsamFile::computeCostGreaterOrEqual( AccessCondition *candidateKey )
{
	index_.BeginKeyOperation( hDb(), candidateKey->access()->keyNumber() );
	getConditionValues();
	candidateKey->cost( index_.countGreaterOrEqual( dynamic_cast< DatabaseHandle& >( hDb() ) ) );
}


void IsamFile::computeCostLess( AccessCondition *candidateKey )
{
	index_.BeginKeyOperation( hDb(), candidateKey->access()->keyNumber() );
	getConditionValues();
	candidateKey->cost( index_.countLess( dynamic_cast< DatabaseHandle& >( hDb() ) ) );
}


void IsamFile::computeCostLessOrEqual( AccessCondition *candidateKey )
{
	index_.BeginKeyOperation( hDb(), candidateKey->access()->keyNumber() );
	getConditionValues();
	candidateKey->cost( index_.countLessOrEqual( dynamic_cast< DatabaseHandle& >( hDb() ) ) );
}


void IsamFile::computeCostNotEqual( AccessCondition *candidateKey )
{
	computeCostLess( candidateKey );
	UL lcost = candidateKey->cost();
	computeCostGreater( candidateKey );
	lcost += candidateKey->cost();
	candidateKey->cost( lcost );
}


bool IsamFile::findFirstEqual( bool existenceFlag )
{
	index_.BeginKeyOperation( hDb(), cond().access()->access()->keyNumber() );
	getConditionValues();

	if( !index_.findEqual( dynamic_cast< DatabaseHandle& >( hDb() ) ) )
		return false;

	completeRowOperation( true );
	if( existenceFlag )
		cond().setFindEndOfFile();

	return true;
}


bool IsamFile::findFirstGreater( bool existenceFlag )
{
	index_.BeginKeyOperation( hDb(), cond().access()->access()->keyNumber() );
	getConditionValues();

	if( !index_.findGreater( dynamic_cast< DatabaseHandle& >( hDb() ) ) )
		return false;

	completeRowOperation( true );
	if( existenceFlag )
		cond().setFindEndOfFile();

	return true;
}


bool IsamFile::findFirstGreaterOrEqual( bool existenceFlag )
{
	index_.BeginKeyOperation( hDb(), cond().access()->access()->keyNumber() );
	getConditionValues();

	if( !index_.findGreaterOrEqual( dynamic_cast< DatabaseHandle& >( hDb() ) ) )
		return false;

	completeRowOperation( true );
	if( existenceFlag )
		cond().setFindEndOfFile();

	return true;
}


bool IsamFile::findFirstLess( bool existenceFlag )
{
	index_.BeginKeyOperation( hDb(), cond().access()->access()->keyNumber() );
	getConditionValues();

	if( !index_.findLessThan( dynamic_cast< DatabaseHandle& >( hDb() ) ) )
		return false;

	completeRowOperation( true );
	if( existenceFlag )
		cond().setFindEndOfFile();

	return true;
}


bool IsamFile::findFirstLessOrEqual( bool existenceFlag )
{
	index_.BeginKeyOperation( hDb(), cond().access()->access()->keyNumber() );
	getConditionValues();

	if( !index_.findLessThanOrEqual( dynamic_cast< DatabaseHandle& >( hDb() ) ) )
		return false;

	completeRowOperation( true );
	if( existenceFlag )
		cond().setFindEndOfFile();

	return true;
}


bool IsamFile::findFirstNotEqual( bool /*existenceFlag*/ )
{
	//****  Temporary  ****
	throw UnsupportedFeatureException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return false;
#endif
}


bool IsamFile::evaluatePredicate( ConditionPredicate *cpred )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( cpred->bc()->col() );

	switch( cpred->op() )
	{
	case CQL_COP_EQUAL :
		return *cd == cpred->bc();
#if defined( _MSC_VER ) && _MSC_VER != 1200
		break;
#endif

	case CQL_COP_GREATER :
		return *cd > cpred->bc();
#if defined( _MSC_VER ) && _MSC_VER != 1200
		break;
#endif

	case CQL_COP_GREATER_OR_EQUAL :
		return *cd >= cpred->bc();
#if defined( _MSC_VER ) && _MSC_VER != 1200
		break;
#endif

	case CQL_COP_LESS :
		return *cd < cpred->bc();
#if defined( _MSC_VER ) && _MSC_VER != 1200
		break;
#endif

	case CQL_COP_LESS_OR_EQUAL :
		return *cd <= cpred->bc();
#if defined( _MSC_VER ) && _MSC_VER != 1200
		break;
#endif

	case CQL_COP_NOT_EQUAL :
		return *cd != cpred->bc();
#if defined( _MSC_VER ) && _MSC_VER != 1200
		break;
#endif

	case CQL_COP_UNDEFINED :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

//  This went away for a while for V6, and then came back
//  #if defined( _MSC_VER ) && _MSC_VER != 1200
#if defined( _MSC_VER )
	//  very stupid Microsoft compiler
	return false;
#endif

//  If your version of GCC barfs on this, take it out.
#if defined( __WATCOMC__ ) || defined( __GNUC__ )
	//  equally stupid Watcom compiler (but less frequently)
	return false;
#endif
}


bool IsamFile::findFirst( bool existenceFlag )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::Find\n" );

	UNI segsToCompare = resolveConditions();

	bool result = false;

	if( cond().access() == 0 )
	{
		beginIsamOperation( 0 );
		result = firstRow();
	}
	else
	{
		beginIsamOperation( cond().access()->access()->keyNumber() -1 );
		index_.segmentsToCompare( segsToCompare );

		switch( cond().access()->op() )
		{
		case CQL_COP_EQUAL :
			result = findFirstEqual( existenceFlag );
			break;

		case CQL_COP_GREATER :
			result = findFirstGreater( existenceFlag );
			break;

		case CQL_COP_GREATER_OR_EQUAL :
			result = findFirstGreaterOrEqual( existenceFlag );
			break;

		case CQL_COP_LESS :
			result = findFirstLess( existenceFlag );
			break;

		case CQL_COP_LESS_OR_EQUAL :
			result = findFirstLessOrEqual( existenceFlag );
			break;

		case CQL_COP_NOT_EQUAL :
			result = findFirstNotEqual( existenceFlag );
			break;

		case CQL_COP_UNDEFINED :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	if( !result )
		return false;

	ConditionPredicate *cpred;
	bool otherConditions;
	for( cpred = cond().predicates().first(), otherConditions = true; otherConditions && cpred; cpred = cond().predicates().next() )
		if( !cpred->resolved() )
			if( evaluatePredicate( cpred ) == false )
				otherConditions = false;

	if( otherConditions == false )
		return findNext( existenceFlag );

	return true;
}


//  Existence is needed here for the case where a slave predicate evaluation fails in findFirst
bool IsamFile::findNext( bool /*existence*/ )
{
	getConditionValues();

	bool stepForward = false;

	switch( cond().access()->op() )
	{
	case CQL_COP_EQUAL :
		stepForward = true;
		break;

	case CQL_COP_GREATER :
		stepForward = true;
		break;

	case CQL_COP_GREATER_OR_EQUAL :
		stepForward = true;
		break;

	case CQL_COP_LESS :
		stepForward = false;
		break;

	case CQL_COP_LESS_OR_EQUAL :
		stepForward = false;
		break;

	case CQL_COP_NOT_EQUAL :
		stepForward = true;
		break;

	case CQL_COP_UNDEFINED :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	if( stepForward )
	{
		if( !nextRow( true ) )
		{
			clearConditions();
			return false;
		}
	}
	else
	{
		if( !previousRow( true ) )
		{
			clearConditions();
			return false;
		}
	}

	ConditionPredicate *cpred;
	for( cpred = cond().predicates().first(); cpred; cpred = cond().predicates().next() )
	{
		if( evaluatePredicate( cpred ) == false )
		{
			clearConditions();
			return false;
		}
	}

	return true;
}


bool IsamFile::firstRow( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::FirstRow\n" );

	beginCurrentKeyOperation();

	if( !index_.firstKey( hDb() ) )
		return false;
	completeRowOperation( false );
	return true;
}


void IsamFile::flushDataToRecord( void )
{
	computeCurrentLength();

	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::FlushDataToRecord\n" );

	if( currentRecord_ && !currentRecordCached_ )
		delete currentRecord_;

	currentRecord_ = new Record( hAdb(), 0 );
	if( !currentRecord_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentRecordPosition_ = 0;

	if( currentRecord_->ConstructRecord( hDb(), baseTableColumns(), currentLength_ ) == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );
}


void IsamFile::getColumnInfo( US _columnNumber, CqlColumnTypes& type, bool& nullflag )
{
	pAbstractColumnDescriptor column;

	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::getColumnInfo, columnNumber=%u\n", ((UL)_columnNumber) );

	column = baseTableColumns()[ _columnNumber ];

	type = column->columnType();
	if( column->isNull() == CQL_YES )
		nullflag = true;
	else
		nullflag = false;
}


bool IsamFile::lastRow( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::LastRow\n" );

	if( beginCurrentKeyOperation() == CQL_FAILURE )
		return CQL_FAILURE;

	if( !index_.lastKey( hDb() ) )
		return false;
	completeRowOperation( false );
	return true;
}


bool IsamFile::nextRow( bool forceFetch )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::NextRow\n" );

	beginCurrentKeyOperation();
	beginRowOperation();

	if( !index_.nextKey( hDb() ) )
		return false;

	completeRowOperation( forceFetch );
	return true;
}


bool IsamFile::previousRow( bool forceFetch )
{
	beginCurrentKeyOperation();
	beginRowOperation();

	if( !index_.previousKey( hDb() ) )
		return false;

	completeRowOperation( forceFetch );
	return true;
}


bool IsamFile::nextRow( void )
{
	return nextRow( false );
}


void IsamFile::open( const CqlString& name )
{
	CqlString s;
	UNI loop;
	ColumnDescriptor *column;
	pAccessor key;

	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::Open, name=%s\n", name.text() );

	if( btreePrinting == CQL_YES )
		fprintf( stderr, "%s, %d, Opening %s\n", __FILE__, __LINE__, name.text() );

	dataName( name );
	try
	{
		file_ = hDb().open( dataName_ );
	}
	catch( ClibFileSystemException& )
	{
		throw AbstractTableException( __FILE__, __LINE__ );
	}

	header_.read( hDb(), file_ );

	for( loop = 0; loop < header_.numberOfColumns(); loop++ )
	{
		column = ColumnDescriptor::readColumn( hDb(), *file_ );
		baseTableColumns().add( column );
	}

	index_.Open( hDb(), name );

	numberOfKeys_ = ((US)index_.Header().NumberOfKeys());

	for( key = keys().first(); key; key = keys().next() )
		if( findKeyColumns( key ) == CQL_FAILURE )
			//************************** throw
			return;

	setFileOpen();

	hDb().openIsamFiles().add( this );
}


bool IsamFile::previousRow( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::PreviousRow\n" );

	beginRowOperation();

	if( !index_.previousKey( hDb() ) )
		return false;
	completeRowOperation( false );
	return true;
}


void IsamFile::setDataFetched( void )
{
	dataFetched_ = true;
}


void IsamFile::updateRow( void )
{
	bool currentRecordAllocated = false;
	UL oldLength;

	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::UpdateRow\n" );

	bool tempCsFunctionLogging = csFunctionLogging;
	csFunctionLogging = 0;
	hAdb().beginTransaction();
	csFunctionLogging = tempCsFunctionLogging;

	//  First delete old keys
	IndexKeyDescriptor *ikd;
	// FIXED: dynamic cast does not work with functions & in for stmt
	Accessor *acc;
	for( acc= keys().first(), acc = keys().next(); acc; acc = keys().next() )
	{
		ikd = dynamic_cast< IndexKeyDescriptor* >( acc );
		if( ikd->dirty() )
			deleteKey( ikd );
	}

	oldLength = currentLength_;
	computeCurrentLength();
	if( currentLength_ > oldLength )
	{
		if( releaseCurrentPosition() == CQL_FAILURE )
			throw TableAccessException( __FILE__, __LINE__ );

		getNewRecordPosition();
	}

	if( currentRecord_ && !currentRecordCached_ )
		delete currentRecord_;

	currentRecord_ = new Record( hAdb(), currentPosition_ );
	if( !currentRecord_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	else
		currentRecordAllocated = true;
	currentRecordPosition_ = currentPosition_;

	if( currentRecord_->ConstructRecord( hDb(), baseTableColumns(), currentLength_ ) == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );

	if( writeRecord() == CQL_FAILURE )
		throw TableAccessException( __FILE__, __LINE__ );

	for( currentKey_ = keys().first(), currentKey_ = keys().next(); currentKey_; currentKey_ = keys().next() )
	{
		IndexKeyDescriptor *likd = ((IndexKeyDescriptor*)currentKey_);

		if( likd->dirty() )
			addKey( likd );
	}

	tempCsFunctionLogging = csFunctionLogging;
	csFunctionLogging = 0;
	hAdb().commitTransaction();
	csFunctionLogging = tempCsFunctionLogging;

	if( currentRecord_ )
	{
		delete currentRecord_;
		currentRecord_ = 0;
	}

	tempCsFunctionLogging = csFunctionLogging;
	csFunctionLogging = 0;
	checkPropagationFlags();
	csFunctionLogging = tempCsFunctionLogging;
}


pFileManager IsamFile::file( void )
{
	return file_;
}


NI IsamFile::destroyIsamIndex( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::DestroyIsamIndex\n" );

	destroyIndex();
	return CQL_SUCCESS;
}


NI IsamFile::destroyIndexIndex( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::DestroyIndexIndex\n" );

	index_.destroyIndex();
	return CQL_SUCCESS;
}


void IsamFile::deleteCurrentRecord( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::DeleteCurrentRecord\n" );

	if( currentRecord_ && !currentRecordCached_ )
	{
		delete currentRecord_;
		currentRecord_ = 0;
	}
}


void IsamFile::checkPropagationFlags( void )
{
	if( csFunctionLogging )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "IsamFile::CheckPropagationFlags\n" );

	//  check flags for both data and index_ FileManager
	if( file_->PropagationCounter() > 0 )
	{
		file_->DecrementPropagationCounter();
		dynamic_cast< DatabaseHandle& >( hDb() ).addToIsamIndex( this );
	}

	if( index_.File().PropagationCounter() > 0 )
	{
		index_.File().DecrementPropagationCounter();
		hDb().addToIndexIndex( &index_ );
	}
}


#ifndef CQL_BOOL_IS_INT

BoundColumn *IsamFile::createBoundColumn( US _columnNumber, bool& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_BOOL, cd, false );
	BoundColumnBool *bcolumn = dynamic_cast< BoundColumnBool * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, bool& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}

#endif


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, NC& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_CHAR, cd, false );
	BoundColumnChar *bcolumn = dynamic_cast< BoundColumnChar * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, NC& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, UC& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_UNSIGNED_CHAR, cd, false );
	BoundColumnUnsignedChar *bcolumn = dynamic_cast< BoundColumnUnsignedChar * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, UC& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, S& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_SHORT, cd, false );
	BoundColumnShort *bcolumn = dynamic_cast< BoundColumnShort * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, S& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, US& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_UNSIGNED_SHORT, cd, false );
	BoundColumnUnsignedShort *bcolumn = dynamic_cast< BoundColumnUnsignedShort * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, US& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, NI& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_INT, cd, false );
	BoundColumnInt *bcolumn = dynamic_cast< BoundColumnInt * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, NI& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, UNI& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_UNSIGNED_INT, cd, false );
	BoundColumnUnsignedInt *bcolumn = dynamic_cast< BoundColumnUnsignedInt * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, UNI& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, L& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_LONG, cd, false );
	BoundColumnLong *bcolumn = dynamic_cast< BoundColumnLong * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, L& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, UL& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_UNSIGNED_LONG, cd, false );
	BoundColumnUnsignedLong *bcolumn = dynamic_cast< BoundColumnUnsignedLong * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, UL& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, F& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_FLOAT, cd, false );
	BoundColumnFloat *bcolumn = dynamic_cast< BoundColumnFloat * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, F& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, D& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_DOUBLE, cd, false );
	BoundColumnDouble *bcolumn = dynamic_cast< BoundColumnDouble * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, D& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, BigintValue& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_BIGINT, cd, false );
	BoundColumnBigint *bcolumn = dynamic_cast< BoundColumnBigint * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, BigintValue& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, DecimalValue& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_DECIMAL, cd, false );
	BoundColumnDecimal *bcolumn = dynamic_cast< BoundColumnDecimal * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, DecimalValue& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, NC*& value, UL& len, bool& nullflag, bool assignFlag, bool freeable )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_PCHAR, cd, freeable );
	BoundColumnPChar *bcolumn = dynamic_cast< BoundColumnPChar * >( bcol );
	bcolumn->userData( value );
	bcolumn->length( len );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, NC*& value, UL& len, bool& nullflag, bool /*forUpdate*/, bool freeable )
{
	createBoundColumn( _columnNumber, value, len, nullflag, true, freeable );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, NC*& value, UC& len, bool& nullflag, bool assignFlag, bool freeable )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_PCHAR_SHORT, cd, freeable );
	BoundColumnPCharShort *bcolumn = dynamic_cast< BoundColumnPCharShort * >( bcol );
	bcolumn->userData( value );
	bcolumn->length( len );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, NC*& value, UC& len, bool& nullflag, bool /*forUpdate*/, bool freeable )
{
	createBoundColumn( _columnNumber, value, len, nullflag, true, freeable );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, UC*& value, UL& len, bool& nullflag, bool assignFlag, bool freeable )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_PUCHAR, cd, freeable );
	BoundColumnPUChar *bcolumn = dynamic_cast< BoundColumnPUChar * >( bcol );
	bcolumn->userData( value );
	bcolumn->length( len );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, UC*& value, UL& len, bool& nullflag, bool /*forUpdate*/, bool freeable )
{
	createBoundColumn( _columnNumber, value, len, nullflag, true, freeable );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, UC*& value, UC& len, bool& nullflag, bool assignFlag, bool freeable )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_PUCHAR_SHORT, cd, freeable );
	BoundColumnPUCharShort *bcolumn = dynamic_cast< BoundColumnPUCharShort * >( bcol );
	bcolumn->userData( value );
	bcolumn->length( len );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, UC*& value, UC& len, bool& nullflag, bool /*forUpdate*/, bool freeable )
{
	createBoundColumn( _columnNumber, value, len, nullflag, true, freeable );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, CqlString& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_STRING, cd, false );
	BoundColumnString *bcolumn = dynamic_cast< BoundColumnString * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, CqlString& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, DateValue& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_DATE, cd, false );
	BoundColumnDate *bcolumn = dynamic_cast< BoundColumnDate * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, DateValue& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, TimeValue& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_TIME, cd, false );
	BoundColumnTime *bcolumn = dynamic_cast< BoundColumnTime * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, TimeValue& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


BoundColumn *IsamFile::createBoundColumn( US _columnNumber, TimestampValue& value, bool& nullflag, bool assignFlag )
{
	ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( columns()[ _columnNumber ] );
	BoundColumn *bcol = BoundColumn::createObject( BoundColumn::CPP_TIMESTAMP, cd, false );
	BoundColumnTimestamp *bcolumn = dynamic_cast< BoundColumnTimestamp * >( bcol );
	bcolumn->userData( value );
	bcolumn->userNullFlag( nullflag );
	if( assignFlag )
		cd->bc( bcol );
	return bcol;
}


void IsamFile::bindColumn( US _columnNumber, TimestampValue& value, bool& nullflag, bool /*forUpdate*/ )
{
	createBoundColumn( _columnNumber, value, nullflag, true );
}


void IsamFile::unbindAllColumns( void )
{
	AbstractColumnDescriptor *acol;
	for( acol = baseTableColumns().first(); acol; acol = baseTableColumns().next() )
	{
		acol->bc( 0 );
	}
}


void IsamFile::unbindColumn( US _columnNumber )
{
	AbstractColumnDescriptor *acol = baseTableColumns()[ _columnNumber ];
	acol->bc( 0 );
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const NC& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< NC& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const UC& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< UC& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const S& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< S& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const US& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< US& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const NI& value, bool& nullflag, ConditionalOperators op  )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< NI& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const UNI& value, bool& nullflag, ConditionalOperators op  )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< UNI& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const L& value, bool& nullflag, ConditionalOperators op  )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< L& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const UL& value, bool& nullflag, ConditionalOperators op  )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< UL& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const F& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< F& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const D& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< D& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, NC*& value, UL& len, bool& nullflag, ConditionalOperators op, bool freeable )
{
	BoundColumn *bc = createBoundColumn( _columnNumber,
										 value,
										 len,
										 nullflag,
										 false,
										 freeable );

	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, NC*& value, UC& len, bool& nullflag, ConditionalOperators op, bool freeable )
{
	BoundColumn *bc = createBoundColumn( _columnNumber,
										 value,
										 len,
										 nullflag,
										 false,
										 freeable );

	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, UC*& value, UL& len, bool& nullflag, ConditionalOperators op, bool freeable )
{
	BoundColumn *bc = createBoundColumn( _columnNumber,
										 value,
										 len,
										 nullflag,
										 false,
										 freeable );

	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, UC*& value, UC& len, bool& nullflag, ConditionalOperators op, bool freeable )
{
	BoundColumn *bc = createBoundColumn( _columnNumber,
										 value,
										 len,
										 nullflag,
										 false,
										 freeable );

	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const BigintValue& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< BigintValue& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const CqlString& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< CqlString& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const DateValue& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< DateValue& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const DecimalValue& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< DecimalValue& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const TimeValue& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< TimeValue& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


ConditionPredicate *IsamFile::setCondition( US _columnNumber, const TimestampValue& value, bool& nullflag, ConditionalOperators op )
{
	BoundColumn *bc = createBoundColumn( _columnNumber, const_cast< TimestampValue& >( value ), nullflag );
	ConditionPredicate *cp = new ConditionPredicate( bc, op );
	if( !cp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	cond().predicates().add( cp );
	return cp;
}


void IsamFile::clearConditions( void )
{
	cond().destroy();
}


UL IsamFile::estimateCost( void )
{
	return 0;
}


UL IsamFile::estimateCost( ConditionPredicate* /*cpred*/ )
{
	return 0;
}


DatabaseHandle& IsamFile::hDb( void )
{
	return dynamic_cast< DatabaseHandle& >( hAdb() );
}


void IsamFile::remove( MemoryIndex&, RECID& )
{
	throw InternalErrorException( __FILE__, __LINE__ );
}


//  deletes the physical files during drop table
void IsamFile::deleteFiles( const CqlString& name )
{
	dataName( name );
	indexName( name );
	if( !file_ )
	{
		file_ = new FileManager( hDb(), CQL_CQL );
		if( !file_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	file_->deleteFile( dataName_ );
	file_->deleteFile( indexName_ );
}


IsamFileHeader::IsamFileHeader( void ) : machineId_( 0 ), numberOfColumns_( 0 ), endOfFile_( 0 )
{
}


IsamFileHeader::~IsamFileHeader( void )
{
	machineId_ = numberOfColumns_ = 0;
	endOfFile_ = 0;
}


NI IsamFileHeader::read( DatabaseHandle&, pFileManager file )
{
	if( file->InputSeek( 0 ) == CQL_FAILURE )
		return CQL_FAILURE;

	*file >> machineId_ >> numberOfColumns_ >> endOfFile_;
	return CQL_SUCCESS;
}


NI IsamFileHeader::setup( UL _machineId )
{
	machineId_ = _machineId;
	endOfFile_ = CQL_LOGICAL_PAGE_SIZE;

	return CQL_SUCCESS;
}


NI IsamFileHeader::write( DatabaseHandle&, pFileManager file )
{
	if( file->OutputSeek( 0 ) == CQL_FAILURE )
		return CQL_FAILURE;

	*file << machineId_ << numberOfColumns_ << endOfFile_;
	return CQL_SUCCESS;
}


OpenFileManager::OpenFileManager( void ): FilenameIndex()
{
}


OpenFileManager::~OpenFileManager( void )
{
}


pFileManager OpenFileManager::Open( DatabaseHandle& dbHandle, CqlString& fname )
{
	pFilenameIndexNode filenameIndexNode;
	pFileManager lfmgr;

	if( fileDebugging )
		*hAEnv << "OpenFileManager, request to open " << fname.text() << "\n";

	const char *fileName = fname.text();
	for(int i = strlen(fileName); i > 0; i--)
	{
		if(!strncmp(&fileName[i], "/", 1))
		{
			CqlString s(dbHandle.initDir());
			s += "/";

			s += &fileName[i+1];
			fname = s;
			break;
		}
	}

	if( fileDebugging )
		*hAEnv << "OpenFileManager, request to open " << fname.text() << "\n";

	if( FindEqualKey( ((ErrorManager&)dbHandle.aErrorMan()), fname ) == CQL_SUCCESS )
	{
		filenameIndexNode = CurrentNode();
		lfmgr = filenameIndexNode->FileMgr();
		lfmgr->IncrementOpenCount();

		if( fileDebugging )
			*hAEnv << "OpenFileManager, file " << fname.text() << " already open" << "\n";

		return lfmgr;
	}

	if( fileDebugging )
		*hAEnv << "OpenFileManager, file " << fname.text() << " not already open" << "\n";

	lfmgr = new FileManager( dbHandle, CQL_CQL );
	if( !lfmgr )
	{
		MemoryAllocationException mex( __FILE__, __LINE__ );
		throw mex;
	}

	if( lfmgr->Open( fname, CQL_CQL ) == CQL_FAILURE )
	{
		delete lfmgr;

		//********************************************************************
		//**  GNU C++ 2.7.2 for LINUX has a problem with exceptions and     **
		//**  inheritence.  FileManagerException derives from               **
		//**  AbstractTableException.  AbstractTableException is caught up  **
		//**  the call chain when FileManagerException is thrown, by all    **
		//**  tested compilers except GNU.  When GNU C++ fixes this         **
		//**  problem, remove the #else part.                               **
		//********************************************************************
#if !defined( __CQL_LINUX )
		FileManagerException fme( fname, "Open failure", EC_OPEN_FAILURE, __FILE__, __LINE__ );
		throw fme;
#else
		AbstractTableException ate( "Open failure", EC_OPEN_FAILURE, __FILE__, __LINE__ );
		throw ate;
#endif
	}

	if( AddIndexNode( ((ErrorManager&)dbHandle.aErrorMan()), fname, lfmgr ) == CQL_FAILURE )
	{
		delete lfmgr;
		InternalErrorException cqlException( __FILE__, __LINE__ );
		throw cqlException;
	}

	lfmgr->IncrementOpenCount();
	return lfmgr;
}


NI OpenFileManager::Close( DatabaseHandle& dbHandle, FileManager& fmgr )
{
	NI rc;

	if( fileDebugging )
		*hAEnv << "OpenFileManager close, file " << fmgr.Name().text() << "\n";

	if( fmgr.IsOpen() == CQL_NO )
		return CQL_SUCCESS;

	fmgr.DecrementOpenCount();
	if( fmgr.OpenCount() != 0 )
		return CQL_SUCCESS;

	rc = FindEqualKey( ((ErrorManager&)dbHandle.aErrorMan()), fmgr.Name() );
	if( rc == CQL_FAILURE )
		return CQL_FAILURE;
	else if( rc == CQL_SUCCESS )
	{
		if( fmgr.Close( dynamic_cast< BufferManager& >( *hAEnv ) ) == CQL_FAILURE )
			return CQL_FAILURE;

		if( deleteIndexNode() == CQL_FAILURE )
			return dbHandle.returnError( INVALID_OPEN_FILE_INDEX, __FILE__, __LINE__ );
	}

	return CQL_SUCCESS;
}


void BigintValue::output( FileManager& fm ) const
{
	fm << bigintLiteral_.highest_ << bigintLiteral_.higher_ << bigintLiteral_.lower_ << bigintLiteral_.lowest_ << bigintLiteral_.sign_;
}


void BigintValue::input( FileManager& fm )
{
	fm >> bigintLiteral_.highest_ >> bigintLiteral_.higher_ >> bigintLiteral_.lower_ >> bigintLiteral_.lowest_ >> bigintLiteral_.sign_;
}


void BinaryValue::output( FileManager& fm ) const
{
	fm << length_;
	fm.write( reinterpret_cast< void* >( const_cast< UC * >( buffer_ ) ), length_ );
}


void BinaryValue::input( FileManager& fm )
{
	fm >> length_;
	if( buffer_ )
		delete [] buffer_;
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	fm.read( reinterpret_cast< void* >( buffer_ ), length_ );
}


void DateValue::output( FileManager& fm ) const
{
	fm << dateLiteral_.year_ << dateLiteral_.month_ << dateLiteral_.day_;
}


void DateValue::input( FileManager& fm )
{
	fm >> dateLiteral_.year_ >> dateLiteral_.month_ >> dateLiteral_.day_;
}


void DecimalValue::output( FileManager& fm ) const
{
	fm << decimalLiteral_.sign_ << decimalLiteral_.scale_;
	fm.write( reinterpret_cast< void* >( const_cast< NC* >( decimalLiteral_.digits_ ) ), sizeof( decimalLiteral_.digits_ ) );
}


void DecimalValue::input( FileManager& fm )
{
	fm >> decimalLiteral_.sign_ >> decimalLiteral_.scale_;
	fm.read( reinterpret_cast< void* >( decimalLiteral_.digits_ ), sizeof( decimalLiteral_.digits_ ) );
}


void TimeValue::output( FileManager& fm ) const
{
	fm << timeLiteral_.hour_ << timeLiteral_.minute_ << timeLiteral_.second_;
}


void TimeValue::input( FileManager& fm )
{
	fm >> timeLiteral_.hour_ >> timeLiteral_.minute_ >> timeLiteral_.second_;
}


void TimestampValue::output( FileManager& fm ) const
{
	fm << timestampLiteral_.year_ << timestampLiteral_.month_ << timestampLiteral_.day_ << timestampLiteral_.hour_ << timestampLiteral_.minute_ << timestampLiteral_.second_ << timestampLiteral_.fraction_;
}


void TimestampValue::input( FileManager& fm )
{
	fm >> timestampLiteral_.year_ >> timestampLiteral_.month_ >> timestampLiteral_.day_ >> timestampLiteral_.hour_ >> timestampLiteral_.minute_ >> timestampLiteral_.second_ >> timestampLiteral_.fraction_;
}


void BitValue::output( FileManager& fm ) const
{
	fm << pvalue_;
}


void BitValue::input( FileManager& fm )
{
	fm >> pvalue_;
}


void FloatValue::output( FileManager& fm ) const
{
	fm << pvalue_;
}


void FloatValue::input( FileManager& fm )
{
	fm >> pvalue_;
}


void IntegerValue::output( FileManager& fm ) const
{
	fm << pvalue_;
}


void IntegerValue::input( FileManager& fm )
{
	fm >> pvalue_;
}


void RealValue::output( FileManager& fm ) const
{
	fm << pvalue_;
}


void RealValue::input( FileManager& fm )
{
	fm >> pvalue_;
}


void SmallintValue::output( FileManager& fm ) const
{
	fm << pvalue_;
}


void SmallintValue::input( FileManager& fm )
{
	fm >> pvalue_;
}


void TinyintValue::output( FileManager& fm ) const
{
	fm << pvalue_;
}


void TinyintValue::input( FileManager& fm )
{
	fm >> pvalue_;
}


void CharValue::output( FileManager& fm ) const
{
	fm << value_;
}


void CharValue::input( FileManager& fm )
{
	fm >> value_;
}


void LongvarcharValue::output( FileManager& fm ) const
{
	fm << length_;
	fm.write( reinterpret_cast< void* >( const_cast< NC* >( buffer_ ) ), length_ );
}


void LongvarcharValue::input( FileManager& fm )
{
	fm >> length_;
	if( length_ )
	{
		if( buffer_ )
			delete [] buffer_;
		buffer_ = new NC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}
	fm.read( reinterpret_cast< void* >( buffer_ ), length_ );
}


void VarcharValue::output( FileManager& fm ) const
{
	fm << length_;
	fm.write( reinterpret_cast< void* >( const_cast< NC* >( buffer_ ) ), length_ );
}


void VarcharValue::input( FileManager& fm )
{
	fm >> length_;
	if( length_ )
	{
		if( buffer_ )
			delete [] buffer_;
		buffer_ = new NC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}
	fm.read( reinterpret_cast< void* >( buffer_ ), length_ );
}


void LongvarbinaryValue::output( FileManager& fm ) const
{
	fm << length_;
	fm.write( reinterpret_cast< void* >( const_cast< UC * >( buffer_ ) ), length_ );
}


void LongvarbinaryValue::input( FileManager& fm )
{
	fm >> length_;
	if( length_ )
	{
		if( buffer_ )
			delete [] buffer_;

		buffer_ = new UC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		fm.read( reinterpret_cast< void* >( buffer_ ), length_ );
	}
}


void VarbinaryValue::output( FileManager& fm ) const
{
	fm << length_;
	fm.write( reinterpret_cast< void* >( const_cast< UC * >( buffer_ ) ), length_ );
}


void VarbinaryValue::input( FileManager& fm )
{
	fm >> length_;
	if( length_ )
	{
		if( buffer_ )
			delete [] buffer_;

		buffer_ = new UC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		fm.read( reinterpret_cast< void* >( buffer_ ), length_ );
	}
}
