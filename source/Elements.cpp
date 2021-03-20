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


#include "CqlSqlInclude.h"


AbstractValueElement::AbstractValueElement( CqlColumnTypes dt ) : dataType_( dt ) 
{
}


AbstractValueElement::~AbstractValueElement( void )
{
}


bool AbstractValueElement::isNumeric( void )
{
	switch( dataType_.typeType() )
	{
	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
	case CQL_BIT :
	case CQL_TIME :
	case CQL_DATE :
	case CQL_TIMESTAMP :
		return false;

	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_REAL :
	case CQL_FLOAT :
	case CQL_DECIMAL :
		break;

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return true;
}


bool AbstractValueElement::isFloat( void )
{
	switch( dataType_.typeType() )
	{
	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
	case CQL_BIT :
	case CQL_TIME :
	case CQL_DATE :
	case CQL_TIMESTAMP :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
		return false;

	case CQL_REAL :
	case CQL_FLOAT :
		break;

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return true;
	return CQL_SUCCESS;
}


AbstractValueElement *AbstractValueElement::createObject( const CqlColumnTypes at )
{
	pAbstractValueElement le = 0;

	switch( at.typeType() )
	{
	case CQL_CHAR :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
		le = new StringElement;
		break;

	case CQL_CHARUC :
		le = new StringUCElement;
		break;

	case CQL_BIT :
		le = new BitLiteralElement;
		break;

	case CQL_TINYINT :
		le = new TinyintLiteralElement;
		break;

	case CQL_SMALLINT :
		le = new SmallintLiteralElement;
		break;

	case CQL_INTEGER :
		le = new IntegerLiteralElement;
		break;

	case CQL_BIGINT :
		le = new BigintLiteralElement;
		break;

	case CQL_REAL :
		le = new RealLiteralElement;
		break;

	case CQL_FLOAT :
		le = new FloatLiteralElement;
		break;

	case CQL_DECIMAL :
		le = new DecimalLiteralElement;
		break;

	case CQL_TIMESTAMP :
		le = new TimestampLiteralElement;
		break;

	case CQL_DATE :
		le = new DateLiteralElement;
		break;

	case CQL_TIME :
		le = new TimeLiteralElement;
		break;

	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		le = new BinaryLiteralElement;
		break;

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	if( !le )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	return le;
}


US AbstractValueElement::abstractDictionaryLength( void )
{
	return sizeof( NI ) + sizeof( NI );
}


void AbstractValueElement::writeAbstractInformation( TempBuffer& buffer )
{
	AbstractValueType vtype = valueType();

	buffer << vtype;
	buffer << dataType_;
}


void AbstractValueElement::readAbstractInformation( TempBuffer& buffer )
{
	AbstractValueType vtype;
	buffer >> vtype;
	buffer >> dataType_;
}


AbstractValueElement *AbstractValueElement::convert( AbstractValueElement *oldElement, CqlColumnTypes type )
{
	AbstractValueElement *val = createObject( type );
	val->value() = oldElement->value();
#if 0
	pAbstractValueElement val;
	CqlString str;

	val = createObject( type );

	oldElement->encode( str );

	*val = str;
#endif

	delete oldElement;
	return val;
}


AbstractValueElement *AbstractValueElement::convert( CqlColumnTypes type )
{
	CqlString str;

	//
	//  this version of Convert does not destroy the old object
	//
	if( type.typeType() == dataType_.typeType() )
		return this;

	AbstractValueElement *val = createObject( type );
	val->value() = value();
#if 0

	encode( str );

	*val = str;
#endif

	return val;
}


AbstractValueElement *AbstractValueElement::createObject( const AbstractType& at )
{
	AbstractValueElement *el = createObject( const_cast< AbstractType& >( at ).columnType() );
	el->value() = at;
	return el;
}


void AbstractValueElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << dataType_;
}


void AbstractValueElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> dataType_;
}


UNI BigintLiteralElement::length( void )
{
	return sizeof( BigintValue );
}


bool BigintLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_BIGINT :
		return true;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
		break;

	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


BigintLiteralElement::BigintLiteralElement( void ) : NumericLiteralElement( CQL_BIGINT )
{
}


BigintLiteralElement::~BigintLiteralElement( void )
{
}


void BigintLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void BigintLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void BigintLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


BinaryLiteralElement::BinaryLiteralElement( void ) : LiteralElement( CQL_BINARY ), value_()
{
}


BinaryLiteralElement::~BinaryLiteralElement( void )
{
}


void BinaryLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	writeAbstractInformation( buffer );
	value_.writeDictionaryInformation( buffer );
}


void BinaryLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


bool BinaryLiteralElement::operator <= ( AbstractValueElement& el )
{
	BinaryLiteralElement& other = dynamic_cast< BinaryLiteralElement& >( el );
	return value_ <= other.value_;
}


bool BinaryLiteralElement::operator < ( AbstractValueElement& el )
{
	BinaryLiteralElement& other = dynamic_cast< BinaryLiteralElement& >( el );
	return value_ < other.value_;
}


bool BinaryLiteralElement::operator >= ( AbstractValueElement& el )
{
	BinaryLiteralElement& other = dynamic_cast< BinaryLiteralElement& >( el );
	return value_ >= other.value_;
}


