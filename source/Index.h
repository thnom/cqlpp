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


#ifndef __Index_h
#define __Index_h


class Index : public NodeIndex, public KeySearchConstants, public AccessorTypes, public CqlConstants, public ErrorConstants
{
	pIndexKeyDescriptor currentKey;
	FileManager* file;
	bool fileOpen_;
	IndexHeader header;
	CqlString indexName_;
	AccessorList keys_;
	UNI segmentsToCompare_;
	bool temporary_;
	UNI transactionCounter;

	NI FindKeyPosition( DatabaseHandle&, pNode*, pNodeElement );
	NI Key( DatabaseHandle&, UL );

	void CheckDescendents( DatabaseHandle&, pNode, pUL );
	void CheckNode( DatabaseHandle&, pNode, RECID, pUL );

public :

	Index( void );
	virtual ~Index( void );

	NI AddElementToNode( DatabaseHandle&, pNode, pNodeElement, NI = CQL_NO );
	NI AddIndexMember( DatabaseHandle&, pIndexKeyDescriptor );
	NI AddKey( DatabaseHandle&, RECID pos );
	NI AddSegment( DatabaseHandle& /*hDb*/, US /*segmentNumber*/, CqlColumnTypes /*type*/, UL /*len*/, US /*columnNumber*/, bool /*descending*/ );
	NI Assign( DatabaseHandle&, Index& );
	NI BeginCreate( pNC name, NI tempstep = CQL_NO );
	NI BeginFind( DatabaseHandle&, UL keyNumber );
	NI beginKey( DatabaseHandle&, NI duplicatesAllowed = CQL_NO );
	NI BeginKeyOperation( DatabaseHandle&, UL keyNumber );
	void CheckBtreeIndex( DatabaseHandle&, pUL = ((pUL)0) );
	NI Close( DatabaseHandle& );
	UL countEqual( DatabaseHandle& );
	UL countGreater( DatabaseHandle& );
	UL countGreaterOrEqual( DatabaseHandle& );
	UL countLess( DatabaseHandle& );
	UL countLessOrEqual( DatabaseHandle& );
	pIndexKeyDescriptor CurrentKey( void ) { return currentKey; }
	void DecrementTransactionCounter( void ) { transactionCounter--; }
	void deleteCurrentKey( DatabaseHandle& );
	NI DeleteElement( DatabaseHandle&, pNode, pNodeElement );
	NI DeleteElementFromNode( DatabaseHandle&, pNode, pNodeElement );
	NI DeleteIndexMember( DatabaseHandle&, UNI );
	NI deleteKey( DatabaseHandle&, Accessor*, RECID );
	NI DeleteNode( DatabaseHandle&, pNode );
	NI DeleteNode( DatabaseHandle&, RECID );
	NI DeleteTree( DatabaseHandle&, RECID );
	void Dump( DatabaseHandle& );
	void DumpKeyNode( DatabaseHandle&, RECID loc, UL& );
	NI EndCreate( DatabaseHandle& /*hDb*/, TableType /*type*/ );
	NI EndKey( DatabaseHandle& );
	FileManager& File( void ) { return *file; }
	bool find( DatabaseHandle&, IndexKeyDescriptor::SearchType );
	bool findEqual( DatabaseHandle& );
	bool findGreater( DatabaseHandle& );
	bool findGreaterOrEqual( DatabaseHandle& );
	bool findLessThan( DatabaseHandle& );
	bool findLessThanOrEqual( DatabaseHandle& );
	bool firstKey( DatabaseHandle& );
	NI FlushDirtyNodes( DatabaseHandle& );
	NI GetSegment( DatabaseHandle&, pUC key );
	NI GetNewNode( DatabaseHandle&, pNode*, NI, NI );
	IndexHeader& Header( void ) { return header; }
	void IncrementTransactionCounter( void ) { transactionCounter++; }
	CqlString& indexName( void ) { return indexName_; }
	US InitialNodeSpace( void );
	AccessorList& keys( void ) { return keys_; }
	bool lastKey( DatabaseHandle& );
	bool nextKey( DatabaseHandle& );
	NI Open( DatabaseHandle&, const CqlString& name );
	bool previousKey( DatabaseHandle& );
	NI ReadNode( DatabaseHandle&, pNode*, RECID loc );
	NI RollbackDirtyNodes( void );
	bool searchForKey( DatabaseHandle&, pNodeElement /*element*/, bool /*compareRecordPosition*/, IndexKeyDescriptor::SearchType );
	void segmentsToCompare( UNI nsegs ) { segmentsToCompare_ = nsegs; }
	NI SetSegment( DatabaseHandle&, pUC key );
	NI SetSegment( DatabaseHandle&, pAbstractColumnDescriptor );
	void setTemporary( void ) { temporary_ = true; }
	bool temporary( void ) { return temporary_; }
	UNI TransactionCounter( void ) { return transactionCounter; }
	NI UpdateParentCounts( DatabaseHandle&, pNode );
	void ZeroElementUseFlags( DatabaseHandle&, pNode );
};

typedef Index *pIndex;


#endif  //  __Index_h
