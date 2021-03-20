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


CharUCValue::CharUCValue( const CharUCValue& other ) : CharValue( other )
{
}


CharUCValue::CharUCValue( const CqlColumnTypes& ctype ) : CharValue(ctype)
{
}


CharUCValue::CharUCValue( pUC& source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const NC *source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const CharValue& source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const CqlString& source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const NC source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const D source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const NI source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const UC *source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const UNI source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const US source ) : CharValue( source )
{
}


CharUCValue::CharUCValue( const UL source ) : CharValue( source )
{
}


CqlConstants::CompareResult CharUCValue::compare( const CharValue& cvOther ) const
{
	CharValue *cv = new CharValue(*value_.toUpperCase());
	return cv->compare(cvOther);
}


CqlConstants::CompareResult CharUCValue::compare( const CharUCValue& cvOther ) const
{
	CharValue *cv1 = new CharValue(*value_.toUpperCase());
	CharValue *cv2 = new CharValue(*cvOther.value_.toUpperCase());
	return cv1->compare(*cv2);
}


CharUCValue& CharUCValue::operator = ( const CharUCValue& other )
{
	value_ = other.value_;
	return *this;
}


AbstractValue& CharUCValue::operator = ( const AbstractValue& cav )
{
	AbstractValue& av = const_cast< AbstractValue& >( cav );

	switch( const_cast< AbstractValue& >( av ).columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_CHAR :
	{
		CharValue& cv = dynamic_cast< CharValue& >( av );
		value_ = cv.value();
	}
	break;

	case CQL_CHARUC :
	{
		//  for a test, to see if the cast exception is because the value is CharValue instead of CharUCValue
		//CharValue& cval = dynamic_cast<CharValue&>(av);
		//std::cout << "cast to CharValue occurred..." << &cval << std::endl;
		CharUCValue& cuv = dynamic_cast<CharUCValue&>(av);
		value_ = cuv.value_;
	}
	break;

	case CQL_VARCHAR :
	{
		VarcharValue& vv = dynamic_cast< VarcharValue& >( av );
		value_ = vv.buffer();
	}
	break;

	case CQL_LONGVARCHAR :
	{
		LongvarcharValue& lvv = dynamic_cast< LongvarcharValue& >( av );
		value_ = lvv.buffer();
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


bool CharUCValue::operator ! ( void ) const
{
	return CharValue::operator !();
}


CqlString *CharUCValue::otherString(const AbstractValue& other) const
{
	AbstractValue& avOther = const_cast<AbstractValue&>(other);
	if( typeid(avOther) == typeid(CharUCValue) )
		return dynamic_cast<CharUCValue&>(avOther).value_.toUpperCase();
	else if( typeid(avOther) == typeid(CharValue) )
		return dynamic_cast<CharValue&>(avOther).value().toUpperCase();
	else
		throw InternalErrorException(__FILE__, __LINE__);
}

bool CharUCValue::operator == ( const AbstractValue& other ) const
{
	return *value_.toUpperCase() == *otherString(other);
}

bool CharUCValue::operator != ( const AbstractValue& other ) const
{
	return *value_.toUpperCase() != *otherString(other);
}

bool CharUCValue::operator  > ( const AbstractValue& other ) const
{
	return *value_.toUpperCase() > *otherString(other);
}

bool CharUCValue::operator >= ( const AbstractValue& other ) const
{
	return *value_.toUpperCase() >= *otherString(other);
}

bool CharUCValue::operator < ( const AbstractValue& other ) const
{
	return *value_.toUpperCase() < *otherString(other);
}

bool CharUCValue::operator <= ( const AbstractValue& other ) const
{
	return *value_.toUpperCase() <= *otherString(other);
}

//AbstractValue& CharUCValue::operator += ( AbstractValue& other )
//{
//	return CharValue::operator += ( other );
//}
//
//
//AbstractValue& CharUCValue::operator -= ( AbstractValue& other )
//{
//	return CharValue::operator -= ( other );
//}
//
//
//AbstractValue& CharUCValue::operator *= ( AbstractValue& other )
//{
//	return CharValue::operator *= ( other );
//}
//
//
//AbstractValue& CharUCValue::operator /= ( AbstractValue& other )
//{
//	return CharValue::operator /= ( other );
//}
