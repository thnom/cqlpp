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


#include "CqlIsamInclude.h"


#define __CQL_FINE_GRAIN_DEBUGGING


Index::Index( void )
	: NodeIndex(),
	  currentKey( 0 ),
	  file( 0 ),
	  fileOpen_( false ),
	  header(), 
	  indexName_(),
	  keys_(),
	  segmentsToCompare_( 0 ),
	  temporary_( false ),
	  transactionCounter( 0 )
{
}


NI Index::Assign( DatabaseHandle& dbHandle, Index& other )
{
	*( static_cast< NodeIndex* >( this ) ) = other;

	if( other.currentKey )
	{
		Accessor *kd, *otherkd;
		for( otherkd = other.keys_.first(), kd = keys_.first(); otherkd; otherkd = other.keys_.next() )
		{
			if( otherkd == other.currentKey )
			{
				currentKey = dynamic_cast< IndexKeyDescriptor* >( kd );
				break;
			}
		}
	}
	else
		currentKey = 0;

	segmentsToCompare_ = other.segmentsToCompare_;

	if( other.file )
	{
		file = new FileManager( dbHandle, other.file->type() );
		if( !file )
			return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

		if( file->Assign( *other.file ) == CQL_FAILURE )
			return CQL_FAILURE;
	}

	if( header.Assign( dbHandle, other.header ) == CQL_FAILURE )
		return CQL_FAILURE;

	indexName_ = other.indexName_;
	keys_ = other.keys_;
	transactionCounter = other.transactionCounter;
	fileOpen_ = other.fileOpen_;
	temporary_ = other.temporary_;

	return CQL_SUCCESS;
}


NI Index::BeginCreate( pNC name, NI temp )
{
	indexName_ = name;
	if( temp )
		temporary_ = true;
	else
		temporary_ = false;
	return CQL_SUCCESS;
}


NI Index::beginKey( DatabaseHandle& dbHandle, NI duplicatesProhibited )
{
	AccessorTypes atype;
	if( duplicatesProhibited )
		atype = AccessorTypes( CQL_TREE_INDEX, CQL_NO_DUPLICATES );
	else
		atype = AccessorTypes( CQL_TREE_INDEX, CQL_DUPLICATES_ALLOWED );

	currentKey = new IndexKeyDescriptor( atype, static_cast< US >( keys_.size() ) );
	if( !currentKey )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

	keys_.add( currentKey );
	return CQL_SUCCESS;
}


