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


void bigTest3( SqlHandle& dbsql )
{
	dbsql.executeImmediate( "UPDATE S SET STATUS=STATUS/2 WHERE CITY='London';" );

	Cursor *cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 60 passed", true );

	dbsql.commitTransaction();
	dbsql.executeImmediate( "UPDATE S SET SNO='S9' WHERE SNO='S2';" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S9" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 61 passed", true );

	dbsql.executeImmediate( "UPDATE S SET SNO='S8' WHERE SNO='S9';" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S8" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 62 passed", true );

	dbsql.commitTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S8" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 63 passed", true );

	dbsql.executeImmediate( "UPDATE S SET SNO='S2' WHERE SNO='S8';" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 64 passed", true );

	dbsql.commitTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 65 passed", true );

	bool duplicateDetected = false;
	try
	{
		dbsql.executeImmediate( "UPDATE S SET SNO='S2' WHERE SNO='S3';" );
	}
	catch( DuplicateRowException& )
	{
		duplicateDetected = true;
	}
	if( !duplicateDetected )
		throw DataException( __FILE__, __LINE__ );

	/* update which conflicts with inserted record */

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S6','XXX',35,'Reston');" );
	dbsql.executeImmediate( "INSERT INTO S VALUES ('S7','YYY',55,'Herndon');" );

	duplicateDetected = false;
	try
	{
		dbsql.executeImmediate( "INSERT INTO S VALUES ('S6','XXX',35,'Reston');" );
	}
	catch( DuplicateRowException& )
	{
		duplicateDetected = true;
	}
	if( !duplicateDetected )
		throw DataException( __FILE__, __LINE__ );

	duplicateDetected = false;
	try
	{
		dbsql.executeImmediate( "UPDATE S SET SNO='S7' WHERE SNO='S4';" );
	}
	catch( DuplicateRowException& )
	{
		duplicateDetected = true;
	}
	if( !duplicateDetected )
		throw DataException( __FILE__, __LINE__ );

	endTest( dbsql, "test 66 passed", true );

	dbsql.rollbackTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 67 passed" );

	cursor = dbsql.declareCursor( "SELECT PNO,PNAME,COLOR,WEIGHT,CITY FROM P WHERE CITY='London' OR COLOR = 'Red';" );
	cursor->open();
	cursor->bindColumn( 0, pPno, pnoLength, pnoNull, false );
	cursor->bindColumn( 1, pPname, pnameLength, pnameNull, false );
	cursor->bindColumn( 2, pColor, colorLength, colorNull, false );
	cursor->bindColumn( 3, weight, weightNull, false );
	cursor->bindColumn( 4, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P1" ) || strcmp( pname, "Nut" ) || strcmp( color, "Red" ) || weight != 12 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P4" ) || strcmp( pname, "Screw" ) || strcmp( color, "Red" ) || weight != 14 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P6" ) || strcmp( pname, "Cog" ) || strcmp( color, "Red" ) || weight != 19 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 68 passed" );

	cursor = dbsql.declareCursor( "SELECT AVG ( SP.QTY) FROM S,P,SP WHERE S.SNO=SP.SNO AND P.PNO=SP.PNO AND S.CITY='London';" );
	cursor->open();
	cursor->bindColumn( 0, qty, qtyNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( qty != 244 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 69 passed" );

	cursor = dbsql.declareCursor( "SELECT ALL S.SNO,S.CITY,P.PNO,P.CITY FROM S,P,SP WHERE S.SNO=SP.SNO AND P.PNO=SP.PNO ORDER BY P.PNO;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pCity, cityLength, cityNull, false );
	cursor->bindColumn( 2, pPno, pnoLength, pnoNull, false );
	cursor->bindColumn( 3, pPcity, pcityLength, pcityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( city, "London" ) || strcmp( pno, "P1" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( city, "Paris" ) || strcmp( pno, "P1" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( city, "London" ) || strcmp( pno, "P2" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( city, "Paris" ) || strcmp( pno, "P2" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( city, "Paris" ) || strcmp( pno, "P2" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( city, "London" ) || strcmp( pno, "P2" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( city, "London" ) || strcmp( pno, "P3" ) || strcmp( pcity, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( city, "London" ) || strcmp( pno, "P4" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( city, "London" ) || strcmp( pno, "P4" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( city, "London" ) || strcmp( pno, "P5" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( city, "London" ) || strcmp( pno, "P5" ) || strcmp( pcity, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( city, "London" ) || strcmp( pno, "P6" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 70 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM S WHERE STATUS >=10 ORDER BY STATUS;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || status != 10 || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || status != 30 || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || status != 30 || strcmp( city, "Athens" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 71 passed" );

	cursor = dbsql.declareCursor( "SELECT P.PNO, SUM(SP.QTY) FROM S,P,SP WHERE S.SNO=SP.SNO AND P.PNO=SP.PNO AND S.CITY='London' GROUP BY P.PNO HAVING SUM(SP.QTY)>100;" );
	cursor->open();
	cursor->bindColumn( 0, pPno, pnoLength, pnoNull, false );
	cursor->bindColumn( 1, qty, qtyNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P1" ) || qty != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P2" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P3" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P4" ) || qty != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P5" ) || qty != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 72 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM SP SPX WHERE SPX.QTY >= ( SELECT MAX(SPY.QTY) FROM SP SPY WHERE SPY.PNO = SPX.PNO);" );
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

	if( strcmp( spsno, "S1" ) || strcmp( sppno, "P3" ) || qty != 400 )
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

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S4" ) || strcmp( sppno, "P4" ) || qty != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S4" ) || strcmp( sppno, "P5" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 73 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM SP SPX WHERE SPX.QTY >= ( SELECT AVG(SPY.QTY) FROM SP SPY);" );
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

	if( strcmp( spsno, "S1" ) || strcmp( sppno, "P3" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S2" ) || strcmp( sppno, "P1" ) || qty != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S2" ) || strcmp( sppno, "P2" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S4" ) || strcmp( sppno, "P4" ) || qty != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S4" ) || strcmp( sppno, "P5" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 74 passed" );

	cursor = dbsql.declareCursor( "SELECT P.PNO, P.CITY FROM P WHERE P.CITY LIKE 'L%';" );
	cursor->open();
	cursor->bindColumn( 0, pPno, pnoLength, pnoNull, false );
	cursor->bindColumn( 1, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P1" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P4" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P6" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 75 passed" );

	cursor = dbsql.declareCursor( "SELECT P.PNO, P.CITY FROM P WHERE P.PNO LIKE 'P_';" );
	cursor->open();
	cursor->bindColumn( 0, pPno, pnoLength, pnoNull, false );
	cursor->bindColumn( 1, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P1" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P2" ) || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P3" ) || strcmp( city, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P4" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P5" ) || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P6" ) || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 76 passed" );

	cursor = dbsql.declareCursor( "SELECT P.PNO, P.CITY FROM P WHERE P.CITY NOT LIKE 'London';" );
	cursor->open();
	cursor->bindColumn( 0, pPno, pnoLength, pnoNull, false );
	cursor->bindColumn( 1, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P2" ) || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P3" ) || strcmp( city, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P5" ) || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 77 passed" );

	cursor = dbsql.declareCursor( "SELECT P.PNO, P.CITY FROM P WHERE NOT (P.CITY LIKE 'London');" );
	cursor->open();
	cursor->bindColumn( 0, pPno, pnoLength, pnoNull, false );
	cursor->bindColumn( 1, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P2" ) || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P3" ) || strcmp( city, "Rome" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P5" ) || strcmp( city, "Paris" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 78 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM SP WHERE QTY BETWEEN 200 AND 400;" );
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

	if( strcmp( spsno, "S2" ) || strcmp( sppno, "P1" ) || qty != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S2" ) || strcmp( sppno, "P2" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S3" ) || strcmp( sppno, "P2" ) || qty != 200 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S4" ) || strcmp( sppno, "P2" ) || qty != 200 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S4" ) || strcmp( sppno, "P4" ) || qty != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S4" ) || strcmp( sppno, "P5" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 79 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT SPX.SNO, S.SNAME FROM S,SP SPX WHERE S.SNO = SPX.SNO AND SPX.PNO NOT IN (SELECT SPY.PNO FROM SP SPY WHERE SPY.SNO = 'S2');" );
	cursor->open();
	cursor->bindColumn( 0, pSpsno, spsnoLength, spsnoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S1" ) || strcmp( sname, "Smith" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( spsno, "S4" ) || strcmp( sname, "Clark" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 80 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT PX.PNAME FROM P PX WHERE PX.WEIGHT >=ALL (SELECT DISTINCT PY.WEIGHT FROM P PY WHERE PY.COLOR = 'Blue');" );
	cursor->open();
	cursor->bindColumn( 0, pPname, pnameLength, pnameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pname, "Bolt" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pname, "Cog" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pname, "Screw" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 81 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT PX.PNAME FROM P PX WHERE PX.WEIGHT >ALL (SELECT DISTINCT PY.WEIGHT FROM P PY WHERE PY.COLOR = 'Blue');" );
	cursor->open();
	cursor->bindColumn( 0, pPname, pnameLength, pnameNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pname, "Cog" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 82 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT PX.PNAME FROM P PX WHERE PX.WEIGHT <ALL (SELECT DISTINCT PY.WEIGHT FROM P PY WHERE PY.COLOR = 'Blue');" );
	cursor->open();
	cursor->bindColumn( 0, pPname, pnameLength, pnameNull, false );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 83 passed" );

	dbsql.executeImmediate( "DELETE FROM S WHERE S.CITY = 'Athens';" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 84 passed", true );

	dbsql.commitTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 85 passed", true );

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S5', 'Adams', 30, 'Athens');" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 86 passed", true );

	dbsql.commitTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 87 passed", true );

	dbsql.executeImmediate( "DELETE FROM S WHERE S.CITY = 'Athens';" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 88 passed", true );

	dbsql.rollbackTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 89 passed", true );

	dbsql.executeImmediate( "DELETE FROM S WHERE S.STATUS = 20;" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

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

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 90 passed", true );

	dbsql.commitTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

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

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 91 passed", true );

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S1', 'Smith', 20, 'London');" );
	dbsql.executeImmediate( "INSERT INTO S VALUES ('S4', 'Clark', 20, 'London');" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 92 passed", true );

	dbsql.commitTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 93 passed", true );

	dbsql.executeImmediate( "DELETE FROM S WHERE S.STATUS = 20;" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

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

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 94 passed", true );

	dbsql.rollbackTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || strcmp( city, "London" ) || status != 20 )
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
	endTest( dbsql, "test 95 passed" );

	cursor = dbsql.declareCursor( "SELECT SNO,SNAME,STATUS FROM LS WHERE STATUS <> 10;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 96 passed" );

	bool columnNotFoundDetected = false;
	try
	{
		cursor = dbsql.declareCursor( "SELECT X1,X2 FROM LS2 WHERE STATUS <> 10;" );
	}
	catch( ColumnNotFoundException& )
	{
		columnNotFoundDetected = true;
	}
	if( !columnNotFoundDetected )
		throw DataException( __FILE__, __LINE__ );

	endTest( dbsql, "test 97 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM CITY_PAIRS WHERE SCITY = 'London';" );
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

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 98 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM CITY_PAIRS WHERE PCITY = 'London';" );
	cursor->open();
	cursor->bindColumn( 0, pCity, cityLength, cityNull, false );
	cursor->bindColumn( 1, pPcity, pcityLength, pcityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "London" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( city, "Paris" ) || strcmp( pcity, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 99 passed" );

	cursor = dbsql.declareCursor( "SELECT COUNT (SCITY) FROM CTP;" );
	cursor->open();
	cursor->bindColumn( 0, qty, qtyNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( qty != 12 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 100 passed" );

	cursor = dbsql.declareCursor( "SELECT COUNT (SCITY) FROM CITY_PAIRS;" );
	cursor->open();
	cursor->bindColumn( 0, qty, qtyNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( qty != 5 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 101 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM PQ WHERE PNO = 'P1';" );
	cursor->open();
	cursor->bindColumn( 0, pSppno, sppnoLength, sppnoNull, false );
	cursor->bindColumn( 1, weight, weightNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) || weight != 600 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 102 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM PQ;" );
	cursor->open();
	cursor->bindColumn( 0, pSppno, sppnoLength, sppnoNull, false );
	cursor->bindColumn( 1, weight, weightNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) || weight != 600 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) || weight != 1000 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P3" ) || weight != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P4" ) || weight != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) || weight != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P6" ) || weight != 100 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 103 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM PQ WHERE SUMQTY > 100 AND PNO <> 'P1';" );
	cursor->open();
	cursor->bindColumn( 0, pSppno, sppnoLength, sppnoNull, false );
	cursor->bindColumn( 1, weight, weightNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) || weight != 1000 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P3" ) || weight != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P4" ) || weight != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) || weight != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 104 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM PQ HAVING COUNT(*)>1;" );
	cursor->open();
	cursor->bindColumn( 0, pSppno, sppnoLength, sppnoNull, false );
	cursor->bindColumn( 1, weight, weightNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) || weight != 600 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) || weight != 1000 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P3" ) || weight != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P4" ) || weight != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) || weight != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P6" ) || weight != 100 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 105 passed" );
}
