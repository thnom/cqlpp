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


BoundColumnPUCharShort::BoundColumnPUCharShort( AbstractColumnDescriptor* _col,
												bool freeable )
	: BoundColumn( _col ), freeable_( freeable ), userData_( 0 )
{
}


BoundColumnPUCharShort::BoundColumnPUCharShort( const BoundColumnPUCharShort& other,
												bool freeable )
	: BoundColumn( other ), freeable_( freeable )
{
	userData_ = other.userData_;
	length_ = other.length_;
}


BoundColumnPUCharShort::~BoundColumnPUCharShort( void )
{
}


bool BoundColumnPUCharShort::operator == ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator == ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator == ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator == ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator > ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator > ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator > ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator >= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator >= ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator >= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator < ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator < ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator < ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator <= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUCharShort::operator <= ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUCharShort::operator <= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


void BoundColumnPUCharShort::operator >> ( BigintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( BigintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( BinaryValue& dest )
{
	if( dest.typeLength() != *length_ )
		throw LengthMismatchException( __FILE__, __LINE__ );

	dest = BinaryValue( *userData_, *length_ );
}


void BoundColumnPUCharShort::operator << ( BinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ !=  source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPUCharShort::operator << ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( CharValue& dest )
{
	dest = CharValue( *userData_ );
}


void BoundColumnPUCharShort::operator << ( CharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ !=  source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.data(), source.length() );
}


void BoundColumnPUCharShort::operator >> ( CharUCValue& dest )
{
	dest = CharUCValue( *userData_ );
}


void BoundColumnPUCharShort::operator << ( CharUCValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ !=  source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.data(), source.length() );
}


void BoundColumnPUCharShort::operator >> ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( DecimalValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( DecimalValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( FloatValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( FloatValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( IntegerValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( IntegerValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( LongvarbinaryValue& dest )
{
	dest = LongvarbinaryValue( *userData_, *length_ );
}


void BoundColumnPUCharShort::operator << ( LongvarbinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ !=  source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPUCharShort::operator >> ( LongvarcharValue& dest )
{
	dest = LongvarcharValue( *userData_ );
}


void BoundColumnPUCharShort::operator << ( LongvarcharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ !=  source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPUCharShort::operator >> ( RealValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( RealValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( SmallintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( SmallintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( TinyintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator << ( TinyintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUCharShort::operator >> ( VarbinaryValue& dest )
{
	dest = VarbinaryValue( static_cast< UC >( *length_ ), *userData_ );
}


void BoundColumnPUCharShort::operator << ( VarbinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ !=  source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPUCharShort::operator >> ( VarcharValue& dest )
{
	dest = VarcharValue( *userData_ );
}


void BoundColumnPUCharShort::operator << ( VarcharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_  )
			delete *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = static_cast< UC >( source.length() );
		if( *length_ !=  source.length() )
			throw SizeConversionException( __FILE__, __LINE__ );
	}

	memcpy( *userData_, source.buffer(), source.length() );
}
