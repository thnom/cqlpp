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


BinaryValue::BinaryValue( pUC& source ) : AbstractValue( CQL_BINARY )
{
	memcpy( &length_, source, sizeof( length_ ) );
	source += sizeof( length_ );
	//  set length in CqlColumnTypes
	typeLength( length_ );

	if( buffer_ )
		delete [] buffer_;

	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	memcpy( buffer_, source, length_ );
	source += length_;
}


BinaryValue::BinaryValue( const CqlColumnTypes& ctype ) : AbstractValue( CQL_BINARY, ctype.typeLength() )
{
	length_ = static_cast< UC >( ctype.typeLength() );
	if( static_cast< L >( length_ ) != static_cast< L >( ctype.typeLength() ) )
		throw SizeConversionException( __FILE__, __LINE__ );
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
}


BinaryValue::BinaryValue( const UC *data, const UNI len ) : AbstractValue( CQL_BINARY, static_cast< const UL >( len ) )
{
	length_ = static_cast< const UC >( len );
	if( length_ != len )
		throw SizeConversionException( __FILE__, __LINE__ );

	buffer_ = new UC[ length_ ];
	//exception
	memcpy( buffer_, data, length_ );
}


BinaryValue::BinaryValue( const CqlString& source ) : AbstractValue( CQL_BINARY, source.length() )
{
	if( !buffer_ || length_ != source.length() )
	{
		if( buffer_ )
			delete [] buffer_;

		length_ = static_cast< UC >( source.length() );
		buffer_ = new UC[ length_ ];
	}
	memcpy( buffer_, source.text(), length_ );
}


