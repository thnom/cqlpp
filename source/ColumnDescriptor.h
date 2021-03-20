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


#ifndef __ColumnDescriptor_h
#define __ColumnDescriptor_h


class Record;


class ColumnDescriptor : public AbstractColumnDescriptor
{
	US columnNumber_;
	bool descending_;

public :

	ColumnDescriptor( US /*colNo*/, bool /*descending*/ = false );
	ColumnDescriptor( void );
	virtual ~ColumnDescriptor( void );

	ColumnDescriptor& operator = ( const ColumnDescriptor& );

	US columnNumber( void ) { return columnNumber_; }
	void columnNumber( US no ) { columnNumber_ = no; }
	bool descending( void ) { return descending_; }
	US dictionaryLength( void );
	static ColumnDescriptor *readColumn( DatabaseHandle&, FileManager& );
	void setDescending( void ) { descending_ = true; }
	void write( AbstractDatabaseHandle&, FileManager* );
	void writeDictionaryInformation( TempBuffer& );

	virtual bool operator == ( BoundColumn* ) = 0;
	virtual bool operator != ( BoundColumn* ) = 0;
	virtual bool operator > ( BoundColumn* ) = 0;
	virtual bool operator >= ( BoundColumn* ) = 0;
	virtual bool operator < ( BoundColumn* ) = 0;
	virtual bool operator <= ( BoundColumn* ) = 0;

	virtual void operator << ( pUC& ) = 0;
	virtual void operator >> ( pUC& ) = 0;
	virtual void operator << ( BinaryValue& ) = 0;
	virtual void operator >> ( BinaryValue& ) = 0;
	virtual void operator << ( BoundColumn* ) = 0;
	virtual void operator >> ( BoundColumn* ) = 0;
	virtual void operator << ( TempBuffer& ) = 0;
	virtual void operator >> ( TempBuffer& ) = 0;

	virtual void clearNullflag( void ) = 0;
	virtual CqlConstants::CompareResult compare( pUC& /*key1*/, pUC& /*key2*/, bool /*descending*/ ) = 0;
	virtual CqlColumnTypes& columnType( void ) = 0;
	virtual void columnType( CqlColumnTypes& ) = 0;
	virtual UL copyLength( void ) = 0;
	virtual UL length( void ) = 0;
	virtual void releaseMemory( void ) = 0;
	virtual void setNullflag( void ) = 0;
	virtual UL streamLength( void ) const = 0;
	virtual AbstractType& value( void ) = 0;
};


template< class T >
class ConcreteColumnDescriptor : public ColumnDescriptor
{
	T value_;

public :

	ConcreteColumnDescriptor( US /*colNo*/, bool desc = false );
	ConcreteColumnDescriptor( void );
	virtual ~ConcreteColumnDescriptor( void );

	bool operator == ( BoundColumn* );
	bool operator != ( BoundColumn* );
	bool operator > ( BoundColumn* );
	bool operator >= ( BoundColumn* );
	bool operator < ( BoundColumn* );
	bool operator <= ( BoundColumn* );

	void operator << ( BoundColumn* );
	void operator >> ( BoundColumn* );
	void operator << ( pUC& );
	void operator >> ( pUC& );
	void operator << ( BinaryValue& );
	void operator >> ( BinaryValue& );
	void operator << ( TempBuffer& );
	void operator >> ( TempBuffer& );

	void clearNullflag( void );
	CqlColumnTypes& columnType( void ) { return value_.columnType(); }
	void columnType( CqlColumnTypes& t ) { value_.columnType( t ); }
	CqlConstants::CompareResult compare( pUC& key1, pUC& key2, bool /*descending*/ );
	UL copyLength( void );
	bool isNull( void );
	UL length( void ) { return value_.length(); }
	CqlString name( void ) { return CqlString( "Not available yet" ); }
	bool& nullflag( void );
	US precision( void ) { return 0; }
	void releaseMemory( void ) { value_.releaseMemory(); }
	void setNullflag( void );
	UL streamLength( void ) const { return value_.streamLength(); }
	CqlColumnType type( void ) { return value_.type(); }
	AbstractType& value( void ) { return dynamic_cast< AbstractType& >( value_ ); }
};


typedef ConcreteColumnDescriptor< Cql_Bigint > BigintColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Binary > BinaryColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Char > CharColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_CharUC > CharUCColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Date > DateColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Decimal > DecimalColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Float > FloatColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Integer > IntegerColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Longvarbinary > LongvarbinaryColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Longvarchar > LongvarcharColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Real > RealColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Smallint > SmallintColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Time > TimeColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Timestamp > TimestampColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Tinyint > TinyintColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Varbinary > VarbinaryColumnDescriptor;
typedef ConcreteColumnDescriptor< Cql_Varchar > VarcharColumnDescriptor;


#include "ConcreteColumnDescriptor.h"


#endif  //  __ColumnDescriptor_h
