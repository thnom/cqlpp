%token BUFFER
%token EQUALS
%token CQL_FILE
%token FILES
%token HOST
%token ID
%token INTEGER
%token ISAM
%token LOG
%token MACHINE
%token MAX
%token NAME
%token NUMBER
%token OF
%token PAGE
%token PAGES
%token SERVICE
%token CQL_SIZE
%token SQL
%token STRING
%token USERS
%{
#ifdef __CQL_CLIENT_SERVER__

#ifdef __CQL_ISAM_SERVER_SIDE__
#include "cqlibrar.h"
#else
#include "cqclient.h"
#endif  //  __CQL_ISAM_SERVER_SIDE__

#else  //  __CQL_CLIENT_SERVER__

#include "cqlibrar.h"

#endif  //  __CQL_CLIENT_SERVER__

	int configerror( char* );
	int configlex( void );
	void configunput( int, char* );

#ifdef _MSC_VER
#pragma warning( disable : 4244 )
#endif

%}
%union {
	char name[ 128 ];
	int number;
}
%type <name> STRING
%type <number> INTEGER
%%
Statement :
	ConfigurationStatement
	| Statement ConfigurationStatement
;

ConfigurationStatement :
	HostNameStatement
	| IsamServiceNameStatement
	| LogFileSizeStatement
	| MachineIDStatement
	| MaxBufferPagesStatement
	| MaxUsersStatement
	| NumberOfLogFilesStatement
	| PageSizeStatement
	| SQLServiceNameStatement
;

HostNameStatement :
	HOST NAME EQUALS STRING = {
		if( dbenv->SysConfigMan()->SetHostName( $4 ) == CQL_FAILURE )
			YYERROR;
	}
;

IsamServiceNameStatement :
	ISAM SERVICE NAME EQUALS STRING = {
		if( dbenv->SysConfigMan()->SetIsamServiceName( $5 ) == CQL_FAILURE )
			YYERROR;
	}
;

SQLServiceNameStatement :
	SQL SERVICE NAME EQUALS STRING = {
		if( dbenv->SysConfigMan()->SetSqlServiceName( $5 ) == CQL_FAILURE )
			YYERROR;
	}
;

LogFileSizeStatement :
	LOG CQL_FILE CQL_SIZE EQUALS INTEGER = {
		dbenv->SysConfigMan()->SetLogFileSize( $5 );
	}
;

MachineIDStatement :
	MACHINE ID EQUALS INTEGER = {
		dbenv->SysConfigMan()->SetMachineId( $4 );
	}
;

MaxBufferPagesStatement :
	MAX BUFFER PAGES EQUALS INTEGER = {
		dbenv->SysConfigMan()->SetMaxBufferPages( $5 );
	}
;

MaxUsersStatement :
	MAX USERS EQUALS INTEGER = {
		dbenv->SysConfigMan()->SetMaxUsers( $4 );
	}
;

NumberOfLogFilesStatement :
	NUMBER OF LOG FILES EQUALS INTEGER = {
		dbenv->SysConfigMan()->SetNumberOfLogFiles( $6 );
	}
;

PageSizeStatement :
	PAGE CQL_SIZE EQUALS INTEGER = {
		dbenv->SysConfigMan()->SetPageSize( $4 );
	}
;
