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


SegmentedKeyGroup::SegmentedKeyGroup( void )
	: SegmentedKeyGroupListElement(),
	  indexName_( CQL_MAXIMUM_INDEX_NAME_LENGTH ),
	  keyNumber( 0 ),
	  primaryKey( CQL_NO ),
	  segmentedKeyColumns(),
	  unique( CQL_NO )
{
}


SegmentedKeyGroup::SegmentedKeyGroup( US knum )
	: SegmentedKeyGroupListElement(),
	  indexName_( CQL_MAXIMUM_INDEX_NAME_LENGTH ),
	  keyNumber( knum ),
	  primaryKey( CQL_NO ),
	  segmentedKeyColumns(),
	  unique( CQL_NO )
{
}


SegmentedKeyGroup::~SegmentedKeyGroup( void )
{
	segmentedKeyColumns.destroy();
}


void SegmentedKeyGroup::SetIndexName( CqlString& name )
{
	indexName_ = name;
}


void SegmentedKeyGroup::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << indexName_ << keyNumber << primaryKey << unique;
	segmentedKeyColumns.writeDictionaryInformation( buffer );
}


void SegmentedKeyGroup::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> indexName_ >> keyNumber >> primaryKey >> unique;
	segmentedKeyColumns.readDictionaryInformation( buffer );
}


US SegmentedKeyGroup::dictionaryLength( void )
{
	return ((US)( indexName_.length() + sizeof( keyNumber ) + sizeof( primaryKey) + sizeof( unique ) + segmentedKeyColumns.dictionaryLength() ) );
}


NI SegmentedKeyGroup::Assign( SegmentedKeyGroup& other )
{
	pAbstractColumnDescriptor colDesc, newColDesc;

	indexName_ = other.indexName_;
	keyNumber = other.keyNumber;
	primaryKey = other.primaryKey;
	unique = other.unique;

	for( colDesc = other.segmentedKeyColumns.first(); colDesc; colDesc = other.segmentedKeyColumns.next() )
	{
		newColDesc = AbstractColumnDescriptor::createObject( 
													colDesc->columnType(),
													colDesc->columnNumber(),
													colDesc->descending() );
		segmentedKeyColumns.add( newColDesc );
	}

	return CQL_SUCCESS;
}

void SegmentedKeyGroup::setIndexName(CqlString& tablename)
{
		NC namebuffer[ 512 ];
		sprintf(namebuffer,"%s%d",tablename.text(),keyNumber);
		indexName_ = namebuffer;
}


SegmentedKeyGroupList::SegmentedKeyGroupList( void ) : SegmentedKeyGroupListBase()
{
}


void SegmentedKeyGroupList::writeDictionaryInformation( TempBuffer& buffer )
{
	pSegmentedKeyGroup skg;

	buffer << size();

	for( skg = first(); skg; skg = next() )
		skg->writeDictionaryInformation( buffer );
}


US SegmentedKeyGroupList::DictionaryLength( void )
{
	US _size;
	pSegmentedKeyGroup skg;

	//  for number of groups
	_size = sizeof( UNI );

	for( skg = first(); skg; skg = next() )
		_size = ((US)( _size + skg->dictionaryLength() ) );

	return _size;
}


void SegmentedKeyGroupList::readDictionaryInformation( TempBuffer& buffer )
{
	pSegmentedKeyGroup skg;
	UNI numberOfGroups, loop;

	buffer >> numberOfGroups;

	for( loop = 0; loop < numberOfGroups; loop++ )
	{
		skg = new SegmentedKeyGroup( ((US)loop) );
		if( !skg )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		skg->readDictionaryInformation( buffer );
		add( skg );
	}
}


NI SegmentedKeyGroupList::Assign( SqlHandle *dbsql, SegmentedKeyGroupList& other )
{
	pSegmentedKeyGroup skg, newSkg;
	UNI loop;

	for( loop = 0, skg = other.first(); skg; skg = other.next(), loop++ )
	{
		newSkg = new SegmentedKeyGroup( ((US)loop) );
		if( !newSkg )
			return dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

		if( newSkg->Assign( *skg ) == CQL_FAILURE )
			return CQL_FAILURE;

		add( newSkg );
	}

	return CQL_SUCCESS;
}


