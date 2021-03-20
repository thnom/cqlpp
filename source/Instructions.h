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


#ifndef __Instructions_h
#define __Instructions_h


class Instruction;
typedef List< Instruction > InstructionListBase;
typedef ListElement< Instruction, InstructionListBase > InstructionListElement;


class Instruction
	: public InstructionListElement,
	  public InstructionConstants,
	  public ErrorConstants,
	  public FunctionConstants,
	  public CqlConstants
{
	bool allocationFlag;
	SqlHandle& dbsql_;
	US setIdentifier_;
	UC *temporaryBuffer_;

	void selectConversion( AbstractValueElement**, AbstractValueElement** );

public :

	Instruction( SqlHandle& );
	virtual ~Instruction( void );

	NI AbsoluteValue( AbstractValueElement* );
	void AbstractAssign( const Instruction& );
	void convert( AbstractValueElement*, CqlColumnTypes );
	AbstractValueElement *convertToFloat( AbstractValueElement *val );
	AbstractValueElement *convertToInteger( AbstractValueElement *val, AbstractType::RoundType roundType = AbstractType::ROUND_NEAREST );
	static Instruction *createObject( SqlHandle&, OperationCodes, BinaryOperators, Functions, UnaryOperators, TertiaryOperators );
	SqlHandle& dbsql( void ) { return dbsql_; }
	void executeFloatFunction( Expression& exp, D func( D ), bool invert = false );
	DateValue *extractDateArgument( AbstractValueElement* );
	D extractFloatArgument( AbstractValueElement* );
	L extractIntegerArgument( AbstractValueElement* );
	TimeValue *extractTimeArgument( AbstractValueElement* );
	NI IsNegative( pNI, AbstractValueElement* );
	void makeTypesCompatible( bool&, AbstractValueElement**, AbstractValueElement** );
	US setIdentifier( void ) { return setIdentifier_; }
	void setIdentifier( US si ) { setIdentifier_ = si; }

	virtual void reprocessViewData( SelectExpressionList& );

	virtual Instruction& operator = ( const Instruction& ) = 0;

	virtual BinaryOperators BinaryOp( void );
	virtual void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack ) = 0;
	virtual ColumnSpecification *col( void );
	virtual US dictionaryLength( void ) = 0;
	virtual void execute( Expression& ) = 0;
	virtual void executePost( Expression& );
	virtual Functions FuncId( void );
	virtual OperationCodes OpCode( void ) = 0;
	virtual void promote( Expression&, bool /*workingType*/ = false ) = 0;
	virtual void processViewData( SelectExpressionList& ) = 0;
	virtual void readDictionaryInformation( TempBuffer& ) = 0;
	virtual TertiaryOperators TertiaryOp( void );
	virtual UnaryOperators UnaryOp( void );
	virtual void writeDictionaryInformation( TempBuffer& ) = 0;
};

typedef Instruction *pInstruction;


class SetComparisonInstruction : public Instruction, public SetComparisonConstants
{
	ComparisonOperators comparisonOp;

public :

	SetComparisonInstruction( SqlHandle&, ComparisonOperators cop );
	SetComparisonInstruction( SqlHandle& );
	virtual ~SetComparisonInstruction( void );

	Instruction& operator = ( const Instruction& );

	void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack );
	ComparisonOperators ComparisonOp( void ) { return comparisonOp; }
	US dictionaryLength( void );
	void readDictionaryInformation( TempBuffer& );
	void processViewData( SelectExpressionList& );
	void writeDictionaryInformation( TempBuffer& );

	virtual ComparisonModifiers ComparisonModifier( void ) = 0;
};

typedef SetComparisonInstruction *pSetComparisonInstruction;


class AllInstruction : public SetComparisonInstruction
{
public :

	AllInstruction( SqlHandle&, ComparisonOperators cop );
	AllInstruction( SqlHandle& );
	~AllInstruction( void );

