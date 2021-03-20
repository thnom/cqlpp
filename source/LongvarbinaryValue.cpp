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


LongvarbinaryValue::LongvarbinaryValue( const LongvarbinaryValue& other ) : AbstractValue( CQL_LONGVARBINARY )
{
	length_ = other.length_;
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memcpy( buffer_, other.buffer_, length_ );
}


LongvarbinaryValue::LongvarbinaryValue( pUC& source ) : AbstractValue( CQL_LONGVARBINARY ), buffer_( 0 ), length_( 0 )
{
	memcpy( &length_, source, sizeof( length_ ) );
	source += sizeof( length_ );

	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	memcpy( buffer_, source, length_ );
	source += length_;
}


LongvarbinaryValue::LongvarbinaryValue( const CqlColumnTypes& ctype ) : AbstractValue( CQL_LONGVARBINARY )
{
	length_ = ctype.typeLength();
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
}


LongvarbinaryValue::LongvarbinaryValue( const UC *source, const UL _length ) : AbstractValue( CQL_LONGVARBINARY ), buffer_( 0 ), length_( 0 )
{
	buffer_ = new UC[ _length ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	length_ = _length;
	memcpy( buffer_, source, length_ );
}


LongvarbinaryValue::LongvarbinaryValue( const CqlString& source ) : AbstractValue( CQL_LONGVARBINARY )
{
	if( !buffer_ || length_ != source.length() )
	{
		if( buffer_ )
			delete [] buffer_;

		length_ = source.length();
		buffer_ = new UC[ length_ ];
	}

	memcpy( buffer_, source.text(), length_ );
}


LongvarbinaryValue::LongvarbinaryValue( const NC* ) : AbstractValue( CQL_LONGVARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


LongvarbinaryValue::LongvarbinaryValue( const UC* ) : AbstractValue( CQL_LONGVARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


LongvarbinaryValue::LongvarbinaryValue( const NC ) : AbstractValue( CQL_LONGVARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


LongvarbinaryValue::LongvarbinaryValue( const D ) : AbstractValue( CQL_LONGVARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


LongvarbinaryValue::LongvarbinaryValue( const NI ) : AbstractValue( CQL_LONGVARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


LongvarbinaryValue::LongvarbinaryValue( const UNI ) : AbstractValue( CQL_LONGVARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


LongvarbinaryValue::LongvarbinaryValue( const US ) : AbstractValue( CQL_LONGVARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


LongvarbinaryValue::LongvarbinaryValue( const UL ) : AbstractValue( CQL_LONGVARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


LongvarbinaryValue& LongvarbinaryValue::operator = ( const LongvarbinaryValue& other )
{
	length_ = other.length_;

	if( buffer_ )
		delete [] buffer_;

	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	memcpy( buffer_, other.buffer_, length_ );
	return *this;
}


AbstractValue& LongvarbinaryValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_BINARY :
		{
			if( buffer_ )
				delete buffer_;

			BinaryValue& bv = dynamic_cast< BinaryValue& >( av );
			length_ = bv.length();
			if( !length_ )
			{
				buffer_ = 0;
				return *this;
			}
			buffer_ = new UC[ length_ ];
			if( !buffer_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			memcpy( buffer_, bv.buffer(), length_ );
		}
		break;

	case CQL_VARBINARY :
		{
			if( buffer_ )
				delete buffer_;
			VarbinaryValue& vv = dynamic_cast< VarbinaryValue& >( av );
			length_ = vv.length();
			if( !length_ )
			{
				buffer_ = 0;
				return *this;
			}
			buffer_ = new UC[ length_ ];
			if( !buffer_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			memcpy( buffer_, vv.buffer(), length_ );
		}
		break;

	case CQL_LONGVARBINARY :
		{
			LongvarbinaryValue& lvv = dynamic_cast< LongvarbinaryValue& >( av );
			length_ = lvv.length_;
			if( buffer_ )
				delete buffer_;
			if( length_ == 0 )
			{
				buffer_ = 0;
				return *this;
			}
			buffer_ = new UC[ length_ ];
			if( !buffer_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			memcpy( buffer_, lvv.buffer_, length_ );
		}
		break;

	case CQL_CHAR :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_CHARUC :
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


CqlConstants::CompareResult LongvarbinaryValue::compare( const LongvarbinaryValue& other ) const
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


void LongvarbinaryValue::input( TempBuffer& tb )
{
	UL instanceLength;

	tb << DO_COPY << FOUR_BYTE_LENGTH;
	tb >> instanceLength;

	if( length_ != instanceLength )
	{
		if( buffer_ )
			delete [] buffer_;

		length_ = instanceLength;
		buffer_ = new UC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	tb >> buffer_;
}


void LongvarbinaryValue::output( TempBuffer& tb ) const
{
	tb << DO_COPY << FOUR_BYTE_LENGTH << length_ << buffer_;
}


UL LongvarbinaryValue::length( void ) const
{
	return length_;
}


UL LongvarbinaryValue::streamLength( void ) const
{
	return length_ + sizeof( length_ );
}


void LongvarbinaryValue::releaseMemory( void )
{
	if( buffer_ )
	{
		delete [] buffer_;
		buffer_ = 0;
		length_ = 0;
	}
}


NC LongvarbinaryValue::asChar() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


S LongvarbinaryValue::asShort() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


L LongvarbinaryValue::asLong() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


BigintValue LongvarbinaryValue::asBigintValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return BigintValue();
#endif
}


DecimalValue LongvarbinaryValue::asDecimalValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DecimalValue();
#endif
}


F LongvarbinaryValue::asFloat() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


D LongvarbinaryValue::asDouble() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


DateValue LongvarbinaryValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue LongvarbinaryValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue LongvarbinaryValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimestampValue();
#endif
}


void LongvarbinaryValue::operator << ( pUC& buf )
{
	UL localLength;
	memcpy( &localLength, buf, sizeof( localLength ) );
	buf += sizeof( localLength );

	if( length_ != localLength )
	{
		if( buffer_ )
			delete [] buffer_;
		buffer_ = new UC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		length_ = localLength;
	}

	memcpy( buffer_, buf, length_ );
	buf += length_;
}


void LongvarbinaryValue::operator >> ( pUC& buf )
{
	memcpy( buf, &length_, sizeof( length_ ) );
	buf += sizeof( length_ );
	memcpy( buf, buffer_, length_ );
	buf += length_;
}


void LongvarbinaryValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( buffer_, length_ );
}


void LongvarbinaryValue::operator << ( BinaryValue& bv )
{
	if( length_ != bv.length() )
	{
		if( buffer_ )
			delete buffer_;

		buffer_ = new UC[ bv.length() ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		length_ = bv.length();
	}

	memcpy( buffer_, bv.buffer(), length_ );
}


void LongvarbinaryValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void LongvarbinaryValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void LongvarbinaryValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void LongvarbinaryValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& LongvarbinaryValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& LongvarbinaryValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& LongvarbinaryValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& LongvarbinaryValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


bool LongvarbinaryValue::operator == ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarbinaryValue& bv = dynamic_cast< LongvarbinaryValue& >( other );
	if( length_ != bv.length_ )
		return false;
	else if( memcmp( buffer_, bv.buffer_, length_ ) )
		return false;
	else
		return true;
}


bool LongvarbinaryValue::operator != ( const AbstractValue& other ) const
{
	if( *this == other )
		return false;
	else
		return true;
}


bool LongvarbinaryValue::operator >= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarbinaryValue& bv = dynamic_cast< LongvarbinaryValue& >( other );
	UNI compareLength = ( length_ < bv.length_ ? length_ : bv.length_ );
	NI memcmpResult = memcmp( buffer_, bv.buffer_, compareLength );
	if( memcmpResult >= 0 )
		return true;
	else if( memcmpResult < 0 )
		return false;
	else if( length_ > bv.length_ )
		return true;
	else
		return false;
}


bool LongvarbinaryValue::operator > ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarbinaryValue& bv = dynamic_cast< LongvarbinaryValue& >( other );
	UNI compareLength = ( length_ < bv.length_ ? length_ : bv.length_ );
	NI memcmpResult = memcmp( buffer_, bv.buffer_, compareLength );
	if( memcmpResult <= 0 )
		return false;
	else if( memcmpResult > 0 )
		return true;
	else if( length_ > bv.length_ )
		return true;
	else
		return false;
}


bool LongvarbinaryValue::operator <= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarbinaryValue& bv = dynamic_cast< LongvarbinaryValue& >( other );
	UNI compareLength = ( length_ < bv.length_ ? length_ : bv.length_ );
	NI memcmpResult = memcmp( buffer_, bv.buffer_, compareLength );
	if( memcmpResult > 0 )
		return false;
	else if( memcmpResult < 0 )
		return true;
	else if( length_ < bv.length_ )
		return true;
	else
		return false;
}


bool LongvarbinaryValue::operator < ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	LongvarbinaryValue& bv = dynamic_cast< LongvarbinaryValue& >( other );
	UNI compareLength = ( length_ < bv.length_ ? length_ : bv.length_ );
	NI memcmpResult = memcmp( buffer_, bv.buffer_, compareLength );
	if( memcmpResult > 0 )
		return false;
	else if( memcmpResult < 0 )
		return true;
	else if( length_ < bv.length_ )
		return true;
	else
		return false;
}


bool LongvarbinaryValue::operator ! ( void ) const
{
	if( length_ )
		return false;
	else
		return true;
}


US LongvarbinaryValue::dictionaryLength( void )
{
	return static_cast< US >( sizeof( bool ) + length_ );
}


void LongvarbinaryValue::encode( CqlString&, bool )
{
	throw StringRepresentationRequestedForBinaryDataException( __FILE__, __LINE__ );
}


void LongvarbinaryValue::writeDictionaryInformation( TempBuffer& _buffer )
{
	_buffer << FOUR_BYTE_LENGTH << DO_COPY << length_ << buffer_;
}


void LongvarbinaryValue::readDictionaryInformation( TempBuffer& _buffer )
{
	_buffer << FOUR_BYTE_LENGTH << DO_COPY;
	_buffer >> length_;
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	_buffer >> buffer_;
}
