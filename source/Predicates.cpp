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


#include "CqlSqlInclude.h"


AbstractPredicateOperand::AbstractPredicateOperand( SqlHandle& sqlh ) : dbsql_( sqlh ), res_( RESOLUTIONS_NOT_SET )
{
}


AbstractPredicateOperand::~AbstractPredicateOperand( void )
{
}


AbstractPredicateOperand *AbstractPredicateOperand::createObject( SqlHandle& sqlh, PredicateType pType )
{
	AbstractPredicateOperand *apo = 0;

	switch( pType )
	{
	case NONTERMINAL :
		apo = new NonterminalPredicateOperand( sqlh );
		break;

	case TERMINAL :
		apo = new TerminalPredicateOperand( sqlh );
		break;

	case MIXED :
	case PREDICATE_UNKNOWN :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	if( apo )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	return apo;
}


AbstractPredicateOperand& AbstractPredicateOperand::operator = ( const AbstractPredicateOperand& other )
{
	res_ = other.res_;
	return *this;
}


bool NonterminalPredicateOperand::notSegmentable( void )
{
	return descendent_->notSegmentable();
}


void NonterminalPredicateOperand::setSkips( void )
{
}


void NonterminalPredicateOperand::processViewData( List< Predicate >& predlist, ExpressionColumnList&, InstructionList& )
{
	descendent_ = predlist[ static_cast< US >( descendentNumber_ ) ];
}


void NonterminalPredicateOperand::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> descendentNumber_;
	Predicate *desc = new Predicate( *buffer.dbsql() );
	desc->readDictionaryInformation( buffer );
}


US NonterminalPredicateOperand::dictionaryLength( void )
{
	return descendent_->dictionaryLength();
}


void NonterminalPredicateOperand::writeDictionaryInformation( TempBuffer& buffer )
{
	descendent_->writeDictionaryInformation( buffer );
}


NonterminalPredicateOperand::NonterminalPredicateOperand( SqlHandle& sqlh )
	: AbstractPredicateOperand( sqlh ),
	  descendent_( ((Predicate*)0) ),
	  descendentNumber_( 0 )
{
}


NonterminalPredicateOperand::~NonterminalPredicateOperand( void )
{
}


void NonterminalPredicateOperand::adjustPredicateTree( void )
{
	descendent_->adjustPredicateTree();
}


//  Note:  This probably needs to be a new kind of list, so that Predicate can be
//  part of two lists.  Alternatively, we can clone the predicate.


OptimizerPredicateList::OptimizerPredicateList( SqlHandle& dbsql ) : PredicateList( dbsql )
{
}


OptimizerPredicateList::~OptimizerPredicateList( void )
{
}


UNI OptimizerPredicateList::dictionaryLength( void )
{
	UNI _size;
	pPredicate pred;

	_size = sizeof( UNI );

	for( pred = first(); pred; pred = next() )
		_size += pred->dictionaryLength();

	return _size;
}


void OptimizerPredicateList::writeDictionaryInformation( TempBuffer& buffer )
{
	Predicate *pred;

	buffer << size();

	for( pred = first(); pred; pred = next() )
		pred->writeDictionaryInformation( buffer );
}


void OptimizerPredicateList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfPredicates, loop;

	buffer >> numberOfPredicates;

	for( loop = 0; loop < numberOfPredicates; loop++ )
	{
		Predicate *pred = new Predicate( *buffer.dbsql() );
		if( !pred )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		pred->readDictionaryInformation( buffer );

		add( pred );
	}
}


void OptimizerPredicateList::processViewData( InstructionList& il, ExpressionColumnList& expColList )
{
	pPredicate pred;
	for( pred = first(); pred; pred = next() )
		pred->processViewData( il, expColList );
}


Predicate *OptimizerPredicateList::followingPred( Predicate *pred )
{
	Predicate *lpred;

	for( lpred = first(); lpred; lpred = next() )
		if( lpred == pred )
			return lpred->next();

	return 0;
}


Predicate *OptimizerPredicateList::precedingPred( Predicate *pred )
{
	Predicate *lpred;

	for( lpred = first(); lpred; lpred = next() )
		if( lpred == pred )
			return lpred->prev();

	return 0;
}


void OptimizerPredicateList::cleanup( void )
{
	Predicate *pred;

	for( pred = first(); pred; pred = next() )
		pred->cleanup();
}


Predicate::Predicate( SqlHandle& sqlh )
	: PredicateListElement(),
	  brother_( 0 ),
	  brotherNumber_( 0 ),
	  columnType_( CQL_COLUMN_UNDEFINED_TYPE ),
	  combination_( COMBINATIONS_NOT_SET ),
	  dbsql_( sqlh ),
	  entries_( 0 ),
	  highPredicateNumber_( 0 ),
	  ins_( ((pInstruction)0) ),
	  instructionNumber_( 0 ),
	  left_( 0 ),
	  linkType_( LINK_TYPES_NOT_SET ),
	  lowPredicateNumber_( 0 ),
	  master_( 0 ),
	  nextSegment_( 0 ),
	  nextSegmentNumber_( 0 ),
	  predicateNumber_( 0 ),
	  res_( RESOLUTIONS_NOT_SET ),
	  right_( 0 ),
	  segmentedLength_( 0 ),
	  setFile_( 0 ),
	  slave_( 0 ),
	  third_( 0 ),
	  thirdNumber_( 0 ),
	  treeLevel_( 0 ),
	  type_( PREDICATE_UNKNOWN ),
	  brotherExists_( false ),
	  brotherKeyFormed_( false ),
	  correlatedLink_( false ),
	  doCompare_( false ),
	  doingRight_( false ),
	  entriesSet_( false ),
	  finishedRight_( false ),
	  firstRowExceedsTarget_( false ),
	  instructionExists_( false ),
	  leftExists_( false ),
	  leftIndex_( false ),
	  leftIsMaster_( false ),
	  leftIsTerminal_( false ),
	  linkPredicate_( false ),
	  masterCorrelated_( false ),
	  nextSegmentExists_( false ),
	  notSegmentable_( false ),
	  onlyOneRow_( false ),
	  outerJoin_( false ),
	  outerJoinFail_( false ),
	  partOfSegmentedKey_( false ),
	  reverseScan_( false ),
	  rightExists_( false ),
	  rightIndex_( false ),
	  rightIsTerminal_( false ),
	  skip_( false ),
	  teof_( false ),
	  thirdExists_( false ),
	  thirdIsTerminal_( false ),
	  uniqueKey_( false ),
	  usedInSegmentScan_( false )
{
}


Predicate::~Predicate( void )
{
}


bool Predicate::resolveCartesianProductLink( void )
{
	slave_->columnFile()->beginIsamOperation( ((US)slave_->kg()->KeyNumber()) );
	return slave_->columnFile()->firstRow();
}


void Predicate::zeroSlavePosition( void )
{
	if( linkType_ == CQL_TEMPORARY )
		slave_->position( 0 );
}


bool Predicate::resolveNextLinkWithIndex( void )
{
	RECID pos;

	if( linkType_ == CQL_OUTER )
		if( outerJoinFail_ )
			return false;

	//**********  GetColumnPointer was here.  After changes, value should already be in master_->ValueBuffer()

	if( linkType_ == EXISTING )
	{
		slave_->columnFile()->establishPosition( slave_->position(), ((US)slave_->kg()->KeyNumber()), true );
		AbstractType *masterVal = master_->columnFile()->getColumnValue( master_->col()->Cno() );
		slave_->columnFile()->clearConditions();

		//  true means freeable
		slave_->columnFile()->setConditionAV( slave_->col()->Cno(),
											  masterVal->avalue(),
											  CQL_COP_GREATER_OR_EQUAL,
											  true );
		if( !slave_->columnFile()->findNext( false ) )
			return false;
		pos = slave_->columnFile()->currentPosition();
		slave_->position( pos );
	}
	else
	{
		if( slave_->position() == 0 )
			return false;

		RECID rid;
		slave_->temporaryIndex()->bindColumn( 1, rid, slave_->positionNull(), false );
		slave_->temporaryIndex()->establishPosition( slave_->position(), 0, true );
		AbstractType *masterVal = master_->columnFile()->getColumnValue( master_->col()->Cno() );
		slave_->columnFile()->clearConditions();
		//  true means freeable
		slave_->columnFile()->setConditionAV( 0, masterVal->avalue(), CQL_COP_GREATER_OR_EQUAL, true );
		if( !slave_->temporaryIndex()->findNext( false ) )
			return false;
		slave_->columnFile()->establishPosition( rid, 0, true );
		pos = slave_->temporaryIndex()->currentPosition();
		slave_->position( pos );
	}

	AbstractType *masterVal = master_->columnFile()->getColumnValue( master_->col()->Cno() );
	AbstractType *slaveVal = slave_->columnFile()->getColumnValue( slave_->col()->Cno() );
	if( masterVal->nullflag() || slaveVal->nullflag() )
		return false;
	else if( *masterVal != *slaveVal )
		return false;

	return true;
}


