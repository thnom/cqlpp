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


IndexDictionary::IndexDictionary( SqlHandle& sqlh ) : SystemDictionary( sqlh, CqlString( CQL_INDEXDICT_NAME ) ), indexName_( CQL_INDEXDICT_INDEX_NAME_LENGTH ), indexNameNull_( false )
{
	try
	{
		table_->open( dictionaryName_ );
	}
	catch( AbstractTableException& )
	{
		dbsql_.resetError();

		CqlColumnTypes *columnDescriptors[ 4 ];
		columnDescriptors[ 0 ] = new CqlColumnTypes( "indexName", CQL_INDEXDICT_INDEX_NAME_TYPE, CQL_INDEXDICT_INDEX_NAME_LENGTH );
		columnDescriptors[ 1 ] = new CqlColumnTypes( "tableName", CQL_INDEXDICT_TABLE_NAME_TYPE, CQL_INDEXDICT_TABLE_NAME_LENGTH );
		columnDescriptors[ 2 ] = new CqlColumnTypes( "owner", CQL_INDEXDICT_AUTHORIZATION_TYPE, CQL_INDEXDICT_AUTHORIZATION_LENGTH );
		columnDescriptors[ 3 ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );

		AccessorTypes *keyDescriptors[ 2 ];
		SegmentTypes *segs[ 2 ];
		keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, segs );
		segs[ 0 ] = new SegmentTypes( "indexName", 0, SegmentTypes::CQL_ASCENDING );
		segs[ 1 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );

		keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

		table_->create( CqlConstants::CQL_CQL, dictionaryName_, columnDescriptors, keyDescriptors );

		delete columnDescriptors[ 0 ];
		delete columnDescriptors[ 1 ];
		delete columnDescriptors[ 2 ];
		delete columnDescriptors[ 3 ];
		delete keyDescriptors[ 0 ];
		delete segs[ 0 ];
		delete segs[ 1 ];
		delete keyDescriptors[ 1 ];
	}
	catch( ... )
	{
		throw;
	}

	SystemDictionary::bind( CID_TABLE_NAME, CID_AUTHORIZATION );
	table_->bindColumn( CID_INDEX_NAME, indexName_, indexNameNull_, true );
}


IndexDictionary::~IndexDictionary( void )
{
	indexName_.reset();
}


void IndexDictionary::add( CqlString& indexName, CqlString& _tableName, CqlString& _auth )
{
	indexName_ = indexName;
	tableName_ = _tableName;
	auth_ = _auth;
	table_->addRow();
}


void IndexDictionary::ddelete( CqlString& indexName )
{
	indexName_ = indexName;
	if( !table_->findFirst( false ) )
		return;

	table_->deleteRow();
}


//  tableName and auth are result parameters here
void IndexDictionary::find( CqlString& indexName, CqlString& _tableName, CqlString& _auth )
{
	indexName_ = indexName;
	if( !table_->findFirst( false ) )
		return;

	_tableName = tableName_;
	_auth = auth_;
}


