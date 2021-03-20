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


AllInstruction::AllInstruction( SqlHandle& _dbsql, ComparisonOperators cop ) : SetComparisonInstruction( _dbsql, cop )
{
}


AllInstruction::AllInstruction( SqlHandle& _dbsql ) : SetComparisonInstruction( _dbsql )
{
}


AllInstruction::~AllInstruction( void )
{
}


void AllInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2, oldVal1;
	pSubqueryElement subqEl;
	pSelectExpression subquerySelect;
	CqlColumnTypes literalType, subqueryType;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	subqEl = ((pSubqueryElement)val2);
	subquerySelect = subqEl->selectExpression();

	bool nflag;
	subquerySelect->temporaryFile().ifile()->getColumnInfo( 0, subqueryType, nflag );

	literalType = val1->dataType();
	if( literalType.typeType() != subqueryType.typeType() )
	{
		oldVal1 = val1;
		val1 = AbstractValueElement::convert( oldVal1, subqueryType );
	}

	switch( ComparisonOp() )
	{
	case SETCOMP_EQUAL :
		exp.allEqual( val1, subqEl );
		break;

	case SETCOMP_NOT_EQUAL :
		exp.allNotEqual( val1, subqEl );
		break;

	case SETCOMP_LESS :
		exp.allLess( val1, subqEl );
		break;

	case SETCOMP_LESS_OR_EQUAL :
		exp.allLessOrEqual( val1, subqEl );
		break;

	case SETCOMP_GREATER :
		exp.allGreater( val1, subqEl );
		break;

	case SETCOMP_GREATER_OR_EQUAL :
		exp.allGreaterOrEqual( val1, subqEl );
		break;

	default :
		delete val2;
		delete val1;
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	delete val2;
	delete val1;
}


void AllInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CqlColumnTypes( CQL_INTEGER ) );
}


void AndInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	if( ! (*val1) )
		exp.pushNo();
	else
	{
		if( !( *val2 ) )
			exp.pushNo();
		else
			exp.pushYes();
	}

	exp.vesStateBoolean();
	delete val1;
	delete val2;
}


void AndInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


AndInstruction::AndInstruction( SqlHandle& _dbsql ) : BinaryOperatorInstruction( _dbsql )
{
}


AndInstruction::~AndInstruction( void )
{
}


AnyInstruction::AnyInstruction( SqlHandle& _dbsql, ComparisonOperators cop ) : SetComparisonInstruction( _dbsql, cop )
{
}


AnyInstruction::AnyInstruction( SqlHandle& _dbsql ) : SetComparisonInstruction( _dbsql )
{
}


AnyInstruction::~AnyInstruction( void )
{
}


void AnyInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2, oldVal1;
	pSubqueryElement subqEl;
	pSelectExpression subquerySelect;
	CqlColumnTypes literalType, subqueryType;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	subqEl = ((pSubqueryElement)val2);
	subquerySelect = subqEl->selectExpression();

	bool nflag;
	subquerySelect->temporaryFile().ifile()->getColumnInfo( 0, subqueryType, nflag );

	literalType = val1->dataType();
	if( literalType.typeType() != subqueryType.typeType() )
	{
		oldVal1 = val1;
		val1 = AbstractValueElement::convert( oldVal1, subqueryType );
	}

	switch( ComparisonOp() )
	{
	case SETCOMP_EQUAL :
		exp.anyEqual( val1, subqEl );
		break;

	case SETCOMP_NOT_EQUAL :
		exp.anyNotEqual( val1, subqEl );
		break;

	case SETCOMP_GREATER :
		exp.anyGreater( val1, subqEl );
		break;

	case SETCOMP_GREATER_OR_EQUAL :
		exp.anyGreaterOrEqual( val1, subqEl );
		break;

	case SETCOMP_LESS :
		exp.anyLess( val1, subqEl );
		break;

	case SETCOMP_LESS_OR_EQUAL :
		exp.anyLessOrEqual( val1, subqEl );
		break;

	default :
		delete val2;
		delete val1;
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	delete val2;
	delete val1;
}


void AnyInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


BetweenInstruction::BetweenInstruction( SqlHandle& _dbsql ) : TertiaryOperatorInstruction( _dbsql )
{
}


BetweenInstruction::~BetweenInstruction( void )
{
}


void BetweenInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1 = 0, val2 = 0, val3 = 0, tval;

	val3 = exp.ves().popValue();
	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	bool switched;
	makeTypesCompatible( switched, &val1, &val2 );
	if( switched )
	{
		tval = val1;
		val1 = val2;
		val2 = tval;
	}

	if( *val1 < *val2 )
	{
		exp.pushNo();
		delete val1;
		delete val2;
		delete val3;
		exp.vesStateBoolean();
		return;
	}

	makeTypesCompatible( switched, &val1, &val3 );
	if( switched )
	{
		tval = val1;
		val1 = val2;
		val2 = tval;
	}

	if( *val1 > *val3 )
	{
		exp.pushNo();
		delete val1;
		delete val2;
		delete val3;
		exp.vesStateBoolean();
		return;
	}

	exp.pushYes();

	exp.vesStateBoolean();
	delete val1;
	delete val2;
	delete val3;
}


void BetweenInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


US BetweenInstruction::dictionaryLength( void )
{
	return 0;
}


BinaryOperatorInstruction::BinaryOperatorInstruction( SqlHandle& _dbsql ) : Instruction( _dbsql )
{
}


BinaryOperatorInstruction::~BinaryOperatorInstruction( void )
{
}


