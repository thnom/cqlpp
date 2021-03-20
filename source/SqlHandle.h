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


#ifndef __SqlHandle_h
#define __SqlHandle_h


class SqlHandle : public CqlConstants, public ErrorConstants
{
	TablenameIndex activeTables_;
	AbstractDatabaseHandle *aHandle_;
	Cursor *currentCursor_;
	StatementHandle *currentStatement_;
	CursorList cursors_;
	IndexDictionary *indexDict_;
	CqlString *initialDirectory_;
	MainDictionary *mainDict_;
	CqlString *outputFile_;
	Parser *parse_;
	CqlString *password_;
	PrivilegeDictionary *privilegeDict_;
	PrivilegeFieldDictionary *privilegeFieldDict_;
	bool readOnly_;
	RefersDictionary *refers_;
	bool relaxedLocking_;
	CqlString *script_;
	bool strictLocking_;
	SystemTableColumns *systemTableColumns_;
	SystemTableIndices *systemTableIndices_;
	SystemTableTables *systemTableTables_;
	UNI temporaryNameCount_;
	UNI updateCount_;
	CqlString *user_;
	SelectExpressionList workingSets_;

	void addDictionaryEntry( TableSpecification& );
	void addDictionaryEntry( CqlString&, CqlString&, pTempBuffer );
	void addIndexDictionaryRecord( CqlString&, CqlString&, CqlString& );
	void addPrivilegeFieldRecord( PrivilegeFieldDictionaryRecord& );
	void addOrUpdatePrivilegeRecord( PrivilegeDictionaryRecord& );
	bool checkForDeletePrivilege( pTableTableElement );
	bool checkForDeletePrivilege( bool& /*grantOption*/, CqlString&, CqlString& );
	bool checkForInsertPrivilege( pAbstractTableSpecification );
	bool checkForInsertPrivilege( bool& /*grantOption*/, CqlString&, CqlString& );
	bool checkForSelectPrivilege( pSelectExpression );
	bool checkForSelectPrivilege( bool& /*grantOption*/, CqlString&, CqlString& );
	bool checkForUpdatePrivilege( pTableTableElement, ColumnTable& );
	bool checkForUpdatePrivilege( bool& /*grantOption*/, CqlString&, CqlString&, GrantColumnList& );
	void closeAllCursors( void );
	void deleteIndexDictionaryRecord( CqlString& );
	void deletePrivilegeRecords( PrivilegeDictionaryRecord& );
	void incrementUpdateCount( void ) { updateCount_++; }
	MainDictionary& mainDict( void ) { return *mainDict_; }
	RefersDictionary& refers( void ) { return *refers_; }
	void updateCount( UNI val ) { updateCount_ = val; }

protected :

	friend class DatabaseFunctionInstruction;
	friend class Parser;
	friend class Predicate;
	friend class SelectExpression;
	friend class SubqueryInstruction;
	friend class TableSpecification;
	friend class TableTableElement;
	friend class UserFunctionInstruction;
	friend class ViewSpecification;

	void allocateWorkingSet( void );
	void clearStatementEnded( void );
	void consumeUntilSelect( CqlString&, pNC );
	Cursor *currentCursor( void ) { return currentCursor_; }
	pStatementHandle currentStatement( void ) { return currentStatement_; }
	CursorList& cursors( void ) { return cursors_; }
	void deleteDictionaryEntry( TableSpecification* );
	void deleteMainDictionaryEntry( AbstractTableSpecification* );
	NC escapeCharacter( void );
	bool escapeFlag( void );
	void findTableForIndex( CqlString&, CqlString&, CqlString& );
	AbstractTableSpecification *getDictionaryRecord( const CqlString&, const CqlString& );
	void updateDictionaryInformation( pTableSpecification oldTable, pTableSpecification newTable );
	SelectExpressionList& workingSets( void ) { return workingSets_; }

public :

	//************************************************************************
	//**  These methods are public because of limitations in the C++ class  **
	//**  protection mechanisms.  The alternative is to make one public     **
	//**  interface class (for example, StatementHandle) a friend of        **
	//**  another public interface class (for example, SqlHandle).  This    **
	//**  would expose the entire private/protected interface of one        **
	//**  public interface class to any application which declares an       **
	//**  object of the other public interface class.  The following        **
	//**  public declarations, while ugly, are the lesser of two evils.     **
	//**  Note that these classes are not indented for general use and      **
	//**  their signature is subject to change in future releases.          **
	//************************************************************************

	Parser *parse( void ) { return parse_; }

	//************************************************************************
	//**  The real public interface starts here.                            **
	//************************************************************************

	SqlHandle(CqlString* /*user*/, CqlString* /*password*/, CqlString* /*initialDirectory*/, CqlString* /*script*/, CqlString* /*outputFile*/);
	~SqlHandle( void );

	SqlHandle& operator = ( const SqlHandle& );

	TablenameIndex& activeTables( void ) { return activeTables_; }
	AbstractDatabaseHandle& aHandle( void ) { return *aHandle_; }
	inline void beginTransaction( void );
	void close( pCursor );
	void commitTransaction( bool /*followWithBegin*/ = true );
	void connect(void);
	char *sysCurrentDirectory( void ) { return Clib::sCurrentDirectory(); }
	Cursor *declareCursor( const char * const /*statement*/ );
	void disableLocking( void );
	void disconnect( void );
	void error( ErrorConstants::ErrorCodes& err, NC *errorFile, NI& errorLine, NI& osError );
	inline ErrorCodes errorCode( void );
	inline CqlString& errorFile( void );
	inline NI errorLine( void );
	void execute( void );
	void executeImmediate( const char * const );
	inline bool fileExists( const CqlString& );
	inline ColumnMetadataList *getColumnMetadata( TableId * /*table ID*/ );
	inline const char * const getErrorText( ErrorCodes );
	inline const char * const getSqlstate( ErrorCodes );
	inline TableIdList *getTableIds( const CqlString& owner );
	inline void initialDirectory(CqlString *val) { initialDirectory_ = val; }
	inline CqlString *initialDirectory(void) { return initialDirectory_; }
	inline bool interactiveMode( void );
	inline bool noError( void );
	inline AbstractTable *openAbstractTable( const char * const /*name*/, TableType = CQL_CQL );
	inline NI osError( void );
	inline CqlString *outputFile(void) { return outputFile_; }
	inline CqlString *password(void ) { return password_; }
	StatementHandle *prepare( NC* /*statement*/ );
	void prepare( StatementHandle* /*sh*/, NC* /*statement*/ );
	bool relaxedLocking( void ) { return relaxedLocking_; }
	inline void resetError( void );
	inline NI returnError( ErrorCodes, const char * const /*filename*/, NI /*linenumber*/, NI /*os error*/ = 0 );
	inline NI returnNormal( ErrorCodes, pNC, NI );
	inline NI returnNormalOrError( void );
	void rollbackTransaction( bool /*followWithBegin*/ = true );
	inline CqlString *script(void) { return script_; }
	void setLockingRelaxed( void );
	void setLockingStrict( void );
	bool strictLocking( void ) { return strictLocking_; }
	SystemTableColumns& systemTableColumns( void ) { return *systemTableColumns_; }
	SystemTableIndices& systemTableIndices( void ) { return *systemTableIndices_; }
	SystemTableTables& systemTableTables( void ) { return *systemTableTables_; }
	NC *temporaryName( void );
	UNI updateCount( void ) { return updateCount_; }
	inline CqlString *user(void) { return user_; }
};


#endif  //  __SqlHandle_h
