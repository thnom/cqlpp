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


#ifndef __AbstractErrorManager_h
#define __AbstractErrorManager_h


class AbstractErrorManager;
typedef List< AbstractErrorManager > AbstractErrorManagerList;
typedef ListElement< AbstractErrorManager, AbstractErrorManagerList > AbstractErrorManagerListElement;


class AbstractErrorManager : public AbstractErrorManagerListElement, public ErrorConstants, public ExceptionCodes
{
public :

	AbstractErrorManager( void );
	virtual ~AbstractErrorManager( void );

	static AbstractErrorManager *createObject( const ExceptionCodes, const CqlString& /*file*/, const NI /*line*/, const CqlString& /*errorText*/, const CqlString& /*sqlstate*/, NI /*oserror*/ = 0 );

	virtual ErrorCodes errorCode( void ) = 0;
	virtual CqlString& errorFile( void ) = 0;
	virtual NI errorLine( void ) = 0;
	virtual const char * const errorText( ErrorCodes ) = 0;
	virtual const char * const sqlstate( ErrorCodes ) = 0;
	virtual NI log( ErrorCodes, pNC, NI, NI = 0 ) = 0;
	virtual NI noError( void ) = 0;
	virtual NI osError( void ) = 0;
	virtual void resetError( void ) = 0;
	//  ********************  This is specific to CQL ISAM layer.  Move to ErrorManager
	//  virtual void resetIfCloseWithPendingTransaction( void ) = 0;
	virtual NI returnError( ErrorCodes, const char * const, NI, NI = 0 ) = 0;
	virtual NI returnNormal( ErrorCodes, const char * const, NI ) = 0;
	virtual NI returnNormalOrError( void ) = 0;
};

typedef AbstractErrorManager *pAbstractErrorManager;


#endif  //  __AbstractErrorManager_h
