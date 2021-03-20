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


#include "CqlIsamInclude.h"



//****************************************************************************
//**  This file contains methods to factory various objects.  All objects
//**  whose implementation may vary depending on the back end file system
//**  are placed in this file, to isolate these dependencies.
//****************************************************************************


pAbstractColumnDescriptor AbstractColumnDescriptor::createObject( CqlColumnTypes ctype, US colNo, bool desc )
{
	ColumnDescriptor *column = 0;

	switch( ctype.typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		throw CqlException( "Internal error, bad type", EC_INTERNAL_ERROR, __FILE__, __LINE__, "HY000" );

	case CQL_CHAR :
		column = new CharColumnDescriptor( colNo );
		break;

	case CQL_CHARUC :
		column = new CharUCColumnDescriptor( colNo );
		//column = new CharColumnDescriptor( colNo );
		break;

	case CQL_VARCHAR :
		column = new VarcharColumnDescriptor( colNo );
		break;

	case CQL_DECIMAL :
		column = new DecimalColumnDescriptor( colNo );
		break;

	case CQL_SMALLINT :
		column = new SmallintColumnDescriptor( colNo );
		break;

	case CQL_INTEGER :
		column = new IntegerColumnDescriptor( colNo );
		break;

	case CQL_REAL :
		column = new RealColumnDescriptor( colNo );
		break;

	case CQL_FLOAT :
		column = new FloatColumnDescriptor( colNo );
		break;

	case CQL_LONGVARCHAR :
		column = new LongvarcharColumnDescriptor( colNo );
		break;

	case CQL_TINYINT :
	case CQL_BIT :
		column = new TinyintColumnDescriptor( colNo );
		break;

	case CQL_BIGINT :
		column = new BigintColumnDescriptor( colNo );
		break;

	case CQL_BINARY :
		column = new BinaryColumnDescriptor( colNo );
		break;

	case CQL_VARBINARY :
		column = new VarbinaryColumnDescriptor( colNo );
		break;

	case CQL_LONGVARBINARY :
		column = new LongvarbinaryColumnDescriptor( colNo );
		break;

	case CQL_DATE :
		column = new DateColumnDescriptor( colNo );
		break;

	case CQL_TIME :
		column = new TimeColumnDescriptor( colNo );
		break;

	case CQL_TIMESTAMP :
		column = new TimestampColumnDescriptor( colNo );
		break;
	}

	if( !column )
		throw AbstractObjectCreationException( "Allocation failure", EC_MEMORY_ALLOCATION_FAILURE, __FILE__, __LINE__ );

	if( desc )
		column->setDescending();

	column->columnType( ctype );

	return column;
}


AbstractDatabaseHandle *AbstractDatabaseHandle::createObject( const CqlString& userID, const CqlString& password, const CqlString& initialDirectory )
{
	DatabaseHandle *dh;
	try
	{
		dh = new DatabaseHandle( userID, password, initialDirectory );
	}
	catch( ... )
	{
		throw;
	}

	return static_cast< AbstractDatabaseHandle* >( dh );
}


AbstractEnvironmentHandle *AbstractEnvironmentHandle::createObject( const CqlString& initialDirectory )
{
	EnvironmentHandle *eh;

	eh = new EnvironmentHandle( initialDirectory );
	return dynamic_cast< AbstractEnvironmentHandle* >( eh );
}


AbstractMessage *AbstractMessage::createObject( MessageIdentifier )
{
	return 0;
}


AbstractSegmentDescriptor *AbstractSegmentDescriptor::createObject( const US segmentNo, const SegmentTypes& segmentTypes )
{
	switch( segmentTypes.segmentType() )
	{
	case CQL_ASCENDING :
	case CQL_DESCENDING :
	{
		IndexSegmentDescriptor *isd = new IndexSegmentDescriptor( segmentNo, segmentTypes );
		return dynamic_cast< AbstractSegmentDescriptor* >( isd );
	}
		
	default :
		break;
	}

	throw CqlException( "Internal error, unrecognized segment type.", EC_INTERNAL_ERROR, __FILE__, __LINE__, "HY000" );
#if defined( _MSC_VER ) && _MSC_VER != 1200
 	//  very stupid Microsoft compiler
	return 0;
#endif
}


