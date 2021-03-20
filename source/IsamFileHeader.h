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


#ifndef __IsamFileHeader_h
#define __IsamFileHeader_h


class IsamFileHeader
{
	UL machineId_;
	US numberOfColumns_;
	RECID endOfFile_;

public :

	IsamFileHeader( UL /*machineId*/, UL /*numberOfColumns*/ );
	IsamFileHeader( void );
	~IsamFileHeader( void );

	RECID endOfFile( void ) { return endOfFile_; }
	void endOfFile( RECID pos ) { endOfFile_ = pos; }
	void incrementNumberOfColumns( void ) { numberOfColumns_++; }
	UL machineId( void ) { return machineId_; }
	US numberOfColumns( void ) { return numberOfColumns_; }
	NI read( DatabaseHandle& /*hDb*/, FileManager* /*file*/ );
	void numberOfColumns( US nc ) { numberOfColumns_ = nc; }
	NI setup( UL machineId );
	NI write( DatabaseHandle& /*hDb*/, FileManager* /*file*/ );
};


#endif  //  __IsamFileHeader_h
