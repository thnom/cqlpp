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


BoundColumnUnsignedChar::BoundColumnUnsignedChar( AbstractColumnDescriptor* _col ) : BoundColumn( _col ), userData_( 0 )
{
}


BoundColumnUnsignedChar::BoundColumnUnsignedChar( const BoundColumnUnsignedChar& other ) : BoundColumn( other )
{
	userData_ = other.userData_;
}


BoundColumnUnsignedChar::~BoundColumnUnsignedChar( void )
{
}


bool BoundColumnUnsignedChar::operator == ( const BigintValue& other ) const
{
	return BigintValue( static_cast< NI >( *userData_ ) ) == other;
}


bool BoundColumnUnsignedChar::operator == ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const DecimalValue& other ) const
{
	return DecimalValue( static_cast< NI >( *userData_ ) ) == other;
}


bool BoundColumnUnsignedChar::operator == ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) == other;
}


bool BoundColumnUnsignedChar::operator == ( const IntegerValue& other ) const
{
	return IntegerValue( static_cast< NI >( *userData_ ) ) == other;
}


bool BoundColumnUnsignedChar::operator == ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) == other;
}


bool BoundColumnUnsignedChar::operator == ( const SmallintValue& other ) const
{
	return SmallintValue( static_cast< NI >( *userData_ ) ) == other;
}


bool BoundColumnUnsignedChar::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const TinyintValue& other ) const
{
	return TinyintValue( static_cast< NI >( *userData_ ) ) == other;
}


bool BoundColumnUnsignedChar::operator == ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator == ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const BigintValue& other ) const
{
	return BigintValue( static_cast< NI >( *userData_ ) ) > other;
}


bool BoundColumnUnsignedChar::operator > ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const DecimalValue& other ) const
{
	return DecimalValue( static_cast< NI >( *userData_ ) ) > other;
}


bool BoundColumnUnsignedChar::operator > ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) > other;
}


bool BoundColumnUnsignedChar::operator > ( const IntegerValue& other ) const
{
	return IntegerValue( static_cast< NI >( *userData_ ) ) > other;
}


bool BoundColumnUnsignedChar::operator > ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) > other;
}


bool BoundColumnUnsignedChar::operator > ( const SmallintValue& other ) const
{
	return SmallintValue( static_cast< NI >( *userData_ ) ) > other;
}


bool BoundColumnUnsignedChar::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const TinyintValue& other ) const
{
	return TinyintValue( static_cast< NI >( *userData_ ) ) > other;
}


bool BoundColumnUnsignedChar::operator > ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator > ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const BigintValue& other ) const
{
	return BigintValue( static_cast< NI >( *userData_ ) ) >= other;
}


bool BoundColumnUnsignedChar::operator >= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const DecimalValue& other ) const
{
	return DecimalValue( static_cast< NI >( *userData_ ) ) >= other;
}


bool BoundColumnUnsignedChar::operator >= ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) >= other;
}


bool BoundColumnUnsignedChar::operator >= ( const IntegerValue& other ) const
{
	return IntegerValue( static_cast< NI >( *userData_ ) ) >= other;
}


bool BoundColumnUnsignedChar::operator >= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) >= other;
}


bool BoundColumnUnsignedChar::operator >= ( const SmallintValue& other ) const
{
	return SmallintValue( static_cast< NI >( *userData_ ) ) >= other;
}


bool BoundColumnUnsignedChar::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const TinyintValue& other ) const
{
	return TinyintValue( static_cast< NI >( *userData_ ) ) >= other;
}


bool BoundColumnUnsignedChar::operator >= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator >= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const BigintValue& other ) const
{
	return BigintValue( static_cast< NI >( *userData_ ) ) < other;
}


bool BoundColumnUnsignedChar::operator < ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const DecimalValue& other ) const
{
	return DecimalValue( static_cast< NI >( *userData_ ) ) < other;
}


bool BoundColumnUnsignedChar::operator < ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) < other;
}


bool BoundColumnUnsignedChar::operator < ( const IntegerValue& other ) const
{
	return IntegerValue( static_cast< NI >( *userData_ ) ) < other;
}


bool BoundColumnUnsignedChar::operator < ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) < other;
}


bool BoundColumnUnsignedChar::operator < ( const SmallintValue& other ) const
{
	return SmallintValue( static_cast< NI >( *userData_ ) ) < other;
}


bool BoundColumnUnsignedChar::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const TinyintValue& other ) const
{
	return TinyintValue( static_cast< NI >( *userData_ ) ) < other;
}


bool BoundColumnUnsignedChar::operator < ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator < ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const BigintValue& other ) const
{
	return BigintValue( static_cast< NI >( *userData_ ) ) <= other;
}


bool BoundColumnUnsignedChar::operator <= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const DecimalValue& other ) const
{
	return DecimalValue( static_cast< NI >( *userData_ ) ) <= other;
}


bool BoundColumnUnsignedChar::operator <= ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) <= other;
}


bool BoundColumnUnsignedChar::operator <= ( const IntegerValue& other ) const
{
	return IntegerValue( static_cast< NI >( *userData_ ) ) <= other;
}


bool BoundColumnUnsignedChar::operator <= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) <= other;
}


bool BoundColumnUnsignedChar::operator <= ( const SmallintValue& other ) const
{
	return SmallintValue( static_cast< NI >( *userData_ ) ) <= other;
}


bool BoundColumnUnsignedChar::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const TinyintValue& other ) const
{
	return TinyintValue( static_cast< NI >( *userData_ ) ) <= other;
}


bool BoundColumnUnsignedChar::operator <= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnUnsignedChar::operator <= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


void BoundColumnUnsignedChar::operator >> ( BigintValue& dest )
{
	dest = BigintValue( static_cast< NI >( *userData_ ) );
}


void BoundColumnUnsignedChar::operator << ( BigintValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnUnsignedChar::operator >> ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( BitValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( DecimalValue& dest )
{
	dest = DecimalValue( static_cast< NI >( *userData_ ) );
}


void BoundColumnUnsignedChar::operator << ( DecimalValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnUnsignedChar::operator >> ( FloatValue& dest )
{
	dest = FloatValue( static_cast< NI >( *userData_ ) );
}


void BoundColumnUnsignedChar::operator << ( FloatValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnUnsignedChar::operator >> ( IntegerValue& dest )
{
	dest = IntegerValue( static_cast< NI >( *userData_ ) );
}


void BoundColumnUnsignedChar::operator << ( IntegerValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnUnsignedChar::operator >> ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( RealValue& dest )
{
	dest = RealValue( static_cast< NI >( *userData_ ) );
}


void BoundColumnUnsignedChar::operator << ( RealValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnUnsignedChar::operator >> ( SmallintValue& dest )
{
	dest = SmallintValue( static_cast< NI >( *userData_ ) );
}


void BoundColumnUnsignedChar::operator << ( SmallintValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnUnsignedChar::operator >> ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( TinyintValue& dest )
{
	dest = TinyintValue( static_cast< NI >( *userData_ ) );
}


void BoundColumnUnsignedChar::operator << ( TinyintValue& source )
{
	*userData_ = source.asChar();
}


void BoundColumnUnsignedChar::operator >> ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator >> ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnUnsignedChar::operator << ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}