	ComparisonModifiers ComparisonModifier( void ) { return MOD_ALL; }
	void execute( Expression& );
	OperationCodes OpCode( void ) { return CQL_ALL; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef AllInstruction *pAllInstruction;


class BinaryOperatorInstruction : public Instruction
{
public :

	BinaryOperatorInstruction( SqlHandle& );
	virtual ~BinaryOperatorInstruction( void );

	Instruction& operator = ( const Instruction& );

	void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack );
	US dictionaryLength( void );
	OperationCodes OpCode( void ) { return BINARY_OPERATOR; }
	void processViewData( SelectExpressionList& );
	void readDictionaryInformation( TempBuffer& );
	void writeDictionaryInformation( TempBuffer& );

	//  for derived classes for promote doing nothing
	virtual void promote( Expression&, bool /*workingType*/ = false ) { }
};

typedef BinaryOperatorInstruction *pBinaryOperatorInstruction;


class AndInstruction : public BinaryOperatorInstruction
{
public :

	AndInstruction( SqlHandle& );
	~AndInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_AND; }
	void execute( Expression& );
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef AndInstruction *pAndInstruction;


class AnyInstruction : public SetComparisonInstruction
{
public :

	AnyInstruction( SqlHandle&, ComparisonOperators cop );
	AnyInstruction( SqlHandle& );
	~AnyInstruction( void );

	ComparisonModifiers ComparisonModifier( void ) { return MOD_ANY; }
	void execute( Expression& );
	OperationCodes OpCode( void ) { return CQL_ANY; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef AnyInstruction *pAnyInstruction;


class TertiaryOperatorInstruction : public Instruction
{
public :

	TertiaryOperatorInstruction( SqlHandle& );
	virtual ~TertiaryOperatorInstruction( void );

	Instruction& operator = ( const Instruction& );

	NI Assign( SqlHandle*, pInstruction );
	void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack );
	void processViewData( SelectExpressionList& );
	OperationCodes OpCode( void ) { return TERTIARY_OPERATOR; }
	void readDictionaryInformation( TempBuffer& );
	void writeDictionaryInformation( TempBuffer& );
};

typedef TertiaryOperatorInstruction *pTertiaryOperatorInstruction;


class BetweenInstruction : public TertiaryOperatorInstruction
{
public :

	BetweenInstruction( SqlHandle& );
	~BetweenInstruction( void );

	US dictionaryLength( void );
	void execute( Expression& );
	void promote( Expression& exp, bool /*workingType*/ = false );
	TertiaryOperators TertiaryOp( void ) { return CQL_BETWEEN; }
};


class ComparisonInstruction : public BinaryOperatorInstruction
{
public :

	ComparisonInstruction( SqlHandle& );
	virtual ~ComparisonInstruction( void );

	void execute( Expression& );
	void promote( Expression& exp, bool /*workingType*/ = false );
};


class DivideInstruction : public BinaryOperatorInstruction
{
public :

	DivideInstruction( SqlHandle& );
	~DivideInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_DIVIDE; }
	void execute( Expression& );
};


class EqualsInstruction : public ComparisonInstruction
{
public :

	EqualsInstruction( SqlHandle& );
	~EqualsInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_EQUALS; }
};

typedef EqualsInstruction *pEqualsInstruction;


class UnaryOperatorInstruction : public Instruction
{
public :

	UnaryOperatorInstruction( SqlHandle& );
	~UnaryOperatorInstruction( void );

	Instruction& operator = ( const Instruction& );

	void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack );
	US dictionaryLength( void );
	OperationCodes OpCode( void ) { return UNARY_OPERATOR; }
	void processViewData( SelectExpressionList& );
	void readDictionaryInformation( TempBuffer& );
	void writeDictionaryInformation( TempBuffer& );

	//  for derived classes for promote doing nothing
	virtual void promote( Expression&, bool /*workingType*/ = false ) { }
};

typedef UnaryOperatorInstruction *pUnaryOperatorInstruction;


class ExistsInstruction : public UnaryOperatorInstruction
{
public :

	ExistsInstruction( SqlHandle& );
	~ExistsInstruction( void );

	void execute( Expression& );
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef ExistsInstruction *pExistsInstruction;


class GreaterInstruction : public ComparisonInstruction
{
public :

