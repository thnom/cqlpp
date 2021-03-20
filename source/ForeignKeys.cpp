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


ForeignKey::ForeignKey( void ) : ForeignKeyListElement(), referencedTableKey_( 0 ), referencedTableName_(), referencingColumns_()
{
}


ForeignKey::~ForeignKey( void )
{
	referencingColumns_.destroy();
	referencedColumns_.destroy();
}


US ForeignKey::dictionaryLength( void )
{
	US size;

	size = ((US)( referencedTableName_.length() + referencedTablePrefix_.length() + sizeof( referencedTableKey_ ) + referencingColumns_.DictionaryLength()
		+ referencedColumns_.DictionaryLength() ) );

	return size;
}


void ForeignKey::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << referencedTableName_ << referencedTablePrefix_ << referencedTableKey_;

	referencingColumns_.writeDictionaryInformation( buffer );
	referencedColumns_.writeDictionaryInformation( buffer );
}


void ForeignKey::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> referencedTableName_ >> referencedTablePrefix_ >> referencedTableKey_;

	referencingColumns_.readDictionaryInformation( buffer );
	referencedColumns_.readDictionaryInformation( buffer );
}


ForeignKey& ForeignKey::operator = ( const ForeignKey& other )
{
	referencedTableName_ = other.referencedTableName_;
	referencedTablePrefix_ = other.referencedTablePrefix_;
	referencedTableKey_ = other.referencedTableKey_;
	referencingColumns_ = other.referencingColumns_;
	referencedColumns_ = other.referencedColumns_;
	return *this;
}


ForeignKeyList::ForeignKeyList( void ) : ForeignKeyListBase()
{
}


US ForeignKeyList::DictionaryLength( void )
{
	US _size;
	pForeignKey fk;

	//  for # of foreign keys
	_size = sizeof( UNI );

	for( fk = first(); fk; fk = next() )
		_size = ((US)( _size + fk->dictionaryLength() ) );

	return _size;
}


void ForeignKeyList::writeDictionaryInformation( TempBuffer& buffer )
{
	pForeignKey fk;

	buffer << size();

	for( fk = first(); fk; fk = next() )
		fk->writeDictionaryInformation( buffer );
}


void ForeignKeyList::readDictionaryInformation( TempBuffer& buffer )
{
	pForeignKey fk;
	UNI numberOfForeignKeys, loop;

	buffer >> numberOfForeignKeys;

	for( loop = 0; loop < numberOfForeignKeys; loop++ )
	{
		fk = new ForeignKey;
		if( !fk )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		fk->readDictionaryInformation( buffer );

		add( fk );
	}
}


NI ForeignKeyList::Assign( SqlHandle *dbsql, ForeignKeyList& other )
{
	pForeignKey fk, newFk;

	for( fk = other.first(); fk; fk = other.next() )
	{
		newFk = new ForeignKey;
		if( !newFk )
			return dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

		*newFk = *fk;
		add( newFk );
	}

	return CQL_SUCCESS;
}


ForeignKeyNames::ForeignKeyNames( void ) : referencingColumns(), baseTableName(), referencedColumns()
{
}


ForeignKeyNames::~ForeignKeyNames( void )
{
	baseTableName.reset();
	baseTablePrefix.reset();
	referencedColumns.destroy();
	referencingColumns.destroy();
}


