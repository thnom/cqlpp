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


Column::Column( SqlHandle& sqlh )
	: ColumnListElement(),
	  alterColumnAdd( false ),
	  alterColumnDrop( false ),
	  alterColumnModify( false ),
	  assignmentValue_( 0 ),
	  bc_( 0 ),
	  bodyNumber( 0 ),
	  breakLevel( 0 ),
	  breakLevel2( 0 ),
	  brk( false ),
	  brk2( false ),
	  columnExpression( sqlh ),
	  computeBase( 0 ),
	  computeColumn( 0 ),
	  computeFlag( 0 ),
	  computeLimit( 0 ),
	  countIndex( false ),
	  dbsql_( sqlh ),
	  descending_( false ),
	  doAssignment( false ),
	  expressionLength( 0 ),
	  firstOperation( false ),
	  functionKey( false ),
	  indicator( false ),
	  invalidCalculation( false ),
	  justifyCenter( false ),
	  justifyRight( false ),
	  label(),
	  maxIndex( false ),
	  minIndex( false ),
	  noDup( false ),
	  orderByNumber( false ),
	  orderColumnNumber( 0 ),
	  orderSkip( 0 ),
	  patternOverride(),
	  prepush( false ),
	  processed( false ),
	  reportValue( 0 ),
	  viewName(),
	  valueRestored( false ),
	  wrapChar( false ),
	  wrapLevel( 0 ),
	  wrapTruncate( false ),
	  wrapWord( false )
{ }


Column::~Column( void )
{
}


void Column::encode( CqlString& output )
{
	reportValue->encode( output, true );
}


void Column::createReportValue( void )
{
	reportValue = AbstractType::createObject( columnExpression.valueExpressionType() );
}


void Column::AssignColumnExpression( pExpression *exp )
{
	(*exp) = &columnExpression;
}


UNI Column::DictionaryLength( void )
{
	UNI size;

	//
	//  flags:
	//    countIndex
	//    descending
	//    maxIndex
	//    minIndex
	//
	size = 4 * sizeof( NI );

	size += columnExpression.dictionaryLength();

	return size;
}


void Column::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << countIndex << descending_ << maxIndex << minIndex;
	columnExpression.writeDictionaryInformation( buffer );
}


void Column::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> countIndex >> descending_ >> maxIndex >> minIndex;
	columnExpression.readDictionaryInformation( buffer );
}


Column& Column::operator = ( const Column& other )
{
	assignmentValue_ = other.assignmentValue_;
	bodyNumber = other.bodyNumber;
	breakLevel = other.breakLevel;
	breakLevel2 = other.breakLevel2;
	columnExpression = other.columnExpression;
	computeBase = other.computeBase;
	computeColumn = other.computeColumn;
	computeFlag = other.computeFlag;
	computeLimit = other.computeLimit;
	expressionLength = other.expressionLength;
	label = other.label;
	orderColumnNumber = other.orderColumnNumber;
	orderSkip = other.orderSkip;
	patternOverride = other.patternOverride;

	if( other.reportValue )
	{
		reportValue = AbstractType::createObject( other.reportValue->columnType() );
		*reportValue = *other.reportValue;
	}
	else
		reportValue = 0;

	viewName = other.viewName;
	wrapLevel = other.wrapLevel;
	alterColumnAdd = other.alterColumnAdd;
	alterColumnDrop = other.alterColumnDrop;
	alterColumnModify = other.alterColumnModify;
	brk = other.brk;
	brk2 = other.brk2;
	countIndex = other.countIndex;
	descending_ = other.descending_;
	doAssignment = other.doAssignment;
	firstOperation = other.firstOperation;
	functionKey = other.functionKey;
	indicator = other.indicator;
	invalidCalculation = other.invalidCalculation;
	justifyCenter = other.justifyCenter;
	justifyRight = other.justifyRight;
	maxIndex = other.maxIndex;
	minIndex = other.minIndex;
	noDup = other.noDup;
	orderByNumber = other.orderByNumber;
	prepush = other.prepush;
	processed = other.processed;
	skip = other.skip;
	valueRestored = other.valueRestored;
	wrapChar = other.wrapChar;
	wrapTruncate = other.wrapTruncate;
	wrapWord = other.wrapWord;
	return *this;
}


void Column::setAssignmentValue( void )
{
	assignmentValue_ = AbstractType::createObject( columnExpression.value()->value().columnType() );
	*assignmentValue_ = columnExpression.value()->value();
}


ColumnSpecification::ColumnSpecification( SqlHandle& sqlh )
	: PermanentColumnSpecification( sqlh ),
	  authorizationId(),
	  cno( 0 ),
	  ifNumber( 0 ),
	  ttEl( ((pTableTableElement)0) ),
	  tableName(),
	  viewColumn( ((pColumn)0) ),
	  viewExpression( sqlh ),
	  isViewColumn( CQL_NO )
{
}


