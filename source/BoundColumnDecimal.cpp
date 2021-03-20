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


BoundColumnDecimal::BoundColumnDecimal( AbstractColumnDescriptor* _col ) : BoundColumn( _col ), userData_( 0 )
{
}


BoundColumnDecimal::BoundColumnDecimal( const BoundColumnDecimal& other ) : BoundColumn( other )
{
	userData_ = other.userData_;
}


BoundColumnDecimal::~BoundColumnDecimal( void )
{
}


bool BoundColumnDecimal::operator == ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) == other;
}


bool BoundColumnDecimal::operator == ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const DecimalValue& other ) const
{
	return *userData_ == other;
}


bool BoundColumnDecimal::operator == ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) == other;
}


bool BoundColumnDecimal::operator == ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) == other;
}


bool BoundColumnDecimal::operator == ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const RealValue& other ) const
{
	return RealValue( *userData_ ) == other;
}


bool BoundColumnDecimal::operator == ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) == other;
}


bool BoundColumnDecimal::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) == other;
}


bool BoundColumnDecimal::operator == ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator == ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) > other;
}


bool BoundColumnDecimal::operator > ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const DecimalValue& other ) const
{
	return *userData_ > other;
}


bool BoundColumnDecimal::operator > ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) > other;
}


bool BoundColumnDecimal::operator > ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) > other;
}


bool BoundColumnDecimal::operator > ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const RealValue& other ) const
{
	return RealValue( *userData_ ) > other;
}


bool BoundColumnDecimal::operator > ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) > other;
}


bool BoundColumnDecimal::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) > other;
}


bool BoundColumnDecimal::operator > ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator > ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) >= other;
}


bool BoundColumnDecimal::operator >= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const DecimalValue& other ) const
{
	return *userData_ >= other;
}


bool BoundColumnDecimal::operator >= ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) >= other;
}


bool BoundColumnDecimal::operator >= ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) >= other;
}


bool BoundColumnDecimal::operator >= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const RealValue& other ) const
{
	return RealValue( *userData_ ) >= other;
}


bool BoundColumnDecimal::operator >= ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) >= other;
}


bool BoundColumnDecimal::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) >= other;
}


bool BoundColumnDecimal::operator >= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator >= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) < other;
}


bool BoundColumnDecimal::operator < ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const DecimalValue& other ) const
{
	return *userData_ < other;
}


bool BoundColumnDecimal::operator < ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) < other;
}


bool BoundColumnDecimal::operator < ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) < other;
}


bool BoundColumnDecimal::operator < ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const RealValue& other ) const
{
	return RealValue( *userData_ ) < other;
}


bool BoundColumnDecimal::operator < ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) < other;
}


bool BoundColumnDecimal::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) < other;
}


bool BoundColumnDecimal::operator < ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator < ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) <= other;
}


bool BoundColumnDecimal::operator <= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const DecimalValue& other ) const
{
	return *userData_ <= other;
}


bool BoundColumnDecimal::operator <= ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) <= other;
}


bool BoundColumnDecimal::operator <= ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) <= other;
}


bool BoundColumnDecimal::operator <= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const RealValue& other ) const
{
	return RealValue( *userData_ ) <= other;
}


bool BoundColumnDecimal::operator <= ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) <= other;
}


bool BoundColumnDecimal::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) <= other;
}


bool BoundColumnDecimal::operator <= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnDecimal::operator <= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


void BoundColumnDecimal::operator >> ( BigintValue& dest )
{
	dest = BigintValue( *userData_ );
}


void BoundColumnDecimal::operator << ( BigintValue& source )
{
	*userData_ = DecimalValue( source );
}


void BoundColumnDecimal::operator >> ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( BitValue& bv )
{
	if( bv.pvalue() )
		*userData_ = DecimalValue( 1 );
	else
		*userData_ = DecimalValue( 0 );
}


void BoundColumnDecimal::operator >> ( BitValue& bv )
{
	if( !userData_ )
		bv.clearPvalue();
	else
		bv.setPvalue();
}


void BoundColumnDecimal::operator >> ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator >> ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator >> ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator >> ( DecimalValue& dest )
{
	dest = *userData_;
}


void BoundColumnDecimal::operator << ( DecimalValue& source )
{
	*userData_ = source;
}


void BoundColumnDecimal::operator >> ( FloatValue& dest )
{
	dest = FloatValue( *userData_ );
}


void BoundColumnDecimal::operator << ( FloatValue& source )
{
	*userData_ = source;
}


void BoundColumnDecimal::operator >> ( IntegerValue& dest )
{
	dest = IntegerValue( *userData_ );
}


void BoundColumnDecimal::operator << ( IntegerValue& source )
{
	*userData_ = DecimalValue( source );
}


void BoundColumnDecimal::operator >> ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator >> ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator >> ( RealValue& dest )
{
	dest = RealValue( *userData_ );
}


void BoundColumnDecimal::operator << ( RealValue& source )
{
	*userData_ = source;
}


void BoundColumnDecimal::operator >> ( SmallintValue& dest )
{
	dest = SmallintValue( *userData_ );
}


void BoundColumnDecimal::operator << ( SmallintValue& source )
{
	*userData_ = DecimalValue( source );
}


void BoundColumnDecimal::operator >> ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator >> ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator >> ( TinyintValue& dest )
{
	dest = TinyintValue( *userData_ );
}


void BoundColumnDecimal::operator << ( TinyintValue& source )
{
	*userData_ = DecimalValue( source );
}


void BoundColumnDecimal::operator >> ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator >> ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnDecimal::operator << ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}
