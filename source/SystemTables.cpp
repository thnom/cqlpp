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


#include "CqlSqlInclude.h"


SystemTable::SystemTable( SqlHandle& sqlh, const CqlString& dname )
:
dbHandle_( sqlh ),
dictionaryName_( "" ),
owner_( CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH ),
ownerColumnNumber_( 1 ),
ownerNull_( false ),
qualifier_( CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH ),
qualifierColumnNumber_( 0 ),
qualifierNull_( false ),
table_( 0 ),
tableName_( CQL_MAXIMUM_TABLE_NAME_LENGTH ),
tableNameColumnNumber_( 2 ),
tableNameNull_( false )
{
	if( sqlh.initialDirectory()->length() )
	{
		dictionaryName_ = *sqlh.initialDirectory();
		dictionaryName_ += "/";
	}
	dictionaryName_ += dname;

	table_ = AbstractTable::createObject( sqlh.aHandle(), CQL_CQL );
}


SystemTable::~SystemTable( void )
{
	tableName_.reset();
	qualifier_.reset();
	owner_.reset();
}


void SystemTable::bind( void )
{
	table_->bindColumn( qualifierColumnNumber_, qualifier_, qualifierNull_, true );
	table_->bindColumn( ownerColumnNumber_, owner_, ownerNull_, true );
	table_->bindColumn( tableNameColumnNumber_, tableName_, tableNameNull_, true );
}


