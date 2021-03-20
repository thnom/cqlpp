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


#ifndef __AbstractValueElement_h
#define __AbstractValueElement_h


class AbstractValueElement : public ErrorConstants, public CqlConstants
{
	CqlColumnTypes dataType_;

public :

	AbstractValueElement( CqlColumnTypes );
	virtual ~AbstractValueElement( void );

	US abstractDictionaryLength( void );
	static AbstractValueElement *convert( AbstractValueElement *oldElement, CqlColumnTypes type );
	AbstractValueElement *convert( CqlColumnTypes type );
	static AbstractValueElement *createObject( const CqlColumnTypes );
	static AbstractValueElement *createObject( const AbstractType& );
	CqlColumnTypes dataType( void ) const { return dataType_; }
	void dataType( CqlColumnTypes t ) { dataType_ = t; }
	bool isFloat( void );
	bool isNumeric( void );
	void readAbstractInformation( TempBuffer& );
	void writeAbstractInformation( TempBuffer& );

	virtual bool correlationFlag( void ) { return false; }
	virtual void setCorrelationFlag( void ) { }

	virtual AbstractValueElement& operator = ( const AbstractValueElement& ) = 0;
	virtual AbstractValueElement& operator = ( const AbstractType& ) = 0;
	virtual AbstractValueElement& operator = ( const AbstractValue& ) = 0;

	virtual bool operator !( void ) = 0;
	virtual bool operator == ( AbstractValueElement& ) = 0;
	virtual bool operator != ( AbstractValueElement& ) = 0;
	virtual bool operator >= ( AbstractValueElement& ) = 0;
	virtual bool operator > ( AbstractValueElement& ) = 0;
	virtual bool operator <= ( AbstractValueElement& ) = 0;
	virtual bool operator < ( AbstractValueElement& ) = 0;

	virtual AbstractValueElement& operator += ( AbstractValueElement& ) = 0;
	virtual AbstractValueElement& operator -= ( AbstractValueElement& ) = 0;
	virtual AbstractValueElement& operator *= ( AbstractValueElement& ) = 0;
	virtual AbstractValueElement& operator /= ( AbstractValueElement& ) = 0;

	virtual AbstractValueElement& operator >> ( TempBuffer& ) = 0;
	virtual AbstractValueElement& operator << ( TempBuffer& ) = 0;

	virtual US dictionaryLength( void ) = 0;
	virtual void encode( CqlString& ) = 0;
	virtual bool expressionCompatible( CqlColumnTypes ) = 0;
	virtual bool isNull( void ) = 0;
	virtual UNI length( void ) = 0;
	virtual void readDictionaryInformation( TempBuffer& ) = 0;
	virtual AbstractType& value( void ) = 0;
	virtual AbstractValueType valueType( void ) = 0;
	virtual void writeDictionaryInformation( TempBuffer& ) = 0;
};

typedef AbstractValueElement *pAbstractValueElement;


#endif  //  __AbstractValueElement_h
