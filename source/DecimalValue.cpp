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


const UL DecimalValue::fixedLength_ = 8 + sizeof( CqlConstants::SignValues ) + sizeof( NC );


DecimalValue::DecimalValue( const DecimalValue& other ) : AbstractValue( CQL_DECIMAL )
{
	decimalLiteral_.sign_ = other.decimalLiteral_.sign_;
	decimalLiteral_.scale_ = other.decimalLiteral_.scale_;
	digit( 0, other.digit( 0 ) );
	digit( 1, other.digit( 1 ) );
	digit( 2, other.digit( 2 ) );
	digit( 3, other.digit( 3 ) );
	digit( 4, other.digit( 4 ) );
	digit( 5, other.digit( 5 ) );
	digit( 6, other.digit( 6 ) );
	digit( 7, other.digit( 7 ) );
	digit( 8, other.digit( 8 ) );
	digit( 9, other.digit( 9 ) );
	digit( 10, other.digit( 10 ) );
	digit( 11, other.digit( 11 ) );
	digit( 12, other.digit( 12 ) );
	digit( 13, other.digit( 13 ) );
	digit( 14, other.digit( 14 ) );
	digit( 15, other.digit( 15 ) );

	DecimalValue& ncother = const_cast< DecimalValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
}


DecimalValue::DecimalValue( const CqlColumnTypes& ) : AbstractValue( CQL_DECIMAL )
{
	  decimalLiteral_.sign_ = SV_POSITIVE;
	  decimalLiteral_.scale_ = 0;
	  memset( decimalLiteral_.digits_, 0, sizeof( decimalLiteral_.digits_ ) );
}


DecimalValue::DecimalValue( pUC& buf ) : AbstractValue( CQL_DECIMAL )
{
	memcpy( &decimalLiteral_.sign_, buf, sizeof( decimalLiteral_.sign_ ) );
	buf += sizeof( decimalLiteral_.sign_ );
	memcpy( &decimalLiteral_.scale_, buf, sizeof( decimalLiteral_.scale_ ) );
	buf += sizeof( decimalLiteral_.scale_ );
	memcpy( decimalLiteral_.digits_, buf, sizeof( decimalLiteral_.digits_ ) );
	buf += sizeof( decimalLiteral_.digits_ );
}


DecimalValue& DecimalValue::operator = ( const DecimalValue& other )
{
	decimalLiteral_.sign_ = other.decimalLiteral_.sign_;
	decimalLiteral_.scale_ = other.decimalLiteral_.scale_;
	digit( 0, other.digit( 0 ) );
	digit( 1, other.digit( 1 ) );
	digit( 2, other.digit( 2 ) );
	digit( 3, other.digit( 3 ) );
	digit( 4, other.digit( 4 ) );
	digit( 5, other.digit( 5 ) );
	digit( 6, other.digit( 6 ) );
	digit( 7, other.digit( 7 ) );
	digit( 8, other.digit( 8 ) );
	digit( 9, other.digit( 9 ) );
	digit( 10, other.digit( 10 ) );
	digit( 11, other.digit( 11 ) );
	digit( 12, other.digit( 12 ) );
	digit( 13, other.digit( 13 ) );
	digit( 14, other.digit( 14 ) );
	digit( 15, other.digit( 15 ) );
	DecimalValue& ncother = const_cast< DecimalValue& >( other );
	if( ncother.nullflag() )
		setNullflag();
	else
		clearNullflag();
	return *this;
}


DecimalValue::DecimalValue( const CqlString& source ) : AbstractValue( CQL_DECIMAL )
{
	*this = source;
}


DecimalValue::DecimalValue( const NC *source ) : AbstractValue( CQL_DECIMAL )
{
	*this = CqlString( source );
}


DecimalValue::DecimalValue( const UC *source ) : AbstractValue( CQL_DECIMAL )
{
	*this = CqlString( reinterpret_cast< const NC * >( source ) );
}


DecimalValue::DecimalValue( const NC source ) : AbstractValue( CQL_DECIMAL )
{
	NC buffer[ 100 ];
	sprintf( buffer, "%d", static_cast< const NI >( source ) );
	*this = CqlString( buffer );
}


DecimalValue::DecimalValue( const UNI source ) : AbstractValue( CQL_DECIMAL )
{
	NC buffer[ 100 ];
	sprintf( buffer, "%u", source );
	*this = CqlString( buffer );
}


DecimalValue::DecimalValue( const US source ) : AbstractValue( CQL_DECIMAL )
{
	NC buffer[ 100 ];
	sprintf( buffer, "%hd", source );
	*this = CqlString( buffer );
}


DecimalValue::DecimalValue( const UL source ) : AbstractValue( CQL_DECIMAL )
{
	NC buffer[ 100 ];
	sprintf( buffer, "%ld", source );
	*this = CqlString( buffer );
}