MainDictionary::MainDictionary( SqlHandle& sqlh )
	: SystemDictionary( sqlh, CQL_MAINDICT_NAME ),
	  aliasFlag_( false ),
	  isView_( 0 ),
	  isViewNull_( false ),
	  recordLength_( 0 ),
	  recordLengthNull_( false ),
	  theRest_( sqlh.aHandle(), &sqlh ),
	  theRestNull_( false )
{
	try
	{
		table().open( dictionaryName() );
	}
	catch( AbstractTableException& )
	{
		//  open failed, try to create
		sqlh.aHandle().aErrorMan().resetError();

		CqlColumnTypes *columnDescriptors[ 6 ];
		//  record length
		columnDescriptors[ 0 ] = new CqlColumnTypes( "recordLength", CQL_MAINDICT_RECORD_LENGTH_TYPE );
		//  table name
		columnDescriptors[ 1 ] = new CqlColumnTypes( "tableName", CQL_MAINDICT_TABLE_NAME_TYPE, CQL_MAINDICT_TABLE_NAME_LENGTH );
		//  authorization
		columnDescriptors[ 2 ] = new CqlColumnTypes( "owner", CQL_MAINDICT_AUTHORIZATION_TYPE, CQL_MAINDICT_AUTHORIZATION_LENGTH );
		//  view flag
		columnDescriptors[ 3 ] = new CqlColumnTypes( "viewFlag", CQL_MAINDICT_IS_VIEW_TYPE );
		//  the rest (BLOB) (BLOBs have 0 length)
		columnDescriptors[ 4 ] = new CqlColumnTypes( "data", CQL_MAINDICT_THE_REST_TYPE, 0 );
		//  no more columns
		columnDescriptors[ 5 ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );

		AccessorTypes *keyDescriptors[ 3 ];

		SegmentTypes *segs[ 3 ];
		keyDescriptors[ 0 ] = new AccessorTypes( CQL_TREE_INDEX, CQL_NO_DUPLICATES, segs );
		segs[ 0 ] = new SegmentTypes( "tableName", 1, CQL_ASCENDING );
		segs[ 1 ] = new SegmentTypes( "owner", 2, CQL_ASCENDING );
		segs[ 2 ] = new SegmentTypes( -1, CQL_SEGMENT_UNDEFINED_TYPE );

		SegmentTypes *segs2[ 2 ];
		keyDescriptors[ 1 ] = new AccessorTypes( CQL_TREE_INDEX, CQL_DUPLICATES_ALLOWED, segs2 );
		segs2[ 0 ] = new SegmentTypes( "owner", 2, CQL_ASCENDING );
		segs2[ 1 ] = new SegmentTypes( -1, CQL_SEGMENT_UNDEFINED_TYPE );

		keyDescriptors[ 2 ] = new AccessorTypes( CQL_ACCESSOR_UNDEFINED_TYPE );

		table().create( CQL_DICTIONARY_TABLE_TYPE, dictionaryName_, columnDescriptors, keyDescriptors );

		delete columnDescriptors[ 0 ];
		delete columnDescriptors[ 1 ];
		delete columnDescriptors[ 2 ];
		delete columnDescriptors[ 3 ];
		delete columnDescriptors[ 4 ];
		delete columnDescriptors[ 5 ];
		delete keyDescriptors[ 0 ];
		delete segs[ 0 ];
		delete segs[ 1 ];
		delete segs[ 2 ];
		delete keyDescriptors[ 1 ];
	}
	catch( ... )
	{
		throw;
	}

	try
	{
		SystemDictionary::bind( CQL_MAINDICT_TABLE_NAME, CQL_MAINDICT_AUTHORIZATION );
		table_->bindColumn( CQL_MAINDICT_RECORD_LENGTH, recordLength_, recordLengthNull_, true );
		table_->bindColumn( CQL_MAINDICT_IS_VIEW, isView_, isViewNull_, true );
	}

	catch( CqlException& )
	{
		throw DictionaryException( __FILE__, __LINE__ );
	}
}


MainDictionary::~MainDictionary( void )
{
}


void MainDictionary::add( S length,
							 CqlString& _tableName,
							 CqlString& _auth,
							 S viewflag,
							 TempBuffer& buffer )
{
	tableName_ = _tableName;
	auth_ = _auth;
	isView_ = viewflag;
	recordLength_ = length;

	try
	{
		UC *theRest = buffer.bufferBase();
		UL theRestSize = buffer.size();
		table_->bindColumn( CQL_MAINDICT_THE_REST,
							theRest,
							theRestSize,
							theRestNull_,
							true,
							false );
		table_->beginRowOperation();
		table_->addRow();
		table_->unbindColumn( CQL_MAINDICT_THE_REST );
	}
	catch( CqlException& )
	{
		//**************** print exception here
		throw DictionaryException( __FILE__, __LINE__ );
	}
}


void MainDictionary::ddelete( CqlString& _tableName, CqlString& _auth )
{
	bool tnameNull = false;
	bool authNull = false;
	tableName_ = _tableName;
	auth_ = _auth;

	table_->beginIsamOperation( 0 );
	table_->setCondition( 1, tableName_, tnameNull, CQL_COP_EQUAL );
	table_->setCondition( 2, auth_, authNull, CQL_COP_EQUAL );

	if( !table_->findFirst( false ) )
		return;

	table_->deleteRow();
}


