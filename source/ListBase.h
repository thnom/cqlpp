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


#ifndef __ListBase_h
#define __ListBase_h


//
//  ListType is typically ListBase< ItemType, ListType >.  In some cases, it is not
//  (e.g., the StackList).  Since "this" is always ListBase< ItemType, ListType >, we need
//  this base class to allow "item->list( ((ListType)this) )
//
template< class ItemType, class ListType >
class ListBase
{
	UL checkCount_;
	ItemType *current_;
	ItemType *first_;
	bool freeable_;
	ItemType *last_;
	UNI size_;

public :

	ListBase( bool /*freeable*/ );
	virtual ~ListBase( void );

	ItemType* operator[]( US );

	void add( ItemType* );
	void addAfter( ItemType*, ItemType* );
	void addBefore( ItemType*, ItemType* );
	void checkListBase( void );
	ItemType *current( void ) { return current_; }
	virtual void current( ItemType* t ) { current_ = t; }
	void destroy( void );
	void emptyListBase( void );
	void exchange( ItemType*, ItemType* );
	ItemType *first( void );
	NI isFirst( ItemType* );
	ItemType *last( void );
	void move( ListBase& destination );  //  moves entire list
	void moveToEnd( ItemType* );
	ItemType *next( void );
	ItemType *prev( void );
	void remove( ItemType* );
	void removeLast( void );
	void removeToBeginning( ItemType* );
	void removeToEnd( ItemType* );
	UNI size( void ) { return size_; }
	void transfer( ItemType* /*item*/, ListBase& /*destinationList*/ );
};


template< class ItemType, class ListType >
ListBase< ItemType, ListType >::ListBase( bool freeable )
:
checkCount_( 0 ),
current_( 0 ),
first_( 0 ),
freeable_( freeable ),
last_( 0 ),
size_( 0 )
{
}


