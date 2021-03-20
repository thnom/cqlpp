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


void endTest( SqlHandle& /*dbsql*/, const char * const /*msg*/, bool /*skipCommit*/ = false );

extern char sno[ 6 ],
		sno2[ 6 ],
		sname[ 21 ],
		city[ 16 ],
		pno[ 7 ],
		pname[ 21 ],
		color[ 7 ],
		pcity[ 16 ],
		spsno[ 6 ],
		sppno[ 7 ],
		fAsCharBuf[ 20 ];

extern char *pSno,
		*pSno2,
		*pSname,
		*pCity,
		*pPno,
		*pPname,
		*pColor,
		*pPcity,
		*pSpsno,
		*pSppno,
		*pFAsCharBuf;

extern long status,
		weight,
		qty,
		long1,
		long2;

extern CqlString fAsString;

extern bool snoNull,
		sno2Null,
		snameNull,
		cityNull,
		pnoNull,
		pnameNull,
		colorNull,
		pcityNull,
		spsnoNull,
		sppnoNull,
		statusNull,
		weightNull,
		qtyNull,
		long1Null,
		long2Null,
		fAsCharBufNull,
		fAsStringNull;

extern unsigned long snoLength,
		sno2Length,
		snameLength,
		cityLength,
		pnoLength,
		pnameLength,
		colorLength,
		pcityLength,
		spsnoLength,
		sppnoLength,
		fAsCharBufLength;

class DataException : public CqlException
{
public :
	DataException( const char * const filename, const int linenumber )
		: CqlException( "Fetch failed when it shouldn't have, or didn't fail when it should have", EC_NO_DATA, filename, linenumber, 0 ) { }
	virtual ~DataException( void ) { }
};


class CompareFailedException : public CqlException
{
public :
	CompareFailedException( const char * const filename, const int linenumber )
		: CqlException( "Compare failed", EC_UNDEFINED, filename, linenumber, 0 ) { }
	virtual ~CompareFailedException( void ) { }
};
