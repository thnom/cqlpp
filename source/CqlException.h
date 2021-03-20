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


#ifndef __CqlException_h
#define __CqlException_h


class CqlException : public ExceptionCodes
{
	ExceptionCodes eCode_;
	CqlString errorText_;
	NI lineNumber_;
	NI osError_;
	CqlString sourceFileName_;
	CqlString sqlstate_;

public:

	CqlException( const CqlString& /*message*/, const ExceptionCodes /*ec*/, const NC * const /*fileName*/, const NI /*lineNo*/, const NC * const /*sqlstate*/, const NI /*osError*/ = 0 );
	virtual ~CqlException( void );

	ExceptionCodes eCode( void ) { return eCode_; }
	CqlString& errorText( void ) { return errorText_; }
	CqlString& sourceFileName( void ) { return sourceFileName_; }
	NI lineNumber( void ) { return lineNumber_; }
	NI osError( void ) { return osError_; }
	CqlString sqlstate( void );

	virtual CqlString detailedErrorText( void );
	virtual void input( TempBuffer& /*tempBuffer*/ );
	virtual void output( AbstractLogger& ) const;
	virtual void output( std::fstream& );
	virtual void output( TempBuffer& /*tempBuffer*/ ) const;

};


class AbstractObjectCreationException : public CqlException
{
public :
	AbstractObjectCreationException( const NC * const msg, const ExceptionCodes ec, const NC * const fname, const NI line, const NI _osError = 0 )
		: CqlException( msg, ec, fname, line, "HY000", _osError )
	{
	}

	virtual ~AbstractObjectCreationException( void ) { }
};


class AbstractTableException : public CqlException
{
public :

	AbstractTableException( const NC * const msg, const ExceptionCodes ec, const NC * const fname, const NI line, const NI _osError = 0 )
		: CqlException( msg, ec, fname, line, "HY000", _osError )
	{
	}

	AbstractTableException( const NC * const filename, const NI linenumber )
		: CqlException( "Abstract table exception", EC_ABSTRACT_TABLE, filename, linenumber, "HY000" ) { }

	virtual ~AbstractTableException( void )
	{
	}

};


class AttachedToOpenFileException : public CqlException
{
public :
	AttachedToOpenFileException( const NC * const filename, const NI linenumber )
		: CqlException( "Object attached to open file", EC_ATTACHED_TO_OPEN_FILE, filename, linenumber, "HY000" )
	{
	}

	virtual ~AttachedToOpenFileException( void ) { }
};


class BinaryTypeUsedInExpressionException : public CqlException
{
public :
	BinaryTypeUsedInExpressionException( const NC * const fname, const NI line )
		: CqlException( "Binary type used in expression.", EC_BINARY_USED_IN_EXPRESSION, fname, line, "HY000" )
	{
	}

	virtual ~BinaryTypeUsedInExpressionException( void ) { }
};


class BtreeInconsistentException : public CqlException
{
public :
	BtreeInconsistentException( const NC * const filename, const NI linenumber )
		: CqlException( "Btree inconsistent", EC_BTREE_INCONSISTENT, filename, linenumber, "HY000" )
	{
	}

	virtual ~BtreeInconsistentException( void ) { }
};


class BufferManagementException : public CqlException
{
public :
	BufferManagementException( const NC * const fname, const NI line, const NI _osError= 0 )
		: CqlException( "Cache buffer management error.", EC_BUFFER_MANAGEMENT_FAILURE, fname, line, "HY000", _osError)
	{
	}

	virtual ~BufferManagementException( void )
	{
	}
};


class CheckViolationException : public CqlException
{
public :
	CheckViolationException( const NC * const fname, const NI line )
		: CqlException( "Check violation", EC_CHECK_VIOLATION, fname, line, "HY000" )
	{
	}

	virtual ~CheckViolationException( void ) { }
};


class ClibraryException : public CqlException
{
public :
	ClibraryException( const NC * const filename, const NI linenumber, const NI _osError = 0 )
		: CqlException( "C library call failed", EC_C_LIBRARY_CALL_FAILED, filename, linenumber, "HY000", _osError ) { }
	virtual ~ClibraryException( void ) { }
};


class ClibFileSystemException : public CqlException
{
protected :

	CqlString fileSystemError_;

public :

