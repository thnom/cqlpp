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


#ifndef __AbstractDatabaseHandle_h
#define __AbstractDatabaseHandle_h


class AbstractDatabaseHandle : public CqlConstants, public ErrorConstants
{
	Parser *parser_;
	CqlString userName_;
	CqlString initDir_;

public :

	AbstractDatabaseHandle( const CqlString& /* userName */,
							const CqlString& /* password  */,
							const CqlString& /* initialDirectory */ );

	virtual ~AbstractDatabaseHandle( void );

	static AbstractDatabaseHandle *createObject( const CqlString& /* userName */,
												 const CqlString& /* password  */,
												 const CqlString& /* initial directory */ );

	AbstractTable *openAbstractTable( const char * const, TableType = CQL_CQL );
	Parser *parser( void ) { return parser_; }
	void parser( Parser *p ) { parser_ = p; }
	NI returnError( ErrorCodes, const char * const, NI, NI = 0 );
	CqlString& userName( void ) { return userName_; }
	CqlString& initDir( void ) { return initDir_; }

	virtual AbstractErrorManager& aErrorMan( void ) = 0;
	virtual void beginTransaction( void ) = 0;
	virtual void commitTransaction( void ) = 0;
	virtual void disconnect( void ) = 0;
	virtual void rollbackTransaction( void ) = 0;
	virtual UserConfigurationManager& userConfig( void ) = 0;
};

typedef AbstractDatabaseHandle *pAbstractDatabaseHandle;


#endif  //  __AbstractDatabaseHandle_h
