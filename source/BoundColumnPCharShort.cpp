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


BoundColumnPCharShort::BoundColumnPCharShort( AbstractColumnDescriptor* _col, bool freeable ) : BoundColumn( _col ), freeable_(freeable), length_( 0 ), userData_( 0 )
{
}


BoundColumnPCharShort::BoundColumnPCharShort( const BoundColumnPCharShort& other,
											  bool freeable )
	: BoundColumn( other ), freeable_( freeable )
{
	length_ = other.length_;
	userData_ = other.userData_;
}


BoundColumnPCharShort::~BoundColumnPCharShort( void )
{
}


bool BoundColumnPCharShort::operator == ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator == ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator == ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator == ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator > ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator > ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator > ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator > ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator >= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator >= ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator >= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator >= ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator < ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator < ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator < ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator < ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator <= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const CharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator <= ( const CharUCValue& other ) const
{
	if( *length_ != other.value().length() )
		return false;

	if( strcmp( *userData_, other.value().text() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const LongvarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnPCharShort::operator <= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPCharShort::operator <= ( const VarcharValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( strcmp( *userData_, other.buffer() ) )
		return false;

	return true;
}


void BoundColumnPCharShort::operator >> ( BigintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( BigintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( BinaryValue& dest )
{
	dest = BinaryValue( reinterpret_cast< UC *>( *userData_ ), *length_ );
}


void BoundColumnPCharShort::operator << ( BinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ != source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPCharShort::operator >> ( CharValue& dest )
{
	dest = CharValue( *userData_ );
}


void BoundColumnPCharShort::operator << ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( CharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ != source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.data(), source.length() );
}


void BoundColumnPCharShort::operator >> ( CharUCValue& dest )
{
	dest = CharUCValue( *userData_ );
}


void BoundColumnPCharShort::operator << ( CharUCValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ != source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.data(), source.length() );
}


void BoundColumnPCharShort::operator >> ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( DecimalValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( DecimalValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( FloatValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( FloatValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( IntegerValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( IntegerValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( LongvarbinaryValue& dest )
{
	dest = LongvarbinaryValue( reinterpret_cast< const UC *>( *userData_ ), *length_ );
}


void BoundColumnPCharShort::operator << ( LongvarbinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ != source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPCharShort::operator >> ( LongvarcharValue& dest )
{
	*length_ = static_cast< UC >( strlen( *userData_ ) );
	if( *length_ != strlen( *userData_ ) )
		throw SizeConversionException( __FILE__, __LINE__ );
	dest = LongvarcharValue( *length_, reinterpret_cast< UC *>( *userData_ ) );
}


void BoundColumnPCharShort::operator << ( LongvarcharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new NC[ source.length() + 1 ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ != source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	strcpy( *userData_, source.buffer() );
}


void BoundColumnPCharShort::operator >> ( RealValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( RealValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( SmallintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( SmallintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( TinyintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator << ( TinyintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPCharShort::operator >> ( VarbinaryValue& dest )
{
	dest = VarbinaryValue( static_cast< UC >( *length_ ), reinterpret_cast< UC *>( *userData_ ) );
}


void BoundColumnPCharShort::operator << ( VarbinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ != source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPCharShort::operator >> ( VarcharValue& dest )
{
	*length_ = static_cast< UC >( strlen( *userData_ ) );
	if( *length_ != strlen( *userData_ ) )
		throw SizeConversionException( __FILE__, __LINE__ );
	dest = VarcharValue( *userData_ );
}


void BoundColumnPCharShort::operator << ( VarcharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new NC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ != source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.buffer(), source.length() );
}
