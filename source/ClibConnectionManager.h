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


#ifndef __ClibConnectionManager_h
#define __ClibConnectionManager_h


class ClibConnectionManager
{
	SOCKET_TYPE activeSockets_[ CQL_MAXIMUM_USERS + 1 ];
	SOCKET_TYPE busySockets_[ CQL_MAXIMUM_USERS + 1 ];
	UNI currentBusySocket_;
	SOCKET_TYPE socketDescriptor_;
	SOCKET_ADDRESS_TYPE socketAddress_;

public :

	ClibConnectionManager( void );
	~ClibConnectionManager( void );

	void bind( CqlString&, CqlString& );
	void findBusySockets( void );
	SOCKET_TYPE firstBusySocket( void );
	bool isActive( SOCKET_TYPE );
	void listen( void );
	SOCKET_TYPE nextBusySocket( void );
	void registerConnection( SOCKET_TYPE );
	void removeConnection( SOCKET_TYPE );
	void setPort( CqlString&, CqlString& );
	SOCKET_ADDRESS_TYPE& socketAddress( void ) { return socketAddress_; }
	SOCKET_TYPE socketDescriptor( void ) { return socketDescriptor_; }
};


#endif  //  __ClibConnectionManager_h