//
//  result will go, and pAbstractTableSpecification will be returned,
//  when exception handling is fully implemented
//
pAbstractTableSpecification MainDictionary::find( const CqlString& tname, const CqlString& owner )
{
	bool tnameNull = false;
	bool authNull = false;
	tableName() = tname;
	auth() = owner;
	table_->setCondition( 1, tableName(), tnameNull, CQL_COP_EQUAL );
	table_->setCondition( 2, auth(), authNull, CQL_COP_EQUAL );

	if( !table_->findFirst( false ) )
		throw TableNotFoundException( __FILE__, __LINE__ );

	theRest_.setBuffer( recordLength_ + 8 );

	UL lreclength = recordLength_ + 4;
	table_->bindColumn( 4, theRest_.bufferRef(), lreclength, theRestNull_, false, false );
	if( !table_->findFirst( false ) )
		throw InternalErrorException( __FILE__, __LINE__ );
	table_->clearConditions();

	pAbstractTableSpecification at;

	if( isView_ )
		at = new ViewSpecification( dbsql_ );
	else
		at = new TableSpecification( dbsql_ );

	if( !at )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	at->tableName() = tname;
	at->authorizationId() = auth_;
	at->dictionaryRecordBuffer( theRest_.bufferBase() );
	at->dictionaryRecordLength( recordLength_ );

	at->readDictionaryInformation( theRest_ );
	//*********************  catch exceptions

	if( aliasFlag_ )
		at->setAliasFlag();
	else if( dbsql_.activeTables().AddIndexNode( &dbsql_, tableName_, auth_, at ) == CQL_FAILURE )
		return 0;

	table_->unbindColumn( 4 );
	return at;
}


TableIdList *MainDictionary::getTableIds( const CqlString& owner )
{
	bool authNull = false;
	bool nameBufNull = false;
	char *pNameBuf = 0;
	UL nblen = CQL_MAINDICT_TABLE_NAME_LENGTH;
	auth() = owner;

	pNameBuf = new char[ CQL_MAINDICT_TABLE_NAME_LENGTH + 1 ];
	if( !pNameBuf )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	table_->beginIsamOperation( 1, CQL_NO );
	table_->setCondition( 2, auth(), authNull, CQL_COP_EQUAL );
	table_->bindColumn( 1, pNameBuf, nblen, nameBufNull, false, true );

	TableIdList *tlist = new TableIdList();
	bool rc;
	for( rc = table_->findFirst( false ); rc; rc = table_->findNext( false ) )
	{
		TableId *tid = new TableId( owner, CqlString(pNameBuf) );
		tlist->add( tid );
	}

	SystemDictionary::bind( CID_TABLE_NAME, CID_AUTHORIZATION );
	return tlist;
}


ColumnMetadataList *MainDictionary::getColumnMetadata( TableId *tid )
{
	AbstractTableSpecification *at = find( tid->tableName(), tid->owner() );
	ColumnMetadataList *cml = new ColumnMetadataList();

	PermanentColumnSpecification *pcs;
	for( pcs = at->columns().first(); pcs; pcs = at->columns().next() )
	{
		ColumnMetadata *cm = new ColumnMetadata( pcs->columnName(),
												 pcs->columnNumber(),
												 pcs->type(),
												 pcs->scale(),
												 pcs->precision() );
		cml->add( cm );
	}

	return cml;
}


