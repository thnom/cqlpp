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


#ifndef __BufferManager_h
#define __BufferManager_h


class BufferManager
{
	BufferPageList activeBufferList_;
	BufferPage *bufferPages_;
	bool bufferSizeChangeProhibited_;
	pUC bufferSpace_;
	BufferPageList committedBufferList_;
	BufferPageList diskBufferList_;
	US fileNumberCounter_;
	BufferPageList inactiveBufferList_;
	UL maximumBufferPages_;
	BufferPageList uncommittedBufferList_;
	RECID virtualEndPosition_;
	VirtualSlotList virtualFileSlots_;
	ClibFileManager virtualSwapFile_;


public :

	BufferManager( const CqlString& /*initial directory*/ );
	virtual ~BufferManager( void );

	void addToInactiveBufferList( BufferPage* );
	void allocateBuffers( UL );
	void changeNumberOfCacheBuffers( UL /*  number of buffers  */ );
	void bringPageIntoMemory( BufferPage* );
	virtual void cleanup( void );
	void displayUnmarkedActiveBuffers( void );
	void initialize( void );
	UC *getDataPointer( BaseBufferPage *page, UNI offset );
	UNI getFileNumber( void ) { return fileNumberCounter_++; }
	BufferPage *getNewPage( void );
	void lockPage( UL, BaseBufferPage*, UL, const char * const );
	void markActiveBuffers( void );
	void releasePage( BaseBufferPage* );
	void retrieveVirtualBuffer( BufferPage *page );
	void swapLeastRecentlyUsedBuffer( BufferPage *page );
};


#endif  //  __BufferManager_h
