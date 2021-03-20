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


#ifndef __StatementHandle_h
#define __StatementHandle_h


class StatementHandle : public CqlConstants, public ErrorConstants
{
	SegmentedKeyGroup *addKeyGroup_;
	BookmarkUseOption bookmarkUseOption_;
	ConcurrencyOption concurrencyOption_;
	TempBuffer *createBuffer_;
	TableSpecification *creationTable_;
	CursorTypeOption cursorTypeOption_;
	SqlHandle& dbsql_;
	AbstractTableSpecification *dropAts_;
	SegmentedKeyGroup *dropKeyGroup_;
	DynamicParameterElementList dynamicParameters_;
	GrantPrivilegeList grantPrivileges_;
	GrantUserList grantUsers_;
	pAbstractTableSpecification insertAts_;
	InsertColumnNameList insertColumnNames_;
	NoscanOption noscanOption_;
	TableSpecification *oldTable_;
	UL queryTimeout_;
	RetrieveDataOption retrieveDataOption_;
	UL rowSetSize_;
	SelectExpressionList sets_;
	UL statementIdentifier_;
	StatementStatus status_;
	HandleStatementType type_;
	UpdateColumnNameAndExpList updateColumns_;
	UNI updateCount_;
	TableTableElement *updateTtel_;
	CqlString viewedTableName_;
	CqlString viewedTablePrefix_;

protected :

	friend class Parser;
	friend class SelectExpression;

	void addKeyGroup( SegmentedKeyGroup *akg ) { addKeyGroup_ = akg; }
	void createBuffer( TempBuffer *b ) { createBuffer_ = b; }
	void creationTable( TableSpecification *t ) { creationTable_ = t; }
	void deleteTtel( TableTableElement *ttel ) { updateTtel_ = ttel; }
	void dropAts( AbstractTableSpecification *a ) { dropAts_ = a; }
	void dropKeyGroup( SegmentedKeyGroup *skg ) { dropKeyGroup_ = skg; }
	void insertAts( AbstractTableSpecification *a ) { insertAts_ = a; }
	void oldTable( pTableSpecification t ) { oldTable_ = t; }
	void type( HandleStatementType t ) { type_ = t; }
	void updateTtel( pTableTableElement ttel ) { updateTtel_ = ttel; }
	CqlString& viewedTableName( void ) { return viewedTableName_; }
	CqlString& viewedTablePrefix( void ) { return viewedTablePrefix_; }

public :

	//************************************************************************
	//**  These methods are public because of limitations in the C++ class  **
	//**  protection mechanisms.  The alternative is to make one public     **
	//**  interface class (for example, StatementHandle) a friend of        **
	//**  another public interface class (for example, SqlHandle).  This    **
	//**  would expose the entire private/protected interface of one        **
	//**  public interface class to any application which declares an       **
	//**  object of the other public interface class.  The following        **
	//**  public declarations, while ugly, are the lesser of two evils.     **
	//**  Note that these classes are not indented for general use and      **
	//**  their signature is subject to change in future releases.          **
	//************************************************************************

	GrantPrivilegeList& grantPrivileges( void ) { return grantPrivileges_; }
	GrantUserList& grantUsers( void ) { return grantUsers_; }
	InsertColumnNameList& insertColumnNames( void ) { return insertColumnNames_; }
	SelectExpressionList& sets( void ) { return sets_; }
	UpdateColumnNameAndExpList& updateColumns( void ) { return updateColumns_; }


	//************************************************************************
	//**  The real public interface starts here.                            **
	//************************************************************************

	StatementHandle( SqlHandle& );
	StatementHandle( SqlHandle&,
					 BookmarkUseOption,
					 ConcurrencyOption,
					 CursorTypeOption,
					 NoscanOption,
					 UL /*queryTimeout*/,
					 RetrieveDataOption,
					 UL /*rowSetSize*/ );

	~StatementHandle( void );

	void alterTable( void );
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
	void bindColumn( US /*columnNumber*/, NC*& /*data*/, UL & /*length*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, UC*& /*data*/, UL & /*len*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, BigintValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, CqlString& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, DateValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, DecimalValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, TimeValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, TimestampValue& /*data*/, bool& /*nullFlag*/, bool /*forUpdate*/ = true );
	void bindColumn( US /*columnNumber*/, AbstractType& /*data*/, bool /*forUpdate*/ = true );
	void close( void );
	void createIndex( void );
	void createTable( void );
	void createView( void );
	SqlHandle& dbsql( void ) { return dbsql_; }
	void dropIndex( void );
	void dropTable( void );
	void dropView( void );
	void execute( void );
	CqlString getPath( void );
	void grant( void );
	void insertWithSelect( void );
	void insertWithValues( void );
	void positionedDelete( void );
	void positionedUpdate( void );
	void revoke( void );
	void searchedDelete( void );
	void searchedUpdate( void );
	void setPath( CqlString& /*new path*/ );
	HandleStatementType type( void ) { return type_; }
	UNI updateCount( void ) { return updateCount_; }
};

typedef StatementHandle *pStatementHandle;


#endif  //  __StatementHandle_h