template< class ItemType, class ListType >
ListBase< ItemType, ListType >::~ListBase( void )
{
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::add( ItemType *item )
{
	if( !first_ )
	{
		first_ = last_ = item;
		item->prev( 0 );
		item->next( 0 );
	}
	else
	{
		last_->next( item );
		item->prev( last_ );
		item->next( 0 );
		last_ = item;
	}

	item->list( ((ListType*)this) );
	current_ = item;
	size_++;

	if( listDebugging )
		checkListBase();
}


//  adds newItem after item
template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::addAfter( ItemType *item, ItemType *newItem )
{
	if( item->next() )
		item->next()->prev( newItem );
	newItem->next( item->next() );
	newItem->prev( item );
	item->next( newItem );
	if( !newItem->next() )
		last_ = newItem;
	newItem->list( ((ListType*)this) );
	size_++;

	if( listDebugging )
		checkListBase();
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::addBefore( ItemType *item, ItemType *newItem )
{
	if( item->prev() )
		item->prev()->next( newItem );
	newItem->prev( item->prev() );
	newItem->next( item );
	item->prev( newItem );
	if( !newItem->prev() )
		first_ = newItem;
	newItem->list( ((ListType*)this) );
	size_++;

	if( listDebugging )
		checkListBase();
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::checkListBase( void )
{
	ItemType *lcurrent;
	UNI lsize;
	ItemType *lnext;

	checkCount_++;
	if( !first_ )
	{
		assert( last_ == 0 );
		assert( size_ == 0 );
		return;
	}

	assert( first_->prev() == 0 );

	lcurrent = first_;
	lnext = lcurrent->next();

	if( !lnext )
	{
		assert( first_ == last_ );
		assert( size_ == 1 );
		assert( first_->list() == this );
		return;
	}

	lsize = 1;

	while( lnext )
	{
		lsize++;
		assert( lnext->prev() == lcurrent );
		assert( lcurrent->list() == this );
		lcurrent = lnext;
		lnext = lcurrent->next();
	}

	//  at end of list
	assert( lcurrent == last_ );
	assert( lsize == size_ );
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::remove( ItemType *item )
{
	if( listDebugging )
		assert( item->list() == this );

	if( item == first_ )
	{
		if( first_ == last_ )
			first_ = last_ = 0;
		else
		{
			first_ = first_->next();
			first_->prev( 0 );
		}
	}
	else if( item == last_ )
	{
		last_ = last_->prev();
		last_->next( 0 );
	}
	else
	{
		item->next()->prev( item->prev() );
		item->prev()->next( item->next() );
	}
	item->list( 0 );
	size_--;

	if( listDebugging )
		checkListBase();
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::removeToEnd( ItemType *item )
{
	if( item == first_ )
	{
		//  deleting entire list
		emptyListBase();
		return;
	}

	last_ = item->prev();
	last_->next( 0 );

	while( item )
	{
		item = item->next();
		size_--;
	}

	if( listDebugging )
		checkListBase();
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::removeToBeginning( ItemType *item )
{
	if( item == last_ )
	{
		emptyListBase();
		return;
	}

	first_ = item->next();
	first_->prev( 0 );

	while( item )
	{
		item = item->prev();
		size_--;
	}

	if( listDebugging )
		checkListBase();
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::removeLast( void )
{
	if( first_ == last_ )
		first_ = last_ = 0;
	else
	{
		last_ = last_->prev();
		last_->next( 0 );
	}

	size_--;

	if( listDebugging )
		checkListBase();
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::destroy( void )
{
	ItemType *member, *nextMember;

	if( freeable_ )
	{
		for( member = first_; member; member = nextMember )
		{
			nextMember = member->next();
			delete member;
		}
	}

	emptyListBase();
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::emptyListBase( void )
{
	first_ = last_ = current_ = 0;
	size_ = 0;
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::exchange( ItemType *el1, ItemType *el2 )
{
	ItemType *prev1;
	ItemType *next2;

	prev1 = el1->prev();
	next2 = el2->next();

	if( first_ == el1 )
		first_ = el2;

	if( last_ == el2 )
		last_ = el1;

	if( prev1 )
		prev1->next( el2 );
	el2->prev( prev1 );
	el2->next( el1 );
	el1->prev( el2 );
	el1->next( next2 );
	if( next2 )
		next2->prev( el1 );

	if( current_ == el1 )
		current_ = el2;
	else if( current_ == el2 )
		current_ = el1;

	if( listDebugging )
		checkListBase();
}


template< class ItemType, class ListType >
ItemType *ListBase< ItemType, ListType >::operator[]( US pos )
{
	ItemType *item;
	US loop;

	for( item = first_, loop = 0; loop < pos && item; loop++, item = item->next() )
		;

	if( !item )
		//********************  throw exception
		return 0;

	current_ = item;
	return item;
}


template< class ItemType, class ListType >
NI ListBase< ItemType, ListType >::isFirst( ItemType *item )
{
	if( item == first_ )
		return CQL_YES;
	else
		return CQL_NO;
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::move( ListBase< ItemType, ListType >& destination )
{
	ItemType *member;
	ItemType *nextMember;

	for( member = first_; member; member = nextMember )
	{
		nextMember = member->next();
		destination.add( member );
	}

	emptyListBase();
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType>::transfer( ItemType *item, ListBase< ItemType, ListType>& destination )
{
	remove( item );
	destination.add( item );
}


template< class ItemType, class ListType >
void ListBase< ItemType, ListType >::moveToEnd( ItemType *item )
{
	if( last_ == item )
		return;

	if( first_ == item )
	{
		first_ = item->next();
		first_->prev( 0 );
		last_->next( item );
		item->next( 0 );
		item->prev( last_ );
		last_ = item;
	}
	else
	{
		item->prev()->next( item->next() );
		item->next()->prev( item->prev() );
		last_->next( item );
		item->prev( last_ );
		item->next( 0 );
		last_ = item;
	}

	if( listDebugging )
		checkListBase();
}


template< class ItemType, class ListType >
ItemType *ListBase< ItemType, ListType >::first( void )
{
	current_ = first_;
	return first_;
}


template< class ItemType, class ListType >
ItemType *ListBase< ItemType, ListType >::next( void )
{
	if( current_ )
		current_ = current_->next();

	return current_;
}


template< class ItemType, class ListType >
ItemType *ListBase< ItemType, ListType >::last( void )
{
	current_ = last_;
	return last_;
}


template< class ItemType, class ListType >
ItemType *ListBase< ItemType, ListType >::prev( void )
{
	if( current_ )
		current_ = current_->prev();

	return current_;
}


#endif  //  _ListBase_h