	ClibFileSystemException( const NC * const fname, const NI line, const NI _osError= 0 )
		: CqlException( "C library file system error", EC_CLIB_FILE_SYSTEM, fname, line, "HY000", _osError)
	{
	}
	virtual ~ClibFileSystemException( void ) { }

	CqlString fileSystemError( void ) { return fileSystemError_; }
};


class ClibFileSystemDetailException : public ClibFileSystemException
{
protected :

	CqlString fileSystemError_;

public :

	ClibFileSystemDetailException( const CqlString& msg,
								   const CqlString& filename,
								   const NC * const fname,
								   const NI line,
								   const bool good,
								   const bool bad,
								   const bool fail,
								   const NI _osError= 0 )
		: ClibFileSystemException(fname, line, _osError)
	{
#ifdef CQL_CLIB_DEBUGGING
		CqlString s = "Filename:";
		s += filename;
		s += ", ";
		s += (good ? "good=1," : "good=0,");
		s += (bad ? "bad=1," : "bad=0,");
		s += (fail ? "fail=1," : "fail=0,");
		s += " message=";
		s += msg;

		cerr << "Status message:" << s << endl;
#endif

		//  CHECKME  this has to be illegal
		//throw ClibFileSystemException( fname, line, _osError);
	}

	virtual ~ClibFileSystemDetailException( void ) { }

	CqlString fileSystemError( void ) { return fileSystemError_; }
};


class CloseCalledWithPendingTransactionException : public CqlException
{
public :
	CloseCalledWithPendingTransactionException( const NC * const filename, const NI linenumber )
		: CqlException( "Close called with pending transaction", EC_CLOSE_CALLED_WITH_PENDING_TRANSACTION, filename, linenumber, "HY000" )
	{
	}

	virtual ~CloseCalledWithPendingTransactionException( void ) { }
};


class ColumnNotFoundException : public CqlException
{
public :
	ColumnNotFoundException( const NC * const filename, const NI line )
		: CqlException( "Column not found", EC_COLUMN_NOT_FOUND, filename, line, "HY000" )
	{
	}

	virtual ~ColumnNotFoundException( void ) { }
};


class CommunicationsException : public CqlException
{
public :
	CommunicationsException( const NC * const fname, const NI line, const NI _osError)
		: CqlException( "Communication failure", EC_COMMUNICATION_FAILURE, fname, line, "HY000", _osError)
	{
	}
	virtual ~CommunicationsException( void )
	{
	}
};


class ConcurrencyException : public CqlException
{
public :
	ConcurrencyException( const NC * const filename, const NI linenumber )
		: CqlException( "Concurrency error occurred", EC_CONCURRENCY, filename, linenumber, "HY000" ) { }
	virtual ~ConcurrencyException( void ) { }
};


class ConversionException : public CqlException
{
public :
	ConversionException( const NC * const fname, const NI line )
		: CqlException( "Conversion failure", EC_CONVERSION_FAILURE, fname, line, "HY000" )
	{
	}
	virtual ~ConversionException( void )
	{
	}
};


class CreateSequenceException : public CqlException
{

public :

	CreateSequenceException( const NC * const fname, const NI line )
		: CqlException( "Create sequence error", EC_CREATE_SEQUENCE, fname, line, "HY000" )
	{
	}

	virtual ~CreateSequenceException( void )
	{
	}

	CqlString detailedErrorText( void )
	{
		return "A create operation occured out of sequence.";
	}
};


class CursorNotFoundException : public CqlException
{
public :
	CursorNotFoundException( const NC * const filename, const NI linenumber )
		: CqlException( "Cusor name not found", EC_CURSOR_NAME_NOT_FOUND, filename, linenumber, "HY000" ) { }
	virtual ~CursorNotFoundException( void ) { }
};


class CursorOperationException : public CqlException
{
public :
	CursorOperationException( const NC * const filename, const NI linenumber )
		: CqlException( "Cursor operation failed", EC_CURSOR_OPERATION_FAILURE, filename, linenumber, "HY000" ) { }

	virtual ~CursorOperationException( void ) { }
};


class CursorStateException : public CqlException
{
public :
	CursorStateException( const NC * const fname, const NI line )
		: CqlException( "Cursor state error", EC_CURSOR_STATE, fname, line, "HY000" )
	{
	}
	
	virtual ~CursorStateException( void )
	{
	}

	CqlString detailedErrorText( void )
	{
		return "A cursor operation was called and the cursor state was invalid.";
	}
};


