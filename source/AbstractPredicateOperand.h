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


#ifndef __AbstractPredicateOperand_h
#define __AbstractPredicateOperand_h


class AbstractPredicateOperand : public AbstractPredicateOperandListElement, public PredicateTypes, public ErrorConstants
{
	SqlHandle& dbsql_;
	enum Resolutions res_;

public :

	AbstractPredicateOperand( SqlHandle& );
	virtual ~AbstractPredicateOperand( void );

	AbstractPredicateOperand& operator = ( const AbstractPredicateOperand& );

	static AbstractPredicateOperand *createObject( SqlHandle&, PredicateType );
	SqlHandle& dbsql( void ) { return dbsql_; }
	enum Resolutions res( void ) { return res_; }
	void res( Resolutions r ) { res_ = r; }

	virtual void adjustPredicateTree( void ) = 0;
	virtual ColumnSpecification *col( void ) = 0;
	virtual US dictionaryLength( void ) = 0;
	virtual Predicate *descendent( void ) = 0;
	virtual UL entries( void ) = 0;
	virtual bool identifierPush( void ) = 0;
	virtual Instruction *ins( void ) = 0;
	virtual SegmentedKeyGroup *kg( void ) = 0;
	virtual bool notSegmentable( void ) = 0;
	virtual void processViewData( List< Predicate >&, ExpressionColumnList&, InstructionList& ) = 0;
	virtual void readDictionaryInformation( TempBuffer& ) = 0;
	virtual void resolve( void ) = 0;
	virtual void setSkips( void ) = 0;
	virtual PredicateType type( void ) = 0;
	virtual void writeDictionaryInformation( TempBuffer& ) = 0;
};

typedef AbstractPredicateOperand *pAbstractPredicateOperand;


#endif  //  __AbstractPredicateOperand_h
