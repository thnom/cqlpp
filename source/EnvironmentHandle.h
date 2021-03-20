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



#ifndef __EnvironmentHandle_h
#define __EnvironmentHandle_h


class EnvironmentHandle
	:	public BufferManager,
		public SystemConfigurationManager,
		virtual public OpenFileManager,
		public TransactionManager,
		public UserManager
{
	UC globalBuffer_[ CQL_PAGE_SIZE ];

	NI LogCommandOnly( TransactionStack&, LogCommands, NI = CQL_NO );

public :

	EnvironmentHandle( const CqlString& /*initial directory*/ );
	~EnvironmentHandle( void );

	NI allocateBuffers( UL );
	void Cleanup( TransactionStack& );
	void Cleanup( void ) { BufferManager::cleanup(); }
	char *osCurrentDirectory( void ) { return Clib::sCurrentDirectory(); }
	NI EndCommitTransaction( TransactionStack& );
	bool fileExists( const CqlString& );
	pUC globalBuffer( void ) { return globalBuffer_; }
	NI LogBeginCreateFile( TransactionStack&, CqlString& );
	NI LogBeginDeleteFile( TransactionStack&, const CqlString& );
	NI LogBeginReverseCreateFile( TransactionStack&, CqlString&, UNI, RECID );
	NI LogBeginReverseDeleteFile( TransactionStack&, CqlString&, CqlString&, UNI, RECID );
	NI LogEndCreateFile( TransactionStack& );
	NI LogEndDeleteFile( TransactionStack& );
	NI LogEndReverseCreateFile( TransactionStack& );
	NI LogEndReverseDeleteFile( TransactionStack& );
	NI LogPage( TransactionStack&, TransactionPageIndexNode* );
	NI LogReverse( TransactionStack& );
	UNI NextLog( UNI );
	UNI PreviousLog( UNI );
	NI StartCommitTransaction( TransactionStack& );
	void TransactionCleanup( DatabaseHandle& );
	void transactionStartup( const CqlString& /*initial directory*/, const NC * const );
	NI TransBeginTransaction( TransactionStack& );
	NI TransRollbackTransaction( TransactionStack& );
	NI WriteLogEntry( TransactionStack& );
};

typedef EnvironmentHandle *pEnvironmentHandle;


#endif  //  __EnvironmentHandle_h
