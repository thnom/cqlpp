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


BufferSpaceIndex::BufferSpaceIndex( void ) : MemoryIndex(), active_( false )
{
}


BufferSpaceIndex::~BufferSpaceIndex( void )
{
}


BufferSpaceIndex& BufferSpaceIndex::operator = ( const BufferSpaceIndex& cother )
{
	BufferSpaceIndex& other = const_cast< BufferSpaceIndex& >( cother );
	*(static_cast< MemoryIndex* >( this ) ) = other;
	active_ = other.active_;
	return *this;
}


BufferSpaceIndexNode *BufferSpaceIndex::currentNode( void )
{
	return reinterpret_cast< BufferSpaceIndexNode* >( MemoryIndex::currentNode() );
}


bool BufferSpaceIndex::findLessThanKey( US fileNumber, UL pageNumber )
{
	MemoryIndexNode *tempNode;

	tempNode = new BufferSpaceIndexNode( fileNumber, pageNumber, 0 );
	if( !tempNode )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	NI returnCode = MemoryIndex::findLessThanKey( tempNode );
	delete tempNode;
	if( returnCode )
		return true;
	else
		return false;
}


bool BufferSpaceIndex::findGreaterOrEqualKey( US fileNumber, UL pageNumber )
{
	MemoryIndexNode *tempNode;

	tempNode= new BufferSpaceIndexNode( fileNumber, pageNumber, 0 );
	if( !tempNode )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	NI returnCode = MemoryIndex::findGreaterOrEqualKey( tempNode );
	delete tempNode;
	if( returnCode )
		return true;
	else
		return false;
}


BaseBufferPage *BufferSpaceIndex::firstNode( void )
{
	NI rc;

	rc = MemoryIndex::firstNode();
	if( rc != CQL_SUCCESS )
		return 0;

	return( getCurrentPage() );
}


BaseBufferPage *BufferSpaceIndex::nextNode( void )
{
	NI rc;

	rc = MemoryIndex::nextNode();
	if( rc != CQL_SUCCESS )
		return 0;

	return( getCurrentPage() );
}


void BufferSpaceIndex::addIndexNode( US fileNumber, UL pageNumber, BaseBufferPage *basePage )
{
	MemoryIndexNode *newNode;

	active_ = true;
	newNode = new BufferSpaceIndexNode( fileNumber, pageNumber, basePage );
	if( !newNode )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	if( MemoryIndex::addIndexNode( newNode ) == CQL_FAILURE )
		throw MemoryIndexException( __FILE__, __LINE__ );
}


BaseBufferPage *BufferSpaceIndex::getCurrentPage( void )
{
	BufferSpaceIndexNode *node = currentNode();
	return node->basePage();
}


bool BufferSpaceIndex::findEqualKey( US fileNumber, UL pageNumber )
{
	MemoryIndexNode *tempNode;

	tempNode = new BufferSpaceIndexNode( fileNumber, pageNumber );
	if( !tempNode )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	NI returnCode = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	switch( returnCode )
	{
	case CQL_NOT_FOUND :
		return false;

	case CQL_SUCCESS :
		break;

	default :
		throw MemoryIndexException( __FILE__, __LINE__ );
	}

	return true;
}


BufferSpaceIndexNode::BufferSpaceIndexNode( US fn, UL pn, BaseBufferPage *bp ) : basePage_( bp ), fileNumber_( fn ), pageNumber_( pn )
{
}


BufferSpaceIndexNode::~BufferSpaceIndexNode( void )
{
	if( basePage_ )
	{
		delete basePage_;
		basePage_ = 0;
	}
}


void BufferSpaceIndexNode::releaseMemory( void )
{
}


