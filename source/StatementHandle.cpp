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


StatementHandle::StatementHandle( SqlHandle& sh )
	: addKeyGroup_( 0 ),
	  bookmarkUseOption_( UB_OFF ),
	  concurrencyOption_( CQL_CCO_LOCK ),
	  createBuffer_( 0 ),
	  creationTable_( 0 ),
	  cursorTypeOption_( CURSOR_DYNAMIC ),
	  dbsql_( sh ),
	  dropAts_( 0 ),
	  dropKeyGroup_( 0 ),
	  dynamicParameters_(),
	  grantPrivileges_(),
	  grantUsers_(),
	  insertAts_( 0 ),
	  insertColumnNames_(),
	  noscanOption_( NOSCAN_OFF ),
	  oldTable_( 0 ),
	  queryTimeout_( CQL_CD_QUERY_TIMEOUT ),
	  retrieveDataOption_( RD_OFF ),
	  rowSetSize_( CQL_CD_ROWSET_SIZE ),
	  sets_(),
	  statementIdentifier_( 0 ),
	  status_( VIRGIN ),
	  type_( CQL_HST_UNKNOWN ),
	  updateColumns_(),
	  updateCount_( 0 ),
	  updateTtel_( 0 ),
	  viewedTableName_(),
	  viewedTablePrefix_()
{
}


StatementHandle::StatementHandle( SqlHandle& sh,
								  BookmarkUseOption buopt,
								  ConcurrencyOption copt,
								  CursorTypeOption ctopt,
								  NoscanOption nopt,
								  UL qtimeout,
								  RetrieveDataOption rdopt,
								  UL rsetsize )
	: addKeyGroup_( 0 ),
	  bookmarkUseOption_( buopt ),
	  concurrencyOption_( copt ),
	  createBuffer_( 0 ),
	  creationTable_( 0 ),
	  cursorTypeOption_( ctopt ),
	  dbsql_( sh ),
	  dropAts_( 0 ),
	  dropKeyGroup_( 0 ),
	  dynamicParameters_(),
	  grantPrivileges_(),
	  grantUsers_(),
	  insertAts_( 0 ),
	  insertColumnNames_(),
	  noscanOption_( nopt ),
	  oldTable_( 0 ),
	  queryTimeout_( qtimeout ),
	  retrieveDataOption_( rdopt ),
	  rowSetSize_( rsetsize ),
	  sets_(),
	  statementIdentifier_( 0 ),
	  status_( VIRGIN ),
	  type_( CQL_HST_UNKNOWN ),
	  updateColumns_(),
	  updateCount_( 0 ),
	  updateTtel_( 0 ),
	  viewedTableName_(),
	  viewedTablePrefix_()
{
}


StatementHandle::~StatementHandle( void )
{
}


void StatementHandle::positionedUpdate( void )
{
	pSelectExpression selectExpression = sets_.first();

	selectExpression->positionedUpdatePart2( updateColumns_, updateTtel_ );
	updateCount_ = 1;
}


void StatementHandle::searchedUpdate( void )
{
	pSelectExpression selectExpression = sets_.first();

	selectExpression->searchedUpdatePart2( updateColumns_, updateTtel_ );
	updateCount_ = dbsql_.updateCount();
}


void StatementHandle::execute( void )
{
	switch( type_ )
	{
	case ALTER_TABLE :
		alterTable();

	case CREATE_INDEX :
		createIndex();

	case CREATE_TABLE :
		createTable();

	case CREATE_VIEW :
		createView();

	case DROP_INDEX :
		dropIndex();

	case DROP_TABLE :
		dropTable();

	case DROP_VIEW :
		dropView();

	case DELETE_POSITIONED :
		positionedDelete();

	case DELETE_SEARCHED :
		searchedDelete();

	case GRANT_STATEMENT :
		grant();

	case INSERT_VALUES :
		insertWithValues();

	case REVOKE_STATEMENT :
		revoke();

	case UPDATE_POSITIONED :
		positionedUpdate();

	case UPDATE_SEARCHED :
		searchedUpdate();

	default :
		throw InternalErrorException( __FILE__, __LINE__ );
	}
}


void StatementHandle::insertWithSelect( void )
{
	pSelectExpression selectExpression = sets_.first();
	pSelectExpression selectExp = ((pSelectExpression)selectExpression->next());
	selectExpression->insertWithSelectPart2( selectExp, insertAts_ );
	updateCount_ = dbsql_.updateCount();
}


void StatementHandle::insertWithValues( void )
{
	pSelectExpression selectExpression = sets_.first();
	selectExpression->checkInsertValues( insertColumnNames_ );
	selectExpression->copyInsertValues( insertAts_, insertColumnNames_ );
	selectExpression->checkView( insertAts_ );
	dbsql_.beginTransaction();

	try
	{
		insertAts_->addRow();
	}
	catch( CqlException& ex )
	{
		dbsql_.rollbackTransaction( false );
		throw ex;
	}

	updateCount_ = 1;
}


void StatementHandle::grant( void )
{
	dbsql_.parse()->grant( grantPrivileges_, grantUsers_ );
}


void StatementHandle::revoke( void )
{
	dbsql_.parse()->revoke( grantPrivileges_, grantUsers_ );
}


void StatementHandle::dropIndex( void )
{
	dbsql_.parse()->dropIndexPart2( creationTable_, oldTable_, dropKeyGroup_ );
}


//
//  at entry:
//
//  baseTableName and baseTablePrefix specify the table to be dropped.
//  cascade and restrict contain the drop conditions.
//
void StatementHandle::dropTable( void )
{
	dbsql_.parse()->processDropPart2( dropAts_ );
}


void StatementHandle::dropView( void )
{
	dbsql_.parse()->processDropPart2( dropAts_ );
}


void StatementHandle::positionedDelete( void )
{
	SelectExpression *selectExpression = sets_.first();
	//  updateTtel_ is also deleteTtel
	selectExpression->positionedDeletePart2( updateTtel_ );
	updateCount_ = 1;
}


void StatementHandle::searchedDelete( void )
{
	SelectExpression *selectExpression = sets_.first();
	//  updateTtel_ variable is also deleteTtel
	selectExpression->searchedDeletePart2( updateTtel_ );
	updateCount_ = dbsql_.updateCount();
}


void StatementHandle::createView( void )
{
	dbsql_.parse()->createViewPart2( viewedTableName_, viewedTablePrefix_, createBuffer_ );
	viewedTableName_.reset();
	viewedTablePrefix_.reset();
	delete createBuffer_;
}


void StatementHandle::createTable( void )
{
	SelectExpression *selectExpression = sets_.first();
	selectExpression->createTablePart2( creationTable_ );
}


void StatementHandle::createIndex( void )
{
	SelectExpression *selectExpression = sets_.first();
	selectExpression->createIndexPart2( oldTable_, creationTable_, addKeyGroup_ );
}


void StatementHandle::alterTable( void )
{
	SelectExpression *selectExpression = sets_.first();
	selectExpression->alterTablePart2( oldTable_, creationTable_ );
}


