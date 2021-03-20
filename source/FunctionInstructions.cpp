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


AbsFunctionInstruction::AbsFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


AbsFunctionInstruction::~AbsFunctionInstruction( void )
{
}


void AbsFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;

	val = exp.ves().popValue();

	if( !val->isNumeric() )
	{
		delete val;
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	if( AbsoluteValue( val ) == CQL_FAILURE )
	{
		delete val;
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	exp.ves().pushValue( val );
}


void AcosFunctionInstruction::execute( Expression& exp )
{
	executeFloatFunction( exp, clibArcCosine );
}


AcosFunctionInstruction::AcosFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


AcosFunctionInstruction::~AcosFunctionInstruction( void )
{
}


AsciiFunctionInstruction::AsciiFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


AsciiFunctionInstruction::~AsciiFunctionInstruction( void )
{
}


void AsciiFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pStringElement stringEl;
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();

	CqlColumnType ctype = val->dataType().typeType();
	if( ctype == CQL_CHAR || ctype == CQL_CHARUC )
	{
		delete val;
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	ile = new IntegerLiteralElement;
	if( !ile )
	{
		delete val;
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	stringEl = ((pStringElement)val);

	const char * const p = stringEl->str().text();
	Cql_Integer& integer = dynamic_cast< Cql_Integer& >( ile->value() );
	NI i = static_cast< NI >( p[0] );
	integer = Cql_Integer( i );
	delete val;
	val = ((pAbstractValueElement)0);
	exp.ves().pushValue( ile );
}


void AsciiFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


void AsinFunctionInstruction::execute( Expression& exp )
{
	executeFloatFunction( exp, clibArcSin );
}


AsinFunctionInstruction::AsinFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


AsinFunctionInstruction::~AsinFunctionInstruction( void )
{
}


Atan2FunctionInstruction::Atan2FunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


Atan2FunctionInstruction::~Atan2FunctionInstruction( void )
{
}


void Atan2FunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1 = ((pAbstractValueElement)0), val2 = ((pAbstractValueElement)0);
	pNumericLiteralElement numericEl1;
	D result, arg1, arg2;

	val2 = exp.ves().popValue();
	arg2 = extractFloatArgument( val2 );
	val1 = exp.ves().popValue();
	arg1 = extractFloatArgument( val1 );
	result = atan2( arg1, arg2 );
	numericEl1 = ((pNumericLiteralElement)val1);
	Cql_Float& f = dynamic_cast< Cql_Float& >( numericEl1->value() );
	f = PrimitiveFloat( result );
	delete val2;
	val2 = ((pAbstractValueElement)0);
	exp.ves().pushValue( val1 );
}


AtanFunctionInstruction::AtanFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


AtanFunctionInstruction::~AtanFunctionInstruction( void )
{
}


void AtanFunctionInstruction::execute( Expression& exp )
{
	executeFloatFunction( exp, clibArcTangent );
}


AvgFunctionInstruction::AvgFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


AvgFunctionInstruction::~AvgFunctionInstruction( void )
{
}


void AvgFunctionInstruction::executePost( Expression& exp )
{
	pAbstractValueElement val, tval;

	val = new IntegerLiteralElement;
	if( !val )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Integer& iv = dynamic_cast< Cql_Integer& >( dynamic_cast< IntegerLiteralElement* >( val )->value() );
	iv = Cql_Integer( exp.count() );

	bool switched;
	makeTypesCompatible( switched, &val, exp.pFunctionSpace() );
	if( switched )
	{
		tval = val;
		val = exp.functionSpace();
		exp.functionSpace( tval );
	}

	*exp.functionSpace() /= *val;

	delete val;
	exp.copyFunctionSpaceToValue();
}


void AvgFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;

	if( exp.aggregateDistinctScan() )
		throw InternalErrorException( __FILE__, __LINE__ );

	val = aggregatePopAndConvert( &exp );

	if( !val->isNull() )
	{
		*exp.functionSpace() += *val;

		exp.incrementCount();
		*val = *exp.functionSpace();
	}

	exp.ves().pushValue( val );
}


CeilingFunctionInstruction::CeilingFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


CeilingFunctionInstruction::~CeilingFunctionInstruction( void )
{
}


void CeilingFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;

	val = exp.ves().popValue();

	if( !val->isNumeric() )
	{
		delete val;
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	val = convertToInteger( val, AbstractType::ROUND_UP );
	exp.ves().pushValue( val );
}


CharFunctionInstruction::CharFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


CharFunctionInstruction::~CharFunctionInstruction( void )
{
}


void CharFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pStringElement stringEl;
	L arg;
	NC p[ 2 ];

	val = exp.ves().popValue();
	arg = extractIntegerArgument( val );
	stringEl = new StringElement();
	if( !stringEl )
	{
		delete val;
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	p[1] = 0;
	p[0] = ((NC)arg);
	stringEl->str() = p;
	exp.ves().pushValue( stringEl );
}


void CharFunctionInstruction::promote( Expression& exp, bool )
{
	exp.forceExpressionType( CQL_INTEGER );
}


ConcatFunctionInstruction::ConcatFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


ConcatFunctionInstruction::~ConcatFunctionInstruction( void )
{
}


void ConcatFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1 = ((pAbstractValueElement)0), val2 = ((pAbstractValueElement)0);
	pStringElement stringEl1, stringEl2, stringEl3 = ((pStringElement)0);

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	CqlColumnType ctype1 = val1->dataType().typeType();
	CqlColumnType ctype2 = val2->dataType().typeType();
	if( (ctype1 != CQL_CHAR && ctype1 != CQL_CHARUC) || (ctype2 != CQL_CHAR && ctype2 != CQL_CHARUC ))
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	stringEl3 = new StringElement();
	if( !stringEl3 )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	stringEl1 = ((pStringElement)val1);
	stringEl2 = ((pStringElement)val2);

	stringEl3->value() = stringEl1->value();
	stringEl3->value() += stringEl2->value();

	delete val1;
	val1 = ((pAbstractValueElement)0);
	delete val2;
	val2 = ((pAbstractValueElement)0);

	exp.ves().pushValue( stringEl3 );
}


void ConcatFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}


ConvertFunctionInstruction::ConvertFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


ConvertFunctionInstruction::~ConvertFunctionInstruction( void )
{
}


void ConvertFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val2, val1, convertedValue;
	L ltype;
	CqlColumnTypes type;

	val2 = exp.ves().popValue();
	ltype = extractIntegerArgument( val2 );
	CqlColumnType ctype = static_cast< CqlColumnType >( ltype );
	type = CqlColumnTypes( ctype );

	val1 = exp.ves().popValue();

	if( !val1->expressionCompatible( type ) )
	{
		convertedValue = AbstractValueElement::convert( val1, ((CqlColumnTypes)type) );
		val1 = convertedValue;
	}

	exp.ves().pushValue( val1 );
}


CosFunctionInstruction::CosFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


CosFunctionInstruction::~CosFunctionInstruction( void )
{
}


void CosFunctionInstruction::execute( Expression& exp )
{
	executeFloatFunction( exp, clibCosine );
}


CotFunctionInstruction::CotFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


CotFunctionInstruction::~CotFunctionInstruction( void )
{
}


void CotFunctionInstruction::execute( Expression& exp )
{
	executeFloatFunction( exp, clibTangent, CQL_YES );
}


CountColumnFunctionInstruction::CountColumnFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


CountColumnFunctionInstruction::~CountColumnFunctionInstruction( void )
{
}


void CountColumnFunctionInstruction::execute( Expression& exp )
{
	pIntegerLiteralElement integerEl;
	pAbstractValueElement val;

	if( exp.aggregateDistinctScan() )
		return;

	val = exp.ves().popValue();
	
	if( !exp.functionSpace() )
		exp.allocateFunctionSpace( CQL_INTEGER );

	integerEl = ((pIntegerLiteralElement)exp.functionSpace());

	if( !val->isNull() )
		exp.incrementCount();

	delete val;

	dynamic_cast< Cql_Integer& >( integerEl->value() ) = Cql_Integer( exp.count() );

	exp.pushFunctionSpace();
}


void CountColumnFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.uniqueScanType( exp.valueExpressionType() );
	exp.uniqueScanLength( exp.valueExpressionLength() );
	exp.forceExpressionType( CQL_INTEGER );
}


CountStarFunctionInstruction::CountStarFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


CountStarFunctionInstruction::~CountStarFunctionInstruction( void )
{
}


void CountStarFunctionInstruction::execute( Expression& exp )
{
	pIntegerLiteralElement integerEl;

	if( !exp.functionSpace() )
		exp.allocateFunctionSpace( CQL_INTEGER );

	integerEl = ((pIntegerLiteralElement)exp.functionSpace());

	exp.incrementCount();

	dynamic_cast< Cql_Integer& >( integerEl->value() ) = Cql_Integer( exp.count() );

	exp.pushFunctionSpace();
}


void CountStarFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


CurdateFunctionInstruction::CurdateFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


CurdateFunctionInstruction::~CurdateFunctionInstruction( void )
{
}


void CurdateFunctionInstruction::execute( Expression& exp )
{
	pDateLiteralElement dle;

	dle = new DateLiteralElement;
	if( !dle )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Date& cqldate = dynamic_cast< Cql_Date& >( dle->value() );
	DateValue dv = cqldate.instance().value();
	dv.setToCurrentDate();
	exp.ves().pushValue( dle );
}


void CurdateFunctionInstruction::promote( Expression& exp, bool /*workingtype*/ )
{
	exp.forceExpressionType( CQL_DATE );
}


CurtimeFunctionInstruction::CurtimeFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


CurtimeFunctionInstruction::~CurtimeFunctionInstruction( void )
{
}


void CurtimeFunctionInstruction::execute( Expression& exp )
{
	pTimeLiteralElement tle;

	tle = new TimeLiteralElement;
	if( !tle )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	TimeValue& ttime = dynamic_cast< Cql_Time& > ( tle->value() ).instance().value();
	ttime.setToCurrentTime();
	exp.ves().pushValue( tle );
}


void CurtimeFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_TIME );
}


DatabaseFunctionInstruction::DatabaseFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


DatabaseFunctionInstruction::~DatabaseFunctionInstruction( void )
{
}


void DatabaseFunctionInstruction::execute( Expression& exp )
{
	//  we return the same name for user and database
	pStringElement stringEl;

	stringEl = new StringElement();
	if( !stringEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	stringEl->str() = exp.dbsql().aHandle().userName();
	exp.ves().pushValue( stringEl );
}


void DatabaseFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}


DayOfMonthFunctionInstruction::DayOfMonthFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


DayOfMonthFunctionInstruction::~DayOfMonthFunctionInstruction( void )
{
}


void DayOfMonthFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val = ((pAbstractValueElement)0);
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();

	DateValue *date = extractDateArgument( val );

	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	IntegerValue& integer = dynamic_cast< Cql_Integer& >( ile->value() ).instance().value();
	integer = date->day();
	exp.ves().pushValue( ile );
}


void DayOfMonthFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


DayOfWeekFunctionInstruction::DayOfWeekFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


DayOfWeekFunctionInstruction::~DayOfWeekFunctionInstruction( void )
{
}


void DayOfWeekFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();
	DateValue *date = extractDateArgument( val );
	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	IntegerValue& integer = dynamic_cast< Cql_Integer& >( ile->value() ).instance().value();
	integer = date->dayOfWeek();
	exp.ves().pushValue( ile );
}


void DayOfWeekFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


DayOfYearFunctionInstruction::DayOfYearFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


DayOfYearFunctionInstruction::~DayOfYearFunctionInstruction( void )
{
}


void DayOfYearFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();
	DateValue *date = extractDateArgument( val );
	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	IntegerValue& integer = dynamic_cast< Cql_Integer& >( ile->value() ).instance().value();
	integer = date->dayOfYear();
	exp.ves().pushValue( ile );
}


void DayOfYearFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


ExpFunctionInstruction::ExpFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


ExpFunctionInstruction::~ExpFunctionInstruction( void )
{
}


void ExpFunctionInstruction::execute( Expression& expression )
{
	executeFloatFunction( expression, clibExponential );
}


FloorFunctionInstruction::FloorFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


FloorFunctionInstruction::~FloorFunctionInstruction( void )
{
}


void FloorFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;

	val = exp.ves().popValue();

	if( !val->isNumeric() )
	{
		delete val;
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	val = convertToInteger( val, AbstractType::ROUND_DOWN );
	exp.ves().pushValue( val );
}


FunctionInstruction::FunctionInstruction( SqlHandle& _dbsql ) : Instruction( _dbsql ), numberOfArguments( 0 )
{
}


FunctionInstruction::~FunctionInstruction( void )
{
}


Instruction& FunctionInstruction::operator = ( const Instruction& cins )
{
	Instruction& ins = const_cast< Instruction& >( cins );
	FunctionInstruction& other = dynamic_cast< FunctionInstruction& >( ins );
	numberOfArguments = other.numberOfArguments;
	return *this;
}


FunctionInstruction *FunctionInstruction::createFunctionInstruction( SqlHandle& _dbsql, Functions funcId, UNI nArgs )
{
	FunctionInstruction *fins;
	switch( funcId )
	{
	case FUNC_COUNT1 :
		fins = new CountStarFunctionInstruction( _dbsql );
		break;

	case FUNC_COUNT2 :
		fins = new CountColumnFunctionInstruction( _dbsql );
		break;

	case FUNC_SUM :
		fins = new SumFunctionInstruction( _dbsql );
		break;

	case FUNC_AVG :
		fins = new AvgFunctionInstruction( _dbsql );
		break;

	case FUNC_MIN :
		fins = new MinFunctionInstruction( _dbsql );
		break;

	case FUNC_MAXIMUM :
		fins = new MaxFunctionInstruction( _dbsql );
		break;

	case FUNC_ASCII :
		fins = new AsciiFunctionInstruction( _dbsql );
		break;

	case FUNC_CHAR :
		fins = new CharFunctionInstruction( _dbsql );
		break;

	case FUNC_CONCAT :
		fins = new ConcatFunctionInstruction( _dbsql );
		break;

	case FUNC_INSERT :
		fins = new InsertFunctionInstruction( _dbsql );
		break;

	case FUNC_LEFT :
		fins = new LeftFunctionInstruction( _dbsql );
		break;

	case FUNC_LTRIM :
		fins = new LtrimFunctionInstruction( _dbsql );
		break;

	case FUNC_LENGTH :
		fins = new LengthFunctionInstruction( _dbsql );
		break;

	case FUNC_LOCATE :
		fins = new LocateFunctionInstruction( _dbsql );
		break;

	case FUNC_LCASE :
		fins = new LcaseFunctionInstruction( _dbsql );
		break;

	case FUNC_REPEAT :
		fins = new RepeatFunctionInstruction( _dbsql );
		break;

	case FUNC_REPLACE :
		fins = new ReplaceFunctionInstruction( _dbsql );
		break;

	case FUNC_RIGHT :
		fins = new RightFunctionInstruction( _dbsql );
		break;

	case FUNC_RTRIM :
		fins = new RtrimFunctionInstruction( _dbsql );
		break;

	case FUNC_SUBSTRING :
		fins = new SubstringFunctionInstruction( _dbsql );
		break;

	case FUNC_UCASE :
		fins = new UcaseFunctionInstruction( _dbsql );
		break;

	case FUNC_ABS :
		fins = new AbsFunctionInstruction( _dbsql );
		break;

	case FUNC_ACOS :
		fins = new AcosFunctionInstruction( _dbsql );
		break;

	case FUNC_ASIN :
		fins = new AsinFunctionInstruction( _dbsql );
		break;

	case FUNC_ATAN :
		fins = new AtanFunctionInstruction( _dbsql );
		break;

	case FUNC_ATAN2 :
		fins = new Atan2FunctionInstruction( _dbsql );
		break;

	case FUNC_CEILING :
		fins = new CeilingFunctionInstruction( _dbsql );
		break;

	case FUNC_COS :
		fins = new CosFunctionInstruction( _dbsql );
		break;

	case FUNC_COT :
		fins = new CotFunctionInstruction( _dbsql );
		break;

	case FUNC_EXP :
		fins = new ExpFunctionInstruction( _dbsql );
		break;

	case FUNC_FLOOR :
		fins = new FloorFunctionInstruction( _dbsql );
		break;

	case FUNC_LOG :
		fins = new LogFunctionInstruction( _dbsql );
		break;

	case FUNC_MOD :
		fins = new ModFunctionInstruction( _dbsql );
		break;

	case FUNC_PI :
		fins = new PiFunctionInstruction( _dbsql );
		break;

	case FUNC_RAND :
		fins = new RandFunctionInstruction( _dbsql );
		break;

	case FUNC_SIGN :
		fins = new SignFunctionInstruction( _dbsql );
		break;

	case FUNC_SIN :
		fins = new SinFunctionInstruction( _dbsql );
		break;

	case FUNC_SQRT :
		fins = new SqrtFunctionInstruction( _dbsql );
		break;

	case FUNC_TAN :
		fins = new TanFunctionInstruction( _dbsql );
		break;

	case FUNC_NOW :
		fins = new NowFunctionInstruction( _dbsql );
		break;

	case FUNC_CURDATE :
		fins = new CurdateFunctionInstruction( _dbsql );
		break;

	case FUNC_DAYOFMONTH :
		fins = new DayOfMonthFunctionInstruction( _dbsql );
		break;

	case FUNC_DAYOFWEEK :
		fins = new DayOfWeekFunctionInstruction( _dbsql );
		break;

	case FUNC_DAYOFYEAR :
		fins = new DayOfYearFunctionInstruction( _dbsql );
		break;

	case FUNC_MONTH :
		fins = new MonthFunctionInstruction( _dbsql );
		break;

	case FUNC_QUARTER :
		fins = new QuarterFunctionInstruction( _dbsql );
		break;

	case FUNC_WEEK :
		fins = new WeekFunctionInstruction( _dbsql );
		break;

	case FUNC_YEAR :
		fins = new YearFunctionInstruction( _dbsql );
		break;

	case FUNC_CURTIME :
		fins = new CurtimeFunctionInstruction( _dbsql );
		break;

	case FUNC_HOUR :
		fins = new HourFunctionInstruction( _dbsql );
		break;

	case FUNC_MINUTE :
		fins = new MinuteFunctionInstruction( _dbsql );
		break;

	case FUNC_SECOND :
		fins = new SecondFunctionInstruction( _dbsql );
		break;

	case FUNC_USER :
		fins = new UserFunctionInstruction( _dbsql );
		break;

	case FUNC_DATABASE :
		fins = new DatabaseFunctionInstruction( _dbsql );
		break;

	case FUNC_IFNULL :
		fins = new IfnullFunctionInstruction( _dbsql );
		break;

	case FUNC_CONVERT :
		fins = new ConvertFunctionInstruction( _dbsql );
		break;

	case NOT_A_FUNCTION :
	default :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	if( fins )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	fins->SetNumberOfArguments( nArgs );
	return fins;
}


AbstractValueElement *FunctionInstruction::aggregatePopAndConvert( Expression *exp )
{
	pAbstractValueElement val;

	val = exp->ves().popValue();

	if( !exp->functionSpace() )
		exp->allocateFunctionSpace( val->dataType() );

	if( !val->isNull() )
	{
		bool switched;
		makeTypesCompatible( switched, &val, exp->pFunctionSpace() );
		if( switched )
		{
			AbstractValueElement *tval = val;
			val = exp->functionSpace();
			exp->functionSpace( tval );
		}
	}

	return val;
}


void FunctionInstruction::buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList &stack )
{
	UNI loop;
	pAbstractPredicateOperand apop;
	pNonterminalPredicateOperand ntpop;
	pPredicate pred;

	for( loop = 0; loop < NumberOfArguments(); loop++ )
	{
		apop = stack.pop();
		if( !apop )
			throw StackUnderflowException( __FILE__, __LINE__ );
	}

	pred = new Predicate( dbsql() );
	if( !pred )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	pred->ins( this );

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


void FunctionInstruction::processViewData( SelectExpressionList& )
{
}


US FunctionInstruction::dictionaryLength( void )
{
	return sizeof( numberOfArguments );
}


void FunctionInstruction::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << numberOfArguments;
}