	GreaterInstruction( SqlHandle& );
	~GreaterInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_GREATER; }
};

typedef GreaterInstruction *pGreaterInstruction;


class GreaterOrEqualInstruction : public ComparisonInstruction
{
public :

	GreaterOrEqualInstruction( SqlHandle& );
	~GreaterOrEqualInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_GREATER_OR_EQUAL; }
};

typedef GreaterOrEqualInstruction *pGreaterOrEqualInstruction;


class IdentifierInstruction : public Instruction
{
	ColumnSpecification *col_;
	US columnNumber_;
	bool correlated_;
	US setNumber_;
	US tableNumber_;


public :

	IdentifierInstruction( SqlHandle& );
	~IdentifierInstruction( void );

	Instruction& operator = ( const Instruction& );

	NI IdentifierInstructionAssign( SqlHandle*, IdentifierInstruction& );
	void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack );
	ColumnSpecification *col( void ) { return col_; }
	void col( ColumnSpecification *c ) { col_ = c; }
	US columnNumber( void ) { return columnNumber_; }
	void columnNumber( US c ) { columnNumber_ = c; }
	bool& correlated( void ) { return correlated_; }
	US dictionaryLength( void );
	void execute( Expression& );
	OperationCodes OpCode( void ) { return IDENTIFIER_PUSH; }
	void processViewData( SelectExpressionList& );
	void promote( Expression& exp, bool /*workingType*/ = false );
	void readDictionaryInformation( TempBuffer& );
	void reprocessViewData( SelectExpressionList& );
	void setCorrelated( void ) { correlated_ = true; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef IdentifierInstruction *pIdentifierInstruction;


class InstructionList : public InstructionListBase, public InstructionConstants, public FunctionConstants, public ErrorConstants
{
public :

	InstructionList( void );

	InstructionList& operator = ( const InstructionList& );

	US dictionaryLength( void );
	void processViewData( SelectExpressionList& );
	void readDictionaryInformation( TempBuffer& );
	void reprocessViewData( SelectExpressionList& );
	void writeDictionaryInformation( TempBuffer& );
};

typedef InstructionList *pInstructionList;


class LessInstruction : public ComparisonInstruction
{
public :

	LessInstruction( SqlHandle& );
	~LessInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_LESS; }
};

typedef LessInstruction *pLessInstruction;


class LessOrEqualInstruction : public ComparisonInstruction
{
public :

	LessOrEqualInstruction( SqlHandle& );
	~LessOrEqualInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_LESS_OR_EQUAL; }
};

typedef LessOrEqualInstruction *pLessOrEqualInstruction;


class LikeInstruction : public BinaryOperatorInstruction
{
public :

	LikeInstruction( SqlHandle& );
	~LikeInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_LIKE; }
	pInstruction Copy( void ) { return ((pInstruction)0); }
	void execute( Expression& );
	void promote( Expression& exp, bool /*workingType*/ = false );
};


class LogicalNotInstruction : public UnaryOperatorInstruction
{
public :

	LogicalNotInstruction( SqlHandle& );
	~LogicalNotInstruction( void );

	void execute( Expression& );
	void promote( Expression& exp, bool /*workingType*/ = false );
	UnaryOperators UnaryOp( void ) { return LOGICAL_NOT; }
};

typedef LogicalNotInstruction *pLogicalNotInstruction;


class NotEqualInstruction : public ComparisonInstruction
{
public :

	NotEqualInstruction( SqlHandle& );
	~NotEqualInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_NOTEQUAL; }
};

typedef NotEqualInstruction *pNotEqualInstruction;


class NullTestInstruction : public UnaryOperatorInstruction
{
public :

	NullTestInstruction( SqlHandle& );
	~NullTestInstruction( void );

	void execute( Expression& );
	void promote( Expression& exp, bool workingType = false );
};

typedef NullTestInstruction *pNullTestInstruction;


class OperatorMinusInstruction : public BinaryOperatorInstruction
{
public :

	OperatorMinusInstruction( SqlHandle& );
	~OperatorMinusInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_MINUS; }
	void execute( Expression& );
};