PrivilegeDictionary::PrivilegeDictionary( SqlHandle& sqlh )
	: SystemDictionary( sqlh, CQL_PRIVILEGEDICT_NAME ),
	  deletePriv_( 0 ),
	  deletePrivNull_( 0 ),
	  grantOption_( 0 ),
	  grantOptionNull_( 0 ),
	  insertPriv_( 0 ),
	  insertPrivNull_( 0 ),
	  referencesPriv_( 0 ),
	  referencesPrivNull_( 0 ),
	  selectPriv_( 0 ),
	  selectPrivNull_( 0 ),
	  updatePriv_( 0 ),
	  updatePrivNull_( 0 ),
	  user_( CQL_PRIVILEGEDICT_USER_LENGTH ),
	  userNull_( 0 )
{
	try
	{
		table_->open( dictionaryName_ );
	}
	catch( AbstractTableException& )
	{
		sqlh.resetError();

		//*******************************************************************
		//**  Open failed, try to create.                                  **
		//*******************************************************************

		CqlColumnTypes *columnDescriptors[ 10 ];
		//  table name
		columnDescriptors[ 0 ] = new CqlColumnTypes( "tableName", CQL_PRIVILEGEDICT_TABLE_NAME_TYPE, CQL_PRIVILEGEDICT_TABLE_NAME_LENGTH );
		//  authorization
		columnDescriptors[ 1 ] = new CqlColumnTypes( "owner", CQL_PRIVILEGEDICT_AUTHORIZATION_TYPE, CQL_PRIVILEGEDICT_AUTHORIZATION_LENGTH );
		//  user holding privileges
		columnDescriptors[ 2 ] = new CqlColumnTypes( "user", CQL_PRIVILEGEDICT_USER_TYPE, CQL_PRIVILEGEDICT_USER_LENGTH );
		//  grant option flag
		columnDescriptors[ 3 ] = new CqlColumnTypes( "grantOption", CQL_PRIVILEGEDICT_GRANT_OPTION_TYPE );
		//  delete privilege flag
		columnDescriptors[ 4 ] = new CqlColumnTypes( "deletePrivilege", CQL_PRIVILEGEDICT_DELETE_PRIV_TYPE );
		//  insert privilege flag
 		columnDescriptors[ 5 ] = new CqlColumnTypes( "insertPrivilege", CQL_PRIVILEGEDICT_INSERT_PRIV_TYPE );
		//  references privilege flag
		columnDescriptors[ 6 ] = new CqlColumnTypes( "referencesPrivilege", CQL_PRIVILEGEDICT_REFERENCES_PRIV_TYPE );
		//  select privilege flag
		columnDescriptors[ 7 ] = new CqlColumnTypes( "selectPrivilege", CQL_PRIVILEGEDICT_SELECT_PRIV_TYPE );
		//  update privilege flag
		columnDescriptors[ 8 ] = new CqlColumnTypes( "updatePrivilege", CQL_PRIVILEGEDICT_UPDATE_PRIV_TYPE );
		//  end of columns
		columnDescriptors[ 9 ] = new CqlColumnTypes( CqlColumnTypes::CQL_COLUMN_UNDEFINED_TYPE );

		AccessorTypes *keyDescriptors[ 2 ];
		SegmentTypes *segs[ 4 ];
		keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, segs ),
		segs[ 0 ] = new SegmentTypes( "tableName", 0, SegmentTypes::CQL_ASCENDING );
		segs[ 1 ] = new SegmentTypes( "owner", 1, SegmentTypes::CQL_ASCENDING );
		segs[ 2 ] = new SegmentTypes( "user", 2, SegmentTypes::CQL_ASCENDING );
		segs[ 3 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );

		keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

		table_->create( CQL_CQL, dictionaryName_, columnDescriptors, keyDescriptors );

		delete columnDescriptors[ 0 ];
		delete columnDescriptors[ 1 ];
		delete columnDescriptors[ 2 ];
		delete columnDescriptors[ 3 ];
		delete columnDescriptors[ 4 ];
 		delete columnDescriptors[ 5 ];
		delete columnDescriptors[ 6 ];
		delete columnDescriptors[ 7 ];
		delete columnDescriptors[ 8 ];
		delete columnDescriptors[ 9 ];
		delete keyDescriptors[ 0 ];
		delete segs[ 0 ];
		delete segs[ 1 ];
		delete segs[ 2 ];
		delete segs[ 3 ];
		delete keyDescriptors[ 1 ];
	}
	catch( ... )
	{
		throw;
	}

	try
	{
		SystemDictionary::bind( CID_TABLE_NAME, CID_AUTHORIZATION );
		table_->bindColumn( CID_USER, user_, userNull_, true );
		user_ = sqlh.aHandle().userName();
		table_->bindColumn( CID_GRANT_OPTION, grantOption_, grantOptionNull_, true );
		table_->bindColumn( CID_DELETE_PRIV, deletePriv_, deletePrivNull_, true );
		table_->bindColumn( CID_INSERT_PRIV, insertPriv_, insertPrivNull_, true );
		table_->bindColumn( CID_REFERENCES_PRIV, referencesPriv_, referencesPrivNull_, true );
		table_->bindColumn( CID_SELECT_PRIV, selectPriv_, selectPrivNull_, true );
		table_->bindColumn( CID_UPDATE_PRIV, updatePriv_, updatePrivNull_, true );
	}

	catch( CqlException& )
	{
		throw DictionaryException( __FILE__, __LINE__ );
	}
}


