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


BoundColumnPChar::BoundColumnPChar( AbstractColumnDescriptor* _col,
									bool freeable )
	: BoundColumn( _col ), freeable_( freeable ), length_( 0 ), userData_( 0 )
{
}


BoundColumnPChar::BoundColumnPChar( const BoundColumnPChar& other,
									bool freeable )
	: BoundColumn( other ), freeable_( freeable )
{
	*userData_ = new NC[ *other.length_ ];
	if( !*userData_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memcpy( *userData_, *other.userData_, *other.length_ );
	length_ = other.length_;
}


BoundColumnPChar::~BoundColumnPChar( void )
{
}


bool BoundColumnPChar::operator == ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator == ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator == ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator == ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator > ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator > ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator > ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator > ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator >= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator >= ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator >= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator >= ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator < ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator < ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator < ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator < ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator <= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator <= ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPChar::operator <= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPChar::operator <= ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


void BoundColumnPChar::operator >> ( BigintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( BigintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( BinaryValue& dest )
{
	dest = BinaryValue( reinterpret_cast< UC *>( *userData_ ), *length_ );
}


void BoundColumnPChar::operator << ( BinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPChar::operator >> ( CharValue& dest )
{
	dest = CharValue( *userData_ );
}


void BoundColumnPChar::operator << ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( CharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;

		*userData_ = new NC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.data(), source.length() );
}


void BoundColumnPChar::operator >> ( CharUCValue& dest )
{
	dest = CharUCValue( *userData_ );
}


void BoundColumnPChar::operator << ( CharUCValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.data(), source.length() );
}


void BoundColumnPChar::operator >> ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( DecimalValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( DecimalValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( FloatValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( FloatValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( IntegerValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( IntegerValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( LongvarbinaryValue& dest )
{
	dest = LongvarbinaryValue( reinterpret_cast< UC *>( *userData_ ), *length_ );
}


void BoundColumnPChar::operator << ( LongvarbinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPChar::operator >> ( LongvarcharValue& dest )
{
	*length_ = strlen( *userData_ );
	dest = LongvarcharValue( *length_, reinterpret_cast< UC *>( *userData_ ) );
}


void BoundColumnPChar::operator << ( LongvarcharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new NC[ source.length() + 1 ];
		*length_ = source.length();
	}

	strcpy( *userData_, source.buffer() );
}


void BoundColumnPChar::operator >> ( RealValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( RealValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( SmallintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( SmallintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( TinyintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator << ( TinyintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPChar::operator >> ( VarbinaryValue& dest )
{
	dest = VarbinaryValue( static_cast< UC >( *length_ ), reinterpret_cast< UC *>( *userData_ ) );
}


void BoundColumnPChar::operator << ( VarbinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPChar::operator >> ( VarcharValue& dest )
{
	*length_ = strlen( *userData_ );
	dest = VarcharValue( *userData_ );
}


void BoundColumnPChar::operator << ( VarcharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.buffer(), source.length() );
}
