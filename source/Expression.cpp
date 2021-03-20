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


Expression::Expression( SqlHandle& sqlh )
	: assignmentType_( CQL_COLUMN_UNDEFINED_TYPE ),
	  columns_(),
	  columnValue_( 0 ),
	  count_( 0 ),
	  dbsql_( sqlh ),
	  function_( 0),
	  functionSpace_( 0 ),
	  functionSpace2_( 0 ),
	  instructions_(),
	  last_( 0 ),
	  linkPredicates_( sqlh ),
	  predicates_( sqlh ),
	  resolvedPredicates_( sqlh ),
	  root_( 0 ),
	  segmentablePredicates_( sqlh ),
	  uniqueScanLength_( 0 ),
	  uniqueScanType_( CQL_COLUMN_UNDEFINED_TYPE ),
	  value_( 0 ),
	  value2_( 0 ),
	  valueExpressionLength_( 0 ),
	  valueExpressionType_( CQL_COLUMN_UNDEFINED_TYPE ),
	  ves_(),
	  vesState_( CQL_EXPS_EMPTY ),
	  workingType_( CQL_COLUMN_UNDEFINED_TYPE ),
	  aggregateDistinctScan_( false ),
	  aggregateFunctionInExpression_( false ),
	  doNotChangeType_( false ),
	  doNotChangeWorkingType_( false ),
	  doNotDeleteValue_( false ),
	  flipFlag_( false ),
	  viewFlag_( false )
{
}


Expression::~Expression( void )
{
}


void Expression::anyEqual( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();

	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_EQUAL, true );
	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushYes();
	else
		pushNo();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::anyNotEqual( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();

	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_EQUAL, true );

	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushNo();
	else
		pushYes();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::anyLess( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();

	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_GREATER, true );

	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushYes();
	else
		pushNo();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::anyLessOrEqual( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();

	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_GREATER_OR_EQUAL, true );

	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushYes();
	else
		pushNo();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::anyGreater( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();

	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_LESS, true );

	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushYes();
	else
		pushNo();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::anyGreaterOrEqual( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();

	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_LESS_OR_EQUAL, true );

	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushYes();
	else
		pushNo();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::allEqual( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();

	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_GREATER, true );

	subqueryResultSet->beginIsamOperation( 0, true );
	bool result;
	result = subqueryResultSet->findFirst( false );

	if( result )
		//  greater exists, so all are not equal
		pushNo();
	else
	{
		//  true means freeable
		subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_LESS, true );
		subqueryResultSet->beginIsamOperation( 0, true );
		subqueryResultSet->findFirst( result );

		if( result )
			//  less exists, so all are not equal
			pushNo();
		else
			pushYes();
	}

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::allNotEqual( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();
	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_EQUAL, true );
	subqueryResultSet->beginIsamOperation( 0, true );
	if( subqueryResultSet->findFirst( false ) )
		pushNo();  //  Equal true, so all not equal false
	else
		pushYes();
	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::allLess( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();
	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_LESS_OR_EQUAL, true );
	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushNo();
	else
		pushYes();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::allLessOrEqual( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();
	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_LESS, true );
	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushNo();
	else
		pushYes();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::allGreater( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();
	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_GREATER_OR_EQUAL, true );
	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushNo();
	else
		pushYes();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::allGreaterOrEqual( pAbstractValueElement val1, pSubqueryElement subqEl )
{
	AbstractTable *subqueryResultSet = subqEl->selectExpression()->temporaryFile().ifile();
	//  true means freeable
	subqueryResultSet->setConditionAV( 0, val1->value().avalue(), CQL_COP_GREATER, true );
	subqueryResultSet->beginIsamOperation( 0, true );

	if( subqueryResultSet->findFirst( false ) )
		pushNo();
	else
		pushYes();

	subqueryResultSet->unbindAllColumns();
	subqueryResultSet->clearConditions();
}


void Expression::pushCondition( bool trueOrFalse )
{
	pIntegerLiteralElement ile;

	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	IntegerValue& integer = dynamic_cast< Cql_Integer& >( ile->value() ).instance().value();
	integer = trueOrFalse;

	ves_.pushValue( ile );
}


void Expression::pushYes( void )
{
	if( flipFlag_ )
	{
		pushCondition( false );
		flipFlag_ = false;
	}
	else
		pushCondition( true );
}


