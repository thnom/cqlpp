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


#ifndef __BoundColumn_h
#define __BoundColumn_h


class BoundColumn;
typedef List< BoundColumn > BoundColumnList;
typedef ListElement< BoundColumn, BoundColumnList > BoundColumnListElement;


class BoundColumn : public BoundColumnListElement, public CqlColumnTypes
{
	AbstractColumnDescriptor *col_;
	bool *userNullFlag_;

public :

	BoundColumn( AbstractColumnDescriptor* );
	BoundColumn( const BoundColumn& );
	virtual ~BoundColumn( void );

	enum CppTypes
	{
		CPP_BIGINT,
		CPP_BOOL,
		CPP_CHAR,
		CPP_DATE,
		CPP_DECIMAL,
		CPP_DOUBLE,
		CPP_FLOAT,
		CPP_INT,
		CPP_LONG,
		CPP_PCHAR,         //  for signed types with four byte length
		CPP_PCHAR_SHORT,   //  for signed types with one byte length
		CPP_PUCHAR,        //  for unsigned types with four byte length
		CPP_PUCHAR_SHORT,  //  for unsigned types with one byte length
		CPP_SHORT,
		CPP_STRING,
		CPP_TIME,
		CPP_TIMESTAMP,
		CPP_UNSIGNED_CHAR,
		CPP_UNSIGNED_LONG,
		CPP_UNSIGNED_INT,
		CPP_UNSIGNED_SHORT
	};

	static BoundColumn *createObject( CppTypes /*type*/, AbstractColumnDescriptor* /*column*/, bool freeable );
	static BoundColumn *createObject( const BoundColumn&, bool freeable );
	static BoundColumn *createObject( CqlColumnType /*type*/, UNI /*length*/, bool freeable );

	//  length, type, file to bind to, column number
	static void bindColumn( US, UL, CqlColumnTypes, AbstractTable&, NI = CQL_YES );
	static void bindColumn( US, CqlColumnTypes, CqlString&, AbstractTable&, NI = CQL_YES );
	static void bindColumn( US, CqlColumnTypes, TempBuffer&, AbstractTable&, NI = CQL_YES );
	static void bindNullColumn( US, CqlColumnTypes, AbstractTable& );
	void clearUserNullFlag( void ) { *userNullFlag_ = false; }
	AbstractColumnDescriptor *col( void ) { return col_; }
	void setUserNullFlag( void ) { *userNullFlag_ = true; }
	void userNullFlag( bool& f ) { userNullFlag_ = &f; }
	bool userNullFlag( void ) { return *userNullFlag_; }

	virtual CppTypes type( void ) const = 0;

	//  operators for evaluating condition predicates
	virtual bool operator == ( const BigintValue& ) const = 0;
	virtual bool operator == ( const BinaryValue& ) const = 0;
	virtual bool operator == ( const BitValue& ) const = 0;
	virtual bool operator == ( const CharValue& ) const = 0;
	virtual bool operator == ( const CharUCValue& ) const = 0;
	virtual bool operator == ( const DateValue& ) const = 0;
	virtual bool operator == ( const DecimalValue& ) const = 0;
	virtual bool operator == ( const FloatValue& ) const = 0;
	virtual bool operator == ( const IntegerValue& ) const = 0;
	virtual bool operator == ( const LongvarbinaryValue& ) const = 0;
	virtual bool operator == ( const LongvarcharValue& ) const = 0;
	virtual bool operator == ( const RealValue& ) const = 0;
	virtual bool operator == ( const SmallintValue& ) const = 0;
	virtual bool operator == ( const TimeValue& ) const = 0;
	virtual bool operator == ( const TimestampValue& ) const = 0;
	virtual bool operator == ( const TinyintValue& ) const = 0;
	virtual bool operator == ( const VarbinaryValue& ) const = 0;
	virtual bool operator == ( const VarcharValue& ) const = 0;

