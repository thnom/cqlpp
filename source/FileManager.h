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


#ifndef __FileManager_h
#define __FileManager_h


class FileManager : public BufferSpaceIndex, public CqlConstants, public ErrorConstants, public SegmentTypes
{
	UNI bufferOffset;
	pUC bufferPointer;
	ClibFileManager clibFile;
	BaseBufferPage *currentReadBufferPage;
	RECID currentReadPosition;
	BaseBufferPage *currentWriteBufferPage;
	RECID currentWritePosition;
	RECID endOfFile;
	UL fileExtensionPage;
	US fileNumber;
	DatabaseHandle *hDb;
	CqlString name;
	UNI openCount;
	UNI propagationCounter;
	UL propagationTransactionNumber;
	UL readPageNumber;
	UNI transactionCounter;
	TableType type_;
	UL writePageNumber;

	bool isOpen;

	NI GetPage( UL, pUL, BaseBufferPage** );
	NI GetReadPage( UL );
	NI GetWritePage( UL );
	NI ReadCurrentPage( BufferPage*, UL );
	NI Seek( RECID, BaseBufferPage**, pUL );

public:

	FileManager( DatabaseHandle& /*hDb*/, TableType /*type*/ );
	~FileManager( void );

	FileManager& operator << ( const AbstractSegmentDescriptor* );
	FileManager& operator >> ( AbstractSegmentDescriptor** );

	FileManager& operator << ( const AbstractValue* );
	FileManager& operator >> ( AbstractValue*& );

	FileManager& operator << ( const AccessorTypes );
	FileManager& operator >> ( AccessorTypes& );

	FileManager& operator << ( const BigintValue& );
	FileManager& operator >> ( BigintValue& );

#ifndef CQL_BOOL_IS_INT
	FileManager& operator << ( const bool );
	FileManager& operator >> ( bool& );
#endif  //  ~CQL_BOOL_IS_INT

	FileManager& operator << ( const NC );
	FileManager& operator >> ( NC& );

	FileManager& operator << ( const CqlColumnTypes& );
	FileManager& operator >> ( CqlColumnTypes& );

	FileManager& operator << ( const CqlColumnType );
	FileManager& operator >> ( CqlColumnType& );

	FileManager& operator << ( const CqlString& );
	FileManager& operator >> ( CqlString& );

	FileManager& operator << ( const D );
	FileManager& operator >> ( D& );

	FileManager& operator << ( const DateValue& );
	FileManager& operator >> ( DateValue& );

	FileManager& operator << ( const DecimalValue& );
	FileManager& operator >> ( DecimalValue& );

	FileManager& operator << ( const F );
	FileManager& operator >> ( F& );

	FileManager& operator << ( const NI );
	FileManager& operator >> ( NI& );

	FileManager& operator << ( const L );
	FileManager& operator >> ( L& );

	FileManager& operator << ( const SegmentType );
	FileManager& operator >> ( SegmentType& );

	FileManager& operator << ( const SignValues );
	FileManager& operator >> ( SignValues& );

	FileManager& operator << ( const S );
	FileManager& operator >> ( S& );

	FileManager& operator << ( const TimeValue& );
	FileManager& operator >> ( TimeValue& );

	FileManager& operator << ( const UC );
	FileManager& operator >> ( UC& );

	FileManager& operator << ( const UNI );
	FileManager& operator >> ( UNI& );

	FileManager& operator << ( const UL );
	FileManager& operator >> ( UL& );

	FileManager& operator << ( const US );
	FileManager& operator >> ( US& );

	FileManager& operator << ( void*& );
	FileManager& operator >> ( void*& );

	NI Assign( FileManager& );
	ClibFileManager& ClibFile( void ) { return clibFile; }
	NI Close( BufferManager& );
	NI Create( CqlString& );
	BaseBufferPage *CurrentReadBufferPage( void ) { return currentReadBufferPage; }
	BaseBufferPage *CurrentWriteBufferPage( void ) { return currentWriteBufferPage; }
	void DecrementOpenCount( void ) { openCount--; }
	void DecrementPropagationCounter( void ) { propagationCounter--; }
	void DecrementTransactionCounter( void ) { transactionCounter--; }
	void deleteFile( const CqlString& /*fname*/ );
	NI DeletePageFromIndex( UL );
	ErrorManager& ErrorMan( void );
	NI FileNumber( void ) { return fileNumber; }
	NI GetBufferPointerForRead( void );
	NI GetBufferPointerForWrite( void );
	void IncrementOpenCount( void ) { openCount++; }
	void IncrementPropagationCounter( void ) { propagationCounter++; }
	void IncrementTransactionCounter( void ) { transactionCounter++; }
	void IncrementTransactionCounterIfZero( void );
	NI InputSeek( RECID );
	NI IsOpen( void ) { return isOpen; }
	CqlString& Name( void ) { return name; }
	NI Open( CqlString& name, TableType /*type*/ );
	UNI OpenCount( void ) { return openCount; }
	NI OpenForAppend( CqlString& name );
	NI OutputSeek( RECID location );
	UNI PropagationCounter( void ) { return propagationCounter; }
	UL PropagationTransactionNumber( void ) { return propagationTransactionNumber; }
	NI PurgePage( BaseBufferPage* );
	void read( void* /*space*/, UNI /*bytesToRead*/ );
	void readLogicalPage( pUC dest, RECID pos );
	NI ReleasePagesForFile( void );
	void SetPropagationTransactionNumber( UL ptn ) { propagationTransactionNumber = ptn; }
	void SetTransactionCounter( UNI c ) { transactionCounter = c; }
	TransactionStack& Stack( void );

	bool temporary( void )
	{
		switch( type_ )
		{
		case CQL_CQL_TEMPORARY :
			return true;

		case CQL_CQL :
		case CQL_DATABLITZ :
			return false;

		case CQL_UNDEFINED :
			throw InternalErrorException( __FILE__, __LINE__ );
		}

		//  Microsoft strikes again
		return false;
	}

	UNI TransactionCounter( void ) { return transactionCounter; }
	void type( TableType tt ) { type_ = tt; }
	TableType type( void ) { return type_; }
	void UpdateFileExtensionPage( UL );
	void write( void* /*space*/, UNI /*bytesToWrite*/ );
	void writeLock( RECID /*location*/ );
};

typedef FileManager *pFileManager;


#endif
