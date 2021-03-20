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


#ifndef __CqlFixedLengthString_h
#define __CqlFixedLengthString_h


class CqlFixedLengthString : public CqlString
{
	UNI fixedLength_;

public :

	CqlFixedLengthString( UL );
	CqlFixedLengthString( CqlString& );
	~CqlFixedLengthString( void );

	CqlFixedLengthString& operator = ( const NC * );
	CqlFixedLengthString& operator=( const CqlString& );
	CqlFixedLengthString& operator = ( const CqlFixedLengthString& );

	CqlFixedLengthString& operator += ( const CqlString& );

	NI concatenate( pNC input );
	NI consumeUntil( pNC );
	void convertToUpperCase( void );
	UNI fixedLength( void ) { return fixedLength_; }
	void initialize( pNC input, UNI len );
	void initialize( UNI len );
	void padWithSpaces( void );
	CompareResult stringCompare( CqlFixedLengthString& );
	CompareResult stringCompare( pNC );
	NI stringCompareCommaDelimitedList( CompareResult*, pNC );
	NI stringCompareWithWildcards( CompareResult*, CqlFixedLengthString&, NC = '\\' );
	NI stringCompareWithWildcards( CompareResult*, pNC, NC = '\\' );
	NI stringCompareWithWildcardsThisPattern( CompareResult*, pNC, NC = '\\' );
	UNI stringLength( void ) { return strlen( text() ); }
	void stripTrailingSpaces( void );
};

typedef CqlFixedLengthString *pCqlFixedLengthString;


#endif  //  __CqlFixedLengthString_h
