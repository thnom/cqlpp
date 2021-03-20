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


#include "CqlSqlInclude.h"


DoubleStringList::DoubleStringList( void ) : DoubleStringListBase()
{
}


DoubleStringList::~DoubleStringList( void )
{
}


void DoubleStringList::writeDictionaryInformation( TempBuffer& buffer )
{
	pDoubleStringListElement dsle;

	buffer << size();

	for( dsle = first(); dsle; dsle = next() )
		dsle->writeDictionaryInformation( buffer );
}


void DoubleStringList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfStrings, loop;
	pDoubleStringListElement dsle;

	buffer >> numberOfStrings;

	for( loop = 0; loop < numberOfStrings; loop++ )
	{
		dsle = new DoubleStringListElement;
		if( !dsle )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		dsle->readDictionaryInformation( buffer );
		add( dsle );
	}
}


StringList::StringList( void ) : StringListBase()
{
}


StringList::~StringList( void )
{
}


US StringList::dictionaryLength( void )
{
	US _size;
	pStringListElement sle;

	//
	//  scalar values:
	//    UNI listSize
	//
	_size = sizeof( UNI );

	for( sle = first(); sle; sle = next() )
		_size = static_cast< US >( _size + sle->dictionaryLength() );

	return _size;
}


void StringList::writeDictionaryInformation( TempBuffer& buffer )
{
	pStringListElement sle;

	buffer << size();

	for( sle = first(); sle; sle = next() )
		sle->writeDictionaryInformation( buffer );
}


void StringList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfCqlStrings, loop;
	pStringListElement sle;

	buffer >> numberOfCqlStrings;

	for( loop = 0; loop < numberOfCqlStrings; loop++ )
	{
		sle = new StringListElement;
		if( !sle )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		sle->readDictionaryInformation( buffer );
		add( sle );
	}
}


StringListGroup::StringListGroup( void ) : StringListGroupListElement(), sl()
{
}


StringListGroup::~StringListGroup( void )
{
}


TripleStringList::TripleStringList( void ) : TripleStringListBase()
{
}


TripleStringList::~TripleStringList( void )
{
}


NI TripleStringList::Assign( SqlHandle *dbsql, TripleStringList& other )
{
	pTripleStringListElement tsel, newTsel;

	for( tsel = other.first(); tsel; tsel = other.next() )
	{
		newTsel = new TripleStringListElement;
		if( !newTsel )
			return dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

		*newTsel = *tsel;
		add( newTsel );
	}

	return CQL_SUCCESS;
}


void TripleStringList::writeDictionaryInformation( TempBuffer& buffer )
{
	pTripleStringListElement tsle;

	buffer << size();

	for( tsle = first(); tsle; tsle = next() )
		tsle->writeDictionaryInformation( buffer );
}


void TripleStringList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfCqlStrings, loop;
	pTripleStringListElement tsle;

	buffer >> numberOfCqlStrings;

	for( loop = 0; loop < numberOfCqlStrings; loop++ )
	{
		tsle = new TripleStringListElement;
		if( !tsle )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		tsle->readDictionaryInformation( buffer );
		add( tsle );
	}
}


