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


#ifndef __CqlString_h
#define __CqlString_h


class CqlString : public CqlConstants
{
	UL bufferLength_;
	UL length_;
	NC *text_;

public :

	CqlString( void );
	CqlString( const NC *input, const UL len );
	CqlString( const NC *input );
	CqlString( const CqlString& s );
	CqlString( UL );

	~CqlString( void );

	CqlString& operator = ( const NC * const );
	CqlString& operator = ( const CqlString& );

	//  changing arguments from pNC to const CqlString&
	bool operator != ( const CqlString& ) const;
	bool operator != ( const NC * ) const;
	bool operator == ( const CqlString& ) const;
	bool operator == ( const NC * ) const;
	bool operator ! ( void ) const;
	bool operator > ( const CqlString& ) const;
	bool operator >= ( const CqlString& ) const;
	bool operator < ( const CqlString& ) const;
	bool operator <= ( const CqlString& ) const;

	CqlString& operator += ( const CqlString& );

	operator pNC();

	NI areWildcards( void );
	void convertToUpperCase( void );
	//  see also toUpperCase()
	US dictionaryLength( void );
	NI fill( NC );
	static NC *findPatternSubstringWithoutMetacharacters( const CqlString& /*pattern*/ );
	UL length( void ) const;
	void output( std::ostream& str ) const;
	void readDictionaryInformation( TempBuffer& );
	CompareResult regularExpressionCompare( CqlString& s2, NC escapeCharacter = '\\' );
	static CompareResult regularExpressionCompare( const char * const /*dataString*/,
												   const char * const /*patternString*/,
												   NC /*escapeCharacter*/ = '\\' );
	void reset( void );
	NI reverse( void );
	void setString( const char * const, UL );
	void setString( pUC, UL );
	void setString( UL );
	//  try taking these out.  Follow normal assignment with convertToUpperCase
	void setStringUpper( const char * const );
	void setStringUpper( CqlString& );
	void spacePadding( void );
	CompareResult stringCompare( const CqlString& ) const;
	CompareResult stringCompareIgnoreCase(const CqlString&) const;
	CompareResult stringCompareCommaDelimitedList( pNC );
	bool stripCompare( const CqlString& ) const;
	void stripTrailingSpaces( void );
	const char * const text( void ) const;
	//  see also convertToUpperCase
	CqlString *toUpperCase(void) const;
	void writeDictionaryInformation( TempBuffer& );
};

typedef CqlString *pCqlString;

std::ostream& operator << ( std::ostream& ostr, const CqlString& str );

inline CqlString operator + ( const CqlString& s1, const CqlString& s2 )
{
	CqlString tstring = s1;
	tstring += s2;
	return tstring;
}


#endif  //  __CqlString_h
