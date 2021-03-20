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


#ifndef __ClibConnection_h
#define __ClibConnection_h


class ClibConnection : public ErrorConstants
{
	SOCKET_TYPE socketDescriptor_;

public :

	void acceptConnection( SOCKET_TYPE /*acceptSocketDescriptor*/, SOCKET_ADDRESS_TYPE& /*socketAddress*/ );
	void initiateConnection( SOCKET_TYPE /*connectSocketDescriptor*/, SOCKET_ADDRESS_TYPE& /*socketAddress*/ );
	void releaseConnection( void );
	UNI read( void* /*data*/, UNI /*len*/ );
	SOCKET_TYPE socketDescriptor( void ) { return socketDescriptor_; }
	void socketDescriptor( SOCKET_TYPE sd ) { socketDescriptor_ = sd; }
	void write( void* /*data*/, UNI /*len*/ );
};

typedef ClibConnection *pClibConnection;


#endif  //  __ClibConnection_h