void Expression::pushNo( void )
{
	if( flipFlag_ )
	{
		pushCondition( true );
		flipFlag_ = false;
	}
	else
		pushCondition( false );
}


void Expression::flipFlipFlag( void )
{
	if( flipFlag_ )
		flipFlag_ = false;
	else
		flipFlag_ = true;
}


void Expression::pushFunctionSpace( void )
{
	pAbstractValueElement el = AbstractValueElement::createObject( functionSpace_->dataType() );
	*el = *functionSpace_;
	ves_.pushValue( el );
}


void Expression::allocateFunctionSpace( CqlColumnTypes aType )
{
	functionSpace_ = AbstractValueElement::createObject( aType );
	functionSpace_->value().setNullflag();
}


void Expression::clearAggregateValues( void )
{
	if( functionSpace_ )
	{
		delete functionSpace_;
		functionSpace_ = 0;
	}

	if( functionSpace2_ )
	{
		delete functionSpace2_;
		functionSpace2_ = 0;
	}
}


void Expression::promote( CqlColumnTypes aType, bool useWorkingType )
{
	CqlColumnTypes *destType;


	if( !useWorkingType )
	{
		if( doNotChangeType_ == true )
			return;

		destType = &valueExpressionType_;
	}
	else
	{
		if( doNotChangeWorkingType_ == true )
			return;
		
		destType = &workingType_;
	}

	switch( destType->typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		*destType = aType;
		break;

	case CQL_VARCHAR :
	case CQL_CHARUC :
	case CQL_LONGVARCHAR :
		switch( aType.typeType() )
		{
		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		//  numeric types can occur for some functions
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_TINYINT :
		case CQL_DECIMAL :
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	case CQL_CHAR :
		switch( aType.typeType() )
		{
		case CQL_CHAR :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		//  numeric types can occur for some functions
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_TINYINT :
		case CQL_DECIMAL :
			break;

		case CQL_CHARUC :
			*destType = aType;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	case CQL_TINYINT :
	case CQL_BIT :
		switch( aType.typeType() )
		{
		case CQL_TINYINT :
		case CQL_BIT :
			break;

		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_DECIMAL :
		case CQL_REAL :
		case CQL_FLOAT :
			*destType = aType;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	case CQL_SMALLINT :
		switch( aType.typeType() )
		{
		case CQL_SMALLINT :
		case CQL_TINYINT :
		case CQL_BIT :
			break;

		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_DECIMAL :
		case CQL_REAL :
		case CQL_FLOAT :
			*destType = aType;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	case CQL_INTEGER :
		switch( aType.typeType() )
		{
		case CQL_TINYINT :
		case CQL_BIT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
			break;

		case CQL_BIGINT :
		case CQL_DECIMAL :
		case CQL_REAL :
		case CQL_FLOAT :
			*destType = aType;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	case CQL_BIGINT :
		switch( aType.typeType() )
		{
		case CQL_TINYINT :
		case CQL_BIT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
			break;

		case CQL_DECIMAL :
		case CQL_REAL :
		case CQL_FLOAT :
			*destType = aType;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	case CQL_DECIMAL :
		switch( aType.typeType() )
		{
		case CQL_TINYINT :
		case CQL_BIT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_DECIMAL :
			break;

		case CQL_REAL :
		case CQL_FLOAT :
			*destType = aType;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	
	case CQL_REAL :
		switch( aType.typeType() )
		{
		case CQL_TINYINT :
		case CQL_BIT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_DECIMAL :
		case CQL_REAL :
			break;

		case CQL_FLOAT :
			*destType = aType;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	case CQL_FLOAT :
		switch( aType.typeType() )
		{
		case CQL_TINYINT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_DECIMAL :
		case CQL_BIT :
		case CQL_REAL :
		case CQL_FLOAT :
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	case CQL_DATE :
		switch( aType.typeType() )
		{
		case CQL_DATE :
			break;

		case CQL_TIME :
		case CQL_TIMESTAMP :
		//  character types can occur with function_s
		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
			*destType = CQL_TIMESTAMP;
			break;

		//  numeric types can occur with function_s.
		case CQL_TINYINT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_BIT :
			*destType = CQL_DATE;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;
		
	case CQL_TIME :
		switch( aType.typeType() )
		{
		case CQL_TIME :
			break;

		case CQL_DATE :
		case CQL_TIMESTAMP :
		//  character types can occur with function_s
		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
			*destType = CQL_TIMESTAMP;
			break;

		//  numeric types can occur with function_s.
		case CQL_TINYINT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_BIT :
			*destType = CQL_TIME;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;


	case CQL_TIMESTAMP :
		switch( aType.typeType() )
		{
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		//  character types can occur with function_s
		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
			*destType = CQL_TIMESTAMP;
			break;

		//  numeric types can occur with function_s.
		case CQL_TINYINT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_BIT :
			*destType = CQL_TIMESTAMP;
			break;

		default :
			throw InvalidTypeCombinationException( __FILE__, __LINE__ );
		}
		break;

	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		//
		//  binary columns_ cannot be used with expressions
		//
		throw InvalidTypeCombinationException( __FILE__, __LINE__ );
	}

	if( aType.typeLength() )
		valueExpressionLength_ = static_cast< US >( aType.typeLength() );
}


void Expression::processInstructionForType( pInstruction ins )
{
	pIdentifierInstruction idIns;
	pValueInstruction valIns;
	pFunctionInstruction funcIns;

	switch( ins->OpCode() )
	{
	case IDENTIFIER_PUSH :
	case NULLPUSH :
		idIns = ((pIdentifierInstruction)ins);
		promote( idIns->col()->type() );
		break;

	case VALUE_PUSH :
		valIns = ((pValueInstruction)ins);
		switch( valIns->El()->valueType() )
		{
		case DYNAMIC_ELEMENT :
			//  not known at this time
			break;

		case NULL_ELEMENT :
			//  null of whatever time
			break;

		case IDENTIFIER_ELEMENT :
		case SUBQUERY_ELEMENT :
			//
			//  should not occur here
			//
			throw ExpressionInconsistencyException( __FILE__, __LINE__ );

		case LITERAL_ELEMENT :
			switch( valIns->El()->dataType().typeType() )
			{
			case CQL_CHAR :
			case CQL_VARCHAR :
			case CQL_LONGVARCHAR :
				promote( CQL_CHAR );
				break;

			case CQL_CHARUC :
				promote( CQL_CHARUC );
				break;

			case CQL_REAL :
			case CQL_FLOAT :
				promote( CQL_FLOAT );
				break;

			case CQL_DECIMAL :
				promote( CQL_DECIMAL );
				break;

			case CQL_BIT :
			case CQL_TINYINT :
			case CQL_SMALLINT :
			case CQL_INTEGER :
			case CQL_BIGINT :
				promote( CQL_INTEGER );
				break;

			case CQL_DATE :
				promote( CQL_DATE );
				break;

			case CQL_TIME :
				promote( CQL_TIME );
				break;

			case CQL_TIMESTAMP :
				promote( CQL_TIMESTAMP );
				break;

			case CQL_COLUMN_UNDEFINED_TYPE :
			case CQL_BINARY :
			case CQL_VARBINARY :
			case CQL_LONGVARBINARY :
				throw InternalErrorException( __FILE__, __LINE__ );
			}
			break;

		case ABSTRACT_VALUE_TYPE_NOT_SET :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
		break;

	case ALL_FUNCTION :
	case EVALUATE_FUNCTION :
		funcIns = ((pFunctionInstruction)ins);
		switch( funcIns->FuncId() )
		{
		case FUNC_COUNT1 :
		case FUNC_COUNT2 :
		case FUNC_LENGTH :
			promote( CQL_DECIMAL );
			break;

		//
		//  these function_s assume the type of their arguments
		//
		case FUNC_IFNULL :
		case FUNC_CONVERT :
			break;

		//
		//  these function_s assume the type of its arguments,
		//  which must be numeric
		//
		case FUNC_SUM :
		case FUNC_AVG :
		case FUNC_MIN :
		case FUNC_MAXIMUM :
		case FUNC_ABS :
		case FUNC_CEILING :
		case FUNC_FLOOR :
			break;

		case FUNC_ASCII :
		case FUNC_LOCATE :
		case FUNC_LEFT :
		case FUNC_RIGHT :
		case FUNC_MOD :
		case FUNC_SIGN :
		case FUNC_DAYOFMONTH :
		case FUNC_DAYOFWEEK :
		case FUNC_DAYOFYEAR :
		case FUNC_MONTH :
		case FUNC_QUARTER :
		case FUNC_WEEK :
		case FUNC_YEAR :
		case FUNC_HOUR :
		case FUNC_MINUTE :
		case FUNC_SECOND :
			valueExpressionType_ = CQL_DECIMAL;
			break;

		case FUNC_CHAR :
		case FUNC_CONCAT :
		case FUNC_INSERT :
		case FUNC_LTRIM :
		case FUNC_LCASE :
		case FUNC_REPEAT :
		case FUNC_REPLACE :
		case FUNC_RTRIM :
		case FUNC_SUBSTRING :
		case FUNC_UCASE :
		case FUNC_USER :
		case FUNC_DATABASE :
			valueExpressionType_ = CQL_CHAR;
			break;

		case FUNC_ACOS :
		case FUNC_ASIN :
		case FUNC_ATAN :
		case FUNC_ATAN2 :
		case FUNC_COS :
		case FUNC_COT :
		case FUNC_EXP :
		case FUNC_LOG :
		case FUNC_PI :
		case FUNC_RAND :
		case FUNC_SIN :
		case FUNC_SQRT :
		case FUNC_TAN :
			valueExpressionType_ = CQL_FLOAT;
			break;

		case FUNC_NOW :
		case FUNC_CURDATE :
		case FUNC_CURTIME :
			valueExpressionType_ = CQL_TIMESTAMP;
			break;

		case NOT_A_FUNCTION :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
		break;

	case Instruction::TERTIARY_OPERATOR :
	case Instruction::GET_ESCAPE :
	case Instruction::SET_PUSH :
	case Instruction::CQL_ALL :
	case Instruction::CQL_ANY :
	case Instruction::CORRELATED_PUSH :
	case Instruction::SUBQUERY_PUSH :
	case Instruction::UNION_ALL :
	case Instruction::UNION_DISTINCT :
	case Instruction::INTERSECTION :
	case Instruction::CQL_MINUS :
	case Instruction::DYNAMIC_PARAMETER_PUSH :
	case Instruction::UNARY_OPERATOR :
	case Instruction::BINARY_OPERATOR :
	case Instruction::IN_OPERATOR :
	case Instruction::ASSIGNMENT_OPERATOR :
		break;

	case Instruction::UNSET :
		throw InternalErrorException( __FILE__, __LINE__ );
	}
}


void Expression::setExpressionType( void )
{
	pInstruction ins;

	valueExpressionType_ = CQL_COLUMN_UNDEFINED_TYPE;

	for( ins = instructions_.first(); ins; ins = instructions_.next() )
		processInstructionForType( ins );
}


bool Expression::allLinks( void )
{
	pPredicate pred;

	for( pred = predicates_.first(); pred; pred = predicates_.next() )
		if( !pred->linkPredicate() )
			return false;

	return true;
}


void Expression::createPredicateList( void )
{
	pInstruction ins;
	pAbstractPredicateOperand apop;

	for( ins = instructions_.first(); ins; ins = instructions_.next() )
		predicates_.addToTree( ins );

	apop = predicates_.predStack().pop();
	if( !apop )
		root_ = ((pPredicate)0);
	else
	{
		root_ = apop->descendent();
		delete apop;
	}
}


void Expression::makePredicateList( pPredicate pred )
{
	switch( pred->type() )
	{
	case TERMINAL :
	case MIXED :
		//
		//  if predicate is terminal and resolvable, it is the entire list
		//
		if( pred->res() == RESOLVE )
			resolvedPredicates_.add( pred );
		break;

	case NONTERMINAL :
		makePredicateList( pred->left()->descendent() );
		if( pred->right() )
			makePredicateList( pred->right()->descendent() );
		break;

	case PREDICATE_UNKNOWN :
		break;
	}
}


void Expression::processViewData( SelectExpressionList& sel )
{
	instructions_.processViewData( sel );
	columns_.processViewData( instructions_ );
	predicates_.processViewData( instructions_, columns_ );
	linkPredicates_.processViewData( instructions_, columns_ );
	resolvedPredicates_.processViewData( instructions_, columns_ );
}


void Expression::reprocessViewData( SelectExpressionList& sel )
{
	instructions_.reprocessViewData( sel );
}


void Expression::convertValueToAssignmentType( const PermanentColumnSpecification& pcs )
{
	pAbstractValueElement convertedVal;

	convertedVal = AbstractValueElement::createObject( pcs.type() );
	*convertedVal = *value_;
	delete value_;
	value_ = convertedVal;
}


void Expression::writeDictionaryInformation( TempBuffer& buffer )
{
	UNI rootPredicateNumber;

	predicates_.writeDictionaryInformation( buffer );
	linkPredicates_.writeDictionaryInformation( buffer );
	resolvedPredicates_.writeDictionaryInformation( buffer );

	if( root_ )
		rootPredicateNumber = root_->predicateNumber();
	else
		rootPredicateNumber = 0;

	buffer << rootPredicateNumber << valueExpressionType_;

	columns_.writeDictionaryInformation( buffer );
	instructions_.writeDictionaryInformation( buffer );
}


void Expression::readDictionaryInformation( TempBuffer& buffer )
{
	predicates_.readDictionaryInformation( buffer );
	linkPredicates_.readDictionaryInformation( buffer );
	resolvedPredicates_.readDictionaryInformation( buffer );

	UNI predicateNumber;
	buffer >> predicateNumber;

	if( predicates_.size() )
		root_ = predicates_[ static_cast< US >( predicateNumber ) ];
	else
		root_ = 0;

	buffer >> valueExpressionType_;

	columns_.readDictionaryInformation( buffer );
	instructions_.readDictionaryInformation( buffer );
}


Expression& Expression::operator = ( const Expression& other )
{
	assignmentType_ = other.assignmentType_;
	columns_ = other.columns_;

	if( other.columnValue_ )
	{
		columnValue_ = AbstractValueElement::createObject( other.columnValue_->dataType() );
		*columnValue_ = *other.columnValue_;
	}
	else
		columnValue_ = ((pAbstractValueElement)0);

	count_ = other.count_;

	if( other.function_ )
		function_ = FunctionInstruction::createFunctionInstruction( dbsql(), other.function_->FuncId(), other.function_->NumberOfArguments() );
	else
		function_ = 0;

	if( other.functionSpace_ )
	{
		functionSpace_ = AbstractValueElement::createObject( other.functionSpace_->dataType() );
		*functionSpace_ = *other.functionSpace_;
	}
	else
		functionSpace_ = ((pAbstractValueElement)0);

	if( other.functionSpace2_ )
	{
		functionSpace2_ = AbstractValueElement::createObject( other.functionSpace2_->dataType() );
		*functionSpace2_ = *other.functionSpace2_;
	}
	else
		functionSpace2_ = ((pAbstractValueElement)0);

	instructions_ = other.instructions_;
	label_ = other.label_;

	if( other.last_)
	{
		last_ = AbstractValueElement::createObject( other.last_->dataType() );
		*last_ = *other.last_;
	}
	else
		last_ = ((pAbstractValueElement)0);

	linkPredicates_ = other.linkPredicates_;
	predicates_ = other.predicates_;
	resolvedPredicates_ = other.resolvedPredicates_;

	if( other.root_ )
	{
		root_ = new Predicate( dbsql_ );
		if( !root_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*root_ = *other.root_;
	}
	else
		root_ = 0;

	segmentablePredicates_ = other.segmentablePredicates_;
	uniqueScanLength_ = other.uniqueScanLength_;
	uniqueScanType_ = other.uniqueScanType_;

	if( other.value_ )
	{
		value_ = AbstractValueElement::createObject( other.value_->dataType() );
		*value_ = *other.value_;
	}
	else
		value_ = ((pAbstractValueElement)0);

	if( other.value2_ )
	{
		value2_ = AbstractValueElement::createObject( other.value2_->dataType() );
		*value2_ = *other.value2_;
	}
	else
		value2_ = ((pAbstractValueElement)0);

	valueExpressionLength_ = other.valueExpressionLength_;
	valueExpressionType_ = other.valueExpressionType_;
	ves_ = other.ves_;
	workingType_ = other.workingType_;
	aggregateDistinctScan_ = other.aggregateDistinctScan_;
	doNotChangeType_ = other.doNotChangeType_;
	doNotChangeWorkingType_ = other.doNotChangeWorkingType_;
	doNotDeleteValue_ = other.doNotDeleteValue_;
	viewFlag_ = other.viewFlag_;
	return *this;
}


bool Expression::findPredicateForSegment( pPredicate andPred, pPredicate termPred, pColumnSpecification colSpec, pPredicate *segmentPredicate )
{
	pPredicate tpred;
	pAbstractPredicateOperand masterPredOp;
	pColumnSpecification predColSpec;

	for( tpred = predicates_.first(); tpred; tpred = predicates_.next() )
	{
		if( tpred == termPred
			|| tpred->notSegmentable()
			|| tpred->lowPredicateNumber() < andPred->lowPredicateNumber()
		    || tpred->highPredicateNumber() > andPred->highPredicateNumber()
			|| tpred->partOfSegmentedKey()
		    || ( tpred->res() != RESOLVE && tpred->res() != NORESOLVE ) )
			continue;

		masterPredOp = tpred->left();
		if( !masterPredOp || !masterPredOp->identifierPush() )
		{
			masterPredOp = tpred->right();
			if( !masterPredOp || !masterPredOp->identifierPush() )
				continue;
		}

		//
		//  masterPredOp now references an identifier push instruction.
		//  colDesc references the table and column
		//
		predColSpec = masterPredOp->ins()->col();
		if( !predColSpec )
			throw InternalErrorException( __FILE__, __LINE__ );

		//
		//  does predicate reference the same column as the segment?
		//
		if( colSpec->Cno() == predColSpec->Cno() && colSpec->TtEl() == predColSpec->TtEl() )
		{
			*segmentPredicate = tpred;
			if( tpred->res() == RESOLVE )
				resolvedPredicates_.remove( tpred );
			return true;
		}
	}

	return false;
}


pPredicate Expression::getTerminal( void )
{
	pPredicate pred = predicates_.first();

	if( !pred )
		return 0;

	return pred->getTerminal();
}


bool Expression::examineForAggregateFunction( void )
{
	pInstruction ins;
	pFunctionInstruction funcIns;

	for( ins = instructions_.first(); ins; ins = instructions_.next() )
	{
		switch( ins->OpCode() )
		{
		case EVALUATE_FUNCTION :
			funcIns = ((pFunctionInstruction)ins);
			switch( funcIns->FuncId() )
			{
			case FUNC_AVG :
			case FUNC_COUNT1:
			case FUNC_COUNT2 :
			case FUNC_MAXIMUM :
			case FUNC_MIN :
			case FUNC_SUM :
				aggregateFunctionInExpression_ = true;
				return true;

			default :
				break;
			}
			break;

		default :
			break;
		}
	}

	return false;
}


void Expression::copyValueToValue2( void )
{
	if( !value2_ )
		value2_ = AbstractValueElement::createObject( valueExpressionType_ );

	*value2_ = *value_;
}


void Expression::exchangeValueWithValue2( void )
{
	pAbstractValueElement tvalue_;

	if( !value2_ )
		value2_ = AbstractValueElement::createObject( valueExpressionType_ );

	tvalue_ = AbstractValueElement::createObject( valueExpressionType_ );

	*tvalue_ = *value2_;
	*value2_ = *value_;
	*value_ = *tvalue_;
	delete tvalue_;
}


void Expression::exchangeFunctionSpaceWithFunctionSpace2( void )
{
	pAbstractValueElement tvalue_;

	if( !functionSpace2_ )
		functionSpace2_ = AbstractValueElement::createObject( valueExpressionType_ );

	tvalue_ = AbstractValueElement::createObject( valueExpressionType_ );

	*tvalue_ = *functionSpace2_;
	*functionSpace2_ = *functionSpace_;
	*functionSpace_ = *tvalue_;
	delete tvalue_;
}


void Expression::releaseFunctionSpaces( void )
{
	if( functionSpace_ )
	{
		delete functionSpace_;
		functionSpace_ = ((pAbstractValueElement)0);
	}

	if( functionSpace2_ )
	{
		delete functionSpace2_;
		functionSpace2_ = ((pAbstractValueElement)0);
	}

	count_ = 0;
}


void Expression::evaluatePost( void )
{
	pInstruction ins;

	for( ins = instructions_.first(); ins; ins = instructions_.next() )
		ins->executePost( *this );
}


void Expression::copyFunctionSpaceToValue( void )
{
	*value_ = *functionSpace_;
}


US Expression::dictionaryLength( void )
{
	//
	//  scalar value_s:
	//    UNI rootPredicateNumber
	//    NI valueExpressionType_
	//

	UNI size = sizeof( UNI ) + sizeof( NI );

	size += columns_.dictionaryLength();
	size += instructions_.dictionaryLength();
	size += linkPredicates_.dictionaryLength();
	size += predicates_.dictionaryLength();
	size += resolvedPredicates_.dictionaryLength();

	return static_cast< US >( size );
}


void Expression::viewReset( void )
{
	ValueExpressionStackElement *_ves;

	for( _ves = ves_.first(); _ves; _ves = ves_.next() )
		_ves->resetValue();

	if( value_ )
	{
		delete value_;
		value_ = 0;
	}
	if( value2_ )
	{
		delete value2_;
		value2_ = 0;
	}
	if( functionSpace_ )
	{
		delete functionSpace_;
		functionSpace_ = 0;
	}
	if( functionSpace2_ )
	{
		delete functionSpace2_;
		functionSpace2_ = 0;
	}
	if( last_ )
	{
		delete last_;
		last_ = 0;
	}
	if( columnValue_ )
	{
		delete columnValue_;
		columnValue_ = 0;
	}

	count_ = 0;
}


void Expression::reset( void )
{
	pExpressionColumnListElement expColListEl;
	pValueExpressionStackElement _ves;
	NI root_IsTerminal;

	instructions_.destroy();

	for( _ves = ves_.first(); _ves; _ves = ves_.next() )
		_ves->resetValue();
	ves_.destroy();

	function_ = ((pFunctionInstruction)0);
	valueExpressionType_ = CQL_COLUMN_UNDEFINED_TYPE;
	assignmentType_ = CQL_COLUMN_UNDEFINED_TYPE;
	if( value_ )
	{
		delete value_;
		value_ = ((pAbstractValueElement)0);
	}
	if( value2_ )
	{
		delete value2_;
		value2_ = ((pAbstractValueElement)0);
	}
	if( functionSpace_ )
	{
		delete functionSpace_;
		functionSpace_ = ((pAbstractValueElement)0);
	}
	if( functionSpace2_ )
	{
		delete functionSpace2_;
		functionSpace2_ = ((pAbstractValueElement)0);
	}
	if( last_ )
	{
		delete last_;
		last_ = ((pAbstractValueElement)0);
	}
	if( columnValue_ )
	{
		delete columnValue_;
		columnValue_ = ((pAbstractValueElement)0);
	}

	for( expColListEl = columns_.first(); expColListEl; expColListEl = columns_.next() )
	{
		expColListEl->Name().reset();
		expColListEl->Prefix().reset();
	}

	if( !root_ )
		root_IsTerminal = true;
	else if( root_->type() == TERMINAL )
		root_IsTerminal = true;
	else
		root_IsTerminal = false;

	if( root_IsTerminal == false )
		root_->destroyTreeObjects();
	else if( root_ )
	{
		if( root_->left() )
			delete root_->left();
		if( root_->right() )
			delete root_->right();
		if( root_->third() )
			delete root_->third();
	}

	root_ = ((pPredicate)0);

	columns_.destroy();
	predicates_.destroy();
	viewFlag_ = false;

	count_ = 0;
}

void Expression::classify( bool correlated )
{
	UNI predNumber = 0;
	root_->classify( 0, &predNumber, segmentablePredicates_, correlated, linkPredicates_ );
}


void Expression::computeValueExpressionType( void )
{
	pInstruction ins;

	for( ins = instructions_.first(); ins; ins = instructions_.next() )
		ins->promote( *this );
}


void Expression::forceExpressionType( CqlColumnTypes aType )
{
	valueExpressionType_ = aType;
	doNotChangeType_ = true;
}


bool Expression::makeSegmentedKey( pPredicate pred, pPredicate termPred, bool tryAlternates )
{
	pTerminalPredicateOperand masterPredOp;
	pSegmentedKeyGroup kg, kg2, originalKg;
	pIdentifierInstruction idIns;
	pAbstractColumnDescriptor colDesc;
	pColumnSpecification col, col2;
	pTableSpecification tableSpec;
	pPredicate segmentPredicate, previousSegment;
	US cno;
	UNI numberOfSegments;
	bool result;

	if( pred->res() == NORESOLVE )
		return false;

	if( pred->left()->identifierPush() )
		masterPredOp = ((pTerminalPredicateOperand)pred->left());
	else if( pred->right()->identifierPush() )
		masterPredOp = ((pTerminalPredicateOperand)pred->right());
	else
		return false;

	idIns = ((pIdentifierInstruction)masterPredOp->ins());
	if( !idIns )
		throw InternalErrorException( __FILE__, __LINE__ );

	col = idIns->col();
	if( !col )
		throw InternalErrorException( __FILE__, __LINE__ );
	cno = col->Cno();
	tableSpec = col->TtEl()->tableSpec();
	if( !tableSpec )
		return false;

	kg = masterPredOp->kg();
	if( !kg )
		throw InternalErrorException( __FILE__, __LINE__ );

	numberOfSegments = kg->SegmentedKeyColumns().size();
					
	if( numberOfSegments < 2 && tryAlternates == true )
	{
		//
		//  are there other candidate keys?
		//
		for( kg2 = tableSpec->uniqueKeyGroups().first(); kg2; kg2 = tableSpec->uniqueKeyGroups().next() )
		{
			if( kg == kg2 )
				continue;

			if( kg2->SegmentedKeyColumns().size() > 1 )
			{
				colDesc = kg2->SegmentedKeyColumns().first();
				if( colDesc->columnNumber() == cno )
				{
					originalKg = kg;
					masterPredOp->kg( kg2 );
					result = makeSegmentedKey( pred, termPred, false );
					if( result )
						return true;

					masterPredOp->kg( originalKg );
				}
			}
		}

		//
		//  try the duplicate keys
		//
		for( kg2 = tableSpec->duplicateKeyGroups().first(); kg2; kg2 = tableSpec->duplicateKeyGroups().next() )
		{
			if( kg == kg2 )
				continue;

			if( kg2->SegmentedKeyColumns().size() > 1 )
			{
				colDesc = kg2->SegmentedKeyColumns().first();
				if( colDesc->columnNumber() == cno )
				{
					originalKg = kg;
					masterPredOp->kg( kg2 );
					result = makeSegmentedKey( pred, termPred, false );
					if( result )
						return true;

					masterPredOp->kg( originalKg );
				}
			}
		}

		//
		//  all keys checked
		//

		return false;
	}

	colDesc = ( kg->SegmentedKeyColumns().first() )->next();
	kg->SegmentedKeyColumns().next();

	col2 = dynamic_cast< ColumnSpecification* >( tableSpec->columns()[ colDesc->columnNumber() ] );

	result = findPredicateForSegment( pred, termPred, col2, &segmentPredicate );
	if( !result )
		return false;

	pred->nextSegment( segmentPredicate );
	pred->setPartOfSegmentedKey();
	termPred->nextSegment( segmentPredicate );
	termPred->setPartOfSegmentedKey();
	segmentPredicate->setPartOfSegmentedKey();

	if( numberOfSegments == 2 )
		return true;

	//
	//  still here, so three or more segments
	//
	while (	( colDesc = kg->SegmentedKeyColumns().next() ) != 0 )
	{
		previousSegment = segmentPredicate;

		col2 = dynamic_cast< ColumnSpecification* >( tableSpec->columns()[ colDesc->columnNumber() ] );

		result = findPredicateForSegment( pred, termPred, col2, &segmentPredicate );
		if( !result )
			break;

		segmentPredicate->res( SEGMENTED );
		segmentPredicate->setPartOfSegmentedKey();
		previousSegment->nextSegment( segmentPredicate );
	}

	return true;
}


bool Expression::searchForSegments( pPredicate pred )
{
	pPredicate termPred;

	if( pred->partOfSegmentedKey() )
		return false;

	pred->setTreeMarkers();

	while( ( termPred = getTerminal() ) != 0 )
	{
		bool result = makeSegmentedKey( pred, termPred, true );
		if( result )
			return true;
	}

	return false;
}

		
bool Expression::findSegmentedKey( void )
{
	pPredicate pred;

	for( pred = segmentablePredicates_.last(); pred; pred = segmentablePredicates_.prev() )
		if( !searchForSegments( pred ) )
			return false;

	return true;
}


void Expression::adjustPredicateTree( void )
{
	root_->adjustPredicateTree();
}


bool Expression::evaluate( void )
{
	pInstruction ins;

	if( value_ )
	{
		delete value_;
		value_ = 0;
	}

	workingType_ = CQL_COLUMN_UNDEFINED_TYPE;
	doNotChangeWorkingType_ = false;
	vesState_ = CQL_EXPS_EMPTY;

	for( ins = instructions_.first(); ins; ins = instructions_.next() )
		ins->execute( *this );

	value_ = ves_.popValue();
	if( !value_->value() )
		return false;
	else
		return true;
}
