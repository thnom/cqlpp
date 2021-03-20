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


#include "CqlIsamInclude.h"


EnvironmentHandle::EnvironmentHandle( const CqlString& initialDirectory )
	:  OpenFileManager(),
	   BufferManager( initialDirectory ),
	   SystemConfigurationManager( initialDirectory ),
	   TransactionManager()
{
	environmentSpecificInitialization();

	//
	//  Buffer allocation, which used to be invoked manually, is now invoked automatically
	//  because EnvironmentHandle inherits from BufferManager.  This loses the ability to
	//  read the number of buffers out of the configuration file, but it is a much cleaner
	//  class structure.  To use the configuration file value for the number of cache buffers,
	//  a resize method on BufferManager is provided ( changeNumberOfCacheBuffers( UL ) ).
	//

	aem = new ErrorManager;

	if( !aem )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	transactionStartup( initialDirectory, CQL_LOG_NAME );
}


EnvironmentHandle::~EnvironmentHandle( void )
{
}


void EnvironmentHandle::transactionStartup( const CqlString& initialDirectory,
											const NC * const logName )
{
	CqlString logfileName, s, s2;
	UNI logNo, lastLog, curLogNum, logToBeginLogging, loop;
	UL maxTransNo = 0;
	ClibFileManager *curLog;

	NI endAnalysis,
		endPass2,
		rc,
		previousEndCreate,
		previousEndDelete,
		previousReverse,
		logEntryExists;

	RECID logPos;
	LogEntry logEntry;
	MemoryIndex workIndex;
	pLogPositionIndexNode logPositionIndexNode;
	LogAnalysisIndex logAnalysisIndex;
	pLogPageIndex logPageIndex = ((pLogPageIndex)&workIndex);
	pLogDeleteIndex logDeleteIndex = ((pLogDeleteIndex)&workIndex);
	pLogCreateIndex logCreateIndex = ((pLogCreateIndex)&workIndex);
	LogUndoneIndex logUndoneIndex;
	TransactionStack stack;

	if( getenv( "TRANSACTION_STARTUP_DEBUGGING" ) )
		transactionStartupDebugging = CQL_YES;

	if( transactionStartupDebugging == CQL_YES )
		*this << "****************** Begin transaction startup *****************\n";

	//  logs is a member of TransactionManager
	logs = new ClibFileManager*[ numberOfLogFiles() ];
	if( !logs )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	for( loop = 0; loop < numberOfLogFiles(); loop++ )
	{
		logs[ loop ] = new ClibFileManager;
		if( !logs[ loop ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	//  endOfLogs is a local variable used to hold a pointer to the end of the
	//  log on some open() methods.

	pRECID endOfLogs = new RECID[ numberOfLogFiles() ];
	if( !endOfLogs )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	try
	{
		if( initialDirectory.length() )
		{
			s = initialDirectory;
			s += "/";
		}
		else
			s = "";
		s += CQL_LOG_LOG_NAME;
	}
	catch( MemoryAllocationException& )
	{
		//  we want the memory failure to show the calling place in the
		//  code.  It is always the allocation of string space in the
		//  CqlString operator
		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	bool logLogExists = true;

	//exception
	try
	{
		// true means set position to the beginning of the file instead of the end
		logLog.open( s, true );
	}
	catch( ClibFileSystemDetailException& ex )
	{
		logLogExists = false;

		//  exception may be normal, because if file isn't there, we create it.
		try
		{
			logLog.create( s );
		}
		catch( ClibFileSystemException& ex2 )
		{
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw TransactionException( ex2.fileSystemError().text(), EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
		}

		//  logLog was successfully created.
		currentLogNumber = 0;
		try
		{
			logLog.write( ((void*)&currentLogNumber), sizeof( currentLogNumber ) );
		}
		//  exception
		catch( ClibFileSystemException& ex2 )
		{
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw TransactionException( ex2.fileSystemError().text(), EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
		}
	}

	//  If logLog exists, we read the current log number.  If we just created it,
	//  we read zero.  This is inefficient but harmless, as it only occurs during
	//  startup.
	if( logLogExists )
	{
		try
		{
			logLog.read( ((void*)&currentLogNumber), sizeof( currentLogNumber ) );
		}
		catch( EofException& ex )
		{
			std::cout << "EofException caught in "
					  << __FILE__
					  << ":"
					  << __LINE__
					  << std::endl;
			//  EOF is normal here, at least sometimes
		}
		catch( ClibFileSystemException& ex )
		{
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw TransactionException( ex.fileSystemError().text(), EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
		}
	}

	try
	{
		makeLogName( logfileName, CQL_LOG_NAME, currentLogNumber, initialDirectory );
	}
	catch( MemoryAllocationException& )
	{
		for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
			delete logs[ logNo ];

		throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	currentLog = logs[ currentLogNumber ];

	//  Open or create last log file used for pass one
	try
	{
		currentLog->open( logfileName, endOfLogFile );
	}
	catch( ClibFileSystemException& ex )
	{
		if( logLogExists )
		{
			//  if logLog exists and the corresponding log file doesn't exist, we have a bad state.
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw TransactionException( ex.fileSystemError().text(), EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
		}

		try
		{
			currentLog->create( logfileName );
		}
		catch( ClibFileSystemException& ex2 )
		{
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw TransactionException( ex2.fileSystemError().text(), EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
		}

		endOfLogFile = ((RECID)0);
	}

	//  Pass 1 is a backward scan.  The initial position is the end of
	//  the current log file.  Starting position is the end of the last log,
	//  specified by currentPosition and currentLogNumber.
	//
	//  *********************************We save the end of each log in the endOfLogs array.  Is this overwritten?

	currentPosition = endOfLogFile;
	endOfLogs[ currentLogNumber ] = endOfLogFile;
	lastLog = currentLogNumber;
	logToBeginLogging = currentLogNumber;

	//  This loop verifies that each expected log file exists.  If it does not
	//  exist, it is created with zero length.
	//  ***************** old comment "Determine first and last logs"?  Didn't we just do that
	//  in the preceding loop?  Doesn't the value of the entry in logLog tell us the latest log flie?

	for( logNo = NextLog( currentLogNumber ); logNo != currentLogNumber; logNo = NextLog( logNo ) )
	{
		try
		{
			s = logName;
		}
		catch( MemoryAllocationException& )
		{
			throw MemoryAllocationException( __FILE__, __LINE__ );
		}


		try
		{
			makeLogName( logfileName, s, logNo, initialDirectory );
		}
		catch( MemoryAllocationException& )
		{
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw MemoryAllocationException( __FILE__, __LINE__ );
		}

		bool openFailed = false;

		try
		{
			logs[ logNo ]->open( logfileName, endOfLogs[ logNo ] );
		}
		catch( ClibFileSystemException& )
		{
			openFailed = true;

			if( logLogExists == CQL_YES )
			{
				for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
					delete logs[ logNo ];

				throw TransactionException( "Log file exists, but open failed.", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
			}

			try
			{
				logs[ logNo ]->create( logfileName );
			}
			catch( ClibFileSystemException& ex )
			{
				for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
					delete logs[ logNo ];

				*this << ex;
				throw TransactionException( "Couldn't create essential log file.", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
			}

			endOfLogs[ logNo ] = 0;
		}

		if( !openFailed && endOfLogs[ logNo ] != 0 )
			lastLog = logNo;
	}

	//  at this point, we know the first and last logs.

	//  pass 1, make a list of open transactions, undone operations

	curLogNum = currentLogNumber;
	logPos = endOfLogFile;
	curLog = logs[ curLogNum ];

	for( endAnalysis = logEntryExists = CQL_NO; endAnalysis == CQL_NO; )
	{
		rc = ReadPreviousLogEntry( logEntry, curLog, &logPos );
		if( rc != CQL_SUCCESS )
		{
			if( rc == CQL_FAILURE )
			{
				for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
					delete logs[ logNo ];

				throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
			}

			for( ; ; )
			{
				//  are we finished?
				if( curLogNum == lastLog && logPos == 0 )
				{
					endAnalysis = CQL_YES;
					break;
				}

				//  move to the next log file
				curLogNum = PreviousLog( curLogNum );
				curLog = logs[ curLogNum ];
				logPos = endOfLogs[ curLogNum ];

				if( !logPos )
					continue;

				if( ReadPreviousLogEntry( logEntry, curLog, &logPos ) != CQL_SUCCESS )
				{
					for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
						delete logs[ logNo ];

					throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
				}

				break;
			}
		}
		else
			logEntryExists = CQL_YES;

		if( logEntryExists && logEntry.TransactionNumber() > maxTransNo )
			maxTransNo = logEntry.TransactionNumber();

		if( endAnalysis == CQL_YES )
			break;

		if( logEntry.UndoFlag() )
			if( logUndoneIndex.AddIndexNode( logEntry.UndoLog(), logEntry.UndoPosition() ) == CQL_FAILURE )
			{
				for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
					delete logs[ logNo ];

				throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
			}

		switch( logEntry.Command() )
		{
		case CLEAN_SHUTDOWN :
		case CLEAN_RECOVERY :
			if( transactionStartupDebugging == CQL_YES )
				*this << "CLEAN_SHUTDOWN or CLEAN_RECOVERY\n";
			endAnalysis = CQL_YES;
			break;

		case BEGIN_TRANSACTION :
			if( transactionStartupDebugging == CQL_YES )
				*this << "BEGIN_TRANSACTION: " << logEntry.TransactionNumber() << "\n";

			if( logAnalysisIndex.FindEqualKey( logEntry.TransactionNumber() ) == CQL_SUCCESS )
			{
				if( transactionStartupDebugging == CQL_YES )
					*this << "Corresponding commit or rollback found, deleting from list\n";

				if( logAnalysisIndex.deleteIndexNode() == CQL_FAILURE )
				{
					for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
						delete logs[ logNo ];

					throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
				}
			}
			else
			{
				if( transactionStartupDebugging == CQL_YES )
					*this << "COMMIT or ROLLBACK not found, adding to list\n";

				if( logAnalysisIndex.AddIndexNode( logEntry.TransactionNumber(), curLogNum, logPos ) == CQL_FAILURE )
				{
					for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
						delete logs[ logNo ];

					throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
				}
			}
			break;

		case END_COMMIT_TRANSACTION :
		case ROLLBACK_TRANSACTION :
			if( transactionStartupDebugging == CQL_YES )
				*this << "END_COMMIT or ROLLBACK: " << logEntry.TransactionNumber() << "\n";

			if( logAnalysisIndex.AddIndexNode( logEntry.TransactionNumber(), curLogNum, logPos ) == CQL_FAILURE )
			{
				for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
					delete logs[ logNo ];

				throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
			}
			break;

		case TRANSACTION_LOG_NOT_SET :
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );

		case BEGIN_COMMIT_TRANSACTION :
		case BEGIN_CREATE_FILE :
		case END_CREATE_FILE :
		case BEGIN_DELETE_FILE :
		case END_DELETE_FILE :
		case DELETE_PAGE :
		case ADD_PAGE :
		case UPDATE_PAGE :
		case REVERSE :
		case BEGIN_RECOVERY :
		case BEGIN_REVERSE_DELETE_FILE :
		case END_REVERSE_DELETE_FILE :
		case BEGIN_REVERSE_CREATE_FILE :
		case END_REVERSE_CREATE_FILE :
			break;
		}
	}

	//
	//  logAnalysisIndex now contains a list of transactions which were never committed.
	//  logUndoneIndex contains a list of operations that have been undone
	//

	if( transactionStartupDebugging == CQL_YES )
	{
		*this << "Transaction startup, pass 1 complete\n";
		*this << "List of uncommitted transactions:\n";

		for( rc = logAnalysisIndex.firstNode(); rc == CQL_SUCCESS; rc = logAnalysisIndex.nextNode() )
			*this << "    Transaction number " << logAnalysisIndex.CurrentNode()->TransactionNumber() << "\n";
	}

	UL incompleteSize;
		for( rc = logAnalysisIndex.firstNode(), incompleteSize = 0; rc == CQL_SUCCESS; rc = logAnalysisIndex.nextNode(), incompleteSize++ )
			;

	if( incompleteSize == 0 )
	{
		if( transactionStartupDebugging )
			*this << "Incomplete transaction list empty, nothing to process...\n";

		transactionCounter = maxTransNo + 1;
		return;
	}

	//  pass 2
	//
	//  This is another reverse scan.
	//  Pass two does more analysis, and also determines the starting
	//  point of the recovery operation, typically the last CLEAN_SHUTDOWN or CLEAN_RECOVERY.
	//  During pass 2, each log entry is examined to find whether it is part of a
	//  completed transaction or an incomplete transaction.
	//
	curLogNum = currentLogNumber;
	logPos = endOfLogFile;
	curLog = logs[ curLogNum ];

	for( endPass2 = previousEndCreate = previousEndDelete = previousReverse = CQL_NO; endPass2 == CQL_NO ; )
	{
		rc = ReadPreviousLogEntry( logEntry, curLog, &logPos );
		if( rc != CQL_SUCCESS )
		{
			//
			//  An error occured getting the previous log entry.  See if this is a real error or merely
			//  a normal end to pass 2.
			//
			if( rc == CQL_FAILURE )
			{
				for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
					delete logs[ logNo ];

				throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
			}

			for( ; ; )
			{
				if( curLogNum == lastLog && logPos == 0 )
				{
					endPass2 = CQL_YES;
					break;
				}

				curLogNum = PreviousLog( curLogNum );
				curLog = logs[ curLogNum ];
				logPos = endOfLogs[ curLogNum ];

				if( !logPos )
					continue;

				if( ReadPreviousLogEntry( logEntry, curLog, &logPos ) != CQL_SUCCESS )
				{
					for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
						delete logs[ logNo ];

					throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
				}

				break;
			}
		}

		if( endPass2 == CQL_YES )
			break;

		//
		//  If this is the first operation following a REVERSE, then this log entry should be skipped
		//  (again, remember that we are scanning backwards).
		//  We reset the previousReverse flag and continue.
		//
		if( previousReverse )
		{
			previousReverse = CQL_NO;
			continue;
		}

		//
		//  Switch on the transaction log entry type.
		//
		switch( logEntry.Command() )
		{
		case CLEAN_SHUTDOWN :
		case CLEAN_RECOVERY :
			//
			//  any time CLEAN_SHUTDOWN or CLEAN_RECOVERY is reached, analysis only needs
			//  to proceed from that point forward.
			//
			if( transactionStartupDebugging == CQL_YES )
				*this << "Reached CLEAN_SHUTDOWN or CLEAN_RECOVERY, terminating\n";
			endPass2 = CQL_YES;
			break;

		case BEGIN_CREATE_FILE :
			{
				//
				//  BEGIN_CREATE_FILE occurred.  This is either the beginning of an operation
				//  which should be completed (potentially) or should be undone.  Remember that
				//  we are scanning backwards, so that we associate BEGIN with END, rather
				//  than V.V.
				//
				if( transactionStartupDebugging == CQL_YES )
					*this << "BEGIN_CREATE_FILE entry... \n";
				//
				//  If create is part of an unfinished transaction, we need to delete.
				//  Is the log entry's transaction number in the logAnalysisIndex?
				//  logAnalysisIndex contains transactions which were never committed.
				//
				bool findStatus;

				//
				//  If we don't find the transactionNumber in logAnalysisIndex, this entry
				//  is not part of an incomplete transaction.
				//
				if( logAnalysisIndex.FindEqualKey( logEntry.TransactionNumber() ) == CQL_NOT_FOUND )
					findStatus = false;
				else
					findStatus = true;

				if( findStatus == true )
				{
					if( transactionStartupDebugging == CQL_YES )
						*this << "Part of incomplete transaction, adding to list.\n";

					//
					//  Transaction is in incomplete list.  Add to this file to deletion.  The file
					//  will be deleted if necessary.
					//
					//  Nothing here tries to determine whether the file exists.  It will eventually be
					//  deleted if it does exist.
					//

					s = logEntry.FileName();
					try
					{
						logDeleteIndex->AddIndexNode( s, previousEndCreate ? true : false, curLogNum, logPos );
					}
					catch( ClibFileSystemException& )
					{
						for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
							delete logs[ logNo ];

						throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
					}
					catch( ... )
					{
						std::cerr << "Unexpected exception, file: " << __FILE__ << ", line: " << __LINE__ << std::endl;
						throw;
					}
				}

				else if( findStatus && transactionStartupDebugging == CQL_YES )
					*this << "Not part of incomplete transaction.\n";

				previousEndCreate = previousEndDelete = CQL_NO;
			}
			break;

		case REVERSE :
			//
			//  For a reverse, we want the previous operation to be skipped.  Since we
			//  are scanning backwards, the next time through the for loop is the previous
			//  operation.
			//
			if( transactionStartupDebugging == CQL_YES )
				*this << "REVERSE entry.\n";
			previousEndCreate = previousEndDelete = CQL_NO;
			previousReverse = CQL_YES;
			break;

		case END_CREATE_FILE :
			//
			//  We set a flag indicating that this entry is END_CREATE_FILE.
			//  The next time through the loop,
			//
			if( transactionStartupDebugging == CQL_YES )
				*this << "END_CREATE_FILE entry.\n";
			//
			//  previousEndCreate and previousEndDelete end up in temporary index nodes.
			//  They are for a future planned enhancement.
			//
			previousEndCreate = CQL_YES;
			previousEndDelete = CQL_NO;
			break;

		case BEGIN_DELETE_FILE :
			{
			if( transactionStartupDebugging == CQL_YES )
				*this << "BEGIN_DELETE_FILE entry... \n";

			//
			//  If delete is part of an unfinished transaction, we need to rename the backup
			//  file that may have been created.
			//

			bool findStatus = true;

			try
			{
				logAnalysisIndex.FindEqualKey( logEntry.TransactionNumber() );
			}
			catch( ClibFileSystemException& )
			{
				//  Not part of an incomplete transaction
				findStatus = false;
			}

			if( findStatus )
			{
				if( transactionStartupDebugging == CQL_YES )
					*this << "Part of incomplete transaction, adding to list.\n";

				//  transaction is incomplete
				try
				{
					s = logEntry.FileName();
					s2 = logEntry.TemporaryName();
				}
				catch( MemoryAllocationException& ex )
				{
					for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
						delete logs[ logNo ];

					std::cerr << ex;
					throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
				}

				//
				//  Add an entry to the list of files which may need to be deleted, due to creation of
				//  a backup file.  FileName() is the old name, to which the file is to revert.
				//  TemporaryName() is the new name that may need to be deleted.
				//
				if( logCreateIndex->AddIndexNode( logEntry.FileName(), logEntry.TemporaryName(), previousEndDelete ? true : false, curLogNum, logPos ) == CQL_FAILURE )
				{
					for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
						delete logs[ logNo ];

					throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
				}
			}
			else if( transactionStartupDebugging == CQL_YES )
				*this << "Part of complete transaction.\n";

			previousEndCreate = previousEndDelete = CQL_NO;
			}
			break;

		case END_DELETE_FILE :
			//
			//  Set flags and continue
			//
			if( transactionStartupDebugging == CQL_YES )
				*this << "END_DELETE_FILE entry.\n";
			previousEndDelete = CQL_YES;
			previousEndCreate = CQL_NO;
			break;

		case ADD_PAGE :
		case DELETE_PAGE :
			if( transactionStartupDebugging == CQL_YES )
			{
				*this << "Page modification entry,  ";
				if( logEntry.Command() == ADD_PAGE )
					*this << "ADD_PAGE... \n";
				else
					*this << "DELETE_PAGE... \n";
			}

			try
			{
				s = logEntry.FileName();
			}
			catch( MemoryAllocationException& ex )
			{
				for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
					delete logs[ logNo ];

				std::cerr << ex;
				throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
			}

			if( logPageIndex->FindEqualKey( s, logEntry.PageNumber() ) == CQL_FAILURE )
			{
				*this << "Most recent for page... \n";
				//  this is the most recent log entry for this page.  Is transaction complete or incomplete?
				if( logAnalysisIndex.FindEqualKey( logEntry.TransactionNumber() ) == CQL_FAILURE )
				{
					if( transactionStartupDebugging == CQL_YES )
						*this << "Part of complete transaction, adding to list.\n";

					//  transaction is complete
					if( logPageIndex->AddIndexNode( s, logEntry.PageNumber(), logEntry.UndoLog(), logEntry.UndoPosition() ) == CQL_FAILURE )
					{
						for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
							delete logs[ logNo ];

						throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
					}
				}
			}
			else
			{
				if( transactionStartupDebugging == CQL_YES )
					*this << "Not most recent for page.\n";
			}

			previousEndCreate = previousEndDelete = CQL_NO;
			break;

		case BEGIN_TRANSACTION :
		case ROLLBACK_TRANSACTION :
		case BEGIN_COMMIT_TRANSACTION :
		case END_COMMIT_TRANSACTION :
		case UPDATE_PAGE :
		case BEGIN_RECOVERY :
		case BEGIN_REVERSE_DELETE_FILE :
		case END_REVERSE_DELETE_FILE :
		case BEGIN_REVERSE_CREATE_FILE :
		case END_REVERSE_CREATE_FILE :
			if( transactionStartupDebugging == CQL_YES )
			{
				*this << "Ignoring entry:  ";
				switch( logEntry.Command() )
				{
				case BEGIN_TRANSACTION :
					*this << "BEGIN_TRANSACTION\n";
					break;

				case ROLLBACK_TRANSACTION :
					*this << "ROLLBACK_TRANSACTION\n";
					break;

				case BEGIN_COMMIT_TRANSACTION :
					*this << "BEGIN_COMMIT_TRANSACTION\n";
					break;

				case END_COMMIT_TRANSACTION :
					*this << "END_COMMIT_TRANSACTION\n";
					break;

				case UPDATE_PAGE :
					*this << "UPDATE_PAGE\n";
					break;

				case BEGIN_RECOVERY :
					*this << "BEGIN_RECOVERY\n";
					break;

				case BEGIN_REVERSE_DELETE_FILE :
					*this << "BEGIN_REVERSE_DELETE_FILE\n";
					break;

				case END_REVERSE_DELETE_FILE :
					*this << "END_REVERSE_DELETE_FILE\n";
					break;

				case BEGIN_REVERSE_CREATE_FILE :
					*this << "BEGIN_REVERSE_CREATE_FILE\n";
					break;

				case END_REVERSE_CREATE_FILE :
					*this << "END_REVERSE_CREATE_FILE\n";
					break;

				default :
					*this << "This can't happen.\n";
				}
			}
			previousEndCreate = previousEndDelete = CQL_NO;
			break;

		case TRANSACTION_LOG_NOT_SET :
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
		}
	}

	if( transactionStartupDebugging == CQL_YES )
		*this << "Transaction startup, pass 2 complete, beginning pass 3\n";

	//
	//  logCreateIndex now contains a list of files that may need to be deleted.
	//

	//  pass3, do the work

	for( rc = workIndex.lastNode(); rc == CQL_SUCCESS; rc = workIndex.previousNode() )
	{
		if( transactionStartupDebugging == CQL_YES )
			*this << "Entry in work index... \n";

		logPositionIndexNode = ((pLogPositionIndexNode)workIndex.currentNode());

		if( logUndoneIndex.FindEqualKey( logPositionIndexNode->LogNumber(), logPositionIndexNode->LogPosition() ) == CQL_SUCCESS )
		{
			if( transactionStartupDebugging == CQL_YES )
				*this << "Entry in undone list, skipping\n";
			continue;
		}

		if( ReadLogEntry( logEntry, logs[ logPositionIndexNode->LogNumber() ], logPositionIndexNode->LogPosition() ) == CQL_FAILURE )
		{
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
		}

		if( transactionStartupDebugging == CQL_YES )
			*this << "Calling RecoveryProcessing for entry\n";

		if( logPositionIndexNode->RecoveryProcessing( *this, stack, logEntry ) == CQL_FAILURE )
		{
			for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
				delete logs[ logNo ];

			throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
		}
	}

	if( transactionStartupDebugging == CQL_YES )
		*this << "Pass three complete\n";

	curLogNum = logToBeginLogging;

	logPos = endOfLogs[ curLogNum ];
	delete [] endOfLogs;

	curLog = logs[ curLogNum ];
	try
	{
		curLog->seekToEnd();
	}
	catch( CqlException& ex )
	{
		for( logNo = 0; logNo < numberOfLogFiles(); logNo++ )
			delete logs[ logNo ];
		throw ex;
	}

	transactionCounter = maxTransNo + 1;

	curLog->outputSeek( logPos );

	try
	{
		logAnalysisIndex.destroyIndex();
	}
	catch( ClibFileSystemException& ex )
	{
		std::cerr << ex;
		throw TransactionException( "Transaction log inconsistency", EC_TRANSACTION_FILE_ERROR, __FILE__, __LINE__ );
	}
}


UNI EnvironmentHandle::NextLog( UNI logNo )
{
	UNI lno = logNo + 1;

	if( lno == numberOfLogFiles() )
		lno = 0;
	return lno;
}


UNI EnvironmentHandle::PreviousLog( UNI logNo )
{
	if( logNo != 0 )
		return logNo - 1;
	else
		return numberOfLogFiles() - 1;
}


NI EnvironmentHandle::WriteLogEntry( TransactionStack& stack )
{
	if( stack.size() > 1 )
		return CQL_SUCCESS;

	if( currentPosition > logFileSize() )
	{
		currentLogNumber = NextLog( currentLogNumber );
		if( currentLogNumber == commitStartLog )
			throw TransactionException( "Transaction size exceeds available log space", EC_TRANSACTION_EXCEEDS_LOG_SPACE, __FILE__, __LINE__ );
		
		currentLog = logs[ currentLogNumber ];
		currentPosition = 0;
		currentLog->outputSeek( currentPosition );
		logLog.outputSeek( 0 );
		logLog.write( ((void*)&currentLogNumber), sizeof( currentLogNumber ) );
		logLog.flush();
	}

	currentLog->write( ((void*)EntryBuffer()), ((UNI)LogEntryLength() ) );
	currentPosition += LogEntryLength();

	currentLog->flush();

	return CQL_SUCCESS;
}


NI EnvironmentHandle::LogCommandOnly( TransactionStack& stack, LogCommands cmd, NI zeroTransactionNumber )
{
	CqlString emptyCqlString( "" );

	if( Setup( stack, cmd, emptyCqlString, ((pUC)0), 0, 0, 0, 0, emptyCqlString, zeroTransactionNumber ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( WriteLogEntry( stack ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI EnvironmentHandle::LogReverse( TransactionStack& stack )
{
	return LogCommandOnly( stack, LogEntry::REVERSE );
}


NI EnvironmentHandle::LogBeginCreateFile( TransactionStack& stack, CqlString& name )
{
	if( Setup( stack, LogEntry::BEGIN_CREATE_FILE, name ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( WriteLogEntry( stack ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI EnvironmentHandle::LogEndCreateFile( TransactionStack& stack )
{
	return LogCommandOnly( stack, LogEntry::END_CREATE_FILE );
}


NI EnvironmentHandle::LogBeginDeleteFile( TransactionStack& stack,
										  const CqlString& name )
{
	if( Setup( stack, LogEntry::BEGIN_DELETE_FILE, const_cast<CqlString&>(name) ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( WriteLogEntry( stack ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI EnvironmentHandle::LogEndDeleteFile( TransactionStack& stack )
{
	return LogCommandOnly( stack, LogEntry::END_DELETE_FILE );
}


NI EnvironmentHandle::LogBeginReverseDeleteFile( TransactionStack& stack, CqlString& originalName, CqlString& tempName, UNI logNo, RECID logPos )
{
	if( Setup(
		stack,
		LogEntry::BEGIN_REVERSE_DELETE_FILE,
		originalName,
		((pUC)0),
		((UL)0),
		CQL_YES,
		logNo,
		logPos,
		tempName ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( WriteLogEntry( stack ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI EnvironmentHandle::LogEndReverseDeleteFile( TransactionStack& stack )
{
	return LogCommandOnly( stack, LogEntry::END_REVERSE_DELETE_FILE );
}


NI EnvironmentHandle::LogBeginReverseCreateFile( TransactionStack& stack, CqlString& name, UNI logNo, RECID logPos )
{
	if( Setup(
		stack,
		LogEntry::BEGIN_REVERSE_CREATE_FILE,
		name,
		((pUC)0),
		((UL)0),
		CQL_YES,
		logNo,
		logPos ) == CQL_FAILURE )
		return CQL_FAILURE;

	if( WriteLogEntry( stack ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


NI EnvironmentHandle::LogEndReverseCreateFile( TransactionStack& stack )
{
	return LogCommandOnly( stack, LogEntry::END_REVERSE_CREATE_FILE );
}


NI EnvironmentHandle::TransBeginTransaction( TransactionStack& stack )
{
	return LogCommandOnly( stack, LogEntry::BEGIN_TRANSACTION );
}


NI EnvironmentHandle::StartCommitTransaction( TransactionStack& stack )
{
	commitStartLog = currentLogNumber;
	return LogCommandOnly( stack, LogEntry::BEGIN_COMMIT_TRANSACTION );
}


NI EnvironmentHandle::EndCommitTransaction( TransactionStack& stack )
{
	if( LogCommandOnly( stack, LogEntry::END_COMMIT_TRANSACTION ) == CQL_FAILURE )
		return CQL_FAILURE;

	currentLog->flush();
	return CQL_SUCCESS;
}


NI EnvironmentHandle::TransRollbackTransaction( TransactionStack& stack )
{
	return LogCommandOnly( stack, LogEntry::ROLLBACK_TRANSACTION );
}


NI EnvironmentHandle::LogPage( TransactionStack& stack, pTransactionPageIndexNode tpage )
{
	if( tpage->FileMgr()->temporary() == CQL_YES )
		return CQL_SUCCESS;

	BaseBufferPage *basePage;
	BufferPage *lastPage, *prevPage;
	pPageChainElement lastChain, last2Chain;
	pUC bufferPointer;
	NI outermostTransaction;

	//
	//  find end of page chain
	//
	basePage = tpage->BasePage();
	lastChain = basePage->transactionPages().last();
	last2Chain = basePage->transactionPages().prev();
	lastPage = lastChain->Page();
	if( last2Chain )
	{
		prevPage = last2Chain->Page();
		outermostTransaction = CQL_NO;
	}
	else
	{
		prevPage = basePage->page();
		outermostTransaction = CQL_YES;
	}

	if( outermostTransaction == CQL_NO )
		return CQL_SUCCESS;

	//  this is called to make sure the buffer is swapped in if it was swapped out earlier.
	bufferPointer = BufferManager::getDataPointer( basePage, 0 );

	if( !lastPage->added() )
	{
		//  write the old page
		if( Setup(
			stack,
			LogEntry::DELETE_PAGE,
			tpage->FileMgr()->Name(),
			prevPage->space(),
			CQL_PAGE_SIZE ) == CQL_FAILURE )
			return CQL_FAILURE;

		if( WriteLogEntry( stack ) == CQL_FAILURE )
			return CQL_FAILURE;
	}

	//  write the modified space
	if( Setup( stack, LogEntry::ADD_PAGE, tpage->FileMgr()->Name(), lastPage->space(), CQL_PAGE_SIZE ) == CQL_FAILURE )
		return CQL_FAILURE;
	if( WriteLogEntry( stack ) == CQL_FAILURE )
		return CQL_FAILURE;

	return CQL_SUCCESS;
}


void EnvironmentHandle::TransactionCleanup( DatabaseHandle& hDb )
{
	UNI loop;

	LogCommandOnly( hDb.stack(), LogEntry::CLEAN_SHUTDOWN, CQL_YES );

	for( loop = 0; loop < numberOfLogFiles(); loop++ )
	{
		logs[ loop ]->close();
		delete logs[ loop ];
	}

	delete [] logs;

	logLog.close();
}


bool EnvironmentHandle::fileExists( const CqlString& name )
{
	ClibFileManager _file;
	CqlString lname = name;

	lname += CQL_DATA_FILE_EXTENSION;
	//exception

	return _file.clibFileExists( lname.text() );
}
