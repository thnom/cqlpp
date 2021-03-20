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


#ifndef __ExpressionColumnListElement_h
#define __ExpressionColumnListElement_h


class ExpressionColumnListElement;
typedef List< ExpressionColumnListElement > ExpressionColumnListElementList;
typedef ListElement< ExpressionColumnListElement, ExpressionColumnListElementList> ExpressionColumnListElementBase;


class ExpressionColumnListElement : public  ExpressionColumnListElementBase, public CqlConstants, public ErrorConstants
{
	ColumnSpecification *column;
	AbstractValue *defaultValue_;
	pIdentifierInstruction ins;
	UNI instructionNumber;
	US length;
	CqlString name;
	CqlString prefix;
	CqlColumnTypes type;

	BFT defaultValueFlag : 1;
	BFT defaultValueNull : 1;
	BFT defaultValueUser : 1;
	BFT duplicateIndex : 1;
	BFT notNull : 1;
	BFT processed : 1;
	BFT uniqueIndex : 1;

public :

	ExpressionColumnListElement( void );
	~ExpressionColumnListElement( void );

	NI Assign( SqlHandle*, ExpressionColumnListElement& );
	ColumnSpecification *Column( void ) { return column; }
	AbstractValue *defaultValue( void ) { return defaultValue_; }
	NI DefaultValueFlag( void ) { return defaultValueFlag; }
	NI DefaultValueNull( void ) { return defaultValueNull; }
	NI DefaultValueUser( void ) { return defaultValueUser; }
	UNI DictionaryLength( void );
	NI DuplicateIndex( void ) { return duplicateIndex; }
	pIdentifierInstruction Ins( void ) { return ins; }
	US Length( void ) { return length; }
	CqlString& Name( void ) { return name; }
	NI NotNull( void ) { return notNull; }
	CqlString& Prefix( void ) { return prefix; }
	void processViewData( InstructionList& );
	NI Processed( void ) { return processed; }
	void readDictionaryInformation( TempBuffer& );
	void SetIns( pIdentifierInstruction i ) { ins = i; }
	void SetProcessed( void ) { processed = CQL_YES; }
	void SetColumn( ColumnSpecification *c ) { column = c; }
	NI SetDefaultValue( SqlHandle*, LiteralElement* /*el*/ );
	void SetDefaultValueFlag( void ) { defaultValueFlag = CQL_YES; }
	void SetDefaultValueNull( void ) { defaultValueNull = CQL_YES; }
	void SetDefaultValueUser( void ) { defaultValueUser = CQL_YES; }
	void SetDuplicateIndex( void ) { duplicateIndex = CQL_YES; }
	void SetLength( US l ) { length = l; }
	void SetNotNull( void ) { notNull = CQL_YES; }
	void SetType( CqlColumnTypes t ) { type = t; }
	void SetUniqueIndex( void ) { uniqueIndex = CQL_YES; }
	CqlColumnTypes Type( void ) { return type; }
	NI UniqueIndex( void ) { return uniqueIndex; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef ExpressionColumnListElement *pExpressionColumnListElement;


#endif  //  __ExpressionColumnListElement_h
