%option noyywrap
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

#include "cqsconfi.h"

#ifdef _MSC_VER
#pragma warning( disable : 4127 4244 4505 )
#endif

%}
whitespace [ \t\n]
%%
"BUFFER" { return BUFFER; }
"=" { return EQUALS; }
"FILES" { return FILES; }
"FILE" { return CQL_FILE; }
"HOST" { return HOST; }
"ID" { return ID; }
"ISAM" { return ISAM; }
"LOG" { return LOG; }
"MACHINE" { return MACHINE; }
"MAX" { return MAX; }
"NAME" { return NAME; }
"NUMBER" { return NUMBER; }
"OF" { return OF; }
"PAGES" { return PAGES; }
"PAGE" { return PAGE; }
"SERVICE" { return SERVICE; }
"SIZE" { return CQL_SIZE; }
"SQL" { return SQL; }
"USERS" { return USERS; }
[0123456789][0123456789]* {
	sscanf( configtext, "%d", &configlval.number );
	return INTEGER;
}
[ABCDEFGHIJKLMNOPQRSTUVWXYZ_][ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789]* {
	memset( configlval.name, 0, sizeof( configlval.name ) );
	strcpy( configlval.name, configtext );
	return STRING;
}
{whitespace}* ;
