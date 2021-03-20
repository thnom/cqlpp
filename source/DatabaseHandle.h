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


#ifndef __DatabaseHandle_h
#define __DatabaseHandle_h


class DatabaseHandle : public AbstractDatabaseHandle
{
	ErrorManager errorManager_;
	IsamFileList openIsamFiles_;
	TransactionStack stack_;
	UL user_;
	UserConfigurationManager userConfig_;

	void writePageToDisk( TransactionPageIndexNode* );
	void flushToBuffers( void );

public :

	DatabaseHandle( const CqlString& /* userName */,
					const CqlString& /* password */,
					const CqlString& /* initialDirectory*/ );
	~DatabaseHandle( void );

	void addToIndexIndex( Index* );
	void addToIsamIndex( IsamFile* );
	AbstractErrorManager& aErrorMan( void ) { return errorManager_; }
	void beginTransaction( void );
	void close( FileManager& );
	void commitTransaction( void );
	UL currentTransaction( void );
	void deleteFromIndexIndex( Index* );
	void deleteFromIsamIndex( IsamFile* );
	void disconnect( void );
	ErrorManager& errorManager( void ) { return errorManager_; }
	FileManager* open( CqlString& str );
	IsamFileList& openIsamFiles( void ) { return openIsamFiles_; }
	void purgeTransactionInformationForIsamFile( AbstractTable* );
	void rollbackTransaction( void );
	TransactionStack& stack( void ) { return stack_; }
	UL user( void ) { return user_; }
	UserConfigurationManager& userConfig( void ) { return userConfig_; }
};


#endif  //  __DatabaseHandle_h
