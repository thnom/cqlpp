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


AbstractTableSpecification::AbstractTableSpecification( SqlHandle& sqlh )
	: aliasFlag_( false ),
	  authorizationId_( CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH ),
	  columns_(),
	  dbsql_( sqlh ),
	  dictionaryRecordLength_( 0 ),
	  numberOfColumns_( 0 ),
	  readOnly_( false ),
	  tableName_( CQL_MAXIMUM_TABLE_NAME_LENGTH ),
	  ttype_( CQL_UNDEFINED ),
	  variableLength_( false ),
	  viewsDerivedFromTable_( 0 )
{
}


AbstractTableSpecification::AbstractTableSpecification( SqlHandle& sqlh, const CqlString& name, const CqlString& authid )
	: aliasFlag_( false ),
	  authorizationId_( CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH ),
	  columns_(),
	  dbsql_( sqlh ),
	  dictionaryRecordLength_( 0 ),
	  numberOfColumns_( 0 ),
	  readOnly_( false ),
	  tableName_( CQL_MAXIMUM_TABLE_NAME_LENGTH ),
	  ttype_( CQL_UNDEFINED ),
	  variableLength_( false ),
	  viewsDerivedFromTable_( 0 )
{
	authorizationId_ = authid;
	tableName_ = name;
}


AbstractTableSpecification::~AbstractTableSpecification( void )
{
	columns_.destroy();
}


void AbstractTableSpecification::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> tableName_ >> authorizationId_ >> numberOfColumns_ >> viewsDerivedFromTable_ >> variableLength_ >> readOnly_;
	columns_.readDictionaryInformation( buffer );

	PermanentColumnSpecification *pcolspec;
	for( pcolspec = columns_.first() ; pcolspec; pcolspec =  columns_.next() )
	{
		ColumnSpecification *cs = dynamic_cast< ColumnSpecification* >( pcolspec );
		cs->TableName() = tableName_;
	}
}


void AbstractTableSpecification::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << tableName_ << authorizationId_ << numberOfColumns_ << viewsDerivedFromTable_ << variableLength_ << readOnly_;
	columns_.writeDictionaryInformation( buffer );
}


PermanentColumnSpecification *AbstractTableSpecification::findColumnUsingName( const CqlString& name )
{
	PermanentColumnSpecification *pcs;
	for( pcs = columns_.first(); pcs; pcs = columns_.next() )
		if( const_cast< CqlString& >( name ) == pcs->columnName() )
			return pcs;

	return 0;
}


AbstractTableSpecification& AbstractTableSpecification::operator = ( const AbstractTableSpecification& other )
{
	authorizationId_ = other.authorizationId_;
	columns_ = other.columns_;
	dictionaryRecordLength_ = other.dictionaryRecordLength_;
	numberOfColumns_ = other.numberOfColumns_;
	readOnly_ = other.readOnly_;
	tableName_ = other.tableName_;
	ttype_ = other.ttype_;
	variableLength_ = other.variableLength_;
	viewsDerivedFromTable_ = other.viewsDerivedFromTable_;
	aliasFlag_ = other.aliasFlag_;
	return *this;
}


void AbstractTableSpecification::clearConditions( void )
{
	PermanentColumnSpecification *pcs;
	UNI loop;
	for( pcs = columns_.first(), loop = 0; pcs; pcs = columns_.next(), loop++ )
	{
		//*************  Temporary until ViewSpecification::baseTable() is fixed
		AbstractTable *at = baseTable( static_cast< US >( loop ) );
		if( at )
			at->clearConditions();
	}
}


US AbstractTableSpecification::dictionaryLength( void )
{
	UNI size = CQL_MAXIMUM_FILE_NAME_LENGTH
		+ CQL_MAXIMUM_FILE_NAME_LENGTH
		+ sizeof( numberOfColumns_ )
		+ sizeof( viewsDerivedFromTable_ )
		+ sizeof( variableLength_ )
		+ sizeof( readOnly_ )
		+ columns_.dictionaryLength();

	return static_cast< US >( size );
}


Table::Table( SqlHandle& _dbsql, AbstractTableSpecification *ats ) : TableTableElement( _dbsql ), tableSpec_( dynamic_cast< TableSpecification* >( ats ) )
{
}


Table::~Table( void )
{
	if( tableSpec_ )
	{
		if( tableSpec_->aliasFlag() )
		{
			delete tableSpec_;
			tableSpec_ = 0;
		}
	}
}


void Table::readDictionaryInformation( TempBuffer& buffer )
{
	tableSpec_->readDictionaryInformation( buffer );
}


void Table::deleteRow( void )
{
	tableSpec_->deleteRow();
}


pAbstractTable Table::file( UNI )
{
	return tableSpec_->file();
}


void Table::magicLock( void )
{
}


void Table::getColumnInfo( US columnNumber, CqlColumnTypes& type, bool& nullFlag )
{
	tableSpec_->file()->getColumnInfo( columnNumber, type, nullFlag );
}


AbstractType *Table::getColumnValue( US columnNumber )
{
	return tableSpec_->file()->getColumnValue( columnNumber );
}


SegmentedKeyGroup *Table::indexExistsForColumn( US columnNumber )
{
	pSegmentedKeyGroup keyGroup;
	pAbstractColumnDescriptor col;

	for( keyGroup = tableSpec_->uniqueKeyGroups().first(); keyGroup; keyGroup = tableSpec_->uniqueKeyGroups().next() )
	{
		col = keyGroup->SegmentedKeyColumns().first();
		if( col->columnNumber() == columnNumber )
			return keyGroup;
	}

	for( keyGroup = tableSpec_->duplicateKeyGroups().first(); keyGroup; keyGroup = tableSpec_->duplicateKeyGroups().next() )
	{
		col = keyGroup->SegmentedKeyColumns().first();
		if( col->columnNumber() == columnNumber )
			return keyGroup;
	}

	return 0;
}


US Table::dictionaryLength( void )
{
	return tableSpec_->dictionaryLength();
}


void Table::writeDictionaryInformation( TempBuffer& buffer )
{
	tableSpec_->writeDictionaryInformation( buffer );
}


void Table::addRow( void )
{
	tableSpec_->addRow();
}


bool Table::firstRow( US keyNumber )
{
	return tableSpec_->firstRow( keyNumber );
}


bool Table::nextRow( void )
{
	return tableSpec_->nextRow();
}


