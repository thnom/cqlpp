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


CharValue::CharValue( const CharValue& other ) : AbstractValue( CQL_CHAR ), value_( other.value_ )
{
	if( const_cast< CharValue& >( other ).nullflag() )
		setNullflag();
}


CharValue::CharValue( pUC& source ) : AbstractValue( CQL_CHAR ), value_()
{
	value_ = reinterpret_cast< NC* >( source );
	source += value_.length();
}


CharValue::CharValue( const NC *source ) : AbstractValue( CQL_CHAR ), value_( source )
{
}


CharValue::CharValue( const UC *source ) : AbstractValue( CQL_CHAR ), value_( reinterpret_cast< const NC* >( source ) )
{
}


CharValue::CharValue( const CqlString& source, const UL len ) : AbstractValue( CQL_CHAR, len )
{
	UC smallLength = static_cast< const UC >( len );
	if( smallLength != len )
		throw SizeConversionException( __FILE__, __LINE__ );
	value_.setString( source.text(), smallLength );
}


CharValue::CharValue( const CqlString& source ) : AbstractValue( CQL_CHAR, source.length() ), value_( source )
{
}


CharValue::CharValue( const CqlColumnTypes& ctype ) : AbstractValue( CQL_CHAR )
{
	value_.setString( ctype.typeLength() );
}


CharValue::CharValue( const NC ) : AbstractValue( CQL_CHAR )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


CharValue::CharValue( const D ) : AbstractValue( CQL_CHAR )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


CharValue::CharValue( const NI ) : AbstractValue( CQL_CHAR )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


CharValue::CharValue( const UNI ) : AbstractValue( CQL_CHAR )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


CharValue::CharValue( const US ) : AbstractValue( CQL_CHAR )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


CharValue::CharValue( const UL ) : AbstractValue( CQL_CHAR )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


CharValue& CharValue::operator = ( const CharValue& other )
{
	value_ = other.value_;
	return *this;
}


AbstractValue& CharValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_CHAR :
	{
		CharValue& cv = dynamic_cast< CharValue& >( av );
		value_ = cv.value_;
	}
	break;

	case CQL_CHARUC :
	{
		//  for a test, to see if the cast exception is because the value is CharValue instead of CharUCValue
		CharUCValue& cuv = dynamic_cast<CharUCValue&>(av);
		value_ = cuv.value_;
	}
	break;

	case CQL_VARCHAR :
	{
		VarcharValue& vv = dynamic_cast< VarcharValue& >( av );
		value_ = vv.buffer();
	}
	break;

	case CQL_LONGVARCHAR :
	{
		LongvarcharValue& lvv = dynamic_cast< LongvarcharValue& >( av );
		value_ = lvv.buffer();
	}
	break;

	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
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


CqlConstants::CompareResult CharValue::compare( const CharValue& other ) const
{
	if( const_cast< CqlString& >( value_ ) < other.value_ )
		return THIS_LESS_THAN_OTHER;
	else if( const_cast< CqlString& >( value_ ) > other.value_ )
		return THIS_GREATER_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


CqlConstants::CompareResult CharValue::compare( const CharUCValue& other ) const
{
	CharValue *cv = new CharValue(*other.value().toUpperCase());
	return compare(*cv);
}

void CharValue::output( TempBuffer& tb ) const
{
	UC instanceLength = static_cast< UC >( value_.length() );
	if( instanceLength != value_.length() )
		throw ConversionException( __FILE__, __LINE__ );

	tb << NO_COPY << ONE_BYTE_LENGTH << static_cast< UC >( instanceLength ) << value_;
}


void CharValue::input( TempBuffer& tb )
{
	UC instanceLength = static_cast< UC >( value_.length() );
	if( instanceLength != value_.length() )
		throw ConversionException( __FILE__, __LINE__ );

	tb << NO_COPY << ONE_BYTE_LENGTH << static_cast< UC >( instanceLength );
	tb >> value_;
}


void CharValue::releaseMemory( void )
{
	value_.reset();
}


NC CharValue::asChar() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


S CharValue::asShort() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


L CharValue::asLong() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


BigintValue CharValue::asBigintValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return BigintValue();
#endif
}


DecimalValue CharValue::asDecimalValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return DecimalValue();
#endif
}


F CharValue::asFloat() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


D CharValue::asDouble() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


DateValue CharValue::asDateValue() const
{
	//  temporary
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return DateValue();
#endif
}


TimeValue CharValue::asTimeValue() const
{
	//  temporary
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return TimeValue();
#endif
}


TimestampValue CharValue::asTimestampValue() const
{
	//  temporary
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return TimestampValue();
#endif
}


const CqlString CharValue::asString( bool /*spacePadding*/ ) const
{
	return value_;
}


void CharValue::operator << ( pUC& buf )
{
	UL tlength;
	memcpy( &tlength, buf, sizeof( tlength ) );
	buf += sizeof( tlength );
	value_ = reinterpret_cast< NC* >( buf );
	buf += tlength;
}


void CharValue::operator >> ( pUC& buf )
{
	memcpy( buf, value_.text(), value_.length() );
	buf += value_.length();
}


void CharValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( reinterpret_cast< const UC * >( value_.text() ), length() );
}


void CharValue::operator << ( BinaryValue& bv )
{
	value_.setString( bv.buffer(), bv.length() - 1 );
}


void CharValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void CharValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void CharValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void CharValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


void CharValue::initialize( void )
{
	value_.setString( typeLength() );
}


AbstractValue& CharValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& CharValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& CharValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& CharValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


bool CharValue::operator == ( const AbstractValue& cother) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	CharValue& cv = dynamic_cast< CharValue& >( other );
	return value_ == cv.value_;
}


bool CharValue::operator != ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	CharValue& cv = dynamic_cast< CharValue& >( other );
	return value_ != cv.value_;
}


bool CharValue::operator >= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	CharValue& cv = dynamic_cast< CharValue& >( other );
	return value_ >= cv.value_;
}


bool CharValue::operator > ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	CharValue& cv = dynamic_cast< CharValue& >( other );
	return value_ > cv.value_;
}


bool CharValue::operator < ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	CharValue& cv = dynamic_cast< CharValue& >( other );
	return value_ < cv.value_;
}


bool CharValue::operator <= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	CharValue& cv = dynamic_cast< CharValue& >( other );
	return value_ <= cv.value_;
}


bool CharValue::operator ! ( void ) const
{
	return !value_;
}


US CharValue::dictionaryLength( void )
{
#ifdef __WATCOMC__
	return static_cast< US >( value_.length() + sizeof( UL ) );
#else
	return static_cast< US >( value_.length() + sizeof( value_.length() ) );
#endif
}


void CharValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	_output = value_;
}


void CharValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> value_;
}


void CharValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << value_;
}


UL CharValue::streamLength( void ) const
{
#ifdef __WATCOMC__
	return value_.length() + sizeof( UL );
#else
	return value_.length() + sizeof( value_.length() );
#endif
}