PrivilegeDictionary::~PrivilegeDictionary( void )
{
}


NI PrivilegeDictionary::findPrivileges( CqlString& _tableName, CqlString& _auth, CqlString& user )
{
	//*******************************************************************
	//**  If the user names match, owner has all privileges            **
	//*******************************************************************
	if( dbsql_.aHandle().userName().stripCompare( _auth ) )
	{
		deletePriv_ = grantOption_ = insertPriv_ = referencesPriv_ = selectPriv_ = updatePriv_ = CQL_YES;
		return CQL_YES;
	}

	if( findStatus_ == CQL_YES && tableName_ == _tableName && auth_ == _auth )
		//  nothing to do
		return selectPriv_;

	tableName_ = _tableName;
	auth_ = _auth;
	user_ = user;
	table_->setCondition( CID_TABLE_NAME, tableName_, tableNameNull_, CQL_COP_EQUAL );
	table_->setCondition( CID_AUTHORIZATION, auth_, authNull_, CQL_COP_EQUAL );
	table_->setCondition( CID_USER, user_, userNull_, CQL_COP_EQUAL );

	findStatus_ = true;
	table_->beginIsamOperation( 0 );
	if( !table_->findFirst( false ) )
	{
		deletePriv_ = grantOption_ = insertPriv_ = referencesPriv_ = selectPriv_ = updatePriv_ = CQL_NO;
		return CQL_NO;
	}

	//  values are bound, so find copied them
	return CQL_YES;
}


bool PrivilegeDictionary::selectPrivilege( CqlString& _tableName, CqlString& _auth, bool& gOption )
{
	if( !findPrivileges( _tableName, _auth, dbsql_.aHandle().userName() ) )
		return false;

	gOption = ( grantOption_ ? true : false );
	return ( selectPriv_ ? true : false );
}


bool PrivilegeDictionary::deletePrivilege( CqlString& _tableName, CqlString& _auth, bool& gOption )
{
	if( !findPrivileges( _tableName, _auth, dbsql_.aHandle().userName() ) )
		return false;

	gOption = ( grantOption_ ? true : false );
	return ( deletePriv_ ? true : false );
}


bool PrivilegeDictionary::updatePrivilege( CqlString& _tableName, CqlString& _auth, bool& gOption )
{
	if( !findPrivileges( _tableName, _auth, dbsql_.aHandle().userName() ) )
		return false;

	gOption = ( grantOption_ ? true : false );
	return ( updatePriv_ ? true : false );
}


bool PrivilegeDictionary::insertPrivilege( CqlString& _tableName, CqlString& _auth, bool& gOption )
{
	if( !findPrivileges( _tableName, _auth, dbsql_.aHandle().userName() ) )
		return false;

	gOption = ( grantOption_ ? true : false );
	return ( insertPriv_ ? true : false );
}


void PrivilegeDictionary::addOrUpdate( PrivilegeDictionaryRecord& priv )
{
	findPrivileges( priv.tableName(), priv.auth(), priv.user() );

	//  If findPrivileges didn't find a record for this name/auth/user,
	//  set all the privileges to no.
	if( findStatus_ == CQL_NO )
	{
		deletePriv_
			= updatePriv_
			= grantOption_
			= insertPriv_
			= referencesPriv_
			= selectPriv_
			= updatePriv_
			= CQL_NO;
	}

	//  This is OK regardless of the current state of grantOption_
	//  ditto for all the other flags
	if( priv.grantOption() )
		grantOption_ = CQL_YES;

	if( priv.deletePriv() )
		deletePriv_ = CQL_YES;

	if( priv.insertPriv() )
		insertPriv_ = CQL_YES;

	if( priv.referencesPriv() )
		referencesPriv_ = CQL_YES;

	if( priv.selectPriv() )
		selectPriv_ = CQL_YES;

	if( priv.updatePriv() )
		updatePriv_ = CQL_YES;

	if( findStatus_ == CQL_NO )
		table_->addRow();
	else
		table_->updateRow();
}


