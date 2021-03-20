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


#ifndef __TerminalPredicateOperand_h
#define __TerminalPredicateOperand_h


class TerminalPredicateOperand : public AbstractPredicateOperand
{
	BoundColumn *bc_;
	ColumnSpecification *col_;
	US columnNumber_;
	pAbstractTable columnFile_;
	UL entries_;
	Instruction *ins_;
	US instructionNumber_;
	SegmentedKeyGroup *kg_;
	RECID position_;
	bool positionNull_;
	AbstractTable *temporaryIndex_;
	TableTableElement *ttEl_;

	bool correlated_;
	bool identifierPush_;
	bool instructionExists_;

public :

	TerminalPredicateOperand( SqlHandle& );
	~TerminalPredicateOperand( void );

	TerminalPredicateOperand& operator = ( const TerminalPredicateOperand& );

	void adjustPredicateTree( void );
	BoundColumn& bc( void ) { return *bc_; }
	ColumnSpecification *col( void ) { return col_; }
	void col( ColumnSpecification *c ) { col_ = c; }
	AbstractTable *columnFile( void ) { return columnFile_; }
	void columnFile( AbstractTable *t ) { columnFile_ = t; }
	bool correlated( void ) { return correlated_; }
	Predicate *descendent( void ) { return 0; }
	US dictionaryLength( void );
	UL entries( void ) { return entries_; }
	Predicate *getPredicate( void ) { return 0; }
	bool identifierPush( void ) { return identifierPush_; }
	Instruction *ins( void ) { return ins_; }
	void ins( Instruction *in ) { ins_ = in; }
	SegmentedKeyGroup *kg( void ) { return kg_; }
	void kg( SegmentedKeyGroup *k ) { kg_ = k; }
	ColumnSpecification *linkCol( void );
	bool notSegmentable( void ) { return false; }
	RECID& position( void ) { return position_; }
	void position( RECID r ) { position_ = r; }
	bool& positionNull( void ) { return positionNull_; }
	void processViewData( List< Predicate >&, ExpressionColumnList&, InstructionList& );
	void readDictionaryInformation( TempBuffer& );
	void resolve( void );
	void setIdentifierPush( void ) { identifierPush_ = true; }
	void setLinkFlag( void );
	void setSkips( void );
	AbstractTable *temporaryIndex( void ) { return temporaryIndex_; }
	void temporaryIndex( AbstractTable *ti ) { temporaryIndex_ = ti; }
	TableTableElement *ttEl( void ) { return ttEl_; }
	void ttEl( TableTableElement *t ) { ttEl_ = t; }
	PredicateType type( void ) { return TERMINAL; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef TerminalPredicateOperand *pTerminalPredicateOperand;


#endif  //  __TerminalPredicateOperand_h
