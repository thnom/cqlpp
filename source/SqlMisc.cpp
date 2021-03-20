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


bool CAdvance( void* sel )
{
	pSelectExpression select = ((pSelectExpression)sel);
	return select->advance();
}


extern FILE *yyin;

NI yyerror( SqlHandle *dbsql, const char * const msg )
{
	fflush( stdout );
	fprintf( stderr, "error, %s\n", msg );
	fflush( stderr );
	fflush( yyin );
	dbsql->parse()->yywrap();
	return 1;
}


NI cqlYyInput( SqlHandle *dbsql, NC *buf, NI size )
{
	NI ch;

	if( dbsql->parse()->shuttingDown() == CQL_YES )
		return 0;

	if( dbsql->parse()->statementEnded() == CQL_YES )
		dbsql->parse()->clearStatementEnded();

	buf[1] = 0;

	if( dbsql->parse()->embeddedInput() == CQL_YES )
		ch = dbsql->parse()->embeddedGetCharacter();
	else
		ch = getc( yyin );

	buf[0] = ((NC)ch);

	switch( ch )
	{
	case EOF :
		fclose( yyin );
		if( !dbsql->parse()->popAnInputFile() )
			return 0;
		return cqlYyInput( dbsql, buf, size );

	default :
		break;
	}

	if( dbsql->parse()->batchMode() && dbsql->parse()->echo() )
		putchar( ((NC)ch) );

	return 1;
}


GrantPrivilege::GrantPrivilege( void )
	: GrantPrivilegeListElement(),
	  deletePriv_( CQL_NO ),
	  insertPriv_( CQL_NO ),
	  referencesPriv_( CQL_NO ),
	  selectPriv_( CQL_NO ),
	  updatePriv_( CQL_NO )
{
}


GrantPrivilege::~GrantPrivilege( void )
{
}


void GrantPrivilege::reset( void )
{
	deletePriv_ = insertPriv_ = referencesPriv_ = selectPriv_ = updatePriv_ = CQL_NO;
}


GrantPrivilege& GrantPrivilege::operator = ( const GrantPrivilege& other )
{
	deletePriv_ = other.deletePriv_;
	insertPriv_ = other.insertPriv_;
	referencesPriv_ = other.referencesPriv_;
	selectPriv_ = other.selectPriv_;
	updatePriv_ = other.updatePriv_;
	return *this;
}


GrantUser::GrantUser( void ) : GrantUserListElement(), userName()
{
}


GrantUser::~GrantUser( void )
{
}


IndexNameListGroup::IndexNameListGroup( void )
	: IndexNameListGroupListElement(),
	  icnl(),
	  duplicateKey( CQL_NO ),
	  primaryKey( CQL_NO ),
	  uniqueKey( CQL_NO )
{
}


IndexNameListGroup::~IndexNameListGroup( void )
{
}


void QueryExpression::cleanup( void )
{
	instructions_.destroy();
	stack_.destroy();
	if( resultSet_ )
	{
		resultSet_->close();
		delete resultSet_;
		resultSet_ = 0;
	}
}


QueryExpression::QueryExpression( void ) : instructions_(), stack_(), resultSet_( 0 )
{
}


QueryExpression::~QueryExpression( void )
{
}


ResultSet::ResultSet( void ) : SetRowList(), numberOfRows( 0 )
{
}


ResultSet::~ResultSet( void )
{
}


RowId::RowId( RECID r ) : RowIdListElement(), rid( r )
{
}


RowId::~RowId( void )
{
}


SelectExpressionCollectionObject::SelectExpressionCollectionObject( void ) : SelectExpressionCollectionObjectListElement(), sets()
{
}


SelectExpressionCollectionObject::~SelectExpressionCollectionObject( void )
{
}


SelectExpressionList::SelectExpressionList( void ) : SelectExpressionListBase()
{
}


UNI SelectExpressionList::DictionaryLength( void )
{
	pSelectExpression select;
	UNI _size;

	//
	//  scalar values:
	//    UNI numberOfListElements
	//
	_size = sizeof( UNI );

	for( select = first(); select; select = next() )
		_size += select->dictionaryLength();

	return _size;
}


void SelectExpressionList::writeDictionaryInformation( TempBuffer& buffer )
{
	pSelectExpression select;

	buffer << size();

	for( select = first(); select; select = next() )
		select->writeDictionaryInformation( buffer );
}


void SelectExpressionList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfSelectExpressions, loop;
	pSelectExpression select;

	buffer >> numberOfSelectExpressions;

	for( loop = 0; loop < numberOfSelectExpressions; loop++ )
	{
		select = new SelectExpression( *buffer.dbsql() );
		if( !select )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		select->readDictionaryInformation( buffer );
		add( select );
	}
}


SetRow::SetRow( void ) : SetRowListElement()
{
}


SetRow::~SetRow( void )
{
}


NI SetRow::Assign( SqlHandle*, SetRow& other )
{
	length = other.length;
	allocationLength = other.allocationLength;

	if( allocationLength )
	{
		data = new UC[ allocationLength ];
		if( !data )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		memset( data, 0, allocationLength );
		memcpy( data, other.data, length );
	}
	else
		data = ((pUC)0);

	ids = other.ids;
	return CQL_SUCCESS;
}