void PrivilegeDictionary::deletePrivs( PrivilegeDictionaryRecord& priv )
{
	findPrivileges( priv.tableName(), priv.auth(), priv.user() );

	//  if( findStatus_ == CQL_NO )
	//*********************  throw an exception, not found
}

PrivilegeDictionaryRecord::PrivilegeDictionaryRecord( void ) : GrantPrivilege(), auth_(), grantOption_( false ), tableName_(), user_()
{
}


PrivilegeDictionaryRecord::~PrivilegeDictionaryRecord( void )
{
	user_.reset();
	tableName_.reset();
	auth_.reset();
}


void PrivilegeDictionaryRecord::Assign( CqlString& tableAuthId, CqlString& tName, CqlString& _user )
{
	auth_ = tableAuthId;
	tableName_ = tName;
	user_ = _user;
}


void PrivilegeDictionaryRecord::reset( void )
{
	grantOption_ = false;
	auth_.reset();
	tableName_.reset();
	user_.reset();
	GrantPrivilege::reset();
}


PrivilegeFieldDictionary::PrivilegeFieldDictionary( SqlHandle& sqlh )
	: SystemDictionary( sqlh, CQL_PRIVILEGEFIELD_DICTIONARY_NAME ),
	  columnName_( CQL_PRIVILEGEFIELDDICT_COLUMN_NAME_LENGTH ),
	  columnNameNull_( false ),
	  findStatus_( false ),
	  priv_( false ),
	  privNull_( false ),
	  user_( CQL_PRIVILEGEFIELDDICT_COLUMN_NAME_LENGTH ),
	  userNull_( false )
{
	try
	{
		table_->open( dictionaryName_ );
	}
	catch( AbstractTableException& )
	{
		dbsql_.resetError();

		//  open failed, try to create

		CqlColumnTypes *columnDescriptors[ 5 ];
		//  table name
		columnDescriptors[ 0 ] = new CqlColumnTypes( "tableName", CQL_PRIVILEGEFIELDDICT_TABLE_NAME_TYPE, CQL_PRIVILEGEFIELDDICT_TABLE_NAME_LENGTH );
		//  authorization
		columnDescriptors[ 1 ] = new CqlColumnTypes( "owner", CQL_PRIVILEGEFIELDDICT_AUTHORIZATION_TYPE, CQL_PRIVILEGEFIELDDICT_AUTHORIZATION_LENGTH );
		//  user name
		columnDescriptors[ 2 ] = new CqlColumnTypes( "user", CQL_PRIVILEGEFIELDDICT_USER_TYPE, CQL_PRIVILEGEFIELDDICT_USER_LENGTH );
		//  column name
		columnDescriptors[ 3 ] = new CqlColumnTypes( "columnName", CQL_PRIVILEGEFIELDDICT_COLUMN_NAME_TYPE, CQL_PRIVILEGEFIELDDICT_COLUMN_NAME_LENGTH );
		//  no more columns
		columnDescriptors[ 4 ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );

		AccessorTypes *keyDescriptors[ 2 ];
		SegmentTypes *segs[ 4 ];
		keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, segs ),
		segs[ 0 ] = new SegmentTypes( "tableName", 0, SegmentTypes::CQL_ASCENDING );
		segs[ 1 ] = new SegmentTypes( "owner", 1, SegmentTypes::CQL_ASCENDING );
		segs[ 2 ] = new SegmentTypes( "user", 2, SegmentTypes::CQL_ASCENDING );
		segs[ 3 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
		keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

		table_->create( CQL_CQL, dictionaryName_, columnDescriptors, keyDescriptors );

		delete columnDescriptors[ 0 ];
		delete columnDescriptors[ 1 ];
		delete columnDescriptors[ 2 ];
		delete columnDescriptors[ 3 ];
		delete columnDescriptors[ 4 ];
		delete keyDescriptors[ 0 ];
		delete segs[ 0 ];
		delete segs[ 1 ];
		delete segs[ 2 ];
		delete segs[ 3 ];
		delete keyDescriptors[ 1 ];
	}

	try
	{
		SystemDictionary::bind( CID_TABLE_NAME, CID_AUTHORIZATION );

		table_->bindColumn( CID_USER, user_, userNull_, true );
		user_ = dbsql_.aHandle().userName();
		table_->bindColumn( CID_COLUMN_NAME, columnName_, columnNameNull_, true );
	}

	catch( CqlException& )
	{
		throw DictionaryException( __FILE__, __LINE__ );
	}
}


