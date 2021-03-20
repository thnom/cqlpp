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


#ifndef __InstructionConstants_h
#define __InstructionConstants_h


class InstructionConstants
{
public :

	enum OperationCodes
	{
		UNSET,
		UNARY_OPERATOR,
		BINARY_OPERATOR,
		IN_OPERATOR,
		EVALUATE_FUNCTION,
		ASSIGNMENT_OPERATOR,
		IDENTIFIER_PUSH,
		VALUE_PUSH,
		ALL_FUNCTION,
		TERTIARY_OPERATOR,
		GET_ESCAPE,
		SET_PUSH,
		CQL_ALL,
		CQL_ANY,
		CORRELATED_PUSH,
		SUBQUERY_PUSH,
		UNION_ALL,
		UNION_DISTINCT,
		INTERSECTION,
		CQL_MINUS,
		NULLPUSH,
		DYNAMIC_PARAMETER_PUSH
	};

	enum BinaryOperators
	{
		OUTER_EQUAL,
		OPERATOR_LIKE,
		OPERATOR_AND,
		OPERATOR_OR,
		OPERATOR_TIMES,
		OPERATOR_DIVIDE,
		OPERATOR_PLUS,
		OPERATOR_MINUS,
		OPERATOR_EQUALS,
		OPERATOR_NOTEQUAL,
		OPERATOR_LESS_OR_EQUAL,
		OPERATOR_GREATER_OR_EQUAL,
		OPERATOR_LESS,
		OPERATOR_GREATER,
		OPERATOR_IN,
		NOT_A_BINARY_OPERATOR
	};

	enum UnaryOperators
	{
		LOGICAL_NOT,
		UNARY_MINUS,
		NULLTEST,
		CQL_EXISTS,
		NOT_A_UNARY_OPERATOR
	};

	enum TertiaryOperators
	{
		CQL_BETWEEN,
		NOT_A_TERTIARY_OPERATOR
	};
};


#endif  //  __InstructionConstants_h
