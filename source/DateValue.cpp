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


const UL DateValue::fixedLength_ = sizeof( S ) + sizeof( US ) + sizeof( US );


DateValue::DateValue( const DateValue& other ) : AbstractValue( CQL_DATE )
{
	dateLiteral_.year_ = other.dateLiteral_.year_;
	dateLiteral_.month_ = other.dateLiteral_.month_;
	dateLiteral_.day_ = other.dateLiteral_.day_;
	if( const_cast< DateValue& >( other ).nullflag() )
		setNullflag();
}


DateValue::DateValue( pUC& source ) : AbstractValue( CQL_DATE )
{
	memcpy( &dateLiteral_.year_, source, sizeof( dateLiteral_.year_ ) );
	source += sizeof( dateLiteral_.year_ );
	memcpy( &dateLiteral_.month_, source, sizeof( dateLiteral_.month_ ) );
	source += sizeof( dateLiteral_.month_ );
	memcpy( &dateLiteral_.day_, source, sizeof( dateLiteral_.day_ ) );
	source += sizeof( dateLiteral_.day_ );
}


DateValue::DateValue( const CqlColumnTypes& ) : AbstractValue( CQL_DATE )
{
	dateLiteral_.year_ = 0;
	dateLiteral_.month_ = 0;
	dateLiteral_.day_ = 0;
}


DateValue::DateValue( const TimestampValue& tv ) : AbstractValue( CQL_DATE )
{
	dateLiteral_.year_ = tv.year();
	dateLiteral_.month_ = tv.month();
	dateLiteral_.day_ = tv.day();
}


DateValue::DateValue( const NC *s ) : AbstractValue( CQL_DATE )
{
	//  This needs to be modified for multiple date formats.
	//  Currently assumes YYYY/MM/DD

	NC buf[ 5 ];

	//  get and decode year
	memcpy( buf, s, 4 );
	buf[ 4 ] = 0;
	NI i;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	dateLiteral_.year_ = static_cast< S >( i );
	s += 5;  // four digits, plus separator (typically /)

	//  get and decode month
	memcpy( buf, s, 2 );
	buf[ 2 ] = 0;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	dateLiteral_.month_ = static_cast< US >( i );
	s += 3;

	//  get and decode day
	memcpy( buf, s, 2 );
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	dateLiteral_.day_ = static_cast< US >( i );
}


DateValue::DateValue( const CqlString& str ) : AbstractValue( CQL_DATE )
{
	//  This needs to be modified for multiple date formats.
	//  Currently assumes YYYY/MM/DD

	NC buf[ 5 ];
	const char * s = const_cast<const char *>(str.text());

	//  get and decode year
	memcpy( buf, s, 4 );
	buf[ 4 ] = 0;
	NI i;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	dateLiteral_.year_ = static_cast< S >( i );
	s += 5;  // four digits, plus separator (typically /)

	//  get and decode month
	memcpy( buf, s, 2 );
	buf[ 2 ] = 0;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	dateLiteral_.month_ = static_cast< US >( i );
	s += 3;

	//  get and decode day
	memcpy( buf, s, 2 );
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	dateLiteral_.day_ = static_cast< US >( i );
}


DateValue::DateValue( const UC *usource ) : AbstractValue( CQL_DATE )
{
	const NC *source = reinterpret_cast< const NC* >( usource );
	//  This needs to be modified for multiple date formats.
	//  Currently assumes YYYY/MM/DD

	NC buf[ 5 ];

	//  get and decode year
	memcpy( buf, source, 4 );
	buf[ 4 ] = 0;
	NI i;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	dateLiteral_.year_ = static_cast< S >( i );
	source += 5;  // four digits, plus separator (typically /)

	//  get and decode month
	memcpy( buf, source, 2 );
	buf[ 2 ] = 0;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	dateLiteral_.month_ = static_cast< US >( i );
	source += 3;

	//  get and decode day
	memcpy( buf, source, 2 );
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	dateLiteral_.day_ = static_cast< US >( i );
}


DateValue::DateValue( const NC ) : AbstractValue( CQL_DATE )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


DateValue::DateValue( const D ) : AbstractValue( CQL_DATE )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


DateValue::DateValue( const NI ) : AbstractValue( CQL_DATE )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


DateValue::DateValue( const UNI ) : AbstractValue( CQL_DATE )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


DateValue::DateValue( const US ) : AbstractValue( CQL_DATE )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


DateValue::DateValue( const UL ) : AbstractValue( CQL_DATE )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


