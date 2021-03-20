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


#ifndef __CqlDefines_h
#define __CqlDefines_h


#define CQL_YES 1
#define CQL_SUCCESS 1
#define CQL_NO ((NI)0)
#define CQL_FAILURE ((NI)0)
#define CQL_WAITING 2
#define CQL_NOT_FOUND 3
#define CQL_TRUNCATED 4
#define CQL_DUPLICATE_REJECTED 5
#define CQL_INTEGRITY_VIOLATION 6
#define CQL_CHECK_VIOLATION 7

#define CQL_LOG_NAME "cqllog"
#define CQL_LOG_FILE_NAME "cql.log"
#define CQL_VIRTUAL_FILE_NAME "cqlvirtual"
#define CQL_LOG_LOG_NAME "cqlCurrentLog"

#define CQL_CONFIG_ENVIRONMENT_VARIABLE_NAME "CQL_CONFIG_FILE"
#define CQL_CONFIG_FILE_NAME "cqlConfig"

#define CQL_LOGICAL_PAGE_SIZE ( CQL_PAGE_SIZE - sizeof( UL ) )

#define CQL_DOUBLE CQL_FLOAT
#define CQL_NUMERIC CQL_DECIMAL


#endif  //  __CqlDefines_h
