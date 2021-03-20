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


BaseBufferPage::BaseBufferPage( const BufferPage *p ) : page_( const_cast< BufferPage* >( p ) ), transactionPages_()
{
}


BaseBufferPage::~BaseBufferPage( void )
{
}


void BaseBufferPage::rollback( void )
{
	PageChainList& pageList = transactionPages_;
	pPageChainElement lastChain;

	lastChain = pageList.last();
	if( !lastChain )
	{
		if( !page_->added() )
			throw TransactionException( __FILE__, __LINE__ );
		else
			return;
	}

	pageList.DeleteLastElement();
}


BaseBufferPage& BaseBufferPage::operator = ( const BaseBufferPage& other )
{
	page_ = other.page_;
	transactionPages_ = other.transactionPages_;
	return *this;
}


BufferManager::BufferManager( const CqlString& initialDir )
	:	activeBufferList_(),
		bufferPages_( 0 ),
		bufferSizeChangeProhibited_( false ),
		bufferSpace_( 0 ),
		committedBufferList_(),
		diskBufferList_(),
		fileNumberCounter_( 0 ),
		inactiveBufferList_(),
		maximumBufferPages_( 0 ),
		uncommittedBufferList_(),
		virtualEndPosition_( 0 ),
		virtualFileSlots_(),
		virtualSwapFile_()
{
	CqlString fname;
	if( initialDir.length() )
	{
		fname = initialDir;
		fname += "/";
	}
	fname += CQL_VIRTUAL_FILE_NAME;
	virtualSwapFile_.openOrCreate( fname );

	//  This needs to be changable according by entry in configuratio file
	allocateBuffers( CQL_MAXIMUM_BUFFER_PAGES );
}


BufferManager::~BufferManager( void )
{
	virtualFileSlots_.destroy();
	committedBufferList_.destroy();
	diskBufferList_.destroy();
	activeBufferList_.destroy();
	inactiveBufferList_.destroy();
	uncommittedBufferList_.destroy();

	if( bufferPages_ )
	{
		delete [] bufferPages_;
		bufferPages_ = 0;
	}

	if( bufferSpace_ )
	{
		delete [] bufferSpace_;
		bufferSpace_ = ((pUC)0);
	}
}


void BufferManager::allocateBuffers( UL maxPages )
{
	UL loop;
	BufferPage *bufferPage;
	pUC spacePosition;

	maximumBufferPages_ = maxPages;
	bufferPages_ = 0;
	bufferSpace_ = 0;

	try
	{
		bufferPages_ = new BufferPage[ maxPages ];
		size_t spaceSize = maxPages * CQL_PAGE_SIZE;
		bufferSpace_ = new UC[ spaceSize ];
		memset( bufferSpace_, 0, spaceSize );
	}
	catch( ... )
	{
		if( bufferPages_ )
		{
			delete bufferPages_;
			bufferPages_ =  0;
		}
		if( bufferSpace_ )
		{
			delete bufferSpace_;
			bufferSpace_ = 0;
		}

		throw;
	}

	memset( bufferSpace_, 0, ((UNI)( maxPages * CQL_PAGE_SIZE ) ) );

	for( loop = 0, bufferPage = bufferPages_, spacePosition = bufferSpace_;
		 loop < maximumBufferPages_;
		 loop++, bufferPage++, spacePosition += CQL_PAGE_SIZE )
	{
		bufferPage->setup( spacePosition );
		inactiveBufferList_.add( bufferPage );
	}
}


void BufferManager::markActiveBuffers( void )
{
	activeBufferList_.markBuffers();
	diskBufferList_.markBuffers();
}


void BufferManager::displayUnmarkedActiveBuffers( void )
{
	activeBufferList_.displayUnmarkedBuffers();
	diskBufferList_.displayUnmarkedBuffers();
}


void BufferManager::cleanup( void )
{
	virtualSwapFile_.close();
}


