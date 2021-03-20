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


#ifndef __AbstractType_h
#define __AbstractType_h


class AbstractType : public CqlConstants, public ErrorConstants, public ExceptionCodes
{

public :

	enum RoundType
	{
		ROUND_NEAREST,
		ROUND_UP,
		ROUND_DOWN
	};

	AbstractType( void ) { }
	virtual ~AbstractType( void ) { }

	static AbstractType* createObject( CqlColumnTypes /*type*/ );

	//  pure virtual operators
	virtual AbstractType& operator = ( const AbstractType& ) = 0;
	virtual AbstractType& operator = ( pUC ) = 0;

	virtual AbstractType& operator += ( const AbstractType& ) = 0;
	virtual AbstractType& operator -= ( const AbstractType& ) = 0;
	virtual AbstractType& operator *= ( const AbstractType& ) = 0;
	virtual AbstractType& operator /= ( const AbstractType& ) = 0;
	virtual AbstractType& operator - ( void ) = 0;

	virtual void operator << ( BoundColumn *bc ) = 0;
	virtual void operator >> ( BoundColumn *bc ) = 0;

	virtual bool operator ! ( void ) const = 0;

	virtual bool operator >= ( AbstractType& ) = 0;
	virtual bool operator > ( AbstractType& ) = 0;
	virtual bool operator <= ( AbstractType& ) = 0;
	virtual bool operator < ( AbstractType& ) = 0;
	virtual bool operator == ( AbstractType& ) = 0;
	virtual bool operator != ( AbstractType& ) = 0;

	//  pure virtual methods
	virtual AbstractValue& avalue( void ) = 0;
	virtual void absoluteValue( void ) = 0;
	virtual void clearNullflag( void ) = 0;
	virtual CqlColumnTypes& columnType( void ) = 0;
	virtual US dictionaryLength( void ) = 0;
	virtual void encode( CqlString& /*output*/,  bool /*spacePadding*/ = true ) = 0;
	virtual bool& nullflag( void ) = 0;
	virtual void readDictionaryInformation( TempBuffer& ) = 0;
	virtual void setNullflag( void ) = 0;
	virtual void writeDictionaryInformation( TempBuffer& ) = 0;
};

typedef AbstractType *pAbstractType;


template< class T >
class ConcreteType : public AbstractType
{
	T instance_;

public :

	ConcreteType( void ) : AbstractType(), instance_(){ }
	ConcreteType( T *other ) : AbstractType(), instance_( *other ) { }
	ConcreteType( const CqlColumnTypes& _type ) : AbstractType(), instance_( _type ) { }
	ConcreteType( const T value ) : AbstractType(), instance_( value ) { }
	ConcreteType( const NC c ) : AbstractType(), instance_( c ) { }
	ConcreteType( const D d ) : AbstractType(), instance_( d ) { }
	ConcreteType( const F f ) : AbstractType(), instance_( f ) { }
	ConcreteType( const NI i ) : AbstractType(), instance_( i ) { }
	ConcreteType( const L l ) : AbstractType(), instance_( l ) { }
	ConcreteType( const S s ) : AbstractType(), instance_( s ) { }
	ConcreteType( const UC *s, const UL len ) : AbstractType(), instance_( s, len ) { }
	ConcreteType( const NC *s ) : AbstractType(), instance_( s ) { }

	//  This is a reference so that the constructor can advance it beyond itself.  Used
	//  for segmented keys so that pUC points to the key for the next segment after
	//  initialization of the current segment.
	ConcreteType( pUC& val ) : AbstractType(), instance_( val ) { }
	ConcreteType( AbstractDatabaseHandle&, pUC, UNI = 0 );
	ConcreteType( AbstractDatabaseHandle&, CqlString& );
	ConcreteType( AbstractDatabaseHandle&, AbstractType* );
	ConcreteType( AbstractDatabaseHandle&, NI val );
	ConcreteType( AbstractDatabaseHandle&, pNC, pUNI );

	virtual ~ConcreteType( void ) { }

	//  stream operators
	void operator << ( pUC& buf ) { instance_ << buf; }
	void operator >> ( pUC& buf ) { instance_ >> buf; }
	void operator << ( BinaryValue& bv ) { instance_ << bv; }
	void operator >> ( BinaryValue& bv ) { instance_ >> bv; }
	void operator << ( BoundColumn *bc ) { instance_ << bc; }
	void operator >> ( BoundColumn *bc ) { instance_ >> bc; }
	void operator << ( TempBuffer& tb ) { instance_ << tb; }
	void operator >> ( TempBuffer& tb ) { instance_ >> tb; }

	//  assignment
	ConcreteType& operator = ( const ConcreteType& other )
	{
		instance_ = other.instance_;
		return *this;
	}

	AbstractType& operator = ( pUC data )
	{
		instance_ = T( data );
		return *this;
	}

	AbstractType& operator = ( const AbstractType& at )
	{
		instance_ = const_cast< AbstractType& >( at ).avalue();
		return *this;
	}

	//
	//  relational operators
	//
	bool operator == ( ConcreteType& other )
	{
		return instance_ == other.instance_;
	}

	bool operator == ( BoundColumn *bc )
	{
		return instance_ == bc;
	}

	bool operator > ( BoundColumn *bc )
	{
		return instance_ > bc;
	}