bool Predicate::resolveLinkWithIndex( void )
{
	AbstractType *masterVal;

	if( linkType_ == EXISTING )
	{
		masterVal = master_->columnFile()->getColumnValue( master_->col()->Cno() );
		slave_->columnFile()->beginIsamOperation( ((US)slave_->kg()->KeyNumber()) );
		slave_->columnFile()->clearConditions();
		//  true means freeable
		slave_->columnFile()->setConditionAV( slave_->col()->Cno(),
											  masterVal->avalue(),
											  CQL_COP_GREATER_OR_EQUAL,
											  true );

		if( dataTracing )
			hAEnv->logPrintf(AbstractLogger::TRACEALL, "Link, master = %s\n", masterVal->avalue().asString().text() );

		if( !slave_->columnFile()->findFirst( false ) )
		{
			if( dataTracing )
				hAEnv->logPrintf(AbstractLogger::TRACEALL, "Link, master = %s, slave not found\n", masterVal->avalue().asString().text() );
			return false;
		}
		else
		{
			if( dataTracing )
				hAEnv->logPrintf(AbstractLogger::TRACEALL, "Link, master = %s, slave found\n", masterVal->avalue().asString().text() );
			slave_->position( slave_->columnFile()->currentPosition() );
		}
	}
	else
	{
		//  this bind is for retrieval
		bool nflag = false;
		masterVal = master_->columnFile()->getColumnValue( master_->col()->Cno() );
		RECID rid;
		slave_->temporaryIndex()->bindColumn( 1, rid, nflag, false );
		slave_->temporaryIndex()->beginIsamOperation( 0 );
		slave_->temporaryIndex()->clearConditions();
		//  true means freeable
		slave_->temporaryIndex()->setConditionAV( 0, masterVal->avalue(), CQL_COP_EQUAL, true );
		if( !slave_->temporaryIndex()->findFirst( false ) )
			return false;
		slave_->columnFile()->establishPosition( rid, 0, false );
		slave_->position( slave_->temporaryIndex()->currentPosition() );
	}

	AbstractType *slaveVal = slave_->columnFile()->getColumnValue( slave_->col()->Cno() );
	if( masterVal->nullflag() || slaveVal->nullflag() )
		return false;
	else if( *masterVal != *slaveVal )
		return false;

	if( outerJoin_ )
		outerJoinFail_ = false;

	return true;
}


bool Predicate::resolveLink( void )
{
	switch( linkType_ )
	{
	case EXISTING :
	case CQL_TEMPORARY :
		return resolveLinkWithIndex();

	case CPLINK :
		return resolveCartesianProductLink();

	default :
		break;
	}

	
	throw InternalErrorException( __FILE__, __LINE__ );
	return false;  //  dumb compiler
}


void Predicate::switchMasterAndSlave( void )
{
	TerminalPredicateOperand *tPredOp = master_;
	master_ = slave_;
	slave_ = tPredOp;

	if( leftIsMaster_ )
		leftIsMaster_ = false;
	else
		leftIsMaster_ = true;
}


void Predicate::findOrMakeIndex( void )
{
	pTerminalPredicateOperand termPredOp = ((pTerminalPredicateOperand)slave_);
	pColumnSpecification col = termPredOp->col();
	pAbstractTable columnFile = termPredOp->columnFile();
	pAbstractTable temporaryIndex;

	//
	//  if an index exists, it is already assign to kg
	//
	if( termPredOp->kg() )
	{
		linkType_ = EXISTING;
		return;
	}
	else
		linkType_ = CQL_TEMPORARY;

	dbsql_.beginTransaction();

	//
	//  make a temporary index
	//
	temporaryIndex = AbstractTable::createObject( dbsql_.aHandle(),	CQL_CQL_TEMPORARY );
	CqlColumnTypes *columnDescriptors[ 3 ];
	columnDescriptors[ 0 ] = new CqlColumnTypes( "data", col->type().typeType(), col->type().typeLength() );
	columnDescriptors[ 1 ] = new CqlColumnTypes( "recordID", CQL_INTEGER );
	columnDescriptors[ 2 ] = new CqlColumnTypes( CqlColumnTypes::CQL_COLUMN_UNDEFINED_TYPE );

	AccessorTypes *keyDescriptors[ 2 ];
	SegmentTypes *segs[ 2 ];
	keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_DUPLICATES_ALLOWED, segs );
	segs[ 0 ] = new SegmentTypes( "data", 0, SegmentTypes::CQL_ASCENDING );
	segs[ 1 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );

	keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

	temporaryIndex->create( CQL_CQL_TEMPORARY, dbsql_.temporaryName(), columnDescriptors, keyDescriptors );

	delete columnDescriptors[ 0 ];
	delete columnDescriptors[ 1 ];
	delete columnDescriptors[ 2 ];
	delete keyDescriptors[ 0 ];
	delete segs[ 0 ];
	delete segs[ 1 ];
	delete keyDescriptors[ 1 ];

	termPredOp->temporaryIndex( temporaryIndex );

	//  Bind to columnFile for read
	CqlColumnTypes ctype;
	bool nullflag;
	columnFile->getColumnInfo( col->Cno(), ctype, nullflag );
	AbstractType *at = AbstractType::createObject( ctype );
	columnFile->bindColumnAV( col->Cno(), at->avalue(), false, true );

	//  Now bind the same column to temporaryIndex (column 0) for write
	temporaryIndex->bindColumnAV( 0, at->avalue(), true, true );

	//  Bind the record identifier as temporaryIndex column 1 for write
	RECID pos;
	bool posNull = false;

	temporaryIndex->bindColumn( 1, pos, posNull, true );

	//
	//  now build the index
	//
	columnFile->beginIsamOperation( 0, false );

	bool result;
	for( result = columnFile->firstRow(); result; result = columnFile->nextRow() )
	{
		pos = columnFile->currentPosition();
		temporaryIndex->beginIsamOperation( 0 );
		temporaryIndex->addRow();
	}

	dbsql_.commitTransaction( false );
	temporaryIndex->unbindAllColumns();
	columnFile->unbindAllColumns();
	delete at;
}


void Predicate::combine( void )
{
	switch( res_ )
	{
	case NORESOLVE :
	case RES_LINK :
	case RES_CLINK :
	case SEGMENTED :
		return;

	default :
		break;
	}

	if( skip_ )
		return;

	if( type_ == TERMINAL )
		return;

	//  combine descendents
	if( left_->type() == NONTERMINAL )
		left_->descendent()->combine();

	if( right_->type() == NONTERMINAL )
		right_->descendent()->combine();

	switch( combination_ )
	{
	case ONLY1 :
		setFile( left_->descendent()->setFile() );
		break;

	case ONLY2 :
		setFile( right_->descendent()->setFile() );
		break;

	case UN12 :
		setFile( left_->descendent()->setFile() );
		makeUnion( right_->descendent()->setFile() );
		break;

	case INT12 :
		setFile( left_->descendent()->setFile() );
		intersection( right_->descendent()->setFile() );
		break;

	default :
		throw InternalErrorException( __FILE__, __LINE__ );
	}
}


void Predicate::makeUnion( AbstractTable *otherSet )
{
	dbsql_.beginTransaction();

	RECID pos;
	bool posNull = false;

	otherSet->bindColumn( 0, pos, posNull, false );
	setFile_->bindColumn( 0, pos, posNull, true );

	otherSet->beginIsamOperation( 0 );

	bool result;
	for( result = otherSet->firstRow(); result; result = otherSet->nextRow() )
	{
		setFile_->beginRowOperation();

		//
		//  duplicate error is O.K. here
		//
		try
		{
			setFile_->addRow();
		}
		catch( DuplicateRowException& )
		{
			//  do nothing
		}
	}

	dbsql_.commitTransaction( false );
}


