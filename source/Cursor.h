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


#ifndef __Cursor_h
#define __Cursor_h


class Cursor;
typedef List< Cursor > CursorList;
typedef ListElement< Cursor, CursorList > CursorListElement;


class Cursor : public CursorListElement, public VariableSpecification, public CqlConstants
{
	enum CursorStatus
	{
		BEGINNING_OF_FILE,
		CLOSED,
		CURSOR_OPEN,
		CURSOR_OPEN_EMPTY,
		END_OF_FILE,
		FETCHING,
		VIRGIN
	};

	BoundColumnList boundColumns_;
	QueryExpression *cursorExpression_;
	CqlString cursorName_;
	SqlHandle& dbsql_;
	DynamicParameterElementList dynamicParameters_;
	SelectExpressionList sets_;
	CursorStatus status_;

protected :

	friend class Parser;

	AbstractTable *resultSet( void );
	void cursorExpression( QueryExpression *c ) { cursorExpression_ = c; }
	void status( enum CursorStatus stat ) { status_ = stat; }

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

	void cleanup( void );
	QueryExpression *cursorExpression( void ) { return cursorExpression_; }
	CqlString& cursorName( void ) { return cursorName_; }
	DynamicParameterElementList& dynamicParameters( void ) { return dynamicParameters_; }
	SelectExpressionList& sets( void ) { return sets_; }


	//************************************************************************
	//**  The real public interface starts here.                            **
	//************************************************************************

	Cursor( SqlHandle& );
	~Cursor( void );

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
	void bindColumn( US /*columnNumber*/, AbstractValue& /*data*/, bool /*forUpdate*/ = true );
	void close( void );
	ColumnMetadataList *describe( void );	
	SqlHandle& dbsql( void ) { return dbsql_; }
	bool fetch( void );
	RECID currentPosition( void );
	void currentPosition( RECID );
	void open( void );
	void positionedDelete( CqlString&, CqlString&, bool /*preparing*/ );
	void positionedUpdate( UpdateColumnNameAndExpList&, bool /*preparing*/ );
	enum CursorStatus status( void ) { return status_; }
};

typedef Cursor *pCursor;


#endif  //  __Cursor_h
