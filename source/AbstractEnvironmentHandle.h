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


#ifndef __AbstractEnvironmentHandle_h
#define __AbstractEnvironmentHandle_h


class AbstractEnvironmentHandle : public AbstractSystemConfigurationManager, public AbstractLogger, virtual public Clib
{
	CqlString *optionCurrentDirectory_;
	const char * const defaultEnvName_;

	enum TraceOptions
	{
		TRACE_NOTHING,
		TRACE_CPP_LIBRARY = 1,
		TRACE_OTHER1 = 2,
		TRACE_OTHER2 = 4,
		TRACE_OTHER3 = 8,
		TRACE_OTHER4 = 16,
		TRACE_OTHER5 = 32
	};

	bool cppLibraryTrace_;
	UNI referenceCount_;

protected:

	ConnectionManager * connectionMan_;

public:

	AbstractEnvironmentHandle( const CqlString& initialDirectory, const char * const traceSpecEnvName = "" );
	virtual ~AbstractEnvironmentHandle( void );

	static AbstractEnvironmentHandle *createObject( const CqlString& /*initialDirectory*/ );

	bool cppLibraryTrace( void ) { return cppLibraryTrace_; }
	void connect( AbstractDatabaseHandle* );
	ConnectionManager& connectionMan( void ) { return *connectionMan_; }
	void disconnect( AbstractDatabaseHandle* );
	const CqlString *optionCurrentDirectory( void ) { return optionCurrentDirectory_; }

	virtual char *osCurrentDirectory( void ) = 0;
	virtual bool fileExists( const CqlString& /*name*/ ) = 0;
	virtual pUC globalBuffer( void ) = 0;
	virtual void transactionStartup( const CqlString& /*initial directory*/,
									 const NC * const /* logName */ ) = 0;
};

typedef AbstractEnvironmentHandle *pAbstractEnvironmentHandle;


#endif  //  __AbstractEnvironmentHandle_h


