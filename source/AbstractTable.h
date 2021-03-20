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


#ifndef __AbstractTable_h
#define __AbstractTable_h


class AbstractTable : public CqlConstants, public ExceptionCodes, public ErrorConstants, public AccessorTypes, public SegmentTypes
{
	const AbstractDatabaseHandle& hAdb_;
	AbstractColumnDescriptorList columns_;
	Condition cond_;
	UL handle_;

protected :

	pAccessor currentKey_;
	US numberOfKeys_;

public :

	AbstractTable( AbstractDatabaseHandle& );
	virtual ~AbstractTable( void );

	static AbstractTable *createObject( AbstractDatabaseHandle&, TableType );

	AbstractColumnDescriptorList& baseTableColumns( void ) { return columns_; }
	void bindColumnAV( US /*columnNumber*/, AbstractValue& /*data*/, bool /*forUpdate*/, bool /*freeable*/ );
	void bindColumnValue( US, UNI, void*, CqlColumnTypes );
	void bindColumnValue( US, CqlString, CqlColumnTypes );
	void bindColumnValue( US, NI );
	//  ******************  is columns() really necessary in addition to baseTableColumns() ???
	AbstractColumnDescriptorList& columns( void ) { return columns_; }
	Condition& cond( void ) { return cond_; }
	pAccessor currentKey( void ) { return currentKey_; }
	AbstractDatabaseHandle& hAdb( void ) { return const_cast< AbstractDatabaseHandle& >( hAdb_ ); }
	UL handle( void ) { return handle_; }
	void handle( UL h ) { handle_ = h; }
	void resetConditions( void );
	ConditionPredicate *setConditionAV( US /*columnNumber*/, const AbstractValue& /*data*/, ConditionalOperators /*op*/, bool /*freeable*/ );

	virtual AbstractTable& operator = ( AbstractTable& ) = 0;

	virtual void addColumn( const CqlColumnTypes /*typeAndLength*/ ) = 0;
	virtual void addColumn( const CqlString& /*name*/, const CqlColumnTypes /*typeAndLength*/ ) = 0;
	virtual void addIndexMember( Accessor* ) = 0;
	virtual void addRow( void ) = 0;
	virtual void beginIsamOperation( NI = -1, NI = CQL_YES, NI = CQL_NO ) = 0;
	virtual void beginRowOperation( void ) = 0;
#ifndef CQL_BOOL_IS_INT
	virtual void bindColumn( US /*columnNumber*/, bool& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
#endif
	virtual void bindColumn( US /*columnNumber*/, NC& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, UC& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, S& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, US& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, NI& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, UNI& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, L& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, UL& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, F& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, D& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, NC*& /*data*/, UL & /*length*/, bool& /*nullFlag*/, bool /*forUpdate*/, bool freeable ) = 0;
	virtual void bindColumn( US /*columnNumber*/, NC*& /*data*/, UC & /*length*/, bool& /*nullFlag*/, bool /*forUpdate*/, bool freeable ) = 0;
	virtual void bindColumn( US /*columnNumber*/, UC*& /*data*/, UL & /*len*/, bool& /*nullFlag*/, bool /*forUpdate*/, bool freeable ) = 0;
	virtual void bindColumn( US /*columnNumber*/, UC*& /*data*/, UC & /*len*/, bool& /*nullFlag*/, bool /*forUpdate*/, bool freeable ) = 0;
	virtual void bindColumn( US /*columnNumber*/, BigintValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, CqlString& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, DateValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, DecimalValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, TimeValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void bindColumn( US /*columnNumber*/, TimestampValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ ) = 0;
	virtual void clearConditions( void ) = 0;
	virtual void close( void ) = 0;
	virtual void create( const TableType /*type*/, const CqlString& /*name*/, CqlColumnTypes** /*columnDefinitions*/, AccessorTypes** /*keyDefinitions*/ ) = 0;
	virtual RECID currentPosition( void ) = 0;
	virtual void deleteCurrentRecord( void ) = 0;
	virtual void deleteFiles( const CqlString& name ) = 0;
	virtual void deleteIndexMember( US ) = 0;
	virtual void deleteRow( void ) = 0;
	virtual void endIsamOperation( void ) = 0;
	virtual void establishPosition( RECID /*position*/, US /*keyNumber*/, bool /*forUpdate*/ ) = 0;
	virtual UL estimateCost( void ) = 0;
	virtual UL estimateCost( ConditionPredicate* ) = 0;
	virtual bool fileOpen( void ) = 0;
	virtual bool findFirst( bool /*existflag*/ ) = 0;
	virtual bool findNext( bool /*existflag*/ ) = 0;
	virtual bool firstRow( void ) = 0;
	virtual void flushDirtyRecords( void ) = 0;
	virtual void getColumnInfo( US /*columnNumber*/, CqlColumnTypes& /*type*/, bool& /*nullflag*/) = 0;
	virtual AbstractType *getColumnValue( US /*columnNumber*/ ) = 0;
	virtual AccessorList& keys( void ) = 0;
	virtual bool lastRow( void ) = 0;
	virtual bool nextRow( void ) = 0;
	virtual void open( const CqlString& ) = 0;
	virtual bool previousRow( bool /*force fetch*/ ) = 0;
	virtual bool previousRow( void ) = 0;
	virtual void releaseResources( void ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const NC& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const UC& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const S& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const US& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const NI& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const UNI& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const L& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const UL& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const F& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const D& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, NC*& /*data*/, UL& /*len*/, bool& /*nullflag*/, ConditionalOperators /*op*/, bool /*freeable*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, NC*& /*data*/, UC& /*len*/, bool& /*nullflag*/, ConditionalOperators /*op*/, bool /*freeable*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, UC*& /*data*/, UL& /*len*/, bool& /*nullflag*/, ConditionalOperators /*op*/, bool /*freeable*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, UC*& /*data*/, UC& /*len*/, bool& /*nullflag*/, ConditionalOperators /*op*/, bool /*freeable*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const BigintValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const CqlString& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const DateValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const DecimalValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const TimeValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual ConditionPredicate *setCondition( US /*columnNumber*/, const TimestampValue& /*data*/, bool& /*nullflag*/, ConditionalOperators /*op*/ ) = 0;
	virtual void setDataFetched( void ) = 0;  //  should be part of ISAM file
	virtual void setFileOpen( void ) = 0;
	virtual bool temporary( void ) = 0;
	virtual TableType ttype( void ) = 0;
	virtual void unbindAllColumns( void ) = 0;
	virtual void unbindColumn( US /*columnNumber*/ ) = 0;
	virtual void updateRow( void ) = 0;
};

typedef AbstractTable *pAbstractTable;


#endif  //  __AbstractTable_h