AbstractTable *AbstractTable::createObject( AbstractDatabaseHandle& adh, TableType tt )
{
	pIsamFile ifile;

	switch( tt )
	{
	case CQL_CQL :
	case CQL_CQL_TEMPORARY :
		ifile = new IsamFile( adh );
		if( !ifile )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		return ifile;

	default :
		throw CqlException( "Internal error, unrecognized type.", EC_INTERNAL_ERROR, __FILE__, __LINE__, "HY000" );
#if defined( _MSC_VER ) && _MSC_VER != 1200
		break;
#endif
	}

#if defined( _MSC_VER ) && _MSC_VER != 1200
	//  brain dead Microsoft compiler
	return 0;
#endif
}


AbstractType *AbstractType::createObject( CqlColumnTypes ctype )
{
	switch( ctype.typeType() )
	{
	case CQL_CHAR :
		return new ConcreteType< PrimitiveChar >( ctype );

	case CQL_VARCHAR :
		return new ConcreteType< PrimitiveVarchar >( ctype );

	case CQL_DECIMAL :
		return new ConcreteType< PrimitiveDecimal >( ctype );

	case CQL_SMALLINT :
		return new ConcreteType< PrimitiveSmallint >( ctype );

	case CQL_INTEGER :
		return new ConcreteType< PrimitiveInteger >( ctype );

	case CQL_REAL :
		return new ConcreteType< PrimitiveReal >( ctype );

	case CQL_FLOAT :
		return new ConcreteType< PrimitiveFloat >( ctype );

	case CQL_LONGVARCHAR :
		return new ConcreteType< PrimitiveLongvarchar >( ctype );

	case CQL_BIT :
		return new ConcreteType< PrimitiveBit >( ctype );

	case CQL_TINYINT :
		return new ConcreteType< PrimitiveTinyint >( ctype );

	case CQL_BIGINT :
		return new ConcreteType< PrimitiveBigint >( ctype );

	case CQL_BINARY :
		return new ConcreteType< PrimitiveBinary >( ctype );

	case CQL_VARBINARY :
		return new ConcreteType< PrimitiveVarbinary >( ctype );

	case CQL_LONGVARBINARY :
		return new ConcreteType< PrimitiveLongvarbinary >( ctype );

	case CQL_DATE :
		return new ConcreteType< PrimitiveDate >( ctype );

	case CQL_TIME :
		return new ConcreteType< PrimitiveTime >( ctype );

	case CQL_TIMESTAMP :
		return new ConcreteType< PrimitiveTimestamp >( ctype );

	case CQL_CHARUC :
		return new Cql_CharUC();

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw CqlException( "Internal error, unrecognized type.", EC_INTERNAL_ERROR, __FILE__, __LINE__, "HY000" );
	}

	//  for stupid compilers
	return 0;
}


