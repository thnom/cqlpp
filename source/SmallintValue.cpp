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


const UL SmallintValue::fixedLength_ = sizeof( S );


SmallintValue::SmallintValue( pUC& source ) : AbstractValue( CQL_SMALLINT )
{
	memcpy( &pvalue_, source, sizeof( pvalue_ ) );
	source += sizeof( pvalue_ );
}


SmallintValue::SmallintValue( const CqlColumnTypes& ) : AbstractValue( CQL_SMALLINT ), pvalue_( 0 )
{
}


SmallintValue::SmallintValue( const SmallintValue& cother ) : AbstractValue( CQL_SMALLINT ), pvalue_( cother.pvalue_ )
{
	SmallintValue& other = const_cast< SmallintValue& >( cother );
	if( other.nullflag() )
		setNullflag();
	else
		clearNullflag();
}


SmallintValue::SmallintValue( const L l ) : AbstractValue( CQL_SMALLINT )
{
	pvalue_ = static_cast< const S >( l );
	if( pvalue_ != l )
		throw ConversionException( __FILE__, __LINE__ );
}


SmallintValue::SmallintValue( const F f ) : AbstractValue( CQL_SMALLINT )
{
	pvalue_ = static_cast< const S >( f );
}


SmallintValue::SmallintValue( const D d ) : AbstractValue( CQL_SMALLINT )
{
	pvalue_ = static_cast< const S >( d );
}


