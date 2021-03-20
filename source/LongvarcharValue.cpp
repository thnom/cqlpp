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


LongvarcharValue::LongvarcharValue( const LongvarcharValue& other ) : AbstractValue( CQL_LONGVARCHAR )
{
	length_ = other.length_;
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memcpy( buffer_, other.buffer_, length_ );
}


LongvarcharValue::LongvarcharValue( pUC& source ) : AbstractValue( CQL_LONGVARCHAR ), buffer_( 0 ), length_( 0 )
{
	const NC *cstring = const_cast< const NC * >( reinterpret_cast< NC* >( source ) );
	size_t stringLength = strlen( cstring );

	//  length check not really necessary now, but if size_t should change in the future...
	length_ = static_cast< UL >( stringLength + 1 );
	if( length_ != stringLength + 1 )
		throw SizeConversionException( __FILE__, __LINE__ );

	if( buffer_ )
		delete [] buffer_;
	buffer_ = new NC[ length_ ];
	strcpy( buffer_, cstring );
	source += length_;
}


LongvarcharValue::LongvarcharValue( const CqlColumnTypes& ctype ) : AbstractValue( CQL_LONGVARCHAR )
{
	length_ = ctype.typeLength();
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
}


LongvarcharValue::LongvarcharValue( UL _length, UC *source ) : AbstractValue( CQL_LONGVARCHAR ), buffer_( 0 ), length_( 0 )
{
	if( !buffer_ || _length + 1 != length_ )
	{
		if( buffer_ )
			delete [] buffer_;

		length_ = _length + 1;
		buffer_ = new NC[ length_ ];
	}

	strcpy( buffer_, reinterpret_cast< NC* >( source ) );
}


LongvarcharValue::LongvarcharValue( const CqlString& source ) : AbstractValue( CQL_LONGVARCHAR ), buffer_( 0 ), length_( 0 )
{
	length_ = source.length();
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	strcpy( buffer_, source.text() );
}


LongvarcharValue::LongvarcharValue( const NC *source ) : AbstractValue( CQL_LONGVARCHAR )
{
	length_ = strlen( source ) + 1;
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	strcpy( buffer_, source );
}


LongvarcharValue::LongvarcharValue( const UC *usource ) : AbstractValue( CQL_LONGVARCHAR )
{
	const NC *source = reinterpret_cast< const NC* >( usource );
	length_ = strlen( source ) + 1;
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	strcpy( buffer_, source );
}