void BinaryOperatorInstruction::buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack )
{
	pPredicate pred;
	pNonterminalPredicateOperand ntpop;

	pred = new Predicate( dbsql() );
	if( !pred )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	pred->ins( this );

	//
	//  pop the operands off the stack
	//
	pred->left( stack.pop() );
	if( pred->left() == 0 )
	{
		delete pred;
		throw InternalErrorException( __FILE__, __LINE__ );
	}
	else
		pred->setLeftExists();

	pred->right( stack.pop() );
	if( pred->right() == 0 )
	{
		delete pred;
		throw InternalErrorException( __FILE__, __LINE__ );
	}
	else
		pred->setRightExists();

	ntpop = new NonterminalPredicateOperand( dbsql() );
	if( !ntpop )
	{
		delete pred;
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	ntpop->descendent( pred );
	stack.push( ntpop );
	predList.add( pred );
}


void BinaryOperatorInstruction::processViewData( SelectExpressionList& )
{
}


Instruction& BinaryOperatorInstruction::operator = ( const Instruction& ins )
{
	AbstractAssign( ins );
	return *this;
}


US BinaryOperatorInstruction::dictionaryLength( void )
{
	return 0;
}


void BinaryOperatorInstruction::readDictionaryInformation( TempBuffer& )
{
}


void BinaryOperatorInstruction::writeDictionaryInformation( TempBuffer& )
{
}


ComparisonInstruction::ComparisonInstruction( SqlHandle& _dbsql ) : BinaryOperatorInstruction( _dbsql )
{
}


ComparisonInstruction::~ComparisonInstruction( void )
{
}


void ComparisonInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2, newVal, tval;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	if( val2->valueType() == SUBQUERY_ELEMENT )
	{
		pSubqueryElement subqEl = ((pSubqueryElement)val2 );
		newVal = subqEl->getAndPushSingleSubqueryValue();
		delete val2;
		val2 = newVal;
	}

	bool switched;
	makeTypesCompatible( switched, &val1, &val2 );
	if( switched )
	{
		tval = val1;
		val1 = val2;
		val2 = tval;
	}

	bool result;

	switch( BinaryOp() )
	{
	case OPERATOR_EQUALS :
		result = *val1 == *val2;
		break;

	case OPERATOR_NOTEQUAL :
		result = *val1 == *val2;
		if( result == true )
			result = false;
		else
			result = true;
		break;

	case OPERATOR_LESS_OR_EQUAL :
		result = *val1 <= *val2;
		break;

	case OPERATOR_GREATER_OR_EQUAL :
		result = *val1 >= *val2;
		break;

	case OPERATOR_LESS :
		result = *val1 < *val2;
		break;

	case OPERATOR_GREATER :
		result = *val1 > *val2;
		break;

	default :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	delete val1;
	delete val2;

	if( result )
		exp.pushYes();
	else
		exp.pushNo();

	exp.vesStateBoolean();
}


void ComparisonInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


void DivideInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2, tval;

	val2 = exp.ves().popValue();

	val1 = exp.ves().popValue();

	bool switched;
	makeTypesCompatible( switched, &val1, &val2 );
	if( switched )
	{
		tval = val1;
		val1 = val2;
		val2 = tval;
	}

	*val1 /= *val2;
	delete val2;

	exp.ves().pushValue( val1 );
}


DivideInstruction::DivideInstruction( SqlHandle& _dbsql ) : BinaryOperatorInstruction( _dbsql )
{
}


DivideInstruction::~DivideInstruction( void )
{
}


EqualsInstruction::EqualsInstruction( SqlHandle& _dbsql ) : ComparisonInstruction( _dbsql )
{
}


EqualsInstruction::~EqualsInstruction(void)
{
}


ExistsInstruction::ExistsInstruction( SqlHandle& _dbsql ) : UnaryOperatorInstruction( _dbsql )
{
}


ExistsInstruction::~ExistsInstruction( void )
{
}


//
//  the subquery associated with EXISTS sets the flag existsValueFlag
//  in its SelectExpression
//
void ExistsInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pSubqueryElement subqEl;

	val = exp.ves().popValue();

	if( val->valueType() != SUBQUERY_ELEMENT )
	{
		delete val;
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	subqEl = ((pSubqueryElement)val);
	if( subqEl->selectExpression()->existsValueFlag() )
		exp.pushYes();
	else
		exp.pushNo();

	exp.vesStateBoolean();
	delete val;
}


void ExistsInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


GreaterInstruction::GreaterInstruction( SqlHandle& _dbsql ) : ComparisonInstruction( _dbsql )
{
}


GreaterInstruction::~GreaterInstruction(void)
{
}


GreaterOrEqualInstruction::GreaterOrEqualInstruction( SqlHandle& _dbsql ) : ComparisonInstruction( _dbsql )
{
}


GreaterOrEqualInstruction::~GreaterOrEqualInstruction(void)
{
}


void IdentifierInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1;

	if( col_->IsViewColumn() )
	{
		val1 = AbstractValueElement::createObject( col_->ViewColumn()->ColumnExpression().valueExpressionType() );
		*val1 = *col_->ViewColumn()->ColumnExpression().value();
	}
	else
		val1 = col_->createValue();

	exp.ves().pushValue( val1 );
	exp.vesStateValue();
}


void IdentifierInstruction::promote( Expression& exp, bool useWorkingType )
{
	exp.promote( col_->type(), useWorkingType );
}


void IdentifierInstruction::buildPredicateTreeElement( PredicateList&, AbstractPredicateOperandList &stack )
{
	pTerminalPredicateOperand tpop;

	tpop = new TerminalPredicateOperand( dbsql() );
	if( !tpop )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	tpop->ins( this );
	tpop->setIdentifierPush();
	tpop->col( col_ );
	tpop->ttEl( col_->TtEl() );
	if( col_->IsViewColumn() == CQL_NO )
		tpop->columnFile( col_->TtEl()->tableSpec()->file() );
	stack.push( tpop );
}


void IdentifierInstruction::processViewData( SelectExpressionList& sel )
{
	pSelectExpression select;
	pTableTableElement ttEl;

	select = sel[ static_cast< US >( setNumber_ ) ];
	ttEl = select->tables()[ static_cast< US >( tableNumber_ ) ];
	col_ = dynamic_cast< ColumnSpecification* >( ttEl->absTableSpec()->columns()[ static_cast< US >( columnNumber_ ) ] );
	col_->SetTtEl( ttEl );
}


void IdentifierInstruction::reprocessViewData( SelectExpressionList& sel )
{
	pSelectExpression select;
	pTableTableElement ttEl;

	select = sel[ static_cast< US >( setNumber_ ) ];
	ttEl = select->tables()[ static_cast< US >( tableNumber_ ) ];
	col_ = dynamic_cast< ColumnSpecification* >( ttEl->absTableSpec()->columns()[ static_cast< US >( columnNumber_ ) ] );
	col_->SetTtEl( ttEl );
}


IdentifierInstruction::IdentifierInstruction( SqlHandle& _dbsql )
	: Instruction( _dbsql ),
	  col_( 0 ),
	  columnNumber_( 0 ),
	  correlated_( false ),
	  setNumber_( 0 ),
	  tableNumber_( 0 )
{
}


IdentifierInstruction::~IdentifierInstruction( void )
{
}


Instruction& IdentifierInstruction::operator = ( const Instruction& cins )
{
	Instruction& ins = const_cast< Instruction& >( cins );
	IdentifierInstruction& other = dynamic_cast< IdentifierInstruction& >( ins );

	if( other.col_ )
		col_ = new ColumnSpecification( *other.col_ );
	else
		col_ = 0;

	columnNumber_ = other.columnNumber_;
	setNumber_ = other.setNumber_;
	tableNumber_ = other.tableNumber_;
	correlated_ = other.correlated_;
	return *this;
}


void IdentifierInstruction::writeDictionaryInformation( TempBuffer& buffer )
{
	if( col_ )
		buffer << col_->Cno() << col_->TtEl()->tableNumber() << col_->TtEl()->setNumber();
	else
		buffer << columnNumber_ << tableNumber_ << setNumber_;
}