void FunctionInstruction::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> numberOfArguments;
}


HourFunctionInstruction::HourFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


HourFunctionInstruction::~HourFunctionInstruction( void )
{
}


void HourFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val = ((pAbstractValueElement)0);
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();

	TimeValue *time = extractTimeArgument( val );
	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	IntegerValue& integer = dynamic_cast< Cql_Integer& >( ile->value() ).instance().value();
	integer = time->hour();
	exp.ves().pushValue( ile );
}


void HourFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


IfnullFunctionInstruction::IfnullFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


IfnullFunctionInstruction::~IfnullFunctionInstruction( void )
{
}


void IfnullFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	if( !val1->isNull() )
	{
		delete val1;
		val1 = ((pAbstractValueElement)0);
		exp.ves().pushValue( val2 );
	}
	else
	{
		delete val2;
		val2 = ((pAbstractValueElement)0);
		exp.ves().pushValue( val1 );
	}
}


InsertFunctionInstruction::InsertFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


InsertFunctionInstruction::~InsertFunctionInstruction( void )
{
}


void InsertFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1 = ((pAbstractValueElement)0);
	pAbstractValueElement val2 = ((pAbstractValueElement)0);
	pAbstractValueElement val3 = ((pAbstractValueElement)0);
	pAbstractValueElement val4 = ((pAbstractValueElement)0);
	pStringElement stringEl1, stringEl2, stringEl3 = ((pStringElement)0), stringToPush;
	L start, length;
	pNC pi, ptemp;
	NI string1TooSmall, deleteval1;
	UNI loop;

	val4 = exp.ves().popValue();
	val3 = exp.ves().popValue();

	length = extractIntegerArgument( val3 );
	val3 = 0;

	val2 = exp.ves().popValue();

	start = extractIntegerArgument( val2 );
	val2 = 0;

	val1 = exp.ves().popValue();

	CqlColumnType ctype1 = val1->dataType().typeType();
	CqlColumnType ctype4 = val4->dataType().typeType();
	if( (ctype1 != CQL_CHAR && ctype1 != CQL_CHARUC) || (ctype4 != CQL_CHAR && ctype4 != CQL_CHARUC))
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	stringEl1 = ((pStringElement)val1);
	stringEl2 = ((pStringElement)val4);
	const char * const p1 = stringEl1->str().text();
	const char * p2 = const_cast<const char *>( stringEl2->str().text() );

	//
	//  is there room in string 1 for bleLength characters starting at bleStart?
	//
	if( ((L)strlen( p1 )) < start + length )
		string1TooSmall = CQL_YES;
	else
		string1TooSmall = CQL_NO;

	if( string1TooSmall == CQL_NO )
	{
		pi = const_cast<char*>( p1 + start );
		for( loop = 0; loop < ((UNI)length); loop++ )
			*pi++ = *p2++;

		stringToPush = stringEl1;
		deleteval1 = CQL_NO;
	}
	else
	{
		deleteval1 = CQL_YES;
		stringEl3 = new StringElement();
		if( !stringEl3 )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		ptemp = new NC[ start + length + 1 ];
		if( !ptemp )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		memcpy( ptemp, p1, ((UNI)start) );
		memcpy( ptemp + start, p2, ((UNI)length) );
		stringEl3->str() = ptemp;
		delete [] ptemp;
		stringToPush = stringEl3;
	}

	exp.ves().pushValue( stringToPush );

	if( deleteval1 == CQL_YES )
		delete val1;
	delete val4;
}


void InsertFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}


LcaseFunctionInstruction::LcaseFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


LcaseFunctionInstruction::~LcaseFunctionInstruction( void )
{
}


void LcaseFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pStringElement stringEl;
	UNI length, loop;

	val = exp.ves().popValue();

	stringEl = ((pStringElement)val);
	char * p = const_cast<char *>(stringEl->str().text());
	length = stringEl->str().length();

	for( loop = 0; loop < length; loop++, p++ )
		if( *p >= 'A' && *p <= 'Z' )
			(*p) += ((NC)0x20);

	exp.ves().pushValue( stringEl );
}


void LcaseFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}


LeftFunctionInstruction::LeftFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


LeftFunctionInstruction::~LeftFunctionInstruction( void )
{
}


void LeftFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1 = ((pAbstractValueElement)0), val2 = ((pAbstractValueElement)0);
	pStringElement stringEl;
	L count;
	pNC ptemp;

	val2 = exp.ves().popValue();

	count = extractIntegerArgument( val2 );
	val2 = 0;

	val1 = exp.ves().popValue();

	stringEl = ((pStringElement)val1);

	CqlColumnType ctype = val1->dataType().typeType();
	if( ctype != CQL_CHAR && ctype != CQL_CHARUC )
		throw IncompatibleTypesException( __FILE__, __LINE__ );

	ptemp = new NC[ count + 1 ];
	if( !ptemp )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	memset( ptemp, 0,  ((UNI)( count + 1 ) ) );
	memcpy( ptemp, stringEl->str().text(), ((UNI)count) );
	stringEl->str() = ptemp;
	delete [] ptemp;
	exp.ves().pushValue( stringEl );
}


void LeftFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


LengthFunctionInstruction::LengthFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


LengthFunctionInstruction::~LengthFunctionInstruction( void )
{
}


void LengthFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pStringElement stringEl;
	pIntegerLiteralElement ile;
	UNI length;

	val = exp.ves().popValue();

	stringEl = ((pStringElement)val);
	length = stringEl->str().length();
	delete val;

	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	IntegerValue ival;
	ival = length;
	*ile = ival;

	exp.ves().pushValue( ile );
}


void LengthFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


LocateFunctionInstruction::LocateFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


LocateFunctionInstruction::~LocateFunctionInstruction( void )
{
}


void LocateFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1 = ((pAbstractValueElement)0), val2 = ((pAbstractValueElement)0), val3 = ((pAbstractValueElement)0);
	pStringElement stringEl1, stringEl2;
	const char *p1;
	L start;
	UNI _position, _length;
	NI foundIt;


	if( NumberOfArguments() == 3 )
	{
		val3 = exp.ves().popValue();
		start = extractIntegerArgument( val3 );
	}
	else
		start = 0;

	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	stringEl2 = ((pStringElement)val2);
	stringEl1 = ((pStringElement)val1);
	const char * const p2 = stringEl2->str().text();

	_position = ((UNI)start);
	_length = strlen( p2 );

	for( p1 = const_cast<const char *>(stringEl1->str().text() + start), foundIt = CQL_NO;
		 *p1 && foundIt == CQL_NO;
		 p1++, _position++ )
		if( !memcmp( p1, p2, _length ) )
			foundIt = CQL_YES;

	delete val2;
	delete val1;

	if( foundIt == CQL_NO )
		_position = 0;
	else
		_position++;

	IntegerValue i( _position );

	IntegerLiteralElement *ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	*ile = i;

	exp.ves().pushValue( ile );
}


void LocateFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


LogFunctionInstruction::LogFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


LogFunctionInstruction::~LogFunctionInstruction( void )
{
}


void LogFunctionInstruction::execute( Expression& exp )
{
	executeFloatFunction( exp, clibLogorithm );
}


LtrimFunctionInstruction::LtrimFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


LtrimFunctionInstruction::~LtrimFunctionInstruction( void )
{
}


void LtrimFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val = ((pAbstractValueElement)0);
	pStringElement stringEl;
	pNC ptemp, p;

	val = exp.ves().popValue();

	stringEl = ((pStringElement)val);

	//
	//  if string has no leading spaces, there is nothing to do
	//
	if( *( stringEl->str().text() ) != ' ' )
	{
		exp.ves().pushValue( val );
		return;
	}

	ptemp = new NC[ stringEl->str().length() + 1 ];
	if( !ptemp )
	{
		delete val;
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	memset( ptemp, 0, stringEl->str().length() + 1 );
	memcpy( ptemp, stringEl->str().text(), stringEl->str().length() );

	//
	//  find the first non-space character
	//
	for( p = ptemp; *p && *p == ' '; p++ )
		;

	stringEl->str() = p;
	delete [] ptemp;
	exp.ves().pushValue( stringEl );
}


void LtrimFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}

	
MaxFunctionInstruction::MaxFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


MaxFunctionInstruction::~MaxFunctionInstruction( void )
{
}


void MaxFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;

	if( exp.aggregateDistinctScan() )
		return;

	val = aggregatePopAndConvert( &exp );

	if( !val->isNull() )
	{
		if( exp.functionSpace()->isNull() )
			*exp.functionSpace() = *val;
		else if( *exp.functionSpace() > *val )
			*val = *exp.functionSpace();
		else
			*exp.functionSpace() = *val;
	}

	exp.ves().pushValue( val );
}

	
MinFunctionInstruction::MinFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


MinFunctionInstruction::~MinFunctionInstruction( void )
{
}


void MinFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;

	if( exp.aggregateDistinctScan() )
		return;

	val = aggregatePopAndConvert( &exp );

	if( !val->isNull() )
	{
		if( exp.functionSpace()->isNull() )
			*exp.functionSpace() = *val;
		else if( *exp.functionSpace() < *val )
			*val = *exp.functionSpace();
		else
			*exp.functionSpace() = *val;
	}

	exp.ves().pushValue( val );
}


MinuteFunctionInstruction::MinuteFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


MinuteFunctionInstruction::~MinuteFunctionInstruction( void )
{
}


void MinuteFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val = ((pAbstractValueElement)0);
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();

	TimeValue *time = extractTimeArgument( val );
	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	IntegerValue& integer = dynamic_cast< Cql_Integer& >( ile->value() ).instance().value();
	integer = time->minute();
	exp.ves().pushValue( ile );
}


void MinuteFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


ModFunctionInstruction::ModFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


ModFunctionInstruction::~ModFunctionInstruction( void )
{
}


void ModFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1 = ((pAbstractValueElement)0), val2 = ((pAbstractValueElement)0);
	pIntegerLiteralElement ile = ((pIntegerLiteralElement)0);
	L arg1, arg2;
	UNI result;

	val2 = exp.ves().popValue();

	arg2 = extractIntegerArgument( val2 );
	val1 = exp.ves().popValue();
	arg1 = extractIntegerArgument( val1 );
	result = ((UNI)( arg1 - ( ( arg1 / arg2 ) * arg2 ) ) );

	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	IntegerValue& integer = dynamic_cast< Cql_Integer& >( ile->value() ).instance().value();
	integer = result;

	exp.ves().pushValue( ile );
}


MonthFunctionInstruction::MonthFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


MonthFunctionInstruction::~MonthFunctionInstruction( void )
{
}


void MonthFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val = ((pAbstractValueElement)0);
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();

	DateValue *date = extractDateArgument( val );

	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	IntegerValue& integer = dynamic_cast< Cql_Integer& >( ile->value() ).instance().value();
	integer = date->month();
	exp.ves().pushValue( ile );
}


void MonthFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


NowFunctionInstruction::NowFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


NowFunctionInstruction::~NowFunctionInstruction( void )
{
}


void NowFunctionInstruction::execute( Expression& exp )
{
	pTimestampLiteralElement tle;

	tle = new TimestampLiteralElement;
	if( !tle )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	TimestampValue& timestamp = dynamic_cast< Cql_Timestamp& >( tle->value() ).instance().value();
	timestamp.setToCurrentTimestamp();
	exp.ves().pushValue( tle );
}


void NowFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_TIMESTAMP );
}


PiFunctionInstruction::PiFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


PiFunctionInstruction::~PiFunctionInstruction( void )
{
}


void PiFunctionInstruction::execute( Expression& exp )
{
	pFloatLiteralElement fle;

	fle = new FloatLiteralElement;
	if( !fle )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Float& fl = dynamic_cast< Cql_Float& >( fle->value() );
	fl = 3.141592654;
	exp.ves().pushValue( fle );
}


void PiFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_FLOAT );
}


QuarterFunctionInstruction::QuarterFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


QuarterFunctionInstruction::~QuarterFunctionInstruction( void )
{
}


void QuarterFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val = ((pAbstractValueElement)0);
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();

	DateValue *dv = extractDateArgument( val );

	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Integer& integer = dynamic_cast< Cql_Integer& >( ile->value() );
	integer.instance().value() = dv->quarter();
	exp.ves().pushValue( ile );
}


void QuarterFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


RandFunctionInstruction::RandFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


RandFunctionInstruction::~RandFunctionInstruction( void )
{
}


void RandFunctionInstruction::execute( Expression& exp )
{
	UNI seed;
	NI result;
	L lseed;
	pAbstractValueElement val;
	pIntegerLiteralElement ileResult;

	val = exp.ves().popValue();

	lseed = extractIntegerArgument( val );
	seed = ((UNI)lseed);
	srand( seed );
	result = rand();

	ileResult = new IntegerLiteralElement;
	if( !ileResult )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Integer& integerResult = dynamic_cast< Cql_Integer& >( ileResult->value() );
	integerResult.instance().value() = result;
	exp.ves().pushValue( ileResult );
}


void RandFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_FLOAT );
}


RepeatFunctionInstruction::RepeatFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


RepeatFunctionInstruction::~RepeatFunctionInstruction( void )
{
}


void RepeatFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}


void RepeatFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2;
	pStringElement stringEl;
	pNC ptemp, pdest;
	UNI spaceNeeded, stringLength;
	L count, loop;

	val2 = exp.ves().popValue();
	count = extractIntegerArgument( val2 );
	val1 = exp.ves().popValue();
	stringEl = ((pStringElement)val1);
	stringLength = stringEl->str().length();
	spaceNeeded = ((UNI)( ( stringLength * count ) + 1 ) );
	ptemp = new NC[ spaceNeeded ];
	if( !ptemp )
	{
		delete val1;
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	memset( ptemp, 0, sizeof( ptemp ) );
	pdest = ptemp;
	const char * const psource = stringEl->str().text();

	for( loop = 0; loop < count; loop++ )
	{
		memcpy( pdest, psource, stringLength );
		pdest += stringLength;
	}

	stringEl->str() = ptemp;
	delete [] ptemp;
	exp.ves().pushValue( stringEl );
}


ReplaceFunctionInstruction::ReplaceFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


ReplaceFunctionInstruction::~ReplaceFunctionInstruction( void )
{
}


void ReplaceFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2 = ((pAbstractValueElement)0), val3 = ((pAbstractValueElement)0);
	pStringElement stringEl1, stringEl2, stringEl3;
	pNC p1, p2, p3, ptemp1 = ((pNC)0), ptemp2 = ((pNC)0), ptemp3 = ((pNC)0), ptemp4 = ((pNC)0);
	UNI length1, length2, length3, remainingLength, currentLength, lengthPart1;
	NI replaceDelta = 0, noRealloc, anyChanges;

	val3 = exp.ves().popValue();
	val2 = exp.ves().popValue();
	val1 = exp.ves().popValue();

	stringEl1 = ((pStringElement)val1);
	stringEl2 = ((pStringElement)val2);
	stringEl3 = ((pStringElement)val3);

	length1 = stringEl1->str().length();
	length2 = stringEl2->str().length();
	length3 = stringEl3->str().length();

	ptemp1 = new NC[ length1 + 1 ];
	if( !ptemp1 )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memset( ptemp1, 0, length1 + 1 );
	memcpy( ptemp1, stringEl1->str().text(), length1 );
	p1= ptemp1;

	ptemp2 = new NC[ length2 + 1 ];
	if( !ptemp2 )
	{
		delete [] ptemp1;
		delete val1;
		delete val2;
		delete val3;
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	memset( ptemp2, 0, length2 + 1 );
	memcpy( ptemp2, stringEl2->str().text(), length2 );
	p2= ptemp2;

	ptemp3 = new NC[ length3 + 1 ];
	if( !ptemp3 )
	{
		delete val1;
		delete val2;
		delete val3;
		delete [] ptemp1;
		delete [] ptemp2;
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	memset( ptemp3, 0, length3 + 1 );
	memcpy( ptemp3, stringEl3->str().text(), length3 );
	p3= ptemp3;

	//
	//  how much does the length of the string change due to a replacement?
	//
	if( length2 > length1 )
	{
		//  string 2 cannot occur inside string1
		exp.ves().pushValue( stringEl1 );
		delete val2;
		delete val3;
		delete [] ptemp1;
		delete [] ptemp2;
		delete [] ptemp3;
		return;
	}

	if( length2 == length3 )
		noRealloc = CQL_YES;
	else
	{
		noRealloc = CQL_NO;
		replaceDelta = length3 - length2;
	}
	currentLength = length1;
	anyChanges = CQL_NO;

	for( remainingLength = length1; remainingLength >= length2; remainingLength-- )
	{
		if( !memcmp( p1, p2, length2 ) )
		{
			anyChanges = CQL_YES;
			if( noRealloc == CQL_YES )
				memcpy( p1, p3, length3 );
			else
			{
				//
				//  size of string changes
				//
				currentLength += replaceDelta;
				ptemp4 = new NC[ currentLength ];
				if( !ptemp4 )
				{
					delete val1;
					delete val2;
					delete val3;
					delete [] ptemp1;
					delete [] ptemp2;
					delete [] ptemp3;
					throw MemoryAllocationException( __FILE__, __LINE__ );
				}
				lengthPart1 = length1 - remainingLength;
				memcpy( ptemp4, ptemp1, lengthPart1 );
				memcpy( ptemp4 + lengthPart1, p3, length3 );
				memcpy( ptemp4 + lengthPart1 + length3, ptemp1 + lengthPart1 + length2, remainingLength - length2 );
				delete [] ptemp1;
				ptemp1 = ptemp4;
				ptemp4 = ((pNC)0);
				remainingLength += replaceDelta;
			}
			p1++;
		}
	}

	if( anyChanges == CQL_YES )
		stringEl1->str() = ptemp1;

	exp.ves().pushValue( stringEl1 );

	delete val2;
	delete val3;
	delete [] ptemp1;
	delete [] ptemp2;
	delete [] ptemp3;
}


void ReplaceFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}


RightFunctionInstruction::RightFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


RightFunctionInstruction::~RightFunctionInstruction( void )
{
}


void RightFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1, val2 = ((pAbstractValueElement)0);
	pStringElement stringEl;
	L count;
	UNI originalLength;
	pNC ptemp;

	val2 = exp.ves().popValue();
	count = extractIntegerArgument( val2 );
	val1 = exp.ves().popValue();
	stringEl = ((pStringElement)val1);
	
	ptemp = new NC[ count + 1 ];
	if( !ptemp )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	memset( ptemp, 0, ((UNI)( count + 1 ) ) );

	originalLength = stringEl->str().length();
	if( count > ((L)originalLength) )
	{
		delete [] ptemp;
		throw InvalidLengthInStringFunctionException( __FILE__, __LINE__ );
	}

	memcpy( ptemp, stringEl->str().text() + (originalLength - count), ((UNI)count) );
	stringEl->str() = ptemp;

	exp.ves().pushValue( stringEl );

	delete val2;
	delete [] ptemp;
}


void RightFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


RtrimFunctionInstruction::RtrimFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


RtrimFunctionInstruction::~RtrimFunctionInstruction( void )
{
}


void RtrimFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val = ((pAbstractValueElement)0);
	pStringElement stringEl;
	NI length, loop;
	pNC ptemp;

	val = exp.ves().popValue();

	stringEl = ((pStringElement)val);
	length = ((NI)stringEl->str().length());
	const char * const p = stringEl->str().text();
	if( p[ length - 1 ] != ' ' )
	{
		//  there are no trailing spaces
		exp.ves().pushValue( stringEl );
		return;
	}

	//
	//  still here, so the last character is a space.  Find the last non-space character
	//

	for( loop = length - 2; loop >= 0; loop-- )
		if( p[ loop ] != ' ' )
			break;

	if( loop < 0 )
		//  the whole thing is spaces
		stringEl->str() = "";

	ptemp = new NC[ loop + 1 ];
	if( !ptemp )
	{
		delete val;
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	memcpy( ptemp, p, loop );
	stringEl->str() = ptemp;
	delete [] ptemp;
	exp.ves().pushValue( stringEl );
}


void RtrimFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}


SecondFunctionInstruction::SecondFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


SecondFunctionInstruction::~SecondFunctionInstruction( void )
{
}


void SecondFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val = ((pAbstractValueElement)0);
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();

	TimeValue *time = extractTimeArgument( val );
	{
		delete val;
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	Cql_Integer& integer = dynamic_cast< Cql_Integer& >( ile->value() );
	integer.instance().value() = const_cast< const TimeValue* >( time )->second();
	exp.ves().pushValue( ile );
}


void SecondFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


SignFunctionInstruction::SignFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


SignFunctionInstruction::~SignFunctionInstruction( void )
{
}


void SignFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pIntegerLiteralElement integerEl;
	NI result;

	val = exp.ves().popValue();

	if( !val->isNumeric() )
	{
		delete val;
		throw IncompatibleTypesException( __FILE__, __LINE__ );
	}

	integerEl = new IntegerLiteralElement;
	if( !integerEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	IntegerValue& integer = dynamic_cast< IntegerValue& >( val->value().avalue() );
	if( integer < IntegerValue( 0 ) )
		result = -1;
	else if( !integer )
		result = 0;
	else
		result = 1;

	integer = result;
	delete val;
	exp.ves().pushValue( integerEl );
}


void SignFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


SinFunctionInstruction::SinFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


SinFunctionInstruction::~SinFunctionInstruction( void )
{
}


void SinFunctionInstruction::execute( Expression& exp )
{
	executeFloatFunction( exp, clibSin );
}


void SinFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_FLOAT );
}


SqrtFunctionInstruction::SqrtFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


SqrtFunctionInstruction::~SqrtFunctionInstruction( void )
{
}


void SqrtFunctionInstruction::execute( Expression& exp )
{
	executeFloatFunction( exp, clibSquareRoot );
}


void SqrtFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_FLOAT );
}


SubstringFunctionInstruction::SubstringFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


SubstringFunctionInstruction::~SubstringFunctionInstruction( void )
{
}


void SubstringFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val1 = ((pAbstractValueElement)0), val2 = ((pAbstractValueElement)0), val3;
	pStringElement stringEl;
	L start, length;
	pNC ptemp;

	val3 = exp.ves().popValue();
	length = extractIntegerArgument( val3 );
	val2 = exp.ves().popValue();
	start = extractIntegerArgument( val2 );
	val1 = exp.ves().popValue();
	stringEl = ((pStringElement)val1);
	const char * const p = stringEl->str().text();

	ptemp = new NC[ length + 1 ];
	if( !ptemp )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	memset( ptemp, 0, ((UNI)( length + 1 ) ) );
	memcpy( ptemp, p + start, ((UNI)length) );

	stringEl->str() = ptemp;
	delete [] ptemp;
	exp.ves().pushValue( stringEl );
}


void SubstringFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}

	
SumFunctionInstruction::SumFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


SumFunctionInstruction::~SumFunctionInstruction( void )
{
}


void SumFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;

	if( exp.aggregateDistinctScan() )
		return;

	val = aggregatePopAndConvert( &exp );

	if( !val->isNull() )
	{
		if( exp.functionSpace()->isNull() )
			*exp.functionSpace() = *val;
		else
		{
			*exp.functionSpace() += *val;
			*val = *exp.functionSpace();
		}
	}

	exp.ves().pushValue( val );
}


TanFunctionInstruction::TanFunctionInstruction( SqlHandle& sqlh ) : FunctionInstruction( sqlh )
{
}


TanFunctionInstruction::~TanFunctionInstruction( void )
{
}


void TanFunctionInstruction::execute( Expression& exp )
{
	executeFloatFunction( exp, clibTangent );
}


void TanFunctionInstruction::promote( Expression& exp, bool /*workingType*/ )
{
	exp.forceExpressionType( CQL_FLOAT );
}


UcaseFunctionInstruction::UcaseFunctionInstruction( SqlHandle& sqlh ) : FunctionInstruction( sqlh )
{
}


UcaseFunctionInstruction::~UcaseFunctionInstruction( void )
{
}


void UcaseFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pStringElement stringEl;
	UNI length, loop;

	val = exp.ves().popValue();

	stringEl = ((pStringElement)val);
	char * p = const_cast<char *>(stringEl->str().text());
	length = stringEl->str().length();

	for( loop = 0; loop < length; loop++, p++ )
		if( *p >= 'a' && *p <= 'z' )
			(*p) -= ((NC)0x20);

	exp.ves().pushValue( stringEl );
}


void UcaseFunctionInstruction::promote( Expression& exp, bool /*useWorkingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}


UserFunctionInstruction::UserFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


UserFunctionInstruction::~UserFunctionInstruction( void )
{
}


void UserFunctionInstruction::execute( Expression& exp )
{
	StringElement *stringEl = new StringElement();
	if( !stringEl )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	stringEl->str() = dbsql().aHandle().userName();
	exp.ves().pushValue( stringEl );
}


void UserFunctionInstruction::promote( Expression& exp, bool /*useWorkingType*/ )
{
	exp.forceExpressionType( CQL_CHAR );
}


WeekFunctionInstruction::WeekFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


WeekFunctionInstruction::~WeekFunctionInstruction( void )
{
}


void WeekFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val;
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();
	DateValue *date = extractDateArgument( val );
	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	Cql_Integer& integer = dynamic_cast< Cql_Integer& >( ile->value() );
	integer = date->weekNumber();
	exp.ves().pushValue( ile );
}


void WeekFunctionInstruction::promote( Expression& exp, bool /*useWorkingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}


YearFunctionInstruction::YearFunctionInstruction( SqlHandle& _dbsql ) : FunctionInstruction( _dbsql )
{
}


YearFunctionInstruction::~YearFunctionInstruction( void )
{
}


void YearFunctionInstruction::execute( Expression& exp )
{
	pAbstractValueElement val = ((pAbstractValueElement)0);
	pIntegerLiteralElement ile;

	val = exp.ves().popValue();

	DateValue *date = extractDateArgument( val );
	ile = new IntegerLiteralElement;
	if( !ile )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	Cql_Integer integer = dynamic_cast< Cql_Integer& >( ile->value() );
	integer = date->year();
	exp.ves().pushValue( ile );
}


void YearFunctionInstruction::promote( Expression& exp, bool /*useWorkingType*/ )
{
	exp.forceExpressionType( CQL_INTEGER );
}
