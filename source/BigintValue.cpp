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


const UL BigintValue::fixedLength_ = sizeof( US ) + sizeof( US ) + sizeof( US ) + sizeof( US ) + sizeof( CqlConstants::SignValues );


BigintValue::BigintValue( const BigintValue& other ) : AbstractValue( CQL_BIGINT )
{
	bigintLiteral_.highest_ = other.bigintLiteral_.highest_;
	bigintLiteral_.higher_ = other.bigintLiteral_.higher_;
	bigintLiteral_.lower_ = other.bigintLiteral_.lower_;
	bigintLiteral_.lowest_ = other.bigintLiteral_.lowest_;

	if( const_cast< BigintValue& >( other ).nullflag() )
		setNullflag();
}


BigintValue::BigintValue( pUC& data ) : AbstractValue( CQL_BIGINT )
{
	memcpy( &bigintLiteral_.highest_, data, sizeof( bigintLiteral_.highest_ ) );
	data += sizeof( bigintLiteral_.highest_ );
	memcpy( &bigintLiteral_.higher_, data, sizeof( bigintLiteral_.higher_ ) );
	data += sizeof( bigintLiteral_.higher_ );
	memcpy( &bigintLiteral_.lower_, data, sizeof( bigintLiteral_.lower_ ) );
	data += sizeof( bigintLiteral_.lower_ );
	memcpy( &bigintLiteral_.lowest_, data, sizeof( bigintLiteral_.lowest_ ) );
	data += sizeof( bigintLiteral_.lowest_ );
	memcpy( &bigintLiteral_.sign_, data, sizeof( bigintLiteral_.sign_ ) );
	data += sizeof( bigintLiteral_.sign_ );
}


BigintValue::BigintValue( const CqlColumnTypes& ) : AbstractValue( CQL_BIGINT )
{
	bigintLiteral_.highest_ = 0;
	bigintLiteral_.higher_ = 0;
	bigintLiteral_.lower_ = 0;
	bigintLiteral_.lowest_ = 0;
	bigintLiteral_.sign_ = SV_POSITIVE;
}


BigintValue::BigintValue( const CqlString& str ) : AbstractValue( CQL_BIGINT )
{
	*this = str;
}


BigintValue::BigintValue( const NC *source ) : AbstractValue( CQL_BIGINT )
{
	*this = CqlString( source );
}


BigintValue::BigintValue( const UC *source ) : AbstractValue( CQL_BIGINT )
{
	*this = CqlString( reinterpret_cast< const NC* >( source ) );
}


BigintValue::BigintValue( const NC s ) : AbstractValue( CQL_BIGINT )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%d", static_cast< const NI >( s ) );
	*this = buffer;
}


BigintValue::BigintValue( const S s ) : AbstractValue( CQL_BIGINT )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%hd", s );
	*this = buffer;
}


BigintValue::BigintValue( const US s ) : AbstractValue( CQL_BIGINT )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%hu", s );
	*this = buffer;
}


BigintValue::BigintValue( const NI i ) : AbstractValue( CQL_BIGINT )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%d", i );
	*this = buffer;
}


BigintValue::BigintValue( const UNI i ) : AbstractValue( CQL_BIGINT )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%u", i );
	*this = buffer;
}


BigintValue::BigintValue( const L l ) : AbstractValue( CQL_BIGINT )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%ld", l );
	*this = buffer;
}


BigintValue::BigintValue( const UL l ) : AbstractValue( CQL_BIGINT )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%lu", l );
	*this = buffer;
}


BigintValue::BigintValue( const D d ) : AbstractValue( CQL_BIGINT )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%f", d );
	*this = buffer;
}


BigintValue::BigintValue( DecimalValue& dv ) : AbstractValue( CQL_BIGINT )
{
	*this = dv.asString();
}


BigintValue::~BigintValue( void )
{
}


