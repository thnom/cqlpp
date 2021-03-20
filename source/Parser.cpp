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


void Parser::positionedUpdate( void )
{
	Cursor *cursor = findCursor();
	cursor->positionedUpdate( updateColumns_, preparing_ );
	if( !preparing_ )
		cleanup();
}


void Parser::searchedUpdate( void )
{
	currentSelectExpression_->searchedUpdate( updateColumns_, preparing_ );
	if( !preparing_ )
		cleanup();
}


void Parser::commitWork( void )
{
	dbsql_.commitTransaction();
	cleanup();
}


void Parser::rollbackWork( void )
{
	dbsql_.rollbackTransaction();
	cleanup();
}


void Parser::declareCursor( void )
{
	SelectExpressionList& sets = dbsql_.workingSets();
	pCursor cursor = dbsql_.currentCursor();
	pSelectExpression _select;
	US numberOfSets;

	for( _select = sets.last(), numberOfSets = 0; _select; _select = sets.prev(), numberOfSets++ )
		_select->processSelect();

	sets.move( cursor->sets() );
	dbsql_.allocateWorkingSet();
	cursor->cursorExpression( cursorExpression_ );
	cursorExpression_ = 0;
	cleanup();
}


void Parser::select( void )
{
	SelectExpressionList& sets = dbsql_.workingSets();
	pSelectExpression selectExp;
	pQueryInstruction queryIns, firstQueryIns;
	QueryInstructionList& ilist = cursorExpression_->instructions();
	US numberOfSets;

	for( selectExp = sets.last(), numberOfSets = 0; selectExp; selectExp = sets.prev(), numberOfSets++ )
	{
		try
		{
			selectExp->processSelect();
		}
		catch( CqlException& ex )
		{
			std::cout << ex;
			cleanup();
			return;
		}
	}

	firstQueryIns = ilist.first();
	
	for( queryIns = ilist.last(); queryIns; queryIns = ilist.prev() )
	{
		if( queryIns == firstQueryIns )
			break;
		queryIns->execute( *cursorExpression_ );
	}

	bool firstSelect;
	for( queryIns = ilist.first(), firstSelect = false; queryIns && !firstSelect; queryIns = ilist.next() )
	{
		if( queryIns == firstQueryIns )
			break;
		firstSelect = queryIns->assignResultSetFile( *cursorExpression_, firstSelect );
	}

	selectExp = dbsql_.workingSets().first();
	try
	{
		selectExp->interactiveSelect( numberOfSets );
	}
	catch( CqlException& ex )
	{
		std::cout << ex;
	}
	cleanup();
}


void Parser::addGrantee( const char * const name )
{
	GrantUser *user = new GrantUser;
	if( !user )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	user->UserName().setStringUpper( name );
	grantUsers_.add( user );
}


void Parser::setUpdateColumnIdentifier( NC *name )
{
	//
	//  this references the most recent grant privilege, which must be update
	//
	pGrantPrivilege priv;
	pGrantColumn grantCol;

	priv = grantPrivileges_.current();
	if( !priv )
		throw InternalErrorException( __FILE__, __LINE__ );

	if( !priv->updatePriv() )
		throw InternalErrorException( __FILE__, __LINE__ );

	grantCol = new GrantColumn;
	if( !grantCol )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	grantCol->ColumnName().setStringUpper( name );
	priv->grantColumns().add( grantCol );
}


void Parser::setReferenceColumnIdentifier( NC *name )
{
	//
	//  this references the most recent grant privilege, which must be REFERENCES
	//
	pGrantPrivilege priv;
	pGrantColumn referenceCol;

	priv = grantPrivileges_.current();
	if( !priv )
		throw InternalErrorException( __FILE__, __LINE__ );

	if( !priv->referencesPriv() )
		throw InternalErrorException( __FILE__, __LINE__ );

	referenceCol = new GrantColumn;
	if( !referenceCol )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	referenceCol->ColumnName().setStringUpper( name );
	priv->referenceColumns().add( referenceCol );
}


void Parser::setSelectListName( NC *name )
{
	selectListName_.setStringUpper( name );
}


void Parser::setSelectListPrefix( NC *name )
{
	selectListPrefix_.setStringUpper( name );
}


void Parser::addColumnUsingSelectListNames( void )
{
	addColumn( selectListName_.text(), selectListPrefix_.text() );
	selectListName_.reset();
	selectListPrefix_.reset();
}


void Parser::addPlusOperator( void )
{
	pBinaryOperatorInstruction ins = new PlusInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	currentExpression_->instructions().add( ins );
	currentExpression_->label() += "+";
}


void Parser::addMinusOperator( void )
{
	pBinaryOperatorInstruction ins = new OperatorMinusInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	currentExpression_->instructions().add( ins );
	currentExpression_->label() += "-";
}


void Parser::addMultiplicationOperator( void )
{
	pBinaryOperatorInstruction ins = new TimesInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	currentExpression_->instructions().add( ins );
	currentExpression_->label() += "*";
}


void Parser::addDivisionOperator( void )
{
	pBinaryOperatorInstruction ins = new DivideInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	currentExpression_->instructions().add( ins );
	currentExpression_->label() += "/";
}


void Parser::addUnaryMinusOperatorIfNecessary( void )
{
	if( !unaryMinusFlag_ )
		return;

	pUnaryOperatorInstruction ins = new UnaryMinusInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	currentExpression_->instructions().add( ins );
	currentExpression_->label() += "-";
}