CqlConstants::CompareResult BufferSpaceIndexNode::compareKeys( MemoryIndexNode *node2 )
{
	BufferSpaceIndexNode *tnode = reinterpret_cast< BufferSpaceIndexNode* >( node2 );
	if( fileNumber_ < tnode->fileNumber_ )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( fileNumber_ > tnode->fileNumber_ )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else if( pageNumber_ < tnode->pageNumber_ )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( pageNumber_ > tnode->pageNumber_ )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


NI DeadlockGraphIndex::AddIndexNode( ErrorManager& em, UL usr, UL waitFor, pDeadlockGraphIndexNode *newNode )
{
	pMemoryIndexNode nNode;

	nNode = new DeadlockGraphIndexNode( usr, waitFor );
	if( !nNode )
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );

	if( MemoryIndex::addIndexNode( nNode ) == CQL_FAILURE )
	{
		delete nNode;
		return CQL_FAILURE;
	}

	if( !newNode )
		return CQL_SUCCESS;

	if( FindEqualKey( em, usr, waitFor ) == CQL_FAILURE )
		return CQL_FAILURE;

	*newNode = CurrentNode();
	return CQL_SUCCESS;
}


NI DeadlockGraphIndex::WaitingFor( ErrorManager& em, UL waitor, UL waitee )
{
	NI rc;

	if( FindEqualKey( em, waitor, waitee ) == CQL_SUCCESS )
		return CQL_YES;

	//  waitor is not explicitly waiting for waitee.
	//  Is there a chain via which waitor is waiting for waitee?  (Say what?)
	for( rc = WaitorFirst( waitor ); rc == CQL_SUCCESS; rc = WaitorNext( waitor ) )
	{
		if( WaitingFor( em, CurrentNode()->WaitingFor(), waitee ) == CQL_YES )
			return CQL_YES;
	}

	return CQL_NO;
}


pDeadlockGraphIndexNode DeadlockGraphIndex::CurrentNode( void )
{
	return ((pDeadlockGraphIndexNode)MemoryIndex::currentNode());
}


DeadlockGraphIndex::DeadlockGraphIndex( void ) : MemoryIndex()
{
}


DeadlockGraphIndex::~DeadlockGraphIndex( void )
{
}


NI DeadlockGraphIndex::FindEqualKey( ErrorManager& em, UL usr, UL waitFor )
{
	NI rc;
	pMemoryIndexNode tempNode;

	tempNode = new DeadlockGraphIndexNode( usr, waitFor );
	if( !tempNode )
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );

	rc = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return rc;
}


NI DeadlockGraphIndex::WaitorFirst( UL waitor )
{
	DeadlockGraphIndexNode tnode( waitor, 0 );

	return findGreaterOrEqualKey( &tnode );
}


NI DeadlockGraphIndex::WaitorNext( UL waitor )
{
	if( nextNode() == CQL_NOT_FOUND )
		return CQL_NOT_FOUND;

	if( CurrentNode()->User() != waitor )
		return CQL_NOT_FOUND;

	return CQL_SUCCESS;
}


DeadlockGraphIndexNode::DeadlockGraphIndexNode( UL usr, UL waitFor ) : MemoryIndexNode(), user( usr ), waitingFor( waitFor )
{
}


DeadlockGraphIndexNode::~DeadlockGraphIndexNode( void )
{
}


CqlConstants::CompareResult DeadlockGraphIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pDeadlockGraphIndexNode tnode = ((pDeadlockGraphIndexNode)node2);

	if( user < tnode->user )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( user > tnode->user )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else if( waitingFor < tnode->waitingFor )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( waitingFor > tnode->waitingFor )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


void DeadlockGraphIndexNode::releaseMemory( void )
{
}


FilenameIndex::FilenameIndex( void ) : MemoryIndex()
{
}


FilenameIndex::~FilenameIndex( void )
{
}


NI FilenameIndex::AddIndexNode( ErrorManager&, CqlString& name, pFileManager fmgr )
{
	pFilenameIndexNode newNode;

	newNode = new FilenameIndexNode( name, fmgr );
	return MemoryIndex::addIndexNode( newNode );
}


NI FilenameIndex::FindEqualKey( ErrorManager& em, CqlString& name )
{
	NI rc;
	pFilenameIndexNode tempNode;

	tempNode = new FilenameIndexNode( name );
	if( !tempNode )
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );

	rc = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return rc;
}


FilenameIndexNode::FilenameIndexNode( CqlString& nm, pFileManager fmgr ) : name( nm ), fileMgr( fmgr )
{
}


FilenameIndexNode::~FilenameIndexNode( void )
{
	name.reset();
	if( fileMgr )
	{
		delete fileMgr;
		fileMgr = 0;
	}
}


