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


#ifndef __NumericLiteralElement_h
#define __NumericLiteralElement_h


class NumericLiteralElement : public LiteralElement
{

public :

	NumericLiteralElement( CqlColumnTypes );
	virtual ~NumericLiteralElement( void );

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

	NI allocateValue( void );
	US dictionaryLength( void );
	void encode( CqlString& output );
	bool isNull( void );
	void readDictionaryInformation( TempBuffer& );
	void setNullflag( void );
	void writeDictionaryInformation( TempBuffer& );
};

typedef NumericLiteralElement *pNumericLiteralElement;


#endif  //  __NumericLiteralElement_h
