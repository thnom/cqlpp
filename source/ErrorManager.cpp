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


ErrorManager::ErrorManager( void ) : AbstractErrorManager(), errorCode_( CQL_NO_ERROR ), errorFile_(), errorLine_( 0 ), osError_( 0 )
{
}


ErrorManager::ErrorManager( const ExceptionCodes exCode, const CqlString& efile, const NI line, const CqlString& etext, const CqlString& sqls, const NI oserr )
	: exceptionCode_( exCode ),
	  errorFile_( efile ),
	  errorLine_( line ),
	  errorText_( etext ),
	  osError_( oserr ),
	  sqlstate_( sqls )
{
}


ErrorManager::~ErrorManager( void )
{
}


NI ErrorManager::cleanup( void )
{
	return CQL_SUCCESS;
}


NI ErrorManager::log( ErrorCodes errCode, pNC fname, NI lineNo, NI osErr )
{
	errorCode_ = errCode;
	errorFile_ = fname;
	errorLine_ = lineNo;
	osError_ = osErr;

	*hAEnv << errCode << fname << lineNo << osErr;
	return CQL_FAILURE;
}


NI ErrorManager::returnError( ErrorCodes errCode, const char * const fname, NI lineNo, NI osErr )
{
	//
	//  if more than one error occurs, we ignore all but the first
	//
	if( !errorCode_ )
	{
		errorCode_ = errCode;
		errorLine_ = lineNo;
		osError_ = osErr;
		errorFile_ = fname;

		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "Error, error code=%d, file=%s, line=%d, oserror=%d\n",
							 ((L)errCode),
							 fname,
							 lineNo,
							 osErr );
	}
	else
	{
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "Multiple errors, error code=%d, file=%s, line=%d, oserror=%d\n",
							 ((L)errCode),
							 fname,
							 lineNo,
							 osErr );
	}

	return CQL_FAILURE;
}


NI ErrorManager::returnRC( NI returnCode,
						   enum ErrorCodes errCode,
						   const char * const fname,
						   NI lineNo,
						   NI osErr )
{
	//
	//  if more than one error occurs, we ignore all but the first
	//
	if( !errorCode_ )
	{
		errorCode_ = errCode;
		errorLine_ = lineNo;
		osError_ = osErr;
		errorFile_ = fname;

		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "Error, return code=%d, error code=%d, file=%s, line=%d, oserror=%d\n",
							 returnCode,
							 ((L)errCode),
							 fname,
							 lineNo,
							 osErr );
	}
	else
	{
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "Multiple errors, return code=%d, error code=%d, file=%s, line=%d, oserror=%d\n",
							 returnCode,
							 ((L)errCode),
							 fname,
							 lineNo,
							 osErr );
	}

	return returnCode;
}


