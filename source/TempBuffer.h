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


#ifndef __TempBuffer_h
#define __TempBuffer_h


class TempBuffer : public CqlConstants, public InstructionConstants, public FunctionConstants, public PredicateTypes, public SetComparisonConstants
{
	UC *buffer_;
	UC *bufferBase_;  //  Points to beginning of data area, after length
	CopyStates copyState_;
	SqlHandle *dbsql_;
	const AbstractDatabaseHandle& hAdb_;
	LengthStates lengthState_;
	UL *size_;
	UL streamCopyLength_;

protected :

	pUC currentPosition_;

public :

	TempBuffer( AbstractDatabaseHandle&, SqlHandle* = 0 );
	TempBuffer( AbstractDatabaseHandle&, const UL length, SqlHandle* = 0 );
	virtual ~TempBuffer( void );

	TempBuffer& operator = ( TempBuffer& );

	TempBuffer& operator << ( const LengthStates );
	TempBuffer& operator << ( const CopyStates );

	TempBuffer& operator << ( const CqlString& /*value*/ );
	TempBuffer& operator >> ( CqlString& /*value*/ ); 
	TempBuffer& operator << ( const D /*value*/ );
	TempBuffer& operator >> ( D& /*value*/ );
	TempBuffer& operator << ( const F /*value*/ );
	TempBuffer& operator >> ( F& /*value*/ ); 
	TempBuffer& operator << ( const L /*value*/ );
	TempBuffer& operator >> ( L& /*value*/ ); 
	TempBuffer& operator << ( const NI /*value*/ );
	TempBuffer& operator >> ( NI& /*value*/ );
	TempBuffer& operator << ( const S /*value*/ );
	TempBuffer& operator >> ( S& /*value*/ ); 
	TempBuffer& operator << ( const SC /*value*/ );
	TempBuffer& operator >> ( SC& /*value*/ ); 
	TempBuffer& operator << ( const UC /*value*/ );
	TempBuffer& operator >> ( UC& /*value*/ );
	TempBuffer& operator << ( const UNI /*value*/ );
	TempBuffer& operator >> ( UNI& /*value*/ );
	TempBuffer& operator << ( const UL /*value*/ );
	TempBuffer& operator >> ( UL& /*value*/ );
	TempBuffer& operator << ( const US /*value*/ );
	TempBuffer& operator >> ( US& /*value*/ );
#ifndef CQL_BOOL_IS_INT
	TempBuffer& operator << ( const bool /*value*/ );
	TempBuffer& operator >> ( bool& /*value*/ );
#endif
	TempBuffer& operator << ( const SignValues /*value*/ );
	TempBuffer& operator >> ( SignValues& /*value*/ );

	TempBuffer& operator << ( const AbstractValue* );
	TempBuffer& operator >> ( AbstractValue*& );

	//  stream methods for SQL primitive types
	TempBuffer& operator << ( const BigintValue& );
	TempBuffer& operator >> ( BigintValue& );
	TempBuffer& operator << ( const PrimitiveBigint& );
	TempBuffer& operator >> ( PrimitiveBigint& );
	TempBuffer& operator << ( const Cql_Bigint& );
	TempBuffer& operator >> ( Cql_Bigint& );

	TempBuffer& operator << ( const BinaryValue& );
	TempBuffer& operator >> ( BinaryValue& );
	TempBuffer& operator << ( const PrimitiveBinary& );
	TempBuffer& operator >> ( PrimitiveBinary& );
	TempBuffer& operator << ( const Cql_Binary& );
	TempBuffer& operator >> ( Cql_Binary& );

	TempBuffer& operator << ( const BitValue& );
	TempBuffer& operator >> ( BitValue& );
	TempBuffer& operator << ( const PrimitiveBit& );
	TempBuffer& operator >> ( PrimitiveBit& );
	TempBuffer& operator << ( const Cql_Bit& );
	TempBuffer& operator >> ( Cql_Bit& );

	TempBuffer& operator << ( const CharValue& );
	TempBuffer& operator >> ( CharValue& );
	TempBuffer& operator << ( const PrimitiveChar& );
	TempBuffer& operator >> ( PrimitiveChar& );
	TempBuffer& operator << ( const Cql_Char& );
	TempBuffer& operator >> ( Cql_Char& );

