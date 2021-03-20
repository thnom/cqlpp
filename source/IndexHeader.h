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


#ifndef __IndexHeader_h
#define __IndexHeader_h


class IndexHeader : public ErrorConstants
{
	RECID endOfFile;
	RECID freeNodeList;
	pRECID keyDescriptorLocations;
	UL machineId;
	UL numberOfKeys;

	BFT initFailed : 1;

public :

	IndexHeader( UL machId, UL nKeys );
	IndexHeader( void );
	~IndexHeader( void );

	NI Assign( DatabaseHandle&, IndexHeader& );
	RECID EndOfFile( void ) { return endOfFile; }
	RECID FreeNodeList( void ) { return freeNodeList; }
	NI InitFailed( void ) { return initFailed; }
	RECID KeyDescriptorLocation( UNI idx ) { return keyDescriptorLocations[ idx ]; }
	pRECID KeyDescriptorLocations( void ) { return keyDescriptorLocations; }
	UL MachineId( void ) { return machineId; }
	UL NumberOfKeys( void ) { return numberOfKeys; }
	NI Read( DatabaseHandle&, FileManager* );
	void SetEndOfFile( RECID pos ) { endOfFile = pos; }
	void SetFreeNodeList( RECID pos ) { freeNodeList = pos; }
	NI SetKeyDescriptorLocation( RECID oldpos, RECID newpos );
	void SetKeyDescriptorLocations( pRECID kdl ) { keyDescriptorLocations = kdl; }
	void SetNumberOfKeys( UL nk ) { numberOfKeys = nk; }
	NI Setup( DatabaseHandle&, UL machId, UL numKeys );
	NI Write( DatabaseHandle&, FileManager* );
};

typedef IndexHeader *pIndexHeader;


#endif  //  __IndexHeader_h
