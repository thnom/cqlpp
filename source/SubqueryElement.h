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


#ifndef __SubqueryElement_h
#define __SubqueryElement_h


class SubqueryElement : public AbstractValueElement
{
	bool correlationFlag_;
	SelectExpression *selectExpression_;
	US setNumber_;
	AbstractType *value_;
	bool valueRetrieved_;

	void getValue( void );

public :

	SubqueryElement( void );
	SubqueryElement( SelectExpression* );
	~SubqueryElement( void );

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

	AbstractValueElement& operator << ( TempBuffer& );
	AbstractValueElement& operator >> ( TempBuffer& );

	void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack );
	bool correlationFlag( void ) { return correlationFlag_; }
	US dictionaryLength( void ) { return abstractDictionaryLength(); }
	void encode( CqlString& ) { throw InternalErrorException( __FILE__, __LINE__ ); }

	bool expressionCompatible( CqlColumnTypes )
	{
		throw InternalErrorException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
		return false;
#endif
	}

	AbstractValueElement *getAndPushSingleSubqueryValue( void );
	bool isNull( void );
	UNI length( void );
	void readDictionaryInformation( TempBuffer& );
	SelectExpression *selectExpression( void ) { return selectExpression_; }
	void setCorrelationFlag( void ) { correlationFlag_ = true; }
	void setNullflag( void ) { throw InternalErrorException( __FILE__, __LINE__ ); }
	AbstractType& value( void ) { return *value_; }
	AbstractValueType valueType( void ) { return SUBQUERY_ELEMENT; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef SubqueryElement *pSubqueryElement;


#endif  //  __SubqueryElement_h