DecimalValue& DecimalValue::operator = ( const CqlString& str )
{
	NC stringBuffer[ 50 ];
	memset( stringBuffer, 0, sizeof( stringBuffer ) );
	strcpy( stringBuffer, str.text() );
	NC *pBuffer = stringBuffer;

	NI negativeFlag = CQL_NO;

	if( *pBuffer == '-' )
	{
		negativeFlag = CQL_YES;
		pBuffer++;
	}
	else if( *pBuffer == '+' )
		pBuffer++;

	UNI stringLength = strlen(pBuffer);

	zero();

	NC *p;
	bool scaleFlag;
	UNI loop;

	for( p = pBuffer, scaleFlag = false, loop = 0; loop < stringLength; loop++, p++ )
	{
		if( *p == '.' )
			scaleFlag = true;
		else if( scaleFlag == true )
			decimalLiteral_.scale_++;
	}
	decimalLiteral_.scale_ *= static_cast< SC >( -1 );

	//
	//  note:  ASCII sensitive
	//
	UNI digitNumber;

	if( scaleFlag )
		digitNumber = stringLength - 2;
	else
		digitNumber = stringLength - 1;
	for( loop = 0, p = pBuffer; loop < stringLength; loop++, p++ )
	{
		if( *p == '.' )
			continue;

		NC digitString[ 2 ];
		digitString[ 0 ] = *p;
		digitString[ 1 ] = 0;
		digit( digitNumber, atoi( digitString ) );
		digitNumber--;
	}

	if( negativeFlag )
		decimalLiteral_.sign_ = SV_NEGATIVE;

	shiftLeft( availableShifts() );
	return *this;
}


DecimalValue& DecimalValue::operator = ( const NC *str )
{
	return *this = CqlString( str );
}


AbstractValue& DecimalValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_DECIMAL :
		{
			DecimalValue& dv = dynamic_cast<DecimalValue& >( av );
			*this = dv;
		}
		break;

	case CQL_BIGINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_REAL :
	case CQL_FLOAT :
	case CQL_TINYINT :
		*this = av.asString();
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
	case CQL_BIT :
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	return *this;
}


DecimalValue::DecimalValue( const NI i ) : AbstractValue( CQL_DECIMAL )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%d", i );
	*this = buffer;
}


DecimalValue::DecimalValue( const L l ) : AbstractValue( CQL_DECIMAL )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%ld", l );
	*this = buffer;
}


DecimalValue::DecimalValue( const D d ) : AbstractValue( CQL_DECIMAL )
{
	NC buffer[ 50 ];
	sprintf( buffer, "%f", d );
	*this = buffer;
}


DecimalValue::DecimalValue( const BigintValue& bv ) : AbstractValue( CQL_DECIMAL )
{
	BigintValue bigv( bv );
	*this = bigv.asString();
}


DecimalValue::DecimalValue( IntegerValue& iv ) : AbstractValue( CQL_DECIMAL )
{
	*this = iv.asString();
}


DecimalValue::DecimalValue( SmallintValue& sv ) : AbstractValue( CQL_DECIMAL )
{
	*this = sv.asString();
}


DecimalValue::DecimalValue( TinyintValue& tv ) : AbstractValue( CQL_DECIMAL )
{
	*this = tv.asString();
}


void DecimalValue::zeroDigits( void )
{
	memset( decimalLiteral_.digits_, 0, sizeof( decimalLiteral_.digits_ ) );
}


void DecimalValue::zero( void )
{
	zeroDigits();
	decimalLiteral_.sign_ = SV_POSITIVE;
	decimalLiteral_.scale_ = 0;
}


void DecimalValue::shiftLeft( UNI shifts )
{
	DecimalValue tdec = *this;

	zeroDigits();

	UNI loop1, limit1, loop2;

	for( loop1 = 0, limit1 = 16 - shifts, loop2 = loop1 + shifts; loop1 < limit1; loop1++, loop2++ )
		digit( loop2, tdec.digit( loop1 ) );

	NI lscale = static_cast< NI >( tdec.decimalLiteral_.scale_ );
	lscale -= static_cast< NI >( shifts );

	decimalLiteral_.scale_ = static_cast< SC >( lscale );
}


void DecimalValue::shiftRight( UNI shifts )
{
	DecimalValue tdec = *this;

	zeroDigits();

	UNI loop1, loop2, limit1;

	for( loop1 = 0, limit1 = 16 - shifts, loop2 = loop1 + shifts; loop1 < limit1; loop1++, loop2++ )
		digit( loop1, tdec.digit( loop2 ) );

	NI lscale = static_cast< NI >( tdec.decimalLiteral_.scale_ );
	lscale += static_cast< NI >( shifts );

	decimalLiteral_.scale_ = static_cast< SC >( lscale );
}


void DecimalValue::shiftToZeroExponent( void )
{
	if( decimalLiteral_.scale_ < 0 )
		shiftRight( decimalLiteral_.scale_ * -1 );
	else
		shiftLeft( decimalLiteral_.scale_ );
}


