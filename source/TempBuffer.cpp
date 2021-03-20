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


TempBuffer::TempBuffer( AbstractDatabaseHandle& adh, SqlHandle* sqlh )
	: buffer_( 0 ),
	  bufferBase_( 0 ),
	  copyState_( DO_COPY ),
	  dbsql_( sqlh ),
	  hAdb_( adh ),
	  lengthState_( NO_LENGTH ),
	  size_( 0 ),
	  streamCopyLength_( 0 ),
	  currentPosition_( 0 )
{
}


TempBuffer::TempBuffer( AbstractDatabaseHandle& adh, const UL sz, SqlHandle* sqlh )
	: buffer_( 0 ),
	  copyState_( DO_COPY ),
	  dbsql_( sqlh ),
	  hAdb_( adh ),
	  lengthState_( NO_LENGTH ),
	  size_( 0 ),
	  streamCopyLength_( 0 ),
	  currentPosition_( 0 )
{
	UL allocationSize = sz + sizeof( UL );
	buffer_ = new UC[ allocationSize ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	bufferBase_ = buffer_ + sizeof( UL );
	size_ = ((UL *)buffer_);
	*size_ = sz;
	currentPosition_ = buffer_ + sizeof( UL );
}


TempBuffer::~TempBuffer( void )
{
	if( buffer_ )
		delete [] buffer_;
	buffer_ = ((pUC)0);
}


TempBuffer& TempBuffer::operator = ( TempBuffer& other )
{
	copyState_ = other.copyState_;
	lengthState_ = other.lengthState_;
	streamCopyLength_ = other.streamCopyLength_;

	if( !buffer_ || *size_ != *other.size_ )
	{
		if( buffer_ )
			delete [] buffer_;

		buffer_ = new UC[ *other.size_ + 4 ];
		if( !buffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		bufferBase_ = buffer_ + sizeof( UL );
		size_ = reinterpret_cast< UL *>( buffer_ );
		*size_ = *other.size_;
		currentPosition_ = buffer_ + sizeof( *size_ );
	}

	memcpy( buffer_ + sizeof( *size_ ), other.buffer_ + sizeof( *size_ ), *size_ );

	return *this;
}


NI TempBuffer::setBuffer( UNI bufSize )
{
	UL allocationSize = bufSize + sizeof( UL );

	if( buffer_ )
		delete [] buffer_;

	buffer_ = new UC[ ((UNI)allocationSize) ];
	if( !buffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	bufferBase_ = buffer_ + sizeof( UL );

	memset( buffer_, 0, ((UNI)allocationSize) );
	currentPosition_ = buffer_ + sizeof( UL );
	size_ = ((pUL)buffer_);
	*size_ = bufSize;
	return CQL_SUCCESS;
}


void TempBuffer::copyOut( void *value, UNI _size )
{
	memcpy( value, currentPosition_, _size );
	currentPosition_ += _size;
}

void TempBuffer::copyIn( const void *value, UNI _size )
{
	memcpy( currentPosition_, value, _size );
	currentPosition_ += _size;
}


TempBuffer& TempBuffer::operator << ( const D value )
{
	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( D& value )
{
	copyOut( &value, sizeof( value ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const F value )
{
	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( F& value )
{
	copyOut( &value, sizeof( value ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const NC value )
{
	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( NC& value )
{
	copyOut( &value, sizeof( value ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const L value )
{
	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( L& value )
{
	copyOut( &value, sizeof( value ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const S value )
{
	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( S& value )
{
	copyOut( &value, sizeof( value ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const CqlString& value )
{
	*this << value.length();
	copyIn( value.text(), value.length() );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( CqlString& value )
{
	UL tlength;
	*this >> tlength;
	if( tlength )
	{
		value.setString( currentPosition_, tlength - 1 );
		currentPosition_ += tlength;
	}
	return *this;
}


TempBuffer& TempBuffer::operator << ( const UC value )
{
	if( lengthState_ == ONE_BYTE_LENGTH )
	{
		streamCopyLength_ = static_cast< const UL >( value );
		if( copyState_ == DO_COPY )
			copyIn( &value, sizeof( value ) );
		lengthState_ = NO_LENGTH;
		return *this;
	}

	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( UC& value )
{
	if( lengthState_ == ONE_BYTE_LENGTH )
	{
		if( copyState_ == DO_COPY )
		{
			copyOut( &value, sizeof( value ) );
			UC uc = value;
			streamCopyLength_ = static_cast< UL >( uc );
		}
		lengthState_ = NO_LENGTH;
		return *this;
	}

	copyOut( &value, sizeof( value ) );
	return *this;
}


#ifndef CQL_BOOL_IS_INT

TempBuffer& TempBuffer::operator << ( const bool value )
{
	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( bool& value )
{
	copyOut( &value, sizeof( value ) );
	return *this;
}

#endif  //  ~CQL_BOOL_IS_INT


TempBuffer& TempBuffer::operator << ( const US value )
{
	copyIn( &value, sizeof( value ) );

	return *this;
}

TempBuffer& TempBuffer::operator >> ( US& value )
{
	copyOut( &value, sizeof( value ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const NI value )
{
	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( NI& value )
{
	copyOut( &value, sizeof( value ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const UNI value )
{
	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( UNI& value )
{
	copyOut( &value, sizeof( value ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const UL value )
{
	if( lengthState_ == FOUR_BYTE_LENGTH )
	{
		streamCopyLength_ = value;
		if( copyState_ == DO_COPY )
			copyIn( &value, sizeof( value ) );
		return *this;
	}

	copyIn( &value, sizeof( value ) );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( UL& value )
{
	if( lengthState_ == FOUR_BYTE_LENGTH )
	{
		copyOut( &value, sizeof( value ) );
		streamCopyLength_ = value;
		return *this;
	}

	copyOut( &value, sizeof( value ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const void *data )
{
	if( data )
		copyIn( data, streamCopyLength_ );
	else
		currentPosition_ += streamCopyLength_;

	return *this;
}

TempBuffer& TempBuffer::operator >> ( void *data )
{
	if( data )
		copyOut( data, streamCopyLength_ );
	else
		currentPosition_ += streamCopyLength_;

	return *this;
}


TempBuffer& TempBuffer::operator << ( const UC *data )
{
	copyIn( data, streamCopyLength_);
	return *this;
}

TempBuffer& TempBuffer::operator >> ( UC *data )
{
	copyOut( data, streamCopyLength_);
	return *this;
}


TempBuffer& TempBuffer::operator << ( const BigintValue& bv )
{
	bv.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Bigint& bv )
{
	return *this << const_cast< Cql_Bigint& >( bv ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveBigint& bv )
{
	return *this << const_cast< PrimitiveBigint& >( bv ).value();
}


TempBuffer& TempBuffer::operator >> ( BigintValue& bv )
{
	bv.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Bigint& bv )
{
	return *this >> bv.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveBigint& bv )
{
	return *this >> bv.value();
}


TempBuffer& TempBuffer::operator << ( const BinaryValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( BinaryValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const BitValue& source )
{
	*this << source.pvalue();
	return *this;
}


TempBuffer& TempBuffer::operator << ( const PrimitiveBit& source )
{
	return *this << const_cast< PrimitiveBit& >( source ).value();
}


TempBuffer& TempBuffer::operator << ( const Cql_Bit& source )
{
	return *this << const_cast< Cql_Bit& >( source ).instance();
}


TempBuffer& TempBuffer::operator >> ( BitValue& dest )
{
	*this >> dest.rPvalue();
	return *this;
}


TempBuffer& TempBuffer::operator >> ( PrimitiveBit& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator >> ( Cql_Bit& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator << ( const CharValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Char& source )
{
	return *this << const_cast< Cql_Char& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveChar& source )
{
	return *this << const_cast< PrimitiveChar& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( CharValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Char& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveChar& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const CharUCValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_CharUC& source )
{
	return *this << const_cast< Cql_CharUC& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveCharUC& source )
{
	return *this << const_cast< PrimitiveCharUC& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( CharUCValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_CharUC& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveCharUC& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const DateValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Date& source )
{
	return *this << const_cast< Cql_Date& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveDate& source )
{
	return *this << const_cast< PrimitiveDate& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( DateValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Date& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveDate& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const DecimalValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Decimal& source )
{
	return *this << const_cast< Cql_Decimal& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveDecimal& source )
{
	return *this << const_cast< PrimitiveDecimal& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( DecimalValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Decimal& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveDecimal& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const FloatValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Float& source )
{
	return *this << const_cast< Cql_Float& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveFloat& source )
{
	return *this << const_cast< PrimitiveFloat& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( FloatValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Float& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveFloat& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const IntegerValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Integer& source )
{
	return *this << const_cast< Cql_Integer& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveInteger& source )
{
	return *this << const_cast< PrimitiveInteger& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( IntegerValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Integer& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveInteger& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const LongvarbinaryValue& source )
{
	source.output( *this );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( LongvarbinaryValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const LongvarcharValue& source )
{
	source.output( *this );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( LongvarcharValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const RealValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Real& source )
{
	return *this << const_cast< Cql_Real& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveReal& source )
{
	return *this << const_cast< PrimitiveReal& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( RealValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Real& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveReal& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const SmallintValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Smallint& source )
{
	return *this << const_cast< Cql_Smallint& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveSmallint& source )
{
	return *this << const_cast< PrimitiveSmallint& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( SmallintValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Smallint& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveSmallint& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const TimeValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Time& source )
{
	return *this << const_cast< Cql_Time& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveTime& source )
{
	return *this << const_cast< PrimitiveTime& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( TimeValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Time& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveTime& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const TimestampValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Timestamp& source )
{
	return *this << const_cast< Cql_Timestamp& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveTimestamp& source )
{
	return *this << const_cast< PrimitiveTimestamp& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( TimestampValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Timestamp& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveTimestamp& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const TinyintValue& source )
{
	source.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Cql_Tinyint& source )
{
	return *this << const_cast< Cql_Tinyint& >( source ).instance();
}


TempBuffer& TempBuffer::operator << ( const PrimitiveTinyint& source )
{
	return *this << const_cast< PrimitiveTinyint& >( source ).value();
}


TempBuffer& TempBuffer::operator >> ( TinyintValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Cql_Tinyint& dest )
{
	return *this >> dest.instance();
}


TempBuffer& TempBuffer::operator >> ( PrimitiveTinyint& dest )
{
	return *this >> dest.value();
}


TempBuffer& TempBuffer::operator << ( const VarbinaryValue& source )
{
	source.output( *this );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( VarbinaryValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const VarcharValue& source )
{
	source.output( *this );
	return *this;
}

TempBuffer& TempBuffer::operator >> ( VarcharValue& dest )
{
	dest.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const CqlColumnType cct )
{
	copyIn( &cct, sizeof( cct ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( CqlColumnType& cct )
{
	copyOut( &cct, sizeof( cct ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const AbstractValue *cav )
{
	bool valueExists;
	if( !cav )
	{
		valueExists = false;
		*this << valueExists;
		return *this;
	}

	//  This looks recursive, because this method is called by operator << for CqlColumnTypes.
	//  This instance of CqlColumnTypes will never have a default value, so when it is called
	//  recursively av will be 0.
	valueExists = true;
	AbstractValue *av = const_cast< AbstractValue* >( cav );
	*this << valueExists << av->columnType();
	av->output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( AbstractValue*& av )
{
	bool valueExists;
	*this >> valueExists;
	if( !valueExists )
		return *this;
	CqlColumnTypes ctype;
	*this >> ctype;
	av = AbstractValue::createObject( ctype );
	av->input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const CqlColumnTypes& type )
{
	*this << type.defaultValue() << type.notNull() << type.typeLength() << type.cTypeName() << type.typeType();
	return *this;
}


TempBuffer& TempBuffer::operator >> ( CqlColumnTypes& type )
{
	UL tlength;
	CqlColumnType ttype;
	AbstractValue *av;
	bool nn;
	*this >> av >> nn >> tlength >> type.typeName() >> ttype;
	type.defaultValue( av );
	type.typeLength( tlength );
	type.typeType( ttype );
	if( nn )
		type.setNotNull();
	else
		type.clearNotNull();
	return *this;
}


TempBuffer& TempBuffer::operator << ( const AbstractColumnDescriptor& ccd )
{
	AbstractColumnDescriptor& cd = const_cast< AbstractColumnDescriptor& >( ccd );
	*this << cd.columnType() << cd.columnNumber() << cd.descending();
	return *this;
}


TempBuffer& TempBuffer::operator >> ( CqlException& ex )
{
	ex.input( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const CqlException& ex )
{
	ex.output( *this );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const ExceptionCodes ecode )
{
	copyIn( &ecode, sizeof( ecode ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( ExceptionCodes &ecode )
{
	copyOut( &ecode, sizeof( ecode ) );
	return *this;
}


void TempBuffer::initializeCurrentPosition( void )
{
	currentPosition_ = buffer_ + sizeof( UL );
}


TempBuffer& TempBuffer::operator << ( const LengthStates ls )
{
	lengthState_ = ls;
	return *this;
}


TempBuffer& TempBuffer::operator << ( const CopyStates cs )
{
	copyState_ = cs;
	return *this;
}


TempBuffer& TempBuffer::operator << ( const SignValues sv )
{
	copyIn( &sv, sizeof( sv ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( SignValues& sv )
{
	copyOut( &sv, sizeof( sv ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const AbstractValueType avt )
{
	copyIn( &avt, sizeof( avt ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( AbstractValueType& avt )
{
	copyOut( &avt, sizeof( avt ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Functions fu )
{
	copyIn( &fu, sizeof( fu ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Functions& fu )
{
	copyOut( &fu, sizeof( fu ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const UnaryOperators uo )
{
	copyIn( &uo, sizeof( uo ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( UnaryOperators& uo )
{
	copyOut( &uo, sizeof( uo ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const BinaryOperators bo )
{
	copyIn( &bo, sizeof( bo ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( BinaryOperators& bo )
{
	copyOut( &bo, sizeof( bo ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const TertiaryOperators to )
{
	copyIn( &to, sizeof( to ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( TertiaryOperators& to )
{
	copyOut( &to, sizeof( to ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const OperationCodes oc )
{
	copyIn( &oc, sizeof( oc ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( OperationCodes& oc )
{
	copyOut( &oc, sizeof( oc ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const PredicateType pt )
{
	copyIn( &pt, sizeof( pt ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( PredicateType& pt )
{
	copyOut( &pt, sizeof( pt ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Resolutions res )
{
	copyIn( &res, sizeof( res ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Resolutions& res )
{
	copyOut( &res, sizeof( res ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const LinkTypes lt )
{
	copyIn( &lt, sizeof( lt ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( LinkTypes& lt )
{
	copyOut( &lt, sizeof( lt ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const Combinations comb )
{
	copyIn( &comb, sizeof( comb ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( Combinations& comb )
{
	copyOut( &comb, sizeof( comb ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const ComparisonOperators co )
{
	copyIn( &co, sizeof( co ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( ComparisonOperators& co )
{
	copyOut( &co, sizeof( co ) );
	return *this;
}


TempBuffer& TempBuffer::operator << ( const ComparisonModifiers cm )
{
	copyIn( &cm, sizeof( cm ) );
	return *this;
}


TempBuffer& TempBuffer::operator >> ( ComparisonModifiers& cm )
{
	copyOut( &cm, sizeof( cm ) );
	return *this;
}


CqlString TempBuffer::asString( void )
{
	CqlString tstr;
	NC lengthBuffer[ 30 ];
	UL length = *size_;

	sprintf( lengthBuffer, "%ld", length );
	tstr = "Size = ";
	tstr = tstr + lengthBuffer;
	tstr = tstr + ".";
	tstr = tstr + "\n";

	US charCounter;
	US loop;
	NC digitBuffer[ 100 ];
	NC last16buffer[ 16 ];
	UC *p;

	for( loop = charCounter = 0, p = buffer_ + sizeof( length ); loop < length; loop++, p++ )
	{
		if( charCounter == 8 )
			tstr = tstr + "  ";
		else if( charCounter == 16 )
		{
			tstr = tstr + "  ";
			UNI loop2;
			for( loop2 = 0; loop2 < 16; loop2++ )
			{
				if( loop2 == 8 )
					tstr = tstr + " ";

				if( isalpha( last16buffer[ loop2 ] ) )
					tstr = tstr + CqlString( last16buffer[ loop2 ] );
				else
					tstr = tstr + ".";
			}
			std::cout << std::endl;
			charCounter = 0;
		}

		sprintf( digitBuffer, "%02x", *p );
		while( strlen( digitBuffer ) > 2 )
		{
			memcpy( digitBuffer, digitBuffer + 1, strlen( digitBuffer ) );
			digitBuffer[ strlen( digitBuffer ) ] = 0;
		}

		tstr = tstr + digitBuffer;
		tstr = tstr + " ";
		charCounter++;
	}

	tstr = tstr + "\n";
	
	return tstr;
}
