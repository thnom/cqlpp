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


#ifndef __FunctionConstants_h
#define __FunctionConstants_h


class FunctionConstants
{
public :

	enum Functions
	{
		FUNC_COUNT1,
		FUNC_COUNT2,
		FUNC_SUM,
		FUNC_AVG,
		FUNC_MIN,
		FUNC_MAXIMUM,
		FUNC_ASCII,
		FUNC_CHAR,
		FUNC_CONCAT,
		FUNC_INSERT,
		FUNC_LEFT,
		FUNC_LTRIM,
		FUNC_LENGTH,
		FUNC_LOCATE,
		FUNC_LCASE,
		FUNC_REPEAT,
		FUNC_REPLACE,
		FUNC_RIGHT,
		FUNC_RTRIM,
		FUNC_SUBSTRING,
		FUNC_UCASE,
		FUNC_ABS,
		FUNC_ACOS,
		FUNC_ASIN,
		FUNC_ATAN,
		FUNC_ATAN2,
		FUNC_CEILING,
		FUNC_COS,
		FUNC_COT,
		FUNC_EXP,
		FUNC_FLOOR,
		FUNC_LOG,
		FUNC_MOD,
		FUNC_PI,
		FUNC_RAND,
		FUNC_SIGN,
		FUNC_SIN,
		FUNC_SQRT,
		FUNC_TAN,
		FUNC_NOW,
		FUNC_CURDATE,
		FUNC_DAYOFMONTH,
		FUNC_DAYOFWEEK,
		FUNC_DAYOFYEAR,
		FUNC_MONTH,
		FUNC_QUARTER,
		FUNC_WEEK,
		FUNC_YEAR,
		FUNC_CURTIME,
		FUNC_HOUR,
		FUNC_MINUTE,
		FUNC_SECOND,
		FUNC_USER,
		FUNC_DATABASE,
		FUNC_IFNULL,
		FUNC_CONVERT,
		NOT_A_FUNCTION
	};
};


#endif  //  __FunctionConstants_h