//  How far can we shift without losing significant digit?
UNI DecimalValue::availableShifts( void )
{
	UNI shifts;
	NI loop;

	for( shifts = 0, loop = 15; loop >= 0; loop-- )
	{
		if( digit( loop ) != 0 )
			break;

		shifts++;
	}

	return shifts;
}


//  normalize returns two DecimalValue's with the same exponent
//  op1 is operand 1.  op2 is operand2.  n1 is normalized 1, and n2 is normalized 2
void DecimalValue::normalize( DecimalValue& n1, DecimalValue& n2, const DecimalValue& op1, const DecimalValue& op2 ) const
{
	n1 = op1;
	n2 = op2;

	//  if decimalLiteral_.scale_ (exponent) values are the same, values are already normalized.
	if( n1.decimalLiteral_.scale_ == n2.decimalLiteral_.scale_ )
		return;

	if( !op1 )
	{
		n1.decimalLiteral_.scale_ = n2.decimalLiteral_.scale_;
		return;
	}
	else if( !op2 )
	{
		n2.decimalLiteral_.scale_ = n1.decimalLiteral_.scale_;
		return;
	}

	//  Pointers are used to select in which direction to normalize
	DecimalValue *pDec1, *pDec2;
	UNI diff;

	if( n1.decimalLiteral_.scale_ > n2.decimalLiteral_.scale_ )
	{
		pDec1 = &n1;
		pDec2 = &n2;
		diff = static_cast< UNI >( n1.decimalLiteral_.scale_ - n2.decimalLiteral_.scale_ );
	}
	else
	{
		pDec1 = &n2;
		pDec2 = &n1;
		diff = static_cast< UNI >( n2.decimalLiteral_.scale_ - n1.decimalLiteral_.scale_ );
	}

	UNI aShifts, shift1, shift2;

	aShifts = pDec1->availableShifts();

	if( diff > aShifts )
	{
		shift2 = diff - aShifts;
		shift1 = aShifts;
	}
	else
	{
		shift1 = diff;
		shift2 = 0;
	}

	pDec1->shiftLeft( shift1 );
	if( shift2 )
		pDec2->shiftRight( shift2 );
}


