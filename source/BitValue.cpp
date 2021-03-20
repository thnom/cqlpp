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


const UL BitValue::fixedLength_ = sizeof( bool );


BitValue::BitValue( const BitValue& cother ) : AbstractValue( CQL_BIT ), pvalue_( cother.pvalue_ )
{
	BitValue& other = const_cast< BitValue& >( cother );
	if( other.nullflag() )
		setNullflag();
	else
		clearNullflag();
}


BitValue::BitValue( const CqlColumnTypes& ) : AbstractValue( CQL_BIT ), pvalue_( false )
{
}


BitValue::BitValue( pUC& source ) : AbstractValue( CQL_BIT )
{
	memcpy( &pvalue_, source, sizeof( pvalue_ ) );
	source += sizeof( pvalue_ );
}


BitValue::BitValue( const CqlString& source ) : AbstractValue( CQL_BIT )
{
	NC ch = source.text()[ 0 ];
	if( ch == 'Y' || ch == 'y' || ch == 'T' || ch == 't' )
		pvalue_ = true;
	else
		pvalue_ = false;
}


BitValue::BitValue( const NC *source ) : AbstractValue( CQL_BIT )
{
	NC ch = *source;
	if( ch == 'Y' || ch == 'y' || ch == 'T' || ch == 't' )
		pvalue_ = true;
	else
		pvalue_ = false;
}


BitValue::BitValue( const UC *source ) : AbstractValue( CQL_BIT )
{
	NC ch = *source;
	if( ch == 'Y' || ch == 'y' || ch == 'T' || ch == 't' )
		pvalue_ = true;
	else
		pvalue_ = false;
}


BitValue::BitValue( const NC source ) : AbstractValue( CQL_BIT )
{
	if( source )
		pvalue_ = true;
	else
		pvalue_ = false;
}


BitValue::BitValue( const D source ) : AbstractValue( CQL_BIT )
{
	if( source )
		pvalue_ = true;
	else
		pvalue_ = false;
}


BitValue::BitValue( const NI source ) : AbstractValue( CQL_BIT )
{
	if( source )
		pvalue_ = true;
	else
		pvalue_ = false;
}


BitValue::BitValue( const UNI source ) : AbstractValue( CQL_BIT )
{
	if( source )
		pvalue_ = true;
	else
		pvalue_ = false;
}


BitValue::BitValue( const US source ) : AbstractValue( CQL_BIT )
{
	if( source )
		pvalue_ = true;
	else
		pvalue_ = false;
}


BitValue::BitValue( const UL source ) : AbstractValue( CQL_BIT )
{
	if( source )
		pvalue_ = true;
	else
		pvalue_ = false;
}


BitValue& BitValue::operator = ( const BitValue& other )
{
	pvalue_ = other.pvalue_;
	return *this;
}


AbstractValue& BitValue::operator = ( const AbstractValue& cav )
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
			if( !dv )
				pvalue_ = false;
			else
				pvalue_ = true;
		}
		break;

	case CQL_BIGINT :
		{
			BigintValue& bv = dynamic_cast< BigintValue& >( av );
			if( !bv )
				pvalue_ = false;
			else
				pvalue_ = true;
		}
		break;

	case CQL_SMALLINT :
		{
			SmallintValue& sv = dynamic_cast< SmallintValue& >( av );
			if( sv.pvalue() )
				pvalue_ = true;
			else
				pvalue_ = false;
		}
		break;

	case CQL_INTEGER :
		{
			IntegerValue& iv = dynamic_cast< IntegerValue& >( av );
			if( iv.pvalue() )
				pvalue_ = true;
			else
				pvalue_ = false;
		}
		break;

	case CQL_REAL :
		{
			RealValue& rv = dynamic_cast< RealValue& >( av );
			if( rv.pvalue() )
				pvalue_ = true;
			else
				pvalue_ = false;
		}
		break;

	case CQL_FLOAT :
		{
			FloatValue& fv = dynamic_cast< FloatValue& >( av );
			if( fv.pvalue() )
				pvalue_ = true;
			else
				pvalue_ = false;
		}
		break;

	case CQL_BIT :
		{
			BitValue& bv = dynamic_cast< BitValue& >( av );
			if( bv.pvalue() )
				pvalue_ = true;
			else
				pvalue_ = false;
		}
		break;

	case CQL_TINYINT :
		{
			TinyintValue& tv = dynamic_cast< TinyintValue& >( av );
			if( tv.pvalue() )
				pvalue_ = true;
			else
				pvalue_ = false;
		}
		break;
	}

	return *this;
}


