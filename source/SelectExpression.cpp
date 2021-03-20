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


void SelectExpression::positionedUpdate( UpdateColumnNameAndExpList& updateColumns, bool preparing )
{
	pTableTableElement table;
	pTripleStringListElement el = tableNames_.first();

	//
	//  check that cursor references only one table
	//
	if( tables_.size() != 1 )
		throw PositionedOperationWithMultipleTablesException( __FILE__, __LINE__ );

	table = tables_.first();

	//
	//  compare the table name in UPDATE to the table name in DECLARE CURSOR
	//
	if( ( el->s2() != CqlString( "" ) && el->s2() != table->authorizationId() ) || el->s1() != table->tableName() )
		throw TableNotFoundException( __FILE__, __LINE__ );

	if( !dbsql_.checkForUpdatePrivilege( table, columns_ ) )
		throw PrivilegeViolationException( __FILE__, __LINE__ );

	if( preparing == CQL_YES )
	{
		dbsql_.currentStatement()->type( UPDATE_POSITIONED );
		dbsql_.currentStatement()->updateTtel( table );
		return;
	}

	positionedUpdatePart2( updateColumns, table );
}


void SelectExpression::positionedUpdatePart2( UpdateColumnNameAndExpList& /*updateColumns*/, pTableTableElement table )
{
	table->rereadCurrentRow();
#if 0
	//**********************  temporary
	assignForUpdate( table->absTableSpec(), updateColumns );
#endif
	table->update();
}


bool SelectExpression::identifyUpdateColumnNames( pAbstractTableSpecification table, UpdateColumnNameAndExpList& updateColumns )
{
	pUpdateColumnNameAndExp uColName;
	bool found;

	for( uColName = updateColumns.first(); uColName; uColName = updateColumns.next() )
	{
		// FIXED
		PermanentColumnSpecification *pcs;
		for( pcs = table->columns().first(), found = false; pcs && !found ; pcs = table->columns().next() )
		{
			ColumnSpecification *colSpec = dynamic_cast< ColumnSpecification* >( pcs );
			if( uColName->s() == colSpec->columnName() )
			{
				uColName->colSpec( colSpec );
				uColName->file( colSpec->TtEl()->file( colSpec->columnNumber() ) );
				found = true;
			}
		}

		if( !found )
			return false;
	}

	return true;
}


void SelectExpression::searchedUpdate( UpdateColumnNameAndExpList& updateColumns, bool preparing )
{
	pTableTableElement table;
	pTripleStringListElement el = tableNames_.first();
	pUpdateColumnNameAndExp updateCol;

	processSelectCommon();

	table = tables_.first();

	if( preparing == CQL_YES )
	{
		dbsql_.currentStatement()->type( UPDATE_SEARCHED );
		dbsql_.currentStatement()->updateTtel( table );
	}

	for( updateCol = updateColumns.first(); updateCol; updateCol = updateColumns.next() )
	{
		identifyExpressionColumns( updateCol->exp() );
		updateCol->exp().computeValueExpressionType();
	}

	if( !identifyUpdateColumnNames( table->absTableSpec(), updateColumns ) )
		throw ColumnNotFoundException( __FILE__, __LINE__ );

	if( !( !( el->s2() ) ) )
		if( el->s2() != table->authorizationId() )
			throw TableNotFoundException( __FILE__, __LINE__ );

	if( el->s1() != table->tableName() )
		throw TableNotFoundException( __FILE__, __LINE__ );

	if( !dbsql_.checkForUpdatePrivilege( table, columns_ ) )
		throw PrivilegeViolationException( __FILE__, __LINE__ );

	if( preparing )
		return;

	searchedUpdatePart2( updateColumns, table );
}


void SelectExpression::searchedUpdatePart2( UpdateColumnNameAndExpList& updateColumns, TableTableElement *table )
{
	setFinalTrip();
	dbsql_.updateCount( 0 );
	dbsql_.beginTransaction();
	createUpdateListFile( table );
	if( !scanFirst() )
	{
		dbsql_.rollbackTransaction( false );
		throw NoDataException( __FILE__, __LINE__ );
	}

	bool result;

	do
	{
		dbsql_.incrementUpdateCount();
		bindColumnsForUpdate( *table, updateColumns );
		addToUpdateList();
		result = scanNext();
	} while( result );

	for( result = updateListFirst(); result; result = updateListNext(), dbsql_.incrementUpdateCount() )
	{
		updateFile_.getBaseTablePositions( baseTablePositionBuffer_ );
		refetchBaseTableRows();
		table->deleteRow();
	}

	for( result = updateListFirst(); result; result = updateListNext() )
	{
		AbstractColumnDescriptor *colDesc;
		AbstractTable *file;
		US loop;

		for( colDesc = table->absTableSpec()->firstBaseTableColumn( &file ), loop = 0; colDesc; colDesc = table->absTableSpec()->nextBaseTableColumn( &file ), loop++ )
		{
			AbstractTable *atable = table->absTableSpec()->baseTable( loop );
			atable->beginRowOperation();
		}

		for( colDesc = table->absTableSpec()->firstBaseTableColumn( &file ), loop = 0; colDesc; colDesc = table->absTableSpec()->nextBaseTableColumn( &file ), loop++ )
		{
			AbstractTable *atable = table->absTableSpec()->baseTable( loop );
			AbstractType *at = updateFile_.ifile()->getColumnValue( loop );
			atable->bindColumnAV( colDesc->columnNumber(), at->avalue(), true, true );
		}

		try
		{
			table->addRow();
		}
		catch( ... )
		{
			dbsql_.rollbackTransaction( false );
			throw;
		}
	}

	dbsql_.commitTransaction( false );
	table->absTableSpec()->checkPropagationFlags();
}


SelectExpression::SelectExpression( SqlHandle& sqlh )
	:  allLinks_( false ),
	   aggregateDistinctScan_( false ),
	   aggregateFunctions_( false ),
	   cartesianProductLink_( false ),
	   cleanedUp_( false ),
	   correlated_( false ),
	   correlatedLink_( false ),
	   distinct_( false ),
	   endGroup_( false ),
	   existsSubquery_( false ),
	   existsValueFlag_( false ),
	   finalTrip_( false ),
	   firstInExpression_( false ),
	   firstScan_( false ),
	   groupBy_( false ),
	   groupByVariableLength_( false ),
	   having_( false ),
	   linksSorted_( false ),
	   listOperationInProgress_( false ),
	   logicalFetch_( false ),
	   midGroup_( false ),
	   mostRecentHavingResult_( false ),
	   nextMostRecentHavingResult_( false ),
	   noCondition_( false ),
	   noSet_( false ),
	   notFlag_( false ),
	   oneSet_( false ),
	   onlyAggregateFunctions_( false ),
	   orderBy_( false ),
	   orderDescending_( false ),
	   orderEnabled_( false ),
	   orderTemporary_( false ),
	   refetchMode_( false ),
	   refetchOK_( false ),
	   setVariableLength_( false ),
	   tablesAndColumnsProcessed_( false ),
	   temporaryFileExists_( false ),
	   unionAll_( false ),
	   unionSet_( false ),
	   unique_( false ),
	   uniqueEnabled_( false ),
	   usingAggregateIndex_( false ),
	   usingCountIndex_( false ),
	   updateEnabled_( false ),
	   baseTablePositionBuffer_( 0 ),
	   baseTablePositionBufferSize_( 0 ),
	   columns_(),
	   columnsLength_( 0 ),
	   dbsql_( sqlh ),
	   existingOrderKey_( 0 ),
	   groupByColumns_(),
	   groupByColumnsLength_( 0 ),
	   havingExp_( sqlh ),
	   numberOfRowIds_( 0 ),
	   orderByExp_( sqlh ),
	   orderFile_( sqlh ),
	   report_( sqlh ),
	   results_(),
	   rowList_( 0 ),
	   rowListNullflag_( false ),
	   tables_(),
	   tableNames_(),
	   temporaryFile_( sqlh ),
	   uniqueFile_( sqlh ),
	   updateFile_( sqlh ),
	   whereCondition_( sqlh )
{
}


SelectExpression::~SelectExpression( void )
{
}


