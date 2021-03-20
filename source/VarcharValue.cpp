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


VarcharValue::VarcharValue( const VarcharValue& other ) : AbstractValue( CQL_VARCHAR )
{
	length_ = other.length_;
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memcpy( buffer_, other.buffer_, length_ );
}


VarcharValue::VarcharValue( const CqlColumnTypes& ctype ) : AbstractValue( CQL_VARCHAR )
{
	length_ = static_cast< UC >( ctype.typeLength() );
	if( length_ != ctype.typeLength() )
		throw SizeConversionException( __FILE__, __LINE__ );
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
}


VarcharValue::VarcharValue( pUC& source ) : AbstractValue( CQL_VARCHAR ), buffer_( 0 ), length_( 0 )
{
	const NC *cstring = const_cast< const NC *>( reinterpret_cast< NC* >( source ) );

	size_t stringLength = strlen( cstring );
	length_ = static_cast< UC >( stringLength + 1 );
	if( length_ != stringLength + 1 )
		throw SizeConversionException( __FILE__, __LINE__ );

	if( buffer_ )
		delete [] buffer_;
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	strcpy( buffer_, cstring );
	source += stringLength;
}


VarcharValue::VarcharValue( const NC *source ) : AbstractValue( CQL_VARCHAR ), buffer_( 0 ), length_( 0 )
{
	UC _length = static_cast< UC >( strlen( source ) + 1 );

	if( !buffer_ || length_ != _length )
	{
		if( buffer_ )
			delete [] buffer_;

		buffer_ = new NC[ _length ];
		length_ = _length;
	}

	strcpy( buffer_, source );
}


VarcharValue::VarcharValue( const CqlString& source ) : AbstractValue( CQL_VARCHAR )
{
	length_ = static_cast< UC >( source.length() );
	if( length_ == 0 )
	{
		buffer_ = new NC[ 1 ];
		buffer_[ 0 ] = 0;
		return;
	}

	if( length_ != source.length() )
		throw SizeConversionException( __FILE__, __LINE__ );
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	strcpy( buffer_, source.text() );
}


