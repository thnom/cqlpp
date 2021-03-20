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


#ifndef __Predicate_h
#define __Predicate_h


class Predicate;
typedef List< Predicate > PredicateListBase;
typedef ListElement< Predicate, PredicateListBase > PredicateListElement;


class Predicate : public PredicateListElement, public PredicateTypes, public ErrorConstants, public InstructionConstants, public CqlConstants
{
	Predicate *brother_;
	UNI brotherNumber_;
	CqlColumnTypes columnType_;
	Combinations combination_;
	SqlHandle& dbsql_;
	UL entries_;
	UNI highPredicateNumber_;
	Instruction *ins_;
	UNI instructionNumber_;
	pAbstractPredicateOperand left_;
	LinkTypes linkType_;
	UNI lowPredicateNumber_;
	pTerminalPredicateOperand master_;
	Predicate *nextSegment_;
	UNI nextSegmentNumber_;
	RECID position_;
	UNI predicateNumber_;
	Resolutions res_;
	pAbstractPredicateOperand right_;
	UNI segmentedLength_;
	pAbstractTable setFile_;
	pTerminalPredicateOperand slave_;
	pAbstractPredicateOperand third_;
	UNI thirdNumber_;
	UNI treeLevel_;
	PredicateType type_;

	bool brotherExists_;
	bool brotherKeyFormed_;
	bool correlatedLink_;
	bool doCompare_;
	bool doingRight_;
	bool entriesSet_;
	bool finishedRight_;
	bool firstRowExceedsTarget_;
	bool instructionExists_;
	bool leftExists_;
	bool leftIndex_;
	bool leftIsMaster_;
	bool leftIsTerminal_;
	bool linkPredicate_;
	bool masterCorrelated_;
	bool nextSegmentExists_;
	bool notSegmentable_;
	bool onlyOneRow_;
	bool outerJoin_;
	bool outerJoinFail_;
	bool partOfSegmentedKey_;
	bool positionNull_;
	bool reverseScan_;
	bool rightExists_;
	bool rightIndex_;
	bool rightIsTerminal_;
	bool skip_;
	bool teof_;
	bool thirdExists_;
	bool thirdIsTerminal_;
	bool uniqueKey_;
	bool usedInSegmentScan_;

public :

	Predicate( SqlHandle& );
	~Predicate( void );

	Predicate& operator = ( const Predicate& );

	void adjustPredicateTree( void );
	Predicate *brother( void ) { return brother_; }
	void brother( Predicate *p ) { brother_ = p; }
	bool checkForResolvableLike( void );
	void classify( UNI /*treeLevel*/, UNI * /*predNumber*/, OptimizerPredicateList&, bool /*correlated*/, OptimizerPredicateList& );
	void cleanup( void );
	void clearLeftExists( void ) { leftExists_ = false; }
	void clearRightExists( void ) { rightExists_ = false; }
	void clearTeof( void ) { teof_ = false; }
	Combinations combination( void ) { return combination_; }
	void combine( void );
	bool correlatedLink( void ) { return correlatedLink_; }
	void destroyTreeObjects( void );
	US dictionaryLength( void );
	bool doCompare( void ) { return doCompare_; }
	UL entries( void ) { return entries_; }
	bool entriesSet( void ) { return entriesSet_; }
	void findOrMakeIndex( void );
	void findSegmentedKey( void );
	Predicate *getTerminal( void );
	UNI highPredicateNumber( void ) { return highPredicateNumber_; }
	void highPredicateNumber( UNI no ) { highPredicateNumber_ = no; }
	Instruction *ins( void ) { return ins_; }
	void ins( Instruction *in ) { ins_ = in; }
	void intersection( pAbstractTable );
	pAbstractPredicateOperand left( void ) { return left_; }
	void left( pAbstractPredicateOperand val ) { left_ = val; }
	bool linkPredicate( void ) { return linkPredicate_; }
	LinkTypes linkType( void ) { return linkType_; }
	void linkType( LinkTypes lt ) { linkType_ = lt; }
	UNI lowPredicateNumber( void ) { return lowPredicateNumber_; }
	void lowPredicateNumber( UNI no ) { lowPredicateNumber_ = no; }
	void makeLink( bool /*correlated*/, OptimizerPredicateList&  );
	void makeSet( void );
	void makeUnion( pAbstractTable );
	pTerminalPredicateOperand master( void ) { return master_; }
	bool masterCorrelated( void ) { return masterCorrelated_; }
	Predicate *nextSegment( void ) { return nextSegment_; }
	void nextSegment( Predicate *nextSeg ) { nextSegment_ = nextSeg; }
	bool notSegmentable( void ) { return notSegmentable_; }
	bool partOfSegmentedKey( void ) { return partOfSegmentedKey_; }
	RECID& position( void ) { return position_; }
	bool& positionNull( void ) { return positionNull_; }
	UNI predicateNumber( void ) { return predicateNumber_; }
	void processViewData( InstructionList&, ExpressionColumnList& );
	void readDictionaryInformation( TempBuffer& );
	void res( Resolutions r ) { res_ = r; }
	bool resolveCartesianProductLink( void );
	bool resolveLink( void );
	bool resolveLinkWithIndex( void );
	bool resolveNextLinkWithIndex( void );
	pAbstractPredicateOperand right( void ) { return right_; }
	void right( pAbstractPredicateOperand val ) { right_ = val; }
	Resolutions res( void ) { return res_; }
	void setCorrelatedLink( void ) { correlatedLink_ = true; }
	void setDoCompare( void ) { doCompare_ = true; }
	pAbstractTable setFile( void ) { return setFile_; }
	void setFile( pAbstractTable sf ) { setFile_ = sf; }
	void setKeySpan( void );
	void setLeftExists( void ) { leftExists_ = true; }
	void setLinkPredicate( void ) { linkPredicate_ = true; }
	void setNonterminalType( OptimizerPredicateList& );
	void setPartOfSegmentedKey( void ) { partOfSegmentedKey_ = true; }
	void setPredicateType( OptimizerPredicateList&, bool /*correlated*/, OptimizerPredicateList& );
	void setNotSegmentable( void ) { notSegmentable_ = true; }
	void setOuterJoin( void ) { outerJoin_ = true; }
	void setRightExists( void ) { rightExists_ = true; }
	void setSkip( void ) { skip_ = true; }
	void setTeof( void ) { teof_ = true; }
	void setTerminalType( bool /*correlated*/, OptimizerPredicateList& );
	void setTreeMarkers( void );
	void setUniqueKey( void ) { uniqueKey_ = true; }
	bool skip( void ) { return skip_; }
	pTerminalPredicateOperand slave( void ) { return slave_; }
	void switchMasterAndSlave( void );
	bool teof( void ) { return teof_; }
	pAbstractPredicateOperand third( void ) { return third_; }
	void third( pAbstractPredicateOperand val ) { third_ = val; }
	UNI treeLevel( void ) { return treeLevel_; }
	void treeLevel( UNI val ) { treeLevel_ = val; }
	PredicateTypes::PredicateType type( void ) { return type_; }
	bool uniqueKey( void ) { return uniqueKey_; }
	void writeDictionaryInformation( TempBuffer& );
	void zeroSlavePosition( void );
};

typedef Predicate *pPredicate;


#endif  //  __Predicate_h