BigintValue& BigintValue::operator = ( const CqlString& str )
{
	US tdigit;
	UL ul1, ul2;
	UNI loop, limit;

	bigintLiteral_.highest_ = bigintLiteral_.higher_ = bigintLiteral_.lower_ = bigintLiteral_.lowest_ = 0;

	const char * p = const_cast<const char *>(str.text());
	if( *p == '-' )
	{
		bigintLiteral_.sign_ = SV_NEGATIVE;
		p++;
	}
	else
		bigintLiteral_.sign_ = SV_POSITIVE;

	for( loop = 0, limit = str.length() - 1; loop < limit; loop++, p++ )
	{
		ul1 = bigintLiteral_.lowest_;
		ul1 *= 10;
		bigintLiteral_.lowest_ = ((US)(ul1 & 0x0000ffff));
		if( ul1 & 0xffff0000 )
		{
			ul2 = ul1 >> 16;
			ul1 = bigintLiteral_.lower_ + ul2;
			bigintLiteral_.lower_ = ((US)(ul1 & 0x0000ffff));
			if( ul1 & 0xffff0000 )
			{
				ul2 = ul1 >> 16;
				ul1 = bigintLiteral_.higher_ + ul2;
				bigintLiteral_.higher_ = ((US)(ul1 & 0x0000ffff));
				if( ul1 & 0xffff0000 )
				{
					ul2 = ul1 >> 16;
					bigintLiteral_.highest_ = ((US)( bigintLiteral_.highest_ + ul2 ) );
				}
			}
		}
			
		tdigit = ((US)( *p - 0x30 ) );
		ul1 = bigintLiteral_.lowest_ + tdigit;
		bigintLiteral_.lowest_ = ((US)(ul1 & 0x0000ffff));
		if( ul1 & 0xffff0000 )
		{
			ul2 = ul1 >> 16;
			ul1 = bigintLiteral_.lower_ + ul2;
			bigintLiteral_.lower_ = ((US)(ul1 & 0x0000ffff));
			if( ul1 & 0xffff0000 )
			{
				ul2 = ul1 >> 16;
				ul1 = bigintLiteral_.higher_ + ul2;
				bigintLiteral_.higher_ = ((US)(ul1 & 0x0000ffff));
				if( ul1 & 0xffff0000 )
				{
					ul2 = ul1 >> 16;
					bigintLiteral_.highest_ = ((US)( bigintLiteral_.highest_ + ul2 ) );
				}
			}
		}
	}

	return *this;
}


BigintValue& BigintValue::operator = ( const NC *str )
{
	*this = CqlString( str );
	return *this;
}


BigintValue& BigintValue::operator = ( const BigintValue& other )
{
	bigintLiteral_.highest_ = other.bigintLiteral_.highest_;
	bigintLiteral_.higher_ = other.bigintLiteral_.higher_;
	bigintLiteral_.lower_ = other.bigintLiteral_.lower_;
	bigintLiteral_.lowest_ = other.bigintLiteral_.lowest_;
	bigintLiteral_.sign_ = other.bigintLiteral_.sign_;
	BigintValue& ncother = const_cast< BigintValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


AbstractValue& BigintValue::operator = ( const AbstractValue& cav )
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

	case CQL_BIGINT :
		*this = dynamic_cast< BigintValue& >( av );
		break;

	case CQL_DECIMAL :
		{
			DecimalValue& dv = dynamic_cast< DecimalValue& >( av );
			*this = dv.asBigintValue();
		}
		break;

	case CQL_SMALLINT :
		{
			SmallintValue& sv = dynamic_cast< SmallintValue& >( av );
			*this = BigintValue( sv );
		}
		break;

	case CQL_INTEGER :
		{
			IntegerValue& iv = dynamic_cast< IntegerValue& >( av );
			*this = BigintValue( iv );
		}
		break;

	case CQL_REAL :
		{
			RealValue& rv = dynamic_cast< RealValue& >( av );
			*this = BigintValue( rv );
		}
		break;

	case CQL_FLOAT :
		{
			FloatValue& fv = dynamic_cast< FloatValue& >( av );
			*this = BigintValue( fv );
		}
		break;

	case CQL_BIT :
		{
			BitValue& bv = dynamic_cast< BitValue& >( av );
			*this = BigintValue( bv );
		}
		break;

	case CQL_TINYINT :
		{
			TinyintValue& tv = dynamic_cast< TinyintValue& >( av );
			*this = BigintValue( tv );
		}
		break;
	}

	return *this;
}