class OrInstruction : public BinaryOperatorInstruction
{
public :

	OrInstruction( SqlHandle& );
	~OrInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_OR; }
	void execute( Expression& );
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef OrInstruction *pOrInstruction;


class OuterJoinInstruction : public BinaryOperatorInstruction
{
public :

	OuterJoinInstruction( SqlHandle& );
	~OuterJoinInstruction( void );

	BinaryOperators BinaryOp( void ) { return OUTER_EQUAL; }
	pInstruction Copy( void ) { return ((pInstruction)0); }
	void execute( Expression& );
};


class PlusInstruction : public BinaryOperatorInstruction
{
public :

	PlusInstruction( SqlHandle& );
	~PlusInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_PLUS; }
	void execute( Expression& );
};


class QueryInstruction;
typedef List< QueryInstruction > QueryInstructionList;
typedef ListElement< QueryInstruction, QueryInstructionList > QueryInstructionListElement;


class QueryInstruction : public QueryInstructionListElement
{
public :

	QueryInstruction( void );
	virtual ~QueryInstruction( void );

	virtual bool assignResultSetFile( QueryExpression&, bool /*firstSelect*/ ) = 0;  // returns firstSelect flag
	virtual void cleanup( QueryExpression& ) = 0;
	virtual void execute( QueryExpression& ) = 0;
};

typedef QueryInstruction *pQueryInstruction;


class SetPushInstruction : public QueryInstruction
{
	SelectExpression *selectExp;

public :

	SetPushInstruction( SelectExpression *s );
	~SetPushInstruction( void );

	void cleanup( QueryExpression& );
	void execute( QueryExpression& );
	//  firstSelect is both the input and return value
	bool assignResultSetFile( QueryExpression&, bool /*firstSelect*/ );
	SelectExpression *SelectExp( void ) { return selectExp; }
};

typedef SetPushInstruction *pSetPushInstruction;


class SubqueryInstruction : public Instruction
{
	SelectExpression *selectExpression_;
	US setNumber_;

public :

	SubqueryInstruction( SqlHandle&, SelectExpression* );
	SubqueryInstruction( SqlHandle& );
	~SubqueryInstruction( void );

	Instruction& operator = ( const Instruction& );

	void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack );
	ColumnSpecification *Col( void );
	US dictionaryLength( void );
	void execute( Expression& );
	void readDictionaryInformation( TempBuffer& );
	OperationCodes OpCode( void ) { return SUBQUERY_PUSH; }
	void processViewData( SelectExpressionList& );
	void promote( Expression&, bool /*workingType*/ = false );
	SelectExpression& selectExpression( void ) { return *selectExpression_; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef SubqueryInstruction *pSubqueryInstruction;


class TimesInstruction : public BinaryOperatorInstruction
{
public :

	TimesInstruction( SqlHandle& );
	~TimesInstruction( void );

	BinaryOperators BinaryOp( void ) { return OPERATOR_TIMES; }
	void execute( Expression& );
};


class UnaryMinusInstruction : public UnaryOperatorInstruction
{
public :

	UnaryMinusInstruction( SqlHandle& );
	~UnaryMinusInstruction( void );

	void execute( Expression& );
};

typedef UnaryMinusInstruction *pUnaryMinusInstruction;


class ValueInstruction : public Instruction
{
	pAbstractValueElement el;

public :

	ValueInstruction( SqlHandle&, AbstractValueElement *e );
	ValueInstruction( SqlHandle& );
	~ValueInstruction( void );

	Instruction& operator = ( const Instruction& );

	void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack );
	US dictionaryLength( void );
	pAbstractValueElement El( void ) { return el; }
	void execute( Expression& );
	OperationCodes OpCode( void ) { return VALUE_PUSH; }
	void processViewData( SelectExpressionList& );
	void promote( Expression& exp, bool /*workingType*/ = false );
	void readDictionaryInformation( TempBuffer& );
	void SetEl( pAbstractValueElement e ) { el = e; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef ValueInstruction *pValueInstruction;


#endif  //  __Instructions_h
