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


BoundColumnString::BoundColumnString( AbstractColumnDescriptor* _col ) : BoundColumn( _col ), userData_( 0 )
{
}


BoundColumnString::BoundColumnString( const BoundColumnString& other ) : BoundColumn( other )
{
	userData_ = other.userData_;
}


BoundColumnString::~BoundColumnString( void )
{
}


bool BoundColumnString::operator == ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const CharValue& other ) const
{
	return *userData_ == other.value();
}


bool BoundColumnString::operator == ( const CharUCValue& other ) const
{
	return *userData_ == other.value();
}


bool BoundColumnString::operator == ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const LongvarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnString::operator == ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator == ( const VarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnString::operator > ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const CharValue& other ) const
{
	return *userData_ > other.value();
}


bool BoundColumnString::operator > ( const CharUCValue& other ) const
{
	return *userData_ > other.value();
}


bool BoundColumnString::operator > ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const LongvarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnString::operator > ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator > ( const VarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnString::operator >= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const CharValue& other ) const
{
	return *userData_ >= other.value();
}


bool BoundColumnString::operator >= ( const CharUCValue& other ) const
{
	return *userData_ >= other.value();
}


bool BoundColumnString::operator >= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const LongvarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnString::operator >= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator >= ( const VarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnString::operator < ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const CharValue& other ) const
{
	return *userData_ < other.value();
}


bool BoundColumnString::operator < ( const CharUCValue& other ) const
{
	return *userData_ < other.value();
}


bool BoundColumnString::operator < ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const LongvarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnString::operator < ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator < ( const VarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnString::operator <= ( const BigintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const BinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const BitValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const CharValue& other ) const
{
	return *userData_ <= other.value();
}


bool BoundColumnString::operator <= ( const CharUCValue& other ) const
{
	return *userData_ <= other.value();
}


bool BoundColumnString::operator <= ( const DateValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const DecimalValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const FloatValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const IntegerValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const LongvarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const LongvarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


bool BoundColumnString::operator <= ( const RealValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const SmallintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const TimeValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const TimestampValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const TinyintValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const VarbinaryValue& ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for moronic compilers
	return false;
#endif
}


bool BoundColumnString::operator <= ( const VarcharValue& other ) const
{
	if( userData_->length() != other.length() )
		return false;

	if( strcmp( userData_->text(), other.buffer() ) )
		return false;

	return true;
}


void BoundColumnString::operator >> ( BigintValue& )
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
}


void BoundColumnString::operator << ( BigintValue& val )
{
	*userData_ = CqlString( val.asString() );
}


void BoundColumnString::operator >> ( BinaryValue& dest )
{
	dest = BinaryValue( *userData_ );
}


void BoundColumnString::operator << ( BinaryValue& source )
{
	*userData_ = CqlString( reinterpret_cast< NC* >( source.buffer() ), source.length() );
}


void BoundColumnString::operator << ( BitValue& val )
{
	*userData_ = val.asString();
}


void BoundColumnString::operator >> ( BitValue& dest )
{
	dest = BitValue( *userData_ );
}


void BoundColumnString::operator >> ( CharValue& dest )
{
	dest = CharValue( *userData_, static_cast< UC >( dest.typeLength() ) );
}


void BoundColumnString::operator << ( CharValue& source )
{
	*userData_ = source.value();
}


void BoundColumnString::operator >> ( CharUCValue& dest )
{
	dest = CharUCValue( *userData_ );
}


void BoundColumnString::operator << ( CharUCValue& source )
{
	*userData_ = source.value();
}


void BoundColumnString::operator >> ( DateValue& dest )
{
	dest = DateValue( *userData_ );
}


void BoundColumnString::operator << ( DateValue& val )
{
	*userData_ = val.asString();
}


void BoundColumnString::operator >> ( DecimalValue& dest )
{
	dest = DecimalValue( *userData_ );
}


void BoundColumnString::operator << ( DecimalValue& val )
{
	*userData_ = val.asString();
}


void BoundColumnString::operator >> ( FloatValue& dest )
{
	dest = FloatValue( *userData_ );
}


void BoundColumnString::operator << ( FloatValue& val )
{
	*userData_ = val.asString();
}


void BoundColumnString::operator >> ( IntegerValue& dest )
{
	dest = IntegerValue( *userData_ );
}


void BoundColumnString::operator << ( IntegerValue& val )
{
	*userData_ = CqlString( val.asString() );
}


void BoundColumnString::operator >> ( LongvarbinaryValue& dest )
{
	dest = LongvarbinaryValue( *userData_ );
}


void BoundColumnString::operator << ( LongvarbinaryValue& source )
{
	*userData_ = CqlString( reinterpret_cast< NC* >( source.buffer() ), source.length() );
}


void BoundColumnString::operator >> ( LongvarcharValue& dest )
{
	dest = LongvarcharValue( *userData_ );
}


void BoundColumnString::operator << ( LongvarcharValue& source )
{
	*userData_ = CqlString( source.buffer() );
}


void BoundColumnString::operator >> ( RealValue&  dest )
{
	dest = RealValue( *userData_ );
}


void BoundColumnString::operator << ( RealValue& val )
{
	*userData_ = CqlString( val.asString() );
}


void BoundColumnString::operator >> ( SmallintValue& dest )
{
	dest = SmallintValue( *userData_ );
}


void BoundColumnString::operator << ( SmallintValue& val )
{
	*userData_ = CqlString( val.asString() );
}


void BoundColumnString::operator >> ( TimeValue& dest )
{
	dest = TimeValue( *userData_ );
}


void BoundColumnString::operator << ( TimeValue& val )
{
	*userData_ = CqlString( val.asString() );
}


void BoundColumnString::operator >> ( TimestampValue& dest )
{
	dest = TimestampValue( *userData_ );
}


void BoundColumnString::operator << ( TimestampValue& val )
{
	*userData_ = CqlString( val.asString() );
}


void BoundColumnString::operator >> ( TinyintValue& dest )
{
	dest = TinyintValue( *userData_ );
}


void BoundColumnString::operator << ( TinyintValue& val )
{
	*userData_ = CqlString( val.asString() );
}


void BoundColumnString::operator >> ( VarbinaryValue& dest )
{
	dest = VarbinaryValue( *userData_ );
}


void BoundColumnString::operator << ( VarbinaryValue& source )
{
	*userData_ = CqlString( reinterpret_cast< NC * >( source.buffer() ), source.length() );
}


void BoundColumnString::operator >> ( VarcharValue& dest )
{
	dest = VarcharValue( *userData_ );
}


void BoundColumnString::operator << ( VarcharValue& source )
{
	*userData_ = CqlString( source.buffer() );
}