	TempBuffer& operator << ( const CharUCValue& );
	TempBuffer& operator >> ( CharUCValue& );
	TempBuffer& operator << ( const PrimitiveCharUC& );
	TempBuffer& operator >> ( PrimitiveCharUC& );
	TempBuffer& operator << ( const Cql_CharUC& );
	TempBuffer& operator >> ( Cql_CharUC& );

	TempBuffer& operator << ( const DateValue& );
	TempBuffer& operator >> ( DateValue& );
	TempBuffer& operator << ( const PrimitiveDate& );
	TempBuffer& operator >> ( PrimitiveDate& );
	TempBuffer& operator << ( const Cql_Date& );
	TempBuffer& operator >> ( Cql_Date& );

	TempBuffer& operator << ( const DecimalValue& );
	TempBuffer& operator >> ( DecimalValue& );
	TempBuffer& operator << ( const PrimitiveDecimal& );
	TempBuffer& operator >> ( PrimitiveDecimal& );
	TempBuffer& operator << ( const Cql_Decimal& );
	TempBuffer& operator >> ( Cql_Decimal& );

	TempBuffer& operator << ( const FloatValue& );
	TempBuffer& operator >> ( FloatValue& );
	TempBuffer& operator << ( const PrimitiveFloat& );
	TempBuffer& operator >> ( PrimitiveFloat& );
	TempBuffer& operator << ( const Cql_Float& );
	TempBuffer& operator >> ( Cql_Float& );

	TempBuffer& operator << ( const IntegerValue& );
	TempBuffer& operator >> ( IntegerValue& );
	TempBuffer& operator << ( const PrimitiveInteger& );
	TempBuffer& operator >> ( PrimitiveInteger& );
	TempBuffer& operator << ( const Cql_Integer& );
	TempBuffer& operator >> ( Cql_Integer& );

	TempBuffer& operator << ( const LongvarbinaryValue& );
	TempBuffer& operator >> ( LongvarbinaryValue& );
	TempBuffer& operator << ( const PrimitiveLongvarbinary& );
	TempBuffer& operator >> ( PrimitiveLongvarbinary& );
	TempBuffer& operator << ( const Cql_Longvarbinary& );
	TempBuffer& operator >> ( Cql_Longvarbinary& );

	TempBuffer& operator << ( const LongvarcharValue& );
	TempBuffer& operator >> ( LongvarcharValue& );
	TempBuffer& operator << ( const PrimitiveLongvarchar& );
	TempBuffer& operator >> ( PrimitiveLongvarchar& );
	TempBuffer& operator << ( const Cql_Longvarchar& );
	TempBuffer& operator >> ( Cql_Longvarchar& );

	TempBuffer& operator << ( const RealValue& );
	TempBuffer& operator >> ( RealValue& );
	TempBuffer& operator << ( const PrimitiveReal& );
	TempBuffer& operator >> ( PrimitiveReal& );
	TempBuffer& operator << ( const Cql_Real& );
	TempBuffer& operator >> ( Cql_Real& );

	TempBuffer& operator << ( const SmallintValue& );
	TempBuffer& operator >> ( SmallintValue& );
	TempBuffer& operator << ( const PrimitiveSmallint& );
	TempBuffer& operator >> ( PrimitiveSmallint& );
	TempBuffer& operator << ( const Cql_Smallint& );
	TempBuffer& operator >> ( Cql_Smallint& );

	TempBuffer& operator << ( const TimeValue& );
	TempBuffer& operator >> ( TimeValue& );
	TempBuffer& operator << ( const PrimitiveTime& );
	TempBuffer& operator >> ( PrimitiveTime& );
	TempBuffer& operator << ( const Cql_Time& );
	TempBuffer& operator >> ( Cql_Time& );

	TempBuffer& operator << ( const TimestampValue& );
	TempBuffer& operator >> ( TimestampValue& );
	TempBuffer& operator << ( const PrimitiveTimestamp& );
	TempBuffer& operator >> ( PrimitiveTimestamp& );
	TempBuffer& operator << ( const Cql_Timestamp& );
	TempBuffer& operator >> ( Cql_Timestamp& );

