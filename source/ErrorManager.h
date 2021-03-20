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


#ifndef __ErrorManager_h
#define __ErrorManager_h


class ErrorManager : public AbstractErrorManager
{
	enum ErrorCodes errorCode_;
	ExceptionCodes exceptionCode_;
	CqlString errorFile_;
	NI errorLine_;
	CqlString errorText_;
	NI osError_;
	CqlString sqlstate_;

public :

	ErrorManager( void );
	ErrorManager( const ExceptionCodes, const CqlString& /*errorFile*/, const NI /*line*/, const CqlString& /*errorText*/, const CqlString& /*sqlstate*/, const NI /*oserror*/ );
	~ErrorManager( void );

	NI cleanup( void );
	enum ErrorCodes errorCode( void ) { return errorCode_; }
	ExceptionCodes exceptionCode( void ) { return exceptionCode_; }
	CqlString& errorFile( void ) { return errorFile_; }
	NI errorLine( void ) { return errorLine_; }
	const char * const errorText( ErrorCodes );
	const char * const sqlstate( ErrorCodes );
	NI log( ErrorManager::ErrorCodes, pNC, NI, NI );
	NI noError( void );
	NI osError( void ) { return osError_; }
	void resetError( void ) { errorCode_ = CQL_NO_ERROR; }
	void resetIfCloseWithPendingTransaction( void );
	NI returnError( ErrorCodes, const char * const, NI, NI = 0 );
	NI returnRC( NI, ErrorCodes, const char * const, NI, NI = 0 );
	NI returnNormal( ErrorCodes, const char * const, NI );
	NI returnNormalRC( NI, ErrorCodes, const char * const, NI );
	NI returnNormalOrError( void );

};

typedef ErrorManager *pErrorManager;


#endif  //  __ErrorManager_h
