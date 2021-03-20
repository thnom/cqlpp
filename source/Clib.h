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


#ifndef __Clib_h
#define __Clib_h


class Clib
{
public:

	static void cqlMemoryClear( void* /*obj*/, unsigned int /*obj size*/ );
	static char *sCurrentDirectory( void );

	void getCurrentTimestamp( S&, US&, US&, US&, US&, US&, UL& );
	NC convertCharToUppercase( NC );
	char *currentDirectory( void );
	static void getEnvironmentVariableValue( CqlString& /*result*/, const NC* /*variableName*/, const NC* /*defaultValue*/ );
	void cqlStrncpy( NC*, NC*, UNI );
};

typedef Clib *pClib;


D clibArcCosine( D );
D clibArcSin( D );
D clibArcTangent( D );
D clibCosine( D );
D clibTangent( D );
D clibExponential( D );
D clibLogorithm( D );
D clibSin( D );
D clibSquareRoot( D );


#endif  //  __Clib_h
