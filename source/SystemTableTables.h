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


#ifndef __SystemTableTables_h
#define __SystemTableTables_h


#define CQL_SYSTEMTABLETABLES_NAME "systable"
#define CQL_SYSTEMTABLETABLES_QUALIFIER_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLETABLES_QUALIFIER_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH
#define CQL_SYSTEMTABLETABLES_OWNER_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLETABLES_OWNER_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH
#define CQL_SYSTEMTABLETABLES_TABLE_NAME_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLETABLES_TABLE_NAME_LENGTH CQL_MAXIMUM_TABLE_NAME_LENGTH
#define CQL_SYSTEMTABLETABLES_TYPE_TYPE CQL_CHAR
#define CQL_SYSTEMTABLETABLES_TYPE_LENGTH 30
#define CQL_SYSTEMTABLETABLES_REMARKS_TYPE CQL_CHAR
#define CQL_SYSTEMTABLETABLES_REMARKS_LENGTH 254


class SystemTableTables : public SystemTable
{
	enum ColumnIds
	{
		CID_QUALIFIER = 0,
		CID_OWNER = 1,
		CID_NAME = 2,
		CID_TYPE = 3,
		CID_REMARKS = 4
	};

	CqlString remarks_;
	bool remarksNull_;
	CqlFixedLengthString type_;
	bool typeNull_;

public :

	SystemTableTables( SqlHandle& );
	virtual ~SystemTableTables( void );

	void add( const CqlString& /*qualifier*/,
			  const CqlString& /*owner*/,
			  const CqlString& /*table name*/,
			  const NC * /*type*/,
			  const CqlString& /*remarks*/ );
};


#endif  //  __SystemTableTables_h
