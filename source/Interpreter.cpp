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


extern FILE *yyin;
extern int yydebug;
extern int debugActionFunctions;


void Parser::newStatement( void )
{
	std::cerr << "SQL> ";
	std::cerr.flush();
}


void commandSyntaxError(std::stringstream *ss)
{
	std::cerr << ss->str() << std::endl;
	std::cerr << "interpreter [-u UserName] [-p password] [-o OutputFileName] [-i script]" << std::endl << std::endl;
	exit(-2);
}


int main( int argc, char *argv[] )
{
	if( argc < 2 )
	{
		std::cerr << "interpreter {UserName} [InitialDirectoryName]"
				  << std:: endl;
		exit( -1 );
	}

	if( getenv( "CQL_DATA_TRACING" ) )
		dataTracing = 1;

	if( getenv( "CQL_PARSER_TRACING" ) )
		yydebug = 1;

	SqlHandle *dbsql;

	//************************************************************************
	//**  DO __NOT__ FREE THESE.  They are passed to the SqlHandle          **
	//**  which assigns them to member variables.  Thus if they free is     **
	//**  called on them here a seg fault will quickly result.  The         **
	//**  SqlHandle destructor is responsible for deleting them.            **
	//************************************************************************
	CqlString *argUser = 0;
	CqlString *argPassword = 0;
	CqlString *argScript = 0;
	CqlString *argOutputFile = 0;
	CqlString *argDirectory = 0;

	try
	{
		if( argc < 2 )
			argUser = new CqlString("PUBLIC");
		else
		{
			int currentArg = 1;
			while( currentArg < argc )
			{
				pNC command = argv[currentArg++];
				if( command[0] != '-' )
				{
					std::stringstream *ss = new std::stringstream();
					*ss << "Command line error, expected -, found "  << command[0] << ", exiting." ;
					commandSyntaxError(ss);
				}
				if( currentArg == argc )
				{
					std::stringstream *ss = new std::stringstream();
					*ss << "Command line error, no value for command " << command[1];
					commandSyntaxError(ss);
				}

				//  the environment handle is not available yet (it is 0).
				//  so, we are cheating a bit and using toupper.  This will fail
				//  miserably in any other character set.
				switch( toupper(command[1]) )
				{
				case 'U' :
					argUser = new CqlString(argv[currentArg++]);
					break;

				case 'I' :
					argScript = new CqlString(argv[currentArg++]);
					break;

				case 'O' :
					argOutputFile = new CqlString(argv[currentArg++]);
					break;

				case 'P' :
					argPassword = new CqlString(argv[currentArg++]);
					break;

				case 'D' :
					argDirectory = new CqlString(argv[currentArg++]);
					break;

				default :
					std::stringstream *ss = new std::stringstream();
					*ss << "Command not recognized, command=" << command[1];
					commandSyntaxError(ss);
				}
			}
		}

		dbsql = new SqlHandle( argUser, argPassword, argDirectory, argScript, argOutputFile );
	}
	catch( CqlException& ex )
	{
		std::cerr << ex;
		return 0;
	}

	//  yydebug = 1;
	//  debugActionFunctions = 1;


	dbSqlEnv->SetInteractiveMode();

	try
	{

		dbsql->connect();
	}

	catch( CqlException& fme )
	{
		std::cerr << fme;
		return 0;
	}

	if( argScript != 0 && argScript->length() > 0 )
	{
		dbsql->parse()->beginScript(const_cast<NC*>(argScript->text()), true);
		std::cout << "Script file found, exiting..." << std::endl;
	}
	else
	{
		yyin = stdin;
		std::cout << "No script file, getting input from standard in" << std::endl;
	}

	dbsql->parse()->setEcho();
	dbsql->parse()->newStatement();

	while( !dbsql->parse()->shuttingDown() )
	{
		dbsql->resetError();
#if !defined(__CQL_CLIENT_SERVER__)
		try
		{
#endif
			if( yydebug )
				std::cerr << "Calling yyparse..." << std::endl;

			yyparse( dbsql );
#if !defined(__CQL_CLIENT_SERVER__)
		}
		catch( CqlException& exc )
		{
			std::cerr << exc;
			break;
		}
#endif

		if( !dbsql->noError() )
		{
			std::cerr << "Error " << ((NI)dbsql->errorCode()) << ", file "
				<< dbsql->errorFile() << ", line "
				<< dbsql->errorLine() << ", OS error "
				<< dbsql->osError() << std::endl;
			dbsql->parse()->newStatement();
		}
	}

	dbsql->disconnect();
	std::cerr << "Interpreter exit" << std::endl;
	delete dbsql;
	delete dbSqlEnv;
	return 0;
}
