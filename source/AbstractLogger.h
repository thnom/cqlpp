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


#ifndef __AbstractLogger_h
#define __AbstractLogger_h


//
//  This class abstracts the error logging functionality.  It has
//  nothing to do with transaction logging.
//

class AbstractLogger : public CqlConstants, virtual public ExceptionCodes, virtual public ErrorConstants
{

public :

		enum TraceLevel
		{
				MINIMAL,
				ENTRY_EXIT,
				DETAILED,
				TRACEALL
		};

private:

		ClibFileManager file_;
		TraceLevel tracelevel_;
		bool logFileOpen_;

public:

		virtual AbstractLogger& operator << ( ErrorCodes /*errorCode*/ ) = 0;
		virtual AbstractLogger& operator << ( const char * const ) = 0;
		virtual AbstractLogger& operator << ( NI ) = 0;
		virtual AbstractLogger& operator << ( UNI ) = 0;
		virtual AbstractLogger& operator << ( RECID ) = 0;
		virtual AbstractLogger& operator << ( void* ) = 0;
		virtual AbstractLogger& operator << ( UL ) = 0;
		virtual AbstractLogger& operator << ( const CqlString& ) = 0;
		virtual AbstractLogger& operator << ( CqlException& ) = 0;

		ClibFileManager& file( void ) { return file_; }
		void logPrintf(TraceLevel, const char * const, ... );

public :

		AbstractLogger( const CqlString& /*initial directory*/ );
		virtual ~AbstractLogger( void );
};

typedef AbstractLogger *pAbstractLogger;


#endif  //  __AbstractLogger_h
