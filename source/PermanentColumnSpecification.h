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


#ifndef __PermanentColumnSpecification_h
#define __PermanentColumnSpecification_h


class PermanentColumnSpecification;
typedef List< PermanentColumnSpecification > PermanentColumnSpecificationList;
typedef ListElement< PermanentColumnSpecification, PermanentColumnSpecificationList > PermanentColumnSpecificationListElement;


class PermanentColumnSpecification : public PermanentColumnSpecificationListElement, public CqlConstants, public ErrorConstants
{
	Expression checkCondition_;
	CqlFixedLengthString columnName_;
	US columnNumber_;
	SqlHandle& dbsql_;
	AbstractValueElement *defaultValue_;
	bool defaultValueFlag_;
	bool defaultValueNull_;
	bool defaultValueUser_;
	bool duplicateIndex_;
	bool notNull_;
	UL offset_;
	UC precision_;
	UC scale_;
	CqlColumnTypes type_;
	bool uniqueIndex_;
	AbstractType *value_;

public :

	PermanentColumnSpecification( SqlHandle& );
	~PermanentColumnSpecification( void );

	PermanentColumnSpecification& operator = ( const PermanentColumnSpecification& );

	Expression& checkCondition( void ) { return checkCondition_; }
	void checkCreateColumnLength( void );
	CqlFixedLengthString& columnName( void ) { return columnName_; }
	US columnNumber( void ) { return columnNumber_; }
	void columnNumber( US cno ) { columnNumber_ = cno; }
	SqlHandle& dbsql( void ) { return dbsql_; }
	AbstractValueElement& defaultValue( void ) { return *defaultValue_; }
	void defaultValue( AbstractValueElement& dv );
	bool defaultValueFlag( void ) { return defaultValueFlag_; }
	bool defaultValueNull( void ) { return defaultValueNull_; }
	bool defaultValueUser( void ) { return defaultValueUser_; }
	US dictionaryLength( void );
	bool duplicateIndex( void ) { return duplicateIndex_; }
	US expressionLength( void );
	void getExpression( TempBuffer& );
	void length( UL tlen ) { type_.typeLength( tlen ); }
	bool notNull( void ) { return notNull_; }
	Expression *pCheckCondition( void ) { return &checkCondition_; }
	UC precision( void ) { return precision_; }
	void precision( UC p ) { precision_ = p; }
	void readDictionaryInformation( TempBuffer& );
	UC scale( void ) { return scale_; }
	void scale( UC s ) { scale_ = s; }
	void setDefaultValueFlag( void ) { defaultValueFlag_ = true; }
	void setDefaultValueNull( void ) { defaultValueNull_ = true; }
	void setDefaultValueUser( void ) { defaultValueUser_ = true; }
	void setDuplicateIndex( void ) { duplicateIndex_ = true; }
	void setNotNull( void ) { notNull_ = true; }
	void setUniqueIndex( void ) { uniqueIndex_ = true; }
	CqlColumnTypes type( void ) const { return type_; }
	void type( CqlColumnTypes tp ) { type_ = tp; }
	CqlColumnTypes& typeR( void ) { return type_; }
	bool uniqueIndex( void ) { return uniqueIndex_; }
	AbstractType& value( void ) { return *value_; }
	void writeExpressionToBuffer( TempBuffer& );
	void writeDictionaryInformation( TempBuffer& );
};

typedef PermanentColumnSpecification *pPermanentColumnSpecification;


#endif  //  __PermanentColumnSpecification_h
