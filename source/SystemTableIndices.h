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


#ifndef __SystemTableIndices_h
#define __SystemTableIndices_h

#define CQL_SYSTEMTABLEINDICES_NAME "sysindices"
#define CQL_SYSTEMTABLEINDICES_QUALIFIER_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLEINDICES_QUALIFIER_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH
#define CQL_SYSTEMTABLEINDICES_OWNER_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLEINDICES_OWNER_LENGTH CQL_MAXIMUM_AUTHORIZATION_ID_LENGTH
#define CQL_SYSTEMTABLEINDICES_TABLE_NAME_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLEINDICES_TABLE_NAME_LENGTH CQL_MAXIMUM_TABLE_NAME_LENGTH
#define CQL_SYSTEMTABLEINDICES_COLUMN_NAME_TYPE CQL_CHARUC
#define CQL_SYSTEMTABLEINDICES_COLUMN_NAME_LENGTH CQL_MAXIMUM_COLUMN_NAME_LENGTH
#define CQL_SYSTEMTABLEINDICES_KEY_NUMBER_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLEINDICES_KEY_NUMBER_LENGTH CQL_SMALLINT_LENGTH
#define CQL_SYSTEMTABLEINDICES_COLUMN_NUMBER_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLEINDICES_COLUMN_NUMBER_LENGTH CQL_SMALLINT_LENGTH
#define CQL_SYSTEMTABLEINDICES_TYPE_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLEINDICES_TYPE_LENGTH CQL_SMALLINT_LENGTH
#define CQL_SYSTEMTABLEINDICES_TYPE_NAME_TYPE CQL_CHAR
#define CQL_SYSTEMTABLEINDICES_TYPE_NAME_LENGTH CQL_MAXIMUM_TYPE_NAME_LENGTH
#define CQL_SYSTEMTABLEINDICES_PRECISION_TYPE CQL_INTEGER
#define CQL_SYSTEMTABLEINDICES_PRECISION_LENGTH CQL_INTEGER_LENGTH
#define CQL_SYSTEMTABLEINDICES_LENGTH_TYPE CQL_INTEGER
#define CQL_SYSTEMTABLEINDICES_LENGTH_LENGTH CQL_INTEGER_LENGTH
#define CQL_SYSTEMTABLEINDICES_SCALE_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLEINDICES_SCALE_LENGTH CQL_SMALLINT_LENGTH
#define CQL_SYSTEMTABLEINDICES_PRIMARY_KEY_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLEINDICES_PRIMARY_KEY_LENGTH CQL_SMALLINT_LENGTH
#define CQL_SYSTEMTABLEINDICES_UNIQUE_KEY_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLEINDICES_UNIQUE_KEY_LENGTH CQL_SMALLINT_LENGTH
#define CQL_SYSTEMTABLEINDICES_DUPLICATE_KEY_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLEINDICES_DUPLICATE_KEY_LENGTH CQL_SMALLINT_LENGTH
#define CQL_SYSTEMTABLEINDICES_TABLE_ROW_TYPE CQL_SMALLINT
#define CQL_SYSTEMTABLEINDICES_TABLE_ROW_LENGTH CQL_SMALLINT_LENGTH
#define CQL_SYSTEMTABLEINDICES_FILE_NAME_TYPE CQL_CHAR
#define CQL_SYSTEMTABLEINDICES_FILE_NAME_LENGTH CQL_MAXIMUM_FILE_NAME_LENGTH
#define CQL_SYSTEMTABLEINDICES_INDEX_NAME_TYPE CQL_CHAR
#define CQL_SYSTEMTABLEINDICES_INDEX_NAME_LENGTH CQL_MAXIMUM_INDEX_NAME_LENGTH


class SystemTableIndices : public SystemTable
{
	enum ColumnIds
	{
		CID_QUALIFIER = 0,
		CID_OWNER = 1,
		CID_TABLE_NAME = 2,
		CID_COLUMN_NAME = 3,
		CID_KEY_NUMBER = 4,
		CID_COLUMN_NUMBER = 5,
		CID_TYPE = 6,
		CID_TYPE_NAME = 7,
		CID_PRECISION = 8,
		CID_LENGTH = 9,
		CID_SCALE = 10,
		CID_PRIMARY_KEY = 11,
		CID_UNIQUE_KEY = 12,
		CID_DUPLICATE_KEY = 13,
		CID_TABLE_ROW = 14,
		CID_FILE_NAME = 15,
		CID_INDEX_NAME = 16
	};

	CqlFixedLengthString columnName_;
	bool columnNameNull_;
	S columnNumber_;
	bool columnNumberNull_;
	S duplicateKey_;
	bool duplicateKeyNull_;
	CqlFixedLengthString fileName_;
	bool fileNameNull_;
	CqlFixedLengthString indexName_;
	bool indexNameNull_;
	S keyNumber_;
	bool keyNumberNull_;
	L length_;
	bool lengthNull_;
	L precision_;
	bool precisionNull_;
	S primaryKey_;
	bool primaryKeyNull_;
	S scale_;
	bool scaleNull_;
	S tableRow_;
	bool tableRowNull_;
	S type_;
	bool typeNull_;
	CqlFixedLengthString typeName_;
	bool typeNameNull_;
	S uniqueKey_;
	bool uniqueKeyNull_;

public :

	SystemTableIndices( SqlHandle& );
	virtual ~SystemTableIndices( void );

	void add( const CqlString& /*qualifier*/,
			  const CqlString& /*owner*/,
			  const CqlString& /*table name*/,
			  const CqlString& /*columnName*/,
			  const S /*table row flag*/,
			  const CqlString& /*file name*/,
			  const S /*keyNumber*/ = 9,
			  const S /*column number*/ = 0,
			  const S /*type*/ = 0,
			  const NC * /*type name*/ = "",
			  const L /*precision*/ = 0,
			  const L /*length*/ = 0,
			  const S /*scale*/ = 0,
			  const S /*primary key flag*/ = 0,
			  const S /*unique key flag*/ = 0,
			  const S /*duplicate key flag*/ = 0,
			  const CqlString& /*index name*/ = CqlString( "" ) );
};

#endif  //  __SystemTableIndices_h
