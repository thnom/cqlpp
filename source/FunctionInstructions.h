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


#ifndef __FunctionInstructions_h
#define __FunctionInstructions_h


class FunctionInstruction : public Instruction
{
	UNI numberOfArguments;

public :

	FunctionInstruction( SqlHandle& );
	virtual ~FunctionInstruction( void );

	Instruction& operator = ( const Instruction& );

	AbstractValueElement *aggregatePopAndConvert( Expression* );
	void buildPredicateTreeElement( PredicateList& predList, AbstractPredicateOperandList& stack );
	static FunctionInstruction *createFunctionInstruction( SqlHandle&, Functions, UNI /*numberOfArguments*/ );
	US dictionaryLength( void );
	UNI NumberOfArguments( void ) { return numberOfArguments; }
	OperationCodes OpCode( void ) { return EVALUATE_FUNCTION; }
	void processViewData( SelectExpressionList& );
	void readDictionaryInformation( TempBuffer& );
	void SetNumberOfArguments( UNI n ) { numberOfArguments = n; }
	void writeDictionaryInformation( TempBuffer& );

	//  base method for classes where promote() does nothign
	virtual void promote( Expression&, bool /*workingType*/ = false ) { }
};

typedef FunctionInstruction *pFunctionInstruction;


class AbsFunctionInstruction : public FunctionInstruction
{
public :

	AbsFunctionInstruction( SqlHandle& );
	~AbsFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_ABS; }
};

typedef AbsFunctionInstruction *pAbsFunctionInstruction;


class AcosFunctionInstruction : public FunctionInstruction
{
public :

	AcosFunctionInstruction( SqlHandle& );
	~AcosFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_ACOS; }
};

typedef AcosFunctionInstruction *pAcosFunctionInstruction;


class AsciiFunctionInstruction : public FunctionInstruction
{
public :

	AsciiFunctionInstruction( SqlHandle& );
	~AsciiFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_ASCII; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef AsciiFunctionInstruction *pAsciiFunctionInstruction;


class AsinFunctionInstruction : public FunctionInstruction
{
public :

	AsinFunctionInstruction( SqlHandle& );
	~AsinFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_ASIN; }
};

typedef AsinFunctionInstruction *pAsinFunctionInstruction;


class Atan2FunctionInstruction : public FunctionInstruction
{
public :

	Atan2FunctionInstruction( SqlHandle& );
	~Atan2FunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_ATAN2; }
};

typedef Atan2FunctionInstruction *pAtan2FunctionInstruction;


class AtanFunctionInstruction : public FunctionInstruction
{
public :

	AtanFunctionInstruction( SqlHandle& );
	~AtanFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_ATAN; }
};

typedef AtanFunctionInstruction *pAtanFunctionInstruction;


class AvgFunctionInstruction : public FunctionInstruction
{
public :

	AvgFunctionInstruction( SqlHandle& );
	~AvgFunctionInstruction( void );

	void execute( Expression& );
	void executePost( Expression& );
	Functions FuncId( void ) { return FUNC_AVG; }
};

typedef AvgFunctionInstruction *pAvgFunctionInstruction;


class CeilingFunctionInstruction : public FunctionInstruction
{
public :

	CeilingFunctionInstruction( SqlHandle& );
	~CeilingFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_CEILING; }
};

typedef CeilingFunctionInstruction *pCeilingFunctionInstruction;


class CharFunctionInstruction : public FunctionInstruction
{
public :

	CharFunctionInstruction( SqlHandle& );
	~CharFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_CHAR; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef CharFunctionInstruction *pCharFunctionInstruction;


class ConcatFunctionInstruction : public FunctionInstruction
{
public :

	ConcatFunctionInstruction( SqlHandle& );
	~ConcatFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_CONCAT; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef ConcatFunctionInstruction *pConcatFunctionInstruction;


class ConvertFunctionInstruction : public FunctionInstruction
{
public :

	ConvertFunctionInstruction( SqlHandle& );
	~ConvertFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_CONVERT; }
};

typedef ConvertFunctionInstruction *pConvertFunctionInstruction;


class CosFunctionInstruction : public FunctionInstruction
{
public :

	CosFunctionInstruction( SqlHandle& );
	~CosFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_COS; }
};

typedef CosFunctionInstruction *pCosFunctionInstruction;


class CotFunctionInstruction : public FunctionInstruction
{
public :

	CotFunctionInstruction( SqlHandle& );
	~CotFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_COT; }
};

typedef CotFunctionInstruction *pCotFunctionInstruction;


class CountColumnFunctionInstruction : public FunctionInstruction
{
public :

	CountColumnFunctionInstruction( SqlHandle& );
	~CountColumnFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_COUNT2; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef CountColumnFunctionInstruction *pCountColumnFunctionInstruction;


class CountStarFunctionInstruction : public FunctionInstruction
{
public :

	CountStarFunctionInstruction( SqlHandle& );
	~CountStarFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_COUNT1; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef CountStarFunctionInstruction *pCountStarFunctionInstruction;


class CurdateFunctionInstruction : public FunctionInstruction
{
public :

