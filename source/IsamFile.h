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


#ifndef __IsamFile_h
#define __IsamFile_h


#define CQL_DATA_FILE_EXTENSION ".data"
#define CQL_INDEX_FILE_EXTENSION ".index"


class IsamFile;
typedef List< IsamFile > IsamFileList;
typedef ListElement< IsamFile, IsamFileList > IsamFileListElement;


class IsamFile : public IsamFileListElement, public AbstractTable, public RecordIndex
{
	CqlColumnTypesCreateList createColumnList_;  //  for create with variable length argument list
	AccessorTypesCreateList createKeyList_;  //  for create with variable length argument list
	ColumnDescriptor *currentColumn_;
	UL currentLength_;
	RECID currentPosition_;
	Record *currentRecord_;
	bool currentRecordCached_;
	RECID currentRecordPosition_;
	bool dataFetched_;
	CqlString dataName_;
	FileManager* file_;
	bool fileOpen_;
	IsamFileHeader header_;
	Index index_;
	CqlString indexName_;
	CqlString isamName_;
	bool temporary_;
	TableType type_;

	void addKey( IndexKeyDescriptor* /*key*/ );
	NI beginCurrentKeyOperation( void );
	void completeRowOperation( bool /*forceFetch*/ );
	void computeCurrentLength( void );
	void computeCostEqual( AccessCondition* );
	void computeCostGreater( AccessCondition* );
	void computeCostGreaterOrEqual( AccessCondition* );
	void computeCostLess( AccessCondition* );
	void computeCostLessOrEqual( AccessCondition* );
	void computeCostNotEqual( AccessCondition* );
	NI copyKeySegmentValues( void );
#ifndef CQL_BOOL_IS_INT
	BoundColumn *createBoundColumn( US /*columnNumber*/, bool& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
#endif  //  ~CQL_BOOL_IS_INT
	BoundColumn *createBoundColumn( US /*columnNumber*/, NC& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, UC& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, NI& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, UNI& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, S& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, US& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, L& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, UL& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, F& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, D& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, BigintValue& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, DecimalValue& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, NC*& /*value*/, UL& /*len*/, bool& /*nullflag*/, bool /*assignFlag*/, bool /*freeable*/ );
	BoundColumn *createBoundColumn( US /*columnNumber*/, NC*& /*value*/, UC& /*len*/, bool& /*nullflag*/, bool /*assignFlag*/, bool /*freeable*/ );
	BoundColumn *createBoundColumn( US /*columnNumber*/, UC*& /*value*/, UL& /*len*/, bool& /*nullflag*/, bool /*assignFlag*/, bool /*freeable*/ );
	BoundColumn *createBoundColumn( US /*columnNumber*/, UC*& /*value*/, UC& /*len*/, bool& /*nullflag*/, bool /*assignFlag*/, bool /*freeable*/ );
	BoundColumn *createBoundColumn( US /*columnNumber*/, CqlString& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, DateValue& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, TimeValue& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	BoundColumn *createBoundColumn( US /*columnNumber*/, TimestampValue& /*value*/, bool& /*nullflag*/, bool /*assignFlag*/ = false );
	void createCommon1( const TableType );
	void createCommon2( const CqlString& /*name*/ );
	NI destroyIndexIndex( void );
	NI destroyIsamIndex( void );
	bool evaluatePredicate( ConditionPredicate* );
	NI fetchData( void );
	bool findFirstEqual( bool /*existenceFlag*/ = false );
	bool findFirstGreater( bool /*existenceFlag*/ = false );
	bool findFirstGreaterOrEqual( bool /*existenceFlag*/ = false );
	bool findFirstLess( bool /*existenceFlag*/ );
	bool findFirstLessOrEqual( bool /*existenceFlag*/ = false );
	bool findFirstNotEqual( bool /*existenceFlag*/ = false );
	bool findNextEqual( bool /*existenceFlag*/ = false );
	bool findNextGreater( bool /*existenceFlag*/ = false );
	bool findNextGreaterOrEqual( bool /*existenceFlag*/ = false );
	bool findNextLess( bool /*existenceFlag*/ = false );
	bool findNextLessOrEqual( bool /*existenceFlag*/ = false );
	bool findNextNotEqual( bool /*existenceFlag*/ = false );
	void getConditionValues( void );
	void getNewRecordPosition( void );
	NI findKeyColumns( pAccessor );
	AccessorList& keys( void ) { return index_.keys(); }
	bool nextRow( bool /*forceFetch*/ );
	bool previousRow( bool /*forceFetch*/ );
	NI releaseCurrentPosition( void );
	UNI resolveConditions( void );
	NI rollbackRecord( void );
	NI rollbackRecord( pRecord );
	void setCurrentPosition( void );
	void setTemporary( void ) { temporary_ = CQL_YES; }
	bool temporary( void ) { return temporary_; }
	NI writeRecord( void );
	NI writeRecord( pRecord );

public :

	IsamFile( AbstractDatabaseHandle& );
	~IsamFile( void );

	AbstractTable& operator = ( AbstractTable& );

	void addColumn( const CqlColumnTypes );
	void addColumn( const CqlString& /*name*/, const CqlColumnTypes /*typeAndLength*/ );
	void addIndexMember( Accessor* );
	void addRow( void );
	void beginIsamOperation( NI = -1, NI = CQL_YES, NI = CQL_NO );
	void beginRowOperation( void );
#ifndef CQL_BOOL_IS_INT
	void bindColumn( US /*columnNumber*/, bool& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
#endif  //  ~CQL_BOOL_IS_INT
	void bindColumn( US /*columnNumber*/, NC& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, UC& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, S& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, US& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, NI& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, UNI& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, L& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, UL& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, F& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, D& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, NC*& /*data*/, UL & /*len*/, bool& /*nullFlag*/, bool /*forUpdate*/, bool freeable = true );
	void bindColumn( US /*columnNumber*/, NC*& /*data*/, UC & /*len*/, bool& /*nullFlag*/, bool /*forUpdate*/, bool freeable = true );
	void bindColumn( US /*columnNumber*/, UC*& /*data*/, UL & /*length*/, bool& /*nullFlag*/, bool /*forUpdate*/, bool freeable = true );
	void bindColumn( US /*columnNumber*/, UC*& /*data*/, UC & /*length*/, bool& /*nullFlag*/, bool /*forUpdate*/, bool freeable = true );
	void bindColumn( US /*columnNumber*/, BigintValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, CqlString& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, DateValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, DecimalValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, TimeValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, TimestampValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void checkPropagationFlags( void );
	void clearConditions( void );
	void clearFileOpen( void ) { fileOpen_ = false; }
	void close( void );
	void create( const TableType /* type */, const CqlString& /* name */, CqlColumnTypes** /*columnDefinitions*/, AccessorTypes** /*keyDefinitions*/ );
	RECID currentPosition( void );
	void dataName( const CqlString& /*name*/ );
	void decrementTransactionCounter( void );
	void deleteCurrentRecord( void );
	void deleteFiles( const CqlString& );
	void deleteIndexMember( US );
	void deleteKey( IndexKeyDescriptor* );
	void deleteRow( void );
	void endIsamOperation( void );
	void establishPosition( RECID /*position*/, US /*keyNumber*/, bool /*forUpdate*/ = true );
	UL estimateCost( void );
	UL estimateCost( ConditionPredicate* );
	FileManager* file( void );
	bool fileOpen( void ) { return fileOpen_; }
	bool findFirst( bool /*existflag*/ = false );
	bool findNext( bool /*existflag*/ = false );
	bool firstRow( void );
	void flushDataToRecord( void );
	void flushDirtyRecords( void );
	void getColumnInfo( US /*columnNumber*/, CqlColumnTypes& /*type*/, bool& /*nullflag*/ );
	AbstractType *getColumnValue( US /*columnNumber*/ );
	DatabaseHandle& hDb( void );
	void incrementTransactionCounter( void );
	Index& index( void ) { return index_; }
	void indexName( const CqlString& /*name*/ );
	bool lastRow( void );
	bool nextRow( void );
	void open( const CqlString& );
	bool previousRow( void );
	void releaseResources( void );
	void remove( MemoryIndex&, RECID& );
	NI rollbackDirtyRecords( void );
	ConditionPredicate *setCondition( US /*columnNumber*/, const NC& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const UC& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const S& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const US& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const NI& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const UNI& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const L& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const UL& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const F& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const D& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, NC*& /*data*/, UL& len, bool& /*nullflag*/, ConditionalOperators /*op*/, bool freeable );
	ConditionPredicate *setCondition( US /*columnNumber*/, NC*& /*data*/, UC& len, bool& /*nullflag*/, ConditionalOperators /*op*/, bool freeable );
	ConditionPredicate *setCondition( US /*columnNumber*/, UC*& /*data*/, UL& len, bool& /*nullflag*/, ConditionalOperators /*op*/, bool freeable );
	ConditionPredicate *setCondition( US /*columnNumber*/, UC*& /*data*/, UC& len, bool& /*nullflag*/, ConditionalOperators /*op*/, bool freeable );
	ConditionPredicate *setCondition( US /*columnNumber*/, const BigintValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const CqlString& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const DateValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const DecimalValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const TimeValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	ConditionPredicate *setCondition( US /*columnNumber*/, const TimestampValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ );
	void setDataFetched( void );
	void setFileOpen( void ) { fileOpen_ = CQL_YES; }
	TableType ttype( void ) { return CQL_CQL; }
	UNI transactionCounter( void );
	void unbindAllColumns( void );
	void unbindColumn( US /*columnNumber*/ );
	void updateRow( void );
};

typedef IsamFile *pIsamFile;


#endif  //  __IsamFile_h
