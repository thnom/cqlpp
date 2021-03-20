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


#ifndef __CqlTableConstants_h
#define __CqlTableConstants_h


class CqlColumnTypesCreate;
typedef List< CqlColumnTypesCreate > CqlColumnTypesCreateList;
typedef ListElement< CqlColumnTypesCreate, CqlColumnTypesCreateList > CqlColumnTypesCreateListElement;


class AccessorTypesCreate;
typedef List< AccessorTypesCreate > AccessorTypesCreateList;
typedef ListElement< AccessorTypesCreate, AccessorTypesCreateList > AccessorTypesCreateListElement;


class SegmentTypesCreate;
typedef List< SegmentTypesCreate > SegmentTypesCreateList;
typedef ListElement< SegmentTypesCreate, SegmentTypesCreateList > SegmentTypesCreateListElement;


class CqlColumnTypes : public CqlConstants
{
	AbstractValue *defaultValue_;
	bool notNull_;
	UL typeLength_;
	CqlString typeName_;
	CqlColumnType typeType_;

public :

	CqlColumnTypes( void ) : defaultValue_( 0 ),
							 notNull_( false),
							 typeLength_( 0 ),
							 typeName_( "UNDEFINED" ),
							 typeType_( CQL_COLUMN_UNDEFINED_TYPE )
		{
		}

	CqlColumnTypes( const CqlString& name,
					const CqlColumnType type,
					const UL length = 0 )
		: defaultValue_( 0 ),
		  notNull_( false),
		  typeLength_( length ),
		  typeName_( name ),
		  typeType_( type )
		{
		}

	CqlColumnTypes( const CqlColumnType type, const UL length = 0 )
		: defaultValue_( 0 ),
		  notNull_( false),
		  typeLength_( length ),
		  typeName_( CqlConstants::columnTypeName( type ) ),
		  typeType_( type )
		{
		}

	CqlColumnTypes( const CqlColumnTypes& other )
		: defaultValue_( 0 ),
		  notNull_( false),
		  typeLength_( other.typeLength_ ),
		  typeName_( other.typeName_ ),
		  typeType_( other.typeType_ )
		{
		}

	virtual ~CqlColumnTypes( void ) { }

	CqlColumnTypes& operator = ( const CqlColumnTypes& );

	void clearNotNull( void ) { notNull_ = false; }
	const CqlString& cTypeName( void ) const { return typeName_; }
	AbstractValue *defaultValue( void ) const { return defaultValue_; }
	void defaultValue( AbstractValue *av ) { defaultValue_ = av; }
	UL dictionaryLength( void );
	bool notNull( void ) const { return notNull_; }
	void setNotNull( void ) { notNull_ = true; }
	UL typeLength( void ) const { return typeLength_; }
	void typeLength( UL len ) { typeLength_ = len; }
	CqlString& typeName( void ) { return typeName_; }
	CqlColumnType typeType( void ) const { return typeType_; }
	void typeType( CqlColumnType t ) { typeType_ = t; }

	bool valid( void )
	{
		switch( typeType_ )
		{
		case CQL_COLUMN_UNDEFINED_TYPE :
		case CQL_CHAR :
		case CQL_VARCHAR :
		case CQL_DECIMAL :
		case CQL_SMALLINT :
		case CQL_INTEGER :
		case CQL_REAL :
		case CQL_FLOAT :
		case CQL_LONGVARCHAR :
		case CQL_BIT :
		case CQL_TINYINT :
		case CQL_BIGINT :
		case CQL_BINARY :
		case CQL_VARBINARY :
		case CQL_LONGVARBINARY :
		case CQL_DATE :
		case CQL_TIME :
		case CQL_TIMESTAMP :
		case CQL_CHARUC :
			return true;

		default :
			break;
		}

		return false;
	}
};


//  This is a wrapper.  CqlColumnTypes can't be a list element because classes derived from it are list elements
class CqlColumnTypesCreate : public CqlColumnTypesCreateListElement, public CqlColumnTypes
{
public :

	CqlColumnTypesCreate( const CqlColumnTypes& ctype ) : CqlColumnTypesCreateListElement(), CqlColumnTypes( ctype ) { }
};


class AccessorQualifierTypes
{
public :

	enum AccessorQualifierType
	{
		CQL_ACCESSOR_QUALIFIER_UNDEFINED_TYPE,
		CQL_DUPLICATES_ALLOWED,
		CQL_NO_DUPLICATES
	};

private :

	AccessorQualifierType aqtypeType_;

public :

	AccessorQualifierTypes( void ) : aqtypeType_( CQL_ACCESSOR_QUALIFIER_UNDEFINED_TYPE )
	{
	}

	AccessorQualifierTypes( AccessorQualifierType aqtype ) : aqtypeType_( aqtype )
	{
	}

	//  default destructor

	AccessorQualifierType aqtypeType( void ) { return aqtypeType_; }
	void aqtypeType( AccessorQualifierType aqt ) { aqtypeType_ = aqt; }