SystemTableIndices::SystemTableIndices( SqlHandle& sqlh )
	: SystemTable( sqlh, CQL_SYSTEMTABLEINDICES_NAME ),
	  columnName_( CQL_SYSTEMTABLEINDICES_COLUMN_NAME_LENGTH ),
	  columnNameNull_( false ),
	  columnNumber_( 0 ),
	  columnNumberNull_( false ),
	  duplicateKey_( 0 ),
	  duplicateKeyNull_( false ),
	  fileName_( CQL_SYSTEMTABLEINDICES_FILE_NAME_LENGTH ),
	  fileNameNull_( false ),
	  indexName_( CQL_SYSTEMTABLEINDICES_INDEX_NAME_LENGTH ),
	  indexNameNull_( false ),
	  keyNumber_( 0 ),
	  keyNumberNull_( false ),
	  length_( 0 ),
	  lengthNull_( false ),
	  precision_( 0 ),
	  precisionNull_( false ),
	  primaryKey_( 0 ),
	  primaryKeyNull_( false ),
	  scale_( 0 ),
	  scaleNull_( false ),
	  tableRow_( 0 ),
	  tableRowNull_( false ),
	  type_( 0 ),
	  typeNull_( false ),
	  typeName_( CQL_SYSTEMTABLEINDICES_TYPE_NAME_LENGTH ),
	  typeNameNull_( false ),
	  uniqueKey_( 0 ),
	  uniqueKeyNull_( false )
{
	try
	{
		table_->open( dictionaryName_ );
	}
	catch( AbstractTableException& )
	{
		sqlh.resetError();

		CqlColumnTypes *columnDescriptors[ 18 ];
		columnDescriptors[ 0 ] = new CqlColumnTypes( "qualifier", CQL_SYSTEMTABLEINDICES_QUALIFIER_TYPE, CQL_SYSTEMTABLEINDICES_QUALIFIER_LENGTH );
		columnDescriptors[ 1 ] = new CqlColumnTypes( "owner", CQL_SYSTEMTABLEINDICES_OWNER_TYPE, CQL_SYSTEMTABLEINDICES_OWNER_LENGTH );
		columnDescriptors[ 2 ] = new CqlColumnTypes( "tableName", CQL_SYSTEMTABLEINDICES_TABLE_NAME_TYPE, CQL_SYSTEMTABLEINDICES_TABLE_NAME_LENGTH );
		columnDescriptors[ 3 ] = new CqlColumnTypes( "columnName", CQL_SYSTEMTABLEINDICES_COLUMN_NAME_TYPE, CQL_SYSTEMTABLEINDICES_COLUMN_NAME_LENGTH );
		columnDescriptors[ 4 ] = new CqlColumnTypes( "keyNumber", CQL_SYSTEMTABLEINDICES_KEY_NUMBER_TYPE );
		columnDescriptors[ 5 ] = new CqlColumnTypes( "columnNumber", CQL_SYSTEMTABLEINDICES_COLUMN_NUMBER_TYPE );
		columnDescriptors[ 6 ] = new CqlColumnTypes( "type", CQL_SYSTEMTABLEINDICES_TYPE_TYPE );
		columnDescriptors[ 7 ] = new CqlColumnTypes( "typeName", CQL_SYSTEMTABLEINDICES_TYPE_NAME_TYPE, CQL_SYSTEMTABLEINDICES_TYPE_NAME_LENGTH );
		columnDescriptors[ 8 ] = new CqlColumnTypes( "precision", CQL_SYSTEMTABLEINDICES_PRECISION_TYPE );
		columnDescriptors[ 9 ] = new CqlColumnTypes( "length", CQL_SYSTEMTABLEINDICES_LENGTH_TYPE );
		columnDescriptors[ 10 ] = new CqlColumnTypes( "scale", CQL_SYSTEMTABLEINDICES_SCALE_TYPE );
		columnDescriptors[ 11 ] = new CqlColumnTypes( "primaryKey", CQL_SYSTEMTABLEINDICES_PRIMARY_KEY_TYPE );
		columnDescriptors[ 12 ] = new CqlColumnTypes( "uniqueKey", CQL_SYSTEMTABLEINDICES_UNIQUE_KEY_TYPE );
		columnDescriptors[ 13 ] = new CqlColumnTypes( "duplicateKey", CQL_SYSTEMTABLEINDICES_DUPLICATE_KEY_TYPE );
		columnDescriptors[ 14 ] = new CqlColumnTypes( "tableRowFlag", CQL_SYSTEMTABLEINDICES_TABLE_ROW_TYPE );
		columnDescriptors[ 15 ] = new CqlColumnTypes( "fileName", CQL_SYSTEMTABLEINDICES_FILE_NAME_TYPE, CQL_SYSTEMTABLEINDICES_FILE_NAME_LENGTH );
		columnDescriptors[ 16 ] = new CqlColumnTypes( "indexName", CQL_SYSTEMTABLEINDICES_INDEX_NAME_TYPE, CQL_SYSTEMTABLEINDICES_INDEX_NAME_LENGTH );
		columnDescriptors[ 17 ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );

		AccessorTypes *keyDescriptors[ 2 ];
		SegmentTypes *segs[ 6 ];
		keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, segs );
		segs[ 0 ] = new SegmentTypes( "owner", 1, SegmentTypes::CQL_ASCENDING );
		segs[ 1 ] = new SegmentTypes( "tableName", 2, SegmentTypes::CQL_ASCENDING );
		segs[ 2 ] = new SegmentTypes( "columnName", 3, SegmentTypes::CQL_ASCENDING );
		segs[ 3 ] = new SegmentTypes( "keyNumber", 4, SegmentTypes::CQL_ASCENDING );
		segs[ 4 ] = new SegmentTypes( "columnNumber", 5, SegmentTypes::CQL_ASCENDING );
		segs[ 5 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
		
		keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

		table_->create( CQL_CQL, dictionaryName_, columnDescriptors, keyDescriptors );

		delete columnDescriptors[ 0 ];
		delete columnDescriptors[ 1 ];
		delete columnDescriptors[ 2 ];
		delete columnDescriptors[ 3 ];
		delete columnDescriptors[ 4 ];
		delete columnDescriptors[ 5 ];
		delete columnDescriptors[ 6 ];
		delete columnDescriptors[ 7 ];
		delete columnDescriptors[ 8 ];
		delete columnDescriptors[ 9 ];
		delete columnDescriptors[ 10 ];
		delete columnDescriptors[ 11 ];
		delete columnDescriptors[ 12 ];
		delete columnDescriptors[ 13 ];
		delete columnDescriptors[ 14 ];
		delete columnDescriptors[ 15 ];
		delete columnDescriptors[ 16 ];
		delete columnDescriptors[ 17 ];
		delete keyDescriptors[ 0 ];
		delete segs[ 0 ];
		delete segs[ 1 ];
		delete segs[ 2 ];
		delete segs[ 3 ];
		delete segs[ 4 ];
		delete segs[ 5 ];
		delete keyDescriptors[ 1 ];
	}
	catch( ... )
	{
		throw;
	}

	try
	{
		SystemTable::bind();
		table_->bindColumn( CID_COLUMN_NAME, columnName_, columnNameNull_, true );
		table_->bindColumn( CID_KEY_NUMBER, keyNumber_, keyNumberNull_, true );
		table_->bindColumn( CID_COLUMN_NUMBER, columnNumber_, columnNumberNull_, true );
		table_->bindColumn( CID_TYPE, type_, typeNull_, true );
		table_->bindColumn( CID_TYPE_NAME, typeName_, typeNameNull_, true );
		table_->bindColumn( CID_PRECISION, precision_, precisionNull_, true );
		table_->bindColumn( CID_LENGTH, length_, lengthNull_, true );
		table_->bindColumn( CID_SCALE, scale_, scaleNull_, true );
		table_->bindColumn( CID_PRIMARY_KEY, primaryKey_, primaryKeyNull_, true );
		table_->bindColumn( CID_UNIQUE_KEY, uniqueKey_, uniqueKeyNull_, true );
		table_->bindColumn( CID_DUPLICATE_KEY, duplicateKey_, duplicateKeyNull_, true );
		table_->bindColumn( CID_TABLE_ROW, tableRow_, tableRowNull_, true );
		table_->bindColumn( CID_FILE_NAME, fileName_, fileNameNull_, true );
		table_->bindColumn( CID_INDEX_NAME, indexName_, indexNameNull_, true );
	}
	catch( CqlException& )
	{
		//  ******************* print exception string here
		throw DictionaryException( __FILE__, __LINE__ );
	}
}


