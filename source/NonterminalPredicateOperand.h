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


#ifndef __NonterminalPredicateOperand_h
#define __NonterminalPredicateOperand_h


class NonterminalPredicateOperand : public AbstractPredicateOperand
{
	Predicate *descendent_;
	UNI descendentNumber_;

public :

	NonterminalPredicateOperand( SqlHandle& );
	~NonterminalPredicateOperand( void );

	void adjustPredicateTree( void );
	ColumnSpecification *col( void ) { return 0; }
	Predicate *descendent( void ) { return descendent_; }
	void descendent( Predicate *p ) { descendent_ = p; }
	US dictionaryLength( void );
	UL entries( void ) { return 0; }
	bool identifierPush( void ) { return false; }
	Instruction *ins( void ) { return 0; }
	SegmentedKeyGroup *kg( void ) { return 0; }
	bool notSegmentable( void );
	void processViewData( List< Predicate >&, ExpressionColumnList&, InstructionList& );
	void readDictionaryInformation( TempBuffer& );
	void resolve( void ) { }
	void setSkips( void );
	PredicateType type( void ) { return NONTERMINAL; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef NonterminalPredicateOperand *pNonterminalPredicateOperand;


#endif  //  __NonterminalPredicateOperand_h