NI ErrorManager::returnNormalOrError( void )
{
	if( errorCode_ != 0 )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI ErrorManager::returnNormal( ErrorCodes errCode, const char * const fname, NI lineNo )
{
	errorCode_ = errCode;
	errorFile_ = fname;
	errorLine_ = lineNo;
	osError_ = 0;
	return CQL_SUCCESS;
}


NI ErrorManager::noError( void )
{
	switch( errorCode_ )
	{
	case CQL_NO_ERROR :
	case CQL_NO_DATA_FOUND :
		return CQL_YES;

	default :
		break;
	}

	return CQL_NO;
}


void ErrorManager::resetIfCloseWithPendingTransaction( void )
{
	if( errorCode_ == CLOSE_CALLED_WITH_PENDING_TRANSACTION )
		resetError();
}


const char * const ErrorManager::errorText( ErrorCodes ec )
{
	switch( ec )
	{
	//
	//  ANSI specified codes
	//

	case CQL_NO_ERROR :
		return "successful completion";

	case CQL_NO_DATA_FOUND :
		return "no data found";

	//
	//  "Normal" errors.  That is, errors which do not indicate abnormal operation
	//

	case ALTER_REQUESTED_FOR_VIEW :
		return "ALTER TABLE not allowed for VIEW";

	case ASSIGNMENT_FROM_INVALID_TYPE :
		return "invalid type specified for assignment";

	case ASYNCHRONOUS_EXECUTION_NOT_SUPPORTED :
		return "ODBC driver does not support asynchronous execution";

	case BAD_CAST :
		return "Invalid cast (internal error)";

	case BINARY_LENGTH_INCORRECT_FOR_SQL_TYPE :
		return "ODBC specified binary data of wrong length for SQL type";

	case BINARY_TYPE_USED_IN_EXPRESSION :
		return "a BINARY, VARBINARY, or LONGVARBINARY column was used in an expression";

	case BOOKMARKS_NOT_SUPPORTED :
		return "ODBC bookmarks not supported yet";

	case BOOLEAN_TEST_OF_INVALID_TYPE :
		return "boolean test of inappropriate type";

	case CHECK_EXPRESSION_COLUMN_NOT_RECOGNIZED :
		return "column name not recognized in CHECK expression";

	case CLOSE_CALLED_WITH_PENDING_TRANSACTION :
		return "attempted to close file with pending transaction";

	case COLUMN_CHECK_EXPRESSION_NOT_SATISFIED :
		return "CHECK expression for column not satisfied for insert or udpate";

	case COLUMN_DOES_NOT_EXIST :
		return "column name not recognized";

	case COLUMN_NUMBER_OUT_OF_RANGE :
		return "specified column number exceeds number of columns in result set";

	case CONCURRENCY :
		return "multiuser interference";

	case CONNECTION_NOT_OPEN :
		return "a client side operation which requires an open connection was called before the connection existed";

	case CONVERSION_DECODING_ERROR :
		return "error converting value to host type";

	case CREATE_INDEX_REQUESTED_FOR_VIEW :
		return "CREATE INDEX not allowed for VIEW";

	case CURSOR_ALREADY_HAS_A_NAME :
		return "name specified for cursor which already has a name";

	case CURSOR_OPERATION_REQUESTED_FOR_NON_SELECT :
		return "statement is not a SELECT statement";

	case DATA_TRUNCATED :
		return "output data was truncated";

	case DELETE_NO_CURRENT_POSITION :
		return "positioned delete called with no current position";

	case DIVISION_BY_ZERO :
		return "division by zero";

	case DUPLICATE_CURSOR_NAME :
		return "duplicate cursor name";

	case DUPLICATE_INSERT_REJECTED :
		return "insert violated UNIQUE constraint";

	case EXTENDED_FETCH_NOT_SUPPORTED :
		return "ODBC level 2 not supported yet";

	case FOREIGN_KEY_DOES_NOT_EXIST :
		return "CREATE declared a foreign key, but no candidate key exists";

	case FUNCTION_SEQUENCE_ERROR :
		return "ODBC function called out of sequence";

	case HOST_SERVICE_NAME_RETRIEVAL_ERROR :
		return "entry not found in `hosts' or `services' file";

	case INCOMPATIBLE_TYPES_IN_EXPRESSION :
		return "incompatible types in expression";

	case INCOMPATIBLE_TYPES_FOR_ASSIGNMENT :
		return "incompatible type for assignment";

	case INDEX_NAME_NOT_FOUND :
		return "index name not found";

	case INTERACTIVE_SELECT_ON_BINARY_TYPE :
		return "interactive select requested for binary column";

	case INVALID_CONVERSION_REQUESTED :
		return "invalid conversion requested";

	case INVALID_CURSOR_HANDLE :
		return "cursor handle is invalid";

	case INVALID_CURSOR_STATE :
		return "cursor state is wrong for requested operation";

	case INVALID_JOIN_RELATIONSHIPS :
		return "join relationships result in infinite data set";

	case INVALID_LENGTH_IN_STRING_FUNCTION :
		return "invalid length in string function";

	case INVALID_TYPE_COMBINATION :
		return "invalid combination of types";

	case INVALID_VARIABLE_SPECIFICATION_VALUE :
		return "invalid variable specification value";

	case INSERT_SELECT_MISMATCH :
		return "insert/select column type mismatch";

	case INSERT_VALUES_MISMATCH :
		return "insert value type mismatch";

	case KEYSETS_NOT_SUPPORTED :
		return "ODBC keyset driver cursors are not supported";

	case NETWORK_PACKET_NOT_CHANGEABLE :
		return "The ODBC network packet size command is ignored";

	case NO_DELETE_PRIVILEGE :
		return "user does not have DELETE privilege";

	case NO_INSERT_PRIVILEGE :
		return "user does not have INSERT privilege";

	case NO_SELECT_PRIVILEGE :
		return "user does not have SELECT privilege";

	case NO_UPDATE_PRIVILEGE :
		return "user does not have UPDATE privilege";

	case NULL_IFILE_HANDLE :
		return "null IsamFile handle";

	case PARAMETER_NOT_SET :
		return "value not provided for parameter";

	case PARAMETER_POSITION_NOT_FOUND :
		return "invalid parameter number";

	case POSITIONED_DELETE_MULTIPLE_TABLES :
		return "positioned delete requested for cursor with more than one table";

	case POSITIONED_OPERATION_NAME_MISMATCH :
		return "Cursor name not recognized";

	case POSITIONED_UPDATE_WITH_MULTIPLE_TABLES :
		return "positioned update requested for cursor with more than one table";

	case QUALIFIERS_NOT_SUPPORTED :
		return "CQL does not use the ODBC qualifier";

	case REFERENTIAL_INTEGRITY_VIOLATION :
		return "insert or delete operation aborted because of referential integrity violation";

	case SCRIPT_NOT_FOUND :
		return "script file not found";

	case SEGMENT_DOES_NOT_EXIST :
		return "value specified for segment which does not exist";

	case SIGNIFICANT_DIGITS_LOST_IN_CONVERSION :
		return "conversion loses significant digits";

	case SIMULATED_CURSORS_NOT_USED :
		return "real cursors supported, so ODBC simulated cursors are not required";

	case SQL_DROP_CASCADE_ERROR :
		return "cascade operation failed during DROP";

	case SQL_DROP_RESTRICT_ERROR :
		return "restricted DROP requested, but references exist";

	case SQL_FILE_OPEN_ERROR :
		return "table open failed";

	case SQL_TABLE_NOT_FOUND :
		return "table name not recognized";

	case SUBQUERY_MUST_RETURN_EXACTLY_ONE_ROW :
		return "subquery returns 0 values or more than one value";

	case SYNTAX :
		return "syntax error";

	case TABLE_NOT_PART_OF_SELECT :
		return "table name not found in FROM clause";

	case TOO_MANY_ROWS :
		return "too many rows";

	case TOO_MUCH_DATA_IN_PUT :
		return "ODBC put data tried to put more data than the buffer size can hold";

	case TRANSLATION_DLL_NOT_SUPPORTED :
		return "ODBC driver does not yet support translation DLL";

	case TYPES_NOT_ASSIGNMENT_COMPATIBLE :
		return "types not assignment compatible";

	case UPDATE_COUNT_REQUESTED_FOR_NON_UPDATE :
		return "update count requested for non-update statement";

	case USER_FILE_CREATE_ERROR :
		return "table creation error";

	case ZERO_ROWS_IN_SUBQUERY :
		return "subquery returned zero rows";

	//
	//  These errors indicate abnormal operation
	//

	case ABNORMAL_CONCURRENCY :
		return "Abnormal concurrency error";

	case ALLOCATION :
		return "memory allocation failure";

	case ATTACHED_TO_OPEN_FILE :
		return "create or open requested for table which is already open";

	case BTREE_INCONSISTENT :
		return "b-tree inconsistency detected";

	case CACHE_INDEX_FAILURE :
		return "error maintaining internal index";

	case COMMUNICATIONS_ERROR :
		return "communications failure";

	case CQL_CLOSE :
		return "close failed";

	case CQL_CREATE :
		return "create failure";

	case CQL_OPEN :
		return "open failure";

	case CREATE_SEQUENCE :
		return "create requests (ISAM level) not in proper sequence";

	case DICTIONARY_CREATE_ERROR :
		return "error creating dictionary";

	case DICTIONARY_INCONSISTENCY :
		return "dictionary is internally inconsistent";

	case DICTIONARY_READ_ERROR :
		return "error reading dictionary";

	case DICTIONARY_UPDATE_ERROR :
		return "error updating dictionary";

	case EXPRESSION_INCONSISTENCY :
		return "invalid expression syntax";

	case FLUSH :
		return "data flush failure";

	case INITIALIZATION :
		return "Object initialization failed";

	case INTERNAL_ERROR :
		return "internal error";

	case INVALID_OPEN_FILE_INDEX :
		return "internal index operation failure";

	case INVALID_NODE_INDEX :
		return "internal index operation failure";

	case INVALID_TIME_FROM_OS :
		return "operating system returned invalid current date/time";

	case ISAM_ACCESS_ERROR :
		return "ISAM level operation failed";

	case ISAM_DATA_INDEX_INCONSISTENCY :
		return "ISAM table is corrupted";

	case ISAM_HEADER_INCONSISTENCY :
		return "ISAM table header is inconsistent with table";

	case LIST_INCONSISTENCY :
		return "internal list error";

	case LOG_READ :
		return "error reading log file";

	case NO_SEGMENTS_FOR_KEY :
		return "no segments defined for key";

	case OPEN_FILE_NOT_FOUND :
		return "internal index inconsistency";

	case PREDICATE_TREE_INCONSISTENCY :
		return "internal data structure inconsistency";

	case PRIVILEGE_DICTIONARY_UPDATE_ERROR :
		return "privilege dictionary update failure";

	case READ_ERROR :
		return "read error";

	case SEEK :
		return "seek error";

	case CQL_SOCKET_ERROR :
		return "socket operation error";

	case SQL_BEGIN_TRANSACTION_ERROR :
		return "begin transaction failure";

	case SQL_DELETE_ROW_FAILURE :
		return "delete row failure";

	case SQL_END_TRANSACTION_ERROR :
		return "commit transaction failure";

	case SQL_INDEX_DELETION_ERROR :
		return "index deletion error";

	case SQL_ROLLBACK_TRANSACTION_ERROR :
		return "rollback transaction failure";

	case STACK_UNDERFLOW :
		return "internal stack error";

	case TEMPNAME :
		return "unable to get temporary name";

	case TEMPORARY_FILE_ACCESS_ERROR :
		return "temporary file access failure";

	case TEMPORARY_FILE_ADD_ERROR :
		return "temporary file insert failure";

	case TEMPORARY_FILE_CREATE_ERROR :
		return "temporary file create failure";

	case TRANSACTION_STATE_ERROR :
		return "internal transaction processing error";

	case TYPE_NOT_SET_FOR_EXPRESSION :
		return "expression type invalid";

	case USER_FILE_ABNORMAL_CREATE_ERROR :
		return "table create failure";

	case USER_FILE_ACCESS_ERROR :
		return "table access error";

	case VIEW_INCONSISTENT :
		return "view inconsistent with table";

	case VIRTUAL :
		return "virtual memory file access failure";

	case WRITE_ERROR :
		return "write failure";
	}

	return "error not recognized";
}


const char * const ErrorManager::sqlstate( ErrorCodes ec )
{
	switch( ec )
	{
	//
	//  ANSI specified codes
	//

	case CQL_NO_ERROR :
		return "00000";

	case CQL_NO_DATA_FOUND :
		return "00000";

	//
	//  "Normal" errors.  That is, errors which do not indicate abnormal operation
	//

	case ALTER_REQUESTED_FOR_VIEW :
		return "S1000";

	case ASSIGNMENT_FROM_INVALID_TYPE :
		return "22005";

	case ASYNCHRONOUS_EXECUTION_NOT_SUPPORTED :
		return "S1C00";

	case BINARY_LENGTH_INCORRECT_FOR_SQL_TYPE :
		return "22003";

	case BINARY_TYPE_USED_IN_EXPRESSION :
		return "S1000";

	case BOOKMARKS_NOT_SUPPORTED :
		return "S1C00";

	case BOOLEAN_TEST_OF_INVALID_TYPE :
		return "S1000";

	case CHECK_EXPRESSION_COLUMN_NOT_RECOGNIZED :
		return "S1000";

	case CLOSE_CALLED_WITH_PENDING_TRANSACTION :
		return "25000";

	case COLUMN_CHECK_EXPRESSION_NOT_SATISFIED :
		return "S1000";

	case COLUMN_DOES_NOT_EXIST :
		return "S0022";

	case COLUMN_NUMBER_OUT_OF_RANGE :
		return "S1002";

	case CONCURRENCY :
		return "40001";

	case CONNECTION_NOT_OPEN :
		return "08003";

	case CONVERSION_DECODING_ERROR :
		return "S1000";

	case CREATE_INDEX_REQUESTED_FOR_VIEW :
		return "S1000";

	case CURSOR_ALREADY_HAS_A_NAME :
		return "24000";

	case CURSOR_OPERATION_REQUESTED_FOR_NON_SELECT :
		return "S1000";

	case DATA_TRUNCATED :
		return "01004";

	case DELETE_NO_CURRENT_POSITION :
		return "S1109";

	case DIVISION_BY_ZERO :
		return "22012";

	case DUPLICATE_CURSOR_NAME :
		return "3C000";

	case DUPLICATE_INSERT_REJECTED :
		return "S1000";

	case EXTENDED_FETCH_NOT_SUPPORTED :
		return "S1C00";

	case FOREIGN_KEY_DOES_NOT_EXIST :
		return "S1000";

	case FUNCTION_SEQUENCE_ERROR :
		return "S1010";

	case HOST_SERVICE_NAME_RETRIEVAL_ERROR :
		return "08001";

	case INCOMPATIBLE_TYPES_IN_EXPRESSION :
		return "07006";

	case INCOMPATIBLE_TYPES_FOR_ASSIGNMENT :
		return "22005";

	case INDEX_NAME_NOT_FOUND :
		return "S1000";

	case INTERACTIVE_SELECT_ON_BINARY_TYPE :
		return "S1000";

	case INVALID_CONVERSION_REQUESTED :
		return "S1000";

	case INVALID_CURSOR_HANDLE :
		return "S1000";

	case INVALID_CURSOR_STATE :
		return "24000";

	case INVALID_JOIN_RELATIONSHIPS :
		return "S1000";

	case INVALID_LENGTH_IN_STRING_FUNCTION :
		return "S1000";

	case INVALID_TYPE_COMBINATION :
		return "S1000";

	case INVALID_VARIABLE_SPECIFICATION_VALUE :
		return "S1000";

	case INSERT_SELECT_MISMATCH :
		return "S1000";

	case INSERT_VALUES_MISMATCH :
		return "21S01";

	case KEYSETS_NOT_SUPPORTED :
		return "S1C00";

	case NETWORK_PACKET_NOT_CHANGEABLE :
		return "S1C00";

	case NO_DELETE_PRIVILEGE :
		return "S1000";

	case NO_INSERT_PRIVILEGE :
		return "S1000";

	case NO_SELECT_PRIVILEGE :
		return "S1000";

	case NO_UPDATE_PRIVILEGE :
		return "S1000";

	case NULL_IFILE_HANDLE :
		return "S1000";

	case PARAMETER_NOT_SET :
		return "S1000";

	case PARAMETER_POSITION_NOT_FOUND :
		return "S1000";

	case POSITIONED_DELETE_MULTIPLE_TABLES :
		return "S1000";

	case POSITIONED_OPERATION_NAME_MISMATCH :
		return "S1000";

	case POSITIONED_UPDATE_WITH_MULTIPLE_TABLES :
		return "S1000";

	case QUALIFIERS_NOT_SUPPORTED :
		return "S1C00";

	case REFERENTIAL_INTEGRITY_VIOLATION :
		return "S1000";

	case SCRIPT_NOT_FOUND :
		return "S1000";

	case SEGMENT_DOES_NOT_EXIST :
		return "S1000";

	case SIGNIFICANT_DIGITS_LOST_IN_CONVERSION :
		return "22003";

	case SIMULATED_CURSORS_NOT_USED :
		return "S1C00";

	case SQL_DROP_CASCADE_ERROR :
		return "S1000";

	case SQL_DROP_RESTRICT_ERROR :
		return "S1000";

	case SQL_FILE_OPEN_ERROR :
		return "S1000";

	case SQL_TABLE_NOT_FOUND :
		return "S0002";

	case SUBQUERY_MUST_RETURN_EXACTLY_ONE_ROW :
		return "S1000";

	case SYNTAX :
		return "37000";

	case TABLE_NOT_PART_OF_SELECT :
		return "S1000";

	case TOO_MANY_ROWS :
		return "01S04";

	case TOO_MUCH_DATA_IN_PUT :
		return "S1090";

	case TRANSLATION_DLL_NOT_SUPPORTED :
		return "S1C00";

	case TYPES_NOT_ASSIGNMENT_COMPATIBLE :
		return "22005";

	case UPDATE_COUNT_REQUESTED_FOR_NON_UPDATE :
		return "S1000";

	case USER_FILE_CREATE_ERROR :
		return "S1000";

	case ZERO_ROWS_IN_SUBQUERY :
		return "S1000";

	//
	//  These errors indicate abnormal operation
	//

	case ABNORMAL_CONCURRENCY :
		return "S1000";

	case ALLOCATION :
		return "S1001";

	case ATTACHED_TO_OPEN_FILE :
		return "S1000";

	case BAD_CAST :
		return "S1000";

	case BTREE_INCONSISTENT :
		return "S1000";

	case CACHE_INDEX_FAILURE :
		return "S1000";

	case COMMUNICATIONS_ERROR :
		return "08S01";

	case CQL_CLOSE :
		return "S1000";

	case CQL_CREATE :
		return "S1000";

	case CQL_OPEN :
		return "37000";

	case CREATE_SEQUENCE :
		return "S1000";

	case DICTIONARY_CREATE_ERROR :
		return "S1000";

	case DICTIONARY_INCONSISTENCY :
		return "S1000";

	case DICTIONARY_READ_ERROR :
		return "S1000";

	case DICTIONARY_UPDATE_ERROR :
		return "S1000";

	case EXPRESSION_INCONSISTENCY :
		return "S1000";

	case FLUSH :
		return "S1000";

	case INITIALIZATION :
		return "S1000";

	case INTERNAL_ERROR :
		return "S1000";

	case INVALID_OPEN_FILE_INDEX :
		return "S1000";

	case INVALID_NODE_INDEX :
		return "S1000";

	case INVALID_TIME_FROM_OS :
		return "S1000";

	case ISAM_ACCESS_ERROR :
		return "37000";

	case ISAM_DATA_INDEX_INCONSISTENCY :
		return "37000";

	case ISAM_HEADER_INCONSISTENCY :
		return "S1000";

	case LIST_INCONSISTENCY :
		return "S1000";

	case LOG_READ :
		return "S1000";

	case NO_SEGMENTS_FOR_KEY :
		return "S1000";

	case OPEN_FILE_NOT_FOUND :
		return "S1000";

	case PREDICATE_TREE_INCONSISTENCY :
		return "S1000";

	case PRIVILEGE_DICTIONARY_UPDATE_ERROR :
		return "S1000";

	case READ_ERROR :
		return "37000";

	case SEEK :
		return "37000";

	case CQL_SOCKET_ERROR :
		return "S1000";

	case SQL_BEGIN_TRANSACTION_ERROR :
		return "S1000";

	case SQL_DELETE_ROW_FAILURE :
		return "S1000";

	case SQL_END_TRANSACTION_ERROR :
		return "S1000";

	case SQL_INDEX_DELETION_ERROR :
		return "37000";

	case SQL_ROLLBACK_TRANSACTION_ERROR :
		return "S1000";

	case STACK_UNDERFLOW :
		return "S1000";

	case TEMPNAME :
		return "S1000";

	case TEMPORARY_FILE_ACCESS_ERROR :
		return "S1000";

	case TEMPORARY_FILE_ADD_ERROR :
		return "S1000";

	case TEMPORARY_FILE_CREATE_ERROR :
		return "S1000";

	case TRANSACTION_STATE_ERROR :
		return "25000";

	case TYPE_NOT_SET_FOR_EXPRESSION :
		return "S1000";

	case USER_FILE_ABNORMAL_CREATE_ERROR :
		return "37000";

	case USER_FILE_ACCESS_ERROR :
		return "37000";

	case VIEW_INCONSISTENT :
		return "S1000";

	case VIRTUAL :
		return "S1000";

	case WRITE_ERROR :
		return "37000";
	}

	return "99999";
}
