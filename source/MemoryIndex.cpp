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


#include "CqlCommonInclude.h"


MemoryIndex::MemoryIndex( void ) : root_( ((pMemoryIndexNode)0) ), currentNode_( ((pMemoryIndexNode)0) ), currentPosition_( 0 )
{
}


MemoryIndex::~MemoryIndex( void )
{
	destroyIndex();
}


void MemoryIndex::destroyIndex( void )
{
	if( !root_ )
		return;

	root_->destroyNode();
	delete root_;
	root_ = currentNode_ = ((pMemoryIndexNode)0);
}


NI MemoryIndex::nextNode( void )
{
	return getKeyByPosition( currentPosition_ + 1 );
}


NI MemoryIndex::firstNode( void )
{
	pMemoryIndexNode node;

	if( !root_ )
		return CQL_NOT_FOUND;

	node = root_;
	while( node->leftChild() )
		node = node->leftChild();

	currentNode_ = node;
	currentPosition_ = 0;
	return CQL_SUCCESS;
}


NI MemoryIndex::addIndexNode( pMemoryIndexNode newNode )
{
	pMemoryIndexNode originalRoot, node, node2, rebalance, father, treeNode, par, rebalanceChild, node2Child;
	CqlConstants::CompareResult rebalanceCompare, compareResult;
	MemoryIndexNode::BalanceFactors rebalanceTemp;
	NI loop, isLeft;

	if( !newNode )
		throw MemoryIndexException( __FILE__, __LINE__ );

	if( memoryIndexDumping == CQL_YES )
		dumpToLog();

	originalRoot = root_;

	if( !root_ )
	{
		root_ = newNode;
		newNode->setRootNode();

		if( memoryIndexDumping == CQL_YES )
			dumpToLog();

		return CQL_SUCCESS;
	}

	//  modify the tree
	rebalance = node = root_;
	father = ((pMemoryIndexNode)0);

	//  algorithm step A2

	for( loop = CQL_YES; loop; )
	{
		switch( newNode->compareKeys( node ) )
		{
		case CqlConstants::THIS_LESS_THAN_OTHER :
			treeNode = node->leftChild();
			if( !treeNode )
			{
				node->setLeftChild( newNode );
				newNode->setParent( node );
				newNode->setIsLeftChild();
				loop = CQL_NO;
			}
			else
			{
				if( treeNode->balanceFactor() != BALANCED )
				{
					father = node;
					rebalance = treeNode;
				}

				node = treeNode;
			}
			break;

		case CqlConstants::THIS_GREATER_THAN_OTHER :
	    case CqlConstants::THIS_EQUAL_TO_OTHER :
			treeNode = node->rightChild();

			if( !treeNode )
			{
				node->setRightChild( newNode );
				newNode->setParent( node );
				newNode->clearIsLeftChild();
				loop = CQL_NO;
			}
			else
			{
				if( treeNode->balanceFactor() != BALANCED )
				{
					father = node;
					rebalance = treeNode;
				}

				node = treeNode;
			}
			break;

		case CqlConstants::COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	//  adjust balance factors

	switch( ( rebalanceCompare = newNode->compareKeys( rebalance ) ) )
	{
	case CqlConstants::THIS_LESS_THAN_OTHER :
		node = node2 = rebalance->leftChild();
		rebalance->incrementLeftTreeLevel();
		rebalance->incrementTreeLevel();

		//  ripple up the tree, increasing tree levels;

		for( isLeft = rebalance->isLeftChild(), par = rebalance->parent(); par; par = par->parent() )
		{
			if( isLeft )
				par->incrementLeftTreeLevel();
			else
				par->incrementRightTreeLevel();

			par->incrementTreeLevel();

			if( par->isLeftChild() )
				isLeft = CQL_YES;
			else
				isLeft = CQL_NO;
		}
		break;

	case CqlConstants::THIS_GREATER_THAN_OTHER :
    case CqlConstants::THIS_EQUAL_TO_OTHER :
		node = node2 = rebalance->rightChild();
		rebalance->incrementRightTreeLevel();
		rebalance->incrementTreeLevel();

		for( isLeft = rebalance->isLeftChild(), par = rebalance->parent(); par; par = par->parent() )
		{
			if( isLeft )
				par->incrementLeftTreeLevel();
			else
				par->incrementRightTreeLevel();

			par->incrementTreeLevel();

			if( par->isLeftChild() )
				isLeft = CQL_YES;
			else
				isLeft = CQL_NO;
		}
		break;

	default :
		throw MemoryIndexException( __FILE__, __LINE__ );
	}

	while( node != newNode )
	{
		compareResult = newNode->compareKeys( node );
		switch( compareResult )
		{
		case CqlConstants::THIS_LESS_THAN_OTHER :
			node->setBalanceFactor( LEFT_BIGGER );
			node->incrementLeftTreeLevel();
			node->incrementTreeLevel();
			node = node->leftChild();
			break;

		case CqlConstants::THIS_GREATER_THAN_OTHER :
		case CqlConstants::THIS_EQUAL_TO_OTHER :
			node->setBalanceFactor( RIGHT_BIGGER );
			node->incrementRightTreeLevel();
			node->incrementTreeLevel();
			node = node->rightChild();
			break;

		case CqlConstants::COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	if( memoryIndexDumping == CQL_YES )
		dumpToLog();

	//  balance factors adjusted, now rebalance tree
	switch( rebalanceCompare )
	{
	case CqlConstants::THIS_LESS_THAN_OTHER :
		rebalanceTemp = LEFT_BIGGER;
		break;

    case CqlConstants::THIS_GREATER_THAN_OTHER :
    case CqlConstants::THIS_EQUAL_TO_OTHER :
		rebalanceTemp = RIGHT_BIGGER;
		break;

	default :
		throw MemoryIndexException( __FILE__, __LINE__ );
	}

	if( rebalance->balanceFactor() == BALANCED )
	{
		//  tree was balanced, now difference is one level, so do nothing
		rebalance->setBalanceFactor( rebalanceTemp );
		if( indexDebugging == CQL_YES )
			checkIndex();

		if( memoryIndexDumping == CQL_YES )
			dumpToLog();

		return CQL_SUCCESS;
	}

	if( rebalanceTemp == LEFT_BIGGER && rebalance->balanceFactor() == RIGHT_BIGGER
	   || rebalanceTemp == RIGHT_BIGGER && rebalance->balanceFactor() == LEFT_BIGGER )
	{
		//  adding node made tree more balanced
		rebalance->setBalanceFactor( BALANCED );

		if( indexDebugging == CQL_YES )
			checkIndex();

		if( memoryIndexDumping == CQL_YES )
			dumpToLog();

		return CQL_SUCCESS;
	}

	if( node2->balanceFactor() == rebalanceTemp )
	{
		//  single rotation required
		node = node2;
		switch( rebalanceTemp )
		{
		case LEFT_BIGGER :
			rebalance->setLeftChild( node2->rightChild() );
			rebalanceChild = rebalance->leftChild();
			if( rebalanceChild )
			{
				rebalanceChild->setParent( rebalance );
				rebalanceChild->setIsLeftChild();
			}
			node2->setRightChild( rebalance );
			rebalance->setParent( node2 );
			rebalance->clearIsLeftChild();
			rebalance->setLeftTreeLevel( node2->rightTreeLevel() );
			rebalance->setTreeLevel( rebalance->leftTreeLevel() + rebalance->rightTreeLevel() );
			node2->setRightTreeLevel( rebalance->treeLevel() + 1 );
			node2->setTreeLevel( node2->leftTreeLevel() + node2->rightTreeLevel() );
			break;

		case RIGHT_BIGGER :
		case BALANCED :
			rebalance->setRightChild( node2->leftChild() );
			rebalanceChild = rebalance->rightChild();
			if( rebalanceChild )
			{
				rebalanceChild->setParent( rebalance );
				rebalanceChild->clearIsLeftChild();
			}

			node2->setLeftChild( rebalance );
			rebalance->setParent( node2 );
			rebalance->setIsLeftChild();

			rebalance->setRightTreeLevel( node2->leftTreeLevel() );
			rebalance->setTreeLevel( rebalance->leftTreeLevel() + rebalance->rightTreeLevel() );
			node2->setLeftTreeLevel( rebalance->treeLevel() + 1 );
			node2->setTreeLevel( node2->leftTreeLevel() + node2->rightTreeLevel() );
		}

		rebalance->setBalanceFactor( BALANCED );
		node2->setBalanceFactor( BALANCED );
	}
	else
	{
		//  double rotation required
		switch( rebalanceTemp )
		{
		case LEFT_BIGGER :
			node = node2->rightChild();
			node->clearIsLeftChild();
			node2->setRightChild( node->leftChild() );
			if( node2->rightChild() )
			{
				node2Child = node2->rightChild();
				node2Child->setParent( node2 );
				node2Child->clearIsLeftChild();
			}
			node->setLeftChild( node2 );
			if( node2 )
			{
				node2->setParent( node );
				node2->setIsLeftChild();
			}
			rebalance->setLeftChild( node->rightChild() );
			if( rebalance->leftChild() )
			{
				rebalanceChild = rebalance->leftChild();
				rebalanceChild->setParent( rebalance );
				rebalanceChild->setIsLeftChild();
			}
			node->setRightChild( rebalance );
			rebalance->setParent( node );
			rebalance->clearIsLeftChild();

			rebalance->setLeftTreeLevel( node->rightTreeLevel() );
			rebalance->setTreeLevel( rebalance->leftTreeLevel() + rebalance->rightTreeLevel() );
			node->setRightTreeLevel( rebalance->treeLevel() + 1 );

			node2->setRightTreeLevel( node->leftTreeLevel() );
			node2->setTreeLevel( node2->leftTreeLevel() + node2->rightTreeLevel() );
			node->setLeftTreeLevel( node2->treeLevel() + 1 );

			node->setTreeLevel( node->leftTreeLevel() + node->rightTreeLevel() );
			break;

		case RIGHT_BIGGER :
		case BALANCED :
			node = node2->leftChild();
			node2->setLeftChild( node );
			node->setIsLeftChild();
			node2->setLeftChild( node->rightChild() );
			if( node2->leftChild() )
			{
				node2Child = node2->leftChild();
				node2Child->setParent( node2 );
				node2Child->setIsLeftChild();
			}
			node->setRightChild( node2 );
			if( node2 )
			{
				node2->setParent( node );
				node2->clearIsLeftChild();
			}
			rebalance->setRightChild( node->leftChild() );
			if( rebalance->rightChild() )
			{
				rebalanceChild = rebalance->rightChild();
				rebalanceChild->setParent( rebalance );
				rebalanceChild->clearIsLeftChild();
			}
			node->setLeftChild( rebalance );
			rebalance->setParent( node );
			rebalance->setIsLeftChild();
			rebalance->setRightTreeLevel( node->leftTreeLevel() );
			rebalance->setTreeLevel( rebalance->leftTreeLevel() + rebalance->rightTreeLevel() );
			node->setLeftTreeLevel( rebalance->treeLevel() + 1 );
			node2->setLeftTreeLevel( node->rightTreeLevel() );
			node2->setTreeLevel( node2->leftTreeLevel() + node2->rightTreeLevel() );
			node->setRightTreeLevel( node2->treeLevel() + 1 );
			node->setTreeLevel( node->leftTreeLevel() + node->rightTreeLevel() );
		}

		if( node->balanceFactor() == rebalanceTemp )
		{
			if( rebalanceTemp == LEFT_BIGGER )
				rebalance->setBalanceFactor( RIGHT_BIGGER );
			else if( rebalanceTemp == RIGHT_BIGGER )
				rebalance->setBalanceFactor( LEFT_BIGGER );
			else
				rebalance->setBalanceFactor( BALANCED );
			node2->setBalanceFactor( BALANCED );
		}
		else if( node->balanceFactor() == BALANCED )
		{
			rebalance->setBalanceFactor( BALANCED );
			node2->setBalanceFactor( BALANCED );
		}
		else
		{
			rebalance->setBalanceFactor( BALANCED );
			node2->setBalanceFactor( rebalanceTemp );
		}
		node->setBalanceFactor( BALANCED );
	}

	if( father )
	{
		if( rebalance == father->rightChild() )
		{
			father->setRightChild( node );
			if( node )
			{
				node->setParent( father );
				node->clearIsLeftChild();
			}
			father->setRightTreeLevel( node->treeLevel() + 1 );
			father->setTreeLevel( father->leftTreeLevel() + father->rightTreeLevel() );
		}
		else
		{
			father->setLeftChild( node );
			if( node )
			{
				node->setParent( father );
				node->setIsLeftChild();
			}
			father->setLeftTreeLevel( node->treeLevel() + 1 );
			father->setTreeLevel( father->leftTreeLevel() + father->rightTreeLevel() );
		}
	}

	else
	{
		root_ = node;
		root_->setRootNode();
		root_->clearIsLeftChild();

		node->setParent( ((pMemoryIndexNode)0) );
		node->setRootNode();
		if( node != originalRoot )
			originalRoot->clearRootNode();
	}

	if( indexDebugging == CQL_YES )
		checkIndex();

	if( memoryIndexDumping == CQL_YES )
		dumpToLog();

	return CQL_SUCCESS;
}


NI MemoryIndex::findEqualKey( pMemoryIndexNode tempNode )
{
	NI rc;

	rc = findGreaterOrEqualKey( tempNode );
	if( rc != CQL_SUCCESS )
		return rc;

	if( tempNode->compareKeys( currentNode_ ) != CqlConstants::THIS_EQUAL_TO_OTHER )
		return CQL_NOT_FOUND;

	return CQL_SUCCESS;
}


NI MemoryIndex::getKeyByPosition( UL targetPosition )
{
	UL currentTreeLevel, localTargetPosition = targetPosition;
	pMemoryIndexNode node;

	node = root_;

	for( ; ; )
	{
		if( !node )
			return CQL_NOT_FOUND;

		currentTreeLevel = node->leftTreeLevel();

		if( localTargetPosition == currentTreeLevel )
		{
			//  found
			currentNode_ = node;
			currentPosition_ = targetPosition;
			return CQL_SUCCESS;
		}
		else if( localTargetPosition < currentTreeLevel )
			node = node->leftChild();
		else
		{
			//  position is greater
			localTargetPosition -= currentTreeLevel + 1;
			node = node->rightChild();
		}
	}
}


NI MemoryIndex::checkIndex( void )
{
	UNI leftTreeDepth, rightTreeDepth;

	if( !root_ )
		return CQL_SUCCESS;

	root_->markNotChecked();

	if( root_->leftChild() )
		leftTreeDepth = root_->leftChild()->treeDepth();
	else
		leftTreeDepth = 0;

	if( root_->rightChild() )
		rightTreeDepth = root_->rightChild()->treeDepth();
	else
		rightTreeDepth = 0;

	switch( root_->balanceFactor() )
	{
	case BALANCED :
		if( leftTreeDepth != rightTreeDepth )
			assert( 0 );
		break;

	case LEFT_BIGGER :
		if( leftTreeDepth - rightTreeDepth != 1 )
			assert( 0 );
		break;

	case RIGHT_BIGGER :
		if( rightTreeDepth - leftTreeDepth != 1 )
			assert( 0 );
		break;
	}

	if( root_->leftChild() )
		root_->leftChild()->checkNodes( root_, CQL_YES );

	if( root_->rightChild() )
		root_->rightChild()->checkNodes( root_, CQL_NO );

	return CQL_SUCCESS;
}


NI MemoryIndex::findGreaterOrEqualKey( pMemoryIndexNode tempNode )
{
	NI rc;
	if( !root_ )
		return CQL_NOT_FOUND;

	findLessThanKey( tempNode );
	if( currentPosition_ == -1 || tempNode->compareKeys( currentNode_ ) != CqlConstants::THIS_EQUAL_TO_OTHER )
		rc = getKeyByPosition( currentPosition_ + 1 );
	else
		rc = CQL_SUCCESS;

	return rc;
}


void MemoryIndex::dumpToLog( void )
{
	*hAEnv << "Dumping memory index .................................\n\n";
	*hAEnv << "root_ = " << root_ << "\n";
	*hAEnv << "currentNode_ = " << currentNode_ << "\n";
	*hAEnv << "currentPosition_ = " << currentPosition_ << "\n";

	//
	//  dump the nodes
	if( root_ )
		root_->dumpToLog();

	*hAEnv << "\n\n";
}


//  if found, result is in currentNode_
NI MemoryIndex::findLessThanKey( pMemoryIndexNode tempNode )
{
	pMemoryIndexNode node, closestLowerNode = ((pMemoryIndexNode)0);

	if( !root_ )
	{
		currentNode_ = ((pMemoryIndexNode)0);
		return CQL_NOT_FOUND;
	}

	node = root_;

	for( ; ; )
	{
		if( !node )
		{
			if( closestLowerNode )
			{
				currentNode_ = closestLowerNode;
				currentPosition_ = calculatePosition( closestLowerNode );
				return CQL_SUCCESS;
			}
			else
			{
				currentNode_ = ((pMemoryIndexNode)0);
				currentPosition_ = -1;
				return CQL_NOT_FOUND;
			}
		}

		switch( tempNode->compareKeys( node ) )
		{
		case CqlConstants::THIS_LESS_THAN_OTHER :
		case CqlConstants::THIS_EQUAL_TO_OTHER :
			node = node->leftChild();
			break;

		case CqlConstants::THIS_GREATER_THAN_OTHER :
			closestLowerNode = node;
			node = node->rightChild();
			break;

		case CqlConstants::COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}
}


L MemoryIndex::calculatePosition( pMemoryIndexNode node )
{
	pMemoryIndexNode par;

	if( !node )
		return ((UL)0);

	if( node->isRootNode() )
		return node->leftTreeLevel();

	par = node->parent();

	if( node->isLeftChild() )
		return calculatePosition( par ) - ( 1 + node->rightTreeLevel() );
	else
		return calculatePosition( par ) + ( node->leftTreeLevel() + 1 );
}


MemoryIndex& MemoryIndex::operator = ( MemoryIndex& other )
{
	root_ = other.root_;
	currentNode_ = other.currentNode_;
	currentPosition_ = other.currentPosition_;
	return *this;
}


NI MemoryIndex::findKey( pMemoryIndexNode tempNode )
{
	pMemoryIndexNode node;

	if( !root_ )
	{
		currentNode_ = ((pMemoryIndexNode)0);
		return CQL_NOT_FOUND;
	}

	node = root_;

	for( ; ; )
	{
		switch( tempNode->compareKeys( node ) )
		{
		case CqlConstants::THIS_EQUAL_TO_OTHER :
			//  key found
			currentNode_ = node;
			currentPosition_ = calculatePosition( node );
			return CQL_SUCCESS;

		case CqlConstants::THIS_LESS_THAN_OTHER :
			//  move left
			node = node->leftChild();
			break;

		case CqlConstants::THIS_GREATER_THAN_OTHER :
			//  move right
			node = node->rightChild();
			break;

		case CqlConstants::COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}
}


void MemoryIndex::setBalanceFactors( pMemoryIndexNode node )
{
	UNI leftDepth, rightDepth;

	if( node->leftChild() )
	{
		setBalanceFactors( node->leftChild() );
		leftDepth = node->leftChild()->treeDepth();
	}
	else
		leftDepth = 0;

	if( node->rightChild() )
	{
		setBalanceFactors( node->rightChild() );
		rightDepth = node->rightChild()->treeDepth();
	}
	else
		rightDepth = 0;

	if( leftDepth == rightDepth )
		node->setBalanceFactor( BALANCED );
	else if( leftDepth > rightDepth )
		node->setBalanceFactor( LEFT_BIGGER );
	else
		node->setBalanceFactor( RIGHT_BIGGER );
}


UNI MemoryIndex::countNodes( pMemoryIndexNode node )
{
	UNI leftCount, rightCount;

	if( !node )
		return 0;

	leftCount = countNodes( node->leftChild() );
	rightCount = countNodes( node->rightChild() );
	return leftCount + rightCount + 1;
}


NI MemoryIndex::adjustBalanceFactors( pMemoryIndexNode rebalance )
{
	pMemoryIndexNode node, par, immediateChild, rebalanceparent;
	UNI leftDepth, rightDepth, difference, nodeCount1 = 0, nodeCount2;
	NI rebalanceWasleftChild;

	if( !rebalance )
		return CQL_SUCCESS;

	if( indexDebugging == CQL_YES )
	{
		//
		//  count the nodes
		//
		nodeCount1 = countNodes( root_ );
	}

	if( rebalance->leftChild() )
		leftDepth = rebalance->leftChild()->treeDepth();
	else
		leftDepth = 0;
	if( rebalance->rightChild() )
		rightDepth = rebalance->rightChild()->treeDepth();
	else
		rightDepth = 0;
	if( leftDepth > rightDepth )
		difference = leftDepth - rightDepth;
	else
		difference = rightDepth - leftDepth;

	if( difference <= 1 )
		return adjustBalanceFactors( rebalance->parent() );

	rebalanceparent = rebalance->parent();
	rebalanceWasleftChild = rebalance->isLeftChild();

	//
	//  tree is unbalanced.
	//
	if( leftDepth > rightDepth )
	{
		//
		//  need to rotate counterclockwise
		//
		node = immediateChild = rebalance->leftChild();
		while( node->rightChild() )
			node = node->rightChild();

		if( node != immediateChild )
		{
			par = node->parent();
			par->setRightChild( node->leftChild() );
			if( par->rightChild() )
			{
				par->rightChild()->setParent( par );
				par->rightChild()->clearIsLeftChild();
			}
		}
		node->setRightChild( rebalance );
		rebalance->clearIsLeftChild();
		rebalance->setParent( node );

		if( node != immediateChild )
		{
			node->setLeftChild( rebalance->leftChild() );
			if( rebalance->leftChild() )
			{
				rebalance->leftChild()->setParent( node );
				rebalance->leftChild()->setIsLeftChild();
			}
		}
		rebalance->setLeftChild( ((pMemoryIndexNode)0) );
		rebalance->clearRootNode();
		if( !rebalanceparent )
		{
			node->setRootNode();
			node->clearIsLeftChild();
			node->setParent( ((pMemoryIndexNode)0) );
			root_ = node;
		}
		else
		{
			if( rebalanceWasleftChild == CQL_YES )
			{
				rebalanceparent->setLeftChild( node );
				node->setIsLeftChild();
			}
			else
			{
				rebalanceparent->setRightChild( node );
				node->clearIsLeftChild();
			}
			node->setParent( rebalanceparent );
		}
			
		setBalanceFactors( root_ );
		if( indexDebugging == CQL_YES )
		{
			nodeCount2 = countNodes( root_ );
			if( nodeCount1 != nodeCount2 )
				assert( 0 );
		}
	}

	else
	{
		node = immediateChild = rebalance->rightChild();
		while( node->leftChild() )
			node = node->leftChild();

		if( node != immediateChild )
		{
			par = node->parent();
			par->setLeftChild( node->rightChild() );
			if( par->leftChild() )
			{
				par->leftChild()->setParent( par );
				par->leftChild()->setIsLeftChild();
			}
		}
		node->setLeftChild( rebalance );
		rebalance->setParent( node );
		rebalance->setIsLeftChild();
		if( node != immediateChild )
		{
			node->setRightChild( rebalance->rightChild() );
			if( rebalance->rightChild() )
			{
				rebalance->rightChild()->setParent( node );
				rebalance->rightChild()->clearIsLeftChild();
			}
		}
		rebalance->setRightChild( ((pMemoryIndexNode)0) );
		rebalance->clearRootNode();
		if( !rebalanceparent )
		{
			node->setRootNode();
			node->clearIsLeftChild();
			node->setParent( ((pMemoryIndexNode)0) );
			root_ = node;
		}
		else
		{
			if( rebalanceWasleftChild == CQL_YES )
			{
				rebalanceparent->setLeftChild( node );
				node->setIsLeftChild();
			}
			else
			{
				rebalanceparent->setRightChild( node );
				node->clearIsLeftChild();
			}
			node->setParent( rebalanceparent );
		}
		setBalanceFactors( root_ );
		if( indexDebugging == CQL_YES )
		{
			nodeCount2 = countNodes( root_ );
			if( nodeCount1 != nodeCount2 )
				assert( 0 );
		}
	}

	return adjustBalanceFactors( rebalanceparent );
}


//  deletes the current node
NI MemoryIndex::deleteIndexNode( void )
{
	NI switchLeft, nodeToDeleteOnLeftSide = CQL_NO, needToRotateRootLeft = CQL_NO, needToRotateRootRight = CQL_NO;
	UNI nodeCount1 = 0, nodeCount2;
	pMemoryIndexNode nodeToDelete,
		nodeToSwitch,
		father,
		deleteparent,
		switchparent,
		tnode,
		immediateChild,
		newChildNode,
		newRoot,
		newRootparent;

	if( indexDebugging == CQL_YES )
	{
		checkIndex();
		nodeCount1 = countNodes( root_ );
	}

	if( memoryIndexDumping == CQL_YES )
		dumpToLog();

	nodeToDelete = currentNode_;

	if( nodeToDelete == root_ )
	{
		if( !root_->leftChild() )
		{
			//
			//  is root_ the entire tree?
			//
			if( !root_->rightChild() )
			{
				root_ = ((pMemoryIndexNode)0);
				nodeToDelete->releaseMemory();
				delete nodeToDelete;

				if( memoryIndexDumping == CQL_YES )
					dumpToLog();

				if( indexDebugging == CQL_YES )
				{
					nodeCount2 = countNodes( root_ );
					if( nodeCount2 != nodeCount1 - 1 )
						assert( 0 );
				}
				return CQL_SUCCESS;
			}

			//
			//  there can only be one level to the right child, since the tree would
			//  otherwise be unbalanced.
			//
			root_ = root_->rightChild();
			root_->setRootNode();
			root_->clearIsLeftChild();
			setBalanceFactors( root_ );
			root_->markChildren( ((pMemoryIndexNode)0), CQL_YES, CQL_NO );

			if( indexDebugging == CQL_YES )
				checkIndex();

			if( memoryIndexDumping == CQL_YES )
				dumpToLog();

			if( indexDebugging == CQL_YES )
			{
				nodeCount2 = countNodes( root_ );
				if( nodeCount2 != nodeCount1 - 1 )
					assert( 0 );
			}

			nodeToDelete->releaseMemory();
			delete nodeToDelete;
			return CQL_SUCCESS;
		}

		else if( !root_->rightChild() )
		{
			//  only one node - see note above
			root_ = root_->leftChild();
			root_->setRootNode();
			root_->clearIsLeftChild();
			setBalanceFactors( root_ );

			root_->markChildren( ((pMemoryIndexNode)0), CQL_YES, CQL_NO );

			if( memoryIndexDumping == CQL_YES )
				dumpToLog();

			if( indexDebugging == CQL_YES )
				checkIndex();

			if( indexDebugging == CQL_YES )
			{
				nodeCount2 = countNodes( root_ );
				if( nodeCount2 != nodeCount1 - 1 )
					assert( 0 );
			}

			nodeToDelete->releaseMemory();
			delete nodeToDelete;
			return CQL_SUCCESS;
		}

		//
		//  deleting root_ node, left and right subtrees both exist.
		//  Two cases, LEFT_BIGGER and RIGHT_BIGGER.  Within each of these, there
		//  are two cases:  preceding node is child of deleted node, or is not.
		switch( root_->balanceFactor() )
		{
		case LEFT_BIGGER :
			tnode = immediateChild = root_->leftChild();
			while( tnode->rightChild() )
				tnode = tnode->rightChild();

			if( tnode == immediateChild )
			{
				tnode->setRightChild( root_->rightChild() );
				if( root_->rightChild() )
					root_->rightChild()->setParent( tnode );
				tnode->setRootNode();
			}
			else
			{
				tnode->parent()->setRightChild( tnode->leftChild() );
				if( tnode->leftChild() )
				{
					tnode->leftChild()->setParent( tnode->parent() );
					tnode->leftChild()->clearIsLeftChild();
				}
				tnode->setRightChild( root_->rightChild() );
				if( root_->rightChild() )
					root_->rightChild()->setParent( tnode );
				tnode->setLeftChild( root_->leftChild() );
				if( root_->leftChild() )
					root_->leftChild()->setParent( tnode );
				tnode->setRootNode();
			}

			root_ = tnode;

			setBalanceFactors( root_ );
			root_->markChildren( ((pMemoryIndexNode)0), CQL_YES, CQL_NO );

			if( indexDebugging == CQL_YES )
				checkIndex();

			if( memoryIndexDumping == CQL_YES )
				dumpToLog();

			if( indexDebugging == CQL_YES )
			{
				nodeCount2 = countNodes( root_ );
				if( nodeCount2 != nodeCount1 - 1 )
					assert( 0 );
			}

			nodeToDelete->releaseMemory();
			delete nodeToDelete;
			return CQL_SUCCESS;

		case RIGHT_BIGGER :
		case BALANCED :
			tnode = immediateChild = root_->rightChild();
			while( tnode->leftChild() )
				tnode = tnode->leftChild();

			if( tnode == immediateChild )
				tnode->setLeftChild( root_->leftChild() );
			else
			{
				tnode->parent()->setLeftChild( tnode->rightChild() );
				if( tnode->parent()->leftChild() )
				{
					tnode->parent()->leftChild()->setIsLeftChild();
					tnode->parent()->leftChild()->setParent( tnode->parent() );
				}

				tnode->setRightChild( root_->rightChild() );
				if( tnode->rightChild() )
				{
					tnode->rightChild()->clearIsLeftChild();
					tnode->rightChild()->setParent( tnode );
				}

				tnode->setLeftChild( root_->leftChild() );
				if( tnode->leftChild() )
					tnode->leftChild()->setParent( tnode );
			}

			tnode->setRootNode();
			tnode->clearIsLeftChild();
			root_ = tnode;

			setBalanceFactors( root_ );
			root_->markChildren( ((pMemoryIndexNode)0), CQL_YES, CQL_NO );

			if( indexDebugging == CQL_YES )
				checkIndex();

			if( memoryIndexDumping == CQL_YES )
				dumpToLog();

			if( indexDebugging == CQL_YES )
			{
				nodeCount2 = countNodes( root_ );
				if( nodeCount2 != nodeCount1 - 1 )
					assert( 0 );
			}

			nodeToDelete->releaseMemory();
			delete nodeToDelete;
			return CQL_SUCCESS;
		}
	}

	//
	//  Determine which side of tree nodeToDelete is on
	//
	//  Initial assignment of nodeToDeleteOnLeftSide is needed in case the parent is the
	//  root_ node
	//
	for( tnode = nodeToDelete, nodeToDeleteOnLeftSide = tnode->isLeftChild();
		 tnode && tnode->isRootNode() == CQL_NO && tnode->parent()->isRootNode() == CQL_NO;
		 tnode = tnode->parent() )
	{
		nodeToDeleteOnLeftSide = tnode->isLeftChild();
	}
			
	if( !nodeToDelete->leftChild() )
	{
		if( root_->balanceFactor() != BALANCED )
		{
			if( nodeToDeleteOnLeftSide == CQL_YES && root_->balanceFactor() == RIGHT_BIGGER  )
			{
				needToRotateRootLeft = CQL_YES;
				needToRotateRootRight = CQL_NO;
			}
			else if( nodeToDeleteOnLeftSide == CQL_NO && root_->balanceFactor() == LEFT_BIGGER )
			{
				needToRotateRootLeft = CQL_NO;
				needToRotateRootRight = CQL_YES;
			}
		}
		else
			needToRotateRootLeft = needToRotateRootRight = CQL_NO;

		father = switchparent = nodeToDelete->parent();
		newChildNode = nodeToDelete->rightChild();

		if( newChildNode )
			newChildNode->setParent( father );

		if( nodeToDelete->isLeftChild() )
		{
			if( !father )
			{
				root_ = newChildNode;
				root_->setRootNode();
				root_->clearIsLeftChild();
			}
			else
			{
				father->setLeftChild( newChildNode );
				if( newChildNode )
					newChildNode->setIsLeftChild();
			}
		}
		else
		{
			if( !father )
			{
				root_ = newChildNode;
				root_->setRootNode();
				root_->clearIsLeftChild();
			}
			else
			{
				father->setRightChild( newChildNode );
				if( newChildNode )
					newChildNode->clearIsLeftChild();
			}
		}

		nodeToDelete->releaseMemory();
		delete nodeToDelete;

		if( needToRotateRootLeft == CQL_YES && root_->rightChild() )
		{
			if( memoryIndexDumping == CQL_YES )
				dumpToLog();

			newRoot = root_->rightChild();
			while( newRoot->leftChild() )
				newRoot = newRoot->leftChild();

			newRootparent = newRoot->parent();

			if( newRootparent->isRootNode() == CQL_NO )
			{
				newRootparent->setLeftChild( newRoot->rightChild() );
				if( newRoot->rightChild() )
				{
					newRoot->rightChild()->setIsLeftChild();
					newRoot->rightChild()->setParent( newRootparent );
				}
			}

			newRoot->setLeftChild( root_ );

			if( newRootparent->isRootNode() == CQL_NO )
			{
				newRoot->setRightChild( root_->rightChild() );
				root_->rightChild()->setParent( newRoot );
			}

			root_->setIsLeftChild();
			root_->clearRootNode();
			root_->setRightChild( ((pMemoryIndexNode)0) );
			root_->setParent( newRoot );

			newRoot->setRootNode();
			newRoot->setParent( ((pMemoryIndexNode)0) );
			root_ = newRoot;

			if( memoryIndexDumping == CQL_YES )
				dumpToLog();
		}
		else if( needToRotateRootRight == CQL_YES && root_->leftChild() )
		{
			if( memoryIndexDumping == CQL_YES )
				dumpToLog();

			newRoot = root_->leftChild();
			while( newRoot->rightChild() )
				newRoot = newRoot->rightChild();

			newRootparent = newRoot->parent();

			if( newRootparent->isRootNode() == CQL_NO )
			{
				newRootparent->setRightChild( newRoot->leftChild() );
				if( newRoot->leftChild() )
				{
					newRoot->leftChild()->clearIsLeftChild();
					newRoot->leftChild()->setParent( newRootparent );
				}
			}

			newRoot->setRightChild( root_ );

			if( newRootparent->isRootNode() == CQL_NO )
			{
				newRoot->setLeftChild( root_->leftChild() );
				root_->leftChild()->setParent( newRoot );
			}

			root_->clearIsLeftChild();
			root_->clearRootNode();
			root_->setLeftChild( ((pMemoryIndexNode)0) );
			root_->setParent( newRoot );

			newRoot->setRootNode();
			newRoot->setParent( ((pMemoryIndexNode)0) );
			root_ = newRoot;

			if( memoryIndexDumping == CQL_YES )
				dumpToLog();
		}
	}

	else if( !nodeToDelete->rightChild() )
	{
		if( root_->balanceFactor() != BALANCED )
		{
			if( nodeToDeleteOnLeftSide == CQL_YES && root_->balanceFactor() == RIGHT_BIGGER  )
			{
				needToRotateRootLeft = CQL_YES;
				needToRotateRootRight = CQL_NO;
			}
			else if( nodeToDeleteOnLeftSide == CQL_NO && root_->balanceFactor() == LEFT_BIGGER )
			{
				needToRotateRootLeft = CQL_NO;
				needToRotateRootRight = CQL_YES;
			}
		}
		else
			needToRotateRootLeft = needToRotateRootRight = CQL_NO;

		father = switchparent = nodeToDelete->parent();
		newChildNode = nodeToDelete->leftChild();

		if( newChildNode )
			newChildNode->setParent( father );

		if( nodeToDelete->isLeftChild() )
		{
			if( !father )
			{
				root_ = newChildNode;
				root_->setRootNode();
				root_->clearIsLeftChild();
			}
			else
			{
				father->setLeftChild( newChildNode );
				if( newChildNode )
					newChildNode->setIsLeftChild();
			}
		}
		else
		{
			if( !father )
			{
				root_ = newChildNode;
				root_->setRootNode();
				root_->clearIsLeftChild();
			}
			else
			{
				father->setRightChild( newChildNode );
				if( newChildNode )
					newChildNode->clearIsLeftChild();
			}
		}

		nodeToDelete->releaseMemory();
		delete nodeToDelete;

		if( needToRotateRootLeft == CQL_YES )
		{
			if( memoryIndexDumping == CQL_YES )
				dumpToLog();

			newRoot = root_->rightChild();
			while( newRoot->leftChild() )
				newRoot = newRoot->leftChild();

			newRootparent = newRoot->parent();

			if( newRootparent->isRootNode() == CQL_NO )
			{
				newRootparent->setLeftChild( newRoot->rightChild() );
				if( newRoot->rightChild() )
				{
					newRoot->rightChild()->setIsLeftChild();
					newRoot->rightChild()->setParent( newRootparent );
				}
			}

			newRoot->setLeftChild( root_ );
			
			if( newRootparent->isRootNode() == CQL_NO )
			{
				newRoot->setRightChild( root_->rightChild() );
				root_->rightChild()->setParent( newRoot );
			}

			root_->setIsLeftChild();
			root_->clearRootNode();
			root_->setRightChild( ((pMemoryIndexNode)0) );
			root_->setParent( newRoot );

			newRoot->setRootNode();
			newRoot->setParent( ((pMemoryIndexNode)0) );
			root_ = newRoot;

			if( memoryIndexDumping == CQL_YES )
				dumpToLog();
		}
		else if( needToRotateRootRight == CQL_YES )
		{
			if( memoryIndexDumping == CQL_YES )
				dumpToLog();

			newRoot = root_->leftChild();
			while( newRoot->rightChild() )
				newRoot = newRoot->rightChild();

			newRootparent = newRoot->parent();

			if( newRootparent->isRootNode() == CQL_NO )
			{
				newRootparent->setRightChild( newRoot->leftChild() );
				if( newRoot->leftChild() )
				{
					newRoot->leftChild()->clearIsLeftChild();
					newRoot->leftChild()->setParent( newRootparent );
				}
			}

			newRoot->setRightChild( root_ );
			if( newRootparent->isRootNode() == CQL_NO )
			{
				newRoot->setLeftChild( root_->leftChild() );
				root_->leftChild()->setParent( newRoot );
			}

			root_->clearIsLeftChild();
			root_->clearRootNode();
			root_->setLeftChild( ((pMemoryIndexNode)0) );
			root_->setParent( newRoot );

			newRoot->setRootNode();
			newRoot->setParent( ((pMemoryIndexNode)0) );
			root_ = newRoot;

			if( memoryIndexDumping == CQL_YES )
				dumpToLog();
		}
	}

	else
	{
		nodeToSwitch = nodeToDelete->rightChild();
		switchLeft = CQL_NO;

		while( nodeToSwitch->leftChild() )
		{
			nodeToSwitch = nodeToSwitch->leftChild();
			switchLeft = CQL_YES;
		}

		switchparent = nodeToSwitch->parent();
		deleteparent = nodeToDelete->parent();
		nodeToSwitch->setParent( deleteparent );

		if( nodeToDelete->isLeftChild() )
		{
			if( deleteparent )
			{
				deleteparent->setLeftChild( nodeToSwitch );
				if( nodeToSwitch )
					nodeToSwitch->setIsLeftChild();
			}
			else
			{
				//
				//  At this point nodeToSwitch is known to be not null, because
				//  right child was not null.
				//
				root_ = nodeToSwitch;
				root_->setRootNode();
				root_->clearIsLeftChild();
			}
		}
		else
		{
			if( deleteparent )
			{
				deleteparent->setRightChild( nodeToSwitch );
				if( nodeToSwitch )
					nodeToSwitch->clearIsLeftChild();
			}
			else
			{
				root_ = nodeToSwitch;
				root_->setRootNode();
				root_->clearIsLeftChild();
			}
		}

		nodeToSwitch->setLeftChild( nodeToDelete->leftChild() );
		nodeToDelete->leftChild()->setParent( nodeToSwitch );

		if( switchparent != nodeToDelete )
		{
			if( switchLeft == CQL_YES )
			{
				if( switchparent )
				{
					tnode = nodeToSwitch->rightChild();
					switchparent->setLeftChild( tnode );
					if( tnode )
					{
						tnode->setIsLeftChild();
						tnode->setParent( switchparent );
					}
				}
				else
				{
					root_ = nodeToSwitch->rightChild();
					root_->setRootNode();
					root_->clearIsLeftChild();
				}
			}
			else
			{
				if( switchparent )
				{
					tnode = nodeToSwitch->leftChild();
					switchparent->setRightChild( tnode );
					if( tnode )
					{
						tnode->clearIsLeftChild();
						tnode->setParent( switchparent );
					}
				}
				else
				{
					root_ = nodeToSwitch->leftChild();
					root_->setRootNode();
					root_->clearIsLeftChild();
				}
			}
			nodeToSwitch->setRightChild( nodeToDelete->rightChild() );
			if( nodeToSwitch->rightChild() )
				nodeToSwitch->rightChild()->setParent( nodeToSwitch );
		}
		else
			//
			//  this prevents sending the address of the deleted node to adjustBalanceFactors
			//
			switchparent = nodeToDelete->parent();

		nodeToDelete->releaseMemory();
		delete nodeToDelete;
	}

	if( memoryIndexDumping == CQL_YES )
		dumpToLog();

	if( adjustBalanceFactors( switchparent ) == CQL_FAILURE )
		return CQL_FAILURE;

	setBalanceFactors( root_ );

	if( indexDebugging == CQL_YES )
		checkIndex();

	if( root_ )
		root_->markChildren( ((pMemoryIndexNode)0), CQL_YES, CQL_NO );

	currentPosition_--;

	if( memoryIndexDumping == CQL_YES )
		dumpToLog();

	if( indexDebugging == CQL_YES )
	{
		nodeCount2 = countNodes( root_ );
		if( nodeCount2 != nodeCount1 - 1 )
			assert( 0 );
	}
	return CQL_SUCCESS;
}


NI MemoryIndex::lastNode( void )
{
	pMemoryIndexNode node;

	if( !root_ )
		return CQL_NOT_FOUND;

	node = root_;
	while( node->rightChild() )
		node = node->rightChild();

	currentNode_ = node;
	currentPosition_ = calculatePosition( node );
	return CQL_SUCCESS;
}


NI MemoryIndex::previousNode( void )
{
	if( currentPosition_ == 0 )
		return CQL_NOT_FOUND;

	return getKeyByPosition( currentPosition_ - 1 );
}


