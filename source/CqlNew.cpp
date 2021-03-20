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


NI AllocationDebuggingLevel = 0;
//  NI AllocationDebuggingLevel = 1;
//  NI AllocationDebuggingLevel = 2;


#define MEM_MARK "~@<!>@~"
#define MARK_LEN 8


typedef struct _alcspec
{
	struct _alcspec *prev;
	struct _alcspec *next;
	pNC ptr;
	UNI len;
	UNI AllocationCount;
	BFT displayed : 1;
	BFT allocated : 1;
} ALCSPEC, *pALCSPEC;


static ALCSPEC *FirstBlock;
static ALCSPEC *LastBlock;
static UNI FreeNumber;
static UNI AllocationNumber;
static L MaximumAllocation;
static L CurrentAllocation;


#ifdef ANSIFUNCS
void listok( void )
#else
void listok()
#endif
{
	ALCSPEC *lp;
	pNC p;
	pNC forceTrap = ((pNC)0);

	for ( lp = FirstBlock; lp; lp = lp->next )
	{
		if( !lp->allocated )
			*forceTrap = 0;

		p = lp->ptr - MARK_LEN;
		if (strcmp(p, MEM_MARK))
			*forceTrap = 0;

		p = lp->ptr + lp->len;
		if (strcmp(p, MEM_MARK))
			*forceTrap = 0;
	}
}


static void AddToList( pALCSPEC alc )
{
	if( !FirstBlock )
		FirstBlock = LastBlock = alc;
	else
	{
		alc->prev = LastBlock;
		LastBlock->next = alc;
		LastBlock = alc;
	}
}


static void RemoveFromList( pALCSPEC alc )
{
	if( !alc->prev && !alc->next )
	{
		/*  only member of list  */
		FirstBlock = LastBlock = ((pALCSPEC)0);
	}
	
	else if( !alc->prev )
	{
		/*  deleting head of list  */
		alc->next->prev = ((pALCSPEC)0);
		FirstBlock = alc->next;
	}

	else if( !alc->next )
	{
		/*  deleting tail of list  */
		alc->prev->next = ((pALCSPEC)0);
		LastBlock = alc->prev;
	}

	else
	{
		/*  deleting in the middle of the list  */
		alc->prev->next = alc->next;
		alc->next->prev = alc->prev;
	}
}


pNC SQLAlloc( UNI size )
{
	pNC p;
	UNI lsize;
	pALCSPEC alc;
	pNC forceTrap = ((pNC)0);

	switch( AllocationDebuggingLevel )
	{
	case 3 :
		AllocationNumber++;
		//  deliberate fall through

	case 0 :
	case 4 :

		if( !size )
			return( ((pNC)0) );

		p = ((pNC)malloc( size ));
		if( !p )
			return( ((pNC)0) );
		memset( p, 0, size );
		return( p );


	case 2 :

		CurrentAllocation += size;

		if( CurrentAllocation > MaximumAllocation )
			MaximumAllocation = CurrentAllocation;

		/*  no break, intentionally  */

	case 1 :

		if( !size )
			return( ((pNC)0) );

		lsize = size + (2 * MARK_LEN) + 2 + sizeof( ALCSPEC );

		p = ((pNC)malloc(lsize));
		if (!p)
			return( ((pNC)0) );

		memset( p, 0, lsize );

		alc = ((pALCSPEC)p);
		p += sizeof( ALCSPEC );

		strcpy(p, MEM_MARK);
		p += MARK_LEN;
		strcpy(p + size, MEM_MARK);

		alc->ptr = p;
		alc->len = size;
		alc->AllocationCount = AllocationNumber++;
		alc->allocated = CQL_YES;

		AddToList( alc );

		listok();

		return(p);

	default :
		*forceTrap = 0;
	}

	return 0;
}


void SQLFree( pNC ptr )
{
	pNC p;
	pALCSPEC alc;
	pNC forceTrap = ((pNC)0);

	switch( AllocationDebuggingLevel )
	{
	case 3 :
		FreeNumber++;
		//  deliberate fall through

	case 0 :
	case 4 :
		free( ptr );
		return;

	case 1 :
	case 2 :

		FreeNumber++;

		/*  verify list integrity  */
		listok();

		p = ((pNC)ptr);
		p -= MARK_LEN;
		p -= sizeof( ALCSPEC );
		alc = ((pALCSPEC)p);

		if( !alc->allocated )
			*forceTrap = 0;
		else
			alc->allocated = CQL_NO;

		if( AllocationDebuggingLevel == 2 )
			CurrentAllocation -= alc->len;

		RemoveFromList( alc );
		free(p);
		return;

	default :
		*forceTrap = 0;
	}
}


void DisplayMemoryStatus( NI DisplayAll )
{
	L AllocationDifference;
	ALCSPEC *lp;
	pNC forceTrap = ((pNC)0);

	AllocationDifference = AllocationNumber - FreeNumber;
	printf( "\nallocation difference = %ld\n", ((L)AllocationDifference) );

	if( AllocationDebuggingLevel < 2 )
		return;

	printf("Current allocation = %ld, maximum allocation = %ld\n",
		((L)CurrentAllocation), ((L)MaximumAllocation) );

	for( lp = FirstBlock; lp; lp = lp->next )
	{
		if( !lp->allocated )
			*forceTrap = 0;

		if( !DisplayAll && lp->displayed )
			continue;

		printf( "AllocationNumber %ld, size %ld\n", ((L)lp->AllocationCount), ((L)lp->len) );

		lp->displayed = 1;
	}
}


static int first = 0;
static long allocationCounter = 0;
static FILE *fpNew;


void* operator new( UNI size )
{
	void *p;
	pNC forceTrap = ((pNC)0);

	if( first == 0 && AllocationDebuggingLevel == 4 )
	{
		first = 1;
		fpNew = fopen( "new.log", "w" );
		if( !fpNew )
			*forceTrap = 0;
	}

	p = SQLAlloc( size );

	if( AllocationDebuggingLevel == 4 )
		fprintf( fpNew, "%lx, %ld\n", ((UL)p), allocationCounter++ );

	return p;
}


static int firstDelete = 0;
static long freeCounter = 0;
FILE *fpDelete;


void operator delete( void* ptr )
{
	pNC forceTrap = ((pNC)0);

	if( firstDelete == 0 && AllocationDebuggingLevel == 4 )
	{
		firstDelete = 1;
		fpDelete = fopen( "delete.log", "w" );
		if( !fpDelete )
			*forceTrap = 0;
	}

	if( AllocationDebuggingLevel == 4 )
		fprintf( fpDelete, "%lx, %ld\n", ((UL)ptr), freeCounter++ );

	SQLFree( ((pNC)ptr) );
}