	virtual bool operator > ( const BigintValue& ) const = 0;
	virtual bool operator > ( const BinaryValue& ) const = 0;
	virtual bool operator > ( const BitValue& ) const = 0;
	virtual bool operator > ( const CharValue& ) const = 0;
	virtual bool operator > ( const CharUCValue& ) const = 0;
	virtual bool operator > ( const DateValue& ) const = 0;
	virtual bool operator > ( const DecimalValue& ) const = 0;
	virtual bool operator > ( const FloatValue& ) const = 0;
	virtual bool operator > ( const IntegerValue& ) const = 0;
	virtual bool operator > ( const LongvarbinaryValue& ) const = 0;
	virtual bool operator > ( const LongvarcharValue& ) const = 0;
	virtual bool operator > ( const RealValue& ) const = 0;
	virtual bool operator > ( const SmallintValue& ) const = 0;
	virtual bool operator > ( const TimeValue& ) const = 0;
	virtual bool operator > ( const TimestampValue& ) const = 0;
	virtual bool operator > ( const TinyintValue& ) const = 0;
	virtual bool operator > ( const VarbinaryValue& ) const = 0;
	virtual bool operator > ( const VarcharValue& ) const = 0;

	virtual bool operator >= ( const BigintValue& ) const = 0;
	virtual bool operator >= ( const BinaryValue& ) const = 0;
	virtual bool operator >= ( const BitValue& ) const = 0;
	virtual bool operator >= ( const CharValue& ) const = 0;
	virtual bool operator >= ( const CharUCValue& ) const = 0;
	virtual bool operator >= ( const DateValue& ) const = 0;
	virtual bool operator >= ( const DecimalValue& ) const = 0;
	virtual bool operator >= ( const FloatValue& ) const = 0;
	virtual bool operator >= ( const IntegerValue& ) const = 0;
	virtual bool operator >= ( const LongvarbinaryValue& ) const = 0;
	virtual bool operator >= ( const LongvarcharValue& ) const = 0;
	virtual bool operator >= ( const RealValue& ) const = 0;
	virtual bool operator >= ( const SmallintValue& ) const = 0;
	virtual bool operator >= ( const TimeValue& ) const = 0;
	virtual bool operator >= ( const TimestampValue& ) const = 0;
	virtual bool operator >= ( const TinyintValue& ) const = 0;
	virtual bool operator >= ( const VarbinaryValue& ) const = 0;
	virtual bool operator >= ( const VarcharValue& ) const = 0;

	virtual bool operator < ( const BigintValue& ) const = 0;
	virtual bool operator < ( const BinaryValue& ) const = 0;
	virtual bool operator < ( const BitValue& ) const = 0;
	virtual bool operator < ( const CharValue& ) const = 0;
	virtual bool operator < ( const CharUCValue& ) const = 0;
	virtual bool operator < ( const DateValue& ) const = 0;
	virtual bool operator < ( const DecimalValue& ) const = 0;
	virtual bool operator < ( const FloatValue& ) const = 0;
	virtual bool operator < ( const IntegerValue& ) const = 0;
	virtual bool operator < ( const LongvarbinaryValue& ) const = 0;
	virtual bool operator < ( const LongvarcharValue& ) const = 0;
	virtual bool operator < ( const RealValue& ) const = 0;
	virtual bool operator < ( const SmallintValue& ) const = 0;
	virtual bool operator < ( const TimeValue& ) const = 0;
	virtual bool operator < ( const TimestampValue& ) const = 0;
	virtual bool operator < ( const TinyintValue& ) const = 0;
	virtual bool operator < ( const VarbinaryValue& ) const = 0;
	virtual bool operator < ( const VarcharValue& ) const = 0;