VarcharValue::VarcharValue( const NC ) : AbstractValue( CQL_VARCHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


VarcharValue::VarcharValue( const D ) : AbstractValue( CQL_VARCHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


VarcharValue::VarcharValue( const NI ) : AbstractValue( CQL_VARCHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


VarcharValue::VarcharValue( const UC *source ) : AbstractValue( CQL_VARCHAR )
{
	const NC *s = reinterpret_cast< const NC* >( source );
	length_ = static_cast< UC >(strlen( s ) + 1 );
	if( length_ != strlen( s ) + 1 )
		throw SizeConversionException( __FILE__, __LINE__ );
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	strcpy( buffer_, s );
}


VarcharValue::VarcharValue( const UNI ) : AbstractValue( CQL_VARCHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


VarcharValue::VarcharValue( const US ) : AbstractValue( CQL_VARCHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


VarcharValue::VarcharValue( const UL ) : AbstractValue( CQL_VARCHAR )
{
	throw InvalidTypeCombinationException( __FILE__, __LINE__ );
}


VarcharValue& VarcharValue::operator = ( const VarcharValue& other )
{
	if( length_ != other.length_ )
	{
		length_ = other.length_;

		if( buffer_ )
			delete [] buffer_;

		buffer_ = new NC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	strcpy( buffer_, other.buffer_ );
	return *this;
}


AbstractValue& VarcharValue::operator = ( const AbstractValue& cav )
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
			length_ = static_cast< const UC >( vv.length_ );
			if( buffer_ )
				delete buffer_;
			if( !length_ )
				buffer_ = 0;
			else
			{
				buffer_ = new NC[ length_ ];
				if( !buffer_ )
					throw MemoryAllocationException( __FILE__, __LINE__ );
				memcpy( buffer_, vv.buffer_, length_ );
			}
		}
		break;

	case CQL_LONGVARCHAR :
		{
			LongvarcharValue& lvv = dynamic_cast< LongvarcharValue& >( av );
			length_ = static_cast< UC >( lvv.length() );
			if( static_cast< UL >( length_ ) != lvv.length() )
				throw LengthExceededException( __FILE__, __LINE__ );
			if( buffer_ )
				delete buffer_;
			if( !length_ )
				buffer_ = 0;
			else
			{
				buffer_ = new NC[ length_ ];
				if( !buffer_ )
					throw MemoryAllocationException( __FILE__, __LINE__ );
				memcpy( buffer_, lvv.buffer(), length_ );
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


CqlConstants::CompareResult VarcharValue::compare( const VarcharValue& other ) const
{
	UC compareLength = ( length_ < other.length_ ? length_ : other.length_ );

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


void VarcharValue::output( TempBuffer& tb ) const
{
	tb << DO_COPY << ONE_BYTE_LENGTH << static_cast< const UC >( length_ );
	tb << buffer_;
}


void VarcharValue::input( TempBuffer& tb )
{
	UC instanceLength;

	tb << DO_COPY << ONE_BYTE_LENGTH;
	tb >> instanceLength;

	if( instanceLength != length_ )
	{
		if( buffer_ )
			delete [] buffer_;
		length_ = instanceLength;
		buffer_ = new NC[ length_ ];
	}

	tb >> buffer_;
}


UL VarcharValue::length( void ) const
{
	return length_;
}


UL VarcharValue::streamLength( void ) const
{
	return length_ + sizeof( length_ );
}


void VarcharValue::releaseMemory( void )
{
	if( buffer_ )
	{
		delete [] buffer_;
		buffer_ = 0;
		length_ = 0;
	}
}


NC VarcharValue::asChar() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


S VarcharValue::asShort() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


L VarcharValue::asLong() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


BigintValue VarcharValue::asBigintValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return BigintValue();
#endif
}


DecimalValue VarcharValue::asDecimalValue() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return DecimalValue();
#endif
}


F VarcharValue::asFloat() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


D VarcharValue::asDouble() const
{
	throw IllegalTypeConversionException( __FILE__, __LINE__ );

#if defined( _MSC_VER ) && _MSC_VER != 1200
	// for dumb compilers
	return 0;
#endif
}


DateValue VarcharValue::asDateValue() const
{
	//  temporary
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return DateValue();
#endif
}


TimeValue VarcharValue::asTimeValue() const
{
	//  temporary
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return TimeValue();
#endif
}


TimestampValue VarcharValue::asTimestampValue() const
{
	//  temporary
	throw IllegalTypeConversionException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return TimestampValue();
#endif
}


const CqlString VarcharValue::asString( bool ) const
{
	//  padding is ignored for variable length string
	return CqlString( buffer_ );
}


void VarcharValue::operator << ( pUC& buf )
{
	UC localLength;
	memcpy( &localLength, buf, sizeof( localLength ) );
	buf += sizeof( localLength );

	if( length_ != localLength )
	{
		if( buffer_ )
			delete [] buffer_;
		buffer_ = new NC[ length_ ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		length_ = localLength;
	}

	strcpy( buffer_, reinterpret_cast< NC* >( buf ) );
	buf += length_;
}


void VarcharValue::operator >> ( pUC& buf )
{
	memcpy( buf, &length_, sizeof( length_ ) );
	buf += sizeof( length_ );
	memcpy( buf, buffer_, length_ );
	buf += length_;
}


void VarcharValue::operator >> ( BinaryValue& bv )
{
	bv = BinaryValue( reinterpret_cast< UC * >( buffer_ ), length_ );
}


void VarcharValue::operator << ( BinaryValue& bv )
{
	if( length_ != bv.length() )
	{
		if( buffer_ )
			delete buffer_;

		buffer_ = new NC[ bv.length() ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		length_ = static_cast< UC >( bv.length() - 1 );
		if( length_ != bv.length() )
			throw LengthExceededException( __FILE__, __LINE__ );
	}

	memcpy( buffer_, bv.buffer(), length_ );
}


void VarcharValue::operator << ( BoundColumn *bc )
{
	*bc >> *this;
}


void VarcharValue::operator >> ( BoundColumn *bc )
{
	*bc << *this;
}


void VarcharValue::operator << ( TempBuffer& tb )
{
	tb >> *this;
}


void VarcharValue::operator >> ( TempBuffer& tb )
{
	tb << *this;
}


AbstractValue& VarcharValue::operator += ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& VarcharValue::operator -= ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& VarcharValue::operator *= ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


AbstractValue& VarcharValue::operator /= ( AbstractValue& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return dynamic_cast< AbstractValue& >( *this );
#endif
}


bool VarcharValue::operator == ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarcharValue& vv = dynamic_cast< VarcharValue& >( other );
	if( length_ != vv.length_ )
		return false;
	else if( memcmp( buffer_, vv.buffer_, length_ ) )
		return false;
	else
		return true;
}


bool VarcharValue::operator != ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarcharValue& vv = dynamic_cast< VarcharValue& >( other );
	if( length_ != vv.length_ )
		return true;
	if( memcmp( buffer_, vv.buffer_, length_ ) )
		return true;
	return false;
}


bool VarcharValue::operator >= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarcharValue& vv = dynamic_cast< VarcharValue& >( other );
	UNI compareLength = ( length_ < vv.length_ ? length_ : vv.length_ );
	NI memcmpResult = memcmp( buffer_, vv.buffer_, compareLength );
	if( memcmpResult > 0 )
		return true;
	else if( memcmpResult < 0 )
		return false;
	else if( length_ >= vv.length_ )
		return true;
	else
		return false;
}


bool VarcharValue::operator > ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarcharValue& vv = dynamic_cast< VarcharValue& >( other );
	UNI compareLength = length_;
	if( vv.length_ < compareLength )
		compareLength = vv.length_;
	NI memcmpResult = memcmp( buffer_, vv.buffer_, compareLength );
	if( memcmpResult <= 0 )
		return false;
	else  if( length_ >= vv.length_ )
		return true;
	else
		return false;
}


bool VarcharValue::operator <= ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarcharValue& vv = dynamic_cast< VarcharValue& >( other );
	UNI compareLength = length_;
	if( vv.length_ < compareLength )
		compareLength = vv.length_;
	NI memcmpResult = memcmp( buffer_, vv.buffer_, compareLength );
	if( memcmpResult < 0 )
		return true;
	else if( memcmpResult > 0 )
		return false;
	else if( length_ <= vv.length_ )
		return true;
	else
		return false;
}


bool VarcharValue::operator < ( const AbstractValue& cother ) const
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );
	VarcharValue& vv = dynamic_cast< VarcharValue& >( other );
	UNI compareLength = length_;
	if( vv.length_ < compareLength )
		compareLength = vv.length_;
	NI memcmpResult = memcmp( buffer_, vv.buffer_, compareLength );
	if( memcmpResult >= 0 )
		return false;
	else  if( length_ < vv.length_ )
		return true;
	else
		return false;
}


bool VarcharValue::operator ! ( void ) const
{
	if( buffer_ && buffer_[ 0 ] )
		return false;
	else
		return true;
}


US VarcharValue::dictionaryLength( void )
{
	return static_cast< US >( length_ + sizeof( length_ ) );
}


void VarcharValue::encode( CqlString& _output, bool /*spacePadding*/ )
{
	_output = buffer_;
}


void VarcharValue::writeDictionaryInformation( TempBuffer& _buffer )
{
	_buffer << ONE_BYTE_LENGTH << DO_COPY << length_ << buffer_;
}


void VarcharValue::readDictionaryInformation( TempBuffer& _buffer )
{
	_buffer << ONE_BYTE_LENGTH << DO_COPY;
	_buffer >> length_;
	buffer_ = new NC[ length_ ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	_buffer >> buffer_;
}
