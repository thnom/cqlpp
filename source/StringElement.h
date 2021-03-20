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


#ifndef __StringElement_h
#define __StringElement_h


class StringElement : public LiteralElement
{
	Cql_Char *concreteValue_;

public :

	StringElement( void );
	~StringElement( void );

	AbstractValueElement& operator = ( const AbstractValueElement& );
	AbstractValueElement& operator = ( const AbstractType& );
	AbstractValueElement& operator = ( const AbstractValue& );
	AbstractValueElement& operator = ( const NC* );
	AbstractValueElement& operator = ( const CqlString& );
	AbstractValueElement& operator = ( const UC* );

	bool operator == ( AbstractValueElement& );
	bool operator != ( AbstractValueElement& );
	bool operator ! ( void );
	bool operator >= ( AbstractValueElement& );
	bool operator > ( AbstractValueElement& );
	bool operator < ( AbstractValueElement& );
	bool operator <= ( AbstractValueElement& );

	AbstractValueElement& operator *= ( AbstractValueElement& );
	AbstractValueElement& operator /= ( AbstractValueElement& );
	AbstractValueElement& operator += ( AbstractValueElement& );
	AbstractValueElement& operator -= ( AbstractValueElement& );

	AbstractValueElement& operator >> ( TempBuffer& );
	AbstractValueElement& operator << ( TempBuffer& );

	void clearNullflag( void ) { concreteValue_->clearNullflag(); }
	Cql_Char *concreteValue(void) { return concreteValue_; }
	US dictionaryLength( void );
	void encode( CqlString& /*output*/ );
	bool expressionCompatible( CqlColumnTypes );
	bool isNull( void );
	UNI length( void );
	bool& nullflag( void ) { return concreteValue_->nullflag(); }
	void readDictionaryInformation( TempBuffer& );
	void setNullflag( void ) { concreteValue_->setNullflag(); }
	void setup( pNC );
	CqlString& str( void ) { return const_cast< CqlString& >( concreteValue_->instance().value().value() ); }
	AbstractType& value( void ) { return dynamic_cast< AbstractType& >( *concreteValue_ ); }
	void writeDictionaryInformation( TempBuffer& );
};

typedef StringElement *pStringElement;


#endif  //  __StringElement_h
