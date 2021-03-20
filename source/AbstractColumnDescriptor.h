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


#ifndef __AbstractColumnDescriptor_h
#define __AbstractColumnDescriptor_h


class AbstractColumnDescriptor;
class AbstractColumnDescriptorList;
typedef List<AbstractColumnDescriptor> AbstractColumnDescriptorListBase;
typedef ListElement<AbstractColumnDescriptor, AbstractColumnDescriptorListBase> AbstractColumnDescriptorListElement;


class ColumnToKeyMap;
typedef List< ColumnToKeyMap > ColumnToKeyMapList;
typedef ListElement< ColumnToKeyMap, ColumnToKeyMapList > ColumnToKeyMapListElement;

class ColumnToKeyMap : public ColumnToKeyMapListElement
{
	Accessor *acc_;
	AbstractSegmentDescriptor *segmentDescriptor_;

public :

	ColumnToKeyMap( Accessor *a, AbstractSegmentDescriptor *sd ) : acc_( a ), segmentDescriptor_( sd ) { }
	virtual ~ColumnToKeyMap( void ) { }

	Accessor *acc( void ) { return acc_; }
	AbstractSegmentDescriptor *segmentDescriptor( void ) { return segmentDescriptor_; }
};


class AbstractColumnDescriptor : public AbstractColumnDescriptorListElement, public CqlConstants, public ExceptionCodes
{
	BoundColumn *bc_;
	ColumnToKeyMapList keyMapList_;

public :

	AbstractColumnDescriptor( void );
	virtual ~AbstractColumnDescriptor( void );

	static AbstractColumnDescriptor* createObject( CqlColumnTypes /*type*/, US /*columnNumber*/, bool /*descendingFlag*/ = false );
	static AbstractColumnDescriptor *input( TempBuffer& );

	BoundColumn *bc( void ) { return bc_; }
	void bc( BoundColumn *b );
	ColumnToKeyMapList& keyMapList( void ) { return keyMapList_; }

	virtual US columnNumber( void ) = 0;
	virtual void columnType( CqlColumnTypes& ) = 0;
	virtual CqlColumnTypes& columnType( void ) = 0;
	virtual bool descending( void ) = 0;
	virtual US dictionaryLength( void ) = 0;
	virtual bool isNull( void ) = 0;
	virtual UL length( void ) = 0;
	virtual CqlString name( void ) = 0;
	virtual US precision( void ) = 0;
	virtual AbstractType& value( void ) = 0;
};

typedef AbstractColumnDescriptor *pAbstractColumnDescriptor;


#endif  //  __AbstractColumnDescriptor_h
