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


#include "CqlCommonInclude.h"


ConditionPredicate::ConditionPredicate( BoundColumn *_bc, ConditionalOperators _op ) : ConditionPredicateListElement(), access_( 0 ), bc_( _bc ), op_( _op ), realPredicate_( 0 ), resolved_( false )
{
}


ConditionPredicate::ConditionPredicate( ConditionPredicate& other ) : ConditionPredicateListElement( other ), access_( other.access_ ), op_( other.op_ ), realPredicate_( &other ), resolved_( false )
{
	bc_ = BoundColumn::createObject( *other.bc_, false );
	if( !bc_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
}


ConditionPredicate::~ConditionPredicate( void )
{
	if( bc_ )
	{
		delete bc_;
		bc_ = 0;
	}
}


Condition::Condition( void ) :	access_( 0 ), predicates_(), findEndOfFile_( false )
{
}


Condition::~Condition( void )
{
	destroy();
}


void Condition::destroy( void )
{
	predicates_.destroy();
}


void Condition::access( AccessCondition *ac )
{
	access_ = ac;
	ConditionPredicate *cpred;
	for( cpred = access_->predicates().first(); cpred; cpred = access_->predicates().next() )
		cpred->setResolved();
}


AccessCondition::AccessCondition( void )
	:	access_( 0 ),
		cost_( 0 ),
		op_( CQL_COP_UNDEFINED ),
		predicates_(),
		trailingPredicateCandidates_()
{
}


AccessCondition::~AccessCondition( void )
{
	predicates_.destroy();
	trailingPredicateCandidates_.destroy();
}


Connection::Connection( void ) : ClibConnection(), connected_( false )
{
}


Connection::~Connection( void )
{
}


Connection& Connection::operator = ( Connection& other )
{
	connected_ = other.connected_;
	return *this;
}


NI Connection::acceptConnection( AbstractDatabaseHandle& )
{
	try
	{
		ClibConnection::acceptConnection( hAEnv->connectionMan().socketDescriptor(), hAEnv->connectionMan().socketAddress() );
	}
	catch( CqlException& ex )
	{
		connected_ = CQL_NO;
		throw ex;
	}

	connected_ = CQL_YES;
	return CQL_SUCCESS;
}


NI Connection::initiateConnection( AbstractDatabaseHandle& )
{
	try
	{
		ClibConnection::initiateConnection( hAEnv->connectionMan().socketDescriptor(), hAEnv->connectionMan().socketAddress() );
	}
	catch( CqlException& ex )
	{
		connected_ = CQL_NO;
		throw ex;
	}

	connected_ = CQL_YES;
	return CQL_SUCCESS;
}


NI Connection::releaseConnection( void )
{
	try
	{
		ClibConnection::releaseConnection();
	}
	catch( CqlException& ex )
	{
		connected_ = CQL_NO;
		throw ex;
	}

	connected_ = CQL_NO;
	return CQL_SUCCESS;
}


ConnectionManager::ConnectionManager( void ) : ClibConnectionManager()
{
}


ConnectionManager::~ConnectionManager( void )
{
}


UL CqlColumnTypes::dictionaryLength( void )
{
	return sizeof( typeType_ ) + sizeof( typeLength_ ) + typeName_.dictionaryLength();
}


CqlColumnTypes& CqlColumnTypes::operator = ( const CqlColumnTypes& other )
{
	defaultValue_ = other.defaultValue_;
	notNull_ = other.notNull_;
	typeLength_ = other.typeLength_;
	typeName_ = other.typeName_;
	typeType_ = other.typeType_;

	return *this;
}


CqlString ExceptionCodes::ecAsString( void ) const
{
	switch( ecode_ )
	{
	case EC_ABSTRACT_TABLE :
		return CqlString( "ABSTRACT_TABLE" );
		
	case EC_ATTACHED_TO_OPEN_FILE :
		return CqlString( "ATTACHED_TO_OPEN_FILE" );

	case EC_BINARY_USED_IN_EXPRESSION :
		return CqlString( "BINARY_USED_IN_EXPRESSION" );

	case EC_BTREE_INCONSISTENT :
		return CqlString( "BTREE_INCONSISTENT" );

	case EC_BUFFER_MANAGEMENT_FAILURE :
		return CqlString( "BUFFER_MANAGEMENT_FAILURE" );

	case EC_CHECK_VIOLATION :
		return CqlString( "CHECK_VIOLATION" );

	case EC_CLIB_FILE_SYSTEM :
		return CqlString( "CLIB_FILE_SYSTEM" );

	case EC_C_LIBRARY_CALL_FAILED :
		return CqlString( "C_LIBRARY_CALL_FAILED" );

	case EC_CLOSE_CALLED_WITH_PENDING_TRANSACTION :
		return CqlString( "CLOSE_CALLED_WITH_PENDING_TRANSACTION" );

	case EC_COLUMN_NOT_FOUND :
		return CqlString( "COLUMN_NOT_FOUND" );

	case EC_COMMUNICATION_FAILURE :
		return CqlString( "COMMUNICATION_FAILURE" );

	case EC_CONCURRENCY :
		return CqlString( "CONCURRENCY" );

	case EC_CONVERSION_FAILURE :
		return CqlString( "CONVERSION_FAILURE" );

	case EC_CONVERSION_SIZE_ERROR :
		return CqlString( "CONVERSION_SIZE_ERROR" );

	case EC_CORRUPTED_DICTIONARY :
		return CqlString( "CORRUPTED_DICTIONARY" );

	case EC_CREATE_SEQUENCE :
		return CqlString( "CREATE_SEQUENCE" );

	case EC_CURSOR_NAME_NOT_FOUND :
		return CqlString( "CURSOR_NAME_NOT_FOUND" );

	case EC_CURSOR_OPERATION_FAILURE :
		return CqlString( "CURSOR_OPERATION_FAILURE" );

	case EC_CURSOR_STATE :
		return CqlString( "CURSOR_STATE" );

	case EC_DICTIONARY_ERROR :
		return CqlString( "DICTIONARY_CREATE_FAILURE" );

	case EC_DICTIONARY_UPDATE_FAILURE :
		return CqlString( "DICTIONARY_UPDATE_FAILURE" );

	case EC_DOWNCAST :
		return CqlString( "DOWNCAST" );

	case EC_DROP_RESTRICT_VIOLATION :
		return CqlString( "DROP_RESTRICT_VIOLATION" );

	case EC_DUPLICATE_ROW :
		return CqlString( "DUPLICATE_ROW" );

	case EC_EXPRESSION_INCONSISTENCY :
		return CqlString( "EXPRESSION_INCONSISTENCY" );

	case EC_EOF :
		return CqlString( "UNEXPECTED_END_OF_FILE" );

	case EC_FILE_NOT_FOUND :
		return CqlString( "FILE_NOT_FOUND" );

	case EC_FILE_SYSTEM :
		return CqlString( "FILE_SYSTEM" );

	case EC_FILENAME_CREATION_FAILURE :
		return CqlString( "FILENAME_CREATION_FAILURE" );

	case EC_FOREIGN_KEY_CREATE_FAILURE :
		return CqlString( "FOREIGN_KEY_CREATE_FAILURE" );

	case EC_GROUP_BY_SELECT_VIOLATION :
		return CqlString( "EC_GROUP_BY_SELECT_VIOLATION" );

	case EC_ILLEGAL_OPERATION :
		return CqlString( "ILLEGAL_OPERATION" );

	case EC_ILLEGAL_OPERATION_FOR_VIEW :
		return CqlString( "ILLEGAL_OPERATION_FOR_VIEW" );

	case EC_ILLEGAL_TYPE_CONVERSION :
		return CqlString( "ILLEGAL_TYPE_CONVERSION" );

	case EC_INCOMPATIBLE_TYPES :
		return CqlString( "INCOMPATIBLE_TYPES" );

	case EC_INDEX_ACCESS :
		return CqlString( "INDEX_ACCESS" );

	case EC_INDEX_NOT_FOUND :
		return CqlString( "INDEX_NOT_FOUND" );

	case EC_INSERT_VALUES_MISMATCH :
		return CqlString( "INSERT_VALUES_MISMATCH" );

	case EC_INTEGRITY_VIOLATION :
		return CqlString( "INTEGRITY_VIOLATION" );

	case EC_INTERNAL_ERROR :
		return CqlString( "INTERNAL_ERROR" );

	case EC_INVALID_CONSTRUCTOR :
		return CqlString( "INVALID_CONSTRUCTOR" );

	case EC_INVALID_JOINT_RELATIONSHIP :
		return CqlString( "INVALID_JOINT_RELATIONSHIP" );

	case EC_INVALID_LENGTH_IN_STRING_FUNCTION :
		return CqlString( "INVALID_LENGTH_IN_STRING_FUNCTION" );

	case EC_INVALID_PARAMETER_VALUE :
		return CqlString( "INVALID_PARAMETER_VALUE" );

	case EC_INVALID_TYPE_COMBINATION :
		return CqlString( "INVALID_TYPE_COMBINATION" );

	case EC_ISAM_ACCESS_FAILURE :
		return CqlString( "ISAM_ACCESS_FAILURE" );

	case EC_ISAM_OPTIMIZATION_ERROR :
		return CqlString( "ISAM_OPTIMIZATION_ERROR" );

	case EC_KEY_NOT_FOUND :
		return CqlString( "KEY_NOT_FOUND" );

	case EC_LENGTH_EXCEEDED :
		return CqlString( "LENGTH_EXCEEDED" );

	case EC_LENGTH_MISMATCH :
		return CqlString( "LENGTH_MISMATCH" );

	case EC_LENGTH_NOT_SET :
		return CqlString( "LENGTH_NOT_SET" );

	case EC_MEMORY_ALLOCATION_FAILURE :
		return CqlString( "MEMORY_ALLOCATION_FAILURE" );

	case EC_MEMORY_INDEX_FAILURE :
		return CqlString( "MEMORY_INDEX_FAILURE" );

	case EC_NO_CURRENT_KEY :
		return CqlString( "NO_CURRENT_KEY" );

	case EC_NO_CURRENT_POSITION :
		return CqlString( "NO_CURRENT_POSITION" );

	case EC_NO_DATA :
		return CqlString( "NO_DATA" );

	case EC_NO_MORE_ROWS :
		return CqlString( "NO_MORE_ROWS" );

	case EC_NO_TRANSACTION :
		return CqlString( "NO_TRANSACTION" );

	case EC_NOT_IMPLEMENTED :
		return CqlString( "NOT_IMPLEMENTED" );

	case EC_NUMERIC_OPERATION_ON_BINARY_DATA :
		return CqlString( "NUMERIC_OPERATION_ON_BINARY_DATA" );

	case EC_NUMERIC_OPERATION_ON_CHARACTER_DATA :
		return CqlString( "NUMERIC_OPERATION_ON_CHARACTER_DATA" );

	case EC_NUMERIC_OPERATION_ON_LOGICAL_DATA :
		return CqlString( "NUMERIC_OPERATION_ON_LOGICAL_DATA" );

	case EC_NUMERIC_OPERATION_ON_TIMESTAMP_DATA :
		return CqlString( "NUMERIC_OPERATION_ON_TIMESTAMP_DATA" );

	case EC_OBJECT_CREATION_FAILURE :
		return CqlString( "OBJECT_CREATION_FAILURE" );

	case EC_OPEN_FAILURE :
		return CqlString( "OPEN_FAILURE" );

	case EC_POSITIONED_OPERATION_WITH_MULTIPLE_TABLES :
		return CqlString( "POSITIONED_OPERATION_WITH_MULTIPLE_TABLES" );

	case EC_PREDICATE_TREE_INCONSISTENT :
		return CqlString( "PREDICATE_TREE_INCONSISTENT" );

	case EC_PRIVILEGE_VIOLATION :
		return CqlString( "PRIVILEGE_VIOLATION" );

	case EC_REPORT_GENERATION :
		return CqlString( "REPORT_GENERATION" );

	case EC_SELECT_EVALUATION :
		return CqlString( "SELECT_EVALUATION" );

	case EC_STACK_OVERFLOW :
		return CqlString( "STACK_OVERFLOW" );

	case EC_STACK_UNDERFLOW :
		return CqlString( "STACK_UNDERFLOW" );

	case EC_STRING_REPRESENTATION_REQUESTED_FOR_BINARY_DATA :
		return CqlString( "STRING_REPRESENTATION_REQUESTED_FOR_BINARY_DATA" );

	case EC_SUBQUERY_MUST_RETURN_EXACTLY_ONE_ROW :
		return CqlString( "SUBQUERY_MUST_RETURN_EXACTLY_ONE_ROW" );

	case EC_SYNTAX_ERROR :
		return CqlString( "SYNTAX_ERROR" );

	case EC_SYSTEM_CONFIGURATION_ERROR :
		return CqlString( "SYSTEM_CONFIGURATION_ERROR" );

	case EC_TABLE_ACCESS_FAILURE :
		return CqlString( "TABLE_ACCESS_FAILURE" );

	case EC_TABLE_NOT_FOUND :
		return CqlString( "TABLE_NOT_FOUND" );

	case EC_TEMPORARY_FILE_ERROR :
		return CqlString( "TEMPORARY_FILE_ERROR" );

	case EC_TRANSACTION_ERROR :
		return CqlString( "TRANSACTION_ERROR" );

	case EC_TRANSACTION_FILE_ERROR :
		return CqlString( "TRANSACTION_FILE_ERROR" );

	case EC_TRANSACTION_EXCEEDS_LOG_SPACE :
		return CqlString( "TRANSACTION_EXCEEDS_LOG_SPACE" );

	case EC_TYPE_CONVERSION :
		return CqlString( "TYPE_CONVERSION" );

	case EC_TYPES_NOT_ASSIGNMENT_COMPATIBLE :
		return CqlString( "TYPES_NOT_ASSIGNMENT_COMPATIBLE" );

	case EC_UNDEFINED :
		return CqlString( "UNKNOWN EXCEPTION (INTERNAL ERROR)" );

	case EC_UNSUPPORTED_FEATURE :
		return CqlString( "UNSUPPORTED_FEATURE" );

	case EC_USER_LIMIT_EXCEEDED :
		return CqlString( "USER_LIMIT_EXCEEDED" );

	case EC_USER_TABLE_CREATE_FAILURE :
		return CqlString( "USER_TABLE_CREATE_FAILURE" );

	case EC_USER_TABLE_UPDATE_FAILURE :
		return CqlString( "USER_TABLE_UPDATE_FAILURE" );
	}

	//  for stupid compilers...
	return CqlString( "" );
}


CqlException::CqlException( const CqlString& eText, const ExceptionCodes _eCode, const NC *const fileName, const NI _lineNumber, const NC *const sqls, const NI _osError )
	: eCode_( _eCode ),
	  errorText_( eText ),
	  lineNumber_( _lineNumber ),
	  osError_( _osError ),
	  sourceFileName_( fileName ),
	  sqlstate_( sqls )
{
	errorText_ = eText;
	sourceFileName_ = fileName;
}


CqlException::~CqlException( void )
{
}


void CqlException::output( std::fstream& file )
{
	file << "Exception occurred:" << std::endl;
	file << "Error name: " << eCode_.ecAsString() << "\n";
	file << "Error message: " << errorText_ << "\n";
	file << "Source file name: " << sourceFileName_ << std::endl;
	file << "Source file line number: " << lineNumber_ << std::endl;
	file << "Operating system error code: " << osError_ << std::endl << std::endl;
}


void CqlException::output( AbstractLogger& al ) const
{
	al	<< "Error code:" << eCode_.ecAsString()
		<< ", error message:" << errorText_
		<< ", source file name:" << sourceFileName_
		<< ", line number:" << lineNumber_
		<< ", operating system error:" << osError_;
}


std::ostream& operator << ( std::ostream& ost, CqlException& ex )
{
	ex.output( static_cast< std::fstream& >( ost) );
	return ost;
}


const AbstractLogger& operator << ( AbstractLogger& al, const AbstractObjectCreationException& ex )
{
	ex.output( al );
	return al;
}


void CqlException::input( TempBuffer& tb )
{
	tb >> eCode_ >> errorText_ >> sourceFileName_ >> lineNumber_ >> osError_;
}


void CqlException::output( TempBuffer& tb ) const
{
	tb << eCode_ << errorText_ << sourceFileName_ << lineNumber_ << osError_;
}


CqlString CqlException::detailedErrorText( void )
{
	//  Default implementation is to return errorText.  Derived classes can
	//  override this function to provide a more user fristd::endly error message
	return errorText_;
}


CqlString CqlException::sqlstate( void )
{
	return CqlString( "HY000" );
}


MemoryIndexNode::MemoryIndexNode( void )
	: leftChild_( ((MemoryIndexNode*)0) ),
	  rightChild_( ((MemoryIndexNode*)0) ),
	  parent_( ((MemoryIndexNode*)0) ),
	  rightTreeLevel_( 0 ),
	  leftTreeLevel_( 0 ),
	  treeLevel_( 0 ),
	  balanceFactor_( BALANCED ),
	  isLeftChild_( CQL_NO ),
	  rootNode_( CQL_NO )
{
}


MemoryIndexNode::~MemoryIndexNode( void )
{
}


void MemoryIndexNode::destroyNode( void )
{
	if( leftChild_ )
	{
		leftChild_->destroyNode();
		delete leftChild_;
	}
	if( rightChild_ )
	{
		rightChild_->destroyNode();
		delete rightChild_;
	}
}


void MemoryIndexNode::dumpToLog( void )
{
	*hAEnv << "\n";
	*hAEnv << "********************************************** node dump,node = " << ((void*)this) << "\n";
	*hAEnv << "leftChild_ = " << leftChild_ << "\n";
	*hAEnv << "rightChild_ = " << rightChild_ << "\n";
	*hAEnv << "parent_ = " << parent_ << "\n";
	*hAEnv << "rightTreeLevel_ = " << rightTreeLevel_ << "\n";
	*hAEnv << "leftTreeLevel_ = " << leftTreeLevel_ << "\n";
	*hAEnv << "treeLevel_ = " << treeLevel_ << "\n";

	switch( balanceFactor_ )
	{
	case BALANCED :
		*hAEnv << "balanceFactor_ = BALANCED";
		break;

	case LEFT_BIGGER :
		*hAEnv << "balanceFactor_ = LEFT_BIGGER";
		break;

	case RIGHT_BIGGER :
		*hAEnv << "balanceFactor_ = RIGHT_BIGGER";
		break;
	}
	*hAEnv << "\n";

	*hAEnv << "isLeftChild_ = " << ((NI)isLeftChild_) << "\n";
	*hAEnv << "rootNode_ = " << ((NI)rootNode_) << "\\n\n";
	*hAEnv << "********************************************** END node dump,node = " << this << "\n";

	if( leftChild_ )
		leftChild_->dumpToLog();

	if( rightChild_ )
		rightChild_->dumpToLog( );
}


NI MemoryIndexNode::checkNodes( pMemoryIndexNode par, NI left )
{
	if( checked_ == CQL_YES )
	{
		multipleOccurances_ = CQL_YES;
		*((NC*)0) = 0;
	}
	else
		checked_ = CQL_YES;

	if( rootNode_ == CQL_YES && isLeftChild_ == CQL_YES )
		*((NC*)0) = 0;

	if( par != parent_ )
		*((NC*)0) = 0;

	if( ( isLeftChild_ == CQL_YES && left == CQL_NO ) || ( isLeftChild_ == ((BFT)CQL_NO) && left == CQL_YES ) )
		*((NC*)0) = 0;

	if( isLeftChild_ )
	{
		if( compareKeys( par ) == CqlConstants::THIS_GREATER_THAN_OTHER )
			*((NC*)0) = 0;
	}
	else
	{
		if( compareKeys( par ) == CqlConstants::THIS_LESS_THAN_OTHER )
			*((NC*)0) = 0;
	}

	if( leftChild_ )
		if( leftChild_->checkNodes( this, CQL_YES ) == CQL_FAILURE )
			*((NC*)0) = 0;

	if( rightChild_ )
		if( rightChild_->checkNodes( this, CQL_NO ) == CQL_FAILURE )
			*((NC*)0) = 0;

	return CQL_SUCCESS;
}


UNI MemoryIndexNode::treeDepth( void )
{
	UNI leftTreeDepth, rightTreeDepth, _treeDepth;

	if( leftChild_ )
		leftTreeDepth = leftChild_->treeDepth();
	else
		leftTreeDepth = 0;

	if( rightChild_ )
		rightTreeDepth = rightChild_->treeDepth();
	else
		rightTreeDepth = 0;

	if( leftTreeDepth > rightTreeDepth )
		_treeDepth = 1 + leftTreeDepth;
	else
		_treeDepth = 1 + rightTreeDepth;

	return _treeDepth;
}


void MemoryIndexNode::markNotChecked( void )
{
	checked_ = multipleOccurances_ = CQL_NO;

	if( leftChild_ )
		leftChild_->markNotChecked();

	if( rightChild_ )
		rightChild_->markNotChecked();
}


MemoryIndexNode& MemoryIndexNode::operator = ( MemoryIndexNode& other )
{
	leftChild_ = other.leftChild_;
	rightChild_ = other.rightChild_;
	parent_ = other.parent_;
	rightTreeLevel_ = other.rightTreeLevel_;
	leftTreeLevel_ = other.leftTreeLevel_;
	treeLevel_ = other.treeLevel_;
	balanceFactor_ = other.balanceFactor_;
	isLeftChild_ = other.isLeftChild_;
	rootNode_ = other.rootNode_;
	return *this;
}


void MemoryIndexNode::markChildren( pMemoryIndexNode par, NI root, NI left )
{
	rootNode_ = root;
	parent_ = par;

	if( left == CQL_YES )
		isLeftChild_ = CQL_YES;
	else
		isLeftChild_ = CQL_NO;

	if( leftChild_ )
	{
		leftChild_->markChildren( this, CQL_NO, CQL_YES );
		leftTreeLevel_ = leftChild_->treeLevel() + 1;
	}
	else
		leftTreeLevel_ = 0;

	if( rightChild_ )
	{
		rightChild_->markChildren( this, CQL_NO, CQL_NO );
		setRightTreeLevel( rightChild_->treeLevel() + 1 );
	}
	else
		setRightTreeLevel( 0 );

	setTreeLevel( leftTreeLevel_ + rightTreeLevel_ );
}


void MemoryIndexNode::releaseMemory( void )
{
}


OutputBuffer::OutputBuffer( AbstractDatabaseHandle& adh ) : TempBuffer( adh ), currentColumn_( 0 ), currentRow_( 0 ), hAdb_( adh ), remainingSpace_( 0 )
{
}


OutputBuffer::~OutputBuffer( void )
{
}


NI OutputBuffer::initialize( void )
{
	if( setBuffer( CQL_OUTPUT_CHUNK_SIZE ) == CQL_FAILURE )
		return CQL_FAILURE;

	remainingSpace_ = CQL_OUTPUT_CHUNK_SIZE;
	return CQL_SUCCESS;
}


void OutputBuffer::enlargeBuffer( void )
{
	UL oldSize = size();
	UC *tempSpace = new UC[ oldSize ];
	if( !tempSpace )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memcpy( tempSpace, bufferBase(), oldSize );
	setBuffer( ((UNI)( size() + CQL_OUTPUT_CHUNK_SIZE)) );
	memcpy( bufferBase(), tempSpace, ((UNI)oldSize) );
	remainingSpace_ += CQL_OUTPUT_CHUNK_SIZE;
}


void OutputBuffer::checkSpace( UNI requiredSize )
{
	if( requiredSize > remainingSpace_ )
		enlargeBuffer();
}


void OutputBuffer::writeObject( void* ptr, UL sz )
{
	checkSpace( sz );
	*( dynamic_cast< TempBuffer* >( this ) ) << FOUR_BYTE_LENGTH << DO_COPY << sz;
	*( dynamic_cast< TempBuffer* >( this ) ) << ptr;
	remainingSpace_ -= ( sz + sizeof( sz ) );
}


OutputBuffer& OutputBuffer::operator << ( US us )
{
	checkSpace( sizeof( US ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << us;
	remainingSpace_ -= sizeof( US );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( NI ni )
{
	checkSpace( sizeof( NI ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << ni;
	remainingSpace_ -= sizeof( NI );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( UNI uni )
{
	checkSpace( sizeof( UNI ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << uni;
	remainingSpace_ -= sizeof( UNI );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( UL ul )
{
	checkSpace( sizeof( UL ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << ul;
	remainingSpace_ -= sizeof( UL );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( UC uc )
{
	checkSpace( sizeof( UC ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << uc;
	remainingSpace_ -= sizeof( UC );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( D d )
{
	checkSpace( sizeof( D ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << d;
	remainingSpace_ -= sizeof( D );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( F f )
{
	checkSpace( sizeof( F ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << f;
	remainingSpace_ -= sizeof( F );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( SC sc )
{
	checkSpace( sizeof( SC ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << sc;
	remainingSpace_ -= sizeof( SC );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( L l )
{
	checkSpace( sizeof( L ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << l;
	remainingSpace_ -= sizeof( L );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( S s )
{
	checkSpace( sizeof( S ) );
	*( dynamic_cast< TempBuffer* >( this ) ) << s;
	remainingSpace_ -= sizeof( S );
	return *this;
}


OutputBuffer& OutputBuffer::operator << ( CqlString& str )
{
	if( !str.length() )
		return *this;

	return *this << str.text();
}


OutputBuffer& OutputBuffer::operator << ( const char * const str )
{
	UL len = static_cast< UL >( strlen( str ) );
	if( !len )
		return *this;

	checkSpace( len  );
	copyIn( str, len );
	remainingSpace_ -= len;

	UL loop;
	const char *p = str;
	for( p = str, loop = 0; loop < len; loop++, p++ )
	{
		if( *p == '\n' )
		{
			currentColumn_ = 0;
			currentRow_++;
		}
		else
			currentColumn_++;
	}

	return *this;
}


UNI OutputBuffer::currentColumn( void )
{
	return currentColumn_;
}


UNI OutputBuffer::currentRow( void )
{
	return currentRow_;
}


//
//  This global will turn on lots (and we mean LOTS) of error messages
//  from the lex/yacc parser for the configuration file.  Any value 
//  other than zero turns debugging on.
//
extern NI configdebug;

extern FILE *configin;


SystemConfigurationManager::SystemConfigurationManager( const CqlString& initialDirectory )
	: Logger( initialDirectory ),
	  hostName_(),
	  isamServiceName_(),
	  logFileSize_( CQL_LOG_FILE_SIZE ),
	  machineId_( CQL_MACHINE_ID ),
	  maxBufferPages_( CQL_MAXIMUM_BUFFER_PAGES ),
	  maxUsers_( CQL_MAXIMUM_USERS ),
	  numberOfLogFiles_( CQL_NUMBER_OF_LOGS ),
	  pageSize_( CQL_PAGE_SIZE ),
	  sqlServiceName_()
{
	NI rc;
	extern NI configparse( AbstractSystemConfigurationManager& );

	//
	//  Look for configuration file.  If found, use values to override defaults.
	//
	//  First, check for value in environment of CQL_CONFIG_FILE.  If it exists, use it
	//  as the name of the CQL configuration file.  If the environment variable is not
	//  set, use __CQL_CONFIG_FILE_NAME__
	//
	isamServiceName_ = CQL_DEFAULT_ISAM_SERVER_SERVICE_NAME;
	sqlServiceName_ = CQL_DEFAULT_SQL_SERVER_SERVICE_NAME;

	CqlString configFileName;
	getEnvironmentVariableValue( configFileName, CQL_CONFIG_ENVIRONMENT_VARIABLE_NAME, CQL_CONFIG_FILE_NAME );

	configin = fopen( configFileName.text(), "r" );
	if( !configin )
	{
		this->hostName( const_cast<char*>("cqlhost") );
		this->logFileSize( 4000000 );
		return;
	}

	//
	//  Config file exists.  Parse it.
	//
	rc = configparse( *this );
	if( rc == 1 )
		throw SystemConfigurationException( __FILE__, __LINE__ );
}


SystemConfigurationManager::~SystemConfigurationManager( void )
{
}


void SystemConfigurationManager::logFileSize( NI size )
{
	logFileSize_ = size;
}


NI SystemConfigurationManager::hostName( pNC name )
{
	hostName_ = name;
	//exception
	return CQL_SUCCESS;
}


NI SystemConfigurationManager::isamServiceName( pNC name )
{
	isamServiceName_ = name;
	//exception
	return CQL_SUCCESS;
}


void SystemConfigurationManager::machineId( NI mid )
{
	machineId_ = mid;
}


void SystemConfigurationManager::maxBufferPages( NI mbp )
{
	maxBufferPages_ = mbp;
}


void SystemConfigurationManager::maxUsers( NI mu )
{
	maxUsers_ = mu;
}


void SystemConfigurationManager::numberOfLogFiles( NI nlf )
{
	numberOfLogFiles_ = nlf;
}


NI SystemConfigurationManager::sqlServiceName( pNC name )
{
	sqlServiceName_ = name;
	//exception
	return CQL_SUCCESS;
}


void SystemConfigurationManager::pageSize( NI size )
{
	pageSize_ = size;
}


//
//  This function is to satisfy an external required by the bison parser for the
//  system configuration file.
//
NI configerror( pNC msg )
{
	fflush( stdout );
	fprintf( stderr, "Error reading system configuration file, %s\n", msg );
	fflush( stderr );
	return 1;
}


UserConfigurationManager::UserConfigurationManager( void )
	: dateFormat_( MMDDYY ),
	  dateSeparator_( CQL_DEFAULT_DATE_SEPARATOR ),
	  timeSeparator_( CQL_DEFAULT_TIME_SEPARATOR ),
	  manyAny_( CQL_MANY_ANY ),
	  oneAny_( CQL_ONE_ANY )
{
}


UserConfigurationManager::~UserConfigurationManager( void )
{
}