class DictionaryException : public CqlException
{
public :

	DictionaryException( const NC * const fname, const NI line )
		: CqlException( "Dictionary exception", EC_DICTIONARY_ERROR, fname, line, "HY000" )
	{
	}

	virtual ~DictionaryException( void )
	{
	}
};


class DictionaryInconsistentException : public CqlException
{
public :
	DictionaryInconsistentException( const NC * const filename, const NI linenumber )
		: CqlException( "Corrupted dictionary!!!", EC_CORRUPTED_DICTIONARY, filename, linenumber, "HY000" ) { }
	virtual ~DictionaryInconsistentException( void ) { }
};


class DictionaryUpdateException : public CqlException
{
public :
	DictionaryUpdateException( const NC * const filename, const NI linenumber )
		: CqlException( "Dictionary update failed", EC_DICTIONARY_UPDATE_FAILURE, filename, linenumber, "HY000" ) { }
	virtual ~DictionaryUpdateException( void ) { }
};


class DuplicateRowException : public CqlException
{
public :
	DuplicateRowException( const NC * const filename, const NI line )
		: CqlException( "Duplicate row error", EC_DUPLICATE_ROW, filename, line, "HY000" )
	{
	}

	virtual ~DuplicateRowException( void ) { }
};


class EofException : public CqlException
{
public :
	EofException( const NC * const filename, const NI line )
		: CqlException( "End of file", EC_EOF, filename, line, "HY000" )
	{
	}

	virtual ~EofException( void ) { }
};


class ExpressionInconsistencyException : public CqlException
{
public :
	ExpressionInconsistencyException( const NC * const filename, const NI line )
		: CqlException( "Expression inconsistency", EC_EXPRESSION_INCONSISTENCY, filename, line, "HY000" )
	{
	}

	virtual ~ExpressionInconsistencyException( void ) { }
};


class FilenameCreationException : public CqlException
{
public :
	FilenameCreationException( const NC * const filename, const NI line )
		: CqlException( "Could not create unique file name", EC_FILENAME_CREATION_FAILURE, filename, line, "HY000" )
	{
	}

	virtual ~FilenameCreationException( void ) { }
};


class FileNotFoundException : public CqlException
{
public :
	FileNotFoundException( const NC * const filename, const NI linenumber, NI errorNumber )
		: CqlException( "File not found", EC_FILE_NOT_FOUND, filename, linenumber, "HY000", errorNumber ) { }
	virtual ~FileNotFoundException( void ) { }
};


class FileSystemException : public CqlException
{
public :
	FileSystemException( const NC * const fname, const NI line )
		: CqlException( "ISAM level file system exception", EC_FILE_SYSTEM, fname, line, "HY000" )
	{
	}
	virtual ~FileSystemException( void )
	{
	}
};


class ForeignKeyCreateException : public CqlException
{
public :
	ForeignKeyCreateException( const NC * const filename, const NI line )
		: CqlException( "Foreign key create failed", EC_FOREIGN_KEY_CREATE_FAILURE, filename, line, "HY000" )
	{
	}

	virtual ~ForeignKeyCreateException( void ) { }
};


class GroupBySelectViolation : public CqlException
{
public :
	GroupBySelectViolation( const NC * const filename, const NI line )
		: CqlException( "Column in select list is illegal for GROUP BY", EC_GROUP_BY_SELECT_VIOLATION, filename, line, "HY000" ) { }
	virtual ~GroupBySelectViolation( void ) { }
};


class IllegalOperationException : public CqlException
{
public :

	IllegalOperationException( const NC * const fname, const NI line )
		: CqlException( "Illegal operation for type", EC_ILLEGAL_OPERATION, fname, line, "HY000" )
	{
	}

	virtual ~IllegalOperationException( void ) { }
};


class IllegalOperationForViewException : public CqlException
{
public :
	IllegalOperationForViewException( const NC * const filename, const NI linenumber )
		: CqlException( "An operation was requested which is legal for a base table but not for a view", EC_ILLEGAL_OPERATION_FOR_VIEW, filename, linenumber, "HY000" ) { }
	virtual ~IllegalOperationForViewException( void ) { }
};


class IndexAccessException : public CqlException
{
public :
	IndexAccessException( const NC * const filename, const NI linenumber )
		: CqlException( "Index access error", EC_INDEX_ACCESS, filename, linenumber, "HY000" )
	{
	}