SmallintValue::SmallintValue( const BigintValue& bv ) : AbstractValue( CQL_SMALLINT )
{
	D d;
	if( sscanf( bv.asString().text(), "%lf", &d ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );

	pvalue_ = static_cast< S >( d );
}


SmallintValue::SmallintValue( const DecimalValue& dv ) : AbstractValue( CQL_SMALLINT )
{
	D d;
	if( sscanf( dv.asString().text(), "%lf", &d ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );

	pvalue_ = static_cast< S >( d );
}


SmallintValue::SmallintValue( const CqlString& source ) : AbstractValue( CQL_SMALLINT )
{
	if( sscanf( source.text(), "%hd", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


SmallintValue::SmallintValue( const NC *source ) : AbstractValue( CQL_SMALLINT )
{
	if( sscanf( source, "%hd", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


SmallintValue::SmallintValue( const UC *source ) : AbstractValue( CQL_SMALLINT )
{
	if( sscanf( reinterpret_cast< const NC* >( source ), "%hd", &pvalue_ ) != 1 )
		throw ConversionException( __FILE__, __LINE__ );
}


SmallintValue::SmallintValue( const NC source ) : AbstractValue( CQL_SMALLINT )
{
	pvalue_ = static_cast< const S >( source );
	if( pvalue_ != source )
		throw SizeConversionException( __FILE__, __LINE__ );
}


SmallintValue::SmallintValue( const NI source ) : AbstractValue( CQL_SMALLINT )
{
	pvalue_ = static_cast< const S >( source );
	if( pvalue_ != source )
		throw SizeConversionException( __FILE__, __LINE__ );
}


SmallintValue::SmallintValue( const UNI source ) : AbstractValue( CQL_SMALLINT )
{
	pvalue_ = static_cast< const S >( source );
	if( static_cast< L >( pvalue_ ) != static_cast< const L >( source ) )
		throw SizeConversionException( __FILE__, __LINE__ );
}


SmallintValue::SmallintValue( const UL source ) : AbstractValue( CQL_SMALLINT )
{
	pvalue_ = static_cast< const S >( source );
	if( static_cast< UL >( pvalue_ ) != source )
		throw SizeConversionException( __FILE__, __LINE__ );
}


SmallintValue::SmallintValue( const US source ) : AbstractValue( CQL_SMALLINT )
{
	pvalue_ = static_cast< const S >( source );
	if( pvalue_ != source )
		throw SizeConversionException( __FILE__, __LINE__ );
}


SmallintValue& SmallintValue::operator = ( const SmallintValue& other )
{
	pvalue_ = other.pvalue_;
	SmallintValue& ncother = const_cast< SmallintValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


AbstractValue& SmallintValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_DECIMAL :
		{
			DecimalValue& dv = dynamic_cast< DecimalValue& >( av );
			*this = SmallintValue( dv );
		}
		break;

	case CQL_BIGINT :
		{
			BigintValue& bv = dynamic_cast< BigintValue& >( av );
			*this = SmallintValue( bv );
		}
		break;

	case CQL_SMALLINT :
		{
			SmallintValue& sv = dynamic_cast< SmallintValue& >( av );
			pvalue_ = sv.pvalue_;
		}
		break;

	case CQL_INTEGER :
		{
			IntegerValue& iv = dynamic_cast< IntegerValue& >( av );
			pvalue_ = static_cast< S >( iv.pvalue() );
			if( static_cast< L >( pvalue_ ) != iv.pvalue() )
				throw SizeConversionException( __FILE__, __LINE__ );
		}
		break;

	case CQL_REAL :
		{
			RealValue& rv = dynamic_cast< RealValue& >( av );
			pvalue_ = static_cast< S >( rv.pvalue() );
		}
		break;

	case CQL_FLOAT :
		{
			FloatValue& fv = dynamic_cast< FloatValue& >( av );
			pvalue_ = static_cast< S >( fv.pvalue() );
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
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	return *this;
}

CqlConstants::CompareResult SmallintValue::compare( const SmallintValue& other ) const
{
	if( pvalue_ < other.pvalue_ )
		return THIS_LESS_THAN_OTHER;
	else if( pvalue_ > other.pvalue_ )
		return THIS_GREATER_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


bool SmallintValue::operator == ( const SmallintValue& other ) const
{
	return pvalue_ == other.pvalue_;
}


bool SmallintValue::operator == ( const AbstractValue& av ) const
{
	return pvalue_ == av.asShort();
}


bool SmallintValue::operator != ( const AbstractValue& av ) const
{
	return pvalue_ != av.asShort();
}


bool SmallintValue::operator > ( const SmallintValue& other ) const
{
	return pvalue_ > other.pvalue_;
}


bool SmallintValue::operator > ( const AbstractValue& av ) const
{
	return pvalue_ > av.asShort();
}


bool SmallintValue::operator >= ( const SmallintValue& other ) const
{
	return pvalue_ >= other.pvalue_;
}


bool SmallintValue::operator >= ( const AbstractValue& av ) const
{
	return pvalue_ >= av.asShort();
}


bool SmallintValue::operator < ( const SmallintValue& other ) const
{
	return pvalue_ < other.pvalue_;
}


bool SmallintValue::operator < ( const AbstractValue& av ) const
{
	return pvalue_ < av.asShort();
}


bool SmallintValue::operator <= ( const SmallintValue& other ) const
{
	return pvalue_ <= other.pvalue_;
}


bool SmallintValue::operator <= ( const AbstractValue& av ) const
{
	return pvalue_ <= av.asShort();
}


bool SmallintValue::operator ! ( void ) const
{
	if( pvalue_ )
		return false;
	else
		return true;
}


void SmallintValue::absoluteValue( void )
{
	if( pvalue_ < 0 )
		pvalue_ *= -1;
}


void SmallintValue::output( TempBuffer& tb ) const
{
	tb << pvalue_;
}


void SmallintValue::input( TempBuffer& tb )
{
	tb >> pvalue_;
}


UL SmallintValue::length( void ) const
{
	return sizeof( SmallintValue );
}


UL SmallintValue::streamLength( void ) const
{
	return fixedLength_;
}


NC SmallintValue::asChar() const
{
	NC sc = static_cast< const NC >( pvalue_ );
	if( sc != pvalue_ )
		throw SizeConversionException( __FILE__, __LINE__ );

	return sc;
}


S SmallintValue::asShort() const
{
	return pvalue_;
}


L SmallintValue::asLong() const
{
	return static_cast< const L >( pvalue_ );
}


BigintValue SmallintValue::asBigintValue() const
{
	return BigintValue( pvalue_ );
}


DecimalValue SmallintValue::asDecimalValue() const
{
	return DecimalValue( pvalue_ );
}


F SmallintValue::asFloat() const
{
	return static_cast< const F >( pvalue_ );
}


D SmallintValue::asDouble() const
{
	return static_cast< const D >( pvalue_ );
}


DateValue SmallintValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue SmallintValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue SmallintValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for stupid compilers
	return TimestampValue();
#endif
}


const CqlString SmallintValue::asString( bool /* spacePadding */ ) const
{
	NC buffer[ 50 ];
	sprintf( buffer, "%d", static_cast< const NI >( pvalue_ ) );
	return CqlString( buffer );
}


void SmallintValue::operator << ( pUC& buf )
{
	memcpy( &pvalue_, buf, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void SmallintValue::operator >> ( pUC& buf )
{
	memcpy( buf, &pvalue_, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void SmallintValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( reinterpret_cast< UC * >( &pvalue_ ), sizeof( pvalue_ ) );
}


void SmallintValue::operator << ( BinaryValue& bv )
{
	memcpy( &pvalue_, bv.buffer(), sizeof( pvalue_ ) );
}


void SmallintValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void SmallintValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void SmallintValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void SmallintValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& SmallintValue::operator += ( AbstractValue& av )
{
	NI sum = pvalue_ + av.asShort();
	pvalue_ = static_cast< S >( sum );
	if( pvalue_ != sum )
		throw SizeConversionException( __FILE__, __LINE__ );
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& SmallintValue::operator -= ( AbstractValue& av )
{
	pvalue_ = static_cast< S >( pvalue_ - av.asShort() );
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& SmallintValue::operator *= ( AbstractValue& av )
{
	pvalue_ = static_cast< S >( pvalue_ * av.asShort() );
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& SmallintValue::operator /= ( AbstractValue& av )
{
	pvalue_ = static_cast< S >( pvalue_ / av.asShort() );
	return dynamic_cast< AbstractValue& >( *this );
}


void SmallintValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	NC buf[ 100 ];
	sprintf( buf, "%d", static_cast< NI >( pvalue_ ) );
	_output = buf;
}


void SmallintValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << pvalue_;
}


void SmallintValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> pvalue_;
}


US SmallintValue::dictionaryLength( void )
{
	return sizeof( bool ) + sizeof( S );
}
