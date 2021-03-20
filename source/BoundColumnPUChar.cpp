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


BoundColumnPUChar::BoundColumnPUChar( AbstractColumnDescriptor* _col,
									  bool freeable )
	: BoundColumn( _col ), freeable_( freeable ), userData_( 0 )
{
}


BoundColumnPUChar::BoundColumnPUChar( const BoundColumnPUChar& other,
									  bool freeable )
	: BoundColumn( other ), freeable_( freeable )
{
	*userData_ = new UC[ *other.length_ ];
	if( !*userData_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memcpy( *userData_, *other.userData_, *other.length_ );
	length_ = other.length_;
}


BoundColumnPUChar::~BoundColumnPUChar( void )
{
	if( *userData_ && freeable_ )
		delete [] *userData_;
}


bool BoundColumnPUChar::operator == ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator == ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator == ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator == ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator > ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator > ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator > ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator >= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator >= ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator >= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator < ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator < ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator < ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const BinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const LongvarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator <= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnPUChar::operator <= ( const VarbinaryValue& other ) const
{
	if( *length_ != other.length() )
		return false;

	if( memcmp( *userData_, other.buffer(), *length_ ) )
		return false;

	return true;
}


bool BoundColumnPUChar::operator <= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


void BoundColumnPUChar::operator >> ( BigintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( BigintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( BinaryValue& dest )
{
	if( dest.typeLength() != *length_ )
		throw LengthMismatchException( __FILE__, __LINE__ );

	dest = BinaryValue( *userData_, *length_ );
}


void BoundColumnPUChar::operator << ( BinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new UC[ source.length() ];
		if( !*userData_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*length_ = source.length();
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPUChar::operator << ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( CharValue& dest )
{
	dest = CharValue( *userData_ );
}


void BoundColumnPUChar::operator << ( CharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.data(), source.length() );
}


void BoundColumnPUChar::operator >> ( CharUCValue& dest )
{
	dest = CharUCValue( *userData_ );
}


void BoundColumnPUChar::operator << ( CharUCValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.data(), source.length() );
}


void BoundColumnPUChar::operator >> ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( DecimalValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( DecimalValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( FloatValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( FloatValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( IntegerValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( IntegerValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( LongvarbinaryValue& dest )
{
	dest = LongvarbinaryValue( *userData_, *length_ );
}


void BoundColumnPUChar::operator << ( LongvarbinaryValue& source )
{
	if( *length_ < source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPUChar::operator >> ( LongvarcharValue& dest )
{
	dest = LongvarcharValue( *userData_ );
}


void BoundColumnPUChar::operator << ( LongvarcharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPUChar::operator >> ( RealValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( RealValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( SmallintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( SmallintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( TinyintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator << ( TinyintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnPUChar::operator >> ( VarbinaryValue& dest )
{
	dest = VarbinaryValue( static_cast< UC >( *length_ ), *userData_ );
}


void BoundColumnPUChar::operator << ( VarbinaryValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.buffer(), source.length() );
}


void BoundColumnPUChar::operator >> ( VarcharValue& dest )
{
	dest = VarcharValue( *userData_ );
}


void BoundColumnPUChar::operator << ( VarcharValue& source )
{
	if( *length_ != source.length() )
	{
		if( *userData_ && freeable_ )
			delete [] *userData_;
		*userData_ = new UC[ source.length() ];
		*length_ = source.length();
	}

	memcpy( *userData_, source.buffer(), source.length() );
}