	virtual ~IndexAccessException( void ) { }
};


class IndexNotFoundException : public CqlException
{
public :
	IndexNotFoundException( const NC * const filename, const NI linenumber )
		: CqlException( "Index not found", EC_INDEX_NOT_FOUND, filename, linenumber, "HY000" ) { }
	virtual ~IndexNotFoundException( void ) { }
};


class IntegrityViolationException : public CqlException
{
public :
	IntegrityViolationException( const NC * const fname, const NI line )
		: CqlException( "Integrity violation", EC_INTEGRITY_VIOLATION, fname, line, "HY000" )
	{
	}

	virtual ~IntegrityViolationException( void ) { }
};


class InternalErrorException : public CqlException
{
public :

	InternalErrorException( const NC * const  fname, const NI line )
		:  CqlException( "Unexpected internal error", EC_INTERNAL_ERROR, fname, line, "HY000" )
	{
	}

	virtual ~InternalErrorException( void ) { }
};


class InvalidConstructorException : public CqlException
{
public :
	InvalidConstructorException( const NC * const filename, const NI linenumber )
		: CqlException( "Type cannot be constructed with input supplied", EC_INVALID_CONSTRUCTOR, filename, linenumber, "HY000" ) { }
	virtual ~InvalidConstructorException( void ) { }
};


class IllegalTypeConversionException : public CqlException
{
public :

	IllegalTypeConversionException( const NC * const fname, const NI line )
		:  CqlException( "Illegal type conversion", EC_ILLEGAL_TYPE_CONVERSION, fname, line, "HY000" )
	{
	}

	virtual ~IllegalTypeConversionException( void ) { }
};


class IncompatibleTypesException : public CqlException
{
public :
	IncompatibleTypesException( const NC * const fname, const NI line )
		: CqlException( "Incompatible types in expression", EC_INCOMPATIBLE_TYPES, fname, line, "HY000" )
	{
	}

	virtual ~IncompatibleTypesException( void ) { }
};


class InsertValuesMismatchException : public CqlException
{
public :
	InsertValuesMismatchException( const NC * const filename, const NI linenumber )
		: CqlException( "Insert value type mismatch", EC_INSERT_VALUES_MISMATCH, filename, linenumber, "HY000" ) { }
	virtual ~InsertValuesMismatchException( void ) { }
};


class InvalidJoinRelationshipsException : public CqlException
{
public :
	InvalidJoinRelationshipsException( const NC * const filename, const NI linenumber )
		: CqlException( "Recursive or unsatisfiable join conditions", EC_INVALID_JOINT_RELATIONSHIP, filename, linenumber, "HY000" ) { }
	virtual ~InvalidJoinRelationshipsException( void ) { }
};


class InvalidLengthInStringFunctionException : public CqlException
{
public :
	InvalidLengthInStringFunctionException( const NC * const filename, const NI linenumber )
		: CqlException( "Invalid length in string function", EC_INVALID_LENGTH_IN_STRING_FUNCTION, filename, linenumber, "HY000" ) { }
	virtual ~InvalidLengthInStringFunctionException( void ) { }
};


class InvalidTypeCombinationException : public CqlException
{
public :
	InvalidTypeCombinationException( const NC * const filename, const NI linenumber )
		: CqlException( "Incompatible type combination", EC_INVALID_TYPE_COMBINATION, filename, linenumber, "HY000" )
	{
	}

	virtual ~InvalidTypeCombinationException( void ) { }
};


class InvalidParameterException : public CqlException
{
public :

	InvalidParameterException( const NC * const fname, const NI line )
		:	CqlException( "Illegal parameter value", EC_INVALID_PARAMETER_VALUE, fname, line, "HY000" )
	{
	}

	virtual ~InvalidParameterException( void ) { }
};


class IsamAccessException : public CqlException
{
public :
	IsamAccessException( const NC * const fileName, const NI line )
		: CqlException( "Isam access error", EC_ISAM_ACCESS_FAILURE, fileName, line, "HY000" )
	{
	}

	virtual ~IsamAccessException( void ) { }
};


class IsamOptimizationException : public CqlException
{
public :
	IsamOptimizationException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "Optimization exception", EC_ISAM_OPTIMIZATION_ERROR, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~IsamOptimizationException( void )
	{
	}

