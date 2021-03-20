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


#ifndef __Accessor_h
#define __Accessor_h


class Accessor;
typedef List<Accessor> AccessorList;
typedef ListElement<Accessor, AccessorList> AccessorListElement;


class Accessor : public AccessorListElement, public CqlConstants, public ErrorConstants, public AccessorTypes
{
protected :

	US keyNumber_;
	US numberOfSegments_;

	AbstractSegmentDescriptorList segments_;

public :

	Accessor( const AccessorTypes /*atype*/, const US /*keyNumber*/ );
	virtual ~Accessor( void );

	Accessor& operator = ( Accessor& );

	static Accessor *createObject( AccessorTypes /*atype*/, US /*keyNumber*/ = 0 );
	US keyNumber( void ) { return keyNumber_; }
	void keyNumber( US kno ) { keyNumber_ = kno; }
	US numberOfSegments( void ) { return numberOfSegments_; }
	void numberOfSegments( US ns ) { numberOfSegments_ = ns; }
	AbstractSegmentDescriptorList& segments( void ) { return segments_; }

	virtual void remove( AbstractDatabaseHandle&, MemoryIndex&, RECID& ) = 0;
};

typedef Accessor *pAccessor;


#endif  //  __Accessor_h
