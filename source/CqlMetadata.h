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

#ifndef __Metadata_h
#define __Metadata_h


class TableId;
typedef List< TableId > TableIdList;
typedef ListElement< TableId, TableIdList > TableIdListElement;


class TableId : public TableIdListElement
{
	CqlFixedLengthString owner_;
	CqlFixedLengthString tableName_;

public :

	TableId( const CqlString& /*owner*/, const CqlString& /*tableName*/ );
	virtual ~TableId( void ) {}

	CqlFixedLengthString& owner( void ) { return owner_; }
	CqlFixedLengthString& tableName( void ) { return tableName_; }
};


class ColumnMetadata;
typedef List< ColumnMetadata > ColumnMetadataList;
typedef ListElement< ColumnMetadata, ColumnMetadataList > ColumnMetadataListElement;

class ColumnMetadata : public ColumnMetadataListElement
{
	CqlFixedLengthString name_;
	US columnNumber_;
	CqlColumnTypes columnType_;
	UL length_;
	US precision_;

public :

	ColumnMetadata( CqlString /*name*/,
									US /*column number*/,
									CqlColumnTypes /*column type*/,
									UL /*length*/,
									US /*precision*/ );

	virtual ~ColumnMetadata( void ) { }

	CqlString& name( void ) { return name_; }
	US columnNumber( void ) { return columnNumber_; }
	CqlColumnTypes columnType( void ) { return columnType_; }
	UL length( void ) { return length_; }
	US precision( void ) { return precision_; }
};


#endif  //  __Metadata_h
