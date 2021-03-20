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


#ifndef __CQLSQLINCLUDE_H
#define __CQLSQLINCLUDE_H

#define __CQL_SQL
#define __CQL_LIBRARY

#include "CqlSqlClass.h"
#include "CqlCommonInclude.h"
#include "CqlMetadata.h"

class AbstractPredicateOperand;
typedef StackList< AbstractPredicateOperand > AbstractPredicateOperandList;
typedef ListElement< AbstractPredicateOperand, AbstractPredicateOperandList > AbstractPredicateOperandListElement;

class FILEListElement;
typedef List< FILEListElement > FILEList;
typedef ListElement< FILEListElement, FILEList > FILEListElementListElement;


class InsertColumnName;
typedef List< InsertColumnName > InsertColumnNameList;

class SelectExpression;
typedef List< SelectExpression > SelectExpressionListBase;
typedef ListElement< SelectExpression, SelectExpressionListBase > SelectExpressionListElement;

class UpdateColumnNameAndExp;
typedef List< UpdateColumnNameAndExp > UpdateColumnNameAndExpList;

#include "AbstractValueElement.h"
#include "DynamicParameterElement.h"
#include "NullLiteralElement.h"
#include "LiteralElement.h"
#include "StringElement.h"
#include "StringUCElement.h"
#include "BinaryLiteralElement.h"
#include "NumericLiteralElement.h"
#include "RealLiteralElement.h"
#include "FloatLiteralElement.h"
#include "DecimalLiteralElement.h"
#include "BitLiteralElement.h"
#include "TinyintLiteralElement.h"
#include "SmallintLiteralElement.h"
#include "IntegerLiteralElement.h"
#include "BigintLiteralElement.h"
#include "TimestampLiteralElement.h"
#include "DateLiteralElement.h"
#include "TimeLiteralElement.h"
#include "SubqueryElement.h"
#include "Instructions.h"
#include "AbstractPredicateOperand.h"
#include "NonterminalPredicateOperand.h"
#include "TerminalPredicateOperand.h"
#include "Predicate.h"
#include "PredicateList.h"
#include "OptimizerPredicateList.h"
#include "FunctionInstructions.h"
#include "ValueExpressionStackElement.h"
#include "ValueExpressionStack.h"
#include "ExpressionColumnListElement.h"
#include "ExpressionColumnList.h"
#include "Expression.h"
#include "ReferencedColumn.h"
#include "ReferencedColumnList.h"
#include "PermanentColumnSpecification.h"
#include "ColumnSpecification.h"
#include "ColumnSpecificationList.h"
#include "Column.h"
#include "ColumnTable.h"
#include "GrantColumn.h"
#include "ReportField.h"
#include "ReportWindow.h"
#include "Report.h"
#include "StringListElement.h"
#include "IndexColumnName.h"
#include "StringList.h"
#include "DoubleStringListElement.h"
#include "DoubleStringList.h"
#include "TripleStringListElement.h"
#include "TripleStringList.h"
#include "StringListGroup.h"
#include "IndexNameListGroup.h"
#include "ForeignKeyNames.h"
#include "AbstractTableSpecification.h"
#include "TableReferenceColumn.h"
#include "TableReferenceColumnList.h"
#include "ForeignKey.h"
#include "ForeignKeyList.h"
#include "SegmentedKeyGroup.h"
#include "SegmentedKeyGroupList.h"
#include "TableSpecification.h"
#include "SelectExpressionList.h"
#include "ViewSpecification.h"
#include "TableTableElement.h"
#include "TableTable.h"
#include "Table.h"
#include "View.h"
#include "GrantPrivilege.h"
#include "GrantUser.h"
#include "PrivilegeDictionaryRecord.h"
#include "PrivilegeFieldDictionaryRecord.h"
#include "RowId.h"
#include "SetRow.h"
#include "ResultSet.h"
#include "TemporaryResultFile.h"
#include "SubqueryResultSet.h"
#include "CAdvance.h"
#include "SelectExpression.h"
#include "SelectExpressionCollectionObject.h"
#include "VariableSpecification.h"
#include "Cursor.h"
#include "InsertColumnName.h"
#include "UpdateColumnNameAndExp.h"
#include "StatementHandle.h"
#include "QueryStackElement.h"
#include "QueryExpression.h"
#include "TablenameIndexNode.h"
#include "TablenameIndex.h"
#include "SystemDictionary.h"
#include "PrivilegeDictionary.h"
#include "PrivilegeFieldDictionary.h"
#include "MainDictionary.h"
#include "IndexDictionary.h"
#include "RefersDictionary.h"
#include "SystemTable.h"
#include "SystemTableTables.h"
#include "SystemTableColumns.h"
#include "SystemTableIndices.h"
#include "SqlHandle.h"
#include "SqlEnvironmentHandle.h"

#ifdef __CQL_SQL_EXTERNAL_DEFINER
SqlEnvironmentHandle *dbSqlEnv = 0;
#else
extern SqlEnvironmentHandle *dbSqlEnv;
#endif

#include "CqlSqlOptions.h"
#include "FILEListElement.h"
#include "ParserConstants.h"
#include "ParserStackElement.h"
#include "Parser.h"

//  inline function headers
#include "SqlHandleInline.h"


#if !(defined(YYPARSE_PARAM)) && !(defined(YYPARSE_PARAM_CHANGED))
int yyparse( SqlHandle* );
#endif
int yyerror( SqlHandle*, const char * const );

#define __CQL_SQL_SERVER_SIDE__


//  Global variables
#ifdef __CQL_SQL_EXTERNAL_DEFINER
bool dataTracing = false;
bool skipTransactionStartup = false;
#else
extern bool dataTracing;
extern bool skipTransactionStartup;
#endif


#endif  //  __CQLSQLCLASS_H
