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


#ifndef __SystemTableColumns_h
#define __SystemTableColumns_h

#define CQL_SYSTEMTABLECOLUMNS_NAME "syscolums"

#define CQL_SYSTEMTABLECOLUMNS_QUALIFIER_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLECOLUMNS_QUALIFIER_LENGTH	CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_OWNER_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLECOLUMNS_OWNER_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_TABLE_NAME_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLECOLUMNS_TABLE_NAME_LENGTH CQL_MAXIMUM_TABLE_NAME_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_COLUMN_NAME_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLECOLUMNS_COLUMN_NAME_LENGTH CQL_MAXIMUM_COLUMN_NAME_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_TYPE_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLECOLUMNS_TYPE_LENGTH CQL_SMALLINT_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_TYPE_NAME_TYPE CQL_CHAR
#define CQL_SYSTEMTABLECOLUMNS_TYPE_NAME_LENGTH 20

#define CQL_SYSTEMTABLECOLUMNS_PRECISION_TYPE CQL_INTEGER
#define CQL_SYSTEMTABLECOLUMNS_PRECISION_LENGTH CQL_INTEGER_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_LENGTH_TYPE CQL_INTEGER
#define CQL_SYSTEMTABLECOLUMNS_LENGTH_LENGTH CQL_INTEGER_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_SCALE_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLECOLUMNS_SCALE_LENGTH CQL_SMALLINT_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_RADIX_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLECOLUMNS_RADIX_LENGTH CQL_SMALLINT_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_NULLABLE_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLECOLUMNS_NULLABLE_LENGTH CQL_SMALLINT_LENGTH

#define CQL_SYSTEMTABLECOLUMNS_REMARKS_TYPE CQL_CHAR
#define CQL_SYSTEMTABLECOLUMNS_REMARKS_LENGTH 254

class SystemTableColumns : public SystemTable
{
	enum ColumnIds
	{
		CID_QUALIFIER = 0,
		CID_OWNER = 1,
		CID_TABLE_NAME = 2,
		CID_COLUMN_NAME = 3,
		CID_TYPE = 4,
		CID_TYPE_NAME = 5,
		CID_PRECISION = 6,
		CID_LENGTH = 7,
		CID_SCALE = 8,
		CID_RADIX = 9,
		CID_NULLABLE = 10,
		CID_REMARKS = 11
	};

	CqlFixedLengthString columnName_;
	bool columnNameNull_;
	L length_;
	bool lengthNull_;
	S nullable_;
	bool nullableNull_;
	L precision_;
	bool precisionNull_;
	S radix_;
	bool radixNull_;
	CqlFixedLengthString remarks_;
	bool remarksNull_;
	S scale_;
	bool scaleNull_;
	S type_;
	bool typeNull_;
	CqlFixedLengthString typeName_;
	bool typeNameNull_;

public :

	SystemTableColumns( SqlHandle& );
	virtual ~SystemTableColumns( void );

	void add( const CqlString& /*qualifier*/,
			  const CqlString& /*owner*/,
			  const CqlString& /*table name*/,
			  const CqlString& /*column name*/,
			  const S /*type*/,
			  const NC * /*type name*/,
			  const L /*precision*/,
			  const L /*length*/,
			  const S /*scale*/,
			  const S /*nullable*/ );
};


#endif  //  __SystemTableColumns_h
