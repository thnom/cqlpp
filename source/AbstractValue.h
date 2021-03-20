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


#ifndef __AbstractValue_h
#define __AbstractValue_h


class AbstractValue : public CqlColumnTypes, public ErrorConstants, public ExceptionCodes
{
	bool nullflag_;

public :

	AbstractValue( CqlColumnType ttype, UL tlength = 0 )
        : CqlColumnTypes( ttype, tlength ), nullflag_( false ) { }

	virtual ~AbstractValue( void ) { }

	static AbstractValue *createObject( const CqlColumnTypes& );
	static AbstractValue *createObject( const AbstractValue& );

	void clearNullflag( void ) { nullflag_ = false; }
	CqlColumnTypes& columnType( void ) { return *this; }
	void columnType( CqlColumnTypes& );
	void setNullflag( void ) { nullflag_ = true; }
	bool& nullflag( void ) { return nullflag_; }

	virtual void absoluteValue( void );
	virtual const CqlString asString( bool spacePadding = false ) const;
	virtual void expand( UL newLength );
	virtual void initialize( void );
	virtual void releaseMemory( void );

	virtual AbstractValue& operator = ( const AbstractValue& ) = 0;

	virtual AbstractValue& operator += ( AbstractValue& ) = 0;
	virtual AbstractValue& operator -= ( AbstractValue& ) = 0;
	virtual AbstractValue& operator *= ( AbstractValue& ) = 0;
	virtual AbstractValue& operator /= ( AbstractValue& ) = 0;

	virtual bool operator > ( const AbstractValue& ) const = 0;
	virtual bool operator >= ( const AbstractValue& ) const = 0;
	virtual bool operator < ( const AbstractValue& ) const = 0;
	virtual bool operator <= ( const AbstractValue& ) const = 0;
	virtual bool operator == ( const AbstractValue& ) const = 0;
	virtual bool operator != ( const AbstractValue& ) const = 0;

	virtual void operator << ( pUC& ) = 0;
	virtual void operator >> ( pUC& ) = 0;
	virtual void operator >> ( BinaryValue& ) = 0;
	virtual void operator << ( BinaryValue& ) = 0;
	virtual void operator << ( BoundColumn* ) = 0;
	virtual void operator >> ( BoundColumn* ) = 0;
	virtual void operator << ( TempBuffer& ) = 0;
	virtual void operator >> ( TempBuffer& ) = 0;

	virtual SC asChar( void ) const = 0;
	virtual S asShort( void ) const = 0;
	virtual L asLong( void ) const = 0;
	virtual BigintValue asBigintValue( void ) const = 0;
	virtual DecimalValue asDecimalValue( void ) const = 0;
	virtual F asFloat( void ) const = 0;
	virtual D asDouble( void ) const = 0;
	virtual DateValue asDateValue( void ) const = 0;
	virtual TimeValue asTimeValue( void ) const = 0;
	virtual TimestampValue asTimestampValue( void ) const = 0;
	
	virtual void input( FileManager& ) = 0;
	virtual void input( TempBuffer& ) = 0;
	virtual UL length( void ) const = 0;
	virtual void output( FileManager& ) const = 0;
	virtual void output( TempBuffer& ) const = 0;
	virtual UL streamLength( void ) const = 0;
};


struct BigintLiteral
{
	US highest_;
	US higher_;
	US lower_;
	US lowest_;
	CqlConstants::SignValues sign_;
};


class BigintValue : public AbstractValue
{
protected :

	BigintLiteral bigintLiteral_;

private :

	CompareResult compareMantissa( const BigintValue& ) const;
	static const UL fixedLength_;

public :

	BigintValue( void ) : AbstractValue( CQL_BIGINT )
	{
		bigintLiteral_.highest_ = 0;
		bigintLiteral_.higher_ = 0;
		bigintLiteral_.lower_ = 0;
		bigintLiteral_.lowest_ = 0;
		bigintLiteral_.sign_ = SV_POSITIVE;
	}
	BigintValue( const BigintLiteral& );
	BigintValue( const CqlColumnTypes& );
	BigintValue( const BigintValue& );
	BigintValue( pUC& );
	BigintValue( const CqlString& );
	BigintValue( const NI );
	BigintValue( const UNI );
	BigintValue( const UL );
	BigintValue( const US );
	BigintValue( const S );
	BigintValue( const L );
	BigintValue( const D );
	BigintValue( const UC *, const UNI );
	BigintValue( const NC * );
	BigintValue( const UC * );
	BigintValue( DecimalValue& );
	BigintValue( const NC );

	virtual ~BigintValue( void );

	AbstractValue& operator = ( const AbstractValue& );
	BigintValue& operator = ( const CqlString& );
	BigintValue& operator = ( const NC * );
	BigintValue& operator = ( const BigintValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;

	bool operator == ( const BigintValue& ) const;
	bool operator > ( const BigintValue& ) const;
	bool operator >= ( const BigintValue& ) const;
	bool operator < ( const BigintValue& ) const;
	bool operator <= ( const BigintValue& ) const;

	BigintValue& operator << ( NI );
	BigintValue& operator >> ( NI );

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator >> ( BinaryValue& );
	void operator << ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );
	bool operator ! ( void ) const;

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	void absoluteValue( void );
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const BigintValue& ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	static const UL fixedLength( void ) { return fixedLength_; }
	bool highBitOn( void );
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	void readDictionaryInformation( TempBuffer& buffer );
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
	void zero( void );
};


class BinaryValue : public AbstractValue
{
protected :

	UC length_;
	pUC buffer_;

public :

	BinaryValue( void ) : AbstractValue( CQL_BINARY ), length_( 0 ), buffer_( 0 ) { }
	BinaryValue( const CqlColumnTypes& );
	BinaryValue( pUC& );
	BinaryValue( const BinaryValue& );
	BinaryValue( const CqlString& );
	BinaryValue( const UC *, const UNI );
	BinaryValue( const NC * );
	BinaryValue( const UC * );
	BinaryValue( const NC );
	BinaryValue( const D );
	BinaryValue( const NI );
	BinaryValue( const L );
	BinaryValue( const UNI );
	BinaryValue( const US );
	BinaryValue( const UL );

