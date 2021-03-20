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


VarbinaryValue::VarbinaryValue( const VarbinaryValue& other ) : AbstractValue( CQL_VARBINARY )
{
	length_ = other.length_;
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memcpy( buffer_, other.buffer_, length_ );
}


VarbinaryValue::VarbinaryValue( pUC& source ) : AbstractValue( CQL_VARBINARY ), buffer_( 0 ), length_( 0 )
{
	memcpy( &length_, source, sizeof( length_ ) );
	source += sizeof( length_ );

	if( buffer_ )
		delete [] buffer_;

	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	memcpy( buffer_, source, length_ );
	source += length_;
}


VarbinaryValue::VarbinaryValue( const CqlColumnTypes& ctype ) : AbstractValue( CQL_VARBINARY )
{
	length_ = static_cast< UC >( ctype.typeLength() );
	if( length_ != ctype.typeLength() )
		throw SizeConversionException( __FILE__, __LINE__ );
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
}


VarbinaryValue::VarbinaryValue( UC _length, UC *source ) : AbstractValue( CQL_VARBINARY ), buffer_( 0 ), length_( 0 )
{
	buffer_ = new UC[ _length ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	length_ = _length;
	memcpy( buffer_, source, length_ );
}


VarbinaryValue::VarbinaryValue( const CqlString& source ) : AbstractValue( CQL_VARBINARY )
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


VarbinaryValue::VarbinaryValue( const NC* ) : AbstractValue( CQL_VARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


VarbinaryValue::VarbinaryValue( const UC* ) : AbstractValue( CQL_VARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


VarbinaryValue::VarbinaryValue( const NC ) : AbstractValue( CQL_VARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


VarbinaryValue::VarbinaryValue( const D ) : AbstractValue( CQL_VARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


VarbinaryValue::VarbinaryValue( const NI ) : AbstractValue( CQL_VARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


VarbinaryValue::VarbinaryValue( const UNI ) : AbstractValue( CQL_VARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


VarbinaryValue::VarbinaryValue( const US ) : AbstractValue( CQL_VARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


VarbinaryValue::VarbinaryValue( const UL ) : AbstractValue( CQL_VARBINARY, 0 )
{
	throw InvalidConstructorException( __FILE__, __LINE__ );
}


void VarbinaryValue::operator = ( const VarbinaryValue& other )
{
	length_ = other.length_;

	if( buffer_ )
		delete [] buffer_;

	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	memcpy( buffer_, other.buffer_, length_ );
}


AbstractValue& VarbinaryValue::operator = ( const AbstractValue& cav )
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
			length_ = static_cast< UC >( bv.length() );
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
			length_ = vv.length_;
			if( !length_ )
			{
				buffer_ = 0;
				return *this;
			}
			buffer_ = new UC[ length_ ];
			if( !buffer_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			memcpy( buffer_, vv.buffer_, length_ );
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


CqlConstants::CompareResult VarbinaryValue::compare( const VarbinaryValue& other ) const
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


void VarbinaryValue::output( TempBuffer& tb ) const
{
	tb << ONE_BYTE_LENGTH << DO_COPY << length_;
	tb << buffer_;
}


void VarbinaryValue::input( TempBuffer& tb )
{
	UC instanceLength;

	tb << ONE_BYTE_LENGTH << DO_COPY;

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


UL VarbinaryValue::length( void ) const
{
	return length_;
}


UL VarbinaryValue::streamLength( void ) const
{
	return length_ + sizeof( length_ );
}


void VarbinaryValue::releaseMemory( void )
{
	if( buffer_ )
	{
		delete [] buffer_;
		buffer_ = 0;
		length_ = 0;
	}
}


NC VarbinaryValue::asChar() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


S VarbinaryValue::asShort() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


L VarbinaryValue::asLong() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


BigintValue VarbinaryValue::asBigintValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return BigintValue();
#endif
}


DecimalValue VarbinaryValue::asDecimalValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DecimalValue();
#endif
}


F VarbinaryValue::asFloat() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


D VarbinaryValue::asDouble() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return 0;
#endif
}


DateValue VarbinaryValue::asDateValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return DateValue();
#endif
}


TimeValue VarbinaryValue::asTimeValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimeValue();
#endif
}


TimestampValue VarbinaryValue::asTimestampValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  for stupid compilers
	return TimestampValue();
#endif
}


void VarbinaryValue::operator << ( pUC& buf )
{
	UC localLength;
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


void VarbinaryValue::operator >> ( pUC& buf )
{
	memcpy( buf, &length_, sizeof( length_ ) );
	buf += length_;
	memcpy( buf, buffer_, length_ );
	buf += length_;
}


void VarbinaryValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( buffer_, length_ );
}


void VarbinaryValue::operator << ( BinaryValue& bv )
{
	if( length_ != bv.length() )
	{
		if( buffer_ )
			delete buffer_;

		buffer_ = new UC[ bv.length() ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		length_ = static_cast< UC >( bv.length() );
		if( length_ != bv.length() )
			throw LengthExceededException( __FILE__, __LINE__ );
	}

	memcpy( buffer_, bv.buffer(), length_ );
}


void VarbinaryValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void VarbinaryValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void VarbinaryValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void VarbinaryValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& VarbinaryValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& VarbinaryValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& VarbinaryValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& VarbinaryValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnBLOBDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


bool VarbinaryValue::operator == ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarbinaryValue& bv = dynamic_cast< VarbinaryValue& >( other );
	if( length_ != bv.length_ )
		return false;
	else if( memcmp( buffer_, bv.buffer_, length_ ) )
		return false;
	else
		return true;
}


bool VarbinaryValue::operator != ( const AbstractValue& other ) const
{
	if( *this == other )
		return false;
	else
		return true;
}


bool VarbinaryValue::operator >= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarbinaryValue& bv = dynamic_cast< VarbinaryValue& >( other );
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


bool VarbinaryValue::operator > ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarbinaryValue& bv = dynamic_cast< VarbinaryValue& >( other );
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


bool VarbinaryValue::operator <= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarbinaryValue& bv = dynamic_cast< VarbinaryValue& >( other );
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


bool VarbinaryValue::operator < ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarbinaryValue& bv = dynamic_cast< VarbinaryValue& >( other );
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


bool VarbinaryValue::operator ! ( void ) const
{
	if( buffer_ && buffer_[ 0 ] )
		return false;
	else
		return true;
}


void VarbinaryValue::encode( CqlString&, bool /*spacePadding*/ )
{
	throw StringRepresentationRequestedForBinaryDataException( __FILE__, __LINE__ );
}


void VarbinaryValue::writeDictionaryInformation( TempBuffer& _buffer )
{
	_buffer << ONE_BYTE_LENGTH << DO_COPY << length_ << buffer_;
}


void VarbinaryValue::readDictionaryInformation( TempBuffer& _buffer )
{
	_buffer << ONE_BYTE_LENGTH << DO_COPY;
	_buffer >> length_;
	buffer_ = new UC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	_buffer >> buffer_;
}


US VarbinaryValue::dictionaryLength( void )
{
	return static_cast< US >( sizeof( bool ) + length_ );
}