void Predicate::intersection( AbstractTable *otherSet )
{
	bool atTopOfSet = true;
	RECID previousPos, currentPos = 0;

	dbsql_.beginTransaction();

	RECID pos;
	bool posNull;
	setFile_->bindColumn( 0, pos, posNull, false );
	otherSet->setCondition( 0, pos, posNull, CQL_COP_EQUAL );

	setFile_->beginIsamOperation( 0 );

	bool result;
	for( result = setFile_->firstRow(); result; result = setFile_->nextRow() )
	{
		previousPos = currentPos;
		currentPos = setFile_->currentPosition();

		otherSet->beginIsamOperation( 0 );

		if( !otherSet->findFirst( false ) )
		{
			//
			//  not in otherSet, so delete from setFile_
			//
			setFile_->deleteRow();

			if( atTopOfSet )
				setFile_->beginIsamOperation( 0 );
			else
				setFile_->establishPosition( previousPos, 0, true );
		}
		else
			atTopOfSet = false;
	}

	dbsql_.commitTransaction( false );
}


void Predicate::setTerminalType( bool correlated, OptimizerPredicateList& linkPreds )
{
	pTerminalPredicateOperand leftOp, rightOp;
	pInstruction leftIns, rightIns;
	Instruction::OperationCodes leftOpCode, rightOpCode;
	pBinaryOperatorInstruction binaryIns;
	BinaryOperatorInstruction::BinaryOperators predOp;
	pIdentifierInstruction idIns1, idIns2;
	NI resolvable;

	leftOp = ((pTerminalPredicateOperand)left_);
	rightOp = ((pTerminalPredicateOperand)right_);
	leftIns = leftOp->ins();
	rightIns = rightOp->ins();
	leftOpCode = leftIns->OpCode();
	rightOpCode = rightIns->OpCode();

	if( ( !leftOp || leftOpCode != IDENTIFIER_PUSH ) && ( !rightOp || rightOpCode != IDENTIFIER_PUSH ) )
	{
		res_ = NORESOLVE;
		return;
	}

	//
	//  check for resolvable operator
	//
	binaryIns = ((pBinaryOperatorInstruction)ins_);
	predOp = binaryIns->BinaryOp();

	switch( predOp )
	{
	case OPERATOR_EQUALS :
		break;

	case OUTER_EQUAL :
	case OPERATOR_GREATER_OR_EQUAL :
	case OPERATOR_GREATER :
	case OPERATOR_LESS_OR_EQUAL :
	case OPERATOR_LESS :
		notSegmentable_ = true;
		break;

	case OPERATOR_LIKE :
		notSegmentable_ = true;

		//
		//  LIKE is resolvable if all metacharacters are at the end
		//
		resolvable = checkForResolvableLike();
		if( !resolvable )
		{
			res_ = NORESOLVE;
			return;
		}
		break;

	default :
		res_ = NORESOLVE;
		notSegmentable_ = true;
		return;
	}

	if( ( predOp == OPERATOR_EQUALS || predOp == OUTER_EQUAL ) && leftOpCode == IDENTIFIER_PUSH && rightOpCode == IDENTIFIER_PUSH )
	{
		idIns1 = ((pIdentifierInstruction)leftIns);
		idIns2 = ((pIdentifierInstruction)rightIns);
		if( idIns1->col() == idIns2->col() )
		{
			res_ = NORESOLVE;
			return;
		}

		makeLink( correlated, linkPreds );
		return;
	}
	else if( leftOpCode == IDENTIFIER_PUSH && rightOpCode == IDENTIFIER_PUSH )
	{
		res_ = NORESOLVE;
		return;
	}

	//
	//  At this point we have either identifier==constant or, possibly, identifier==sub_query.
	//  Reject if either side is sub-query
	//
	if( leftOpCode == CORRELATED_PUSH || leftOpCode == SUBQUERY_PUSH || rightOpCode == CORRELATED_PUSH || rightOpCode == SUBQUERY_PUSH )
	{
		res_ = NORESOLVE;
		return;
	}

	if( leftOpCode == IDENTIFIER_PUSH )
	{
		if( leftOp->res() == RESOLVE )
			res_ = RESOLVE;
		else
		{
			res_ = NORESOLVE;
			return;
		}
	}
	else
	{
		if( rightOp->res() == RESOLVE )
			res_ = RESOLVE;
		else
		{
			res_ = NORESOLVE;
			return;
		}
	}

	//
	//  the predicate res_olution is RESOLVE if we are still here
	//

	setKeySpan();

	switch( predOp )
	{
	case OPERATOR_EQUALS :
	case OPERATOR_LIKE :
		reverseScan_ = false;
		doCompare_ = true;
		firstRowExceedsTarget_ = false;
		break;

	case OPERATOR_GREATER :
		reverseScan_ = false;
		doCompare_ = false;
		firstRowExceedsTarget_ = true;
		break;

	case OPERATOR_GREATER_OR_EQUAL :
		reverseScan_ = false;
		doCompare_ = false;
		firstRowExceedsTarget_ = false;
		break;

	case OPERATOR_LESS :
		reverseScan_ = true;
		doCompare_ = false;
		firstRowExceedsTarget_ = true;
		break;

	case OPERATOR_LESS_OR_EQUAL :
		reverseScan_ = true;
		doCompare_ = false;
		firstRowExceedsTarget_ = false;
		break;

	default :
		break;
	}
}


