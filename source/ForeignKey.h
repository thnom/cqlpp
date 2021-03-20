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


#ifndef __ForeignKey_h
#define __ForeignKey_h


class ForeignKey;
typedef List< ForeignKey > ForeignKeyListBase;
typedef ListElement< ForeignKey, ForeignKeyListBase > ForeignKeyListElement;


class ForeignKey : public ForeignKeyListElement
{
	US referencedTableKey_;
	CqlString referencedTableName_;
	CqlString referencedTablePrefix_;
	ReferencedColumnList referencedColumns_;
	TableReferenceColumnList referencingColumns_;

public :

	ForeignKey( void );
	~ForeignKey( void );

	ForeignKey& operator = ( const ForeignKey& );

	US dictionaryLength( void );
	void readDictionaryInformation( TempBuffer& );
	ReferencedColumnList& referencedColumns( void ) { return referencedColumns_; }
	TableReferenceColumnList& referencingColumns( void ) { return referencingColumns_; }
	US referencedTableKey( void ) { return referencedTableKey_; }
	void referencedTableKey( US keyNo ) { referencedTableKey_ = keyNo; }
	CqlString& referencedTableName( void ) { return referencedTableName_; }
	void referencedTableName( const CqlString& n ) { referencedTableName_ = n; }
	CqlString& referencedTablePrefix( void ) { return referencedTablePrefix_; }
	void referencedTablePrefix( const CqlString& p ) { referencedTablePrefix_ = p; }
	void writeDictionaryInformation( TempBuffer& );
};

typedef ForeignKey *pForeignKey;


#endif  //  __ForeignKey_h
