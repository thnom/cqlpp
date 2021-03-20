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


const UL TimeValue::fixedLength_ = sizeof( US ) + sizeof( US ) + sizeof( US );


TimeValue::TimeValue( const TimeValue& other ) : AbstractValue( CQL_TIME )
{
	timeLiteral_.hour_ = other.timeLiteral_.hour_;
	timeLiteral_.minute_ = other.timeLiteral_.minute_;
	timeLiteral_.second_ = other.timeLiteral_.second_;
	if( const_cast< TimeValue& >( other ).nullflag() )
		setNullflag();
}


TimeValue::TimeValue( pUC& source ) : AbstractValue( CQL_TIME )
{
	memcpy( &timeLiteral_.hour_, source, sizeof( timeLiteral_.hour_ ) );
	source += sizeof( timeLiteral_.hour_ );
	memcpy( &timeLiteral_.minute_, source, sizeof( timeLiteral_.minute_ ) );
	source += sizeof( timeLiteral_.minute_ );
	memcpy( &timeLiteral_.second_, source, sizeof( timeLiteral_.second_ ) );
	source += sizeof( timeLiteral_.second_ );
}


TimeValue::TimeValue( const CqlColumnTypes& ) : AbstractValue( CQL_TIME )
{
	timeLiteral_.hour_ = 0;
	timeLiteral_.minute_ = 0;
	timeLiteral_.second_ = 0;
}


TimeValue::TimeValue( const TimestampValue& tsv ) : AbstractValue( CQL_TIME )
{
	timeLiteral_.hour_ = tsv.hour();
	timeLiteral_.minute_ = tsv.minute();
	timeLiteral_.second_ = tsv.second();
}


TimeValue::TimeValue( const NC *str ) : AbstractValue( CQL_TIME )
{
	//  Assumes format HH:MM:SS
	NC buf[ 3 ];
	buf[ 2 ] = 0;
	NI i;

	//  get and decode hour
	memcpy( buf, str, 2 );
	str += 3;  // two digits, plus separator
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timeLiteral_.hour_ = static_cast< US >( i );

	//  get and decode minute;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timeLiteral_.minute_ = static_cast< US >( i );

	//  get and decode second;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timeLiteral_.second_ = static_cast< US >( i );
}


TimeValue::TimeValue( const CqlString& s ) : AbstractValue( CQL_TIME )
{
	//  Assumes format HH:MM:SS
	const char * str = const_cast<const char *>(s.text());

	NC buf[ 3 ];
	buf[ 2 ] = 0;
	NI i;

	//  get and decode hour
	memcpy( buf, str, 2 );
	str += 3;  // two digits, plus separator
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timeLiteral_.hour_ = static_cast< US >( i );

	//  get and decode minute;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timeLiteral_.minute_ = static_cast< US >( i );

	//  get and decode second;
	memcpy( buf, str, 2 );
	str += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timeLiteral_.second_ = static_cast< US >( i );
}