bool Table::previousRow( void )
{
	return tableSpec_->previousRow();
}


bool Table::lastRow( US keyNumber )
{
	return tableSpec_->lastRow( keyNumber );
}


bool Table::firstUsingIndex( Column* )
{
	throw InternalErrorException( __FILE__, __LINE__ );
	return false;
}


bool Table::lastUsingIndex( Column* )
{
	throw InternalErrorException( __FILE__, __LINE__ );
	return false;
}


bool Table::countFromIndex( Column* )
{
	throw InternalErrorException( __FILE__, __LINE__ );
	return false;
}


void Table::flushDataToRecords( void )
{
	//  this should go away
}


TableSpecification::TableSpecification( SqlHandle& sqlh )
	: AbstractTableSpecification( sqlh ),
	  checkCondition_( sqlh ),
	  dictionaryRecordBuffer_( 0 ),
	  duplicateKeyGroups_(),
	  file_( ((pAbstractTable)0) ),
	  fileName_( CQL_MAXIMUM_FILE_NAME_LENGTH ),
	  foreignKeys_(),
	  numberOfKeys_( 0 ),
	  recordLength_( 0 ),
	  uniqueKeyGroups_()
{
}


TableSpecification::TableSpecification( SqlHandle& sqlh, const CqlString& name, const CqlString& authid )
	: AbstractTableSpecification( sqlh, name, authid ),
	  checkCondition_( sqlh ),
	  dictionaryRecordBuffer_( 0 ),
	  duplicateKeyGroups_(),
	  file_( 0 ),
	  fileName_( CQL_MAXIMUM_FILE_NAME_LENGTH ),
	  foreignKeys_(),
	  numberOfKeys_( 0 ),
	  recordLength_( 0 ),
	  uniqueKeyGroups_()
{
	file_ = AbstractTable::createObject( sqlh.aHandle(), CQL_CQL );
}


TableSpecification::~TableSpecification( void )
{
	duplicateKeyGroups_.destroy();

	foreignKeys_.destroy();
	uniqueKeyGroups_.destroy();
}


AbstractTable *TableSpecification::baseTable( US /*columnNumber*/ )
{
	return file_;
}


AbstractColumnDescriptor *TableSpecification::firstBaseTableColumn( AbstractTable **absTable )
{
	*absTable = file_;
	currentBaseTableColumn_ = file_->columns().first();
	return currentBaseTableColumn_;
}


AbstractColumnDescriptor *TableSpecification::nextBaseTableColumn( AbstractTable **absTable )
{
	*absTable = file_;
	currentBaseTableColumn_ = currentBaseTableColumn_->next();
	return currentBaseTableColumn_;
}


TableSpecification& TableSpecification::operator = ( const TableSpecification& cother )
{
	TableSpecification other = const_cast< TableSpecification& >( cother );
	dynamic_cast< AbstractTableSpecification& >( *this ) = dynamic_cast< AbstractTableSpecification& >( other );

	//
	//  Previous comment here was incorrect.  It is necessary to copy everything, because
	//  the old dictionary entries are deleted and completely new dictionary entries are
	//  added.
	//
	checkCondition_ = other.checkCondition_;
	//
	//  new dictionaryRecordBuffer will be constructed when AddDictionaryEntry is called
	//  for "this"
	//
	duplicateKeyGroups_ = other.duplicateKeyGroups_;
	file_ = other.file_;
	fileName_ = other.fileName_;
	foreignKeys_ = other.foreignKeys_;
	numberOfKeys_ = other.numberOfKeys_;
	//
	//  This will get recalculated, but copy it anyway
	//
	recordLength_ = other.recordLength_;
	uniqueKeyGroups_ = other.uniqueKeyGroups_;

	return *this;
}


bool TableSpecification::firstRowMatchingPredicate( Predicate& pred )
{
	pValueInstruction valueIns;
	pTerminalPredicateOperand leftTermPredOp, rightTermPredOp, resolvedTermPredOp;

	leftTermPredOp = ((pTerminalPredicateOperand)pred.left());
	rightTermPredOp = ((pTerminalPredicateOperand)pred.right());

	if( leftTermPredOp->ins()->OpCode() == VALUE_PUSH )
	{
		valueIns = ((pValueInstruction)leftTermPredOp->ins());
		resolvedTermPredOp = rightTermPredOp;
	}
	else
	{
		valueIns = ((pValueInstruction)rightTermPredOp->ins());
		resolvedTermPredOp = leftTermPredOp;
	}

	ConditionalOperators cop = CQL_COP_UNDEFINED;

	switch( pred.ins()->BinaryOp() )
	{
	case OPERATOR_EQUALS :
		cop = CQL_COP_EQUAL;
		break;

	case OPERATOR_LESS_OR_EQUAL :
		cop = CQL_COP_LESS_OR_EQUAL;
		break;

	case OPERATOR_GREATER_OR_EQUAL :
		cop = CQL_COP_GREATER_OR_EQUAL;
		break;

	case OPERATOR_LESS :
		cop = CQL_COP_LESS;
		break;

	case OPERATOR_GREATER :
		cop = CQL_COP_GREATER;
		break;

	case OPERATOR_LIKE :
		{
			//  Like is a special case because meta characters have to be stripped from the
			//  end of the string.
			AbstractValue *av = AbstractValue::createObject( valueIns->El()->value().avalue() );
			CharValue *cv = dynamic_cast< CharValue* >( av );
			NC *patternSubstring = CqlString::findPatternSubstringWithoutMetacharacters( cv->value() );
			const_cast< CqlString& >( cv->value() ) = patternSubstring;
			delete [] patternSubstring;
			file_->beginIsamOperation( resolvedTermPredOp->kg()->KeyNumber() );
			file_->setConditionAV( 0, *cv, CQL_COP_GREATER_OR_EQUAL, true );
			return file_->findFirst( false );
		}

	case OUTER_EQUAL :
	case OPERATOR_AND :
	case OPERATOR_OR :
	case OPERATOR_TIMES :
	case OPERATOR_DIVIDE :
	case OPERATOR_PLUS :
	case OPERATOR_MINUS :
	case OPERATOR_NOTEQUAL :
	case OPERATOR_IN :
	case NOT_A_BINARY_OPERATOR :
		throw InternalErrorException( __FILE__, __LINE__ );
	}

	file_->beginIsamOperation( resolvedTermPredOp->kg()->KeyNumber() );
	file_->setConditionAV( 0, valueIns->El()->value().avalue(), cop, true );
	return file_->findFirst( false );
}