//  This should be replaced with a memcmp on architectures where memcmp would work.
CqlConstants::CompareResult DecimalValue::compareMantissa( const DecimalValue& other ) const
{
	DecimalValue op1 = *this;
	DecimalValue op2 = other;
	DecimalValue nop1, nop2;  //  normalized values

	if( op1.decimalLiteral_.scale_ != op2.decimalLiteral_.scale_ )
		//  normalize so we can compare the digits.
		normalize( nop1, nop2, op1, op2 );
	else
	{
		nop1 = op1;
		nop2 = op2;
	}

	if( nop1.digit( 15 ) > nop2.digit( 15 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 15 ) < nop2.digit( 15 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 14 ) > nop2.digit( 14 ) )
		return THIS_GREATER_THAN_OTHER;
	else if( nop1.digit( 14 ) < nop2.digit( 14 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 13 ) > nop2.digit( 13 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 13 ) < nop2.digit( 13 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 12 ) > nop2.digit( 12 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 12 ) < nop2.digit( 12 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 11 ) > nop2.digit( 11 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 11 ) < nop2.digit( 11 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 10 ) > nop2.digit( 10 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 10 ) < nop2.digit( 10 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 9 ) > nop2.digit( 9 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 9 ) < nop2.digit( 9 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 8 ) > nop2.digit( 8 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 8 ) < nop2.digit( 8 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 7 ) > nop2.digit( 7 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 7 ) < nop2.digit( 7 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 6 ) > nop2.digit( 6 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 6 ) < nop2.digit( 6 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 5 ) > nop2.digit( 5 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 5 ) < nop2.digit( 5 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 4 ) > nop2.digit( 4 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 4 ) < nop2.digit( 4 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 3 ) > nop2.digit( 3 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 3 ) < nop2.digit( 3 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 2 ) > nop2.digit( 2 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 2 ) < nop2.digit( 2 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 1 ) > nop2.digit( 1 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 1 ) < nop2.digit( 1 ) )
		return THIS_LESS_THAN_OTHER;
	else if( nop1.digit( 0 ) > nop2.digit( 0 ) )
		return THIS_GREATER_THAN_OTHER;
	else if(  nop1.digit( 0 ) < nop2.digit( 0 ) )
		return THIS_LESS_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


CqlConstants::CompareResult DecimalValue::compare( const DecimalValue& other ) const
{
	if( decimalLiteral_.sign_ == SV_NEGATIVE && other.decimalLiteral_.sign_ == SV_POSITIVE )
		return THIS_LESS_THAN_OTHER;
	else if( decimalLiteral_.sign_ == SV_POSITIVE && other.decimalLiteral_.sign_ == SV_NEGATIVE )
		return THIS_GREATER_THAN_OTHER;

	CompareResult cmr = compareMantissa( other );

	if( decimalLiteral_.sign_ == SV_NEGATIVE )
	{
		if( cmr == THIS_LESS_THAN_OTHER )
			return THIS_GREATER_THAN_OTHER;
		else
			return THIS_LESS_THAN_OTHER;
	}
	else
		return cmr;
}


bool DecimalValue::operator == ( const DecimalValue& other ) const
{
	if( compare( other ) == THIS_EQUAL_TO_OTHER )
		return true;

	return false;
}


bool DecimalValue::operator == ( const AbstractValue& av ) const
{
	return *this == av.asDecimalValue();
}


bool DecimalValue::operator != ( const AbstractValue& av ) const
{
	if( *this == av.asDecimalValue() )
		return false;
	else
		return true;
}


void DecimalValue::absoluteValue( void )
{
	decimalLiteral_.sign_ = SV_POSITIVE;
}


void DecimalValue::output( TempBuffer& tb ) const
{
	tb << decimalLiteral_.sign_ << decimalLiteral_.scale_;
	tb << NO_COPY << FOUR_BYTE_LENGTH << static_cast< UL >( sizeof( decimalLiteral_.digits_ ) );
	tb << decimalLiteral_.digits_;
}


void DecimalValue::input( TempBuffer& tb )
{
	tb >> decimalLiteral_.sign_ >> decimalLiteral_.scale_;
	tb << NO_COPY << FOUR_BYTE_LENGTH << static_cast< UL >( sizeof( decimalLiteral_.digits_ ) );
	tb >> decimalLiteral_.digits_;
}


UL DecimalValue::length( void ) const
{
	return sizeof( DecimalValue );
}


UL DecimalValue::streamLength( void ) const
{
	return fixedLength_;
}


NC DecimalValue::asChar() const
{
	if( *this > DecimalValue( CQL_MAXIMUM_SC ) || *this < DecimalValue( CQL_MINIMUM_SC ) )
		throw SizeConversionException( __FILE__, __LINE__ );

	NI i;
	if( sscanf( asString().text(), "%d", &i ) != 1 )
		throw InternalErrorException( __FILE__, __LINE__ );

	return static_cast< SC >( i );
}


S DecimalValue::asShort() const
{
	if( *this > DecimalValue( CQL_MAXIMUM_S ) || *this < DecimalValue( CQL_MINIMUM_S ) )
		throw SizeConversionException( __FILE__, __LINE__ );

	NI i;
	if( sscanf( asString().text(), "%d", &i ) != 1 )
		throw InternalErrorException( __FILE__, __LINE__ );

	return static_cast< S >( i );
}


L DecimalValue::asLong() const
{
	if( *this > DecimalValue( CQL_MAXIMUM_L ) || *this < DecimalValue( CQL_MINIMUM_L ) )
		throw SizeConversionException( __FILE__, __LINE__ );

	L l;
	if( sscanf( asString().text(), "%ld", &l ) != 1 )
		throw InternalErrorException( __FILE__, __LINE__ );

	return static_cast< L >( l );
}


BigintValue DecimalValue::asBigintValue() const
{
	return BigintValue( asString() );
}


DecimalValue DecimalValue::asDecimalValue() const
{
	return *this;
}


F DecimalValue::asFloat() const
{
	F f;
	if( sscanf( asString().text(), "%f", &f ) != 1 )
		throw InternalErrorException( __FILE__, __LINE__ );

	return f;
}


D DecimalValue::asDouble() const
{
	D d;
	if( sscanf( asString().text(), "%lf", &d ) != 1 )
		throw InternalErrorException( __FILE__, __LINE__ );

	return d;
}


DateValue DecimalValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for dumb compilers
	return DateValue();
#endif
}


TimeValue DecimalValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for dumb compilers
	return TimeValue();
#endif
}


TimestampValue DecimalValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for dumb compilers
	return TimestampValue();
#endif
}


//  logical operators

bool DecimalValue::operator ! ( void ) const
{
	NC zeroBuffer[ sizeof( decimalLiteral_.digits_ ) ];
	memset( zeroBuffer, 0, sizeof( zeroBuffer ) );
	if( !memcmp( decimalLiteral_.digits_, zeroBuffer, sizeof( zeroBuffer ) ) )
		return true;

	return false;
}


bool DecimalValue::operator < ( const DecimalValue& other ) const
{
	CompareResult cmr = compare( other );
	if( cmr == THIS_LESS_THAN_OTHER )
		return true;

	return false;
}


bool DecimalValue::operator < ( const AbstractValue& av ) const
{
	return *this < av.asDecimalValue();
}


bool DecimalValue::operator <= ( const DecimalValue& other ) const
{
	CompareResult cmr = compare( other );
	if( cmr == THIS_GREATER_THAN_OTHER )
		return false;

	return true;
}


