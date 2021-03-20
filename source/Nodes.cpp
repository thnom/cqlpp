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


Node::Node( void )
	: NodeElementList(),
	  currentElement( 0 ),
	  higherElement( 0 ),
	  leftBrother( 0 ),
	  leftEntries( 0 ),
	  location( 0 ),
	  lowerElement( 0 ),
	  lowerKeyNode( 0 ),
	  numberOfEntries( 0 ),
	  parent( 0 ),
	  remainingSpace( 0 ),
	  rightBrother( 0 ),
	  rightEntries( 0 ),
	  dirty( CQL_NO ),
	  root( CQL_NO ),
	  temporary( CQL_NO ),
	  terminal( CQL_NO )
{
}


Node::Node( RECID loc )
	: NodeElementList(),
	  currentElement( 0 ),
	   higherElement( 0 ),
	   leftBrother( 0 ),
	   leftEntries( 0 ),
	   location( loc ),
	   lowerElement( 0 ),
	   lowerKeyNode( 0 ),
	   numberOfEntries( 0 ),
	   parent( 0 ),
	   remainingSpace( 0 ),
	   rightBrother( 0 ),
	   rightEntries( 0 ),
	   dirty( CQL_NO ),
	   root( CQL_NO ),
	   temporary( CQL_NO ),
	   terminal( CQL_NO )
{
}


Node::~Node( void )
{
	destroy();
}


NI Node::Assign( DatabaseHandle& dbHandle, Node& other )
{
	*((NodeElementList*)this) = ((NodeElementList&)other);

	location = other.location;
	parent = other.parent;
	leftBrother = other.leftBrother;
	leftEntries = other.leftEntries;
	rightBrother = other.rightBrother;
	rightEntries = other.rightEntries;
	lowerKeyNode = other.lowerKeyNode;
	numberOfEntries = other.numberOfEntries;
	remainingSpace = other.remainingSpace;

	if( other.currentElement )
	{
		currentElement = new NodeElement( dbHandle );
		if( !currentElement )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*currentElement = *other.currentElement;
	}
	else
		currentElement = 0;

	if( other.lowerElement )
	{
		lowerElement = new NodeElement( dbHandle );
		if( !lowerElement )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*lowerElement = *other.lowerElement;
	}
	else
		lowerElement = 0;

	if( other.higherElement )
	{
		higherElement = new NodeElement( dbHandle );
		if( !higherElement )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*higherElement = *other.higherElement;
	}
	else
		higherElement = 0;

	root = other.root;
	terminal = other.terminal;
	dirty = other.dirty;
	temporary = other.temporary;

	return CQL_SUCCESS;
}


NI Node::WriteNode( DatabaseHandle&, pFileManager file )
{
	pNodeElement element;
	UL localNumEntries;

	if( file->OutputSeek( location ) == CQL_FAILURE )
		return CQL_FAILURE;

	*file << parent << leftBrother << rightBrother << numberOfEntries << remainingSpace << terminal;

	if( numberOfEntries == 0 )
		return CQL_SUCCESS;

	*file << lowerKeyNode;

	//  write the node values
	for( element = first(), localNumEntries = 0; element; element = next(), localNumEntries++ )
		if( element->Write( *file ) == CQL_FAILURE )
			return CQL_FAILURE;

	if( btreeDebugging && numberOfEntries != localNumEntries )
		assert( 0 );

	return CQL_SUCCESS;
}


NI Node::ReadNode( DatabaseHandle& dbHandle, pFileManager file, RECID tLocation )
{
	US loop;
	pNodeElement element;

	destroy();

	SetLocation( tLocation );

	if( file->InputSeek( tLocation ) == CQL_FAILURE )
		return CQL_FAILURE;

	*file >> parent >> leftBrother >> rightBrother >> numberOfEntries >> remainingSpace >> terminal;

	if( numberOfEntries == 0 )
		return CQL_SUCCESS;

	*file >> lowerKeyNode;

	for( loop = 0; loop < numberOfEntries; loop++ )
	{
		element = new NodeElement( dbHandle );
		if( !element )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		if( element->Read( *file ) == CQL_FAILURE )
			return CQL_FAILURE;

		add( element );
	}

	return CQL_SUCCESS;
}


