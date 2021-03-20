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


#include "CqlSqlInclude.h"


Cursor::Cursor( SqlHandle& sh )
	: CursorListElement(),
	  cursorExpression_( ((pQueryExpression)0) ),
	  cursorName_(),
	  dbsql_( sh ),
	  dynamicParameters_(),
	  sets_(),
	  status_( VIRGIN )
{
}


Cursor::~Cursor( void )
{
}


void Cursor::positionedUpdate( UpdateColumnNameAndExpList& updateColumns, bool preparing )
{
	switch( status_ )
	{
	case Cursor::VIRGIN :
	case Cursor::CLOSED :
	case Cursor::CURSOR_OPEN :
	case Cursor::CURSOR_OPEN_EMPTY :
	case Cursor::END_OF_FILE :
	case Cursor::BEGINNING_OF_FILE :
		throw CursorStateException( __FILE__, __LINE__ );

	case Cursor::FETCHING :
		break;
	}

	sets_.first()->positionedUpdate( updateColumns, preparing );
}


void Cursor::open( void )
{
	QueryInstruction *queryIns;

	dbsql_.resetError();
	dbsql_.parse()->clearStatementEnded();

	if( !cursorName_ )
			cursorName_ = *dbSqlEnv->anonymousCursorName();

	if( !cursorExpression_ )
		throw CursorStateException( __FILE__, __LINE__ );
	QueryInstructionList& ilist = cursorExpression_->instructions();

	bool noData = false;

	for( queryIns = ilist.last(); queryIns; queryIns = ilist.prev() )
	{
		try
		{
			queryIns->execute( *cursorExpression_ );
		}
		catch( NoDataException& )
		{
			noData = true;
		}
	}

	if( noData )
		status_ = CURSOR_OPEN_EMPTY;
	else
	{
		bool firstSelect;
		for( queryIns = ilist.first(), firstSelect = false; queryIns && !firstSelect; queryIns = ilist.next() )
			firstSelect = queryIns->assignResultSetFile( *cursorExpression_, firstSelect );

		resultSet()->unbindAllColumns();
		status_ = CURSOR_OPEN;
	}
}


//  Note, caller now needs to wrap call with try/catch to capture the no more rows condition
bool Cursor::fetch( void )
{
	bool result = false;

	switch( status_ )
	{
	case VIRGIN :
	case CLOSED :
		throw CursorStateException( __FILE__, __LINE__ );

	case CURSOR_OPEN_EMPTY :
	case END_OF_FILE :
		return false;

	case CURSOR_OPEN :
	case BEGINNING_OF_FILE :
		resultSet()->beginIsamOperation( 0 );
		result = resultSet()->firstRow();
		status_ = FETCHING;
		break;

	case FETCHING :
		result = resultSet()->nextRow();
		break;
	}

	return result;
}


void Cursor::bindColumn( US columnNumber, NC& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, UC& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, S& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, US& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, NI& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, UNI& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, L& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, UL& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, F& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, D& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, NC*& bdata, UL & len, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, len, nullFlag, forUpdate, true );
}


void Cursor::bindColumn( US columnNumber, UC*& bdata, UL & len, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, len, nullFlag, forUpdate, true );
}


void Cursor::bindColumn( US columnNumber, BigintValue& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, CqlString& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, DateValue& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, DecimalValue& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, TimeValue& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, TimestampValue& bdata, bool& nullFlag, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumn( columnNumber, bdata, nullFlag, forUpdate );
}


void Cursor::bindColumn( US columnNumber, AbstractValue& bdata, bool forUpdate )
{
	if( status_ == CURSOR_OPEN_EMPTY )
		return;

	resultSet()->bindColumnAV( columnNumber, bdata, forUpdate, true );
}


void Cursor::close( void )
{
	status_ = CLOSED;
}


void Cursor::cleanup( void )
{
	if( cursorExpression_ )
	{
		QueryInstruction *queryIns;
		QueryInstructionList& ilist = cursorExpression_->instructions();

		for( queryIns = ilist.last(); queryIns; queryIns = ilist.prev() )
			queryIns->cleanup( *cursorExpression_ );

		cursorExpression_->cleanup();
		delete cursorExpression_;
		cursorExpression_ = 0;
	}
}


RECID Cursor::currentPosition( void )
{
	return resultSet()->currentPosition();
}


void Cursor::currentPosition( RECID pos )
{
	//  arbitrarily use key 0
	resultSet()->establishPosition( pos, 0, true );
}


AbstractTable *Cursor::resultSet( void )
{
	return cursorExpression_->resultSet();
}


void Cursor::positionedDelete( CqlString&, CqlString&, bool preparing )
{
	//
	//  check for valid cursor state
	//
	switch( status_ )
	{
	case Cursor::VIRGIN :
	case Cursor::CLOSED :
	case Cursor::CURSOR_OPEN :
	case Cursor::CURSOR_OPEN_EMPTY :
	case Cursor::BEGINNING_OF_FILE :
	case Cursor::END_OF_FILE :
		throw CursorStateException( __FILE__, __LINE__ );

	case Cursor::FETCHING :
		break;
	}

	sets_.first()->positionedDelete( preparing );
}


ColumnMetadataList *Cursor::describe( void )
{
		AbstractTable *rs = resultSet();
		AbstractColumnDescriptorList acdl = rs->columns();
		AbstractColumnDescriptor *cd;
		ColumnMetadataList *cml = new ColumnMetadataList();

		pColumn col;
		SelectExpression *sel = sets_.first();

		US columnNum;
		for( cd = acdl.first(),
				 col = sel->columns().first(),
				 columnNum = 0;

			 col && cd;

			 cd = acdl.next(),
				 col = sel->columns().next(),
				 columnNum++ )
		{
			ColumnMetadata *cm = new ColumnMetadata( col->ColumnExpression().label().text(),
														 ((unsigned short)columnNum),
														 cd->columnType(),
														 cd->length(),
														 cd->precision() );

				cml->add( cm );
		}

		return cml;
}
