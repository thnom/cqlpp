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


#ifndef __AbstractTableSpecification_h
#define __AbstractTableSpecification_h


class AbstractTableSpecification;
typedef List< AbstractTableSpecification > AbstractTableSpecificationList;
typedef ListElement<AbstractTableSpecification,AbstractTableSpecificationList> AbstractTableSpecificationListElement;


class AbstractTableSpecification : public AbstractTableSpecificationListElement,
								   public ErrorConstants,
								   public CqlConstants
{
	bool aliasFlag_;
	CqlFixedLengthString authorizationId_;
	ColumnSpecificationList columns_;
	SqlHandle& dbsql_;
	US dictionaryRecordLength_;
	US numberOfColumns_;
	bool readOnly_;
	CqlFixedLengthString tableName_;
	TableType ttype_;
	bool variableLength_;
	US viewsDerivedFromTable_;

public :

	AbstractTableSpecification( SqlHandle& );
	AbstractTableSpecification( SqlHandle&, const CqlString&, const CqlString& );
	virtual ~AbstractTableSpecification( void );

	AbstractTableSpecification& operator = ( const AbstractTableSpecification& );
	
	bool aliasFlag( void ) { return aliasFlag_; }
	CqlFixedLengthString& authorizationId( void ) { return authorizationId_; }
	void clearAliasFlag( void ) { aliasFlag_ = false; }
	void clearConditions( void );
	ColumnSpecificationList& columns( void ) { return columns_; }
	SqlHandle& dbsql( void ) { return dbsql_; }
	US dictionaryLength( void );
	US dictionaryRecordLength( void ) { return dictionaryRecordLength_; }
	void dictionaryRecordLength( US len ) { dictionaryRecordLength_ = len; }
	PermanentColumnSpecification *findColumnUsingName( const CqlString& );
	US numberOfColumns( void ) { return numberOfColumns_; }
	void numberOfColumns( US nc ) { numberOfColumns_ = nc; }
	void setAliasFlag( void ) { aliasFlag_ = true; }
	void setReadOnly( void ) { readOnly_ = true; }
	void setVariableLength( void ) { variableLength_ = true; }
	CqlFixedLengthString& tableName( void ) { return tableName_; }
	TableType ttype( void ) { return ttype_; }
	bool variableLength( void ) { return variableLength_; }
	void viewsDerivedFromTable( US val ) { viewsDerivedFromTable_ = val; }

	virtual void addRow() = 0;
	virtual void assignValue( Column&, PermanentColumnSpecification& ) = 0;
	virtual AbstractTable *baseTable( US /*column number*/ ) = 0;
	virtual void beginRowOperation( void ) = 0;
	virtual void checkPropagationFlags( void ) = 0;
	virtual void close( void ) = 0;
	virtual void computeDictionaryRecordLength( void ) = 0;
	virtual void deleteCurrentRecord( void ) = 0;
	virtual void deleteDictionaryEntry( void ) = 0;
	virtual void deleteFiles( void ) = 0;
	virtual void deleteRow( void ) = 0;
	virtual void dictionaryRecordBuffer( pUC ) = 0;
	virtual AbstractColumnDescriptor *firstBaseTableColumn( AbstractTable** ) = 0;
	virtual bool isView( void ) = 0;
	virtual AbstractColumnDescriptor *nextBaseTableColumn( AbstractTable** ) = 0;
	virtual US numberOfBaseTables( void ) = 0;
	virtual void open( TableType = CQL_CQL ) = 0;
	virtual void processCascade( void ) = 0;
	virtual void readDictionaryInformation( TempBuffer& ) = 0;
	virtual bool referencesExist( void ) = 0;
	virtual void releaseMemory( void ) = 0;
	virtual void retrieveBaseTablePositions( pUC* ) = 0;
	virtual void retrieveBaseTableRows( pUC* ) = 0;
	virtual void writeDictionaryInformation( TempBuffer& ) = 0;
};

typedef AbstractTableSpecification *pAbstractTableSpecification;


#endif  //  __AbstractTableSpecification_h
