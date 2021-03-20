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


#ifndef __IndexDictionary_h
#define __IndexDictionary_h


#define CQL_INDEXDICT_NAME "indexdict"
#define CQL_INDEXDICT_INDEX_NAME_TYPE CQL_CHARUC
#define CQL_INDEXDICT_INDEX_NAME_LENGTH CQL_MAXIMUM_INDEX_NAME_LENGTH
#define CQL_INDEXDICT_TABLE_NAME_TYPE CQL_CHARUC
#define CQL_INDEXDICT_TABLE_NAME_LENGTH CQL_MAXIMUM_TABLE_NAME_LENGTH
#define CQL_INDEXDICT_AUTHORIZATION_TYPE CQL_CHARUC
#define CQL_INDEXDICT_AUTHORIZATION_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH


class IndexDictionary : public SystemDictionary
{
	enum ColumnIds
	{
		CID_INDEX_NAME = 0,
		CID_TABLE_NAME = 1,
		CID_AUTHORIZATION = 2
	};

	CqlFixedLengthString indexName_;
	bool indexNameNull_;

public :

	IndexDictionary( SqlHandle& );
	virtual ~IndexDictionary( void );

	void add( CqlString&, CqlString&, CqlString& );
	void ddelete( CqlString& );
	void find( CqlString&, CqlString&, CqlString& );
};


#endif  //  __IndexDictionary_h
