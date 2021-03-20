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


#ifndef __MemoryIndexNode_h
#define __MemoryIndexNode_h


class MemoryIndexNode : public CqlConstants, public MemoryIndexConstants
{
    MemoryIndexNode *leftChild_;
    MemoryIndexNode *rightChild_;
    MemoryIndexNode *parent_;

	UL rightTreeLevel_;
	UL leftTreeLevel_;
	UL treeLevel_;

    enum BalanceFactors balanceFactor_;

    BFT isLeftChild_ : 1;
    BFT rootNode_ : 1;

public :

	MemoryIndexNode( void );
	virtual ~MemoryIndexNode( void );

    BFT checked_ : 1;
    BFT multipleOccurances_ : 1;

	MemoryIndexNode& operator = ( MemoryIndexNode& );

    enum BalanceFactors balanceFactor( void ) { return balanceFactor_; }
    void clearIsLeftChild( void ) { isLeftChild_ = CQL_NO; }
	NI checkNodes( MemoryIndexNode *parent, NI left );
    void clearRootNode( void ) { rootNode_ = CQL_NO; }
	void destroyNode( void );
	void dumpToLog( void );
    void incrementLeftTreeLevel( void ) { leftTreeLevel_++; }
    void incrementRightTreeLevel( void ) { rightTreeLevel_++; }
    void incrementTreeLevel( void ) { treeLevel_++; }
    NI isLeftChild( void ) { return isLeftChild_; }
    NI isRootNode( void ) { return rootNode_; }
    MemoryIndexNode *leftChild( void ) { return leftChild_; }
    UL leftTreeLevel( void ) { return leftTreeLevel_; }
    void markChildren( MemoryIndexNode *parent, NI root, NI left );
    void markNotChecked( void );
    MemoryIndexNode *parent( void ) { return parent_; }
    MemoryIndexNode *rightChild( void ) { return rightChild_; }
    UL rightTreeLevel( void ) { return rightTreeLevel_; }
    void setBalanceFactor( enum BalanceFactors balFactor ) { balanceFactor_ = balFactor; }
    void setIsLeftChild( void ) { isLeftChild_ = CQL_YES; }
    void setLeftChild( MemoryIndexNode *lc ) { leftChild_ = lc; }
    void setLeftTreeLevel( UL level ) { leftTreeLevel_ = level; }
    void setParent( MemoryIndexNode *p ) { parent_ = p; }
    void setRightChild( MemoryIndexNode *rc ) { rightChild_ = rc; }
    void setRightTreeLevel( UL level ) { rightTreeLevel_ = level; }
    void setRootNode( void ) { rootNode_ = CQL_YES; }
    void setTreeLevel( UL level ) { treeLevel_ = level; }
	UNI treeDepth( void );
    UL treeLevel( void ) { return treeLevel_; }

    virtual CqlConstants::CompareResult compareKeys( MemoryIndexNode *node2 ) = 0;
	virtual void releaseMemory( void ) = 0;
};

typedef MemoryIndexNode *pMemoryIndexNode;


#endif  //  __MemoryIndexNode_h
