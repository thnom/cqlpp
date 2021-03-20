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


void bigTest2( SqlHandle& dbsql )
{
	Cursor *cursor = dbsql.declareCursor( "SELECT COUNT(*) FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, qty, qtyNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( qty != 5 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 30 passed" );

	cursor = dbsql.declareCursor( "SELECT COUNT(DISTINCT SNO) FROM SP;" );
	cursor->open();
	cursor->bindColumn( 0, qty, qtyNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( qty != 4 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 31 passed" );

	//  This SELECT is illegal because column QTY is not univalued for each PNO value
	try
	{
		cursor = dbsql.declareCursor( "SELECT PNO,QTY FROM SP GROUP BY PNO;" );
	}
	catch( GroupBySelectViolation& )
	{
		// The normal case.
		endTest( dbsql, "test 32 passed" );
	}
	//  Any other exception deliberately not caught here.

	cursor = dbsql.declareCursor( "SELECT PNO,SUM(QTY) FROM SP GROUP BY PNO;" );
	cursor->open();
	cursor->bindColumn( 0, pSppno, sppnoLength, sppnoNull, false );
	cursor->bindColumn( 1, qty, qtyNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) || qty != 600 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) || qty != 1000 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P3" ) || qty != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P4" ) || qty != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) || qty != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P6" ) || qty != 100 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 33 passed" );

	cursor = dbsql.declareCursor( "SELECT SP.PNO,MAX(SP.QTY),MIN(SP.QTY) FROM SP WHERE SP.SNO<>'S1' GROUP BY SP.PNO;" );
	cursor->open();
	cursor->bindColumn( 0, pSppno, sppnoLength, sppnoNull, false );
	cursor->bindColumn( 1, qty, qtyNull, false );
	cursor->bindColumn( 2, long1, long1Null, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P1" ) || qty != 300 || long1 != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P2" ) || qty != 400 || long1 != 200 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P4" ) || qty != 300 || long1 != 300 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) || qty != 400 || long1 != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 34 passed" );

	cursor = dbsql.declareCursor( "SELECT SP.PNO FROM SP GROUP BY PNO HAVING COUNT(*) > 1;" );
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

	if( strcmp( sppno, "P4" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sppno, "P5" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 35 passed" );

	cursor = dbsql.declareCursor( "SELECT SUM(STATUS),COUNT(STATUS),MIN(STATUS),MAX(STATUS),AVG(STATUS) FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, weight, weightNull, false );
	cursor->bindColumn( 1, qty, qtyNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, long1, long1Null, false );
	cursor->bindColumn( 4, long2, long2Null, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( weight != 110 || qty != 5 || status != 10 || long1 != 30 || long2 != 22 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 36 passed" );

	cursor = dbsql.declareCursor( "SELECT SNO FROM LS WHERE STATUS < 50;" );
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
	endTest( dbsql, "test 37 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM LS2;" );
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
	endTest( dbsql, "test 38 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM PQ;" );
	cursor->open();
	cursor->bindColumn( 0, pPno, pnoLength, pnoNull, false );
	cursor->bindColumn( 1, weight, weightNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P1" ) || weight != 600 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P2" ) || weight != 1000 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P3" ) || weight != 400 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P4" ) || weight != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P5" ) || weight != 500 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( pno, "P6" ) || weight != 100 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 39 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM CTP;" );
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
	endTest( dbsql, "test 40 passed" );

	cursor = dbsql.declareCursor( "SELECT DISTINCT * FROM CTP;" );
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
	endTest( dbsql, "test 41 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM CITY_PAIRS;" );
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
	endTest( dbsql, "test 42 passed" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 43 passed" );

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S6', 'XXX', 35, 'Reston' );" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 44 passed", true );

	cursor = dbsql.declareCursor( "SELECT DISTINCT STATUS FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, status, statusNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 45 passed", true );

	cursor = dbsql.declareCursor( "SELECT * FROM S WHERE SNO='S6';" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 46 passed", true );

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S7', 'YYY', 25, 'Herndon' );" );
	
	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S7" ) || strcmp( sname, "YYY" ) || strcmp( city, "Herndon" ) || status != 25 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 47 passed", true );

	dbsql.executeImmediate( "DELETE FROM S WHERE SNO='S7';" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 48 passed", true );

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S7', 'YYY', 25, 'Herndon' );" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S7" ) || strcmp( sname, "YYY" ) || strcmp( city, "Herndon" ) || status != 25 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );

	dbsql.executeImmediate( "DELETE FROM S WHERE STATUS=25;" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 49 passed", true );

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S7', 'XXX', 25, 'Herndon' );" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S7" ) || strcmp( sname, "XXX" ) || strcmp( city, "Herndon" ) || status != 25 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );

	dbsql.executeImmediate( "DELETE FROM S WHERE SNAME='XXX';" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 50 passed", true );

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S6', 'XXX', 35, 'Reston' );" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 51 passed", true );

	dbsql.commitTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 52 passed", true );

	dbsql.executeImmediate( "DELETE FROM S WHERE SNO='S6';" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 53 passed", true );

	dbsql.commitTransaction();

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );

	bool duplicateDetected = false;
	try
	{
		dbsql.executeImmediate( "INSERT INTO S VALUES ('S3','XXX',55,'Denver')" );
	}
	catch( DuplicateRowException& )
	{
		duplicateDetected = true;
	}
	if( !duplicateDetected )
		throw DataException( __FILE__, __LINE__ );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 54 passed", true );

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S6','XXX',55,'Reston');" );

	cursor = dbsql.declareCursor( "SELECT * FROM S ORDER BY STATUS DESC;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 55 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	cursor->close();

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S7','YYY',35,'Herndon');" );

	//  reopen
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 55 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S7" ) || strcmp( sname, "YYY" ) || strcmp( city, "Herndon" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	cursor->close();

	duplicateDetected = false;
	try
	{
		dbsql.executeImmediate( "INSERT INTO S VALUES ('S6','ZZZ',65,'Denver');" );
	}
	catch( DuplicateRowException& )
	{
		duplicateDetected = true;
	}
	if( !duplicateDetected )
		throw DataException( __FILE__, __LINE__ );

	//  reopen
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 55 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S7" ) || strcmp( sname, "YYY" ) || strcmp( city, "Herndon" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	cursor->close();

	duplicateDetected = false;
	try
	{
		dbsql.executeImmediate( "INSERT INTO S VALUES ('S7','AAA',15,'Fairfax');" );
	}
	catch( DuplicateRowException& )
	{
		duplicateDetected = true;
	}
	if( !duplicateDetected )
		throw DataException( __FILE__, __LINE__ );

	// reopen
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S6" ) || strcmp( sname, "XXX" ) || strcmp( city, "Reston" ) || status != 55 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S7" ) || strcmp( sname, "YYY" ) || strcmp( city, "Herndon" ) || status != 35 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S3" ) || strcmp( sname, "Blake" ) || strcmp( city, "Paris" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 20 || strcmp( city, "London" ) )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 20 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S2" ) || strcmp( sname, "Jones" ) || strcmp( city, "Paris" ) || status != 10 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	dbsql.rollbackTransaction();
	endTest( dbsql, "test 55 passed", true );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
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
	endTest( dbsql, "test 56 passed", true );

	dbsql.executeImmediate( "UPDATE S SET SNO='S6' WHERE SNO='S3';" );
	dbsql.executeImmediate( "UPDATE S SET SNO='S7' WHERE SNO='S4';" );

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
		dbsql.executeImmediate( "INSERT INTO S VALUES ('S7','XXX',35,'Reston');" );
	}
	catch( DuplicateRowException& )
	{
		duplicateDetected = true;
	}
	if( !duplicateDetected )
		throw DataException( __FILE__, __LINE__ );

	dbsql.executeImmediate( "INSERT INTO S VALUES ('S3','XXX',35,'Reston');" );
	dbsql.executeImmediate( "INSERT INTO S VALUES ('S4','XXX',35,'Reston');" );

	/* make sure it still rejects genuine duplicate */

	duplicateDetected = false;
	try
	{
		dbsql.executeImmediate( "INSERT INTO S VALUES ('S2','XXX',35,'Reston');" );
	}
	catch( DuplicateRowException& )
	{
		duplicateDetected = true;
	}
	if( !duplicateDetected )
		throw DataException( __FILE__, __LINE__ );

	dbsql.rollbackTransaction();
	endTest( dbsql, "test 57 passed", true );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
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
	endTest( dbsql, "test 58 passed", true );

	dbsql.executeImmediate( "UPDATE S SET STATUS=2*STATUS WHERE CITY='London';" );

	cursor = dbsql.declareCursor( "SELECT * FROM S;" );
	cursor->open();
	cursor->bindColumn( 0, pSno, snoLength, snoNull, false );
	cursor->bindColumn( 1, pSname, snameLength, snameNull, false );
	cursor->bindColumn( 2, status, statusNull, false );
	cursor->bindColumn( 3, pCity, cityLength, cityNull, false );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S1" ) || strcmp( sname, "Smith" ) || status != 40 || strcmp( city, "London" ) )
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

	if( strcmp( sno, "S4" ) || strcmp( sname, "Clark" ) || strcmp( city, "London" ) || status != 40 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( !cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	if( strcmp( sno, "S5" ) || strcmp( sname, "Adams" ) || strcmp( city, "Athens" ) || status != 30 )
		throw CompareFailedException( __FILE__, __LINE__ );

	if( cursor->fetch() )
		throw DataException( __FILE__, __LINE__ );

	dbsql.close( cursor );
	endTest( dbsql, "test 59 passed", true );
}