CqlConstants::CompareResult BigintValue::compareMantissa( const BigintValue& other ) const
{
	if( bigintLiteral_.highest_ > other.bigintLiteral_.highest_ )
		return THIS_GREATER_THAN_OTHER;
	else if( bigintLiteral_.highest_ < other.bigintLiteral_.highest_ )
		return THIS_LESS_THAN_OTHER;
	else if( bigintLiteral_.higher_ > other.bigintLiteral_.higher_ )
		return THIS_GREATER_THAN_OTHER;
	else if( bigintLiteral_.higher_ < other.bigintLiteral_.higher_ )
		return THIS_LESS_THAN_OTHER;
	else if( bigintLiteral_.lower_ > other.bigintLiteral_.lower_ )
		return THIS_GREATER_THAN_OTHER;
	else if( bigintLiteral_.lower_ < other.bigintLiteral_.lower_ )
		return THIS_LESS_THAN_OTHER;
	else if( bigintLiteral_.lowest_ > other.bigintLiteral_.lowest_ )
		return THIS_GREATER_THAN_OTHER;
	else if( bigintLiteral_.lowest_ < other.bigintLiteral_.lowest_ )
		return THIS_LESS_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


CqlConstants::CompareResult BigintValue::compare( const BigintValue& other ) const
{
	if( bigintLiteral_.sign_ && !other.bigintLiteral_.sign_ )
		return THIS_LESS_THAN_OTHER;
	else if( other.bigintLiteral_.sign_ && !bigintLiteral_.sign_ )
		return THIS_GREATER_THAN_OTHER;

	CompareResult compareResult = compareMantissa( other );
	if( compareResult == THIS_EQUAL_TO_OTHER )
		return THIS_EQUAL_TO_OTHER;

	if( bigintLiteral_.sign_ )
	{
		if( compareResult == THIS_LESS_THAN_OTHER )
			return THIS_GREATER_THAN_OTHER;
		else  //  if not required here because equal and lower have been checked
			return THIS_LESS_THAN_OTHER;
	}
	else
		return compareResult;
}


bool BigintValue::operator == ( const AbstractValue& other ) const
{
	return compare( other.asBigintValue() ) == THIS_EQUAL_TO_OTHER;
}


bool BigintValue::operator != ( const AbstractValue& other ) const
{
	if( *this == other )
		return false;
	else
		return true;
}


bool BigintValue::operator == ( const BigintValue& other ) const
{
	return compare( other ) == THIS_EQUAL_TO_OTHER;
}


bool BigintValue::operator > ( const AbstractValue& other ) const
{
	return compare( other.asBigintValue() ) == THIS_GREATER_THAN_OTHER;
}


bool BigintValue::operator > ( const BigintValue& other ) const
{
	return compare( other ) == THIS_GREATER_THAN_OTHER;
}


bool BigintValue::operator >= ( const AbstractValue& other ) const
{
	return compare( other.asBigintValue() ) != THIS_LESS_THAN_OTHER;
}


bool BigintValue::operator >= ( const BigintValue& other ) const
{
	return compare( other ) != THIS_LESS_THAN_OTHER;
}


bool BigintValue::operator < ( const AbstractValue& other ) const
{
	return compare( other.asBigintValue() ) == THIS_LESS_THAN_OTHER;
}


bool BigintValue::operator < ( const BigintValue& other ) const
{
	return compare( other ) == THIS_LESS_THAN_OTHER;
}


bool BigintValue::operator <= ( const AbstractValue& other ) const
{
	return compare( other.asBigintValue() ) != THIS_GREATER_THAN_OTHER;
}


bool BigintValue::operator <= ( const BigintValue& other ) const
{
	return compare( other ) != THIS_GREATER_THAN_OTHER;
}


void BigintValue::absoluteValue( void )
{
	bigintLiteral_.sign_ = SV_POSITIVE;
}


void BigintValue::output( TempBuffer& tb ) const
{
	tb << bigintLiteral_.highest_ << bigintLiteral_.higher_ << bigintLiteral_.lower_ << bigintLiteral_.lowest_ << bigintLiteral_.sign_;
}


void BigintValue::input( TempBuffer& tb )
{
	tb >> bigintLiteral_.highest_ >> bigintLiteral_.higher_ >> bigintLiteral_.lower_ >> bigintLiteral_.lowest_ >> bigintLiteral_.sign_;
}


SC BigintValue::asChar( void ) const
{
	if( bigintLiteral_.highest_ || bigintLiteral_.higher_ || bigintLiteral_.lower_ || ( bigintLiteral_.lowest_ != ( bigintLiteral_.lowest_ & 0x00ff ) ) )
		throw 	IllegalTypeConversionException( __FILE__, __LINE__ );

	//  cast is O.K., because the test (bigintLiteral_.lowest_ & 0x00ff) passed
	return ((SC)bigintLiteral_.lowest_);
}


S BigintValue::asShort( void ) const
{
	if( bigintLiteral_.highest_ || bigintLiteral_.higher_ || bigintLiteral_.lower_ )
		throw IllegalTypeConversionException( __FILE__, __LINE__ );

	return bigintLiteral_.lowest_;
}


L BigintValue::asLong( void ) const
{
	if( bigintLiteral_.highest_ || bigintLiteral_.higher_ )
		throw IllegalTypeConversionException( __FILE__, __LINE__ );

	L tval = ( ( bigintLiteral_.lower_ << 8 ) | bigintLiteral_.lowest_ );
	return tval;
}


BigintValue BigintValue::asBigintValue( void ) const
{
	return *this;
}


DecimalValue BigintValue::asDecimalValue( void ) const
{
	DecimalValue dv( *this );
	return dv;
}


F BigintValue::asFloat( void ) const
{
	D d = asDouble();
	return ((F)d);
}


D BigintValue::asDouble( void ) const
{
	D d;

	d = bigintLiteral_.highest_;
	d *= 65535;
	d += bigintLiteral_.higher_;
	d *= 65535;
	d += bigintLiteral_.lower_;
	d *= 65535;
	d += bigintLiteral_.lowest_;

	return d;
}


DateValue BigintValue::asDateValue( void ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

	//  for very stupid compilers
#if defined( _MSC_VER ) && _MSC_VER != 1200
  	DateValue dv;
	return dv;
#endif
}


TimeValue BigintValue::asTimeValue( void ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

	//  for very stupid compilers
#if defined( _MSC_VER ) && _MSC_VER != 1200
	TimeValue tv;
	return tv;
#endif
}


TimestampValue BigintValue::asTimestampValue( void ) const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

	//  for very stupid compilers
#if defined( _MSC_VER ) && _MSC_VER != 1200
 	TimestampValue tv;
	return tv;
#endif
}


