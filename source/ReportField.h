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


#ifndef __ReportField_h
#define __ReportField_h


class ReportField;
typedef List< ReportField > ReportFieldList;
typedef ListElement< ReportField, ReportFieldList > ReportFieldListElement;


class ReportField : public ReportFieldListElement, public CqlConstants, public ErrorConstants
{
	pColumn col;
	UNI columnNumber;
	CqlString cqlTemplate;
	CqlString output;
	CqlString pattern;
	CqlColumnTypes type;
	UNI variableLength;

	BFT initialized : 1;
	BFT justify : 1;
	BFT noZero : 1;
	BFT skip : 1;
	BFT wrap : 1;

public :

	ReportField( void );
	~ReportField( void );

	NI Assign( SqlHandle*, ReportField& );
	UNI ColumnNumber( void ) { return columnNumber; }
	void generateOutput( void );
	CqlString& Output( void ) { return output; }
	void SetCol( pColumn c ) { col = c; }
	void SetColumn( UNI c ) { columnNumber = c; }
};

typedef ReportField *pReportField;


#endif  //  __ReportField_h