NI Index::AddSegment( DatabaseHandle& dbHandle, US segno, CqlColumnTypes type, UL len, US colNo, bool desc )
{
	if( !currentKey )
		throw CreateSequenceException( __FILE__, __LINE__ );

	if( currentKey->AddSegment( dbHandle, segno, type, len, colNo, desc ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI Index::EndKey( DatabaseHandle& dbHandle )
{
	if( !currentKey )
		return dbHandle.returnError( CREATE_SEQUENCE, __FILE__, __LINE__ );

	currentKey = ((pIndexKeyDescriptor)0);
	return CQL_SUCCESS;
}


NI Index::EndCreate( DatabaseHandle& dbHandle, TableType type )
{
	UL loop;
	RECID tRoot;
	pNode node;

	if( fileOpen_ )
		return dbHandle.returnError( ATTACHED_TO_OPEN_FILE, __FILE__, __LINE__ );

	file = new FileManager( dbHandle, type );
	if( !file )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );
	if( temporary_ )
		file->type( CQL_CQL_TEMPORARY );

	dbHandle.addToIndexIndex( this );

	if( file->Create( indexName_ ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( header.Setup( dbHandle, hAEnv->machineId(), keys_.size() ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( header.Write( dbHandle, file ) == CQL_FAILURE )
		return CQL_FAILURE;

	tRoot = ( keys_.size() + 1 ) * CQL_LOGICAL_PAGE_SIZE;
	node = new Node( tRoot );
	if( !node )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );
	node->SetTerminal();
	node->SetRoot();
	node->SetRemainingSpace( InitialNodeSpace() );

	Accessor *acc;
	for( acc = keys_.first(), loop = 0; acc; acc = keys_.next(), loop++ )
	{
		IndexKeyDescriptor *keyDesc = dynamic_cast< IndexKeyDescriptor* >( acc );

		keyDesc->SetRootLocation( tRoot );
		if( keyDesc->Write( dbHandle, file, *node, ( loop + 1 ) * CQL_LOGICAL_PAGE_SIZE ) == CQL_FAILURE )
		{
			delete node;
			return CQL_FAILURE;
		}

		node->SetLocation( tRoot );
		tRoot += CQL_LOGICAL_PAGE_SIZE;
		if( node->WriteNode( dbHandle, file ) == CQL_FAILURE )
		{
			delete node;
			return CQL_FAILURE;
		}
	}

	delete node;

	return CQL_SUCCESS;
}


NI Index::Open( DatabaseHandle& dbHandle, const CqlString& name )
{
	UNI loop;
	CqlString s;
	pIndexKeyDescriptor keyd;

	s = name;
	//exception

	s += CQL_INDEX_FILE_EXTENSION;
	//exception
	
	file = dynamic_cast< EnvironmentHandle* >( hAEnv )->Open( dbHandle, s );

	if( header.Read( dbHandle, file ) == CQL_FAILURE )
		return CQL_FAILURE;

	for( loop = 0; loop < header.NumberOfKeys(); loop++ )
	{
		Accessor *acc =  Accessor::createObject( CQL_TREE_INDEX, static_cast< US >( loop ) );
		keyd = dynamic_cast< IndexKeyDescriptor* >( acc );
		keyd->descriptorLocation( header.KeyDescriptorLocation( loop ) );

		if( keyd->Read( dbHandle, *file ) == CQL_FAILURE )
			return CQL_FAILURE;

		keys_.add( keyd );
	}

	return CQL_SUCCESS;
}


NI Index::Close( DatabaseHandle& dbHandle )
{
	if( !file->IsOpen() )
		return CQL_SUCCESS;

	if( dynamic_cast< EnvironmentHandle* >( hAEnv )->Close( dbHandle, *file ) == CQL_FAILURE )
		return CQL_FAILURE;

	destroyIndex();
	return CQL_SUCCESS;
}


NI Index::Key( DatabaseHandle& dbHandle, UL keyNumber )
{
	Accessor *accessor;
	UL loop;

	for( loop = 0, accessor = keys_.first(); accessor && loop < keyNumber; loop++, accessor = keys_.next() )
		;

	if( !accessor )
		return dbHandle.returnError( LIST_INCONSISTENCY, __FILE__, __LINE__ );

	currentKey = dynamic_cast< IndexKeyDescriptor* >( accessor );
	return CQL_SUCCESS;
}


NI Index::BeginKeyOperation( DatabaseHandle& dbHandle, UL keyNumber )
{
	if( Key( dbHandle, keyNumber ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( currentKey->FirstSegment( dbHandle ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI Index::BeginFind( DatabaseHandle& dbHandle, UL keyNumber )
{
	if( Key( dbHandle, keyNumber ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( currentKey->ZeroSegmentValues() == CQL_FAILURE )
		return CQL_FAILURE;

	if( currentKey->FirstSegment( dbHandle ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI Index::SetSegment( DatabaseHandle& dbHandle, pUC key )
{
	return currentKey->SetSegment( dbHandle, key );
}


NI Index::SetSegment( DatabaseHandle& dbHandle, pAbstractColumnDescriptor col )
{
	return currentKey->SetSegment( dbHandle, dynamic_cast< ColumnDescriptor* >( col ) );
}


NI Index::GetSegment( DatabaseHandle& dbHandle, pUC key )
{
	return currentKey->GetSegment( dbHandle, key );
}


NI Index::FindKeyPosition( DatabaseHandle& dbHandle, pNode *terminalNode, pNodeElement inputElement )
{
	pNodeElement element;
	CompareResult result;
	pNode node;
	RECID pos;

	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( node->NumberOfEntries() == 0 )
	{
		node->SetCurrentElement( 0 );
		node->SetLowerElement( 0 );
		node->SetHigherElement( 0 );
		*terminalNode = node;
		return CQL_SUCCESS;
	}

	while( !node->Terminal() )
	{
		pos = node->LowerKeyNode();

		for( element = node->first(); element; element = node->next() )
		{
			try
			{
				result = inputElement->Compare( *element, currentKey->segments(), false );
			}
			//exception
			catch( ... )
			{
				delete node;
				return CQL_FAILURE;
			}

			if( result == THIS_LESS_THAN_OTHER )
				break;

			pos = element->Son();
		}

		if( ReadNode( dbHandle, &node, pos ) == CQL_FAILURE )
			return CQL_FAILURE;
	}

	if( node->FindPositionInNode( dbHandle, inputElement, currentKey->segments() ) == CQL_FAILURE )
	{
		delete node;
		return CQL_FAILURE;
	}

	*terminalNode = node;
	return CQL_SUCCESS;
}


bool Index::searchForKey( DatabaseHandle& dbHandle, pNodeElement inputElement, bool compareRecordPosition, IndexKeyDescriptor::SearchType searchType )
{
	RECID pos;
	CompareResult result;
	pNodeElement element, lowerElement = ((pNodeElement)0);
	pNode node;

	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		throw IndexAccessException( __FILE__, __LINE__ );

	if( node->NumberOfEntries() == 0 )
		return false;

	while( node->Terminal() == CQL_NO )
	{
		pos = node->LowerKeyNode();

		for( element = node->first(); element; element = node->next() )
		{
			result = inputElement->Compare( *element, currentKey->segments(), false );
			if( result == THIS_LESS_THAN_OTHER )
				break;
			pos = element->Son();
		}

		if( ReadNode( dbHandle, &node, pos ) == CQL_FAILURE )
			throw IndexAccessException( __FILE__, __LINE__ );
	}

	for( element = node->first(); element; element = node->next() )
	{
		result = inputElement->Compare( *element, currentKey->segments(), compareRecordPosition, segmentsToCompare_ );
		switch( result )
		{
		case THIS_EQUAL_TO_OTHER :
			switch( searchType )
			{
			case CQL_EQUAL :
			case CQL_GREATER_THAN_OR_EQUAL :
			case CQL_LESS_THAN_OR_EQUAL :
				currentKey->SetCurrentNode( node );
				node->SetCurrentElement( element );
				currentKey->SetCurrentElementNumber();
				return true;

			case CQL_LESS_THAN :
				if( lowerElement )
				{
					currentKey->SetCurrentNode( node );
					node->SetCurrentElement( lowerElement );
					currentKey->SetCurrentElementNumber();
					return true;
				}
				else
					return false;

			case CQL_GREATER_THAN :
				break;
			}
			break;

		case THIS_LESS_THAN_OTHER :
			switch( searchType )
			{
			case CQL_EQUAL :
				return false;

			case CQL_GREATER_THAN_OR_EQUAL :
			case CQL_GREATER_THAN :
				currentKey->SetCurrentNode( node );
				node->SetCurrentElement( element );
				currentKey->SetCurrentElementNumber();
				return true;

			case CQL_LESS_THAN :
			case CQL_LESS_THAN_OR_EQUAL :
				if( lowerElement )
				{
					currentKey->SetCurrentNode( node );
					node->SetCurrentElement( lowerElement );
					currentKey->SetCurrentElementNumber();
					return true;
				}
				else
					return false;
			}
			break;

		case THIS_GREATER_THAN_OTHER :
			switch( searchType )
			{
			case CQL_EQUAL :
			case CQL_GREATER_THAN :
			case CQL_GREATER_THAN_OR_EQUAL :
				break;

			case CQL_LESS_THAN :
			case CQL_LESS_THAN_OR_EQUAL :
				lowerElement = element;
				break;
			}
			break;

		case COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	switch( searchType )
	{
	case CQL_EQUAL :
	case CQL_GREATER_THAN :
	case CQL_GREATER_THAN_OR_EQUAL :
		break;
		
	case CQL_LESS_THAN :
	case CQL_LESS_THAN_OR_EQUAL :
		if( lowerElement )
		{
			currentKey->SetCurrentNode( node );
			node->SetCurrentElement( lowerElement );
			currentKey->SetCurrentElementNumber();
			return true;
		}
		break;
	}

	return false;
}


#ifdef __CQL_FINE_GRAIN_DEBUGGING
NI Index::AddElementToNode( DatabaseHandle& dbHandle, pNode node, pNodeElement inputElement, NI recursive )
#else
NI Index::AddElementToNode( DatabaseHandle& dbHandle, pNode node, pNodeElement inputElement, NI )
#endif
{
	pNode rightBrother = 0, leftBrother = 0, parent = 0, newNode, newRoot;
	pNodeElement element, inputCopy, lastElement = 0;
	US space;
	NI terminal = node->Terminal();
#ifdef __CQL_FINE_GRAIN_DEBUGGING
	UL startNumberOfEntries = 0, endNumberOfEntries;
#endif

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
	{
		if( recursive == CQL_NO )
			CheckBtreeIndex( dbHandle, &startNumberOfEntries );
		else
			CheckBtreeIndex( dbHandle );
	}
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	//
	//  Get a write lock if we don't already have one
	//
	if( node->Dirty() == CQL_NO )
	{
		file->writeLock( node->Location() );
		node->SetDirty();
	}

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	//
	//  If there is enough space in the node, we simply add the new
	//  element to it.
	//
	if( node->RemainingSpace() >= inputElement->SpaceNeeded() )
	{
		if( node->AddElement( inputElement ) == CQL_FAILURE )
			return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
		if( btreeDebugging )
			CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

		//
		//  If node->LowerElement() is 0, then the element we are adding is the smallest
		//  element in the node.  We therefore have to update the parent node's key.
		//  There are two exceptions.  First, if this is the root node, there is no parent
		//  to update; we therefore check for node->Parent() not being 0.  Second, if
		//  LeftBrother() is zero, then this is the lowest terminal node.  The lowest
		//  terminal node does not have a key in the parent, so no parent update is
		//  necessary (it is pointed to in the parent by lowerKeyNode). 
		//
		if( !node->LowerElement() && node->LeftBrother() && node->Parent() )
		{
			if( ReadNode( dbHandle, &parent, node->Parent() ) == CQL_FAILURE )
				return CQL_FAILURE;

			if( parent->Dirty() == CQL_NO )
			{
				file->writeLock( parent->Location() );
				parent->SetDirty();
			}

			if( parent->ReplaceKey( dbHandle, node->Location(), inputElement ) == CQL_FAILURE )
				return CQL_FAILURE;
		}

#ifdef __CQL_FINE_GRAIN_DEBUGGING
		if( btreeDebugging )
			CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

		//
		//  We update the counts, percolating up the tree
		//
		if( UpdateParentCounts( dbHandle, node ) == CQL_FAILURE )
			return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
		if( btreeDebugging )
		{
			CheckBtreeIndex( dbHandle, &endNumberOfEntries );
			if( recursive == CQL_NO && startNumberOfEntries + 1 != endNumberOfEntries )
				assert( 0 );
		}
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

		return CQL_SUCCESS;
	}

	//
	//  We are still here, so there isn't enough room in the node for the new element.
	//  We read the parent, right and left brother nodes, if they exist, to see if we can avoid
	//  splitting the node (which increases the height of the B-tree) by shifting keys
	//  to the left or right brother.
	//

	if( node->RightBrother() )
		if( ReadNode( dbHandle, &rightBrother, node->RightBrother() ) == CQL_FAILURE )
			return CQL_FAILURE;

	if( node->LeftBrother() )
		if( ReadNode( dbHandle, &leftBrother, node->LeftBrother() ) == CQL_FAILURE )
			return CQL_FAILURE;

	if( node->Parent() )
		if( ReadNode( dbHandle, &parent, node->Parent() ) == CQL_FAILURE )
			return CQL_FAILURE;

	//
	//  First we check for the possibility of shifting elements to the right brother, to
	//  make room for the new element in its node.  We only do this if node->HigherElement()
	//  exists, because if node->HigherElement() is 0, then the element we are adding
	//  would be the highest element in its node, and we can't gain anything by shifting
	//  elements to the right.
	//
	//  NOTE:  An improvement would be to try to simply make the new element the lowest
	//  element in the right brother
	//
	if( rightBrother && node->HigherElement() )
	{
		//
		//  Compute the amount of space which can be made available in this node by shifting keys
		//  to the right brother.  Stop counting if the amount of space needed is reached.
		//
		if( rightBrother->RemainingSpace() >= inputElement->SpaceNeeded() )
		{
			//  can we move enough keys to right brother to fit new key here?
			for( element = node->last(), space = 0; element && element != node->HigherElement(); element = node->prev() )
			{
				space = ((US)( space + element->SpaceNeeded() ) );
				if( space >= inputElement->SpaceNeeded() || space > rightBrother->RemainingSpace() )
					break;
			}

#ifdef __CQL_FINE_GRAIN_DEBUGGING
			if( btreeDebugging )
				CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

			if( space >= inputElement->SpaceNeeded() && space <= rightBrother->RemainingSpace() )
			{
				//
				//  we can shift keys to the right brother and add key to node
				//
				//  lastElement is used to save the element most recently worked on.
				//  At the end of the moving process, it is the last element added to the
				//  beginning of the right brother.  It is then used to update the right
				//  brother's key in the right brother's parent
				//

				if( rightBrother->Dirty() == CQL_NO )
				{
					file->writeLock( rightBrother->Location() );
					rightBrother->SetDirty();
				}

				for( element = node->last(), space = 0; element && element != node->HigherElement(); element = lastElement->prev() )
				{
					lastElement = element;
					space = ((US)( space + element->SpaceNeeded() ) );
					node->IncreaseRemainingSpace( element->SpaceNeeded() );

					//  Delete the item from node, and add to right brother
					node->remove( element );

					if( rightBrother->AddElementToBeginning( element ) == CQL_FAILURE )
						return CQL_FAILURE;

					node->DecrementNumberOfEntries();

#ifdef __CQL_FINE_GRAIN_DEBUGGING
					if( btreeDebugging )
						CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

					//
					//  Stop if we've made enough space in node
					//
					if( space >= inputElement->SpaceNeeded() )
						break;
				}

#ifdef __CQL_FINE_GRAIN_DEBUGGING
				if( btreeDebugging )
					CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

				if( node->AddElement( inputElement ) == CQL_FAILURE )
					return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
				if( btreeDebugging )
					CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

				//  the parent key for the brother node needs to be updated.  A node with a brother always has a parent
				if( parent->Dirty() == CQL_NO )
				{
					file->writeLock( parent->Location() );
					parent->SetDirty();
				}

				if( parent->ReplaceKey( dbHandle, node->RightBrother(), lastElement ) == CQL_FAILURE )
					return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
				if( btreeDebugging )
					CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

				//
				//  We need to update the parent counts for both node and right brother
				//
				if( UpdateParentCounts( dbHandle, node ) == CQL_FAILURE
					|| UpdateParentCounts( dbHandle, rightBrother ) == CQL_FAILURE )
					return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
				if( btreeDebugging )
				{
					CheckBtreeIndex( dbHandle, &endNumberOfEntries );
					if( recursive == CQL_NO && startNumberOfEntries + 1 != endNumberOfEntries )
						assert( 0 );
				}
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

				return CQL_SUCCESS;
			}
		}
	}

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	//
	//  We didn't succeed in shifting keys to the right brother, so here we try the same thing with the
	//  left brother.  If node->LowerElement() is 0, the new element is the lowest for node, so we
	//  can't do any shifting.
	//
	//  NOTE:  An improvement would be to try to add the new element to left brother as the highest
	//  element in left brother
	//
	if( leftBrother && node->LowerElement() )
	{
		//
		//  Can we make enough space by shift keys to the left brother?
		//
		if( leftBrother->RemainingSpace() >= inputElement->SpaceNeeded() )
		{
			//  can we move enough keys to left brother to fit new key here?
			for( element = node->first(), space = 0; element != node->LowerElement(); element = node->next() )
			{
				space = ((US)( space + element->SpaceNeeded() ) );
				if( space >= inputElement->SpaceNeeded() || space > leftBrother->RemainingSpace() )
					break;
			}

			if( space >= inputElement->SpaceNeeded() && space <= leftBrother->RemainingSpace() )
			{
				//
				//  we can shift keys to the left brother and add new key to node
				//

				if( leftBrother->Dirty() == CQL_NO )
				{
					file->writeLock( leftBrother->Location() );
					leftBrother->SetDirty();
				}

				for( element = node->first(), space = 0; element != node->LowerElement(); element = node->first() )
				{
					space = ((US)( space + element->SpaceNeeded() ) );

					node->IncreaseRemainingSpace( element->SpaceNeeded() );
					node->remove( element );

					if( leftBrother->AddElementToEnd( element ) == CQL_FAILURE )
						return CQL_FAILURE;

					node->DecrementNumberOfEntries();

#ifdef __CQL_FINE_GRAIN_DEBUGGING
					if( btreeDebugging )
						CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

					if( space >= inputElement->SpaceNeeded() )
						break;
				}

				//
				//  It is not necessary to update the parent key of the left brother, because we added keys on the right
				//
				
				//  add new element
				if( node->AddElement( inputElement ) == CQL_FAILURE )
					return CQL_FAILURE;
				
#ifdef __CQL_FINE_GRAIN_DEBUGGING
				if( btreeDebugging )
					CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

				//
				//  Need to update counts of both node and leftBrother
				//
				if( UpdateParentCounts( dbHandle,
										node ) == CQL_FAILURE || UpdateParentCounts( dbHandle,
																					 leftBrother ) == CQL_FAILURE )
					return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
				if( btreeDebugging )
				{
					CheckBtreeIndex( dbHandle, &endNumberOfEntries );
					if( recursive == CQL_NO && startNumberOfEntries + 1 != endNumberOfEntries )
						assert( 0 );
				}
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

				return CQL_SUCCESS;
			}
		}
	}

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	//
	//  Neither shifting to left nor shifting to right succeeded.
	//  Node needs to be split.
	//
	if( GetNewNode( dbHandle, &newNode, CQL_NO, node->Terminal() ) == CQL_FAILURE )
		return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	//
	//  Add the new element to the new node
	//
	if( newNode->AddElement( inputElement ) == CQL_FAILURE )
		return CQL_FAILURE;
	
#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	inputCopy = new NodeElement( dbHandle );
	if( !inputCopy )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );
	*inputCopy = *inputElement;

	//
	//  Now add all the keys which are higher than the new element to the new node,
	//  unless node->LowerElement() is 0
	//
	if( node->LowerElement() )
	{
		for( element = node->HigherElement(), node->current( element ); element; element = node->next() )
		{
			node->IncreaseRemainingSpace( element->SpaceNeeded() );
			node->remove( element );

			node->DecrementNumberOfEntries();
			if( newNode->AddElement( element ) == CQL_FAILURE )
				return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
			if( btreeDebugging )
				CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING
		}
	}

	newNode->SetLeftBrother( node->Location() );
	newNode->SetRightBrother( node->RightBrother() );
	if( newNode->RightBrother() )
	{
		if( rightBrother->Dirty() == CQL_NO )
		{
			file->writeLock( rightBrother->Location() );
			rightBrother->SetDirty();
		}

		rightBrother->SetLeftBrother( newNode->Location() );
	}
	
	node->SetRightBrother( newNode->Location() );

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	//***********************************************************************
	//**  If the node is not a terminal node, each of the nodes pointed    **
	//**  to by the new node's elements need to be reparented.             **
	//***********************************************************************
	if( terminal == CQL_NO )
	{
		for( element = newNode->first(); element; element = newNode->next() )
		{
			pNode tnode;

			if( ReadNode( dbHandle, &tnode, element->Son() ) == CQL_FAILURE )
				return CQL_FAILURE;

			if( tnode->Dirty() == CQL_NO )
			{
				file->writeLock( tnode->Location() );
				tnode->SetDirty();
			}

			tnode->SetParent( newNode->Location() );
		}
	}

	//
	//  Either node has a parent, or node is the root node.  If node has a parent, we need to
	//  add the new node (as an element) to the parent
	//
	if( node->Parent() )
	{
		if( ReadNode( dbHandle, &parent, node->Parent() ) == CQL_FAILURE )
			return CQL_FAILURE;
		
		newNode->SetParent( node->Parent() );
		
		inputCopy->SetSon( newNode->Location() );
		if( parent->FindPositionInNode( dbHandle, inputCopy, currentKey->segments() ) == CQL_FAILURE )
			return CQL_FAILURE;
		
		if( parent->Dirty() == CQL_NO )
		{
			file->writeLock( parent->Location() );
			parent->SetDirty();
		}

		if( AddElementToNode( dbHandle, parent, inputCopy, CQL_YES ) == CQL_FAILURE )
			return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
		if( btreeDebugging )
			CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

		//
		//  Update parent counts for node and for newNode
		//
		if( UpdateParentCounts( dbHandle, node ) == CQL_FAILURE || UpdateParentCounts( dbHandle, newNode ) == CQL_FAILURE )
			return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
		if( btreeDebugging )
		{
			CheckBtreeIndex( dbHandle, &endNumberOfEntries );
			if( recursive == CQL_NO && startNumberOfEntries + 1 != endNumberOfEntries )
				assert( 0 );
		}
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

		return CQL_SUCCESS;
	}

	//
	//  If we get here, node was the root node.  Then we need to create a new root node, and make node
	//  and newNode its children.
	//
	if( GetNewNode( dbHandle, &newRoot, CQL_YES, CQL_NO ) == CQL_FAILURE )
		return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	//
	//  Node has to be the lowest element, because there are only two child nodes, and we moved all the
	//  keys higher than the insertion point to the new node.
	//
	newRoot->SetLowerKeyNode( node->Location() );
	inputCopy->SetSon( newNode->Location() );
	if( newRoot->AddElement( inputCopy ) == CQL_FAILURE )
		return CQL_FAILURE;
	
#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	node->SetParent( newRoot->Location() );

	newNode->SetParent( newRoot->Location() );
	
	node->ClearRoot();
	if( currentKey->ChangeRootPointer( dbHandle, file, newRoot->Location() ) == CQL_FAILURE )
		return CQL_FAILURE;
	
#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	if( header.Write( dbHandle, file ) == CQL_FAILURE )
		return CQL_FAILURE;
	
#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	if( UpdateParentCounts( dbHandle, node ) == CQL_FAILURE || UpdateParentCounts( dbHandle, newNode ) == CQL_FAILURE )
		return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
	{
		CheckBtreeIndex( dbHandle, &endNumberOfEntries );
		if( recursive == CQL_NO && startNumberOfEntries + 1 != endNumberOfEntries )
			assert( 0 );
	}
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	return CQL_SUCCESS;
}


NI Index::DeleteElementFromNode( DatabaseHandle& dbHandle, pNode node, pNodeElement deletionElement )
{
	pNode rightBrother = 0, leftBrother = 0, parent = 0;
	pNodeElement element, lastElement = 0, firstElement = node->first();
	
	if( node->Dirty() == CQL_NO )
	{
		file->writeLock( node->Location() );
		node->SetDirty();
	}
	
	if( DeleteElement( dbHandle, node, deletionElement ) == CQL_FAILURE )
		return CQL_FAILURE;

	//  can we make the tree smaller?
	if( node->RightBrother() )
		if( ReadNode( dbHandle, &rightBrother, node->RightBrother() ) == CQL_FAILURE )
			return CQL_FAILURE;

	if( node->LeftBrother() )
		if( ReadNode( dbHandle, &leftBrother, node->LeftBrother() ) == CQL_FAILURE )
			return CQL_FAILURE;

	if( node->Parent() )
		if( ReadNode( dbHandle, &parent, node->Parent() ) == CQL_FAILURE )
			return CQL_FAILURE;

	//  can we combine with right brother?
	if( node->RightBrother() && ( ( InitialNodeSpace() - node->RemainingSpace() ) <= rightBrother->RemainingSpace() ) )
	{
		//  move keys to right brother.  First key moved becomes new first key of right brother
		for( element = node->last(); element; element = node->prev() )
		{
			lastElement = element;
			if( rightBrother->AddElementToBeginning( element ) == CQL_FAILURE )
				return CQL_FAILURE;
		}
		if( parent->ReplaceKey( dbHandle, node->RightBrother(), lastElement ) == CQL_FAILURE )
			return CQL_FAILURE;

		if( DeleteElementFromNode( dbHandle, parent, firstElement ) == CQL_FAILURE )
			return CQL_FAILURE;

		if( DeleteNode( dbHandle, node ) == CQL_FAILURE )
			return CQL_FAILURE;

		if( UpdateParentCounts( dbHandle, rightBrother ) == CQL_FAILURE )
			return CQL_FAILURE;
	}

	//  if not, the left brother?
	else if( node->LeftBrother() && ( ( InitialNodeSpace() - node->RemainingSpace() ) <= leftBrother->RemainingSpace() ) )
	{
		//  move keys to left brother.
		for( element = node->first(); element; element = node->next() )
			if( leftBrother->AddElementToEnd( element ) == CQL_FAILURE )
				return CQL_FAILURE;

		if( DeleteElementFromNode( dbHandle, parent, firstElement ) == CQL_FAILURE )
			return CQL_FAILURE;
	
		if( DeleteNode( dbHandle, node ) == CQL_FAILURE )
			return CQL_FAILURE;

		if( UpdateParentCounts( dbHandle, leftBrother ) == CQL_FAILURE )
			return CQL_FAILURE;
	}
	
	if( UpdateParentCounts( dbHandle, node ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI Index::AddKey( DatabaseHandle& dbHandle, RECID pos )
{
	pNodeElement element;
	pNode node;
	
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );

	segmentsToCompare_ = keys_.current()->numberOfSegments();

	if( currentKey->CreateElementFromSegments( dbHandle, &element, pos ) == CQL_FAILURE )
		return CQL_FAILURE;
	
	if( currentKey->aqtypeType() == CQL_NO_DUPLICATES )
	{
		if( searchForKey( dbHandle, element, CQL_NO, CQL_EQUAL ) )
		{
			element->Dump();
			delete element;
			throw DuplicateRowException( __FILE__, __LINE__ );
		}
	}

	if( FindKeyPosition( dbHandle, &node, element ) == CQL_FAILURE )
		return CQL_FAILURE;
	
	if( AddElementToNode( dbHandle, node, element ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( node->WriteNode( dbHandle, file ) == CQL_FAILURE )
		return CQL_FAILURE;

	dbHandle.addToIndexIndex( this );

	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );

	return CQL_SUCCESS;
}


void Index::deleteCurrentKey( DatabaseHandle& dbHandle )
{
	Node *node = currentKey->CurrentNode();
	
	if( btreePrinting )
		fprintf( stderr, "deleting key, node %lx, key %s\n", ((UL)node), node->CurrentElement()->asString().text() );

	if( DeleteElementFromNode( dbHandle, node, node->CurrentElement() ) == CQL_FAILURE )
		throw IndexAccessException( __FILE__, __LINE__ );

	if( node->WriteNode( dbHandle, file ) == CQL_FAILURE )
		throw IndexAccessException( __FILE__, __LINE__ );

	dbHandle.addToIndexIndex( this );

	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
}


NI Index::deleteKey( DatabaseHandle& dbHandle, Accessor *lkey, RECID pos )
{
	pNode node;
	pNodeElement element;

	currentKey = dynamic_cast<IndexKeyDescriptor*>(lkey);
	
	if( currentKey->CreateElementFromSegments( dbHandle, &element, pos ) == CQL_FAILURE )
		return CQL_FAILURE;
	
	if( !searchForKey( dbHandle, element, CQL_YES, CQL_EQUAL ) )
	{
		delete element;
		throw IndexAccessException( __FILE__, __LINE__ );
	}

	node = currentKey->CurrentNode();
	if( btreePrinting == CQL_YES )
		fprintf( stderr, "deleting key, node %lx, key %s\n", ((UL)node), node->CurrentElement()->asString().text() );

	if( DeleteElementFromNode( dbHandle, node, node->CurrentElement() ) == CQL_FAILURE )
	{
		delete element;
		throw IndexAccessException( __FILE__, __LINE__ );
	}

	if( node->WriteNode( dbHandle, file ) == CQL_FAILURE )
	{
		delete element;
		throw IndexAccessException( __FILE__, __LINE__ );
	}

	try
	{
		dbHandle.addToIndexIndex( this );
	}
	catch( ... )
	{
		delete element;
		throw;
	}

	delete element;

	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );

	return CQL_SUCCESS;
}


bool Index::find( DatabaseHandle& dbHandle, SearchType type )
{
	pNodeElement element;
	
	if( currentKey->CreateElementFromSegments( dbHandle, &element, ((RECID)0) ) == CQL_FAILURE )
		throw IndexAccessException( __FILE__, __LINE__ );
	
	bool rc = searchForKey( dbHandle, element, CQL_NO, type );
	delete element;
	return rc;
}


bool Index::findEqual( DatabaseHandle& dbHandle  )
{
	return find( dbHandle, CQL_EQUAL );
}


bool Index::findGreater( DatabaseHandle& dbHandle )
{
	return find( dbHandle, CQL_GREATER_THAN );
}


bool Index::findGreaterOrEqual( DatabaseHandle& dbHandle )
{
	return find( dbHandle, CQL_GREATER_THAN_OR_EQUAL );
}


bool Index::findLessThan( DatabaseHandle& dbHandle )
{
	return find( dbHandle, CQL_LESS_THAN );
}


bool Index::findLessThanOrEqual( DatabaseHandle& dbHandle )
{
	return find( dbHandle, CQL_LESS_THAN_OR_EQUAL );
}


NI Index::GetNewNode( DatabaseHandle& dbHandle, pNode *newNode, NI isRoot, NI isTerminal  )
{
	RECID pos, newListHead;
	pNode tnode;
	
	if( header.FreeNodeList() )
	{
		pos = header.FreeNodeList();
		if( file->InputSeek( pos ) == CQL_FAILURE )
			return CQL_FAILURE;
		file->read( ((void*)hAEnv->globalBuffer()), CQL_LOGICAL_PAGE_SIZE );
		memcpy( &newListHead, hAEnv->globalBuffer(), sizeof( newListHead ) );
		header.SetFreeNodeList( newListHead );
		if( header.Write( dbHandle, file ) == CQL_FAILURE )
			return CQL_FAILURE;
	}
	else
	{
		pos = header.EndOfFile();
		header.SetEndOfFile( pos + CQL_LOGICAL_PAGE_SIZE );
	}
	
	tnode = new Node( pos );
	if( !tnode )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );
	tnode->SetRemainingSpace( CQL_LOGICAL_PAGE_SIZE
							  - ( ( 4 * sizeof( RECID ) )
								  + sizeof( UL )
								  + sizeof( US )
								  + sizeof( NI ) ) );
	
	if( AddIndexNode( dbHandle, pos, tnode ) == CQL_FAILURE )
		return CQL_FAILURE;

	dbHandle.addToIndexIndex( this );
	file->writeLock( tnode->Location() );
	tnode->SetDirty();
	
	if( isTerminal )
		tnode->SetTerminal();
	if( isRoot )
		tnode->SetRoot();
	*newNode = tnode;
	return CQL_SUCCESS;
}


void Index::DumpKeyNode( DatabaseHandle& dbHandle, RECID loc, UL& nEntries )
{
	pNodeElement element;
	pNode node;
	US loop;
	
	if( ReadNode( dbHandle, &node, loc ) == CQL_FAILURE )
	{
		std::cout << "error reading root" << std::endl;
		return;
	}
	
	std::cout << "node " << node->Location() << std::endl;
	std::cout << "numberOfEntries:  " << node->NumberOfEntries() << std::endl;
	std::cout << "terminal:  " << node->Terminal() << std::endl;
	std::cout << "parent:  " << node->Parent() << std::endl;
	std::cout << "leftBrother:  " << node->LeftBrother() << std::endl;
	std::cout << "rightBrother:  " << node->RightBrother() << std::endl;
	std::cout << "lowerKeyNode:  " << node->LowerKeyNode() << std::endl;

	for( element = node->first(), loop = 0; element; element = node->next(), loop++ )
	{
		std::cout << "        Element " << loop << ":  ";
		element->Dump();
	}

	if( !node->Terminal() )
	{
		DumpKeyNode( dbHandle, node->LowerKeyNode(), nEntries );
		
		for( element = node->first(); element; element = node->next() )
			DumpKeyNode( dbHandle, element->Son(), nEntries );
	}
	else
		nEntries += ((UL)loop);
}


void Index::Dump( DatabaseHandle& dbHandle )
{
	UL loop, nEntries;
	//FIXED
	Accessor *acc;	
	for( acc = keys_.first(), loop = 0; acc; acc = keys_.next(), loop++ )
	{
		IndexKeyDescriptor *kd = dynamic_cast< IndexKeyDescriptor* >(acc);
		std::cout << "Dumping key " << loop << std::endl;
		nEntries = 0;
		DumpKeyNode( dbHandle, kd->RootLocation(), nEntries );
		std::cout << "Number of terminal entries:  " << nEntries << std::endl << std::endl;
	}
}


NI Index::ReadNode( DatabaseHandle& dbHandle, pNode *node, RECID loc )
{
	pNode tnode;
	pNodeIndexNode nodeIndexNode;
	
	if( FindEqualKey( dbHandle, loc ) == CQL_SUCCESS )
	{
		nodeIndexNode = CurrentNode();
		*node = nodeIndexNode->CachedNode();
		return CQL_SUCCESS;
	}
	
	tnode = new Node;
	if( !tnode )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );
	*node = tnode;
	
	if( tnode->ReadNode( dbHandle, file, loc ) == CQL_FAILURE )
		return CQL_FAILURE;
	
	if( AddIndexNode( dbHandle, loc, tnode ) == CQL_FAILURE )
		return CQL_FAILURE;
	
	return CQL_SUCCESS;
}


NI Index::DeleteNode( DatabaseHandle& dbHandle, pNode node )
{
	if( FindEqualKey( dbHandle, node->Location() ) != CQL_SUCCESS )
	   return dbHandle.returnError( INVALID_NODE_INDEX, __FILE__, __LINE__ );

	if( deleteIndexNode() == CQL_FAILURE )
		return dbHandle.returnError( CACHE_INDEX_FAILURE, __FILE__, __LINE__ );

	delete node;
	return CQL_SUCCESS;
}


NI Index::FlushDirtyNodes( DatabaseHandle& dbHandle )
{
	NI rc;
	pNodeIndexNode tnode;
	
	for( rc = firstNode(); rc == CQL_SUCCESS; rc = nextNode() )
	{
		tnode = CurrentNode();

		if( tnode->CachedNode()->Dirty() )
			if( tnode->CachedNode()->WriteNode( dbHandle, file ) == CQL_FAILURE )
				return CQL_FAILURE;
	}

	destroyIndex();

	if( currentKey )
		currentKey->SetCurrentNode( ((pNode)0) );

	return CQL_SUCCESS;
}


NI Index::RollbackDirtyNodes( void )
{
	NI rc;
	pNodeIndexNode tnode;

	for( rc = firstNode(); rc == CQL_SUCCESS; rc = nextNode() )
	{
		tnode = CurrentNode();

		if( tnode->CachedNode()->Dirty() )
			if( tnode->CachedNode()->RollbackNode( file ) == CQL_FAILURE )
				return CQL_FAILURE;
	}

	destroyIndex();

	return CQL_SUCCESS;
}


NI Index::DeleteElement( DatabaseHandle& dbHandle, pNode node, pNodeElement deletionElement )
{
	pNode parent;
	
	if( node->Parent() && node->isFirst( deletionElement ) )
	{
		//  need to change parent key
		if( ReadNode( dbHandle, &parent, node->Parent() ) == CQL_FAILURE )
			return CQL_FAILURE;
		
		if( parent->ReplaceKey( dbHandle, node->Location(), deletionElement->next() ) )
			return CQL_FAILURE;
	}

	node->remove( deletionElement );
	node->IncreaseRemainingSpace( deletionElement->SpaceNeeded() );
	node->DecrementNumberOfEntries();
	delete deletionElement;

	return CQL_SUCCESS;
}


bool Index::firstKey( DatabaseHandle& dbHandle )
{
	RECID pos;
	pNode node;

 	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		throw IndexAccessException( __FILE__, __LINE__ );

	if( node->NumberOfEntries() == 0 )
		return false;

	while( node->Terminal() == CQL_NO )
	{
		pos = node->LowerKeyNode();
		if( ReadNode( dbHandle, &node, pos ) == CQL_FAILURE )
			throw IndexAccessException( __FILE__, __LINE__ );
	}

	currentKey->SetCurrentNode( node );
	node->SetCurrentElement( node->first() );
	currentKey->SetCurrentElementNumber( 0 );

	if( btreePrinting == CQL_YES )
		fprintf( stderr, "In first(), node = %lx, key = %s\n", ((UL)node), node->CurrentElement()->asString().text() );

	return true;
}


bool Index::nextKey( DatabaseHandle& dbHandle )
{
	pNodeElement element;
	pNode node, nextTerminalNode;
	RECID pos;

	node = currentKey->CurrentNode();
	if( !node )
	{
		if( ReadNode( dbHandle, &node, currentKey->CurrentNodeLocation() ) == CQL_FAILURE )
			throw IndexAccessException( __FILE__, __LINE__ );

		currentKey->SetCurrentNode( node );
		currentKey->ReturnToCurrentElement( node );
	}

	element = node->CurrentElement()->next();
	if( element )
	{
		node->SetCurrentElement( element );
		currentKey->IncrementCurrentElementNumber();
		return true;
	}

	//
	//  There was no next element, so we need to find the next terminal node.
	//  Since this is a terminal node, the next terminal node is this node's
	//  right brother.
	//
	
	pos = node->RightBrother();
	if( !pos )
	{
		node->SetCurrentElement( ((pNodeElement)0) );
		return false;
	}

	if( ReadNode( dbHandle, &nextTerminalNode, pos ) == CQL_FAILURE )
		throw IndexAccessException( __FILE__, __LINE__ );

	currentKey->SetCurrentNode( nextTerminalNode );
	nextTerminalNode->SetCurrentElement( nextTerminalNode->first() );
	currentKey->SetCurrentElementNumber( 0 );
	return true;
}


bool Index::lastKey( DatabaseHandle& dbHandle )
{
	RECID pos;
	pNode node;
	pNodeElement element;

	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		throw IndexAccessException( __FILE__, __LINE__ );

	if( node->NumberOfEntries() == 0 )
		return false;

	while( node->Terminal() == CQL_NO )
	{
		element = node->last();
		pos = element->Son();
		if( ReadNode( dbHandle, &node, pos ) == CQL_FAILURE )
			throw IndexAccessException( __FILE__, __LINE__ );
	}

	currentKey->SetCurrentNode( node );
	node->SetCurrentElement( node->last() );
	currentKey->SetCurrentElementNumber();
	return true;
}


bool Index::previousKey( DatabaseHandle& dbHandle )
{
	pNodeElement element;
	pNode node, previousTerminalNode;
	RECID pos;

	node = currentKey->CurrentNode();

	if( !node )
	{
		if( ReadNode( dbHandle, &node, currentKey->CurrentNodeLocation() ) == CQL_FAILURE )
			throw IndexAccessException( __FILE__, __LINE__ );

		currentKey->SetCurrentNode( node );
		currentKey->ReturnToCurrentElement( node );
	}

	element = node->CurrentElement()->prev();
	if( element )
	{
		node->SetCurrentElement( element );
		currentKey->DecrementCurrentElementNumber();
		return true;
	}

	//
	//  There was no previous element, so we need to find the previous terminal node.
	//  Since this is a terminal node, the next terminal node is this node's
	//  left brother.
	//
	
	pos = node->RightBrother();
	if( !pos )
	{
		node->SetCurrentElement( ((pNodeElement)0) );
		return false;
	}

	if( ReadNode( dbHandle, &previousTerminalNode, pos ) == CQL_FAILURE )
		throw IndexAccessException( __FILE__, __LINE__ );

	//
	//  There is another terminal node.  The last element is the desired key.
	//
	currentKey->SetCurrentNode( previousTerminalNode );
	previousTerminalNode->SetCurrentElement( previousTerminalNode->last() );
	currentKey->SetCurrentElementNumber();
	return true;
}


Index::~Index( void )
{
	currentKey = ((pIndexKeyDescriptor)0);
	file = ((pFileManager)0);
	header.IndexHeader::~IndexHeader();
	indexName_.CqlString::~CqlString();

	// FIXED
	Accessor *acc;
	for( acc = keys_.first(); acc; acc = keys_.next() )
	{
		currentKey = dynamic_cast< IndexKeyDescriptor* >( acc );
		if( currentKey->lengthIndex() )
		{
			IndexSegmentDescriptor *isd = dynamic_cast< IndexSegmentDescriptor* >( currentKey->segments().first() );
			if( isd->column() )
				delete isd->column();
			isd->column( 0 );
			delete isd;
		}
		else
			currentKey->segments().destroy();
	}

	keys_.destroy();
	transactionCounter = 0;
	fileOpen_ = temporary_ = false;
}


NI Index::UpdateParentCounts( DatabaseHandle& dbHandle, pNode node )
{
	pNode parentNode;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	if( !node->Parent() )
		return CQL_SUCCESS;

	if( ReadNode( dbHandle, &parentNode, node->Parent() ) == CQL_FAILURE )
		return CQL_FAILURE;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	if( node->Dirty() == CQL_NO )
	{
		file->writeLock( node->Location() );
		node->SetDirty();
	}

	return parentNode->UpdateNonterminalCount( dbHandle, this, node->Location(), node->NumberOfEntries() );
}


UL Index::countEqual( DatabaseHandle& dbHandle )
{
	pNodeElement element;
	pNode node;
	UL eqCount = 0;
	CompareResult result;
	RECID pos;

	NodeElement *inputElement;
	if( currentKey->CreateElementFromSegments( dbHandle, &inputElement, 0 ) == CQL_FAILURE )
		throw InternalErrorException( __FILE__, __LINE__ );

	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		throw BtreeInconsistentException( __FILE__, __LINE__ );

	if( node->NumberOfEntries() == 0 )
		return 0;

	while( node->Terminal() == CQL_NO )
	{
		pos = node->LowerKeyNode();

		for( element = node->first(); element; element = node->next() )
		{
			if( inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ ) == THIS_LESS_THAN_OTHER )
				break;

			pos = element->Son();
		}

		if( ReadNode( dbHandle, &node, pos ) == CQL_FAILURE )
			throw BtreeInconsistentException( __FILE__, __LINE__ );
	}

	for( element = node->first(); element; element = node->next() )
	{
		result = inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ );
		switch( result )
		{
		case THIS_LESS_THAN_OTHER :
			break;

		case THIS_EQUAL_TO_OTHER :
			eqCount++;
			break;

		case THIS_GREATER_THAN_OTHER :
			return eqCount;

		case COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	//
	//  if we get here, the last element in the terminal node matched the input key
	//
	while( node->RightBrother() )
	{
		if( ReadNode( dbHandle, &node, node->RightBrother() ) == CQL_FAILURE )
			throw BtreeInconsistentException( __FILE__, __LINE__ );

		for( element = node->first(); element; element = node->next() )
		{
			result = inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ );

			switch( result )
			{
			case THIS_LESS_THAN_OTHER :
				break;

			case THIS_EQUAL_TO_OTHER :
				eqCount++;
				break;

			case THIS_GREATER_THAN_OTHER :
				return eqCount;

			case COMPARE_RESULT_UNSET :
				throw InternalErrorException( __FILE__, __LINE__ );
			}
		}
	}

	//
	//  no more right brothers
	//
	return eqCount;
}


UL Index::countLessOrEqual( DatabaseHandle& dbHandle )
{
	pNodeElement element;
	pNode node;
	UL leqCount = 0;
	CompareResult result;
	RECID pos;

	NodeElement *inputElement;
	if( currentKey->CreateElementFromSegments( dbHandle, &inputElement, 0 ) == CQL_FAILURE )
		throw InternalErrorException( __FILE__, __LINE__ );

	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		throw BtreeInconsistentException( __FILE__, __LINE__ );

	if( node->NumberOfEntries() == 0 )
		return 0;

	while( node->Terminal() == CQL_NO )
	{
		pos = node->LowerKeyNode();

		for( element = node->first(); element; element = node->next() )
		{
			if( inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ ) == THIS_LESS_THAN_OTHER )
				break;

			leqCount += element->Entries();
			pos = element->Son();
		}

		if( ReadNode( dbHandle, &node, pos ) == CQL_FAILURE )
			throw BtreeInconsistentException( __FILE__, __LINE__ );
	}

	for( element = node->first(); element; element = node->next() )
	{
		result = inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ );

		switch( result )
		{
		case THIS_LESS_THAN_OTHER :
			leqCount++;
			break;

		case THIS_EQUAL_TO_OTHER :
			leqCount++;
			break;

		case THIS_GREATER_THAN_OTHER :
			return leqCount;

		case COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	//  if we get here, the last element in the terminal node matched the input key
	while( node->RightBrother() )
	{
		if( ReadNode( dbHandle, &node, node->RightBrother() ) == CQL_FAILURE )
			throw BtreeInconsistentException( __FILE__, __LINE__ );

		for( element = node->first(); element; element = node->next() )
		{
			result = inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ );

			switch( result )
			{
			case THIS_LESS_THAN_OTHER :
				break;

			case THIS_EQUAL_TO_OTHER :
				leqCount++;
				break;

			case THIS_GREATER_THAN_OTHER :
				return leqCount;

			case COMPARE_RESULT_UNSET :
				throw InternalErrorException( __FILE__, __LINE__ );
			}
		}
	}

	//  no more right brothers
	return leqCount;
}


UL Index::countGreaterOrEqual( DatabaseHandle& dbHandle )
{
	pNodeElement element;
	pNode node;
	UL geqCount = 0;
	CompareResult result;
	RECID pos;

	NodeElement *inputElement;
	if( currentKey->CreateElementFromSegments( dbHandle, &inputElement, 0 ) == CQL_FAILURE )
		throw InternalErrorException( __FILE__, __LINE__ );

	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( node->NumberOfEntries() == 0 )
		return 0;

	while( node->Terminal() == CQL_NO )
	{
		pos = node->LowerKeyNode();

		for( element = node->first(); element; element = node->next() )
		{
			if( inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ ) == THIS_LESS_THAN_OTHER )
				break;

			pos = element->Son();
		}

		//
		//  count the greater keys
		//
		do
		{
			geqCount += element->Entries();
		} while( ( element = node->next() ) != ((pNodeElement)0) );

		if( ReadNode( dbHandle, &node, pos ) == CQL_FAILURE )
			throw BtreeInconsistentException( __FILE__, __LINE__ );
	}

	for( element = node->first(); element; element = node->next() )
	{
		result = inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ );

		switch( result )
		{
		case THIS_LESS_THAN_OTHER :
			break;

		case THIS_EQUAL_TO_OTHER :
		case THIS_GREATER_THAN_OTHER :
			do
			{
				geqCount++;
			} while( ( element = node->next() ) != ((pNodeElement)0) );
			return geqCount;

		case COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	return geqCount;
}


UL Index::countLess( DatabaseHandle& dbHandle )
{
	pNodeElement element;
	pNode node;
	UL lCount = 0;
	CompareResult result;
	RECID pos;

	NodeElement *inputElement;
	if( currentKey->CreateElementFromSegments( dbHandle, &inputElement, 0 ) == CQL_FAILURE )
		throw InternalErrorException( __FILE__, __LINE__ );

	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		throw BtreeInconsistentException( __FILE__, __LINE__ );

	if( node->NumberOfEntries() == 0 )
		return 0;

	while( node->Terminal() == CQL_NO )
	{
		pos = node->LowerKeyNode();

		for( element = node->first(); element; element = node->next() )
		{
			if( inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ ) == THIS_LESS_THAN_OTHER )
				break;

			lCount += element->Entries();
			pos = element->Son();
		}

		if( ReadNode( dbHandle, &node, pos ) == CQL_FAILURE )
			throw BtreeInconsistentException( __FILE__, __LINE__ );
	}

	for( element = node->first(); element; element = node->next() )
	{
		result = inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ );

		switch( result )
		{
		case THIS_LESS_THAN_OTHER :
			lCount++;
			break;

		case THIS_EQUAL_TO_OTHER :
		case THIS_GREATER_THAN_OTHER :
			return lCount;

		case COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	return lCount;
}


UL Index::countGreater( DatabaseHandle& dbHandle )
{
	pNodeElement element;
	pNode node;
	UL gCount = 0;
	CompareResult result;
	RECID pos;

	NodeElement *inputElement;
	if( currentKey->CreateElementFromSegments( dbHandle, &inputElement, 0 ) == CQL_FAILURE )
		throw InternalErrorException( __FILE__, __LINE__ );

	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		throw BtreeInconsistentException( __FILE__, __LINE__ );

	if( node->NumberOfEntries() == 0 )
		return 0;

	while( node->Terminal() == CQL_NO )
	{
		pos = node->LowerKeyNode();

		for( element = node->first(); element; element = node->next() )
		{
			if( inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ ) == THIS_LESS_THAN_OTHER )
				break;

			pos = element->Son();
		}

		//
		//  count the greater keys
		//
		while( ( element = node->next() ) != ((pNodeElement)0) )
			gCount += element->Entries();

		if( ReadNode( dbHandle, &node, pos ) == CQL_FAILURE )
			throw BtreeInconsistentException( __FILE__, __LINE__ );
	}

	for( element = node->first(); element; element = node->next() )
	{
		result = inputElement->Compare( *element, currentKey->segments(), false, segmentsToCompare_ );

		switch( result )
		{
		case THIS_LESS_THAN_OTHER :
		case THIS_EQUAL_TO_OTHER :
			break;

		case THIS_GREATER_THAN_OTHER :
			do
			{
				gCount++;
			} while( ( element = node->next() ) != ((pNodeElement)0) );
			return gCount;

		case COMPARE_RESULT_UNSET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	return gCount;
}


void Index::CheckNode( DatabaseHandle& dbHandle, pNode node, RECID par, pUL numberOfEntries )
{
	pNodeElement element, previousElement, nextElement = ((pNodeElement)0), previous = ((pNodeElement)0);
	pNode lBrother, rBrother;
	UL localNumEntries = 0;

	if( par != node->Parent() )
		assert( 0 );

	if( node->LeftBrother() )
	{
		if( ReadNode( dbHandle, &lBrother, node->LeftBrother() ) == CQL_FAILURE )
			assert( 0 );

		if( lBrother->RightBrother() != node->Location() )
			assert( 0 );
	}

	if( node->RightBrother() )
	{
		if( ReadNode( dbHandle, &rBrother, node->RightBrother() ) == CQL_FAILURE )
			assert( 0 );

		if( rBrother->LeftBrother() != node->Location() )
			assert( 0 );
	}

	if( node->NumberOfEntries() )
	{
		for( element = node->first(), localNumEntries = 0; element; element = node->next(), localNumEntries++ )
		{
			if( element->CheckUseFlag() == CQL_YES )
				assert( 0 );
			element->SetCheckUseFlag();
			if( nextElement && element != nextElement )
				assert( 0 );
			previousElement = element->prev();
			if( previousElement != previous )
				assert( 0 );
			nextElement = element->next();
			previous = element;
		}
	}

	if( node->NumberOfEntries() != localNumEntries )
		assert( 0 );

	if( node->Terminal() == CQL_YES && numberOfEntries != ((pUL)0) )
		*numberOfEntries += localNumEntries;
}


void Index::CheckDescendents( DatabaseHandle& dbHandle, pNode node, pUL numberOfEntries )
{
	pNodeElement element;
	pNode other;

	if( node->Terminal() == CQL_YES )
		return;

	if( node->LowerKeyNode() )
	{
		if( ReadNode( dbHandle, &other, node->LowerKeyNode() ) == CQL_FAILURE )
			assert( 0 );

		CheckNode( dbHandle, other, node->Location(), numberOfEntries );
		CheckDescendents( dbHandle, other, numberOfEntries );
	}

	for( element = node->first(); element; element = node->next() )
	{
		if( ReadNode( dbHandle, &other, element->Son() ) == CQL_FAILURE )
			assert( 0 );

		CheckNode( dbHandle, other, node->Location(), numberOfEntries );
		CheckDescendents( dbHandle, other, numberOfEntries );
	}
}


void Index::ZeroElementUseFlags( DatabaseHandle& dbHandle, pNode node )
{
	pNodeElement element;
	pNode other;

	for( element = node->first(); element; element = node->next() )
		element->ClearCheckUseFlag();

	if( node->Terminal() == CQL_YES )
		return;

	if( node->LowerKeyNode() )
	{
		if( ReadNode( dbHandle, &other, node->LowerKeyNode() ) == CQL_FAILURE )
			assert( 0 );

		ZeroElementUseFlags( dbHandle, other );
	}

	for( element = node->first(); element; element = node->next() )
	{
		if( ReadNode( dbHandle, &other, element->Son() ) == CQL_FAILURE )
			assert( 0 );

		ZeroElementUseFlags( dbHandle, other );
	}
}


void Index::CheckBtreeIndex( DatabaseHandle& dbHandle, pUL numberOfEntries )
{
	pNode node;

	if( ReadNode( dbHandle, &node, currentKey->RootLocation() ) == CQL_FAILURE )
		assert( 0 );

	ZeroElementUseFlags( dbHandle, node );

	if( numberOfEntries )
		*numberOfEntries = ((UL)0);

	CheckNode( dbHandle, node, ((RECID)0), numberOfEntries );
	CheckDescendents( dbHandle, node, numberOfEntries );

	if( numberOfEntries )
		hAEnv ->logPrintf(AbstractLogger::TRACEALL, "numberOfEntries is %d\n", *numberOfEntries );
}


US Index::InitialNodeSpace( void )
{
	return CQL_LOGICAL_PAGE_SIZE - ( ( 4 * sizeof( RECID ) ) + sizeof( UL ) + sizeof( US ) + sizeof( NI ) );
}


NI Index::AddIndexMember( DatabaseHandle& dbHandle, pIndexKeyDescriptor keyDesc )
{
	pRECID oldKeyDescriptorLocations, newKeyDescriptorLocations;
	RECID descriptorPage, rootPage, newListHead;
	UL oldNumberOfKeys;
	pNode node;

	//
	//  Read the header
	//
	if( header.Read( dbHandle, file ) == CQL_FAILURE )
		return CQL_FAILURE;

	oldNumberOfKeys = header.NumberOfKeys();
	header.SetNumberOfKeys( oldNumberOfKeys + 1 );

	oldKeyDescriptorLocations = header.KeyDescriptorLocations();

	newKeyDescriptorLocations = new RECID[ header.NumberOfKeys() ];
	if( !newKeyDescriptorLocations )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

	memset( newKeyDescriptorLocations, 0, sizeof( RECID ) );
	memcpy( newKeyDescriptorLocations, oldKeyDescriptorLocations, sizeof( RECID ) * oldNumberOfKeys );
	header.SetKeyDescriptorLocations( newKeyDescriptorLocations );
	delete oldKeyDescriptorLocations;

	//
	//  Now we have an array of key descriptor locations with one extra slot at the
	//  end, with the value 0 in that slot.  We now need to assign the first available
	//  page in the index file to be the key descriptor page, and to assign it to that
	//  slot.
	//
	if( header.FreeNodeList() )
	{
		descriptorPage = header.FreeNodeList();
		if( file->InputSeek( descriptorPage ) == CQL_FAILURE )
			return CQL_FAILURE;
		file->read( ((void*)hAEnv->globalBuffer()), CQL_LOGICAL_PAGE_SIZE );
		memcpy( &newListHead, hAEnv->globalBuffer(), sizeof( newListHead ) );
		header.SetFreeNodeList( newListHead );
		//  header will be written later
	}
	else
	{
		descriptorPage = header.EndOfFile();
		header.SetEndOfFile( descriptorPage + CQL_LOGICAL_PAGE_SIZE );
	}

	newKeyDescriptorLocations[ header.NumberOfKeys() - 1 ] = descriptorPage;

	//
	//  Now do the same thing for the new root page
	//
	if( header.FreeNodeList() )
	{
		rootPage = header.FreeNodeList();
		if( file->InputSeek( rootPage ) == CQL_FAILURE )
			return CQL_FAILURE;
		file->read( ((void*)hAEnv->globalBuffer()), CQL_LOGICAL_PAGE_SIZE );
		memcpy( &newListHead, hAEnv->globalBuffer(), sizeof( newListHead ) );
		header.SetFreeNodeList( newListHead );
		//  header will be written later
	}
	else
	{
		rootPage = header.EndOfFile();
		header.SetEndOfFile( rootPage + CQL_LOGICAL_PAGE_SIZE );
	}

	node = new Node( rootPage );
	if( !node )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

	node->SetTerminal();
	node->SetRoot();
	node->SetRemainingSpace( InitialNodeSpace() );

	keyDesc->SetRootLocation( rootPage );
	if( keyDesc->Write( dbHandle, file, *node, descriptorPage ) == CQL_FAILURE )
	{
		delete node;
		return CQL_FAILURE;
	}

	node->SetLocation( rootPage );
	if( node->WriteNode( dbHandle, file ) == CQL_FAILURE )
	{
		delete node;
		return CQL_FAILURE;
	}

	delete node;

	if( header.Write( dbHandle, file ) == CQL_FAILURE )
		return CQL_FAILURE;

	keys_.add( keyDesc );

	return CQL_SUCCESS;
}


NI Index::DeleteIndexMember( DatabaseHandle& dbHandle, UNI keyno )
{
	pRECID oldKeyDescriptorLocations, newKeyDescriptorLocations, dLocOld, dLocNew;
	RECID deleteDescriptorPage;
	UL oldNumberOfKeys;
	UNI loop;

	if( header.Read( dbHandle, file ) == CQL_FAILURE )
		return CQL_FAILURE;

	oldNumberOfKeys = header.NumberOfKeys();
	header.SetNumberOfKeys( oldNumberOfKeys - 1 );

	oldKeyDescriptorLocations = header.KeyDescriptorLocations();

	newKeyDescriptorLocations = new RECID[ oldNumberOfKeys - 1 ];
	if( !newKeyDescriptorLocations )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

	//
	//  Copy the key descriptor page locations for key numbers lower than the key
	//  being deleted.
	//
	for( dLocOld = oldKeyDescriptorLocations, dLocNew = newKeyDescriptorLocations, loop = 0; loop < keyno; loop++, dLocOld++, dLocNew++ )
		*dLocOld = *dLocNew;

	//
	//  Move past the descriptor page for the key being deleted, saving its location.
	//
	deleteDescriptorPage = *dLocOld++;
	
	//
	//  Copy the rest
	//
	for( loop++; loop < oldNumberOfKeys; loop++, dLocOld++, dLocNew++ )
		*dLocOld = *dLocNew;

	header.SetKeyDescriptorLocations( newKeyDescriptorLocations );
	delete oldKeyDescriptorLocations;

	//
	//  Now we place all nodes which are part of the tree being deleted onto the
	//  free node list.
	//
	if( DeleteTree( dbHandle, deleteDescriptorPage ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI Index::DeleteTree( DatabaseHandle& dbHandle, RECID page )
{
	pNode node;
	pNodeElement element;

	if( ReadNode( dbHandle, &node, page ) == CQL_FAILURE )
		return dbHandle.returnError( BTREE_INCONSISTENT, __FILE__, __LINE__ );

	//
	//  If node is a terminal node, delete it and return
	//
	if( node->Terminal() == CQL_YES )
	{
		if( DeleteNode( dbHandle, page ) == CQL_FAILURE )
			return CQL_FAILURE;

		return CQL_SUCCESS;
	}

	//
	//  Node is non-terminal.  Delete all its descendents before deleting it
	//
	if( node->LowerKeyNode() )
		if( DeleteTree( dbHandle, node->LowerKeyNode() ) == CQL_FAILURE )
			return CQL_FAILURE;

	for( element = node->first(); element; element = node->next() )
		if( DeleteTree( dbHandle, element->Son() ) == CQL_FAILURE )
			return CQL_FAILURE;

	if( DeleteNode( dbHandle, page ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI Index::DeleteNode( DatabaseHandle& dbHandle, RECID page )
{
	RECID oldListHead, zero;

	if( header.FreeNodeList() )
	{
		oldListHead = header.FreeNodeList();
		if( file->InputSeek( page ) == CQL_FAILURE )
			return CQL_FAILURE;

		file->write( ((void*)&oldListHead), sizeof( oldListHead ) );
	}
	else
	{
		//
		//  Free node list is empty, so this becomes the first entry with a 0 as its
		//  forward pointer.
		//
		zero = ((RECID)0);
		if( file->InputSeek( page ) == CQL_FAILURE )
			return CQL_FAILURE;

		file->write( ((void*)&zero), sizeof( zero ) );
	}


	header.SetFreeNodeList( page );

	if( header.Write( dbHandle, file ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


IndexHeader::IndexHeader( void )
	:  endOfFile(0),
	   freeNodeList(0),
	   keyDescriptorLocations( ((pRECID)0) ),
	   machineId(0),
	   numberOfKeys(0),
	   initFailed(CQL_NO)
{
}


IndexHeader::IndexHeader( UL machId, UL nKeys )
	:  endOfFile( 0 ),
	   freeNodeList( ((RECID)0) ),
	   keyDescriptorLocations( ((pRECID)0) ),
	   machineId( machId ),
	   numberOfKeys( nKeys ),
	   initFailed( CQL_YES )
{
	UL loop;

	keyDescriptorLocations = new RECID[ numberOfKeys ];
	if( !keyDescriptorLocations )
		return;

	for( loop = 0; loop < numberOfKeys; loop++ )
		keyDescriptorLocations[ loop ] = ( ( loop + 1 ) * CQL_LOGICAL_PAGE_SIZE );

	//
	//  one page for header
	//
	//  one page for each key description
	//
	//  one page for each root node
	//
	endOfFile = CQL_LOGICAL_PAGE_SIZE * ( ( 2 * numberOfKeys ) + 1 );
	initFailed = CQL_NO;
}


NI IndexHeader::Assign( DatabaseHandle& dbHandle, IndexHeader& other )
{
	endOfFile = other.endOfFile;
	freeNodeList = other.freeNodeList;
	machineId = other.machineId;
	numberOfKeys = other.numberOfKeys;
	initFailed = other.initFailed;

	if( other.keyDescriptorLocations )
	{
		keyDescriptorLocations = new RECID[ numberOfKeys ];
		if( !keyDescriptorLocations )
			return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

		memcpy( keyDescriptorLocations, other.keyDescriptorLocations, numberOfKeys * sizeof( RECID ) );
	}
	else
		keyDescriptorLocations = ((pRECID)0);

	return CQL_SUCCESS;
}


NI IndexHeader::Setup( DatabaseHandle& dbHandle, UL machId, UL nKeys )
{
	UL loop;

	machineId = machId;
	numberOfKeys = nKeys;
	freeNodeList = ((RECID)0);
	initFailed = CQL_NO;

	keyDescriptorLocations = new RECID[ numberOfKeys ];
	if( !keyDescriptorLocations )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

	for( loop = 0; loop < numberOfKeys; loop++ )
		keyDescriptorLocations[ loop ] = ( ( loop + 1 ) * CQL_LOGICAL_PAGE_SIZE );

	endOfFile = CQL_LOGICAL_PAGE_SIZE * ( ( 2 * numberOfKeys ) + 1 );
	return CQL_SUCCESS;
}


NI IndexHeader::Write( DatabaseHandle&, pFileManager file )
{
	UL loop;

	if( file->OutputSeek( 0 ) == CQL_FAILURE )
		return CQL_FAILURE;

	*file << machineId << numberOfKeys << endOfFile << freeNodeList;

	for( loop = 0; loop < numberOfKeys; loop++ )
		*file << keyDescriptorLocations[ loop ];

	return CQL_SUCCESS;
}


NI IndexHeader::Read( DatabaseHandle& dbHandle, pFileManager file )
{
	UL loop;
	pRECID kdl;

	if( file->InputSeek( 0 ) == CQL_FAILURE )
		return CQL_FAILURE;

	*file >> machineId >> numberOfKeys >> endOfFile >> freeNodeList;

	keyDescriptorLocations = new RECID[ numberOfKeys ];
	if( !keyDescriptorLocations )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

	for( loop = 0, kdl = keyDescriptorLocations; loop < numberOfKeys; loop++, kdl++ )
		*file >> *kdl;

	return CQL_SUCCESS;
}


NI IndexHeader::SetKeyDescriptorLocation( RECID oldpos, RECID newpos )
{
	UNI loop;

	for( loop = 0; loop < numberOfKeys; loop++ )
	{
		if( keyDescriptorLocations[ loop ] == oldpos )
		{
			keyDescriptorLocations[ loop ] = newpos;
			return CQL_SUCCESS;
		}
	}

	return CQL_FAILURE;
}


IndexHeader::~IndexHeader( void )
{
	machineId = numberOfKeys = 0;
	endOfFile = freeNodeList = 0;
	if( keyDescriptorLocations )
	{
		delete [] keyDescriptorLocations;
		keyDescriptorLocations = ((pRECID)0);
	}
}


IndexKeyDescriptor::IndexKeyDescriptor( AccessorTypes atype, US kn )
	: Accessor( atype, kn ),
	  currentNode( ((pNode)0) ),
	  currentNodeLocation( 0 ),
	  currentSegment( ((pAbstractSegmentDescriptor)0) ),
	  currentElementNumber( 0 ),
	  descriptorLocation_( 0 ),
	  dirty_( false ),
	  lengthIndex_( false ),
	  maximumKeyLength_( 0 ),
	  rootLocation( 0 )
{
}


IndexKeyDescriptor::~IndexKeyDescriptor( void )
{
}


NI IndexKeyDescriptor::Assign( DatabaseHandle& dbHandle, IndexKeyDescriptor& other )
{
	IndexKeyDescriptor& tOther = ((IndexKeyDescriptor&)other);

	if( tOther.currentNode )
	{
		currentNode = new Node;
		if( !currentNode )
			return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

		if( currentNode->Assign( dbHandle, *tOther.currentNode ) == CQL_FAILURE )
			return CQL_FAILURE;
	}
	else
		currentNode = ((pNode)0);

	currentNodeLocation = tOther.currentNodeLocation;

	if( tOther.currentSegment )
	{
		currentSegment = AbstractSegmentDescriptor::createObject( tOther.currentSegment->segmentNumber(), tOther.currentSegment->segmentType() );
		//*********************  catch exceptions
		*currentSegment = *tOther.currentSegment;
	}
	else
		currentSegment = ((pAbstractSegmentDescriptor)0);

	currentElementNumber = tOther.currentElementNumber;
	descriptorLocation_ = tOther.descriptorLocation_;
	maximumKeyLength_ = tOther.maximumKeyLength_;
	rootLocation = tOther.rootLocation;

	*( dynamic_cast< Accessor* >( this ) ) = dynamic_cast< Accessor& >( other );
	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::AddSegment( DatabaseHandle&, US segno, CqlColumnTypes type, UL len, US colNo, bool desc )
{
	AbstractColumnDescriptor *acol;

	try
	{
		acol = AbstractColumnDescriptor::createObject( type, colNo, desc );
	}
	catch( AbstractObjectCreationException& ex )
	{
		*hAEnv << ex;
		return CQL_FAILURE;
	}

	SegmentTypes stype( ( desc ? CQL_DESCENDING : CQL_ASCENDING ) );
	pAbstractSegmentDescriptor seg = AbstractSegmentDescriptor::createObject( segno, stype );
	seg->column( acol );

	segments_.add( seg );
	maximumKeyLength_ = ((US)( maximumKeyLength_ + len ) );
	numberOfSegments_++;
	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::Read( DatabaseHandle&, FileManager& file )
{
	UNI loop;

	if( file.InputSeek( descriptorLocation_ ) == CQL_FAILURE )
		return CQL_FAILURE;

	AccessorTypes atype;
	file >> atype >> keyNumber_ >> lengthIndex_ >> maximumKeyLength_ >> numberOfSegments_ >> rootLocation;
	typeType( atype.typeType() );
	aqtypeType( atype.aqtypeType() );
	for( loop = 0; loop < numberOfSegments_; loop++ )
	{
		AbstractSegmentDescriptor *seg;
		file >> &seg;
		segments_.add( seg );
	}

	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::FirstSegment( DatabaseHandle& dbHandle )
{
	currentSegment = segments_.first();
	if( !currentSegment )
		return dbHandle.returnError( LIST_INCONSISTENCY, __FILE__, __LINE__ );

	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::NextSegment( void )
{
	currentSegment = segments_.next();
	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::Write( DatabaseHandle& dbHandle, pFileManager file, Node& node )
{
	pAbstractSegmentDescriptor seg;

	if( file->OutputSeek( descriptorLocation_ ) == CQL_FAILURE )
		return CQL_FAILURE;

	AccessorTypes atype( typeType(), aqtypeType() );
	*file << atype << keyNumber_ << lengthIndex_ << maximumKeyLength_ << numberOfSegments_ << rootLocation;
	typeType( atype.typeType() );
	aqtypeType( atype.aqtypeType() );
	for( seg = segments_.first(); seg; seg = segments_.next() )
		*file << seg;

	node.SetLocation( rootLocation );
	node.SetTerminal();
	if( node.WriteNode( dbHandle, file ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::ZeroSegmentValues( void )
{
	pAbstractSegmentDescriptor seg;

	for( seg = segments_.first(); seg; seg = segments_.next() )
	{
		// ((ColumnDescriptor*)seg->column())->setNullflag();
		try
		{
			dynamic_cast< ColumnDescriptor* >( seg->column() )->setNullflag();
		}
		catch( ... )
		{
			return CQL_FAILURE;
		}
	}

	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::Write( DatabaseHandle& dbHandle, pFileManager file, Node& node, RECID descLoc )
{
	descriptorLocation_ = descLoc;
	return Write( dbHandle, file, node );
}


NI IndexKeyDescriptor::SetSegment( DatabaseHandle& dbHandle, pUC key )
{
	if( btreePrinting == CQL_YES )
		fprintf( stderr,
				 "%s, %d, this=%lx, SetSegment, currentSegment=%lx, key = %s\n",
				 __FILE__,
				 __LINE__,
				 ((UL)this),
				 ((UL)currentSegment),
				 key );

	if( !currentSegment )
		return dbHandle.returnError( SEGMENT_DOES_NOT_EXIST, __FILE__, __LINE__ );

	ColumnDescriptor& cd = dynamic_cast< ColumnDescriptor& >( *currentSegment->column() );
	cd << key;

	if( NextSegment() == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::SetSegment( DatabaseHandle& dbHandle, ColumnDescriptor *column )
{
	if( !currentSegment )
		return dbHandle.returnError( SEGMENT_DOES_NOT_EXIST, __FILE__, __LINE__ );

	if( column->isNull() == CQL_YES )
		dynamic_cast< ColumnDescriptor* >( currentSegment->column() )->setNullflag();
	else
	{
		ColumnDescriptor *cd = dynamic_cast< ColumnDescriptor* >( currentSegment->column() );
		cd->clearNullflag();
		BinaryValue bv;
		*column >> bv;
		*cd << bv;
		currentSegment = currentSegment->next();
	}

	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::GetSegment( DatabaseHandle& dbHandle, pUC key )
{
	if( !currentSegment )
		return dbHandle.returnError( SEGMENT_DOES_NOT_EXIST, __FILE__, __LINE__ );

	ColumnDescriptor& cd = dynamic_cast< ColumnDescriptor& >( *currentSegment->column() );
	//
	//  stream out value?  to whom?
	//  Do we want stream in/out to classes templated against AbstractType?
	//  In these cases, they would be useful.  But, assignment operators might work.
	//  However, an assignment operator is unidirectional, and gives us no way
	//  to get the data out.
	//  To get the data out using an assignment operator, the target needs to be a
	//  class with the appropriate assignment operator defined.
	//
	cd << key;
	//  return ((pColumnDescriptor)currentSegment->column())->GetColumn( dbHandle, key );
	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::CreateElementFromSegments( DatabaseHandle& dbHandle, pNodeElement *element, RECID pos )
{
	pAbstractSegmentDescriptor seg;
	pNodeElement el;

	if( btreePrinting == CQL_YES )
		fprintf( stderr, "%s, %d, creating element for %ld\n", __FILE__, __LINE__, pos );

	el = new NodeElement( dbHandle );
	if( !el )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

	el->SetSon( pos );

	// Compute the key length, and initialize the TempBuffer
	UL keyLength;

	for( seg = segments_.first(), keyLength = 0; seg; seg = segments_.next() )
	{
		ColumnDescriptor *cd = reinterpret_cast< ColumnDescriptor* >( seg->column() );
		if( cd->isNull() )
			keyLength++;
		else
			//  extra byte for null indicator
			keyLength += ( 1 + cd->streamLength() );
	}

	el->setBuffer( keyLength );

	for( seg = segments_.first(); seg; seg = segments_.next() )
	{
		ColumnDescriptor *cd = reinterpret_cast< ColumnDescriptor* >( seg->column() );

		*el << FOUR_BYTE_LENGTH << NO_COPY << cd->length();
		*cd >> *el;
	}

	*element = el;

	return CQL_SUCCESS;
}


NI IndexKeyDescriptor::ChangeRootPointer( DatabaseHandle&, pFileManager file, RECID rootLoc )
{
	if( file->OutputSeek( descriptorLocation_ + ( 2 * sizeof( US ) ) + sizeof( NI ) ) == CQL_FAILURE )
		return CQL_FAILURE;

	*file << rootLoc;
	rootLocation = rootLoc;
	return CQL_SUCCESS;
}


void IndexKeyDescriptor::SetCurrentNode( pNode node )
{
	currentNode = node;

	if( node )
		currentNodeLocation = node->Location();
}


void IndexKeyDescriptor::SetCurrentElementNumber( void )
{
	pNodeElement element;
	UNI eno;

	for( element = currentNode->first(), eno = 0; element; element = currentNode->next(), eno++ )
		if( element == currentNode->CurrentElement() )
			currentElementNumber = eno;
}


void IndexKeyDescriptor::ReturnToCurrentElement( pNode node )
{
	pNodeElement element;
	UNI eno;

	for( element = currentNode->first(), eno = 0; eno < currentElementNumber && element; element = currentNode->next(), eno++ )
		;

	node->SetCurrentElement( element );
}


void IndexKeyDescriptor::remove( AbstractDatabaseHandle&, MemoryIndex&, RECID& )
{
	throw InternalErrorException( __FILE__, __LINE__ );
}


IndexSegmentDescriptor::IndexSegmentDescriptor( const US sno, const SegmentTypes& stype ) : AbstractSegmentDescriptor( sno, stype )
{
}


IndexSegmentDescriptor::~IndexSegmentDescriptor( void )
{
}