	TempBuffer& operator << ( const TinyintValue& );
	TempBuffer& operator >> ( TinyintValue& );
	TempBuffer& operator << ( const PrimitiveTinyint& );
	TempBuffer& operator >> ( PrimitiveTinyint& );
	TempBuffer& operator << ( const Cql_Tinyint& );
	TempBuffer& operator >> ( Cql_Tinyint& );

	TempBuffer& operator << ( const VarbinaryValue& );
	TempBuffer& operator >> ( VarbinaryValue& );
	TempBuffer& operator << ( const PrimitiveVarbinary& );
	TempBuffer& operator >> ( PrimitiveVarbinary& );
	TempBuffer& operator << ( const Cql_Varbinary& );
	TempBuffer& operator >> ( Cql_Varbinary& );

	TempBuffer& operator << ( const VarcharValue& );
	TempBuffer& operator >> ( VarcharValue& );
	TempBuffer& operator << ( const PrimitiveVarchar& );
	TempBuffer& operator >> ( PrimitiveVarchar& );
	TempBuffer& operator << ( const Cql_Varchar& );
	TempBuffer& operator >> ( Cql_Varchar& );

	TempBuffer& operator << ( const CqlColumnTypes& /*type*/ );
	TempBuffer& operator >> ( CqlColumnTypes& /*type*/ );

	TempBuffer& operator << ( const ExceptionCodes /*ecode*/ );
	TempBuffer& operator >> ( ExceptionCodes& /*ecode*/ );

	TempBuffer& operator << ( const NodeElement& /*nodeElement*/ );
	TempBuffer& operator >> ( NodeElement& /*nodeElement*/ );

	TempBuffer& operator << ( const AbstractColumnDescriptor& );

	//  Binary types.
	TempBuffer& operator << ( const UC* );
	TempBuffer& operator >> ( UC* );
	TempBuffer& operator << ( const void* );
	TempBuffer& operator >> ( void* );

	//  Exception types
	TempBuffer& operator << ( const CqlException& /*ex*/ );
	TempBuffer& operator >> ( CqlException& /*ex*/ );

	//  enumerated types
	TempBuffer& operator << ( const AbstractValueType );
	TempBuffer& operator >> ( AbstractValueType& );
	TempBuffer& operator << ( const BinaryOperators );
	TempBuffer& operator >> ( BinaryOperators& );
	TempBuffer& operator << ( const Combinations );
	TempBuffer& operator >> ( Combinations& );
	TempBuffer& operator << ( const ComparisonOperators );
	TempBuffer& operator >> ( ComparisonOperators& );
	TempBuffer& operator << ( const ComparisonModifiers );
	TempBuffer& operator >> ( ComparisonModifiers& );
	TempBuffer& operator << ( const CqlColumnType );
	TempBuffer& operator >> ( CqlColumnType& );
	TempBuffer& operator << ( const Functions );
	TempBuffer& operator >> ( Functions& );
	TempBuffer& operator << ( const LinkTypes );
	TempBuffer& operator >> ( LinkTypes& );
	TempBuffer& operator << ( const OperationCodes );
	TempBuffer& operator >> ( OperationCodes& );
	TempBuffer& operator << ( const PredicateType );
	TempBuffer& operator >> ( PredicateType& );
	TempBuffer& operator << ( const Resolutions );
	TempBuffer& operator >> ( Resolutions& );
	TempBuffer& operator << ( const TertiaryOperators );
	TempBuffer& operator >> ( TertiaryOperators& );
	TempBuffer& operator << ( const UnaryOperators );
	TempBuffer& operator >> ( UnaryOperators& );

	CqlString asString( void );
	pUC buffer( void ) { return buffer_; }
	pUC bufferBase( void ) { return bufferBase_; }
	pUC& bufferRef( void ) { return bufferBase_; }
	UL bufferDepth( void ) { return currentPosition_ - ( buffer_ + 4 ); }
	void copyOut( void *value, UNI size );
	void copyIn( const void *value, UNI size );
	SqlHandle *dbsql( void ) { return dbsql_; }
	AbstractDatabaseHandle& hAdb( void ) { return const_cast< AbstractDatabaseHandle& >( hAdb_ ); }
	void expand( US /*size*/ );
	void initializeCurrentPosition( void );
	UL size( void ) { return *size_; }
	NI setBuffer( UNI bufSize );
};

typedef TempBuffer *pTempBuffer;


#endif  //  __TempBuffer_h
