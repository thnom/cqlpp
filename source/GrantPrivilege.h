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


#ifndef __GrantPrivilege_h
#define __GrantPrivilege_h


class GrantPrivilege;
typedef List< GrantPrivilege > GrantPrivilegeList;
typedef ListElement< GrantPrivilege, GrantPrivilegeList > GrantPrivilegeListElement;


class GrantPrivilege : public GrantPrivilegeListElement
{
	BFT deletePriv_ : 1;
	BFT insertPriv_ : 1;
	BFT referencesPriv_ : 1;
	BFT selectPriv_ : 1;
	BFT updatePriv_ : 1;

	GrantColumnList grantColumns_;
	GrantColumnList referenceColumns_;

public :

	GrantPrivilege( void );
	~GrantPrivilege( void );

	GrantPrivilege& operator=( const GrantPrivilege& );

	void clearDeletePriv( void ) { deletePriv_ = CQL_NO; }
	void clearInsertPriv( void ) { insertPriv_ = CQL_NO; }
	void clearReferencesPriv( void ) { referencesPriv_ = CQL_NO; }
	void clearSelectPriv( void ) { selectPriv_ = CQL_NO; }
	void clearUpdatePriv( void ) { updatePriv_ = CQL_NO; }
	NI deletePriv( void ) { return deletePriv_; }
	GrantColumnList& grantColumns( void ) { return grantColumns_; }
	NI insertPriv( void ) { return insertPriv_; }
	NI referencesPriv( void ) { return referencesPriv_; }
	GrantColumnList& referenceColumns( void ) { return referenceColumns_; }
	NI selectPriv( void ) { return selectPriv_; }
	void setDeletePriv( void ) { deletePriv_ = CQL_YES; }
	void setInsertPriv( void ) { insertPriv_ = CQL_YES; }
	void setReferencesPriv( void ) { referencesPriv_ = CQL_YES; }
	void setSelectPriv( void ) { selectPriv_ = CQL_YES; }
	void setUpdatePriv( void ) { updatePriv_ = CQL_YES; }
	void reset( void );
	NI updatePriv( void ) { return updatePriv_; }
};

typedef GrantPrivilege *pGrantPrivilege;


#endif  //  __GrantPrivilege_h
