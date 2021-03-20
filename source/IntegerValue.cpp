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


const UL IntegerValue::fixedLength_ = sizeof( L );


IntegerValue::IntegerValue( const IntegerValue& other ) : AbstractValue( CQL_INTEGER ), pvalue_( other.pvalue_ )
{
	if( const_cast< IntegerValue& >( other ).nullflag() )
		setNullflag();
}


IntegerValue::IntegerValue( pUC& source ) : AbstractValue( CQL_INTEGER )
{
	memcpy( &pvalue_, source, sizeof( pvalue_ ) );
	source += sizeof( pvalue_ );
}


IntegerValue::IntegerValue( const CqlColumnTypes& ) : AbstractValue( CQL_INTEGER ), pvalue_( 0 )
{
}


IntegerValue::IntegerValue( const F f ) : AbstractValue( CQL_INTEGER )
{
	pvalue_ = static_cast< const L >( f );
}


IntegerValue::IntegerValue( const S s ) : AbstractValue( CQL_INTEGER )
{
	pvalue_ = static_cast< const L >( s );
}


IntegerValue::IntegerValue( const D d ) : AbstractValue( CQL_INTEGER )
{
	pvalue_ = static_cast< const L >( d );
}


IntegerValue::IntegerValue( const NC source ) : AbstractValue( CQL_INTEGER )
{
	pvalue_ = static_cast< const L >( source );
}


IntegerValue::IntegerValue( const NI source ) : AbstractValue( CQL_INTEGER )
{
	pvalue_ = static_cast< const L >( source );
}


IntegerValue::IntegerValue( const UNI source ) : AbstractValue( CQL_INTEGER )
{
	pvalue_ = static_cast< const L >( source );
}


IntegerValue::IntegerValue( const US source ) : AbstractValue( CQL_INTEGER )
{
	pvalue_ = static_cast< const L >( source );
}


IntegerValue::IntegerValue( const UL source ) : AbstractValue( CQL_INTEGER )
{
	pvalue_ = static_cast< const L >( source );
}


