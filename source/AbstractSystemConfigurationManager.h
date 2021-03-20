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


#ifndef __AbstractSystemConfigurationManager_h
#define __AbstractSystemConfigurationManager_h


class AbstractSystemConfigurationManager : virtual public Clib
{
public :

	AbstractSystemConfigurationManager( void );
	virtual ~AbstractSystemConfigurationManager( void );

	virtual NI hostName( pNC ) = 0;
	virtual NI isamServiceName( pNC ) = 0;
	virtual RECID logFileSize( void ) = 0;
	virtual void logFileSize( NI ) = 0;
	virtual UNI machineId( void ) = 0;
	virtual void machineId( NI ) = 0;
	virtual UNI maxBufferPages( void ) = 0;
	virtual void maxBufferPages( NI ) = 0;
	virtual void maxUsers( NI ) = 0;
	virtual UNI numberOfLogFiles( void ) = 0;
	virtual void numberOfLogFiles( NI ) = 0;
	virtual void pageSize( NI ) = 0;
	virtual NI sqlServiceName( pNC ) = 0;
};

typedef AbstractSystemConfigurationManager *pAbstractSystemConfigurationManager;


#endif  //  __AbstractSystemConfigurationManager_h