	CurdateFunctionInstruction( SqlHandle& );
	~CurdateFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_CURDATE; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef CurdateFunctionInstruction *pCurdateFunctionInstruction;


class CurtimeFunctionInstruction : public FunctionInstruction
{
public :

	CurtimeFunctionInstruction( SqlHandle& );
	~CurtimeFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_CURTIME; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef CurtimeFunctionInstruction *pCurtimeFunctionInstruction;


class DatabaseFunctionInstruction : public FunctionInstruction
{
public :

	DatabaseFunctionInstruction( SqlHandle& );
	~DatabaseFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_DATABASE; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef DatabaseFunctionInstruction *pDatabaseFunctionInstruction;


class DayOfMonthFunctionInstruction : public FunctionInstruction
{
public :

	DayOfMonthFunctionInstruction( SqlHandle& );
	~DayOfMonthFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_DAYOFMONTH; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef DayOfMonthFunctionInstruction *pDayOfMonthFunctionInstruction;


class DayOfWeekFunctionInstruction : public FunctionInstruction
{
public :

	DayOfWeekFunctionInstruction( SqlHandle& );
	~DayOfWeekFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_DAYOFWEEK; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef DayOfWeekFunctionInstruction *pDayOfWeekFunctionInstruction;


class DayOfYearFunctionInstruction : public FunctionInstruction
{
public :

	DayOfYearFunctionInstruction( SqlHandle& );
	~DayOfYearFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_DAYOFYEAR; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef DayOfYearFunctionInstruction *pDayOfYearFunctionInstruction;


class ExpFunctionInstruction : public FunctionInstruction
{
public :

	ExpFunctionInstruction( SqlHandle& );
	~ExpFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_EXP; }
};

typedef ExpFunctionInstruction *pExpFunctionInstruction;


class FloorFunctionInstruction : public FunctionInstruction
{
public :

	FloorFunctionInstruction( SqlHandle& );
	~FloorFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_FLOOR; }
};

typedef FloorFunctionInstruction *pFloorFunctionInstruction;


class HourFunctionInstruction : public FunctionInstruction
{
public :

	HourFunctionInstruction( SqlHandle& );
	~HourFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_HOUR; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef HourFunctionInstruction *pHourFunctionInstruction;


class IfnullFunctionInstruction : public FunctionInstruction
{
public :

	IfnullFunctionInstruction( SqlHandle& );
	~IfnullFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_IFNULL; }
};

typedef IfnullFunctionInstruction *pIfnullFunctionInstruction;


class InsertFunctionInstruction : public FunctionInstruction
{
public :

	InsertFunctionInstruction( SqlHandle& );
	~InsertFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_INSERT; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef InsertFunctionInstruction *pInsertFunctionInstruction;


class LcaseFunctionInstruction : public FunctionInstruction
{
public :

	LcaseFunctionInstruction( SqlHandle& );
	~LcaseFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_LCASE; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef LcaseFunctionInstruction *pLcaseFunctionInstruction;


class LeftFunctionInstruction : public FunctionInstruction
{
public :

	LeftFunctionInstruction( SqlHandle& );
	~LeftFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_LEFT; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef LeftFunctionInstruction *pLeftFunctionInstruction;


class LengthFunctionInstruction : public FunctionInstruction
{
public :

	LengthFunctionInstruction( SqlHandle& );
	~LengthFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_LENGTH; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef LengthFunctionInstruction *pLengthFunctionInstruction;


class LocateFunctionInstruction : public FunctionInstruction
{
public :

	LocateFunctionInstruction( SqlHandle& );
	~LocateFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_LOCATE; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef LocateFunctionInstruction *pLocateFunctionInstruction;


class LogFunctionInstruction : public FunctionInstruction
{
public :

	LogFunctionInstruction( SqlHandle& );
	~LogFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_LOG; }
};

typedef LogFunctionInstruction *pLogFunctionInstruction;


class LtrimFunctionInstruction : public FunctionInstruction
{
public :

	LtrimFunctionInstruction( SqlHandle& );
	~LtrimFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_LTRIM; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef LtrimFunctionInstruction *pLtrimFunctionInstruction;


class MaxFunctionInstruction : public FunctionInstruction
{
public :

	MaxFunctionInstruction( SqlHandle& );
	~MaxFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_MAXIMUM; }
};

typedef MaxFunctionInstruction *pMaxFunctionInstruction;


class MinFunctionInstruction : public FunctionInstruction
{
public :

	MinFunctionInstruction( SqlHandle& );
	~MinFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_MIN; }
};

typedef MinFunctionInstruction *pMinFunctionInstruction;


class MinuteFunctionInstruction : public FunctionInstruction
{
public :

	MinuteFunctionInstruction( SqlHandle& );
	~MinuteFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_MINUTE; }
	void promote( Expression&, bool /*workingType*/ = false );
};

typedef MinuteFunctionInstruction *pMinuteFunctionInstruction;


class ModFunctionInstruction : public FunctionInstruction
{
public :

	ModFunctionInstruction( SqlHandle& );
	~ModFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_MOD; }
};

typedef ModFunctionInstruction *pModFunctionInstruction;


class MonthFunctionInstruction : public FunctionInstruction
{
public :