	bool operator >= ( BoundColumn *bc )
	{
		return instance_ >= bc;
	}

	bool operator < ( BoundColumn *bc )
	{
		return instance_ < bc;
	}

	bool operator <= ( BoundColumn *bc )
	{
		return instance_ <= bc;
	}

	bool operator < ( ConcreteType& other )
	{
		return instance_ < other.instance_;
	}

	bool operator <= ( ConcreteType& other )
	{
		return instance_ <= other.instance_;
	}

	bool operator > ( ConcreteType& other )
	{
		return instance_ > other.instance_;
	}

	bool operator > ( AbstractType& other )
	{
		return avalue() > other.avalue();
	}

	bool operator >= ( AbstractType& other )
	{
		return avalue() >= other.avalue();
	}

	bool operator < ( AbstractType& other )
	{
		return avalue() < other.avalue();
	}

	bool operator <= ( AbstractType& other )
	{
		return avalue() <= other.avalue();
	}

	bool operator == ( AbstractType& other )
	{
		return avalue() == other.avalue();
	}

	bool operator != ( AbstractType& other )
	{
		return avalue() != other.avalue();
	}

	bool operator >= ( ConcreteType& other )
	{
		return instance_ >= other.instance_;
	}

	bool operator !( void ) const
	{
		return !instance_;
	}

	//
	//  Arithmetic operators
	//
	ConcreteType operator /=( ConcreteType& other )
	{
		return ConcreteType( instance_ /= other.instance_ );
	}

	AbstractType& operator += ( const AbstractType& cother )
	{
		AbstractType& other = const_cast< AbstractType& >( cother );
		avalue() += other.avalue();
		return *this;
	}
	
	AbstractType& operator -= ( const AbstractType& cother )
	{
		AbstractType& other = const_cast< AbstractType& >( cother );
		avalue() -= other.avalue();
		return *this;
	}
	
	AbstractType& operator *= ( const AbstractType& cother )
	{
		AbstractType& other = const_cast< AbstractType& >( cother );
		avalue() *= other.avalue();
		return *this;
	}

	AbstractType& operator /= ( const AbstractType& cother )
	{
		AbstractType& other = const_cast< AbstractType& >( cother );
		avalue() /= other.avalue();
		return *this;
	}

	AbstractType& operator - ( void )
	{
		instance_.operator-();
		return *this;
	}

	void absoluteValue( void )
	{
		instance_.absoluteValue();
	}

	const CqlString asString( NI spacePadding = CQL_NO )
	{
		return instance_.asString( spacePadding );
	}

	AbstractValue& avalue( void ) { return instance_.value(); }

	void clearNullflag( void ) { instance_.clearNullflag(); }

	CqlColumnTypes& columnType( void ) { return instance_.columnType(); }

	void columnType( CqlColumnTypes& t )
	{
		instance_.columnType( t );
	}

	CompareResult compare( const ConcreteType& v ) const;

	US dictionaryLength( void )
	{
		return instance_.dictionaryLength();
	}

	void encode( CqlString& output, bool spacePadding = true )
	{
		instance_.encode( output, spacePadding );
	}

	void expand( UL newLength )
	{
		instance_.expand( newLength );
	}

	T& instance( void ) { return instance_; }

	UL length( void ) { return instance_.length(); }

	void readDictionaryInformation( TempBuffer& buffer )
	{
		instance_.readDictionaryInformation( buffer );
	}

	void releaseMemory( void )
	{
		instance_.releaseMemory();
	}

	void setNullflag( void ) { instance_.setNullflag(); }

	UL streamLength( void ) const { return instance_.streamLength(); }

	CqlColumnType type( void ) { return instance_.type(); }

	bool& nullflag( void ) { return instance_.nullflag(); }

	void writeDictionaryInformation( TempBuffer& buffer )
	{
		instance_.writeDictionaryInformation( buffer );
	}
};


typedef ConcreteType< PrimitiveBigint > Cql_Bigint;
typedef ConcreteType< PrimitiveBinary > Cql_Binary;
typedef ConcreteType< PrimitiveBit > Cql_Bit;
typedef ConcreteType< PrimitiveChar > Cql_Char;
typedef ConcreteType< PrimitiveCharUC > Cql_CharUC;
typedef ConcreteType< PrimitiveDate > Cql_Date;
typedef ConcreteType< PrimitiveDecimal > Cql_Decimal;
typedef ConcreteType< PrimitiveFloat > Cql_Float;
typedef ConcreteType< PrimitiveInteger > Cql_Integer;
typedef ConcreteType< PrimitiveLongvarbinary > Cql_Longvarbinary;
typedef ConcreteType< PrimitiveLongvarchar > Cql_Longvarchar;
typedef ConcreteType< PrimitiveReal > Cql_Real;
typedef ConcreteType< PrimitiveSmallint > Cql_Smallint;
typedef ConcreteType< PrimitiveTime > Cql_Time;
typedef ConcreteType< PrimitiveTimestamp > Cql_Timestamp;
typedef ConcreteType< PrimitiveTinyint > Cql_Tinyint;
typedef ConcreteType< PrimitiveVarbinary > Cql_Varbinary;
typedef ConcreteType< PrimitiveVarchar > Cql_Varchar;


#endif  //  __AbstractType_h
