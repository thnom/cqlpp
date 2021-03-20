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


SqlHandle::SqlHandle( CqlString *aUser, CqlString *aPassword, CqlString *aInitialDirectory, CqlString *aScript, CqlString *aOutputFile )
	: activeTables_(),
	  
	  currentCursor_( 0 ),
	  currentStatement_( 0 ),
	  cursors_(),
	  indexDict_( 0 ),
	  initialDirectory_(aInitialDirectory),
	  mainDict_( 0 ),
	  outputFile_(aOutputFile),
	  parse_( 0 ),
	  password_(aPassword),
	  privilegeDict_( 0 ),
	  privilegeFieldDict_( 0 ),
	  readOnly_( false ),
	  refers_( 0 ),
	  relaxedLocking_( false ),
	  script_(aScript),
	  strictLocking_( true ),
	  systemTableColumns_( 0 ),
	  systemTableIndices_( 0 ),
	  systemTableTables_( 0 ),
	  temporaryNameCount_( 0 ),
	  updateCount_( 0 ),
	  user_(aUser),
	  workingSets_()
{
	if( !dbSqlEnv )
	{
		dbSqlEnv = new SqlEnvironmentHandle( *initialDirectory_ );
		if( !dbSqlEnv )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	if( !initialDirectory_ )
		initialDirectory_ = new CqlString( dbSqlEnv->optionCurrentDirectory() );

	aHandle_ = AbstractDatabaseHandle::createObject( *user_, *password_, *initialDirectory_ );

	//  constructors may create dictionaries/system tables
	beginTransaction();

	try
	{
		mainDict_ = new MainDictionary( *this );
		indexDict_ = new IndexDictionary( *this );
		privilegeDict_ = new PrivilegeDictionary( *this );
		privilegeFieldDict_ = new PrivilegeFieldDictionary( *this );
		refers_ = new RefersDictionary( *this );
		systemTableTables_ = new SystemTableTables( *this );
		systemTableColumns_ = new SystemTableColumns( *this );
		systemTableIndices_ = new SystemTableIndices( *this );
	}
	catch( ... )
	{
		//*******************  better catch here?
		throw;
	}

	parse_ = new Parser( *this );
	if( !parse_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	//  In case anything was created...
	commitTransaction();
}


SqlHandle::~SqlHandle( void )
{
	if( parse_ )
	{
		delete parse_;
		parse_ = ((pParser)0);
	}

	if( aHandle_ )
	{
		delete aHandle_;
		aHandle_ = 0;
	}

	if( initialDirectory_ )
	{
		delete initialDirectory_;
		initialDirectory_ = 0;
	}

	if( outputFile_ )
	{
		delete outputFile_;
		outputFile_ = 0;
	}

	if( password_ )
	{
		delete password_;
		password_ = 0;
	}

	if( script_ )
	{
		delete script_;
		script_ = 0;
	}

	if( user_ )
	{
		delete user_;
		user_ = 0;
	}
}


SqlHandle& SqlHandle::operator = ( const SqlHandle& other )
{
	activeTables_ = const_cast< SqlHandle& >( other ).activeTables_;
	aHandle_ = other.aHandle_;
	currentCursor_ = other.currentCursor_;
	currentStatement_ = other.currentStatement_;
	cursors_ = other.cursors_;
	indexDict_ = other.indexDict_;
	mainDict_ = other.mainDict_;
	parse_ = other.parse_;
	privilegeDict_ = other.privilegeDict_;
	privilegeFieldDict_ = other.privilegeFieldDict_;
	refers_ = other.refers_;
	systemTableColumns_ = other.systemTableColumns_;
	systemTableIndices_ = other.systemTableIndices_;
	systemTableTables_ = other.systemTableTables_;
	temporaryNameCount_ = other.temporaryNameCount_;
	updateCount_ = other.updateCount_;
	workingSets_ = other.workingSets_;
	readOnly_ = other.readOnly_;
	relaxedLocking_ = other.relaxedLocking_;
	strictLocking_ = other.strictLocking_;

	return *this;
}


void SqlHandle::updateDictionaryInformation( pTableSpecification newTable, pTableSpecification oldTable )
{
	deleteDictionaryEntry( oldTable );
	addDictionaryEntry( *newTable );
}


void SqlHandle::addDictionaryEntry( TableSpecification& table )
{
	pTempBuffer buffer;
	pSegmentedKeyGroup skg;

	buffer = new TempBuffer( *aHandle_ );
	if( !buffer )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	table.computeDictionaryRecordLength();
	table.writeDictionaryInformation( *buffer );

	mainDict_->add(
		table.dictionaryRecordLength(),
		table.tableName(),
		table.authorizationId(),
		CQL_NO,
		*buffer );

	for( skg = table.uniqueKeyGroups().first(); skg; skg = table.uniqueKeyGroups().next() )
		addIndexDictionaryRecord( skg->IndexName(), table.tableName(), table.authorizationId() );

	for( skg = table.duplicateKeyGroups().first(); skg; skg = table.duplicateKeyGroups().next() )
		addIndexDictionaryRecord( skg->IndexName(), table.tableName(), table.authorizationId() );
}


void SqlHandle::addDictionaryEntry( CqlString& name, CqlString& prefix, pTempBuffer buffer )
{
	US recordLength = static_cast< US >( ( CQL_MAXIMUM_FILE_NAME_LENGTH * 2 ) + (buffer->size() ) );
	mainDict_->add( recordLength, name, prefix, true, *buffer );
}


void SqlHandle::deleteMainDictionaryEntry( pAbstractTableSpecification table )
{
	mainDict_->ddelete( table->tableName(), table->authorizationId() );
}


void SqlHandle::deleteDictionaryEntry( pTableSpecification table )
{
	pSegmentedKeyGroup skg;

	deleteMainDictionaryEntry( table );
	//
	//  Delete the key group entries from the index dictionary
	//
	for( skg = table->uniqueKeyGroups().first(); skg; skg = table->uniqueKeyGroups().next() )
		deleteIndexDictionaryRecord( skg->IndexName() );

	for( skg = table->duplicateKeyGroups().first(); skg; skg = table->duplicateKeyGroups().next() )
		deleteIndexDictionaryRecord( skg->IndexName() );
}


bool SqlHandle::checkForSelectPrivilege( SelectExpression *select )
{
	pTableTableElement ttEl;
	pAbstractTableSpecification absTableSpec;

	for( ttEl = select->tables().first(); ttEl; ttEl = select->tables().next() )
	{
		absTableSpec = ttEl->absTableSpec();

		bool grantOption;
		if( !privilegeDict_->selectPrivilege( absTableSpec->tableName(), absTableSpec->authorizationId(), grantOption ) )
			return false;
	}

	return true;
}


bool SqlHandle::checkForDeletePrivilege( pTableTableElement ttEl )
{
	pAbstractTableSpecification absTableSpec = ttEl->absTableSpec();

	bool grantOption;
	return privilegeDict_->deletePrivilege( absTableSpec->tableName(), absTableSpec->authorizationId(), grantOption );
}


bool SqlHandle::checkForUpdatePrivilege( pTableTableElement ttEl, ColumnTable& cols )
{
	pAbstractTableSpecification absTableSpec = ttEl->absTableSpec();
	pColumn col;
	pExpressionColumnListElement expColListEl;

	bool grantOption;
	if( !privilegeDict_->deletePrivilege( absTableSpec->tableName(), absTableSpec->authorizationId(), grantOption ) )
		return false;

	//
	//  O.K., we have update privilege on the table, but what about the columns?
	//
	for( col = cols.first(); col; col = cols.next() )
	{
		expColListEl = col->ColumnExpression().columns().first();

		if( privilegeFieldDict_->privilege(
			absTableSpec->tableName(),
			absTableSpec->authorizationId(),
			expColListEl->Column()->columnName() ) == CQL_NO )
			return false;
	}

	return true;
}


bool SqlHandle::checkForInsertPrivilege( pAbstractTableSpecification absTableSpec )
{
	bool grantOption;
	return privilegeDict_->insertPrivilege( absTableSpec->tableName(), absTableSpec->authorizationId(), grantOption );
}


bool SqlHandle::checkForInsertPrivilege( bool& grantOpt, CqlString& tableName, CqlString& authId )
{
	return privilegeDict_->insertPrivilege( tableName, authId, grantOpt );
}


bool SqlHandle::checkForDeletePrivilege( bool& grantOpt, CqlString& tableName, CqlString& authId )
{
	return privilegeDict_->deletePrivilege( tableName, authId, grantOpt );
}


bool SqlHandle::checkForSelectPrivilege( bool& grantOpt, CqlString& tableName, CqlString& authId )
{
	return privilegeDict_->selectPrivilege( tableName, authId, grantOpt );
}

bool SqlHandle::checkForUpdatePrivilege( bool& grantOpt, CqlString& tableName, CqlString& authId, GrantColumnList& grantCols )
{
	pGrantColumn gc;

	if( !privilegeDict_->updatePrivilege( tableName, authId, grantOpt ) )
		return false;

	for( gc = grantCols.first(); gc; gc = grantCols.next() )
		if( !privilegeFieldDict_->privilege( tableName, authId, gc->ColumnName() ) )
			return false;

	return true;
}


AbstractTableSpecification *SqlHandle::getDictionaryRecord( const CqlString& tableName, const CqlString& prefix )
{
	AbstractTableSpecification *table;
	pTablenameIndexNode tablenameNode;
	NI rc;
	bool aliasFlag = false;

	hAEnv->logPrintf(AbstractLogger::TRACEALL, "getDictionaryRecord, name=%s, ", tableName.text() );
	if( prefix.length() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "prefix=%s\n", prefix.text() );
	else
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "no prefix\n" );

	if( !prefix )
		rc = activeTables_.FindEqualKey( this, tableName, aHandle_->userName() );
	else
		rc = activeTables_.FindEqualKey( this, tableName, prefix );

	if( rc == CQL_SUCCESS )
	{
		tablenameNode = activeTables_.CurrentNode();
		if( tablenameNode->InUse() == CQL_NO )
		{
			hAEnv->logPrintf(AbstractLogger::TRACEALL, "found, setting in use\n" );
			tablenameNode->SetInUse();
			table = tablenameNode->At();
			table->clearAliasFlag();
			return table;
		}
		else
		{
			hAEnv->logPrintf(AbstractLogger::TRACEALL, "found, setting alias flag\n" );
			aliasFlag = true;
		}
	}

	CqlString auth;

	if( !prefix )
		auth = aHandle_->userName();
	else
		auth = prefix;

	return mainDict_->find( tableName, auth );
}


void SqlHandle::addOrUpdatePrivilegeRecord( PrivilegeDictionaryRecord& priv )
{
	privilegeDict_->addOrUpdate( priv );
}


void SqlHandle::addPrivilegeFieldRecord( PrivilegeFieldDictionaryRecord& priv )
{
	privilegeFieldDict_->add( priv );
}


void SqlHandle::deletePrivilegeRecords( PrivilegeDictionaryRecord& priv )
{
	beginTransaction();
	privilegeDict_->deletePrivs( priv );
	privilegeFieldDict_->deletePrivs( priv );
	commitTransaction( false );
}


void SqlHandle::addIndexDictionaryRecord( CqlString& indexName, CqlString& tableName, CqlString& auth )
{
	indexDict_->add( indexName, tableName, auth );
}


void SqlHandle::deleteIndexDictionaryRecord( CqlString& indexName )
{
	indexDict_->ddelete( indexName );
}


void SqlHandle::findTableForIndex( CqlString& indexName, CqlString& tableName, CqlString& auth )
{
	indexDict_->find( indexName, tableName, auth );
}


void SqlHandle::allocateWorkingSet( void )
{
	pSelectExpression select;

	select = new SelectExpression( *this );
	if( !select )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	workingSets_.add( select );
}


void SqlHandle::clearStatementEnded( void )
{
	parse_->clearStatementEnded();
}


void SqlHandle::connect()
{
	resetError();
	parse_->clearStatementEnded();

	aHandle_->userName().setStringUpper( *user_ );

//***********************  Need connect here
#if 0
	if( dbSqlEnv_->TransactionStartup( aHandle->AErrorMan(), CQL_LOG_NAME ) == CQL_FAILURE )
		return CQL_FAILURE;
#endif

	allocateWorkingSet();
}


void SqlHandle::disconnect( void )
{
	resetError();
	parse_->clearStatementEnded();
	rollbackTransaction( false );
	workingSets_.destroy();
	activeTables_.destroyIndex();
	delete systemTableIndices_;
	delete systemTableColumns_;
	delete systemTableTables_;
	delete refers_;
	delete privilegeFieldDict_;
	delete privilegeDict_;
	delete indexDict_;
	delete mainDict_;

	while( parse_->popAnInputFile() )
		;

	aHandle_->disconnect();
}


void SqlHandle::setLockingStrict( void )
{
	resetError();
	parse_->clearStatementEnded();
	relaxedLocking_ = false;
	strictLocking_ = true;
}


void SqlHandle::setLockingRelaxed( void )
{
	resetError();
	parse_->clearStatementEnded();
	relaxedLocking_ = true;
	strictLocking_ = false;
}


void SqlHandle::disableLocking( void )
{
	resetError();
	parse_->clearStatementEnded();
	relaxedLocking_ = strictLocking_ = false;
	readOnly_ = true;
}


NC SqlHandle::escapeCharacter( void )
{
	return parse_->escapeCharacter();
}	


bool SqlHandle::escapeFlag( void )
{
	return parse_->escape();
}


void SqlHandle::error( ErrorConstants::ErrorCodes& err, NC *filename, NI& linenumber, NI& oserror )
{
	err = errorCode();
	if( filename )
		strcpy( filename, errorFile().text() );
	linenumber = errorLine();
	oserror = osError();
}


void SqlHandle::consumeUntilSelect( CqlString& s, pNC statement )
{
	s = statement;
}


Cursor *SqlHandle::declareCursor( const char * const statement )
{
	Cursor *localCursor = new Cursor( *this );
	if( !localCursor )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	resetError();
	parse_->clearStatementEnded();
	parse_->embeddedStatement() = statement;
	parse_->allocateCursorExpression();
	parse_->setEmbeddedInput();
	parse_->setDeclaringCursor();
	currentCursor_ = localCursor;
	cursors_.add( localCursor );

	//  yyparse returns 0 for O.K. in the C tradition.
	//  Non-zero means syntax error.  Catch and re-throw any other exception
	try
	{
		if( yyparse( this ) )
			throw SyntaxErrorException( __FILE__, __LINE__ );
	}
	catch( ... )
	{
		throw;
	}
	
	return localCursor;
}


void SqlHandle::prepare( StatementHandle *statem, NC *statement )
{
	SelectExpressionList& sets = workingSets();

	resetError();
	parse_->clearStatementEnded();

	parse_->embeddedStatement() = statement;
	parse_->setEmbeddedInput();
	parse_->setPreparing();
	currentStatement_ = statem;
	if( yyparse( this ) )
		throw SyntaxErrorException( __FILE__, __LINE__ );

	sets.move( statem->sets() );

	switch( statem->type() )
	{
	case INSERT_VALUES :
	case INSERT_SELECT :
		parse_->insertColumnNames().move( statem->insertColumnNames() );
		break;

	case UPDATE_SEARCHED :
	case UPDATE_POSITIONED :
		parse_->updateColumns().move( statem->updateColumns() );
		break;

	case GRANT_STATEMENT :
	case REVOKE_STATEMENT :
		parse_->grantPrivileges().move( statem->grantPrivileges() );
		parse_->grantUsers().move( statem->grantUsers() );
		break;

	default :
		break;
	}

	allocateWorkingSet();
	parse_->cleanup();
}


StatementHandle *SqlHandle::prepare( NC *statement )
{
	StatementHandle *statem = new StatementHandle( *this );
	if( !statem )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	prepare( statem, statement );
	return statem;
}


void SqlHandle::execute( void )
{
	currentStatement_->execute();
}


void SqlHandle::close( Cursor *cur )
{
	resetError();
	parse_->clearStatementEnded();
	cur->close();
	cur->cursorName().reset();
	cur->dynamicParameters().destroy();

	cur->cleanup();

	pSelectExpression select;
	for( select = cur->sets().first(); select; select = cur->sets().next() )
		select->cleanup();
	cur->sets().destroy();

	cursors_.remove( cur );
	delete cur;
}


void SqlHandle::executeImmediate( const char * const statement )
{
	resetError();
	parse_->clearStatementEnded();
	parse_->embeddedStatement() = statement;
	parse_->setEmbeddedInput();
	if( yyparse( this ) )
		throw SyntaxErrorException( __FILE__, __LINE__ );
}


void SqlHandle::commitTransaction( bool followWithBegin )
{
	resetError();
	parse_->clearStatementEnded();
	aHandle_->commitTransaction();
	if( followWithBegin )
		aHandle_->beginTransaction();
}


void SqlHandle::rollbackTransaction( bool followWithBegin )
{
	resetError();
	parse_->clearStatementEnded();
	aHandle_->rollbackTransaction();
	if( followWithBegin == CQL_YES )
		aHandle_->beginTransaction();
}


NC *SqlHandle::temporaryName( void )
{
	static NC nameBuf[ 100 ];

	sprintf( nameBuf, "TEMP%d", temporaryNameCount_++ );
	return nameBuf;
}