	CqlString detailedErrorText( void )
	{
		return "An unexpected error occured during Isam access optimization.";
	}
};


class KeyNotFoundException : public CqlException
{
public :
	KeyNotFoundException( const NC * const filename, const NI line )
		: CqlException( "Key not found", EC_KEY_NOT_FOUND, filename, line, "HY000" )
	{
	}

	virtual ~KeyNotFoundException( void ) { }
};


class LengthExceededException : public CqlException
{
public :

	LengthExceededException( const NC * const fname, const NI line )
		:	CqlException( "Maximum length exceeded", EC_LENGTH_EXCEEDED, fname, line, "HY000" )
	{
	}

	virtual ~LengthExceededException( void ) { }
};


class LengthMismatchException : public CqlException
{
public :

	LengthMismatchException( const NC * const fname, const NI line )
		:	CqlException( "Maximum length exceeded", EC_LENGTH_MISMATCH, fname, line, "HY000" )
	{
	}

	virtual ~LengthMismatchException( void ) { }
};


class LengthNotSetException : public CqlException
{
public :

	LengthNotSetException( const NC * const fname, const NI line )
		:	CqlException( "Maximum length exceeded", EC_LENGTH_NOT_SET, fname, line, "HY000" )
	{
	}

	virtual ~LengthNotSetException( void ) { }
};


class MemoryAllocationException : public CqlException
{
public :

	MemoryAllocationException( const char * const fileName, const NI _lineNumber, const NI _osError= 0 )
		: CqlException( "Memory allocation failure", EC_MEMORY_ALLOCATION_FAILURE, fileName, _lineNumber, "HY013", _osError)
	{
	}

	virtual ~MemoryAllocationException( void )
	{
	}
};


class MemoryIndexException : public CqlException
{
public :
	MemoryIndexException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "Memory index error", EC_MEMORY_INDEX_FAILURE, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~MemoryIndexException( void )
	{
	}
};


class NoCurrentKeyException : public CqlException
{

public :

	NoCurrentKeyException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "No current key", EC_NO_CURRENT_KEY, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~NoCurrentKeyException( void )
	{
	}

	CqlString detailedErrorText( void )
	{
		return "A requested operation uses the current key, but there is no current key.";
	}
};


class NumericOperationOnBLOBDataException : public CqlException
{
public :
	NumericOperationOnBLOBDataException( const NC * const filename, const NI linenumber )
		: CqlException( "Numeric operation requested for binary data", EC_NUMERIC_OPERATION_ON_BINARY_DATA, filename, linenumber, "HY000" ) { }
	virtual ~NumericOperationOnBLOBDataException( void ) { }
};


class NumericOperationOnCharacterDataException : public CqlException
{
public :
	NumericOperationOnCharacterDataException( const NC * const filename, const NI linenumber )
		: CqlException( "Numeric operation requested for character data", EC_NUMERIC_OPERATION_ON_CHARACTER_DATA, filename, linenumber, "HY000" ) { }
	virtual ~NumericOperationOnCharacterDataException( void ) { }
};


class NumericOperationOnLogicalDataException : public CqlException
{
public :
	NumericOperationOnLogicalDataException( const NC * const filename, const NI linenumber )
		: CqlException( "Numeric operation requested for logical data", EC_NUMERIC_OPERATION_ON_LOGICAL_DATA, filename, linenumber, "HY000" ) { }
	virtual ~NumericOperationOnLogicalDataException( void ) { }
};


class NumericOperationOnTimestampDataException : public CqlException
{
public :
	NumericOperationOnTimestampDataException( const NC * const filename, const NI linenumber )
		: CqlException( "Numeric operation requested for timestamp data", EC_NUMERIC_OPERATION_ON_TIMESTAMP_DATA, filename, linenumber, "HY000" ) { }
	virtual ~NumericOperationOnTimestampDataException( void ) { }
};


class NoCurrentPositionException : public CqlException
{

public :

	NoCurrentPositionException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "No current key", EC_NO_CURRENT_POSITION, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~NoCurrentPositionException( void )
	{
	}

	CqlString detailedErrorText( void )
	{
		return "A requested operation uses the current key, but there is no current key.";
	}
};


class NoDataException : public CqlException
{
public :
	NoDataException( const NC * const filename, const NI linenumber )
		: CqlException( "No data found", EC_NO_DATA, filename, linenumber, "HY000" ) { }
	virtual ~NoDataException( void ) { }
};


