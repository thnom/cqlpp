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


#ifndef __View_h
#define __View_h


class View : public TableTableElement
{
	ViewSpecification *viewSpec_;

public :

	View( SqlHandle&, AbstractTableSpecification* );
	~View( void );

	AbstractTableSpecification *absTableSpec( void ) { return viewSpec_; }
	void addRow( void );
	CqlFixedLengthString& authorizationId( void ) { return viewSpec_->authorizationId(); }
	bool countFromIndex( Column* ) { return CQL_FAILURE; }
	void deleteRow( void );
	US dictionaryLength( void );
	SegmentedKeyGroupList& duplicateKeyGroups( void )
	{ 
		throw InternalErrorException( __FILE__, __LINE__ );
#ifdef _MSC_VER
#if _MSC_VER != 1200
		//  The Microsoft compiler is very stupid.  This would be an error if
		//  this code was ever executed (returning a reference to a local).
		//  However, it is never reached.  The same comment applies to the
		//  two cases below where this sequence is used.
		SegmentedKeyGroupList skgl;
		return skgl;
#endif
#endif
	}
	pAbstractTable file( UNI );
	bool firstRow( US /*keyNumber*/ );

	bool firstUsingIndex( Column* )
	{
		throw InternalErrorException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
		return false;
#endif
	}

	void flushDataToRecords( void );
	ForeignKeyList& foreignKeys( void )
	{
		throw InternalErrorException( __FILE__, __LINE__ );
#ifdef _MSC_VER
#if _MSC_VER != 1200
		ForeignKeyList fkl;
		return fkl;
#endif
#endif
	}
	void getColumnInfo( US /*columnNumber*/, CqlColumnTypes&, bool& /*nullflag*/ );
	AbstractType *getColumnValue( US /*columnNumber*/ );
	SegmentedKeyGroup *indexExistsForColumn( US /*columnNumber*/ );
	bool isView( void ) { return true; }
	bool lastRow( US /*keyNumber*/ );

	bool lastUsingIndex( Column* )
	{
		throw InternalErrorException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
		return false;
#endif
	}

	void magicLock( void );
	bool nextRow( void );
	bool previousRow( void );
	void readDictionaryInformation( TempBuffer& );
	TableSpecification *tableSpec( void ) { return 0; }
	CqlFixedLengthString& tableName( void ) { return viewSpec_->tableName(); }
	SegmentedKeyGroupList& uniqueKeyGroups( void )
	{
		throw InternalErrorException( __FILE__, __LINE__ );
#ifdef _MSC_VER
#if _MSC_VER != 1200
		SegmentedKeyGroupList skgl;
		return skgl;
#endif
#endif
	}
	void viewCleanup( void );
	pViewSpecification viewSpec( void ) { return viewSpec_; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef View *pView;


#endif  //  __View_h