LongvarcharValue& LongvarcharValue::operator = ( const LongvarcharValue& other )
{
	if( length_ != other.length_ )
	{
		if( buffer_ )
			delete [] buffer_;

		buffer_ = new NC[ other.length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		length_ = other.length_;
	}

	strcpy( buffer_, other.buffer_ );
	return *this;
}


AbstractValue& LongvarcharValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_CHAR :
	case CQL_CHARUC :
		{
			CharValue& cv = dynamic_cast< CharValue& >( av );
			*this = cv.value();
		}
		break;

	case CQL_VARCHAR :
		{
			VarcharValue& vv = dynamic_cast< VarcharValue& >( av );
			length_ = vv.length();
			if( buffer_ )
				delete buffer_;
			if( !length_ )
				buffer_ = 0;
			else
			{
				buffer_ = new NC[ length_ ];
				if( !buffer_ )
					throw MemoryAllocationException( __FILE__, __LINE__ );
				memcpy( buffer_, vv.buffer(), length_ );
			}
		}
		break;

	case CQL_LONGVARCHAR :
		{
			LongvarcharValue& lvv = dynamic_cast< LongvarcharValue& >( av );
			length_ = lvv.length_;
			if( buffer_ )
				delete buffer_;
			if( !length_ )
				buffer_ = 0;
			else
			{
				buffer_ = new NC[ length_ ];
				if( !buffer_ )
					throw MemoryAllocationException( __FILE__, __LINE__ );
				memcpy( buffer_, lvv.buffer_, length_ );
			}
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


LongvarcharValue::LongvarcharValue( const NC ) : AbstractValue( CQL_CHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


LongvarcharValue::LongvarcharValue( const D ) : AbstractValue( CQL_CHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


LongvarcharValue::LongvarcharValue( const NI ) : AbstractValue( CQL_CHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


LongvarcharValue::LongvarcharValue( const UNI ) : AbstractValue( CQL_CHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


LongvarcharValue::LongvarcharValue( const US ) : AbstractValue( CQL_CHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


LongvarcharValue::LongvarcharValue( const UL ) : AbstractValue( CQL_CHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


CqlConstants::CompareResult LongvarcharValue::compare( const LongvarcharValue& other ) const
{
	UL compareLength = ( length_ < other.length_ ? length_ : other.length_ );

	NI cmr = memcmp( buffer_, other.buffer_, compareLength );

	if( cmr == 0 )
	{
		if( length_ == other.length_ )
			return THIS_EQUAL_TO_OTHER;
		else if( length_ > other.length_ )
			return THIS_GREATER_THAN_OTHER;
		else
			return THIS_LESS_THAN_OTHER;
	}

	else if( cmr < 0 )
		return THIS_LESS_THAN_OTHER;
	else
		return THIS_GREATER_THAN_OTHER;
}


void LongvarcharValue::output( TempBuffer& tb ) const
{
	tb << DO_COPY << FOUR_BYTE_LENGTH << length_ << buffer_;
}


void LongvarcharValue::input( TempBuffer& tb )
{
	UL instanceLength;

	tb << DO_COPY << FOUR_BYTE_LENGTH;
	tb >> instanceLength;

	if( length_ != instanceLength )
	{
		if( buffer_ )
			delete [] buffer_;

		length_ = instanceLength;
		buffer_ = new NC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	tb >> buffer_;
}


UL LongvarcharValue::length( void ) const
{
	return length_;
}


UL LongvarcharValue::streamLength( void ) const
{
	return length_ + sizeof( length_ );
}


void LongvarcharValue::releaseMemory( void )
{
	if( buffer_ )
	{
		delete [] buffer_;
		buffer_ = 0;
		length_ = 0;
	}
}


NC LongvarcharValue::asChar() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


S LongvarcharValue::asShort() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


L LongvarcharValue::asLong() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


BigintValue LongvarcharValue::asBigintValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return BigintValue();
#endif
}


DecimalValue LongvarcharValue::asDecimalValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DecimalValue();
#endif
}


F LongvarcharValue::asFloat() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


D LongvarcharValue::asDouble() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


DateValue LongvarcharValue::asDateValue() const
{
	//  temporary
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue LongvarcharValue::asTimeValue() const
{
	//  temporary
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue LongvarcharValue::asTimestampValue() const
{
	//  temporary
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimestampValue();
#endif
}


const CqlString LongvarcharValue::asString( bool /* spacePadding */ ) const
{
	return CqlString( buffer_ );
}


void LongvarcharValue::operator << ( pUC& buf )
{
	UL localLength;

	memcpy( &localLength, buf, sizeof( localLength ) );
	buf += sizeof( localLength );

	if( localLength != length_ )
	{
		if( buffer_ )
			delete [] buffer_;
		buffer_ = new NC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		length_ = localLength;
	}

	memcpy( buffer_, buf, length_ );
	buf += length_;
}


void LongvarcharValue::operator >> ( pUC& buf )
{
	memcpy( buf, &length_, sizeof( length_ ) );
	buf += sizeof( length_ );
	memcpy( buf, buffer_, length_ );
	buf += length_;
}


void LongvarcharValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( reinterpret_cast< UC *>( buffer_ ), length_ );
}


void LongvarcharValue::operator << ( BinaryValue& bv )
{
	if( length_ != bv.length() )
	{
		if( buffer_ )
			delete buffer_;

		buffer_ = new NC[ bv.length() ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		length_ = bv.length();
	}

	memcpy( buffer_, bv.buffer(), length_ );
}


void LongvarcharValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void LongvarcharValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void LongvarcharValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void LongvarcharValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& LongvarcharValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& LongvarcharValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& LongvarcharValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& LongvarcharValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


bool LongvarcharValue::operator == ( const AbstractValue& cother) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarcharValue& cv = dynamic_cast< LongvarcharValue& >( other );

	if( length_ != cv.length_ )
		return false;

	if( !strcmp( buffer_, cv.buffer_ ) )
		return true;
	else
		return false;
}


bool LongvarcharValue::operator != ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarcharValue& cv = dynamic_cast< LongvarcharValue& >( other );
	if( length_ != cv.length_ )
		return true;

	if( strcmp( buffer_, cv.buffer_ ) )
		return true;
	else
		return false;
}


bool LongvarcharValue::operator >= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarcharValue& cv = dynamic_cast< LongvarcharValue& >( other );
	NI compareLength = ( length_ < cv.length_ ? length_ : cv.length_ );
	NI memcmpResult = memcmp( buffer_, cv.buffer_, compareLength );
	if( memcmpResult < 0 )
		return false;
	else if( memcmpResult > 0 )
		return true;
	else if( length_ > cv.length_ )
		return true;
	else
		return false;
}


bool LongvarcharValue::operator > ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarcharValue& cv = dynamic_cast< LongvarcharValue& >( other );
	NI compareLength = ( length_ < cv.length_ ? length_ : cv.length_ );
	NI memcmpResult = memcmp( buffer_, cv.buffer_, compareLength );
	if( memcmpResult <= 0 )
		return false;
	else if( memcmpResult > 0 )
		return true;
	else if( length_ > cv.length_ )
		return true;
	else
		return false;
}


bool LongvarcharValue::operator < ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarcharValue& cv = dynamic_cast< LongvarcharValue& >( other );
	NI compareLength = ( length_ < cv.length_ ? length_ : cv.length_ );
	NI memcmpResult = memcmp( buffer_, cv.buffer_, compareLength );
	if( memcmpResult >= 0 )
		return false;
	else if( memcmpResult < 0 )
		return true;
	else if( length_ < cv.length_ )
		return true;
	else
		return false;
}


bool LongvarcharValue::operator <= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarcharValue& cv = dynamic_cast< LongvarcharValue& >( other );
	NI compareLength = ( length_ < cv.length_ ? length_ : cv.length_ );
	NI memcmpResult = memcmp( buffer_, cv.buffer_, compareLength );
	if( memcmpResult > 0 )
		return false;
	else if( memcmpResult < 0 )
		return true;
	else if( length_ < cv.length_ )
		return true;
	else
		return false;
}


bool LongvarcharValue::operator ! ( void ) const
{
	if( buffer_ && buffer_[ 0 ] )
		return false;
	else
		return true;
}


void LongvarcharValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	_output = buffer_;
}


US LongvarcharValue::dictionaryLength( void )
{
	return static_cast< US >( sizeof( bool ) + length_ );
}


void LongvarcharValue::writeDictionaryInformation( TempBuffer& _buffer )
{
	_buffer << nullflag() << FOUR_BYTE_LENGTH << DO_COPY << length_ << buffer_;
}


void LongvarcharValue::readDictionaryInformation( TempBuffer& _buffer )
{
	_buffer >> nullflag();
	_buffer << FOUR_BYTE_LENGTH << DO_COPY;
	_buffer >> length_;
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	_buffer >> buffer_;
}