void IdentifierInstruction::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> columnNumber_ >> tableNumber_ >> setNumber_;
}


NI IdentifierInstruction::IdentifierInstructionAssign( SqlHandle *_dbsql, IdentifierInstruction& other )
{
	if( other.col_ )
	{
		col_ = new ColumnSpecification( *other.col_ );
		if( !col_ )
			return _dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );
	}
	else
		col_ = 0;

	columnNumber_ = other.columnNumber_;
	setNumber_ = other.setNumber_;
	tableNumber_ = other.tableNumber_;
	correlated_ = other.correlated_;
	return CQL_SUCCESS;
}


US IdentifierInstruction::dictionaryLength( void )
{
	return 3 * sizeof( UNI );
}


Instruction::Instruction( SqlHandle& sqlh ) : allocationFlag( false ), dbsql_( sqlh ), setIdentifier_( 0 ), temporaryBuffer_( 0 )
{
}


Instruction& Instruction::operator = ( const Instruction& other )
{
	allocationFlag = other.allocationFlag;
	dbsql_ = other.dbsql_;
	setIdentifier_ = other.setIdentifier_;
	return *this;
}


void Instruction::selectConversion( pAbstractValueElement *val1, pAbstractValueElement *val2 )
{
	pAbstractValueElement tval;

	//************************************************************************
	//**  If the types are assignment compatible, and the val1 type should  **
	//**  be promoted to the val2 type, exchange val1 and val2.             **
	//************************************************************************
	switch( (*val1)->dataType().typeType() )
	{
	case CQL_CHARUC :
	case CQL_VARCHAR :
	case CQL_LONGVARCHAR :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
			return;

		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_BIT :
		case CQL_TINYINT :
		case CQL_BIGINT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_CHAR :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_CHAR :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
			return;

		case CQL_CHARUC :
			tval = *val1;
			*val1 = *val2;
			*val2 = tval;
			return;

		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_BIT :
		case CQL_TINYINT :
		case CQL_BIGINT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_DECIMAL :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_TINYINT :
		case CQL_BIGINT :
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_BIT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;
		
	case CQL_SMALLINT :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_SMALLINT :
		case CQL_TINYINT :
			return;

		case CQL_DECIMAL :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_BIGINT :
			tval = *val1;
			*val1 = *val2;
			*val2 = tval;
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_BIT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_INTEGER :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_TINYINT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
			return;

		case CQL_DECIMAL :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_BIGINT :
			tval = *val1;
			*val1 = *val2;
			*val2 = tval;
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_BIT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_REAL :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_TINYINT :
		case CQL_BIGINT :
		case CQL_REAL :
			return;

		case CQL_FLOAT :
			tval = *val1;
			*val1 = *val2;
			*val2 = tval;
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_BIT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_FLOAT :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_TINYINT :
		case CQL_BIGINT :
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_BIT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_BIT :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_BIT :
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_TINYINT :
		case CQL_BIGINT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_TINYINT :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_TINYINT :
			return;

		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
		case CQL_REAL :
		case CQL_FLOAT :
			tval = *val1;
			*val1 = *val2;
			*val2 = tval;
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_BIT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_BIGINT :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_TINYINT :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_BIGINT :
			return;

		case CQL_DECIMAL :
		case CQL_REAL :
		case CQL_FLOAT :
			tval = *val1;
			*val1 = *val2;
			*val2 = tval;
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_BIT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_BIT :
		case CQL_TINYINT :
		case CQL_BIGINT :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_DATE :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_DATE :
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_BIT :
		case CQL_TINYINT :
		case CQL_BIGINT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_TIME :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_TIME :
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_BIT :
		case CQL_TINYINT :
		case CQL_BIGINT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIMESTAMP :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_TIMESTAMP :
		switch( (*val2)->dataType().typeType() )
		{
		case CQL_TIMESTAMP :
			return;

		case CQL_CHAR :
		case CQL_CHARUC :
		case CQL_VARCHAR :
		case CQL_LONGVARCHAR :
		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_BIT :
		case CQL_TINYINT :
		case CQL_BIGINT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_COLUMN_UNDEFINED_TYPE :
			break;
		}
		break;

	case CQL_COLUMN_UNDEFINED_TYPE :
		break;
	}

	throw InternalErrorException( __FILE__, __LINE__ );
}


void Instruction::makeTypesCompatible( bool& switched, pAbstractValueElement *pVal1, pAbstractValueElement *pVal2 )
{
	pAbstractValueElement val1 = *pVal1, val2 = *pVal2, newval;

	switched = false;

	if( val1->expressionCompatible( val2->dataType() ) )
		return;

	//
	//  convert which to what?
	//
	selectConversion( pVal1, pVal2 );

	if( val1 != *pVal1 )
	{
		val1 = *pVal1;
		val2 = *pVal2;
		switched = true;
	}

	newval = AbstractValueElement::convert( val2, val1->dataType() );
	*pVal2 = newval;
}


//
//  This is the version for functions which don't need any
//  post processing.
//
void Instruction::executePost( Expression& )
{
}


AbstractValueElement *Instruction::convertToInteger( AbstractValueElement *ave, AbstractType::RoundType )
{
	pNumericLiteralElement val = ((pNumericLiteralElement)ave);
	pIntegerLiteralElement newVal;
	L l = 0;

	switch( val->dataType().typeType() )
	{
	case CQL_BIGINT :
		l = dynamic_cast< Cql_Bigint& >( val->value() ).instance().value().asLong();
		break;

	case CQL_BINARY :
		throw ConversionException( __FILE__, __LINE__ );

	case CQL_BIT :
		l = dynamic_cast< Cql_Bit& >( val->value() ).instance().value().asLong();
		break;

	case CQL_CHAR :
		throw ConversionException( __FILE__, __LINE__ );

	case CQL_CHARUC :
		throw ConversionException( __FILE__, __LINE__ );

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );

	case CQL_DATE :
		throw ConversionException( __FILE__, __LINE__ );

	case CQL_DECIMAL :
		l = dynamic_cast< Cql_Decimal& >( val->value() ).instance().value().asLong();
		break;

	case CQL_FLOAT :
		l = dynamic_cast< Cql_Float& >( val->value() ).instance().value().asLong();
		break;

	case CQL_INTEGER :
		return val;

	case CQL_LONGVARBINARY :
		throw ConversionException( __FILE__, __LINE__ );

	case CQL_LONGVARCHAR :
		throw ConversionException( __FILE__, __LINE__ );

	case CQL_SMALLINT :
		l = dynamic_cast< Cql_Smallint& >( val->value() ).instance().value().asLong();
		break;

	case CQL_REAL :
		l = dynamic_cast< Cql_Real& >( val->value() ).instance().value().asLong();
		break;

	case CQL_TIME :
		throw ConversionException( __FILE__, __LINE__ );

	case CQL_TIMESTAMP :
		throw ConversionException( __FILE__, __LINE__ );

	case CQL_TINYINT :
		l = dynamic_cast< Cql_Real& >( val->value() ).instance().value().asLong();
		break;

	case CQL_VARBINARY :
		throw ConversionException( __FILE__, __LINE__ );

	case CQL_VARCHAR :
		throw ConversionException( __FILE__, __LINE__ );
	}

	newVal = new IntegerLiteralElement;
	if( !newVal )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	dynamic_cast< Cql_Integer& >( newVal->value() ).instance().value() = l;

	delete val;
	return newVal;
}