bool TableSpecification::nextRowMatchingPredicate( void )
{
	return file_->findNext( false );
}


void TableSpecification::deleteCurrentRecord( void )
{
	file_->deleteRow();
}


void TableSpecification::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer.setBuffer( dictionaryRecordLength() + sizeof( UL ) );
	AbstractTableSpecification::writeDictionaryInformation( buffer );
	buffer << fileName_ << recordLength_ << numberOfKeys_;

	writeExpressionToDictionary( buffer );

	uniqueKeyGroups_.writeDictionaryInformation( buffer );
	duplicateKeyGroups_.writeDictionaryInformation( buffer );
	foreignKeys_.writeDictionaryInformation( buffer );
}


void TableSpecification::writeExpressionToDictionary( TempBuffer& buffer )
{
	checkCondition_.instructions().writeDictionaryInformation( buffer );
}


void TableSpecification::readExpressionFromDictionary( TempBuffer& buffer )
{
	checkCondition_.instructions().readDictionaryInformation( buffer );
}


US TableSpecification::expressionLength( void )
{
	return checkCondition_.instructions().dictionaryLength();
}


void TableSpecification::computeDictionaryRecordLength( void )
{
	UNI len;

	len = AbstractTableSpecification::dictionaryLength();
	len += columns().dictionaryLength();

	len = static_cast< US >( len + fileName_.length() );
	len += sizeof( recordLength_ );
	len += sizeof( numberOfKeys_ );

	len = ((US)( len + expressionLength() ) );
	len = ((US)( len + foreignKeys_.DictionaryLength() ) );
	len = ((US)( len + uniqueKeyGroups_.DictionaryLength() ) );
	len = ((US)( len + duplicateKeyGroups_.DictionaryLength() ) );

	dictionaryRecordLength( static_cast< US >( len ) );
}


void TableSpecification::assignValue( Column& col, PermanentColumnSpecification& pcs )
{
	col.ColumnExpression().evaluate();
	col.ColumnExpression().convertValueToAssignmentType( pcs );
	col.setAssignmentValue();
	file_->bindColumnAV( pcs.columnNumber(), col.assignmentValue().avalue(), true, false );
}


void TableSpecification::deleteRow( void )
{
	CqlColumnTypes type;
	pAbstractTableSpecification ats;
	pTableSpecification tableSpec;
	pAbstractTable ifile;
	CqlString name, prefix;

	dbsql().refers().table().beginIsamOperation( 0 );
	CqlString refersTableName = tableName();
	bool tableNameNull_;
	dbsql().refers().table().bindColumn( 0, refersTableName, tableNameNull_, false );
	CqlString refersAuthorizationId = authorizationId();
	bool authorizationIdNull_;
	dbsql().refers().table().bindColumn( 1, refersAuthorizationId, authorizationIdNull_, false );

	//  output column bindings
	CqlString fkTableName;
	bool fkTableNameNull;
	dbsql().refers().table().bindColumn( RefersDictionary::CID_TABLE_NAME, fkTableName, fkTableNameNull, false );
	CqlString fkAuthorizationId;
	bool fkAuthorizationIdNull;
	dbsql().refers().table().bindColumn( RefersDictionary::CID_AUTH, fkAuthorizationId, fkAuthorizationIdNull, false );
	US fkKeyNumber;
	bool fkKeyNumberNull;
	dbsql().refers().table().bindColumn( RefersDictionary::CID_FK_KEY_NUMBER, fkKeyNumber, fkKeyNumberNull, false );
	CqlString columnNumbers;
	bool columnNumbersNull;
	dbsql().refers().table().bindColumn( RefersDictionary::CID_COLUMN_NUMBERS, columnNumbers, columnNumbersNull, false );
	CqlString fkColumnNumbers;
	bool fkColumnNumbersNull;
	dbsql().refers().table().bindColumn( RefersDictionary::CID_FK_COLUMN_NUMBERS, fkColumnNumbers, fkColumnNumbersNull, false );

	bool result;
	result = dbsql().refers().table().findFirst( false );

	while( result )
	{
		//
		//  There are foreign keys.  Check whether this pending delete will violate referential integrity
		//

		const US *pColumnNumbers = reinterpret_cast< const US * >( columnNumbers.text() + sizeof( UL ) );
		const US *pFkColumnNumbers = reinterpret_cast< const US * >( fkColumnNumbers.text() + sizeof( UL ) );

		//
		//  now open the foreign key file
		//
		try
		{
			ats = dbsql().getDictionaryRecord( fkTableName, fkAuthorizationId );
		}
		catch( CqlException& ex )
		{
			throw ex;
		}

		tableSpec = ((pTableSpecification)ats);

		ifile = dbsql().openAbstractTable( tableSpec->fileName_.text(), ats->ttype() );
		{
			delete ats;
			throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		ifile->beginIsamOperation( fkKeyNumber );

		US numColumns, loop;
		for( loop = 0, numColumns = static_cast< US >( columns().size() ); loop < numColumns; loop++ )
		{
			AbstractType *val = file_->getColumnValue( *pColumnNumbers++ );
			ifile->bindColumnAV( *pFkColumnNumbers++, val->avalue(), true, false );
		}

		bool fkFindResult;
		try
		{
			fkFindResult = ifile->findFirst( false );
		}
		catch( CqlException& ex )
		{
			ifile->close();
			delete ats;
			throw ex;
		}

		ifile->close();
		delete ats;

		if( fkFindResult )
			throw IntegrityViolationException( __FILE__, __LINE__ );

		result = dbsql().refers().table().nextRow();

		//
		//  see if the next row in reference dictionary is for the same table/authid
		//
		if( result )
			if( refersTableName != tableName() || refersAuthorizationId != authorizationId() )
				result = false;
	}

	file_->deleteRow();
}


void TableSpecification::beginRowOperation( void )
{
	file_->beginRowOperation();
}


void TableSpecification::checkConditionColumnExecute( IdentifierInstruction& ins, Expression& tCheckCondition )
{
	CqlColumnTypes type;
	pAbstractValueElement val;
	pLiteralElement literalEl;

	AbstractType *at = file_->getColumnValue( ins.columnNumber() );

	val = AbstractValueElement::createObject( *at );
	literalEl = ((pLiteralElement)val);
	tCheckCondition.ves().pushValue( val );
}


bool TableSpecification::evaluateCheckCondition( Expression& tCheckCondition )
{
	pInstruction ins;
	pAbstractValueElement value;

	for( ins = tCheckCondition.instructions().first(); ins; ins = tCheckCondition.instructions().next() )
	{
		if( ins->OpCode() == InstructionConstants::IDENTIFIER_PUSH )
			checkConditionColumnExecute( dynamic_cast< IdentifierInstruction& >( *ins ), tCheckCondition );
		else
			ins->execute( tCheckCondition );
	}

	value = tCheckCondition.ves().popValue();

	if( !( *value ) )
		return false;
	else
		return true;
}


bool TableSpecification::identifyExpressionColumns( Expression& tCheckCondition )
{
	ExpressionColumnList& expColList = tCheckCondition.columns();
	pExpressionColumnListElement expColListEl;
	pPermanentColumnSpecification pcs;
	NI found;

	if( tCheckCondition.instructions().size() == 0 )
		return CQL_SUCCESS;

	US colNo;
	for( expColListEl = expColList.first(); expColListEl; expColListEl = expColList.next() )
	{
		for( pcs = columns().first(), found = CQL_NO, colNo = 0; found == CQL_NO && pcs; pcs = columns().next(), colNo++ )
		{
			if( expColListEl->Name() == pcs->columnName() )
			{
				expColListEl->Ins()->columnNumber( colNo );
				found = CQL_YES;
			}
		}

		if( found == CQL_NO )
			return false;
	}

	return true;
}


bool TableSpecification::firstRow( US keyNumber )
{
	file_->beginIsamOperation( keyNumber );
	return file_->firstRow();
}


bool TableSpecification::nextRow( void )
{
	return file_->nextRow();
}


bool TableSpecification::lastRow( US keyNumber )
{
	file_->beginIsamOperation( keyNumber );
	return file_->lastRow();
}


bool TableSpecification::previousRow( void )
{
	return file_->previousRow();
}


void TableSpecification::releaseMemory( void )
{
	if( dictionaryRecordBuffer_ )
	{
		delete [] dictionaryRecordBuffer_;
		dictionaryRecordBuffer_ = 0;
	}
}


US TableSpecification::numberOfBaseTables( void )
{
	return 1;
}


void TableSpecification::retrieveBaseTablePositions( pUC *p )
{
	RECID rid;
	rid = file_->currentPosition();

	if( dataTracing )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "Retrieved base table position %d\n", rid );

	memcpy( *p, &rid, sizeof( rid ) );
	(*p) += sizeof( rid );
}


