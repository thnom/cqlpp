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


BoundColumnShort::BoundColumnShort( AbstractColumnDescriptor* _col ) : BoundColumn( _col ), userData_( 0 )
{
}


BoundColumnShort::BoundColumnShort( const BoundColumnShort& other ) : BoundColumn( other )
{
	userData_ = other.userData_;
}


BoundColumnShort::~BoundColumnShort( void )
{
}

	
bool BoundColumnShort::operator == ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) == other;
}


bool BoundColumnShort::operator == ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) == other;
}


bool BoundColumnShort::operator == ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) == other;
}


bool BoundColumnShort::operator == ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) == other;
}


bool BoundColumnShort::operator == ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) == other;
}


bool BoundColumnShort::operator == ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) == other;
}


bool BoundColumnShort::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) == other;
}


bool BoundColumnShort::operator == ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator == ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) > other;
}


bool BoundColumnShort::operator > ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) > other;
}


bool BoundColumnShort::operator > ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) > other;
}


bool BoundColumnShort::operator > ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) > other;
}


bool BoundColumnShort::operator > ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) > other;
}


bool BoundColumnShort::operator > ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) > other;
}


bool BoundColumnShort::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) > other;
}


bool BoundColumnShort::operator > ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator > ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) >= other;
}


bool BoundColumnShort::operator >= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) >= other;
}


bool BoundColumnShort::operator >= ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) >= other;
}


bool BoundColumnShort::operator >= ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) >= other;
}


bool BoundColumnShort::operator >= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) >= other;
}


bool BoundColumnShort::operator >= ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) >= other;
}


bool BoundColumnShort::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) >= other;
}


bool BoundColumnShort::operator >= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator >= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) < other;
}


bool BoundColumnShort::operator < ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) < other;
}


bool BoundColumnShort::operator < ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) < other;
}


bool BoundColumnShort::operator < ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) < other;
}


bool BoundColumnShort::operator < ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) < other;
}


bool BoundColumnShort::operator < ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) < other;
}


bool BoundColumnShort::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) < other;
}


bool BoundColumnShort::operator < ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator < ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) <= other;
}


bool BoundColumnShort::operator <= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) <= other;
}


bool BoundColumnShort::operator <= ( const FloatValue& other ) const
{
	return FloatValue( static_cast< L >( *userData_ ) ) <= other;
}


bool BoundColumnShort::operator <= ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) <= other;
}


bool BoundColumnShort::operator <= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const RealValue& other ) const
{
	return RealValue( static_cast< L >( *userData_ ) ) <= other;
}


bool BoundColumnShort::operator <= ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) <= other;
}


bool BoundColumnShort::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) <= other;
}


bool BoundColumnShort::operator <= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnShort::operator <= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


void BoundColumnShort::operator >> ( BigintValue& dest )
{
	dest = BigintValue( *userData_ );
}


void BoundColumnShort::operator << ( BigintValue& source )
{
	*userData_ = source.asShort();
}


void BoundColumnShort::operator >> ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( BitValue& bv )
{
	if( bv.pvalue() )
		*userData_ = 1;
	else
		*userData_ = 0;
}


void BoundColumnShort::operator >> ( BitValue& bv )
{
	if( *userData_ )
		bv.setPvalue();
	else
		bv.clearPvalue();
}


void BoundColumnShort::operator >> ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator >> ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator >> ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator >> ( DecimalValue& dest )
{
	dest = DecimalValue( *userData_ );
}


void BoundColumnShort::operator << ( DecimalValue& source )
{
	*userData_ = source.asShort();
}


void BoundColumnShort::operator >> ( FloatValue& dest )
{
	dest = FloatValue( *userData_ );
}


void BoundColumnShort::operator << ( FloatValue& source )
{
	*userData_ = source.asShort();
}


void BoundColumnShort::operator >> ( IntegerValue& dest )
{
	dest = IntegerValue( *userData_ );
}


void BoundColumnShort::operator << ( IntegerValue& source )
{
	*userData_ = source.asShort();
}


void BoundColumnShort::operator >> ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator >> ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator >> ( RealValue& dest )
{
	dest = RealValue( *userData_ );
}


void BoundColumnShort::operator << ( RealValue& source )
{
	*userData_ = source.asShort();
}


void BoundColumnShort::operator >> ( SmallintValue& dest )
{
	dest = SmallintValue( *userData_ );
}


void BoundColumnShort::operator << ( SmallintValue& source )
{
	*userData_ = source.asShort();
}


void BoundColumnShort::operator >> ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator >> ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator >> ( TinyintValue& dest )
{
	dest = TinyintValue( *userData_ );
}


void BoundColumnShort::operator << ( TinyintValue& source )
{
	*userData_ = source.asShort();
}


void BoundColumnShort::operator >> ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator >> ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnShort::operator << ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}