ColumnSpecification::ColumnSpecification( const ColumnSpecification& other )
	: PermanentColumnSpecification( const_cast< ColumnSpecification& >( other ).dbsql() ),
	  viewExpression( const_cast< ColumnSpecification& >( other ).dbsql() )
{
	authorizationId = other.authorizationId;
	cno = other.cno;
	ifNumber = other.ifNumber;
	ttEl = other.ttEl;
	tableName = other.tableName;
	viewColumn = other.viewColumn;
	viewExpression = other.viewExpression;
	isViewColumn = other.isViewColumn;
	dynamic_cast< PermanentColumnSpecification& >( *this ) = dynamic_cast< PermanentColumnSpecification& >( const_cast< ColumnSpecification& >( other ) );
}


ColumnSpecification::~ColumnSpecification( void )
{
}


ColumnSpecification& ColumnSpecification::operator = ( const ColumnSpecification& cother )
{
	authorizationId = cother.authorizationId;
	cno = cother.cno;
	ifNumber = cother.ifNumber;
	ttEl = cother.ttEl;
	tableName = cother.tableName;
	viewColumn = cother.viewColumn;
	viewExpression = cother.viewExpression;
	isViewColumn = cother.isViewColumn;
	ColumnSpecification& other = const_cast< ColumnSpecification& >( cother );
	PermanentColumnSpecification& pcsThis = dynamic_cast< PermanentColumnSpecification& >( *this );
	PermanentColumnSpecification& pcsOther = dynamic_cast< PermanentColumnSpecification& >( other );
	pcsThis = pcsOther;
	return *this;
}


NI ColumnSpecification::Assign( SqlHandle *_dbsql, ColumnSpecification& other )
{
	dynamic_cast< PermanentColumnSpecification& >( *this ) = dynamic_cast< PermanentColumnSpecification& >( other );

	authorizationId = other.authorizationId;

	cno = other.cno;

	if( other.viewColumn )
	{
		viewColumn = new Column( *_dbsql );
		if( !viewColumn )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		*viewColumn = *other.viewColumn;
	}
	else
		viewColumn = ((pColumn)0);

	ifNumber = other.ifNumber;

	if( other.ttEl )
	{
		ttEl = TableTableElement::createObject( *_dbsql, other.ttEl->isView(), *other.ttEl->absTableSpec() );
		*ttEl = *other.ttEl;
	}
	else
		ttEl = 0;

	tableName = other.tableName;

	viewExpression = other.viewExpression;
	isViewColumn = other.isViewColumn;
	return CQL_SUCCESS;
}


AbstractValueElement *ColumnSpecification::createValue( void )
{
	AbstractType *atype = ttEl->getColumnValue( cno );
	AbstractValueElement *el = AbstractValueElement::createObject( *atype );
	return el;
}


void ColumnSpecificationList::writeDictionaryInformation( TempBuffer& buffer )
{
	UNI listSize = size();
	buffer << listSize;

	pPermanentColumnSpecification pcs;

	for( pcs = first(); pcs; pcs = next() )
		pcs->writeDictionaryInformation( buffer );
}


void ColumnSpecificationList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI listSize, loop;
	pColumnSpecification pcs;

	buffer >> listSize;

	for( loop = 0; loop < listSize; loop++ )
	{
		pcs = new ColumnSpecification( *buffer.dbsql() );
		if( !pcs )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		pcs->readDictionaryInformation( buffer );

		add( pcs );
	}
}


US ColumnSpecificationList::dictionaryLength( void )
{
	UNI _size = 0;
	pPermanentColumnSpecification pcs;

	for( pcs = first(); pcs; pcs = next() )
		_size += pcs->dictionaryLength();

	return static_cast< US >( _size );
}


ColumnSpecificationList::ColumnSpecificationList( void ) : PermanentColumnSpecificationList()
{
}


ColumnSpecificationList& ColumnSpecificationList::operator = ( const ColumnSpecificationList& cother )
{
	ColumnSpecificationList& other = const_cast< ColumnSpecificationList& >( cother );

	// FIXED
	PermanentColumnSpecification *pcs;
	for( pcs= other.first(); pcs; pcs = other.next() )
	{
		ColumnSpecification *colSpec = dynamic_cast< ColumnSpecification* >( pcs );
		ColumnSpecification *newColSpec = new ColumnSpecification( colSpec->dbsql() );
		if( !newColSpec )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		*newColSpec = *colSpec;
		add( newColSpec );
	}

	return *this;
}