	virtual bool operator <= ( const BigintValue& ) const = 0;
	virtual bool operator <= ( const BinaryValue& ) const = 0;
	virtual bool operator <= ( const BitValue& ) const = 0;
	virtual bool operator <= ( const CharValue& ) const = 0;
	virtual bool operator <= ( const CharUCValue& ) const = 0;
	virtual bool operator <= ( const DateValue& ) const = 0;
	virtual bool operator <= ( const DecimalValue& ) const = 0;
	virtual bool operator <= ( const FloatValue& ) const = 0;
	virtual bool operator <= ( const IntegerValue& ) const = 0;
	virtual bool operator <= ( const LongvarbinaryValue& ) const = 0;
	virtual bool operator <= ( const LongvarcharValue& ) const = 0;
	virtual bool operator <= ( const RealValue& ) const = 0;
	virtual bool operator <= ( const SmallintValue& ) const = 0;
	virtual bool operator <= ( const TimeValue& ) const = 0;
	virtual bool operator <= ( const TimestampValue& ) const = 0;
	virtual bool operator <= ( const TinyintValue& ) const = 0;
	virtual bool operator <= ( const VarbinaryValue& ) const = 0;
	virtual bool operator <= ( const VarcharValue& ) const = 0;

	virtual void operator << ( BigintValue& ) = 0;
	virtual void operator >> ( BigintValue& ) = 0;

	virtual void operator << ( BinaryValue& ) = 0;
	virtual void operator >> ( BinaryValue& ) = 0;

	virtual void operator << ( BitValue& ) = 0;
	virtual void operator >> ( BitValue& ) = 0;

	virtual void operator << ( CharValue& ) = 0;
	virtual void operator >> ( CharValue& ) = 0;

	virtual void operator << ( CharUCValue& ) = 0;
	virtual void operator >> ( CharUCValue& ) = 0;

	virtual void operator << ( DateValue& ) = 0;
	virtual void operator >> ( DateValue& ) = 0;

	virtual void operator << ( DecimalValue& ) = 0;
	virtual void operator >> ( DecimalValue& ) = 0;

	virtual void operator << ( FloatValue& ) = 0;
	virtual void operator >> ( FloatValue& ) = 0;

	virtual void operator << ( IntegerValue& ) = 0;
	virtual void operator >> ( IntegerValue& ) = 0;

	virtual void operator << ( LongvarbinaryValue& ) = 0;
	virtual void operator >> ( LongvarbinaryValue& ) = 0;

	virtual void operator << ( LongvarcharValue& ) = 0;
	virtual void operator >> ( LongvarcharValue& ) = 0;

	virtual void operator << ( RealValue& ) = 0;
	virtual void operator >> ( RealValue& ) = 0;

	virtual void operator << ( SmallintValue& ) = 0;
	virtual void operator >> ( SmallintValue& ) = 0;

	virtual void operator << ( TimeValue& ) = 0;
	virtual void operator >> ( TimeValue& ) = 0;

	virtual void operator << ( TimestampValue& ) = 0;
	virtual void operator >> ( TimestampValue& ) = 0;

	virtual void operator << ( TinyintValue& ) = 0;
	virtual void operator >> ( TinyintValue& ) = 0;

	virtual void operator << ( VarbinaryValue& ) = 0;
	virtual void operator >> ( VarbinaryValue& ) = 0;

	virtual void operator << ( VarcharValue& ) = 0;
	virtual void operator >> ( VarcharValue& ) = 0;
};

typedef BoundColumn *pBoundColumn;


class BoundColumnBool : public BoundColumn
{
	bool *userData_;

public :

	BoundColumnBool( AbstractColumnDescriptor* );
	BoundColumnBool( const BoundColumnBool& );
	virtual ~BoundColumnBool( void );

