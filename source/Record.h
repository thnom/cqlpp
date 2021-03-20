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


#ifndef __Record_h
#define __Record_h


class Record : public TempBuffer, public ErrorConstants
{
	RECID location;
	//  instead of length and dataBuffer, TempBuffer is used
	// UL length;
	// pUC dataBuffer;

	BFT dirty : 1;
	BFT temporary : 1;

public :

	Record( AbstractDatabaseHandle & );
	Record( AbstractDatabaseHandle&, RECID );
	~Record( void );

	NI Assign( DatabaseHandle&, Record& );
	NI ConstructRecord( DatabaseHandle&, AbstractColumnDescriptorList& columns, UL len );
	NI DataPointer( pUC*, US, pNI );
	NI Dirty( void ) { return dirty; }
	NI InputCachedRecord( AbstractColumnDescriptorList& );
	RECID Location( void ) { return location; }
	NI Read( DatabaseHandle&, FileManager*, AbstractColumnDescriptorList& );
	void SetDirty( void ) { dirty = CQL_YES; }
	void SetTemporary( void ) { temporary = CQL_YES; }
	NI Temporary( void ) { return temporary; }

};

typedef Record *pRecord;


#endif  //  __Record_h
