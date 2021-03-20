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


#ifndef __IndexNameListGroup_h
#define __IndexNameListGroup_h


class IndexNameListGroup;
typedef List< IndexNameListGroup > IndexNameListGroupList;
typedef ListElement< IndexNameListGroup, IndexNameListGroupList > IndexNameListGroupListElement;


class IndexNameListGroup : public IndexNameListGroupListElement
{
	IndexColumnNameList icnl;

	BFT duplicateKey : 1;
	BFT primaryKey : 1;
	BFT uniqueKey : 1;

public :

	IndexNameListGroup( void );
	~IndexNameListGroup( void );

#if 0
	pListElement Copy( void );
#endif
	NI DuplicateKey( void ) { return duplicateKey; }
	IndexColumnNameList& Icnl( void ) { return icnl; }
	NI PrimaryKey( void ) { return primaryKey; }
	void SetDuplicateKey( void ) { duplicateKey = CQL_YES; }
	void SetPrimaryKey( void ) { primaryKey = CQL_YES; }
	void SetUniqueKey( void ) { uniqueKey = CQL_YES; }
	NI UniqueKey( void ) { return uniqueKey; }
};

typedef IndexNameListGroup *pIndexNameListGroup;


#endif  //  __IndexNameListGroup_h
