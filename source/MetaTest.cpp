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


int main( int argc, char *argv[] )
{
	if( argc != 2 )
		exit(-1);

	SqlHandle *dbsql = 0;

	try
	{
		SqlHandle *dbsql= new SqlHandle;
		dbsql->connect( argv[1] );
		TableIdList *tidl = dbsql->getTableIds( argv[1] );
		TableId *tid;
		for( tid = tidl->first(); tid; tid = tidl->next() )
		{
			std::cout << "table=" << tid->tableName() << std::endl;
		}

		std::cout << std::endl;

		for( tid = tidl->first(); tid; tid = tidl->next() )
		{
			ColumnMetadataList *cml = dbsql->getColumnMetadata( tid );
			ColumnMetadata *cm;
			std::cout << "table=" << tid->tableName() << std::endl;
			for( cm = cml->first(); cm; cm = cml->next() )
			{
				std::cout << "    column " << cm->name().text()
						  << ", type=" << cm->columnType().typeName()
						  << ", len=" << cm->length()
						  << ", precision=" << cm->precision()
						  << std::endl;
			}
			std::cout << std::endl;
		}
	}
	catch( CqlException& ex )
	{
		std::cout << "Error occurred:" << std::endl;
		std::cout << ex;
		return -1;
	}

	std::cout << "Done..." << std::endl;
	delete dbsql;
	return 0;
}
