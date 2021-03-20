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


#ifndef __MainDictionary_h
#define __MainDictionary_h


#define CQL_MAINDICT_NAME "maindict"
#define CQL_MAINDICT_RECORD_LENGTH 0
#define CQL_MAINDICT_RECORD_LENGTH_LENGTH CQL_SMALLINT_LENGTH
#define CQL_MAINDICT_RECORD_LENGTH_TYPE CQL_SMALLINT
#define CQL_MAINDICT_TABLE_NAME 1
#define CQL_MAINDICT_TABLE_NAME_LENGTH CQL_MAXIMUM_TABLE_NAME_LENGTH
#define CQL_MAINDICT_TABLE_NAME_TYPE CQL_CHARUC
#define CQL_MAINDICT_AUTHORIZATION 2
#define CQL_MAINDICT_AUTHORIZATION_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH
#define CQL_MAINDICT_AUTHORIZATION_TYPE CQL_CHARUC
#define CQL_MAINDICT_IS_VIEW 3
#define CQL_MAINDICT_IS_VIEW_LENGTH CQL_SMALLINT_LENGTH
#define CQL_MAINDICT_IS_VIEW_TYPE CQL_SMALLINT
#define CQL_MAINDICT_THE_REST 4
#define CQL_MAINDICT_THE_REST_TYPE CQL_LONGVARBINARY


class MainDictionary : public SystemDictionary
{
	bool aliasFlag_;
	S isView_;
	bool isViewNull_;
	S recordLength_;
	bool recordLengthNull_;
	TempBuffer theRest_;
	bool theRestNull_;

	enum ColumnIds
	{
		CID_RECORD_LENGTH = 0,
		CID_TABLE_NAME = 1,
		CID_AUTHORIZATION = 2,
		CID_IS_VIEW = 3,
		CID_THE_REST = 4
	};

public :

	MainDictionary( SqlHandle& );
	virtual ~MainDictionary( void );

	void add( S, CqlString&, CqlString&, S, TempBuffer& );
	void ddelete( CqlString& tableName, CqlString& auth );
	pAbstractTableSpecification find( const CqlString&, const CqlString& );
	ColumnMetadataList *getColumnMetadata( TableId * );
	TableIdList *getTableIds( const CqlString& );
};


#endif  //  __MainDictionary_h
