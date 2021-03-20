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


#ifndef __LogEntry_h
#define __LogEntry_h


class LogEntry : virtual public ErrorConstants, virtual public ExceptionCodes
{
public :

	enum LogCommands
	{
		ADD_PAGE,
		BEGIN_COMMIT_TRANSACTION,
		BEGIN_CREATE_FILE,
		BEGIN_DELETE_FILE,
		BEGIN_RECOVERY,
		BEGIN_REVERSE_CREATE_FILE,
		BEGIN_REVERSE_DELETE_FILE,
		BEGIN_TRANSACTION,
		CLEAN_RECOVERY,
		CLEAN_SHUTDOWN,
		DELETE_PAGE,
		END_COMMIT_TRANSACTION,
		END_CREATE_FILE,
		END_DELETE_FILE,
		END_REVERSE_CREATE_FILE,
		END_REVERSE_DELETE_FILE,
		REVERSE,
		ROLLBACK_TRANSACTION,
		TRANSACTION_LOG_NOT_SET,
		UPDATE_PAGE
	};

private :

	enum LogCommands *command;
	pUL dataLength;
	pUC entryBuffer;
	pNC fileName;
    pUL footerEntryLength;
	pUC logData;
	pUL logEntryLength;
    pUL pageNumber;
	//************************************************************************
	//**  temporaryName is also used for extra log name.                    **
	//************************************************************************
    pNC temporaryName;
    pUL transactionNumber;
    pNI undoFlag;
    pUNI undoLog;
    pRECID undoPosition;

public :

	LogEntry( void );
    virtual ~LogEntry( void );

    LogCommands Command( void ) { return *command; }
	UL DataLength( void ) { return *dataLength; }
    pUC EntryBuffer( void ) { return entryBuffer; }
    pNC FileName( void ) { return fileName; }
    pUC LogData( void ) { return logData; }
    UL LogEntryLength( void ) { return *logEntryLength; }
    NI makeLogName( CqlString& result, CqlString& nameBase, UNI logNum );
    UL PageNumber( void ) { return *pageNumber; }
    NI SetBuffer( UL );

    NI Setup(
		TransactionStack& /* stack */,
		LogCommands /*cmd*/,
		CqlString& /* fName */ = nullCqlString,
		pUC /* data */ = ((pUC)0),
		UL /* dataLen */ = ((UL)0),
		NI /* uFlag */ = CQL_NO,
		UNI /* ulog */ = 0,
		UL /* uPos */ = 0,
		CqlString& /* tempName */ = nullCqlString,
		NI /* zeroTransactionNumber */ = CQL_NO );

    pNC TemporaryName( void ) { return temporaryName; }
    UL TransactionNumber( void ) { return *transactionNumber; }
    NI UndoFlag( void ) { return *undoFlag; }
    UNI UndoLog( void ) { return *undoLog; }
    RECID UndoPosition( void ) { return *undoPosition; }
};

typedef LogEntry *pLogEntry;
typedef LogEntry::LogCommands *pLogCommands;


#endif  //  __LogEntry_h
