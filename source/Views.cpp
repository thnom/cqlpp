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


View::View( SqlHandle& sqlh, AbstractTableSpecification *ats ) : TableTableElement( sqlh ), viewSpec_( dynamic_cast< ViewSpecification* >( ats ) )
{
}


View::~View( void )
{
	if( viewSpec_ )
	{
		if( viewSpec_->aliasFlag() )
		{
			delete viewSpec_;
			viewSpec_ = 0;
		}
	}
}


void View::addRow()
{
	viewSpec_->addRow();
}


void View::deleteRow( void )
{
	viewSpec_->deleteRow();
}


bool View::firstRow( US /*keyNumber*/ )
{
	return false;
}


bool View::nextRow( void )
{
	return false;
}


bool View::previousRow( void )
{
	return false;
}


bool View::lastRow( US /*keyNumber*/ )
{
	return false;
}


void View::magicLock( void )
{
}


void View::getColumnInfo( US /*columnNumber*/, CqlColumnTypes&, bool& /*nullflag*/ )
{
}


SegmentedKeyGroup *View::indexExistsForColumn( US /*columnNumber*/ )
{
	return 0;
}


US View::dictionaryLength( void )
{
	return viewSpec_->dictionaryLength();
}


void View::writeDictionaryInformation( TempBuffer& buffer )
{
	viewSpec_->writeDictionaryInformation( buffer );
}


void View::readDictionaryInformation( TempBuffer& buffer )
{
	viewSpec_->readDictionaryInformation( buffer );
}


pAbstractTable View::file( UNI )
{
	return 0;
}


void View::flushDataToRecords( void )
{
}


AbstractType *View::getColumnValue( US )
{
	throw UnsupportedFeatureException( __FILE__, __LINE__ );
	return 0;
}


void View::viewCleanup( void )
{
	SelectExpression *select;

	select = viewSpec_->selectExpressions().first();
	select->viewCleanup();
}


ViewSpecification::ViewSpecification( SqlHandle& sqlh )
	: AbstractTableSpecification( sqlh ),
	  checkOption_( CQL_NO ),
	  dictionaryRecordBuffer_( 0 ),
	  processed_( CQL_NO ),
	  selectExpressions_(),
	  viewColumnNames_(),
	  virtualBufferLength_( 0 )
{
}


ViewSpecification::ViewSpecification( SqlHandle& sqlh, CqlString& name, CqlString& authid )
	: AbstractTableSpecification( sqlh, name, authid ),
	  checkOption_( false ),
	  dictionaryRecordBuffer_( 0 ),
	  processed_( CQL_NO ),
	  selectExpressions_(),
	  viewColumnNames_(),
	  virtualBufferLength_( 0 )
{
}


ViewSpecification::~ViewSpecification( void )
{
	selectExpressions_.destroy();
	viewColumnNames_.destroy();
}


ViewSpecification& ViewSpecification::operator = ( const ViewSpecification& cother )
{
	ViewSpecification& other = const_cast< ViewSpecification& >( cother );
	virtualBufferLength_ = other.virtualBufferLength_;
	dictionaryRecordBuffer_ = other.dictionaryRecordBuffer_;
	checkOption_ = other.checkOption_;
	dynamic_cast< AbstractTableSpecification& >( *this ) = dynamic_cast< AbstractTableSpecification& >( other );
	return *this;
}


void ViewSpecification::deleteDictionaryEntry( void )
{
	dbsql().deleteMainDictionaryEntry( this );
}


bool ViewSpecification::referencesExist( void )
{
	return false;
}


void ViewSpecification::processCascade( void )
{
}


void ViewSpecification::deleteRow( void )
{
}


void ViewSpecification::computeDictionaryRecordLength( void )
{
}


void ViewSpecification::addRow( void )
{
}


void ViewSpecification::assignValue( Column&, PermanentColumnSpecification& )
{
}


void ViewSpecification::open( TableType )
{
}


