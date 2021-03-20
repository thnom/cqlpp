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


#ifndef __ViewSpecification_h
#define __ViewSpecification_h


class ViewSpecification : public AbstractTableSpecification
{
	bool checkOption_;
	UC *dictionaryRecordBuffer_;
	bool processed_;
	SelectExpressionList selectExpressions_;
	StringList viewColumnNames_;
	US virtualBufferLength_;


public :

	ViewSpecification( SqlHandle& );
	ViewSpecification( SqlHandle&, CqlString&, CqlString& );
	~ViewSpecification( void );

	ViewSpecification& operator = ( const ViewSpecification& );

	US virtualBufferLength( void ) { return virtualBufferLength_; }
	void virtualBufferLength( US len ) { virtualBufferLength_ = len; }
	void increaseVirtualBufferLength( US len ) { virtualBufferLength_ = static_cast< US >( ( virtualBufferLength_ + len ) ); }

	void addRow( void );
	void assignValue( Column&, PermanentColumnSpecification& );
	AbstractTable *baseTable( US /*column number*/ );
	void beginRowOperation( void );
	void checkPropagationFlags( void );
	void close( void );
	void computeDictionaryRecordLength( void );
	NI ConstructViewDictionaryRecord( void );
	void deleteCurrentRecord( void );
	void deleteDictionaryEntry( void );
	void deleteFiles( void ) { }
	void deleteRow( void );
	void dictionaryRecordBuffer( pUC drb ) { dictionaryRecordBuffer_ = drb; }
	AbstractColumnDescriptor *firstBaseTableColumn( AbstractTable** );
	bool isView( void ) { return true; }
	AbstractColumnDescriptor *nextBaseTableColumn( AbstractTable** );
	US numberOfBaseTables( void );
	void open( TableType = CQL_CQL );
	void processCascade( void );
	NI ProcessView( SqlHandle* );
	void readDictionaryInformation( TempBuffer& );
	bool referencesExist( void );
	void releaseMemory( void );
	void retrieveBaseTablePositions( pUC* );
	void retrieveBaseTableRows( pUC* );
	SelectExpressionList& selectExpressions( void ) { return selectExpressions_; }
	US ViewRepresentationSize( void );
	void writeDictionaryInformation( TempBuffer& );
};

typedef ViewSpecification *pViewSpecification;


#endif  //  __ViewSpecification_h
