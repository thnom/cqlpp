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


const UL FloatValue::fixedLength_ = sizeof( D );


FloatValue::FloatValue( const FloatValue& other ) : AbstractValue( CQL_FLOAT ), pvalue_( other.pvalue_ )
{
	if( const_cast< FloatValue& >( other ).nullflag() )
		setNullflag();
}


FloatValue::FloatValue( pUC& source ) : AbstractValue( CQL_FLOAT )
{
	memcpy( &pvalue_, source, sizeof( pvalue_ ) );
	source += sizeof( pvalue_ );
}


FloatValue::FloatValue( const CqlColumnTypes& ) : AbstractValue( CQL_FLOAT ), pvalue_( 0 )
{
}


FloatValue::FloatValue( BigintValue& bv ) : AbstractValue( CQL_FLOAT )
{
	if( sscanf( bv.asString().text(), "%lf", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


FloatValue::FloatValue( DecimalValue& dv ) : AbstractValue( CQL_FLOAT )
{
	if( sscanf( dv.asString().text(), "%lf", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


FloatValue::FloatValue( const CqlString& source ) : AbstractValue( CQL_FLOAT )
{
	if( sscanf( source.text(), "%lf", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


FloatValue::FloatValue( const NC *source ) : AbstractValue( CQL_FLOAT )
{
	if( sscanf( source, "%lf", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


FloatValue::FloatValue( const UC *source ) : AbstractValue( CQL_FLOAT )
{
	if( sscanf( reinterpret_cast< const NC* >( source ), "%lf", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


FloatValue::FloatValue( const NC source ) : AbstractValue( CQL_FLOAT )
{
	pvalue_ = static_cast< const D >( source );
}


FloatValue::FloatValue( const NI source ) : AbstractValue( CQL_FLOAT )
{
	pvalue_ = static_cast< const D >( source );
}


FloatValue::FloatValue( const UNI source ) : AbstractValue( CQL_FLOAT )
{
	pvalue_ = static_cast< const D >( source );
}


FloatValue::FloatValue( const US source ) : AbstractValue( CQL_FLOAT )
{
	pvalue_ = static_cast< const D >( source );
}


FloatValue::FloatValue( const UL source ) : AbstractValue( CQL_FLOAT )
{
	pvalue_ = static_cast< const D >( source );
}


FloatValue& FloatValue::operator = ( const FloatValue& other )
{
	pvalue_ = other.pvalue_;
	FloatValue& ncother = const_cast< FloatValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


AbstractValue& FloatValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_DECIMAL :
	case CQL_BIGINT :
		*this = FloatValue( av.asString() );
		break;

	case CQL_SMALLINT :
		{
			SmallintValue& sv = dynamic_cast< SmallintValue& >( av );
			pvalue_ = sv.pvalue();
		}
		break;

	case CQL_INTEGER :
		{
			IntegerValue& iv = dynamic_cast< IntegerValue& >( av );
			pvalue_ = iv.pvalue();
		}
		break;

	case CQL_REAL :
		{
			RealValue& rv = dynamic_cast< RealValue& >( av );
			pvalue_ = rv.pvalue();
		}
		break;

	case CQL_FLOAT :
		{
			FloatValue& fv = dynamic_cast< FloatValue& >( av );
			pvalue_ = fv.pvalue_;
		}
		break;

	case CQL_BIT :
		{
			BitValue& bv = dynamic_cast< BitValue& >( av );
			if( bv.pvalue() )
				pvalue_ = 1;
			else
				pvalue_ = 0;
		}
		break;

	case CQL_TINYINT :
		{
			TinyintValue& tv = dynamic_cast< TinyintValue& >( av );
			pvalue_ = tv.pvalue();
		}
		break;

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
	}

	return *this;
}


CqlConstants::CompareResult FloatValue::compare( const FloatValue& other ) const
{
	if( pvalue_ < other.pvalue_ )
		return THIS_LESS_THAN_OTHER;
	else if( pvalue_ > other.pvalue_ )
		return THIS_GREATER_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


bool FloatValue::operator == ( const FloatValue& other ) const
{
	return pvalue_ == other.pvalue_;
}


bool FloatValue::operator == ( const AbstractValue& other ) const
{
	return pvalue_ == other.asDouble();
}


bool FloatValue::operator != ( const AbstractValue& other ) const
{
	return pvalue_ != other.asDouble();
}


bool FloatValue::operator > ( const FloatValue& other ) const
{
	return pvalue_ > other.pvalue_;
}


bool FloatValue::operator > ( const AbstractValue& other ) const
{
	return pvalue_ > other.asDouble();
}


bool FloatValue::operator >= ( const FloatValue& other ) const
{
	return pvalue_ >= other.pvalue_;
}


bool FloatValue::operator >= ( const AbstractValue& other ) const
{
	return pvalue_ >= other.asDouble();
}


bool FloatValue::operator < ( const FloatValue& other ) const
{
	return pvalue_ < other.pvalue_;
}


bool FloatValue::operator < ( const AbstractValue& other ) const
{
	return pvalue_ < other.asDouble();
}


bool FloatValue::operator <= ( const FloatValue& other ) const
{
	return pvalue_ <= other.pvalue_;
}


bool FloatValue::operator <= ( const AbstractValue& other ) const
{
	return pvalue_ <= other.asDouble();
}


bool FloatValue::operator ! ( void ) const
{
	if( pvalue_ )
		return false;
	else
		return true;
}


void FloatValue::absoluteValue( void )
{
	if( pvalue_ < 0 )
		pvalue_ *= -1;
}


void FloatValue::output( TempBuffer& tb ) const
{
	tb << pvalue_;
}


void FloatValue::input( TempBuffer& tb )
{
	tb >> pvalue_;
}


UL FloatValue::length( void ) const
{
	return sizeof( FloatValue );
}


UL FloatValue::streamLength( void ) const
{
	return fixedLength_;
}


NC FloatValue::asChar() const
{
	NC sc = static_cast< const NC >( pvalue_ );
	if( sc < pvalue_ || sc > pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return sc;
}


S FloatValue::asShort() const
{
	S s = static_cast< const S >( pvalue_ );
	if( s < pvalue_ || s > pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return s;
}


L FloatValue::asLong() const
{
	L l = static_cast< const L >( pvalue_ );
	if( l < pvalue_ || l > pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return l;
}


BigintValue FloatValue::asBigintValue() const
{
	return BigintValue( pvalue_ );
}


DecimalValue FloatValue::asDecimalValue() const
{
	return DecimalValue( pvalue_ );
}


F FloatValue::asFloat() const
{
	F f = static_cast< const F >( pvalue_ );
	if( f < pvalue_ || f > pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return f;
}


D FloatValue::asDouble() const
{
	return pvalue_;
}


DateValue FloatValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue FloatValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue FloatValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimestampValue();
#endif
}


const CqlString FloatValue::asString( bool /* spacePadding */ ) const
{
	NC buffer[ 50 ];
	sprintf( buffer, "%f", pvalue_ );
	return CqlString( buffer );
}


void FloatValue::operator << ( pUC& buf )
{
	memcpy( buf, &pvalue_, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void FloatValue::operator >> ( pUC& buf )
{
	memcpy( &pvalue_, buf, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void FloatValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( reinterpret_cast< UC * >( &pvalue_ ), sizeof( pvalue_ ) );
}


void FloatValue::operator << ( BinaryValue& bv )
{
	memcpy( &pvalue_, bv.buffer(), sizeof( pvalue_ ) );
}


void FloatValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void FloatValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void FloatValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void FloatValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& FloatValue::operator += ( AbstractValue& av )
{
	pvalue_ += av.asDouble();
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& FloatValue::operator -= ( AbstractValue& av )
{
	pvalue_ -= av.asDouble();
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& FloatValue::operator *= ( AbstractValue& av )
{
	pvalue_ *= av.asDouble();
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& FloatValue::operator /= ( AbstractValue& av )
{
	pvalue_ /= av.asDouble();
	return dynamic_cast< AbstractValue& >( *this );
}


void FloatValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	NC buf[ 100 ];
	sprintf( buf, "%f", pvalue_ );
	_output = buf;
}


US FloatValue::dictionaryLength( void )
{
	return sizeof( bool ) + sizeof( pvalue_ );
}


void FloatValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << pvalue_;
}


void FloatValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> pvalue_;
}
