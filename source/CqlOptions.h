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


#ifndef __CqlOptions_h
#define __CqlOptions_h


#define CQL_MAXIMUM_BUFFER_PAGES 256
#define CQL_PAGE_SIZE 4096
#define CQL_MAXIMUM_FILE_NAME_LENGTH 64
#define CQL_MAXIMUM_TABLE_NAME_LENGTH 20
#define CQL_MAXIMUM_INDEX_NAME_LENGTH ( CQL_MAXIMUM_TABLE_NAME_LENGTH + 4 )
#define CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH 20
#define CQL_MAXIMUM_COLUMN_NAME_LENGTH 20
#define CQL_MAXIMUM_USER_NAME_LENGTH 20
#define CQL_NUMBER_OF_LOGS 4
#define CQL_LOG_FILE_SIZE 8388608
#define CQL_MAXIMUM_USERS 16
#define CQL_MACHINE_ID 1
#define CQL_DEFAULT_DATE_FORMAT "MMDDYY"
#define CQL_DEFAULT_DATE_SEPARATOR '/'
#define CQL_DEFAULT_TIME_SEPARATOR ':'
#define CQL_ONE_ANY '_'
#define CQL_MANY_ANY '%'

#define CQL_DEFAULT_SQL_SERVER_SERVICE_NAME "CQL"
#define CQL_DEFAULT_ISAM_SERVER_SERVICE_NAME "CQLISAM"


#endif  //  __CqlOptions_h
