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


#ifndef __Table_h
#define __Table_h


class Table : public TableTableElement
{
	TableSpecification *tableSpec_;

public :

	Table( SqlHandle&, pAbstractTableSpecification );
	~Table( void );

	AbstractTableSpecification *absTableSpec( void ) { return tableSpec_; }
	void addRow( void );
	void Alter( void );
	CqlFixedLengthString& authorizationId( void ) { return tableSpec_->authorizationId(); }
	bool countFromIndex( Column* );
	void deleteRow( void );
	US dictionaryLength( void );
	SegmentedKeyGroupList& duplicateKeyGroups( void ) { return tableSpec_->duplicateKeyGroups(); }
	AbstractTable *file( UNI );
	bool firstRow( US /*keyNumber*/ );
	bool firstUsingIndex( Column* );
	void flushDataToRecords( void );
	ForeignKeyList& foreignKeys( void ) { return tableSpec_->foreignKeys(); }
	void getColumnInfo( US /*columnNumber*/, CqlColumnTypes& /*type*/, bool& /*nullflag*/ );
	AbstractType *getColumnValue( US /*columnNumber*/ );
	SegmentedKeyGroup *indexExistsForColumn( US /*columnNumber*/ );
	bool isView( void ) { return false; }
	bool lastRow( US /*keyNumber*/ );
	bool lastUsingIndex( Column* );
	void magicLock( void );
	bool nextRow( void );
	bool previousRow( void );
	void readDictionaryInformation( TempBuffer& );
	CqlFixedLengthString& tableName( void ) { return tableSpec_->tableName(); }
	TableSpecification *tableSpec( void ) { return tableSpec_; }
	SegmentedKeyGroupList& uniqueKeyGroups( void ) { return tableSpec_->uniqueKeyGroups(); }
	void viewCleanup( void ) { }
	pViewSpecification viewSpec( void ) { return 0; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef Table *pTable;


#endif  //  __Table_h