	void userData( bool& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_BOOL; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnChar : public BoundColumn
{
	NC *userData_;

public :

	BoundColumnChar( AbstractColumnDescriptor* );
	BoundColumnChar( const BoundColumnChar& );
	virtual ~BoundColumnChar( void );

	void userData( NC& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_CHAR; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnUnsignedChar : public BoundColumn
{
	UC *userData_;

public :

	BoundColumnUnsignedChar( AbstractColumnDescriptor* );
	BoundColumnUnsignedChar( const BoundColumnUnsignedChar& );
	virtual ~BoundColumnUnsignedChar( void );

	void userData( UC& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_UNSIGNED_CHAR; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnShort : public BoundColumn
{
	S *userData_;

public :

	BoundColumnShort( AbstractColumnDescriptor* );
	BoundColumnShort( const BoundColumnShort& );
	virtual ~BoundColumnShort( void );

	void userData( S& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_SHORT; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnUnsignedShort : public BoundColumn
{
	US *userData_;

public :

	BoundColumnUnsignedShort( AbstractColumnDescriptor* );
	BoundColumnUnsignedShort( const BoundColumnUnsignedShort& );
	virtual ~BoundColumnUnsignedShort( void );

	void userData( US& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_UNSIGNED_SHORT; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnInt : public BoundColumn
{
	NI *userData_;

public :

	BoundColumnInt( AbstractColumnDescriptor* );
	BoundColumnInt( const BoundColumnInt& );
	virtual ~BoundColumnInt( void );

	void userData( NI& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_INT; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnUnsignedInt : public BoundColumn
{
	UNI *userData_;

public :

	BoundColumnUnsignedInt( AbstractColumnDescriptor* );
	BoundColumnUnsignedInt( const BoundColumnUnsignedInt& );
	virtual ~BoundColumnUnsignedInt( void );

	void userData( UNI& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_UNSIGNED_INT; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnLong : public BoundColumn
{
	L *userData_;

public :

	BoundColumnLong( AbstractColumnDescriptor* );
	BoundColumnLong( const BoundColumnLong& );
	virtual ~BoundColumnLong( void );

	void userData( L& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_LONG; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnUnsignedLong : public BoundColumn
{
	UL *userData_;

public :

	BoundColumnUnsignedLong( AbstractColumnDescriptor* );
	BoundColumnUnsignedLong( const BoundColumnUnsignedLong& );
	virtual ~BoundColumnUnsignedLong( void );

	void userData( UL& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_UNSIGNED_LONG; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnFloat : public BoundColumn
{
	F *userData_;

public :

	BoundColumnFloat( AbstractColumnDescriptor* );
	BoundColumnFloat( const BoundColumnFloat& );
	virtual ~BoundColumnFloat( void );

	void userData( F& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_FLOAT; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnDouble : public BoundColumn
{
	D *userData_;

public :

	BoundColumnDouble( AbstractColumnDescriptor* );
	BoundColumnDouble( const BoundColumnDouble& );
	virtual ~BoundColumnDouble( void );

	void userData( D& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_DOUBLE; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnPChar : public BoundColumn
{
	bool freeable_;
	UL *length_;
	NC **userData_;

public :

	BoundColumnPChar( AbstractColumnDescriptor*, bool /*freeable*/ );
	BoundColumnPChar( const BoundColumnPChar&, bool /*freeable*/ );
	virtual ~BoundColumnPChar( void );

	void length( UL& len ) { length_ = &len; }
	void userData( NC*& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_PCHAR; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnPCharShort : public BoundColumn
{
	bool freeable_;
	UC *length_;
	NC **userData_;

public :

	BoundColumnPCharShort( AbstractColumnDescriptor*, bool /*freeable*/ );
	BoundColumnPCharShort( const BoundColumnPCharShort&, bool /*freeable*/ );
	virtual ~BoundColumnPCharShort( void );

	void length( UC& len ) { length_ = &len; }
	void userData( NC*& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_PCHAR_SHORT; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnPUChar : public BoundColumn
{
	bool freeable_;
	UL *length_;
	UC **userData_;

public :

	BoundColumnPUChar( AbstractColumnDescriptor*, bool /*freeable*/ );
	BoundColumnPUChar( const BoundColumnPUChar&, bool /*freeable*/  );
	virtual ~BoundColumnPUChar( void );

	void length( UL& l ) { length_ = &l; }
	void userData( UC*& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_PUCHAR; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnPUCharShort : public BoundColumn
{
	bool freeable_;
	UC *length_;
	UC **userData_;

public :

	BoundColumnPUCharShort( AbstractColumnDescriptor*, bool /*freeable*/ );
	BoundColumnPUCharShort( const BoundColumnPUCharShort&, bool /*freeable*/  );
	virtual ~BoundColumnPUCharShort( void );

	void length( UC& l ) { length_ = &l; }
	void userData( UC*& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_PUCHAR_SHORT; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnString : public BoundColumn
{
	CqlString *userData_;

public :

	BoundColumnString( AbstractColumnDescriptor* );
	BoundColumnString( const BoundColumnString& );
	virtual ~BoundColumnString( void );

	void userData( CqlString& s ) { userData_ = &s; }

	CppTypes type( void ) const { return CPP_STRING; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnDate : public BoundColumn
{
	DateValue *userData_;

public :

	BoundColumnDate( AbstractColumnDescriptor* );
	BoundColumnDate( const BoundColumnDate& );
	virtual ~BoundColumnDate( void );

	void userData( DateValue& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_DATE; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnTime : public BoundColumn
{
	TimeValue *userData_;

public :

	BoundColumnTime( AbstractColumnDescriptor* );
	BoundColumnTime( const BoundColumnTime& );
	virtual ~BoundColumnTime( void );

	void userData( TimeValue& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_TIME; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnTimestamp : public BoundColumn
{
	TimestampValue *userData_;

public :

	BoundColumnTimestamp( AbstractColumnDescriptor* );
	BoundColumnTimestamp( const BoundColumnTimestamp& );
	virtual ~BoundColumnTimestamp( void );

	void userData( TimestampValue& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_TIMESTAMP; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnBigint : public BoundColumn
{
	BigintValue *userData_;

public :

	BoundColumnBigint( AbstractColumnDescriptor* );
	BoundColumnBigint( const BoundColumnBigint& );
	virtual ~BoundColumnBigint( void );

	void userData( BigintValue& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_BIGINT; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


class BoundColumnDecimal : public BoundColumn
{
	DecimalValue *userData_;

public :

	BoundColumnDecimal( AbstractColumnDescriptor* );
	BoundColumnDecimal( const BoundColumnDecimal& );
	virtual ~BoundColumnDecimal( void );

	void userData( DecimalValue& ud ) { userData_ = &ud; }

	CppTypes type( void ) const { return CPP_DECIMAL; }

	bool operator == ( const BigintValue& ) const;
	bool operator == ( const BinaryValue& ) const;
	bool operator == ( const BitValue& ) const;
	bool operator == ( const CharValue& ) const;
	bool operator == ( const CharUCValue& ) const;
	bool operator == ( const DateValue& ) const;
	bool operator == ( const DecimalValue& ) const;
	bool operator == ( const FloatValue& ) const;
	bool operator == ( const IntegerValue& ) const;
	bool operator == ( const LongvarbinaryValue& ) const;
	bool operator == ( const LongvarcharValue& ) const;
	bool operator == ( const RealValue& ) const;
	bool operator == ( const SmallintValue& ) const;
	bool operator == ( const TimeValue& ) const;
	bool operator == ( const TimestampValue& ) const;
	bool operator == ( const TinyintValue& ) const;
	bool operator == ( const VarbinaryValue& ) const;
	bool operator == ( const VarcharValue& ) const;

	bool operator > ( const BigintValue& ) const;
	bool operator > ( const BinaryValue& ) const;
	bool operator > ( const BitValue& ) const;
	bool operator > ( const CharValue& ) const;
	bool operator > ( const CharUCValue& ) const;
	bool operator > ( const DateValue& ) const;
	bool operator > ( const DecimalValue& ) const;
	bool operator > ( const FloatValue& ) const;
	bool operator > ( const IntegerValue& ) const;
	bool operator > ( const LongvarbinaryValue& ) const;
	bool operator > ( const LongvarcharValue& ) const;
	bool operator > ( const RealValue& ) const;
	bool operator > ( const SmallintValue& ) const;
	bool operator > ( const TimeValue& ) const;
	bool operator > ( const TimestampValue& ) const;
	bool operator > ( const TinyintValue& ) const;
	bool operator > ( const VarbinaryValue& ) const;
	bool operator > ( const VarcharValue& ) const;

	bool operator >= ( const BigintValue& ) const;
	bool operator >= ( const BinaryValue& ) const;
	bool operator >= ( const BitValue& ) const;
	bool operator >= ( const CharValue& ) const;
	bool operator >= ( const CharUCValue& ) const;
	bool operator >= ( const DateValue& ) const;
	bool operator >= ( const DecimalValue& ) const;
	bool operator >= ( const FloatValue& ) const;
	bool operator >= ( const IntegerValue& ) const;
	bool operator >= ( const LongvarbinaryValue& ) const;
	bool operator >= ( const LongvarcharValue& ) const;
	bool operator >= ( const RealValue& ) const;
	bool operator >= ( const SmallintValue& ) const;
	bool operator >= ( const TimeValue& ) const;
	bool operator >= ( const TimestampValue& ) const;
	bool operator >= ( const TinyintValue& ) const;
	bool operator >= ( const VarbinaryValue& ) const;
	bool operator >= ( const VarcharValue& ) const;

	bool operator < ( const BigintValue& ) const;
	bool operator < ( const BinaryValue& ) const;
	bool operator < ( const BitValue& ) const;
	bool operator < ( const CharValue& ) const;
	bool operator < ( const CharUCValue& ) const;
	bool operator < ( const DateValue& ) const;
	bool operator < ( const DecimalValue& ) const;
	bool operator < ( const FloatValue& ) const;
	bool operator < ( const IntegerValue& ) const;
	bool operator < ( const LongvarbinaryValue& ) const;
	bool operator < ( const LongvarcharValue& ) const;
	bool operator < ( const RealValue& ) const;
	bool operator < ( const SmallintValue& ) const;
	bool operator < ( const TimeValue& ) const;
	bool operator < ( const TimestampValue& ) const;
	bool operator < ( const TinyintValue& ) const;
	bool operator < ( const VarbinaryValue& ) const;
	bool operator < ( const VarcharValue& ) const;

	bool operator <= ( const BigintValue& ) const;
	bool operator <= ( const BinaryValue& ) const;
	bool operator <= ( const BitValue& ) const;
	bool operator <= ( const CharValue& ) const;
	bool operator <= ( const CharUCValue& ) const;
	bool operator <= ( const DateValue& ) const;
	bool operator <= ( const DecimalValue& ) const;
	bool operator <= ( const FloatValue& ) const;
	bool operator <= ( const IntegerValue& ) const;
	bool operator <= ( const LongvarbinaryValue& ) const;
	bool operator <= ( const LongvarcharValue& ) const;
	bool operator <= ( const RealValue& ) const;
	bool operator <= ( const SmallintValue& ) const;
	bool operator <= ( const TimeValue& ) const;
	bool operator <= ( const TimestampValue& ) const;
	bool operator <= ( const TinyintValue& ) const;
	bool operator <= ( const VarbinaryValue& ) const;
	bool operator <= ( const VarcharValue& ) const;

	void operator << ( BigintValue& );
	void operator >> ( BigintValue& );

	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );

	void operator << ( BitValue& );
	void operator >> ( BitValue& );

	void operator << ( CharValue& );
	void operator >> ( CharValue& );

	void operator << ( CharUCValue& );
	void operator >> ( CharUCValue& );

	void operator << ( DateValue& );
	void operator >> ( DateValue& );

	void operator << ( DecimalValue& );
	void operator >> ( DecimalValue& );

	void operator << ( FloatValue& );
	void operator >> ( FloatValue& );

	void operator << ( IntegerValue& );
	void operator >> ( IntegerValue& );

	void operator << ( LongvarbinaryValue& );
	void operator >> ( LongvarbinaryValue& );

	void operator << ( LongvarcharValue& );
	void operator >> ( LongvarcharValue& );

	void operator << ( RealValue& );
	void operator >> ( RealValue& );

	void operator << ( SmallintValue& );
	void operator >> ( SmallintValue& );

	void operator << ( TimeValue& );
	void operator >> ( TimeValue& );

	void operator << ( TimestampValue& );
	void operator >> ( TimestampValue& );

	void operator << ( TinyintValue& );
	void operator >> ( TinyintValue& );

	void operator << ( VarbinaryValue& );
	void operator >> ( VarbinaryValue& );

	void operator << ( VarcharValue& );
	void operator >> ( VarcharValue& );
};


#endif  //  __BoundColumn_h