AbstractValueElement *Instruction::convertToFloat( AbstractValueElement *ave )
{
	pNumericLiteralElement val = ((pNumericLiteralElement)ave);
	pFloatLiteralElement newVal;
	D d;

	if( val->dataType().typeType() == CQL_FLOAT )
		return val;

	d = dynamic_cast< Cql_Decimal& >( val->value() ).instance().value().asDouble();

	newVal = new FloatLiteralElement;
	if( !newVal )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	FloatValue& fl = dynamic_cast< Cql_Float& >( newVal->value() ).instance().value();
	fl = d;

	delete val;
	return newVal;
}


L Instruction::extractIntegerArgument( AbstractValueElement *val )
{
	pIntegerLiteralElement ile;
	L l;

	AbstractValueElement *newVal = convertToInteger( val );
	ile = ((pIntegerLiteralElement)newVal);
	IntegerValue& integer = dynamic_cast< Cql_Integer& >( ile->value() ).instance().value();
	l = integer.asLong();
	delete val;
	return l;
}


DateValue *Instruction::extractDateArgument( AbstractValueElement *val )
{
	pDateLiteralElement dle;

	if( val->dataType().typeType() != CQL_DATE )
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	dle = ((pDateLiteralElement)val);
	DateValue& d = dynamic_cast< Cql_Date& >( dle->value() ).instance().value();
	delete val;
	return &d;
}


TimeValue *Instruction::extractTimeArgument( AbstractValueElement *val )
{
	pTimeLiteralElement tle;

	if( val->dataType().typeType() != CQL_TIME )
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	tle = ((pTimeLiteralElement)val);
	TimeValue& t = dynamic_cast< Cql_Time& >( tle->value() ).instance().value();
	delete val;
	return &t;
}


D Instruction::extractFloatArgument( AbstractValueElement *val )
{
	pFloatLiteralElement fle;
	D d;

	AbstractValueElement *newVal = convertToFloat( val );
	fle = ((pFloatLiteralElement)newVal);
	FloatValue& f = dynamic_cast< Cql_Float& >( fle->value() ).instance().value();
	d = f.asDouble();
	delete val;
	return d;
}


NI Instruction::AbsoluteValue( pAbstractValueElement val )
{
	pNumericLiteralElement nle;

	nle = ((pNumericLiteralElement)val);
	nle->value().absoluteValue();
	return CQL_SUCCESS;
}


