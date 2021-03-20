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


#include "CqlCommonInclude.h"


CqlString::CqlString( void ) : bufferLength_( 0 ), length_( 0 ), text_( 0 )
{
}


CqlString::CqlString( const NC *input, const UL len )
{
	length_ = len + 1;
	bufferLength_ = length_;
	text_ = new NC[ bufferLength_ ];
	if( !text_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memset( text_, 0, bufferLength_ );

	if( input )
	{
		memcpy( text_, input, length_ - 1 );
		text_[ length_ - 1 ] = 0;
	}
	else
		memset( text_, 0, length_ );
}


CqlString::CqlString( const NC *input )
{
	if( !input )
		length_ = bufferLength_ = 1;
	else
	{
		length_ = strlen( input ) + 1;
		bufferLength_ = length_;
	}

	text_ = new NC[ length_ ];
	if( !text_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memset(text_, 0, length_);

	if( input )
		strcpy( text_, input );
	else
		text_[ 0 ] = 0;
}


CqlString::CqlString( const CqlString& s )
{
	if( s.length_ )
	{
		length_ = s.length_;
		bufferLength_ = length_;
		text_ = new NC[ length_ ];
		if( !text_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		memset( text_, 0, length_ );

		strcpy( text_, s.text_ );
	}
	else
	{
		text_ = 0;
		length_ = bufferLength_ = 0;
	}
}


CqlString::CqlString( UL len )
{
	length_ = bufferLength_ = len;
	text_ = new NC[ length_ ];
	if( !text_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memset( text_, 0, length_ );
}


CqlString::~CqlString( void )
{
	if( text_ )
	{
		delete [] text_;
		text_ = 0;
		length_ = bufferLength_ = 0;
	}
}


void CqlString::reset( void )
{
	if( text_ )
	{
		delete [] text_;
		text_ = 0;
		length_ = bufferLength_ = 0;
	}
}


void CqlString::setString( const char * const input, UL len )
{
	if( !len )
	{
		length_ = 0;
		return;
	}

	length_ = len + 1;
	if( bufferLength_ < length_  )
	{
		if( text_ )
			delete [] text_;

		bufferLength_ = length_;
		text_ = new NC[ length_ ];
		if( !text_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		memset( text_, 0, length_ );
	}

	if( input )
	{
		strncpy( text_, input, length_ - 1 );
		text_[ length_ - 1 ] = 0;
	}
	else
		text_[ 0 ] = 0;
}


void CqlString::setString( pUC input, UL len )
{
	setString( reinterpret_cast< NC* >( input ), len );
}


void CqlString::setStringUpper( const char * const input )
{
	UNI len, loop;

	if( !input )
		return;

	if( input )
		len = strlen( input ) + 1;
	else
		len = 1;

	if( bufferLength_ < len )
	{
		if( text_ )
			delete [] text_;

		length_ = bufferLength_ = len;
		text_ = new NC[ length_ ];
		if( !text_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		memset(text_, 0, length_);
	}
	else
		length_ = len;

	memset( text_, 0, length_ );

	if( input )
	{
		char *pIn = const_cast<char*>(input);
		char *pOut = const_cast<char*>(text_);
		for( loop = 0; loop < len; loop++, pIn++, pOut++ )
			*pOut = hAEnv->convertCharToUppercase( *pIn );
	}
}


void CqlString::convertToUpperCase( void )
{
	NC ucChar;
	pNC p;

	for( p = text_; *p; p++ )
	{
		ucChar = hAEnv->convertCharToUppercase( *p );
		*p = ucChar;
	}
}

CqlString *CqlString::toUpperCase() const
{
	CqlString *cstr = new CqlString(*this);
	cstr->convertToUpperCase();
	return cstr;
}

void CqlString::setStringUpper( CqlString& input )
{
	setStringUpper( input.text_ );
}


void CqlString::setString( UL len )
{
	if( bufferLength_ < len )
	{
		if( text_ )
			delete [] text_;

		length_ = len + 1;
		bufferLength_ = length_;
		text_ = new NC[ length_ ];
		if( !text_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		memset(text_, 0, length_);
	}
	else
		length_ = len;

	if( length_ )
		text_[ length_ - 1 ] = 0;
}


CqlConstants::CompareResult CqlString::stringCompare( const CqlString& other ) const
{
	CqlString s1 = *this;
	s1.stripTrailingSpaces();
	CqlString s2 = other;
	s2.stripTrailingSpaces();

	NI strcmpResult = strcmp( s1.text_, s2.text_ );
	if( strcmpResult < 0 )
		return THIS_LESS_THAN_OTHER;
	else if( strcmpResult > 0 )
		return THIS_GREATER_THAN_OTHER;
	else
		return THIS_EQUAL_TO_OTHER;
}


CqlConstants::CompareResult CqlString::stringCompareIgnoreCase(const CqlString& other) const
{
	return toUpperCase()->stringCompare(*other.toUpperCase());
}


bool CqlString::stripCompare( const CqlString& other ) const
{
	CqlString s1 = *this;
	s1.stripTrailingSpaces();
	CqlString s2 = other;
	s2.stripTrailingSpaces();
	return s1 == s2;
}


NI CqlString::reverse( void )
{
	pNC temporary, p1, p2;
	UNI loop;

	temporary = new NC[ length_ ];
	if( !temporary )
		return CQL_FAILURE;
	memset(text_, 0, length_);
	memcpy( temporary, text_, length_ );

	for( loop = 0, p1 = text_, p2 = temporary + (length_ - 2 ); loop < length_ - 1; loop++, p1++, p2-- )
		*p1 = *p2;

	return CQL_SUCCESS;
}


void CqlString::readDictionaryInformation( TempBuffer& buffer )
{
	buffer << FOUR_BYTE_LENGTH << DO_COPY;
	buffer >> length_;
	bufferLength_ = length_;

	if( length_ )
	{
		text_ = new NC[ length_ ];
		if( !text_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		memset(text_, 0, length_);
		buffer >> text_;
	}
}


void CqlString::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << FOUR_BYTE_LENGTH << DO_COPY << length_;
	if( length_ )
		buffer << text_;
}


CqlString& CqlString::operator = ( const NC *const input )
{
	length_ = strlen( input ) + 1;
	if( bufferLength_ < length_ )
	{
		bufferLength_ = length_;
		if( text_ )
			delete [] text_;
		text_ = new NC[ length_ ];
		if( !text_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		memset(text_, 0, length_);
	}

	strcpy( text_, input );
	return *this;
}


CqlString& CqlString::operator = ( const CqlString& other )
{
	if( !other.length_ )
	{
		length_ = 0;
		if( text_ )
			text_[ 0 ] = 0;
		return *this;
	}

	length_ = other.length_;
	if( bufferLength_ < length_ )
	{
		if( text_ )
			delete [] text_;
		bufferLength_ = length_;
		text_ = new NC[ bufferLength_ ];
		if( !text_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		memset(text_, 0, length_);
	}

	strcpy( text_, other.text_ );
	return *this;
}


bool CqlString::operator <= ( const CqlString& other ) const
{
	CompareResult result;

	result = stringCompare( other );

	switch( result )
	{
	case THIS_LESS_THAN_OTHER :
	case THIS_EQUAL_TO_OTHER :
		return true;

	case THIS_GREATER_THAN_OTHER :
		break;

	case COMPARE_RESULT_UNSET :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


bool CqlString::operator >= ( const CqlString& other ) const
{
	CompareResult result;

	result = stringCompare( other );

	switch( result )
	{
	case THIS_GREATER_THAN_OTHER :
	case THIS_EQUAL_TO_OTHER :
		return true;

	case THIS_LESS_THAN_OTHER :
		break;

	case COMPARE_RESULT_UNSET :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


bool CqlString::operator < ( const CqlString& other ) const
{
	CompareResult result;

	result = stringCompare( other );

	switch( result )
	{
	case THIS_LESS_THAN_OTHER :
		return true;

	case THIS_EQUAL_TO_OTHER :
	case THIS_GREATER_THAN_OTHER :
		break;

	case COMPARE_RESULT_UNSET :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


bool CqlString::operator > ( const CqlString& other ) const
{
	CompareResult result;

	result = stringCompare( other );

	switch( result )
	{
	case THIS_GREATER_THAN_OTHER :
		return true;

	case THIS_EQUAL_TO_OTHER :
	case THIS_LESS_THAN_OTHER :
		break;

	case COMPARE_RESULT_UNSET :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return false;
}


NI CqlString::fill( NC ch )
{
	memset( text_, ch, length_ - 1 );
	return CQL_SUCCESS;
}


CqlString& CqlString::operator += ( const CqlString& other )
{
	if( !text_ )
	{
		length_ = bufferLength_ = other.length_;
		text_ = new NC[ length_ ];
		if( !text_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		memset(text_, 0, length_);

		strcpy( text_, other.text_ );
		return *this;
	}

	//  both lengths have null byte, so subtract one (only one null byte for concatenated string)
	UL newLength = ( length_ + other.length_ - 1 );
	pNC newText = new NC[ newLength ];
	if( !newText )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memset(newText, 0, newLength);

	strcpy( newText, text_ );
	strcat( newText, other.text_ );
	if( bufferLength_ < newLength )
	{
		bufferLength_ = newLength;
		//  we don't get here unless text_ is != 0
		delete [] text_;
		text_ = newText;
	}
	else
	{
		strcpy( text_, newText );
		delete newText;
	}

	length_ = newLength;
	return *this;
}


void CqlString::stripTrailingSpaces( void )
{
	if( length() < 2 )
		return;

	char *p;
	for( p = const_cast<char*>(text_) + ( length() - 2 ); *p == ' ' && p >= text(); p-- )
		*p = 0;
}


void CqlFixedLengthString::stripTrailingSpaces( void )
{
	if( length() < 2 )
		return;

	char *p;
	for( p = const_cast<char*>(text()) + ( fixedLength_ - 2 ); *p == ' ' && p >= text(); p-- )
		*p = 0;
}


void CqlFixedLengthString::padWithSpaces( void )
{
	if( length() < 2 )
		return;

	NC *p;
	for( p = const_cast<char*>(text()) + (fixedLength_ - 2); *p == 0 && p >= text(); p-- )
		*p = ' ';
}
	


CqlFixedLengthString& CqlFixedLengthString::operator += ( const CqlString& cother )
{
	stripTrailingSpaces();
	CqlString other = cother;
	other.stripTrailingSpaces();
	UL totalLength = strlen( text() );

	if( other.text() )
		totalLength += strlen( other.text() );

	if( totalLength > fixedLength_ )
		throw LengthExceededException( __FILE__, __LINE__ );

	strcat( const_cast<char*>(text()), const_cast<char*>(other.text()) );
	//  actual length doesn't change for fixed length string
	return *this;
}


bool CqlString::operator != ( const CqlString& other ) const
{
	if( !text_ )
	{
		if( other.text_ )
			return true;
		else
			return false;
	}
	else if( !other.text_ )
		return false;

	CqlString s1 = *this;
	s1.stripTrailingSpaces();
	CqlString s2 = other;
	s2.stripTrailingSpaces();
	if( !strcmp( s1.text_, s2.text_ ) )
		return false;
	else
		return true;
}


bool CqlString::operator == ( const CqlString& other ) const
{
	if( !text_ )
	{
		if( !other.text_ )
			return true;
		else
			return false;
	}
	else if( !other.text_ )
		return false;

	CqlString s1 = *this;
	s1.stripTrailingSpaces();
	CqlString s2 = other;
	s2.stripTrailingSpaces();
	if( strcmp( s1.text_, s2.text_ ) )
		return false;
	else
		return true;
}

bool CqlString::operator == ( const NC* source ) const
{
	return *this == CqlString( source );
}


bool CqlString::operator != ( const NC* source ) const
{
	if( this == 0 )
		return false;
	else if( *this == CqlString( source ) )
		return false;
	else
		return true;
}


bool CqlString::operator ! ( void ) const
{
	if( text_ && text_[ 0 ] )
		return false;
	else
		return true;
}


void CqlString::spacePadding( void )
{
	pNC p;
	UNI loop;
	NI firstNonSpace;

	for( loop = 0, p = text_ + ( length_ - 2 ), firstNonSpace = CQL_NO; firstNonSpace == CQL_NO && loop < length_ - 1; loop++, p-- )
	{
		if( *p == 0 )
			*p = ' ';
		else
			firstNonSpace = CQL_YES;
	}
}


//
//  Regular expression parsing algorithm
//
// while( there are pattern characters remaining )
// {
// 	Find the next (which, the first time, is the first) patternSubstring without metacharacters;
// 	Form the dataSubstring of the corresponding length;
// 
// 	if( patternSubstring is the entire pattern )
// 		return normal compare;
// 	else
// 	{
// 		do normal compare on substrings;
// 		if compare fails
// 			return NOTEQUAL;
// 	}
// 	
// 	//  substring compare succeeded.
// 
// 	if( the meta character is the escape character )
// 	{
// 		consume the escape character;
// 		compare the next pattern character to the next data character;
// 		if they don't match
// 			return NOTEQUAL;
// 	}
// 	else if the meta character is the ONE_ANY (_) character
// 	{
// 		consume the ONE_ANY character in patternString;
// 		consume one character in dataString;
// 	}
// 	else
// 	{
// 		//  We have the MANY_ANY character, not escaped.
// 		Find the next patternSubstring without metacharacters;
// 		search the dataString for patternSubstring;
// 		if patternSubstring found in dataString
// 		{
// 			consume patternSubstring;
// 			consume data up to substring location;
// 		}
// 		else
// 			return NOTEQUAL;
// 	}
// }


static NC metacharacters[ 2 ];
static NI metacharactersSet = 0;

NC *CqlString::findPatternSubstringWithoutMetacharacters( const CqlString& pattern )
{
	const char * const patternString = pattern.text();

	if( !metacharactersSet )
	{
		//  copy the permanent (all except the escapeCharacter) meta characters to the metacharacters[] array
		metacharacters[ 0 ] = CQL_ONE_ANY;
		metacharacters[ 1 ] = CQL_MANY_ANY;
		metacharactersSet = 1;
	}

	pNC patternSubstring;

	//  If the leading character is a metacharacter, return 0.
	//  This step is necessary because strtok() ignores leading delimiter characters
	switch( *patternString )
	{
	case CQL_ONE_ANY :
	case CQL_MANY_ANY :
		return 0;

	default :
		break;
	}

	patternSubstring = strtok( const_cast<char*>(patternString), metacharacters );
	//  strtok uses a static buffer, so we need to allocate a buffer for the substring.
	//  The calling function is responsible for calling delete on the substring.
	NC *returnString = new NC[ strlen( patternSubstring ) + 1 ];
	if( !returnString )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memset(returnString, 0, strlen(patternSubstring) + 1);
	strcpy( returnString, patternSubstring );
	return returnString;
}


CqlConstants::CompareResult CqlString::regularExpressionCompare( CqlString& s2, NC escapeCharacter )
{
	return regularExpressionCompare( text_, s2.text(), escapeCharacter );
}


//
//  Note:  This method arbitrarily returns THIS_LESS_THAN_OTHER when the compare fails.
CqlConstants::CompareResult CqlString::regularExpressionCompare( const char * const cDataString,
																 const char * const cPatternString,
																 NC escapeCharacter )
{
	size_t substringLength;
	char * dataString = const_cast<char *>( cDataString );
	const char * patternString = const_cast<const char *>( cPatternString );

	while( *patternString )
	{
		if( !*dataString )
			return THIS_LESS_THAN_OTHER;

		NC *patternSubstring = findPatternSubstringWithoutMetacharacters( patternString );
		if( patternSubstring )
		{
			substringLength = strlen( patternSubstring );
			patternString += substringLength;

			if( strlen( dataString) < substringLength )
			{
				delete [] patternSubstring;
				return THIS_LESS_THAN_OTHER;
			}

			NI memcmpResult = memcmp( patternSubstring, dataString, substringLength );
			delete [] patternSubstring;
			patternSubstring = 0;
			if( memcmpResult )
				return THIS_LESS_THAN_OTHER;

			//  Compare succeeded.  Consume the substring;
			dataString += substringLength;
			if( !( *patternString ) && !( *dataString ) )
				return THIS_EQUAL_TO_OTHER;
		}

		//  There was no patternSubstring, so patternString is pointing at a metacharacter.
		//  Is it the escape character?
		if( *patternString == escapeCharacter )
		{
			patternString++;
			if( *patternString != *dataString )
				return THIS_LESS_THAN_OTHER;

			//  They match.  Consume the characters
			dataString++;
			patternString++;
		}
		else if( *patternString == CQL_ONE_ANY )
		{
			patternString++;
			dataString++;
		}
		else if( *patternString == CQL_MANY_ANY )
		{
			patternString++;
			if( !*patternString )
				// CQL_MANY_ANY (%) is the last character, so it matches the rest of dataString
				return THIS_EQUAL_TO_OTHER;

			for( patternSubstring = findPatternSubstringWithoutMetacharacters( patternString ); *patternString && !patternSubstring; patternSubstring = findPatternSubstringWithoutMetacharacters( patternString ) )
				//  The next character is a metacharacter.  This means %% or %_.  In this case,
				//  the second metacharacter is meaningless because it follows %.
				patternString++;

			if( !patternString )
				//  effectively, last character in pattern string is %, so it matches the rest of the dataString
				return THIS_EQUAL_TO_OTHER;

			substringLength = strlen( patternSubstring );

			NC *dataSubstring;
			NI foundSubstring = 0;
			for( dataSubstring = dataString; !foundSubstring && *dataSubstring; dataSubstring++ )
				if( !memcmp( dataSubstring, patternSubstring, substringLength ) )
					foundSubstring = 1;

			delete [] patternSubstring;

			if( !foundSubstring )
				//  entire dataString was searched without finding substring
				return THIS_LESS_THAN_OTHER;

			//  consume substrings from both pattern and data
			patternString += substringLength;
			dataString += ( dataSubstring - dataString );

		}
	}

	if( *dataString )
		return THIS_LESS_THAN_OTHER;

	//  dataString and patternString both ended at the same time
	return THIS_EQUAL_TO_OTHER;
}


CqlConstants::CompareResult CqlString::stringCompareCommaDelimitedList( pNC item )
{
	NC itemFromList[ 100 ];
	pNC pIn = text_, pOut, stringBuffer, patternBuffer, pStr, pPat;
	UNI itemLen, otherLen;
	CompareResult cr = COMPARE_RESULT_UNSET;

	while( *pIn )
	{
		memset( itemFromList, 0, sizeof( itemFromList ) );
		pOut = itemFromList;
		if( *pIn == '\'' )
			pIn++;
		while( *pIn && *pIn != ',' && *pIn != '\'' )
			*pOut++ = *pIn++;
		if( *pIn == '\'' )
			pIn++;
		if( *pIn == ',' )
			pIn++;

		itemLen = strlen( item );
		stringBuffer = new NC[ itemLen + 1 ];
		if( !stringBuffer )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		memset( stringBuffer, 0, itemLen + 1 );

		memset( stringBuffer, 0, itemLen + 1 );
		memcpy( stringBuffer, item, itemLen );
		pStr = stringBuffer + ( itemLen - 1 );

		otherLen = strlen( itemFromList );
		patternBuffer = new NC[ otherLen + 1 ];
		if( !patternBuffer )
		{
			delete [] stringBuffer;
			throw MemoryAllocationException( __FILE__, __LINE__ );
		}
		memset( patternBuffer, 0, otherLen + 1 );
		memcpy( patternBuffer, itemFromList, otherLen );
		pPat = patternBuffer + ( otherLen - 1 );

		cr = regularExpressionCompare( stringBuffer, patternBuffer, '\\' );
		delete [] patternBuffer;
		delete [] stringBuffer;
		
		if( cr == THIS_EQUAL_TO_OTHER )
			return cr;
	}

	return cr;
}


NI CqlString::areWildcards( void )
{
	pNC p;
	UNI loop;

	for( loop = 0, p = text_; loop < length_; loop++ )
		if( *p == CQL_ONE_ANY || *p == CQL_MANY_ANY )
			return CQL_YES;

	return CQL_NO;
}


US CqlString::dictionaryLength( void )
{
	//  don't store null terminator (?)
	return ((US)( sizeof( length_ ) + length_ ) );
}


UL CqlString::length( void ) const
{
	return length_;
}


const char * const CqlString::text( void ) const
{
	return text_;
}


void CqlString::output( std::ostream& ostr ) const
{
	if( text_ )
		ostr << text_;
}


CqlString::operator pNC( void )
{
	return text_;
}


std::ostream& operator << ( std::ostream& ostr, const CqlString& str )
{
	str.output( ostr );
	return ostr;
}


CqlFixedLengthString::CqlFixedLengthString( UL len ) : CqlString( len + 1 ), fixedLength_( len + 1 )
{
}

CqlFixedLengthString::CqlFixedLengthString( CqlString& other )
		: CqlString( other ), fixedLength_( other.length() + 1 )
{
}


CqlFixedLengthString::~CqlFixedLengthString( void )
{
}


CqlFixedLengthString& CqlFixedLengthString::operator = ( const CqlString& source )
{
	if( source.length() > length() )
		throw LengthExceededException( __FILE__, __LINE__ );
	unsigned int sourcelen = strlen( const_cast<char*>(source.text() ) );
	char *destText = const_cast<char*>(text());
	memset( destText, 0, length() );
	memcpy( destText, const_cast<char*>(source.text()), sourcelen );
	return *this;
}


CqlFixedLengthString& CqlFixedLengthString::operator = ( const CqlFixedLengthString& source )
{
	if( source.length() > length() )
		throw LengthExceededException( __FILE__, __LINE__ );
	memset( const_cast<char*>(text()), ' ', length() - 1 );
	memcpy( const_cast<char*>(text()), const_cast<char*>(source.text()), strlen( const_cast<char*>(source.text()) ) );
	return *this;
}


CqlFixedLengthString& CqlFixedLengthString::operator = ( const NC *source )
{
	if( strlen( source ) > length() )
		throw LengthExceededException( __FILE__, __LINE__ );
	memset( const_cast<char*>(text()), ' ', length() - 1 );
	memcpy( const_cast<char*>(text()), source, strlen( const_cast<char*>(source) ) );
	return *this;
}


CqlStringWithPosition& CqlStringWithPosition::operator = ( const CqlString& other )
{
	position_ = 0;
	dynamic_cast< CqlString& >( *this ) = other;
	return *this;
}


CqlStringWithPosition::CqlStringWithPosition( void ) : CqlString(), position_( 0 )
{
}


NC CqlStringWithPosition::nextCharacter( void )
{
	if( !text() || text()[ position_ ] == 0 )
		return EOF;

	return text()[ position_++ ];
}