ColumnTable::ColumnTable( void ) : ColumnTableBase()
{
}


ColumnTable& ColumnTable::operator = ( const ColumnTable& other )
{
	destroy();

	Column *col, *newCol;
	for( col = const_cast< ColumnTable& >( other ).first(); col; col = const_cast< ColumnTable& >( other ).next() )
	{
		newCol = new Column( col->dbsql() );
		if( !newCol )
			throw MemoryAllocationException( __FILE__, __LINE__ );
		*newCol = *col;
		add( newCol );
	}

	return *this;
}


NI ColumnTable::SetExpressionTypes( SqlHandle* )
{
	Column *col;

	for( col = first(); col; col = next() )
		col->ColumnExpression().setExpressionType();

	return CQL_SUCCESS;
}


UNI ColumnTable::DictionaryLength( void )
{
	Column *col;
	UNI _size;

	//
	//  scalar values:
	//    UNI numberOfListElements
	//
	_size = sizeof( UNI );

	for( col = first(); col; col = next() )
		_size += col->DictionaryLength();

	return _size;
}


void ColumnTable::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << size();

	Column *col;

	for( col = first(); col; col = next() )
		col->writeDictionaryInformation( buffer );
}


void ColumnTable::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfColumns, loop;
	Column *col;

	buffer >> numberOfColumns;

	for( loop = 0; loop < numberOfColumns; loop++ )
	{
		col = new Column( *buffer.dbsql() );
		if( !col )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		col->readDictionaryInformation( buffer );

		add( col );
	}
}


void ExpressionColumnList::processViewData( InstructionList& il )
{
	pExpressionColumnListElement expColListEl;

	for( expColListEl = first(); expColListEl; expColListEl = next() )
		expColListEl->processViewData( il );
}


void ExpressionColumnList::writeDictionaryInformation( TempBuffer& buffer )
{
	pExpressionColumnListElement expColListEl;

	buffer << size();

	for( expColListEl = first(); expColListEl; expColListEl = next() )
		expColListEl->writeDictionaryInformation( buffer );
}


void ExpressionColumnList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI numberOfColumns, loop;
	pExpressionColumnListElement expColListEl;

	buffer >> numberOfColumns;

	for( loop = 0; loop < numberOfColumns; loop++ )
	{
		expColListEl = new ExpressionColumnListElement;
		if( !expColListEl )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		expColListEl->readDictionaryInformation( buffer );
		add( expColListEl );
	}
}


ExpressionColumnList& ExpressionColumnList::operator = ( const ExpressionColumnList& cother )
{
	ExpressionColumnList& other = const_cast< ExpressionColumnList& >( cother );
	pExpressionColumnListElement ecle, newEcle;

	for( ecle = other.first(); ecle; ecle = other.next() )
	{
		newEcle = new ExpressionColumnListElement;
		if( !newEcle )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		*newEcle = *ecle;
		add( newEcle );
	}

	return *this;
}


US ExpressionColumnList::dictionaryLength( void )
{
	pExpressionColumnListElement expColListEl;
	UNI _size;

	//
	//  Scalar values:
	//    UNI numberOfListElements
	_size = sizeof( UNI );

	for( expColListEl = first(); expColListEl; expColListEl = next() )
		_size += expColListEl->DictionaryLength();

	return static_cast< US >( _size );
}


ExpressionColumnListElement::ExpressionColumnListElement( void )
	: ExpressionColumnListElementBase(),
	  column( ((pColumnSpecification)0) ),
	  defaultValue_( 0 ),
	  ins( ((pIdentifierInstruction)0) ),
	  instructionNumber( 0 ),
	  length( 0 ),
	  name(),
	  prefix(),
	  type( CQL_COLUMN_UNDEFINED_TYPE ),
	  defaultValueFlag( CQL_NO ),
	  defaultValueNull( CQL_NO ),
	  defaultValueUser( CQL_NO ),
	  duplicateIndex( CQL_NO ),
	  notNull( CQL_NO ),
	  processed( CQL_NO ),
	  uniqueIndex( CQL_NO )
{
}


ExpressionColumnListElement::~ExpressionColumnListElement( void )
{
}


void ExpressionColumnListElement::processViewData( InstructionList& il )
{
	ins = dynamic_cast< IdentifierInstruction* >( il[ static_cast< US >( instructionNumber ) ] );
}


void ExpressionColumnListElement::writeDictionaryInformation( TempBuffer& buffer )
{
	instructionNumber = ins->position();
	buffer << name << prefix << instructionNumber;
}


void ExpressionColumnListElement::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> name >> prefix >> instructionNumber;
}