class NotImplementedException : public CqlException
{
public :
	NotImplementedException( const NC * const filename, const NI linenumber )
		: CqlException( "Not yet implemented", EC_NOT_IMPLEMENTED, filename, linenumber, "HY000" ) { }
	virtual ~NotImplementedException( void ) { }
};


class NoTransactionException : public CqlException
{
public :
	NoTransactionException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "No active transaction", EC_NO_TRANSACTION, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~NoTransactionException( void )
	{
	}

	CqlString detailedErrorText( void )
	{
		return "An requested operation uses the current transaction, but there is no current transaction.";
	}
};


class PositionedOperationWithMultipleTablesException : public CqlException
{
public :
	PositionedOperationWithMultipleTablesException( const NC * const filename, const NI linenumber )
		: CqlException( "Positioned operation attempted for more than one base table", EC_POSITIONED_OPERATION_WITH_MULTIPLE_TABLES, filename, linenumber, "HY000" ) { }
	virtual ~PositionedOperationWithMultipleTablesException( void ) { }
};


class PredicateTreeInconsistentException : public CqlException
{
public :
	PredicateTreeInconsistentException( const NC * const filename, const NI linenumber )
		: CqlException( "Predicate tree corrupted", EC_PREDICATE_TREE_INCONSISTENT, filename, linenumber, 0 ) { }
	virtual ~PredicateTreeInconsistentException( void ) { }
};


class PrivilegeViolationException : public CqlException
{
public :
	PrivilegeViolationException( const NC * const filename, const NI linenumber )
		: CqlException( "User does not have privileges for requested operation", EC_PRIVILEGE_VIOLATION, filename, linenumber, "HY000" ) { }
	virtual ~PrivilegeViolationException( void ) { }
};


class ReportGenerationException : public CqlException
{
public :
	ReportGenerationException( const NC * const filename, const NI linenumber )
		: CqlException( "Report generation error", EC_REPORT_GENERATION, filename, linenumber, "HY000" ) { }
	virtual ~ReportGenerationException( void ) { }
};


class SelectEvaluationException : public CqlException
{
public :
	SelectEvaluationException( const NC * const filename, const NI linenumber )
		: CqlException( "Error evaluating SELECT", EC_SELECT_EVALUATION, filename, linenumber, "HY000" ) { }
	virtual ~SelectEvaluationException( void ) { }
};


class SizeConversionException : public CqlException
{
public :

	SizeConversionException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "Conversion of differently sized objects failed", EC_CONVERSION_SIZE_ERROR, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~SizeConversionException( void )
	{
	}
};


class SqlDropRestrictException : public CqlException
{
public :
	SqlDropRestrictException( const NC * const filename, const NI linenumber )
		: CqlException( "Table has the DROP RESTRICT attribute", EC_DROP_RESTRICT_VIOLATION, filename, linenumber, "HY000" ) { }
	virtual ~SqlDropRestrictException( void ) { }
};


class StackOverflowException : public CqlException
{
public :
	StackOverflowException( const NC * const filename, const NI linenumber )
		: CqlException( "Stack underflow", EC_STACK_OVERFLOW, filename, linenumber, "HY000" ) { }
	virtual ~StackOverflowException( void ) { }
};


class StackUnderflowException : public CqlException
{
public :
	StackUnderflowException( const NC * const filename, const NI linenumber )
		: CqlException( "Stack underflow", EC_STACK_UNDERFLOW, filename, linenumber, "HY000" ) { }
	virtual ~StackUnderflowException( void ) { }
};


class StringRepresentationRequestedForBinaryDataException : public CqlException
{
public :
	StringRepresentationRequestedForBinaryDataException( const NC * const filename, const NI linenumber )
		: CqlException( "String representation requested for binary data", EC_STRING_REPRESENTATION_REQUESTED_FOR_BINARY_DATA, filename, linenumber, "HY000" ) { }
	virtual ~StringRepresentationRequestedForBinaryDataException( void ) { }
};


