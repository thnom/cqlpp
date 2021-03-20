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


#include "BigTest.h"


void bigTest1( SqlHandle& dbsql )
{
	Cursor *cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();

	ColumnMetadataList *cml = cursor->describe();
	UNI ncols = cml->size();
	std::cout << "describe() list has " << ncols << " members." << std::endl;
	ColumnMetadata *cm;
	for( cm = cml->first(); cm; cm = cml->next() )
	{
			std::cout << "name=" << cm->name()
								<< ", type=" << cm->columnType().cTypeName()
								<< ", length=" << cm->length()
								<< ", precision=" << cm->precision()
								<< std::endl;
	}
	delete cml;
	cml = 0;

	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 1 passed" );

	cursor = dbsql.declareCursor( "SELECT PNO FROM SP;" );
	cursor->open();

	cml = cursor->describe();
	ncols = cml->size();
	std::cout << "describe() list has " << ncols << " members." << std::endl;
	for( cm = cml->first(); cm; cm = cml->next() )
	{
			std::cout << "name=" << cm->name()
								<< ", type=" << cm->columnType().cTypeName()
								<< ", length=" << cm->length()
								<< ", precision=" << cm->precision()
								<< std::endl;
	}
	delete cml;
	cml = 0;

	cursor->bindColumn( 0, pSppno, sppnoLength, sppnoNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P3" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P4" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P4" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P6" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 2 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT PNO FROM SP;" );
	cursor->open();
	cursor->bindColumn( 0, pSppno, sppnoLength, sppnoNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P3" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P4" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P6" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 3 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT SNO FROM SP;" );
	cursor->open();
	cursor->bindColumn( 0, pSpsno, spsnoLength, spsnoNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S1" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S2" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S3" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch( ) )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S4" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 4 passed" );

	cursor = dbsql.declareCursor( "SELECT SNO FROM S WHERE CITY='Paris' AND STATUS > 20;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 5 passed" );

	cursor = dbsql.declareCursor( "SELECT SNO,STATUS FROM S WHERE CITY='Paris' ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, status, statusNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 6 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT PNO,CITY FROM SP,S WHERE SP.SNO = S.SNO;" );
	cursor->open();
	cursor->bindColumn( 0, pSppno, sppnoLength, sppnoNull, false );
	cursor->bindColumn( 1, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P3" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P4" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P6" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 7 passed" );

	cursor = dbsql.declareCursor( "SELECT T1.SNO,T2.SNO FROM S T1,S T2 WHERE T1.CITY=T2.CITY AND T1.SNO<T2.SNO;");
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSno2, sno2Length, sno2Null, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sno2, "S4" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sno2, "S3" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 8 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT SNAME FROM S,SP WHERE S.SNO=SP.SNO AND SP.PNO='P2';" );
	cursor->open();
	cursor->bindColumn( 0, pSname, snameLength, snameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Blake" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Clark" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Jones" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Smith" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 9 passed" );

	cursor = dbsql.declareCursor( "SELECT SNAME FROM S WHERE SNO = ANY (SELECT SNO FROM SP WHERE PNO='P2');");
	cursor->open();
	cursor->bindColumn( 0, pSname, snameLength, snameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Blake" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Clark" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Jones" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Smith" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 10 passed" );

	cursor = dbsql.declareCursor( "SELECT SNO FROM S WHERE STATUS < ANY (SELECT STATUS FROM S);" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 11 passed" );

	cursor = dbsql.declareCursor( "SELECT SNAME FROM S WHERE SNO IN (SELECT SNO FROM SP WHERE PNO='P2');" );
	cursor->open();
	cursor->bindColumn( 0, pSname, snameLength, snameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Blake" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Clark" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Jones" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Smith" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 12 passed" );

	cursor = dbsql.declareCursor( "SELECT SNAME FROM S WHERE SNO IN (SELECT SNO FROM SP WHERE PNO IN (SELECT PNO FROM P WHERE COLOR='Red'));" );
	cursor->open();
	cursor->bindColumn( 0, pSname, snameLength, snameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Clark" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Jones" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Smith" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 13 passed" );

	cursor = dbsql.declareCursor( "SELECT SNAME FROM S WHERE 'P2' IN (SELECT PNO FROM SP WHERE SNO=S.SNO);" );
	cursor->open();
	cursor->bindColumn( 0, pSname, snameLength, snameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Blake" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Clark" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Jones" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Smith" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 14 passed" );

	cursor = dbsql.declareCursor( "SELECT SNO FROM S WHERE CITY = (SELECT CITY FROM S WHERE SNO='S1');" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 15 passed" );

	cursor = dbsql.declareCursor( "SELECT SNAME FROM S WHERE EXISTS (SELECT * FROM SP WHERE SNO=S.SNO AND PNO='P2');" );
	cursor->open();
	cursor->bindColumn( 0, pSname, snameLength, snameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Blake" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Clark" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Jones" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Smith" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 16 passed" );

	cursor = dbsql.declareCursor( "SELECT SNAME FROM S WHERE NOT EXISTS (SELECT * FROM SP WHERE SNO=S.SNO AND PNO='P2');" );
	cursor->open();
	cursor->bindColumn( 0, pSname, snameLength, snameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Adams" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 17 passed" );

	cursor = dbsql.declareCursor( "SELECT SNAME FROM S WHERE NOT EXISTS (SELECT * FROM P WHERE NOT EXISTS (SELECT * FROM SP WHERE SNO=S.SNO AND PNO=P.PNO));" );
	cursor->open();
	cursor->bindColumn( 0, pSname, snameLength, snameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sname, "Smith" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 18 passed" );

	cursor = dbsql.declareCursor( "SELECT PNO,WEIGHT*454 FROM P;" );
	cursor->open();
	cursor->bindColumn( 0, pPno, pnoLength, pnoNull, false );
	cursor->bindColumn( 1, weight, weightNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P1" ) || weight != 5448 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P2" ) || weight != 7718 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P3" ) || weight != 7718 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P4" ) || weight != 6356 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P5" ) || weight != 5448 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P6" ) || weight != 8626 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 19 passed" );

	cursor = dbsql.declareCursor( "SELECT SNO,PNO,QTY FROM SP WHERE SNO='S1' OR SNO='S2' ORDER BY SNO,PNO,QTY;" );
	cursor->open();
	cursor->bindColumn( 0, pSpsno, spsnoLength, spsnoNull, false );
	cursor->bindColumn( 1, pSppno, sppnoLength, sppnoNull, false );
	cursor->bindColumn( 2, qty, qtyNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S1" ) || strcmp( sppno, "P1" ) || qty != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S1" ) || strcmp( sppno, "P2" ) || qty != 200 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S1" ) || strcmp( sppno, "P3" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S1" ) || strcmp( sppno, "P4" ) || qty != 200 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S1" ) || strcmp( sppno, "P5" ) || qty != 100 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S1" ) || strcmp( sppno, "P6" ) || qty != 100 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S2" ) || strcmp( sppno, "P1" ) || qty != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S2" ) || strcmp( sppno, "P2" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 20 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM S WHERE STATUS >= 20 ORDER BY SNO;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || status != 30 || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || status != 30 || strcmp( city, "Athens" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 21 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM S WHERE STATUS=20 ORDER BY SNO DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 22 passed" );

	cursor = dbsql.declareCursor( "SELECT S.CITY,P.CITY FROM S,SP,P WHERE S.SNO=SP.SNO AND SP.PNO=P.PNO;" );
	cursor->open();
	cursor->bindColumn( 0, pCity, cityLength, cityNull, false );
	cursor->bindColumn( 1, pPcity, pcityLength, pcityNull, false );

	//  use vpcity here, since it is available and the same size

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 23 passed" );

	cursor = dbsql.declareCursor( "SELECT S.CITY,P.CITY FROM S,P,SP WHERE S.SNO=SP.SNO AND SP.PNO=P.PNO;" );
	cursor->open();	
	cursor->bindColumn( 0, pCity, cityLength, cityNull, false );
	cursor->bindColumn( 1, pPcity, pcityLength, pcityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 24 passed" );

	cursor = dbsql.declareCursor( "SELECT S.CITY,P.CITY FROM SP,S,P WHERE S.SNO=SP.SNO AND SP.PNO=P.PNO;" );
	cursor->open();
	cursor->bindColumn( 0, pCity, cityLength, cityNull, false );
	cursor->bindColumn( 1, pPcity, pcityLength, pcityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 25 passed" );

	cursor = dbsql.declareCursor( "SELECT S.CITY,P.CITY FROM SP,P,S WHERE S.SNO=SP.SNO AND SP.PNO=P.PNO;" );
	cursor->open();
	cursor->bindColumn( 0, pCity, cityLength, cityNull, false );
	cursor->bindColumn( 1, pPcity, pcityLength, pcityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 26 passed" );

	cursor = dbsql.declareCursor( "SELECT S.CITY,P.CITY FROM P,S,SP WHERE S.SNO=SP.SNO AND SP.PNO=P.PNO ORDER BY S.CITY,P.CITY;" );
	cursor->open();
	cursor->bindColumn( 0, pCity, cityLength, cityNull, false );
	cursor->bindColumn( 1, pPcity, pcityLength, pcityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 27 passed" );

	cursor = dbsql.declareCursor( "SELECT S.CITY,P.CITY FROM P,SP,S WHERE S.SNO=SP.SNO AND SP.PNO=P.PNO ORDER BY S.CITY,P.CITY;" );
	cursor->open();
	cursor->bindColumn( 0, pCity, cityLength, cityNull, false );
	cursor->bindColumn( 1, pPcity, pcityLength, pcityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 28 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT S.CITY,P.CITY FROM S,SP,P WHERE S.SNO=SP.SNO AND SP.PNO=P.PNO;" );
	cursor->open();
	cursor->bindColumn( 0, pCity, cityLength, cityNull, false );
	cursor->bindColumn( 1, pPcity, pcityLength, pcityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 29 passed" );
}