bool DecimalValue::operator <= ( const AbstractValue& av ) const
{
	return *this <= av.asDecimalValue();
}


bool DecimalValue::operator > ( const DecimalValue& other ) const
{
	CompareResult cmr = compare( other );
	if( cmr == THIS_GREATER_THAN_OTHER )
		return true;

	return false;
}


bool DecimalValue::operator > ( const AbstractValue& av ) const
{
	return *this > av.asDecimalValue();
}


bool DecimalValue::operator >= ( const DecimalValue& other ) const
{
	CompareResult cmr = compare( other );
	if( cmr == THIS_LESS_THAN_OTHER )
		return false;

	return true;
}


bool DecimalValue::operator >= ( const AbstractValue& av ) const
{
	return *this >= av.asDecimalValue();
}


void DecimalValue::digit( const UNI digitNumber, const UNI iDigitValue )
{
	const NC digitValue = static_cast< const NC >( iDigitValue );

	switch( digitNumber )
	{
	case 0 :
		decimalLiteral_.digits_[ 0 ] &= 0xf0;
 		decimalLiteral_.digits_[ 0 ] |= digitValue;
		break;

	case 1 :
		decimalLiteral_.digits_[ 0 ] &= 0x0f;
		decimalLiteral_.digits_[ 0 ] |= ( digitValue << 4 );
		break;

	case 2 :
		decimalLiteral_.digits_[ 1 ] &= 0xf0;
 		decimalLiteral_.digits_[ 1 ] |= digitValue;
		break;

	case 3 :
		decimalLiteral_.digits_[ 1 ] &= 0x0f;
		decimalLiteral_.digits_[ 1 ] |= ( digitValue << 4 );
		break;

	case 4 :
		decimalLiteral_.digits_[ 2 ] &= 0xf0;
 		decimalLiteral_.digits_[ 2 ] |= digitValue;
		break;

	case 5 :
		decimalLiteral_.digits_[ 2 ] &= 0x0f;
		decimalLiteral_.digits_[ 2 ] |= ( digitValue << 4 );
		break;

	case 6 :
		decimalLiteral_.digits_[ 3 ] &= 0xf0;
 		decimalLiteral_.digits_[ 3 ] |= digitValue;
		break;

	case 7 :
		decimalLiteral_.digits_[ 3 ] &= 0x0f;
		decimalLiteral_.digits_[ 3 ] |= ( digitValue << 4 );
		break;

	case 8 :
		decimalLiteral_.digits_[ 4 ] &= 0xf0;
 		decimalLiteral_.digits_[ 4 ] |= digitValue;
		break;

	case 9 :
		decimalLiteral_.digits_[ 4 ] &= 0x0f;
		decimalLiteral_.digits_[ 4 ] |= ( digitValue << 4 );
		break;

	case 10 :
		decimalLiteral_.digits_[ 5 ] &= 0xf0;
 		decimalLiteral_.digits_[ 5 ] |= digitValue;
		break;

	case 11 :
		decimalLiteral_.digits_[ 5 ] &= 0x0f;
		decimalLiteral_.digits_[ 5 ] |= ( digitValue << 4 );
		break;

	case 12 :
		decimalLiteral_.digits_[ 6 ] &= 0xf0;
 		decimalLiteral_.digits_[ 6 ] |= digitValue;
		break;

	case 13 :
		decimalLiteral_.digits_[ 6 ] &= 0x0f;
		decimalLiteral_.digits_[ 6 ] |= ( digitValue << 4 );
		break;

	case 14 :
		decimalLiteral_.digits_[ 7 ] &= 0xf0;
 		decimalLiteral_.digits_[ 7 ] |= digitValue;
		break;

	case 15 :
		decimalLiteral_.digits_[ 7 ] &= 0x0f;
		decimalLiteral_.digits_[ 7 ] |= ( digitValue << 4 );
		break;

	default :
		throw InternalErrorException( __FILE__, __LINE__ );
	}
}


