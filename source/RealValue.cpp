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


const UL RealValue::fixedLength_ = sizeof( F );


RealValue::RealValue( const RealValue& other ) : AbstractValue( CQL_REAL ), pvalue_( other.pvalue_ )
{
	if( const_cast< RealValue& >( other ).nullflag() )
		setNullflag();
}


RealValue::RealValue( pUC& source ) : AbstractValue( CQL_REAL )
{
	memcpy( &pvalue_, source, sizeof( pvalue_ ) );
	source += sizeof( pvalue_ );
}


RealValue::RealValue( const CqlColumnTypes& ) : AbstractValue( CQL_REAL ), pvalue_( 0 )
{
}


RealValue::RealValue( BigintValue& bv ) : AbstractValue( CQL_REAL )
{
	if( sscanf( bv.asString().text(), "%f", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


RealValue::RealValue( DecimalValue& dv ) : AbstractValue( CQL_REAL )
{
	if( sscanf( dv.asString().text(), "%f", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


RealValue::RealValue( const D d ) : AbstractValue( CQL_REAL )
{
	pvalue_ = static_cast< const F >( d );
}


RealValue::RealValue( const NC source ) : AbstractValue( CQL_REAL )
{
	pvalue_ = static_cast< const F >( source );
}


RealValue::RealValue( const NI source ) : AbstractValue( CQL_REAL )
{
	pvalue_ = static_cast< const F >( source );
}


RealValue::RealValue( const UNI source ) : AbstractValue( CQL_REAL )
{
	pvalue_ = static_cast< const F >( source );
}


RealValue::RealValue( const US source ) : AbstractValue( CQL_REAL )
{
	pvalue_ = static_cast< const F >( source );
}


RealValue::RealValue( const UL source ) : AbstractValue( CQL_REAL )
{
	pvalue_ = static_cast< const F >( source );
}


RealValue::RealValue( const CqlString& source ) : AbstractValue( CQL_REAL )
{
	if( sscanf( source.text(), "%f", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


RealValue::RealValue( const NC *source ) : AbstractValue( CQL_REAL )
{
	if( sscanf( source, "%f", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


RealValue::RealValue( const UC *source ) : AbstractValue( CQL_REAL )
{
	if( sscanf( reinterpret_cast< const NC* >( source ), "%f", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


RealValue& RealValue::operator = ( const RealValue& other )
{
	pvalue_ = other.pvalue_;
	RealValue& ncother = const_cast< RealValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


AbstractValue& RealValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_DECIMAL :
	case CQL_BIGINT :
		*this = RealValue( av.asString() );

	case CQL_SMALLINT :
		{
			SmallintValue& sv = dynamic_cast< SmallintValue& >( av );
			pvalue_ = sv.pvalue();
		}
		break;

	case CQL_INTEGER :
		{
			IntegerValue& iv = dynamic_cast< IntegerValue& >( av );
			pvalue_ = static_cast< F >( iv.pvalue() );
		}
		break;

	case CQL_REAL :
		{
			RealValue& rv = dynamic_cast< RealValue& >( av );
			pvalue_ = rv.pvalue_;
		}
		break;

	case CQL_FLOAT :
		{
			FloatValue& fv = dynamic_cast< FloatValue& >( av );
			pvalue_ = static_cast< F >( fv.pvalue() );
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


CqlConstants::CompareResult RealValue::compare( const RealValue& other ) const
{
	if( pvalue_ < other.pvalue_ )
		return THIS_LESS_THAN_OTHER;
	else if( pvalue_ > other.pvalue_ )
		return THIS_GREATER_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


bool RealValue::operator == ( const RealValue& other ) const
{
	return pvalue_ == other.pvalue_;
}


bool RealValue::operator > ( const RealValue& other ) const
{
	return pvalue_ > other.pvalue_;
}


bool RealValue::operator >= ( const RealValue& other ) const
{
	return pvalue_ >= other.pvalue_;
}


bool RealValue::operator < ( const RealValue& other ) const
{
	return pvalue_ < other.pvalue_;
}


bool RealValue::operator <= ( const RealValue& other ) const
{
	return pvalue_ <= other.pvalue_;
}


bool RealValue::operator ! ( void ) const
{
	if( pvalue_ )
		return false;
	else
		return true;
}


void RealValue::absoluteValue( void )
{
	if( pvalue_ < 0 )
		pvalue_ *= -1;
}


void RealValue::output( TempBuffer& tb ) const
{
	tb << pvalue_;
}


void RealValue::input( TempBuffer& tb )
{
	tb >> pvalue_;
}


UL RealValue::length( void ) const
{
	return sizeof( RealValue );
}


UL RealValue::streamLength( void ) const
{
	return fixedLength_;
}


NC RealValue::asChar() const
{
	NC sc = static_cast< const NC >( pvalue_ );
	if( sc < pvalue_ || sc > pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return sc;
}


S RealValue::asShort() const
{
	S s = static_cast< const S >( pvalue_ );
	if( s < pvalue_ || s > pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return s;
}


L RealValue::asLong() const
{
	L l = static_cast< const L >( pvalue_ );
	if( l < pvalue_ || l > pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return l;
}


BigintValue RealValue::asBigintValue() const
{
	return BigintValue( pvalue_ );
}


DecimalValue RealValue::asDecimalValue() const
{
	return DecimalValue( pvalue_ );
}


F RealValue::asFloat() const
{
	return pvalue_;
}


D RealValue::asDouble() const
{
	return static_cast< const D >( pvalue_ );
}


DateValue RealValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue RealValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue RealValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimestampValue();
#endif
}


const CqlString RealValue::asString( bool /* spacePadding */ ) const
{
	NC buffer[ 50 ];
	sprintf( buffer, "%f", pvalue_ );
	return CqlString( buffer );
}


void RealValue::operator << ( pUC& buf )
{
	memcpy( &pvalue_, buf, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void RealValue::operator >> ( pUC& buf )
{
	memcpy( buf, &pvalue_, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void RealValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( reinterpret_cast< UC * >( &pvalue_ ), sizeof( pvalue_ ) );
}


void RealValue::operator << ( BinaryValue& bv )
{
	memcpy( &pvalue_, bv.buffer(), sizeof( pvalue_ ) );
}


void RealValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void RealValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void RealValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void RealValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& RealValue::operator += ( AbstractValue& av )
{
	pvalue_ += av.asFloat();
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& RealValue::operator -= ( AbstractValue& av )
{
	pvalue_ -= av.asFloat();
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& RealValue::operator *= ( AbstractValue& av )
{
	pvalue_ *= av.asFloat();
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& RealValue::operator /= ( AbstractValue& av )
{
	pvalue_ /= av.asFloat();
	return dynamic_cast< AbstractValue& >( *this );
}


bool RealValue::operator > ( const AbstractValue& av ) const
{
	return pvalue_ > av.asFloat();
}


bool RealValue::operator >= ( const AbstractValue& av ) const
{
	return pvalue_ >= av.asFloat();
}


bool RealValue::operator < ( const AbstractValue& av ) const
{
	return pvalue_ < av.asFloat();
}


bool RealValue::operator <= ( const AbstractValue& av ) const
{
	return pvalue_ <= av.asFloat();
}


bool RealValue::operator == ( const AbstractValue& av ) const
{
	return pvalue_ == av.asFloat();
}


bool RealValue::operator != ( const AbstractValue& av ) const
{
	return pvalue_ != av.asFloat();
}


void RealValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	NC buf[ 100 ];
	sprintf( buf, "%f", pvalue_ );
	_output = buf;
}


US RealValue::dictionaryLength( void )
{
	return sizeof( bool ) + sizeof( pvalue_ );
}


void RealValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << pvalue_;
}


void RealValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> pvalue_;
}