UC *BufferManager::getDataPointer( BaseBufferPage *basePage, UNI bufferOffset )
{
	BufferPage *endPage;
	pPageChainElement lastChain;

	lastChain = basePage->transactionPages().last();
	if( lastChain )
		endPage = lastChain->Page();
	else
		endPage = basePage->page();

	bringPageIntoMemory( endPage );
	return endPage->space() + bufferOffset;
}


void BufferManager::lockPage( UL usr, BaseBufferPage *basePage, UL transactionNo, const char * const fileName )
{
	BufferPage *page, *lastPage, *newPage;
	pPageChainElement lastChain, newChain;

	page = basePage->page();
	lastChain = basePage->transactionPages().last();
	if( lastChain )
		lastPage = lastChain->Page();
	else
		lastPage = page;

	if( page && page->uncommitted() && page->transactionNumber() == transactionNo )
		return;

	if( lastPage->uncommitted() && lastPage->user() != usr )
		throw ConcurrencyException( __FILE__, __LINE__ );

	newPage = getNewPage();

	newPage->pageNumber( page->pageNumber() );
	newPage->fileName( fileName );

	newChain = new PageChainElement( newPage );
	if( !newChain )
	{
		if( bufferDebugging == CQL_YES )
				assert( 0 );

		newPage->list()->remove( newPage );
		inactiveBufferList_.add( newPage );
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	newPage->user( usr );
	newPage->transactionNumber( transactionNo );
	lastPage->setUncommitted();

	memcpy( newPage->base(), lastPage->base(), CQL_PAGE_SIZE );
	newPage->incrementRevision();
	basePage->transactionPages().add( newChain );

	if( newPage->list() )
	{
		if( bufferDebugging == CQL_YES )
			fprintf( stderr, "%s, %d, deleting %lx from its list (active or uncommitted)\n", __FILE__, __LINE__, ((UL)newPage) );

		newPage->list()->remove( newPage );
		newPage->clearOnDisk();
	}

	if( bufferDebugging == CQL_YES )
	{
		fprintf( stderr, "%s, %d, adding %lx to uncommittedBufferList_\n", __FILE__, __LINE__, ((UL)newPage) );

		if( newPage->onDisk() )
			*((NC*)0) = 0;
	}

	uncommittedBufferList_.add( newPage );
}


void BufferManager::bringPageIntoMemory( BufferPage *page )
{
	BufferPage *availablePage;

	if( page->onDisk() )
	{
		//
		//  if inactive list is not empty, use available buffer
		//
		availablePage = inactiveBufferList_.first();
		if( availablePage )
		{
			inactiveBufferList_.remove( availablePage );
			page->setup( availablePage->base() );
			if( availablePage->freeable() )
				delete availablePage;
		}
		else
			swapLeastRecentlyUsedBuffer( page );

		retrieveVirtualBuffer( page );
		page->list()->moveToEnd( page );
	}
}


void BufferManager::releasePage( BaseBufferPage *basePage )
{
	NI lastCqlTime;
	pVirtualSlot vslot, vslot2;
	BufferPage *page, *lastPage;
	PageChainList& pageList = basePage->transactionPages();
	pPageChainElement lastChain;

	for( lastCqlTime = CQL_NO; lastCqlTime == CQL_NO; )
	{
		page = basePage->page();
		lastChain = pageList.last();
		if( lastChain )
		{
			lastPage = lastChain->Page();
			pageList.DeleteLastElement();
		}
		else
		{
			lastCqlTime = CQL_YES;
			lastPage = page;
		}

		if( bufferDebugging == CQL_YES )
			fprintf( stderr, "%s, %d, releasing page %lx\n", __FILE__, __LINE__, ((UL)lastPage) );

		if( lastPage->onDisk() )
		{
			if( bufferDebugging == CQL_YES )
				fprintf( stderr,
						 "%s, %d, page %lx is on disk, deleting from diskBufferList_, not adding to list\n",
						 __FILE__,
						 __LINE__,
						 ((UL)lastPage) );

			diskBufferList_.remove( lastPage );
			vslot = new VirtualSlot( lastPage->virtualFilePosition() );
			if( !vslot )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			if( lastPage->freeable() == CQL_YES )
				delete lastPage;

			if( bufferDebugging )
				for( vslot2 = virtualFileSlots_.first(); vslot2; vslot2 = virtualFileSlots_.next() )
					if( vslot2->FilePosition() == vslot->FilePosition() )
						assert( 0 );

			if( bufferDebugging == CQL_YES )
				fprintf( stderr, "%s, %d, added virtualSlot %lx to virtualFileSlots_\n", __FILE__, __LINE__, ((UL)vslot) );

			virtualFileSlots_.add( vslot );
		}
		else
		{
			//  buffer is in memory
			if( lastPage->list() )
			{
				if( bufferDebugging == CQL_YES )
					fprintf( stderr, "%s, %d, deleting %lx from its list (active or uncommitted)\n", __FILE__, __LINE__, ((UL)lastPage) );

				lastPage->list()->remove( lastPage );
			}

			if( bufferDebugging == CQL_YES )
			{
				fprintf( stderr, "%s, %d, page is in memory, adding %lx to inactiveBufferList_\n", __FILE__, __LINE__, ((UL)lastPage) );

				if( lastPage->onDisk() )
					*((NC*)0) = 0;
			}

			inactiveBufferList_.add( lastPage );
		}
	}
}


BufferPage *BufferManager::getNewPage( void )
{
	BufferPage *lpage;

	if( bufferDebugging == CQL_YES )
		fprintf( stderr, "%s, %d, getting new page\n", __FILE__, __LINE__ );

	lpage = inactiveBufferList_.first();
	if( lpage )
	{
		if( bufferDebugging == CQL_YES )
		{
			fprintf( stderr, "%s, %d, moving page %lx from inactive to active list\n", __FILE__, __LINE__, ((UL)lpage) );
			if( lpage->onDisk() )
				assert( 0 );
		}

		inactiveBufferList_.remove( lpage );
		activeBufferList_.add( lpage );
	}
	else
	{
		lpage = new BufferPage;
		if( !lpage )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		lpage->setFreeable();

		if( bufferDebugging == CQL_YES )
			fprintf( stderr, "%s, %d, inactive list empty, allocating new page %lx\n", __FILE__, __LINE__, ((UL)lpage) );

		swapLeastRecentlyUsedBuffer( lpage );
		activeBufferList_.add( lpage );
	}

	lpage->setAdded();
	return lpage;
}


void BufferManager::retrieveVirtualBuffer( BufferPage *page )
{
	pVirtualSlot vslot;

	if( bufferDebugging == CQL_YES )
		fprintf( stderr, "%s, %d, reading buffer from virtual file @ %lx\n", __FILE__, __LINE__, page->virtualFilePosition() );

	vslot = new VirtualSlot( page->virtualFilePosition() );
	if( !vslot )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	if( bufferDebugging == CQL_YES )
		fprintf( stderr, "%s, %d, added virtualSlot %lx to virtualFileSlots_\n", __FILE__, __LINE__, ((UL)vslot) );

	virtualFileSlots_.add( vslot );

	virtualSwapFile_.inputSeek( page->virtualFilePosition() );
	virtualSwapFile_.read( ((void*)page->base()), CQL_PAGE_SIZE );
	page->clearOnDisk();

	if( bufferDebugging == CQL_YES )
		fprintf( stderr, "%s, %d, deleting %lx from diskPageList\n", __FILE__, __LINE__, ((UL)page) );

	diskBufferList_.remove( page );

	if( page->uncommitted() )
	{
		if( bufferDebugging == CQL_YES )
		{
			fprintf( stderr, "%s, %d, adding %lx to uncommittedBufferList_ in RetrieveVirtualBuffer\n", __FILE__, __LINE__, ((UL)page) );

			if( page->onDisk() )
				assert( 0 );
		}

		uncommittedBufferList_.add( page );
	}
	else
	{
		if( bufferDebugging == CQL_YES )
		{
			fprintf( stderr, "%s, %d, adding %lx to activeBufferList_ in RetrieveVirtualBuffer\n", __FILE__, __LINE__, ((UL)page) );

			if( page->onDisk() )
				*((NC*)0) = 0;
		}

		activeBufferList_.add( page );
	}
}


void BufferManager::swapLeastRecentlyUsedBuffer( BufferPage *page )
{
	BufferPage *leastRecentlyUsed, *diskPage;
	pVirtualSlot vslot;
	RECID virtualPosition;

	vslot = ((pVirtualSlot)virtualFileSlots_.first());
	if( vslot )
	{
		virtualPosition = vslot->FilePosition();

		if( bufferDebugging == CQL_YES )
			fprintf( stderr, "%s, %d, removing %lx from virtualFileSlots_\n", __FILE__, __LINE__, ((UL)vslot) );

		virtualFileSlots_.remove( vslot );
		delete vslot;
	}
	else
	{
		virtualPosition = virtualEndPosition_;
		virtualEndPosition_ += CQL_PAGE_SIZE;
	}
	leastRecentlyUsed = activeBufferList_.first();
	if( !leastRecentlyUsed )
	{
		if( bufferDebugging == CQL_YES )
			fprintf( stderr,
					 "%s, %d, active buffer list empty, getting leastRecentlyUsed from uncommittedBufferList_\n",
					 __FILE__,
					 __LINE__ );

		leastRecentlyUsed = uncommittedBufferList_.first();
		if( !leastRecentlyUsed )
		{
			if( bufferDebugging == CQL_YES )
			{
				//
				//  write list of buffers to the log
				//
				for( diskPage = diskBufferList_.first(); diskPage; diskPage = diskBufferList_.next() )
					*hAEnv << "Page Number:"
								 << diskPage->pageNumber()
								 << ", File Name:"
								 << diskPage->fileName()
								 << "\n";
			}

			throw MemoryAllocationException( __FILE__, __LINE__ );
		}
	}
	else
	{
		if( bufferDebugging == CQL_YES )
			fprintf( stderr, "%s, %d, leastRecentlyUsed taken from activeBufferList_\n", __FILE__, __LINE__ );
	}

	if( bufferDebugging == CQL_YES )
		fprintf( stderr, "%s, %d, deleting leastRecentlyUsed %lx from its list\n", __FILE__, __LINE__, ((UL)leastRecentlyUsed) );

	leastRecentlyUsed->list()->remove( leastRecentlyUsed );
	leastRecentlyUsed->setOnDisk();

	if( bufferDebugging == CQL_YES )
	{
		fprintf( stderr, "%s, %d, adding %lx to diskBufferList_\n", __FILE__, __LINE__, ((UL)leastRecentlyUsed) );

		if( !leastRecentlyUsed->onDisk() )
			*((NC*)0) = 0;
	}

	diskBufferList_.add( leastRecentlyUsed );
	leastRecentlyUsed->virtualFilePosition( virtualPosition );

	if( bufferDebugging == CQL_YES )
		fprintf( stderr, "%s, %d, writing buffer to virtual file @ %lx\n", __FILE__, __LINE__, virtualPosition );

	virtualSwapFile_.outputSeek( virtualPosition );
	virtualSwapFile_.write( ((void*)leastRecentlyUsed->base()), CQL_PAGE_SIZE );

	page->setup( leastRecentlyUsed->base() );
}


void BufferManager::addToInactiveBufferList( BufferPage *page )
{
	if( bufferDebugging == CQL_YES )
	{
		fprintf( stderr, "%s, %d, adding %lx to inactiveBufferList_\n", __FILE__, __LINE__, ((UL)page) );
		if( page->onDisk() )
			assert( 0 );
	}

	inactiveBufferList_.add( page );
}


void BufferManager::changeNumberOfCacheBuffers( UL numberOfBuffers )
{
	//
	//  If anything has used the buffers, prohibit change in size.
	//  This method is only available for one purpose.  That purpose is
	//  to change the number of buffers from the default CQL_MAXIMUM_BUFFER_PAGES
	//  to a value specified in the system configuration file.
	//
	if( bufferSizeChangeProhibited_ )
		throw BufferManagementException( __FILE__, __LINE__ );

	bufferSizeChangeProhibited_ = true;

	//  first, free everything allocated in the constructor
	delete [] bufferSpace_;
	delete [] bufferPages_;

	bufferPages_ = new BufferPage[ numberOfBuffers ];
	if( !bufferPages_ )
		throw BufferManagementException( __FILE__, __LINE__ );

	//  CQL_PAGE_SIZE needs to be replaced by configuration file
	//  value also.
	bufferSpace_ = new UC[ numberOfBuffers * CQL_PAGE_SIZE ];
	if( !bufferSpace_ )
		throw BufferManagementException( __FILE__, __LINE__ );

	memset( bufferSpace_, 0, static_cast< size_t >( numberOfBuffers * CQL_PAGE_SIZE ) );

	UNI loop;
	UC *spacePosition;
	BufferPage *bp;

	for( loop = 0, bp = bufferPages_, spacePosition = bufferSpace_; loop < maximumBufferPages_; loop++, bp++, spacePosition += CQL_PAGE_SIZE )
	{
		bp->setup( spacePosition );
		inactiveBufferList_.add( bp );
	}
}


BufferPage::BufferPage( void )
	:	added_( false ),
		base_( 0 ),
		filePosition_( 0 ),
		freeable_( false ),
		marked_( false ),
		onDisk_( false ),
		pageNumber_( 0 ),
		revision_( 0 ),
		space_( 0 ),
		transactionNumber_( 0 ),
		uncommitted_( false ),
		user_( 0 ),
		virtualFilePosition_( 0 )
{
	memset( fileName_, 0, sizeof( fileName_ ) );
}


BufferPage::~BufferPage( void )
{
}


void BufferPage::fileName( const char * const name )
{
	memset( fileName_, 0, sizeof( fileName_ ) );
	strcpy( fileName_, name );
}


void BufferPage::setup( UC *buffer )
{
	base_ = buffer;
	revision_ = reinterpret_cast< UL * >( buffer );
	buffer += sizeof( UL );
	space_ = buffer;
}


BufferPageList::BufferPageList( void ) : BufferPageListBase()
{
}


BufferPageList::~BufferPageList( void )
{
}


void BufferPageList::markBuffers( void )
{
	BufferPage *page;

	for( page = first(); page; page = next() )
		page->setMarked();
}


void BufferPageList::displayUnmarkedBuffers( void )
{
	BufferPage *page;

	for( page = first(); page; page = next() )
		if( !page->marked() )
			fprintf( stderr, "%s, %d, page %lx unmarked\n", __FILE__, __LINE__, ((UL)page) );
}


void BufferPageList::destroy( void )
{
	BufferPage *bp, *nextbp;

	for( bp = first(); bp; bp = nextbp )
	{
		nextbp = bp->next();
		if( bp->freeable() )
			delete bp;
	}

	emptyListBase();
}


PageChainElement::PageChainElement( BufferPage *p ) : PageChainElementListElement(), page( p )
{
}


PageChainElement::~PageChainElement( void )
{
}


void PageChainList::DeleteLastElement()
{
	pPageChainElement el;
	BufferPage *page;

	el = last();
	removeLast();
	page = el->Page();
	page->list()->remove( page );
	page->clearOnDisk();

	if( bufferDebugging == CQL_YES )
		if( page->onDisk() )
			*((NC*)0) = 0;

	dynamic_cast< EnvironmentHandle* >( hAEnv )->addToInactiveBufferList( page );
	delete el;
}


PageChainList::PageChainList( void )
{
}


PageChainList& PageChainList::operator = ( const PageChainList& cother )
{
	PageChainList& other = const_cast< PageChainList& >( cother );
	PageChainElement *pce, *newPce;

	for( pce = other.first(); pce; pce = other.next() )
	{
		newPce = new PageChainElement( pce->Page() );
		if( !newPce )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		//
		//  Constructor assigns the only element
		//
		add( newPce );
	}

	return *this;
}
