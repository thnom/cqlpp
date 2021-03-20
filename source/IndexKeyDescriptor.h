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


#ifndef __IndexKeyDescriptor_h
#define __IndexKeyDescriptor_h

class IndexKeyDescriptor : public Accessor, public KeySearchConstants, public SegmentTypes
{
	pNode currentNode;
	RECID currentNodeLocation;
	pAbstractSegmentDescriptor currentSegment;
	UNI currentElementNumber;
	RECID descriptorLocation_;
	bool dirty_;
	bool lengthIndex_;
	UL maximumKeyLength_;
	RECID rootLocation;

public :

	IndexKeyDescriptor( AccessorTypes /*atype*/, US /*keyNumber*/ = 0 );
	~IndexKeyDescriptor( void );

	NI AddSegment( DatabaseHandle&, US segno, CqlColumnTypes type, UL len, US colNo, bool desc );
	NI Assign( DatabaseHandle&, IndexKeyDescriptor& );
	NI ChangeRootPointer( DatabaseHandle&, FileManager* file, RECID rootLoc );
	void clearDirty( void ) { dirty_ = false; }
	NI CreateElementFromSegments( DatabaseHandle&, pNodeElement*, RECID );
	pNode CurrentNode( void ) { return currentNode; }
	RECID CurrentNodeLocation( void ) { return currentNodeLocation; }
	pAbstractSegmentDescriptor CurrentSegment( void ) { return currentSegment; }
	void DecrementCurrentElementNumber( void ) { currentElementNumber--; }
	void descriptorLocation( RECID dl ) { descriptorLocation_ = dl; }
	bool dirty( void ) { return dirty_; }
	NI FirstSegment( DatabaseHandle& );
	NI GetSegment( DatabaseHandle&, pUC key );
	void IncrementCurrentElementNumber( void ) { currentElementNumber++; }
	bool lengthIndex( void ) { return lengthIndex_; }
	UL maximumKeyLength( void ) { return maximumKeyLength_; }
	void maximumKeyLength( UL mkl ) { maximumKeyLength_ = mkl; }
	NI NextSegment( void );
	NI Read( DatabaseHandle&, FileManager& );
	NI ReadSegment( ColumnDescriptor **seg, FileManager* fmgr );
	void remove( AbstractDatabaseHandle&, MemoryIndex&, RECID& );
	void ReturnToCurrentElement( pNode );
	RECID RootLocation( void ) { return rootLocation; }
	void SetCurrentNode( pNode node );
	void SetCurrentElementNumber( void );
	void SetCurrentElementNumber( UNI eno ) { currentElementNumber = eno; }
	void setDirty( void ) { dirty_ = true; }
	void setLengthIndex( void ) { lengthIndex_ = true; }
	void SetRootLocation( RECID loc ) { rootLocation = loc; }
	NI SetSegment( DatabaseHandle&, pUC key );
	NI SetSegment( DatabaseHandle&, ColumnDescriptor* );
	NI Write( DatabaseHandle&, FileManager*, Node& );
	NI Write( DatabaseHandle&, FileManager*, Node&, RECID );
	NI ZeroSegmentValues( void );
};

typedef IndexKeyDescriptor *pIndexKeyDescriptor;


#endif  //  __IndexKeyDescriptor_h
