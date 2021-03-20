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


#ifndef __SystemConfigurationManager_h
#define __SystemConfigurationManager_h


class SystemConfigurationManager : public Logger
{
	CqlString hostName_;
	CqlString isamServiceName_;
	RECID logFileSize_;
	UNI machineId_;
	UNI maxBufferPages_;
	UNI maxUsers_;
	UNI numberOfLogFiles_;
	UNI pageSize_;
	CqlString sqlServiceName_;

public :

	SystemConfigurationManager( const CqlString& /*initial directory*/ );
	~SystemConfigurationManager( void );

	CqlString& hostName( void ) { return hostName_; }
	NI hostName( pNC );
	CqlString& isamServiceName( void ) { return isamServiceName_; }
	NI isamServiceName( pNC );
	RECID logFileSize( void ) { return logFileSize_; }
	void logFileSize( NI );
	UNI machineId( void ) { return machineId_; }
	void machineId( NI );
	UNI maxBufferPages( void ) { return maxBufferPages_; }
	void maxBufferPages( NI );
	void maxUsers( NI );
	UNI numberOfLogFiles( void ) { return numberOfLogFiles_; }
	void numberOfLogFiles( NI );
	void pageSize( NI );
	NI setSystemConfiguration( void );
	CqlString& sqlServiceName( void ) { return sqlServiceName_; }
	NI sqlServiceName( pNC );
};

typedef SystemConfigurationManager *pSystemConfigurationManager;


#endif  //  __SystemConfigurationManager_h
