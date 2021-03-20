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


#ifndef __Expression_h
#define __Expression_h


class Expression : public PredicateTypes, public CqlConstants, public ErrorConstants, public InstructionConstants, public FunctionConstants
{
	//  This enumeration tracks the state of the stack.  Used to decide how to
	//  process some logical operators, such as logical not.
	enum ExpressionStackState
	{
		CQL_EXPS_EMPTY,
		CQL_EXPS_VALUE,
		CQL_EXPS_BOOLEAN
	};

	CqlColumnTypes assignmentType_;
	BoundColumn *bc_;
	ExpressionColumnList columns_;
	pAbstractValueElement columnValue_;
	L count_;
	SqlHandle& dbsql_;
	FunctionInstruction *function_;
	AbstractValueElement *functionSpace_;
	AbstractValueElement *functionSpace2_;
	InstructionList instructions_;
	CqlString label_;
	AbstractValueElement *last_;
	OptimizerPredicateList linkPredicates_;
	PredicateList predicates_;
	OptimizerPredicateList resolvedPredicates_;
	Predicate *root_;
	OptimizerPredicateList segmentablePredicates_;
	US uniqueScanLength_;
	CqlColumnTypes uniqueScanType_;
	AbstractValueElement *value_;
	AbstractValueElement *value2_;
	US valueExpressionLength_;
	CqlColumnTypes valueExpressionType_;
	ValueExpressionStack ves_;
	ExpressionStackState vesState_;
	CqlColumnTypes workingType_;

	bool aggregateDistinctScan_;
	bool aggregateFunctionInExpression_;
	bool doNotChangeType_;
	bool doNotChangeWorkingType_;
	bool doNotDeleteValue_;
	bool flipFlag_;
	bool viewFlag_;

	bool findPredicateForSegment( pPredicate, pPredicate, ColumnSpecification*, pPredicate* );
	pPredicate getTerminal( void );
	void pushCondition( bool );

public :

	Expression( SqlHandle& );
	~Expression( void );

	Expression& operator = ( const Expression& );