CqlConstants::CompareResult FilenameIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pFilenameIndexNode tnode = ((pFilenameIndexNode)node2);

	return name.stringCompare( tnode->name );
}


pFilenameIndexNode FilenameIndex::CurrentNode( void )
{
	return ((pFilenameIndexNode)MemoryIndex::currentNode());
}


void FilenameIndexNode::releaseMemory( void )
{
	name.reset();
}


IndexIndex::IndexIndex( void ) : MemoryIndex()
{
}


IndexIndex::~IndexIndex( void )
{
}


pIndexIndexNode IndexIndex::CurrentNode( void )
{
	return ((pIndexIndexNode)MemoryIndex::currentNode());
}


NI IndexIndex::FindEqualKey( ErrorManager& em, pIndex index )
{
	NI rc;
	pMemoryIndexNode tempNode;

	tempNode = new IndexIndexNode( index );
	if( !tempNode )
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );

	rc = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return rc;
}


//
//  if item is already in the index, return success
//
NI IndexIndex::AddIndexNode( ErrorManager& em, pIndex index )
{
	pMemoryIndexNode newNode;

	if( FindEqualKey( em, index ) == CQL_SUCCESS )
		return CQL_SUCCESS;

	newNode = new IndexIndexNode( index );
	index->IncrementTransactionCounter();
	return MemoryIndex::addIndexNode( newNode );
}


NI IndexIndex::DeleteEntryForIndex( ErrorManager& em, pIndex index )
{
	if( FindEqualKey( em, index ) == CQL_SUCCESS )
		if( deleteIndexNode() == CQL_FAILURE )
			return CQL_FAILURE;

	return CQL_SUCCESS;
}


IndexIndexNode::IndexIndexNode( pIndex index ) : openIndex( index )
{
}


IndexIndexNode::~IndexIndexNode( void )
{
}


void IndexIndexNode::releaseMemory( void )
{
}


CqlConstants::CompareResult IndexIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pIndexIndexNode tnode = ((pIndexIndexNode)node2);
	void *p1, *p2;

	p1 = ((void*)openIndex);
	p2 = ((void*)tnode->openIndex);

	if( p1 < p2 )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( p1 > p2 )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


IsamIndex::IsamIndex( void ) : MemoryIndex()
{
}


IsamIndex::~IsamIndex( void )
{
}


pIsamIndexNode IsamIndex::CurrentNode( void )
{
	return ((pIsamIndexNode)MemoryIndex::currentNode());
}


NI IsamIndex::AddIndexNode( ErrorManager& em, pAbstractTable file )
{
	pMemoryIndexNode newNode;

	if( FindEqualKey( em, file ) == CQL_SUCCESS )
		return CQL_SUCCESS;

	newNode = new IsamIndexNode( file );
	((pIsamFile)file)->incrementTransactionCounter();
	return MemoryIndex::addIndexNode( newNode );
}


NI IsamIndex::FindEqualKey( ErrorManager& em, pAbstractTable file )
{
	NI rc;
	pMemoryIndexNode tempNode;

	tempNode = new IsamIndexNode( file );
	if( !tempNode )
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );

	rc = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return rc;
}


NI IsamIndex::DeleteEntryForIsamFile( ErrorManager& em, pAbstractTable isamFile )
{
	if( FindEqualKey( em, isamFile ) == CQL_SUCCESS )
		if( deleteIndexNode() == CQL_FAILURE )
			return CQL_FAILURE;

	return CQL_SUCCESS;
}


IsamIndexNode::IsamIndexNode( pAbstractTable file ) : openIsam( file )
{
}


IsamIndexNode::~IsamIndexNode( void )
{
}


void IsamIndexNode::releaseMemory( void )
{
}


CqlConstants::CompareResult IsamIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pIsamIndexNode tnode = ((pIsamIndexNode) node2 );
	void *p1;
	void *p2;

	p1 = ((void*)openIsam);
	p2 = ((void*)tnode->openIsam);
	if( p1 < p2)
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( p1 > p2 )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


LockIndex::LockIndex( void ) : MemoryIndex()
{
}


LockIndex::~LockIndex( void )
{
}


pLockIndexNode LockIndex::CurrentNode( void )
{
	return ((pLockIndexNode)MemoryIndex::currentNode());
}