PrivilegeFieldDictionary::~PrivilegeFieldDictionary( void )
{
}


bool PrivilegeFieldDictionary::privilege( CqlString& _tableName, CqlString& _auth, CqlString& _columnName )
{
	if( dbsql_.aHandle().userName() == _auth )
	{
		findStatus_ = CQL_YES;
		priv_ = true;
		return true;
	}

	if( findStatus_ && tableName_ == _tableName && auth_ == _auth )
		return priv_;

	tableName_ = _tableName;
	auth_ = _auth;
	//  user_ set in constructor
	columnName_ = _columnName;

	table_->beginIsamOperation( 0 );
	findStatus_ = true;
	if( !table_->findFirst( false ) )
	{
		priv_ = false;
		return false;
	}

	priv_ = true;
	return true;
}


void PrivilegeFieldDictionary::add( PrivilegeFieldDictionaryRecord& priv )
{
	tableName_ = priv.tableName();
	auth_ = priv.auth();
	user_ = priv.user();
	columnName_ = priv.columnName();

	table_->addRow();
}


//  this method takes PrivilegeDictionaryRecord instead of
//  PrivilegeFieldDictionaryRecord.  All privileges for the
//  user are being deleted, so column names are unnecessary.
void PrivilegeFieldDictionary::deletePrivs( PrivilegeDictionaryRecord& priv )
{
	for( ; ; )
	{
		tableName_ = priv.tableName();
		auth_ = priv.auth();
		user_ = priv.user();

		if( !table_->findFirst( false ) )
			return;
		table_->deleteRow();
	}
}


PrivilegeFieldDictionaryRecord::PrivilegeFieldDictionaryRecord( void ) : PrivilegeDictionaryRecord(), columnName_()
{
}


PrivilegeFieldDictionaryRecord::~PrivilegeFieldDictionaryRecord( void )
{
}


void PrivilegeFieldDictionaryRecord::setup( const CqlString& prefix, const CqlString& tName, const CqlString& userName, const CqlString& _columnName )
{
	columnName_ = _columnName;
	user() = prefix;
	tableName() = tName;
	user() = userName;
}