void Instruction::executeFloatFunction( Expression& exp, D func( D ), bool invert )
{
	pAbstractValueElement val;
	pNumericLiteralElement numericEl;
	D d;

	val = exp.ves().popValue();

	if( !val->isFloat() )
	{
		delete val;
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	AbstractValueElement *newVal = convertToFloat( val );
	numericEl = ((pNumericLiteralElement)newVal);
	FloatValue& f = dynamic_cast< Cql_Float& >( numericEl->value() ).instance().value();

	d = func( f.asDouble() );

	if( invert )
		d = 1/d;

	f = d;

	exp.ves().pushValue( newVal );
}


void Instruction::reprocessViewData( SelectExpressionList& )
{
	//  Do nothing base method for instructions which don't need reprocessing
}


Instruction *Instruction::createObject( SqlHandle& dbsql, OperationCodes opCode, BinaryOperators binaryOp, Functions funcId, UnaryOperators unaryOp, TertiaryOperators tertiaryOp )
{
	pInstruction localIns = ((pInstruction)0);

	switch( opCode )
	{
	case UNARY_OPERATOR :
		switch( unaryOp )
		{
		case LOGICAL_NOT :
			localIns = new LogicalNotInstruction( dbsql );
			break;

		case UNARY_MINUS :
			localIns = new UnaryMinusInstruction( dbsql );
			break;

		case NULLTEST :
			localIns = new NullTestInstruction( dbsql );
			break;

		case CQL_EXISTS :
			localIns = new ExistsInstruction( dbsql );
			break;

		default :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
		break;

	case BINARY_OPERATOR :
		switch( binaryOp )
		{
		case OUTER_EQUAL :
			localIns = new OuterJoinInstruction( dbsql );
			break;

		case OPERATOR_LIKE :
			localIns = new LikeInstruction( dbsql );
			break;

		case OPERATOR_AND :
			localIns = new AndInstruction( dbsql );
			break;

		case OPERATOR_OR :
			localIns = new OrInstruction( dbsql );
			break;

		case OPERATOR_TIMES :
			localIns = new TimesInstruction( dbsql );
			break;

		case OPERATOR_DIVIDE :
			localIns = new DivideInstruction( dbsql );
			break;

		case OPERATOR_PLUS :
			localIns = new PlusInstruction( dbsql );
			break;

		case OPERATOR_MINUS :
			localIns = new OperatorMinusInstruction( dbsql );
			break;

		case OPERATOR_EQUALS :
			localIns = new EqualsInstruction( dbsql );
			break;

		case OPERATOR_NOTEQUAL :
			localIns = new NotEqualInstruction( dbsql );
			break;

		case OPERATOR_LESS_OR_EQUAL :
			localIns = new LessOrEqualInstruction( dbsql );
			break;

		case OPERATOR_GREATER_OR_EQUAL :
			localIns = new GreaterOrEqualInstruction( dbsql );
			break;

		case OPERATOR_LESS :
			localIns = new LessInstruction( dbsql );
			break;

		case OPERATOR_GREATER :
			localIns = new GreaterInstruction( dbsql );
			break;

		default :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
		break;

	case TERTIARY_OPERATOR :
		switch( tertiaryOp )
		{
		case CQL_BETWEEN :
			localIns = new BetweenInstruction( dbsql );
			break;

		default :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
		break;

	case EVALUATE_FUNCTION :
		switch( funcId )
		{
		case FUNC_COUNT1 :
			localIns = new CountStarFunctionInstruction( dbsql );
			break;

		case FUNC_COUNT2 :
			localIns = new CountColumnFunctionInstruction( dbsql );
			break;

		case FUNC_SUM :
			localIns = new SumFunctionInstruction( dbsql );
			break;

		case FUNC_AVG :
			localIns = new AvgFunctionInstruction( dbsql );
			break;

		case FUNC_MIN :
			localIns = new MinFunctionInstruction( dbsql );
			break;

		case FUNC_MAXIMUM :
			localIns = new MaxFunctionInstruction( dbsql );
			break;

		case FUNC_ASCII :
			localIns = new AsciiFunctionInstruction( dbsql );
			break;

		case FUNC_CHAR :
			localIns = new CharFunctionInstruction( dbsql );
			break;

		case FUNC_CONCAT :
			localIns = new ConcatFunctionInstruction( dbsql );
			break;

		case FUNC_INSERT :
			localIns = new InsertFunctionInstruction( dbsql );
			break;

		case FUNC_LEFT :
			localIns = new LeftFunctionInstruction( dbsql );
			break;

		case FUNC_LTRIM :
			localIns = new LtrimFunctionInstruction( dbsql );
			break;

		case FUNC_LENGTH :
			localIns = new LengthFunctionInstruction( dbsql );
			break;

		case FUNC_LOCATE :
			localIns = new LocateFunctionInstruction( dbsql );
			break;

		case FUNC_LCASE :
			localIns = new LcaseFunctionInstruction( dbsql );
			break;

		case FUNC_REPEAT :
			localIns = new RepeatFunctionInstruction( dbsql );
			break;

		case FUNC_REPLACE :
			localIns = new ReplaceFunctionInstruction( dbsql );
			break;

		case FUNC_RIGHT :
			localIns = new RightFunctionInstruction( dbsql );
			break;

		case FUNC_RTRIM :
			localIns = new RtrimFunctionInstruction( dbsql );
			break;

		case FUNC_SUBSTRING :
			localIns = new SubstringFunctionInstruction( dbsql );
			break;

		case FUNC_UCASE :
			localIns = new UcaseFunctionInstruction( dbsql );
			break;

		case FUNC_ABS :
			localIns = new AbsFunctionInstruction( dbsql );
			break;

		case FUNC_ACOS :
			localIns = new AcosFunctionInstruction( dbsql );
			break;

		case FUNC_ASIN :
			localIns = new AsinFunctionInstruction( dbsql );
			break;

		case FUNC_ATAN :
			localIns = new AtanFunctionInstruction( dbsql );
			break;

		case FUNC_ATAN2 :
			localIns = new Atan2FunctionInstruction( dbsql );
			break;

		case FUNC_CEILING :
			localIns = new CeilingFunctionInstruction( dbsql );
			break;

		case FUNC_COS :
			localIns = new CosFunctionInstruction( dbsql );
			break;

		case FUNC_COT :
			localIns = new CotFunctionInstruction( dbsql );
			break;

		case FUNC_EXP :
			localIns = new ExpFunctionInstruction( dbsql );
			break;

		case FUNC_FLOOR :
			localIns = new FloorFunctionInstruction( dbsql );
			break;

		case FUNC_LOG :
			localIns = new LogFunctionInstruction( dbsql );
			break;

		case FUNC_MOD :
			localIns = new ModFunctionInstruction( dbsql );
			break;

		case FUNC_PI :
			localIns = new PiFunctionInstruction( dbsql );
			break;

		case FUNC_RAND :
			localIns = new RandFunctionInstruction( dbsql );
			break;

		case FUNC_SIGN :
			localIns = new SignFunctionInstruction( dbsql );
			break;

		case FUNC_SIN :
			localIns = new SinFunctionInstruction( dbsql );
			break;

		case FUNC_SQRT :
			localIns = new SqrtFunctionInstruction( dbsql );
			break;

		case FUNC_TAN :
			localIns = new TanFunctionInstruction( dbsql );
			break;

		case FUNC_NOW :
			localIns = new NowFunctionInstruction( dbsql );
			break;

		case FUNC_CURDATE :
			localIns = new CurdateFunctionInstruction( dbsql );
			break;

		case FUNC_DAYOFMONTH :
			localIns = new DayOfMonthFunctionInstruction( dbsql );
			break;

		case FUNC_DAYOFWEEK :
			localIns = new DayOfWeekFunctionInstruction( dbsql );
			break;

		case FUNC_DAYOFYEAR :
			localIns = new DayOfYearFunctionInstruction( dbsql );
			break;

		case FUNC_MONTH :
			localIns = new MonthFunctionInstruction( dbsql );
			break;

		case FUNC_QUARTER :
			localIns = new QuarterFunctionInstruction( dbsql );
			break;

		case FUNC_WEEK :
			localIns = new WeekFunctionInstruction( dbsql );
			break;

		case FUNC_YEAR :
			localIns = new YearFunctionInstruction( dbsql );
			break;

		case FUNC_CURTIME :
			localIns = new CurtimeFunctionInstruction( dbsql );
			break;

		case FUNC_HOUR :
			localIns = new HourFunctionInstruction( dbsql );
			break;

		case FUNC_MINUTE :
			localIns = new MinuteFunctionInstruction( dbsql );
			break;

		case FUNC_SECOND :
			localIns = new SecondFunctionInstruction( dbsql );
			break;

		case FUNC_USER :
			localIns = new UserFunctionInstruction( dbsql );
			break;

		case FUNC_DATABASE :
			localIns = new DatabaseFunctionInstruction( dbsql );
			break;

		case FUNC_IFNULL :
			localIns = new IfnullFunctionInstruction( dbsql );
			break;

		case FUNC_CONVERT :
			localIns = new ConvertFunctionInstruction( dbsql );
			break;

		case NOT_A_FUNCTION :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
		break;

	case IDENTIFIER_PUSH :
		localIns = new IdentifierInstruction( dbsql );
		break;

	case VALUE_PUSH :
		localIns = new ValueInstruction( dbsql );
		break;

	case CQL_ALL :
		localIns = new AllInstruction( dbsql );
		break;

	case CQL_ANY :
		localIns = new AnyInstruction( dbsql );
		break;

	case SUBQUERY_PUSH :
		localIns = new SubqueryInstruction( dbsql );
		break;

	default :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	if( !localIns )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	return localIns;
}


pColumnSpecification Instruction::col( void )
{
	return ((pColumnSpecification)0);
}


InstructionConstants::BinaryOperators Instruction::BinaryOp( void )
{
	return NOT_A_BINARY_OPERATOR;
}


InstructionConstants::UnaryOperators Instruction::UnaryOp( void )
{
	return NOT_A_UNARY_OPERATOR;
}


InstructionConstants::TertiaryOperators Instruction::TertiaryOp( void )
{
	return NOT_A_TERTIARY_OPERATOR;
}


FunctionConstants::Functions Instruction::FuncId( void )
{
	return NOT_A_FUNCTION;
}


Instruction::~Instruction( void )
{
	if( temporaryBuffer_ )
	{
		delete temporaryBuffer_;
		temporaryBuffer_ = 0;
	}
}


void Instruction::AbstractAssign( const Instruction& other )
{
	setIdentifier_ = other.setIdentifier_;
}


void InstructionList::processViewData( SelectExpressionList& sel )
{
	pInstruction ins;

	for( ins = first(); ins; ins = next() )
		ins->processViewData( sel );
}


void InstructionList::reprocessViewData( SelectExpressionList& sel )
{
	pInstruction ins;

	for( ins = first(); ins; ins = next() )
		ins->reprocessViewData( sel );
}


InstructionList::InstructionList( void ) : InstructionListBase()
{
}


void InstructionList::writeDictionaryInformation( TempBuffer& buffer )
{
	pInstruction ins;
	OperationCodes opCode;
	pBinaryOperatorInstruction binaryOpIns;
	pUnaryOperatorInstruction unaryOpIns;
	pTertiaryOperatorInstruction tertiaryOpIns;
	pFunctionInstruction functionIns;

	buffer << size();

	for( ins = first(); ins; ins = next() )
	{
		opCode = ins->OpCode();

		buffer << opCode;

		switch( opCode )
		{
		case BINARY_OPERATOR :
			binaryOpIns = ((pBinaryOperatorInstruction)ins);
			buffer << binaryOpIns->BinaryOp();
			break;

		case UNARY_OPERATOR :
			unaryOpIns = ((pUnaryOperatorInstruction)ins);
			buffer << unaryOpIns->UnaryOp();
			break;

		case TERTIARY_OPERATOR :
			tertiaryOpIns = ((pTertiaryOperatorInstruction)ins);
			buffer << tertiaryOpIns->TertiaryOp();
			break;

		case EVALUATE_FUNCTION :
			functionIns = ((pFunctionInstruction)ins);
			buffer << functionIns->FuncId();
			break;

		default :
			;//  do nothing
		}

		ins->writeDictionaryInformation( buffer );
	}
}


void InstructionList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfInstructions, loop;
	pInstruction ins;
	OperationCodes opCode = UNSET;
	BinaryOperators binaryOp = NOT_A_BINARY_OPERATOR;
	UnaryOperators unaryOp = NOT_A_UNARY_OPERATOR;
	TertiaryOperators tertiaryOp = NOT_A_TERTIARY_OPERATOR;
	Functions func = NOT_A_FUNCTION;

	buffer >> numberOfInstructions;

	for( loop = 0; loop < numberOfInstructions; loop++ )
	{
		buffer >> opCode;

		switch( opCode )
		{
		case BINARY_OPERATOR :
			buffer >> binaryOp;
			break;

		case UNARY_OPERATOR :
			buffer >> unaryOp;
			break;

		case TERTIARY_OPERATOR :
			buffer >> tertiaryOp;
			break;

		case EVALUATE_FUNCTION :
			buffer >> func;
			break;

		default :
			;//  do nothing
		}

		ins = Instruction::createObject( *buffer.dbsql(), opCode, binaryOp, func, unaryOp, tertiaryOp );
		ins->readDictionaryInformation( buffer );
		add( ins );
	}
}


US InstructionList::dictionaryLength( void )
{
	US _size;
	pInstruction ins;

	_size = sizeof( UNI );

	for( ins = first(); ins; ins = next() )
	{
		_size += ((US)( 2 * sizeof( NI ) ) );
		_size = ((US)( _size + ins->dictionaryLength() ) );
	}

	return _size;
}


InstructionList& InstructionList::operator = ( const InstructionList& cother )
{
	InstructionList& other = const_cast< InstructionList& >( cother );

	pInstruction ins, newIns;
	for( ins = other.first(); ins; ins = other.next() )
	{
		newIns = Instruction::createObject( ins->dbsql(), ins->OpCode(), ins->BinaryOp(), ins->FuncId(), ins->UnaryOp(), ins->TertiaryOp() );
		*newIns = *ins;
		add( newIns );
	}

	return *this;
}


LessInstruction::LessInstruction( SqlHandle& _dbsql ) : ComparisonInstruction( _dbsql )
{
}


LessInstruction::~LessInstruction(void)
{
}


LessOrEqualInstruction::LessOrEqualInstruction( SqlHandle& _dbsql ) : ComparisonInstruction( _dbsql )
{
}


LessOrEqualInstruction::~LessOrEqualInstruction(void)
{
}


LikeInstruction::LikeInstruction( SqlHandle& _dbsql ) : BinaryOperatorInstruction( _dbsql )
{
}


LikeInstruction::~LikeInstruction( void )
{
}


void LikeInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2;
	pStringElement stringEl1, stringEl2;
	CompareResult result;
	NC escapeCharacter;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	stringEl1 = ((pStringElement)val1);
	stringEl2 = ((pStringElement)val2);

	if( exp.dbsql().parse()->escape() )
	{
		escapeCharacter = exp.dbsql().parse()->escapeCharacter();
		result = stringEl1->str().regularExpressionCompare( stringEl2->str(), escapeCharacter );
	}
	else
		result = stringEl1->str().regularExpressionCompare( stringEl2->str(), 0 );

	delete val1;
	delete val2;

	if( result == THIS_EQUAL_TO_OTHER )
		exp.pushYes();
	else
		exp.pushNo();

	exp.vesStateBoolean();
}


void LikeInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


LogicalNotInstruction::LogicalNotInstruction( SqlHandle& _dbsql ) : UnaryOperatorInstruction( _dbsql )
{
}


LogicalNotInstruction::~LogicalNotInstruction( void )
{
}


void LogicalNotInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	L l;

	if( exp.vesStateIsEmpty() || exp.vesStateIsValue() )
	{
		exp.flipFlipFlag();
		return;
	}

	val = exp.ves().popValue();
	l = extractIntegerArgument( val );
	if( l )
		exp.pushNo();
	else
		exp.pushYes();

	exp.vesStateBoolean();
}


void LogicalNotInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


NotEqualInstruction::NotEqualInstruction( SqlHandle& _dbsql ) : ComparisonInstruction( _dbsql )
{
}


NotEqualInstruction::~NotEqualInstruction(void)
{
}


NullTestInstruction::NullTestInstruction( SqlHandle& _dbsql ) : UnaryOperatorInstruction( _dbsql )
{
}


NullTestInstruction::~NullTestInstruction( void )
{
}


void NullTestInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;

	val = exp.ves().popValue();

	if( val->isNull() )
		exp.pushYes();
	else
		exp.pushNo();

	exp.vesStateBoolean();
	delete val;
}


void NullTestInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


OperatorMinusInstruction::OperatorMinusInstruction( SqlHandle& _dbsql ) : BinaryOperatorInstruction( _dbsql )
{
}


OperatorMinusInstruction::~OperatorMinusInstruction(void)
{
}


void OperatorMinusInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2, tval;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	bool switched;
	makeTypesCompatible( switched, &val1, &val2 );
	if( switched )
	{
		tval = val1;
		val1 = val2;
		val2 = tval;
	}

	*val1 -= *val2;
	delete val2;
	exp.ves().pushValue( val1 );
}


OrInstruction::OrInstruction( SqlHandle& _dbsql ) : BinaryOperatorInstruction( _dbsql )
{
}


OrInstruction::~OrInstruction( void )
{
}


void OrInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	if( !( !( *val1 ) ) )
		exp.pushYes();
	else
	{
		if( !( !( *val2 ) ) )
			exp.pushYes();
		else
			exp.pushNo();
	}

	exp.vesStateBoolean();
	delete val1;
	delete val2;
}


void OrInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


OuterJoinInstruction::OuterJoinInstruction( SqlHandle& _dbsql ) : BinaryOperatorInstruction( _dbsql )
{
}


OuterJoinInstruction::~OuterJoinInstruction( void )
{
}


void OuterJoinInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2;
	pIntegerLiteralElement ile;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	//
	//  the equal test for the outer join is always true
	//
	delete val2;
	delete val1;

	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	dynamic_cast< Cql_Integer& >( ile->value() ) = Cql_Integer( 1 );
	exp.ves().pushValue( ile );
}


PlusInstruction::PlusInstruction( SqlHandle& _dbsql ) : BinaryOperatorInstruction( _dbsql )
{
}


PlusInstruction::~PlusInstruction(void)
{
}


void PlusInstruction::execute( Expression& exp )
{
	AbstractValueElement *val2 = exp.ves().popValue();
	AbstractValueElement *val1 = exp.ves().popValue();

	bool switched;
	makeTypesCompatible( switched, &val1, &val2 );
	//  for addition, we don't care whether values were switched

	*val1 += *val2;
	delete val2;

	exp.ves().pushValue( val1 );
}


QueryInstruction::QueryInstruction( void ) : QueryInstructionListElement()
{
}


QueryInstruction::~QueryInstruction( void )
{
}


