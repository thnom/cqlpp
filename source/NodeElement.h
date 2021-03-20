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


#ifndef __NodeElement_h
#define __NodeElement_h


class NodeElement;
typedef List< NodeElement > NodeElementList;
typedef ListElement< NodeElement, NodeElementList > NodeElementListElement;


class NodeElement : public NodeElementListElement, public TempBuffer
{
	bool checkUseFlag;
	UL entries;
	AbstractDatabaseHandle& hAdb_;
	RECID son;

public :

	NodeElement( AbstractDatabaseHandle& );
	NodeElement( const NodeElement& );
	~NodeElement( void );

	NodeElement& operator=( NodeElement& );

	NI CheckUseFlag( void ) { return checkUseFlag; }
	void ClearCheckUseFlag( void ) { checkUseFlag = CQL_NO; }
	CompareResult Compare( NodeElement&, AbstractSegmentDescriptorList&, bool /*compareRecordPosition*/, UNI /*segmentsToCompare*/ = 0 );
	void Dump( void );
	UL Entries( void ) { return entries; }
	void input( TempBuffer& );
	NodeElement *NextNodeElement( void );
	void output( TempBuffer& );
	NodeElement *PreviousNodeElement( void );
	NI Read( FileManager& );
	void SetCheckUseFlag( void ) { checkUseFlag = CQL_YES; }
	void SetEntries( UL e ) { entries = e; }
	void SetSon( RECID pos ) { son = pos; }
	RECID Son( void ) { return son; }
	US SpaceNeeded( void );
	void updateKey( NodeElement* );
	NI Write( FileManager& );
};

typedef NodeElement *pNodeElement;


#endif  //  __NodeElement_h
