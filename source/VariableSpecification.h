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


#ifndef __VariableSpecification_h
#define __VariableSpecification_h


class VariableSpecification : public ErrorConstants
{
	void* data;
	BFT indicator : 1;
	UNI length;
	CqlString pattern;

public :

	enum HostType
	{
		HOST_TYPE_UNKNOWN,
		HOST_SHORT_INTEGER,
		HOST_LONG_INTEGER,
		HOST_FLOAT,
		HOST_DOUBLE,
		HOST_CHAR_ARRAY,
		HOST_CHAR,
		HOST_DATE,
		HOST_TIME,
		HOST_TIMESTAMP,
		HOST_BINARY,
		HOST_DECIMAL
	};

private :

	enum HostType type;

public :

	VariableSpecification( void );
	virtual ~VariableSpecification( void );

	void* Data( void ) { return data; }
	NI Indicator( void ) { return indicator; }
	UNI Length( void ) { return length; }
	CqlString& Pattern( void ) { return pattern; }
	void SetIndicator( void ) { indicator = CQL_YES; }
	void setup( void* d, HostType t, UNI len, pNC pat = ((pNC)0) );
	HostType Type( void ) { return type; }
};

typedef VariableSpecification *pVariableSpecification;


#endif  //  __VariableSpecification_h