US DecimalValue::digit( const UNI digitNumber ) const
{
	switch( digitNumber )
	{
	case 0 :
		return static_cast< const US>( decimalLiteral_.digits_[ 0 ] & 0x0f );

	case 1 :
		return static_cast< const US>( ( decimalLiteral_.digits_[ 0 ] & 0xf0 ) >> 4 );

	case 2 :
		return static_cast< const US>( decimalLiteral_.digits_[ 1 ] & 0x0f );

	case 3 :
		return static_cast< const US>( ( decimalLiteral_.digits_[ 1 ] & 0xf0 ) >> 4 );

	case 4 :
		return static_cast< const US>( decimalLiteral_.digits_[ 2 ] & 0x0f );

	case 5 :
		return static_cast< const US>( ( decimalLiteral_.digits_[ 2 ] & 0xf0 ) >> 4 );

	case 6 :
		return static_cast< const US>( decimalLiteral_.digits_[ 3 ] & 0x0f );

	case 7 :
		return static_cast< const US>( ( decimalLiteral_.digits_[ 3 ] & 0xf0 ) >> 4 );

	case 8 :
		return static_cast< const US>( decimalLiteral_.digits_[ 4 ] & 0x0f );

	case 9 :
		return static_cast< const US>( ( decimalLiteral_.digits_[ 4 ] & 0xf0 ) >> 4 );

	case 10 :
		return static_cast< const US>( decimalLiteral_.digits_[ 5 ] & 0x0f );

	case 11 :
		return static_cast< const US>( ( decimalLiteral_.digits_[ 5 ] & 0xf0 ) >> 4 );

	case 12 :
		return static_cast< const US>( decimalLiteral_.digits_[ 6 ] & 0x0f );

	case 13 :
		return static_cast< const US>( ( decimalLiteral_.digits_[ 6 ] & 0xf0 ) >> 4 );

	case 14 :
		return static_cast< const US>( decimalLiteral_.digits_[ 7 ] & 0x0f );

	case 15 :
		return static_cast< const US>( ( decimalLiteral_.digits_[ 7 ] & 0xf0 ) >> 4 );

	default :
		break;
	}

	throw InternalErrorException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for very stupid compilers
	return 0;
#endif
}


const CqlString DecimalValue::asString( bool /* spacePadding */ ) const
{
	D d = 0;
	UNI loop, limit, loop2;

	for( loop = 0, loop2 = 15; loop < 16; loop++, loop2-- )
	{
		d *= 10;
		d += digit( loop2 );
	}

	if( decimalLiteral_.scale_ < 0 )
	{
		for( loop = 0, limit = ( decimalLiteral_.scale_ * -1 ); loop < limit; loop++ )
			d /= 10;
	}
	else if( decimalLiteral_.scale_ > 0 )
	{
		for( loop = 0, limit = decimalLiteral_.scale_; loop < limit; loop++ )
			d *= 10;
	}

	NC buffer[ 50 ];
	sprintf( buffer, "%f", d );
	return CqlString( buffer );
}


void DecimalValue::operator << ( pUC& buf )
{
	memcpy( &decimalLiteral_.sign_, buf, sizeof( decimalLiteral_.sign_ ) );
	buf += sizeof( decimalLiteral_.sign_ );
	memcpy( &decimalLiteral_.scale_, buf, sizeof( decimalLiteral_.scale_ ) );
	buf += sizeof( decimalLiteral_.scale_ );
	memcpy( decimalLiteral_.digits_, buf, sizeof( decimalLiteral_.digits_ ) );
	buf += sizeof( decimalLiteral_.digits_ );
}


void DecimalValue::operator >> ( pUC& buf )
{
	memcpy( buf, &decimalLiteral_.sign_, sizeof( decimalLiteral_.sign_ ) );
	buf += sizeof( decimalLiteral_.sign_ );
	memcpy( buf, &decimalLiteral_.scale_, sizeof( decimalLiteral_.scale_ ) );
	buf += sizeof( decimalLiteral_.scale_ );
	memcpy( buf, decimalLiteral_.digits_, sizeof( decimalLiteral_.digits_ ) );
	buf += sizeof( decimalLiteral_.digits_ );
}


void DecimalValue::operator >> ( BinaryValue& bv )
{
	bv.expand( sizeof( decimalLiteral_.sign_ ) + sizeof( decimalLiteral_.scale_ ) + 8 );
	UC *tbuffer = bv.buffer();
	*this >> tbuffer;
}


void DecimalValue::operator << ( BinaryValue& bv )
{
	UC *p = bv.buffer();
	*this << p;
}


void DecimalValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void DecimalValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void DecimalValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void DecimalValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& DecimalValue::operator += ( AbstractValue& av )
{
	DecimalValue& other = dynamic_cast< DecimalValue& >( av );

	DecimalValue tdec1, tdec2;
	UNI loop, carry, dig1, dig2, dig;

	if( other.nullflag() )
		return dynamic_cast< AbstractValue& >( *this );

	if( nullflag() )
	{
		*this = other;
		clearNullflag();
		return dynamic_cast< AbstractValue& >( *this );
	}

	if( other.decimalLiteral_.sign_ == SV_NEGATIVE && decimalLiteral_.sign_ == SV_POSITIVE )
	{
		other.decimalLiteral_.sign_ = SV_POSITIVE;
		*this -= av;
		return dynamic_cast< AbstractValue& >( *this );
	}
	else if( decimalLiteral_.sign_ == SV_NEGATIVE && other.decimalLiteral_.sign_ == SV_POSITIVE )
	{
		tdec1 = other;
		tdec2 = *this;
		tdec2.decimalLiteral_.sign_ = SV_POSITIVE;
		tdec2 -= dynamic_cast< AbstractValue& >( tdec1 );
		tdec2.decimalLiteral_.sign_ = SV_POSITIVE;
		*this = dynamic_cast< AbstractValue& >( tdec2 );
		return dynamic_cast< AbstractValue& >( *this );
	}

	normalize( tdec1, tdec2, *this, other );

	for( loop = 0, carry = 0; loop < 16; loop++ )
	{
		dig1 = tdec1.digit( loop );
		dig2 = tdec2.digit( loop );

		dig = carry + dig1 + dig2;

		if( dig > 9 )
		{
			carry = 1;
			dig -= 10;
		}
		else
			carry = 0;

		tdec1.digit( loop, dig );
	}

	if( carry )
	{
		tdec1.shiftRight( 1 );
		tdec1.digit( 15, carry );
	}

	*this = tdec1;
	return *this;
}