DateValue& DateValue::operator = ( const DateValue& other )
{
	dateLiteral_.year_ = other.dateLiteral_.year_;
	dateLiteral_.month_ = other.dateLiteral_.month_;
	dateLiteral_.day_ = other.dateLiteral_.day_;
	DateValue& ncother = const_cast< DateValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


AbstractValue& DateValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_DATE :
		{
			DateValue& dv = dynamic_cast< DateValue& >( av );
			*this = dv;
		}
		break;

	case CQL_TIME :
		dateLiteral_.year_ = 0;
		dateLiteral_.month_ = 0;
		dateLiteral_.day_ = 0;
		break;

	case CQL_TIMESTAMP :
		{
			TimestampValue& tv = dynamic_cast< TimestampValue& >( av );
			*this = DateValue( tv );
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


CqlConstants::CompareResult DateValue::compare( const DateValue& other ) const
{
	if( dateLiteral_.year_ > other.dateLiteral_.year_ )
		return THIS_GREATER_THAN_OTHER;
	else if( dateLiteral_.year_ < other.dateLiteral_.year_ )
		return THIS_LESS_THAN_OTHER;
	else if( dateLiteral_.month_ > other.dateLiteral_.month_ )
		return THIS_GREATER_THAN_OTHER;
	else if( dateLiteral_.month_ < other.dateLiteral_.month_ )
		return THIS_LESS_THAN_OTHER;
	else if( dateLiteral_.day_ > other.dateLiteral_.day_ )
		return THIS_GREATER_THAN_OTHER;
	else if( dateLiteral_.day_ < other.dateLiteral_.day_ )
		return THIS_LESS_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


bool DateValue::operator == ( const DateValue& other ) const
{
	return compare( other ) == THIS_EQUAL_TO_OTHER;
}


bool DateValue::operator == ( const AbstractValue& other ) const
{
	DateValue val = other.asDateValue();

	return *this == val;
//	return *this == other.asDateValue();
}


bool DateValue::operator != ( const AbstractValue& other ) const
{
	DateValue val = other.asDateValue();

//	if( *this == other.asDateValue() )
	if( *this == val )
		return false;
	else
		return true;
}


bool DateValue::operator > ( const DateValue& other ) const
{
	return compare( other ) == THIS_GREATER_THAN_OTHER;
}


bool DateValue::operator > ( const AbstractValue& other ) const
{
	DateValue val = other.asDateValue();

	return *this > val;
//	return *this > other.asDateValue();
}


bool DateValue::operator >= ( const DateValue& other ) const
{
	return compare( other ) != THIS_LESS_THAN_OTHER;
}


bool DateValue::operator >= ( const AbstractValue& other ) const
{
	DateValue val = other.asDateValue();

	return *this >= val;
//	return *this >= other.asDateValue();
}


bool DateValue::operator < ( const DateValue& other ) const
{
	return compare( other ) == THIS_LESS_THAN_OTHER;
}


bool DateValue::operator < ( const AbstractValue& other ) const
{
	DateValue val = other.asDateValue();

	return *this < val;
//	return *this < other.asDateValue();
}


bool DateValue::operator <= ( const DateValue& other ) const
{
	return compare( other ) != THIS_GREATER_THAN_OTHER;
}


bool DateValue::operator <= ( const AbstractValue& other ) const
{
	DateValue val = other.asDateValue();

	return *this <= val;
//	return *this <= other.asDateValue();
}


bool DateValue::operator ! ( void ) const
{
	if( !dateLiteral_.year_ && !dateLiteral_.month_ && !dateLiteral_.day_ )
		return true;
	else
		return false;
}


void DateValue::output( TempBuffer& tb ) const
{
	tb << dateLiteral_.year_ << dateLiteral_.month_ << dateLiteral_.day_;
}


void DateValue::input( TempBuffer& tb )
{
	tb >> dateLiteral_.year_ >> dateLiteral_.month_ >> dateLiteral_.day_;
}


UL DateValue::length( void ) const
{
	return sizeof( DateValue );
}


UL DateValue::streamLength( void ) const
{
	return fixedLength_;
}


NC DateValue::asChar() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


S DateValue::asShort() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


L DateValue::asLong() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


BigintValue DateValue::asBigintValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return BigintValue();
#endif
}


DecimalValue DateValue::asDecimalValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DecimalValue();
#endif
}


F DateValue::asFloat() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


D DateValue::asDouble() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


DateValue DateValue::asDateValue() const
{
	return *this;
}


TimeValue DateValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue DateValue::asTimestampValue() const
{
	return TimestampValue( *this );
}


const CqlString DateValue::asString( bool /* spacePadding */ ) const
{
	//  Need to make this sensitive to date format
	NC buffer[ 50 ];
	sprintf( buffer, "%02d/%02d/%4d", dateLiteral_.month_, dateLiteral_.day_, dateLiteral_.year_ );
	return CqlString( buffer );
}


void DateValue::operator << ( pUC& buf )
{
	memcpy( &dateLiteral_.year_, buf, sizeof( dateLiteral_.year_ ) );
	buf += sizeof( dateLiteral_.year_ );
	memcpy( &dateLiteral_.month_, buf, sizeof( dateLiteral_.month_ ) );
	buf += sizeof( dateLiteral_.month_ );
	memcpy( &dateLiteral_.day_, buf, sizeof( dateLiteral_.day_ ) );
	buf += sizeof( dateLiteral_.day_ );
}


void DateValue::operator >> ( pUC& buf )
{
	memcpy( buf, &dateLiteral_.year_, sizeof( dateLiteral_.year_ ) );
	buf += sizeof( dateLiteral_.year_ );
	memcpy( buf, &dateLiteral_.month_, sizeof( dateLiteral_.month_ ) );
	buf += sizeof( dateLiteral_.month_ );
	memcpy( buf, &dateLiteral_.day_, sizeof( dateLiteral_.day_ ) );
	buf += sizeof( dateLiteral_.day_ );
}


void DateValue::operator >> ( BinaryValue& bv )
{
	UC _length = sizeof( dateLiteral_.year_ ) + sizeof( dateLiteral_.month_ ) + sizeof( dateLiteral_.day_ );
	UC *buf = new UC[ _length ];
	if( !buf )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	UC *bufBase = buf;

	*this >> buf;
	bv = BinaryValue( bufBase, _length );
	delete bufBase;
}


void DateValue::operator << ( BinaryValue& bv )
{
	UC *p = bv.buffer();
	*this << p;
}


void DateValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void DateValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void DateValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void DateValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& DateValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& DateValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& DateValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& DateValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


US DateValue::dictionaryLength( void )
{
	return sizeof( bool ) + sizeof( dateLiteral_.year_ ) + sizeof( dateLiteral_.month_ ) + sizeof( dateLiteral_.day_ );
}


void DateValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << dateLiteral_.year_ << dateLiteral_.month_ << dateLiteral_.day_;
}


void DateValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> dateLiteral_.year_ >> dateLiteral_.month_ >> dateLiteral_.day_;
}


void DateValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	_output = asString();
}


void DateValue::setToCurrentDate( void )
{
	US hour, minute, second;
	UL fraction;
	hAEnv->getCurrentTimestamp( dateLiteral_.year_, dateLiteral_.month_, dateLiteral_.day_, hour, minute, second, fraction );
}


bool DateValue::isLeapYear( void ) const
{
	if( !( dateLiteral_.year_ % 400 ) || ( ( dateLiteral_.year_ % 100 ) && !( dateLiteral_.year_ % 4 ) ) )
		return true;

	return false;
}


US DateValue::firstDayOfYear( void ) const
{
	US _day, loop;
	DateValue dv;

	for( loop = 1, _day = 1; loop < dateLiteral_.year_; loop++ )
	{
		if( ++_day == 7 )
			_day = 0;

		dv.dateLiteral_.year_ = loop;

		if( dv.isLeapYear() && ++_day == 7 )
			_day = 0;
	}

	return _day;
}


US DateValue::dayOfYear( void ) const
{
	UNI loop, tday;
	DateValue dv;

	for( loop = 1, tday = 0; loop < dateLiteral_.month_; loop++ )
	{
		dv.month( static_cast< US >( loop ) );
		tday += dv.lastDayOfMonth();
	}

	tday += dateLiteral_.day_;
	return static_cast< US >( tday );
}


US DateValue::lastDayOfMonth( void ) const
{
	switch( dateLiteral_.month_ )
	{
	case 4 :
	case 6 :
	case 9 :
	case 11 :
		return 30;

	case 2 :
		if( isLeapYear() )
			return 29;
		else
			return 28;

	default :
		break;
	}

	return 31;
}


US DateValue::dayOfWeek( void ) const
{
	US _day = firstDayOfYear();
	US yearDay = dayOfYear();

	UNI loop, limit;
	for( loop = 0, limit = ( ( yearDay - 1 ) % 7 ); loop < limit; loop++ )
		if( ++_day == 7 )
			_day = 0;

	return _day;
}


US DateValue::quarter( void ) const
{
	if( dateLiteral_.month_ >= 10 )
		return 4;
	else if( dateLiteral_.month_ >= 7 )
		return 3;
	else if( dateLiteral_.month_ >= 4 )
		return 2;
	else
		return 1;
}


US DateValue::weekNumber( void ) const
{
	US tday = firstDayOfYear();
	US yearDay = dayOfYear();

	UNI loop, limit, weekNum;

	for( loop = 0, limit = ( ( yearDay - 1 ) % 7 ), weekNum = 1; loop < limit; loop++ )
	{
		if( ++tday == 7 )
		{
			tday = 0;
			weekNum++;
		}
	}

	return static_cast< US >( weekNum );
}