NI ExpressionColumnListElement::Assign( SqlHandle *dbsql, ExpressionColumnListElement& other )
{
	if( other.column )
	{
		column = new ColumnSpecification( *dbsql );
		if( !column )
			return dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

		if( column->Assign( dbsql, *other.column ) == CQL_FAILURE )
			return CQL_FAILURE;
	}
	else
		column = 0;

	if( other.defaultValue_ )
	{
		defaultValue_ = AbstractValue::createObject( *other.defaultValue_ );
		if( !defaultValue_ )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}
	else
		defaultValue_ = 0;

	if( other.ins )
	{
		ins = new IdentifierInstruction( *dbsql );
		if( !ins )
			return dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

		if( ins->IdentifierInstructionAssign( dbsql, *other.ins ) == CQL_FAILURE )
			return CQL_FAILURE;
	}
	else
		ins = ((pIdentifierInstruction)0);

	instructionNumber = other.instructionNumber;
	length = other.length;

	name = other.name;
	prefix = other.prefix;
	type = other.type;
	defaultValueFlag = other.defaultValueFlag;
	defaultValueNull = other.defaultValueNull;
	defaultValueUser = other.defaultValueUser;
	duplicateIndex = other.duplicateIndex;
	notNull = other.notNull;
	processed = other.processed;
	uniqueIndex = other.uniqueIndex;

	return CQL_SUCCESS;
}


UNI ExpressionColumnListElement::DictionaryLength( void )
{
	UNI size;

	size = CQL_MAXIMUM_FILE_NAME_LENGTH;
	size += CQL_MAXIMUM_FILE_NAME_LENGTH;
	size += ins->dictionaryLength();
	return size;
}


