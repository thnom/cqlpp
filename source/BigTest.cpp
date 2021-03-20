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


//  Variables for result columns
char sno[ 6 ],
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

long status,
		weight,
		qty,
		long1,
		long2;

char *pSno,
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

CqlString fAsString;

bool snoNull,
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

unsigned long snoLength,
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

void bigTest1( SqlHandle& );
void bigTest2( SqlHandle& );
void bigTest3( SqlHandle& );
void bigTest4( SqlHandle& );
void bigTest5( SqlHandle& );
void bigTest6( SqlHandle& );


void endTest( SqlHandle& dbsql, const char * const msg, bool skipCommit = false )
{
	printf( "%s\n", msg );

	if( !skipCommit )
		dbsql.commitTransaction();
}


int main( int argc, char *argv[] )
{
	CqlString *user = 0;
	if( argc < 2 )
	{
		std::cerr << "BigTest {UserName} [InitialDataDirectory]" << std::endl;
		exit( 1 );
	}
	else
		user = new CqlString(argv[2]);

	CqlString *initialDirectory = 0;

	if( argc == 3 )
		initialDirectory = new CqlString(argv[2]);

	pSno = sno;
	snoLength = sizeof( sno );

	pSno2 = sno2;
	sno2Length = sizeof( sno2 );

	pSname = sname;
	snameLength = sizeof( sname );

	pCity = city;
	cityLength = sizeof( city );

	pPno = pno;
	pnoLength = sizeof( pno );

	pPname = pname;
	pnameLength = sizeof( pname );

	pColor = color;
	colorLength = sizeof( color );

	pPcity = pcity;
	pcityLength = sizeof( pcity );

	pSpsno = spsno;
	spsnoLength = sizeof( spsno );

	pSppno = sppno;
	sppnoLength = sizeof( sppno );

	pFAsCharBuf = fAsCharBuf;
	fAsCharBufLength = sizeof( fAsCharBuf );

	SqlHandle *dbsql;

	try
	{
		dbsql = new SqlHandle( user, 0, initialDirectory, 0, 0 );
	}
	catch( CqlException& ex )
	{
		std::cerr << ex;
		return -1;
	}

	dbsql->connect();

	try
	{
		bigTest1( *dbsql );
		bigTest2( *dbsql );
		bigTest3( *dbsql );
		bigTest4( *dbsql );
	}
	catch( CqlException& ex )
	{
		std::cout << "Error occurred:" << std::endl;
		std::cout << ex;
		return -1;
	}

	dbsql->disconnect();
	std::cout << "BigTest exiting..." << std::endl;
	delete dbsql;
	return( 0 );
}
