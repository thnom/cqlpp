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


#ifndef __AbstractMessage_h
#define __AbstractMessage_h


class AbstractMessage : public MessageIdentifiers, public CqlConstants, public ErrorConstants
{
	AbstractObjectList commandObjects_;
	AbstractObjectList commandData_;
	pUC data_;
	UNI messageLength_;
	AbstractObjectList replyObjects_;
	AbstractObjectList replyData_;

	BFT initFailed_ : 1;

	NI clientReceiveMessage( Connection& );
	NI clientSendMessage( Connection& );

public :

	AbstractMessage( void );
	virtual ~AbstractMessage( void );

	static AbstractMessage *createObject( MessageIdentifier );

	NI clientExecute( void );
	AbstractObjectList& commandData( void ) { return commandData_; }
	AbstractObjectList& commandObjects( void ) { return commandObjects_; }
	NI completeRead( AbstractDatabaseHandle&, Connection&, US );
	UL getHandle( void );
	NI getStatus( void );
	static NI readMessage( AbstractDatabaseHandle&, AbstractMessage**, Connection& );
	AbstractObjectList& replyData( void ) { return replyData_; }
	AbstractObjectList& replyObjects( void ) { return replyObjects_; }
	void setInitFailed( void ) { initFailed_ = CQL_YES; }
	void setup( UL );
	NI writeMessage( AbstractDatabaseHandle&, Connection& );

	virtual NI execute( void ) = 0;
	virtual MessageIdentifier messageId( void ) = 0;
};

typedef AbstractMessage *pAbstractMessage;


#endif  //  __AbstractMessage_h