	void adjustPredicateTree( void );
	bool aggregateDistinctScan( void ) { return aggregateDistinctScan_; }
	bool aggregateFunctionInExpression( void ) { return aggregateFunctionInExpression_; }
	void allEqual( AbstractValueElement*, SubqueryElement* );
	bool allLinks( void );
	void allGreater( pAbstractValueElement, pSubqueryElement );
	void allGreaterOrEqual( pAbstractValueElement, pSubqueryElement );
	void allLess( pAbstractValueElement, pSubqueryElement );
	void allLessOrEqual( pAbstractValueElement, pSubqueryElement );
	void allNotEqual( pAbstractValueElement, pSubqueryElement );
	void allocateFunctionSpace( CqlColumnTypes );
	void anyEqual( pAbstractValueElement, pSubqueryElement );
	void anyNotEqual( pAbstractValueElement, pSubqueryElement );
	void anyGreater( pAbstractValueElement, pSubqueryElement );
	void anyGreaterOrEqual( pAbstractValueElement, pSubqueryElement );
	void anyLess( pAbstractValueElement, pSubqueryElement );
	void anyLessOrEqual( pAbstractValueElement, pSubqueryElement );
	CqlColumnTypes& assignmentType( void ) { return assignmentType_; }
	void assignmentType( CqlColumnTypes t ) { assignmentType_ = t; }
	void classify( bool /*correlated*/ );
	void clearAggregateDistinctScan( void ) { aggregateDistinctScan_ = false; };
	void clearAggregateValues( void );
	void clearViewFlag( void ) { viewFlag_ = false; }
	ExpressionColumnList& columns( void ) { return columns_; }
	AbstractValueElement *columnValue( void ) { return columnValue_; }
	void computeValueExpressionType( void );
	void convertValueToAssignmentType( const PermanentColumnSpecification& );
	void copyFunctionSpaceToValue( void );
	void copyValueToValue2( void );
	void correlatedSetIterate( SelectExpression* );
	L count( void ) { return count_; }
	void createPredicateList( void );
	SqlHandle& dbsql( void ) { return dbsql_; }
	US dictionaryLength( void );
	bool doNotChangeType( void ) { return doNotChangeType_; }
	void equal( pAbstractValueElement, pAbstractValueElement );
	bool evaluate( void );
	void evaluatePost( void );
	bool examineForAggregateFunction( void );
	void exchangeFunctionSpaceWithFunctionSpace2( void );
	void exchangeValueWithValue2( void );
	bool findSegmentedKey( void );
	void flipFlipFlag( void );
	void forceExpressionType( CqlColumnTypes type );
	AbstractValueElement *functionSpace( void ) { return functionSpace_; }
	void functionSpace( AbstractValueElement *fs ) { functionSpace_ = fs; }
	AbstractValueElement *functionSpace2( void ) { return functionSpace2_; }
	void greater( pAbstractValueElement, pAbstractValueElement );
	void greaterOrEqual( pAbstractValueElement, pAbstractValueElement );
	void incrementCount( void ) { count_++; }
	InstructionList& instructions( void ) { return instructions_; }
	CqlString& label( void ) { return label_; }
	AbstractValueElement *last( void ) { return last_; }
	void less( pAbstractValueElement, pAbstractValueElement );
	void lessOrEqual( pAbstractValueElement, pAbstractValueElement );
	OptimizerPredicateList& linkPredicates( void ) { return linkPredicates_; }
	void makePredicateList( pPredicate );
	bool makeSegmentedKey( pPredicate, pPredicate, bool /*try alternates*/ );
	void notEqual( pAbstractValueElement, pAbstractValueElement );
	AbstractValueElement **pFunctionSpace( void ) { return &functionSpace_; }
	void processInstructionForType( Instruction* );
	void processViewData( SelectExpressionList& );
	void promote( CqlColumnTypes /*type*/, bool useWorkingType = false );
	void pushFunctionSpace( void );
	void pushNo( void );
	void pushYes( void );
	void readDictionaryInformation( TempBuffer& );
	void releaseFunctionSpaces();
	void reprocessViewData( SelectExpressionList& );
	void reset( void );
	OptimizerPredicateList& resolvedPredicates( void ) { return resolvedPredicates_; }
	Predicate *root( void ) { return root_; }
	bool searchForSegments( Predicate* );
	OptimizerPredicateList& segmentablePredicates( void ) { return segmentablePredicates_; }
	void setAggregateDistinctScan( void ) { aggregateDistinctScan_ = true; }
	void setDoNotChangeType( void ) { doNotChangeType_ = true; }
	void setDoNotDeleteValue( void ) { doNotDeleteValue_ = true; }
	void setExpressionType( void );
	void setViewFlag( void ) { viewFlag_ = true; }
	US uniqueScanLength( void ) { return uniqueScanLength_; }
	void uniqueScanLength( US l ) { uniqueScanLength_ = l; }
	CqlColumnTypes uniqueScanType( void ) { return uniqueScanType_; }
	void uniqueScanType( CqlColumnTypes t ) { uniqueScanType_ = t; }
	AbstractValueElement *value( void ) { return value_; }
	void value( AbstractValueElement *v ) { value_ = v; }
	AbstractValueElement *value2( void ) { return value2_; }
	US valueExpressionLength( void ) { return valueExpressionLength_; }
	CqlColumnTypes valueExpressionType( void ) { return valueExpressionType_; }
	void valueExpressionType( CqlColumnTypes t ) { valueExpressionType_ = t; }
	ValueExpressionStack& ves( void ) { return ves_; }
	ExpressionStackState vesState( void ) { return vesState_; }
	void vesStateBoolean( void ) { vesState_ = CQL_EXPS_BOOLEAN; }
	void vesStateEmpty( void ) { vesState_ = CQL_EXPS_EMPTY; }
	bool vesStateIsBoolean( void ) { return vesState_ == CQL_EXPS_BOOLEAN; }
	bool vesStateIsEmpty( void ) { return vesState_ == CQL_EXPS_EMPTY; }
	bool vesStateIsValue( void ) { return vesState_ == CQL_EXPS_VALUE; }
	void vesStateValue( void ) { vesState_ = CQL_EXPS_VALUE; }
	void viewReset( void );
	CqlColumnTypes workingType( void ) { return workingType_; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef Expression *pExpression;


#endif  //  __Expression_h