void Predicate::setNonterminalType( OptimizerPredicateList& segmentablePredicateList )
{
	pNonterminalPredicateOperand left_Ntp, right_Ntp;
	pPredicate rightPred, leftPred;
	pBinaryOperatorInstruction binaryIns, leftIns, rightIns;

	if( !left_ || left_->type() == TERMINAL || !right_ || right_->type() == TERMINAL || ins_->OpCode() != BINARY_OPERATOR )
	{
		res_ = NORESOLVE;
		combination_ = COMBINATIONS_NOT_SET;
		return;
	}

	left_Ntp = ((pNonterminalPredicateOperand)left_);
	right_Ntp = ((pNonterminalPredicateOperand)right_);
	binaryIns = ((pBinaryOperatorInstruction)ins_);
	leftPred  = left_Ntp->descendent();
	rightPred = right_Ntp->descendent();
	leftIns = ((pBinaryOperatorInstruction)leftPred->ins());
	rightIns = ((pBinaryOperatorInstruction)rightPred->ins());
	
	switch( binaryIns->BinaryOp() )
	{
	case OPERATOR_AND :
		if( ( left_->notSegmentable() || right_ && right_->notSegmentable() ) || ( rightPred->res() == RESOLVE && !rightPred->doCompare() ) )
			notSegmentable_ = true;
		else
		{
			//
			//  add to segmentable predicate list
			//
			segmentablePredicateList.add( this );
		}

		switch( left_->res() )
		{
		case RESOLVE :
			switch( right_->res() )
			{
			case RESOLVE :
				//
				//  is this part of a > (>=)/< (<=) pair?
				//
				if( leftPred->slave()->kg()->KeyNumber() == rightPred->slave()->kg()->KeyNumber() && leftPred->doCompare() == false && rightPred->doCompare() == false )
				{
					if( leftPred->ins()->OpCode() == BINARY_OPERATOR )
					{
						switch( leftIns->BinaryOp() )
						{
						case OPERATOR_GREATER :
						case OPERATOR_GREATER_OR_EQUAL :
							if( rightIns->OpCode() == BINARY_OPERATOR )
							{
								switch( rightIns->BinaryOp() )
								{
								case OPERATOR_LESS :
								case OPERATOR_LESS_OR_EQUAL :
									leftPred->brother( rightPred );
									break;

								default :
									break;
								}
							}
							break;

						case OPERATOR_LESS :
						case OPERATOR_LESS_OR_EQUAL :
							if( rightIns->OpCode() == BINARY_OPERATOR )
							{
								switch( rightIns->BinaryOp() )
								{
								case OPERATOR_GREATER :
								case OPERATOR_GREATER_OR_EQUAL :
									rightPred->brother( leftPred );
									break;

								default :
									break;
								}
							}
							break;

						default :
							break;
						}
					}
				}

				if( leftPred->brother() )
				{
					res_ = CQPARTIAL;
					combination_ = ONLY1;
					right_->setSkips();
				}
				else if( rightPred->brother() )
				{
					res_ = CQPARTIAL;
					combination_ = ONLY2;
					left_->setSkips();
				}
				else if( leftPred->doCompare() == true && leftPred->uniqueKey() == true )
				{
					res_ = CQPARTIAL;
					combination_ = ONLY1;
					setUniqueKey();
					right_->setSkips();
				}
				else if( rightPred->doCompare() == true && rightPred->uniqueKey() == true )
				{
					res_ = CQPARTIAL;
					combination_ = ONLY2;
					setUniqueKey();
					left_->setSkips();
				}
				else
				{
					res_ = CQPARTIAL;
					if( leftPred->left()->entries() < rightPred->left()->entries() )
					{
						combination_ = ONLY1;
						entries_ = leftPred->left()->entries();
						right_->setSkips();
					}
					else
					{
						combination_ = ONLY2;
						entries_ = rightPred->left()->entries();
						left_->setSkips();
					}
				}
				break;

			case CQPARTIAL :
				res_ = CQPARTIAL;
				if( leftPred->left()->entries() < rightPred->left()->entries() )
				{
					combination_ = ONLY1;
					entries_ = leftPred->left()->entries();
					right_->setSkips();
				}
				else
				{
					combination_ = ONLY2;
					entries_ = rightPred->left()->entries();
					left_->setSkips();
				}
				break;

			case NORESOLVE :
			case RES_LINK :
			case RES_CLINK :
			case CONSTANT :
			case RESOLUTIONS_NOT_SET :
				res_ = CQPARTIAL;
				combination_ = ONLY1;
				entries_ = leftPred->left()->entries();
				break;

			default :
				throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
			}
			break;

		case CQPARTIAL :
			res_ = CQPARTIAL;

			switch( right_->res() )
			{
			case RESOLVE :
			case CQPARTIAL :
				if( leftPred->left()->entries() < rightPred->left()->entries() )
				{
					combination_ = ONLY1;
					entries_ = leftPred->left()->entries();
					right_->setSkips();
				}
				else
				{
					combination_ = ONLY2;
					entries_ = rightPred->left()->entries();
					left_->setSkips();
				}
				break;

			case NORESOLVE :
			case RES_LINK :
			case RES_CLINK :
			case CONSTANT :
			case RESOLUTIONS_NOT_SET :
				combination_ = ONLY1;
				entries_ = leftPred->left()->entries();
				break;

			default :
				throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
			}
			break;

		case NORESOLVE :
		case RES_LINK :
		case RES_CLINK :
		case CONSTANT :
			switch( right_->res() )
			{
			case NORESOLVE :
			case RES_LINK :
			case RES_CLINK :
			case CONSTANT :
			case RESOLUTIONS_NOT_SET :
				res_ = NORESOLVE;
				combination_ = COMBINATIONS_NOT_SET;
				break;

			case CQPARTIAL :
			case RESOLVE :
				res_ = CQPARTIAL;
				combination_ = ONLY2;
				entries_ = rightPred->left()->entries();
				break;

			default :
				throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
			}
			break;

		case RESOLUTIONS_NOT_SET :
			res_ = NORESOLVE;
			combination_ = COMBINATIONS_NOT_SET;
			break;

		default :
			throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
		}
		break;

	case OPERATOR_OR :
		notSegmentable_ = true;

		switch( left_->res() )
		{
		case RESOLVE :
			switch( right_->res() )
			{
			case RESOLVE :
			case CQPARTIAL :
				res_ = right_->res();
				combination_ = UN12;
				if( leftPred->left()->entries() > rightPred->left()->entries() )
					entries_ = leftPred->left()->entries();
				else
					entries_ = rightPred->left()->entries();
				break;

			case NORESOLVE :
			case CONSTANT :
			case RESOLUTIONS_NOT_SET :
				res_ = NORESOLVE;
				combination_ = COMBINATIONS_NOT_SET;
				break;

			case RES_LINK :
			case RES_CLINK :
				res_ = RESOLVE;
				combination_ = ONLY1;
				entries_ = leftPred->left()->entries();
				break;

			default :
				throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
			}
			break;

		case CQPARTIAL :
			switch( right_->res() )
			{
			case RESOLVE :
			case CQPARTIAL :
				res_ = CQPARTIAL;
				combination_ = UN12;
				if( leftPred->left()->entries() > rightPred->left()->entries() )
					entries_ = leftPred->left()->entries();
				else
					entries_ = rightPred->left()->entries();
				break;

			case NORESOLVE :
			case CONSTANT :
			case RESOLUTIONS_NOT_SET :
				res_ = NORESOLVE;
				combination_ = COMBINATIONS_NOT_SET;
				break;

			case RES_LINK :
			case RES_CLINK :
				res_ = CQPARTIAL;
				combination_ = ONLY1;
				entries_ = leftPred->left()->entries();
				break;

			default :
				throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
			}
			break;

		case NORESOLVE :
		case RESOLUTIONS_NOT_SET :
			res_ = NORESOLVE;
			combination_ = COMBINATIONS_NOT_SET;
			break;

		default :
			throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
		}

	default :
		break;
	}
}


void Predicate::setPredicateType( OptimizerPredicateList& segmentablePredicateList, bool correlated, OptimizerPredicateList& linkPreds )
{
	switch( left_->type() )
	{
	case NONTERMINAL :

		if( right_ )
		{
			switch( right_->type() )
			{
			case NONTERMINAL :
				setNonterminalType( segmentablePredicateList );
				type_ = NONTERMINAL;
				return;

			case PREDICATE_UNKNOWN :
				type_ = NONTERMINAL;
				return;

			case TERMINAL :
				setTerminalType( correlated, linkPreds );
				type_ = MIXED;
				return;

			default :
				throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
			}
		}
		break;

	case TERMINAL :
		if( !right_ )
		{
			res_ = NORESOLVE;
			type_ = TERMINAL;
			return;
		}

		switch( right_->type() )
		{
		case TERMINAL :
			setTerminalType( correlated, linkPreds );
			type_ = TERMINAL;
			return;

		case NONTERMINAL :
			setNonterminalType( segmentablePredicateList );
			type_ = MIXED;
			return;

		default :
			throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
		}

	default :
		throw PredicateTreeInconsistentException( __FILE__, __LINE__ );
	}
}


void Predicate::classify( UNI tTreeLevel, UNI *predNumber, OptimizerPredicateList& segmentablePredicateList, bool correlated, OptimizerPredicateList& linkPreds )
{
	pNonterminalPredicateOperand ntpop;
	pPredicate pred;

	treeLevel( tTreeLevel );
	lowPredicateNumber( *predNumber );
	(*predNumber)++;

	if( left_ )
	{
		if( left_->type() == NONTERMINAL )
		{
			ntpop = ((pNonterminalPredicateOperand)left_);
			pred = ntpop->descendent();
			pred->classify( tTreeLevel + 1, predNumber, segmentablePredicateList, correlated, linkPreds );
			left_->res( pred->res() );
		}
		else if( left_->identifierPush() )
			left_->resolve();
		else
			left_->res( PredicateTypes::CONSTANT );
	}

	if( right_ )
	{
		if( right_->type() == PredicateTypes::NONTERMINAL )
		{
			ntpop = ((pNonterminalPredicateOperand)right_);
			pred = ntpop->descendent();
			pred->classify( tTreeLevel + 1, predNumber, segmentablePredicateList, correlated, linkPreds );
			right_->res( pred->res() );
		}
		else if( right_->identifierPush() )
			right_->resolve();
		else
			right_->res( PredicateTypes::CONSTANT );
	}

	if( third_ )
	{
		if( third_->type() == PredicateTypes::NONTERMINAL )
		{
			ntpop = ((pNonterminalPredicateOperand)third_);
			pred = ntpop->descendent();
			pred->classify( tTreeLevel + 1, predNumber, segmentablePredicateList, correlated, linkPreds );
		}
		else if( third_->identifierPush() )
			third_->resolve();
		else
			third_->res( PredicateTypes::CONSTANT );
	}

	highPredicateNumber( *predNumber );
	( *predNumber )++;

	setPredicateType( segmentablePredicateList, correlated, linkPreds );
}


