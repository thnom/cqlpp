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


BoundColumnFloat::BoundColumnFloat( AbstractColumnDescriptor* _col ) : BoundColumn( _col ), userData_( 0 )
{
}


BoundColumnFloat::BoundColumnFloat( const BoundColumnFloat& other ) : BoundColumn( other )
{
	userData_ = other.userData_;
}


BoundColumnFloat::~BoundColumnFloat( void )
{
}


bool BoundColumnFloat::operator == ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) == other;
}


bool BoundColumnFloat::operator == ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) == other;
}


bool BoundColumnFloat::operator == ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) == other;
}


bool BoundColumnFloat::operator == ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) == other;
}


bool BoundColumnFloat::operator == ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const RealValue& other ) const
{
	return RealValue( *userData_ ) == other;
}


bool BoundColumnFloat::operator == ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) == other;
}


bool BoundColumnFloat::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) == other;
}


bool BoundColumnFloat::operator == ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator == ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) > other;
}


bool BoundColumnFloat::operator > ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) > other;
}


bool BoundColumnFloat::operator > ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) > other;
}


bool BoundColumnFloat::operator > ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) > other;
}


bool BoundColumnFloat::operator > ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const RealValue& other ) const
{
	return RealValue( *userData_ ) > other;
}


bool BoundColumnFloat::operator > ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) > other;
}


bool BoundColumnFloat::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) > other;
}


bool BoundColumnFloat::operator > ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator > ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) >= other;
}


bool BoundColumnFloat::operator >= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) >= other;
}


bool BoundColumnFloat::operator >= ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) >= other;
}


bool BoundColumnFloat::operator >= ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) >= other;
}


bool BoundColumnFloat::operator >= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const RealValue& other ) const
{
	return RealValue( *userData_ ) >= other;
}


bool BoundColumnFloat::operator >= ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) >= other;
}


bool BoundColumnFloat::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) >= other;
}


bool BoundColumnFloat::operator >= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator >= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) < other;
}


bool BoundColumnFloat::operator < ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) < other;
}


bool BoundColumnFloat::operator < ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) < other;
}


bool BoundColumnFloat::operator < ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) < other;
}


bool BoundColumnFloat::operator < ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const RealValue& other ) const
{
	return RealValue( *userData_ ) < other;
}


bool BoundColumnFloat::operator < ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) < other;
}


bool BoundColumnFloat::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) < other;
}


bool BoundColumnFloat::operator < ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator < ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const BigintValue& other ) const
{
	return BigintValue( *userData_ ) <= other;
}


bool BoundColumnFloat::operator <= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const CharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const CharUCValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const DecimalValue& other ) const
{
	return DecimalValue( *userData_ ) <= other;
}


bool BoundColumnFloat::operator <= ( const FloatValue& other ) const
{
	return FloatValue( *userData_ ) <= other;
}


bool BoundColumnFloat::operator <= ( const IntegerValue& other ) const
{
	return IntegerValue( *userData_ ) <= other;
}


bool BoundColumnFloat::operator <= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const LongvarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const RealValue& other ) const
{
	return RealValue( *userData_ ) <= other;
}


bool BoundColumnFloat::operator <= ( const SmallintValue& other ) const
{
	return SmallintValue( *userData_ ) <= other;
}


bool BoundColumnFloat::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const TinyintValue& other ) const
{
	return TinyintValue( *userData_ ) <= other;
}


bool BoundColumnFloat::operator <= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnFloat::operator <= ( const VarcharValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


void BoundColumnFloat::operator >> ( BigintValue& dest )
{
	dest = BigintValue( static_cast< D >( *userData_ ) );
}


void BoundColumnFloat::operator << ( BigintValue& source )
{
	*userData_ = source.asFloat();
}


void BoundColumnFloat::operator >> ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( BinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( BitValue& bv )
{
	if( bv.pvalue() )
		*userData_ = 1;
	else
		*userData_ = 0;
}


void BoundColumnFloat::operator >> ( BitValue& bv )
{
	if( *userData_ )
		bv.setPvalue();
	else
		bv.clearPvalue();
}


void BoundColumnFloat::operator >> ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( CharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator >> ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( CharUCValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator >> ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( DateValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator >> ( DecimalValue& dest )
{
	dest = DecimalValue( static_cast< F >( *userData_ ) );
}


void BoundColumnFloat::operator << ( DecimalValue& source )
{
	*userData_ = source.asFloat();
}


void BoundColumnFloat::operator >> ( FloatValue& dest )
{
	dest = FloatValue( static_cast< D >( *userData_ ) );
}


void BoundColumnFloat::operator << ( FloatValue& source )
{
	*userData_ = source.asFloat();
}


void BoundColumnFloat::operator >> ( IntegerValue& dest )
{
	dest = IntegerValue( static_cast< L >( *userData_ ) );
}


void BoundColumnFloat::operator << ( IntegerValue& source )
{
	*userData_ = source.asFloat();
}


void BoundColumnFloat::operator >> ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( LongvarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator >> ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( LongvarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator >> ( RealValue& dest )
{
	dest = RealValue( *userData_ );
}


void BoundColumnFloat::operator << ( RealValue& source )
{
	*userData_ = source.asFloat();
}


void BoundColumnFloat::operator >> ( SmallintValue& dest )
{
	dest = SmallintValue( static_cast< S >( *userData_ ) );
}


void BoundColumnFloat::operator << ( SmallintValue& source )
{
	*userData_ = source.asFloat();
}


void BoundColumnFloat::operator >> ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( TimeValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator >> ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( TimestampValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator >> ( TinyintValue& dest )
{
	dest = TinyintValue( static_cast< NC >( *userData_ ) );
}


void BoundColumnFloat::operator << ( TinyintValue& source )
{
	*userData_ = source.asFloat();
}


void BoundColumnFloat::operator >> ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( VarbinaryValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator >> ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnFloat::operator << ( VarcharValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}