	virtual ~BinaryValue( void )
	{
		if( buffer_ )
		{
			delete [] buffer_;
			buffer_ = 0;
			length_ = 0;
		}
	}

	AbstractValue& operator = ( const AbstractValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	void operator = ( const BinaryValue& );

	bool operator ! ( void ) const;
	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator >> ( BinaryValue& );
	void operator << ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	UC *buffer( void ) const { return buffer_; }
	CompareResult compare( const BinaryValue& ) const;
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	US dictionaryLength( void );
	void expand( UL newLength );
	void initialize( void );
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	UC*& rBuffer( void ) { return buffer_; }
	void readDictionaryInformation( TempBuffer& buffer );
	UC& rLength( void ) { return length_; }
	void releaseMemory( void );
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


class BitValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	bool pvalue_;

public :

	BitValue( void ) : AbstractValue( CQL_BIT ), pvalue_( 0 ) { }
	BitValue( const CqlColumnTypes& );
	BitValue( pUC& );
	BitValue( const BitValue& );
	BitValue( const UC *, const UNI );
	BitValue( const NC * );
	BitValue( const UC * );
	BitValue( const NC );
	BitValue( const CqlString& );
	BitValue( const D );
	BitValue( const NI );
	BitValue( const L );
	BitValue( const UNI );
	BitValue( const US );
	BitValue( const UL );

	virtual ~BitValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	BitValue& operator = ( const BitValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator ! ( void ) const;
	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator >> ( BinaryValue& );
	void operator << ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	void absoluteValue( void );
	const CqlString asString( bool spacePadding = false ) const;
	void clearPvalue( void ) { pvalue_ = false; }
	CompareResult compare( const BitValue& ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	static const UL fixedLength( void ) { return fixedLength_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	bool pvalue( void ) const { return pvalue_; }
	void readDictionaryInformation( TempBuffer& buffer );
	bool& rPvalue( void ) { return pvalue_; }
	void setPvalue( void ) { pvalue_ = true; }
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


class CharUCValue;

class CharValue : public AbstractValue
{
protected :

	CqlString value_;

public :

	CharValue( void ) : AbstractValue( CQL_CHAR ), value_() { }
	CharValue( CqlColumnType ct ) : AbstractValue( ct ), value_() { }
	CharValue( const CqlColumnTypes& );
	CharValue( const CharValue& );
	CharValue( pUC& );
	CharValue( const NC * );
	CharValue( const UC * );
	CharValue( const NC );
	CharValue( const CqlString& /*data*/ );
	CharValue( const CqlString& /*data*/, const UL /*typeLength*/ );
	CharValue( const UC *, const UNI );
	CharValue( const D );
	CharValue( const NI );
	CharValue( const L );
	CharValue( const UNI );
	CharValue( const US );
	CharValue( const UL );

	virtual ~CharValue( void )
	{
		value_.reset();
	}

	AbstractValue& operator = ( const AbstractValue& );
	CharValue& operator = ( const CharValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator ! ( void ) const;
	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator >> ( BinaryValue& );
	void operator << ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const CharValue& ) const;
	CompareResult compare( const CharUCValue& ) const;
	const char * const data( void ) { return value_.text(); }
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	void initialize( void );
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const { return value_.length(); }
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	void readDictionaryInformation( TempBuffer& buffer );
	void releaseMemory( void );
	UL streamLength( void ) const;
	const CqlString& value( void ) const { return value_; }
	void writeDictionaryInformation( TempBuffer& buffer );
};


class CharUCValue : public CharValue
{
	//  this is a utility used by relational operator methods.
	//  if operates on the second value for those methods, hence other value
	CqlString *otherString(const AbstractValue& /*otherValue*/) const;

public :

	CharUCValue( void ) : CharValue(CQL_CHARUC) { }
	CharUCValue( const CqlColumnTypes& );
	CharUCValue( const CharValue& );
	CharUCValue( const CharUCValue& );
	CharUCValue( pUC& );
	CharUCValue( const CqlString& );
	CharUCValue( const NC * );
	CharUCValue( const UC * );
	CharUCValue( const NC );
	CharUCValue( const D );
	CharUCValue( const NI );
	CharUCValue( const L );
	CharUCValue( const UNI );
	CharUCValue( const US );
	CharUCValue( const UL );
	CharUCValue( const UC *, const UNI );

	virtual ~CharUCValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	CharUCValue& operator = ( const CharUCValue& );
	CharUCValue& operator = ( const CharValue& );

	//  inheriting this didn't work, as the argument types are different,
	//  and I no longer muck around with cast operators to cloud such cases.
	bool operator ! ( void ) const;

	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;

//	SC asChar( void ) const;
//	S asShort( void ) const;
//	L asLong( void ) const;
//	BigintValue asBigintValue( void ) const;
//	DecimalValue asDecimalValue( void ) const;
//	F asFloat( void ) const;
//	D asDouble( void ) const;
//	DateValue asDateValue( void ) const;
//	TimeValue asTimeValue( void ) const;
//	TimestampValue asTimestampValue( void ) const;
	
	CompareResult compare( const CharValue& ) const;
	CompareResult compare( const CharUCValue& ) const;
};


struct DateLiteral
{
	S year_;
	US month_;
	US day_;
};


class DateValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	struct DateLiteral dateLiteral_;

	bool isLeapYear( void ) const;
	US firstDayOfYear( void ) const;
	US lastDayOfMonth( void ) const;

public :

	DateValue( void ) : AbstractValue( CQL_DATE )
	{
		dateLiteral_.year_ = 0;
		dateLiteral_.month_ = 0;
		dateLiteral_.day_ = 0;
	}

	DateValue( DateLiteral& dl ) : AbstractValue( CQL_DATE )
	{
		dateLiteral_.year_ = dl.year_;
		dateLiteral_.month_= dl.month_;
		dateLiteral_.day_ = dl.day_;
	}

	DateValue( S y, US m, US d ) : AbstractValue( CQL_DATE )
	{
		dateLiteral_.year_ = y;
		dateLiteral_.month_ = m;
		dateLiteral_.day_ = d;
	}

	DateValue( const CqlColumnTypes& );
	DateValue( const DateValue& );
	DateValue( pUC& );
	DateValue( const CqlString& );
	DateValue( const NC * );
	DateValue( const UC * );
	DateValue( const NC );
	DateValue( const TimestampValue& );
	DateValue( const D );
	DateValue( const NI );
	DateValue( const L );
	DateValue( const UNI );
	DateValue( const US );
	DateValue( const UL );
	DateValue( const UC *, const UNI );

	virtual ~DateValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	DateValue& operator = ( const DateValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;
	bool operator ! ( void ) const;
	bool operator != ( const AbstractValue& ) const;

	bool operator == ( const DateValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator <= ( const DateValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const DateValue& ) const;
	US day( void ) const { return dateLiteral_.day_; }
	US dayOfWeek( void ) const;
	US dayOfYear( void ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	static const UL fixedLength( void ) { return fixedLength_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	US month( void ) const { return dateLiteral_.month_; }
	void month( US m ) { dateLiteral_.month_ = m; }
	void output( FileManager& ) const;
	void output( TempBuffer& ) const ;
	US quarter( void ) const;
	void readDictionaryInformation( TempBuffer& buffer );
	void setToCurrentDate( void );
	UL streamLength( void ) const;
	US weekNumber( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
	S year( void ) const { return dateLiteral_.year_; }
};


struct DecimalLiteral
{
	CqlConstants::SignValues sign_;
	NC scale_;
	NC digits_[ 8 ];
};


class DecimalValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	DecimalLiteral decimalLiteral_;

private :

	CompareResult compareMantissa( const DecimalValue& ) const;

public :

	DecimalValue( void ) : AbstractValue( CQL_DECIMAL )
	{
		decimalLiteral_.sign_ = SV_POSITIVE;
		decimalLiteral_.scale_ = 0;
		memset( decimalLiteral_.digits_, 0, sizeof( decimalLiteral_.digits_ ) );
	}

	DecimalValue( pUC& );
	DecimalValue( const CqlColumnTypes& );
	DecimalValue( const BigintValue& );
	DecimalValue( IntegerValue& );
	DecimalValue( SmallintValue& );
	DecimalValue( TinyintValue& );
	DecimalValue( const DecimalValue& );
	DecimalValue( const NI );
	DecimalValue( const UNI );
	DecimalValue( const US );
	DecimalValue( const UL );
	DecimalValue( const L );
	DecimalValue( const D );
	DecimalValue( const UC *, const UNI );
	DecimalValue( const NC * );
	DecimalValue( const UC * );
	DecimalValue( const NC );
	DecimalValue( const CqlString& );

	virtual ~DecimalValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	DecimalValue& operator = ( const CqlString& );
	DecimalValue& operator = ( const NC * );
	DecimalValue& operator = ( const DecimalValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;
	bool operator ! ( void ) const;
	bool operator != ( const AbstractValue& ) const;

	bool operator == ( const DecimalValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator <= ( const DecimalValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	void absoluteValue( void );
	const CqlString asString( bool spacePadding = false ) const;
	UNI availableShifts( void );
	CompareResult  compare( const DecimalValue& ) const;
	US dictionaryLength( void );
	US digit( const UNI ) const;
	void digit( const UNI /* digitNumber */, const UNI /* digitValue */ );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	static const UL fixedLength( void ) { return fixedLength_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void normalize( DecimalValue& /* n1 */, DecimalValue& /* n2 */, const DecimalValue& /* op1 */, const DecimalValue& /* op2 */ ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	void readDictionaryInformation( TempBuffer& buffer );
	void shiftLeft( UNI /* digitsToShift */ );
	void shiftRight( UNI /* digitsToShift */ );
	void shiftToZeroExponent( void );
	void shiftToRemoveTrailingZeros( void );
	UNI significantDigits( void );
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
	void zero( void );  //  zero digits, scale, and sign
	void zeroDigits( void );
};


class FloatValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	D pvalue_;

public :

	FloatValue( void ) : AbstractValue( CQL_FLOAT ), pvalue_( 0 ) { }
	FloatValue( const CqlColumnTypes& );
	FloatValue( const FloatValue& );
	FloatValue( const D v ) : AbstractValue( CQL_FLOAT ), pvalue_( v ) { }
	FloatValue( pUC& );
	FloatValue( BigintValue& );
	FloatValue( DecimalValue& );
	FloatValue( L l ) : AbstractValue( CQL_FLOAT ), pvalue_( l ) { }
	FloatValue( IntegerValue&) ;
	FloatValue( RealValue& );
	FloatValue( SmallintValue& );
	FloatValue( TinyintValue& );
	FloatValue( const UC *, const UNI );
	FloatValue( const NC * );
	FloatValue( const UC * );
	FloatValue( const NC );
	FloatValue( const CqlString& );
	FloatValue( const NI );
	FloatValue( const UNI );
	FloatValue( const US );
	FloatValue( const UL );

	virtual ~FloatValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	FloatValue& operator = ( const FloatValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;
	bool operator ! ( void ) const;
	bool operator != ( const AbstractValue& ) const;

	bool operator == ( const FloatValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator <= ( const FloatValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	void absoluteValue( void );
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const FloatValue& ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	static const UL fixedLength( void ) { return fixedLength_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	D pvalue( void ) const { return pvalue_; }
	void readDictionaryInformation( TempBuffer& buffer );
	D& rPvalue( void ) { return pvalue_; }
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


class IntegerValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	L pvalue_;

public :

	IntegerValue( void ) : AbstractValue( CQL_INTEGER ), pvalue_( 0 ) { }
	IntegerValue( const CqlColumnTypes& );
	IntegerValue( const IntegerValue& );
	IntegerValue( const D );
	IntegerValue( const F );
	IntegerValue( const NI );
	IntegerValue( const L l ) : AbstractValue( CQL_INTEGER ), pvalue_( l ) { }
	IntegerValue( const S );
	IntegerValue( const UNI );
	IntegerValue( const US );
	IntegerValue( const UL );
	IntegerValue( pUC& );
	IntegerValue( const BigintValue& );
	IntegerValue( const DecimalValue& );
	IntegerValue( const SmallintValue& );
	IntegerValue( const TinyintValue& );
	IntegerValue( const UC *, const UNI );
	IntegerValue( const NC * );
	IntegerValue( const UC * );
	IntegerValue( const NC );
	IntegerValue( const CqlString& );

	virtual ~IntegerValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	IntegerValue& operator = ( const IntegerValue& );
#ifndef CQL_BOOL_IS_INT
	IntegerValue& operator = ( const bool );
#endif
	IntegerValue& operator = ( const NC );
	IntegerValue& operator = ( const UC );
	IntegerValue& operator = ( const S );
	IntegerValue& operator = ( const US );
	IntegerValue& operator = ( const NI );
	IntegerValue& operator = ( const UNI );
	IntegerValue& operator = ( const L );
	IntegerValue& operator = ( const UL );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;
	bool operator ! ( void ) const;

	bool operator == ( const IntegerValue& ) const;
	bool operator != ( const IntegerValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator <= ( const IntegerValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	void absoluteValue( void );
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const IntegerValue& ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	static const UL fixedLength( void ) { return fixedLength_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	L pvalue( void ) const { return pvalue_; }
	void readDictionaryInformation( TempBuffer& buffer );
	L& rPvalue( void ) { return pvalue_; }
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


class LongvarbinaryValue : public AbstractValue
{
protected :

	UC *buffer_;
	UL length_;

public :

	LongvarbinaryValue( void ) : AbstractValue( CQL_LONGVARBINARY ), buffer_( 0 ), length_( 0 ) { }
	LongvarbinaryValue( const CqlColumnTypes& );
	LongvarbinaryValue( const LongvarbinaryValue& );
	LongvarbinaryValue( pUC& );
	LongvarbinaryValue( const UC * /*buffer*/, const UL /*length*/ );
	LongvarbinaryValue( BinaryValue& );
	LongvarbinaryValue( const CqlString& );
	LongvarbinaryValue( VarbinaryValue& );
	LongvarbinaryValue( const NC * );
	LongvarbinaryValue( const UC * );
	LongvarbinaryValue( const NC );
	LongvarbinaryValue( const D );
	LongvarbinaryValue( const NI );
	LongvarbinaryValue( const L );
	LongvarbinaryValue( const UNI );
	LongvarbinaryValue( const US );
	LongvarbinaryValue( const UL );

	virtual ~LongvarbinaryValue( void )
	{
		if( buffer_ )
		{
			delete [] buffer_;
			buffer_ = 0;
			length_ = 0;
		}
	}

	AbstractValue& operator = ( const AbstractValue& );
	LongvarbinaryValue& operator = ( const LongvarbinaryValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator ! ( void ) const;
	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	UC *buffer( void ) const { return buffer_; }
	CompareResult compare( const LongvarbinaryValue& ) const;
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	US dictionaryLength( void );
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	UC*& rBuffer( void ) { return buffer_; }
	void readDictionaryInformation( TempBuffer& buffer );
	void releaseMemory( void );
	UL& rLength( void ) { return length_; }
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


class LongvarcharValue : public AbstractValue
{
protected :

	NC *buffer_;
	UL length_;

public :

	LongvarcharValue( void ) : AbstractValue( CQL_LONGVARCHAR ), buffer_( 0 ), length_ ( 0 ) { }
	LongvarcharValue( const CqlColumnTypes& );
	LongvarcharValue( const LongvarcharValue& );
	LongvarcharValue( pUC& );
	LongvarcharValue( UL /*length*/, UC * /*buffer*/ );
	LongvarcharValue( CharValue& );
	LongvarcharValue( const CqlString& );
	LongvarcharValue( VarcharValue& );
	LongvarcharValue( const UC *, const UNI );
	LongvarcharValue( const NC * );
	LongvarcharValue( const UC * );
	LongvarcharValue( const NC );
	LongvarcharValue( const D );
	LongvarcharValue( const NI );
	LongvarcharValue( const L );
	LongvarcharValue( const UNI );
	LongvarcharValue( const US );
	LongvarcharValue( const UL );

	virtual ~LongvarcharValue( void )
	{
		if( buffer_ )
		{
			delete [] buffer_;
			buffer_ = 0;
			length_ = 0;
		}
	}

	AbstractValue& operator = ( const AbstractValue& );
	LongvarcharValue& operator = ( const LongvarcharValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator ! ( void ) const;
	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	const CqlString asString( bool spacePadding = false ) const;
	NC *buffer( void ) const { return buffer_; }
	CompareResult compare( const LongvarcharValue& ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	NC*& rBuffer( void ) { return buffer_; }
	UL& rLength( void ) { return length_; }
	void readDictionaryInformation( TempBuffer& buffer );
	void releaseMemory( void );
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


class RealValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	F pvalue_;

public :

	RealValue( void ) : AbstractValue( CQL_REAL ), pvalue_( 0 ) { }
	RealValue( const CqlColumnTypes& );
	RealValue( const RealValue& );
	RealValue( const D );
	RealValue( const NI );
	RealValue( const UNI );
	RealValue( const US );
	RealValue( const UL );
	RealValue( const F v ) : AbstractValue( CQL_REAL ), pvalue_( v ) { }
	RealValue( const L l ) : AbstractValue( CQL_REAL ), pvalue_( static_cast< const F >( l ) ) { }
	RealValue( pUC& );
	RealValue( BigintValue& );
	RealValue( DecimalValue& );
	RealValue( const IntegerValue& );
	RealValue( const SmallintValue& );
	RealValue( const TinyintValue& );
	RealValue( const UC *, const UNI );
	RealValue( const NC * );
	RealValue( const UC * );
	RealValue( const NC );
	RealValue( const CqlString& );

	virtual ~RealValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	RealValue& operator = ( const RealValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;
	bool operator ! ( void ) const;

	bool operator == ( const RealValue& ) const;
	bool operator != ( const RealValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator <= ( const RealValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	void absoluteValue( void );
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const RealValue& other ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	static const UL fixedLength( void ) { return fixedLength_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	F pvalue( void ) const { return pvalue_; }
	void readDictionaryInformation( TempBuffer& buffer );
	F& rPvalue( void ) { return pvalue_; }
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


class SmallintValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	S pvalue_;

public :

	SmallintValue( void ) : AbstractValue( CQL_SMALLINT ), pvalue_( 0 ) { }
	SmallintValue( const CqlColumnTypes& );
	SmallintValue( const D );
	SmallintValue( const F );
	SmallintValue( const S v ) : AbstractValue( CQL_SMALLINT ), pvalue_( v ) { }
	SmallintValue( const L l );
	SmallintValue( const NI );
	SmallintValue( const UNI );
	SmallintValue( const US );
	SmallintValue( const UL );
	SmallintValue( pUC& );
	SmallintValue( const SmallintValue& );
	SmallintValue( const BigintValue& );
	SmallintValue( const DecimalValue& );
	SmallintValue( const UC *, const UNI );
	SmallintValue( const NC * );
	SmallintValue( const UC * );
	SmallintValue( const NC );
	SmallintValue( const CqlString& );

	virtual ~SmallintValue( void ) { }

	SmallintValue( TinyintValue& );

	AbstractValue& operator = ( const AbstractValue& );
	SmallintValue& operator = ( const SmallintValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;
	bool operator ! ( void ) const;

	bool operator == ( const SmallintValue& ) const;
	bool operator != ( const SmallintValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator <= ( const SmallintValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	void absoluteValue( void );
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const SmallintValue& ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	static const UL fixedLength( void ) { return fixedLength_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	S pvalue( void ) const { return pvalue_; }
	void readDictionaryInformation( TempBuffer& buffer );
	S& rPvalue( void ) { return pvalue_; }
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


struct TimeLiteral
{
	US hour_;
	US minute_;
	US second_;
};


class TimeValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	struct TimeLiteral timeLiteral_;

public :

	TimeValue( void ) : AbstractValue( CQL_TIME )
	{
		timeLiteral_.hour_ = 0;
		timeLiteral_.minute_ = 0;
		timeLiteral_.second_ = 0;
	}
	TimeValue( TimeLiteral& tl ) : AbstractValue( CQL_TIME )
	{
		timeLiteral_.hour_ = tl.hour_;
		timeLiteral_.minute_ = tl.minute_;
		timeLiteral_.second_ = tl.second_;
	}
	TimeValue( US h, US m, US s ) : AbstractValue( CQL_TIME )
	{
		timeLiteral_.hour_ = h;
		timeLiteral_.minute_ = m;
		timeLiteral_.second_ = s;
	}
	TimeValue( const CqlColumnTypes& );
	TimeValue( const TimeValue& );
	TimeValue( pUC& );
	TimeValue( const CqlString& );
	TimeValue( const NC * );
	TimeValue( const UC * );
	TimeValue( const NC );
	TimeValue( const TimestampValue& );
	TimeValue( const D );
	TimeValue( const NI );
	TimeValue( const L );
	TimeValue( const UNI );
	TimeValue( const US );
	TimeValue( const UL );
	TimeValue( const UC *, const UNI );

	virtual ~TimeValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	TimeValue& operator = ( const TimeValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;
	bool operator ! ( void ) const;

	bool operator == ( const TimeValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator <= ( const TimeValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const TimeValue& ) const;
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	US dictionaryLength( void );
	static const UL fixedLength( void ) { return fixedLength_; }
	US hour( void ) const { return timeLiteral_.hour_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	US minute( void ) const { return timeLiteral_.minute_; }
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	US second( void ) const { return timeLiteral_.second_; }
	void readDictionaryInformation( TempBuffer& buffer );
	void setToCurrentTime( void );
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


struct TimestampLiteral
{
	S year_;
	US month_;
	US day_;
	US hour_;
	US minute_;
	US second_;
	UL fraction_;
};


class TimestampValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	TimestampLiteral timestampLiteral_;

public :

	TimestampValue( void ) : AbstractValue( CQL_TIMESTAMP )
	{
		timestampLiteral_.year_ = 0;
		timestampLiteral_.month_ = 0;
		timestampLiteral_.day_ = 0;
		timestampLiteral_.hour_ = 0;
		timestampLiteral_.minute_ = 0;
		timestampLiteral_.second_ = 0;
		timestampLiteral_.fraction_ = 0;
	}
	
	TimestampValue( TimestampLiteral& tl ) : AbstractValue( CQL_TIMESTAMP )
	{
		timestampLiteral_.year_ = tl.year_;
		timestampLiteral_.month_ = tl.month_;
		timestampLiteral_.day_ = tl.day_;
		timestampLiteral_.hour_= tl.hour_;
		timestampLiteral_.minute_ = tl.minute_;
		timestampLiteral_.second_ = tl.second_;
		timestampLiteral_.fraction_ = tl.fraction_;
	}
	
	TimestampValue( S y,
					US m,
					US d,
					US h,
					US mi,
					US s,
					UL f )
		: AbstractValue( CQL_TIMESTAMP )
	{
		timestampLiteral_.year_ = y;
		timestampLiteral_.month_ = m;
		timestampLiteral_.day_ = d;
		timestampLiteral_.hour_ = h;
		timestampLiteral_.minute_ = mi;
		timestampLiteral_.second_ = s;
		timestampLiteral_.fraction_ = f;
	}

	TimestampValue( const CqlColumnTypes& );
	TimestampValue( const TimestampValue& );
	TimestampValue( pUC& );
	TimestampValue( const CqlString& );
	TimestampValue( const NC * );
	TimestampValue( const UC * );
	TimestampValue( const NC );
	TimestampValue( const D );
	TimestampValue( const NI );
	TimestampValue( const L );
	TimestampValue( const UNI );
	TimestampValue( const US );
	TimestampValue( const UL );
	TimestampValue( const TimeValue& );
	TimestampValue( const DateValue& );
	TimestampValue( const UC *, const UNI );

	virtual ~TimestampValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	TimestampValue& operator = ( const TimestampValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;
	bool operator ! ( void ) const;

	bool operator == ( const TimestampValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator <= ( const TimestampValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const TimestampValue& ) const;
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	US day( void ) const { return timestampLiteral_.day_; }
	US dictionaryLength( void );

	static const UL fixedLength( void ) { return fixedLength_; }

	UL fraction( void ) const { return timestampLiteral_.fraction_; }
	US hour( void ) const { return timestampLiteral_.hour_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	US minute( void ) const { return timestampLiteral_.minute_; }
	US month( void ) const { return timestampLiteral_.month_; }
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	void readDictionaryInformation( TempBuffer& buffer );
	US second( void ) const { return timestampLiteral_.second_; }
	void setToCurrentTimestamp( void );
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
	S year( void ) const { return timestampLiteral_.year_; }
};


class TinyintValue : public AbstractValue
{
	static const UL fixedLength_;

protected :

	NC pvalue_;

public :

	TinyintValue( void ) : AbstractValue( CQL_TINYINT ), pvalue_( 0 ) { }
	TinyintValue( const CqlColumnTypes& );
	TinyintValue( const TinyintValue& );
	TinyintValue( const NC v ) : AbstractValue( CQL_TINYINT ), pvalue_( v ) { }
	TinyintValue( pUC& );
	TinyintValue( const D );
	TinyintValue( const NI );
	TinyintValue( const UNI );
	TinyintValue( const US );
	TinyintValue( const UL );
	TinyintValue( const S );
	TinyintValue( const L );
	TinyintValue( const F );
	TinyintValue( const BigintValue& );
	TinyintValue( const DecimalValue& );
	TinyintValue( const UC *, const UNI );
	TinyintValue( const NC * );
	TinyintValue( const UC * );
	TinyintValue( const CqlString& );

	virtual ~TinyintValue( void ) { }

	AbstractValue& operator = ( const AbstractValue& );
	TinyintValue& operator = ( const TinyintValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;
	bool operator ! ( void ) const;

	bool operator == ( const TinyintValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator <= ( const TinyintValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	void absoluteValue( void );
	const CqlString asString( bool spacePadding = false ) const;
	CompareResult compare( const TinyintValue& ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	static const UL fixedLength( void ) { return fixedLength_; }
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	NC pvalue( void ) const { return pvalue_; }
	void readDictionaryInformation( TempBuffer& buffer );
	NC& rPvalue( void ) { return pvalue_; }
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


class VarbinaryValue : public AbstractValue
{
protected :

	UC *buffer_;
	UC length_;

public :

	VarbinaryValue( void ) : AbstractValue( CQL_VARBINARY ), buffer_( 0 ), length_( 0 ) { }
	VarbinaryValue( const CqlColumnTypes& );
	VarbinaryValue( const VarbinaryValue& );
	VarbinaryValue( pUC& );
	VarbinaryValue( UC /*length*/, UC * /*buffer*/ );
	VarbinaryValue( const CqlString& );
	VarbinaryValue( BinaryValue& );
	VarbinaryValue( const UC *, const UNI );
	VarbinaryValue( const NC * );
	VarbinaryValue( const UC * );
	VarbinaryValue( const NC );
	VarbinaryValue( const D );
	VarbinaryValue( const NI );
	VarbinaryValue( const L );
	VarbinaryValue( const UNI );
	VarbinaryValue( const US );
	VarbinaryValue( const UL );

	virtual ~VarbinaryValue( void )
	{
		if( buffer_ )
		{
			delete [] buffer_;
			buffer_ = 0;
			length_ = 0;
		}
	}

	AbstractValue& operator = ( const AbstractValue& );
	void operator = ( const VarbinaryValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator ! ( void ) const;
	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	UC *buffer( void ) const { return buffer_; }
	CompareResult compare( const VarbinaryValue& ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	void input( FileManager& );
	void input( TempBuffer& );
	UL length( void ) const;
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	UC*& rBuffer( void ) { return buffer_; }
	void readDictionaryInformation( TempBuffer& buffer );
	UC& rLength( void ) { return length_; }
	void releaseMemory( void );
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};


class VarcharValue : public AbstractValue
{
protected :

	NC *buffer_;
	UC length_;

public :

	VarcharValue( void ) : AbstractValue( CQL_VARCHAR ), buffer_( 0 ), length_( 0 ) { }
	VarcharValue( const CqlColumnTypes& );
	VarcharValue( const VarcharValue& );
	VarcharValue( const NC* /*value*/ );
	VarcharValue( pUC& );
	VarcharValue( CharValue& );
	VarcharValue( const UC *, const UNI );
	VarcharValue( const UC * );
	VarcharValue( const NC );
	VarcharValue( const D );
	VarcharValue( const NI );
	VarcharValue( const L );
	VarcharValue( const UNI );
	VarcharValue( const US );
	VarcharValue( const UL );
	VarcharValue( const CqlString& );

	virtual ~VarcharValue( void )
	{
		if( buffer_ )
		{
			delete [] buffer_;
			buffer_ = 0;
			length_ = 0;
		}
	}

	AbstractValue& operator = ( const AbstractValue& );
	VarcharValue& operator = ( const VarcharValue& );

	AbstractValue& operator += ( AbstractValue& );
	AbstractValue& operator -= ( AbstractValue& );
	AbstractValue& operator *= ( AbstractValue& );
	AbstractValue& operator /= ( AbstractValue& );

	bool operator ! ( void ) const;
	bool operator == ( const AbstractValue& ) const;
	bool operator != ( const AbstractValue& ) const;
	bool operator > ( const AbstractValue& ) const;
	bool operator >= ( const AbstractValue& ) const;
	bool operator < ( const AbstractValue& ) const;
	bool operator <= ( const AbstractValue& ) const;

	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator >> ( BinaryValue& );
	void operator << ( BinaryValue& );
	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	const CqlString asString( bool spacePadding = false ) const;
	NC *buffer( void ) const { return buffer_; }
	NC *&rBuffer( void ) { return buffer_; }
	CompareResult compare( const VarcharValue& ) const;
	US dictionaryLength( void );
	void encode( CqlString& encodedValue, bool /*spacePadding*/ = true );
	void input( FileManager& );
	void input( TempBuffer& );
	UL length ( void ) const;
	UC& rLength( void ) { return length_; }
	void output( FileManager& ) const;
	void output( TempBuffer& ) const;
	void readDictionaryInformation( TempBuffer& buffer );
	void releaseMemory( void );
	UL streamLength( void ) const;
	void writeDictionaryInformation( TempBuffer& buffer );
};



template< class T >
class Primitive : public CqlConstants
{
protected :

	T value_;

public :

	Primitive( void ) : value_() { }
	Primitive( const CqlColumnTypes& ctype ) : value_( ctype ) { }
	Primitive( pUC& p ) : value_( p ) { }
	Primitive( const NC c ) : value_( c ) { }
	Primitive( const D d ) : value_( d ) { }
	Primitive( const F f ) : value_( f ) { }
	Primitive( const NI i ) : value_( i ) { }
	Primitive( const L l ) : value_( l ) { }
	Primitive( const S s ) : value_( s ) { }
	Primitive( const UC *s, const UL len ) : value_( s, len ) { }
	Primitive( const NC *s ) : value_( s ) { }
	virtual ~Primitive( void ) { }

	operator T&()
	{
		return value_;
	}

	Primitive& operator = ( const T& other )
	{
		value_ = other;
		return *this;
	}

	AbstractValue& operator = ( const AbstractValue& other )
	{
		return value_ = other;
	}

	AbstractValue& operator = ( const CqlString& other )
	{ 
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const NC* other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const NC& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const D& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const F& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const NI& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const L& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const S& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const UC& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const UC* other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const UNI& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const UL& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator = ( const US& other )
	{
		value_ = T( other );
		return value_;
	}

	AbstractValue& operator += ( AbstractValue& other ) { return value_ += other; }
	AbstractValue& operator -= ( AbstractValue& other ) { return value_ += other; }
	AbstractValue& operator *= ( AbstractValue& other ) { return value_ += other; }
	AbstractValue& operator /= ( AbstractValue& other ) { return value_ += other; }

	bool operator == ( BoundColumn* ) const;
	bool operator > ( BoundColumn* ) const;
	bool operator >= ( BoundColumn* ) const;
	bool operator < ( BoundColumn* ) const;
	bool operator <= ( BoundColumn* ) const;

	bool operator == ( const Primitive< T >& ) const;
	bool operator < ( const Primitive< T >& ) const;
	bool operator <= ( const Primitive< T >& ) const;
	bool operator > ( const Primitive< T >& ) const;
	bool operator >= ( const Primitive< T >& ) const;
	bool operator ! ( void ) const;

	bool operator > ( const AbstractValue& other ) const { return value_ > other; }
	bool operator >= ( const AbstractValue& other ) const { return value_ >= other; }
	bool operator < ( const AbstractValue& other ) const { return value_ < other; }
	bool operator <= ( const AbstractValue& other ) const { return value_ <= other; }
	bool operator == ( const AbstractValue& other ) const { return value_ == other; }
	bool operator != ( const AbstractValue& other ) const { return value_ != other; }

	void operator << ( pUC& buf );
	void operator >> ( pUC& buf );
	void operator >> ( BinaryValue& bv ) { value_ >> bv; }
	void operator << ( BinaryValue& bv ) { value_ << bv; }
	void operator << ( BoundColumn* bc ) { value_ << bc; }
	void operator >> ( BoundColumn* bc ) { value_ >> bc; }
	void operator << ( TempBuffer& tb );
	void operator >> ( TempBuffer& tb );

	Primitive& operator - ( void )
	{
		!value_;
		return *this;
	}

	SC asChar( void ) const;
	S asShort( void ) const;
	L asLong( void ) const;
	BigintValue asBigintValue( void ) const;
	DecimalValue asDecimalValue( void ) const;
	F asFloat( void ) const;
	D asDouble( void ) const;
	DateValue asDateValue( void ) const;
	TimeValue asTimeValue( void ) const;
	TimestampValue asTimestampValue( void ) const;
	
	void absoluteValue( void ) { value_.absoluteValue(); }
	const CqlString asString( bool spacePadding = false ) const { return value_.asString( spacePadding ); }
	CompareResult compare( const T& other ) const { return value_.compare( other ); }
	void clearNullflag( void ) { value_.clearNullflag(); }
	CqlColumnTypes& columnType( void ) { return value_.columnType(); }
	void columnType( CqlColumnTypes& t ) { value_.columnType( t ); }
	US dictionaryLength( void ) { return value_.dictionaryLength(); }
	void encode( CqlString& encodedValue, bool spacePadding = true ) { value_.encode( encodedValue, spacePadding ); }
	void expand( UL newLength ) { value_.expand( newLength ); }
	void input( FileManager& fm ) { value_.input( fm ); }
	void input( TempBuffer& tb ) { value_.input( tb ); }
	UL length( void ) const { return value_.length(); }
	void output( FileManager& fm ) const { value_.output( fm ); }
	void output( TempBuffer& tb ) const { value_.output( tb ); }
	void readDictionaryInformation( TempBuffer& buffer ) { value_.readDictionaryInformation( buffer ); }
	void releaseMemory( void ) { value_.releaseMemory(); }
	void setNullflag( void ) { value_.setNullflag(); }
	UL streamLength( void ) const { return value_.streamLength(); }
	CqlColumnType type( void ) { return value_.typeType(); }
	T& value( void ) { return value_; }
	bool& nullflag( void ) { return value_.nullflag(); }
	void writeDictionaryInformation( TempBuffer& buffer ) { value_.writeDictionaryInformation( buffer ); }
};


typedef Primitive< BigintValue > PrimitiveBigint;
typedef Primitive< BinaryValue > PrimitiveBinary;
typedef Primitive< BitValue > PrimitiveBit;
typedef Primitive< CharValue > PrimitiveChar;
typedef Primitive< CharUCValue > PrimitiveCharUC;
typedef Primitive< DateValue > PrimitiveDate;
typedef Primitive< DecimalValue > PrimitiveDecimal;
typedef Primitive< FloatValue > PrimitiveFloat;
typedef Primitive< IntegerValue > PrimitiveInteger;
typedef Primitive< LongvarbinaryValue > PrimitiveLongvarbinary;
typedef Primitive< LongvarcharValue > PrimitiveLongvarchar;
typedef Primitive< RealValue > PrimitiveReal;
typedef Primitive< SmallintValue > PrimitiveSmallint;
typedef Primitive< TimeValue > PrimitiveTime;
typedef Primitive< TimestampValue > PrimitiveTimestamp;
typedef Primitive< TinyintValue > PrimitiveTinyint;
typedef Primitive< VarbinaryValue > PrimitiveVarbinary;
typedef Primitive< VarcharValue > PrimitiveVarchar;

class AbstractType;

//class PrimitiveCharUC : public PrimitiveChar
//{
//};

template< class T >
bool Primitive< T >::operator == ( const Primitive< T >& other ) const
{
	if( value_.compare( other.value_ ) == THIS_EQUAL_TO_OTHER )
		return true;
	else
		return false;
}


template< class T >
bool Primitive< T >::operator == ( BoundColumn *bc ) const
{
	return *bc == value_;
}


template< class T >
bool Primitive< T >::operator > ( BoundColumn *bc ) const
{
	return *bc < value_;
}


template< class T >
bool Primitive< T >::operator >= ( BoundColumn *bc ) const
{
	return *bc <= value_;
}


template< class T >
bool Primitive< T >::operator < ( BoundColumn *bc ) const
{
	return *bc > value_;
}


template< class T >
bool Primitive< T >::operator <= ( BoundColumn *bc ) const
{
	return *bc >= value_;
}


template< class T >
bool Primitive< T >::operator < ( const Primitive< T >&  other ) const
{
	if( value_.compare( other.value_ ) == THIS_LESS_THAN_OTHER )
		return true;
	else
		return false;
}


template< class T >
bool Primitive< T >::operator <= ( const Primitive< T >& other ) const
{
	CompareResult cmr = value_.compare( other.value_ );
	if( cmr == THIS_LESS_THAN_OTHER || cmr == THIS_EQUAL_TO_OTHER )
		return true;
	else
		return false;
}


template< class T >
bool Primitive< T >::operator > ( const Primitive< T >& other ) const
{
	if( value_.compare( other.value_ ) == THIS_GREATER_THAN_OTHER )
		return true;
	else
		return false;
}


template< class T >
bool Primitive<  T >::operator >= ( const Primitive< T >& other ) const
{
	CompareResult cmr = value_.compare( other.value_ );
	if( cmr == THIS_GREATER_THAN_OTHER || cmr == THIS_EQUAL_TO_OTHER )
		return true;
	else
		return false;
}


template< class T >
bool Primitive<  T >::operator ! ( void ) const
{
	return !value_;
}


template< class T >
SC Primitive< T >::asChar( void ) const
{
	return value_.asChar();
}


template< class T >
S Primitive< T >::asShort( void ) const
{
	return value_.asShort();
}


template< class T >
L Primitive< T >::asLong( void ) const
{
	return value_.asLong();
}


template< class T >
BigintValue Primitive< T >::asBigintValue( void ) const
{
	return value_.asBigintValue();
}


template< class T >
DecimalValue Primitive< T >::asDecimalValue( void ) const
{
	return value_.asDecimalValue();
}


template< class T >
F Primitive< T >::asFloat( void ) const
{
	return value_.asFloat();
}


template< class T >
D Primitive< T >::asDouble( void ) const
{
	return value_.asDouble();
}


template< class T >
DateValue Primitive< T >::asDateValue( void ) const
{
	return value_.asDateValue();
}


template< class T >
TimeValue Primitive< T >::asTimeValue( void ) const
{
	return value_.asTimeValue();
}


template< class T >
TimestampValue Primitive< T >::asTimestampValue( void ) const
{
	return value_.asTimestampValue();
}


template< class T >
void Primitive< T >::operator << ( pUC& buf )
{
	UC localNullFlag = *buf++;
	if( localNullFlag )
	{
		setNullflag();
		return;
	}

	clearNullflag();
	value_ << buf;
}


template< class T >
void Primitive< T >::operator >> ( pUC& buf )
{
	if( nullflag() )
	{
		*buf++ = true;
		return;
	}

	*buf++ = false;
	value_ >> buf;
}


template< class T >
void Primitive< T >::operator << ( TempBuffer& tb )
{
	UC localNullflag;
	tb >> localNullflag;
	if( localNullflag )
	{
		setNullflag();
		return;
	}

	clearNullflag();
	tb >> value_;
}


template< class T >
void Primitive< T >::operator >> ( TempBuffer& tb )
{
	UC localNullflag = nullflag();
	tb << localNullflag;
	if( localNullflag )
	{
		setNullflag();
		return;
	}

	clearNullflag();
	tb << value_;
}


#endif  //  __AbstractValue_h