void Predicate::processViewData( InstructionList& il, ExpressionColumnList& expColList )
{
	if( brotherExists_ )
		brother_ = ( *list() )[ static_cast< US >( brotherNumber_ ) ];

	if( leftExists_ )
	{
		if( leftIsTerminal_ )
		{
			left_ = new TerminalPredicateOperand( dbsql_ );
			if( !left_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
		else
		{
			left_ = new NonterminalPredicateOperand( dbsql_ );
			if( !left_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		left_->processViewData( *list(), expColList, il );
	}

	if( rightExists_ )
	{
		if( rightIsTerminal_ )
		{
			right_ = new TerminalPredicateOperand( dbsql_ );
			if( !right_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
		else
		{
			right_ = new NonterminalPredicateOperand( dbsql_ );
			if( !right_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		right_->processViewData( *list(), expColList, il );
	}

	if( thirdExists_ )
	{
		if( thirdIsTerminal_ )
		{
			third_ = new TerminalPredicateOperand( dbsql_ );
			if( !third_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
		else
		{
			third_ = new NonterminalPredicateOperand( dbsql_ );
			if( !third_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		third_->processViewData( *list(), expColList, il );
	}

	if( instructionExists_ )
		ins_ = il[ static_cast< US >( instructionNumber_ ) ];

	if( nextSegmentExists_ )
		nextSegment_ = ( *list() )[ static_cast< US >( nextSegmentNumber_) ];
}


void Predicate::cleanup( void )
{
	pTerminalPredicateOperand termPredOp;

	if( res_ == RES_LINK && linkType_ == CQL_TEMPORARY )
	{
		termPredOp = ((pTerminalPredicateOperand)slave_);
		if( termPredOp )
		{
			termPredOp->temporaryIndex()->close();
			termPredOp->temporaryIndex( 0 );
		}
	}

	if( setFile_ )
	{
		setFile_->close();
		setFile_ = 0;
	}
}


void Predicate::destroyTreeObjects( void )
{
	pNonterminalPredicateOperand ntpop;


	if( left_ )
	{
		if( left_->type() == NONTERMINAL )
		{
			ntpop = ((pNonterminalPredicateOperand)left_);
			ntpop->descendent()->destroyTreeObjects();
		}
	}

	if( right_ )
	{
		if( right_->type() == NONTERMINAL )
		{
			ntpop = ((pNonterminalPredicateOperand)right_);
			ntpop->descendent()->destroyTreeObjects();
		}
	}

	if( third_ )
	{
		if( third_->type() == NONTERMINAL )
		{
			ntpop = ((pNonterminalPredicateOperand)third_);
			ntpop->descendent()->destroyTreeObjects();
		}
	}

	if( left_ )
		delete left_;

	if( right_ )
		delete right_;

	if( third_ )
		delete third_;
}


US Predicate::dictionaryLength( void )
{
	UNI size;

	//
	//  flags:
	//    brotherExists_
	//    correlatedLink_
	//    doCompare_
	//    firstRowExceedsTarget_
	//    leftExists_
	//    leftIndex_
	//    leftIsMaster_
	//    leftIsTerminal_
	//    linkPredicate_
	//    masterCorrelated_
	//    nextSegmentExists_
	//    onlyOneRow_
	//    outerJoin_
	//    reverseScan_
	//    rightExists_
	//    rightIndex_
	//    rightIsTerminal_
	//    thirdExists_
	//    uniqueKey_

	size = sizeof( NI ) * 19;

	//
	//  scalar values:
	//    UNI brother_
	//    NI columnType_
	//    NI combination_
	//    UNI ins_truction
	//    NI linkType_
	//    UNI nextSegment_
	//    NI res_olution
	//    NI predicateType

	size += sizeof( UNI ) * 3 + sizeof( NI ) * 5;

	if( left_ )
		size += left_->dictionaryLength();
	if( right_ )
		size += right_->dictionaryLength();
	if( third_ )
		size += third_->dictionaryLength();

	return static_cast< US >( size );
}


void Predicate::writeDictionaryInformation( TempBuffer& buffer )
{
	UNI listPosition;

	buffer << brotherExists_
		   << combination_
		   << columnType_
		   << correlatedLink_
		   << doCompare_
		   << firstRowExceedsTarget_
		   << leftExists_
		   << instructionExists_
		   << leftIndex_
		   << leftIsMaster_
		   << leftIsTerminal_
		   << linkPredicate_
		   << masterCorrelated_
		   << nextSegmentExists_
		   << onlyOneRow_
		   << outerJoin_
		   << reverseScan_
		   << rightExists_
		   << rightIndex_
		   << rightIsTerminal_
		   << thirdExists_
		   << thirdIsTerminal_
		   << uniqueKey_
		   << brotherNumber_
		   << combination_
		   << instructionNumber_
		   << linkType_
		   << nextSegmentNumber_
		   << res_
		   << type_;

	if( leftExists_ )
		left_->writeDictionaryInformation( buffer );

	if( rightExists_ )
		right_->writeDictionaryInformation( buffer );

	if( thirdExists_ )
		third_->writeDictionaryInformation( buffer );

	if( linkPredicate_ )
	{
		if( leftIsMaster_ )
		{
			master_ = dynamic_cast< TerminalPredicateOperand* >( left_ );
			slave_ = dynamic_cast< TerminalPredicateOperand* >( right_ );
		}
		else
		{
			master_ = dynamic_cast< TerminalPredicateOperand* >( right_ );
			slave_ = dynamic_cast< TerminalPredicateOperand* >( left_ );
		}
	}

	if( brother_ )
		listPosition = brother_->position();
	else
		listPosition = 0;
	buffer << listPosition;

	if( ins_ )
		listPosition = ins_->position();
	else
		listPosition = 0;
	buffer << listPosition;
	
	if( nextSegment_ )
		listPosition = nextSegment_->position();
	else
		listPosition = 0;
	buffer << listPosition;
}


void Predicate::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> brotherExists_
		   >> combination_
		   >> columnType_
		   >> correlatedLink_
		   >> doCompare_
		   >> firstRowExceedsTarget_
		   >> leftExists_
		   >> instructionExists_
		   >> leftIndex_
		   >> leftIsMaster_
		   >> leftIsTerminal_
		   >> linkPredicate_
		   >> masterCorrelated_
		   >> nextSegmentExists_
		   >> onlyOneRow_
		   >> outerJoin_
		   >> reverseScan_
		   >> rightExists_
		   >> rightIndex_
		   >> rightIsTerminal_
		   >> thirdExists_
		   >> thirdIsTerminal_
		   >> uniqueKey_
		   >> brotherNumber_
		   >> combination_
		   >> instructionNumber_
		   >> linkType_
		   >> nextSegmentNumber_
		   >> res_
		   >> type_;

	if( leftExists_ )
	{
		if( leftIsTerminal_ )
		{
			left_ = new TerminalPredicateOperand( dbsql_ );
			if( !left_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
		else
		{
			left_ = new NonterminalPredicateOperand( dbsql_ );
			if( !left_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		left_->readDictionaryInformation( buffer );
	}

	if( rightExists_ )
	{
		if( rightIsTerminal_ )
		{
			right_ = new TerminalPredicateOperand( dbsql_ );
			if( !right_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
		else
		{
			right_ = new NonterminalPredicateOperand( dbsql_ );
			if( !right_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		right_->readDictionaryInformation( buffer );
	}

	if( thirdExists_ )
	{
		if( thirdIsTerminal_ )
		{
			third_ = new TerminalPredicateOperand( dbsql_ );
			if( !third_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
		else
		{
			third_ = new NonterminalPredicateOperand( dbsql_ );
			if( !third_ )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		third_->readDictionaryInformation( buffer );
	}

	buffer >> brotherNumber_;
	buffer >> instructionNumber_;
	buffer >> nextSegmentNumber_;

	if( linkPredicate_ )
	{
		if( leftIsMaster_ )
		{
			master_ = dynamic_cast< TerminalPredicateOperand* >( left_ );
			slave_ = dynamic_cast< TerminalPredicateOperand* >( right_ );
		}
		else
		{
			master_ = dynamic_cast< TerminalPredicateOperand* >( right_ );
			slave_ = dynamic_cast< TerminalPredicateOperand* >( left_ );
		}
	}
}


Predicate& Predicate::operator = ( const Predicate& other )
{
	brother_ = new Predicate( other.dbsql_ );
	if( !brother_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	*brother_ = *other.brother_;
	brotherNumber_ = other.brotherNumber_;
	columnType_ = other.columnType_;
	combination_ = other.combination_;
	entries_ = other.entries_;
	highPredicateNumber_ = other.highPredicateNumber_;

	if( other.ins_ )
	{
		ins_ = Instruction::createObject( dbsql_, other.ins_->OpCode(), other.ins_->BinaryOp(), other.ins_->FuncId(), other.ins_->UnaryOp(), other.ins_->TertiaryOp() );
		*ins_ = *other.ins_;
	}
	else
		ins_ = 0;

	instructionNumber_ = other.instructionNumber_;

	if( other.left_ )
	{
		left_ = AbstractPredicateOperand::createObject( dbsql_, other.left_->type() );
		*left_ = *other.left_;
		leftExists_ = true;
	}
	else
	{
		left_ = 0;
		leftExists_ = false;
	}

	linkType_ = other.linkType_;
	lowPredicateNumber_ = other.lowPredicateNumber_;

	if( other.right_ )
	{
		right_ = AbstractPredicateOperand::createObject( dbsql_, other.right_->type() );
		*right_ = *other.right_;
		rightExists_ = true;
	}
	else
	{
		right_ = 0;
		rightExists_ = false;
	}

	if( other.third_ )
	{
		third_ = AbstractPredicateOperand::createObject( dbsql_, other.third_->type() );
		*third_ = *other.third_;
		thirdExists_ = true;
	}
	else
	{
		third_ = 0;
		thirdExists_ = false;
	}

	if( other.master_ )
	{
		if( other.master_ == other.left_ )
		{
			master_ = dynamic_cast< TerminalPredicateOperand* >( left_ );
			leftIsMaster_ = true;
		}
		else
		{
			master_ = dynamic_cast< TerminalPredicateOperand* >( right_ );
			leftIsMaster_ = false;
		}
	}
	else
		master_ = 0;

	if( other.slave_ )
	{
		if( other.slave_ == other.left_ )
			slave_ = dynamic_cast< TerminalPredicateOperand* >( left_ );
		else
			slave_ = dynamic_cast< TerminalPredicateOperand* >( right_ );
	}
	else
		slave_ = 0;

	if( other.nextSegment_ )
	{
		nextSegment_ = new Predicate( other.dbsql_ );
		if( !nextSegment_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*nextSegment_ = *other.nextSegment_;
	}
	else
		nextSegment_ = 0;

	nextSegmentNumber_ = other.nextSegmentNumber_;
	res_ = other.res_;

	segmentedLength_ = other.segmentedLength_;

	setFile_ = AbstractTable::createObject( dbsql_.aHandle(), other.setFile_->ttype() );

	*setFile_ = *other.setFile_;

	thirdNumber_ = other.thirdNumber_;
	treeLevel_ = other.treeLevel_;
	type_ = other.type_;

	brotherExists_ = other.brotherExists_;
	brotherKeyFormed_ = other.brotherKeyFormed_;
	correlatedLink_ = other.correlatedLink_;
	doCompare_ = other.doCompare_;
	doingRight_ = other.doingRight_;
	entriesSet_ = other.entriesSet_;
	finishedRight_ = other.finishedRight_;
	firstRowExceedsTarget_ = other.firstRowExceedsTarget_;
	instructionExists_ = other.instructionExists_;
	leftExists_ = other.leftExists_;
	leftIndex_ = other.leftIndex_;
	leftIsMaster_ = other.leftIsMaster_;
	leftIsTerminal_ = other.leftIsTerminal_;
	linkPredicate_ = other.linkPredicate_;
	masterCorrelated_ = other.masterCorrelated_;
	nextSegmentExists_ = other.nextSegmentExists_;
	notSegmentable_ = other.notSegmentable_;
	onlyOneRow_ = other.onlyOneRow_;
	outerJoin_ = other.outerJoin_;
	outerJoinFail_ = other.outerJoinFail_;
	partOfSegmentedKey_ = other.partOfSegmentedKey_;
	reverseScan_ = other.reverseScan_;
	rightExists_ = other.rightExists_;
	rightIndex_ = other.rightIndex_;
	rightIsTerminal_ = other.rightIsTerminal_;
	skip_ = other.skip_;
	teof_ = other.teof_;
	thirdExists_ = other.thirdExists_;
	thirdIsTerminal_ = other.thirdIsTerminal_;
	uniqueKey_ = other.uniqueKey_;
	usedInSegmentScan_ = other.usedInSegmentScan_;

	return *this;
}


Predicate *Predicate::getTerminal( void )
{
	Predicate *lpred;

	if( usedInSegmentScan_ )
		return 0;

	if( type_ == TERMINAL )
	{
		usedInSegmentScan_ = true;
		return this;
	}

	if( doingRight_ )
	{
		if( finishedRight_ )
			return 0;

		if( right_->type() == TERMINAL )
		{
			finishedRight_ = true;
			usedInSegmentScan_ = true;
			return this;
		}

		return right_->descendent()->getTerminal();
	}

	if( left_->type() == TERMINAL )
	{
		doingRight_ = true;
		return getTerminal();
	}

	lpred = left_->descendent()->getTerminal();
	if( lpred )
		return lpred;

	doingRight_ = true;
	return getTerminal();
}


void Predicate::makeSet( void )
{
	pTableSpecification tableSpec;
	pAbstractTable file;
	pIdentifierInstruction identifierIns;
	pTerminalPredicateOperand leftTermPredOp, rightTermPredOp;

	leftTermPredOp = ((pTerminalPredicateOperand)left_);
	rightTermPredOp = ((pTerminalPredicateOperand)right_);
	if( leftTermPredOp->ins()->OpCode() == IDENTIFIER_PUSH )
		identifierIns = ((pIdentifierInstruction)leftTermPredOp->ins());
	else
		identifierIns = ((pIdentifierInstruction)rightTermPredOp->ins());

	tableSpec = identifierIns->col()->TtEl()->tableSpec();
	if( !tableSpec )
		throw InternalErrorException( __FILE__, __LINE__ );
	file = tableSpec->file();

	dbsql_.beginTransaction();

	setFile_ = AbstractTable::createObject( dbsql_.aHandle(), CQL_CQL_TEMPORARY );

	CqlColumnTypes *columnDescriptors[ 2 ];
	columnDescriptors[ 0 ] = new CqlColumnTypes( "recordID", CQL_INTEGER );
	columnDescriptors[ 1 ] = new CqlColumnTypes( CqlColumnTypes::CQL_COLUMN_UNDEFINED_TYPE );

	AccessorTypes *keyDescriptors[ 2 ];
	SegmentTypes *segs[ 2 ];
	keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_DUPLICATES_ALLOWED, segs );
	segs[ 0 ] = new SegmentTypes( "recordID", 0, SegmentTypes::CQL_ASCENDING );
	segs[ 1 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );

	keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

	setFile_->create( CQL_CQL_TEMPORARY, dbsql_.temporaryName(), columnDescriptors, keyDescriptors );

	delete columnDescriptors[ 0 ];
	delete columnDescriptors[ 1 ];
	delete keyDescriptors[ 0 ];
	delete segs[ 0 ];
	delete segs[ 1 ];
	delete keyDescriptors[ 1 ];

	RECID pos;
	bool posNull = false;
	setFile_->bindColumn( 0, pos, posNull, true );

	bool result;
	for( result = tableSpec->firstRowMatchingPredicate( *this ); result; result = tableSpec->nextRowMatchingPredicate() )
	{
		pos = file->currentPosition();
		setFile_->beginRowOperation();
		try
		{
			setFile_->addRow();
		}
		catch( CqlException& ex )
		{
			dbsql_.rollbackTransaction();
			throw ex;
		}
	}

	dbsql_.commitTransaction( false );

#if 0
	if( setFile_->CheckPropagationFlags() == CQL_FAILURE )
		return dbsql_.Return( INTERNAL_ERROR, __FILE__, __LINE__ );
#endif
}


bool Predicate::checkForResolvableLike( void )
{
	pTerminalPredicateOperand termPredOp;
	pValueInstruction valueIns;
	pStringElement stringEl;
	pNC pattern = ((pNC)0), p;

	if( left_->type() == TERMINAL )
	{
		termPredOp = ((pTerminalPredicateOperand)left_);
		if( termPredOp->ins()->OpCode() == VALUE_PUSH )
		{
			valueIns = ((pValueInstruction)termPredOp->ins());
			CqlColumnType ctype = valueIns->El()->dataType().typeType();
			if( ctype == CQL_CHAR || ctype == CQL_CHARUC )
			{
				stringEl = ((pStringElement)valueIns->El());
				pattern = const_cast<char*>(stringEl->str().text());
			}
		}
	}

	if( !pattern )
	{
		if( right_->type() == TERMINAL )
		{
			termPredOp = ((pTerminalPredicateOperand)right_);
			if( termPredOp->ins()->OpCode() == VALUE_PUSH )
			{
				valueIns = ((pValueInstruction)termPredOp->ins());
				CqlColumnType ctype = valueIns->El()->dataType().typeType();
				if( ctype == CQL_CHAR || ctype == CQL_CHARUC )
				{
					stringEl = ((pStringElement)valueIns->El());
					pattern = const_cast<char*>(stringEl->str().text());
				}
			}
		}
	}

	if( !pattern )
		return false;

	p = pattern + ( strlen( pattern ) - 1 );
	while( p >= pattern )
	{
		if( *p != CQL_MANY_ANY && *p != CQL_ONE_ANY )
			break;

		p--;
	}

	if( p < pattern )
		return false;

	//
	//  At least one normal character.  Check for metacharacters preceding normal character
	//
	for( p--; p >= pattern; p-- )
	{
		if( *p == CQL_ONE_ANY || *p == CQL_MANY_ANY )
			return false;
	}

	//
	//  All normal characters, or normal followed by meta
	//
	return true;
}


void Predicate::makeLink( bool correlated, OptimizerPredicateList& pl )
{
	pIdentifierInstruction leftIns, rightIns;
	pColumnSpecification leftColumn, rightColumn;
	pTableTableElement leftTtEl, rightTtEl;

	leftIns = ((pIdentifierInstruction)left_->ins());
	if( !leftIns )
		throw InternalErrorException( __FILE__, __LINE__ );
	leftColumn = leftIns->col();
	if( !leftColumn )
		throw InternalErrorException( __FILE__, __LINE__ );
	leftTtEl = leftColumn->TtEl();
	if( !leftTtEl )
		throw InternalErrorException( __FILE__, __LINE__ );

	rightIns = ((pIdentifierInstruction)right_->ins());
	if( !rightIns )
		throw InternalErrorException( __FILE__, __LINE__ );
	rightColumn = rightIns->col();
	if( !rightColumn )
		throw InternalErrorException( __FILE__, __LINE__ );
	rightTtEl = rightColumn->TtEl();
	if( !rightTtEl )
		throw InternalErrorException( __FILE__, __LINE__ );

	linkPredicate_ = true;

	if( correlated == true )
	{
		correlatedLink_ = true;
		if( leftIns->correlated() == true )
		{
			masterCorrelated_ = true;
			master_ = ((pTerminalPredicateOperand)left_);
			slave_ = ((pTerminalPredicateOperand)right_);
			leftIsMaster_ = true;
		}
		else if( rightIns->correlated() == true )
		{
			masterCorrelated_ = true;
			master_ = ((pTerminalPredicateOperand)right_);
			slave_ = ((pTerminalPredicateOperand)left_);
			leftIsMaster_ = false;
		}
		else
			throw InternalErrorException( __FILE__, __LINE__ );
	}
	else
	{
		if( leftTtEl->tableNumber() > rightTtEl->tableNumber() )
		{
			master_ = ((pTerminalPredicateOperand)right_);
			slave_ = ((pTerminalPredicateOperand)left_);
			leftIsMaster_ = false;
		}
		else
		{
			master_ = ((pTerminalPredicateOperand)left_);
			slave_ = ((pTerminalPredicateOperand)right_);
			leftIsMaster_ = true;
		}
	}

	pl.add( this );
}


void Predicate::setKeySpan( void )
{
	pBinaryOperatorInstruction binaryOperatorIns;
	pTerminalPredicateOperand leftTermPredOp, rightTermPredOp, resolvedTermPredOp;
	pInstruction leftIns, rightIns;
	pIdentifierInstruction identifierIns;
	pValueInstruction valueIns;
	pTableSpecification tableSpec;
	pAbstractTable file;

	if( ins_->OpCode() != BINARY_OPERATOR )
		throw InternalErrorException( __FILE__, __LINE__ );

	binaryOperatorIns = ((pBinaryOperatorInstruction)ins_);

	switch( binaryOperatorIns->BinaryOp() )
	{
	case OPERATOR_EQUALS :
	case OPERATOR_LESS_OR_EQUAL :
	case OPERATOR_GREATER_OR_EQUAL :
	case OPERATOR_LESS :
	case OPERATOR_GREATER :
	{
		if( left_->type() != TERMINAL || right_->type() != TERMINAL )
			return;

		leftTermPredOp = ((pTerminalPredicateOperand)left_);
		leftIns = leftTermPredOp->ins();
		if( leftIns->OpCode() != IDENTIFIER_PUSH && leftIns->OpCode() != VALUE_PUSH )
			return;

		rightTermPredOp = ((pTerminalPredicateOperand)right_);
		rightIns = rightTermPredOp->ins();
		if( rightIns->OpCode() != IDENTIFIER_PUSH && rightIns->OpCode() != VALUE_PUSH )
			return;

		if( leftIns->OpCode() == IDENTIFIER_PUSH )
		{
			resolvedTermPredOp = leftTermPredOp;
			if( rightIns->OpCode() != VALUE_PUSH )
				throw InternalErrorException( __FILE__, __LINE__ );

			identifierIns = ((pIdentifierInstruction)leftIns);
			valueIns = ((pValueInstruction)rightIns);
		}
		else
		{
			resolvedTermPredOp = rightTermPredOp;
			if( leftIns->OpCode() != VALUE_PUSH )
				throw InternalErrorException( __FILE__, __LINE__ );

			identifierIns = ((pIdentifierInstruction)rightIns);
			valueIns = ((pValueInstruction)leftIns);
		}

		tableSpec = identifierIns->col()->TtEl()->tableSpec();
		if( !tableSpec )
			throw InternalErrorException( __FILE__, __LINE__ );

		file = tableSpec->file();
		file->beginIsamOperation( ((US)resolvedTermPredOp->kg()->KeyNumber()), false );

		switch( binaryOperatorIns->BinaryOp() )
		{
		case OPERATOR_EQUALS :
			//  true means freeable
			file->setConditionAV( 0, valueIns->El()->value().avalue(), CQL_COP_EQUAL, true );
			entries_ = file->estimateCost();
			break;

		case OPERATOR_LESS_OR_EQUAL :
			//  true means freeable
			file->setConditionAV( 0, valueIns->El()->value().avalue(), CQL_COP_LESS_OR_EQUAL, true );
			entries_ = file->estimateCost();
			break;

		case OPERATOR_GREATER_OR_EQUAL :
			//  true means freeable
			file->setConditionAV( 0,
								  valueIns->El()->value().avalue(),
								  CQL_COP_GREATER_OR_EQUAL,
								  true );
			entries_ = file->estimateCost();
			break;

		case OPERATOR_LESS :
			//  true means freeable
			file->setConditionAV( 0, valueIns->El()->value().avalue(), CQL_COP_LESS, true );
			entries_ = file->estimateCost();
			break;

		case OPERATOR_GREATER :
			//  true means freeable
			file->setConditionAV( 0, valueIns->El()->value().avalue(), CQL_COP_GREATER, true );
			entries_ = file->estimateCost();
			break;

		default :
			throw InternalErrorException( __FILE__, __LINE__ );
		}
		entriesSet_ = true;
		file->clearConditions();
		return;
	}

	case OPERATOR_IN :
	case OUTER_EQUAL :
	case OPERATOR_LIKE :
	case OPERATOR_AND :
	case OPERATOR_OR :
	case OPERATOR_TIMES :
	case OPERATOR_DIVIDE :
	case OPERATOR_PLUS :
	case OPERATOR_MINUS :
	case OPERATOR_NOTEQUAL :
		break;

	case NOT_A_BINARY_OPERATOR :
		throw InternalErrorException( __FILE__, __LINE__ );
	}
}


void Predicate::setTreeMarkers( void )
{
	doingRight_ = finishedRight_ = false;

	if( left_ && left_->type() == NONTERMINAL )
		left_->descendent()->setTreeMarkers();

	if( right_ && right_->type() == NONTERMINAL )
		right_->descendent()->setTreeMarkers();
}


void Predicate::adjustPredicateTree( void )
{
	if( !left_ )
	{
		if( !right_ )
			throw InternalErrorException( __FILE__, __LINE__ );

		combination_ = ONLY1;
		return;
	}

	else if( !right_ )
	{
		if( !left_ )
			throw InternalErrorException( __FILE__, __LINE__ );

		combination_ = ONLY2;
		return;
	}

	left_->adjustPredicateTree();
	right_->adjustPredicateTree();

	switch( combination_ )
	{
	case UN12 :
	case INT12 :
		if( left_->res() == SEGMENTED )
			combination_ = ONLY2;
		else if( right_->res() == SEGMENTED )
			combination_ = ONLY1;
		break;

	default :
		break;
	}
}


PredicateList::PredicateList( SqlHandle& sqlh ) : PredicateListBase(), dbsql_( sqlh ), predStack_(), root_( 0 )
{
}


PredicateList::~PredicateList( void )
{
}


void PredicateList::addToTree( Instruction *ins )
{
	ins->buildPredicateTreeElement( *this, predStack_ );
}


void PredicateList::processViewData( InstructionList& il, ExpressionColumnList& expColList )
{
	pPredicate pred;

	for( pred = first(); pred; pred = next() )
		pred->processViewData( il, expColList );
}


US PredicateList::dictionaryLength( void )
{
	UNI _size;
	pPredicate pred;

	//
	//  scalar values:
	//    UNI numberOfListElements
	//
	_size = sizeof( UNI );

	for( pred = first(); pred; pred = next() )
		_size += pred->dictionaryLength();

	return static_cast< US >( _size );
}


void PredicateList::writeDictionaryInformation( TempBuffer& buffer )
{
	pPredicate pred;

	buffer << size();

	for( pred = first(); pred; pred = next() )
		pred->writeDictionaryInformation( buffer );
}


void PredicateList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfPredicates, loop;
	pPredicate pred;

	buffer >> numberOfPredicates;

	for( loop = 0; loop < numberOfPredicates; loop++ )
	{
		pred = new Predicate( *buffer.dbsql() );
		if( !pred )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		pred->readDictionaryInformation( buffer );
		add( pred );
	}
}


PredicateList& PredicateList::operator = ( const PredicateList& cother )
{
	PredicateList& other = const_cast< PredicateList& >( cother );

	if( other.root_ )
	{
		root_ = new Predicate( dbsql_ );
		if( !root_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*root_ = *other.root_;
	}
	else
		root_ = 0;

	predStack_ = other.predStack_;

	Predicate *pred;
	for( pred = other.first(); pred; pred = other.next() )
	{
		Predicate *newPred = new Predicate( dbsql_ );
		if( !newPred )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*newPred = *pred;
		add( newPred );
	}

	return *this;
}


TerminalPredicateOperand::TerminalPredicateOperand( SqlHandle& sqlh )
	: AbstractPredicateOperand( sqlh ),
	  col_( 0 ),
	  columnNumber_( 0 ),
	  columnFile_( 0 ),
	  entries_( 0 ),
	  ins_( 0 ),
	  instructionNumber_( 0 ),
	  kg_( ((pSegmentedKeyGroup)0) ),
	  position_( 0 ),
	  positionNull_( false ),
	  temporaryIndex_( 0 ),
	  ttEl_( 0 ),
	  correlated_( false ),
	  identifierPush_( false ),
	  instructionExists_( false )
{
}


TerminalPredicateOperand::~TerminalPredicateOperand( void )
{
}


void TerminalPredicateOperand::setSkips( void )
{
}


void TerminalPredicateOperand::resolve( void )
{
	//
	//  it only comes here if it is an identifier push
	//
	IdentifierInstruction *idIns = dynamic_cast< IdentifierInstruction* >( ins_ );
	ColumnSpecification *tCol = idIns->col();

	//
	//  if predicate does not refer to first table, then it isn't resolved
	//
	if( tCol->TtEl()->tableNumber() != 0 )
	{
		res( NORESOLVE );
		return;
	}

	kg_ = tCol->TtEl()->indexExistsForColumn( tCol->Cno() );
	if( kg_ )
		res( RESOLVE );
	else
		res( NORESOLVE );
}


void TerminalPredicateOperand::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> identifierPush_
		   >> correlated_
		   >> instructionExists_
		   >> columnNumber_
		   >> instructionNumber_;
}


TerminalPredicateOperand& TerminalPredicateOperand::operator = ( const TerminalPredicateOperand& cother )
{
	TerminalPredicateOperand& other = const_cast< TerminalPredicateOperand& >( cother );

	if( other.col_ )
	{
		col_ = new ColumnSpecification( other.dbsql() );
		if( !col_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*col_ = *other.col_;
	}
	else
		col_ = 0;

	columnNumber_ = other.columnNumber_;

	if( other.columnFile_ )
	{
		columnFile_ = AbstractTable::createObject( dbsql().aHandle(), other.columnFile_->ttype() );
		*columnFile_ = *other.columnFile_;
	}
	else
		columnFile_ = 0;


	entries_ = other.entries_;

	if( other.ins_ )
	{
		ins_ = Instruction::createObject( dbsql(), other.ins_->OpCode(), other.ins_->BinaryOp(), other.ins_->FuncId(), other.ins_->UnaryOp(), other.ins_->TertiaryOp() );
		*ins_ = *other.ins_;
	}
	else
		ins_ = 0;

	instructionNumber_ = other.instructionNumber_;

	if( other.kg_ )
	{
		kg_ = new SegmentedKeyGroup;
		if( !kg_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*kg_ = *other.kg_;
	}
	else
		kg_ = 0;

	position_ = other.position_;

	if( other.temporaryIndex_ )
	{
		temporaryIndex_ = AbstractTable::createObject( dbsql().aHandle(), other.temporaryIndex_->ttype() );
		*temporaryIndex_ = *other.temporaryIndex_;
	}
	else
		temporaryIndex_ = 0;

	if( other.ttEl_ )
	{
		ttEl_ = TableTableElement::createObject( dbsql(), other.ttEl_->isView(), *other.ttEl_->absTableSpec() );
		*ttEl_ = *other.ttEl_;
	}

	correlated_ = other.correlated_;
	identifierPush_ = other.identifierPush_;
	instructionExists_ = other.instructionExists_;

	return *this;
}


void TerminalPredicateOperand::processViewData( List< Predicate >&, ExpressionColumnList& expColList, InstructionList& insList )
{
	pExpressionColumnListElement expColListEl = expColList[ columnNumber_ ];
	col_ = expColListEl->Column();
	ins_ = insList[ instructionNumber_ ];
}


US TerminalPredicateOperand::dictionaryLength( void )
{
	UNI size;

	//
	//  flags:
	//    correlated_
	//    identifierPush_
	//    instructionExists_
	//
	size = 2 * sizeof( NI );

	//
	//  scalar values:
	//    UNI col_umn (index into col_umn list)
	//    UNI ins_truction (index into ins_truction list)

	size += 2 * sizeof( UNI );

	return static_cast< US >( size );
}


void TerminalPredicateOperand::writeDictionaryInformation( TempBuffer& buffer )
{
	UNI listPosition;

	buffer << identifierPush_ << correlated_ << instructionExists_;

	if( col_ )
		listPosition = col_->position();
	else
		listPosition = 0;
	buffer << listPosition;

	if( ins_ )
		listPosition = ins_->position();
	else
		listPosition = 0;
	buffer << listPosition;
}


void TerminalPredicateOperand::setLinkFlag( void )
{
	ttEl_->setLinkFlag();
}


void TerminalPredicateOperand::adjustPredicateTree( void )
{
}