TimeValue::TimeValue( const UC *usource ) : AbstractValue( CQL_TIME )
{
	const NC *source = reinterpret_cast< const NC* >( usource );
	//  Assumes format HH:MM:SS
	NC buf[ 3 ];
	buf[ 2 ] = 0;
	NI i;

	//  get and decode hour
	memcpy( buf, source, 2 );
	source += 3;  // two digits, plus separator
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timeLiteral_.hour_ = static_cast< US >( i );

	//  get and decode minute;
	memcpy( buf, source, 2 );
	source += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timeLiteral_.minute_ = static_cast< US >( i );

	//  get and decode second;
	memcpy( buf, source, 2 );
	source += 3;
	if( sscanf( buf, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	timeLiteral_.second_ = static_cast< US >( i );
}


TimeValue::TimeValue( const NC ) : AbstractValue( CQL_TIME )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimeValue::TimeValue( const D ) : AbstractValue( CQL_TIME )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimeValue::TimeValue( const NI ) : AbstractValue( CQL_TIME )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimeValue::TimeValue( const US ) : AbstractValue( CQL_TIME )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


TimeValue::TimeValue( const UL ) : AbstractValue( CQL_TIME )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}



TimeValue& TimeValue::operator = ( const TimeValue& other )
{
	timeLiteral_.hour_ = other.timeLiteral_.hour_;
	timeLiteral_.minute_ = other.timeLiteral_.minute_;
	timeLiteral_.second_ = other.timeLiteral_.second_;
	TimeValue& ncother = const_cast< TimeValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


AbstractValue& TimeValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_TIME :
		{
			TimeValue& tv = dynamic_cast< TimeValue& >( av );
			timeLiteral_.hour_ = tv.timeLiteral_.hour_;
			timeLiteral_.minute_ = tv.timeLiteral_.minute_;
			timeLiteral_.second_ = tv.timeLiteral_.second_;
		}
		break;

	case CQL_TIMESTAMP :
		{
			TimestampValue& tv = dynamic_cast< TimestampValue& >( av );
			if( tv.year() || tv.month() || tv.day() )
				throw SizeConversionException( __FILE__, __LINE__ );
			timeLiteral_.hour_ = tv.hour();
			timeLiteral_.minute_ = tv.minute();
			timeLiteral_.second_ = tv.second();
		}
		break;

	case CQL_DATE :
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


CqlConstants::CompareResult TimeValue::compare( const TimeValue& other ) const
{
	if( timeLiteral_.hour_ > other.timeLiteral_.hour_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timeLiteral_.hour_ < other.timeLiteral_.hour_ )
		return THIS_LESS_THAN_OTHER;
	else if( timeLiteral_.minute_ > other.timeLiteral_.minute_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timeLiteral_.minute_ < other.timeLiteral_.minute_ )
		return THIS_LESS_THAN_OTHER;
	else if( timeLiteral_.second_ > other.timeLiteral_.second_ )
		return THIS_GREATER_THAN_OTHER;
	else if( timeLiteral_.second_ < other.timeLiteral_.second_ )
		return THIS_LESS_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


bool TimeValue::operator == ( const TimeValue& other ) const
{
	return compare( other ) == THIS_EQUAL_TO_OTHER;
}


bool TimeValue::operator == ( const AbstractValue& other ) const
{
	TimeValue val = other.asTimeValue();

	return *this == val;
//	return *this == other.asTimeValue();
}


bool TimeValue::operator != ( const AbstractValue& other ) const
{
	TimeValue val = other.asTimeValue();

//	if( *this == other.asTimeValue() )
	if( *this == val )
		return false;
	else
		return true;
}


bool TimeValue::operator > ( const TimeValue& other ) const
{
	return compare( other ) == THIS_GREATER_THAN_OTHER;
}


bool TimeValue::operator > ( const AbstractValue& other ) const
{
	TimeValue val = other.asTimeValue();

	return *this > val;
//	return *this > other.asTimeValue();
}


bool TimeValue::operator >= ( const TimeValue& other ) const
{
	return compare( other ) != THIS_LESS_THAN_OTHER;
}


bool TimeValue::operator >= ( const AbstractValue& other ) const
{
	TimeValue val = other.asTimeValue();

	return *this >= val;
//	return *this >= other.asTimeValue();
}


bool TimeValue::operator < ( const TimeValue& other ) const
{
	return compare( other ) == THIS_LESS_THAN_OTHER;
}


bool TimeValue::operator < ( const AbstractValue& other ) const
{
	TimeValue val = other.asTimeValue();

	return *this < val;
//	return *this < other.asTimeValue();
}


bool TimeValue::operator <= ( const TimeValue& other ) const
{
	return compare( other ) != THIS_GREATER_THAN_OTHER;
}


bool TimeValue::operator <= ( const AbstractValue& other ) const
{
	TimeValue val = other.asTimeValue();

	return *this <= val;
//	return *this <= other.asTimeValue();
}


bool TimeValue::operator ! ( void ) const
{
	if( !timeLiteral_.hour_ && !timeLiteral_.minute_ && !timeLiteral_.second_ )
		return true;
	else
		return false;
}


void TimeValue::output( TempBuffer& tb ) const
{
	tb << timeLiteral_.hour_ << timeLiteral_.minute_ << timeLiteral_.second_;
}


void TimeValue::input( TempBuffer& tb )
{
	tb >> timeLiteral_.hour_ >> timeLiteral_.minute_ >> timeLiteral_.second_;
}


UL TimeValue::length( void ) const
{
	return sizeof( TimeValue );
}


UL TimeValue::streamLength( void ) const
{
	return fixedLength_;
}


NC TimeValue::asChar() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


S TimeValue::asShort() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


L TimeValue::asLong() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


BigintValue TimeValue::asBigintValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return BigintValue();
#endif
}


DecimalValue TimeValue::asDecimalValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DecimalValue();
#endif
}


F TimeValue::asFloat() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


D TimeValue::asDouble() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


DateValue TimeValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue TimeValue::asTimeValue() const
{
	return *this;
}


TimestampValue TimeValue::asTimestampValue() const
{
	return TimestampValue( *this );
}


const CqlString TimeValue::asString( bool /* spacePadding */ ) const
{
	//  need to make this sensitive to date format
	NC buffer[ 50 ];
	sprintf( buffer, "%02d:%02d:%02d", timeLiteral_.hour_, timeLiteral_.minute_, timeLiteral_.second_ );
	return CqlString( buffer );
}


void TimeValue::operator << ( pUC& buf )
{
	memcpy( &timeLiteral_.hour_, buf, sizeof( timeLiteral_.hour_ ) );
	buf += sizeof( timeLiteral_.hour_ );
	memcpy( &timeLiteral_.minute_, buf, sizeof( timeLiteral_.minute_ ) );
	buf += sizeof( timeLiteral_.minute_ );
	memcpy( &timeLiteral_.second_, buf, sizeof( timeLiteral_.second_ ) );
	buf += sizeof( timeLiteral_.second_ );
}


void TimeValue::operator >> ( pUC& buf )
{
	memcpy( buf, &timeLiteral_.hour_, sizeof( timeLiteral_.hour_ ) );
	buf += sizeof( timeLiteral_.hour_ );
	memcpy( buf, &timeLiteral_.minute_, sizeof( timeLiteral_.minute_ ) );
	buf += sizeof( timeLiteral_.minute_ );
	memcpy( buf, &timeLiteral_.second_, sizeof( timeLiteral_.second_ ) );
	buf += sizeof( timeLiteral_.second_ );
}


void TimeValue::operator >> ( BinaryValue& bv )
{
	UC _length = sizeof( timeLiteral_.hour_ ) + sizeof( timeLiteral_.minute_ ) + sizeof( timeLiteral_.second_ );
	UC *buf = new UC[ _length ];
	if( !buf )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	UC *bufBase = buf;

	*this >> buf;
	bv = BinaryValue( bufBase, _length );
	delete bufBase;
}


void TimeValue::operator << ( BinaryValue& bv )
{
	UC *p = bv.buffer();
	*this << p;
}


void TimeValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void TimeValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void TimeValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void TimeValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& TimeValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& TimeValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& TimeValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& TimeValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnTimestampDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


US TimeValue::dictionaryLength( void )
{
	return static_cast< US >( sizeof( bool ) + sizeof( timeLiteral_.hour_ ) + sizeof( timeLiteral_.minute_ ) + sizeof( timeLiteral_.second_ ) );
}


void TimeValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << timeLiteral_.hour_ << timeLiteral_.minute_ << timeLiteral_.second_;
}


void TimeValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> timeLiteral_.hour_ >> timeLiteral_.minute_ >> timeLiteral_.second_;
}


void TimeValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	_output = asString();
}


void TimeValue::setToCurrentTime( void )
{
	S year;
	US month, day;
	UL fraction;
	hAEnv->getCurrentTimestamp( year, month, day, timeLiteral_.hour_, timeLiteral_.minute_, timeLiteral_.second_, fraction );
}
