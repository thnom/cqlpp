//
//  Copyright (C) 1994-2003  Seth Kurtzberg
//
//
%token SQL_ABS
%token ACOS
%token AMPERSAND
%token SQL_ABSOLUTE
%token ACOS
%token ADA
%token ADD
%token ADD_DAYS
%token ADD_HOURS
%token ADD_MINUTES
%token ADD_MONTHS
%token ADD_SECONDS
%token ADD_YEARS
%token ALL
%token ALLOCATE
%token ALTER
%token AND
%token ANY
%token ARE
%token ARITHMETIC_MINUS
%token ARITHMETIC_PLUS
%token AS
%token ASIN
%token ASC
%token ASCII
%token ASSERTION
%token ASTERISK
%token AT
%token ATAN
%token ATAN2
%token AUTHORIZATION
%token AVG
%token BEFORE
%token SQL_BEGIN
%token BETWEEN
%token BIGINT
%token BINARY
%token BIT
%token BIT_LENGTH
%token BREAK
%token BY
%token CASCADE
%token CASCADED
%token CASE
%token CAST
%token CATALOG
%token CEILING
%token CENTER
%token SQL_CHAR
%token CHAR_LENGTH
%token CHARACTER_STRING_LITERAL
%token CHECK
%token CLOSE
%token COALESCE
%token COBOL
%token COLLATE
%token COLLATION
%token COLON
%token COLUMN
%token COMMA
%token COMMIT
%token COMPUTE
%token CONCAT
%token CONNECT
%token CONNECTION
%token CONSTRAINT
%token CONSTRAINTS
%token CONTINUE
%token CONVERT
%token CORRESPONDING
%token COS
%token COT
%token COUNT
%token CREATE
%token CURDATE
%token CURRENT
%token CURRENT_DATE
%token CURRENT_TIME
%token CURRENT_TIMESTAMP
%token CURTIME
%token CURSOR
%token DATABASE
%token SQL_DATE
%token DATE_FORMAT
%token DATE_REMAINDER
%token DATE_VALUE
%token DAY
%token DAYOFMONTH
%token DAYOFWEEK
%token DAYOFYEAR
%token DAYS_BETWEEN
%token DEALLOCATE
%token DEC
%token DECLARE
%token DEFAULT
%token DEFERRABLE
%token DEFERRED
%token SQL_DELETE
%token DESC
%token DESCRIBE
%token DESCRIPTOR
%token DIAGNOSTICS
%token DICTIONARY
%token DIRECTORY
%token DISCONNECT
%token DISPLACEMENT
%token DISTINCT
%token DOLLAR_SIGN
%token DOMAIN_TOKEN
%token DOT
%token SQL_DOUBLE
%token DOUBLE_QUOTED_STRING
%token DROP
%token ELSE
%token END
%token END_EXEC
%token EQUAL
%token ESCAPE
%token EXCEPT
%token SQL_EXCEPTION
%token EXEC
%token EXECUTE
%token EXISTS
%token EXP
%token EXPONENT
%token EXTERNAL
%token EXTRACT
%token SQL_FALSE
%token FETCH
%token FIRST
%token SQL_FLOAT
%token FLOOR
%token FN
%token FOR
%token FOREIGN
%token FORTRAN
%token FOUND
%token FOUR_DIGITS
%token FROM
%token FULL
%token GET
%token GLOBAL
%token GO
%token GOTO
%token GRANT
%token GREATER_THAN
%token GREATER_OR_EQUAL
%token GROUP
%token HAVING
%token HOUR
%token HOURS_BETWEEN
%token IDENTITY
%token IFNULL
%token SQL_IGNORE
%token IMMEDIATE
%token SQL_IN
%token INCLUDE
%token INDEX
%token INDICATOR
%token INITIALLY
%token INNER
%token INPUT
%token INSENSITIVE
%token INSERT
%token INTEGER
%token INTERSECT
%token INTERVAL
%token INTO
%token IS
%token ISOLATION
%token JOIN
%token JUSTIFY
%token KEY
%token LANGUAGE
%token LAST
%token LCASE
%token LEFT
%token LEFTPAREN
%token LENGTH
%token LESS_OR_EQUAL
%token LESS_THAN
%token LEVEL
%token LIKE
%token LINE_WIDTH
%token LOCAL
%token LOCATE
%token LOG
%token SQL_LONG
%token LOWER
%token LTRIM
%token LTRIP
%token MATCH
%token SQL_MAX
%token MICROSOFT
%token SQL_MIN
%token MINUS
%token MINUTE
%token MINUTES_BETWEEN
%token MOD
%token MODIFY
%token MODULE
%token MONTH
%token MONTHS_BETWEEN
%token MUMPS
%token NAMES
%token NATIONAL
%token NCHAR
%token NEXT
%token NODUP
%token NONE
%token NOT
%token NOT_EQUAL
%token NOW
%token SQL_NULL
%token NULLIF
%token NUMERIC
%token OCTET_LENGTH
%token ODBC
%token OF
%token SQL_OFF
%token SQL_ON
%token ONLY
%token OPEN
%token OPTION
%token OR
%token ORDER
%token OUTER
%token OUTPUT
%token OVERLAPS
%token PAGE
%token PARTIAL
%token SQL_PASCAL
%token PERSISTENT
%token CQL_PI
%token PLI
%token POSITION
%token PRECISION
%token PREPARE
%token PRESERVE
%token PRIMARY
%token PRIOR
%token PRIVILEGES
%token PROCEDURE
%token PRODUCT
%token PUBLIC
%token QUARTER
%token QUESTION_MARK
%token QUIT
%token RAND
%token READ_ONLY
%token REAL
%token REFERENCES
%token REPEAT
%token REPLACE
%token RESTRICT
%token REVOKE
%token RIGHT
%token RIGHTPAREN
%token ROLLBACK
%token ROWS
%token RPAD
%token RTRIM
%token SCHEMA
%token SCREEN_WIDTH
%token SCROLL
%token SECOND
%token SECONDS_BETWEEN
%token SELECT
%token SEMICOLON
%token SEQUENCE
%token SETOPT
%token SET
%token SHOWOPT
%token SIGN
%token SIGNED_INTEGER
%token SIN
%token SINGLE_QUOTE
%token SQL_SIZE
%token SLASH
%token SMALLINT
%token SOME
%token SPACE
%token SQL
%token SQL_TRUE
%token SQLCA
%token SQLCODE
%token SQLERROR
%token SQLSTATE
%token SQLWARNING
%token SQRT
%token STDEV
%token SUBSTRING
%token SUM
%token SYSDATE
%token SYSDATE_FORMAT
%token SYSTEM
%token TABLE
%token TAN
%token TEMPORARY
%token THEN
%token THREE_DIGITS
%token TIME
%token TIMESTAMP
%token TIMEZONE_HOUR
%token TIMEZONE_MINUTE
%token TINYINT
%token TITLE
%token TO
%token TO_CHAR
%token TO_DATE
%token TRANSACTION
%token TRANSLATE
%token TRANSLATION
%token TRUNCATE
%token GENERAL_TITLE
%token TWO_DIGITS
%token UCASE
%token UNION
%token UNIQUE
%token SQL_UNKNOWN
%token UNSIGNED_INTEGER
%token UPDATE
%token UPPER
%token USAGE
%token USER
%token USER_DEFINED_NAME
%token USING
%token VALUE
%token VALUES
%token VARBINARY
%token VARCHAR
%token VARYING
%token VENDOR
%token VIEW
%token WEEK
%token WHEN
%token WHENEVER
%token WHERE
%token WHERE_CURRENT_OF
%token WITH
%token WORD_WRAPPED
%token WORK
%token WRAPPED
%token YEAR
%token YEARS_BETWEEN
%{
#define __CQL_PARSER_GLOBALS
#include "CqlSqlInclude.h"
	int yylex( SqlHandle* );
	void yyunput( int, char* );
	extern char *yytext;

#define YYLEX yylex( dbsql )
	%}