void TableSpecification::retrieveBaseTableRows( pUC* p )
{
	RECID rid;
	memcpy( &rid, *p, sizeof( rid ) );
	(*p) += sizeof( rid );

	if( dataTracing )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "Calling establish position for %d\n", rid );

	file_->establishPosition( rid, 0, true );
}


void TableSpecification::readDictionaryInformation( TempBuffer& buffer )
{
	AbstractTableSpecification::readDictionaryInformation( buffer );
	buffer >> fileName_ >> recordLength_ >> numberOfKeys_;
	readExpressionFromDictionary( buffer );
	uniqueKeyGroups_.readDictionaryInformation( buffer );
	duplicateKeyGroups_.readDictionaryInformation( buffer );
	foreignKeys_.readDictionaryInformation( buffer );
}


void TableSpecification::deleteDictionaryEntry( void )
{
	dbsql().deleteDictionaryEntry( this );
}


void TableSpecification::deleteFiles( void )
{
	if( !file_ )
		file_ = AbstractTable::createObject( dbsql().aHandle(), CQL_CQL );

	file_->deleteFiles( fileName_ );
}


bool TableSpecification::referencesExist( void )
{
	return false;
}


void TableSpecification::processCascade( void )
{
	throw UnsupportedFeatureException( __FILE__, __LINE__ );
}


void TableSpecification::lockFile( void )
{
	throw UnsupportedFeatureException( __FILE__, __LINE__ );
}


void TableSpecification::renameToTemporary( void )
{
	throw UnsupportedFeatureException( __FILE__, __LINE__ );
}


bool TableSpecification::fileExists( void )
{
	return hAEnv->fileExists( fileName_ );
}


void TableSpecification::createIndexStructures( IndexNameListGroupList& indices )
{
	US keyNum;
	pIndexColumnName icn;
	pIndexNameListGroup inlg;
	pPermanentColumnSpecification pcs;
	pAbstractColumnDescriptor coldesc;
	pSegmentedKeyGroup skg;

	for( pcs = columns().first(), keyNum = 0; pcs; pcs = columns().next() )
	{
		if( pcs->duplicateIndex() || pcs->uniqueIndex() )
		{
			skg = new SegmentedKeyGroup( keyNum );
			if( !skg )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			keyNum++;

			skg->setIndexName(tableName());

			coldesc = AbstractColumnDescriptor::createObject( pcs->type(), pcs->columnNumber(), false );

			skg->SegmentedKeyColumns().add( coldesc );
			if( pcs->uniqueIndex() )
			{
				skg->SetUnique();
				uniqueKeyGroups_.add( skg );
			}
			else
				duplicateKeyGroups_.add( skg );
		}
	}

	for( inlg = indices.first(); inlg; inlg = indices.next(), keyNum++ )
	{
		skg = new SegmentedKeyGroup( keyNum );
		if( !skg )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		skg->setIndexName(tableName());

		for( icn = inlg->Icnl().first(); icn; icn = inlg->Icnl().next() )
		{
			pcs = findColumnUsingName( icn->s() );
			coldesc = AbstractColumnDescriptor::createObject( pcs->type(), pcs->columnNumber(), icn->descending() );
			skg->SegmentedKeyColumns().add( coldesc );
		}

		if( inlg->UniqueKey() )
		{
			skg->SetUnique();
			uniqueKeyGroups_.add( skg );
		}
		else if( inlg->PrimaryKey() )
		{
				hAEnv->logPrintf(AbstractLogger::TRACEALL,"%s:%d, primary key flag set, setting in segmented key group\n",
												 __FILE__,
												 __LINE__);
			skg->SetPrimaryKey();
			uniqueKeyGroups_.add( skg );
		}
		else if( inlg->DuplicateKey() )
			duplicateKeyGroups_.add( skg );
	}
}