CqlConstants::CompareResult BitValue::compare( const BitValue& other ) const
{
	if( pvalue_ && !other.pvalue_ )
		return THIS_LESS_THAN_OTHER;
	else if( !pvalue_ && other.pvalue_ )
		return THIS_GREATER_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


void BitValue::absoluteValue( void )
{
	throw InvalidParameterException( __FILE__, __LINE__ );
}


void BitValue::output( TempBuffer& tb ) const
{
	tb << pvalue_;
}


void BitValue::input( TempBuffer& tb )
{
	tb >> pvalue_;
}


UL BitValue::length( void ) const
{
	return sizeof( BitValue );
}


UL BitValue::streamLength( void ) const
{
	return fixedLength_;
}


SC BitValue::asChar() const
{
	return pvalue_;
}


S BitValue::asShort() const
{
	return static_cast< const S >( pvalue_ );
}


L BitValue::asLong() const
{
	return static_cast< const L >( pvalue_ );
}


BigintValue BitValue::asBigintValue() const
{
	return BigintValue( static_cast< NI >( pvalue_ ) );
}


DecimalValue BitValue::asDecimalValue() const
{
	return DecimalValue( static_cast< NI >( pvalue_ ) );
}


F BitValue::asFloat() const
{
	return static_cast< const F >( pvalue_ );
}


D BitValue::asDouble() const
{
	return static_cast< const D >( pvalue_ );
}


DateValue BitValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue BitValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue BitValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimestampValue();
#endif
}


const CqlString BitValue::asString( bool /* spacePadding */ ) const
{
	NC buffer[ 50 ];
	sprintf( buffer, "%d", static_cast< const NI >( pvalue_ ) );
	return CqlString( buffer );
}


void BitValue::operator << ( pUC& buf )
{
	memcpy( &pvalue_, buf, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void BitValue::operator >> ( pUC& buf )
{
	memcpy( buf, &pvalue_, sizeof( pvalue_ ) );
	buf += sizeof( pvalue_ );
}


void BitValue::operator >> ( BinaryValue& bv )
{
	UC _length = sizeof( pvalue_ );
	bv = BinaryValue( reinterpret_cast< UC * >( &pvalue_ ), _length );
}


void BitValue::operator << ( BinaryValue& bv )
{
	memcpy( &pvalue_, bv.buffer(), sizeof( pvalue_ ) );
}


void BitValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void BitValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void BitValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void BitValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& BitValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnLogicalDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& BitValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnLogicalDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& BitValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnLogicalDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& BitValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnLogicalDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


bool BitValue::operator == ( const AbstractValue& av ) const
{
	L l = av.asLong();
	if( l && pvalue_ || !l && !pvalue_ )
		return true;
	else
		return false;
}


bool BitValue::operator != ( const AbstractValue& av ) const
{
	if( *this == av )
		return false;
	else
		return true;
}


bool BitValue::operator > ( const AbstractValue& av ) const
{
	L l = av.asLong();
	if( !l && pvalue_ )
		return true;
	else
		return false;
}


bool BitValue::operator >= ( const AbstractValue& av ) const
{
	L l = av.asLong();
	if( !l || ( l && pvalue_ ) )
		return true;
	else
		return false;
}


bool BitValue::operator < ( const AbstractValue& av ) const
{
	L l = av.asLong();
	if( l && !pvalue_ )
		return true;
	else
		return false;
}


bool BitValue::operator <= ( const AbstractValue& av ) const
{
	L l = av.asLong();
	if( l || ( !l && !pvalue_ ) )
		return true;
	else
		return false;
}


bool BitValue::operator ! ( void ) const
{
	if( pvalue_ )
		return false;
	else
		return true;
}


US BitValue::dictionaryLength( void )
{
	return static_cast< US >( sizeof( bool ) + sizeof( pvalue_ ) );
}


void BitValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	if( pvalue_ )
		_output = "true";
	else
		_output = "false";
}


void BitValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << pvalue_;
}


void BitValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> pvalue_;
}
