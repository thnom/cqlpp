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


Record::Record( AbstractDatabaseHandle& adh ) : TempBuffer( adh ), location( 0 ), dirty( false ), temporary( false )
{
}


Record::Record( AbstractDatabaseHandle& adh, RECID loc ) : TempBuffer( adh ), location( loc ), dirty( false ), temporary( false )
{
}


Record::~Record( void )
{
}


//  This method needs to use a TempBuffer, so that data can be streamed from ColumnDescriptor objects.
//  Record now inherits from TempBuffer.  Streaming to *this should stream to TempBuffer
NI Record::ConstructRecord( DatabaseHandle& dbHandle, AbstractColumnDescriptorList& columns, UL len )
{
	US cno;

	if( setBuffer( len ) == CQL_FAILURE )
		return dbHandle.returnError( ALLOCATION, __FILE__, __LINE__ );

	AbstractColumnDescriptor* acd;
	for( acd = columns.first(), cno = 0; acd; acd = columns.next(), cno++ )
	{
		ColumnDescriptor *colDesc = dynamic_cast< ColumnDescriptor* >( acd );
		*colDesc >> *this;
	}

	return CQL_SUCCESS;
}

		
NI Record::Assign( DatabaseHandle&, Record& other )
{
	*((TempBuffer*)this) = ((TempBuffer&)other);
	location = other.location;

	dirty = other.dirty;
	temporary = other.temporary;

	return CQL_SUCCESS;
}


NI Record::InputCachedRecord( AbstractColumnDescriptorList& columns )
{
	initializeCurrentPosition();

	// FIXED
	AbstractColumnDescriptor* acd;
	for( acd = columns.first(); acd; acd = columns.next() )
	{
		ColumnDescriptor *col = dynamic_cast< ColumnDescriptor* >( acd );
		*col << *this;
	}

	return CQL_SUCCESS;
}


NI Record::Read( DatabaseHandle&, pFileManager file, AbstractColumnDescriptorList& columns )
{
	UL length;
	*file >> length;
	setBuffer( length );

	file->read( ((void*) currentPosition_), ((UNI)length) );
	return InputCachedRecord( columns );
}


UserManager::UserManager( void ) : userIdCounter( 0 )
{
}


UserManager::~UserManager( void )
{
}


void UserManager::GetUserId( pUL userId )
{
	*userId = userIdCounter++;
}


VirtualSlot::VirtualSlot( RECID filePos )
{
	filePosition = filePos;
}


VirtualSlot::~VirtualSlot( void )
{
}


VirtualSlot *VirtualSlot::Copy( void )
{
	pVirtualSlot vs;

	vs = new VirtualSlot( filePosition );
	if( !vs )
		return 0;
	return vs;
}


BoundColumn::BoundColumn( AbstractColumnDescriptor* _col ) : col_( _col ), userNullFlag_( 0 )
{
}


BoundColumn::BoundColumn( const BoundColumn& other ) : BoundColumnListElement(), CqlColumnTypes(), col_( other.col_ ), userNullFlag_( other.userNullFlag_ )
{
}


BoundColumn::~BoundColumn( void )
{
}


void BoundColumn::bindColumn( US /*columnNumber*/, CqlColumnTypes /*aType*/, CqlString& /*value*/, AbstractTable& /*table*/, NI /*forUpdate*/ )
{
}


void BoundColumn::bindColumn( US /*columnNumber*/, UL /*aLength*/, CqlColumnTypes /*aType*/, AbstractTable& /*table*/, NI /*forUpdate*/ )
{
}


void BoundColumn::bindNullColumn( US /*columnNumber*/, CqlColumnTypes /*aType*/, AbstractTable& /*table*/ )
{
}


ColumnDescriptor::ColumnDescriptor( US colNo, bool desc ) : AbstractColumnDescriptor(),	columnNumber_( colNo ), descending_( desc )
{
}


ColumnDescriptor::ColumnDescriptor( void ) : AbstractColumnDescriptor(), columnNumber_( 0 ), descending_( false )
{
}


ColumnDescriptor::~ColumnDescriptor( void )
{
}


void ColumnDescriptor::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << length() << columnNumber_ << descending_;
}


US ColumnDescriptor::dictionaryLength( void )
{
	return sizeof( CqlColumnTypes ) + sizeof( UL ) + sizeof( columnNumber_ ) + sizeof( descending_ );
}


ColumnDescriptor& ColumnDescriptor::operator = ( const ColumnDescriptor& other )
{
	columnNumber_ = other.columnNumber_;
	return *this;
}


ColumnDescriptor *ColumnDescriptor::readColumn( DatabaseHandle&, FileManager& file )
{
	CqlColumnTypes type;
	US colNo;
	bool desc;

	file >> type >> colNo >> desc;

	bool descending = desc ? true : false;

	AbstractColumnDescriptor *tCol;

	try
	{
		tCol = AbstractColumnDescriptor::createObject( type, colNo, descending );
	}
	catch( AbstractObjectCreationException& ex )
	{
		*hAEnv << ex;
		return 0;
	}

	return dynamic_cast< ColumnDescriptor* >( tCol );
}


void ColumnDescriptor::write( AbstractDatabaseHandle&, pFileManager file )
{
	try
	{
		CqlColumnTypes ttype( columnType() );
		*file << ttype << columnNumber_ << descending_;
	}
	catch( ... )
	{
		throw;
	}
}