AbstractValue *AbstractValue::createObject( const AbstractValue& cother )
{
	AbstractValue& other = const_cast< AbstractValue& >( cother );

	switch( const_cast< AbstractValue& >( other ).columnType().typeType() )
	{
	case CQL_CHAR :
	{
		CharValue& oldVal = dynamic_cast< CharValue& >( other );
		CharValue *newVal = new CharValue( oldVal );
		return dynamic_cast< AbstractValue* >( newVal );
	}

	case CQL_VARCHAR :
	{
		VarcharValue& oldval = dynamic_cast< VarcharValue& >( other );
		VarcharValue *newval = new VarcharValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_DECIMAL :
	{
		DecimalValue& oldval = dynamic_cast< DecimalValue& >( other );
		DecimalValue *newval = new DecimalValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_SMALLINT :
	{
		SmallintValue& oldval = dynamic_cast< SmallintValue& >( other );
		SmallintValue *newval = new SmallintValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_INTEGER :
	{
		IntegerValue& oldval = dynamic_cast< IntegerValue& >( other );
		IntegerValue *newval = new IntegerValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_REAL :
	{
		RealValue& oldval = dynamic_cast< RealValue& >( other );
		RealValue *newval = new RealValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_FLOAT :
	{
		FloatValue& oldval = dynamic_cast< FloatValue& >( other );
		FloatValue *newval = new FloatValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_LONGVARCHAR :
	{
		LongvarcharValue& oldval = dynamic_cast< LongvarcharValue& >( other );
		LongvarcharValue *newval = new LongvarcharValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_BIT :
	{
		BitValue& oldval = dynamic_cast< BitValue& >( other );
		BitValue *newval = new BitValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_TINYINT :
	{
		TinyintValue& oldval = dynamic_cast< TinyintValue& >( other );
		TinyintValue *newval = new TinyintValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_BIGINT :
	{
		BigintValue& oldval = dynamic_cast< BigintValue& >( other );
		BigintValue *newval = new BigintValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_BINARY :
	{
		BinaryValue& oldval = dynamic_cast< BinaryValue& >( other );
		BinaryValue *newval = new BinaryValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_VARBINARY :
	{
		VarbinaryValue& oldval = dynamic_cast< VarbinaryValue& >( other );
		VarbinaryValue *newval = new VarbinaryValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_LONGVARBINARY :
	{
		LongvarbinaryValue& oldval = dynamic_cast< LongvarbinaryValue& >( other );
		LongvarbinaryValue *newval = new LongvarbinaryValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_DATE :
	{
		DateValue& oldval = dynamic_cast< DateValue& >( other );
		DateValue *newval = new DateValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_TIME :
	{
		TimeValue& oldval = dynamic_cast< TimeValue& >( other );
		TimeValue *newval = new TimeValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_TIMESTAMP :
	{
		TimestampValue& oldval = dynamic_cast< TimestampValue& >( other );
		TimestampValue *newval = new TimestampValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_CHARUC :
	{
		CharUCValue& oldval = dynamic_cast< CharUCValue& >( other );
		CharUCValue *newval = new CharUCValue( oldval );
		return dynamic_cast< AbstractValue* >( newval );
	}

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return 0;  //  dumb compiler
}


AbstractValue *AbstractValue::createObject( const CqlColumnTypes& ctype )
{
	switch( ctype.typeType() )
	{
	case CQL_CHAR :
	{
		CharValue *val = new CharValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_VARCHAR :
	{
		VarcharValue *val = new VarcharValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_DECIMAL :
	{
		DecimalValue *val = new DecimalValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_SMALLINT :
	{
		SmallintValue *val = new SmallintValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_INTEGER :
	{
		IntegerValue *val = new IntegerValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_REAL :
	{
		RealValue *val = new RealValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_FLOAT :
	{
		FloatValue *val = new FloatValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_LONGVARCHAR :
	{
		LongvarcharValue *val = new LongvarcharValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_BIT :
	{
		BitValue *val = new BitValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_TINYINT :
	{
		TinyintValue *val = new TinyintValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_BIGINT :
	{
		BigintValue *val = new BigintValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_BINARY :
	{
		BinaryValue *val = new BinaryValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_VARBINARY :
	{
		VarbinaryValue *val = new VarbinaryValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_LONGVARBINARY :
	{
		LongvarbinaryValue *val = new LongvarbinaryValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_DATE :
	{
		DateValue *val = new DateValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_TIME :
	{
		TimeValue *val = new TimeValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_TIMESTAMP :
	{
		TimestampValue *val = new TimestampValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_CHARUC :
	{
		CharUCValue *val = new CharUCValue( ctype );
		return dynamic_cast< AbstractValue* >( val );
	}

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return 0;  //  dumb compiler
}


Accessor* Accessor::createObject( AccessorTypes atype, US keyNumber )
{
	switch( atype.typeType() )
	{
	case CQL_TREE_INDEX :
		{
			IndexKeyDescriptor *ikd = new IndexKeyDescriptor( atype, keyNumber );
			return dynamic_cast< Accessor* >( ikd );
		}

	case DBZ_TREE_INDEX :
	case DBZ_HASH_INDEX :
	case DBZ_MATERIALIZED_JOIN :
		return 0;

	default :
		//  throw exception
		break;
	}

	return 0;
}


BoundColumn *BoundColumn::createObject( CppTypes cpptype, AbstractColumnDescriptor* col, bool freeable )
{
	BoundColumn *bc = 0;

	switch( cpptype )
	{
	case CPP_BIGINT :
		bc = new BoundColumnBigint( col );
		break;

	case CPP_CHAR :
		bc = new BoundColumnChar( col );
		break;

	case CPP_DATE :
		bc = new BoundColumnDate( col );
		break;

	case CPP_DECIMAL :
		bc = new BoundColumnDecimal( col );
		break;

	case CPP_DOUBLE :
		bc = new BoundColumnDouble( col );
		break;

	case CPP_FLOAT :
		bc = new BoundColumnFloat( col );
		break;

	case CPP_LONG :
		bc = new BoundColumnLong( col );
		break;

	case CPP_PCHAR :
		bc = new BoundColumnPChar( col, freeable );
		break;

	case CPP_PCHAR_SHORT :
		bc = new BoundColumnPCharShort( col, freeable );
		break;

	case CPP_PUCHAR :
		bc = new BoundColumnPUChar( col, freeable );
		break;

	case CPP_PUCHAR_SHORT :
		bc = new BoundColumnPUCharShort( col, freeable );
		break;

	case CPP_SHORT :
		bc = new BoundColumnShort( col );
		break;

	case CPP_STRING :
		bc = new BoundColumnString( col );
		break;

	case CPP_TIME :
		bc = new BoundColumnTime( col );
		break;

	case CPP_TIMESTAMP :
		bc = new BoundColumnTimestamp( col );
		break;

	case CPP_INT :
		bc = new BoundColumnInt( col );
		break;

	case CPP_UNSIGNED_CHAR :
		bc = new BoundColumnUnsignedChar( col );
		break;

	case CPP_UNSIGNED_LONG :
		bc = new BoundColumnUnsignedLong( col );
		break;

	case CPP_UNSIGNED_INT :
		bc = new BoundColumnUnsignedInt( col );
		break;

	case CPP_UNSIGNED_SHORT :
		bc = new BoundColumnUnsignedShort( col );
		break;

	case CPP_BOOL :
		throw UnsupportedFeatureException( __FILE__, __LINE__ );
	}

	if( !bc )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	return bc;
}


BoundColumn *BoundColumn::createObject( const BoundColumn& cother, bool /*freeable*/ )
{
	BoundColumn& other = const_cast< BoundColumn& >( cother );
	BoundColumn *bc = 0;

	switch( other.type() )
	{
	case CPP_BIGINT :
		bc = new BoundColumnBigint( dynamic_cast< BoundColumnBigint& >( other ) );
		break;

	case CPP_CHAR :
		bc = new BoundColumnChar( dynamic_cast< BoundColumnChar& >( other ) );
		break;

	case CPP_DATE :
		bc = new BoundColumnDate( dynamic_cast< BoundColumnDate& >( other ) );
		break;

	case CPP_DECIMAL :
		bc = new BoundColumnDecimal( dynamic_cast< BoundColumnDecimal& >( other ) );
		break;

	case CPP_DOUBLE :
		bc = new BoundColumnDouble( dynamic_cast< BoundColumnDouble& >( other ) );
		break;

	case CPP_FLOAT :
		bc = new BoundColumnFloat( dynamic_cast< BoundColumnFloat& >( other ) );
		break;

	case CPP_LONG :
		bc = new BoundColumnLong( dynamic_cast< BoundColumnLong& >( other ) );
		break;

	case CPP_PCHAR :
		bc = new BoundColumnPChar( dynamic_cast< BoundColumnPChar& >( other ) );
		break;

	case CPP_PUCHAR :
		bc = new BoundColumnPUChar( dynamic_cast< BoundColumnPUChar& >( other ) );
		break;

	case CPP_SHORT :
		bc = new BoundColumnShort( dynamic_cast< BoundColumnShort& >( other ) );
		break;

	case CPP_STRING :
		bc = new BoundColumnString( dynamic_cast< BoundColumnString& >( other ) );
		break;

	case CPP_TIME :
		bc = new BoundColumnTime( dynamic_cast< BoundColumnTime& >( other ) );
		break;

	case CPP_TIMESTAMP :
		bc = new BoundColumnTimestamp( dynamic_cast< BoundColumnTimestamp& >( other ) );
		break;

	case CPP_BOOL :
	case CPP_INT :
	case CPP_PCHAR_SHORT :
	case CPP_PUCHAR_SHORT :
	case CPP_UNSIGNED_CHAR :
	case CPP_UNSIGNED_LONG :
	case CPP_UNSIGNED_INT :
	case CPP_UNSIGNED_SHORT :
		throw UnsupportedFeatureException( __FILE__, __LINE__ );
	}

	if( !bc )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	return bc;
}


AbstractErrorManager *AbstractErrorManager::createObject( const ExceptionCodes ec, const CqlString& fname, const NI line, const CqlString& errorText, const CqlString& sqlstate, NI oserror )
{
	ErrorManager *em = new ErrorManager( ec, fname, line, errorText, sqlstate, oserror );
	if( !em )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	return em;
}