void TableSpecification::addKeyToIsamFile( SegmentedKeyGroup& skg )
{
	SegmentTypes **stypes = new SegmentTypes*[ skg.SegmentedKeyColumns().size() + 1 ];
	if( !stypes )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	AccessorQualifierTypes::AccessorQualifierType aqtype = skg.Unique() ? AccessorQualifierTypes::CQL_NO_DUPLICATES : AccessorQualifierTypes::CQL_DUPLICATES_ALLOWED;
	AccessorTypes atype( AccessorTypes::CQL_TREE_INDEX, aqtype, stypes );
	Accessor *keydesc = Accessor::createObject( atype, skg.KeyNumber() );

	pAbstractColumnDescriptor colDesc;
	US loop;
	for( colDesc = skg.SegmentedKeyColumns().first(), loop = 0; colDesc; colDesc = skg.SegmentedKeyColumns().next(), loop++ )
	{
		stypes[ loop ] = new SegmentTypes( colDesc->columnNumber(), colDesc->descending() ? SegmentTypes::CQL_DESCENDING : SegmentTypes::CQL_ASCENDING );
		if( !stypes[ loop ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}
	stypes[ loop ] = new SegmentTypes( SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
	if( !stypes[ loop ] )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	file_->addIndexMember( keydesc );
}


void TableSpecification::createFiles( void )
{
	CqlColumnTypes **ctypes = new CqlColumnTypes*[ columns().size() + 1 ];
	if( !ctypes )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	pPermanentColumnSpecification col;
	UNI loop;
	for( col = columns().first(), loop = 0; col; col = columns().next(), loop++ )
	{
		ctypes[ loop ] = new CqlColumnTypes( col->type() );
		if( !ctypes[ loop ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		ctypes[ loop ]->typeName() = col->columnName();
	}
	ctypes[ loop ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );
	if( !ctypes[ loop ] )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	US _numberOfKeys = static_cast< US >( uniqueKeyGroups_.size() + duplicateKeyGroups_.size() );
	AccessorTypes **atypes = new AccessorTypes*[ _numberOfKeys + 1 ];
	if( !atypes )
		throw MemoryAllocationException( __FILE__, __LINE__ );
	pSegmentedKeyGroup skg;
	for( skg = uniqueKeyGroups_.first(), loop = 0; skg; skg = uniqueKeyGroups_.next(), loop++ )
	{
		SegmentTypes **stypes = new SegmentTypes*[ skg->SegmentedKeyColumns().size() + 1 ];
		if( !stypes )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		AbstractColumnDescriptor *acol;
		UNI loop2;
		for( acol = skg->SegmentedKeyColumns().first(), loop2 = 0; acol; acol = skg->SegmentedKeyColumns().next(), loop2++ )
		{
			col = columns()[ acol->columnNumber() ];
			stypes[ loop2 ] = new SegmentTypes( col->columnName(), acol->columnNumber(), acol->descending() ? SegmentTypes::CQL_DESCENDING : SegmentTypes::CQL_ASCENDING );
			if( !stypes[ loop2 ] )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
		stypes[ loop2 ] = new SegmentTypes( SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
		if( !stypes[ loop2 ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		atypes[ loop ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorTypes::CQL_NO_DUPLICATES, stypes );
		if( !atypes[ loop ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	for( skg = duplicateKeyGroups_.first(); skg; skg = duplicateKeyGroups_.next(), loop++ )
	{
		SegmentTypes **stypes = new SegmentTypes*[ skg->SegmentedKeyColumns().size() + 1 ];
		if( !stypes )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		AbstractColumnDescriptor *acol;
		UNI loop2;
		for( acol = skg->SegmentedKeyColumns().first(), loop2 = 0; acol; acol = skg->SegmentedKeyColumns().next(), loop2++ )
		{
			col = columns()[ acol->columnNumber() ];
			stypes[ loop2 ] = new SegmentTypes( col->columnName(), acol->columnNumber(), acol->descending() ? SegmentTypes::CQL_DESCENDING : SegmentTypes::CQL_ASCENDING );
			if( !stypes[ loop2 ] )
				throw MemoryAllocationException( __FILE__, __LINE__ );
		}
		stypes[ loop2 ] = new SegmentTypes( SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
		if( !stypes[ loop2 ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		atypes[ loop ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorTypes::CQL_DUPLICATES_ALLOWED, stypes );
		if( !atypes[ loop ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	atypes[ loop ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );
	if( !atypes[ loop ] )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	file_->create( CQL_CQL, fileName_, ctypes, atypes );
}


void TableSpecification::open( TableType tTtype )
{
	if( file_ && file_->fileOpen() )
		return;

	file_ = AbstractTable::createObject( dbsql().aHandle(), tTtype );
	file_->open( fileName_ );
}


void TableSpecification::close( void )
{
	if( file_ )
	{
		file_->close();
		delete file_;
		file_ = 0;
	}

	columns().destroy();
	releaseMemory();
}


SegmentedKeyGroup *TableSpecification::deleteKeyGroup( CqlString& iname )
{
	pSegmentedKeyGroup lskg;

	for( lskg = duplicateKeyGroups_.first(); lskg; lskg = duplicateKeyGroups_.next() )
	{
		if( iname == lskg->IndexName() )
		{
			duplicateKeyGroups_.remove( lskg );
			return lskg;
		}
	}

	for( lskg = uniqueKeyGroups_.first(); lskg; lskg = uniqueKeyGroups_.next() )
	{
		if( iname == lskg->IndexName() )
		{
			uniqueKeyGroups_.remove( lskg );
			return lskg;
		}
	}

	throw KeyNotFoundException( __FILE__, __LINE__ );
	//  dumb compiler
	return 0;
}


void TableSpecification::addRow( void )
{
	CqlColumnTypes type;
	pAbstractTableSpecification ats;
	pTableSpecification referencedTable;
	pAbstractTable ifile;
	pForeignKey fk;
	CqlString refTableName, refTablePrefix;
	pTableReferenceColumn referencingCol;
	pReferencedColumn referencedCol;

	PermanentColumnSpecification *pcolspec;
	for( pcolspec = columns().first() ; pcolspec; pcolspec =  columns().next() )
	{
		ColumnSpecification *colSpec = dynamic_cast< ColumnSpecification* >( pcolspec ); 
		if( colSpec->checkCondition().instructions().size() != 0 )
			if( !evaluateCheckCondition( colSpec->checkCondition() ) )
				throw IntegrityViolationException( __FILE__, __LINE__ );
	}

	if( checkCondition_.instructions().size() != 0 )
		if( !evaluateCheckCondition( checkCondition_ ) )
			throw IntegrityViolationException( __FILE__, __LINE__ );

	for( fk = foreignKeys_.first(); fk; fk = foreignKeys_.next() )
	{
		refTableName = fk->referencedTableName();
		refTablePrefix = fk->referencedTablePrefix();

		ats = dbsql().getDictionaryRecord( refTableName, refTablePrefix );
		if( !ats )
			throw InternalErrorException( __FILE__, __LINE__ );
		referencedTable = ((pTableSpecification)ats);

		ifile = dbsql().openAbstractTable( referencedTable->fileName_.text(), ats->ttype() );
		ifile->beginIsamOperation( fk->referencedTableKey() );

		for( referencingCol = fk->referencingColumns().first(), referencedCol = fk->referencedColumns().first();
			referencingCol;
			referencingCol = fk->referencingColumns().next(), referencedCol = fk->referencedColumns().next() )
		{
			AbstractType *at = file_->getColumnValue( referencingCol->columnNumber() );
			ifile->bindColumnAV( referencedCol->columnNumber(), at->avalue(), true, false );
		}

		if( ifile->findFirst( false ) == false )
		{
			ifile->close();
			delete ifile;
			delete referencedTable;
			throw IntegrityViolationException( __FILE__, __LINE__ );
		}
	}

	try
	{
		file_->addRow();
	}
	catch( ... )
	{
		file_->unbindAllColumns();
		throw;
	}

	file_->unbindAllColumns();
}


void TableSpecification::createDefaultKey( void )
{
	pPermanentColumnSpecification pcs;
	pAbstractColumnDescriptor coldesc;
	pSegmentedKeyGroup skg;

	skg = new SegmentedKeyGroup( 0 );
	if( !skg )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	sprintf( skg->IndexName(), "%s%d", tableName().text(), 0 );

	pcs = columns().first();

	coldesc = AbstractColumnDescriptor::createObject( pcs->type(), pcs->columnNumber(), false );
	skg->SegmentedKeyColumns().add( coldesc );
	duplicateKeyGroups_.add( skg );
}


void TableSpecification::addColumn( const ColumnSpecification& cs )
{
	pPermanentColumnSpecification pcs = new PermanentColumnSpecification( cs );
	if( !pcs )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	columns().add( pcs );
}


void TableSpecification::addIndexMember( SegmentedKeyGroup& keyGroup )
{
	pAbstractColumnDescriptor columnDesc;

	//
	//  This function receives a SegmentedKeyGroup object, which is the SQL level
	//  object that describes a key.  From the SegmentedKeyGroup object, a
	//  KeyDescriptor object must be produced for the call to the ISAM level
	//  AddIndexMember function.
	//

	Accessor *keyDesc = Accessor::createObject( AccessorTypes::CQL_TREE_INDEX );

	if( keyGroup.Unique() == CQL_YES )
		keyDesc->aqtypeType( AccessorQualifierTypes::CQL_NO_DUPLICATES );

	keyDesc->numberOfSegments( ((US)keyGroup.SegmentedKeyColumns().size() ) );

	//
	//  SegmentedKeyGroup and KeyDescriptor both describe segments using class
	//  ColumnDescriptorList.  We need to copy SegmentedKeyDescriptor's list to
	//  the KeyDescriptor object we are building.
	//

	US loop;
	for( columnDesc = keyGroup.SegmentedKeyColumns().first(), loop = 0; columnDesc; columnDesc = keyGroup.SegmentedKeyColumns().next(), loop++ )
	{
		AbstractSegmentDescriptor *seg = AbstractSegmentDescriptor::createObject( loop, columnDesc->descending() ? SegmentTypes::CQL_DESCENDING : SegmentTypes::CQL_ASCENDING );
		seg->column( columnDesc );
		keyDesc->segments().add( seg );
	}

	file_->addIndexMember( keyDesc );
}


US TableSpecification::findKeyNumberForColumnSet( SegmentedKeyGroupList& groups, pUS columnNumbers )
{
	pSegmentedKeyGroup keyGroup;
	pAbstractColumnDescriptor colDesc;
	pUS colNums;
	NI found;

	for( keyGroup = groups.first(); keyGroup; keyGroup = groups.next() )
	{
		colNums = columnNumbers;
		for( colDesc = keyGroup->SegmentedKeyColumns().first(), found = CQL_YES; found == CQL_YES && colDesc; colDesc = keyGroup->SegmentedKeyColumns().next() )
		{
			if( colDesc->columnNumber() != *colNums++ )
				found = CQL_NO;
		}

		if( found == CQL_YES )
			return keyGroup->KeyNumber();
	}

	throw KeyNotFoundException( __FILE__, __LINE__ );
	return 0;  //  dumb compiler
}


US TableSpecification::findUniqueKeyNumberForColumnSet( US *columnNumbers )
{
	return findKeyNumberForColumnSet( uniqueKeyGroups_, columnNumbers );
}


US TableSpecification::findDuplicateKeyNumberForColumnSet( US *columnNumbers )
{
	return findKeyNumberForColumnSet( duplicateKeyGroups_, columnNumbers );
}


void TableSpecification::createForeignKeyStructures( ForeignKeyNamesList& fkl )
{
	UNI tNumberOfColumns, loop;
	UL bufferSize;
	US us, keyNo, nextKeyNumber;
	pUS pus;
	pForeignKeyNames fkn;
	pStringListElement sleReferencing, sleReferenced;
	pAbstractTableSpecification referencedTable = ((pAbstractTableSpecification)0);
	pTableSpecification tableSpec;
	pPermanentColumnSpecification pcsReferencing, pcsReferenced;
	pColumnSpecification colSpec;
	pForeignKey fk;
	pTableReferenceColumn trc = ((pTableReferenceColumn)0);
	pReferencedColumn refCol = ((pReferencedColumn)0);
	pUC referencingColNumBuf = ((pUC)0), referencedColNumBuf = ((pUC)0), ingPtr, edPtr;
	pAbstractColumnDescriptor colDesc;
	pSegmentedKeyGroup skg;

	for( fkn = fkl.first(); fkn; fkn = fkl.next() )
	{
		//
		//  find base table name
		//
		if( !fkn->BaseTablePrefix() )
			fkn->BaseTablePrefix() = authorizationId();

		referencedTable = dbsql().getDictionaryRecord( fkn->BaseTableName(), fkn->BaseTablePrefix() );
		tableSpec = ((pTableSpecification)referencedTable);

		fk = new ForeignKey;
		if( !fk )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		fk->referencedTableName( fkn->BaseTableName() );
		fk->referencedTablePrefix( fkn->BaseTablePrefix() );

		tNumberOfColumns = fkn->ReferencingColumns().size();
		bufferSize = sizeof( UL ) + ( tNumberOfColumns * sizeof( US ) );
		referencingColNumBuf = new UC[ bufferSize ];
		if( !referencingColNumBuf )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		ingPtr = referencingColNumBuf;
		memcpy( ingPtr, &bufferSize, sizeof( bufferSize ) );
		ingPtr += sizeof( bufferSize );

		referencedColNumBuf = new UC[ bufferSize ];
		if( !referencedColNumBuf )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		edPtr = referencedColNumBuf;
		memcpy( edPtr, &bufferSize, sizeof( bufferSize ) );
		edPtr += sizeof( bufferSize );

		for(sleReferencing = fkn->ReferencingColumns().first(),
			sleReferenced = fkn->ReferencedColumns().first();

			sleReferencing;

			sleReferencing = fkn->ReferencingColumns().next(),
			sleReferenced = fkn->ReferencedColumns().next() )
		{
			pcsReferencing = findColumnUsingName( sleReferencing->s() );
			pcsReferenced = referencedTable->findColumnUsingName( sleReferenced->s() );
			trc = new TableReferenceColumn;
			if( !trc )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			trc->columnNumber( pcsReferencing->columnNumber() );
			us = ((US)pcsReferencing->columnNumber());
			memcpy( ingPtr, &us, sizeof( us ) );
			ingPtr += sizeof( us );

			refCol = new ReferencedColumn;
			if( !refCol )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			refCol->columnNumber( pcsReferenced->columnNumber() );
			us = ((US)pcsReferenced->columnNumber());
			memcpy( edPtr, &us, sizeof( us ) );
			edPtr += sizeof( us );

			fk->referencingColumns().add( trc );
			fk->referencedColumns().add( refCol );
			trc = ((pTableReferenceColumn)0);
			refCol = ((pReferencedColumn)0);
		}

		//
		//  Find the key in the foreign table which corresponds to the list of columns
		//
		keyNo = tableSpec->findUniqueKeyNumberForColumnSet( ((pUS)( referencedColNumBuf + sizeof( UL ) ) ) );
		fk->referencedTableKey( keyNo );
		foreignKeys_.add( fk );

		//
		//  There needs to be a key on this table on the referencing column(s) for checking during delete on foreign table.
		//  This key does not have to be unique, (although in general sensible table construction would use a unique key).
		//
		try
		{
			keyNo = findUniqueKeyNumberForColumnSet( ((pUS)( referencingColNumBuf + sizeof( UL ) ) ) );
		}
		catch( KeyNotFoundException& )
		{
			try
			{
				keyNo = findDuplicateKeyNumberForColumnSet( ((pUS)( referencingColNumBuf + sizeof( UL ) ) ) );
			}
			catch( KeyNotFoundException& )
			{
				//
				//  add a unique key for the referencing columns
				//
				nextKeyNumber = static_cast< US >( uniqueKeyGroups_.size() );
				keyNo = nextKeyNumber;
				skg = new SegmentedKeyGroup( nextKeyNumber );
				if( !skg )
					throw MemoryAllocationException( __FILE__, __LINE__ );

				for( loop = 0, pus = ((pUS)( referencingColNumBuf + sizeof( UL ) ) ); loop < tNumberOfColumns; loop++, pus++ )
				{
					colSpec = dynamic_cast< ColumnSpecification* >( columns()[ *pus ] );
					colDesc = AbstractColumnDescriptor::createObject( colSpec->type(), *pus, false );
					skg->SegmentedKeyColumns().add( colDesc );
				}

				uniqueKeyGroups_.add( skg );
			}
		}


		//
		//  Now we add an entry to the references dictionary, to enable lookup of the foreign key in the
		//  reverse direction during delete.
		//

		bool referencedTableNameNull = false;
		dbsql().refers().table().bindColumn( 0, fk->referencedTableName(), referencedTableNameNull, true );
		bool referencedTablePrefixNull = false;
		dbsql().refers().table().bindColumn( 1, fk->referencedTablePrefix(), referencedTablePrefixNull, true );
		bool tableNameNull = false;
		dbsql().refers().table().bindColumn( 2, tableName(), tableNameNull, true );
		bool authNull = false;
		dbsql().refers().table().bindColumn( 3, authorizationId(), authNull, true );
		bool keyNoNull = false;
		dbsql().refers().table().bindColumn( 4, keyNo, keyNoNull, true );
		bool referencedColNumBufNull = false;
		dbsql().refers().table().bindColumn( 5,
											 referencedColNumBuf,
											 bufferSize,
											 referencedColNumBufNull,
											 true,
											 true );
		bool referencingColNumBufNull = false;
		dbsql().refers().table().bindColumn( 6,
											 referencingColNumBuf,
											 bufferSize,
											 referencingColNumBufNull,
											 true,
											 true );

		dbsql().refers().table().beginRowOperation();
		dbsql().refers().table().addRow();

		delete [] referencingColNumBuf;
		referencingColNumBuf = ((pUC)0);
		delete [] referencedColNumBuf;
		referencedColNumBuf = ((pUC)0);
		referencedTable = ((pAbstractTableSpecification)0);
	}

	return;
}


void TableSpecification::findUniqueFileName( SqlHandle *sqlh )
{
	char *p1, *p2;
	NC limit;

	fileName_ = *sqlh->initialDirectory();
	if( fileName_.stringLength() )
		fileName_ += "/";

	unsigned int maxlen = CQL_MAXIMUM_FILE_NAME_LENGTH - fileName_.length();

	if( tableName().length() + authorizationId().length() < maxlen )
	{
		fileName_ += tableName();
		fileName_ += authorizationId();
	}

	else if( tableName().length() > ( maxlen / 2 ) && authorizationId().length() > ( maxlen / 2 ) )
	{
		CqlString tstring;
		tstring.setString( tableName().text(), ( maxlen / 2 ) );
		fileName_ += tstring;
		tstring.setString( authorizationId().text(), ( maxlen / 2 ) );
		fileName_ += tstring;
	}

	else if( tableName().length() > ( maxlen / 2 ) )
	{
		CqlString tstring;
		tstring.setString( tableName(), ( maxlen / 2 ) );
		fileName_ += tstring;
		fileName_ += authorizationId();
	}

	else
	{
		CqlString tstring;
		tstring = tableName();
		fileName_ += tstring;
		tstring.setString( authorizationId().text(), ( maxlen / 2 ) );
		fileName_ += tstring;
	}

	if( fileExists() )
	{
		p1 = const_cast<char*>(fileName_.text() + ( fileName_.length() - 1 ));
		p2 = p1 - 1;
		*p1 = 'A';
		*p2 = 'A';
		limit = 'Z' + 1;

		while( fileExists() )
		{
			(*p1)++;
			if( *p1 == limit )
			{
				*p1 = 'A';
				(*p2)++;
				if( *p2 == limit )
					throw FilenameCreationException( __FILE__, __LINE__ );
			}
		}
	}
}


void TableSpecification::copyData( AbstractTableSpecification& )
{
	throw NotImplementedException( __FILE__, __LINE__ );
}


void TableSpecification::checkPropagationFlags( void )
{
	//  this should go away
}


TableTable::TableTable( void ) : TableTableElementListBase(), processed( CQL_NO )
{
}


void TableTable::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfTables, loop;
	pTable table;
	pView view;
	pTableSpecification tableSpec;
	pViewSpecification viewSpec;
	pTableTableElement ttEl;

	buffer >> numberOfTables;

	for( loop = 0; loop < numberOfTables; loop++ )
	{
		bool isView;
		buffer >> isView;

		if( isView )
		{
			viewSpec = new ViewSpecification( *buffer.dbsql() );
			if( !viewSpec )
				throw MemoryAllocationException( __FILE__, __LINE__ );
			
			view = new View( *buffer.dbsql(), viewSpec );
			if( !view )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			ttEl = view;
		}
		else
		{
			tableSpec = new TableSpecification( *buffer.dbsql() );
			if( !tableSpec )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			table = new Table( *buffer.dbsql(), tableSpec );
			if( !table )
				throw MemoryAllocationException( __FILE__, __LINE__ );

			ttEl = table;
		}

		ttEl->readDictionaryInformation( buffer );
		add( ttEl );
	}
}


UNI TableTable::DictionaryLength( void )
{
	UNI _size;
	pTableTableElement ttEl;

	//
	//  scalar values:
	//    UNI numberOfListElements
	//
	_size = sizeof( UNI );

	for( ttEl = first(); ttEl; ttEl = next() )
		_size += ttEl->dictionaryLength();

	return _size;
}


void TableTable::writeDictionaryInformation( TempBuffer& buffer )
{
	pTableTableElement ttEl;

	buffer << size();

	for( ttEl = first(); ttEl; ttEl = next() )
	{
		buffer << ttEl->isView();
		ttEl->writeDictionaryInformation( buffer );
	}
}


NI TableTable::Assign( TableTable& other )
{
	processed = other.processed;

	return CQL_SUCCESS;
}


void TableTable::clearConditions( void )
{
	TableTableElement *table;
	
	for( table = first(); table; table = next() )
		table->clearConditions();
}


void TableTable::viewCleanup( void )
{
	TableTableElement *table;
	
	for( table = first(); table; table = next() )
		table->viewCleanup();
}


TablenameIndex::TablenameIndex( void ) : MemoryIndex()
{
}


TablenameIndex::~TablenameIndex( void )
{
}


void TablenameIndex::ClearInUseFlags( void )
{
	NI rc;

	for( rc = firstNode(); rc == CQL_SUCCESS; rc = nextNode() )
		CurrentNode()->ClearInUse();
}


pTablenameIndexNode TablenameIndex::CurrentNode( void )
{
	return ((pTablenameIndexNode)MemoryIndex::currentNode());
}


NI TablenameIndex::AddIndexNode( SqlHandle *dbsql, CqlString& name, CqlString& auth, AbstractTableSpecification *at )
{
	pTablenameIndexNode newNode;

	newNode = new TablenameIndexNode;
	if( !newNode )
		return dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

	newNode->Setup( name, auth, at );
	newNode->SetInUse();

	return MemoryIndex::addIndexNode( newNode );
}


NI TablenameIndex::FindEqualKey( SqlHandle *dbsql, const CqlString& name, const CqlString& auth )
{
	NI rc;
	pTablenameIndexNode tempNode;

	tempNode = new TablenameIndexNode;
	if( !tempNode )
		return dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

	tempNode->Setup( name, auth );

	rc = MemoryIndex::findEqualKey( tempNode );
	delete tempNode;
	return rc;
}


TablenameIndexNode::TablenameIndexNode( void ) : MemoryIndexNode(), name(), auth(), at( 0 ), inUse( CQL_NO )
{
}


TablenameIndexNode::~TablenameIndexNode( void )
{
	name.reset();
	auth.reset();
	if( at )
	{
		delete at;
		at = ((pAbstractTableSpecification)0);
	}
}


void TablenameIndexNode::releaseMemory( void )
{
	name.reset();
	auth.reset();
}


void TablenameIndexNode::Setup( const CqlString& na, const CqlString& au, AbstractTableSpecification *a )
{
	name = na;
	auth = au;
	at = a;
}


CqlConstants::CompareResult TablenameIndexNode::compareKeys( pMemoryIndexNode node2 )
{
	pTablenameIndexNode tnode = ((pTablenameIndexNode)node2);

	if( name < tnode->name )
		return THIS_LESS_THAN_OTHER;
	else if( name > tnode->name )
		return THIS_GREATER_THAN_OTHER;

	//  Equal, so check auth
	if( auth < tnode->auth )
		return THIS_LESS_THAN_OTHER;
	else if( auth > tnode->auth )
		return THIS_GREATER_THAN_OTHER;

	//  both are equal
	return THIS_EQUAL_TO_OTHER;
}


