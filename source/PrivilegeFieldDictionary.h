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


#ifndef __PrivilegeFieldDictionary_h
#define __PrivilegeFieldDictionary_h

#define CQL_PRIVILEGEFIELD_DICTIONARY_NAME "privfield"
#define CQL_PRIVILEGEFIELDDICT_TABLE_NAME_LENGTH CQL_MAXIMUM_TABLE_NAME_LENGTH
#define CQL_PRIVILEGEFIELDDICT_TABLE_NAME_TYPE CQL_CHARUC
#define CQL_PRIVILEGEFIELDDICT_AUTHORIZATION_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH
#define CQL_PRIVILEGEFIELDDICT_AUTHORIZATION_TYPE CQL_CHARUC
#define CQL_PRIVILEGEFIELDDICT_USER_LENGTH CQL_MAXIMUM_USER_NAME_LENGTH
#define CQL_PRIVILEGEFIELDDICT_USER_TYPE CQL_CHARUC
#define CQL_PRIVILEGEFIELDDICT_COLUMN_NAME_LENGTH CQL_MAXIMUM_COLUMN_NAME_LENGTH
#define CQL_PRIVILEGEFIELDDICT_COLUMN_NAME_TYPE CQL_CHARUC


class PrivilegeFieldDictionary : public SystemDictionary
{
	CqlFixedLengthString columnName_;
	bool columnNameNull_;
	bool findStatus_;
	bool priv_;
	bool privNull_;
	CqlFixedLengthString user_;
	bool userNull_;

	enum ColumnIds
	{
		CID_TABLE_NAME = 0,
		CID_AUTHORIZATION = 1,
		CID_USER = 2,
		CID_COLUMN_NAME = 3
	};

public:

	PrivilegeFieldDictionary( SqlHandle& );
	virtual ~PrivilegeFieldDictionary( void );

	void add( PrivilegeFieldDictionaryRecord& );
	//  this is deliberately PrivilegeDictionaryRecord, because this method
	//  deletes all privileges for the table/auth/user
	void deletePrivs( PrivilegeDictionaryRecord& );
	bool privilege( CqlString& tableName, CqlString& auth, CqlString& columnName );
};


#endif  //  __PrivilegeFieldDictionary_h