void ViewSpecification::close( void )
{
	SelectExpression *select;

	for( select = selectExpressions_.first(); select; select = selectExpressions_.next() )
		select->cleanup();
}


void ViewSpecification::releaseMemory( void )
{
	if( dictionaryRecordBuffer_ )
	{
		delete [] dictionaryRecordBuffer_;
		dictionaryRecordBuffer_ = 0;
	}
}


US ViewSpecification::numberOfBaseTables( void )
{
	return selectExpressions_.first()->numberOfBaseTables();
}


void ViewSpecification::retrieveBaseTablePositions( pUC *p )
{
	pSelectExpression select = selectExpressions_.first();
	select->retrieveBaseTablePositions();

	memcpy( (*p), select->baseTablePositionBuffer(), select->baseTablePositionBufferSize() );
	(*p) += select->baseTablePositionBufferSize();
}


void ViewSpecification::retrieveBaseTableRows( pUC* )
{
}


void ViewSpecification::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> checkOption_;

	viewColumnNames_.readDictionaryInformation( buffer );
	selectExpressions_.readDictionaryInformation( buffer );
}


void ViewSpecification::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << checkOption_;
	viewColumnNames_.writeDictionaryInformation( buffer );
	selectExpressions_.writeDictionaryInformation( buffer );
}


AbstractTable *ViewSpecification::baseTable( US /*columnNumber*/ )
{
	//  Must be fixed for selects as well as updatable views
#if 0
	throw UnsupportedFeatureException( __FILE__, __LINE__ );
#endif
	return 0;
}


AbstractColumnDescriptor *ViewSpecification::firstBaseTableColumn( AbstractTable** )
{
	throw UnsupportedFeatureException( __FILE__, __LINE__ );
	return 0;
}


AbstractColumnDescriptor *ViewSpecification::nextBaseTableColumn( AbstractTable** )
{
	throw UnsupportedFeatureException( __FILE__, __LINE__ );
	return 0;
}


void ViewSpecification::beginRowOperation( void )
{
}


void ViewSpecification::checkPropagationFlags( void )
{
	pSelectExpression select = selectExpressions_.first();
	pTableTableElement ttEl;

	for( ttEl = select->tables().first(); ttEl; ttEl = select->tables().next() )
		ttEl->absTableSpec()->checkPropagationFlags();
}


void ViewSpecification::deleteCurrentRecord( void )
{
	pSelectExpression select = selectExpressions_.first();
	pTableTableElement ttEl;

	for( ttEl = select->tables().first(); ttEl; ttEl = select->tables().next() )
		ttEl->absTableSpec()->deleteCurrentRecord();
}


NI ViewSpecification::ProcessView( SqlHandle *_dbsql )
{
	pSelectExpression select;
	pColumn column;
	pColumnSpecification colSpec;
	pStringListElement vcn;

	if( processed_ )
	{
		for( select = selectExpressions_.first(); select; select = selectExpressions_.next() )
			select->reprocessViewSelect( selectExpressions_ );
		return CQL_SUCCESS;
	}

	for( select = selectExpressions_.first(); select; select = selectExpressions_.next() )
	{
		select->processViewSelect( selectExpressions_ );
		select->processSelect();
	}

	//
	//  create the columns list for ViewSpecification
	//
	select = selectExpressions_.first();
	for( column = select->columns().first(), vcn = viewColumnNames_.first(); column; column = select->columns().next(), vcn = viewColumnNames_.next()  )
	{
		colSpec = new ColumnSpecification( *_dbsql );
		if( !colSpec )
			return _dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

		colSpec->SetIsViewColumn();
		column->ColumnExpression().setViewFlag();
		colSpec->SetViewColumn( column );
		colSpec->type( column->ColumnExpression().valueExpressionType() );
		colSpec->length( column->ColumnExpression().valueExpressionLength() );
		columns().add( colSpec );

		column->ViewName() = vcn->s();
		colSpec->columnName() = vcn->s();
		colSpec->TableName() = tableName();
	}

	processed_ = true;
	return CQL_SUCCESS;
}


