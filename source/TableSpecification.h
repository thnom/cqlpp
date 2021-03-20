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


#ifndef __TableSpecification_h
#define __TableSpecification_h


class TableSpecification : public AbstractTableSpecification, public InstructionConstants
{
	Expression checkCondition_;
	AbstractColumnDescriptor *currentBaseTableColumn_;
	pUC dictionaryRecordBuffer_;
	SegmentedKeyGroupList duplicateKeyGroups_;
	pAbstractTable file_;
	CqlFixedLengthString fileName_;
	ForeignKeyList foreignKeys_;
	US numberOfKeys_;
	US recordLength_;
	SegmentedKeyGroupList uniqueKeyGroups_;

	void addKeyToIsamFile( SegmentedKeyGroup& );
	US findKeyNumberForColumnSet( SegmentedKeyGroupList& /*keys*/, pUS /*columnNumbers*/ );
	US findDuplicateKeyNumberForColumnSet( US * /*columnNumbers*/ );
	US findUniqueKeyNumberForColumnSet( US * /*columnNumbers*/ );

public :

	TableSpecification( SqlHandle& );
	TableSpecification( SqlHandle&, const CqlString& /*table name*/, const CqlString& /*owner*/ );
	~TableSpecification( void );

	TableSpecification& operator = ( const TableSpecification& );

	void addColumn( const ColumnSpecification& );
	void addIndexMember( SegmentedKeyGroup& );
	void addRow( void );
	void assignValue( Column&, PermanentColumnSpecification& );
	AbstractTable *baseTable( US /*column number*/ );
	void beginRowOperation( void );
	Expression& checkCondition( void ) { return checkCondition_; }
	void checkConditionColumnExecute( IdentifierInstruction&, Expression& );
	void checkPropagationFlags( void );
	void close( void );
	void computeDictionaryRecordLength( void );
	void copyData( AbstractTableSpecification& );
	void createDefaultKey( void );
	void createFiles( void );
	void createForeignKeyStructures( ForeignKeyNamesList& );
	void createIndexStructures( IndexNameListGroupList& );
	void deleteCurrentRecord( void );
	void deleteDictionaryEntry( void );
	void deleteFiles( void );
	SegmentedKeyGroup *deleteKeyGroup( CqlString& );
	void deleteRow( void );
	void dictionaryRecordBuffer( UC *drb ) { dictionaryRecordBuffer_ = drb; }
	SegmentedKeyGroupList& duplicateKeyGroups( void ) { return duplicateKeyGroups_; }
	bool evaluateCheckCondition( Expression& );
	US expressionLength( void );
	pAbstractTable file( void ) { return file_; }
	bool fileExists( void );
	CqlFixedLengthString& fileName( void ) { return fileName_; }
	void findUniqueFileName( SqlHandle* );
	AbstractColumnDescriptor *firstBaseTableColumn( AbstractTable** );
	bool firstRow( US keyNumber );
	bool firstRowMatchingPredicate( Predicate& );
	ForeignKeyList& foreignKeys( void ) { return foreignKeys_; }
	bool identifyExpressionColumns( Expression& );
	bool isView( void ) { return false; }
	bool lastRow( US /*keyNumber*/ );
	void lockFile( void );
	AbstractColumnDescriptor *nextBaseTableColumn( AbstractTable** );
	bool nextRow( void );
	bool nextRowMatchingPredicate( void );
	US numberOfBaseTables( void );
	US numberOfKeys( void ) { return numberOfKeys_; }
	void numberOfKeys( US nk ) { numberOfKeys_ = nk; }
	void open( TableType = CQL_CQL );
	bool previousRow( void );
	void processCascade( void );
	void readExpressionFromDictionary( TempBuffer& );
	void readDictionaryInformation( TempBuffer& );
	bool referencesExist( void );
	void releaseMemory( void );
	void renameToTemporary( void );
	void retrieveBaseTablePositions( pUC* );
	void retrieveBaseTableRows( pUC* );
	SegmentedKeyGroupList& uniqueKeyGroups( void ) { return uniqueKeyGroups_; }
	void writeDictionaryInformation( TempBuffer& );
	void writeExpressionToDictionary( TempBuffer& );
};

typedef TableSpecification *pTableSpecification;


#endif  //  __TableSpecification_h
