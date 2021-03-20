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


#ifndef __CqlIsamGlobal_h
#define __CqlIsamGlobal_h


#ifdef __CQL_ISAM_EXTERNAL_DEFINER
NI btreeDebugging = 0;
NI btreePrinting = 0;
NI bufferDebugging = 0;
NI fileDebugging = 0;
CqlString nullCqlString( "" );
NI transactionCounterDebugging = 0;
NI transactionDebugging = 0;
NI transactionStartupDebugging = 0;
#else
CQL_GLOBAL NI btreeDebugging;
CQL_GLOBAL NI btreePrinting;
CQL_GLOBAL NI bufferDebugging;
CQL_GLOBAL NI fileDebugging;
CQL_GLOBAL CqlString nullCqlString;
CQL_GLOBAL NI transactionCounterDebugging;
CQL_GLOBAL NI transactionDebugging;
CQL_GLOBAL NI transactionStartupDebugging;
#endif  //  __CQL_ISAM_EXTERNAL_DEFINER


#endif  //  __CqlIsamGlobal_h
