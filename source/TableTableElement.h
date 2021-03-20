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


#ifndef __TableTableElement_h
#define __TableTableElement_h


class TableTableElement;
typedef List< TableTableElement > TableTableElementListBase;
typedef ListElement< TableTableElement, TableTableElementListBase > TableTableElementListElement;

//
//  this class is the list element for the TableTable.  The actual TableTable entries are
//  derived from this class (one type for base tables, and one type for views)
//
class TableTableElement : public TableTableElementListElement, public CqlConstants, public ErrorConstants
{
	NI cartesianProductCount_;
	bool correlated_;
	CqlString correlationName_;
	SqlHandle& dbsql_;
	bool linkFlag_;
	bool processed_;
	US setNumber_;
	US tableNumber_;
	bool valid_;


public :

	TableTableElement( SqlHandle& );
	virtual ~TableTableElement( void );

	TableTableElement& operator = ( const TableTableElement& );

	NI cartesianProductCount( void ) { return cartesianProductCount_; }
	void clearCartesianProductCount( void ) { cartesianProductCount_ = 0; }
	void clearConditions( void );
	void clearValid( void ) { valid_ = false; }
	bool correlated( void ) { return correlated_; }
	CqlString& correlationName( void ) { return correlationName_; }
	static TableTableElement *createUsingDictionary( SqlHandle&, TripleStringListElement& );
	static TableTableElement *createObject( SqlHandle&, bool /*viewflag*/, AbstractTableSpecification& );
	SqlHandle& dbsql( void ) { return dbsql_; }
	void incrementCartesianProductCount( void ) { cartesianProductCount_++; }
	bool linkFlag( void ) { return linkFlag_; }
	void processView( void );
	void rereadCurrentRow( void );
	void setCorrelated( void ) { correlated_ = true; }
	void setLinkFlag( void ) { linkFlag_ = true; }
	US setNumber( void ) { return setNumber_; }
	void setNumber( US sn ) { setNumber_ = sn; }
	void setValid( void ) { valid_ = true; }
	US tableNumber( void ) { return tableNumber_; }
	void tableNumber( US n ) { tableNumber_ = n; }
	void update( void );
	bool valid( void ) { return valid_; }

	virtual AbstractTableSpecification *absTableSpec( void ) = 0;
	virtual void addRow( void ) = 0;
	virtual CqlFixedLengthString& authorizationId( void ) = 0;
	virtual bool countFromIndex( Column* ) = 0;
	virtual void deleteRow( void ) = 0;
	virtual US dictionaryLength( void ) = 0;
	virtual SegmentedKeyGroupList& duplicateKeyGroups( void ) = 0;
	virtual pAbstractTable file( UNI ) = 0;
	virtual bool firstRow( US /*keyNumber*/ ) = 0;
	virtual bool firstUsingIndex( Column* ) = 0;
	virtual void flushDataToRecords( void ) = 0;
	virtual ForeignKeyList& foreignKeys( void ) = 0;
	virtual void getColumnInfo( US /*columnNumber*/, CqlColumnTypes&, bool& /*nullflag*/ ) = 0;
	virtual AbstractType *getColumnValue( US /*columnNumber*/ ) = 0;
	virtual SegmentedKeyGroup *indexExistsForColumn( US /*columnNumber*/ ) = 0;
	virtual bool isView( void ) = 0;
	virtual bool lastRow( US /*keyNumber*/ ) = 0;
	virtual bool lastUsingIndex( Column* ) = 0;
	virtual void magicLock( void ) = 0;
	virtual bool nextRow( void ) = 0;
	virtual bool previousRow( void ) = 0;
	virtual void readDictionaryInformation( TempBuffer& ) = 0;
	virtual CqlFixedLengthString& tableName( void ) = 0;
	virtual TableSpecification *tableSpec( void ) = 0;
	virtual SegmentedKeyGroupList& uniqueKeyGroups( void ) = 0;
	virtual void viewCleanup( void ) = 0;
	virtual ViewSpecification *viewSpec( void ) = 0;
	virtual void writeDictionaryInformation( TempBuffer& ) = 0;
};

typedef TableTableElement *pTableTableElement;


#endif  //  __TableTableElement_h
