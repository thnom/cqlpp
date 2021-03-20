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


#ifndef __ListElement_h
#define __ListElement_h


template<class ItemType, class ListType>
class ListElement
{
	ListType *list_;        //  the list this element is part of
	ItemType *next_;
	ItemType *prev_;

public :

	ListElement( void );
	virtual ~ListElement( void );

	ListType *list( void ) { return list_; }
	void list( ListType *l ) { list_ = l; }
	ItemType *next( void ) { return next_; }
	void next( ItemType *it ) { next_ = it; }
	NI position( void );
	ItemType *prev( void ) { return prev_; }
	void prev( ItemType *it ) { prev_ = it; }
};


template<class ItemType, class ListType>
ListElement<ItemType,ListType>::ListElement( void )
:
list_( 0 ),
next_( 0 ),
prev_( 0 )
{
}


template<class ItemType, class ListType>
ListElement<ItemType,ListType>::~ListElement( void )
{
}


template<class ItemType, class ListType>
NI ListElement<ItemType, ListType>::position( void )
{
	ItemType *el;
	UNI loop;

	for( el = list_->first(), loop = 0; el; el = list_->next(), loop++ )
		if( el == this )
			return loop;

	//  if we get here, we have a bad list.
	//***************************  throw exception
	return -1;
}


#endif  //  __ListElement_h