UL BigintValue::length( void ) const
{
	return sizeof( bigintLiteral_.highest_ ) + sizeof( bigintLiteral_.higher_ ) + sizeof( bigintLiteral_.lower_ ) + sizeof( bigintLiteral_.lowest_ ) + sizeof( bigintLiteral_.sign_ );
}


UL BigintValue::streamLength( void ) const
{
	return fixedLength_;
}


const CqlString BigintValue::asString( bool /* spacePadding */ ) const
{
	D dHighest = static_cast< const D >( bigintLiteral_.highest_ ) * pow( static_cast< D >( 2 ), static_cast< D >( 24 ) );
	D dHigher = static_cast< const D >( bigintLiteral_.higher_ ) * pow( static_cast< D >( 2 ), static_cast< D >( 16 ) );
	D dLower = static_cast< const D >( bigintLiteral_.lower_ ) * pow( static_cast< D >( 2 ), static_cast< D >( 8 ) );
	D d = static_cast< const D >( bigintLiteral_.lowest_ ) + dLower + dHigher + dHighest;
	if( bigintLiteral_.sign_ )
		d *= -1;

	NC buffer[ 50 ];
	sprintf( buffer, "%f", d );
	return CqlString( buffer );
}


void BigintValue::operator << ( pUC& buf )
{
	memcpy( &bigintLiteral_.highest_, buf, sizeof( bigintLiteral_.highest_ ) );
	buf += sizeof( bigintLiteral_.highest_ );
	memcpy( &bigintLiteral_.higher_, buf, sizeof( bigintLiteral_.higher_ ) );
	buf += sizeof( bigintLiteral_.higher_ );
	memcpy( &bigintLiteral_.lower_, buf, sizeof( bigintLiteral_.lower_ ) );
	buf += sizeof( bigintLiteral_.lower_ );
	memcpy( &bigintLiteral_.lowest_, buf, sizeof( bigintLiteral_.lowest_ ) );
	buf += sizeof( bigintLiteral_.lowest_ );
	memcpy( &bigintLiteral_.sign_, buf, sizeof( bigintLiteral_.sign_ ) );
	buf += sizeof( bigintLiteral_.sign_ );
}