SetComparisonInstruction::SetComparisonInstruction( SqlHandle& _dbsql, ComparisonOperators cop ) : Instruction( _dbsql ), comparisonOp( cop )
{
}


SetComparisonInstruction::SetComparisonInstruction( SqlHandle& _dbsql ) : Instruction( _dbsql )
{
}


SetComparisonInstruction::~SetComparisonInstruction( void )
{
}


Instruction& SetComparisonInstruction::operator = ( const Instruction& cins )
{
	Instruction& ins = const_cast< Instruction& >( cins );
	SetComparisonInstruction& other = dynamic_cast< SetComparisonInstruction& >( ins );

	AbstractAssign( ins );
	comparisonOp = other.comparisonOp;
	return *this;
}


void SetComparisonInstruction::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << comparisonOp << ComparisonModifier();
}


void SetComparisonInstruction::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> comparisonOp;

	ComparisonModifiers sqm;
	buffer >> sqm;
}


US SetComparisonInstruction::dictionaryLength( void )
{
	return sizeof( ComparisonOperators ) + sizeof( ComparisonModifiers );
}


void SetComparisonInstruction::buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack )
{
	pPredicate pred;
	pNonterminalPredicateOperand ntpop;

	pred = new Predicate( dbsql() );
	if( !pred )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	pred->ins( this );
	//
	//  pop the operands off the stack
	//
	pred->left( stack.pop() );
	if( pred->left() == 0 )
	{
		delete pred;
		throw InternalErrorException( __FILE__, __LINE__ );
	}
	else
		pred->setLeftExists();

	pred->right( stack.pop() );
	if( pred->right() == 0 )
	{
		delete pred;
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	ntpop = new NonterminalPredicateOperand( dbsql() );
	if( !ntpop )
	{
		delete pred;
		throw InternalErrorException( __FILE__, __LINE__ );
	}
	ntpop->descendent( pred );

	stack.push( ntpop );
	predList.add( pred );
}

	
void SetComparisonInstruction::processViewData( SelectExpressionList& )
{
}


SetPushInstruction::SetPushInstruction( pSelectExpression s ) : QueryInstruction(), selectExp( s )
{
}


SetPushInstruction::~SetPushInstruction( void )
{
}


void SetPushInstruction::execute( QueryExpression& )
{
	if( selectExp->correlated() )
		return;

	if( selectExp->previousSelectExpression() == 0 )
		selectExp->cursorEvaluate();
		
	else if( selectExp->nextSelectExpression() == 0 )
		selectExp->cursorEvaluate();

	else if( selectExp->nextSelectExpression()->correlated() )
	{
		selectExp->setCorrelated();
		return;
	}

	else
		selectExp->cursorEvaluate();
}


bool SetPushInstruction::assignResultSetFile( QueryExpression& qexp, bool firstSelect )
{
	if( !firstSelect )
	{
		selectExp->setQueryExpressionResultSet( &qexp );
		return true;
	}

	return false;
}


void SetPushInstruction::cleanup( QueryExpression& )
{
	selectExp->cleanup();
}


SubqueryInstruction::SubqueryInstruction( SqlHandle& _dbsql, SelectExpression *sel ) : Instruction( _dbsql ), selectExpression_( sel )
{
}


SubqueryInstruction::SubqueryInstruction( SqlHandle& _dbsql ) : Instruction( _dbsql ), selectExpression_( 0 )
{
}


SubqueryInstruction::~SubqueryInstruction( void )
{
}


void SubqueryInstruction::execute( Expression& exp )
{
	pSubqueryElement subqEl;

	subqEl = new SubqueryElement( selectExpression_ );
	if( !subqEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	if( selectExpression_->correlated() )
	{
		try
		{
			selectExpression_->cursorEvaluate();
		}
		catch( NoDataException& )
		{
			//  No data is a normal condition
		}
	}

	exp.ves().pushValue( subqEl );
	exp.vesStateValue();
}


void SubqueryInstruction::promote( Expression& exp, bool useWorkingType )
{
	CqlColumnTypes type;

	type = selectExpression_->columns().first()->ColumnExpression().valueExpressionType();
	exp.promote( type, useWorkingType );
}


void SubqueryInstruction::buildPredicateTreeElement( PredicateList&, AbstractPredicateOperandList &stack )
{
	pTerminalPredicateOperand tpop;

	tpop = new TerminalPredicateOperand( dbsql() );
	if( !tpop )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	tpop->ins( this );
	stack.push( tpop );
}


void SubqueryInstruction::processViewData( SelectExpressionList& sel )
{
	selectExpression_ = sel[ static_cast< US >( setNumber_ ) ];
}


pColumnSpecification SubqueryInstruction::Col( void )
{
	return ((pColumnSpecification)0);
}


US SubqueryInstruction::dictionaryLength( void )
{
	//
	//  information stored in dictionary is set number
	//
	return sizeof( setNumber_ );
}


void SubqueryInstruction::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> setNumber_;
}


void SubqueryInstruction::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << setNumber_;
}


