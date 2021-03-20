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


#ifndef __Report_h
#define __Report_h


typedef bool (*UserReportFunction)( void* );

class Report : public OutputBuffer, public ErrorConstants
{
	UserReportFunction advance_;
	ReportWindowList bodies;
	ReportWindow continuation;
	UNI currentBody;
	UNI currentField;
	DateValue date_;
	CqlString datePattern;
	SqlHandle& dbsql_;
	UserReportFunction formFeed;
	ReportWindow header;
	UNI indent;
	CqlString initialization;
	CqlString lineBuffer;
	UNI outputLength;
	UserReportFunction pause;
	UNI rowsPerPage;
	UserReportFunction skipTest;
	ReportWindow subtotal;
	UserReportFunction subtotalTest;
	ReportWindowList termination;
	CqlString title;
	CqlString ttitle;
	void* userParameter;

	bool blockCalled;
	bool lines;
	bool ready;
	bool virgin;

	void GenerateTopOfPage( void );
	void generateWindow( ReportWindow& w, NI doubleSpace = CQL_NO );

public :

	Report( SqlHandle& );
	~Report( void );

	Report& operator = ( const Report& );

	ReportWindowList& Bodies( void ) { return bodies; }
	NI Cleanup( void );
	DateValue& date( void ) { return date_; }
	ReportWindow& Header( void ) { return header; }
	void horizontalCatchup( UNI );
	NI Initialize( SqlHandle* );
	NI Process( SqlHandle* );
	NI Run( SqlHandle* );
	void advance( UserReportFunction urf ) { advance_ = urf; }
	void SetUserParameter( void* up ) { userParameter = up; }
};

typedef Report *pReport;


#endif  //  __Report_h