LockIndexNode::LockIndexNode( UL usr ) : user( usr ), readLock( CQL_YES ), writeLock( CQL_NO )
{
}


LockIndexNode::~LockIndexNode( void )
{
}


void LockIndexNode::releaseMemory( void )
{
}


void LockIndexNode::PromoteLock( void )
{
	readLock = CQL_NO;
	writeLock = CQL_YES;
}


CqlConstants::CompareResult LockIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pLockIndexNode tnode = ((pLockIndexNode)node2);

	if( user < tnode->user )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( user > tnode->user )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


NI NodeIndex::AddIndexNode( DatabaseHandle&, RECID loc, pNode node )
{
	pMemoryIndexNode newNode;
	
	newNode = new NodeIndexNode( loc, node );
	return MemoryIndex::addIndexNode( newNode );
}


NI NodeIndex::FindEqualKey( DatabaseHandle& dbHandle, RECID loc )
{
	NI rc;
	pMemoryIndexNode tempNode;
	
	tempNode = new NodeIndexNode( loc );
	if( !tempNode )
		return dbHandle.returnError( ErrorManager::ALLOCATION, __FILE__, __LINE__ );
	
	rc = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return rc;
}


NodeIndex::NodeIndex( void ) : MemoryIndex()
{
}


NodeIndex::~NodeIndex( void )
{
}


pNodeIndexNode NodeIndex::CurrentNode( void )
{
	return ((pNodeIndexNode)MemoryIndex::currentNode());
}


NodeIndexNode::NodeIndexNode( RECID loc, pNode node ) : MemoryIndexNode(), location( loc ), cachedNode( node )
{
}


NodeIndexNode::~NodeIndexNode( void )
{
	if( cachedNode )
	{
		delete cachedNode;
		cachedNode = ((pNode)0);
	}
}


CqlConstants::CompareResult NodeIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pNodeIndexNode tnode = ((pNodeIndexNode)node2);
	
	if( location < tnode->location )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( location > tnode->location )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


void NodeIndexNode::releaseMemory( void )
{
}


NI RecordIndex::AddIndexNode( DatabaseHandle&, RECID loc, pRecord record )
{
	pRecordIndexNode newNode;

	newNode = new RecordIndexNode( loc, record );
	return MemoryIndex::addIndexNode( newNode );
}


NI RecordIndex::FindEqualKey( DatabaseHandle& dbHandle, RECID loc )
{
	NI rc;
	pMemoryIndexNode tempNode;

	tempNode = new RecordIndexNode( loc );
	if( !tempNode )
		return dbHandle.returnError( ErrorManager::ALLOCATION, __FILE__, __LINE__ );

	rc = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return rc;
}


RecordIndex::RecordIndex( void ) : MemoryIndex()
{
}


RecordIndex::~RecordIndex( void )
{
}


pRecordIndexNode RecordIndex::CurrentNode( void )
{
	return ((pRecordIndexNode)MemoryIndex::currentNode());
}


CqlConstants::CompareResult RecordIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pRecordIndexNode tnode = ((pRecordIndexNode)node2);

	if( location < tnode->location )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( location > tnode->location )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


RecordIndexNode::RecordIndexNode( RECID loc, pRecord record ) : location( loc ), cachedRecord( record )
{
}


RecordIndexNode::~RecordIndexNode( void )
{
	if( cachedRecord )
	{
		delete cachedRecord;
		cachedRecord = ((pRecord)0);
	}
}


void RecordIndexNode::releaseMemory( void )
{
}


TransactionPageIndex::TransactionPageIndex( void ) : MemoryIndex()
{
}


TransactionPageIndex::~TransactionPageIndex( void )
{
}


pTransactionPageIndexNode TransactionPageIndex::CurrentNode( void )
{
	return ((pTransactionPageIndexNode)MemoryIndex::currentNode());
}


