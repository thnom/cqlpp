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


#ifndef __Column_h
#define __Column_h


class Column;
typedef List< Column > ColumnTableBase;
typedef ListElement< Column, ColumnTableBase > ColumnListElement;


class Column : public ColumnListElement, public ErrorConstants
{
	bool alterColumnAdd;
	bool alterColumnDrop;
	bool alterColumnModify;
	AbstractType *assignmentValue_;
	BoundColumn *bc_;
	UNI bodyNumber;
	NI breakLevel;
	NI breakLevel2;
	bool brk;
	bool brk2;
	Expression columnExpression;
	UNI computeBase;
	NI computeColumn;
	UNI computeFlag;
	UNI computeLimit;
	bool countIndex;
	SqlHandle& dbsql_;
	bool descending_;
	bool doAssignment;
	UNI expressionLength;
	bool firstOperation;
	bool functionKey;
	bool indicator;
	bool invalidCalculation;
	bool justifyCenter;
	bool justifyRight;
	CqlString label;
	bool maxIndex;
	bool minIndex;
	bool noDup;
	bool orderByNumber;
	UNI orderColumnNumber;
	UNI orderSkip;
	CqlString patternOverride;
	bool prepush;
	bool processed;
	pAbstractType reportValue;
	bool skip;
	CqlString viewName;
	bool valueRestored;
	bool wrapChar;
	NI wrapLevel;
	bool wrapTruncate;
	bool wrapWord;

public :

	Column( SqlHandle& );
	~Column( void );

	Column& operator = ( const Column& );

	void AssignColumnExpression( pExpression *exp );
	AbstractType& assignmentValue( void ) { return *assignmentValue_; }
	NI BindColumn( pAbstractTable, NI = CQL_YES );
	Expression& ColumnExpression( void ) { return columnExpression; }
	pExpression ColumnExpressionAddress( void ) { return &columnExpression; }
	void createReportValue( void );
	UNI ExpressionLength( void ) { return expressionLength; }
	NI CountIndex( void ) { return countIndex; }
	SqlHandle& dbsql( void ) { return dbsql_; }
	bool descending( void ) { return descending_; }
	UNI DictionaryLength( void );
	void encode( CqlString& );
	CqlString& Label( void ) { return label; }
	NI MaxIndex( void ) { return maxIndex; }
	NI MinIndex( void ) { return minIndex; }
	CqlString& PatternOverride( void ) { return patternOverride; }
	void readDictionaryInformation( TempBuffer& );
	pAbstractType ReportValue( void ) { return reportValue; }
	void SetAlterColumnAdd( void ) { alterColumnAdd = CQL_YES; }
	void SetAlterColumnDrop( void ) { alterColumnDrop = CQL_YES; }
	void SetAlterColumnModify( void ) { alterColumnModify = CQL_YES; }
	void setAssignmentValue( void );
	void SetBrk( void ) { brk = CQL_YES; }
	void SetBrk2( void ) { brk2 = CQL_YES; }
	void SetCountIndex( void ) { countIndex = CQL_YES; }
	void setDescending( void ) { descending_ = true; }
	void SetDoAssignment( void ) { doAssignment = CQL_YES; }
	void SetFirstOperation( void ) { firstOperation = CQL_YES; }
	void SetFunctionKey( void ) { functionKey = CQL_YES; }
	void SetIndicator( void ) { indicator = CQL_YES; }
	void SetInvalidCalculation( void ) { invalidCalculation = CQL_YES; }
	void SetJustifyCenter( void ) { justifyCenter = CQL_YES; }
	void SetJustifyRight( void ) { justifyRight = CQL_YES; }
	void SetMaxIndex( void ) { maxIndex = CQL_YES; }
	void SetMinIndex( void ) { minIndex = CQL_YES; }
	void SetNoDup( void ) { noDup = CQL_YES; }
	void SetOrderByNumber( void ) { orderByNumber = CQL_YES; }
	void SetPrepush( void ) { prepush = CQL_YES; }
	void SetProcessed( void ) { processed = CQL_YES; }
	void SetSkip( void ) { skip = CQL_YES; }
	void SetValueRestored( void ) { valueRestored = CQL_YES; }
	void SetWrapChar( void ) { wrapChar = CQL_YES; }
	void SetWrapTruncate( void ) { wrapTruncate = CQL_YES; }
	void SetWrapWord( void ) { wrapWord = CQL_YES; }
	CqlString& ViewName( void ) { return viewName; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef Column *pColumn;


#endif  //  __Column_h
