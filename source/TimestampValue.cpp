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


const UL TimestampValue::fixedLength_ = sizeof( S ) + sizeof( US ) + sizeof( US ) + sizeof( US ) + sizeof( US ) + sizeof( US ) + sizeof( UL );


TimestampValue::TimestampValue( const TimestampValue& other )
	: AbstractValue( CQL_TIMESTAMP )
{
	timestampLiteral_.year_ = other.timestampLiteral_.year_;
	timestampLiteral_.month_ = other.timestampLiteral_.month_;
	timestampLiteral_.day_ = other.timestampLiteral_.day_;
	timestampLiteral_.hour_ = other.timestampLiteral_.hour_;
	timestampLiteral_.minute_ = other.timestampLiteral_.minute_;
	timestampLiteral_.second_ = other.timestampLiteral_.second_;
	timestampLiteral_.fraction_ = other.timestampLiteral_.fraction_;

	if( const_cast< TimestampValue& >( other ).nullflag() )
		setNullflag();
}


TimestampValue::TimestampValue( pUC& source ) : AbstractValue( CQL_TIMESTAMP )
{
	memcpy( &timestampLiteral_.year_, source, sizeof( timestampLiteral_.year_ ) );
	source += timestampLiteral_.year_;
	memcpy( &timestampLiteral_.month_, source, sizeof( timestampLiteral_.month_ ) );
	source += timestampLiteral_.month_;
	memcpy( &timestampLiteral_.day_, source, sizeof( timestampLiteral_.day_ ) );
	source += timestampLiteral_.day_;
	memcpy( &timestampLiteral_.hour_, source, sizeof( timestampLiteral_.hour_ ) );
	source += timestampLiteral_.hour_;
	memcpy( &timestampLiteral_.minute_, source, sizeof( timestampLiteral_.minute_ ) );
	source += timestampLiteral_.minute_;
	memcpy( &timestampLiteral_.second_, source, sizeof( timestampLiteral_.second_ ) );
	source += timestampLiteral_.second_;
	memcpy( &timestampLiteral_.fraction_, source, sizeof( timestampLiteral_.fraction_ ) );
	source += timestampLiteral_.fraction_;
}


TimestampValue::TimestampValue( const CqlColumnTypes& )
	: AbstractValue( CQL_TIMESTAMP )
{
	timestampLiteral_.year_ = 0;
	timestampLiteral_.month_ = 0;
	timestampLiteral_.day_ = 0;
	timestampLiteral_.hour_ = 0;
	timestampLiteral_.minute_ = 0;
	timestampLiteral_.second_ = 0;
	timestampLiteral_.fraction_ = 0;
}


TimestampValue::TimestampValue( const DateValue& dv ) : AbstractValue( CQL_TIMESTAMP )
{
	timestampLiteral_.hour_ = 0;
	timestampLiteral_.minute_ = 0;
	timestampLiteral_.second_ = 0;
	timestampLiteral_.fraction_ = 0;
	timestampLiteral_.year_ = dv.year();
	timestampLiteral_.month_ = dv.month();
	timestampLiteral_.day_ = dv.day();
}


TimestampValue::TimestampValue( const TimeValue& tv ) : AbstractValue( CQL_TIMESTAMP )
{
	timestampLiteral_.year_ = 0;
	timestampLiteral_.month_ = 0;
	timestampLiteral_.day_ = 0;
	timestampLiteral_.fraction_ = 0;
	timestampLiteral_.hour_ = tv.hour();
	timestampLiteral_.minute_ = tv.minute();
	timestampLiteral_.second_ = tv.second();
}


