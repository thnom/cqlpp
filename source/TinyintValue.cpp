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


const UL TinyintValue::fixedLength_ = sizeof( NC );


TinyintValue::TinyintValue( const TinyintValue& other ) : AbstractValue( CQL_TINYINT ), pvalue_( other.pvalue_ )
{
	if( const_cast< TinyintValue& >( other ).nullflag() )
		setNullflag();
}


TinyintValue::TinyintValue( pUC& source ) : AbstractValue( CQL_TINYINT )
{
	memcpy( &pvalue_, source, sizeof( pvalue_ ) );
	source += sizeof( pvalue_ );
}


TinyintValue::TinyintValue( const CqlColumnTypes& ) : AbstractValue( CQL_TINYINT ), pvalue_( 0 )
{
}


TinyintValue::TinyintValue( const S s ) : AbstractValue( CQL_TINYINT )
{
	pvalue_ = static_cast< const NC >( s );
	if( pvalue_ != s )
		throw ConversionException( __FILE__, __LINE__ );
}


TinyintValue::TinyintValue( const F f ) : AbstractValue( CQL_TINYINT )
{
	pvalue_ = static_cast< const NC >( f );
}


TinyintValue::TinyintValue( const L l ) : AbstractValue( CQL_TINYINT )
{
	pvalue_ = static_cast< const NC >( l );
	if( pvalue_ != l )
		throw ConversionException( __FILE__, __LINE__ );
}


TinyintValue::TinyintValue( const D d ) : AbstractValue( CQL_TINYINT )
{
	pvalue_ = static_cast< const NC >( d );
}


TinyintValue::TinyintValue( const NI source ) : AbstractValue( CQL_TINYINT )
{
	pvalue_ = static_cast< const NC >( source );
	if( pvalue_ != source )
		throw ConversionException( __FILE__, __LINE__ );
}


TinyintValue::TinyintValue( const UNI source ) : AbstractValue( CQL_TINYINT )
{
	pvalue_ = static_cast< const NC >( source );
	if( static_cast< L >( pvalue_ ) != static_cast< const L >( source ) )
		throw ConversionException( __FILE__, __LINE__ );
}


TinyintValue::TinyintValue( const US source ) : AbstractValue( CQL_TINYINT )
{
	pvalue_ = static_cast< const NC >( source );
	if( pvalue_ != source )
		throw ConversionException( __FILE__, __LINE__ );
}


TinyintValue::TinyintValue( const UL source ) : AbstractValue( CQL_TINYINT )
{
	pvalue_ = static_cast< const NC >( source );
	if( static_cast< L >( pvalue_ ) != static_cast< const L >( source ) )
		throw ConversionException( __FILE__, __LINE__ );
}