BinaryValue::BinaryValue( const NC* ) : AbstractValue( CQL_BINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


BinaryValue::BinaryValue( const UC* ) : AbstractValue( CQL_BINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


BinaryValue::BinaryValue( const NC ) : AbstractValue( CQL_BINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


BinaryValue::BinaryValue( const double ) : AbstractValue( CQL_BINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


BinaryValue::BinaryValue( const NI ) : AbstractValue( CQL_BINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


BinaryValue::BinaryValue( const UNI ) : AbstractValue( CQL_BINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


BinaryValue::BinaryValue( const US ) : AbstractValue( CQL_BINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


BinaryValue::BinaryValue( const UL ) : AbstractValue( CQL_BINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


BinaryValue::BinaryValue( const BinaryValue& other ) : AbstractValue( CQL_BINARY, other.length_ )
{
	if( !buffer_ || length_ != other.length_ )
	{
		if( buffer_ )
			delete [] buffer_;

		length_ = other.length_;
		buffer_ = new UC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	memcpy( buffer_, other.buffer_, length_ );
}


AbstractValue& BinaryValue::operator = ( const AbstractValue& cav )
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
			length_ = bv.length_;
			if( !length_ )
			{
				buffer_ = 0;
				return *this;
			}
			buffer_ = new UC[ length_ ];
			if( !buffer_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			memcpy( buffer_, bv.buffer_, length_ );
		}
		break;

	case CQL_VARBINARY :
		{
			if( buffer_ )
				delete buffer_;
			VarbinaryValue& vv = dynamic_cast< VarbinaryValue& >( av );
			length_ = static_cast< UC >( vv.length() );
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
			length_ = static_cast< UC >( lvv.length() );
			if( static_cast< UL >( length_ ) != lvv.length() )
				throw LengthExceededException( __FILE__, __LINE__ );
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
			memcpy( buffer_, lvv.buffer(), length_ );
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


CqlConstants::CompareResult BinaryValue::compare( const BinaryValue& other ) const
{
	UC lengthToCompare = ( length_ < other.length_ ? length_ : other.length_ );

	NI cmr = memcmp( buffer_, other.buffer_, lengthToCompare );

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


void BinaryValue::output( TempBuffer& tb ) const
{
	//  fixed length binary, don't copy length.
	tb << NO_COPY << ONE_BYTE_LENGTH << length_ << buffer_;
}	


void BinaryValue::input( TempBuffer& tb )
{
	tb << NO_COPY << ONE_BYTE_LENGTH << length_;
	tb >> buffer_;
}


void BinaryValue::expand( UL newLength )
{
	pUC tval = new UC[ length_ + newLength ];
	if( !tval )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	memset( tval, 0, length_ + newLength );
	if( length_ )
		memcpy( tval, buffer_, length_ );
	if( buffer_ )
		delete [] buffer_;

	buffer_ = tval;
	length_ = ((UC)( length_ + newLength ) );
}


UL BinaryValue::length( void ) const
{
	return length_;
}


UL BinaryValue::streamLength( void ) const
{
	return length() + sizeof( length_ );
}


void BinaryValue::releaseMemory( void )
{
	if( buffer_ )
	{
		delete [] buffer_;
		buffer_ = 0;
		length_ = 0;
	}
}


SC BinaryValue::asChar() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


S BinaryValue::asShort() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


L BinaryValue::asLong() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


BigintValue BinaryValue::asBigintValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return BigintValue();
#endif
}


DecimalValue BinaryValue::asDecimalValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DecimalValue();
#endif
}


F BinaryValue::asFloat() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


D BinaryValue::asDouble() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


DateValue BinaryValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue BinaryValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue BinaryValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimestampValue();
#endif
}


void BinaryValue::operator << ( pUC& buf )
{
	memcpy( buffer_, buf, length_ );
	buf += length_;
}


void BinaryValue::operator >> ( pUC& buf )
{
	memcpy( buf, buffer_, length_ );
	buf += length_;
}


void BinaryValue::operator >> ( BinaryValue& bv )
{
	bv = *this;
}


void BinaryValue::operator << ( BinaryValue& bv )
{
	*this = bv;
}


void BinaryValue::operator = ( const BinaryValue& other )
{
	length_ = other.length_;

	if( buffer_ )
		delete [] buffer_;

	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	memcpy( buffer_, other.buffer_, length_ );
}


void BinaryValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void BinaryValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void BinaryValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void BinaryValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


void BinaryValue::initialize( void )
{
	length_ = static_cast< UC >( typeLength() );
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
}


AbstractValue& BinaryValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& BinaryValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& BinaryValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& BinaryValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


bool BinaryValue::operator == ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	BinaryValue& bv = dynamic_cast< BinaryValue& >( other );
	if( length_ != bv.length_ )
		return false;
	else if( memcmp( buffer_, bv.buffer_, length_ ) )
		return false;
	else
		return true;
}


bool BinaryValue::operator != ( const AbstractValue& other ) const
{
	if( *this == other )
		return false;
	else
		return true;
}


bool BinaryValue::operator >= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	BinaryValue& bv = dynamic_cast< BinaryValue& >( other );
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


bool BinaryValue::operator > ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	BinaryValue& bv = dynamic_cast< BinaryValue& >( other );
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


bool BinaryValue::operator <= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	BinaryValue& bv = dynamic_cast< BinaryValue& >( other );
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


bool BinaryValue::operator < ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	BinaryValue& bv = dynamic_cast< BinaryValue& >( other );
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


bool BinaryValue::operator ! ( void ) const
{
	if( buffer_ && length_ )
		return false;
	else
		return true;
}


void BinaryValue::encode( CqlString&, bool /*spacePadding*/ )
{
	throw StringRepresentationRequestedForBinaryDataException( __FILE__, __LINE__ );
}


US BinaryValue::dictionaryLength( void )
{
	return static_cast< US >( sizeof( bool ) + length_ );
}


void BinaryValue::writeDictionaryInformation( TempBuffer& _buffer )
{
	_buffer << nullflag() << ONE_BYTE_LENGTH << DO_COPY << length_ << buffer_;
}


void BinaryValue::readDictionaryInformation( TempBuffer& _buffer )
{
	_buffer >> nullflag();
	_buffer << ONE_BYTE_LENGTH << DO_COPY;
	_buffer >> length_;
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	_buffer >> buffer_;
}