NI TransactionPageIndex::DeleteEntriesForFile( ErrorManager& em, US fileNo )
{
	pTransactionPageIndexNode tempNode, tnode2;

	tempNode = new TransactionPageIndexNode( fileNo, 0 );
	if( !tempNode )
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );

	while( ( MemoryIndex::findGreaterOrEqualKey( tempNode ) ) == CQL_SUCCESS )
	{
		tnode2 = CurrentNode();
		if( tnode2->FileNumber() != fileNo )
		{
			delete tempNode;
			return CQL_SUCCESS;
		}
		
		if( deleteIndexNode() == CQL_FAILURE )
		{
			delete tempNode;
			return CQL_FAILURE;
		}
	}

	delete tempNode;
	return CQL_SUCCESS;
}


NI TransactionPageIndex::AddIndexNode( ErrorManager&, US fileNo, UL pageNo, pFileManager fmgr, BaseBufferPage *bPage )
{
	pMemoryIndexNode newNode;

	newNode = new TransactionPageIndexNode( fileNo, pageNo, fmgr, bPage );
	return MemoryIndex::addIndexNode( newNode );
}


NI TransactionPageIndex::FindEqualKey( US fileNo, UL pageNo )
{
	static TransactionPageIndexNode tempNode;

	tempNode.Setup( fileNo, pageNo );
	return MemoryIndex::findEqualKey( &tempNode );
}


void TransactionPageIndexNode::Setup( US fileNo, UL pageNo )
{
	*fileNumber = fileNo;
	*pageNumber = pageNo;
}


TransactionPageIndexNode::TransactionPageIndexNode( void )
	: basePage( 0 ),
	  fileMgr( ((pFileManager)0) ),
	  fileNumber( ((pUL)keyBuffer) ),
	  pageNumber( ((pUL)( keyBuffer + sizeof( *fileNumber ) ) ) )
{
	memset( keyBuffer, 0, sizeof( keyBuffer ) );
}


TransactionPageIndexNode::TransactionPageIndexNode( UL fileNo, UL pageNo, pFileManager fmgr, BaseBufferPage *bPage )
	: MemoryIndexNode(),
	  basePage( bPage ),
	  fileMgr( fmgr ),
	  fileNumber( ((pUL)keyBuffer) ),
	  pageNumber( ((pUL)( keyBuffer + sizeof( *fileNumber ) ) ) )
{
	memcpy( fileNumber, &fileNo, sizeof( *fileNumber ) );
	memcpy( pageNumber, &pageNo, sizeof( *pageNumber ) );
}


TransactionPageIndexNode::~TransactionPageIndexNode( void )
{
}


void TransactionPageIndexNode::releaseMemory( void )
{
}


CqlConstants::CompareResult TransactionPageIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pTransactionPageIndexNode tnode = ((pTransactionPageIndexNode)node2);
	NI i = memcmp( keyBuffer, tnode->keyBuffer, sizeof( keyBuffer ) );
	if( i < 0 )
		return CqlConstants::THIS_LESS_THAN_OTHER;
	else if( i > 0 )
		return CqlConstants::THIS_GREATER_THAN_OTHER;
	else
		return CqlConstants::THIS_EQUAL_TO_OTHER;
}


pWaiteeIndexNode WaiteeIndex::CurrentNode( void )
{
	return ((pWaiteeIndexNode)MemoryIndex::currentNode());
}


NI WaiteeIndex::AddIndexNode( ErrorManager& em, pDeadlockGraphIndexNode deadNode, UL usr, UL waitFor )
{
	pMemoryIndexNode nNode;

	nNode = new WaiteeIndexNode( deadNode, usr, waitFor );
	if( !nNode )
		return em.returnError( ALLOCATION, __FILE__, __LINE__ );

	if( MemoryIndex::addIndexNode( nNode ) == CQL_FAILURE )
	{
		delete nNode;
		return CQL_FAILURE;
	}

	return CQL_SUCCESS;
}


WaiteeIndex::WaiteeIndex( void ) : DeadlockGraphIndex()
{
}


WaiteeIndex::~WaiteeIndex( void )
{
}


pDeadlockGraphIndexNode WaiteeIndexNode::DeadlockIndexNode( void )
{
	return deadlockIndexNode;
}


WaiteeIndexNode::WaiteeIndexNode( pDeadlockGraphIndexNode deadNode, UL usr, UL waitFor ) : DeadlockGraphIndexNode( usr, waitFor ), deadlockIndexNode( deadNode )
{
}


WaiteeIndexNode::~WaiteeIndexNode( void )
{
}
