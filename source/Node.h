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


#ifndef __Node_h
#define __Node_h


class Node : public NodeElementList, public CqlConstants, public ErrorConstants
{
	pNodeElement currentElement;
	pNodeElement higherElement;
	RECID leftBrother;
	UL leftEntries;
	RECID location;
	pNodeElement lowerElement;
	RECID lowerKeyNode;
	UL numberOfEntries;
	RECID parent;
	US remainingSpace;
	RECID rightBrother;
	UL rightEntries;

	bool dirty;
	bool root;

	//
	//  temporary means that this is a memory only index
	//
	bool temporary;
	bool terminal;

public :

	Node( void );
	Node( RECID );
	~Node( void );

	NI AddElement( pNodeElement );
	NI AddElementToBeginning( pNodeElement );
	NI AddElementToEnd( pNodeElement );
	NI Assign( DatabaseHandle&, Node& );
	void ClearRoot( void ) { root = CQL_NO; }
	void ClearTerminal( void ) { terminal = false; }
	pNodeElement CurrentElement( void ) { return currentElement; }
	void DecrementNumberOfEntries( void ) { numberOfEntries--; }
	NI Dirty( void ) { return dirty; }
	NI DiscardNode( FileManager* file );
	NI FindMatchingElement( DatabaseHandle&,
							pNodeElement,
							AbstractSegmentDescriptorList& );
	NI FindPositionInNode( DatabaseHandle&,
						   pNodeElement,
						   AbstractSegmentDescriptorList& );
	pNodeElement HigherElement( void ) { return higherElement; }
	void IncrementNumberOfEntries( void ) { numberOfEntries++; }
	NI UpdateNonterminalCount( DatabaseHandle&, Index*, RECID, UL );
	void IncreaseRemainingSpace( US amount ) { remainingSpace = ((US)( remainingSpace + amount ) ); }
	RECID LeftBrother( void ) { return leftBrother; }
	UL LeftEntries( void ) { return leftEntries; }
	RECID Location( void ) { return location; }
	pNodeElement LowerElement( void ) { return lowerElement; }
	RECID LowerKeyNode( void ) { return lowerKeyNode; }
	UL NumberOfEntries( void ) { return numberOfEntries; }
	RECID Parent( void ) { return parent; }
	NI ReadNode( DatabaseHandle&, FileManager* file, RECID location );
	void ReduceRemainingSpace( US amount ) { remainingSpace = ((US)( remainingSpace - amount ) ); }
	US RemainingSpace( void ) { return remainingSpace; }
	NI ReplaceKey( DatabaseHandle&, RECID, pNodeElement );
	RECID RightBrother( void ) { return rightBrother; }
	UL RightEntries( void ) { return rightEntries; }
	NI RollbackNode( FileManager* file );
	NI Root( void ) { return root; }
	void SetCurrentElement( pNodeElement element ) { currentElement = element; }
	void SetDirty( void ) { dirty = CQL_YES; }
	void SetHigherElement( pNodeElement element ) { higherElement = element; }
	void SetLeftBrother( RECID bro ) { leftBrother = bro; }
	void SetLocation( RECID loc ) { location = loc; }
	void SetLowerElement( pNodeElement element ) { lowerElement = element; }
	void SetLowerKeyNode( RECID pos ) { lowerKeyNode = pos; }
	void SetParent( RECID par ) { parent = par; }
	void SetRemainingSpace( US space ) { remainingSpace = space; }
	void SetRightBrother( RECID bro ) { rightBrother = bro; }
	void SetRoot( void ) { root = CQL_YES; }
	void SetTemporary( void ) { temporary = CQL_YES; }
	void SetTerminal( void ) { terminal = true; }
	bool Temporary( void ) { return temporary; }
	NI Terminal( void ) { return terminal; }
	NI WriteNode( DatabaseHandle&, FileManager* file );
};

typedef Node *pNode;


#endif  //  __Node_h
