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


#ifndef __CqlMachine_h
#define __CqlMachine_h


#define __CQL_LINUX


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#if __GNUC__ > 2
#define __CQL_NEW_C_PLUS_PLUS_HEADERS
#else
#undef __CQL_NEW_C_PLUS_PLUS_HEADERS
#endif


#if defined( __CQL_NEW_C_PLUS_PLUS_HEADERS )
#include <ostream>
#include <fstream>
#include <iostream>
#include <sstream>
#else  // !__CQL_NEW_C_PLUS_PLUS_HEADERS
#include <ostream.h>
#include <fstream.h>
#include <iostream.h>
#endif // !__CQL_NEW_C_PLUS_PLUS_HEADERS

#include <string.h>
#include <time.h>
#include <limits.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <assert.h>
#include <ctype.h>

#ifndef _ERRNO_H
#include <errno.h>
#endif

typedef unsigned char UC, *pUC;
typedef char SC, *pSC;
typedef char NC, *pNC;

typedef short S, *pS;
typedef unsigned short US, *pUS;

typedef int NI, *pNI;
typedef unsigned int UNI, *pUNI;

//  the bit field type
typedef unsigned int BFT;

typedef long L, *pL;
typedef unsigned long UL, *pUL;

typedef float F, *pF;
typedef double D, *pD;

typedef long RECID, *pRECID;

//
//  This type is not a pointer, it is an integer of the appropriate size
//  to hold the value of a pointer.
//
typedef long CQL_POINTER;

typedef NI SOCKET_TYPE;
typedef struct sockaddr_in SOCKET_ADDRESS_TYPE;
typedef struct servent *SERVICE_ENTRY_TYPE;

#define CQL_MACHINE_TYPE INTEL80X86
#define CQL_MAXIMUM_UNI UINT_MAX
#define CQL_MAXIMUM_UL ULONG_MAX
#define CQL_MAXIMUM_SC SCHAR_MAX
#define CQL_MINIMUM_SC SCHAR_MIN
#define CQL_MAXIMUM_S SHRT_MAX
#define CQL_MINIMUM_S SHRT_MIN
#define CQL_MAXIMUM_L LONG_MAX
#define CQL_MINIMUM_L LONG_MIN
#define CQL_MAXIMUM_F FLT_MAX
#define CQL_MINIMUM_F FLT_MIN
#define CQL_NI_IS_LONG

//  Connection oriented defines
#define CQL_LISTEN_BACKLOG 10

#ifdef __EXTERNAL_DEFINER__
#define CQL_GLOBAL /**/
#else
#define CQL_GLOBAL extern
#endif


//  Defines and type definitions for ODBC
typedef short RETCODE;
#define SQL_API /**/


#endif  //  __CqlMachine_h