SystemTableIndices::~SystemTableIndices( void )
{
}


void SystemTableIndices::add( const CqlString& qName,
							  const CqlString& oName,
							  const CqlString& tName,
							  const CqlString& cName,
							  const S rowFlag,
							  const CqlString& fName,
							  const S kNum,
							  const S cNum,
							  const S typ,
							  const NC *typeNam,
							  const L prec,
							  const L len,
							  const S scal,
							  const S pKeyFlag,
							  const S uKeyFlag,
							  const S dKeyFlag,
							  const CqlString& iName )
{
	qualifier() = qName;
	owner() = oName;
	tableName() = tName;
	columnName_ = cName;
	columnNumber_ = cNum;
	duplicateKey_ = dKeyFlag;
	fileName_ = fName;
	indexName_ = iName;
	keyNumber_ = kNum;
	length_ = len;
	precision_ = prec;
	primaryKey_ = pKeyFlag;
	scale_ = scal;
	tableRow_ = rowFlag;
	type_ = typ;
	typeName_ = typeNam;
	uniqueKey_ = uKeyFlag;

	if( pKeyFlag )
			hAEnv->logPrintf(AbstractLogger::TRACEALL,"%s:%d, primary key flag true.\n",__FILE__,__LINE__);

	table_->addRow();
}


SystemTableTables::SystemTableTables( SqlHandle& sqlh ) : SystemTable( sqlh, CQL_SYSTEMTABLETABLES_NAME ), remarks_(), type_( CQL_SYSTEMTABLETABLES_TYPE_LENGTH )
{
	table_ = AbstractTable::createObject( sqlh.aHandle(), CQL_CQL );

	try
	{
		table_->open( dictionaryName_ );
	}
	catch( AbstractTableException& )
	{
		sqlh.resetError();

		CqlColumnTypes *columnDescriptors[ 6 ];
		columnDescriptors[ 0 ] = new CqlColumnTypes( "qualifier", CQL_SYSTEMTABLETABLES_QUALIFIER_TYPE, CQL_SYSTEMTABLETABLES_QUALIFIER_LENGTH );
		columnDescriptors[ 1 ] = new CqlColumnTypes( "owner", CQL_SYSTEMTABLETABLES_OWNER_TYPE, CQL_SYSTEMTABLETABLES_OWNER_LENGTH );
		columnDescriptors[ 2 ] = new CqlColumnTypes( "tableName", CQL_SYSTEMTABLETABLES_TABLE_NAME_TYPE, CQL_SYSTEMTABLETABLES_TABLE_NAME_LENGTH );
		columnDescriptors[ 3 ] = new CqlColumnTypes( "type", CQL_SYSTEMTABLETABLES_TYPE_TYPE );
		columnDescriptors[ 4 ] = new CqlColumnTypes( "remarks", CQL_SYSTEMTABLETABLES_REMARKS_TYPE, CQL_SYSTEMTABLETABLES_REMARKS_LENGTH );
		columnDescriptors[ 5 ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );

		AccessorTypes *keyDescriptors[ 2 ];
		SegmentTypes *segs[ 3 ];
		keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, segs );
		segs[ 0 ] = new SegmentTypes( "owner", 1, SegmentTypes::CQL_ASCENDING );
		segs[ 1 ] = new SegmentTypes( "tableName", 2, SegmentTypes::CQL_ASCENDING );
		segs[ 2 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
		keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

		table_->create( CQL_CQL, dictionaryName_, columnDescriptors, keyDescriptors );

		delete columnDescriptors[ 0 ];
		delete columnDescriptors[ 1 ];
		delete columnDescriptors[ 2 ];
		delete columnDescriptors[ 3 ];
		delete columnDescriptors[ 4 ];
		delete columnDescriptors[ 5 ];
		delete keyDescriptors[ 0 ];
		delete segs[ 0 ];
		delete segs[ 1 ];
		delete segs[ 2 ];
		delete keyDescriptors[ 1 ];
	}
	catch( ... )
	{
		throw;
	}

	try
	{
		SystemTable::bind();
		table_->bindColumn( CID_TYPE, type_, typeNull_, true );
		table_->bindColumn( CID_REMARKS, remarks_, remarksNull_, true );
	}
	catch( CqlException& )
	{
		//  ******************* print exception string here
		throw DictionaryException( __FILE__, __LINE__ );
	}
}


SystemTableTables::~SystemTableTables( void )
{
	table_->close();
	delete table_;
	table_ = 0;
}


void SystemTableTables::add( const CqlString& qName, const CqlString& oName, const CqlString& tName, const NC *typ, const CqlString& remark )
{
	qualifier() = qName;
	owner() = oName;
	tableName() = tName;
	type_ = typ;
	remarks_ = remark;

	table_->addRow();
}