bool BinaryLiteralElement::operator > ( AbstractValueElement& el )
{
	BinaryLiteralElement& other = dynamic_cast< BinaryLiteralElement& >( el );
	return value_ > other.value_;
}


UNI BinaryLiteralElement::length( void )
{
	return value_.length();
}


bool BinaryLiteralElement::operator ! ( void )
{
	if( value_.length() != 0 )
		return false;
	else
		return true;
}


bool BinaryLiteralElement::isNull( void )
{
	return value_.nullflag();
}


bool BinaryLiteralElement::operator == ( AbstractValueElement& el )
{
	BinaryLiteralElement& other = dynamic_cast< BinaryLiteralElement& >( el );
	return value_ == other.value_;
}


void BinaryLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	readAbstractInformation( buffer );
	value_.readDictionaryInformation( buffer );
}


bool BinaryLiteralElement::expressionCompatible( CqlColumnTypes )
{
	throw BinaryTypeUsedInExpressionException( __FILE__, __LINE__ );
	return false;
}


void BinaryLiteralElement::encode( CqlString& )
{
	throw BinaryTypeUsedInExpressionException( __FILE__, __LINE__ );
}


AbstractValueElement& BinaryLiteralElement::operator = ( const AbstractValueElement& caval )
{
	AbstractValueElement& aval = const_cast< AbstractValueElement& >( caval );
	switch( aval.dataType().typeType() )
	{
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		{
			BinaryLiteralElement& binaryEl = dynamic_cast< BinaryLiteralElement& >( aval );
			value_ = binaryEl.value_;
		}
		break;

	case CQL_BIGINT :
	case CQL_BIT :
	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_DATE :
	case CQL_DECIMAL :
	case CQL_FLOAT :
	case CQL_INTEGER :
	case CQL_LONGVARCHAR :
	case CQL_REAL :
	case CQL_SMALLINT :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_TINYINT :
	case CQL_VARCHAR :
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	value_.clearNullflag();
	return *this;
}


AbstractValueElement& BinaryLiteralElement::operator << ( class TempBuffer& buffer )
{
	buffer << value();
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& BinaryLiteralElement::operator >> ( class TempBuffer& buffer )
{
	buffer >> value();
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& BinaryLiteralElement::operator += ( AbstractValueElement& )
{
	throw BinaryTypeUsedInExpressionException( __FILE__, __LINE__ );
	return dynamic_cast< AbstractValueElement& >( *this );  // dumb compiler
}


AbstractValueElement& BinaryLiteralElement::operator -= ( AbstractValueElement& )
{
	throw BinaryTypeUsedInExpressionException( __FILE__, __LINE__ );
	return dynamic_cast< AbstractValueElement& >( *this );  // dumb compiler
}


AbstractValueElement& BinaryLiteralElement::operator *= ( AbstractValueElement& )
{
	throw BinaryTypeUsedInExpressionException( __FILE__, __LINE__ );
	return dynamic_cast< AbstractValueElement& >( *this );  // dumb compiler
}


AbstractValueElement& BinaryLiteralElement::operator /= ( AbstractValueElement& )
{
	throw BinaryTypeUsedInExpressionException( __FILE__, __LINE__ );
	return dynamic_cast< AbstractValueElement& >( *this );  // dumb compiler
}


bool BinaryLiteralElement::operator != ( AbstractValueElement& av )
{
	BinaryLiteralElement& other = dynamic_cast< BinaryLiteralElement& >( av );
	return value_ != other.value_;
}


AbstractValueElement& BinaryLiteralElement::operator = ( const AbstractType& at )
{
	value() = const_cast< AbstractType& >( at );
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& BinaryLiteralElement::operator = ( const NC *source )
{
	value_ = source;
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& BinaryLiteralElement::operator = ( const CqlString& source )
{
	value_ = Cql_Binary( reinterpret_cast< const UC* >( source.text() ), source.length() );
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& BinaryLiteralElement::operator = ( const UC *source )
{
	value_ = const_cast< UC* >( source );
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& BinaryLiteralElement::operator = ( const AbstractValue& av )
{
	value_.avalue() = av;
	return dynamic_cast< AbstractValueElement& >( *this );
}


UNI BitLiteralElement::length( void )
{
	return 1;
}


BitLiteralElement::BitLiteralElement( void ) : NumericLiteralElement( CQL_BIT )
{
}


BitLiteralElement::~BitLiteralElement( void )
{
}


bool BitLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_BIT :
		return true;
		break;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
		break;

	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


void BitLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void BitLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void BitLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


UNI DateLiteralElement::length( void )
{
	DateValue dv;
	return dv.length();
}


bool DateLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_DATE :
		return true;

	case CQL_TIME :
	case CQL_TIMESTAMP :
		break;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


DateLiteralElement::DateLiteralElement( void ) : NumericLiteralElement( CQL_DATE )
{
}


DateLiteralElement::~DateLiteralElement( void )
{
}


void DateLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void DateLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void DateLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


UNI DecimalLiteralElement::length( void )
{
	DecimalValue dv;
	return dv.length();
}


DecimalLiteralElement::DecimalLiteralElement( void ) : NumericLiteralElement( CQL_DECIMAL )
{
}


DecimalLiteralElement::~DecimalLiteralElement( void )
{
}


bool DecimalLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_DECIMAL :
		return true;
		break;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_REAL :
	case CQL_FLOAT :
		break;

	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


void DecimalLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void DecimalLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void DecimalLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


DoubleStringListElement::DoubleStringListElement( void ) : DoubleStringListElementListElement(), s2()
{
}


DoubleStringListElement::~DoubleStringListElement( void )
{
}


DoubleStringListElement& DoubleStringListElement::operator = ( const DoubleStringListElement& other )
{
	s1 = other.s1;
	s2 = other.s2;
	return *this;
}


US DoubleStringListElement::DictionaryLength( void )
{
	return static_cast< US >( s1.dictionaryLength() + s2.dictionaryLength() );
}


void DoubleStringListElement::writeDictionaryInformation( TempBuffer& buffer )
{
	s1.writeDictionaryInformation( buffer );
	s2.writeDictionaryInformation( buffer );
}


void DoubleStringListElement::readDictionaryInformation( TempBuffer& buffer )
{
	s1.readDictionaryInformation( buffer );
	s2.readDictionaryInformation( buffer );
}


UNI DynamicParameterElement::length( void )
{
	if( dynamicEl )
		return dynamicEl->length();
	else
		return 0;
}


DynamicParameterElement::DynamicParameterElement( void ) : AbstractValueElement( CQL_COLUMN_UNDEFINED_TYPE ), dynamicEl( 0 )
{
}


DynamicParameterElement::~DynamicParameterElement( void )
{
	if( dynamicEl )
	{
		delete dynamicEl;
		dynamicEl = ((pAbstractValueElement)0);
	}
}


void DynamicParameterElement::writeDictionaryInformation( TempBuffer& buffer )
{
	if( dynamicEl )
		dynamicEl->writeDictionaryInformation( buffer );
}


void DynamicParameterElement::readDictionaryInformation( TempBuffer& buffer )
{
	readDictionaryInformation( buffer );
}


AbstractType& DynamicParameterElement::value( void )
{
	return dynamicEl->value();
}


AbstractValueElement& DynamicParameterElement::operator << ( TempBuffer& buffer )
{
	buffer << dynamicEl->value();
	return *this;
}


AbstractValueElement& DynamicParameterElement::operator >> ( TempBuffer& buffer )
{
	buffer >> dynamicEl->value();
	return *this;
}


AbstractValueElement& DynamicParameterElement::operator += ( AbstractValueElement& av )
{
	dynamicEl->value() += av.value();
	return *this;
}


AbstractValueElement& DynamicParameterElement::operator -= ( AbstractValueElement& av )
{
	dynamicEl->value() -= av.value();
	return *this;
}


AbstractValueElement& DynamicParameterElement::operator *= ( AbstractValueElement& av )
{
	dynamicEl->value() *= av.value();
	return *this;
}


AbstractValueElement& DynamicParameterElement::operator /= ( AbstractValueElement& av )
{
	dynamicEl->value() /= av.value();
	return *this;
}


bool DynamicParameterElement::operator < ( AbstractValueElement& av )
{
	return dynamicEl->value() < av.value();
}


bool DynamicParameterElement::operator <= ( AbstractValueElement& av )
{
	return dynamicEl->value() <= av.value();
}


bool DynamicParameterElement::operator > ( AbstractValueElement& av )
{
	return dynamicEl->value() > av.value();
}


bool DynamicParameterElement::operator >= ( AbstractValueElement& av )
{
	return dynamicEl->value() >= av.value();
}


bool DynamicParameterElement::operator == ( AbstractValueElement& av )
{
	return dynamicEl->value() == av.value();
}


bool DynamicParameterElement::operator != ( AbstractValueElement& av )
{
	return dynamicEl->value() != av.value();
}


bool DynamicParameterElement::operator ! ( void )
{
	return !dynamicEl->value();
}


AbstractValueElement& DynamicParameterElement::operator = ( const AbstractValueElement& av )
{
	dynamicEl->value() = const_cast< AbstractValueElement& >( av ).value();
	return *this;
}


AbstractValueElement& DynamicParameterElement::operator = ( const AbstractType& at )
{
	dynamicEl->value() = const_cast< AbstractType& >( at );
	return *this;
}


AbstractValueElement& DynamicParameterElement::operator = ( const AbstractValue& av )
{
	dynamicEl->value().avalue() = av;
	return *this;
}


AbstractValueElement& DynamicParameterElement::operator = ( const UC *source )
{
	dynamicEl->value() = const_cast< UC* >( source );
	return *this;
}


FILEListElement::FILEListElement( void ) : FILEListElementListElement()
{
}


FILEListElement::~FILEListElement( void )
{
}


UNI FloatLiteralElement::length( void )
{
	return sizeof( D );
}


FloatLiteralElement::FloatLiteralElement( void ) : NumericLiteralElement( CQL_FLOAT )
{
}


FloatLiteralElement::~FloatLiteralElement( void )
{
}


bool FloatLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_FLOAT :
		return true;
		break;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
		break;

	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


void FloatLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void FloatLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void FloatLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


IntegerLiteralElement::IntegerLiteralElement( void ) : NumericLiteralElement( CQL_INTEGER )
{
}


IntegerLiteralElement::~IntegerLiteralElement( void )
{
}


UNI IntegerLiteralElement::length( void )
{
	return sizeof( L );
}


bool IntegerLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_INTEGER :
		return true;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
		break;

	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


void IntegerLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void IntegerLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void IntegerLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


AbstractValueElement& IntegerLiteralElement::operator << ( TempBuffer& buffer )
{
	buffer << value_;
	return *this;
}


AbstractValueElement& IntegerLiteralElement::operator >> ( TempBuffer& buffer )
{
	buffer >> value_;
	return *this;
}


IntegerLiteralElement& IntegerLiteralElement::operator = ( const IntegerValue& source )
{
	value_ = source;
	return *this;
}


LiteralElement::LiteralElement( CqlColumnTypes t ) : AbstractValueElement( t )
{
}


LiteralElement::~LiteralElement( void )
{
}


UNI NullLiteralElement::length( void )
{
	return 1;
}


NullLiteralElement::NullLiteralElement( void ) : AbstractValueElement( CQL_COLUMN_UNDEFINED_TYPE )
{
}


NullLiteralElement::~NullLiteralElement( void )
{
}


void NullLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::writeDictionaryInformation( buffer );
}


void NullLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::readDictionaryInformation( buffer );
}


AbstractType& NullLiteralElement::value( void )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	//  This is, for the moment, just filler
	return *AbstractType::createObject( CqlColumnTypes( CQL_INTEGER ) );
}


AbstractValueElement& NullLiteralElement::operator << ( TempBuffer& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator >> ( TempBuffer& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator += ( AbstractValueElement& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator -= ( AbstractValueElement& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator *= ( AbstractValueElement& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator /= ( AbstractValueElement& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


bool NullLiteralElement::operator == ( AbstractValueElement& )
{
	return false;
}


bool NullLiteralElement::operator != ( AbstractValueElement& )
{
	return false;
}


bool NullLiteralElement::operator > ( AbstractValueElement& )
{
	return false;
}


bool NullLiteralElement::operator >= ( AbstractValueElement& )
{
	return false;
}


bool NullLiteralElement::operator < ( AbstractValueElement& )
{
	return false;
}


bool NullLiteralElement::operator <= ( AbstractValueElement& )
{
	return false;
}


bool NullLiteralElement::operator !( void )
{
	return false;
}


AbstractValueElement& NullLiteralElement::operator = ( const AbstractValueElement& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator = ( const AbstractType& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator = ( const AbstractValue& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator = ( const NC* )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator = ( const UC* )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& NullLiteralElement::operator = ( const CqlString& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
	return *this;
}


bool NumericLiteralElement::isNull( void )
{
	return value().nullflag();
}


void NumericLiteralElement::setNullflag( void )
{
	value().setNullflag();
}


void NumericLiteralElement::encode( CqlString& output )
{
	value().encode( output );
}


NumericLiteralElement::NumericLiteralElement( CqlColumnTypes t ) : LiteralElement( t )
{
}


NumericLiteralElement::~NumericLiteralElement( void )
{
}


bool NumericLiteralElement::operator ! ( void )
{
	return !value();
}


bool NumericLiteralElement::operator == ( AbstractValueElement& el )
{
	NumericLiteralElement& other = dynamic_cast< NumericLiteralElement& >( el );
	return value() == other.value();
}


bool NumericLiteralElement::operator <= ( AbstractValueElement& el )
{
	NumericLiteralElement& other = dynamic_cast< NumericLiteralElement& >( el );
	return value() <= other.value();
}


bool NumericLiteralElement::operator >= ( AbstractValueElement& el )
{
	NumericLiteralElement& other = dynamic_cast< NumericLiteralElement& >( el );
	return value() >= other.value();
}


bool NumericLiteralElement::operator < ( AbstractValueElement& el )
{
	NumericLiteralElement& other = dynamic_cast< NumericLiteralElement& >( el );
	return value() < other.value();
}


bool NumericLiteralElement::operator > ( AbstractValueElement& el )
{
	NumericLiteralElement& other = dynamic_cast< NumericLiteralElement& >( el );
	return value() > other.value();
}


US NumericLiteralElement::dictionaryLength( void )
{
	US len;

	len = LiteralElement::dictionaryLength();

	len = ((US)( len + value().dictionaryLength() ) );

	return len;
}


AbstractValueElement& NumericLiteralElement::operator += ( AbstractValueElement& aother )
{
	NumericLiteralElement& other = dynamic_cast< NumericLiteralElement& >( aother );
	value() += other.value();
	return *this;
}


AbstractValueElement& NumericLiteralElement::operator -= ( AbstractValueElement& el )
{
	NumericLiteralElement& other = dynamic_cast< NumericLiteralElement& >( el );
	value() -= other.value();
	return *this;
}


AbstractValueElement& NumericLiteralElement::operator *= ( AbstractValueElement& el )
{
	NumericLiteralElement& other = dynamic_cast< NumericLiteralElement& >( el );
	value() *= other.value();
	return *this;
}


AbstractValueElement& NumericLiteralElement::operator /= ( AbstractValueElement& el )
{
	NumericLiteralElement& other = dynamic_cast< NumericLiteralElement& >( el );
	value() /= other.value();
	return *this;
}


void NumericLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::writeDictionaryInformation( buffer );
	value().writeDictionaryInformation( buffer );
}


void NumericLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::readDictionaryInformation( buffer );
	value().readDictionaryInformation( buffer );
}


AbstractValueElement& NumericLiteralElement::operator << ( TempBuffer& buffer )
{
	buffer << value();
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& NumericLiteralElement::operator >> ( TempBuffer& buffer )
{
	buffer >> value();
	return dynamic_cast< AbstractValueElement& >( *this );
}


bool NumericLiteralElement::operator != ( AbstractValueElement& av )
{
	return value() != av.value();
}


AbstractValueElement& NumericLiteralElement::operator = ( const AbstractValueElement& source )
{
	value() = const_cast< AbstractValueElement& >( source ).value();
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& NumericLiteralElement::operator = ( const UC *source )
{
	value() = const_cast< UC* >( source );
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& NumericLiteralElement::operator = ( const AbstractType& at )
{
	value() = const_cast< AbstractType& >( at );
	return dynamic_cast< AbstractValueElement& >( *this );
}


AbstractValueElement& NumericLiteralElement::operator = ( const AbstractValue& av )
{
	value().avalue() = av;
	return dynamic_cast< AbstractValueElement& >( *this );
}


ParserStackElement::ParserStackElement( void )
{
}


ParserStackElement::~ParserStackElement( void )
{
}


QueryStackElement::QueryStackElement( pSelectExpression s ) : QueryStackElementListElement(), selectExp( s )
{
}


QueryStackElement::~QueryStackElement( void )
{
}


UNI RealLiteralElement::length( void )
{
	return sizeof( F );
}


RealLiteralElement::RealLiteralElement( void ) : NumericLiteralElement( CQL_REAL )
{
}


RealLiteralElement::~RealLiteralElement( void )
{
}


bool RealLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_REAL :
		return true;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_FLOAT :
		break;

	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


void RealLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void RealLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void RealLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


UNI SmallintLiteralElement::length( void )
{
	return sizeof( S );
}


bool SmallintLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_SMALLINT :
		return true;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
		break;

	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


SmallintLiteralElement::SmallintLiteralElement( void ) : NumericLiteralElement( CQL_SMALLINT )
{
}


SmallintLiteralElement::~SmallintLiteralElement( void )
{
}


void SmallintLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void SmallintLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void SmallintLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


StringElement::StringElement(void) : LiteralElement(CQL_CHAR)
{
	concreteValue_ = new Cql_Char();
}


StringElement::~StringElement( void )
{
	if( concreteValue_ != 0 )
	{
		delete concreteValue_;
		concreteValue_ = 0;
	}
}


bool StringElement::operator == ( AbstractValueElement& el )
{
	StringElement& other = dynamic_cast< StringElement& >( el );
	return *concreteValue_ == *other.concreteValue_;
}


bool StringElement::operator <= ( AbstractValueElement& el )
{
	StringElement& other = dynamic_cast< StringElement& >( el );
	return *concreteValue_ <= *other.concreteValue_;
}


bool StringElement::operator >= ( AbstractValueElement& el )
{
	StringElement& other = dynamic_cast< StringElement& >( el );
	return *concreteValue_ >= *other.concreteValue_;
}


bool StringElement::operator < ( AbstractValueElement& el )
{
	StringElement& other = dynamic_cast< StringElement& >( el );
	return *concreteValue_ < *other.concreteValue_;
}
	

bool StringElement::operator > ( AbstractValueElement& el )
{
	StringElement& other = dynamic_cast< StringElement& >( el );
	return *concreteValue_ > *other.concreteValue_;
}


UNI StringElement::length( void )
{
	return concreteValue_->length();
}


bool StringElement::isNull( void )
{
	return concreteValue_->nullflag();
}


void StringElement::encode( CqlString& output )
{
	output = concreteValue_->instance().value().value();
}


void StringElement::setup( pNC txt )
{
	*concreteValue_ = txt;
}


US StringElement::dictionaryLength( void )
{
	return static_cast< US >( concreteValue_->dictionaryLength() + LiteralElement::dictionaryLength() );
}


void StringElement::writeDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::writeDictionaryInformation( buffer );
	concreteValue_->writeDictionaryInformation( buffer );
}


void StringElement::readDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::readDictionaryInformation( buffer );
	concreteValue_->readDictionaryInformation( buffer );
}


bool StringElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
		return true;

	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
		break;

	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


AbstractValueElement& StringElement::operator << ( TempBuffer& buffer )
{
	buffer << *concreteValue_;
	return *this;
}


AbstractValueElement& StringElement::operator >> ( TempBuffer& buffer )
{
	buffer >> *concreteValue_;
	return *this;
}


AbstractValueElement& StringElement::operator += ( AbstractValueElement& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& StringElement::operator -= ( AbstractValueElement& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& StringElement::operator *= ( AbstractValueElement& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& StringElement::operator /= ( AbstractValueElement& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
	return *this;
}


bool StringElement::operator != ( AbstractValueElement& ave )
{
	return *concreteValue_ != ave.value();
}


bool StringElement::operator ! ( void )
{
	return !(*concreteValue_);
}


AbstractValueElement& StringElement::operator = ( const AbstractValueElement& other )
{
	*concreteValue_ = const_cast< AbstractValueElement& >( other ).value();
	return *this;
}


AbstractValueElement& StringElement::operator = ( const AbstractType& at )
{
	*concreteValue_ = const_cast< AbstractType& >( at );
	return *this;
}


AbstractValueElement& StringElement::operator = ( const AbstractValue& av )
{
	concreteValue_->avalue() = av;
	return *this;
}


AbstractValueElement& StringElement::operator = ( const NC *source )
{
	*concreteValue_ = source;
	return *this;
}


StringUCElement::StringUCElement(void) : LiteralElement(CQL_CHARUC)
{
	concreteValue_ = new Cql_CharUC();
}


StringUCElement::~StringUCElement( void )
{
	if( concreteValue_ != 0 )
	{
		delete concreteValue_;
		concreteValue_ = 0;
	}
}


Cql_Char *StringUCElement::charValue(AbstractValueElement& el)
{
	if( typeid(el) == typeid(StringUCElement) )
	{
		StringUCElement& suce  = dynamic_cast<StringUCElement&>(el);
		return dynamic_cast<Cql_Char*>(suce.concreteValue_);
	}
	else if( typeid(el) == typeid(StringElement) )
	{
		StringElement& se = dynamic_cast<StringElement&>(el);
		return se.concreteValue();
	}
	else
		throw InternalErrorException(__FILE__, __LINE__);
}


bool StringUCElement::operator == ( AbstractValueElement& el )
{
	return *concreteValue_ == *charValue(el);
}


bool StringUCElement::operator <= ( AbstractValueElement& el )
{
	return *concreteValue_ <= *charValue(el);
}


bool StringUCElement::operator >= ( AbstractValueElement& el )
{
	return *concreteValue_ >= *charValue(el);
}


bool StringUCElement::operator < ( AbstractValueElement& el )
{
	return *concreteValue_ < *charValue(el);
}
	

bool StringUCElement::operator > ( AbstractValueElement& el )
{
	return *concreteValue_ > *charValue(el);
}


UNI StringUCElement::length( void )
{
	return concreteValue_->length();
}


bool StringUCElement::isNull( void )
{
	return concreteValue_->nullflag();
}


void StringUCElement::encode( CqlString& output )
{
	output = concreteValue_->instance().value().value();
}


void StringUCElement::setup( pNC txt )
{
	*concreteValue_ = txt;
}


US StringUCElement::dictionaryLength( void )
{
	return static_cast< US >( concreteValue_->dictionaryLength() + LiteralElement::dictionaryLength() );
}


void StringUCElement::writeDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::writeDictionaryInformation( buffer );
	concreteValue_->writeDictionaryInformation( buffer );
}


void StringUCElement::readDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::readDictionaryInformation( buffer );
	concreteValue_->readDictionaryInformation( buffer );
}


bool StringUCElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
		return true;

	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
		break;

	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


AbstractValueElement& StringUCElement::operator << ( TempBuffer& buffer )
{
	buffer << *concreteValue_;
	return *this;
}


AbstractValueElement& StringUCElement::operator >> ( TempBuffer& buffer )
{
	buffer >> *concreteValue_;
	return *this;
}


AbstractValueElement& StringUCElement::operator += ( AbstractValueElement& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& StringUCElement::operator -= ( AbstractValueElement& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& StringUCElement::operator *= ( AbstractValueElement& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
	return *this;
}


AbstractValueElement& StringUCElement::operator /= ( AbstractValueElement& )
{
	throw NumericOperationOnCharacterDataException( __FILE__, __LINE__ );
	return *this;
}


bool StringUCElement::operator != ( AbstractValueElement& ave )
{
	return *concreteValue_ != ave.value();
}


bool StringUCElement::operator ! ( void )
{
	return !(*concreteValue_);
}


AbstractValueElement& StringUCElement::operator = ( const AbstractValueElement& other )
{
	*concreteValue_ = const_cast< AbstractValueElement& >( other ).value();
	return *this;
}


AbstractValueElement& StringUCElement::operator = ( const AbstractType& at )
{
	*concreteValue_ = const_cast< AbstractType& >( at );
	return *this;
}


AbstractValueElement& StringUCElement::operator = ( const AbstractValue& av )
{
	concreteValue_->avalue() = av;
	return *this;
}


AbstractValueElement& StringUCElement::operator = ( const NC *source )
{
	*concreteValue_ = source;
	return *this;
}


StringListElement::StringListElement( void ) : StringListElementBase(), s_()
{
}


StringListElement::~StringListElement( void )
{
	s_.reset();
}


void StringListElement::Assign( StringListElement& other )
{
	s_ = other.s_;
}


US StringListElement::dictionaryLength( void )
{
	return s_.dictionaryLength();
}


void StringListElement::writeDictionaryInformation( TempBuffer& buffer )
{
	s_.writeDictionaryInformation( buffer );
}


void StringListElement::readDictionaryInformation( TempBuffer& buffer )
{
	s_.readDictionaryInformation( buffer );
}


SubqueryElement::SubqueryElement( void )
	: AbstractValueElement( CQL_COLUMN_UNDEFINED_TYPE ),
	  correlationFlag_( false ),
	  selectExpression_( 0 ),
	  setNumber_( 0 ),
	  value_( 0 ),
	  valueRetrieved_( false )
{
}


SubqueryElement::SubqueryElement( pSelectExpression sel )
	: AbstractValueElement( CQL_COLUMN_UNDEFINED_TYPE ),
	  correlationFlag_( false ),
	  selectExpression_( sel ),
	  setNumber_( 0 ),
	  value_( 0 ),
	  valueRetrieved_( false )
{
}


SubqueryElement::~SubqueryElement( void )
{
}


AbstractValueElement *SubqueryElement::getAndPushSingleSubqueryValue( void )
{
	pAbstractTable subqueryResultSet = selectExpression_->temporaryFile().ifile();
	CqlColumnTypes subqueryType;
	bool nFlag;

	subqueryResultSet->getColumnInfo( 0, subqueryType, nFlag );

	subqueryResultSet->beginIsamOperation( 0 );

	if( !subqueryResultSet->firstRow() )
		throw SubqueryMustReturnExactlyOneRowException( __FILE__, __LINE__ );

	value_ = subqueryResultSet->getColumnValue( 0 );

	//
	//  check that there is only one value
	//
	if( subqueryResultSet->nextRow() )
		throw SubqueryMustReturnExactlyOneRowException( __FILE__, __LINE__ );

	AbstractValueElement *resultVal = AbstractValueElement::createObject( *value_ );
	return resultVal;
}


void SubqueryElement::getValue( void )
{
	value_ = selectExpression_->temporaryFile().ifile()->getColumnValue( 0 );
	valueRetrieved_ = true;
}


UNI SubqueryElement::length( void )
{
	if( !valueRetrieved_ )
		getValue();

	return value_->columnType().typeLength();
}


void SubqueryElement::readDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::readDictionaryInformation( buffer );
	buffer >> setNumber_;
}


void SubqueryElement::writeDictionaryInformation( TempBuffer& buffer )
{
	AbstractValueElement::writeDictionaryInformation( buffer );
	buffer << setNumber_;
}


bool SubqueryElement::isNull( void )
{
	return value_->nullflag();
}


AbstractValueElement& SubqueryElement::operator << ( TempBuffer& buffer )
{
	buffer << *value_;
	return *this;
}


AbstractValueElement& SubqueryElement::operator >> ( TempBuffer& buffer )
{
	buffer >> *value_;
	return *this;
}


AbstractValueElement& SubqueryElement::operator += ( AbstractValueElement& ave )
{
	*value_ += ave.value();
	return *this;
}


AbstractValueElement& SubqueryElement::operator -= ( AbstractValueElement& ave )
{
	*value_ -= ave.value();
	return *this;
}


AbstractValueElement& SubqueryElement::operator *= ( AbstractValueElement& ave )
{
	*value_ *= ave.value();
	return *this;
}


AbstractValueElement& SubqueryElement::operator /= ( AbstractValueElement& ave )
{
	*value_ /= ave.value();
	return *this;
}


bool SubqueryElement::operator == ( AbstractValueElement& ave )
{
	return *value_ == ave.value();
}


bool SubqueryElement::operator != ( AbstractValueElement& ave )
{
	return *value_ != ave.value();
}


bool SubqueryElement::operator > ( AbstractValueElement& ave )
{
	return *value_ > ave.value();
}


bool SubqueryElement::operator >= ( AbstractValueElement& ave )
{
	return *value_ >= ave.value();
}


bool SubqueryElement::operator < ( AbstractValueElement& ave )
{
	return *value_ < ave.value();
}


bool SubqueryElement::operator <= ( AbstractValueElement& ave )
{
	return *value_ <= ave.value();
}


bool SubqueryElement::operator ! ( void )
{
	return !( *value_ );
}


AbstractValueElement& SubqueryElement::operator = ( const AbstractValueElement& ave )
{
	*value_ = const_cast< AbstractValueElement& >( ave ).value();
	return *this;
}


AbstractValueElement& SubqueryElement::operator = ( const AbstractType& at )
{
	*value_ = const_cast< AbstractType& >( at );
	return *this;
}


AbstractValueElement& SubqueryElement::operator = ( const AbstractValue& av )
{
	value_->avalue() = av;
	return *this;
}


TableTableElement::TableTableElement( SqlHandle& sqlh )
	: TableTableElementListElement(),
	  cartesianProductCount_( 0 ),
	  correlated_( false ),
	  correlationName_(),
	  dbsql_( sqlh ),
	  linkFlag_( false ),
	  processed_( false ),
	  setNumber_( 0 ),
	  tableNumber_( 0 ),
	  valid_( false )
{
}


TableTableElement::~TableTableElement( void )
{
}


TableTableElement *TableTableElement::createUsingDictionary( SqlHandle& sqlh, TripleStringListElement& tsl )
{
	pAbstractTableSpecification ats;
	pTable table;
	pView view;

	hAEnv->logPrintf(AbstractLogger::TRACEALL, "createUsingDictionary..., " );
	if( tsl.s1().length() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "s1=%s, ", tsl.s1().text() );
	if( tsl.s2().length() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "s2=%s, ", tsl.s2().text() );
	hAEnv->logPrintf(AbstractLogger::TRACEALL, "end of names...\n\n" );

	ats = sqlh.getDictionaryRecord( tsl.s1(), tsl.s2() );
	if( !ats )
		return 0;

	TableTableElement *ttel;

	if( ats->isView() )
	{
		view = new View( sqlh, ats );
		if( !view )
		{
			delete ats;
			throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		ttel = view;
	}
	else
	{
		table = new Table( sqlh, ats );
		if( !table )
		{
			delete ats;
			throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		ttel = table;
	}

	ttel->correlationName() = tsl.s3();
	return ttel;
}


TableTableElement *TableTableElement::createObject( SqlHandle& sqlh, bool isView, AbstractTableSpecification& aTable )
{
	TableTableElement *ttel;
	if( isView )
		ttel = new View( sqlh, &aTable );
	else
		ttel = new Table( sqlh, &aTable );

	if( !ttel )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	return ttel;
}


TableTableElement& TableTableElement::operator = ( const TableTableElement& other )
{
	processed_ = other.processed_;
	linkFlag_ = other.linkFlag_;
	cartesianProductCount_ = other.cartesianProductCount_;
	return *this;
}


void TableTableElement::rereadCurrentRow( void )
{
	throw NotImplementedException( __FILE__, __LINE__ );
}


void TableTableElement::update( void )
{
	throw NotImplementedException( __FILE__, __LINE__ );
}


void TableTableElement::processView( void )
{
	viewSpec()->ProcessView( &dbsql_ );
}


void TableTableElement::clearConditions( void )
{
	absTableSpec()->clearConditions();
}


TimeLiteralElement::TimeLiteralElement( void ) : NumericLiteralElement( CQL_TIME )
{
}


TimeLiteralElement::~TimeLiteralElement( void )
{
}


UNI TimeLiteralElement::length( void )
{
	return sizeof( TimeValue );
}


bool TimeLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_TIME :
		return true;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
	case CQL_DATE :
	case CQL_TIMESTAMP :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;  // dumb compiler
}


void TimeLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void TimeLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void TimeLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


TimestampLiteralElement::TimestampLiteralElement( void ) : NumericLiteralElement( CQL_TIMESTAMP )
{
}


TimestampLiteralElement::~TimestampLiteralElement( void )
{
}


UNI TimestampLiteralElement::length( void )
{
	return sizeof( TimestampValue );
}


bool TimestampLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_TIMESTAMP :
		return true;

	case CQL_DATE :
	case CQL_TIME :
		break;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_TINYINT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


void TimestampLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void TimestampLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void TimestampLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


TinyintLiteralElement::TinyintLiteralElement( void ) : NumericLiteralElement( CQL_TINYINT )
{
}


TinyintLiteralElement::~TinyintLiteralElement( void )
{
}


UNI TinyintLiteralElement::length( void )
{
	return sizeof( SC );
}


bool TinyintLiteralElement::expressionCompatible( CqlColumnTypes type )
{
	switch( type.typeType() )
	{
	case CQL_TINYINT :
		return true;

	case CQL_CHAR :
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
	case CQL_BIT :
	case CQL_SMALLINT :
	case CQL_INTEGER :
	case CQL_BIGINT :
	case CQL_DECIMAL :
	case CQL_REAL :
	case CQL_FLOAT :
		break;

	case CQL_DATE :
	case CQL_TIME :
	case CQL_TIMESTAMP :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


void TinyintLiteralElement::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << value_;
}


void TinyintLiteralElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> value_;
}


void TinyintLiteralElement::setNullflag( void )
{
	value_.setNullflag();
}


AbstractValueElement& TinyintLiteralElement::operator << ( TempBuffer& buffer )
{
	buffer << value_;
	return *this;
}


AbstractValueElement& TinyintLiteralElement::operator >> ( TempBuffer& buffer )
{
	buffer >> value_;
	return *this;
}


TripleStringListElement::TripleStringListElement( void ) : s1_(), s2_(), s3_()
{
}


TripleStringListElement::~TripleStringListElement( void )
{
}


TripleStringListElement& TripleStringListElement::operator = ( const TripleStringListElement& other )
{
	s1_ = other.s1_;
	s2_ = other.s2_;
	s3_ = other.s3_;
	return *this;
}


US TripleStringListElement::DictionaryLength( void )
{
	return static_cast< US >( s1_.dictionaryLength() + s2_.dictionaryLength() + s3_.dictionaryLength() );
}


void TripleStringListElement::writeDictionaryInformation( TempBuffer& buffer )
{
	s1_.writeDictionaryInformation( buffer );
	s2_.writeDictionaryInformation( buffer );
	s3_.writeDictionaryInformation( buffer );
}


void TripleStringListElement::readDictionaryInformation( TempBuffer& buffer )
{
	s1_.readDictionaryInformation( buffer );
	s2_.readDictionaryInformation( buffer );
	s3_.readDictionaryInformation( buffer );
}


ValueExpressionStackElement::ValueExpressionStackElement( void ) : nullFlag_( false ), value_( 0 )
{
}


ValueExpressionStackElement::~ValueExpressionStackElement( void )
{
}


void ValueExpressionStackElement::resetValue( void )
{
	if( value_ )
	{
		delete value_;
		value_ = 0;
	}
}


ValueExpressionStackElement& ValueExpressionStackElement::operator = ( const ValueExpressionStackElement& other )
{
	if( other.value_ )
	{
		value_ = AbstractValueElement::createObject( other.value_->dataType() );
		*value_ = *other.value_;
	}
	else
		value_ = 0;

	nullFlag_ = other.nullFlag_;

	return *this;
}
