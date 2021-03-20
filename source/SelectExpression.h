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


#ifndef __SelectExpression_h
#define __SelectExpression_h


class SelectExpression
	: public SelectExpressionListElement,
	  public PredicateTypes,
	  public InstructionConstants,
	  public CqlConstants,
	  public ErrorConstants
{
	enum LinkStates
	{
		START,
		RETRY,
		SHIFT
	};

	enum ColumnProgressionStates
	{
		SELECT_LIST_COLUMNS,
		WHERE_CONDITION,
		GROUP_BY_COLUMNS,
		HAVING_CONDITION,
		ORDER_CONDITION
	};

	bool allLinks_;
	bool aggregateDistinctScan_;
	bool aggregateFunctions_;
	bool cartesianProductLink_;
	bool cleanedUp_;
	bool correlated_;
	bool correlatedLink_;
	bool distinct_;
	bool endGroup_;
	bool existsSubquery_;
	bool existsValueFlag_;
	bool finalTrip_;
	bool firstInExpression_;
	bool firstScan_;
	bool groupBy_;
	bool groupByVariableLength_;
	bool having_;
	bool linksSorted_;
	bool listOperationInProgress_;
	bool logicalFetch_;
	bool midGroup_;
	bool mostRecentHavingResult_;
	bool nextMostRecentHavingResult_;
	bool noCondition_;
	bool noSet_;
	bool notFlag_;
	bool oneSet_;
	bool onlyAggregateFunctions_;
	bool orderBy_;
	bool orderDescending_;
	bool orderEnabled_;
	bool orderTemporary_;
	bool refetchMode_;
	bool refetchOK_;
	bool setVariableLength_;
	bool tablesAndColumnsProcessed_;
	bool temporaryFileExists_;
	bool unionAll_;
	bool unionSet_;
	bool unique_;
	bool uniqueEnabled_;
	bool usingAggregateIndex_;
	bool usingCountIndex_;
	bool updateEnabled_;

	UC *baseTablePositionBuffer_;
	UL baseTablePositionBufferSize_;
	ColumnProgressionStates columnProgressionState_;
	ColumnTable columns_;
	UNI columnsLength_;
	SqlHandle& dbsql_;
	US existingOrderKey_;
	ColumnTable groupByColumns_;
	UNI groupByColumnsLength_;
	Expression havingExp_;
	LinkStates linkState_;
	UNI numberOfRowIds_;
	Expression orderByExp_;
	TemporaryResultFile orderFile_;
	Report report_;
	ResultSet results_;
	pAbstractTable rowList_;
	bool rowListNullflag_;
	RECID rowListPosition_;
	TableTable tables_;
	//
	//  This list holds the names collected by the parser.
	//  It is a triple string list, because each name may
	//  (ODBC syntax) have a preceding database name, and
	//  ANSI syntax allows a correlation name.  S() is the
	//  table name, S2() is the prefix, and S3() is the
	//  correlation name
	//

	TripleStringList tableNames_;
	TemporaryResultFile temporaryFile_;
	TemporaryResultFile uniqueFile_;
	TemporaryResultFile updateFile_;
	Expression whereCondition_;

	void addRowToResultSet( TemporaryResultFile& );
	void addToUpdateList( void );
	void aggregateScan( void );
	void allocateBaseTablePositionBuffer( UNI /*numberOfTables*/ );
	void allocateSetOrderBuffer( void );
	void allocateSetDataBuffer( void );
	void beginStrictLocking( void );
	void bindToTemporaryFile( TemporaryResultFile& );
	void checkForVariableLength( void );
	void cleanupReport( void );
	void combine( void );
	void computeDataLength( void );
	void createReport( void );
	void createTemporaryFile( TemporaryResultFile& );
	bool doCartesianProductLink();
	bool doLinks( void );
	void eliminateLink( pPredicate, pPredicate );
	void eliminateThisLink( pPredicate, pPredicate );
	void evaluate( void );
	bool findColumn( pExpressionColumnListElement expColListEl, bool /*correlated*/ = false );
	bool findCorrelatedColumn( pExpressionColumnListElement );
	pExpression firstExpression( void );
	bool firstResultRow();
	void groupScan( void );
	void generateReport( void );
	void identifyExpressionColumns( Expression& );
	bool identifyUpdateColumnNames( pAbstractTableSpecification, UpdateColumnNameAndExpList& );
	LinkStates linkState( void ) { return linkState_; }
	void magicLock( void );
	void makeHaving( void );
	void makeOrder( void );
	void makeUnique( void );
	void makeSets( void );
	bool memorySetFirst( pTableTableElement, pPredicate );
	bool memorySetNext( pTableTableElement, pPredicate );
	bool moreLinks( void );
	bool moreCartesianProductLinks( void );
	pExpression nextExpression( void );
	bool orderTemporaryFirst( void );
	bool orderTemporaryNext( void );
	void postFunctionProcessing( void );
	void refetchBaseTableRows( void );
	void runColumnExpressions( void );
	void scalarScan( TemporaryResultFile&, bool /*unbind after scan*/ );
	bool scanFirst( void );
	bool scanNext( void );
	void setFunctionSpaceNull( void );
	bool slaveDuplicateCheck( void );
	void sortLinks( bool /*doWork*/ = true );
	bool uniqueFirst( void );
	bool uniqueNext( void );
	bool updateListFirst( void );
	bool updateListNext( void );
	bool validityCheck( pPredicate );
	bool viewFirst( void );
	bool viewNext( void );

public :

	SelectExpression( SqlHandle& );
	~SelectExpression( void );

	SelectExpression& operator = ( const SelectExpression& );

	void addAllColumnsForTable( pColumn, pTableTableElement );
	void addToRowList( void );
	bool advance( void );
	bool aggregateFunctions( void ) { return aggregateFunctions_; }
	bool allLinks( void ) { return allLinks_; }
	void alterTable( bool /*preparing*/ );
	void alterTablePart2( TableSpecification*, TableSpecification* );
	bool assignmentCompatible( Column&, PermanentColumnSpecification& );
	void assignHavingExpression( pExpression* );
	void assignOrderByExpression( pExpression* );
	void assignWhereExpression( pExpression* );
	UC *baseTablePositionBuffer( void ) { return baseTablePositionBuffer_; }
	UNI baseTablePositionBufferSize( void ) { return baseTablePositionBufferSize_; }
	//
	//  sets up for parsing a column
	//
	Column *beginColumn( void );
	void bindColumnsForUpdate( TableTableElement&, UpdateColumnNameAndExpList& );
	bool cartesianProductLink( void ) { return cartesianProductLink_; }
	void checkForAllLinks( void );
	//
	//  checks types of value list against insert columns
	//
	void checkInsertValues( InsertColumnNameList& );
	//
	//  if a view, and view was defined WITH CHECK OPTION,
	//  check validity of insert or update
	//
	void checkView( pAbstractTableSpecification );
	void cleanup( void );
	//
	//  copies insert values, performing required conversions
	//
	void clearAggregateFunctions( void ) { aggregateFunctions_ = false; }
	void clearAggregateValues( void );
	void clearCartesianProductLink( void ) { cartesianProductLink_ = false; }
	void clearCleanedUp( void ) { cleanedUp_ = false; }
	void clearCorrelated( void ) { correlated_ = false; }
	void clearFinalTrip( void ) { finalTrip_ = false; }
	void clearFirstInExpression( void ) { firstInExpression_ = false; }
	void clearFirstScan( void ) { firstScan_ = false; }
	void clearGroupBy( void ) { groupBy_ = false; }
	void clearGroupByVariableLength( void ) { groupByVariableLength_ = false; }
	void clearHaving( void ) { having_ = false; }
	void clearLinksSorted( void ) { linksSorted_ = false; }
	void clearListOperationInProgress( void ) { listOperationInProgress_ = false; }
	void clearMidGroup( void ) { midGroup_ = false; }
	void clearNoCondition( void ) { noCondition_ = false; }
	void clearNoSet( void ) { noSet_ = false; }
	void clearNotFlag( void ) { notFlag_ = false; }
	void clearOneSet( void ) { oneSet_ = false; }
	void clearOnlyAggregateFunctions( void ) { onlyAggregateFunctions_ = false; }
	void clearOrderBy( void ) { orderBy_ = false; }
	void clearOrderDescending( void ) { orderDescending_ = false; }
	void clearOrderEnabled( void ) { orderEnabled_ = false; }
	void clearOrderTemporary( void ) { orderTemporary_ = false; }
	void clearRefetchMode( void ) { refetchMode_ = false; }
	void clearRefetchOK( void ) { refetchOK_ = false; }
	void clearTemporaryFileExists( void ) { temporaryFileExists_ = false; }
	void clearUnionAll( void ) { unionAll_ = false; }
	void clearUnionSet( void ) { unionSet_ = false; }
	void clearUnique( void ) { unique_ = false; }
	void clearUniqueEnabled( void ) { uniqueEnabled_ = false; }
	void clearUsingAggregateIndex( void ) { usingAggregateIndex_ = false; }
	void clearUsingCountIndex( void ) { usingCountIndex_ = false; }
	ColumnTable& columns( void ) { return columns_; }
	CompareResult compareGroupColumns( void );
	void copyInsertValues( pAbstractTableSpecification, InsertColumnNameList& );
	bool correlated( void ) { return correlated_; }
	Report& report( void ) { return report_; }
	void createRowListFile( void );
	void createIndex( bool /*uniqueIndex*/, CqlString& /*name*/, bool /*preparing*/ );
	void createIndexPart2( TableSpecification*, TableSpecification*, SegmentedKeyGroup* );
	void createTable( TableSpecification*, IndexNameListGroupList*, ForeignKeyNamesList*, bool /*preparing*/ );
	void createTablePart2( TableSpecification* );
	void createUpdateListFile( pTableTableElement );
	void createView( CqlString& name, CqlString& prefix );
	void cursorEvaluate( void );
	US dictionaryLength( void );
	bool distinct( void ) { return distinct_; }
	bool endGroup( void ) { return endGroup_; }
	US existingOrderKey( void ) { return existingOrderKey_; }
	void existsScan( void );
	bool existsValueFlag( void ) { return existsValueFlag_; }
	bool finalTrip( void ) { return finalTrip_; }
	bool firstInExpression( void ) { return firstInExpression_; }
	bool firstScan( void ) { return firstScan_; }
	bool groupBy( void ) { return groupBy_; }
	ColumnTable& groupByColumns( void ) { return groupByColumns_; }
	bool groupByVariableLength( void ) { return groupByVariableLength_; }
	bool having( void ) { return having_; }
	void insertWithSelect( InsertColumnNameList&, bool /*preparing*/ );
	void insertWithSelectPart2( SelectExpression*, pAbstractTableSpecification );
	void interactiveSelect( US /*numberOfSets*/ );
	bool linksSorted( void ) { return linksSorted_; }
	bool listOperationInProgress( void ) { return listOperationInProgress_; }
	bool logicalFetch( void ) { return logicalFetch_; }
	bool midGroup( void ) { return midGroup_; }
	bool mostRecentHavingResult( void ) { return mostRecentHavingResult_; }
	void mostRecentHavingResult( bool mrhr ) { mostRecentHavingResult_ = mrhr; }
	void moveGroupColumns( void );
	bool nextMostRecentHavingResult( void ) { return nextMostRecentHavingResult_; }
	bool nextResultRow( void );
	SelectExpression *nextSelectExpression( void );
	bool noCondition( void ) { return noCondition_; }
	bool noSet( void ) { return noSet_; }
	bool notFlag( void ) { return notFlag_; }
	US numberOfBaseTables( void );
	bool oneSet( void ) { return oneSet_; }
	bool onlyAggregateFunctions( void ) { return onlyAggregateFunctions_; }
	void openUserFiles( void );
	bool orderBy( void ) { return orderBy_; }
	Expression& orderByExp( void ) { return orderByExp_; }
	bool orderDescending( void ) { return orderDescending_; }
	bool orderEnabled( void ) { return orderEnabled_; }
	bool orderTemporary( void ) { return orderTemporary_; }
	void positionedDelete( bool /*preparing*/ );
	void positionedDeletePart2( pTableTableElement );
	void positionedUpdate( UpdateColumnNameAndExpList&, bool /*preparing*/ );
	void positionedUpdatePart2( UpdateColumnNameAndExpList&, pTableTableElement );
	SelectExpression *previousSelectExpression( void );
	void processColumns( void );
	void processSelect( void );
	void processSelectCommon( void );
	void processTables( bool /*clearInUseFlags*/ = true );
	void processTablesAndColumns( bool /*clearInUseFlags*/ = true );
	void processViewSelect( SelectExpressionList& );
	void readDictionaryInformation( TempBuffer& );
	bool refetchMode( void ) { return refetchMode_; }
	bool refetchOK( void ) { return refetchOK_; }
	void retrieveBaseTablePositions( void );
	void reprocessViewSelect( SelectExpressionList& );
	bool rowListFirst( void );
	bool rowListNext( void );
	void searchedDelete( bool /*preparing*/ );
	void searchedDeletePart2( TableTableElement* );
	void searchedUpdate( UpdateColumnNameAndExpList&, bool /*preparing*/ );
	void searchedUpdatePart2( UpdateColumnNameAndExpList&, pTableTableElement );
	void setAggregateFunctions( void ) { aggregateFunctions_ = true; }
	void setCartesianProductLink( void ) { cartesianProductLink_ = true; }
	void setCorrelated( void ) { correlated_ = true; }
	void setDistinct( void ) { distinct_ = true; }
	void setEndGroup( void ) { endGroup_ = true; }
	void setExistsSubquery( void ) { existsSubquery_ = true; }
	void setFinalTrip( void ) { finalTrip_ = true; }
	void setFirstInExpression( void ) { firstInExpression_ = true; }
	void setFirstScan( void ) { firstScan_ = true; }
	void setGroupBy( void ) { groupBy_ = true; }
	void setGroupByVariableLength( void ) { groupByVariableLength_ = true; }
	void setHaving( void ) { having_ = true; }
	void setLinksSorted( void ) { linksSorted_ = true; }
	void setListOperationInProgress( void ) { listOperationInProgress_ = true; }
	void setMidGroup( void ) { midGroup_ = true; }
	void setNextMostRecentHavingResult( bool r ) { nextMostRecentHavingResult_ = r; }
	void setNoCondition( void ) { noCondition_ = true; }
	void setNoSet( void ) { noSet_ = true; }
	void setNotFlag( void ) { notFlag_ = true; }
	void setOneSet( void ) { oneSet_ = true; }
	void setOnlyAggregateFunctions( void ) { onlyAggregateFunctions_ = true; }
	void setOrderBy( void ) { orderBy_ = true; }
	void setOrderDescending( void ) { orderDescending_ = true; }
	void setOrderEnabled( void ) { orderEnabled_ = true; }
	void setOrderTemporary( void ) { orderTemporary_ = true; }
	void setQueryExpressionResultSet( QueryExpression *qexp );
	void setRefetchMode( void ) { refetchMode_ = true; }
	void setRefetchOK( void ) { refetchOK_ = true; }
	void setTablesAndColumnsProcessed( void ) { tablesAndColumnsProcessed_ = true; }
	void setUnionAll( void ) { unionAll_ = true; }
	void setUnionSet( void ) { unionSet_ = true; }
	void setUnique( void ) { unique_ = true; }
	void setUniqueEnabled( void ) { uniqueEnabled_ = true; }
	void setUsingAggregateIndex( void ) { usingAggregateIndex_ = true; }
	void setUsingCountIndex( void ) { usingCountIndex_= true; }
	NI setVariableLength( void ) { return setVariableLength_; }
	void swapDataForGroupBy( void );
	TableTable& tables( void ) { return tables_; }
	TripleStringList& tableNames( void ) { return tableNames_; }
	TemporaryResultFile& temporaryFile( void ) { return temporaryFile_; }
	bool unionAll( void ) { return unionAll_; }
	bool unionSet( void ) { return unionSet_; }
	bool unique( void ) { return unique_; }
	bool usingAggregateIndex( void ) { return usingAggregateIndex_; }
	bool usingCountIndex( void ) { return usingCountIndex_; }
	void viewCleanup( void );
	Expression& whereCondition( void ) { return whereCondition_; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef SelectExpression *pSelectExpression;


#endif  //  __SelectExpression_h