NI ExpressionColumnListElement::SetDefaultValue( SqlHandle*, LiteralElement *el )
{
	pStringElement stringElement;
	pRealLiteralElement realElement;
	pFloatLiteralElement floatElement;
	pDecimalLiteralElement decimalElement;
	pBitLiteralElement bitElement;
	pTinyintLiteralElement tinyintElement;
	pSmallintLiteralElement smallintElement;
	pIntegerLiteralElement integerElement;
	pBigintLiteralElement bigintElement;
	pTimestampLiteralElement timestampElement;
	pDateLiteralElement dateElement;
	pTimeLiteralElement timeElement;

	if( defaultValue_ )
	{
		delete defaultValue_;
		defaultValue_ = 0;
	}

	switch( type.typeType() )
	{
	case CQL_CHAR :
	case CQL_VARCHAR :
	case CQL_CHARUC :
		stringElement = ((pStringElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new CharValue( stringElement->str() ) );
		break;

	case CQL_DECIMAL :
		decimalElement = ((pDecimalLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new DecimalValue( dynamic_cast< Cql_Decimal& >( decimalElement->value() ).instance().value() ) );
		break;

	case CQL_BIT :
		bitElement = ((pBitLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new BitValue( dynamic_cast< Cql_Bit& >( bitElement->value() ).instance().value() ) );
		break;

	case CQL_TINYINT :
		tinyintElement = ((pTinyintLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new TinyintValue( dynamic_cast< Cql_Tinyint& >( tinyintElement->value() ).instance().value() ) );
		break;

	case CQL_SMALLINT :
		smallintElement = ((pSmallintLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new SmallintValue( dynamic_cast< Cql_Smallint& >( smallintElement->value() ).instance().value() ) );
		break;

	case CQL_INTEGER :
		integerElement = ((pIntegerLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new IntegerValue( dynamic_cast< Cql_Integer& >( integerElement->value() ).instance().value() ) );
		break;

	case CQL_BIGINT :
		bigintElement = ((pBigintLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new BigintValue( dynamic_cast< Cql_Bigint& >( bigintElement->value() ).instance().value() ) );
		break;

	case CQL_REAL :
		realElement = ((pRealLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new RealValue( dynamic_cast< Cql_Real& >( realElement->value() ).instance().value() ) );
		break;

	case CQL_FLOAT :
		floatElement = ((pFloatLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new FloatValue( dynamic_cast< Cql_Float& >( floatElement->value() ).instance().value() ) );
		break;

	case CQL_DATE :
		dateElement = ((pDateLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new DateValue( dynamic_cast< Cql_Date& >( dateElement->value() ).instance().value() ) );
		break;

	case CQL_TIME :
		timeElement = ((pTimeLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new TimeValue( dynamic_cast< Cql_Time& >( timeElement->value() ).instance().value() ) );
		break;

	case CQL_TIMESTAMP :
		timestampElement = ((pTimestampLiteralElement)el);
		defaultValue_ = dynamic_cast< AbstractValue* >( new TimestampValue( dynamic_cast< Cql_Timestamp& >( timestampElement->value() ).instance().value() ) );
		break;

	case CQL_LONGVARCHAR :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARBINARY :
	case CQL_COLUMN_UNDEFINED_TYPE :
		return CQL_FAILURE;
	}

	if( !defaultValue_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	return CQL_SUCCESS;
}


GrantColumn::GrantColumn( void ) : GrantColumnListElement(), columnName()
{
}


GrantColumn::~GrantColumn( void )
{
}


IndexColumnName::IndexColumnName( void ) : descending_( false ), s_()
{
}


IndexColumnName::~IndexColumnName( void )
{
}


InsertColumnName::InsertColumnName( void ) : pcs_( 0 ), s_()
{
}


InsertColumnName::~InsertColumnName( void )
{
}


PermanentColumnSpecification::PermanentColumnSpecification( SqlHandle& sqlh )
:
checkCondition_( sqlh ),
columnName_( CQL_MAXIMUM_COLUMN_NAME_LENGTH ),
columnNumber_( 0 ),
dbsql_( sqlh ),
defaultValue_( 0 ),
defaultValueFlag_( false ),
defaultValueNull_( false ),
defaultValueUser_( false ),
duplicateIndex_( false ),
notNull_( false ),
offset_( 0 ),
precision_( 0 ),
scale_( 0 ),
type_( CQL_COLUMN_UNDEFINED_TYPE ),
uniqueIndex_( false ),
value_( 0 )
{
}


PermanentColumnSpecification::~PermanentColumnSpecification( void )
{
}


//
//  if precision_ is 0, it wasn't specified by create
//
void PermanentColumnSpecification::checkCreateColumnLength( void )
{
	switch( type().typeType() )
	{
	case CQL_CHAR :
	case CQL_VARCHAR :
	case CQL_CHARUC :
	case CQL_BINARY :
	case CQL_VARBINARY :
	case CQL_LONGVARCHAR :
	case CQL_LONGVARBINARY :
		precision( static_cast< UC >( type().typeLength() ) );
		break;

	case CQL_DECIMAL :
		if( !precision() )
			precision( CQL_DEFAULT_DECIMAL_PRECISION );
		length( DecimalValue::fixedLength() );
		break;

	case CQL_SMALLINT :
		length( SmallintValue::fixedLength() );
		break;

	case CQL_INTEGER :
		length( IntegerValue::fixedLength() );
		break;

	case CQL_REAL :
		length( RealValue::fixedLength() );
		break;
		
	case CQL_FLOAT :
		length( FloatValue::fixedLength() );
		break;
		
	case CQL_TINYINT :
		length( TinyintValue::fixedLength() );
		break;

	case CQL_BIGINT :
		length( BigintValue::fixedLength() );
		break;

	case CQL_DATE :
		length( DateValue::fixedLength() );
		break;

	case CQL_TIME :
		length( TimeValue::fixedLength() );
		break;

	case CQL_TIMESTAMP :
		length( TimestampValue::fixedLength() );
		break;

	case CQL_BIT :
		length( BitValue::fixedLength() );
		break;

	case CQL_COLUMN_UNDEFINED_TYPE :
		throw InternalErrorException( __FILE__, __LINE__ );
	}
}


void PermanentColumnSpecification::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << columnName_ << type_ << columnNumber_;

	buffer << FOUR_BYTE_LENGTH << DO_COPY;
	if( defaultValue_ )
	{
		buffer << defaultValue_->length();
		*defaultValue_ >> buffer;
	}
	else
		buffer << L( 0 );

	buffer << notNull_
		   << uniqueIndex_
		   << duplicateIndex_
		   << defaultValueNull_
		   << defaultValueUser_
		   << defaultValueFlag_
		   << offset_
		   << precision_
		   << scale_;

	writeExpressionToBuffer( buffer );
}


void PermanentColumnSpecification::writeExpressionToBuffer( TempBuffer& buffer )
{
	checkCondition_.instructions().writeDictionaryInformation( buffer );
}


void PermanentColumnSpecification::getExpression( TempBuffer& buffer )
{
	checkCondition_.instructions().readDictionaryInformation( buffer );
}


US PermanentColumnSpecification::expressionLength( void )
{
	return checkCondition_.instructions().dictionaryLength();
}


PermanentColumnSpecification& PermanentColumnSpecification::operator = ( const PermanentColumnSpecification& other )
{
	checkCondition_ = other.checkCondition_;
	columnName_ = other.columnName_;
	columnNumber_ = other.columnNumber_;

	if( other.defaultValue_ )
		defaultValue_ = other.defaultValue_->createObject( other.defaultValue_->value() );
	else
		defaultValue_ = 0;

	defaultValueFlag_ = other.defaultValueFlag_;
	defaultValueNull_ = other.defaultValueNull_;
	defaultValueUser_ = other.defaultValueUser_;
	duplicateIndex_ = other.duplicateIndex_;
	notNull_ = other.notNull_;
	offset_ = other.offset_;
	precision_ = other.precision_;
	scale_ = other.scale_;
	type_ = other.type_;
	uniqueIndex_ = other.uniqueIndex_;
	return *this;
}


US PermanentColumnSpecification::dictionaryLength( void )
{
	UNI size;

	size = columnName_.length() + type_.dictionaryLength() + sizeof( columnNumber_ );
	if( defaultValue_ )
		size += defaultValue_->length();
	size += sizeof( notNull_ )
		+ sizeof( uniqueIndex_ )
		+ sizeof( duplicateIndex_ )
		+ sizeof( defaultValueNull_ )
		+ sizeof( defaultValueUser_ )
		+ sizeof( defaultValueFlag_ )
		+ sizeof( offset_ )
		+ sizeof( precision_ )
		+ sizeof( scale_ );

	size += expressionLength();

	return static_cast< US >( size );
}


void PermanentColumnSpecification::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> columnName_ >> type_ >> columnNumber_;

	UL defaultValueLength;
	buffer << DO_COPY << FOUR_BYTE_LENGTH;
	buffer >> defaultValueLength;

	if( defaultValueLength )
	{
		defaultValue_ = AbstractValueElement::createObject( type_ );
		*defaultValue_ << buffer;
	}

	buffer >> notNull_
		   >> uniqueIndex_
		   >> duplicateIndex_
		   >> defaultValueNull_
		   >> defaultValueUser_
		   >> defaultValueFlag_
		   >> offset_
		   >> precision_
		   >> scale_;

	getExpression( buffer );
}


void PermanentColumnSpecification::defaultValue( AbstractValueElement& ave )
{
	defaultValue_ = AbstractValueElement::createObject( ave.value() );
}


ReferencedColumn::ReferencedColumn( void ) : ReferencedColumnListElement(), columnNumber_( 0 )
{
}


ReferencedColumn::ReferencedColumn( US cn ) : ReferencedColumnListElement(), columnNumber_( cn )
{
}


ReferencedColumn::~ReferencedColumn( void )
{
}


US ReferencedColumn::dictionaryLength( void )
{
	return sizeof( columnNumber_ );
}


void ReferencedColumn::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << columnNumber_;
}


void ReferencedColumn::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> columnNumber_;
}


ReferencedColumnList::ReferencedColumnList( void ) : ReferencedColumnListBase()
{
}



US ReferencedColumnList::DictionaryLength( void )
{
	UNI _size;
	pReferencedColumn rc;

	//  for number of columns
	_size = sizeof( UNI );

	for( rc = first(); rc; rc = next() )
		_size += rc->dictionaryLength();

	return static_cast< US >( _size );
}


void ReferencedColumnList::writeDictionaryInformation( TempBuffer& buffer )
{
	pReferencedColumn rc;

	buffer << size();

	for( rc = first(); rc; rc = next() )
		rc->writeDictionaryInformation( buffer );
}


void ReferencedColumnList::readDictionaryInformation( TempBuffer& buffer )
{
	pReferencedColumn rc;
	UNI numberOfColumns, loop;

	buffer >> numberOfColumns;

	for( loop = 0; loop < numberOfColumns; loop++ )
	{
		rc = new ReferencedColumn;
		if( !rc )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		rc->readDictionaryInformation( buffer );
		add( rc );
	}
}


NI ReferencedColumnList::Assign( SqlHandle*, ReferencedColumnList& other )
{
	pReferencedColumn refCol, newRefCol;

	for( refCol = other.first(); refCol; refCol = other.next() )
	{
		newRefCol = new ReferencedColumn( refCol->columnNumber() );
		if( !newRefCol )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		add( newRefCol );
	}

	return CQL_SUCCESS;
}


SystemTableColumns::SystemTableColumns( SqlHandle& sqlh )
	: SystemTable( sqlh, CQL_SYSTEMTABLECOLUMNS_NAME ),
	  columnName_( CQL_SYSTEMTABLECOLUMNS_COLUMN_NAME_LENGTH ),
	  columnNameNull_( 0 ),
	  length_( 0 ),
	  lengthNull_( 0 ),
	  nullable_( 0 ),
	  nullableNull_( 0 ),
	  precision_( 0 ),
	  precisionNull_( 0 ),
	  radix_( 0 ),
	  radixNull_( 0 ),
	  remarks_( CQL_SYSTEMTABLECOLUMNS_REMARKS_LENGTH ),
	  remarksNull_( 0 ),
	  scale_( 0 ),
	  scaleNull_( 0 ),
	  type_( 0 ),
	  typeNull_( 0 ),
	  typeName_( CQL_SYSTEMTABLECOLUMNS_TYPE_NAME_LENGTH ),
	  typeNameNull_( 0 )
{
	try
	{
		table_->open( dictionaryName_ );
	}
	catch( AbstractTableException& )
	{
		sqlh.resetError();

		CqlColumnTypes *columnDescriptors[ 13 ];
		columnDescriptors[ 0 ] = new CqlColumnTypes( "qualifier", CQL_SYSTEMTABLECOLUMNS_QUALIFIER_TYPE, CQL_SYSTEMTABLECOLUMNS_QUALIFIER_LENGTH );
		columnDescriptors[ 1 ] = new CqlColumnTypes( "owner", CQL_SYSTEMTABLECOLUMNS_OWNER_TYPE, CQL_SYSTEMTABLECOLUMNS_OWNER_LENGTH );
		columnDescriptors[ 2 ] = new CqlColumnTypes( "tableName", CQL_SYSTEMTABLECOLUMNS_TABLE_NAME_TYPE, CQL_SYSTEMTABLECOLUMNS_TABLE_NAME_LENGTH );
		columnDescriptors[ 3 ] = new CqlColumnTypes( "columnName", CQL_SYSTEMTABLECOLUMNS_COLUMN_NAME_TYPE, CQL_SYSTEMTABLECOLUMNS_COLUMN_NAME_LENGTH );
		columnDescriptors[ 4 ] = new CqlColumnTypes( "type", CQL_SYSTEMTABLECOLUMNS_TYPE_TYPE );
		columnDescriptors[ 5 ] = new CqlColumnTypes( "typeName", CQL_SYSTEMTABLECOLUMNS_TYPE_NAME_TYPE, CQL_SYSTEMTABLECOLUMNS_TYPE_NAME_LENGTH );
		columnDescriptors[ 6 ] = new CqlColumnTypes( "precision", CQL_SYSTEMTABLECOLUMNS_PRECISION_TYPE );
		columnDescriptors[ 7 ] = new CqlColumnTypes( "length", CQL_SYSTEMTABLECOLUMNS_LENGTH_TYPE );
		columnDescriptors[ 8 ] = new CqlColumnTypes( "scale", CQL_SYSTEMTABLECOLUMNS_SCALE_TYPE );
		columnDescriptors[ 9 ] = new CqlColumnTypes( "radix", CQL_SYSTEMTABLECOLUMNS_RADIX_TYPE );
		columnDescriptors[ 10 ] = new CqlColumnTypes( "nullable", CQL_SYSTEMTABLECOLUMNS_NULLABLE_TYPE );
		columnDescriptors[ 11 ] = new CqlColumnTypes( "remarks", CQL_SYSTEMTABLECOLUMNS_REMARKS_TYPE, CQL_SYSTEMTABLECOLUMNS_REMARKS_LENGTH );
		columnDescriptors[ 12 ] = new CqlColumnTypes( CQL_COLUMN_UNDEFINED_TYPE );

		AccessorTypes *keyDescriptors[ 2 ];
		SegmentTypes *segs[ 4 ];
		keyDescriptors[ 0 ] = new AccessorTypes( AccessorTypes::CQL_TREE_INDEX, AccessorQualifierTypes::CQL_NO_DUPLICATES, segs );
		segs[ 0 ] = new SegmentTypes( "owner", 1, SegmentTypes::CQL_ASCENDING );
		segs[ 1 ] = new SegmentTypes( "tableName", 2, SegmentTypes::CQL_ASCENDING );
		segs[ 2 ] = new SegmentTypes( "columnName", 3, SegmentTypes::CQL_ASCENDING );
		segs[ 3 ] = new SegmentTypes( -1, SegmentTypes::CQL_SEGMENT_UNDEFINED_TYPE );
		
		keyDescriptors[ 1 ] = new AccessorTypes( AccessorTypes::CQL_ACCESSOR_UNDEFINED_TYPE );

		table_->create( CQL_CQL, dictionaryName_, columnDescriptors, keyDescriptors );

		delete columnDescriptors[ 0 ];
		delete columnDescriptors[ 1 ];
		delete columnDescriptors[ 2 ];
		delete columnDescriptors[ 3 ];
		delete columnDescriptors[ 4 ];
		delete columnDescriptors[ 5 ];
		delete columnDescriptors[ 6 ];
		delete columnDescriptors[ 7 ];
		delete columnDescriptors[ 8 ];
		delete columnDescriptors[ 9 ];
		delete columnDescriptors[ 10 ];
		delete columnDescriptors[ 11 ];
		delete columnDescriptors[ 12 ];
		delete keyDescriptors[ 0 ];
		delete segs[ 0 ];
		delete segs[ 1 ];
		delete segs[ 2 ];
		delete segs[ 3 ];
		delete keyDescriptors[ 1 ];
	}
	catch( ... )
	{
		throw;
	}

	try
	{
		SystemTable::bind();
		table_->bindColumn( CID_COLUMN_NAME, columnName_, columnNameNull_, true );
		table_->bindColumn( CID_TYPE, type_, typeNull_, true );
		table_->bindColumn( CID_TYPE_NAME, typeName_, typeNameNull_, true );
		table_->bindColumn( CID_PRECISION, precision_, precisionNull_, true );
		table_->bindColumn( CID_LENGTH, length_, lengthNull_, true );
		table_->bindColumn( CID_SCALE, scale_, scaleNull_, true );
		table_->bindColumn( CID_RADIX, radix_, radixNull_, true );
		table_->bindColumn( CID_NULLABLE, nullable_, nullableNull_, true );
		table_->bindColumn( CID_REMARKS, remarks_, remarksNull_, true );
	}
	catch( CqlException& )
	{
		//  ******************* print exception string here
		throw DictionaryException( __FILE__, __LINE__ );
	}
}


SystemTableColumns::~SystemTableColumns( void )
{
	table_->close();
	delete table_;
	table_ = 0;
}


void SystemTableColumns::add( const CqlString& qName,
							  const CqlString& oName,
							  const CqlString& tName,
							  const CqlString& cName,
							  const S typ,
							  const NC *typeNam,
							  const L precisio,
							  const L lengt,
							  const S scal,
							  const S nullabl )
{
	qualifier() = qName;
	owner() = oName;
	tableName() = tName;
	columnName_ = cName;
	length_ = lengt;
	nullable_ = nullabl;
	precision_ = precisio;
	scale_ = scal;
	type_ = typ;
	typeName_ = typeNam;

	table_->addRow();
}


TableReferenceColumn::TableReferenceColumn( void ) : TableReferenceColumnListElement(), columnNumber_( 0 ), ifile_( 0 )
{
}


TableReferenceColumn::TableReferenceColumn( US cn, pAbstractTable at ) : TableReferenceColumnListElement(), columnNumber_( cn ), ifile_( at )
{
}


TableReferenceColumn::~TableReferenceColumn( void )
{
}


US TableReferenceColumn::dictionaryLength( void )
{
	return sizeof( columnNumber_ );
}


void TableReferenceColumn::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << columnNumber_;
}


void TableReferenceColumn::readDictionaryInformation( TempBuffer& buffer )
{
	buffer >> columnNumber_;
}


TableReferenceColumnList::TableReferenceColumnList( void ) : TableReferenceColumnListBase()
{
}


US TableReferenceColumnList::DictionaryLength( void )
{
	US _size;
	pTableReferenceColumn trc;

	//  for number of columns
	_size = sizeof( UNI );

	for( trc = first(); trc; trc = next() )
		_size = ((US)( _size + trc->dictionaryLength() ) );

	return _size;
}


void TableReferenceColumnList::writeDictionaryInformation( TempBuffer& buffer )
{
	pTableReferenceColumn trc;

	buffer << size();

	for( trc = first(); trc; trc = next() )
		trc->writeDictionaryInformation( buffer );
}


void TableReferenceColumnList::readDictionaryInformation( TempBuffer& buffer )
{
	pTableReferenceColumn trc;
	UNI numberOfColumns, loop;

	buffer >> numberOfColumns;

	for( loop = 0; loop < numberOfColumns; loop++ )
	{
		trc = new TableReferenceColumn;
		if( !trc )
			throw MemoryAllocationException( __FILE__, __LINE__ );

		trc->readDictionaryInformation( buffer );
		add( trc );
	}
}


NI TableReferenceColumnList::Assign( SqlHandle *dbsql, TableReferenceColumnList& other )
{
	pTableReferenceColumn tableRefCol, newTableRefCol;

	for( tableRefCol = other.first(); tableRefCol; tableRefCol = other.next() )
	{
		newTableRefCol = new TableReferenceColumn( tableRefCol->columnNumber(), tableRefCol->ifile() );
		if( !newTableRefCol )
			return dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

		add( newTableRefCol );
	}

	return CQL_SUCCESS;
}


//
//  create to enable PREPARE/EXECUTE split
//
UpdateColumnNameAndExp::UpdateColumnNameAndExp( SqlHandle& sqlh ) : UpdateColumnNameAndExpListElement(), colSpec_( 0 ), dbsql_( sqlh ), exp_( sqlh ), file_( 0 )
{
}


UpdateColumnNameAndExp::~UpdateColumnNameAndExp( void )
{
}