%union {
	char parserUserName[ CQL_MAXIMUM_PARSER_NAME_LENGTH ];
	int integerValue;
	SetComparisonConstants::ComparisonOperators comparisonOp;
	SetComparisonConstants::ComparisonModifiers comparisonMod;
	ParserConstants::LogicalOperators logicalOp;
	ParserConstants::AggregateFunctions aggregate;
	struct DateLiteral dateLiteral_;
	pUIWithLeadingZeros uiwlz;
}
%type <comparisonMod> AllOrAny
%type <logicalOp> AND
%type <aggregate> AggregateFunction
%type <aggregate> AVG
%type <comparisonOp> ComparisonOperator
%type <integerValue> Length
%type <aggregate> SQL_MAX
%type <aggregate> SQL_MIN
%type <logicalOp> OR
%type <integerValue> SIGNED_INTEGER
%type <aggregate> SUM
%type <uiwlz> UnsignedInteger
%type <parserUserName> USER_DEFINED_NAME
%type <dateLiteral_> DATE_VALUE
%%
Statement :
BeginScriptStatement
| AlterTableStatement {
	try
	{
		dbsql->parse()->alterTable();
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}
| CreateIndexStatement
{
	try
	{
		dbsql->parse()->createIndex();
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}

| CreateSchemaStatement
{
	YYACCEPT;
}

| CreateTableStatement
{
	try
	{
		dbsql->parse()->createTable();
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}

| CreateViewStatement
{
	try
	{
		dbsql->parse()->createView();
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}
| DeleteStatement
| DropIndexStatement
{
	try
	{
		dbsql->parse()->dropIndex();
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}
| DropTableStatement
{
	try
	{
		dbsql->parse()->dropTable();
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}
| DropViewStatement
{
	try
	{
		dbsql->parse()->dropView();
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}
| GrantStatement
{
	try
	{
		dbsql->parse()->grant( dbsql->parse()->grantPrivileges(), dbsql->parse()->grantUsers() );
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}
| InsertStatement
{
	try
	{
		dbsql->parse()->insert();
	}
	catch( ... )
	{
		dbsql->parse()->cleanup();
		throw;
	}
	YYACCEPT;
}
| RevokeStatement
{
	try
	{
		dbsql->parse()->revoke( dbsql->parse()->grantPrivileges(), dbsql->parse()->grantUsers() );
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}
| SelectStatement
{
	if( dbsql->parse()->declaringCursor() )
	{
		try
		{
			dbsql->parse()->declareCursor();
		}
		catch( ... )
		{
			dbsql->parse()->cleanup();
			throw;
		}
		YYACCEPT;
	}
	else
	{
		try
		{
			dbsql->parse()->select();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			dbsql->parse()->cleanup();
			YYERROR;
		}
		YYACCEPT;
	}
}
| SetoptStatement
{
	try
	{
		dbsql->parse()->setOption( Parser::OPTION_DIRECTORY );
	}
	catch( ... )
	{
		dbsql->parse()->cleanup();
		throw;
	}
	YYACCEPT;
}
| ShowoptStatement
{
	try
	{
		dbsql->parse()->showOption( Parser::OPTION_DIRECTORY );
	}
	catch( ... )
	{
		dbsql->parse()->cleanup();
		throw;
	}
	YYACCEPT;
}
| UpdateStatement 
| InterpreterStatement
| NullStatement
| EmptyStatement
;

NullStatement :
SEMICOLON
{
#if 0
	std::cout << "Invalid or empty statement\nSQL> ";
	YYERROR;
#endif
	YYACCEPT;
}
;

EmptyStatement :
{
#if 0
	std::cout << "Invalid or empty statement\nSQL> ";
	YYERROR;
#endif
	YYACCEPT;
}
;

BeginScriptStatement :
AMPERSAND DOUBLE_QUOTED_STRING
{
	try
	{
		dbsql->parse()->beginScript( yytext + 1 );
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		dbsql->parse()->cleanup();
		YYERROR;
	}
	YYACCEPT;
}
;
AlterTableStatement :
ALTER TABLE
{
	try
	{
		dbsql->parse()->statementInitialization(); ;
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		YYERROR;
	}
}
AlterTableName
ADD
AlterAddColumnList
;

AlterTableName :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->addTableName( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

AlterAddColumnList :
AlterAddColumn
| LEFTPAREN AlterAddColumnN1 RIGHTPAREN
;

AlterAddColumnN1 :
AlterAddColumn
AlterAddColumnN0
;

AlterAddColumnN0 :
AlterAddColumnN0 COMMA AlterAddColumn
| //  nothing
;

AlterAddColumn :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setAlterColumnName( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	DataType
;

CreateIndexStatement :
CREATE
{
	try
	{
		dbsql->parse()->statementInitialization();
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
		YYERROR;
	}
}
MaybeUnique
INDEX
IndexName
SQL_ON
CreateIndexTableName
LEFTPAREN
IndexColumnIdentifierN1
RIGHTPAREN
;

CreateIndexTableName :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->baseTableName().setStringUpper( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

MaybeUnique :
	UNIQUE
	{
		try
		{
			dbsql->parse()->setCreatingUniqueIndex();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| //  nothing
;

IndexColumnIdentifierN1 :
	IndexColumnIdentifier IndexColumnIdentifierN0
;

IndexColumnIdentifierN0 :
	IndexColumnIdentifierN0 COMMA IndexColumnIdentifier
	| //  nothing
;

IndexColumnIdentifier :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setIndexColumnIdentifier( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	IndexColumnModifier
;

IndexColumnModifier :
	ASC
	| DESC
	{
		try
		{
			dbsql->parse()->setIndexColumnDescending();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| //  nothing
;

CreateSchemaStatement :
	CREATE SCHEMA AUTHORIZATION USER_DEFINED_NAME
	{
		try
		{
			dbsql->aHandle().userName() = CqlString( $4 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

CreateTableStatement :
	CREATE TABLE
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	CreateTableBaseTableName LEFTPAREN ColumnElementN1 RIGHTPAREN
;

CreateTableBaseTableName :
	USER_DEFINED_NAME DOT USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->baseTablePrefix().setStringUpper( $1 );
			dbsql->parse()->baseTableName().setStringUpper( $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->baseTableName().setStringUpper( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ColumnElementN1 :
	ColumnElement ColumnElementN0
;

ColumnElementN0 :
	ColumnElementN0 COMMA ColumnElement
	| //  nothing
;

ColumnElement :
	ColumnDefinition
	| TableConstraintDefinition
;

ColumnDefinition :
	CreateColumnIdentifier
	DataType
	DefaultValueClause
	ColumnConstraintClause
;

CreateColumnIdentifier :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->addCreateColumn( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ColumnConstraintClause :
	ColumnConstraintDefinition
	ColumnConstraintDefinitionN0

	| //  nothing
;

DefaultValueClause :
	DEFAULT DefaultValue
	| //  nothing
;

ColumnConstraintDefinitionN0 :
	ColumnConstraintDefinitionN0 ColumnConstraintDefinition
	| //  nothing
;

ColumnConstraintDefinition :
	NOT SQL_NULL
	{
		try
		{
			dbsql->parse()->setColumnNotNull();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| UNIQUE
	{
		try
		{
			dbsql->parse()->setColumnUnique();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| PRIMARY KEY
	{
		try
		{
			dbsql->parse()->setColumnUnique();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| INDEX
	{
		try
		{
			dbsql->parse()->setColumnIndex();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	
	| REFERENCES
	{
		try
		{
			dbsql->parse()->beginForeignKey();
			dbsql->parse()->setReferencingIdentifier( dbsql->parse()->currentCreateColumn()->columnName() );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	ReferencedBaseTableName
	ReferencedColumns
	
	| CHECK
	{
		try
		{
			dbsql->parse()->beginColumnCheckCondition();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN SearchCondition RIGHTPAREN
;

ReferencedBaseTableName :
	USER_DEFINED_NAME DOT USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setReferencedTablePrefix( $1 );
			dbsql->parse()->setReferencedTableName( $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setReferencedTableName( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

DefaultValue :
	DefaultValueLiteral
	{
		try
		{
			dbsql->parse()->setDefaultValue();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	
	| SQL_NULL
	{
		try
		{
			dbsql->parse()->setDefaultValueNull();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER
	{
		try
		{
			dbsql->parse()->setDefaultValueUser();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

DefaultValueLiteral :
	CHARACTER_STRING_LITERAL
	{
		try
		{
			dbsql->parse()->characterDefaultValue( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| DefaultValueNumericLiteral
	| DefaultValueODBCDateTimeExtension
;

DefaultValueNumericLiteral :
	DefaultValueExactNumericLiteral

	| DefaultValueApproximateNumericLiteral
	{
		try
		{
			dbsql->parse()->approximateNumericDefaultValue( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

DefaultValueExactNumericLiteral :
	SIGNED_INTEGER DOT UnsignedInteger
	{
		try
		{
			dbsql->parse()->exactNumericDefaultValue( $1, $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| SIGNED_INTEGER
	{
		try
		{
			dbsql->parse()->exactNumericDefaultValue( $1, Parser::createUiwz( 0 ) );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| UnsignedInteger DOT UnsignedInteger
	{
		try
		{
			dbsql->parse()->exactNumericDefaultValue( $1, $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| UnsignedInteger
	{
		try
		{
			dbsql->parse()->exactNumericDefaultValue( $1, 0 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| UnsignedInteger DOT
	{
		try
		{
			dbsql->parse()->exactNumericDefaultValue( $1, 0 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| DOT UnsignedInteger
	{
		try
		{
			dbsql->parse()->exactNumericDefaultValue( 0, $2 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

DefaultValueApproximateNumericLiteral :
	Mantissa EXPONENT Exponent
;

DefaultValueODBCDateTimeExtension :
	ODBCStdEscInitiator 'd' SINGLE_QUOTE DATE_VALUE SINGLE_QUOTE ODBCStdEscTerminator
	{
		try
		{
			dbsql->parse()->dateDefaultValue( $4 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| ODBCExtEscInitiator 'd' SINGLE_QUOTE DATE_VALUE SINGLE_QUOTE ODBCExtEscTerminator
	{
		try
		{
			dbsql->parse()->dateDefaultValue( $4 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| ODBCStdEscInitiator 't' TimeLiteral ODBCStdEscTerminator
	{
		try
		{
			dbsql->parse()->timeDefaultValue( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| ODBCExtEscInitiator 't' TimeLiteral ODBCExtEscTerminator
	{
		try
		{
			dbsql->parse()->timeDefaultValue( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| ODBCStdEscInitiator 't' 's' TimestampLiteral ODBCStdEscTerminator
	{
		try
		{
			dbsql->parse()->timestampDefaultValue( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| ODBCExtEscInitiator 't' 's' TimestampLiteral ODBCExtEscTerminator
	{
		try
		{
			dbsql->parse()->timestampDefaultValue( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

TableConstraintDefinition :
	FOREIGN KEY
	{
		try
		{
			dbsql->parse()->beginForeignKey();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	ReferencingColumns
	REFERENCES
	ReferencedTableName
	TableReferencedColumns

	| UNIQUE
	{
		try
		{
			dbsql->parse()->beginUniqueKeyGroup();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN TableKeyColumnN1 RIGHTPAREN

	| PRIMARY KEY
	{
		try
		{
			dbsql->parse()->beginPrimaryKeyGroup();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN TableKeyColumnN1 RIGHTPAREN
	
	| INDEX
	{
		try
		{
			dbsql->parse()->beginDuplicateKeyGroup();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN TableKeyColumnN1 RIGHTPAREN

	| CHECK
	{
		try
		{
			dbsql->parse()->beginCheckClause();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN SearchCondition RIGHTPAREN
;

ReferencedTableName :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setReferencedTableName( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

TableKeyColumnN1 :
	TableKeyColumn TableKeyColumnN0
;

TableKeyColumnN0 :
	TableKeyColumnN0 COMMA TableKeyColumn
	| //  nothing
;

TableKeyColumn :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setKeyColumn( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

CreateViewStatement :
	CREATE VIEW
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	ViewedTableName ViewColumnIdentifierN0 AS QuerySpecification
	MaybeWithCheckOption
	SEMICOLON
;

MaybeWithCheckOption :
	WITH CHECK OPTION
	{
		try
		{
			dbsql->parse()->setCheckOption();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	|  //  nothing
;

ViewColumnIdentifierN0 :
	LEFTPAREN ViewColumnIdentifierN1 RIGHTPAREN
	//  empty
;

ViewColumnIdentifierN1 :
	ViewColumnIdentifier ViewColumnIdentifierN0
;

ViewColumnIdentifierN0 :
	ViewColumnIdentifierN0 COMMA ViewColumnIdentifier
	| //  nothing
;

ViewColumnIdentifier :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setViewColumnIdentifier( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

DeleteStatement :
	SQL_DELETE
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	FROM
	{
		try
		{
			dbsql->parse()->clearDoingColumns();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	TableName
	DeleteStatementPart2
;

DeleteStatementPart2 :
	DeleteStatementPositioned
	{
		try
		{
			dbsql->parse()->positionedDelete();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
		YYACCEPT;
	}

	| DeleteStatementSearched SEMICOLON
	{
		try
		{
			dbsql->parse()->searchedDelete();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
		YYACCEPT;
	}
;
	

DeleteStatementPositioned :
	WHERE_CURRENT_OF CursorName
;

DeleteStatementSearched :
	MaybeWhereClause
;

MaybeWhereClause :
	Where SearchCondition
	|  //  nothing
;

Where :
	WHERE
	{
		try
		{
			dbsql->parse()->startWhere();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

DropIndexStatement :
	DROP INDEX
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	IndexName
;

DropTableStatement :
	DROP TABLE
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	DropTableName
	DropModifier
;

DropTableName :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->baseTableName().setStringUpper( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

DropModifier :
	CASCADE
	{
		try
		{
			dbsql->parse()->setCascade();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| RESTRICT
	{
		try
		{
			dbsql->parse()->setRestrict();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| //  nothing
;

DropViewStatement :
	DROP VIEW
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	ViewedTableName DropModifier
;

GrantStatement :
	GRANT
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	GrantPrivilegeList SQL_ON GrantTableName TO GranteeList MaybeWithGrantOption
;

GrantTableName :
	USER_DEFINED_NAME DOT USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setGrantTablePrefix( $1 );
			dbsql->parse()->setGrantTableName( $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setGrantTableName( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

GrantPrivilegeList :
	ALL PRIVILEGES
	{
		try
		{
			dbsql->parse()->grantPrivilegeAll();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| GrantPrivilegeN1
;

GrantPrivilegeN1 :
	GrantPrivilege
	| GrantPrivilege COMMA GrantPrivilegeN1
;

GrantPrivilege :
	SQL_DELETE
	{
		try
		{
			dbsql->parse()->grantPrivilegeDelete();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| INSERT
	{
		try
		{
			dbsql->parse()->grantPrivilegeInsert();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| SELECT
	{
		try
		{
			dbsql->parse()->grantPrivilegeSelect();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| UPDATE
	{
		try
		{
			dbsql->parse()->grantPrivilegeUpdate();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	UpdateColumnList0

	| REFERENCES
	{
		try
		{
			dbsql->parse()->grantPrivilegeReferences();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	ReferenceColumnList0
;

GranteeList :
	PUBLIC
	{
		try
		{
			dbsql->parse()->addGrantee( "PUBLIC" );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| GranteeNameN1
;

GranteeNameN1 :
	GranteeName
	| GranteeName COMMA GranteeNameN1
;

MaybeWithGrantOption :
	WITH GRANT OPTION
	{
		try
		{
			dbsql->parse()->setGrantOption();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	|  //  nothing
;

UpdateColumnList0 :
	//  nothing
	| LEFTPAREN UpdateColumnIdentifierN1 RIGHTPAREN
;

UpdateColumnIdentifierN1 :
	UpdateColumnIdentifier UpdateColumnIdentifierN0
;

UpdateColumnIdentifierN0 :
	UpdateColumnIdentifierN0 COMMA UpdateColumnIdentifier
	| //  nothing
;

UpdateColumnIdentifier :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setUpdateColumnIdentifier( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ReferenceColumnList0 :
	//  nothing
	| LEFTPAREN ReferenceColumnIdentifierN1 RIGHTPAREN
;

ReferenceColumnIdentifierN1 :
	ReferenceColumnIdentifier ReferenceColumnIdentifierN0
;

ReferenceColumnIdentifierN0 :
	ReferenceColumnIdentifierN0 COMMA ReferenceColumnIdentifier
	| //  nothing
;

ReferenceColumnIdentifier :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setReferenceColumnIdentifier( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ColumnIdentifierList0 :
	//  nothing
	| LEFTPAREN InsertColumnIdentifierN1 RIGHTPAREN
;

InsertColumnIdentifierN1 :
	InsertColumnIdentifier InsertColumnIdentifierN0
;

InsertColumnIdentifierN0 :
	InsertColumnIdentifierN0 COMMA InsertColumnIdentifier
	| //  nothing
;

InsertColumnIdentifier :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setInsertColumnIdentifier( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

InsertStatement :
	INSERT INTO
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	InsertTableName ColumnIdentifierList0 InsertValueExpression
;

InsertTableName :
	USER_DEFINED_NAME DOT USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->baseTablePrefix().setStringUpper( $1 );
			dbsql->parse()->addTableName( $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->addTableName( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

InsertValueExpression :
	VALUES LEFTPAREN
	{
		try
		{
			dbsql->parse()->beginColumn();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	InsertValueN1 RIGHTPAREN

	| QuerySpecification
;

InsertValueN1 :
	InsertValue
	InsertValueN0
;

InsertValueN0 :
	InsertValueN0 COMMA
	{
		try
		{
			dbsql->parse()->beginColumn();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	InsertValue
|	//  nothing
;

RevokeStatement :
	REVOKE
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	GrantPrivilegeList SQL_ON TableName FROM GranteeList DropModifier
;

SelectStatement :
	SELECT
	{
		try
		{
			dbsql->parse()->statementInitialization();
			dbsql->parse()->generateSetPush();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	SelectModifier SelectList From TableReferenceList SelectStatementPartTwo
	SEMICOLON
;

From :
	FROM
	{
		try
		{
			dbsql->parse()->clearDoingColumns();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

SelectStatementPartTwo :
	Where SearchCondition SelectAfterWhereClause
	| SelectAfterWhereClause
;

SelectAfterWhereClause :
	FOR UPDATE OF ColumnNameN1

	| GROUP BY GroupByColumnNameN1 SelectAfterGroupBy
	{
		try
		{
			dbsql->parse()->groupBy();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| SelectAfterGroupBy
;

GroupByColumnNameN1 :
	GroupByColumnName
	| GroupByColumnName COMMA GroupByColumnNameN1
;

GroupByColumnName :
	USER_DEFINED_NAME DOT USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->addGroupByColumn( $1, $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->addGroupByColumn( 0, $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

SelectAfterGroupBy :
	Having SearchCondition SelectAfterHaving
	| SelectAfterHaving
;

Having :
	HAVING
	{
		try
		{
			dbsql->parse()->startHaving();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

SelectAfterHaving :
	OrderBy SortSpecificationN1
	| UNION SelectStatement
	| //  nothing
;

OrderBy :
	ORDER BY
	{
		try
		{
			dbsql->parse()->startOrderBy();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

SelectModifier :
	ALL
	| DISTINCT
	{
		try
		{
			dbsql->parse()->selectDistinct();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| //  nothing
;

MaybeGroupByClause :
	GROUP BY GroupByColumnNameN1 SelectAfterGroupBy
	{
		try
		{
			dbsql->parse()->groupBy();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	|  //  nothing
;

ColumnNameN1 :
	ColumnName
	| ColumnName COMMA ColumnNameN1
;

MaybeHavingClause :
	Having SearchCondition
	| //  nothing
;


SetoptStatement :
	SETOPT DIRECTORY DOUBLE_QUOTED_STRING
	{
		try
		{
			char *str = yytext + 1;
			char *end = str + (strlen(str) - 1);
			while( *end == '\n' || *end == '\t' || *end == ' ' || *end == '"' )
			{
				*end = 0;
				end--;
			}
			dbsql->parse()->optionValue( str );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ShowoptStatement :
	SHOWOPT DIRECTORY SEMICOLON
;

UpdateStatement :
	UPDATE
	{
		try
		{
			dbsql->parse()->statementInitialization();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	TableName UpdateSetList UpdatePart2
;

UpdatePart2 :
	WHERE_CURRENT_OF CursorName
	{
		try
		{
			dbsql->parse()->positionedUpdate();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
		YYACCEPT;
	}

	| MaybeWhereClause SEMICOLON
	{
		try
		{
			dbsql->parse()->searchedUpdate();
		}
		catch( ... )
		{
			dbsql->parse()->cleanup();
			throw;
		}
		YYACCEPT;
	}
;

UpdateSetList :
	SET
	{
		try
		{
			dbsql->parse()->clearDoingColumns();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	UpdateSetN1
;

UpdateSetN1 :
	UpdateSet
	| UpdateSet COMMA UpdateSetN1
;

UpdateSet :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->addUpdateColumnIdentifier( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	EQUAL UpdateSetExpression
;

UpdateSetExpression :
	Expression
	| SQL_NULL
;

ApproximateNumericLiteral :
	Mantissa EXPONENT Exponent
;

Mantissa :
	ExactNumericLiteral
;

Exponent :
	ExponentSignModifier UnsignedInteger
;

ExponentSignModifier :
	ARITHMETIC_PLUS
	| ARITHMETIC_MINUS
	| //  nothing
;

ApproximateNumericType :
	SQL_FLOAT
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_FLOAT );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| SQL_FLOAT LEFTPAREN UnsignedInteger RIGHTPAREN
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_FLOAT );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| SQL_DOUBLE PRECISION
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_FLOAT );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| REAL
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_REAL );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ArgumentList :
	ExpressionN1
;

ExpressionN1 :
	Expression
	| Expression COMMA ExpressionN1
;

BetweenPredicate :
	Expression MaybeNot BETWEEN Expression AND Expression
	{
		try
		{
			dbsql->parse()->addBetweenInstruction();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

MaybeNot :
	NOT
	{
		try
		{
			dbsql->parse()->addNOTOperator();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| //  nothing
;

BinaryType :
	BINARY
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_BINARY );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN Length RIGHTPAREN

	| VARBINARY
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_VARBINARY );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN Length RIGHTPAREN

	| SQL_LONG VARBINARY
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_LONGVARBINARY );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

CharacterStringType :
	SQL_CHAR
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_CHAR );
			dbsql->parse()->setColumnLength( 254 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	|
	SQL_CHAR
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_CHAR );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN Length RIGHTPAREN
	
	| SQL_CHAR VARYING
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_VARCHAR );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN Length RIGHTPAREN
	
	| VARCHAR
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_VARCHAR );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	LEFTPAREN Length RIGHTPAREN
	
	| SQL_LONG VARCHAR
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_LONGVARCHAR );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ColumnName :
	USER_DEFINED_NAME DOT USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setSelectListPrefix( $1 );
			dbsql->parse()->setSelectListName( $3 );
			dbsql->parse()->addColumnUsingSelectListNames();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setSelectListName( $1 );
			dbsql->parse()->addColumnUsingSelectListNames();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ComparisonOperator :
	LESS_THAN {}
	| GREATER_THAN {}
	| LESS_OR_EQUAL {}
	| GREATER_OR_EQUAL {}
	| EQUAL {}
	| NOT_EQUAL {}
;

ComparisonPredicate :
	Expression ComparisonOperator ExpressionOrSubQuery
	{
		try
		{
			dbsql->parse()->addComparisonOperator( $2 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ExpressionOrSubQuery :
	Expression
	| LEFTPAREN SubQuery RIGHTPAREN
;

CursorName :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->cursorName().setStringUpper( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

DataType :
	CharacterStringType
	| ExactNumericType
	| ApproximateNumericType
	| BinaryType
	| DateType
	| TimeType
	| TimestampType
;

DateSeparator :
	ARITHMETIC_MINUS
;

DateType :
	SQL_DATE
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_DATE );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

DateValue :
	YearsValue DateSeparator MonthsValue DateSeparator DaysValue
;

DaysValue :
	TWO_DIGITS
;

DynamicParameter :
	QUESTION_MARK
	{
		try
		{
			dbsql->parse()->addDynamicParameterPush();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ExactNumericLiteral :
	SIGNED_INTEGER DOT UnsignedInteger
	{
		try
		{
			dbsql->parse()->exactNumericLiteral( $1, $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| SIGNED_INTEGER
	{
		try
		{
			dbsql->parse()->exactNumericLiteral( $1, 0 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| UnsignedInteger DOT UnsignedInteger
	{
		try
		{
			dbsql->parse()->exactNumericLiteral( $1, $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| UnsignedInteger
	{
		try
		{
			dbsql->parse()->exactNumericLiteral( $1, 0 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| UnsignedInteger DOT
	{
		try
		{
			dbsql->parse()->exactNumericLiteral( $1, 0 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| DOT UnsignedInteger
	{
		try
		{
			dbsql->parse()->exactNumericLiteral( 0, $2 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ExactNumericType :
	DEC
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_DECIMAL );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN PrecisionAndScale RIGHTPAREN

	| DEC
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_DECIMAL );
			dbsql->parse()->setPrecision( 16 );
			dbsql->parse()->setScale( 0 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| NUMERIC
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_DECIMAL );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN PrecisionAndScale RIGHTPAREN

	| NUMERIC
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_DECIMAL );
			dbsql->parse()->setPrecision( 16 );
			dbsql->parse()->setScale( 0 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	
	| BIT
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_BIT );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| SMALLINT
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_SMALLINT );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| TINYINT
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_TINYINT );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| INTEGER
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_INTEGER );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| BIGINT
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_BIGINT );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ExistsPredicate :
	NOT ExistsPart2
	{
		try
		{
			dbsql->parse()->addNOTOperator();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| ExistsPart2
;

ExistsPart2 :
	EXISTS
	{
		try
		{
			dbsql->parse()->setExistsFlag();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	LEFTPAREN SubQuery RIGHTPAREN
	{
		try
		{
			dbsql->parse()->addExistsInstruction();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

Expression :
	Term

	| ExpressionPlusTerm
	{
		try
		{
			dbsql->parse()->addPlusOperator();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| ExpressionMinusTerm
	{
		try
		{
			dbsql->parse()->addMinusOperator();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ExpressionPlusTerm :
	Expression ARITHMETIC_PLUS Term
;

ExpressionMinusTerm :
	Expression ARITHMETIC_MINUS Term
;

Term :
	Factor

	| TermAsteriskFactor
	{
		try
		{
			dbsql->parse()->addMultiplicationOperator();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| TermSlashFactor
	{
		try
		{
			dbsql->parse()->addDivisionOperator();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

TermAsteriskFactor :
	Term ASTERISK Factor
;

TermSlashFactor :
	Term SLASH Factor
;

Factor :
	UnaryOperator Primary
	{
		try
		{
			dbsql->parse()->addUnaryMinusOperatorIfNecessary();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| Primary
;

UnaryOperator :
	ARITHMETIC_PLUS

	| ARITHMETIC_MINUS
	{
		try
		{
			dbsql->parse()->setUnaryMinusFlag();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

Primary :
	ColumnName
	| DynamicParameter
	| Literal
	| ODBCScalarFunctionExtension
	| SetFunctionReference
	| USER
	| LEFTPAREN Expression RIGHTPAREN
;

HoursValue :
	TWO_DIGITS
;

IndexName :
	USER_DEFINED_NAME DOT USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->indexPrefix().setStringUpper( $1 );
			dbsql->parse()->indexName().setStringUpper( $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->indexName().setStringUpper( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

InPredicate :
	Expression MaybeNot
	SQL_IN
	{
		try
		{
			dbsql->parse()->resetValueCounter();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	LEFTPAREN InValueExpression RIGHTPAREN
	{
		try
		{
			dbsql->parse()->addSetComparison( SetComparisonConstants::SETCOMP_EQUAL, SetComparisonConstants::MOD_ANY );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

InValueExpression :
	ValueN1
	| SubQuery
;

ValueN1 :
	Value
	| Value COMMA ValueN1
;

Value :
	Literal
	
	| USER
	{
		try
		{
			dbsql->parse()->addUSERPush();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	
	| DynamicParameter
;

InsertValue :
	DynamicParameter

	| DATE_VALUE
	{
		try
		{
			dbsql->parse()->dateLiteral( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| Literal
	
	| SQL_NULL
	{
		try
		{
			dbsql->parse()->addNULLPush();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER
	{
		try
		{
			dbsql->parse()->addUSERPush();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

Length :
	UnsignedInteger
	{
		try
		{
			dbsql->parse()->setColumnLength( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

LikePredicate :
	Expression MaybeNot LIKE PatternValue
;

PatternValue :
	CHARACTER_STRING_LITERAL
	{
		try
		{
			dbsql->parse()->characterStringLiteral( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	
	| DynamicParameter

	| USER
	{
		try
		{
			dbsql->parse()->addUSERPush();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

Literal :
	CHARACTER_STRING_LITERAL
	{
		try
		{
			dbsql->parse()->characterStringLiteral( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	
	| NumericLiteral

	| ODBCDateTimeExtension
;

MinutesValue :
	TWO_DIGITS
;

MonthsValue :
	TWO_DIGITS
;

NullPredicate :
	Expression IS MaybeNot SQL_NULL
;

NumericLiteral :
	ExactNumericLiteral
	| ApproximateNumericLiteral
	{
		try
		{
			dbsql->parse()->approximateNumericLiteral( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ODBCDateTimeExtension :
	ODBCStdEscInitiator 'd' SINGLE_QUOTE DATE_VALUE SINGLE_QUOTE ODBCStdEscTerminator
	{
		try
		{
			dbsql->parse()->dateLiteral( $4 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
		
	| ODBCExtEscInitiator 'd' SINGLE_QUOTE DATE_VALUE SINGLE_QUOTE ODBCExtEscTerminator
	{
		try
		{
			dbsql->parse()->dateLiteral( $4 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
		
	| ODBCStdEscInitiator 't' TimeLiteral ODBCStdEscTerminator
	{
		try
		{
			dbsql->parse()->timeLiteral( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
		
	| ODBCExtEscInitiator 't' TimeLiteral ODBCExtEscTerminator
	{
		try
		{
			dbsql->parse()->timeLiteral( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
		
	| ODBCStdEscInitiator 't' 's' TimestampLiteral ODBCStdEscTerminator
	{
		try
		{
			dbsql->parse()->timestampLiteral( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
		
	| ODBCExtEscInitiator 't' 's' TimestampLiteral ODBCExtEscTerminator
	{
		try
		{
			dbsql->parse()->timestampLiteral( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ODBCExtEscInitiator :
	'{'
;

ODBCExtEscTerminator :
	'}'
;

ODBCOuterJoinExtension :
	ODBCStdEscInitiator 'o' 'j' OuterJoin ODBCStdEscTerminator
	| ODBCExtEscInitiator 'o' 'j' OuterJoin ODBCExtEscTerminator
;

ODBCScalarFunctionExtension :
	ODBCStdEscInitiator 'f' 'n' ScalarFunction ODBCStdEscTerminator
	| ODBCExtEscInitiator 'f' 'n' ScalarFunction ODBCExtEscTerminator
;

ODBCStdEscInitiator :
	ODBCStdEscPrefix SQLEscVendorClause
;

SQLEscVendorClause :
	VENDOR LEFTPAREN MICROSOFT RIGHTPAREN COMMA PRODUCT LEFTPAREN ODBC RIGHTPAREN
;

ODBCStdEscPrefix :
	DOLLAR_SIGN LEFTPAREN
;

ODBCStdEscTerminator :
	ASTERISK RIGHTPAREN
;

SortSpecificationN1 :
	SortSpecification SortSpecificationN0
;

SortSpecificationN0 :
	SortSpecificationN0 COMMA SortSpecification
	|  //  nothing
;

SortSpecification :
	SortSpec SortModifier
;

SortSpec :
	UnsignedInteger { }
	| ColumnName
;

SortModifier :
	ASC
	| DESC
	{
		try
		{
			dbsql->parse()->setOrderDescending();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| //  nothing
;

OuterJoin :
	TableName MaybeCorrelationName LEFT OUTER JOIN TableName MaybeCorrelationName SQL_ON SearchCondition
;

MaybeCorrelationName :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setCorrelationName( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| //  nothing
;

PrecisionAndScale :
	UnsignedInteger COMMA UnsignedInteger
	{
		try
		{
			dbsql->parse()->setPrecision( $1 );
			dbsql->parse()->setScale( $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| UnsignedInteger
	{
		try
		{
			dbsql->parse()->setPrecision( $1 );
			dbsql->parse()->setScale( 0 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

Predicate :
	BetweenPredicate
	| ComparisonPredicate
	| ExistsPredicate
	| InPredicate

	| LikePredicate
	{
		try
		{
			dbsql->parse()->addLIKEOperator();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	
	| NullPredicate
	| QuantifiedPredicate
;

QuantifiedPredicate :
	Expression ComparisonOperator AllOrAny LEFTPAREN SubQuery RIGHTPAREN
	{
		try
		{
			dbsql->parse()->addSetComparison( $2, $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

AllOrAny :
	ALL {}
	| ANY {}
;

QuerySpecification :
	SELECT SelectModifier SelectList From TableReferenceList MaybeWhereClause MaybeGroupByClause MaybeHavingClause
;

ReferencedColumns :
	LEFTPAREN ReferencedColumnIdentifierN1 RIGHTPAREN
;

ReferencedColumnIdentifierN1 :
	ReferencedColumnIdentifier
	ReferencedColumnIdentifierN0
;

ReferencedColumnIdentifierN0 :
	ReferencedColumnIdentifierN0 COMMA ReferencedColumnIdentifier
	| //  nothing
;

ReferencedColumnIdentifier :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setReferencedIdentifier( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

TableReferencedColumns :
	LEFTPAREN TableReferencedColumnIdentifierN1 RIGHTPAREN
;

TableReferencedColumnIdentifierN1 :
	TableReferencedColumnIdentifier
	TableReferencedColumnIdentifierN0
;

TableReferencedColumnIdentifierN0 :
	TableReferencedColumnIdentifierN0 COMMA TableReferencedColumnIdentifier
	| //  nothing
;

TableReferencedColumnIdentifier :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setReferencedIdentifier( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ReferencingColumns :
	LEFTPAREN ReferencingColumnIdentifierN1 RIGHTPAREN
;

ReferencingColumnIdentifierN1 :
	ReferencingColumnIdentifier ReferencingColumnIdentifierN0
;

ReferencingColumnIdentifierN0 :
	ReferencingColumnIdentifierN0 COMMA ReferencingColumnIdentifier
	| //  nothing
;

ReferencingColumnIdentifier :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->setReferencingIdentifier( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ScalarFunction :
	FunctionName LEFTPAREN ArgumentList RIGHTPAREN
;

FunctionName :
	ASCII
	| SQL_CHAR
	| CONCAT
	| INSERT
	| LEFT
	| LTRIM
	| LENGTH
	| LOCATE
	| LCASE
	| REPEAT
	| REPLACE
	| RIGHT
	| RTRIM
	| SUBSTRING
	| UCASE
	| SQL_ABS
	| ACOS
	| ASIN
	| ATAN
	| ATAN2
	| CEILING
	| COS
	| COT
	| EXP
	| FLOOR
	| LOG
	| MOD
	| CQL_PI
	| RAND
	| SIGN
	| SIN
	| SQRT
	| TAN
	| NOW
	| CURDATE
	| DAYOFMONTH
	| DAYOFWEEK
	| DAYOFYEAR
	| MONTH
	| QUARTER
	| WEEK
	| YEAR
	| CURTIME
	| HOUR
	| MINUTE
	| SECOND
	| USER
	| DATABASE
	| IFNULL
	| CONVERT
;

SearchCondition :
	BooleanTerm OR SearchCondition
	{
		try
		{
			dbsql->parse()->addLogicalOperator( $2 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| BooleanTerm
;

BooleanTerm :
	BooleanFactor AND BooleanTerm
	{
		try
		{
			dbsql->parse()->addLogicalOperator( $2 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| BooleanFactor
;

BooleanFactor :
	Not BooleanPrimary
	{
		try
		{
			dbsql->parse()->addNOTOperator();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| BooleanPrimary
;

Not :
	NOT
;

BooleanPrimary :
	Predicate
	| LEFTPAREN SearchCondition RIGHTPAREN
;

SecondsFraction :
	THREE_DIGITS MaybeTHREE_DIGITS
;

MaybeTHREE_DIGITS :
	THREE_DIGITS
;

SecondsValue :
	TWO_DIGITS
;

SelectList :
	ASTERISK
	{
		try
		{
			dbsql->parse()->addColumn( "*" );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| SelectSublistN1
;

SelectSublistN1 :
	SelectSublist
	| SelectSublist COMMA SelectSublistN1
;

SelectSublist :
	Expression
	{
		try
		{
			dbsql->parse()->endSelectListElement();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

SetFunctionReference :
	COUNT LEFTPAREN ASTERISK RIGHTPAREN
	{
		try
		{
			dbsql->parse()->addCountStarInstruction();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| DistinctFunction
	| AllFunction
;

DistinctFunction :
	COUNT LEFTPAREN MaybeDistinct ColumnName RIGHTPAREN
	{
		try
		{
			dbsql->parse()->addCountColumnInstruction();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	| AggregateFunction LEFTPAREN DISTINCT ColumnName RIGHTPAREN
	{
		try
		{
			dbsql->parse()->addAggregateFunction( $1 );
			dbsql->parse()->selectDistinct();
			dbsql->parse()->selectUnique();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

MaybeDistinct :
	DISTINCT
	{
		try
		{
			dbsql->parse()->selectDistinct();
			dbsql->parse()->selectUnique();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	|  //  nothing
;

AggregateFunction :
	AVG
	| SQL_MAX
	| SQL_MIN
	| SUM
;

AllFunction :
	AggregateFunction LEFTPAREN Expression RIGHTPAREN
	{
		try
		{
			dbsql->parse()->addAggregateFunction( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

SubQuery :
	SELECT
	{
		try
		{
			dbsql->parse()->startSubquery();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	SelectModifier SelectList FROM
	{
		try
		{
			dbsql->parse()->clearDoingColumns();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
	TableReferenceList MaybeWhereClause MaybeGroupByClause MaybeHavingClause
	{
		try
		{
			dbsql->parse()->endSubquery();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

TableName :
	USER_DEFINED_NAME DOT USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->baseTablePrefix().setStringUpper( $1 );
			dbsql->parse()->addTableName( $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->addTableName( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	} 
;

TableReference :
	TableName MaybeCorrelationName
;

TableReferenceList :
	TableReferenceN1
	| ODBCOuterJoinExtension
;

ODBCOuterJoinExtension :
	ODBCStdEscInitiator FN ScalarFunction ODBCStdEscTerminator
|	ODBCExtEscInitiator FN ScalarFunction ODBCExtEscTerminator
;

TableReferenceN1 :
	TableReference
	| TableReference COMMA TableReferenceN1
;

TimeLiteral :
	SINGLE_QUOTE TimeValue SINGLE_QUOTE
;

TimeSeparator :
	COLON
;

TimeType :
	TIME
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_TIME );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

TimeValue :
	HoursValue TimeSeparator MinutesValue TimeSeparator SecondsValue
;

TimestampLiteral :
	SINGLE_QUOTE DateValue TimestampSeparator TimeValue MaybeSecondsFraction SINGLE_QUOTE
;

MaybeSecondsFraction :
	DOT SecondsFraction
	| //  nothing
;

TimestampSeparator :
	SPACE
;

TimestampType :
	TIMESTAMP
	{
		try
		{
			dbsql->parse()->setColumnType( CqlConstants::CQL_TIMESTAMP );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

UnsignedInteger :
	TWO_DIGITS {}
	| THREE_DIGITS {}
	| FOUR_DIGITS {}
	| UNSIGNED_INTEGER {}
;

GranteeName :
	USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->addGrantee( yytext );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

ViewedTableName :
	USER_DEFINED_NAME DOT USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->viewedTablePrefix().setStringUpper( $1 );
			dbsql->parse()->viewedTableName().setStringUpper( $3 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}

	| USER_DEFINED_NAME
	{
		try
		{
			dbsql->parse()->viewedTableName().setStringUpper( $1 );
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
	}
;

YearsValue :
	FOUR_DIGITS
;

InterpreterStatement :
	COMMIT WORK
	{
		try
		{
			dbsql->parse()->statementInitialization();
			dbsql->parse()->commitWork();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
		YYACCEPT;
	}
	
	| ROLLBACK WORK
	{
		try
		{
			dbsql->parse()->statementInitialization();
			dbsql->parse()->rollbackWork();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYERROR;
		}
		YYACCEPT;
	}

	| QUIT
	{
		try
		{
			dbsql->parse()->quit();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			YYACCEPT;
		}
		YYACCEPT;
	}
;
