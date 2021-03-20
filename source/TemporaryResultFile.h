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


#ifndef __TemporaryResultFile_h
#define __TemporaryResultFile_h


//
//  this class specifies a temporary result set, which is an IsamFile with additional
//  members specifying the location and length of the refetch information.
//
class TemporaryResultFile : public ErrorConstants, public CqlConstants
{
	BoundColumnList boundColumns_;
	SqlHandle& dbsql_;
	AbstractTable *ifile_;
	UC *refetchInfo_;
	US refetchInfoColumnNumber_;
	UL refetchInfoLength_;
	bool refetchInfoNull_;
	AbstractType *value_;

public :

	TemporaryResultFile( SqlHandle& );
	virtual ~TemporaryResultFile( void );

	TemporaryResultFile& operator = ( const TemporaryResultFile& );

	NI Assign( SqlHandle*, TemporaryResultFile& );
	void bindBaseTablePositions( void );
	BoundColumnList& boundColumns( void ) { return boundColumns_; }
	void cleanup( void );
	void getBaseTablePositions( UC * );
	AbstractTable *ifile( void ) { return ifile_; }
	void ifile( AbstractTable *f ) { ifile_ = f; }
	UL refetchInfoLength( void ) { return refetchInfoLength_; }
	void refetchInfoAlloc( US /*length*/ );
	US refetchInfoColumnNumber( void ) { return refetchInfoColumnNumber_; }
	void refetchInfoColumnNumber( US ricn ) { refetchInfoColumnNumber_ = ricn; }
	void releaseResources( void );
	void setBaseTablePositions( UC * );
	AbstractType& value( void ) { return *value_; }
};


#endif  //  __TemporaryResultFile_h
