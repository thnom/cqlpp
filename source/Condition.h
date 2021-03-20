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


#ifndef __Condition_h
#define __Condition_h


class ConditionPredicate;
typedef List< ConditionPredicate > ConditionPredicateList;
typedef ListElement< ConditionPredicate, ConditionPredicateList > ConditionPredicateListElement;

class ConditionPredicate : public ConditionPredicateListElement, public CqlConstants
{
	Accessor *access_;
	BoundColumn *bc_;
	ConditionalOperators op_;
	ConditionPredicate *realPredicate_;  // used to map copy to original
	bool resolved_;

public :

	ConditionPredicate( BoundColumn* /*bc*/, ConditionalOperators /*op*/ );
	ConditionPredicate( ConditionPredicate& );
	virtual ~ConditionPredicate( void );

	void access( Accessor *ac ) { access_ = ac; }
	Accessor *access( void ) { return access_; }
	BoundColumn *bc( void ) { return bc_; }
	ConditionalOperators op( void ) { return op_; }
	ConditionPredicate *realPredicate( void ) { return realPredicate_; }
	bool resolved( void ) { return resolved_; }
	void setResolved( void ) { resolved_ = true; }
};


class AccessCondition;
typedef List< AccessCondition > AccessConditionList;
typedef ListElement< AccessCondition, AccessConditionList > AccessConditionListElement;


//  This class is used to assemble an access key.
class AccessCondition : public AccessConditionListElement, public CqlConstants
{
	Accessor *access_;
	UL cost_;
	ConditionalOperators op_;
	ConditionPredicateList predicates_;
	ConditionPredicateList trailingPredicateCandidates_;

public :

	AccessCondition( void );
	virtual ~AccessCondition( void );

	Accessor *access( void ) { return access_; }
	void access( Accessor *a ) { access_ = a; }
	UL cost( void ) { return cost_; }
	void cost( UL c ) { cost_ = c; }
	ConditionalOperators op( void ) { return op_; }
	void op( ConditionalOperators o ) { op_ = o; }
	ConditionPredicateList& predicates( void ) { return predicates_; }
	void setCost( void );
	ConditionPredicateList& trailingPredicateCandidates( void ) { return trailingPredicateCandidates_; }
};


class Condition : public CqlConstants
{
	AccessCondition *access_;
	ConditionPredicateList predicates_;
	bool findEndOfFile_;

public :

	Condition( void );
	virtual ~Condition( void );

	AccessCondition *access( void ) { return access_; }
	void access( AccessCondition *ac );
	void clearFindEndOfFile( void ) { findEndOfFile_ = false; }
	void destroy( void );
	bool findEndOfFile( void ) { return findEndOfFile_; }
	ConditionPredicateList& predicates( void ) { return predicates_; }
	void setFindEndOfFile( void ) { findEndOfFile_ = true; }
};


#endif  //  __Condition_h