TinyintValue::TinyintValue( const BigintValue& bv ) : AbstractValue( CQL_TINYINT )
{
	D d;
	if( sscanf( bv.asString().text(), "%lf", &d ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );

	pvalue_ = static_cast< NC >( d );
}


TinyintValue::TinyintValue( const DecimalValue& dv ) : AbstractValue( CQL_TINYINT )
{
	D d;
	if( sscanf( dv.asString().text(), "%lf", &d ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );

	pvalue_ = static_cast< NC >( d );
}


TinyintValue::TinyintValue( const CqlString& source ) : AbstractValue( CQL_TINYINT )
{
	NI i;
	if( sscanf( source.text(), "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	pvalue_ = static_cast< NC >( i );
	if( pvalue_ != i )
		throw SizeConversionException( __FILE__, __LINE__ );
}


TinyintValue::TinyintValue( const NC *source ) : AbstractValue( CQL_TINYINT )
{
	NI i;
	if( sscanf( source, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	pvalue_ = static_cast< NC >( i );
	if( pvalue_ != i )
		throw SizeConversionException( __FILE__, __LINE__ );
}


TinyintValue::TinyintValue( const UC *usource ) : AbstractValue( CQL_TINYINT )
{
	const NC *source = reinterpret_cast< const NC* >( usource );
	NI i;
	if( sscanf( source, "%d", &i ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
	pvalue_ = static_cast< NC >( i );
	if( pvalue_ != i )
		throw SizeConversionException( __FILE__, __LINE__ );
}


TinyintValue& TinyintValue::operator = ( const TinyintValue& other )
{
	pvalue_ = other.pvalue_;
	TinyintValue& ncother = const_cast< TinyintValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


AbstractValue& TinyintValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_DECIMAL :
		{
			DecimalValue& dv = dynamic_cast< DecimalValue& >( av );
			*this = TinyintValue( dv );
		}
		break;

	case CQL_BIGINT :
		{
			BigintValue& bv = dynamic_cast< BigintValue& >( av );
			*this = TinyintValue( bv );
		}
		break;

	case CQL_SMALLINT :
		{
			SmallintValue& sv = dynamic_cast< SmallintValue& >( av );
			pvalue_ = static_cast< NC >( sv.pvalue() );
			if( static_cast< S >( pvalue_ ) != sv.pvalue() )
				throw SizeConversionException( __FILE__, __LINE__ );
		}
		break;

	case CQL_INTEGER :
		{
			IntegerValue& iv = dynamic_cast< IntegerValue& >( av );
			pvalue_ = static_cast< NC >( iv.pvalue() );
			if( static_cast< L >( pvalue_ ) != iv.pvalue() )
				throw SizeConversionException( __FILE__, __LINE__ );
		}
		break;

	case CQL_REAL :
		{
			RealValue& rv = dynamic_cast< RealValue& >( av );
			pvalue_ = static_cast< NC >( rv.pvalue() );
		}
		break;

	case CQL_FLOAT :
		{
			FloatValue& fv = dynamic_cast< FloatValue& >( av );
			pvalue_ = static_cast< NC >( fv.pvalue() );
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
			pvalue_ = tv.pvalue_;
		}
		break;

	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_CHAR :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
	case CQL_CHARUC :
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	return *this;
}


CqlConstants::CompareResult TinyintValue::compare( const TinyintValue& other ) const
{
	if( pvalue_ < other.pvalue_ )
		return THIS_LESS_THAN_OTHER;
	else if( pvalue_ > other.pvalue_ )
		return THIS_GREATER_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


bool TinyintValue::operator == ( const TinyintValue& other ) const
{
	return pvalue_ == other.pvalue_;
}


bool TinyintValue::operator == ( const AbstractValue& other ) const
{
	return pvalue_ == other.asChar();
}


bool TinyintValue::operator != ( const AbstractValue& other ) const
{
	return pvalue_ != other.asChar();
}


bool TinyintValue::operator > ( const TinyintValue& other ) const
{
	return pvalue_ > other.pvalue_;
}


bool TinyintValue::operator > ( const AbstractValue& other ) const
{
	return pvalue_ > other.asChar();
}


bool TinyintValue::operator >= ( const TinyintValue& other ) const
{
	return pvalue_ >= other.pvalue_;
}


bool TinyintValue::operator >= ( const AbstractValue& other ) const
{
	return pvalue_ >= other.asChar();
}


bool TinyintValue::operator < ( const TinyintValue& other ) const
{
	return pvalue_ < other.pvalue_;
}


bool TinyintValue::operator < ( const AbstractValue& other ) const
{
	return pvalue_ < other.asChar();
}


bool TinyintValue::operator <= ( const TinyintValue& other ) const
{
	return pvalue_ <= other.pvalue_;
}


bool TinyintValue::operator <= ( const AbstractValue& other ) const
{
	return pvalue_ <= other.asChar();
}


bool TinyintValue::operator ! ( void ) const
{
	if( pvalue_ )
		return false;
	else
		return true;
}


void TinyintValue::absoluteValue( void )
{
	if( pvalue_ < 0 )
		pvalue_ *= -1;
}


void TinyintValue::output( TempBuffer& tb ) const
{
	tb << pvalue_;
}


void TinyintValue::input( TempBuffer& tb )
{
	tb >> pvalue_;
}


UL TinyintValue::length( void ) const
{
	return sizeof( TinyintValue );
}


UL TinyintValue::streamLength( void ) const
{
	return fixedLength_;
}


NC TinyintValue::asChar() const
{
	return pvalue_;
}


S TinyintValue::asShort() const
{
	return static_cast< const S >( pvalue_ );
}


L TinyintValue::asLong() const
{
	return static_cast< const L >( pvalue_ );
}


BigintValue TinyintValue::asBigintValue() const
{
	return BigintValue( pvalue_ );
}


DecimalValue TinyintValue::asDecimalValue() const
{
	return DecimalValue( pvalue_ );
}


F TinyintValue::asFloat() const
{
	return static_cast< const F >( pvalue_ );
}


D TinyintValue::asDouble() const
{
	return static_cast< const D >( pvalue_ );
}


DateValue TinyintValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue TinyintValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue TinyintValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimestampValue();
#endif
}


const CqlString TinyintValue::asString( bool /* spacePadding */ ) const
{
	NC buffer[ 50 ];
	sprintf( buffer, "%d", static_cast< const NI >( pvalue_ ) );
	return CqlString( buffer );
}


void TinyintValue::operator << ( pUC& buf )
{
	memcpy( &pvalue_, buf, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void TinyintValue::operator >> ( pUC& buf )
{
	memcpy( buf, &pvalue_, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void TinyintValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( reinterpret_cast< UC * >( &pvalue_ ), sizeof( pvalue_ ) );
}


void TinyintValue::operator << ( BinaryValue& bv )
{
	memcpy( &pvalue_, bv.buffer(), sizeof( pvalue_ ) );
}


void TinyintValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void TinyintValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void TinyintValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void TinyintValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& TinyintValue::operator += ( AbstractValue& av )
{
	NI i;
	i = pvalue_ + av.asChar();
	pvalue_ = static_cast< NC >( i );
	if( pvalue_ != i )
		throw ConversionException( __FILE__, __LINE__ );

	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& TinyintValue::operator -= ( AbstractValue& av )
{
	NI i;
	i = pvalue_ - av.asChar();
	pvalue_ = static_cast< NC >( i );
	if( pvalue_ != i )
		throw ConversionException( __FILE__, __LINE__ );

	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& TinyintValue::operator *= ( AbstractValue& av )
{
	NI i;
	i = pvalue_ * av.asChar();
	pvalue_ = static_cast< NC >( i );
	if( pvalue_ != i )
		throw ConversionException( __FILE__, __LINE__ );

	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& TinyintValue::operator /= ( AbstractValue& av )
{
	NI i;
	i = pvalue_ / av.asChar();
	pvalue_ = static_cast< NC >( i );
	if( pvalue_ != i )
		throw ConversionException( __FILE__, __LINE__ );

	return dynamic_cast< AbstractValue& >( *this );
}


void TinyintValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	NC buf[ 100 ];
	sprintf( buf, "%d", static_cast< NI >( pvalue_ ) );
	_output = buf;
}


US TinyintValue::dictionaryLength( void )
{
	return sizeof( bool ) + sizeof( pvalue_ );
}


void TinyintValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << pvalue_;
}


void TinyintValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> pvalue_;
}
