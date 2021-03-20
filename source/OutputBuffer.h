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


#ifndef __OutputBuffer_h
#define __OutputBuffer_h


#define CQL_OUTPUT_CHUNK_SIZE 4096

class OutputBuffer : public TempBuffer
{
	UNI currentColumn_;
	UNI currentRow_;
	AbstractDatabaseHandle& hAdb_;
	UL remainingSpace_;

	void enlargeBuffer( void );

public :

	OutputBuffer( AbstractDatabaseHandle& );
	~OutputBuffer( void );

	OutputBuffer& operator << ( US );
	OutputBuffer& operator << ( NI );
	OutputBuffer& operator << ( UNI );
	OutputBuffer& operator << ( UL );
	OutputBuffer& operator << ( UC );
	OutputBuffer& operator << ( D );
	OutputBuffer& operator << ( F );
	OutputBuffer& operator << ( NC );
	OutputBuffer& operator << ( L );
	OutputBuffer& operator << ( S );
	OutputBuffer& operator << ( CqlString& );
	OutputBuffer& operator << ( const char * const );

	void checkSpace( UNI );
	UNI currentColumn( void );
	UNI currentRow( void );
	NI initialize( void );
	void writeObject( void*, UL );
};


#endif  //  __OutputBuffer_h
