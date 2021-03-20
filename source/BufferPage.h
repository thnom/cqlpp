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


#ifndef __BufferPage_h
#define __BufferPage_h


class BufferPage;
typedef List< BufferPage > BufferPageListBase;
typedef ListElement< BufferPage, BufferPageListBase > BufferPageListElement;


class BufferPage : public BufferPageListElement, public LockIndex
{
	bool added_;
	UC *base_;
	NC fileName_[ CQL_MAXIMUM_FILE_NAME_LENGTH ];
	RECID filePosition_;
	bool freeable_;
	bool marked_;
	bool onDisk_;
	UL pageNumber_;
	UL *revision_;
	UC *space_;
	UL transactionNumber_;
	bool uncommitted_;
	UL user_;
	RECID virtualFilePosition_;

public :

	BufferPage( void );
	~BufferPage( void );

	bool added( void ) { return added_; }
	UC *base( void ) { return base_; }
	void clearAdded( void ) { added_ = false; }
	void clearFreeable( void ) { freeable_ = false; }
	void clearMarked( void ) { marked_ = false; }
	void clearOnDisk( void ) { onDisk_ = false; }
	void clearUncommitted( void ) { uncommitted_ = false; }
	const char * const fileName( void ) { return fileName_; }
	void fileName( const char * const name );
	RECID filePosition( void ) { return filePosition_; }
	bool freeable( void ) { return freeable_; }
	void incrementRevision( void ) { revision_++; }
	bool marked( void ) { return marked_; }
	bool onDisk( void ) { return onDisk_; }
	UL pageNumber( void ) { return pageNumber_; }
	void pageNumber( UL pno ) { pageNumber_ = pno; }
	void setAdded( void ) { added_ = true; }
	void setFreeable( void ) { freeable_ = true; }
	void setMarked( void ) { marked_ = true; }
	void setOnDisk( void ) { onDisk_ = true; }
	void setUncommitted( void ) { uncommitted_ = true; }
	void setup( UC * );
	UC *space( void ) { return space_; }
	UL transactionNumber( void ) { return transactionNumber_; }
	void transactionNumber( UL no ) { transactionNumber_ = no; }
	bool uncommitted( void ) { return uncommitted_; }
	UL user( void ) { return user_; }
	void user( UL usr ) { user_ = usr; }
	RECID virtualFilePosition( void ) { return virtualFilePosition_; }
	void virtualFilePosition( RECID pos ) { virtualFilePosition_ = pos; }
};


#endif  //  __BufferPage_h