RefersDictionary::RefersDictionary( SqlHandle& sqlh )
	: SystemDictionary( sqlh, CQL_REFERENCEDICT_NAME ),
	  columnNumbers_(),
	  fkAuth_( CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH ),
	  fkAuthNull_( false ),
	  fkTableName_( CQL_MAXIMUM_TABLE_NAME_LENGTH ),
	  fkTableNameNull_( false ),
	  fkKeyNumber_( 0 ),
	  fkKeyNumberNull_( false ),
	  fkColumnNumbers_(),
	  fkColumnNumbersNull_( false )
{
	try
	{
		table_->open( dictionaryName_ );
	}
	catch( AbstractTableException& )
	{
		dbsql().resetError();

		//*******************************************************************
		//**  Open failed, try to create.                                  **
		//*******************************************************************

		CqlColumnTypes *columnDescriptors[ 8 ];
		columnDescriptors[ 0 ] = new CqlColumnTypes( "tableName", CQL_REFERENCEDICT_TABLE_NAME_TYPE, CQL_REFERENCEDICT_TABLE_NAME_LENGTH );
		columnDescriptors[ 1 ] = new CqlColumnTypes( "owner", CQL_REFERENCEDICT_AUTH_TYPE, CQL_REFERENCEDICT_AUTH_LENGTH );
		columnDescriptors[ 2 ] = new CqlColumnTypes( "fkTableName", CQL_REFERENCEDICT_FK_TABLE_NAME_TYPE, CQL_REFERENCEDICT_FK_TABLE_NAME_LENGTH );
		columnDescriptors[ 3 ] = new CqlColumnTypes( "tkOwner", CQL_REFERENCEDICT_FK_AUTH_TYPE, CQL_REFERENCEDICT_FK_AUTH_LENGTH );
		columnDescriptors[ 4 ] = new CqlColumnTypes( "fkKeyNumber", CQL_REFERENCEDICT_FK_KEY_NUMBER_TYPE );
		columnDescriptors[ 5 ] = new CqlColumnTypes( "referencedColumns", CQL_REFERENCEDICT_COLUMN_NUMBERS_TYPE, 0 );
		columnDescriptors[ 6 ] = new CqlColumnTypes( "referencedFkColumns", CQL_REFERENCEDICT_FK_COLUMN_NUMBERS_TYPE, 0 );
		columnDescriptors[ 7 ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );

		AccessorTypes *keyDescriptors[ 2 ];
		SegmentTypes *segs[ 3 ];
		keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, segs ),
		segs[ 0 ] = new SegmentTypes( "tableName", 0, CQL_ASCENDING );
		segs[ 1 ] = new SegmentTypes( "owner", 1, CQL_ASCENDING );
		segs[ 2 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
		keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

		table_->create( CQL_CQL, dictionaryName_, columnDescriptors, keyDescriptors );

		delete columnDescriptors[ 0 ];
		delete columnDescriptors[ 1 ];
		delete columnDescriptors[ 2 ];
		delete columnDescriptors[ 3 ];
		delete columnDescriptors[ 4 ];
		delete columnDescriptors[ 5 ];
		delete columnDescriptors[ 6 ];
		delete columnDescriptors[ 7 ];
		delete keyDescriptors[ 0 ];
		delete segs[ 0 ];
		delete segs[ 1 ];
		delete segs[ 2 ];
		delete keyDescriptors[ 1 ];
	}
	catch( ... )
	{
		throw;
	}

	try
	{
		SystemDictionary::bind( CID_TABLE_NAME, CID_AUTH );
		table_->bindColumn( CID_FK_TABLE_NAME, fkTableName_, fkTableNameNull_, true );
		table_->bindColumn( CID_FK_AUTH, fkAuth_, fkAuthNull_, true );
		table_->bindColumn( CID_FK_KEY_NUMBER, fkKeyNumber_, fkKeyNumberNull_, true );
		table_->bindColumn( CID_COLUMN_NUMBERS, columnNumbers_, columnNumbersNull_, true );
		table_->bindColumn( CID_FK_COLUMN_NUMBERS, fkColumnNumbers_, fkColumnNumbersNull_, true );
	}

	catch( CqlException& )
	{
		throw DictionaryException( __FILE__, __LINE__ );
	}
}


RefersDictionary::~RefersDictionary( void )
{
}


SystemDictionary::SystemDictionary( SqlHandle& sqlh, const CqlString& name )
	: auth_( CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH ),
	  authNull_( 0 ),
	  dbsql_( sqlh ),
	  dictionaryName_( "" ),
	  findStatus_( 0 ),
	  table_( 0 ),
	  tableName_( CQL_MAXIMUM_TABLE_NAME_LENGTH ),
	  tableNameNull_( 0 )
{
	if( sqlh.initialDirectory()->length() )
	{
		dictionaryName_ = *sqlh.initialDirectory();
		dictionaryName_ += "/";
	}
	dictionaryName_ += name;

	table_ = AbstractTable::createObject( sqlh.aHandle(), CQL_CQL );
}


SystemDictionary::~SystemDictionary( void )
{
	if( table_ )
	{
		delete table_;
		table_ = 0;
	}
}


void SystemDictionary::bind( US tableNameColumnNumber, US authorizationColumnNumber )
{
	try
	{
		table_->bindColumn( tableNameColumnNumber, tableName_, tableNameNull_, true );
		table_->bindColumn( authorizationColumnNumber, auth_, authNull_, true );
	}
	catch( CqlException& )
	{
		throw DictionaryException( __FILE__, __LINE__ );
	}
}
