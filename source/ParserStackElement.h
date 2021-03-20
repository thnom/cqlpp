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


#ifndef __ParserStackElement_h
#define __ParserStackElement_h


class ParserStackElement;
typedef StackList< ParserStackElement > ParserStack;
typedef ListElement< ParserStackElement, ParserStack > ParserStackElementListElement;


class ParserStackElement : public ParserStackElementListElement
{
protected :

protected :
	friend class Parser;

	pSelectExpression currentSelectExpression_;
	pExpression currentExpression_;

	bool batchMode_;
	bool cascade_;
	bool creatingUniqueIndex_;
	bool declaringCursor_;
	bool doingColumns_;
	bool doingColumnElement_;
	bool echo_;
	bool embeddedInput_;
	bool escape_;
	bool insertWithSelect_;
	bool preparing_;
	bool restrict_;
	bool selectInto_;
	bool shuttingDown_;
	bool statementEnded_;
	bool unaryMinusFlag_;

public :

	ParserStackElement( void );
	~ParserStackElement( void );
};

typedef ParserStackElement *pParserStackElement;


#endif  //  __ParserStackElement_h