SqlEnvironmentHandle::SqlEnvironmentHandle( char *initialDirectory )
		: currentAnonymousCursorNumber_( 0 ),
			initFailed( CQL_NO ),
			interactiveMode( CQL_NO )
{
	aHandle_ = AbstractEnvironmentHandle::createObject( initialDirectory );
	hAEnv = aHandle_;
}


SqlEnvironmentHandle::~SqlEnvironmentHandle( void )
{
}

CqlString *SqlEnvironmentHandle::anonymousCursorName( void )
{
		NC cname[128];
		sprintf( cname, "cursor%3d", currentAnonymousCursorNumber_++ );
		return new CqlString( cname );
}

SubqueryResultSet::SubqueryResultSet( SqlHandle& sqlh ) : TemporaryResultFile( sqlh ), dbsql_( sqlh ), resultBuffer_( 0 )
{
}


SubqueryResultSet::~SubqueryResultSet( void )
{
	if( resultBuffer_ )
	{
		delete resultBuffer_;
		resultBuffer_ = 0;
	}
}


TemporaryResultFile::TemporaryResultFile( SqlHandle& sqlh )
	: boundColumns_(),
	  dbsql_( sqlh ),
	  ifile_( 0 ),
	  refetchInfo_( 0 ),
	  refetchInfoColumnNumber_( 0 ),
	  refetchInfoLength_( 0 ),
	  refetchInfoNull_( 0 )
{
}


TemporaryResultFile::~TemporaryResultFile( void )
{
}


TemporaryResultFile& TemporaryResultFile::operator = ( const TemporaryResultFile& other )
{
	if( other.ifile_ )
	{
		ifile_ = AbstractTable::createObject( dbsql_.aHandle(), CQL_CQL );
		*ifile_ = *other.ifile_;
	}
	else
		ifile_ = 0;

	refetchInfoColumnNumber_ = other.refetchInfoColumnNumber_;
	refetchInfoLength_ = other.refetchInfoLength_;
	return *this;
}


void TemporaryResultFile::setBaseTablePositions( UC *p )
{
	memcpy( refetchInfo_, p, refetchInfoLength_ );
	ifile_->bindColumn( refetchInfoColumnNumber_, refetchInfo_, refetchInfoLength_, refetchInfoNull_, true, false );
}


void TemporaryResultFile::bindBaseTablePositions( void )
{
	ifile_->bindColumn( refetchInfoColumnNumber_, refetchInfo_, refetchInfoLength_, refetchInfoNull_, true, false );
}


void TemporaryResultFile::getBaseTablePositions( UC *dest )
{
	memcpy( dest, refetchInfo_, refetchInfoLength_ );
}


void TemporaryResultFile::cleanup( void )
{
	if( ifile_ )
	{
		ifile_->close();
		delete ifile_;
		ifile_ = 0;
	}

	if( refetchInfo_ )
	{
		delete [] refetchInfo_;
		refetchInfo_ = 0;
	}
}


void TemporaryResultFile::releaseResources( void )
{
	ifile_->releaseResources();
}


void TemporaryResultFile::refetchInfoAlloc( US len )
{
	refetchInfoLength_ = len;
	refetchInfo_ = new UC[ refetchInfoLength_ ];
	if( !refetchInfo_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memset( refetchInfo_, 0, refetchInfoLength_ );
}


ValueExpressionStack::ValueExpressionStack( void ) : ValueExpressionStackElementList()
{
}


ValueExpressionStack::~ValueExpressionStack( void )
{
}


void ValueExpressionStack::pushValue( AbstractValueElement *v )
{
	ValueExpressionStackElement *vel;

	vel = new ValueExpressionStackElement;
	if( !vel )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	vel->value( v );
	ValueExpressionStackElementList::push( vel );
}


AbstractValueElement *ValueExpressionStack::popValue( void )
{
	pValueExpressionStackElement vel;

	vel = ValueExpressionStackElementList::pop();
	if( !vel )
		throw StackUnderflowException( __FILE__, __LINE__ );

	AbstractValueElement *v = vel->value();
	delete vel;
	return v;
}


ValueExpressionStack& ValueExpressionStack::operator = ( const ValueExpressionStack& cother )
{
	ValueExpressionStack& other = const_cast< ValueExpressionStack& >( cother );
	pValueExpressionStackElement vesEl, newVesEl;

	for( vesEl = other.first(); vesEl; vesEl = other.next() )
	{
		newVesEl = new ValueExpressionStackElement;
		if( !newVesEl )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*newVesEl = *vesEl;
		add( newVesEl );
	}
	return *this;
}


ValueExpressionStackElement *ValueExpressionStack::topOfStack( void )
{
	return ValueExpressionStackElementList::last();
}


VariableSpecification::VariableSpecification( void )
	: data( ((void*)0) ),
	  indicator( CQL_NO ),
	  length( 0 ),
	  pattern(),
	  type( HOST_TYPE_UNKNOWN )
{
}


VariableSpecification::~VariableSpecification( void )
{
}


void VariableSpecification::setup( void* d, HostType t, UNI len, pNC pat )
{
	data = d;
	type = t;
	length = len;
	if( pat )
		pattern = pat;
}