void BigintValue::operator >> ( pUC& buf )
{
	memcpy( buf, &bigintLiteral_.highest_, sizeof( bigintLiteral_.highest_ ) );
	buf += sizeof( bigintLiteral_.highest_ );
	memcpy( buf, &bigintLiteral_.higher_, sizeof( bigintLiteral_.higher_ ) );
	buf += sizeof( bigintLiteral_.higher_ );
	memcpy( buf, &bigintLiteral_.lower_, sizeof( bigintLiteral_.lower_ ) );
	buf += sizeof( bigintLiteral_.lower_ );
	memcpy( buf, &bigintLiteral_.lowest_, sizeof( bigintLiteral_.lowest_ ) );
	buf += sizeof( bigintLiteral_.lowest_ );
	memcpy( buf, &bigintLiteral_.sign_, sizeof( bigintLiteral_.sign_ ) );
	buf += sizeof( bigintLiteral_.sign_ );
}


void BigintValue::operator >> ( BinaryValue& bv )
{
	size_t size = sizeof( bigintLiteral_.highest_ ) + sizeof( bigintLiteral_.higher_ ) + sizeof( bigintLiteral_.lower_ ) + sizeof( bigintLiteral_.lowest_ ) + sizeof( bigintLiteral_.sign_ );

	UC *tempBuffer = new UC[ size ];
	if( !tempBuffer )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	UC *p = tempBuffer;
	memcpy( p, &bigintLiteral_.highest_, sizeof( bigintLiteral_.highest_ ) );
	p += sizeof( bigintLiteral_.highest_ );
	memcpy( p, &bigintLiteral_.higher_, sizeof( bigintLiteral_.higher_ ) );
	p += sizeof( bigintLiteral_.higher_ );
	memcpy( p, &bigintLiteral_.lower_, sizeof( bigintLiteral_.lower_ ) );
	p += sizeof( bigintLiteral_.lower_ );
	memcpy( p, &bigintLiteral_.lowest_, sizeof( bigintLiteral_.lowest_ ) );
	p += sizeof( bigintLiteral_.lowest_ );
	memcpy( p, &bigintLiteral_.sign_, sizeof( bigintLiteral_.sign_ ) );

	UC _length = static_cast< UC >( size );
	bv = BinaryValue( tempBuffer, _length );
	delete tempBuffer;
}


void BigintValue::operator << ( BinaryValue& bv )
{
	UC *p = bv.buffer();
	memcpy( &bigintLiteral_.highest_, p, sizeof( bigintLiteral_.highest_ ) );
	p += sizeof( bigintLiteral_.highest_ );
	memcpy( &bigintLiteral_.higher_, p, sizeof( bigintLiteral_.higher_ ) );
	p += sizeof( bigintLiteral_.higher_ );
	memcpy( &bigintLiteral_.lower_, p, sizeof( bigintLiteral_.lower_ ) );
	p += sizeof( bigintLiteral_.lower_ );
	memcpy( &bigintLiteral_.lowest_, p, sizeof( bigintLiteral_.lowest_ ) );
	p += sizeof( bigintLiteral_.lowest_ );
	memcpy( &bigintLiteral_.sign_, p, sizeof( bigintLiteral_.sign_ ) );
}


void BigintValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void BigintValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void BigintValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void BigintValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


bool BigintValue::operator ! ( void ) const
{
	if( bigintLiteral_.lowest_ || bigintLiteral_.lower_ || bigintLiteral_.higher_ || bigintLiteral_.highest_ )
		return false;

	return true;
}