SelectExpression& SelectExpression::operator = ( const SelectExpression& other )
{
	allLinks_ = other.allLinks_;
	aggregateDistinctScan_ = other.aggregateDistinctScan_;
	aggregateFunctions_ = other.aggregateFunctions_;
	cartesianProductLink_ = other.cartesianProductLink_;
	cleanedUp_ = other.cleanedUp_;
	correlated_ = other.correlated_;
	correlatedLink_ = other.correlatedLink_;
	distinct_ = other.distinct_;
	endGroup_ = other.endGroup_;
	existsSubquery_ = other.existsSubquery_;
	existsValueFlag_ = other.existsValueFlag_;
	finalTrip_ = other.finalTrip_;
	firstInExpression_ = other.firstInExpression_;
	firstScan_ = other.firstScan_;
	groupBy_ = other.groupBy_;
	groupByVariableLength_  = other.groupByVariableLength_ ;
	having_ = other.having_;
	linksSorted_ = other.linksSorted_;
	listOperationInProgress_ = other.listOperationInProgress_;
	logicalFetch_ = other.logicalFetch_;
	midGroup_ = other.midGroup_;
	mostRecentHavingResult_ = other.mostRecentHavingResult_;
	nextMostRecentHavingResult_ = other.nextMostRecentHavingResult_;
	noCondition_ = other.noCondition_;
	noSet_ = other.noSet_;
	notFlag_ = other.notFlag_;
	oneSet_ = other.oneSet_;
	onlyAggregateFunctions_ = other.onlyAggregateFunctions_;
	orderBy_ = other.orderBy_;
	orderDescending_ = other.orderDescending_;
	orderEnabled_ = other.orderEnabled_;
	orderTemporary_ = other.orderTemporary_;
	refetchMode_ = other.refetchMode_;
	refetchOK_ = other.refetchOK_;
	setVariableLength_ = other.setVariableLength_;
	tablesAndColumnsProcessed_  = other.tablesAndColumnsProcessed_ ;
	temporaryFileExists_ = other.temporaryFileExists_;
	unionAll_ = other.unionAll_;
	unionSet_ = other.unionSet_;
	unique_ = other.unique_;
	uniqueEnabled_ = other.uniqueEnabled_;
	usingAggregateIndex_ = other.usingAggregateIndex_;
	usingCountIndex_ = other.usingCountIndex_;
	updateEnabled_ = other.updateEnabled_;

	baseTablePositionBufferSize_  = other.baseTablePositionBufferSize_ ;
	if( baseTablePositionBufferSize_  )
	{
		baseTablePositionBuffer_ = new UC[ baseTablePositionBufferSize_  ];
		if( !baseTablePositionBuffer_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		memcpy( baseTablePositionBuffer_, other.baseTablePositionBuffer_, baseTablePositionBufferSize_  );
	}
	else
		baseTablePositionBuffer_ = 0;

	columnProgressionState_ = other.columnProgressionState_;

	columns_ = other.columns_;
	columnsLength_ = other.columnsLength_;
	report_ = other.report_;
	existingOrderKey_ = other.existingOrderKey_;

	groupByColumns_ = other.groupByColumns_;
	groupByColumnsLength_ = other.groupByColumnsLength_;

	havingExp_ = other.havingExp_;
	linkState_ = other.linkState_;
	numberOfRowIds_ = other.numberOfRowIds_;
	orderByExp_ = other.orderByExp_;
	orderFile_ = other.orderFile_;
	*rowList_ = *other.rowList_;
	results_ = other.results_;
	tables_ = other.tables_;
	tableNames_ = other.tableNames_;
	temporaryFile_ = other.temporaryFile_;
	uniqueFile_ = other.uniqueFile_;
	updateFile_ = other.updateFile_;
	whereCondition_ = other.whereCondition_;
	return *this;
}


void SelectExpression::interactiveSelect( US numberOfSets )
{
	pColumn col;
	US cno;

	createReport();

	if( numberOfSets == 1 )
		oneSet_ = CQL_YES;

	if( dbsql_.strictLocking() )
		beginStrictLocking();

	evaluate();

	temporaryFile_.ifile()->unbindAllColumns();
	for( col = columns_.first(), cno = 0; col; col = columns_.next(), cno++ )
		temporaryFile_.ifile()->bindColumnAV( cno, col->ColumnExpression().value()->value().avalue(), false, true );

	if( !firstResultRow() )
		throw NoDataException( __FILE__, __LINE__ );

	for( col = columns_.first(), cno = 0; col; col = columns_.next(), cno++ )
		*col->ReportValue() = col->ColumnExpression().value()->value();

	generateReport();
	std::cout << reinterpret_cast< NC* >( report_.bufferBase() );
	std::cout << std::endl;
}


US SelectExpression::dictionaryLength( void )
{
	US size;

	//
	//  flags:
	//    allLinks_
	//    aggregateFunctions_
	//    cartesianProductLink_
	//    correlated_
	//    distinct_
	//    existsSubquery_
	//    groupBy_
	//    groupByVariableLength_ 
	//    having_
	//    noCondition_
	//    noSet_
	//    oneSet_
	//    onlyAggregateFunctions_
	//    orderBy_
	//    orderDescending_
	//    orderTemporary_
	//    setVariableLength_
	//    unionAll_
	//    unionSet_
	//    unique_
	//    usingAggregateIndex_
	//    usingCountIndex_

	size = sizeof( NI ) * 22;

	//
	//  scalars:
	//    UNI existingOrderKey_

	size += ((US)sizeof( UNI ));

	size = ((US)( size + columns_.DictionaryLength() ) );
	size = ((US)( size + groupByColumns_.DictionaryLength() ) );
	size = ((US)( size + havingExp_.dictionaryLength() ) );
	size = ((US)( size + orderByExp_.dictionaryLength() ) );
	size = ((US)( size + tables_.DictionaryLength() ) );
	size = ((US)( size + whereCondition_.dictionaryLength() ) );

	return size;
}


void SelectExpression::makeSets( void )
{
	pPredicate pred;

	if( noSet_ || whereCondition_.resolvedPredicates().size() <= 1 )
		return;

	for( pred = whereCondition_.resolvedPredicates().first(); pred; pred = whereCondition_.resolvedPredicates().next() )
	{
		if( pred->skip() )
			continue;
		pred->makeSet();
	}

	combine();
}


void SelectExpression::combine( void )
{
	whereCondition_.root()->combine();
}


void SelectExpression::swapDataForGroupBy( void )
{
	pExpression exp;

	for( exp = firstExpression(); exp; exp = nextExpression() )
		exp->exchangeValueWithValue2();
}


void SelectExpression::moveGroupColumns( void )
{
	pColumn col;

	for( col = groupByColumns_.first(); col; col = groupByColumns_.next() )
		col->ColumnExpression().copyValueToValue2();
}


void SelectExpression::makeUnique( void )
{
	aggregateDistinctScan_ = CQL_YES;
	createTemporaryFile( uniqueFile_ );
	scalarScan( uniqueFile_, true );
	uniqueEnabled_ = CQL_YES;
	unique_ = true;
	aggregateDistinctScan_ = CQL_NO;
}


void SelectExpression::makeOrder( void )
{
	//
	//  check for existing order key here
	//
	orderTemporary_ = CQL_YES;
	createTemporaryFile( orderFile_ );
	scalarScan( orderFile_, false );
	orderEnabled_ = CQL_YES;
}


bool SelectExpression::uniqueFirst( void )
{
	uniqueFile_.bindBaseTablePositions();
	uniqueFile_.ifile()->beginIsamOperation( 0 );
	if( !uniqueFile_.ifile()->firstRow() )
		return false;
	uniqueFile_.getBaseTablePositions( baseTablePositionBuffer_ );
	refetchBaseTableRows();
	return true;
}


bool SelectExpression::uniqueNext( void )
{
	if( !uniqueFile_.ifile()->nextRow() )
		return false;
	uniqueFile_.getBaseTablePositions( baseTablePositionBuffer_ );
	refetchBaseTableRows();
	return true;
}


void SelectExpression::bindToTemporaryFile( TemporaryResultFile& tempfile )
{
	Column *col;
	US loop;
	for( col = columns_.first(), loop = 0; col; col = columns_.next(), loop++ )
	{
		Expression& exp = col->ColumnExpression();
		tempfile.ifile()->bindColumnAV( loop, exp.value()->value().avalue(), false, true );
		if( dataTracing )
			hAEnv->logPrintf(AbstractLogger::TRACEALL, "Result set, data column %d, value %s\n", loop, exp.value()->value().avalue().asString().text() );
	}

	if( orderBy_ )
	{
		ExpressionColumnListElement *expCol;
		for( expCol = orderByExp_.columns().first(); expCol; expCol = orderByExp_.columns().next(), loop++ )
		{
			AbstractValue& av = expCol->Column()->createValue()->value().avalue();
			tempfile.ifile()->bindColumnAV( loop, av, true, true );
			if( dataTracing )
				hAEnv->logPrintf(AbstractLogger::TRACEALL, "Result set, order column, value %s\n", av.asString().text() );
		}
	}
	
	if( groupBy_ )
	{
		for( col = groupByColumns_.first(); col; col = groupByColumns_.next(), loop++ )
		{
			tempfile.ifile()->bindColumnAV( loop, col->ColumnExpression().value()->value().avalue(), true, true );
			if( dataTracing )
				hAEnv->logPrintf(AbstractLogger::TRACEALL, "Result set, group by column, value %s\n", col->ColumnExpression().value()->value().avalue().asString().text() );
		}
	}

	if( having_ )
	{
		tempfile.ifile()->bindColumnAV( loop++, havingExp_.value()->value().avalue(), true, true );
		if( dataTracing )
			hAEnv->logPrintf(AbstractLogger::TRACEALL, "Result set, having expression, value %s\n", havingExp_.value()->value().avalue().asString().text() );
	}
}


bool SelectExpression::orderTemporaryFirst( void )
{
	bindToTemporaryFile( orderFile_ );
	orderFile_.bindBaseTablePositions();
	orderFile_.ifile()->beginIsamOperation( 0 );
	if( !orderFile_.ifile()->firstRow() )
		return false;
	orderFile_.getBaseTablePositions( baseTablePositionBuffer_ );
	refetchBaseTableRows();
	return true;
}


bool SelectExpression::orderTemporaryNext( void )
{
	bindToTemporaryFile( orderFile_ );

	if( !orderFile_.ifile()->nextRow() )
		return false;

	orderFile_.getBaseTablePositions( baseTablePositionBuffer_ );
	refetchBaseTableRows();
	return true;
}


bool SelectExpression::doLinks( void )
{
	OptimizerPredicateList& linkPreds = whereCondition_.linkPredicates();
	UNI nlinks = linkPreds.size();
	pPredicate pred;

	linkState_ = START;

	if( nlinks == 0 )
	{
		if( tables_.size() == 1 )
			return true;

		return doCartesianProductLink();
	}

	for( pred = linkPreds.first(); pred; pred = linkPreds.next() )
		pred->zeroSlavePosition();

	for( pred = linkPreds.last(); pred; pred = linkPreds.prev() )
	{
		pred->clearTeof();
		if( pred->skip() )
			continue;

		if( !pred->resolveLink() )
			return false;
	}

	return true;
}


bool SelectExpression::doCartesianProductLink( void )
{
	pTableTableElement ttEl;

	for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
	{
		ttEl->clearCartesianProductCount();
		if( !ttEl->firstRow( 0 ) )
			return false;
	}

	return true;
}


bool SelectExpression::moreCartesianProductLinks( void )
{
	pTableTableElement ttEl, nextTtEl, nextNextTtEl;
	bool result;

	if( tables_.size() == 2 )
	{
		ttEl = tables_.last();
		return ttEl->nextRow();
	}

	ttEl = tables_.first();
	nextTtEl = tables_.next();

	if( nextTtEl->cartesianProductCount() != 0 )
		return false;

	while( nextTtEl != ((pTableTableElement)0) )
	{
		if( nextTtEl->cartesianProductCount() > ttEl->cartesianProductCount() )
			break;

		ttEl = nextTtEl;
		nextTtEl = tables_.next();
	}

	result = nextTtEl->nextRow();
	nextNextTtEl = tables_.next();
	if( !result )
	{
		if( !nextNextTtEl )
		{
			result = false;
			return CQL_SUCCESS;
		}

		nextTtEl->incrementCartesianProductCount();
		if( !moreCartesianProductLinks() )
			return false;
	}

	while( nextNextTtEl )
	{
		if( !nextNextTtEl->firstRow( 0 ) )
			return false;

		nextNextTtEl->clearCartesianProductCount();
		nextNextTtEl = tables_.next();
	}

	return true;
}


bool SelectExpression::moreLinks( void )
{
	OptimizerPredicateList& linkPreds = whereCondition_.linkPredicates();
	UNI nlinks = linkPreds.size();
	pPredicate pred, pred2;

	if( nlinks == 0 )
	{
		if( tables_.size() == 1 )
			return true;

		return moreCartesianProductLinks();
	}

	//
	//  For MoreLinks, if any link is resolved, we are done. if a link
	//  fails to resolve, we must mark it and proceed to the next link.
	//  When all links fail to resolve, then MoreLinks fails
	//

	for( pred = linkPreds.first(); pred; pred = linkPreds.next() )
	{
		if( linkState_ == RETRY )
		{
			linkState_ = SHIFT;
			pred = pred->prev();
		}

		if( pred->skip() )
			continue;

		if( pred->resolveNextLinkWithIndex() )
		{
			correlatedLink_ = CQL_NO;

			if( linkState_ == SHIFT )
			{
				linkState_ = START;

				for( pred2 = pred->prev(); pred2; pred2 = pred2->prev() )
				{
					if( pred2->skip() )
						continue;

					if( !pred2->resolveLinkWithIndex() )
						linkState_ = RETRY;
				}
			}

			if( linkState_ != RETRY )
				return true;
		}
		else
		{
			linkState_ = SHIFT;
			if( pred->correlatedLink() )
				correlatedLink_ = true;
		}
	}

	return false;
}


bool SelectExpression::memorySetFirst( pTableTableElement ttEl, pPredicate pred )
{
	pTableSpecification table = ttEl->tableSpec();
	pred->setFile()->bindColumn( 0, pred->position(), pred->positionNull(), false );
	pred->setFile()->beginIsamOperation( 0 );
	if( !pred->setFile()->firstRow() )
		return false;
	table->file()->establishPosition( pred->position(), 0, true );
	return true;
}


bool SelectExpression::memorySetNext( pTableTableElement ttEl, pPredicate pred )
{
	pTableSpecification table = ttEl->tableSpec();
	if( !pred->setFile()->nextRow() )
		return false;
	table->file()->establishPosition( pred->position(), 0, true );
	return true;
}


void SelectExpression::checkView( pAbstractTableSpecification )
{
}


bool SelectExpression::assignmentCompatible( Column& col, PermanentColumnSpecification& pcs )
{
	switch( col.ColumnExpression().valueExpressionType().typeType() )
	{
	case CQL_CHAR :
	case CQL_CHARUC :
		switch( pcs.type().typeType() )
		{
		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
			return true;

		default :
			return false;
		}

	case CQL_DECIMAL :
		switch( pcs.type().typeType() )
		{
		case CQL_COLUMN_UNDEFINED_TYPE :
			throw InternalErrorException( __FILE__, __LINE__ );

		case CQL_BIGINT :
		case CQL_BIT :
		case CQL_DECIMAL :
		case CQL_FLOAT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_SMALLINT :
		case CQL_TINYINT :
			return true;

		default :
			return false;
		}

	case CQL_FLOAT :
		switch( pcs.type().typeType() )
		{
		case CQL_COLUMN_UNDEFINED_TYPE :
			throw InternalErrorException( __FILE__, __LINE__ );

		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_DECIMAL :
			return true;

		default :
			return false;
		}

	case CQL_DATE :
		switch( pcs.type().typeType() )
		{
		case CQL_COLUMN_UNDEFINED_TYPE :
			throw InternalErrorException( __FILE__, __LINE__ );

		case CQL_DATE :
			return true;

		default :
			return false;
		}

	case CQL_TIMESTAMP :
		switch( pcs.type().typeType() )
		{
		case CQL_COLUMN_UNDEFINED_TYPE :
			throw InternalErrorException( __FILE__, __LINE__ );

		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
			return true;

		default :
			return false;
		}

	case CQL_COLUMN_UNDEFINED_TYPE :
	default :
		break;
	}

	throw InternalErrorException( __FILE__, __LINE__ );
}


void SelectExpression::checkInsertValues( InsertColumnNameList& insertColumnNames )
{
	pColumn col;
	pInsertColumnName icn;

	if( columns_.SetExpressionTypes( &dbsql_ ) == CQL_FAILURE )
		throw InternalErrorException( __FILE__, __LINE__ );

	for( col = columns_.first(), icn = insertColumnNames.first(); col; col = columns_.next(), icn = insertColumnNames.next() )
		if( !assignmentCompatible( *col, icn->pcs() ) )
			throw IncompatibleTypesException( __FILE__, __LINE__ );
}


void SelectExpression::copyInsertValues( pAbstractTableSpecification table, InsertColumnNameList& insertColumnNames )
{
	pInsertColumnName icn;
	pColumn col;

	for( col = columns_.first(), icn = insertColumnNames.first(); col; col = columns_.next(), icn = insertColumnNames.next() )
		table->assignValue( *col, icn->pcs() );
}


CqlConstants::CompareResult SelectExpression::compareGroupColumns( void )
{
	pColumn col;

	for( col = groupByColumns_.first(); col; col = groupByColumns_.next() )
	{
		if( *col->ColumnExpression().value() == *col->ColumnExpression().value2() )
			continue;
		else if( col->ColumnExpression().value() < col->ColumnExpression().value2() )
			return THIS_LESS_THAN_OTHER;
		else
			return THIS_GREATER_THAN_OTHER;
	}

	return THIS_EQUAL_TO_OTHER;
}


void SelectExpression::cleanup( void )
{
	TripleStringListElement *tsl;
	Column *col;
	SelectExpression *select;

	if( cleanedUp_ )
		return;

	//
	//  cleanup any subqueries
	//
	if( ( select = nextSelectExpression() ) != 0 )
		select->cleanup();

	cleanupReport();

	if( temporaryFileExists_ == CQL_YES )
		temporaryFile_.cleanup();

	if( orderEnabled_ == CQL_YES )
		orderFile_.cleanup();

	if( uniqueEnabled_ == CQL_YES )
		uniqueFile_.cleanup();

	if( updateEnabled_ == CQL_YES )
		updateFile_.cleanup();

	if( rowList_ )
	{
		rowList_->close();
		delete rowList_;
		rowList_ = 0;
	}

	aggregateFunctions_ = false;
	cartesianProductLink_ = false;
	correlated_ = false;
	finalTrip_ = false;
	firstInExpression_ = false;
	firstScan_ = false;
	groupBy_ = false;
	groupByVariableLength_  = false;
	having_ = false;
	linksSorted_ = false;
	listOperationInProgress_ = false;
	logicalFetch_ = false;
	midGroup_ = false;
	noCondition_ = false;
	noSet_ = false;
	notFlag_ = false;
	oneSet_ = false;
	onlyAggregateFunctions_ = false;
	orderBy_ = false;
	orderDescending_ = false;
	orderEnabled_ = false;
	orderTemporary_ = false;
	refetchOK_ = false;
	refetchMode_ = false;
	setVariableLength_ = false;
	temporaryFileExists_ = false;
	unionAll_ = false;
	unionSet_ = false;
	unique_ = false;
	uniqueEnabled_ = false;
	updateEnabled_ = false;
	usingAggregateIndex_ = false;
	usingCountIndex_ = false;

	for( tsl = tableNames_.first(); tsl; tsl = tableNames_.next() )
	{
		tsl->s1().reset();
		tsl->s2().reset();
		tsl->s3().reset();
	}

	tableNames_.destroy();

	tables_.viewCleanup();
	tables_.clearConditions();
	tables_.destroy();
	tables_.ClearProcessed();
	for( col = columns_.first(); col; col = columns_.next() )
		col->ColumnExpression().reset();
	columns_.destroy();
	orderByExp_.reset();
	for( col = groupByColumns_.first(); col; col = groupByColumns_.next() )
		col->ColumnExpression().reset();
	groupByColumns_.destroy();
	havingExp_.reset();
	whereCondition_.reset();
	if( baseTablePositionBuffer_ )
	{
		delete [] baseTablePositionBuffer_;
		baseTablePositionBuffer_ = ((pUC)0);
	}

#if 0
	dbsql_.ResetIfCloseWithPendingTransaction();
#endif
	cleanedUp_ = true;
}


void SelectExpression::viewCleanup( void )
{
	if( temporaryFileExists_ == CQL_YES )
		temporaryFile_.cleanup();
	temporaryFileExists_ = false;

	if( orderEnabled_ == CQL_YES )
		orderFile_.cleanup();
	orderEnabled_ = false;
	orderTemporary_ = false;

	if( uniqueEnabled_ == CQL_YES )
		uniqueFile_.cleanup();
	unique_ = uniqueEnabled_ = false;

	if( rowList_ )
	{
		rowList_->close();
		delete rowList_;
		rowList_ = 0;
	}

	Column *col;
	for( col = groupByColumns_.first(); col; col = groupByColumns_.next() )
		col->ColumnExpression().viewReset();

	mostRecentHavingResult_ = nextMostRecentHavingResult_ = midGroup_ = endGroup_ = false;
}


void SelectExpression::checkForAllLinks( void )
{
	allLinks_ = whereCondition_.allLinks();
}


US SelectExpression::numberOfBaseTables( void )
{
	pTableTableElement ttEl;
	UNI ntables = 0;

	for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
		ntables += ttEl->absTableSpec()->numberOfBaseTables();

	return static_cast< US >( ntables );
}


void SelectExpression::allocateBaseTablePositionBuffer( UNI size )
{
	if( baseTablePositionBuffer_ )
	{
		if( size <= baseTablePositionBufferSize_  )
			return;

		delete [] baseTablePositionBuffer_;
	}

	baseTablePositionBuffer_ = new UC[ size ];
	if( !baseTablePositionBuffer_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	baseTablePositionBufferSize_  = size;
}


void SelectExpression::retrieveBaseTablePositions( void )
{
	pTableTableElement ttEl;
	pUC p = baseTablePositionBuffer_;

	if( !baseTablePositionBuffer_ )
		throw InternalErrorException( __FILE__, __LINE__ );

	for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
		ttEl->absTableSpec()->retrieveBaseTablePositions( &p );
}


void SelectExpression::refetchBaseTableRows( void )
{
	pTableTableElement ttEl;
	pUC p = baseTablePositionBuffer_;

	if( !baseTablePositionBuffer_ )
		throw InternalErrorException( __FILE__, __LINE__ );

	for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
		ttEl->absTableSpec()->retrieveBaseTableRows( &p );
}


Expression *SelectExpression::firstExpression( void )
{
	pColumn col;

	columnProgressionState_ = SELECT_LIST_COLUMNS;
	col = columns_.first();
	return col->ColumnExpressionAddress();
}


Expression *SelectExpression::nextExpression( void )
{
	pColumn col;

	switch( columnProgressionState_ )
	{
	case SELECT_LIST_COLUMNS :
		col = columns_.next();
		if( col )
			return col->ColumnExpressionAddress();

		if( !noCondition_ )
		{
			columnProgressionState_ = WHERE_CONDITION;
			return &whereCondition_;
		}
		//  deliberate fall through

	case WHERE_CONDITION :
		col = groupByColumns_.first();
		if( col )
		{
			columnProgressionState_ = GROUP_BY_COLUMNS;
			return col->ColumnExpressionAddress();
		}
		if( having_ == CQL_YES )
		{
			columnProgressionState_ = HAVING_CONDITION;
			return &havingExp_;
		}
		return 0;

	case GROUP_BY_COLUMNS :
		col = groupByColumns_.next();
		if( col )
			return col->ColumnExpressionAddress();
		if( having_ == CQL_YES )
		{
			columnProgressionState_ = HAVING_CONDITION;
			return &havingExp_;
		}
		return 0;

	case HAVING_CONDITION :
		return 0;

	case ORDER_CONDITION :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	return 0;
}


void SelectExpression::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << allLinks_
		   << aggregateFunctions_
		   << cartesianProductLink_
		   << correlated_
		   << distinct_
		   << existsSubquery_
		   << groupBy_
		   << groupByVariableLength_ 
		   << having_
		   << noCondition_
		   << noSet_
		   << oneSet_
		   << onlyAggregateFunctions_
		   << orderBy_
		   << orderDescending_
		   << orderTemporary_
		   << setVariableLength_
		   << unionAll_
		   << unionSet_
		   << unique_
		   << usingAggregateIndex_
		   << usingCountIndex_
		   << existingOrderKey_;

	columns_.writeDictionaryInformation( buffer );
	groupByColumns_.writeDictionaryInformation( buffer );
	havingExp_.writeDictionaryInformation( buffer );
	orderByExp_.writeDictionaryInformation( buffer );
	tableNames_.writeDictionaryInformation( buffer );
	whereCondition_.writeDictionaryInformation( buffer );
}


void SelectExpression::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> allLinks_
		   >> aggregateFunctions_
		   >> cartesianProductLink_
		   >> correlated_
		   >> distinct_
		   >> existsSubquery_
		   >> groupBy_
		   >> groupByVariableLength_ 
		   >> having_
		   >> noCondition_
		   >> noSet_
		   >> oneSet_
		   >> onlyAggregateFunctions_
		   >> orderBy_
		   >> orderDescending_
		   >> orderTemporary_
		   >> setVariableLength_
		   >> unionAll_
		   >> unionSet_
		   >> unique_
		   >> usingAggregateIndex_
		   >> usingCountIndex_
		   >> existingOrderKey_;

	columns_.readDictionaryInformation( buffer );
	groupByColumns_.readDictionaryInformation( buffer );
	havingExp_.readDictionaryInformation( buffer );
	orderByExp_.readDictionaryInformation( buffer );
	tableNames_.readDictionaryInformation( buffer );
	whereCondition_.readDictionaryInformation( buffer );
}


void SelectExpression::createUpdateListFile( pTableTableElement table )
{
	UNI loop;
	pAbstractColumnDescriptor colDesc;
	pAbstractTable file;
	pAbstractTableSpecification absTableSpec = table->absTableSpec();
	pAbstractTable atable;

	//  count the base table columns_
	UNI numberOfBaseTableColumns;
	for( colDesc = absTableSpec->firstBaseTableColumn( &file ), numberOfBaseTableColumns = 0; colDesc; colDesc = absTableSpec->nextBaseTableColumn( &file ), numberOfBaseTableColumns++ )
		;

	//  Columns + record IDs plus end marker
	UNI numberOfUpdateListColumns = numberOfBaseTableColumns + 2;

	CqlColumnTypes **columnSpecifiers = new CqlColumnTypes*[ numberOfUpdateListColumns ];  //  +1 for end marker
	if( !columnSpecifiers )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	for( colDesc = absTableSpec->firstBaseTableColumn( &file ), loop = 0; colDesc; colDesc = absTableSpec->nextBaseTableColumn( &file ), loop++ )
	{
		NC nameBuf[ 100 ];
		sprintf( nameBuf, "col%d", loop );
		columnSpecifiers[ loop ] = new CqlColumnTypes( colDesc->columnType() );
		if( !columnSpecifiers[ loop ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}
	allocateBaseTablePositionBuffer( numberOfBaseTables() * sizeof( RECID ) );
	columnSpecifiers[ loop ] = new CqlColumnTypes( "recordIDs", CQL_BINARY, baseTablePositionBufferSize_  );
	if( !columnSpecifiers[ loop ] )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	updateFile_.refetchInfoColumnNumber( static_cast< US >( loop ) );
	updateFile_.refetchInfoAlloc( static_cast< US >( baseTablePositionBufferSize_ ) );
	loop++;

	columnSpecifiers[ loop ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );
	if( !columnSpecifiers[ loop ] )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	AccessorTypes *keyDescriptors[ 2 ];
	SegmentTypes *segs[ 2 ];
	keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, segs );
	segs[ 0 ] = new SegmentTypes( "col0", 0, SegmentTypes::CQL_ASCENDING );
	segs[ 1 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
	keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

	atable = AbstractTable::createObject( dbsql_.aHandle(), CQL_CQL_TEMPORARY );

	atable->create( CQL_CQL_TEMPORARY, dbsql_.temporaryName(), columnSpecifiers, keyDescriptors );

	delete keyDescriptors[ 0 ];
	delete keyDescriptors[ 1 ];
	delete segs[ 0 ];
	delete segs[ 1 ];

	for( colDesc = absTableSpec->firstBaseTableColumn( &file ), loop = 0; colDesc; colDesc = absTableSpec->nextBaseTableColumn( &file ), loop++ )
		delete columnSpecifiers[ loop ];
	delete columnSpecifiers[ loop ];  //  row IDs

	delete [] columnSpecifiers;

	updateFile_.ifile( atable );
	updateEnabled_ = true;
	updateFile_.bindBaseTablePositions();
}


bool SelectExpression::updateListFirst( void )
{
	updateFile_.ifile()->beginIsamOperation( 0 );
	if( !updateFile_.ifile()->firstRow() )
		return false;

	return true;
}


bool SelectExpression::updateListNext( void )
{
	pTableTableElement table = tables_.first();
	pAbstractTableSpecification absTableSpec = table->absTableSpec();

	absTableSpec->beginRowOperation();
	if( !updateFile_.ifile()->nextRow() )
		return false;

	return true;
}


void SelectExpression::createRowListFile( void )
{
	//  do this first so that baseTablePositionBufferSize_ is valid
	allocateBaseTablePositionBuffer( numberOfBaseTables() * sizeof( RECID ) );

	CqlColumnTypes *columnDescriptors[ 2 ];
	columnDescriptors[ 0 ] = new CqlColumnTypes( "recordIDs", CQL_BINARY, baseTablePositionBufferSize_  ),
	columnDescriptors[ 1 ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );

	AccessorTypes *keyDescriptors[ 2 ];
	SegmentTypes *segs[ 2 ];
	keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, segs );
	segs[ 0 ] = new SegmentTypes( "recordIDs", 0, SegmentTypes::CQL_ASCENDING );
	segs[ 1 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
	keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

	rowList_ = AbstractTable::createObject( dbsql_.aHandle(), CQL_CQL_TEMPORARY );
	rowList_->create( CQL_CQL_TEMPORARY, dbsql_.temporaryName(), columnDescriptors, keyDescriptors );

	delete columnDescriptors[ 0 ];
	delete columnDescriptors[ 1 ];
	delete keyDescriptors[ 0 ];
	delete segs[ 0 ];
	delete segs[ 1 ];
	delete keyDescriptors[ 1 ];

	rowList_->bindColumn( 0, baseTablePositionBuffer_, baseTablePositionBufferSize_ , rowListNullflag_, true, false );
}


void SelectExpression::addToRowList( void )
{
	rowList_->beginRowOperation();

	retrieveBaseTablePositions();
	rowList_->addRow();
}


bool SelectExpression::rowListFirst( void )
{
	rowList_->beginIsamOperation( 0 );
	if( !rowList_->firstRow() )
		return false;
	rowListPosition_ = rowList_->currentPosition();
	refetchBaseTableRows();
	return true;
}


bool SelectExpression::rowListNext( void )
{
	rowList_->establishPosition( rowListPosition_, 0, true );
	if( !rowList_->nextRow() )
		return false;
	rowListPosition_ = rowList_->currentPosition();
	refetchBaseTableRows();
	return true;
}


void SelectExpression::createReport( void )
{
	pColumn col;
	pReportField repField;
	pReportWindow repWindow;
	UNI _position, columnLength = 0, labelLength;
	const char *columnLabel;

	report_.date().setToCurrentDate();
	repWindow = new ReportWindow;
	if( !repWindow )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	report_.Bodies().add( repWindow );

	for( col = columns_.first(), _position = 0; col; col = columns_.next() )
	{
		col->createReportValue();

		repField = new ReportField;
		if( !repField )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		repField->SetCol( col );
		repField->SetColumn( _position );
		report_.Bodies().current()->fields().add( repField );

		switch( col->ColumnExpression().valueExpressionType().typeType() )
		{
		case CQL_CHAR :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_CHARUC :
			columnLength = col->ColumnExpression().valueExpressionLength();
			break;

		case CQL_DECIMAL :
			columnLength = 18;
			break;

		case CQL_SMALLINT :
			columnLength = 6;
			break;

		case CQL_INTEGER :
			columnLength = 11;
			break;

		case CQL_REAL :
			columnLength = 9;
			break;

		case CQL_FLOAT :
			columnLength = 19;
			break;

		case CQL_BIT :
			columnLength = 1;
			break;

		case CQL_TINYINT :
			columnLength = 4;
			break;

		case CQL_BIGINT :
			columnLength = 21;
			break;

		case CQL_DATE :
			columnLength = 10;
			break;

		case CQL_TIME :
			columnLength = 8;
			break;

		case CQL_TIMESTAMP :
			columnLength = 24;
			break;

		case CQL_COLUMN_UNDEFINED_TYPE :
			throw InternalErrorException( __FILE__, __LINE__ );
		}

		repField = new ReportField;
		if( !repField )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		columnLabel = const_cast<const char *>(col->ColumnExpression().label().text());
		if( !columnLabel || !columnLabel[ 0 ] )
			columnLabel = col->Label().text();
		repField->Output() = columnLabel;
		repField->SetColumn( _position );
		report_.Header().fields().add( repField );
		labelLength = strlen( columnLabel );
		if( columnLength > labelLength )
			_position += columnLength + 1;
		else
			_position += labelLength + 1;
	}

	report_.advance( CAdvance );
	report_.SetUserParameter( this );
}


void SelectExpression::beginStrictLocking( void )
{
}


void SelectExpression::evaluate( void )
{
	cursorEvaluate();
}


bool SelectExpression::firstResultRow( void )
{
	temporaryFile_.ifile()->beginIsamOperation( 0 );
	return temporaryFile_.ifile()->firstRow();
}


bool SelectExpression::nextResultRow( void )
{
	return temporaryFile_.ifile()->nextRow();
}


void SelectExpression::generateReport( void )
{
	if( report_.Initialize( &dbsql_ ) == CQL_FAILURE )
		throw ReportGenerationException( __FILE__, __LINE__ );

	if( report_.Run( &dbsql_ ) == CQL_FAILURE )
		throw ReportGenerationException( __FILE__, __LINE__ );

	if( report_.Cleanup() == CQL_FAILURE )
		throw ReportGenerationException( __FILE__, __LINE__ );
}


#if 0

void SelectExpression::assignForUpdate( AbstractTableSpecification *absTableSpec, UpdateColumnNameAndExpList& updateColumns )
{
	UpdateColumnNameAndExp *updateValue;
	US loop;

	for( updateValue = updateColumns.first(), loop = 0; updateValue; updateValue = updateColumns.next(), loop++ )
	{
		AbstractTable *atable = absTableSpec->baseTable( loop );
		atable->beginRowOperation();
	}

	for( updateValue = updateColumns.first(), loop = 0; updateValue; updateValue = updateColumns.next(), loop++ )
	{
		Expression& exp = updateValue->exp();
		exp.evaluate();
		exp.convertValueToAssignmentType( *updateValue->colSpec() );
		AbstractTable *atable = absTableSpec->baseTable( loop );
		atable->bindColumnAV( updateValue->colSpec()->Cno(), exp.value()->value().avalue() );
	}
}

#endif


void SelectExpression::bindColumnsForUpdate( TableTableElement& ttEl, UpdateColumnNameAndExpList& updateColumns )
{
	AbstractTableSpecification *absTableSpec = ttEl.absTableSpec();
	UNI loop;

	AbstractColumnDescriptor *colDesc;
	AbstractTable *file;

	for( colDesc = absTableSpec->firstBaseTableColumn( &file ), loop = 0; colDesc; colDesc = absTableSpec->nextBaseTableColumn( &file ), loop++ )
	{
		AbstractType *at = file->getColumnValue( colDesc->columnNumber() );
		updateFile_.ifile()->bindColumnAV( static_cast< US >( loop ), at->avalue(), true, true );
		if( dataTracing )
			hAEnv->logPrintf(AbstractLogger::TRACEALL, "bindColumnsForUpdate, column %d, value %s\n", loop, at->avalue().asString().text() );
	}

	UpdateColumnNameAndExp *updateValue;

	for( updateValue = updateColumns.first(), loop = 0; updateValue; updateValue = updateColumns.next(), loop++ )
	{
		Expression& exp = updateValue->exp();
		exp.evaluate();
		exp.convertValueToAssignmentType( *updateValue->colSpec() );
		updateFile_.ifile()->bindColumnAV( updateValue->colSpec()->Cno(), exp.value()->value().avalue(), true, true );
		if( dataTracing )
			hAEnv->logPrintf(AbstractLogger::TRACEALL, "bindColumnsForUpdate, rebinding column %d, value %s\n", loop, exp.value()->value().avalue().asString().text() );
	}

	retrieveBaseTablePositions();
	updateFile_.setBaseTablePositions( baseTablePositionBuffer_ );
}


void SelectExpression::addToUpdateList( void )
{
	updateFile_.ifile()->beginRowOperation();
	updateFile_.ifile()->addRow();
}


void SelectExpression::checkForVariableLength( void )
{
	pTableTableElement ttEl;
	pAbstractTableSpecification abstractTable;

	for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
	{
		abstractTable = ttEl->absTableSpec();
		if( abstractTable->variableLength() )
		{
			setVariableLength_ = CQL_YES;
			return;
		}
	}

	setVariableLength_ = CQL_NO;
}


void SelectExpression::setQueryExpressionResultSet( pQueryExpression qexp )
{
	qexp->resultSet( *temporaryFile_.ifile() );
	temporaryFileExists_ = false;
}


void SelectExpression::createTemporaryFile( TemporaryResultFile& tempFile )
{
	pColumn col;
	UNI firstOrderColumn, lastOrderColumn, loop, numberOfColumns, positionBufferSize;
	CqlColumnTypes type;

	if( tempFile.ifile() )
	{
		delete tempFile.ifile();
		tempFile.ifile( 0 );
	}

	for( col = columns_.first(), numberOfColumns = 0; col; col = columns_.next(), numberOfColumns++ )
		;
	if( orderBy_ )
		numberOfColumns += orderByExp_.columns().size();

	if( groupBy_ )
		numberOfColumns += groupByColumns_.size();

	if( having_ )
		numberOfColumns++;
	
	numberOfColumns++;  //  for position buffer

	CqlColumnTypes **columnSpecifiers = new CqlColumnTypes*[ numberOfColumns + 1 ];  //  +1 for end marker
	if( !columnSpecifiers )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	for( col = columns_.first(), firstOrderColumn = lastOrderColumn = loop = 0; col; col = columns_.next(), lastOrderColumn++, loop++ )
	{
		Expression& exp = col->ColumnExpression();

		if( aggregateDistinctScan_ == ((BFT)CQL_NO) )
		{
			type = exp.valueExpressionType();

			if( (type.typeType() == CQL_CHAR || type.typeType() == CQL_CHARUC) && type.typeLength() == 0 )
				type = CQL_LONGVARCHAR;
		}
		else
		{
			if( exp.uniqueScanType().typeType() == CQL_COLUMN_UNDEFINED_TYPE )
				type = exp.valueExpressionType();
			else
				type = exp.uniqueScanType();
		}
		NC nameBuf[ 100 ];
		sprintf( nameBuf, "DataCol%d", loop );
		type.typeName() = nameBuf;
		columnSpecifiers[ loop ] = new CqlColumnTypes( type );
		if( !columnSpecifiers[ loop ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	if( orderBy_ == CQL_YES )
	{
		//  Explicit order by overrides default order column list
		ExpressionColumnListElement *expCol;
		for( firstOrderColumn = lastOrderColumn, expCol = orderByExp_.columns().first();  expCol; expCol = orderByExp_.columns().next(), loop++ )
		{
			NC nameBuf[ 100 ];
			sprintf( nameBuf, "OrderCol%d", loop );
			expCol->Column()->typeR().typeName() = nameBuf;
			columnSpecifiers[ loop ] = new CqlColumnTypes( expCol->Column()->type() );
			if( !columnSpecifiers[ loop ] )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		lastOrderColumn = loop;
	}

	if( groupBy_ == CQL_YES )
	{
		for( col = groupByColumns_.first(); col; col = groupByColumns_.next(), loop++ )
		{
			NC nameBuf[ 100 ];
			sprintf( nameBuf, "GroupCol%d", loop );
			Expression& exp = col->ColumnExpression();
			exp.valueExpressionType().typeName() = nameBuf;
			columnSpecifiers[ loop ] = new CqlColumnTypes( exp.valueExpressionType() );
			if( !columnSpecifiers[ loop ] )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
	}

	if( having_ )
	{
		havingExp_.valueExpressionType().typeName() = "havingExpression";
		columnSpecifiers[ loop ] = new CqlColumnTypes( havingExp_.valueExpressionType() );
		if( !columnSpecifiers[ loop ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		loop++;
	}

	//  The column number for refetch information is one past the last data column.
	//  The last data column is numberOfColumns - 1.
	tempFile.refetchInfoColumnNumber( static_cast< US >( numberOfColumns - 1 ) );
	US nBaseTables = numberOfBaseTables();
	positionBufferSize = nBaseTables * sizeof( RECID );
	tempFile.refetchInfoAlloc( static_cast< US >( positionBufferSize ) );
	columnSpecifiers[ loop ] = new CqlColumnTypes( "recordIDs", CQL_BINARY, positionBufferSize );
	if( !columnSpecifiers[ loop ] )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	loop++;
	//  For base tables, this duplicates the information in TemporaryResultFile.
	//  It may be necessary to create the row list file.
	allocateBaseTablePositionBuffer( positionBufferSize );

	columnSpecifiers[ loop ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );
	if( !columnSpecifiers[ loop ] )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	UNI numberOfOrderColumns = lastOrderColumn - firstOrderColumn;
	SegmentTypes **stypes = new SegmentTypes*[ numberOfOrderColumns + 1 ];
	if( !stypes )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	UNI segNumber;
	if( orderBy_ )
	{
		ExpressionColumnListElement *expCol;
		UNI columnListColumnNumber;
		for( expCol = orderByExp_.columns().first(), segNumber = 0, columnListColumnNumber = firstOrderColumn;  expCol; expCol = orderByExp_.columns().next(), loop++, segNumber++, columnListColumnNumber++ )
		{
			if( orderDescending_ )
				stypes[ segNumber ] = new SegmentTypes( columnSpecifiers[ columnListColumnNumber ]->typeName(), static_cast< S >( columnListColumnNumber ), SegmentTypes::CQL_DESCENDING );
			else
				stypes[ segNumber ] = new SegmentTypes( columnSpecifiers[ columnListColumnNumber ]->typeName(), static_cast< S >( columnListColumnNumber ), SegmentTypes::CQL_ASCENDING );

			if( !stypes[ segNumber ] )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
	}
	else
	{
		for( segNumber = 0, loop = firstOrderColumn; loop < lastOrderColumn; segNumber++, loop++ )
		{
			NC nameBuf[ 100 ];
			sprintf( nameBuf, "DataCol%d", loop );
			stypes[ segNumber ] = new SegmentTypes( nameBuf, static_cast< S >( loop ), SegmentTypes::CQL_ASCENDING );
			if( !stypes[ segNumber ] )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
	}
	stypes[ segNumber ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
	AccessorTypes *keyDescriptors[ 2 ];

	if( distinct_ )
		keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, stypes );
	else
		keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_DUPLICATES_ALLOWED, stypes );

	keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

	AbstractTable *at = AbstractTable::createObject( dbsql_.aHandle(), CQL_CQL_TEMPORARY );
	tempFile.ifile( at );

	tempFile.ifile()->create( CQL_CQL_TEMPORARY, dbsql_.temporaryName(), columnSpecifiers, keyDescriptors );
}


void SelectExpression::cursorEvaluate( void )
{
	checkForVariableLength();
	computeDataLength();
	createTemporaryFile( temporaryFile_ );
	temporaryFileExists_ = CQL_YES;

	if( unique_ )
		makeUnique();

	if( groupBy_ )
		makeOrder();

	if( dbsql_.strictLocking() && aggregateFunctions_ )
		magicLock();

	if( existsSubquery_ == CQL_YES )
	{
		existsScan();
		return;
	}

	if( aggregateFunctions_ && !groupBy_ )
		aggregateScan();
	else if( groupBy_ )
		groupScan();
	else
		scalarScan( temporaryFile_, true );
}


void SelectExpression::aggregateScan( void )
{
	bool result;

	//  scan the rows.  For loop does the work, body deliberately empty.
	for( result = scanFirst(); result; result = scanNext() )
		;

	//
	//  if subquery evaluation produced error because no rows were found, reset the error
	//
	if( dbsql_.errorCode() == ZERO_ROWS_IN_SUBQUERY )
		dbsql_.resetError();

	postFunctionProcessing();
	addRowToResultSet( temporaryFile_ );
	clearAggregateValues();
}


void SelectExpression::groupScan( void )
{
	CompareResult compareResult;

	setFunctionSpaceNull();
	if( !scanFirst() )
		throw NoDataException( __FILE__, __LINE__ );
	moveGroupColumns();

	for( ; ; )
	{
		swapDataForGroupBy();
		nextMostRecentHavingResult_ = mostRecentHavingResult_;

		if( !scanNext() )
		{
			swapDataForGroupBy();

			if( !having_ || nextMostRecentHavingResult_ == CQL_YES )
				addRowToResultSet( temporaryFile_ );

			break;
		}

		compareResult = compareGroupColumns();
		if( compareResult != THIS_EQUAL_TO_OTHER )
		{
			swapDataForGroupBy();

			if( !having_ || nextMostRecentHavingResult_ == CQL_YES )
				addRowToResultSet( temporaryFile_ );

			swapDataForGroupBy();
			setFunctionSpaceNull();
			runColumnExpressions();
			moveGroupColumns();
		}
	}
}


void SelectExpression::scalarScan( TemporaryResultFile& tempFile, bool unbindAfterScan )
{
	if( !scanFirst() )
		throw NoDataException( __FILE__, __LINE__ );

	addRowToResultSet( tempFile );

	while( scanNext() )
		addRowToResultSet(tempFile );

	if( unbindAfterScan )
		tempFile.ifile()->unbindAllColumns();
}


void SelectExpression::existsScan( void )
{
	existsValueFlag_ = scanFirst();
}


void SelectExpression::computeDataLength( void )
{
	pColumn col;

	for( col = columns_.first(), columnsLength_ = 0; col; col = columns_.next() )
		columnsLength_ += col->ExpressionLength();

	for( col = groupByColumns_.first(), groupByColumnsLength_ = 0; col; col = groupByColumns_.next() )
		groupByColumnsLength_ += col->ExpressionLength();
}


void SelectExpression::magicLock( void )
{
	pTableTableElement ttEl;

	for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
		ttEl->magicLock();
}


void SelectExpression::addRowToResultSet( TemporaryResultFile& tempFile )
{
	bindToTemporaryFile( tempFile );
	tempFile.ifile()->beginRowOperation();
	retrieveBaseTablePositions();
	tempFile.setBaseTablePositions( baseTablePositionBuffer_ );
	try
	{
		tempFile.ifile()->addRow();
	}
	catch( DuplicateRowException& )
	{
		//  Allowable here.  This is the mechanism to implement DISTINCT in some cases.
		return;
	}
}


void SelectExpression::setFunctionSpaceNull( void )
{
	Column *col;

	for( col = columns_.first(); col; col = columns_.next() )
		col->ColumnExpression().releaseFunctionSpaces();

	if( having_ )
		havingExp_.releaseFunctionSpaces();
}


void SelectExpression::postFunctionProcessing( void )
{
	Column *col;
	for( col = columns_.first(); col; col = columns_.next() )
		col->ColumnExpression().evaluatePost();
}


void SelectExpression::clearAggregateValues( void )
{
	Column *col;
	for( col = columns_.first(); col; col = columns_.next() )
		col->ColumnExpression().clearAggregateValues();
}


void SelectExpression::assignOrderByExpression( pExpression *exp )
{
	(*exp) = &orderByExp_;
}


void SelectExpression::assignWhereExpression( pExpression *exp )
{
	(*exp) = &whereCondition_;
}


void SelectExpression::assignHavingExpression( pExpression *exp )
{
	(*exp) = &havingExp_;
}


void SelectExpression::sortLinks( bool /*doWork*/ )
{
	pPredicate pred, pred2;
	OptimizerPredicateList& linkPreds = whereCondition_.linkPredicates();
	pBinaryOperatorInstruction binaryOpIns;
	pTableTableElement ttEl, firstTtEl;
	UNI numberOfLinks = linkPreds.size();

	if( numberOfLinks == 0 || linksSorted_ == CQL_YES )
		return;

	linksSorted_ = CQL_YES;

	for( pred = linkPreds.first(); pred; pred = linkPreds.next() )
	{
		for( pred2 = linkPreds.followingPred( pred ); pred2; pred2 = linkPreds.followingPred( pred2 ) )
			if( pred->master()->ttEl()->tableNumber() < pred2->master()->ttEl()->tableNumber() )
				linkPreds.exchange( pred, pred2 );
	}

	for( pred = linkPreds.first(); pred; pred = linkPreds.next() )
		if( pred->slave()->correlated() || pred->master()->ttEl()->tableNumber() > pred->slave()->ttEl()->tableNumber() )
			pred->switchMasterAndSlave();

	validityCheck( 0 );

	//
	//  In this loop we look for pairs of links which form a loop
	//  in the link resolution logic.  If there are two links, and
	//  the master file for link #1 is the slave file for link #2
	//  AND the slave file for link #1 is the master file for link
	//  then ...
	//
	if( numberOfLinks > 1 )
	{
		for( pred = linkPreds.last(); pred; pred = linkPreds.prev() )
		{
			if( pred->master()->correlated() )
				continue;

			for( pred2 = pred->prev(); pred2; pred2 = pred2->prev() )
				if( pred->master()->ttEl() == pred2->slave()->ttEl() && pred->slave()->ttEl() == pred->master()->ttEl() )
					pred->switchMasterAndSlave();
		}
	}

	while( slaveDuplicateCheck() )
		;

	validityCheck( 0 );

	for( pred = linkPreds.last(); pred; pred = linkPreds.prev() )
	{
		if( pred->master()->type() != pred->slave()->type() )
		{
			pred->linkType( CPLINK );

			if( noCondition_ == CQL_YES )
				noCondition_ = CQL_NO;
		}
	}

	for( pred = linkPreds.last(); pred; pred = linkPreds.prev() )
		pred->findOrMakeIndex();

	//
	//  mark the outer joins
	//
	for( pred = linkPreds.last(); pred; pred = linkPreds.prev() )
	{
		binaryOpIns = dynamic_cast< BinaryOperatorInstruction* >( pred->ins() );
		if( binaryOpIns->BinaryOp() == OUTER_EQUAL )
			pred->linkType( CQL_OUTER );
	}

	//
	//  mark all linked tables_
	//
	for( pred = linkPreds.first(); pred && pred->next(); pred = linkPreds.next() )
		pred->slave()->ttEl()->setLinkFlag();

	linkPreds.last()->master()->setLinkFlag();
	linkPreds.last()->slave()->setLinkFlag();

	//
	//  find unlinked files, add a CPLINK for each
	//
	for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
	{
		if( ttEl->linkFlag() )
			continue;

		pred = new Predicate( dbsql_ );
		if( !pred )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		pred->linkType( CPLINK );
		pred->setLinkPredicate();

		linkPreds.add( pred );
	}

	if( !prev() || !correlated_ )
	{
		pred = linkPreds.last();
		ttEl = pred->master()->ttEl();
		firstTtEl = tables_.first();

		if( firstTtEl != ttEl )
		{
			tables_.remove( ttEl );
			tables_.addBefore( firstTtEl, ttEl );
		}
	}
}


SelectExpression *SelectExpression::previousSelectExpression( void )
{
	return prev();
}


SelectExpression *SelectExpression::nextSelectExpression( void )
{
	return next();
}


void SelectExpression::cleanupReport( void )
{
}


Column *SelectExpression::beginColumn( void )
{
	Column *col = new Column( dbsql_ );
	if( !col )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	columns_.add( col );
	return col;
}


bool SelectExpression::viewNext( void )
{
	CompareResult compareResult;
	pView view = ((pView)tables_.first());
	pSelectExpression firstSelect = view->viewSpec()->selectExpressions().first();

	if( firstSelect->endGroup() )
		return false;

	if( firstSelect->groupBy() )
	{
		if( !firstSelect->midGroup() )
			throw InternalErrorException( __FILE__, __LINE__ );

		firstSelect->swapDataForGroupBy();
		firstSelect->setFunctionSpaceNull();
		firstSelect->runColumnExpressions();
		firstSelect->moveGroupColumns();
		
		for( ; ; )
		{
			firstSelect->swapDataForGroupBy();
			firstSelect->setNextMostRecentHavingResult( firstSelect->mostRecentHavingResult() );

			if( !firstSelect->scanNext() )
			{
				firstSelect->swapDataForGroupBy();

				if( !firstSelect->having() || firstSelect->nextMostRecentHavingResult() )
				{
					firstSelect->setEndGroup();
					return true;
				}
				else
					return false;
			}

			compareResult = firstSelect->compareGroupColumns();

			if( compareResult != THIS_EQUAL_TO_OTHER )
			{
				firstSelect->swapDataForGroupBy();

				if( !firstSelect->having() || firstSelect->nextMostRecentHavingResult() )
					return true;

				firstSelect->swapDataForGroupBy();
				firstSelect->setFunctionSpaceNull();
				firstSelect->runColumnExpressions();
				firstSelect->moveGroupColumns();
			}
		}
	}
	else if( !firstSelect->scanNext() )
		return false;

	return true;
}


bool SelectExpression::viewFirst( void )
{
	CompareResult compareResult;
	pView view = ((pView)tables_.first());
	pSelectExpression firstSelect = view->viewSpec()->selectExpressions().first();

	if( firstSelect->distinct() )
		firstSelect->makeUnique();
	else
		firstSelect->setUnique();

	if( firstSelect->groupBy() )
		firstSelect->makeOrder();

	setFinalTrip();
	firstSelect->setFunctionSpaceNull();
	if( !firstSelect->scanFirst() )
		return false;

	if( firstSelect->groupBy())
	{
		firstSelect->moveGroupColumns();

		for( ; ; )
		{
			firstSelect->swapDataForGroupBy();
			firstSelect->setNextMostRecentHavingResult( firstSelect->mostRecentHavingResult() );
			
			if( !firstSelect->scanNext() )
			{
				firstSelect->setEndGroup();

				firstSelect->swapDataForGroupBy();

				if( !firstSelect->having() || firstSelect->nextMostRecentHavingResult() )
					return true;
				else
					return false;
			}

			compareResult = firstSelect->compareGroupColumns();

			if( compareResult != THIS_EQUAL_TO_OTHER )
			{
				firstSelect->swapDataForGroupBy();

				if( !firstSelect->having() || firstSelect->nextMostRecentHavingResult() )
				{
					firstSelect->setMidGroup();
					return true;
				}

				firstSelect->swapDataForGroupBy();
				firstSelect->setFunctionSpaceNull();
				firstSelect->runColumnExpressions();
				firstSelect->moveGroupColumns();
			}
		}
	}

	return true;
}


bool SelectExpression::scanNext( void )
{
	if( usingAggregateIndex_ )
		return false;

	pTableTableElement table = tables_.first();

	logicalFetch_ = CQL_NO;

	bool result;
	do
	{
		if( unique_ == CQL_YES && uniqueEnabled_ == CQL_YES )
		{
			if( !uniqueNext() )
			{
				firstScan_ = false;
				return false;
			}

			runColumnExpressions();
			logicalFetch_ = true;
			return true;
		}

		else if( orderBy_ == CQL_YES && orderEnabled_ == CQL_YES && orderTemporary_ == CQL_YES )
		{
			bool lresult;

			do
			{
				if( !orderTemporaryNext() )
				{
					firstScan_ = CQL_NO;
					return false;
				}

				if( !noCondition_)
					lresult = whereCondition_.evaluate();
				else
					lresult = true;
			} while( !lresult );

			runColumnExpressions();
			logicalFetch_ = true;
			return true;
		}

		//
		//  number of links is 0 but number of #tables_ is >1
		//  for cartesian product
		//
		if( whereCondition_.linkPredicates().size() > 0 || tables_.size() > 1 )
		{
			for( ; ; )
			{
				if( !moreLinks() )
				{
					if( correlatedLink_ )
					{
						correlatedLink_ = false;
						firstScan_ = false;
						return false;
					}

					break;
				}

				if( noCondition_ )
				{
					runColumnExpressions();
					return true;
				}
				else
				{
					if( whereCondition_.evaluate() )
					{
						runColumnExpressions();
						return true;
					}
				}
			}

			if( cartesianProductLink_ )
			{
				cartesianProductLink_ = false;
				firstScan_ = false;
				return false;
			}
		}

		if( orderBy_ && orderEnabled_ )
		{
			bool lresult;

			if( orderDescending_ )
				lresult = table->previousRow();
			else
				lresult = table->nextRow();

			if( !lresult )
			{
				firstScan_ = false;
				return false;
			}
		}

		else if( table->isView() )
		{
			if( !viewNext() )
			{
				firstScan_ = false;
				return false;
			}
		}

		else if( noSet_ == CQL_YES )
		{
			if( !table->nextRow() )
			{
				firstScan_ = false;
				return false;
			}
		}

		else if( whereCondition_.resolvedPredicates().size() == 1 )
		{
			if( !table->tableSpec()->nextRowMatchingPredicate() )
			{
				firstScan_ = CQL_NO;
				return false;
			}
		}

		else
		{
			if( !memorySetNext( table, whereCondition_.root() ) )
			{
				firstScan_ = false;
				return false;
			}
		}

		if( !doLinks() )
			result = false;
		else
		{
			if( !noCondition_ )
				result = whereCondition_.evaluate();
			else
				result = true;
		}
	} while( !result );

	runColumnExpressions();
	return true;
}


bool SelectExpression::scanFirst( void )
{
	pTableTableElement table = tables_.first();
	pColumn column;

	refetchOK_ = CQL_NO;
	logicalFetch_ = CQL_NO;

	bool result;

	if( usingAggregateIndex_ == CQL_YES )
	{
		column = columns_.first();
		if( column->MinIndex() )
			result = table->firstUsingIndex( column );
		else if( column->MaxIndex() )
			result = table->lastUsingIndex( column );
		else if( column->CountIndex() )
			result = table->countFromIndex( column );
		else
			throw InternalErrorException( __FILE__, __LINE__ );

		if( !result )
			return false;
		runColumnExpressions();
		return true;
	}

	else if( correlated_ && allLinks() )
	{
		firstScan_ = false;
		if( !doLinks() )
			return false;
		
		if( !noCondition_ )
		{
			result = whereCondition_.evaluate();
			if( !result )
				return scanNext();
		}

		runColumnExpressions();
		return true;
	}

	else if( orderBy_ && orderEnabled_ )
	{
		if( orderTemporary_ )
		{
			if( !orderTemporaryFirst() )
			{
				firstScan_ = CQL_NO;
				return false;
			}

			if( noCondition_ == ((BFT)CQL_NO) )
			{
				result = whereCondition_.evaluate();
				if( !result )
					return scanNext();
			}

			runColumnExpressions();
			logicalFetch_ = true;
			return true;
		}
		else
		{
			if( orderDescending_ )
				result = table->lastRow( existingOrderKey_ );
			else
				result = table->firstRow( existingOrderKey_ );

			if( !result )
			{
				firstScan_ = CQL_NO;
				return false;
			}
		}
	}

	else if( unique_ == CQL_YES && uniqueEnabled_ == CQL_YES )
	{
		if( !uniqueFirst() )
		{
			firstScan_ = CQL_NO;
			return false;
		}

		logicalFetch_ = true;
		runColumnExpressions();
		return true;
	}

	else if( table->isView() )
	{
		if( !viewFirst() )
		{
			firstScan_ = false;
			return false;
		}
	}

	else if( noSet_ )
	{
		if( !table->firstRow( 0 ) )
		{
			firstScan_ = false;
			return false;
		}
	}

	else if( whereCondition_.resolvedPredicates().size() == 1 )
	{
		result = table->tableSpec()->firstRowMatchingPredicate( *whereCondition_.resolvedPredicates().first() );
		if( !result )
		{
			firstScan_ = false;
			return false;
		}
	}

	else
	{
		if( !memorySetFirst( table, whereCondition_.root() ) )
		{
			firstScan_ = false;
			return false;
		}

		logicalFetch_ = true;
	}

	if( !doLinks() )
		return scanNext();

	if( !noCondition_ )
	{
		result = whereCondition_.evaluate();
		if( !result )
			return scanNext();
	}

	runColumnExpressions();

	return true;
}


void SelectExpression::runColumnExpressions( void )
{
	pColumn col;

	for( col = columns_.first(); col; col = columns_.next() )
	{
		if( aggregateDistinctScan_ )
			col->ColumnExpression().setAggregateDistinctScan();

		col->ColumnExpression().evaluate();

		if( aggregateDistinctScan_ == CQL_YES )
			col->ColumnExpression().clearAggregateDistinctScan();
	}

	for( col = groupByColumns_.first(); col; col = groupByColumns_.next() )
		col->ColumnExpression().evaluate();

	if( having_ )
		mostRecentHavingResult_ = havingExp_.evaluate();
}


//
//  this function includes those parts of SELECT processing which are common to SELECT,
//  DELETE with WHERE, INSERT with SELECT, and UPDATE with WHERE.
//
void SelectExpression::processSelectCommon( void )
{
	processTablesAndColumns();

	whereCondition_.computeValueExpressionType();
	whereCondition_.createPredicateList();

	if( whereCondition_.root() == 0 )
		noCondition_ = noSet_ = true;
	else
	{
		whereCondition_.classify( correlated_ );
		whereCondition_.makePredicateList( whereCondition_.root() );

		if( whereCondition_.resolvedPredicates().size() == 0 )
		{
			noSet_ = CQL_YES;
			if( whereCondition_.root()->linkPredicate() )
				noCondition_ = true;
			else
				noCondition_ = false;
		}

		whereCondition_.findSegmentedKey();
		whereCondition_.adjustPredicateTree();
	}
}


void SelectExpression::processSelect( void )
{
	if( groupBy_ && !orderBy_ )
	{
		Column *col;
		ExpressionColumnListElement *el1, *el2;
		IdentifierInstruction *ins;

		orderBy_ = CQL_YES;

		for( col = groupByColumns_.first(); col; col = groupByColumns_.next() )
		{
			Expression& exp = col->ColumnExpression();

			el1 = exp.columns().first();

			el2 = new ExpressionColumnListElement;
			if( !el2 )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			el2->Name() = el1->Name();
			el2->Prefix() = el1->Prefix();

			orderByExp_.columns().add( el2 );

			ins = new IdentifierInstruction( dbsql_ );
			if( !ins )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			el2->SetIns( ins );
			orderByExp_.instructions().add( ins );
			ins->col( el1->Ins()->col() );
		}
	}

	processSelectCommon();

	if( groupBy_ )
	{
		//  check for legal SELECT with GROUP BY
		Column *col;
		for( col = columns_.first(); col; col = columns_.next() )
		{
			Expression& exp = col->ColumnExpression();
			ExpressionColumnListElement *expCol = exp.columns().first();

			//  Is the column an aggregate function?
			if( !exp.aggregateFunctionInExpression() )
			{
				//  No, so it needs to be a GROUP BY column to be legal
				Column *col2;
				bool found;
				for( col2 = groupByColumns_.first(), found = false; !found && col2; col2 = groupByColumns_.next() )
				{
					Expression& exp2 = col2->ColumnExpression();
					ExpressionColumnListElement *expCol2 = exp2.columns().first();
					if( expCol2->Column() == expCol->Column() )
						found = true;
				}

				if( !found )
					throw GroupBySelectViolation( __FILE__, __LINE__ );
			}
		}
	}

	if( orderBy_ )
		orderByExp_.computeValueExpressionType();

	if( !correlated_ )
		makeSets();

	sortLinks();
	checkForAllLinks();
}


void SelectExpression::processViewSelect( SelectExpressionList& sel )
{
	Column *column;
	UNI positionBufferSize;

	processTables();

	for( column = columns_.first(); column; column = columns_.next() )
		column->ColumnExpression().processViewData( sel );

	for( column = groupByColumns_.first(); column; column = groupByColumns_.next() )
		column->ColumnExpression().processViewData( sel );

	havingExp_.processViewData( sel );
	orderByExp_.processViewData( sel );
	whereCondition_.processViewData( sel );

	US nBaseTables = numberOfBaseTables();
	positionBufferSize = nBaseTables * sizeof( RECID );
	allocateBaseTablePositionBuffer( positionBufferSize );
}


void SelectExpression::reprocessViewSelect( SelectExpressionList& sel )
{
	Column *column;

	for( column = columns_.first(); column; column = columns_.next() )
		column->ColumnExpression().reprocessViewData( sel );

	for( column = groupByColumns_.first(); column; column = groupByColumns_.next() )
		column->ColumnExpression().reprocessViewData( sel );

	havingExp_.reprocessViewData( sel );
	orderByExp_.reprocessViewData( sel );
	whereCondition_.reprocessViewData( sel );
}


void SelectExpression::processTablesAndColumns( bool clearInUseFlags )
{
	if( tablesAndColumnsProcessed_ )
		return;

	processTables( clearInUseFlags );
	processColumns();
	openUserFiles();
}


void SelectExpression::processTables( bool clearInUseFlags )
{
	pTripleStringListElement tsl;
	pTableTableElement tableTableElement;
	pAbstractTableSpecification ats;
	US tableNum;

	if( tables_.Processed() )
		return;

	tables_.SetProcessed();

	if( clearInUseFlags )
		dbsql_.activeTables().ClearInUseFlags();

	for( tsl = tableNames_.first(), tableNum = 0; tsl; tsl = tableNames_.next(), tableNum++ )
	{
		tableTableElement = TableTableElement::createUsingDictionary( dbsql_, *tsl );
		if( !tableTableElement )
			throw TableNotFoundException( __FILE__, __LINE__ );

		tableTableElement->tableNumber( tableNum );
		tables_.add( tableTableElement );

		if( tableTableElement->isView() )
			tableTableElement->processView();

		ats = tableTableElement->absTableSpec();
	 	// FIXED
	 	PermanentColumnSpecification *pcs;
		for( pcs = ats->columns().first(); pcs; pcs = ats->columns().next() )
		{
			ColumnSpecification *colSpec = dynamic_cast< ColumnSpecification* >( pcs );
			colSpec->SetTtEl( tableTableElement );
		}
	}
}


void SelectExpression::addAllColumnsForTable( pColumn col, pTableTableElement ttEl )
{
	pColumn newCol, previousCol = ((pColumn)0);
	pExpressionColumnListElement expColListEl;
	pAbstractTableSpecification abstractTable = ttEl->absTableSpec();
	ColumnSpecificationList& tCols = abstractTable->columns();
	pIdentifierInstruction ins;
	US cno;

	//
	//  The first column name replaces the asterisk.  Subsequent
	//  names require allocation of a new columnTable element
	//
	bool firstAsteriskColumn = true;
	// FIXED
	PermanentColumnSpecification *pcs;
	for( pcs = tCols.first(), cno = 0; pcs; pcs = tCols.next(), cno++ )
	{
		ColumnSpecification *tColSpec = dynamic_cast< ColumnSpecification* >(pcs);
		if( firstAsteriskColumn )
		{
			firstAsteriskColumn = false;
			newCol = col;
			previousCol = col;
			expColListEl = col->ColumnExpression().columns().first();
			ins = dynamic_cast< IdentifierInstruction* >( newCol->ColumnExpression().instructions().first() );
			newCol->ColumnExpression().label() = pcs->columnName();
		}
		else
		{
			newCol = new Column( dbsql_ );
			if( !newCol )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			expColListEl = new ExpressionColumnListElement;
			if( !expColListEl )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			newCol->ColumnExpression().columns().add( expColListEl );
			newCol->ColumnExpression().label() = pcs->columnName();
			columns_.addAfter( previousCol, newCol );
			previousCol = newCol;

			ins = new IdentifierInstruction( dbsql_ );
			if( !ins )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			newCol->ColumnExpression().instructions().add( ins );
		}

		ins->col( tColSpec );
		expColListEl->SetIns( ins );

		tColSpec->SetTtEl( ttEl );
		tColSpec->SetCno( cno );
		expColListEl->SetColumn( tColSpec );
		expColListEl->SetProcessed();
		expColListEl->Name() = tColSpec->columnName();
		expColListEl->Prefix() = tColSpec->TableName();

		if( tColSpec->TableName().text() && tColSpec->TableName().text()[ 0 ] != 0 )
		{
			newCol->Label() = tColSpec->TableName();
			newCol->Label().stripTrailingSpaces();
			newCol->Label() += ".";
		}
		newCol->Label() += tColSpec->columnName();
	}

	columns_.current( previousCol );
}


bool SelectExpression::findCorrelatedColumn( pExpressionColumnListElement expColListEl )
{
	pSelectExpression sel;

	for( sel = previousSelectExpression(); sel; sel = sel->previousSelectExpression() )
	{
		sel->processTablesAndColumns( false );
		sel->setTablesAndColumnsProcessed();

		if( sel->findColumn( expColListEl, true ) )
		{
			correlated_ = true;
			return true;
		}
	}

	return false;
}


bool SelectExpression::findColumn( pExpressionColumnListElement expColListEl, bool tCorrelated )
{
	pTableTableElement ttEl;
	pAbstractTableSpecification abstractTable;
	US cno;

	for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
	{
		abstractTable = ttEl->absTableSpec();
		ColumnSpecificationList& cols = abstractTable->columns();
		PermanentColumnSpecification *pcs;
		for( pcs = cols.first(), cno = 0; pcs; pcs = cols.next(), cno++ )
		{
		 	ColumnSpecification *colSpec = dynamic_cast< ColumnSpecification* >(pcs);
			if( expColListEl->Name() == colSpec->columnName()
				&& ( !expColListEl->Prefix()
					 || expColListEl->Prefix() == ttEl->tableName()
					 || ( expColListEl->Prefix() == ttEl->correlationName() ) ) )
			{
				colSpec->SetTtEl( ttEl );
				if( !colSpec->TableName() )
					colSpec->TableName() = ttEl->tableName();
				if( !expColListEl->Prefix() )
					expColListEl->Prefix() = ttEl->tableName();
				colSpec->SetCno( cno );
				expColListEl->SetColumn( colSpec );
				expColListEl->Ins()->col( colSpec );
				if( tCorrelated == CQL_YES )
					expColListEl->Ins()->setCorrelated();
				return true;
			}
		}
	}

	return false;
}


void SelectExpression::identifyExpressionColumns( Expression& exp )
{
	ExpressionColumnList& expColList = exp.columns();
	pExpressionColumnListElement expColListEl;

	for( expColListEl = expColList.first(); expColListEl; expColListEl = expColList.next() )
	{
		if( !findColumn( expColListEl ) )
		{
			if( !findCorrelatedColumn( expColListEl ) )
				throw ColumnNotFoundException( __FILE__, __LINE__ );

			correlated_ = true;
		}
	}
}


void SelectExpression::processColumns( void )
{
	pColumn col;
	pExpressionColumnListElement expColListEl;
	pTableTableElement ttEl;
	bool found;

	//
	//  find any asterisks in the select list, and replace with column names
	//
	for( col = columns_.first(); col; col = columns_.next() )
	{
		expColListEl = col->ColumnExpression().columns().first();

		//
		//  check for asterisk
		//
		if( expColListEl && expColListEl->Name() == CqlString( "*" ) )
		{
			if( !expColListEl->Prefix() )
			{
				//
				//  no authorization identifier with asterisk.  All columns_ of all tables_
				//
				for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
					addAllColumnsForTable( col, ttEl );
			}
			else
			{
				for( ttEl = tables_.first(), found = false; !found && ttEl; ttEl = tables_.next() )
				{
					if( expColListEl->Prefix() == ttEl->absTableSpec()->tableName() )
					{
						found = true;
						addAllColumnsForTable( col, ttEl );
					}
					break;
				}

				if( !found )
					throw TableNotFoundException( __FILE__, __LINE__ );
			}
		}

		else identifyExpressionColumns( col->ColumnExpression() );
	}

	identifyExpressionColumns( whereCondition_ );

	for( col = columns_.first(), onlyAggregateFunctions_ = true; col; col = columns_.next() )
	{
		Expression& exp = col->ColumnExpression();

		exp.computeValueExpressionType();
		aggregateFunctions_ = exp.examineForAggregateFunction();
		if( !aggregateFunctions_ )
			onlyAggregateFunctions_ = false;
	}

	for( col = groupByColumns_.first(); col; col = groupByColumns_.next() )
	{
		identifyExpressionColumns( col->ColumnExpression() );
		col->ColumnExpression().computeValueExpressionType();
	}

	if( having_ )
	{
		identifyExpressionColumns( havingExp_ );
		havingExp_.computeValueExpressionType();
	}

	identifyExpressionColumns( orderByExp_ );
}


void SelectExpression::openUserFiles( void )
{
	pTableTableElement ttEl;
	pAbstractTableSpecification abstractTable;

	for( ttEl = tables_.first(); ttEl; ttEl = tables_.next() )
	{
		abstractTable = ttEl->absTableSpec();
		abstractTable->open();
	}
}


//
//  at entry:
//
//  this is the SelectExpression describing the insert.  It's Next() value is
//  the SelectExpression pointing to the select
//
void SelectExpression::insertWithSelect( InsertColumnNameList&, bool preparing )
{
	pAbstractTableSpecification table;
	pSelectExpression selectExp = ((pSelectExpression)next());
	pColumn sourceCol, destCol;

	processTables();

	//
	//  process tables_ and columns_ for SELECT
	//
	selectExp->processTablesAndColumns();
	table = tables_.first()->absTableSpec();

	//
	//  check for INSERT privilege for base table (or tables_)
	//
	if( !dbsql_.checkForInsertPrivilege( table ) )
		throw PrivilegeViolationException( __FILE__, __LINE__ );

	if( !dbsql_.checkForSelectPrivilege( selectExp ) )
		throw PrivilegeViolationException( __FILE__, __LINE__ );

	//
	//  check that the number of result columns_ in the SELECT matches the number of
	//  columns_ for the INSERT
	//
	if( columns_.size() != selectExp->columns_.size() )
		throw InsertValuesMismatchException( __FILE__, __LINE__ );

	//
	//  check that the types for the SELECT are compatible with the types for
	//  the INSERT
	//
	for( destCol = columns_.first(), sourceCol = selectExp->columns_.first();
		destCol;
		destCol = columns_.next(), sourceCol = selectExp->columns_.next() )
	{
		switch( destCol->ColumnExpression().valueExpressionType().typeType() )
		{
		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_CHAR :
			case CQL_CHARUC :
			case CQL_VARCHAR :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_TINYINT :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_TINYINT :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_SMALLINT :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_TINYINT :
			case CQL_SMALLINT :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_INTEGER :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_TINYINT :
			case CQL_SMALLINT :
			case CQL_INTEGER :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_BIGINT :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_TINYINT :
			case CQL_SMALLINT :
			case CQL_INTEGER :
			case CQL_BIGINT :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_DECIMAL :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_TINYINT :
			case CQL_SMALLINT :
			case CQL_INTEGER :
			case CQL_BIGINT :
			case CQL_DECIMAL :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_REAL :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_TINYINT :
			case CQL_SMALLINT :
			case CQL_INTEGER :
			case CQL_BIGINT :
			case CQL_DECIMAL :
			case CQL_REAL :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_FLOAT :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_TINYINT :
			case CQL_SMALLINT :
			case CQL_INTEGER :
			case CQL_BIGINT :
			case CQL_DECIMAL :
			case CQL_REAL :
			case CQL_FLOAT :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_LONGVARCHAR :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_LONGVARCHAR :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_BIT :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_TINYINT :
			case CQL_SMALLINT :
			case CQL_INTEGER :
			case CQL_BIGINT :
			case CQL_DECIMAL :
			case CQL_REAL :
			case CQL_FLOAT :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_BINARY :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_BINARY :
			case CQL_VARBINARY :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_VARBINARY :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_BINARY :
			case CQL_VARBINARY :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_LONGVARBINARY :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_LONGVARBINARY :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_DATE :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_DATE :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_TIME :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_TIME :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_TIMESTAMP :
			switch( sourceCol->ColumnExpression().valueExpressionType().typeType() )
			{
			case CQL_DATE :
			case CQL_TIME :
			case CQL_TIMESTAMP :
				break;

			default :
				throw TypesNotAssignmentCompatibleException( __FILE__, __LINE__ );
			}
			break;

		case CQL_COLUMN_UNDEFINED_TYPE :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
	}

	selectExp->processSelect();
	dbsql_.updateCount( 0 );

	if( preparing )
	{
		dbsql_.currentStatement()->type( INSERT_SELECT );
		dbsql_.currentStatement()->insertAts( table );
		return;
	}

	insertWithSelectPart2( selectExp, table );
}


void SelectExpression::insertWithSelectPart2( pSelectExpression selectExp, pAbstractTableSpecification table )
{
	if( !selectExp->scanFirst() )
		throw NoDataException( __FILE__, __LINE__ );

	dbsql_.incrementUpdateCount();

	*this = *selectExp;

	checkView( table );

	dbsql_.beginTransaction();

	try
	{
		table->addRow();
	}
	catch( CqlException& ex )
	{
		dbsql_.rollbackTransaction( false );
		throw ex;
	}

	for( ; ; )
	{
		if( !selectExp->scanNext() )
			break;

		dbsql_.incrementUpdateCount();

		*this = *selectExp;
		checkView( table );

		try
		{
			table->addRow();
		}
		catch( CqlException& ex )
		{
			dbsql_.rollbackTransaction( false );
			throw ex;
		}
	}

	dbsql_.commitTransaction( false );
}


bool SelectExpression::validityCheck( pPredicate linkToSkip )
{
	pPredicate pred, pred2;
	OptimizerPredicateList& linkPreds = whereCondition_.linkPredicates();

	for( pred = linkPreds.first(); pred; pred = linkPreds.next() )
	{
		pred->master()->ttEl()->clearValid();
		pred->slave()->ttEl()->clearValid();
	}

	//
	//  master file of initial link is initially valid
	//
	linkPreds.last()->master()->ttEl()->setValid();

	for( pred = linkPreds.last(); pred; pred = linkPreds.prev() )
	{
		if( pred == linkToSkip || pred->masterCorrelated() )
			continue;

		if( !pred->master()->ttEl()->valid() )
		{
			//
			//  master file is not valid.  Look for predicate with valid master file
			//
			for( pred2 = linkPreds.precedingPred( pred ); pred2; pred2 = linkPreds.precedingPred( pred2 ) )
			{
				if( pred2 == linkToSkip )
					continue;

				if( pred2->master()->ttEl()->valid() )
				{
					linkPreds.exchange( pred, pred2 );
					pred = pred2;
					pred->master()->ttEl()->setValid();
					pred->slave()->ttEl()->setValid();
					break;
				}
			}

			if( pred2 )
				continue;

			//
			//  Search for valid master file failed.  Check slave files.
			//
			if( pred->slave()->ttEl()->valid() )
			{
				pred->switchMasterAndSlave();
				continue;
			}

			//
			//  Slave file not valid either.  Look for another link whose
			//  slave file is valid
			//
			for( pred2 = pred->prev(); pred2; pred2 = pred2->prev() )
			{
				if( pred2 == linkToSkip )
					continue;

				if( pred2->slave()->ttEl()->valid() )
				{
					pred->switchMasterAndSlave();
					linkPreds.exchange( pred, pred2 );
					pred = pred2;
					pred->master()->ttEl()->setValid();
					pred->slave()->ttEl()->setValid();
					break;
				}
			}

			if( pred2 )
				continue;

			//
			//  can't untangle
			//
			throw InvalidJoinRelationshipsException( __FILE__, __LINE__ );
		}
		else
		{
			//
			//  master file is already valid
			//
			pred->slave()->ttEl()->setValid();
		}
	}

	return true;
}


bool SelectExpression::slaveDuplicateCheck( void )
{
	OptimizerPredicateList& linkPreds = whereCondition_.linkPredicates();
	pPredicate pred, pred2;

	for( pred = linkPreds.first(); pred && pred->next(); pred = linkPreds.next() )
	{
		for( pred2 = linkPreds.followingPred( pred ); pred2; pred2 = linkPreds.followingPred( pred2 ) )
		{
			if( pred->slave()->ttEl() == pred2->slave()->ttEl() )
			{
				eliminateLink( pred, pred2 );
				return true;
			}
		}
	}

	return false;
}


void SelectExpression::eliminateLink( pPredicate pred, pPredicate pred2 )
{
	if( pred->linkType() == EXISTING && pred2->linkType() == EXISTING )
	{
		if( pred->slave()->entries() < pred2->slave()->entries() )
			eliminateThisLink( pred2, pred );
		else
			eliminateThisLink( pred, pred2 );
	}
	else if( pred->linkType() == EXISTING )
		eliminateThisLink( pred2, pred );
	else
		eliminateThisLink( pred, pred2 );
}


void SelectExpression::eliminateThisLink( pPredicate predToEliminate, pPredicate predToStay )
{
	pPredicate pred;

	if( !validityCheck( predToEliminate ) )
	{
		//
		//  try deleting the other one
		//
		if( validityCheck( predToStay ) )
		{
			pred = predToStay;
			predToEliminate = pred;
		}
	}

	whereCondition_.linkPredicates().remove( predToEliminate );
}


void SelectExpression::positionedDelete( bool preparing )
{
	pTableTableElement table;
	pTripleStringListElement tsl;

	//
	//  check that cursor references only one table
	//
	if( tables_.size() != 1 )
		throw PositionedOperationWithMultipleTablesException( __FILE__, __LINE__ );

	table = tables_.first();

	//
	//  compare the table name in DELETE to the table name in DECLARE CURSOR
	//
	tsl = tableNames_.first();
	if( ( tsl->s2() != CqlString( "" ) && tsl->s2() != table->authorizationId() ) || tsl->s1() != table->tableName() )
		throw TableNotFoundException( __FILE__, __LINE__ );

	if( !dbsql_.checkForDeletePrivilege( table ) )
		throw PrivilegeViolationException( __FILE__, __LINE__ );

	if( preparing == CQL_YES )
	{
		dbsql_.currentStatement()->type( DELETE_POSITIONED );
		dbsql_.currentStatement()->deleteTtel( table );
		return;
	}

	positionedDeletePart2( table );
}


void SelectExpression::positionedDeletePart2( pTableTableElement table )
{
	table->rereadCurrentRow();
	table->deleteRow();
}


void SelectExpression::searchedDelete( bool preparing )
{
	pTableTableElement table;

	processSelectCommon();
	table = tables_.first();

	if( preparing )
	{
		dbsql_.currentStatement()->type( DELETE_SEARCHED );
		dbsql_.currentStatement()->deleteTtel( table );
	}

	if( !dbsql_.checkForDeletePrivilege( table ) )
		throw PrivilegeViolationException( __FILE__, __LINE__ );

	if( preparing )
		return;

	searchedDeletePart2( table );
}


void SelectExpression::searchedDeletePart2( pTableTableElement table )
{
	setFinalTrip();
	dbsql_.updateCount( 0 );

	dbsql_.beginTransaction();
	createRowListFile();
	if( !scanFirst() )
	{
		dbsql_.rollbackTransaction( false );
		throw NoDataException( __FILE__, __LINE__ );
	}

	bool result;

	do
	{
		dbsql_.incrementUpdateCount();
		addToRowList();
		result = scanNext();
	} while( result );

	for( result = rowListFirst(); result; result = rowListNext() )
		table->deleteRow();

	dbsql_.commitTransaction( false );
	table->absTableSpec()->checkPropagationFlags();
}


//
//  at entry:
//
//  first member of tables_ list has the table name
//  keys are attached to the lists of the first member of tables_
//
//  dbsql_.UserName() has the currently logged in user
//
//  the columns_ list has the definitions of the columns_
//
//  the indexNameGroups parameter is a list of list.  Each list is itself a list of names, each
//  list comprising a key
//
void SelectExpression::createTable( pTableSpecification table, IndexNameListGroupList *indexNameGroups, ForeignKeyNamesList *foreignKeyNameList, bool preparing )
{
	pPermanentColumnSpecification pcs;
	US numkey = 0, colNum;

	//  setup file name
	table->findUniqueFileName( &dbsql_ );

	//
	//  check column lengths, set to defaults where unspecified.
	//
	dbsql_.parse()->createTableColumns().move( table->columns() );
	for( pcs = table->columns().first(), colNum = 0; pcs; pcs = table->columns().next(), colNum++ )
	{
		pcs->checkCreateColumnLength();
		pcs->columnNumber( colNum );

		switch( pcs->type().typeType() )
		{
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
			table->setVariableLength();
			break;

		default :
			break;
		}
	}

	for( pcs = table->columns().first(); pcs; pcs = table->columns().next() )
		table->identifyExpressionColumns( pcs->checkCondition() );

	table->identifyExpressionColumns( table->checkCondition() );

	//
	//  For the keys, associate the column name with a column number.
	//
	table->createIndexStructures( *indexNameGroups );

	//
	//  For the foreign keys (if any), associate the column names with foreign table column numbers.
	//
	table->createForeignKeyStructures( *foreignKeyNameList );

	//
	//  count the keys.  There are four types of keys:
	//
	//  single column keys - unique_Index or duplicateIndex member of PermanentColumnSpecification is CQL_YES
	//  (already counted by preceding loop)
	//
	//  segmented unique_ keys - list uniqueKeyGroups of TableSpecification
	//  segmented non-unique_ keys - list duplicateKeyGroups of TableSpecification
	//
	numkey = ((US)( numkey + table->uniqueKeyGroups().size() ) );
	numkey += ((US)( numkey + table->duplicateKeyGroups().size() ) );

	if( numkey == 0 )
	{
		table->createDefaultKey();
		numkey = 1;
	}

	table->numberOfKeys( numkey );

	table->numberOfColumns( ((US)table->columns().size()) );

	if( preparing == CQL_YES )
	{
		dbsql_.currentStatement()->type( CREATE_TABLE );
		dbsql_.currentStatement()->creationTable( table );
		return;
	}

	createTablePart2( table );
}


void SelectExpression::createTablePart2( pTableSpecification table )
{
	pPermanentColumnSpecification pcs;
	pSegmentedKeyGroup skg;
	pAbstractColumnDescriptor colDesc;
	S loop;

	//************************************************************************
	//  Add entry to main dictionary                                        **
	//************************************************************************
	dbsql_.addDictionaryEntry( *table );

	//************************************************************************
	//  Create the data and index files.  Also takes care of references.    **
	//************************************************************************
	table->createFiles();

	//************************************************************************
	//**  Add entries to system tables_.  First SYSTABLES                    **
	//**                                                                    **
	//**  Qualifier, owner, and table name are used in several system       **
	//**  table objects.  We create only one BoundColumn object, and        **
	//**  rebind it for each system table object update.                    **
	//************************************************************************

	dbsql_.systemTableTables().add( "", table->authorizationId(), table->tableName(), "TABLE", "" );

	//************************************************************************
	//**  Now, one row for each column in SYSCOLUMNS                        **
	//************************************************************************

	//  columns_ are already bound
	for( pcs = table->columns().first(); pcs; pcs = table->columns().next() )
	{
		const char *typeName = 0;

		switch( pcs->type().typeType() )
		{
		case CQL_CHAR :
			typeName = "CHAR";
			break;
			
		case CQL_VARCHAR :
			typeName = "VARCHAR";
			break;
			
		case CQL_DECIMAL :
			typeName = "DECIMAL";
			break;
			
		case CQL_SMALLINT :
			typeName = "SMALLINT";
			break;
			
		case CQL_INTEGER :
			typeName = "INTEGER";
			break;
			
		case CQL_REAL :
			typeName = "REAL";
			break;
			
		case CQL_FLOAT :
			typeName = "FLOAT";
			break;
			
		case CQL_LONGVARCHAR :
			typeName = "LONGVARCHAR";
			break;
			
		case CQL_BIT :
			typeName = "BIT";
			break;
			
		case CQL_TINYINT :
			typeName = "TINYINT";
			break;
			
		case CQL_BIGINT :
			typeName = "BIGINT";
			break;
			
		case CQL_BINARY :
			typeName = "BINARY";
			break;
			
		case CQL_VARBINARY :
			typeName = "VARBINARY";
			break;
			
		case CQL_LONGVARBINARY :
			typeName = "LONGVARBINARY";
			break;
			
		case CQL_DATE :
			typeName = "DATE";
			break;
			
		case CQL_TIME :
			typeName = "TIME";
			break;
			
		case CQL_TIMESTAMP :
			typeName = "TIMESTAMP";
			break;
			
		case CQL_CHARUC :
			typeName = "CHARUC";
			break;
			
		case CQL_COLUMN_UNDEFINED_TYPE :
			throw InternalErrorException( __FILE__, __LINE__ );
		}

		S nullable;
		if( pcs->notNull() )
			nullable = 0;
		else
			nullable = 1;

		dbsql_.systemTableColumns().add( "",
										 table->authorizationId(),
										 table->tableName(),
										 pcs->columnName(),
										 static_cast< S >( pcs->type().typeType() ),
										 typeName,
										 pcs->precision(),
										 pcs->type().typeLength(),
										 pcs->scale(),
										 nullable );
	}

	//
	//  Now, one row for each unique_ key in SYSINDICES, plus one row for the table (with the table name)
	//
	dbsql_.systemTableIndices().add( "",
									 table->authorizationId(),
									 table->tableName(),
									 CqlString( "" ),
									 1 /*table row flag*/,
									 table->fileName() );

	for( skg = table->uniqueKeyGroups().first(); skg; skg = table->uniqueKeyGroups().next() )
	{
		for( colDesc = skg->SegmentedKeyColumns().first(), loop = 0; colDesc; colDesc = skg->SegmentedKeyColumns().next(), loop++ )
		{
			pcs = table->columns()[ colDesc->columnNumber() ];

			const char *typeName = 0;

			switch( pcs->type().typeType() )
			{
			case CQL_CHAR :
				typeName = "CHAR";
				break;
				
			case CQL_VARCHAR :
				typeName = "VARCHAR";
				break;
				
			case CQL_DECIMAL :
				typeName = "DECIMAL";
				break;
				
			case CQL_SMALLINT :
				typeName = "SMALLINT";
				break;
				
			case CQL_INTEGER :
				typeName = "INTEGER";
				break;
				
			case CQL_REAL :
				typeName = "REAL";
				break;
				
			case CQL_FLOAT :
				typeName = "FLOAT";
				break;
				
			case CQL_LONGVARCHAR :
				typeName = "LONGVARCHAR";
				break;
				
			case CQL_BIT :
				typeName = "BIT";
				break;
				
			case CQL_TINYINT :
				typeName = "TINYINT";
				break;
				
			case CQL_BIGINT :
				typeName = "BIGINT";
				break;
				
			case CQL_BINARY :
				typeName = "BINARY";
				break;
				
			case CQL_VARBINARY :
				typeName = "VARBINARY";
				break;
				
			case CQL_LONGVARBINARY :
				typeName = "LONGVARBINARY";
				break;
				
			case CQL_DATE :
				typeName = "DATE";
				break;
				
			case CQL_TIME :
				typeName = "TIME";
				break;
				
			case CQL_TIMESTAMP :
				typeName = "TIMESTAMP";
				break;
				
			case CQL_CHARUC :
				typeName = "CHARUC";
				break;
				
			case CQL_COLUMN_UNDEFINED_TYPE :
				throw InternalErrorException( __FILE__, __LINE__ );
			}

			S primaryKeyFlag = 0, unique_KeyFlag = 0, duplicateKeyFlag = 0;
			if( skg->PrimaryKey() )
				primaryKeyFlag = 1;
			if( skg->Unique() )
				unique_KeyFlag = 1;

			dbsql_.systemTableIndices().add( "",
											 table->authorizationId(),
											 table->tableName(),
											 pcs->columnName(),
											 0 /*table row flag*/,
											 CqlString( " " ),
											 skg->KeyNumber(),
											 loop,
											 static_cast< S >( pcs->type().typeType() ),
											 typeName,
											 pcs->precision(),
											 pcs->type().typeLength(),
											 pcs->scale(),
											 primaryKeyFlag,
											 unique_KeyFlag,
											 duplicateKeyFlag,
											 skg->IndexName() );
		}
	}

	//************************************************************************
	//**  Bindings are identical for UniqueKeyGroups, DuplicateKeyGroups    **
	//************************************************************************

	for( skg = table->duplicateKeyGroups().first(); skg; skg = table->duplicateKeyGroups().next() )
	{
		S primaryKeyFlag = 0, unique_KeyFlag = 0, duplicateKeyFlag = 1;

		for( colDesc = skg->SegmentedKeyColumns().first(), loop = 0; colDesc; colDesc = skg->SegmentedKeyColumns().next(), loop++ )
		{
			pcs = table->columns()[ colDesc->columnNumber() ];

			const char *typeName = 0;

			switch( pcs->type().typeType() )
			{
			case CQL_CHAR :
				typeName = "CHAR";
				break;
				
			case CQL_VARCHAR :
				typeName = "VARCHAR";
				break;
				
			case CQL_DECIMAL :
				typeName = "DECIMAL";
				break;
				
			case CQL_SMALLINT :
				typeName = "SMALLINT";
				break;
				
			case CQL_INTEGER :
				typeName = "INTEGER";
				break;
				
			case CQL_REAL :
				typeName = "REAL";
				break;
				
			case CQL_FLOAT :
				typeName = "FLOAT";
				break;
				
			case CQL_LONGVARCHAR :
				typeName = "LONGVARCHAR";
				break;
				
			case CQL_BIT :
				typeName = "BIT";
				break;
				
			case CQL_TINYINT :
				typeName = "TINYINT";
				break;
				
			case CQL_BIGINT :
				typeName = "BIGINT";
				break;
				
			case CQL_BINARY :
				typeName = "BINARY";
				break;
				
			case CQL_VARBINARY :
				typeName = "VARBINARY";
				break;
				
			case CQL_LONGVARBINARY :
				typeName = "LONGVARBINARY";
				break;
				
			case CQL_DATE :
				typeName = "DATE";
				break;
				
			case CQL_TIME :
				typeName = "TIME";
				break;
				
			case CQL_TIMESTAMP :
				typeName = "TIMESTAMP";
				break;
				
			case CQL_CHARUC :
				typeName = "CHARUC";
				break;
				
			case CQL_COLUMN_UNDEFINED_TYPE :
				throw InternalErrorException( __FILE__, __LINE__ );
			}

			dbsql_.systemTableIndices().add( "",
											 table->authorizationId(),
											 table->tableName(),
											 pcs->columnName(),
											 0 /*table row flag*/,
											 CqlString( " " ),
											 skg->KeyNumber(),
											 loop,
											 static_cast< S >( pcs->type().typeType() ),
											 typeName,
											 pcs->precision(),
											 pcs->type().typeLength(),
											 pcs->scale(),
											 primaryKeyFlag,
											 unique_KeyFlag,
											 duplicateKeyFlag,
											 skg->IndexName() );
		}
	}
}


//
//  at entry:
//
//  SelectExpression contains:
//
//  Table name in first element of list of tables_
//  List of columns_ comprising index
//
void SelectExpression::createIndex( bool creatingUniqueIndex, CqlString& indexName, bool preparing )
{
	UNI numberOfSegments, loop;
	S keyNumber;
	pTableSpecification table, newTable;
	pTripleStringListElement tsl;
	ColumnTable& cols = columns_;
	pAbstractColumnDescriptor keyColumn;
	pColumnSpecification colSpec;
	pSegmentedKeyGroup keyGroup;
	pColumn col;

	tsl = new TripleStringListElement;
	if( !tsl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	tsl->s1().setStringUpper( dbsql_.parse()->baseTableName() );
	tableNames_.add( tsl );

	processTables();
	table = tables_.first()->tableSpec();
	if( table->isView() )
		throw IllegalOperationForViewException( __FILE__, __LINE__ );

	processColumns();
	openUserFiles();

	newTable = new TableSpecification( dbsql_ );
	if( !newTable )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	*newTable = *table;
	keyNumber = table->numberOfKeys();
	newTable->numberOfKeys( static_cast< US >( table->numberOfKeys() + 1 ) );

	keyGroup = new SegmentedKeyGroup( keyNumber );
	if( !keyGroup )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	if( creatingUniqueIndex == CQL_YES )
		keyGroup->SetUnique();

	keyGroup->SetIndexName( indexName );

	numberOfSegments = cols.size();

	for( loop = 0, col = cols.first(); loop < numberOfSegments; loop++, col = cols.next() )
	{
		//
		//  for CreateIndex, all columns_ have only one column descriptor
		//
		colSpec = col->ColumnExpression().columns().first()->Column();

		keyColumn = AbstractColumnDescriptor::createObject( colSpec->type(), static_cast< US >( colSpec->columnNumber() ), col->descending() );
		keyGroup->SegmentedKeyColumns().add( keyColumn );
	}

	if( creatingUniqueIndex )
		newTable->uniqueKeyGroups().add( keyGroup );
	else
		newTable->duplicateKeyGroups().add( keyGroup );

	if( preparing == CQL_YES )
	{
		dbsql_.currentStatement()->type( CREATE_INDEX );
		dbsql_.currentStatement()->creationTable( newTable );
		dbsql_.currentStatement()->oldTable( table );
		return;
	}

	createIndexPart2( table, newTable, keyGroup );
}


void SelectExpression::createIndexPart2( pTableSpecification table, pTableSpecification newTable, pSegmentedKeyGroup keyGroup )
{
	pPermanentColumnSpecification pcs;
	pAbstractColumnDescriptor colDesc;
	CqlColumnTypes dataType;
	UNI loop;

	//  update dictionary information
	dbsql_.updateDictionaryInformation( newTable, table );

	for( colDesc = keyGroup->SegmentedKeyColumns().first(), loop = 0;
		 colDesc;
		 colDesc = keyGroup->SegmentedKeyColumns().next(), loop++ )
	{
		pcs = table->columns()[ colDesc->columnNumber() ];

		const char *ltypeName = 0;

		switch( pcs->type().typeType() )
		{
		case CQL_CHAR :
			ltypeName = "CHAR";
			break;
			
		case CQL_VARCHAR :
			ltypeName = "VARCHAR";
			break;
			
		case CQL_DECIMAL :
			ltypeName = "DECIMAL";
			break;
			
		case CQL_SMALLINT :
			ltypeName = "SMALLINT";
			break;
			
		case CQL_INTEGER :
			ltypeName = "INTEGER";
			break;
			
		case CQL_REAL :
			ltypeName = "REAL";
			break;
			
		case CQL_FLOAT :
			ltypeName = "FLOAT";
			break;
			
		case CQL_LONGVARCHAR :
			ltypeName = "LONGVARCHAR";
			break;
			
		case CQL_BIT :
			ltypeName = "BIT";
			break;
			
		case CQL_TINYINT :
			ltypeName = "TINYINT";
			break;
			
		case CQL_BIGINT :
			ltypeName = "BIGINT";
			break;
			
		case CQL_BINARY :
			ltypeName = "BINARY";
			break;
			
		case CQL_VARBINARY :
			ltypeName = "VARBINARY";
			break;
			
		case CQL_LONGVARBINARY :
			ltypeName = "LONGVARBINARY";
			break;
			
		case CQL_DATE :
			ltypeName = "DATE";
			break;
			
		case CQL_TIME :
			ltypeName = "TIME";
			break;
			
		case CQL_TIMESTAMP :
			ltypeName = "TIMESTAMP";
			break;
			
		case CQL_CHARUC :
			ltypeName = "CHARUC";
			break;
			
		case CQL_COLUMN_UNDEFINED_TYPE :
			throw InternalErrorException( __FILE__, __LINE__ );
		}

		S primaryKeyFlag = 0, unique_KeyFlag = 0, duplicateKeyFlag = 0;
		if( keyGroup->PrimaryKey() )
			primaryKeyFlag = 1;
		if( keyGroup->Unique() )
			unique_KeyFlag = 1;
		if( !primaryKeyFlag && !unique_KeyFlag )
			duplicateKeyFlag = 1;

		dbsql_.systemTableIndices().add( "",
										 table->authorizationId(),
										 table->tableName(),
										 pcs->columnName(),
										 0 /*table row flag*/,
										 CqlString( " " ),
										 keyGroup->KeyNumber(),
										 static_cast< US >( loop ),
										 static_cast< S >( pcs->type().typeType() ),
										 ltypeName,
										 pcs->precision(),
										 pcs->type().typeLength(),
										 pcs->scale(),
										 primaryKeyFlag,
										 unique_KeyFlag,
										 duplicateKeyFlag,
										 keyGroup->IndexName() );
	}

	table->addIndexMember( *keyGroup );
}


//
//  On entry:
//
//  SelectExpression contains:
//
//  Table name in first element of list of tables_
//  List of columns_ to add in Columns
//

void SelectExpression::alterTable( bool preparing )
{
	pTableSpecification newTable;
	pTableSpecification oldTable;
	pPermanentColumnSpecification col;
	pColumn newCol;
	UNI numberOfAddedColumns, loop1;

	newTable = new TableSpecification( dbsql_ );
	if( !newTable )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	processTables();
	openUserFiles();

	oldTable = tables_.first()->tableSpec();
	if( !oldTable )
		throw IllegalOperationForViewException( __FILE__, __LINE__ );

	//  copy the old file structure
	*newTable = *oldTable;

	//  increase column count
	numberOfAddedColumns = columns_.size();
	newTable->numberOfColumns( ((US)( newTable->numberOfColumns() + numberOfAddedColumns ) ) );

	//  Add new column structures
	for( loop1 = 0, newCol = columns_.first();
		loop1 < numberOfAddedColumns;
		loop1++, newCol = columns_.next() )
	{
		col = new PermanentColumnSpecification( *newCol->ColumnExpression().columns().first()->Column() );
		if( !col )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		newTable->columns().add( col );
	}

	if( preparing == CQL_YES )
	{
		dbsql_.currentStatement()->type( ALTER_TABLE );
		dbsql_.currentStatement()->creationTable( newTable );
		dbsql_.currentStatement()->oldTable( oldTable );
		return;
	}

	alterTablePart2( oldTable, newTable );
}


void SelectExpression::alterTablePart2( pTableSpecification oldTable, pTableSpecification newTable )
{
	oldTable->lockFile();

	dbsql_.beginTransaction();
	oldTable->renameToTemporary();
	newTable->createFiles();
	newTable->copyData( *oldTable );
	try
	{
		dbsql_.updateDictionaryInformation( oldTable, newTable );
	}
	catch( CqlException& ex )
	{
		dbsql_.rollbackTransaction( false );
		throw ex;
	}

	dbsql_.commitTransaction( false );
}


bool SelectExpression::advance( void )
{
	pColumn col;

	if( !nextResultRow() )
		return false;

	//********************  CHANGE ME!!!
	for( col = columns_.first(); col; col = columns_.next() )
		*col->ReportValue() = col->ColumnExpression().value()->value();

	return true;
}