void Parser::addTableName( NC *name )
{
	pTripleStringListElement tsl = new TripleStringListElement;
	if( !tsl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	if( baseTablePrefix_.length() )
	{
		tsl->s2().setStringUpper( baseTablePrefix_ );
		baseTablePrefix_.reset();
	}

	tsl->s1().setStringUpper( name );
	currentSelectExpression_->tableNames().add( tsl );
}


void Parser::setCorrelationName( NC *name )
{
	pTripleStringListElement tsl = currentSelectExpression_->tableNames().last();
	if( !tsl )
		throw InternalErrorException( __FILE__, __LINE__ );

	tsl->s3().setStringUpper( name );
}


Parser::Parser( SqlHandle& sqlh )
	:  baseTableName_(),
	   baseTablePrefix_(),
	   createTableColumns_(),
	   currentCreateColumn_( 0 ),
	   currentExpression_( 0 ),
	   cursorExpression_( 0 ),
	   cursorName_(),
	   currentSelectExpression_( 0 ),
	   dbsql_( sqlh ),
	   defaultValue_( 0 ),
	   embeddedStatement_(),
	   escapeCharacter_( 0 ),
	   files_(),
	   foreignKeys_(),
	   grantPrivileges_(),
	   grantTableName_(),
	   grantTablePrefix_(),
	   grantUsers_(),
	   indexName_(),
	   indexPrefix_(),
	   indices_(),
	   insertColumnNames_(),
	   keyColumnNames_(),
	   optionValue_( 0 ),
	   selectListName_(),
	   selectListPrefix_(),
	   stack_(),
	   tableCheckCondition_( sqlh ),
	   tableListName_(),
	   tableListPrefix_(),
	   valueCounter_( 0 ),
	   viewColumnNames_(),
	   viewedTableName_(),
	   viewedTablePrefix_(),
	   batchMode_( false ),
	   cascade_( false ),
	   checkOption_( false ),
	   creatingUniqueIndex_( false ),
	   declaringCursor_( false ),
	   doingColumnElement_( false ),
	   doingColumns_( false ),
	   echo_( false ),
	   embeddedInput_( false ),
	   escape_( false ),
	   existsFlag_( false ),
	   grantOption_( false ),
	   insertWithSelect_( false ),
	   preparing_( false ),
	   restrict_( false ),
	   selectInto_( false ),
	   shuttingDown_( false ),
	   statementEnded_( false ),
	   unaryMinusFlag_( false )
{
}


Parser::~Parser( void )
{
	if( optionValue_ )
	{
		delete optionValue_;
		optionValue_ = 0;
	}
}


void Parser::allocateCursorExpression( void )
{
	cursorExpression_ = new QueryExpression;
	if( !cursorExpression_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );
}


void Parser::generateSetPush( void )
{
	if( !cursorExpression_ )
		allocateCursorExpression();

	SetPushInstruction *ins = new SetPushInstruction( currentSelectExpression_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	cursorExpression_->instructions().add( ins );
}


void Parser::startWhere( void )
{
	currentSelectExpression_->assignWhereExpression( &currentExpression_ );
}


void Parser::addComparisonOperator( ComparisonOperators op )
{
	switch( op )
	{
	case SETCOMP_EQUAL :
		addEqualsInstruction();
		break;

	case SETCOMP_NOT_EQUAL :
		addNotEqualInstruction();
		break;

	case SETCOMP_LESS :
		addLessInstruction();
		break;

	case SETCOMP_LESS_OR_EQUAL :
		addLessOrEqualInstruction();
		break;

	case SETCOMP_GREATER :
		addGreaterInstruction();
		break;

	case SETCOMP_GREATER_OR_EQUAL :
		addGreaterOrEqualInstruction();
		break;
	}
}


void Parser::addBetweenInstruction( void )
{
	BetweenInstruction *ins = new BetweenInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addEqualsInstruction( void )
{
	pEqualsInstruction ins = new EqualsInstruction( dbsql_);
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addLessInstruction( void )
{
	pLessInstruction ins = new LessInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addGreaterInstruction( void )
{
	pGreaterInstruction ins = new GreaterInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addLessOrEqualInstruction( void )
{
	pLessOrEqualInstruction ins = new LessOrEqualInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addGreaterOrEqualInstruction( void )
{
	pGreaterOrEqualInstruction ins = new GreaterOrEqualInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addNotEqualInstruction( void )
{
	pNotEqualInstruction ins = new NotEqualInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addLogicalOperator( LogicalOperators lop )
{
	switch( lop )
	{
	case LOP_AND :
		addAndInstruction();
		break;

	case LOP_OR :
		addOrInstruction();
		break;
	}
}


void Parser::addAndInstruction( void )
{
	pAndInstruction ins = new AndInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addOrInstruction( void )
{
	pOrInstruction ins = new OrInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::startOrderBy( void )
{
	currentSelectExpression_->assignOrderByExpression( &currentExpression_ );
	currentSelectExpression_->setOrderBy();
}


void Parser::endSelectListElement( void )
{
	doingColumnElement_ = false;
}


void Parser::setOrderDescending( void )
{
	currentSelectExpression_->setOrderDescending();
}


void Parser::startSubquery( void )
{
	pSelectExpression _select;

	stackPush();

	_select = new SelectExpression( dbsql_ );
	if( !_select )
	{
		stackPop();
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	dbsql_.workingSets().add( _select );
	currentSelectExpression_ = _select;

	if( existsFlag_ == CQL_YES )
		_select->setExistsSubquery();

	doingColumns_ = true;
	doingColumnElement_ = false;

	generateSetPush();
}


void Parser::endSubquery( void )
{
	pSelectExpression innerSelect = currentSelectExpression_;
	pSubqueryInstruction ins;

	stackPop();
	ins = new SubqueryInstruction( dbsql_, innerSelect );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addSetComparison( ComparisonOperators compOp, ComparisonModifiers compMod )
{
	switch( compMod )
	{
	case MOD_ANY :
		addAnyInstruction( compOp );
		break;

	case MOD_ALL :
		addAllInstruction( compOp );
		break;
	}
}


void Parser::addAnyInstruction( ComparisonOperators compOp )
{
	pAnyInstruction ins = new AnyInstruction( dbsql_, compOp );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addAllInstruction( ComparisonOperators compOp )
{
	pAllInstruction ins = new AllInstruction( dbsql_, compOp );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::stackPush( void )
{
	pParserStackElement pse = new ParserStackElement;
	if( !pse )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	pse->currentSelectExpression_ = currentSelectExpression_;
	pse->currentExpression_ = currentExpression_;
	pse->batchMode_ = batchMode_;
	pse->cascade_ = cascade_;
	pse->creatingUniqueIndex_ = creatingUniqueIndex_;
	pse->declaringCursor_ = declaringCursor_;
	pse->doingColumns_ = doingColumns_;
	pse->doingColumnElement_ = doingColumnElement_;
	pse->echo_ = echo_;
	pse->embeddedInput_ = embeddedInput_;
	pse->escape_ = escape_;
	pse->insertWithSelect_ = insertWithSelect_;
	pse->restrict_ = restrict_;
	pse->selectInto_ = selectInto_;
	pse->shuttingDown_ = shuttingDown_;
	pse->statementEnded_ = statementEnded_;
	pse->unaryMinusFlag_ = unaryMinusFlag_;

	stack_.push( pse );
}


void Parser::stackPop( void )
{
	pParserStackElement pse;

	pse = stack_.pop();
	if( !pse )
		throw StackUnderflowException( __FILE__, __LINE__ );

	currentSelectExpression_ = pse->currentSelectExpression_;
	currentExpression_ = pse->currentExpression_;
	batchMode_ = pse->batchMode_;
	cascade_ = pse->cascade_;
	creatingUniqueIndex_ = pse->creatingUniqueIndex_;
	declaringCursor_ = pse->declaringCursor_;
	doingColumns_ = pse->doingColumns_;
	doingColumnElement_ = pse->doingColumnElement_;
	echo_ = pse->echo_;
	embeddedInput_ = pse->embeddedInput_;
	escape_ = pse->escape_;
	insertWithSelect_ = pse->insertWithSelect_;
	restrict_ = pse->restrict_;
	selectInto_ = pse->selectInto_;
	shuttingDown_ = pse->shuttingDown_;
	statementEnded_ = pse->statementEnded_;
	unaryMinusFlag_ = pse->unaryMinusFlag_;

	delete pse;
}


void Parser::addExistsInstruction( void )
{
	pExistsInstruction existsIns = new ExistsInstruction( dbsql_ );
	if( !existsIns )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( existsIns );
}


void Parser::addCountStarInstruction( void )
{
	if( doingColumns_ )
		beginColumn();

	CountStarFunctionInstruction *ins = new CountStarFunctionInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	currentExpression_->instructions().add( ins );
	currentExpression_->label() += "COUNT(*)";
}


void Parser::addCountColumnInstruction( void )
{
	CountColumnFunctionInstruction *ins = new CountColumnFunctionInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
	currentExpression_->label() += ")";
}


void Parser::addAggregateFunction( AggregateFunctions aggFunc )
{
	switch( aggFunc )
	{
	case AGGREGATE_AVG :
		addAvgInstruction();
		break;

	case AGGREGATE_MAX :
		addMaxInstruction();
		break;

	case AGGREGATE_MIN :
		addMinInstruction();
		break;

	case AGGREGATE_SUM :
		addSumInstruction();
		break;
	}

	currentExpression_->label() += ")";
}


void Parser::addAvgInstruction( void )
{
	AvgFunctionInstruction *ins = new AvgFunctionInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addMaxInstruction( void )
{
	MaxFunctionInstruction *ins = new MaxFunctionInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addMinInstruction( void )
{
	MinFunctionInstruction *ins = new MinFunctionInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addSumInstruction( void )
{
	SumFunctionInstruction *ins = new SumFunctionInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addGroupByColumn( NC *prefix, NC *name )
{
	pColumn col;
	pExpressionColumnListElement expColListEl;
	pIdentifierInstruction ins;

	col = new Column( dbsql_ );
	if( !col )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	currentSelectExpression_->groupByColumns().add( col );

	expColListEl = new ExpressionColumnListElement;
	if( !expColListEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	expColListEl->Name().setStringUpper( name );
	if( prefix )
		expColListEl->Prefix().setStringUpper( prefix );

	col->ColumnExpression().columns().add( expColListEl );

	ins = new IdentifierInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	expColListEl->SetIns( ins );
	col->ColumnExpression().instructions().add( ins );
}


void Parser::groupBy( void )
{
	currentSelectExpression_->setGroupBy();
}


void Parser::startHaving( void )
{
	currentSelectExpression_->assignHavingExpression( &currentExpression_ );
	currentSelectExpression_->setHaving();
}


void Parser::addUpdateColumnIdentifier( NC *name )
{
	UpdateColumnNameAndExp *updateValue = new UpdateColumnNameAndExp( dbsql_ );
	if( !updateValue )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	updateValue->s().setStringUpper( name );
	updateColumns_.add( updateValue );
	currentExpression_ = updateValue->pExp();
}


void Parser::addCreateColumn( NC *name )
{
	pColumnSpecification colSpec;
	pNC p;

	colSpec = new ColumnSpecification( dbsql_ );
	if( !colSpec )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	strcpy( colSpec->columnName(), name );

	for( p = colSpec->columnName(); *p; p++ )
		*p = hAEnv->convertCharToUppercase( *p );

	createTableColumns_.add( colSpec );
	currentCreateColumn_ = colSpec;
}


void Parser::beginColumnCheckCondition( void )
{
	currentExpression_ = currentCreateColumn_->pCheckCondition();
	doingColumns_ = false;
}


void Parser::setGrantTableName( NC *name )
{
	grantTableName_ = name;
}


void Parser::setGrantTablePrefix( NC *prefix )
{
	grantTablePrefix_ = prefix;
}


void Parser::addToLabel( NC *txt )
{
	currentExpression_->label() += txt;
}


NC Parser::embeddedGetCharacter( void )
{
	return embeddedStatement_.nextCharacter();
}


//****************************************************************************
//**  yyin is defined in the bison/yacc generated files, and declared as    **
//**  external here.                                                        **
//****************************************************************************
extern FILE *yyin;

void Parser::beginScript( NC *name, bool noShorten )
{
	FILE *prevFile;
	pFILEListElement fle;
	pNC p;

	//
	//  remove trailing quote and newline
	//
	if( noShorten == false )
	{
		p = name + ( strlen( name ) - 1 );
		*(p--) = 0;
		*p = 0;
	}

	fle = new FILEListElement;
	if( !fle )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	prevFile = yyin;
	yyin = fopen( name, "r" );
	if( !yyin )
	{
		yyin = prevFile;
		delete fle;
		throw FileNotFoundException( __FILE__, __LINE__, errno );
	}

	fle->SetF( prevFile );
	files_.add( fle );
	batchMode_ = CQL_YES;
}


bool Parser::popAnInputFile( void )
{
	pFILEListElement fle;

	fle = files_.last();
	if( !fle )
		return false;

	files_.remove( fle );

	//  2/1/03 removed close which was duplicated from caller
	yyin = fle->F();
	delete fle;

	if( files_.size() == 0 )
	{
		batchMode_ = false;
		newStatement();
	}

	return true;
}


FILE *tempYyin;

NI Parser::yywrap( void )
{
	if( shuttingDown_ )
		return 1;

	if( statementEnded_ )
	{
		statementEnded_ = CQL_NO;
		yyin = tempYyin;
		return 1;
	}

	popAnInputFile();

	return 1;
}


void Parser::initForStatement( void )
{
}


void Parser::selectDistinct( void )
{
	currentSelectExpression_->setDistinct();
}


void Parser::selectUnique( void )
{
	currentSelectExpression_->setUnique();
}


void Parser::columnHeading( NC *txt )
{
	Column *column = currentSelectExpression_->columns().current();
	if( !column )
		throw InternalErrorException( __FILE__, __LINE__ );
	currentExpression_->label() = txt;
}


void Parser::setJustifyRight( void )
{
	currentSelectExpression_->columns().current()->SetJustifyRight();
}


void Parser::setJustifyCenter( void )
{
	currentSelectExpression_->columns().current()->SetJustifyCenter();
}


void Parser::addNOTOperator( void )
{
	LogicalNotInstruction *ins = new LogicalNotInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addLIKEOperator( void )
{
	BinaryOperatorInstruction *ins = new LikeInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addValueInstruction( pAbstractValueElement el )
{
	ValueInstruction *ins = new ValueInstruction( dbsql_, el );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
}


void Parser::addNULLPush( void )
{
	NullLiteralElement *el = new NullLiteralElement;
	if( !el )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	addValueInstruction( el );
}


void Parser::addIdentifierPush( void )
{
	IdentifierInstruction *ins = new IdentifierInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	ins->col( currentSelectExpression_->columns().current()->ColumnExpression().columns().first()->Column() );
	currentExpression_->instructions().add( ins );
}


void Parser::addUSERPush( void )
{
	FunctionInstruction *ins = new UserFunctionInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	ins->SetNumberOfArguments( 0 );
	currentExpression_->instructions().add( ins ) ;
}


void Parser::addDynamicParameterPush( void )
{
	AbstractValueElement *el = new DynamicParameterElement;
	if( !el )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	addValueInstruction( el );
	currentExpression_->label() += "?";
}


void Parser::endColumnElement( void )
{
	doingColumnElement_ = false;
}


void Parser::addColumn( const char * const name, const char * const prefix )
{
	pColumn col;
	pExpressionColumnListElement expColListEl;
	pIdentifierInstruction ins;

	if( doingColumns_ && !doingColumnElement_ )
	{
		doingColumnElement_ = true;
		col = new Column( dbsql_ );
		if( !col )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		currentSelectExpression_->columns().add( col );
		col->AssignColumnExpression( &currentExpression_ );
	}

	expColListEl = new ExpressionColumnListElement;
	if( !expColListEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	expColListEl->Name().setStringUpper( name );
	expColListEl->Prefix().setStringUpper( prefix );
	currentExpression_->columns().add( expColListEl );

	ins = new IdentifierInstruction( dbsql_ );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	expColListEl->SetIns( ins );
	currentExpression_->instructions().add( ins );

	if( prefix )
	{
		currentExpression_->label() += prefix;
		currentExpression_->label() += ".";
	}

	currentExpression_->label() += name;
}


void Parser::setAlterColumnName( NC *name )
{
	addColumn( name );
}


void Parser::setSegmentedKeyColumn( NC *name )
{
	StringListElement *element = new StringListElement;
	if( !element )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	element->s().setStringUpper( name );
	keyColumnNames_.add( element );
}


void Parser::setColumnType( CqlColumnTypes t )
{
	currentCreateColumn_->type( t );
}


void Parser::setColumnLength( NI l )
{
	currentCreateColumn_->length( l );
}


void Parser::setColumnLength( UIWithLeadingZeros* l )
{
	setColumnLength( l->val );
}


void Parser::setPrecision( NI p )
{
	currentCreateColumn_->precision( static_cast< UC >( p ) );
}


void Parser::setPrecision( UIWithLeadingZeros* p )
{
	setPrecision( p->val );
}


void Parser::setScale( UIWithLeadingZeros* s )
{
	currentCreateColumn_->scale( ((UC)s->val) );
}


void Parser::setScale( NI s )
{
	currentCreateColumn_->scale(s);
}


void Parser::setIndexColumnIdentifier( NC *name )
{
	addColumn( name );
}


void Parser::setInsertColumnIdentifier( NC *name )
{
	InsertColumnName *icn = new InsertColumnName;
	if( !icn )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	icn->s().setStringUpper( name );
	insertColumnNames_.add( icn );
}


void Parser::setViewColumnIdentifier( NC *name )
{
	StringListElement *sle = new StringListElement;
	if( !sle )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	sle->s().setStringUpper( name );
	viewColumnNames_.add( sle );
}


void Parser::setIndexColumnDescending( void )
{
	currentSelectExpression_->columns().current()->setDescending();
}


void Parser::setCreateColumnIdentifier( NC *name )
{
	addColumn( name );
}


void Parser::setColumnNotNull( void )
{
	currentCreateColumn_->setNotNull();
}


void Parser::setColumnUnique( void )
{
	currentCreateColumn_->setUniqueIndex();
}


void Parser::setColumnIndex( void )
{
	currentCreateColumn_->setDuplicateIndex();
}


void Parser::setReferencedTableName( NC *name )
{
	foreignKeys_.current()->BaseTableName().setStringUpper( name );
}


void Parser::setReferencedTablePrefix( NC *prefix )
{
	foreignKeys_.current()->BaseTablePrefix().setStringUpper( prefix );
}


void Parser::setReferencingIdentifier( NC *name )
{
	StringListElement *sle = new StringListElement;
	if( !sle )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	sle->s().setStringUpper( name );
	foreignKeys_.current()->ReferencingColumns().add( sle );
}


void Parser::setReferencedIdentifier( NC *name )
{
	StringListElement *sle = new StringListElement;
	if( !sle )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	sle->s().setStringUpper( name );
	foreignKeys_.current()->ReferencedColumns().add( sle );
}


void Parser::characterStringLiteral( NC *val )
{
	UNI len = strlen( val );

	StringElement *stringElement = new StringElement();
	if( !stringElement )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	stringElement->str().setString( val + 1, len - 2 );

	ValueInstruction *ins = new ValueInstruction( dbsql_, stringElement );
	if( !ins )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	currentExpression_->instructions().add( ins );
	currentExpression_->label() += val;
}


void Parser::characterDefaultValue( NC *val )
{
	UNI len = strlen( val );
	StringElement *stringEl = new StringElement();
	if( !stringEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	stringEl->str().setString( val + 1, len - 2 );
	defaultValue_ = stringEl;
}


void Parser::approximateNumericLiteral( NC *val )
{
	FloatLiteralElement *element = new FloatLiteralElement;
	if( !element )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Float& cqlf = dynamic_cast< Cql_Float& >( element->value() );
	cqlf = FloatValue( val );
	addValueInstruction( element );
	currentExpression_->label() += val;
}


void Parser::approximateNumericDefaultValue( NC *val )
{
	FloatLiteralElement *floatEl = new FloatLiteralElement;
	if( !floatEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Float& cqlf = dynamic_cast< Cql_Float& >( floatEl->value() );
	cqlf = FloatValue( val );
	defaultValue_ = floatEl;
}


void Parser::dateLiteral( DateLiteral& dl )
{
	DateLiteralElement *element = new DateLiteralElement;
	if( !element )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Date& cdv = dynamic_cast< Cql_Date& >( element->value() );
	cdv = DateValue( dl );
	addValueInstruction( element );
	currentExpression_->label() += "DATE";
}


void Parser::dateDefaultValue( DateLiteral& dl )
{
	DateLiteralElement *dateEl = new DateLiteralElement;
	if( !dateEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Date& cdv = dynamic_cast< Cql_Date& >( dateEl->value() );
	cdv = DateValue( dl );
	defaultValue_ = dateEl;
}


void Parser::timeLiteral( NC *val )
{
	TimeLiteralElement *element = new TimeLiteralElement;
	if( !element )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Time& ctv = dynamic_cast< Cql_Time& >( element->value() );
	ctv = TimeValue( val );
	addValueInstruction( element );
	currentExpression_->label() += val;
}


void Parser::timeDefaultValue( NC *val )
{
	TimeLiteralElement *timeEl = new TimeLiteralElement;
	if( !timeEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Time& ctv = dynamic_cast< Cql_Time& >( timeEl->value() );
	ctv = TimeValue( val );
	defaultValue_ = timeEl;
}


void Parser::timestampLiteral( NC *val )
{
	TimestampLiteralElement *element = new TimestampLiteralElement;
	if( !element )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Timestamp ctsv = dynamic_cast< Cql_Timestamp& >( element->value() );
	ctsv = TimeValue( val );
	addValueInstruction( element );
	currentExpression_->label() += val;
}


void Parser::timestampDefaultValue( NC *val )
{
	TimestampLiteralElement *timestampEl = new TimestampLiteralElement;
	if( !timestampEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Timestamp ctsv = dynamic_cast< Cql_Timestamp& >( timestampEl->value() );
	ctsv = TimeValue( val );
	defaultValue_ = timestampEl;
}


void Parser::binaryLiteral( NI val )
{
	IntegerLiteralElement *ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	dynamic_cast< Cql_Integer& >( ile->value() ) = val;
	addValueInstruction( ile );
}


char *Parser::zeroString( UIWithLeadingZeros* fraction )
{
	memset( zeroBuffer, 0, sizeof( zeroBuffer ) );
	memset( zeroBuffer, '0', fraction->lzs );
	return zeroBuffer;
}


void Parser::exactNumericLiteral( NI mantissa, UIWithLeadingZeros* fraction )
{
	pDecimalLiteralElement element;
	NC buf[ 50 ];

	element = new DecimalLiteralElement;
	if( !element )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	if( mantissa != 0 )
	{
		if( fraction && fraction->lzs != -1 )
			sprintf( buf, "%d.%s%d", mantissa, zeroString(fraction), fraction->val );
		else
			sprintf( buf, "%d", mantissa );
	}
	else
	{
		if( fraction && fraction->lzs != -1 )
			sprintf( buf, "0.%s%d", zeroString(fraction), fraction->val );
		else
			sprintf( buf, "0" );
	}

	DecimalValue dv;
	dv = buf;
	AbstractValue& av = element->value().avalue();
	av = dv;

	addValueInstruction( element );
	currentExpression_->label() += buf;
}


void Parser::exactNumericLiteral( UIWithLeadingZeros* mantissa, UIWithLeadingZeros* fraction )
{
	exactNumericLiteral( mantissa->val, fraction );
}


void Parser::exactNumericDefaultValue( NI mantissa, UIWithLeadingZeros* fraction )
{
	pDecimalLiteralElement decimalEl;
	NC buf[ 50 ];
	CqlString sval;

	decimalEl = new DecimalLiteralElement;
	if( !decimalEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	if( mantissa != 0 )
	{
		if( fraction && fraction->lzs != -1 )
			sprintf( buf, "%d.%s%d", mantissa, zeroString(fraction), fraction->val );
		else
			sprintf( buf, "%d", mantissa );
	}
	else
	{
		if( fraction && fraction->lzs != -1 )
			sprintf( buf, "0.%s%d", zeroString(fraction), fraction->val );
		else
			sprintf( buf, "0" );
	}

	Cql_Decimal& cdv = dynamic_cast< Cql_Decimal& >( decimalEl->value() );
	cdv = DecimalValue( buf );
	defaultValue_ = decimalEl;
}

	
void Parser::exactNumericDefaultValue( UIWithLeadingZeros* mantissa, UIWithLeadingZeros* fraction )
{
	exactNumericDefaultValue( mantissa->val, fraction );
}


void Parser::setDefaultValueNull( void )
{
	currentCreateColumn_->setDefaultValueNull();
}


void Parser::setDefaultValueUser( void )
{
	currentCreateColumn_->setDefaultValueUser();
}


void Parser::setOption( Parser::OptionType ot )
{
	switch( ot )
	{
	case OPTION_DIRECTORY :
		dbsql_.initialDirectory( new CqlString(*optionValue_ ));
		break;
	}

	cleanup();
}


void Parser::showOption( Parser::OptionType ot )
{
	switch( ot )
	{
	case OPTION_DIRECTORY :
		std::cerr << *dbsql_.initialDirectory() << std::endl;
		break;
	}

	cleanup();
}


void Parser::setDefaultValue( void )
{
	currentCreateColumn_->defaultValue( *defaultValue_ );
	currentCreateColumn_->setDefaultValueFlag();
}


void Parser::beginForeignKey( void )
{
	ForeignKeyNames *fkn = new ForeignKeyNames;
	if( !fkn )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	foreignKeys_.add( fkn );
}


void Parser::beginUniqueKeyGroup( void )
{
	IndexNameListGroup *inlg = new IndexNameListGroup;
	if( !inlg )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	inlg->SetUniqueKey();
	indices_.add( inlg );
}


void Parser::beginPrimaryKeyGroup( void )
{
	IndexNameListGroup *inlg = new IndexNameListGroup;
	if( !inlg )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	inlg->SetPrimaryKey();
	indices_.add( inlg );
}


void Parser::beginDuplicateKeyGroup( void )
{
	IndexNameListGroup *inlg = new IndexNameListGroup;
	if( !inlg )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	inlg->SetDuplicateKey();
	indices_.add( inlg );
}


void Parser::beginCheckClause( void )
{
	currentExpression_ = &tableCheckCondition_;
	doingColumns_ = false;
}


void Parser::setKeyColumn( NC *name )
{
	pIndexNameListGroup inlg;
	pIndexColumnName icn;

	icn = new IndexColumnName;
	if( !icn )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	icn->s().setStringUpper( name );
	inlg = indices_.current();
	inlg->Icnl().add( icn );
}


void Parser::statementInitialization( void )
{
	for( currentSelectExpression_ = dbsql_.workingSets().first(); currentSelectExpression_; currentSelectExpression_ = dbsql_.workingSets().next() )
		currentSelectExpression_->clearCleanedUp();

	currentSelectExpression_ = dbsql_.workingSets().first();
	dbsql_.resetError();
	statementEnded_ = unaryMinusFlag_ = false;
	doingColumns_ = CQL_YES;
}


void Parser::cleanup( void )
{
	SelectExpressionList& sets = dbsql_.workingSets();
	pIndexNameListGroup inlg;
	pUpdateColumnNameAndExp updateColName;

	for( currentSelectExpression_ = sets.first(); currentSelectExpression_; currentSelectExpression_ = sets.next() )
		currentSelectExpression_->cleanup();

	setStatementEnded();

	cascade_ =
		checkOption_ =
		creatingUniqueIndex_ =
		declaringCursor_ =
		doingColumns_ =
		doingColumnElement_ =
		escape_ =
		existsFlag_ =
		grantOption_ =
		insertWithSelect_ =
		preparing_ =
		restrict_ =
		selectInto_ =
		shuttingDown_ =
		unaryMinusFlag_ =
		false;

	baseTableName_.reset();
	baseTablePrefix_.reset();
	cursorName_.reset();
	embeddedStatement_.reset();
	grantTableName_.reset();
	grantTablePrefix_.reset();
	indexName_.reset();
	indexPrefix_.reset();
	selectListName_.reset();
	selectListPrefix_.reset();
	viewColumnNames_.destroy();
	viewedTableName_.reset();
	viewedTablePrefix_.reset();

	foreignKeys_.destroy();
	grantPrivileges_.destroy();
	grantUsers_.destroy();
	for( inlg = indices_.first(); inlg; inlg = indices_.next() )
		inlg->Icnl().destroy();
	indices_.destroy();
	insertColumnNames_.destroy();
	keyColumnNames_.destroy();

	for( updateColName = updateColumns_.first(); updateColName; updateColName = updateColumns_.next() )
		updateColName->exp().reset();
	updateColumns_.destroy();

	if( cursorExpression_ )
	{
		delete cursorExpression_;
		cursorExpression_ = ((pQueryExpression)0);
	}

	if( !batchMode_ )
		newStatement();

	sets.destroy();
	dbsql_.allocateWorkingSet();
}


Cursor *Parser::findCursor( void )
{
	pCursor localCursor;

	for( localCursor = dbsql_.cursors().first(); localCursor; localCursor = dbsql_.cursors().next() )
		if( cursorName_ == localCursor->cursorName() )
			return localCursor;

	throw CursorNotFoundException( __FILE__, __LINE__ );
	return 0;  //  dumb compiler
}


void Parser::quit( void )
{
	shuttingDown_ = true;
}


void Parser::beginColumn( void )
{
	Column *col = currentSelectExpression_->beginColumn();
	col->AssignColumnExpression( &currentExpression_ );
}


void Parser::grantPrivilegeAll( void )
{
	GrantPrivilege *grantPriv = new GrantPrivilege;
	if( !grantPriv )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	grantPriv->setDeletePriv();
	grantPriv->setInsertPriv();
	grantPriv->setSelectPriv();
	grantPriv->setUpdatePriv();
	grantPriv->setReferencesPriv();
	grantPrivileges_.add( grantPriv );
}


void Parser::grantPrivilegeDelete( void )
{
	GrantPrivilege *grantPriv = new GrantPrivilege;
	if( !grantPriv )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	grantPriv->setDeletePriv();
	grantPrivileges_.add( grantPriv );
}


void Parser::grantPrivilegeInsert( void )
{
	GrantPrivilege *grantPriv = new GrantPrivilege;
	if( !grantPriv )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	grantPriv->setInsertPriv();
	grantPrivileges_.add( grantPriv );
}


void Parser::grantPrivilegeSelect( void )
{
	GrantPrivilege *grantPriv = new GrantPrivilege;
	if( !grantPriv )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	grantPriv->setSelectPriv();
	grantPrivileges_.add( grantPriv );
}


void Parser::grantPrivilegeUpdate( void )
{
	GrantPrivilege *grantPriv = new GrantPrivilege;
	if( !grantPriv )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	grantPriv->setUpdatePriv();
	grantPrivileges_.add( grantPriv );
}


void Parser::grantPrivilegeReferences( void )
{
	GrantPrivilege *grantPriv = new GrantPrivilege;
	if( !grantPriv )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	grantPriv->setReferencesPriv();
	grantPrivileges_.add( grantPriv );
}


void Parser::insert( void )
{
	if( insertWithSelect_ )
		currentSelectExpression_->insertWithSelect( insertColumnNames_, preparing_ );
	else
		insertWithValues();

	if( !preparing_ )
		cleanup();
}


bool Parser::identifyInsertColumnNames( AbstractTableSpecification *table )
{
	PermanentColumnSpecification *pcs;
	InsertColumnName *icn;
	bool found;

	if( insertColumnNames_.size() == 0 )
	{
		for( pcs = table->columns().first(); pcs; pcs = table->columns().next() )
		{
			icn = new InsertColumnName;
			if( !icn )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			icn->pcs( pcs );
			insertColumnNames_.add( icn );
		}
	}

	else
	{
		for( icn = insertColumnNames_.first(); icn; icn = insertColumnNames_.next() )
		{
			for( pcs = table->columns().first(), found = false; pcs && found == CQL_NO; pcs = table->columns().next() )
			{
				if( icn->s() == pcs->columnName() )
				{
					icn->pcs( pcs );
					found = true;
				}
			}

			if( !found )
				return false;
		}
	}

	return true;
}


void Parser::insertWithValues2( AbstractTableSpecification *table )
{
	US numberOfColumnValues;

 	//
	//  check for INSERT privilege for base table
	//
	if( !dbsql_.checkForInsertPrivilege( table ) )
		throw PrivilegeViolationException( __FILE__, __LINE__ );

	table->open();

	numberOfColumnValues = ((US)insertColumnNames_.size());
	if( numberOfColumnValues == 0 )
		numberOfColumnValues = static_cast< US >( table->columns().size() );

	if( currentSelectExpression_->columns().size() != numberOfColumnValues )
		throw InsertValuesMismatchException( __FILE__, __LINE__ );

	if( !identifyInsertColumnNames( table ) )
		throw ColumnNotFoundException( __FILE__, __LINE__ );

	if( preparing_ )
		return;

	currentSelectExpression_->checkInsertValues( insertColumnNames_ );
	table->beginRowOperation();
	currentSelectExpression_->copyInsertValues( table, insertColumnNames_ );
	currentSelectExpression_->checkView( table );

	dbsql_.beginTransaction();

	try
	{
		table->addRow();
	}
	catch( DuplicateRowException& dre )
	{
		dbsql_.rollbackTransaction( false );
		throw dre;
	}
	catch( IntegrityViolationException& ive )
	{
		dbsql_.rollbackTransaction( false );
		throw ive;
	}
	catch( CheckViolationException& cve )
	{
		dbsql_.rollbackTransaction( CQL_NO );
		throw cve;
	}

	dbsql_.commitTransaction( false );
	table->checkPropagationFlags();
}


void Parser::insertWithValues( void )
{
	pAbstractTableSpecification table = ((pAbstractTableSpecification)0);
	pTripleStringListElement tsl;

	tsl = currentSelectExpression_->tableNames().first();
	dbsql_.activeTables().ClearInUseFlags();
	table = dbsql_.getDictionaryRecord( tsl->s1(), tsl->s2() );
	if( !table )
		throw TableNotFoundException( __FILE__, __LINE__ );

	if( preparing_ )
	{
		dbsql_.currentStatement()->type( INSERT_VALUES );
		dbsql_.currentStatement()->insertAts( table );
	}

	insertWithValues2( table );
}


//
//  at entry:
//
//  grantPrivileges_ lists the privileges being granted.  If the privilege is
//  update or references, the member of the grantPrivileges_ may include a list of columns.
//
//  grantUsers_ lists the users getting privileges
//
void Parser::grant( GrantPrivilegeList& grantPrivs, GrantUserList& gUsers )
{
	PrivilegeDictionaryRecord pdr;
	PrivilegeFieldDictionaryRecord pfdr;
	pGrantPrivilege gp;
	pGrantUser gu;
	pGrantColumn gc;

	if( preparing_ )
		return;

	bool owner;
	if( !grantTablePrefix_ )
	{
		grantTablePrefix_ = dbsql_.aHandle().userName();
		owner = true;
	}
	else if( grantTablePrefix_ == dbsql_.aHandle().userName() )
		owner = true;
	else
		owner = false;

	dbsql_.beginTransaction();

	for( gp = grantPrivs.first(); gp; gp = grantPrivs.next() )
	{
		if( !owner )
		{
			//
			//  need to check whether current user has the privilege, and, if so, whether he has the
			//  grant option for the privilege
			//
			bool grantOpt;

			if( gp->updatePriv() )
			{
				if( !dbsql_.checkForUpdatePrivilege( grantOpt, grantTableName_, grantTablePrefix_, gp->grantColumns() ) || !grantOpt )
				{
					cleanup();
					throw PrivilegeViolationException( __FILE__, __LINE__ );
				}
			}

			if( gp->insertPriv() )
			{
				if( !dbsql_.checkForInsertPrivilege( grantOpt, grantTableName_, grantTablePrefix_ ) || !grantOpt )
				{
					cleanup();
					throw PrivilegeViolationException( __FILE__, __LINE__ );
				}
			}

			if( gp->deletePriv() )
			{
				if( !dbsql_.checkForDeletePrivilege( grantOpt, grantTableName_, grantTablePrefix_ ) || !grantOpt )
				{
					cleanup();
					throw PrivilegeViolationException( __FILE__, __LINE__ );
				}
			}

			if( gp->selectPriv() )
			{
				if( !dbsql_.checkForSelectPrivilege( grantOpt, grantTableName_, grantTablePrefix_ ) || !grantOpt )
				{
					cleanup();
					throw PrivilegeViolationException( __FILE__, __LINE__ );
				}
			}
		}

		for( gu = gUsers.first(); gu; gu = gUsers.next() )
		{
			if( gp->updatePriv() == CQL_YES || gp->referencesPriv() == CQL_YES && gp->grantColumns().first() )
			{
				for( gc = gp->grantColumns().first(); gc; gc = gp->grantColumns().next() )
				{
					pfdr.setup( grantTablePrefix_, grantTableName_, gu->UserName(), gc->ColumnName() );
					dbsql_.addPrivilegeFieldRecord( pfdr );
				}
			}

			pdr.reset();
			pdr.Assign( grantTablePrefix_, grantTableName_, gu->UserName() );
			if( gp->deletePriv() )
				pdr.setDeletePriv();
			if( gp->insertPriv() )
				pdr.setInsertPriv();
			if( gp->referencesPriv() )
				pdr.setReferencesPriv();
			if( gp->selectPriv() )
				pdr.setSelectPriv();
			if( gp->updatePriv() )
				pdr.setUpdatePriv();

			if( grantOption_ == CQL_YES )
				pdr.setGrantOption();

			dbsql_.addOrUpdatePrivilegeRecord( pdr );
		}
	}

	dbsql_.commitTransaction( false );
	//  not necessary to check for preparing_ because we don't get here for prepare
	cleanup();
}


//
//  conditions on entry are the same as for GRANT
//
void Parser::revoke( GrantPrivilegeList& grantPrivs, GrantUserList& gUsers )
{
	PrivilegeDictionaryRecord pdr;
	pGrantPrivilege gp;
	pGrantUser gu;

	if( preparing_ )
		return;

	dbsql_.beginTransaction();

	for( gp = grantPrivs.first(); gp; gp = grantPrivs.next() )
	{
		for( gu = gUsers.first(); gu; gu = gUsers.next() )
		{
			//
			//  delete function automatically finds any associated columns
			//
			pdr.reset();
			pdr.Assign( grantTablePrefix_, grantTableName_, gu->UserName() );
			dbsql_.deletePrivilegeRecords( pdr );
		}
	}

	dbsql_.commitTransaction( false );
}


void Parser::dropIndex( void )
{
	CqlString tName, tAuth;
	pAbstractTableSpecification aTable;
	pTableSpecification table, oldTable;
	pSegmentedKeyGroup skg;

	dbsql_.findTableForIndex( indexName_, tName, tAuth );
	dbsql_.activeTables().ClearInUseFlags();
	aTable = dbsql_.getDictionaryRecord( tName, dbsql_.aHandle().userName() );
	if( !aTable )
		throw DictionaryInconsistentException( __FILE__, __LINE__ );

	oldTable = dynamic_cast< TableSpecification* >( aTable );

	table = new TableSpecification( dbsql_ );
	if( !table )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	*table = *oldTable;

	skg = table->deleteKeyGroup( indexName_ );

	oldTable->open();

	if( preparing_ == CQL_YES )
	{
		dbsql_.currentStatement()->type( DROP_INDEX );
		dbsql_.currentStatement()->oldTable( oldTable );
		dbsql_.currentStatement()->creationTable( table );
		dbsql_.currentStatement()->dropKeyGroup( skg );
		return;
	}

	dropIndexPart2( table, oldTable, skg );
}


void Parser::dropIndexPart2( pTableSpecification table, pTableSpecification oldTable, pSegmentedKeyGroup dropKeyGroup )
{
	pAbstractColumnDescriptor colDesc;
	pColumnSpecification colSpec;
	pPermanentColumnSpecification pcs;
	UNI loop;

	dbsql_.beginTransaction();

	try
	{
		oldTable->file()->deleteIndexMember( dropKeyGroup->KeyNumber() );
	}
	catch( ... )
	{
		dbsql_.rollbackTransaction( CQL_NO );
		throw;
	}

	//
	//  Update system dictionaries
	//
	dbsql_.updateDictionaryInformation( table, oldTable );

	//
	//  Update SystemTableIndices table
	//
	for( colDesc = dropKeyGroup->SegmentedKeyColumns().first(), loop = 0; colDesc; colDesc = dropKeyGroup->SegmentedKeyColumns().next(), loop++ )
	{
		colSpec = dynamic_cast< ColumnSpecification* >( oldTable->columns()[ colDesc->columnNumber() ] );
		pcs = colSpec;

		bool nflag = false;

		dbsql_.systemTableIndices().table().beginIsamOperation( 0 );
		dbsql_.systemTableIndices().table().setCondition( CQL_SYSTEMTABLEINDICES_OWNER_TYPE, oldTable->authorizationId(), nflag, CQL_COP_EQUAL );
		dbsql_.systemTableIndices().table().setCondition( CQL_SYSTEMTABLEINDICES_TABLE_NAME_TYPE, oldTable->tableName(), nflag, CQL_COP_EQUAL );
		dbsql_.systemTableIndices().table().setCondition( CQL_SYSTEMTABLEINDICES_COLUMN_NAME_TYPE, pcs->columnName(), nflag, CQL_COP_EQUAL );
		dbsql_.systemTableIndices().table().setCondition( CQL_SYSTEMTABLEINDICES_KEY_NUMBER_TYPE, dropKeyGroup->KeyNumber(), nflag, CQL_COP_EQUAL );
		dbsql_.systemTableIndices().table().setCondition( CQL_SYSTEMTABLEINDICES_COLUMN_NUMBER_TYPE, loop, nflag, CQL_COP_EQUAL );

		if( !dbsql_.systemTableIndices().table().findFirst( false ) )
			throw DictionaryUpdateException( __FILE__, __LINE__ );

		dbsql_.systemTableIndices().table().deleteRow();
	}

	dbsql_.commitTransaction( false );
}


void Parser::processDrop( AbstractTableSpecification *vtable )
{
	if( restrict_ )
	{
		//
		//  drop must fail if other definitions (view, references) would become invalid if
		//  this table is dropped.
		//
		if( vtable->referencesExist() )
			throw SqlDropRestrictException( __FILE__, __LINE__ );
	}

	if( preparing_ )
		return;

	processDropPart2( vtable );
}


void Parser::processDropPart2( AbstractTableSpecification *vtable )
{
	dbsql_.beginTransaction();

	try
	{
		vtable->deleteDictionaryEntry();
	}
	catch( ... )
	{
		dbsql_.rollbackTransaction( false );
		throw;
	}

	vtable->deleteFiles();

	if( cascade_ )
	{
		//
		// delete any tables/views which now contain invalid references
		//
		try
		{
			vtable->processCascade();
		}
		catch( ... )
		{
			dbsql_.rollbackTransaction( false );
			throw;
		}
	}

	dbsql_.commitTransaction( false );
}


void Parser::dropTable( void )
{
	AbstractTableSpecification *absTableSpec;

	dbsql_.activeTables().ClearInUseFlags();
	if( !baseTablePrefix_ )
		absTableSpec = dbsql_.getDictionaryRecord( baseTableName_, dbsql_.aHandle().userName() );
	else
		absTableSpec = dbsql_.getDictionaryRecord( baseTableName_, baseTablePrefix_ );

	if( !absTableSpec )
		throw TableNotFoundException( __FILE__, __LINE__ );

	if( preparing_ )
	{
		dbsql_.currentStatement()->type( DROP_TABLE );
		dbsql_.currentStatement()->dropAts( absTableSpec );
	}

	processDrop( absTableSpec );

	cleanup();
}


void Parser::dropView( void )
{
	ViewSpecification *view;

	if( !viewedTablePrefix_ )
		view = new ViewSpecification( dbsql_, viewedTableName_, dbsql_.aHandle().userName() );
	else
		view = new ViewSpecification( dbsql_, viewedTableName_, viewedTablePrefix_ );

	if( !view )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	if( preparing_ )
	{
		dbsql_.currentStatement()->type( DROP_VIEW );
		dbsql_.currentStatement()->dropAts( view );
	}

	processDrop( view );
}


void Parser::positionedDelete( void )
{
	Cursor *cursor = findCursor();
	cursor->positionedDelete( baseTableName_, baseTablePrefix_, preparing_ );
	if( !preparing_ )
		cleanup();
}


void Parser::searchedDelete( void )
{
	currentSelectExpression_->searchedDelete( preparing_ );
	if( !preparing_ )
		cleanup();
}


//
//  at entry:
//
//  Class Parser members viewedTableName_/viewedTablePrefix_ contain the view name.
//
//  members of selectExpression contain the view's query.
//
void Parser::createView( void )
{
	NI rc;
	UNI numberOfSets, size;
	pSelectExpression _select;
	pStringListElement vcn;
	pColumn column;

	rc = CQL_FAILURE;

	for( _select = dbsql_.workingSets().first(), numberOfSets = 0; _select; _select = dbsql_.workingSets().next(), numberOfSets++ )
		_select->processTablesAndColumns();

	//
	//  if there are no explicit view column names, create the implicit view column name list
	//
	if( !viewColumnNames_.size() )
	{
		_select = dbsql_.workingSets().first();
		for( column = _select->columns().first(); column; column = _select->columns().next() )
		{
			vcn = new StringListElement;
			if( !vcn )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			vcn->s() = column->ColumnExpression().columns().first()->Name();
			viewColumnNames_.add( vcn );
		}
	}

	TempBuffer buffer( dbsql_.aHandle() );

	//
	//  scalar values:
	//    NI checkOption_
	//
	size = sizeof( NI );

	size += viewColumnNames_.dictionaryLength();
	size += dbsql_.workingSets().DictionaryLength();

	if( buffer.setBuffer( size ) == CQL_FAILURE )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	buffer << checkOption_;

	viewColumnNames_.writeDictionaryInformation( buffer );
	dbsql_.workingSets().writeDictionaryInformation( buffer );

	if( preparing_ == CQL_YES )
	{
		dbsql_.currentStatement()->type( CREATE_VIEW );
		dbsql_.currentStatement()->createBuffer( &buffer );
		dbsql_.currentStatement()->viewedTableName() = viewedTableName_;
		if( !viewedTablePrefix_ )
			dbsql_.currentStatement()->viewedTablePrefix() = dbsql_.aHandle().userName();
		else
			dbsql_.currentStatement()->viewedTablePrefix() = viewedTablePrefix_;
		//
		//  everything we need has been saved, so cleanup is O.K. here
		//
		cleanup();
		return;
	}

	if( !viewedTablePrefix_ )
		createViewPart2( viewedTableName_, dbsql_.aHandle().userName(), &buffer );
	else
		createViewPart2( viewedTableName_, viewedTablePrefix_, &buffer );

	cleanup();
}


void Parser::createViewPart2( CqlString& viewName, CqlString& viewPrefix, pTempBuffer buffer )
{
	dbsql_.addDictionaryEntry( viewName, viewPrefix, buffer );
}


void Parser::createTable( void )
{
	pTableSpecification table;

	if( !baseTablePrefix_ )
		table = new TableSpecification( dbsql_, baseTableName_, dbsql_.aHandle().userName() );
	else
		table = new TableSpecification( dbsql_, baseTableName_, baseTablePrefix_ );
	if( !table )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	tableCheckCondition_.instructions().move( table->checkCondition().instructions() );
	tableCheckCondition_.columns().move( table->checkCondition().columns() );
	dbsql_.workingSets().current()->createTable( table, &indices_, &foreignKeys_, preparing_ );

	if( !baseTablePrefix_ )
	{
		if( dbsql_.activeTables().AddIndexNode( &dbsql_, baseTableName_, dbsql_.aHandle().userName(), table ) == CQL_FAILURE )
			throw InternalErrorException( __FILE__, __LINE__ );
	}
	else
	{
		if( dbsql_.activeTables().AddIndexNode( &dbsql_, baseTableName_, baseTablePrefix_, table ) == CQL_FAILURE )
			throw InternalErrorException( __FILE__, __LINE__ );
	}

	if( !preparing_ )
		cleanup();
}


void Parser::createIndex( void )
{
	pSelectExpression selectExpression = dbsql_.workingSets().current();
	selectExpression->createIndex( creatingUniqueIndex_, indexName_, preparing_ );
	if( !preparing_ )
		cleanup();
}


void Parser::alterTable( void )
{
	SelectExpression *selectExpression = dbsql_.workingSets().current();
	selectExpression->alterTable( preparing_ );
	if( !preparing_ )
		cleanup();
}


void Parser::optionValue( char *val )
{
	if( optionValue_ )
		delete optionValue_;
	optionValue_ = new CqlString( val );
}

UIWithLeadingZeros *Parser::createUiwz( char *input )
{
	UIWithLeadingZeros *uiw = new UIWithLeadingZeros;
	if( !uiw )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	if( !input )
	{
		uiw->val = 0;
		uiw->lzs = -1;
	}
	else
	{
		sscanf( input, "%u", &uiw->val );
		uiw->lzs = 0;
		char *p;
		for( p = input; *p && *p == '0'; p++ )
			uiw->lzs++;
	}

	return uiw;
}