Instruction& SubqueryInstruction::operator = ( const Instruction& cins )
{
	Instruction& ins = const_cast< Instruction& >( cins );
	SubqueryInstruction& other = dynamic_cast< SubqueryInstruction& >( ins );

	if( other.selectExpression_ )
	{
		selectExpression_ = new SelectExpression( *other.selectExpression_ );
		if( !selectExpression_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	setNumber_ = other.setNumber_;
	return *this;
}


TertiaryOperatorInstruction::TertiaryOperatorInstruction( SqlHandle& _dbsql ) : Instruction( _dbsql )
{
}


TertiaryOperatorInstruction::~TertiaryOperatorInstruction( void )
{
}


void TertiaryOperatorInstruction::buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList&stack )
{
	pPredicate pred;
	pNonterminalPredicateOperand ntpop;

	pred = new Predicate( dbsql() );
	if( !pred )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	pred->ins( this );

	//
	//  pop the operands off the stack
	//
	pred->left( stack.pop() );
	if( pred->left() == 0 )
	{
		delete pred;
		throw StackUnderflowException( __FILE__, __LINE__ );
	}
	else
		pred->setLeftExists();

	pred->right( stack.pop() );
	if( pred->right() == 0 )
	{
		delete pred;
		throw StackUnderflowException( __FILE__, __LINE__ );
	}

	pred->third( stack.pop() );
	if( pred->third() == 0 )
	{
		delete pred;
		throw StackUnderflowException( __FILE__, __LINE__ );
	}

	ntpop = new NonterminalPredicateOperand( dbsql() );
	if( !ntpop )
	{
		delete pred;
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	ntpop->descendent( pred );
	stack.push( ntpop );
	predList.add( pred );
}


void TertiaryOperatorInstruction::processViewData( SelectExpressionList& )
{
}


Instruction& TertiaryOperatorInstruction::operator = ( const Instruction& ins )
{
	dynamic_cast< Instruction& >( *this ) = ins;
	return *this;
}


void TertiaryOperatorInstruction::writeDictionaryInformation( TempBuffer& )
{
}


void TertiaryOperatorInstruction::readDictionaryInformation( TempBuffer& )
{
}


TimesInstruction::TimesInstruction( SqlHandle& _dbsql ) : BinaryOperatorInstruction( _dbsql )
{
}


TimesInstruction::~TimesInstruction( void )
{
}


void TimesInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	bool switched;
	makeTypesCompatible( switched, &val1, &val2 );
	//  for multiplication, we don't care whether values were switched

	*val1 *= *val2;
	delete val2;
	exp.ves().pushValue( val1 );
}


UnaryMinusInstruction::UnaryMinusInstruction( SqlHandle& _dbsql ) : UnaryOperatorInstruction( _dbsql )
{
}


UnaryMinusInstruction::~UnaryMinusInstruction( void )
{
}


void UnaryMinusInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pNumericLiteralElement nle;

	val = exp.ves().popValue();

	if( !val->isNumeric() )
	{
		delete val;
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	nle = ((pNumericLiteralElement)val);
	-nle->value();
	exp.ves().pushValue( val );
}


UnaryOperatorInstruction::UnaryOperatorInstruction( SqlHandle& _dbsql ) : Instruction( _dbsql )
{
}


UnaryOperatorInstruction::~UnaryOperatorInstruction( void )
{
}


void UnaryOperatorInstruction::buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList&stack )
{
	pPredicate pred;
	pNonterminalPredicateOperand ntpop;

	pred = new Predicate( dbsql() );
	if( !pred )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	pred->ins( this );

	//
	//  pop the predicate stack into the left operand
	//
	pred->left( stack.pop() );
	if( pred->left() == 0 )
	{
		delete pred;
		throw StackUnderflowException( __FILE__, __LINE__ );
	}
	else
		pred->setLeftExists();

	ntpop = new NonterminalPredicateOperand( dbsql() );
	if( !ntpop )
	{
		delete pred;
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}
	ntpop->descendent( pred );

	stack.push( ntpop );
	predList.add( pred );
}


void UnaryOperatorInstruction::processViewData( SelectExpressionList& )
{
}


Instruction& UnaryOperatorInstruction::operator = ( const Instruction& ins )
{
	dynamic_cast< Instruction& >( *this ) = ins;
	return *this;
}


US UnaryOperatorInstruction::dictionaryLength( void )
{
	return 0;
}


void UnaryOperatorInstruction::writeDictionaryInformation(TempBuffer& )
{
}


void UnaryOperatorInstruction::readDictionaryInformation( TempBuffer& )
{
}


ValueInstruction::ValueInstruction( SqlHandle& _dbsql, pAbstractValueElement e ) : Instruction( _dbsql ), el( e )
{
}


ValueInstruction::ValueInstruction( SqlHandle& sqlh ) : Instruction( sqlh ), el( 0 )
{
}


ValueInstruction::~ValueInstruction( void )
{
	if( el )
		delete el;
}


void ValueInstruction::execute( Expression& exp )
{
	AbstractValueElement *newEl = AbstractValueElement::createObject( el->value() );
	exp.ves().pushValue( newEl );
	exp.vesStateValue();
}


void ValueInstruction::promote( Expression& exp, bool useWorkingType )
{
	exp.promote( el->dataType(), useWorkingType );
}


void ValueInstruction::buildPredicateTreeElement( PredicateList&, AbstractPredicateOperandList&stack )
{
	pTerminalPredicateOperand tpop;

	tpop = new TerminalPredicateOperand( dbsql() );
	if( !tpop )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	tpop->ins( this );
	stack.push( tpop );
}


void ValueInstruction::processViewData( SelectExpressionList& )
{
}


Instruction& ValueInstruction::operator = ( const Instruction& cins )
{
	Instruction& ins = const_cast< Instruction& >( cins );
	ValueInstruction& other = dynamic_cast< ValueInstruction& >( ins );

	if( other.el )
	{
		el = AbstractValueElement::createObject( other.el->value() );
		*el = *other.el;
	}
	else
		el = 0;
	return *this;
}


US ValueInstruction::dictionaryLength( void )
{
	UNI size = sizeof( NI ) + el->dictionaryLength();
	return static_cast< US >( size );
}


void ValueInstruction::writeDictionaryInformation( TempBuffer& buffer )
{
	CqlColumnTypes type = el->dataType();
	buffer << type;
	el->writeDictionaryInformation( buffer );
}


void ValueInstruction::readDictionaryInformation( TempBuffer& buffer )
{
	CqlColumnTypes type;
	buffer >> type;

	el = AbstractValueElement::createObject( type );
	el->readDictionaryInformation( buffer );
}
