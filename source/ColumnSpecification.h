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


#ifndef __ColumnSpecification_h
#define __ColumnSpecification_h


class ColumnSpecification : public PermanentColumnSpecification
{
	CqlString authorizationId;
	US cno;
	NI ifNumber;
	TableTableElement *ttEl;
	CqlString tableName;
	Column *viewColumn;
	Expression viewExpression;

	BFT isViewColumn : 1;

public :

	ColumnSpecification( SqlHandle& );
	ColumnSpecification( const ColumnSpecification& );
	~ColumnSpecification( void );

	ColumnSpecification& operator = ( const ColumnSpecification& );

	NI Assign( SqlHandle*, ColumnSpecification& );
	CqlString& AuthorizationId( void ) { return authorizationId; }
	US Cno( void ) { return cno; }
	AbstractValueElement *createValue( void );
	NI IsViewColumn( void ) { return isViewColumn; }
	void SetCno( US c ) { cno = c; }
	void SetIsViewColumn( void ) { isViewColumn = CQL_YES; }
	void SetViewColumn( Column *col ) { viewColumn = col; }
	void SetTtEl( TableTableElement *t ) { ttEl = t; }
	CqlString& TableName( void ) { return tableName; }
	TableTableElement *TtEl( void ) { return ttEl; }
	Column *ViewColumn( void ) { return viewColumn; }
	Expression& ViewExpression( void ) { return viewExpression; }
};

typedef ColumnSpecification *pColumnSpecification;


#endif  //  __ColumnSpecification_h
