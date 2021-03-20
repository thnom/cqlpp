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


#ifndef __PrivilegeDictionary_h
#define __PrivilegeDictionary_h


#define CQL_PRIVILEGEDICT_NAME "privdict"
#define CQL_PRIVILEGEDICT_TABLE_NAME_LENGTH CQL_MAXIMUM_TABLE_NAME_LENGTH
#define CQL_PRIVILEGEDICT_TABLE_NAME_TYPE CQL_CHARUC
#define CQL_PRIVILEGEDICT_AUTHORIZATION_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH
#define CQL_PRIVILEGEDICT_AUTHORIZATION_TYPE CQL_CHARUC
#define CQL_PRIVILEGEDICT_USER_LENGTH CQL_MAXIMUM_USER_NAME_LENGTH
#define CQL_PRIVILEGEDICT_USER_TYPE CQL_CHARUC
#define CQL_PRIVILEGEDICT_GRANT_OPTION_LENGTH sizeof( S )
#define CQL_PRIVILEGEDICT_GRANT_OPTION_TYPE CQL_SMALLINT
#define CQL_PRIVILEGEDICT_DELETE_PRIV_LENGTH sizeof( S )
#define CQL_PRIVILEGEDICT_DELETE_PRIV_TYPE CQL_SMALLINT
#define CQL_PRIVILEGEDICT_INSERT_PRIV_LENGTH sizeof( S )
#define CQL_PRIVILEGEDICT_INSERT_PRIV_TYPE CQL_SMALLINT
#define CQL_PRIVILEGEDICT_REFERENCES_PRIV_LENGTH sizeof( S )
#define CQL_PRIVILEGEDICT_REFERENCES_PRIV_TYPE CQL_SMALLINT
#define CQL_PRIVILEGEDICT_SELECT_PRIV_LENGTH sizeof( S )
#define CQL_PRIVILEGEDICT_SELECT_PRIV_TYPE CQL_SMALLINT
#define CQL_PRIVILEGEDICT_UPDATE_PRIV_LENGTH sizeof( S )
#define CQL_PRIVILEGEDICT_UPDATE_PRIV_TYPE CQL_SMALLINT


class PrivilegeDictionary : public SystemDictionary
{
	S deletePriv_;
	bool deletePrivNull_;
	S grantOption_;
	bool grantOptionNull_;
	S insertPriv_;
	bool insertPrivNull_;
	S referencesPriv_;
	bool referencesPrivNull_;
	S selectPriv_;
	bool selectPrivNull_;
	S updatePriv_;
	bool updatePrivNull_;
	CqlFixedLengthString user_;
	bool userNull_;

	enum ColumnIds
	{
		CID_TABLE_NAME = 0,
		CID_AUTHORIZATION = 1,
		CID_USER = 2,
		CID_GRANT_OPTION = 3,
		CID_DELETE_PRIV = 4,
		CID_INSERT_PRIV = 5,
		CID_REFERENCES_PRIV = 6,
		CID_SELECT_PRIV = 7,
		CID_UPDATE_PRIV = 8
	};

	NI findPrivileges( CqlString& tableName, CqlString& auth, CqlString& user );
	NI getPrivileges( CqlString& tableName, CqlString& auth );

public:

	PrivilegeDictionary( SqlHandle& );
	virtual ~PrivilegeDictionary( void );

	void addOrUpdate( PrivilegeDictionaryRecord& );
	bool deletePrivilege( CqlString& tableName, CqlString& auth, bool& grantOption );
	void deletePrivs( PrivilegeDictionaryRecord& );
	bool insertPrivilege( CqlString& tableName, CqlString& auth, bool& grantOption );
	bool selectPrivilege( CqlString& tableName, CqlString& auth, bool& grantOption );
	bool updatePrivilege( CqlString& tableName, CqlString& auth, bool& grantOption );
};


#endif  //  __PrivilegeDictionary_h