class SubqueryMustReturnExactlyOneRowException : public CqlException
{
public :
	SubqueryMustReturnExactlyOneRowException( const NC *const fileName, const NI _lineNumber )
		: CqlException( "Subquery must return exactly one row", EC_SUBQUERY_MUST_RETURN_EXACTLY_ONE_ROW, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~SubqueryMustReturnExactlyOneRowException( void ) { }
};


class SyntaxErrorException : public CqlException
{
public :
	SyntaxErrorException( const NC * const filename, const NI linenumber )
		: CqlException( "Syntax error", EC_SYNTAX_ERROR, filename, linenumber, "HY000" ) { }
	virtual ~SyntaxErrorException( void ) { }
};


class SystemConfigurationException : public CqlException
{
public :
	SystemConfigurationException( const NC * const fileName, const NI _lineNumber, const NI _osError= 0 )
		: CqlException( "System configuration error.", EC_SYSTEM_CONFIGURATION_ERROR, fileName, _lineNumber, "HY000", _osError)
	{
	}

	virtual ~SystemConfigurationException( void )
	{
	}
};


class TableNotFoundException : public CqlException
{
public :
	TableNotFoundException( const NC * const filename, const NI line )
		: CqlException( "Table not found", EC_TABLE_NOT_FOUND, filename, line, "HY000" )
	{
	}

	virtual ~TableNotFoundException( void ) { }
};


class TemporaryFileException : public CqlException
{
public :
	TemporaryFileException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "Temporary file error", EC_TEMPORARY_FILE_ERROR, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~TemporaryFileException( void ) { }
};


class TransactionException : public CqlException
{
public :

	TransactionException( const NC * const msg, const ExceptionCodes _eCode, const NC * const fileName, const NI _lineNumber, const NI _osError= 0 )
		: CqlException( msg, _eCode, fileName, _lineNumber, "HY000", _osError)
	{
	}

	TransactionException( const NC * const filename, const NI linenumber )
		: CqlException( "Transaction processing error", EC_TRANSACTION_ERROR, filename, linenumber, "HY000" )
	{
	}

	virtual ~TransactionException( void ) { }
};


class TypeConversionException : public CqlException
{
public :

	TypeConversionException( const NC * const fname, const NI line )
		:  CqlException( " type conversion", EC_TYPE_CONVERSION, fname, line, "HY000" )
	{
	}

	virtual ~TypeConversionException( void ) { }
};


class TypesNotAssignmentCompatibleException : public CqlException
{
public :
	TypesNotAssignmentCompatibleException( const NC * const filename, const NI linenumber )
		: CqlException( "Types not assignment compatible", EC_TYPES_NOT_ASSIGNMENT_COMPATIBLE, filename, linenumber, "HY000" ) { }
	virtual ~TypesNotAssignmentCompatibleException( void ) { }
};


class UnsupportedFeatureException : public CqlException
{
public :
	UnsupportedFeatureException( const NC * const filename, const NI linenumber )
		: CqlException( "Unsupported feature exception", EC_UNSUPPORTED_FEATURE, filename, linenumber, "HY000" )
	{
	}

	virtual ~UnsupportedFeatureException( void ) { }
};


class UserLimitExceededException : public CqlException
{
public:
	UserLimitExceededException( const NC * const filename, const NI linenumber )
		: CqlException( "Server connection limit exceeded", EC_USER_LIMIT_EXCEEDED, filename, linenumber, "HY000" ) { }
	virtual ~UserLimitExceededException( void ) { }
};


class TableAccessException : public CqlException
{
public :
	TableAccessException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "User file access error", EC_TABLE_ACCESS_FAILURE, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~TableAccessException( void ) { }
};


class UserTableCreateException : public CqlException
{
public :
	UserTableCreateException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "User file access error", EC_USER_TABLE_CREATE_FAILURE, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~UserTableCreateException( void ) { }
};


class UserTableUpdateException : public CqlException
{
public :
	UserTableUpdateException( const NC * const filename, const NI linenumber )
		: CqlException( "Error updating user table", EC_USER_TABLE_UPDATE_FAILURE, filename, linenumber, "HY000" ) { }
	virtual ~UserTableUpdateException( void ) { }
};


class WildcardCompareException : public CqlException
{
public :

	WildcardCompareException( const NC * const fileName, const NI _lineNumber )
		: CqlException( "Wild card compare internal error", EC_INTERNAL_ERROR, fileName, _lineNumber, "HY000" )
	{
	}

	virtual ~WildcardCompareException( void ) { }
};


std::ostream& operator << ( std::ostream&, CqlException& );


#endif  //  __CqlException_h
