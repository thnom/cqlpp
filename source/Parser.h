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


#ifndef __Parser_h
#define __Parser_h


extern "C"
{
	struct _UIWithLeadingZeros
	{
		unsigned int val;
		int lzs;  /*  -1 means inactive  */
	};
	typedef struct _UIWithLeadingZeros UIWithLeadingZeros;
	typedef UIWithLeadingZeros *pUIWithLeadingZeros;
}


class Parser : public ParserConstants, public SetComparisonConstants, public CqlConstants, public ErrorConstants
{
public :
	enum OptionType
	{
		OPTION_DIRECTORY
	};

private :
	CqlString baseTableName_;
	CqlString baseTablePrefix_;
	ColumnSpecificationList createTableColumns_;
	pPermanentColumnSpecification currentCreateColumn_;
	pExpression currentExpression_;
	pQueryExpression cursorExpression_;
	CqlString cursorName_;
	pSelectExpression currentSelectExpression_;
	SqlHandle& dbsql_;
	pAbstractValueElement defaultValue_;
	CqlStringWithPosition embeddedStatement_;
	NC escapeCharacter_;
	FILEList files_;
	ForeignKeyNamesList foreignKeys_;
	GrantPrivilegeList grantPrivileges_;
	CqlString grantTableName_;
	CqlString grantTablePrefix_;
	GrantUserList grantUsers_;
	CqlString indexName_;
	CqlString indexPrefix_;
	IndexNameListGroupList indices_;
	InsertColumnNameList insertColumnNames_;
	StringList keyColumnNames_;
	CqlString *optionValue_;
	CqlString selectListName_;
	CqlString selectListPrefix_;
	ParserStack stack_;
	Expression tableCheckCondition_;
	CqlString tableListName_;
	CqlString tableListPrefix_;
	UpdateColumnNameAndExpList updateColumns_;
	UNI valueCounter_;
	StringList viewColumnNames_;
	CqlString viewedTableName_;
	CqlString viewedTablePrefix_;
	char zeroBuffer[ 100 ];

	bool batchMode_;
	bool cascade_;
	bool checkOption_;
	bool creatingUniqueIndex_;
	bool declaringCursor_;
	bool doingColumnElement_;
	bool doingColumns_;
	bool echo_;
	bool embeddedInput_;
	bool escape_;
	bool existsFlag_;
	bool grantOption_;
	bool insertWithSelect_;
	bool preparing_;
	bool restrict_;
	bool selectInto_;
	bool shuttingDown_;
	bool statementEnded_;
	bool unaryMinusFlag_;

	void addAllInstruction( ComparisonOperators );
	void addAndInstruction( void );
	void addAnyInstruction( ComparisonOperators );
	void addAvgInstruction( void );
	void addEqualsInstruction( void );
	void addGreaterInstruction( void );
	void addGreaterOrEqualInstruction( void );
	void addLessInstruction( void );
	void addLessOrEqualInstruction( void );
	void addMaxInstruction( void );
	void addMinInstruction( void );
	void addNotEqualInstruction( void );
	void addNotInstruction( void );
	void addOrInstruction( void );
	void addReferencedColumn( NC* );
	void addSumInstruction( void );
	void addValueInstruction( pAbstractValueElement );
	bool identifyInsertColumnNames( pAbstractTableSpecification );
	void insertWithValues( void );
	void insertWithValues2( pAbstractTableSpecification );
	void processDrop( pAbstractTableSpecification );

public :
	
	Parser( SqlHandle& );
	~Parser( void );