	virtual bool valid( void )
	{
		switch( aqtypeType_ )
		{
		case CQL_ACCESSOR_QUALIFIER_UNDEFINED_TYPE :
		case CQL_DUPLICATES_ALLOWED :
		case CQL_NO_DUPLICATES :
			return true;

		default :
			break;
		}

		return false;
	}
};


class SegmentTypes
{
public :

	enum SegmentType
	{
		CQL_ASCENDING,
		CQL_DESCENDING,
		CQL_SEGMENT_UNDEFINED_TYPE
	};

private :

	CqlString columnName_;
	//  This is S, rather than unsigned S, because in certain error situations it can be negative.  See IsamFile::create().
	S columnNumber_;
	SegmentType segmentType_;

public :

	SegmentTypes( void ) : columnName_(), columnNumber_( -1 ), segmentType_( CQL_SEGMENT_UNDEFINED_TYPE ) { }
	SegmentTypes( const S _columnNumber, const SegmentType stype ) : columnNumber_( _columnNumber ), segmentType_( stype ) { }
	SegmentTypes( const CqlString& name, const S _columnNumber, const SegmentType stype ) : columnName_( name ), columnNumber_( _columnNumber ), segmentType_( stype ) { }
	SegmentTypes( const SegmentTypes& other ) : columnName_( other.columnName_ ), columnNumber_( other.columnNumber_ ), segmentType_( other.segmentType_ ) { }
	SegmentTypes( SegmentType _segmentType ) : columnNumber_( -1 ), segmentType_( _segmentType ) { }

	virtual ~SegmentTypes( void ) { }

	CqlString& columnName( void ) { return columnName_; }
	S columnNumber( void ) const { return columnNumber_; }
	void columnNumber( S cn ) { columnNumber_ = cn; }
	SegmentType segmentType( void ) const { return segmentType_; }
	void segmentType( SegmentType st ) { segmentType_ = st; }

	bool valid( void )
	{
		if( columnNumber_ < 0 )
			return false;

		switch( segmentType_ )
		{
		case CQL_ASCENDING :
		case CQL_DESCENDING :
		case CQL_SEGMENT_UNDEFINED_TYPE :
			return true;

		default :
			break;
		}

		return false;
	}
};


//  This class is a wrapper to allow a SegmentTypes list.  SegmentTypes can't be a
//  list member because a class derived from it is a list member
class SegmentTypesCreate : public SegmentTypesCreateListElement, public SegmentTypes
{
public :

	SegmentTypesCreate( const SegmentTypes& stype ) : SegmentTypesCreateListElement(), SegmentTypes( stype ) { }
};


class AccessorTypes : public AccessorQualifierTypes
{
	//  This member is used for the create() which takes CqlColumnTypes** and AccessorTypes**.
	//  For each member of the AccessorTypes array, an array of SegmentTypes descriptors is attached
	//  to this member.
	SegmentTypes **segments_;

public :

	enum AccessorType
	{
		CQL_TREE_INDEX,
		CQL_ACCESSOR_UNDEFINED_TYPE,
		DBZ_TREE_INDEX,
		DBZ_HASH_INDEX,
		DBZ_MATERIALIZED_JOIN
	};

private :

	AccessorType typeType_;

public :

	AccessorTypes( void ) : AccessorQualifierTypes(), typeType_( CQL_ACCESSOR_UNDEFINED_TYPE ) { }
	AccessorTypes( AccessorType atype, AccessorQualifierType aqtype = CQL_ACCESSOR_QUALIFIER_UNDEFINED_TYPE ) : AccessorQualifierTypes( aqtype ), typeType_( atype ) { }
	AccessorTypes( AccessorType atype, AccessorQualifierType aqtype, SegmentTypes **segs ) : AccessorQualifierTypes( aqtype ), segments_( segs ), typeType_( atype ) { }

	//  default destructor

	//  assignment operators
	AccessorTypes& operator = ( AccessorType type )
	{
		typeType_ = type;
		return *this;
	}

	SegmentTypes **segments( void ) { return segments_; }
	AccessorType typeType( void ) { return typeType_; }
	void typeType( AccessorType tt ) { typeType_ = tt; }

	bool valid( void )
	{
		switch( typeType_ )
		{
		case CQL_TREE_INDEX :
		case DBZ_TREE_INDEX :
		case DBZ_HASH_INDEX :
		case DBZ_MATERIALIZED_JOIN :
		case CQL_ACCESSOR_UNDEFINED_TYPE :
			break;

		default :
			return false;
		}

		return AccessorQualifierTypes::valid();
	}
};


class AccessorTypesCreate : public AccessorTypesCreateListElement, public AccessorTypes
{
	SegmentTypesCreateList segmentList_;

public :

	AccessorTypesCreate( const AccessorTypes& atype ) : AccessorTypesCreateListElement(), AccessorTypes( atype ) { }

	SegmentTypesCreateList& segmentList( void ) { return segmentList_; }
};


#endif //  __CqlTableConstants_h