NI Node::FindPositionInNode( DatabaseHandle&, pNodeElement inputElement, AbstractSegmentDescriptorList& segments )
{
	pNodeElement element, previousElement;
	CompareResult result;

	previousElement = ((pNodeElement)0);
	try
	{
		for( element = first(); element; element = next() )
		{
			result = inputElement->Compare( *element, segments, true );
	
			if( result == THIS_LESS_THAN_OTHER )
			{
				lowerElement = previousElement;
				higherElement = element;
				return CQL_SUCCESS;
			}

			previousElement = element;
		}
	}
	//exception
	catch( ... )
	{
		return CQL_FAILURE;
	}

	lowerElement = last();
	higherElement = ((pNodeElement)0);
	return CQL_SUCCESS;
}


NI Node::RollbackNode( pFileManager )
{
	return CQL_SUCCESS;
}


NI Node::AddElement( pNodeElement element )
{
	if( lowerElement )
		addAfter( lowerElement, element );
	else if( higherElement )
		addBefore( higherElement, element );
	else
		add( element );

	IncrementNumberOfEntries();
	ReduceRemainingSpace( element->SpaceNeeded() );

	return CQL_SUCCESS;
}


NI Node::AddElementToBeginning( pNodeElement element )
{
	if( !first() )
		add( element );
	else
		addBefore( first(), element );

	IncrementNumberOfEntries();

	ReduceRemainingSpace( element->SpaceNeeded() );

	return CQL_SUCCESS;
}


NI Node::AddElementToEnd( pNodeElement element )
{
	if( last() )
		addAfter( last(), element );
	else
		add( element );

	IncrementNumberOfEntries();

	ReduceRemainingSpace( element->SpaceNeeded() );

	return CQL_SUCCESS;
}


NI Node::FindMatchingElement( DatabaseHandle&, pNodeElement element, AbstractSegmentDescriptorList& segments  )
{
	pNodeElement el;
	CompareResult result;

	try
	{
		for( el = first(); el; el = next() )
		{
			result = el->Compare( *element, segments, false );

			if( result == THIS_EQUAL_TO_OTHER )
			{
				currentElement = el;
				return CQL_SUCCESS;
			}
		}
	}
	catch( ... )
	{
		//exception
		// leave this here so we can add exception processing later
		return CQL_FAILURE;
	}

	return CQL_FAILURE;
}


NI Node::ReplaceKey( DatabaseHandle& dbHandle, RECID child, pNodeElement element )
{
	pNodeElement el;

	for( el = first(); el; el = next() )
	{
		if( el->Son() == child )
		{
			el->updateKey( element );
			return CQL_SUCCESS;
		}
	}

	return dbHandle.returnError( BTREE_INCONSISTENT, __FILE__, __LINE__ );
}


#ifdef __CQL_FINE_GRAIN_DEBUGGING
NI Node::UpdateNonterminalCount( DatabaseHandle& dbHandle, pIndex index, RECID child, UL numEntries )
#else
NI Node::UpdateNonterminalCount( DatabaseHandle& dbHandle, pIndex, RECID child, UL numEntries )
#endif //  __CQL_FINE_GRAIN_DEBUGGING
{
	pNodeElement el;

#ifdef __CQL_FINE_GRAIN_DEBUGGING
	if( btreeDebugging )
		index->CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

	if( child == lowerKeyNode )
		return CQL_SUCCESS;

	for( el = first(); el; el = next() )
	{
		if( el->Son() == child )
		{
			el->SetEntries( numEntries );
#ifdef __CQL_FINE_GRAIN_DEBUGGING
			if( btreeDebugging )
				index->CheckBtreeIndex( dbHandle );
#endif  //  __CQL_FINE_GRAIN_DEBUGGING

			return CQL_SUCCESS;
		}
	}

	return dbHandle.returnError( BTREE_INCONSISTENT, __FILE__, __LINE__ );
}