	void addAggregateFunction( AggregateFunctions );
	void addBetweenInstruction( void );
	void addColumn( const char * const /*name*/, const char * const /*prefix*/ = 0 );
	void addColumnUsingSelectListNames( void );
	void addComparisonOperator( ComparisonOperators );
	void addCountColumnInstruction( void );
	void addCountStarInstruction( void );
	void addCreateColumn( NC* /*name*/ );
	void addDivisionOperator( void );
	void addDynamicParameterPush( void );
	void addExistsInstruction( void );
	void addGrantee( const char * const /*userName*/ );
	void addGroupByColumn( NC* /*owner*/, NC* /*user*/ );
	void addIdentifierPush( void );
	void addLIKEOperator( void );
	void addLogicalOperator( LogicalOperators );
	void addMinusOperator( void );
	void addMultiplicationOperator( void );
	void addNOTOperator( void );
	void addNULLPush( void );
	void addPlusOperator( void );
	void addSetComparison( ComparisonOperators, ComparisonModifiers );
	void addTableName( NC* /*name*/ );
	void addToLabel( NC* /*stringToAdd*/ );
	void addUnaryMinusOperator( void );
	void addUnaryMinusOperatorIfNecessary( void );
	void addUpdateColumnIdentifier( NC* /*name*/ );
	void addUSERPush( void );
	void allocateCursorExpression( void );
	void alterTable( void );
	void approximateNumericDefaultValue( NC* /*value*/ );
	void approximateNumericLiteral( NC* /*value*/ );
	CqlString& baseTableName( void ) { return baseTableName_; }
	CqlString& baseTablePrefix( void ) { return baseTablePrefix_; }
	bool batchMode( void ) { return batchMode_; }
	void beginCheckClause( void );
	void beginColumn( void );
	void beginColumnCheckCondition( void );
	void beginDuplicateKeyGroup( void );
	void beginForeignKey( void );
	void beginPrimaryKeyGroup( void );
	void beginScript( NC* /*name*/, bool /*noShorten*/ );
	void beginUniqueKeyGroup( void );
	void binaryLiteral( NI /*value*/ );
	void characterDefaultValue( NC* /*value*/ );
	void characterStringLiteral( NC* /*value*/ );
	void cleanup( void );
	void clearBatchMode( void ) { batchMode_ = false; }
	void clearDoingColumns( void ) { doingColumns_ = false; }
	void clearEcho( void ) { echo_ = false; }
	void clearShuttingDown( void ) { shuttingDown_ = false; } 
	void clearStatementEnded( void ) { statementEnded_ = false; }
	void columnHeading( NC* /*string*/ );
	void commitWork( void );
	void createIndex( void );
	void createTable( void );
	ColumnSpecificationList& createTableColumns( void ) { return createTableColumns_; }
	static UIWithLeadingZeros *createUiwz( char* );
	void createView( void );
	void createViewPart2( CqlString&, CqlString&, pTempBuffer );
	pPermanentColumnSpecification currentCreateColumn( void ) { return currentCreateColumn_; }
	pSelectExpression currentSelectExpression( void ) { return currentSelectExpression_; }
	pQueryExpression cursorExpression( void ) { return cursorExpression_; }
	CqlString& cursorName( void ) { return cursorName_; }
	void dateDefaultValue( DateLiteral& /*value*/ );
	void dateLiteral( DateLiteral& /*value*/ );
	void declareCursor( void );
	bool declaringCursor( void ) { return declaringCursor_; }
	void dropIndex( void );
	void dropIndexPart2( pTableSpecification, pTableSpecification, pSegmentedKeyGroup );
	void dropTable( void );
	void dropView( void );
	bool echo( void ) { return echo_; }
	NC embeddedGetCharacter( void );
	bool embeddedInput( void ) { return embeddedInput_; }
	CqlStringWithPosition& embeddedStatement( void ) { return embeddedStatement_; }
	void endColumnElement( void );
	void endSelectListElement( void );
	void endSubquery( void );
	bool escape( void ) { return escape_; }
	NC escapeCharacter( void ) { return escapeCharacter_; }
	void escapeCharacter( NC c ) { escapeCharacter_ = c; }
	void exactNumericDefaultValue( NI /*mantissa*/,
								   UIWithLeadingZeros* /*fraction*/ );
	void exactNumericDefaultValue( UIWithLeadingZeros*, UIWithLeadingZeros* );
	void exactNumericLiteral( NI /*mantissa*/, UIWithLeadingZeros* /*fraction*/ );
	void exactNumericLiteral( UIWithLeadingZeros* /*mantissa*/, UIWithLeadingZeros* /*fraction*/ );
	FILEList& files( void ) { return files_; }
	Cursor *findCursor( void );
	ForeignKeyNamesList& foreignKeys( void ) { return foreignKeys_; }
	void generateSetPush( void );
	void grant( GrantPrivilegeList&, GrantUserList& );
	GrantPrivilegeList& grantPrivileges( void ) { return grantPrivileges_; }
	void grantPrivilegeAll( void );
	void grantPrivilegeDelete( void );
	void grantPrivilegeInsert( void );
	void grantPrivilegeReferences( void );
	void grantPrivilegeSelect( void );
	void grantPrivilegeUpdate( void );
	GrantUserList& grantUsers( void ) { return grantUsers_; }
	void groupBy( void );
	CqlString& indexName( void ) { return indexName_; }
	CqlString& indexPrefix( void ) { return indexPrefix_; }
	IndexNameListGroupList& indices( void ) { return indices_; }
	void initForStatement( void );
	void insert( void );
	InsertColumnNameList& insertColumnNames( void ) { return insertColumnNames_; }
	StringList& keyColumnNames( void ) { return keyColumnNames_; }
	void newStatement( void );
	CqlString& optionValue( void );
	void optionValue( char* );
	bool popAnInputFile( void );
	void positionedDelete( void );
	void positionedUpdate( void );
	void prepare( void );
	bool preparing( void ) { return preparing_; }
	void processDropPart2( pAbstractTableSpecification );
	void quit( void );
	void resetValueCounter( void ) { valueCounter_ = 0; }
	void revoke( GrantPrivilegeList&, GrantUserList& );
	void rollbackWork( void );
	void searchedDelete( void );
	void searchedUpdate( void );
	void select( void );
	void selectDistinct( void );
	void selectUnique( void );
	void setAlterColumnName( NC* /*name*/ );
	void setBaseTablePrefix( NC* /*prefix*/ );
	void setBatchMode( void ) { batchMode_ = true; }
	void setCascade( void ) { cascade_ = true; }
	void setCheckOption( void ) { checkOption_ = true; }
	void setColumnIndex( void );
	void setColumnLength( NI /*length*/ );
	void setColumnLength( UIWithLeadingZeros* /*length*/ );
	void setColumnNotNull( void );
	void setColumnType( CqlColumnTypes );
	void setColumnUnique( void );
	void setCorrelationName( NC* /*name*/ );
	void setCreateColumnIdentifier( NC* /*identifier*/ );
	void setCreatingUniqueIndex( void ) { creatingUniqueIndex_ = true; }
	void setDeclaringCursor( void ) { declaringCursor_ = true; }
	void setDefaultValue( void );
	void setDefaultValueNull( void );
	void setDefaultValueUser( void );
	void setOption( OptionType );
	void setOrderDescending( void );
	void setEcho( void ) { echo_ = true; }
	void setEmbeddedInput( void ) { embeddedInput_ = true; }
	void setEscape( void ) { escape_ = true; }
	void setExistsFlag( void ) { existsFlag_ = true; }
	void setGrantOption( void ) { grantOption_ = true; }
	void setGrantTableName( NC* /*name*/ );
	void setGrantTablePrefix( NC* /*prefix*/ );
	void setIndexColumnDescending( void );
	void setIndexColumnIdentifier( NC* /*identifier*/ );
	void setInsertColumnIdentifier( NC* /*identifier*/ );
	void setInsertWithSelect( void ) { insertWithSelect_ = true; }
	void setJustifyCenter( void );
	void setJustifyRight( void );
	void setPrecision( NI /*precision*/ );
	void setPrecision( UIWithLeadingZeros* /*precision*/ );
	void setPreparing( void ) { preparing_ = true; }
	void setKeyColumn( NC* /*name*/ );
	void setReferenceColumnIdentifier( NC* /*name*/ );
	void setReferencedIdentifier( NC* /*identifier*/ );
	void setReferencedTableName( NC* /*name*/ );
	void setReferencedTablePrefix( NC* /*prefix*/ );
	void setReferencingColumnIdentifier( NC* );
	void setReferencingIdentifier( NC* );
	void setRestrict( void ) { restrict_ = true; }
	void setScale( NI /*scale*/ );
	void setScale( UIWithLeadingZeros* /*scale*/ );
	void setSegmentedKeyColumn( NC* /*name*/ );
	void setSelectInto( void ) { selectInto_ = true; }
	void setSelectListName( NC* );
	void setSelectListPrefix( NC* );
	void setShuttingDown( void ) { shuttingDown_ = true; }
	void setStatementEnded( void ) { statementEnded_ = true; }
	void setUnaryMinusFlag( void ) { unaryMinusFlag_ = true; }
	void setUpdateColumnIdentifier( NC* );
	void setUpdateTableName( NC* );
	void setViewColumnIdentifier( NC* );
	void setViewedTableName( NC* );
	void setViewedTablePrefix( NC* );
	void showOption( OptionType );
	bool shuttingDown( void ) { return shuttingDown_; }
	void stackPop( void );
	void stackPush( void );
	void startHaving( void );
	void startOrderBy( void );
	void startSubquery( void );
	void startWhere( void );
	bool statementEnded( void ) { return statementEnded_; }
	void statementInitialization( void );
	Expression& tableCheckCondition( void ) { return tableCheckCondition_; }
	void timeDefaultValue( NC* /*value*/ );
	void timeLiteral( NC* /*value*/ );
	void timestampDefaultValue( NC* /*value*/ );
	void timestampLiteral( NC* /*value*/ );
	UpdateColumnNameAndExpList& updateColumns( void ) { return updateColumns_; }
	StringList& viewColumnNames( void ) { return viewColumnNames_; }
	CqlString& viewedTableName( void ) { return viewedTableName_; }
	CqlString& viewedTablePrefix( void ) { return viewedTablePrefix_; }
	NI yywrap( void );
	char *zeroString( UIWithLeadingZeros* );
};

typedef Parser *pParser;


#endif  //  __Parser_h