	MonthFunctionInstruction( SqlHandle& );
	~MonthFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_MONTH; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef MonthFunctionInstruction *pMonthFunctionInstruction;


class NowFunctionInstruction : public FunctionInstruction
{
public :

	NowFunctionInstruction( SqlHandle& );
	~NowFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_NOW; }
	void promote( Expression& exp, bool workingType = false );
};

typedef NowFunctionInstruction *pNowFunctionInstruction;


class PiFunctionInstruction : public FunctionInstruction
{
public :

	PiFunctionInstruction( SqlHandle& );
	~PiFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_PI; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef PiFunctionInstruction *pPiFunctionInstruction;


class QuarterFunctionInstruction : public FunctionInstruction
{
public :

	QuarterFunctionInstruction( SqlHandle& );
	~QuarterFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_QUARTER; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef QuarterFunctionInstruction *pQuarterFunctionInstruction;


class RandFunctionInstruction : public FunctionInstruction
{
public :

	RandFunctionInstruction( SqlHandle& );
	~RandFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_RAND; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef RandFunctionInstruction *pRandFunctionInstruction;


class RepeatFunctionInstruction : public FunctionInstruction
{
	UNI repetitionCount;

public :

	RepeatFunctionInstruction( SqlHandle& );
	~RepeatFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_REPEAT; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef RepeatFunctionInstruction *pRepeatFunctionInstruction;


class ReplaceFunctionInstruction : public FunctionInstruction
{
public :

	ReplaceFunctionInstruction( SqlHandle& );
	~ReplaceFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_REPLACE; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef ReplaceFunctionInstruction *pReplaceFunctionInstruction;


class RightFunctionInstruction : public FunctionInstruction
{
public :

	RightFunctionInstruction( SqlHandle& );
	~RightFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_RIGHT; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef RightFunctionInstruction *pRightFunctionInstruction;


class RtrimFunctionInstruction : public FunctionInstruction
{
public :

	RtrimFunctionInstruction( SqlHandle& );
	~RtrimFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_RTRIM; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef RtrimFunctionInstruction *pRtrimFunctionInstruction;


class SecondFunctionInstruction : public FunctionInstruction
{
public :

	SecondFunctionInstruction( SqlHandle& );
	~SecondFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_SECOND; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef SecondFunctionInstruction *pSecondFunctionInstruction;


class SignFunctionInstruction : public FunctionInstruction
{
public :

	SignFunctionInstruction( SqlHandle& );
	~SignFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_SIGN; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef SignFunctionInstruction *pSignFunctionInstruction;


class SinFunctionInstruction : public FunctionInstruction
{
public :

	SinFunctionInstruction( SqlHandle& );
	~SinFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_SIN; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef SinFunctionInstruction *pSinFunctionInstruction;


class SqrtFunctionInstruction : public FunctionInstruction
{
public :

	SqrtFunctionInstruction( SqlHandle& );
	~SqrtFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_SQRT; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef SqrtFunctionInstruction *pSqrtFunctionInstruction;


class SubstringFunctionInstruction : public FunctionInstruction
{
public :

	SubstringFunctionInstruction( SqlHandle& );
	~SubstringFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_SUBSTRING; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef SubstringFunctionInstruction *pSubstringFunctionInstruction;


class SumFunctionInstruction : public FunctionInstruction
{
public :

	SumFunctionInstruction( SqlHandle& );
	~SumFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_SUM; }
};

typedef SumFunctionInstruction *pSumFunctionInstruction;


class TanFunctionInstruction : public FunctionInstruction
{
public :

	TanFunctionInstruction( SqlHandle& );
	~TanFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_TAN; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef TanFunctionInstruction *pTanFunctionInstruction;


class UcaseFunctionInstruction : public FunctionInstruction
{
public :

	UcaseFunctionInstruction( SqlHandle& );
	~UcaseFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_UCASE; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef UcaseFunctionInstruction *pUcaseFunctionInstruction;


class UserFunctionInstruction : public FunctionInstruction
{
public :

	UserFunctionInstruction( SqlHandle& );
	~UserFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_USER; }
	void promote( Expression& exp, bool /*workingType*/ = false );
};

typedef UserFunctionInstruction *pUserFunctionInstruction;


class WeekFunctionInstruction : public FunctionInstruction
{
public :

	WeekFunctionInstruction( SqlHandle& );
	~WeekFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_WEEK; }
	void promote( Expression& exp, bool /*useWorkingType*/ = false );
};

typedef WeekFunctionInstruction *pWeekFunctionInstruction;


class YearFunctionInstruction : public FunctionInstruction
{
public :

	YearFunctionInstruction( SqlHandle& );
	~YearFunctionInstruction( void );

	void execute( Expression& );
	Functions FuncId( void ) { return FUNC_YEAR; }
	void promote( Expression& exp, bool /*useWorkingType*/ = false );
};

typedef YearFunctionInstruction *pYearFunctionInstruction;


#endif  //  __FunctionInstructions_h
