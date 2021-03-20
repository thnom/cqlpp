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


#ifndef __LogPageIndexNode_h
#define __LogPageIndexNode_h


class LogPageIndexNode : public LogPositionIndexNode, public ErrorConstants
{
	UL pageNumber;

public :

	LogPageIndexNode( const CqlString& fName, const UL pageNo, const UNI logNo = 0, const RECID logPos = 0 );
	~LogPageIndexNode( void );

    CqlConstants::CompareResult compareKeys( pMemoryIndexNode node2 );
	NI RecoveryProcessing( EnvironmentHandle&, TransactionStack&, LogEntry& );
};

typedef LogPageIndexNode *pLogPageIndexNode;


#endif  //  __LogPageIndexNode_h
