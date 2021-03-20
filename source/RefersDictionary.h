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


#ifndef __RefersDictionary_h
#define __RefersDictionary_h


#define CQL_REFERENCEDICT_NAME "refers"
#define CQL_REFERENCEDICT_TABLE_NAME_TYPE CQL_CHARUC
#define CQL_REFERENCEDICT_TABLE_NAME_LENGTH CQL_MAXIMUM_TABLE_NAME_LENGTH
#define CQL_REFERENCEDICT_AUTH_TYPE CQL_CHARUC
#define CQL_REFERENCEDICT_AUTH_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH
#define CQL_REFERENCEDICT_FK_TABLE_NAME_TYPE CQL_CHARUC
#define CQL_REFERENCEDICT_FK_TABLE_NAME_LENGTH CQL_MAXIMUM_TABLE_NAME_LENGTH
#define CQL_REFERENCEDICT_FK_AUTH_TYPE CQL_CHARUC
#define CQL_REFERENCEDICT_FK_AUTH_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH
#define CQL_REFERENCEDICT_FK_KEY_NUMBER_TYPE CQL_SMALLINT
#define CQL_REFERENCEDICT_FK_KEY_NUMBER_LENGTH CQL_SMALLINT_LENGTH
#define CQL_REFERENCEDICT_COLUMN_NUMBERS_TYPE CQL_LONGVARBINARY
#define CQL_REFERENCEDICT_FK_COLUMN_NUMBERS_TYPE CQL_LONGVARBINARY


//
//  fk prefix means "foreign key"
//
class RefersDictionary : public SystemDictionary
{
public :

	enum ColumnIds
	{
		CID_TABLE_NAME = 0,
		CID_AUTH = 1,
		CID_FK_TABLE_NAME = 2,
		CID_FK_AUTH = 3,
		CID_FK_KEY_NUMBER = 4,
		CID_COLUMN_NUMBERS = 5,
		CID_FK_COLUMN_NUMBERS = 6
	};

private :

	CqlString columnNumbers_;  //  actually LONGVARBINARY
	bool columnNumbersNull_;
	CqlFixedLengthString fkAuth_;
	bool fkAuthNull_;
	CqlFixedLengthString fkTableName_;
	bool fkTableNameNull_;
	S fkKeyNumber_;
	bool fkKeyNumberNull_;
	CqlString fkColumnNumbers_;  //  actually LONGVARBINARY
	bool fkColumnNumbersNull_;

public :

	RefersDictionary( SqlHandle& );
	virtual ~RefersDictionary( void );
};


#endif  //  __RefersDictionary_h