NodeElement::NodeElement( AbstractDatabaseHandle& adh ) : TempBuffer( adh ), checkUseFlag( false ), entries( 0 ), hAdb_( adh ), son( 0 )
{
}


NodeElement::NodeElement( const NodeElement& other )
	: NodeElementListElement(),
	  TempBuffer( other.hAdb_ ),
	  checkUseFlag( other.checkUseFlag ),
	  entries( other.entries ),
	  hAdb_( other.hAdb_ ),
	  son( other.son )
{
}


NodeElement::~NodeElement( void )
{
}


NI NodeElement::Write( FileManager& file )
{
	UL length = size();
	file << son << entries << length;

	file.write( bufferBase(), length );
	return CQL_SUCCESS;
}


NI NodeElement::Read( FileManager& file )
{
	UL len;
	pUC tbuf;

	file >> son >> entries >> len;

	tbuf = new UC[ len ];
	if( !tbuf )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	file.read( ((void*)tbuf), len );
	setBuffer( len );
	*this << NO_COPY << FOUR_BYTE_LENGTH << len << tbuf;

	delete [] tbuf;
	return CQL_SUCCESS;
}


NodeElement& NodeElement::operator=( NodeElement& other )
{
	entries = other.entries;
	son = other.son;
	checkUseFlag = other.checkUseFlag;
	*((TempBuffer*)this) = ((TempBuffer&)other);
	return *this;
}


void NodeElement::updateKey( NodeElement *other )
{
	*((TempBuffer*)this) = *((TempBuffer*)other);
}


pNodeElement NodeElement::NextNodeElement( void )
{
	return ((pNodeElement)next());
}


pNodeElement NodeElement::PreviousNodeElement( void )
{
	return ((pNodeElement)prev());
}


CqlConstants::CompareResult NodeElement::Compare( NodeElement& other, AbstractSegmentDescriptorList& segments, bool compareRecordPosition, UNI segmentsToCompare )
{
	pAbstractSegmentDescriptor seg;
	pUC key1 = bufferBase();
	pUC key2 = other.bufferBase();
	CompareResult compareResult;

	UNI segsCompared;
	for( seg = segments.first(), segsCompared = 0; seg; seg = segments.next(), segsCompared++ )
	{
		if( segmentsToCompare && segsCompared == segmentsToCompare )
			break;

		ColumnDescriptor& col = dynamic_cast< ColumnDescriptor& >( *seg->column() );
		if( seg->segmentType() == SegmentTypes::CQL_DESCENDING )
			compareResult = col.compare( key1, key2, true );
		else
			compareResult = col.compare( key1, key2, false );
		if( compareResult != THIS_EQUAL_TO_OTHER )
			return compareResult;
	}

	//  they are equal

	if( !compareRecordPosition )
		return THIS_EQUAL_TO_OTHER;
	else if( son == other.son )
		return THIS_EQUAL_TO_OTHER;
	else if( son < other.son )
		return THIS_LESS_THAN_OTHER;
	else
		return THIS_GREATER_THAN_OTHER;
}


void NodeElement::Dump( void )
{
	NC tbuf[ 4096 ];
	UL length = size();
	std::cout << "Length:  " << length << "   Son:  " << son << "   Key:  ";
	memcpy( tbuf, bufferBase(), ((UNI)length) );
	tbuf[ length ] = 0;
	std::cout << tbuf << std::endl;;
}


US NodeElement::SpaceNeeded( void )
{
#ifdef __WATCOMC__
	return static_cast< US >( size() + sizeof( son ) + sizeof( entries ) + sizeof( UL ) );
#else
	return static_cast< US >( size() + sizeof( son ) + sizeof( entries ) + sizeof( size() ) );
#endif
}