AbstractValue& DecimalValue::operator -= ( AbstractValue& av )
{
	DecimalValue& other = dynamic_cast< DecimalValue& >( av );

	NI niResult;
	bool swapFlag = false;
	UNI dig, borrow, dig1, dig2, loop;
	DecimalValue tdecOther, tdecThis, tdecTemp;

	tdecOther = other;

	if( decimalLiteral_.sign_ != other.decimalLiteral_.sign_ )
	{
		if( other.decimalLiteral_.sign_ == SV_NEGATIVE )
		{
			//
			//  we have x - -y, change to x + y
			//
			tdecOther.decimalLiteral_.sign_ = SV_POSITIVE;
			*this += dynamic_cast< AbstractValue& >( tdecOther );
			return dynamic_cast< AbstractValue& >( *this );
		}
		else
		{
			//
			//  we have -x - y, change to x + y, then change sign of result
			//
			decimalLiteral_.sign_ = SV_POSITIVE;
			*this += dynamic_cast< AbstractValue& >( other );
			decimalLiteral_.sign_ = SV_NEGATIVE;
			return dynamic_cast< AbstractValue& >( *this );
		}
	}

	//
	//  still here, so we have either (+x) - (+y) or (-x) - (-y)
	//
	if( decimalLiteral_.sign_ == SV_NEGATIVE )
	{
		//
		//  change - (-y) to + (+y)
		//
		tdecOther.decimalLiteral_.sign_ = SV_POSITIVE;
		*this +=  dynamic_cast< AbstractValue& >( tdecOther );
		return dynamic_cast< AbstractValue& >( *this );
	}

	normalize( tdecThis, tdecOther, *this, other );

	if( tdecOther > tdecThis )
	{
		swapFlag = true;
		tdecTemp = tdecThis;
		tdecThis = tdecOther;
		tdecOther = tdecTemp;
	}

	for( loop = borrow = 0; loop < 16; loop++ )
	{
		dig1 = tdecThis.digit( loop );
		dig2 = tdecOther.digit( loop );

		niResult = ((NI)dig1) - ( ((NI)borrow) + ((NI)dig2) );

		if( niResult >= 0 )
		{
			dig = ((UNI)niResult);
			borrow = 0;
		}
		else
		{
			borrow = 1;
			niResult += 10;
			dig = ((UNI)niResult);
		}

		tdecThis.digit( loop, dig );
	}

	if( swapFlag )
		tdecThis.decimalLiteral_.sign_ = SV_NEGATIVE;

	*this = tdecThis;
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& DecimalValue::operator *= ( AbstractValue& av )
{
	DecimalValue& other = dynamic_cast< DecimalValue& >( av );
	UNI loop, significantDigitsThis, significantDigitsOther;
	DecimalValue tdecThis, tdecOther, oneDigit, result, one, _zero;
	SignValues sign1, sign2;
	NC scale1, scale2;

	tdecThis = *this;
	tdecOther = other;

	if( tdecThis.availableShifts() < 1 )
		tdecThis.shiftRight( 1 );

	if( tdecOther.availableShifts() < 1 )
		tdecOther.shiftRight( 1 );

	significantDigitsThis = tdecThis.significantDigits();
	significantDigitsOther = tdecOther.significantDigits();

	while( significantDigitsThis + significantDigitsOther > 15 )
	{
		if( significantDigitsThis > significantDigitsOther )
		{
			tdecThis.shiftRight( 1 );
			significantDigitsThis--;
		}
		else
		{
			tdecOther.shiftRight( 1 );
			significantDigitsOther--;
		}
	}

	sign1 = tdecThis.decimalLiteral_.sign_;
	scale1 = tdecThis.decimalLiteral_.scale_;
	tdecThis.decimalLiteral_.sign_ = SV_POSITIVE;
	tdecThis.decimalLiteral_.scale_ = 0;

	sign2 = tdecOther.decimalLiteral_.sign_;
	scale2 = tdecOther.decimalLiteral_.scale_;
	tdecOther.decimalLiteral_.sign_ = SV_POSITIVE;
	tdecOther.decimalLiteral_.scale_ = 0;

	result.zero();
	one.zero();
	one.digit( 0, 1 );
	_zero.zero();

	for( loop = 0; loop < significantDigitsThis; loop++ )
	{
		oneDigit.zero();
		oneDigit.digit( 0, tdecOther.digit( loop ) );

		while( oneDigit > _zero )
		{
			result += dynamic_cast< AbstractValue& >( tdecThis );
			oneDigit -= dynamic_cast< AbstractValue& >( one );
		}

		tdecThis.shiftLeft( 1 );
		tdecThis.decimalLiteral_.scale_++;
	}

	if( sign1 == sign2 )
		result.decimalLiteral_.sign_ = SV_POSITIVE;
	else
		result.decimalLiteral_.sign_ = SV_NEGATIVE;

	result.decimalLiteral_.scale_ = static_cast< SC >( scale1 + scale2 );
	*this = result;
	return dynamic_cast< AbstractValue& >( *this );
}


AbstractValue& DecimalValue::operator /= ( AbstractValue& av )
{
	DecimalValue& other = dynamic_cast< DecimalValue& >( av );
	SignValues signThis, signOther;
	NC scaleThis, scaleOther;
	NI loop;
	DecimalValue tdecThis, tdecOther, result, _zero, one;

	_zero.zero();
	if( !other )
		return dynamic_cast< AbstractValue& >( *this );

	if( !( *this ) )
		return dynamic_cast< AbstractValue& >( *this );

	signThis = decimalLiteral_.sign_;
	signOther = other.decimalLiteral_.sign_;
	scaleThis = decimalLiteral_.scale_;
	scaleOther = other.decimalLiteral_.scale_;

	tdecThis = *this;
	tdecOther = other;

	tdecThis.decimalLiteral_.sign_ = SV_POSITIVE;
	tdecThis.decimalLiteral_.scale_ = 0;
	tdecOther.decimalLiteral_.sign_ = SV_POSITIVE;
	tdecOther.decimalLiteral_.scale_ = 0;
	result.zero();
	_zero.zero();

	for( loop = 15; loop >= 0 && ( !( !tdecThis ) ); loop-- )
	{
		one.zero();
		one.digit( loop, 1 );

		do
		{
			tdecThis -= dynamic_cast< AbstractValue& >( tdecOther );
			result += dynamic_cast< AbstractValue& >( one );
		}
		while( tdecThis.compare( _zero ) == THIS_GREATER_THAN_OTHER );

		if( tdecThis.decimalLiteral_.sign_ == SV_NEGATIVE )
		{
			/*  reverse last subtraction  */
			tdecThis += dynamic_cast< AbstractValue& >( tdecOther );
			result -= dynamic_cast< AbstractValue& >( one );
		}

		if( tdecOther.digit( 0 ) )
		{
			if( tdecThis.digit( 15 ) != 0 )
			{
				tdecOther.shiftRight( 1 );
				tdecOther.decimalLiteral_.scale_--;
			}
			else
			{
				tdecThis.shiftLeft( 1 );
				tdecThis.decimalLiteral_.scale_++;
			}
		}
		else
		{
			tdecOther.shiftRight( 1 );
			tdecOther.decimalLiteral_.scale_--;
		}
	}

	//
	//  remove trailing zeroes
	//
	result.shiftToRemoveTrailingZeros();
	*this = result;
	decimalLiteral_.scale_ = static_cast< NC >( decimalLiteral_.scale_ + ( scaleThis - scaleOther ) - 15 );
	if( signThis == signOther )
		decimalLiteral_.sign_ = SV_POSITIVE;
	else
   		decimalLiteral_.sign_ = SV_NEGATIVE;
	return dynamic_cast< AbstractValue& >( *this );
}


UNI DecimalValue::significantDigits( void )
{
	UNI loop, loop2;

	for( loop = 0, loop2 = 15; loop < 16; loop++, loop2-- )
		if( digit( loop2 ) )
			break;

	return loop2;
}


void DecimalValue::shiftToRemoveTrailingZeros( void )
{
	UNI loop;

	if( !( *this ) )
		return;

	for( loop = 0; loop < 16; loop++ )
		if( digit( loop ) )
			break;

	if( loop )
		shiftRight( loop );
}


US DecimalValue::dictionaryLength( void )
{
	return sizeof( DecimalValue );
}


void DecimalValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	_output = asString();
}


void DecimalValue::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << decimalLiteral_.sign_ << decimalLiteral_.scale_;
	buffer << NO_COPY << FOUR_BYTE_LENGTH << static_cast< UL >( sizeof( decimalLiteral_.digits_ ) );
	buffer << decimalLiteral_.digits_;
}


void DecimalValue::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> decimalLiteral_.sign_ >> decimalLiteral_.scale_;
	buffer << NO_COPY << FOUR_BYTE_LENGTH << static_cast< UL >( sizeof( decimalLiteral_.digits_ ) );
	buffer >> decimalLiteral_.digits_;
}
