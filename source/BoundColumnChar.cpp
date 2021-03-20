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


BoundColumnChar::BoundColumnChar( AbstractColumnDescriptor* _col ) : BoundColumn( _col ), userData_( 0 )
{
}


BoundColumnChar::BoundColumnChar( const BoundColumnChar& other ) : BoundColumn( other )
{
	userData_ = other.userData_;
}


BoundColumnChar::~BoundColumnChar( void )
{
}


bool BoundColumnChar::operator == ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) == other;
}


bool BoundColumnChar::operator == ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator == ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator == ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator == ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) == other;
}


bool BoundColumnChar::operator == ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) == other;
}


bool BoundColumnChar::operator == ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) == other;
}


bool BoundColumnChar::operator == ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator == ( const LongvarcharValue& other ) const
{
	if( strlen( userData_ ) != other.length() + 1 )
		return false;

	if( strcmp( userData_, other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnChar::operator == ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) == other;
}


bool BoundColumnChar::operator == ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) == other;
}


bool BoundColumnChar::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator == ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) == other;
}


bool BoundColumnChar::operator == ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator == ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) > other;
}


bool BoundColumnChar::operator > ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) > other;
}


bool BoundColumnChar::operator > ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) > other;
}


bool BoundColumnChar::operator > ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) > other;
}


bool BoundColumnChar::operator > ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) > other;
}


bool BoundColumnChar::operator > ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) > other;
}


bool BoundColumnChar::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) > other;
}


bool BoundColumnChar::operator > ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator > ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) >= other;
}


bool BoundColumnChar::operator >= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) >= other;
}


bool BoundColumnChar::operator >= ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) >= other;
}


bool BoundColumnChar::operator >= ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) >= other;
}


bool BoundColumnChar::operator >= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) >= other;
}


bool BoundColumnChar::operator >= ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) >= other;
}


bool BoundColumnChar::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) >= other;
}


bool BoundColumnChar::operator >= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator >= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) < other;
}


bool BoundColumnChar::operator < ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) < other;
}


bool BoundColumnChar::operator < ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) < other;
}


bool BoundColumnChar::operator < ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) < other;
}


bool BoundColumnChar::operator < ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) < other;
}


bool BoundColumnChar::operator < ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) < other;
}


bool BoundColumnChar::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) < other;
}


bool BoundColumnChar::operator < ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator < ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) <= other;
}


bool BoundColumnChar::operator <= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) <= other;
}


bool BoundColumnChar::operator <= ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) <= other;
}


bool BoundColumnChar::operator <= ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) <= other;
}


bool BoundColumnChar::operator <= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) <= other;
}


bool BoundColumnChar::operator <= ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) <= other;
}


bool BoundColumnChar::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) <= other;
}


bool BoundColumnChar::operator <= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnChar::operator <= ( const VarcharValue& other ) const
{
	if( strcmp( userData_, other.buffer() ) <= 0 )
		return true;

	return false;
}


void BoundColumnChar::operator >> ( BigintValue& dest )
{
	dest = BigintValue( *userData_ );
}


void BoundColumnChar::operator << ( BigintValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnChar::operator >> ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( DecimalValue& dest )
{
	dest = DecimalValue( *userData_ );
}


void BoundColumnChar::operator << ( DecimalValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnChar::operator >> ( FloatValue& dest )
{
	dest = FloatValue( *userData_ );
}


void BoundColumnChar::operator << ( FloatValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnChar::operator >> ( IntegerValue& dest )
{
	dest = IntegerValue( *userData_ );
}


void BoundColumnChar::operator << ( IntegerValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnChar::operator >> ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( RealValue& dest )
{
	dest = RealValue( *userData_ );
}


void BoundColumnChar::operator << ( RealValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnChar::operator >> ( SmallintValue& dest )
{
	dest = SmallintValue( *userData_ );
}


void BoundColumnChar::operator << ( SmallintValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnChar::operator >> ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( TinyintValue& dest )
{
	dest = TinyintValue( *userData_ );
}


void BoundColumnChar::operator << ( TinyintValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnChar::operator >> ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator >> ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnChar::operator << ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}