IntegerValue::IntegerValue( const BigintValue& bv ) : AbstractValue( CQL_INTEGER )
{
	D d;
	if( sscanf( bv.asString().text(), "%lf", &d ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );

	pvalue_ = static_cast< L >( d );
}


IntegerValue::IntegerValue( const DecimalValue& dv ) : AbstractValue( CQL_INTEGER )
{
	D d;
	if( sscanf( dv.asString().text(), "%lf", &d ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );

	pvalue_ = static_cast< L >( d );
}


IntegerValue::IntegerValue( const CqlString& source ) : AbstractValue( CQL_INTEGER )
{
	if( sscanf( source.text(), "%ld", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


IntegerValue::IntegerValue( const NC *source ) : AbstractValue( CQL_INTEGER )
{
	if( sscanf( source, "%ld", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


IntegerValue::IntegerValue( const UC *source ) : AbstractValue( CQL_INTEGER )
{
	if( sscanf( reinterpret_cast< const NC* >( source ), "%ld", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


IntegerValue& IntegerValue::operator = ( const IntegerValue& other )
{
	pvalue_ = other.pvalue_;
	IntegerValue& ncother = const_cast< IntegerValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


AbstractValue& IntegerValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_CHAR :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_CHARUC :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_DECIMAL :
		{
			DecimalValue& dv = dynamic_cast< DecimalValue& >( av );
			*this = IntegerValue( dv );
		}
		break;

	case CQL_BIGINT :
		{
			BigintValue& bv = dynamic_cast< BigintValue& >( av );
			*this = IntegerValue( bv );
		}
		break;

	case CQL_SMALLINT :
		{
			SmallintValue& sv = dynamic_cast< SmallintValue& >( av );
			pvalue_ = sv.pvalue();
		}
		break;

	case CQL_INTEGER :
		*this = dynamic_cast< IntegerValue& >( av );
		break;

	case CQL_REAL :
		{
			RealValue& rv = dynamic_cast< RealValue& >( av );
			pvalue_ = static_cast< L >( rv.pvalue() );
		}
		break;

	case CQL_FLOAT :
		{
			FloatValue& fv = dynamic_cast< FloatValue& >( av );
			pvalue_ = static_cast< L >( fv.pvalue() );
		}
		break;

	case CQL_BIT :
		{
			BitValue& bv = dynamic_cast< BitValue& >( av );
			pvalue_ = bv.pvalue();
		}
		break;

	case CQL_TINYINT :
		{
			TinyintValue& tv = dynamic_cast< TinyintValue& >( av );
			pvalue_ = tv.pvalue();
		}
		break;
	}

	return *this;
}


IntegerValue& IntegerValue::operator = ( const US val )
{
	pvalue_ = val;
	return *this;
}


IntegerValue& IntegerValue::operator = ( const NI val )
{
	pvalue_ = val;
	return *this;
}


IntegerValue& IntegerValue::operator = ( const UNI val )
{
	pvalue_ = val;
	return *this;
}


IntegerValue& IntegerValue::operator = ( const L val )
{
	pvalue_ = val;
	return *this;
}

#ifndef CQL_BOOL_IS_INT

IntegerValue& IntegerValue::operator = ( const bool val )
{
	if( val )
		pvalue_ = 1;
	else
		pvalue_ = 0;
	return *this;
}

#endif  //  ~CQL_BOOL_IS_INT


CqlConstants::CompareResult IntegerValue::compare( const IntegerValue& other ) const
{
	if( pvalue_ < other.pvalue_ )
		return THIS_LESS_THAN_OTHER;
	else if( pvalue_ > other.pvalue_ )
		return THIS_GREATER_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


bool IntegerValue::operator == ( const IntegerValue& other ) const
{
	return pvalue_ == other.pvalue_;
}


bool IntegerValue::operator == ( const AbstractValue& other ) const
{
	return pvalue_ == other.asLong();
}


bool IntegerValue::operator != ( const AbstractValue& other ) const
{
	if( pvalue_ == other.asLong() )
		return false;
	else
		return true;
}


bool IntegerValue::operator > ( const IntegerValue& other ) const
{
	return pvalue_ > other.pvalue_;
}


bool IntegerValue::operator > ( const AbstractValue& other ) const
{
	return pvalue_ > other.asLong();
}


bool IntegerValue::operator >= ( const IntegerValue& other ) const
{
	return pvalue_ >= other.pvalue_;
}


bool IntegerValue::operator >= ( const AbstractValue& other ) const
{
	return pvalue_ >= other.asLong();
}


bool IntegerValue::operator < ( const IntegerValue& other ) const
{
	return pvalue_ < other.pvalue_;
}


bool IntegerValue::operator < ( const AbstractValue& other ) const
{
	return pvalue_ < other.asLong();
}


bool IntegerValue::operator <= ( const IntegerValue& other ) const
{
	return pvalue_ <= other.pvalue_;
}


bool IntegerValue::operator <= ( const AbstractValue& other ) const
{
	return pvalue_ <= other.asLong();
}


bool IntegerValue::operator ! ( void ) const
{
	if( pvalue_ )
		return false;
	else
		return true;
}


void IntegerValue::absoluteValue( void )
{
	if( pvalue_ < 0 )
		pvalue_ *= -1;
}


void IntegerValue::output( TempBuffer& tb ) const
{
	tb << pvalue_;
}


void IntegerValue::input( TempBuffer& tb )
{
	tb >> pvalue_;
}


UL IntegerValue::length( void ) const
{
	return sizeof( IntegerValue );
}


UL IntegerValue::streamLength( void ) const
{
	return fixedLength_;
}


NC IntegerValue::asChar() const
{
	NC sc = static_cast< const NC >( pvalue_ );
	if( sc != pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return sc;
}


S IntegerValue::asShort() const
{
	S s = static_cast< const S >( pvalue_ );
	if( s != pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return s;
}


L IntegerValue::asLong() const
{
	return pvalue_;
}


BigintValue IntegerValue::asBigintValue() const
{
	return BigintValue( pvalue_ );
}


DecimalValue IntegerValue::asDecimalValue() const
{
	return DecimalValue( pvalue_ );
}


F IntegerValue::asFloat() const
{
	return static_cast< const F >( pvalue_ );
}


D IntegerValue::asDouble() const
{
	return static_cast< const D >( pvalue_ );
}


DateValue IntegerValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue IntegerValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue IntegerValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimestampValue();
#endif
}


const CqlString IntegerValue::asString( bool /* spacePadding */ ) const
{
	NC buffer[ 50 ];
	sprintf( buffer, "%ld", pvalue_ );
	return CqlString( buffer );
}


void IntegerValue::operator << ( pUC& buf )
{
	memcpy( &pvalue_, buf, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void IntegerValue::operator >> ( pUC& buf )
{
	memcpy( buf, &pvalue_, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void IntegerValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( reinterpret_cast< UC * >( &pvalue_ ), sizeof( pvalue_ ) );
}


void IntegerValue::operator << ( BinaryValue& bv )
{
	memcpy( &pvalue_, bv.buffer(), sizeof( pvalue_ ) );
}


void IntegerValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void IntegerValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void IntegerValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void IntegerValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& IntegerValue::operator += ( AbstractValue& av )
{
	pvalue_ += av.asLong();
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& IntegerValue::operator -= ( AbstractValue& av )
{
	pvalue_ -= av.asLong();
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& IntegerValue::operator *= ( AbstractValue& av )
{
	pvalue_ *= av.asLong();
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& IntegerValue::operator /= ( AbstractValue& av )
{
	pvalue_ /= av.asLong();
	return dynamic_cast< AbstractValue& >( *this );
}


void IntegerValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	NC buf[ 100 ];
	sprintf( buf, "%ld", pvalue_ );
	_output = buf;
}


void IntegerValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << pvalue_;
}


void IntegerValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> pvalue_;
}


US IntegerValue::dictionaryLength( void )
{
	return sizeof( bool ) + sizeof( pvalue_ );
}