AbstractValue& BigintValue::operator += ( AbstractValue& av )
{
	BigintValue other = av.asBigintValue();
	BigintValue tOther, tThis;
	UL ul1, ul2;

	if( bigintLiteral_.sign_ == SV_POSITIVE && other.bigintLiteral_.sign_ == SV_NEGATIVE )
	{
		tOther = *this;
		tOther.bigintLiteral_.sign_ = SV_POSITIVE;
		*this -= dynamic_cast< AbstractValue& >( tOther );
		return dynamic_cast< AbstractValue& >( *this );
	}
	else if( bigintLiteral_.sign_ == SV_NEGATIVE && other.bigintLiteral_.sign_ == SV_POSITIVE )
	{
		tThis = other;
		tOther = *this;
		tOther.bigintLiteral_.sign_ = SV_POSITIVE;
		tThis -= dynamic_cast< AbstractValue& >( tOther );
		*this = tThis;
		return *this;
	}

	//
	//  at this point, either both signs are positive or both
	//  are negative.  We add the values and leave the result
	//  sign where it is
	//

	ul1 = bigintLiteral_.lowest_ + other.bigintLiteral_.lowest_;
	bigintLiteral_.lowest_ = ((US)(ul1 & 0x0000ffff));
	if( ul1 & 0xffff0000 )
	{
		ul2 = ul1 >> 16;
		ul1 = bigintLiteral_.lower_ + ul2;
		bigintLiteral_.lower_ = ((US)(ul1 & 0x0000ffff));
		if( ul1 & 0xffff0000 )
		{
			ul2 = ul1 >> 16;
			ul1 = bigintLiteral_.higher_ + ul2;
			bigintLiteral_.higher_ = ((US)(ul1 & 0x0000ffff));
			if( ul1 & 0xffff0000 )
			{
				ul2 = ul1 >> 16;
				bigintLiteral_.highest_ = ((S)( bigintLiteral_.highest_ + ul2 ) );
			}
		}
	}

	ul1 = bigintLiteral_.lower_ + other.bigintLiteral_.lower_;
	bigintLiteral_.lower_ = ((US)(ul1 & 0x0000ffff));
	if( ul1 & 0xffff0000 )
	{
		ul2 = ul1 >> 16;
		ul1 = bigintLiteral_.higher_ + ul2;
		bigintLiteral_.higher_ = ((US)(ul1 & 0x0000ffff));
		if( ul1 & 0xffff0000 )
		{
			ul2 = ul1 >> 16;
			bigintLiteral_.highest_ = ((S)( bigintLiteral_.highest_ + ul2 ) );
		}
	}

	ul1 = bigintLiteral_.higher_ + other.bigintLiteral_.higher_;
	bigintLiteral_.higher_ = ((US)(ul1 & 0xffff0000));
	if( ul1 & 0xffff0000 )
	{
		ul2 = ul1 >> 16;
		bigintLiteral_.highest_ = ((S)( bigintLiteral_.highest_ + ul2 ) );
	}

	bigintLiteral_.highest_ = ((US)( bigintLiteral_.highest_ + other.bigintLiteral_.highest_ ) );
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& BigintValue::operator -= ( AbstractValue& av )
{
	BigintValue other = av.asBigintValue();
	BigintValue tOther, tThis;
	L tThisHighest, tThisHigher, tThisLower, tThisLowest, tOtherHighest, tOtherHigher, tOtherLower, tOtherLowest;
	SignValues resultSign;

	if( bigintLiteral_.sign_ == SV_POSITIVE && other.bigintLiteral_.sign_ == SV_NEGATIVE )
	{
		tOther = *this;
		tOther.bigintLiteral_.sign_ = SV_POSITIVE;
		*this += dynamic_cast< AbstractValue& >( tOther );
		return dynamic_cast< AbstractValue& >( *this );
	}
	else if( bigintLiteral_.sign_ == SV_NEGATIVE && other.bigintLiteral_.sign_ == SV_POSITIVE )
	{
		tThis = *this;
		tOther = other;
		tThis.bigintLiteral_.sign_ = tOther.bigintLiteral_.sign_ = SV_POSITIVE;
		tThis += dynamic_cast< AbstractValue& >( tOther );
		tThis.bigintLiteral_.sign_ = SV_NEGATIVE;
		*this = tThis;
		return dynamic_cast< AbstractValue& >( *this );
	}
	else if( bigintLiteral_.sign_ == SV_NEGATIVE && other.bigintLiteral_.sign_ == SV_NEGATIVE )
	{
		//  this is   -x - -y == -x+y
		tThis = *this;
		tOther = other;
		tOther.bigintLiteral_.sign_ = SV_POSITIVE;
		tThis += dynamic_cast< AbstractValue& >( tOther );
		*this = tThis;
		return dynamic_cast< AbstractValue& >( *this );
	}
	else if( *this < other )
	{
		//  subtraction gives negative result.  Exchange, change sign
		//  at end
		tThis = other;
		tOther = *this;
		resultSign = SV_NEGATIVE;
	}
	else
	{
		//  subtraction, result is positive
		resultSign = SV_POSITIVE;
		tThis = *this;
		tOther = other;
	}

	tThisLowest = tThis.bigintLiteral_.lowest_;
	tThisLower = tThis.bigintLiteral_.lower_;
	tThisHigher = tThis.bigintLiteral_.higher_;
	tThisHighest = tThis.bigintLiteral_.highest_;
	tOtherLowest = tOther.bigintLiteral_.lowest_;
	tOtherLower = tOther.bigintLiteral_.lower_;
	tOtherHigher = tOther.bigintLiteral_.higher_;
	tOtherHighest = tOther.bigintLiteral_.highest_;

	//
	//  adjust so that each element of tThis is bigger than the
	//  corresponding element of tOther
	//
	if( tThisLowest < tOtherLowest )
	{
		tThisLowest += 0x10000;
		if( tThisLower != 0 )
			tThisLower--;
		else
		{
			tThisLower += 0x10000;
			if( tThisHigher != 0 )
				tThisHigher--;
			else
				tThisHighest--;
		}
	}

	if( tThisLower < tOtherLower )
	{
		tThisLower += 0x10000;
		if( tThisHigher != 0 )
			tThisHigher--;
		else
		{
			tThisHigher += 0x10000;
			tThisHighest--;
		}
	}

	if( tThisHigher < tOtherHigher )
	{
		tThisHigher += 0x10000;
		tThisHighest--;
	}

	tThisLowest -= tOtherLowest;
	tThisLower -= tOtherLower;
	tThisHigher -= tOtherHigher;
	tThisHighest -= tOtherHighest;

	bigintLiteral_.lowest_ = ((US)tThisLowest);
	bigintLiteral_.lower_ = ((US)tThisLower);
	bigintLiteral_.higher_ = ((US)tThisHigher);
	bigintLiteral_.highest_ = ((US)tThisHighest);
	bigintLiteral_.sign_ = resultSign;
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& BigintValue::operator *= ( AbstractValue& av )
{
	BigintValue other = av.asBigintValue();
	BigintValue tThis, tOther;
	UL tThisHighest, tThisHigher, tThisLower, tThisLowest, tOtherHighest, tOtherHigher, tOtherLower, tOtherLowest, ul, ul2;

	tThis = *this;
	tOther = other;

	tThisLowest = tThis.bigintLiteral_.lowest_;
	tThisLower = tThis.bigintLiteral_.lower_;
	tThisHigher = tThis.bigintLiteral_.higher_;
	tThisHighest = tThis.bigintLiteral_.highest_;
	tOtherLowest = tOther.bigintLiteral_.lowest_;
	tOtherLower = tOther.bigintLiteral_.lower_;
	tOtherHigher = tOther.bigintLiteral_.higher_;
	tOtherHighest = tOther.bigintLiteral_.highest_;

	ul = tThisLowest * tOtherLowest;
	ul2 = ul & 0x0000ffff;
	bigintLiteral_.lowest_ = ((US)ul2);
	if( ul & 0xffff0000 )
	{
		ul = ul >> 16;
		tThisLower += ul;
	}

	ul = tThisLower * tOtherLower;
	ul2 = ul & 0x0000ffff;
	bigintLiteral_.lower_ = ((US)ul2);
	if( ul & 0xffff0000 )
	{
		ul = ul >> 16;
		tThisHigher += ul;
	}

	ul = tThisHigher * tOtherHigher;
	ul2 = ul & 0x0000ffff;
	bigintLiteral_.higher_ = ((US)ul2);
	if( ul & 0xffff0000 )
	{
		ul = ul >> 16;
		tThisHighest += ul;
	}

	ul = tThisHighest * tOtherHighest;
	ul2 = ul & 0x0000ffff;
	bigintLiteral_.highest_ = ((US)ul2);
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& BigintValue::operator /= ( AbstractValue& av )
{
	BigintValue other = av.asBigintValue();
	BigintValue tThis, tOther, result, lzero, one;
	NI shifts;

	if( *this < other )
	{
		//  integer division, so answer is 0
		this->zero();
		return dynamic_cast< AbstractValue& >( *this );
	}

	tThis = *this;
	tOther = other;

	//
	//  shift tOther left until it is bigger than tThis,
	//  then shift right once.
	//
	shifts = 0;
	while( tOther < tThis && !tOther.highBitOn() )
	{
		tOther << 1;
		shifts++;
	}

	//
	//  shifting may have stopped because tOther is bigger,
	//  or it may have stopped because an additional shift
	//  to tOther would lose data.  If the former is true,
	//  shift right once.
	//

	if( tOther > tThis )
	{
		tOther >> 1;
		shifts--;
	}

	//
	//  now do the subtract/shift algorithm
	//
	result.zero();
	lzero.zero();
	one.zero();
	one.bigintLiteral_.lowest_ = 1;

	while( shifts >= 0 )
	{
		result << 1;

		while( tThis > lzero )
		{
			tThis -= dynamic_cast< AbstractValue& >( tOther );
			result += dynamic_cast< AbstractValue& >( one );
		}

		//
		//  reverse the last subtraction
		//
		tThis += dynamic_cast< AbstractValue& >( tOther );
		result -= dynamic_cast< AbstractValue& >( one );
	}

	*this = result;
	return dynamic_cast< AbstractValue& >( *this );
}


bool BigintValue::highBitOn( void )
{
	if( bigintLiteral_.highest_ & 0x80000000 )
		return true;
	else
		return false;
}


void BigintValue::zero( void )
{
	bigintLiteral_.highest_ = bigintLiteral_.higher_ = bigintLiteral_.lower_ = bigintLiteral_.lowest_ = 0;
}


BigintValue& BigintValue::operator << ( NI nshifts )
{
	NI loop;
	bool highBit1, highBit2;

	for( loop = 0; loop < nshifts; loop++ )
	{
		if( bigintLiteral_.lowest_ & 0x8000 )
			highBit1 = true;
		else
			highBit1 = false;

		bigintLiteral_.lowest_ = ((US)( bigintLiteral_.lowest_ << 1 ) );

		if( bigintLiteral_.lower_ & 0x8000 )
			highBit2 = true;
		else
			highBit2 = false;

		bigintLiteral_.lower_ = ((US)( bigintLiteral_.lower_ << 1 ) );
		if( highBit1 == true )
			bigintLiteral_.lower_ |= 1;
		highBit1 = highBit2;

		if( bigintLiteral_.higher_ & 0x8000 )
			highBit2 = true;
		else
			highBit2 = false;

		bigintLiteral_.higher_ = ((US)( bigintLiteral_.higher_ << 1 ) );
		if( highBit1 == true )
			bigintLiteral_.higher_ |= 1;
		highBit1 = highBit2;

		bigintLiteral_.highest_ = ((US)( bigintLiteral_.highest_ >> 1 ) );
		if( highBit1 )
			bigintLiteral_.highest_ |= 1;
	}


	return *this;
}


BigintValue& BigintValue::operator >> ( NI nshifts )
{
	NI loop;
	bool lowBit1, lowBit2;

	for( loop = 0; loop < nshifts; loop++ )
	{
		if( bigintLiteral_.highest_ & 1 )
			lowBit1 = true;
		else
			lowBit1 = false;
		bigintLiteral_.highest_ = ((US)( bigintLiteral_.highest_ >> 1 ) );

		if( bigintLiteral_.higher_ & 1 )
			lowBit2 = true;
		else
			lowBit2 = false;
		bigintLiteral_.higher_ = ((US)( bigintLiteral_.higher_ >> 1 ) );
		if( lowBit1 == true )
			bigintLiteral_.higher_ |= 0x8000;
		lowBit1 = lowBit2;

		if( bigintLiteral_.lower_ & 1 )
			lowBit2 = true;
		else
			lowBit2 = false;
		bigintLiteral_.lower_ = ((US)( bigintLiteral_.lower_ >> 1 ) );
		if( lowBit1 == true )
			bigintLiteral_.lower_ |= 0x8000;
		lowBit1 = lowBit2;

		bigintLiteral_.lowest_ = ((US)( bigintLiteral_.lowest_ >> 1 ) );
		if( lowBit1 == true )
			bigintLiteral_.lowest_ |= 0x8000;
	}

	return *this;
}


void BigintValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	_output = asString();
}


US BigintValue::dictionaryLength( void )
{
	return static_cast< US >( sizeof( bool ) + sizeof( bigintLiteral_.highest_ ) + sizeof( bigintLiteral_.higher_ ) + sizeof( bigintLiteral_.lower_ ) + sizeof( bigintLiteral_.lowest_ ) );
}


void BigintValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << nullflag() << bigintLiteral_.highest_ << bigintLiteral_.higher_ << bigintLiteral_.lower_ << bigintLiteral_.lowest_;
}


void BigintValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> nullflag() >> bigintLiteral_.highest_ >> bigintLiteral_.higher_ >> bigintLiteral_.lower_ >> bigintLiteral_.lowest_;
}