TimestampValue::TimestampValue( const NC *str ) : AbstractValue( CQL_TIMESTAMP )
{
	// Assumes YYYY/MM/DD HH:MM:SS.fraction

	NC buf[ 30 ];

	//  get and decode year
	memcpy( buf, str, 4 );
	buf[ 4 ] = 0;
	str += 5;  // four digits, plus separator (typically /)
	NI i;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.year_ = static_cast< S >( i );

	//  get and decode month
	memcpy( buf, str, 2 );
	buf[ 2 ] = 0;
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.month_ = static_cast< US >( i );

	//  get and decode day
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.day_ = static_cast< US >( i );

	//  get and decode hour
	memcpy( buf, str, 2 );
	str += 3;  // two digits, plus separator
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.hour_ = static_cast< US >( i );

	//  get and decode minute;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.minute_ = static_cast< US >( i );

	//  get and decode second;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.second_ = static_cast< US >( i );

	//  get and decode fraction.  The rest of the string is the fraction.
	strcpy( buf, str );
	if( sscanf( buf, "%lu", &timestampLiteral_.fraction_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


TimestampValue::TimestampValue( const UC *ustr ) : AbstractValue( CQL_TIMESTAMP )
{
	const NC *str = reinterpret_cast< const NC* >( ustr );

	// Assumes YYYY/MM/DD HH:MM:SS.fraction

	NC buf[ 30 ];

	//  get and decode year
	memcpy( buf, str, 4 );
	buf[ 4 ] = 0;
	str += 5;  // four digits, plus separator (typically /)
	NI i;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.year_ = static_cast< S >( i );

	//  get and decode month
	memcpy( buf, str, 2 );
	buf[ 2 ] = 0;
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.month_ = static_cast< US >( i );

	//  get and decode day
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.day_ = static_cast< US >( i );

	//  get and decode hour
	memcpy( buf, str, 2 );
	str += 3;  // two digits, plus separator
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.hour_ = static_cast< US >( i );

	//  get and decode minute;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.minute_ = static_cast< US >( i );

	//  get and decode second;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.second_ = static_cast< US >( i );

	//  get and decode fraction.  The rest of the string is the fraction.
	strcpy( buf, str );
	if( sscanf( buf, "%lu", &timestampLiteral_.fraction_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


TimestampValue::TimestampValue( const CqlString& s ) : AbstractValue( CQL_TIMESTAMP )
{
	const char *str = const_cast<const char *>(s.text());

	// Assumes YYYY/MM/DD HH:MM:SS.fraction

	NC buf[ 30 ];

	//  get and decode year
	memcpy( buf, str, 4 );
	buf[ 4 ] = 0;
	NI i;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.year_ = static_cast< S >( i );
	str += 5;  // four digits, plus separator (typically /)

	//  get and decode month
	memcpy( buf, str, 2 );
	buf[ 2 ] = 0;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.month_ = static_cast< US >( i );
	str += 3;

	//  get and decode day
	memcpy( buf, str, 2 );
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.day_ = static_cast< US >( i );

	//  get and decode hour
	memcpy( buf, str, 2 );
	str += 3;  // two digits, plus separator
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.hour_ = static_cast< US >( i );

	//  get and decode minute;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.minute_ = static_cast< US >( i );

	//  get and decode second;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timestampLiteral_.second_ = static_cast< US >( i );

	//  get and decode fraction.  The rest of the string is the fraction.
	strcpy( buf, str );
	if( sscanf( buf, "%lu", &timestampLiteral_.fraction_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


TimestampValue::TimestampValue( const NC ) : AbstractValue( CQL_TIMESTAMP )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimestampValue::TimestampValue( const D ) : AbstractValue( CQL_TIMESTAMP )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimestampValue::TimestampValue( const NI ) : AbstractValue( CQL_TIMESTAMP )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimestampValue::TimestampValue( const UNI ) : AbstractValue( CQL_TIMESTAMP )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimestampValue::TimestampValue( const US ) : AbstractValue( CQL_TIMESTAMP )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimestampValue::TimestampValue( const UL ) : AbstractValue( CQL_TIMESTAMP )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimestampValue& TimestampValue::operator = ( const TimestampValue& other )
{
	timestampLiteral_.year_ = other.timestampLiteral_.year_;
	timestampLiteral_.month_ = other.timestampLiteral_.month_;
	timestampLiteral_.day_ = other.timestampLiteral_.day_;
	timestampLiteral_.hour_ = other.timestampLiteral_.hour_;
	timestampLiteral_.minute_ = other.timestampLiteral_.minute_;
	timestampLiteral_.second_ = other.timestampLiteral_.second_;
	timestampLiteral_.fraction_ = other.timestampLiteral_.fraction_;
	TimestampValue& ncother = const_cast< TimestampValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


AbstractValue& TimestampValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_DATE :
		{
			DateValue& dv = dynamic_cast< DateValue& >( av );
			timestampLiteral_.year_ = dv.year();
			timestampLiteral_.month_ = dv.month();
			timestampLiteral_.day_ = dv.day();
			timestampLiteral_.hour_ = timestampLiteral_.minute_ = timestampLiteral_.second_ = 0;
			timestampLiteral_.fraction_ = 0;
		}
		break;

	case CQL_TIME :
		{
			TimeValue& tv = dynamic_cast< TimeValue& >( av );
			timestampLiteral_.year_ = timestampLiteral_.month_ = timestampLiteral_.day_ = 0;
			timestampLiteral_.fraction_ = 0;
			timestampLiteral_.hour_ = tv.hour();
			timestampLiteral_.minute_ = tv.minute();
			timestampLiteral_.second_ = tv.second();
		}
		break;

	case CQL_TIMESTAMP :
		{
			TimestampValue& tv = dynamic_cast< TimestampValue& >( av );
			*this = tv;
		}
		break;

	case CQL_CHAR :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
	case CQL_CHARUC :
	case CQL_DECIMAL :
	case CQL_BIGINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_REAL :
	case CQL_FLOAT :
	case CQL_BIT :
	case CQL_TINYINT :
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	return *this;
}


CqlConstants::CompareResult TimestampValue::compare( const TimestampValue& other ) const
{
	if( timestampLiteral_.year_ > other.timestampLiteral_.year_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timestampLiteral_.year_ < other.timestampLiteral_.year_ )
		return THIS_LESS_THAN_OTHER;
	else if( timestampLiteral_.month_ > other.timestampLiteral_.month_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timestampLiteral_.month_ < other.timestampLiteral_.month_ )
		return THIS_LESS_THAN_OTHER;
	else if( timestampLiteral_.day_ > other.timestampLiteral_.day_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timestampLiteral_.day_ < other.timestampLiteral_.day_ )
		return THIS_LESS_THAN_OTHER;
	else if( timestampLiteral_.hour_ > other.timestampLiteral_.hour_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timestampLiteral_.hour_ < other.timestampLiteral_.hour_ )
		return THIS_LESS_THAN_OTHER;
	else if( timestampLiteral_.minute_ > other.timestampLiteral_.minute_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timestampLiteral_.minute_ < other.timestampLiteral_.minute_ )
		return THIS_LESS_THAN_OTHER;
	else if( timestampLiteral_.second_ > other.timestampLiteral_.second_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timestampLiteral_.second_ < other.timestampLiteral_.second_ )
		return THIS_LESS_THAN_OTHER;
	else if( timestampLiteral_.fraction_ > other.timestampLiteral_.fraction_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timestampLiteral_.fraction_ < other.timestampLiteral_.fraction_ )
		return THIS_LESS_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


bool TimestampValue::operator == ( const TimestampValue& other ) const
{
	return compare( other ) == THIS_EQUAL_TO_OTHER;
}


bool TimestampValue::operator == ( const AbstractValue& other ) const
{
	TimestampValue val = other.asTimestampValue();

	return *this == val;
//	return *this == other.asTimestampValue();
}


bool TimestampValue::operator != ( const AbstractValue& other ) const
{
	TimestampValue val = other.asTimestampValue();

//	if( *this == other.asTimestampValue() )
	if( *this == val )
		return false;
	else
		return true;
}


bool TimestampValue::operator > ( const TimestampValue& other ) const
{
	return compare( other ) == THIS_GREATER_THAN_OTHER;
}


bool TimestampValue::operator > ( const AbstractValue& other ) const
{
	TimestampValue val = other.asTimestampValue();

	return *this > val;
//	return *this > other.asTimestampValue();
}


bool TimestampValue::operator >= ( const TimestampValue& other ) const
{
	return compare( other ) != THIS_LESS_THAN_OTHER;
}


bool TimestampValue::operator >= ( const AbstractValue& other ) const
{
	TimestampValue val = other.asTimestampValue();

	return *this >= val;
//	return *this >= other.asTimestampValue();
}


bool TimestampValue::operator < ( const TimestampValue& other ) const
{
	return compare( other ) == THIS_LESS_THAN_OTHER;
}


bool TimestampValue::operator < ( const AbstractValue& other ) const
{
	TimestampValue val = other.asTimestampValue();

	return *this < val;
//	return *this < other.asTimestampValue();
}


bool TimestampValue::operator <= ( const TimestampValue& other ) const
{
	return compare( other ) != THIS_GREATER_THAN_OTHER;
}


bool TimestampValue::operator <= ( const AbstractValue& other ) const
{
	TimestampValue val = other.asTimestampValue();

	return *this <= val;
//	return *this <= other.asTimestampValue();
}


bool TimestampValue::operator ! ( void ) const
{
	if( !timestampLiteral_.year_ && !timestampLiteral_.month_ && !timestampLiteral_.day_ && !timestampLiteral_.hour_ && !timestampLiteral_.minute_ && !timestampLiteral_.second_ && !timestampLiteral_.fraction_ )
		return true;
	else
		return false;
}


void TimestampValue::output( TempBuffer& tb ) const
{
	tb << timestampLiteral_.year_ << timestampLiteral_.month_ << timestampLiteral_.day_ << timestampLiteral_.hour_ << timestampLiteral_.minute_ << timestampLiteral_.second_ << timestampLiteral_.fraction_;
}


void TimestampValue::input( TempBuffer& tb )
{
	tb >> timestampLiteral_.year_ >> timestampLiteral_.month_ >> timestampLiteral_.day_ >> timestampLiteral_.hour_ >> timestampLiteral_.minute_ >> timestampLiteral_.second_ >> timestampLiteral_.fraction_;
}


UL TimestampValue::length( void ) const
{
	return sizeof( TimestampValue );
}


UL TimestampValue::streamLength( void ) const
{
	return fixedLength_;
}


NC TimestampValue::asChar() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


S TimestampValue::asShort() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


L TimestampValue::asLong() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


BigintValue TimestampValue::asBigintValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return BigintValue();
#endif
}


DecimalValue TimestampValue::asDecimalValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DecimalValue();
#endif
}


F TimestampValue::asFloat() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


D TimestampValue::asDouble() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


DateValue TimestampValue::asDateValue() const
{
#ifdef __CQL_SOLARIS
	DateValue dv;
	dv = *this;
#else
	DateValue dv( *this );
#endif

	return dv;
}


TimeValue TimestampValue::asTimeValue() const
{
#ifdef __CQL_SOLARIS
	TimeValue tv;
	tv = *this;
#else
	TimeValue tv( *this );
#endif

	return tv;
}


TimestampValue TimestampValue::asTimestampValue() const
{
	return *this;
}


const CqlString TimestampValue::asString( bool /* spacePadding */ ) const
{
	NC buffer[ 50 ];
	sprintf( buffer, "%02d/%02d/%04d %02d:%02d:%02d.%03ld", timestampLiteral_.month_, timestampLiteral_.day_, timestampLiteral_.year_, timestampLiteral_.hour_, timestampLiteral_.minute_, timestampLiteral_.second_, timestampLiteral_.fraction_ );
	return CqlString( buffer );
}


void TimestampValue::operator << ( pUC& buf )
{
	memcpy( &timestampLiteral_.year_, buf, sizeof( timestampLiteral_.year_ ) );
	buf += sizeof( timestampLiteral_.year_ );
	memcpy( &timestampLiteral_.month_, buf, sizeof( timestampLiteral_.month_ ) );
	buf += sizeof( timestampLiteral_.month_ );
	memcpy( &timestampLiteral_.day_, buf, sizeof( timestampLiteral_.day_ ) );
	buf += sizeof( timestampLiteral_.day_ );
	memcpy( &timestampLiteral_.hour_, buf, sizeof( timestampLiteral_.hour_ ) );
	buf += sizeof( timestampLiteral_.hour_ );
	memcpy( &timestampLiteral_.minute_, buf, sizeof( timestampLiteral_.minute_ ) );
	buf += sizeof( timestampLiteral_.minute_ );
	memcpy( &timestampLiteral_.second_, buf, sizeof( timestampLiteral_.second_ ) );
	buf += sizeof( timestampLiteral_.second_ );
	memcpy( &timestampLiteral_.fraction_, buf, sizeof( timestampLiteral_.fraction_ ) );
	buf += sizeof( timestampLiteral_.fraction_ );
}


void TimestampValue::operator >> ( pUC& buf )
{
	memcpy( buf, &timestampLiteral_.year_, sizeof( timestampLiteral_.year_ ) );
	buf += sizeof( timestampLiteral_.year_ );
	memcpy( buf, &timestampLiteral_.month_, sizeof( timestampLiteral_.month_ ) );
	buf += sizeof( timestampLiteral_.month_ );
	memcpy( buf, &timestampLiteral_.day_, sizeof( timestampLiteral_.day_ ) );
	buf += sizeof( timestampLiteral_.day_ );
	memcpy( buf, &timestampLiteral_.hour_, sizeof( timestampLiteral_.hour_ ) );
	buf += sizeof( timestampLiteral_.hour_ );
	memcpy( buf, &timestampLiteral_.minute_, sizeof( timestampLiteral_.minute_ ) );
	buf += sizeof( timestampLiteral_.minute_ );
	memcpy( buf, &timestampLiteral_.second_, sizeof( timestampLiteral_.second_ ) );
	buf += sizeof( timestampLiteral_.second_ );
	memcpy( buf, &timestampLiteral_.fraction_, sizeof( timestampLiteral_.fraction_ ) );
	buf += sizeof( timestampLiteral_.fraction_ );
}


void TimestampValue::operator >> ( BinaryValue& bv )
{
	UC _length = sizeof( timestampLiteral_.year_ ) + sizeof( timestampLiteral_.month_ ) + sizeof( timestampLiteral_.day_ ) + sizeof( timestampLiteral_.hour_ ) + sizeof( timestampLiteral_.minute_ ) + sizeof( timestampLiteral_.second_ ) + sizeof( timestampLiteral_.fraction_ );
	UC *buf = new UC[ _length ];
	if( !buf )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	UC *bufBase = buf;

	*this >> buf;
	bv = BinaryValue( bufBase, _length );
	delete bufBase;
}


void TimestampValue::operator << ( BinaryValue& bv )
{
	UC *p = bv.buffer();
	*this << p;
}


void TimestampValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void TimestampValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void TimestampValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void TimestampValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& TimestampValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& TimestampValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& TimestampValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& TimestampValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


void TimestampValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << timestampLiteral_.year_ << timestampLiteral_.month_ << timestampLiteral_.day_ << timestampLiteral_.hour_ << timestampLiteral_.minute_ << timestampLiteral_.second_ << timestampLiteral_.fraction_;
}


void TimestampValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> timestampLiteral_.year_ >> timestampLiteral_.month_ >> timestampLiteral_.day_ >> timestampLiteral_.hour_ >> timestampLiteral_.minute_ >> timestampLiteral_.second_ >> timestampLiteral_.fraction_;
}


US TimestampValue::dictionaryLength( void )
{
	return static_cast< US >( sizeof( bool ) + sizeof( timestampLiteral_.year_ ) + sizeof( timestampLiteral_.month_ ) + sizeof( timestampLiteral_.day_ ) + sizeof( timestampLiteral_.hour_ ) + sizeof( timestampLiteral_.minute_ ) + sizeof( timestampLiteral_.second_ ) + sizeof( timestampLiteral_.fraction_ ) );
}


void TimestampValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	_output = asString();
}


void TimestampValue::setToCurrentTimestamp( void )
{
	hAEnv->getCurrentTimestamp( timestampLiteral_.year_, timestampLiteral_.month_, timestampLiteral_.day_, timestampLiteral_.hour_, timestampLiteral_.minute_, timestampLiteral_.second_, timestampLiteral_.fraction_ );
}
