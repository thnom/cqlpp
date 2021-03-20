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


#include "CqlCommonInclude.h"


AbstractColumnDescriptor::AbstractColumnDescriptor( void ) : AbstractColumnDescriptorListElement(),
																														 bc_( 0 ),
																														 keyMapList_()
{
}


AbstractColumnDescriptor::~AbstractColumnDescriptor( void )
{
	if( bc_ )
	{
		delete bc_;
		bc_ = 0;
	}

	keyMapList_.destroy();
}


AbstractSegmentDescriptor& AbstractSegmentDescriptor::operator = ( const AbstractSegmentDescriptor& other )
{
	segmentNumber_ = other.segmentNumber_;
	column_ = other.column_;

	return *this;
}


void AbstractColumnDescriptor::bc( BoundColumn *b )
{
	if( bc_ )
		delete bc_;

	bc_ = b;
}


AbstractColumnDescriptor *AbstractColumnDescriptor::input( TempBuffer& tb )
{
	US columnNumber;
	bool descending;
	CqlColumnTypes type;

	tb >> type >> columnNumber >> descending;
	AbstractColumnDescriptor *cd = createObject( type, columnNumber, descending );
	return cd;
}


AbstractColumnDescriptorList::AbstractColumnDescriptorList( void ) : AbstractColumnDescriptorListBase()
{
}


AbstractColumnDescriptorList::~AbstractColumnDescriptorList( void )
{
}


US AbstractColumnDescriptorList::dictionaryLength( void )
{
	US _size;
	pAbstractColumnDescriptor cd;

	//  for number of columns
	_size = sizeof( UNI );

	for( cd = first(); cd; cd = next() )
		_size = ((US)( _size + cd->dictionaryLength() ) );

	return _size;
}


void AbstractColumnDescriptorList::input( TempBuffer& tb )
{
	pAbstractColumnDescriptor cd;
	UNI loop;

	for( loop = 0; loop < size(); loop++ )
	{
		cd = AbstractColumnDescriptor::input( tb );
		add( cd );
	}
}


void AbstractColumnDescriptorList::writeDictionaryInformation( TempBuffer& buffer )
{
	buffer << size();
	AbstractColumnDescriptor *acd;
	for( acd = first(); acd; acd = next() )
		buffer << *acd;
}


void AbstractColumnDescriptorList::readDictionaryInformation( TempBuffer& buffer )
{
	UNI _size;
	buffer >> _size;
	UNI loop;
	AbstractColumnDescriptor *acd;
	for( loop = 0; loop < _size; loop++ )
	{
		acd = AbstractColumnDescriptor::input( buffer );
		add( acd );
	}
}


AbstractDatabaseHandle::AbstractDatabaseHandle( const CqlString& user,
												const CqlString& password,
												const CqlString& initialDirectory )
	: userName_( user ), initDir_(initialDirectory)
{
	CqlString _user;
	if( user.length() )
		_user = user;
	else
		_user = "PUBLIC";

	CqlString _pw;
	if( password != 0 && password.length() )
		_pw = password;
	else
		_pw = "";

	CqlString _idirectory;
	if( initialDirectory != 0 && initialDirectory.length() )
		_idirectory = initialDirectory;
	else
		_idirectory = Clib::sCurrentDirectory();

	if( !hAEnv )
		hAEnv = AbstractEnvironmentHandle::createObject( initialDirectory );

	hAEnv->connect( this );
}


AbstractDatabaseHandle::~AbstractDatabaseHandle( void )
{
	hAEnv->disconnect( this );
}


AbstractTable *AbstractDatabaseHandle::openAbstractTable( const char * const name, TableType tt )
{
	AbstractTable *at = AbstractTable::createObject( *this, tt );

	try
	{
		CqlString sName( name );
		at->open( sName );
	}
	catch( ... )
	{
		delete at;
		throw;
	}

	return at;
}


NI AbstractDatabaseHandle::returnError( ErrorCodes ec,
										const char * const fname,
										NI lineNo,
										NI osErr )
{
	return aErrorMan().returnError( ec, fname, lineNo, osErr );
}


AbstractEnvironmentHandle::AbstractEnvironmentHandle( const CqlString& initialDirectory,
													  const char * const traceSpecEnvName )
	: Clib(),
	  AbstractLogger( initialDirectory ),
	  defaultEnvName_( "CQL_TRACE_CONFIG" ),
	  cppLibraryTrace_( false ),
	  referenceCount_( 0 )
{
	if( initialDirectory.length() )
		optionCurrentDirectory_ = new CqlString( initialDirectory );
	else
		optionCurrentDirectory_ = new CqlString( Clib::sCurrentDirectory() );
	if( !optionCurrentDirectory_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	connectionMan_ = new ConnectionManager;
	if( !connectionMan_ )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	CqlString result;

	char *tsen = const_cast<char*>( traceSpecEnvName );
	if( strlen( tsen ) == 0 )
		tsen = const_cast<char*>(defaultEnvName_);

	getEnvironmentVariableValue( result, tsen, "0" );
	unsigned int traceSpec;
	sscanf( const_cast<char*>(result.text()), "%u", &traceSpec );
	if( traceSpec & TRACE_CPP_LIBRARY )
		cppLibraryTrace_ = true;
}


AbstractEnvironmentHandle::~AbstractEnvironmentHandle( void )
{
	if( connectionMan_ )
	{
		delete connectionMan_;
		connectionMan_ = 0;
	}
}


void AbstractEnvironmentHandle::connect( AbstractDatabaseHandle* )
{
}


void AbstractEnvironmentHandle::disconnect( AbstractDatabaseHandle* )
{
}


AbstractErrorManager::AbstractErrorManager( void )
{
}


AbstractErrorManager::~AbstractErrorManager( void )
{
}


AbstractLogger::AbstractLogger( const CqlString& initialDir )
	: file_(),
	  logFileOpen_( false )
{
	CqlString loglevel;
	Clib::getEnvironmentVariableValue( loglevel, "CQL_LOG_LEVEL", "" );
	if( loglevel.length() > 1 )
			tracelevel_ = static_cast<enum TraceLevel>(atoi(loglevel.text()));

	CqlString s;

	if( initialDir.length() )
	{
		s = initialDir;
		s += "/";
	}

	s += CQL_LOG_FILE_NAME;
	file_.openOrCreate( s );
	logFileOpen_ = CQL_YES;
}


AbstractLogger::~AbstractLogger( void )
{
}


//
//  This is a limited function used to log things.  It is not a complete
//  implementation of printf, and uses some "%" things that printf does
//  not recognize.  It doesn't find %%, nor anything between % and the
//  specification
//

class LogPrintfArgument : virtual public CqlConstants
{

public :

		enum ArgumentType
		{
				UNKNOWN,
				BOOLEAN,
				COLUMN_TYPE,
				POINTER,
				SIGNED_LONG,
				TEXT,
				UNSIGNED_LONG,
				LOGPRINTF_VALUE
		};

private :

		ArgumentType argType;
		pNC text;
		CqlColumnTypes type;
		UL ul;
		UL valueLength;
		L sl;
		void* pointer;

public :

		LogPrintfArgument( void )
				: argType( UNKNOWN ),
					text( ((pNC)0) ),
					type( CQL_COLUMN_UNDEFINED_TYPE ),
					ul( 0 ),
					valueLength( 0 ),
					sl( 0 ),
					pointer( ((void*)0) )
				{
				}

		~LogPrintfArgument( void ) { }

		ArgumentType ArgType( void ) { return argType; }
		L Sl( void ) { return sl; }
		void* Pointer( void ) { return pointer; }
		void SetArgumentType( ArgumentType t ) { argType = t; }
		void SetPointer( void* p ) { pointer = p; }
		void SetSl( L l ) { sl = l; }
		void SetText( pNC t ) { text = t; }
		void SetType( CqlColumnTypes t ) { type = t; }
		void SetUl( UL u ) { ul = u; }
		void SetValueLength( UL l ) { valueLength = l; }
		pNC Text( void ) { return text; }
		CqlColumnTypes Type( void ) { return type; }
		UL Ul( void ) { return ul; }
		UL ValueLength( void ) { return valueLength; }
};

typedef LogPrintfArgument *pLogPrintfArgument;

void AbstractLogger::logPrintf(AbstractLogger::TraceLevel tl, const char * const text, ... )
{
	if( static_cast<int>(tl) > tracelevel_ )
		return;

	va_list variableArgs;
	pLogPrintfArgument arg, *args;
	UNI numberOfVarArgs, loop, argno, bufLength, loop2;
	pNC p2, pointer, dumpPointer;
	NC buffer[ 256 ], buf2[ 100 ], valueBuffer[ 20 ];
	UC asciiBuffer[ 16 ];

	const char * p = text;
	for( numberOfVarArgs = 0; *p; p++ )
		if( *p == '%' )
			numberOfVarArgs++;

	va_start( variableArgs, text );
	args = new pLogPrintfArgument[ numberOfVarArgs ];
	if( !args )
		throw MemoryAllocationException( __FILE__, __LINE__ );

	for( argno = 0; argno < numberOfVarArgs; argno++ )
	{
		args[ argno ] = new LogPrintfArgument;
		if( !args[ argno ] )
			throw MemoryAllocationException( __FILE__, __LINE__ );
	}

	for( argno= 0, p = text; argno < numberOfVarArgs; p++ )
	{
		if( *p == '%' )
		{
			p++;
			switch( *p )
			{
			case 'b' :
				args[ argno ]->SetArgumentType( LogPrintfArgument::BOOLEAN );
				break;

			case 'd' :
				args[ argno ]->SetArgumentType( LogPrintfArgument::SIGNED_LONG );
				break;

			case 's' :
				args[ argno ]->SetArgumentType( LogPrintfArgument::TEXT );
				break;

			case 't' :
				args[ argno ]->SetArgumentType( LogPrintfArgument::COLUMN_TYPE );
				break;

			case 'u' :
				args[ argno ]->SetArgumentType( LogPrintfArgument::UNSIGNED_LONG );
				break;

			case 'v' :
				args[ argno ]->SetArgumentType( LogPrintfArgument::LOGPRINTF_VALUE );
				break;

			case 'x' :
				args[ argno ]->SetArgumentType( LogPrintfArgument::POINTER );
				break;
			}
			argno++;
		}
	}

	for( loop = 0; loop < numberOfVarArgs; loop++ )
	{
		switch( args[ loop ]->ArgType() )
		{
		case LogPrintfArgument::BOOLEAN :
			args[ loop ]->SetSl( va_arg( variableArgs, L ) );
			break;

		case LogPrintfArgument::COLUMN_TYPE :
			args[ loop ]->SetType( static_cast< CqlColumnType >( va_arg( variableArgs, NI ) ) );
			break;

		case LogPrintfArgument::POINTER :
			args[ loop ]->SetPointer( va_arg( variableArgs, void* ) );
			break;

		case LogPrintfArgument::SIGNED_LONG :
			args[ loop ]->SetSl( va_arg( variableArgs, L ) );
			break;

		case LogPrintfArgument::TEXT :
			args[ loop ]->SetText( va_arg( variableArgs, pNC ) );
			break;

		case LogPrintfArgument::UNKNOWN :
			break;

		case LogPrintfArgument::UNSIGNED_LONG :
			args[ loop ]->SetUl( va_arg( variableArgs, UL ) );
			break;

		case LogPrintfArgument::LOGPRINTF_VALUE :
			args[ loop ]->SetText( va_arg( variableArgs, pNC ) );
			args[ loop ]->SetValueLength( va_arg( variableArgs, UL ) );
			break;
		}
	}

	va_end( variableArgs );

	memset( buffer, 0, sizeof( buffer ) );
	char *lp;
	if( text != 0 && numberOfVarArgs > 0 )
	{
		for( lp = const_cast<char*>(text), p2 = buffer, argno = 0, arg = args[ argno ]; *lp; lp++ )
		{
			if( *lp != '%' )
				*p2++ = *lp;
			else
			{
				arg = args[ argno ];

				if( buffer[ 0 ] )
				{
					file_ << buffer;
					memset( buffer, 0, sizeof( buffer ) );
					p2 = buffer;
				}

				//
				//  p is pointing to '%'.  Advance to argument descriptor.
				lp++;

				switch( *lp )
				{
				case 'b' :
					if( arg->Sl() != 0 )
						file_ <<  "TRUE";
					else
						file_ << "FALSE";
					break;

				case 'd' :
					file_ << arg->Sl();
					break;

				case 's' :
					file_ << arg->Text();
					break;

				case 't' :
					//  this is a special case for the CqlColumnType enumeration
					switch( arg->Type().typeType() )
					{
					case CQL_COLUMN_UNDEFINED_TYPE :
						file_ << "UNDEFINED_TYPE";
						break;

					case CQL_CHAR :
						file_ << "CHAR";
						break;

					case CQL_VARCHAR :
						file_ << "VARCHAR";
						break;

					case CQL_DECIMAL :
						file_ << "DECIMAL";
						break;

					case CQL_SMALLINT :
						file_ << "SMALLINT";
						break;

					case CQL_INTEGER :
						file_ << "INTEGER";
						break;

					case CQL_REAL :
						file_ << "REAL";
						break;

					case CQL_FLOAT :
						file_ << "FLOAT";
						break;

					case CQL_LONGVARCHAR :
						file_ << "LONGVARCHAR";
						break;

					case CQL_BIT :
						file_ << "BIT";
						break;

					case CQL_TINYINT :
						file_ << "TINYINT";
						break;

					case CQL_BIGINT :
						file_ << "BIGINT";
						break;

					case CQL_BINARY :
						file_ << "BINARY";
						break;

					case CQL_VARBINARY :
						file_ << "VARBINARY";
						break;

					case CQL_LONGVARBINARY :
						file_ << "LONGVARBINARY";
						break;

					case CQL_DATE :
						file_ << "DATE";
						break;

					case CQL_TIME :
						file_ << "TIME";
						break;

					case CQL_TIMESTAMP :
						file_ << "TIMESTAMP";
						break;

					case CQL_CHARUC :
						file_ << "CHARUC";
						break;
					}
					break;

				case 'u' :
					file_ << arg->Ul();
					break;

				case 'v' :
					file_ << "\n";
					for( loop = loop2 = 0, dumpPointer = arg->Text();
						 loop < arg->ValueLength();
						 loop++, dumpPointer++ )
					{
						asciiBuffer[ loop2++ ] = *dumpPointer;
						sprintf( valueBuffer, "%02x", *dumpPointer );
						bufLength = strlen( valueBuffer );
						if( bufLength > 2 )
							pointer = valueBuffer + ( bufLength - 2 );
						else
							pointer = valueBuffer;
						pointer[ 2 ] = 0;
						file_ << pointer;

						if( ( ( loop + 1 ) % 16 ) == 0 )
						{
							file_ << "    ";
							buf2[ 1 ] = 0;
							for( loop2 = 0; loop2 < 16; loop2++ )
							{
								if( asciiBuffer[ loop2 ] < ' ' || asciiBuffer[ loop2 ] > 127 )
									file_ << ".";
								else
								{
									buf2[ 0 ] = asciiBuffer[ loop2 ];
									file_ << buf2;
								}

								if( ( ( loop2 + 1 ) % 8 ) == 0 )
									file_ << "  ";
							}
							loop2 = 0;
							file_ << "\n";
						}
						else if( ( ( loop + 1 ) % 8 ) == 0 )
							file_ << "  ";
					}
					file_ << "\n";
					break;

				case 'x' :
					sprintf( buf2, "%lx", ((UL)arg->Pointer()) );
					file_ << buf2;
					break;
				}

				argno++;
			}
		}
	}

	if( buffer[ 0 ] )
		file_ << buffer;

	//  true means block recursive logging call
	file_.flush( true );

	if( numberOfVarArgs > 0 )
	{
		for( argno = 0; argno < numberOfVarArgs; argno++ )
			delete args[ argno ];

		delete [] args;
	}
}


AbstractMessage::AbstractMessage( void )
  : commandObjects_(),
	commandData_(),
	data_( ((pUC)0) ),
	replyObjects_(),
	replyData_(),
	initFailed_( CQL_NO )
{
}


AbstractMessage::~AbstractMessage( void )
{
	commandObjects_.destroy();
	commandData_.destroy();
	replyObjects_.destroy();
	replyData_.destroy();

	if( data_ )
	{
		delete [] data_;
		data_ = ((pUC)0);
	}
}


NI AbstractMessage::readMessage( AbstractDatabaseHandle& dbHandle, pAbstractMessage *newMessage, Connection &connection )
{
	UNI messLength, lenRead;
	US us;
	MessageIdentifier messId;

	lenRead = connection.read( ((void*)&messLength), sizeof( messLength ) );
	if( lenRead == 0 )
	{
		*newMessage = ((pAbstractMessage)0);
		return CQL_SUCCESS;
	}
	else if( lenRead != sizeof( messLength ) )
		return CQL_FAILURE;

	lenRead = connection.read( ((void*)&us), sizeof( us ) );
	if( lenRead != sizeof( us ) )
		return dbHandle.returnError( CQL_SOCKET_ERROR, __FILE__, __LINE__ );
	messId = ((MessageIdentifier)us);

	if( csFunctionLogging )
	{
		*hAEnv << "Incoming function " ;

		switch( messId )
		{
		case AddColumn :
			*hAEnv << "AddColumn";
			break;

		case AddIndexMember :
			*hAEnv << "AddIndexMember";
			break;

		case AddRow :
			*hAEnv << "AddRow";
			break;

		case AddSegment :
			*hAEnv << "AddSegment";
			break;

		case BeginCreate :
			*hAEnv << "BeginCreate";
			break;

		case BeginIsamOperation :
			*hAEnv << "BeginIsamOperation";
			break;

		case BeginKey :
			*hAEnv << "BeginKey";
			break;

		case BeginRowOperation :
			*hAEnv << "BeginRowOperation";
			break;

		case BeginTransaction :
			*hAEnv << "BeginTransaction";
			break;

		case CheckPropagationFlags :
			*hAEnv << "CheckPropagationFlags";
			break;

		case Close :
			*hAEnv << "Close";
			break;

		case Columns :
			*hAEnv << "Columns";
			break;

		case CommitTransaction :
			*hAEnv << "CommitTransaction";
			break;

		case CurrentPosition :
			*hAEnv << "CurrentPosition";
			break;

		case DeleteCurrentRecord :
			*hAEnv << "DeleteCurrentRecord";
			break;

		case DeleteIndexMember :
			*hAEnv << "DeleteIndexMember";
			break;

		case DeleteRow :
			*hAEnv << "DeleteRow";
			break;

		case DestroyIndexIndex :
			*hAEnv << "DestroyIndexIndex";
			break;

		case DestroyIsamIndex :
			*hAEnv << "DestroyIsamIndex";
			break;

		case DisconnectMessageId :
			*hAEnv << "IsamDisconnect";
			break;

		case EndCreate :
			*hAEnv << "EndCreate";
			break;

		case EndKey :
			*hAEnv << "EndKey";
			break;

		case EstablishPosition :
			*hAEnv << "EstablishPosition";
			break;

		case FileExists :
			*hAEnv << "FileExists";
			break;

		case FileOpen :
			*hAEnv << "FileOpen";
			break;

		case FindEqual :
			*hAEnv << "FindEqual";
			break;

		case FindFirstPartialKeyMatch :
			*hAEnv << "FindFirstPartialKeyMatch";
			break;

		case FindGreater :
			*hAEnv << "FindGreater";
			break;

		case FindGreaterOrEqual :
			*hAEnv << "FindGreaterOrEqual";
			break;

		case FindLess :
			*hAEnv << "FindLess";
			break;

		case FindLessOrEqual :
			*hAEnv << "FindLessOrEqual";
			break;

		case FindNextPartialKeyMatch :
			*hAEnv << "FindNextPartialKeyMatch";
			break;

		case FirstRow :
			*hAEnv << "FirstRow";
			break;

		case FlushDataToRecord :
			*hAEnv << "FlushDataToRecord";
			break;

		case GetColumnInfo :
			*hAEnv << "GetColumnInfo";
			break;

		case GetColumnLength :
			*hAEnv << "GetColumnLength";
			break;

		case GetColumnValue :
			*hAEnv << "GetColumnValue";
			break;

		case GetColumnValueCurrentSetting :
			*hAEnv << "GetColumnValueCurrentSetting";
			break;

		case LastRow :
			*hAEnv << "LastRow";
			break;

		case NextRow :
			*hAEnv << "NextRow";
			break;

		case NumberOfEntriesEqualToKey :
			*hAEnv << "NumberOfEntriesEqualToKey";
			break;

		case NumberOfEntriesGreaterOrEqualToKey :
			*hAEnv << "NumberOfEntriesGreaterOrEqualToKey";
			break;

		case NumberOfEntriesGreaterThanKey :
			*hAEnv << "NumberOfEntriesGreaterThanKey";
			break;

		case NumberOfEntriesLessOrEqualToKey :
			*hAEnv << "NumberOfEntriesLessOrEqualToKey";
			break;

		case NumberOfEntriesLessThanKey :
			*hAEnv << "NumberOfEntriesLessThanKey";
			break;

		case Open :
			*hAEnv << "Open";
			break;

		case PurgeTransactionInformationForIsamFile :
			*hAEnv << "PurgeTransactionInformationForIsamFile";
			break;

		case PreviousRow :
			*hAEnv << "PreviousRow";
			break;

		case RollbackTransaction :
			*hAEnv << "RollbackTransaction";
			break;

		case SetColumn :
			*hAEnv << "SetColumn";
			break;

		case SetDataFetched :
			*hAEnv << "SetDataFetched";
			break;

		case StopServer :
			*hAEnv << "StopServer";
			break;

		case UpdateRow :
			*hAEnv << "UpdateRow";
			break;
		}

		*hAEnv << "\n";
	}

	(*newMessage) = createObject( messId );
	//  exception
	return (*newMessage)->completeRead( dbHandle, connection, ((US)messLength) );
}


NI AbstractMessage::completeRead( AbstractDatabaseHandle& dbHandle, Connection& connection, US messLength )
{
	pAbstractObject obj;
	pUC buf;
	UNI lenRead;

	messageLength_ = messLength;

	if( messageLength_ )
	{
		data_ = new UC[ messageLength_ ];
		if( !data_ )
			return CQL_FAILURE;

		lenRead = connection.read( ((void*)data_), messageLength_ );
		if( lenRead != messageLength_ )
			return dbHandle.returnError( CQL_SOCKET_ERROR, __FILE__, __LINE__ );

		buf = data_;

		for( obj = commandObjects_.first(); obj; obj = commandObjects_.next() )
			if( obj->getObject( &buf ) == CQL_FAILURE )
				return CQL_FAILURE;

		for( obj = commandData_.first(); obj; obj = commandData_.next() )
			if( obj->getObject( &buf ) == CQL_FAILURE )
				return CQL_FAILURE;
	}

	return CQL_SUCCESS;
}


NI AbstractMessage::writeMessage( AbstractDatabaseHandle&, Connection &connection )
{
	pAbstractObject obj;
	pUC buf, bigBuffer;
	UL bigLength;

	messageLength_ = 0;

	for( obj = replyObjects_.first(); obj; obj = replyObjects_.next() )
		messageLength_ += obj->messageLength();

	for( obj = replyData_.first(); obj; obj = replyData_.next() )
		messageLength_ += obj->messageLength();

	if( data_ )
		delete [] data_;

	data_ = new UC[ messageLength_ ];
	if( !data_ )
		return CQL_FAILURE;

	buf = data_;

	for( obj = replyObjects_.first(); obj; obj = replyObjects_.next() )
	{
		if( obj->putObject( &buf ) == CQL_FAILURE )
		{
			delete [] data_;
			data_ = ((pUC)0);
			return CQL_FAILURE;
		}
	}

	for( obj = replyData_.first(); obj; obj = replyData_.next() )
	{
		if( obj->putObject( &buf ) == CQL_FAILURE )
		{
			delete [] data_;
			data_ = ((pUC)0);
			return CQL_FAILURE;
		}
	}

	bigLength = messageLength_ + sizeof( messageLength_ );
	bigBuffer = new UC[ ((UNI)bigLength) ];
	if( !bigBuffer )
	{
		delete [] data_;
		data_ = ((pUC)0);
		return CQL_FAILURE;
	}
	buf = bigBuffer;
	memcpy( buf, &messageLength_, sizeof( messageLength_ ) );
	buf += sizeof( messageLength_ );
	memcpy( buf, data_, messageLength_ );
	delete [] data_;
	data_ = ((pUC)0);

	try
	{
		connection.write( ((void*)bigBuffer), static_cast< UNI >( bigLength ) );
	}
	catch( CqlException& ex )
	{
		//  catching so we can clean up bigBuffer
		delete [] bigBuffer;
		throw ex;
	}

	delete [] bigBuffer;
	return CQL_SUCCESS;
}


AbstractSegmentDescriptor::AbstractSegmentDescriptor( void ) : SegmentTypes(), column_( 0 )
{
}


AbstractSegmentDescriptor::AbstractSegmentDescriptor( const US sno, pAbstractColumnDescriptor col, const SegmentTypes& stype )
	: SegmentTypes( stype ),
	  segmentNumber_( sno ),
	  column_( col )
{
}


AbstractSegmentDescriptor::AbstractSegmentDescriptor( const US sno, const SegmentTypes& stype )
	: SegmentTypes( stype ),
	  segmentNumber_( sno ),
	  column_( 0 )
{
}


AbstractSegmentDescriptor::~AbstractSegmentDescriptor( void )
{
}


AbstractSystemConfigurationManager::AbstractSystemConfigurationManager( void )
{
}


AbstractSystemConfigurationManager::~AbstractSystemConfigurationManager( void )
{
}


AbstractTable::AbstractTable( AbstractDatabaseHandle& adh )
	: hAdb_( adh ),
	  columns_(),
	  cond_(),
	  handle_( ((UL)0) ),
	  currentKey_( ((pAccessor)0) ),
	  numberOfKeys_( 0 )
{
}


AbstractTable::~AbstractTable( void )
{
	columns_.destroy();
	cond_.destroy();
}


void AbstractTable::resetConditions( void )
{
	cond_.destroy();
}


void AbstractTable::bindColumnAV( US _columnNumber, AbstractValue& value, bool /*forUpdate*/, bool freeable )
{
	switch( value.columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		break;

	case CQL_CHAR :
	case CQL_CHARUC :
		{
			CharValue& cval = dynamic_cast< CharValue& >( value );
			bindColumn( _columnNumber, const_cast< CqlString& >( cval.value() ), cval.nullflag(), true );
		}
		break;

	case CQL_VARCHAR :
		{
			VarcharValue& vval = dynamic_cast< VarcharValue& >( value );
			bindColumn( _columnNumber, vval.rBuffer(), vval.rLength(), vval.nullflag(), true, freeable );
		}
		break;

	case CQL_DECIMAL :
		{
			DecimalValue& dval = dynamic_cast< DecimalValue& >( value );
			bindColumn( _columnNumber, dval, dval.nullflag(), true );
		}
		break;

	case CQL_SMALLINT :
		{
			SmallintValue& sval = dynamic_cast< SmallintValue& >( value );
			bindColumn( _columnNumber, sval.rPvalue(), sval.nullflag(), true );
		}
		break;

	case CQL_INTEGER :
		{
			IntegerValue& ival = dynamic_cast< IntegerValue& >( value );
			bindColumn( _columnNumber, ival.rPvalue(), ival.nullflag(), true );
		}
		break;

	case CQL_REAL :
		{
			RealValue& rval = dynamic_cast< RealValue& >( value );
			bindColumn( _columnNumber, rval.rPvalue(), rval.nullflag(), true );
		}
		break;

	case CQL_FLOAT :
		{
			FloatValue& fval = dynamic_cast< FloatValue& >( value );
			bindColumn( _columnNumber, fval.rPvalue(), fval.nullflag(), true );
		}
		break;

	case CQL_LONGVARCHAR :
		{
			LongvarcharValue& lval = dynamic_cast< LongvarcharValue& >( value );
			bindColumn( _columnNumber, lval.rBuffer(), lval.rLength(), lval.nullflag(), true, freeable );
		}
		break;

	case CQL_BIT :
		{
			BitValue& bval = dynamic_cast< BitValue& >( value );
			bindColumn( _columnNumber, bval.rPvalue(), bval.nullflag(), true );
		}
		break;

	case CQL_TINYINT :
		{
			TinyintValue& tval = dynamic_cast< TinyintValue& >( value );
			bindColumn( _columnNumber, tval.rPvalue(), tval.nullflag(), true );
		}
		break;

	case CQL_BIGINT :
		{
			BigintValue& bval = dynamic_cast< BigintValue& >( value );
			bindColumn( _columnNumber, bval, bval.nullflag(), true );
		}
		break;

	case CQL_BINARY :
		{
			BinaryValue& bval = dynamic_cast< BinaryValue& >( value );
			bindColumn( _columnNumber, bval.rBuffer(), bval.rLength(), bval.nullflag(), true, freeable );
		}
		break;

	case CQL_VARBINARY :
		{
			VarbinaryValue& vval = dynamic_cast< VarbinaryValue& >( value );
			bindColumn( _columnNumber, vval.rBuffer(), vval.rLength(), vval.nullflag(), true, freeable );
		}
		break;

	case CQL_LONGVARBINARY :
		{
			LongvarbinaryValue& lval = dynamic_cast< LongvarbinaryValue& >( value );
			bindColumn( _columnNumber, lval.rBuffer(), lval.rLength(), lval.nullflag(), true, freeable );
		}
		break;

	case CQL_DATE :
		{
			DateValue& dval = dynamic_cast< DateValue& >( value );
			bindColumn( _columnNumber, dval, dval.nullflag(), true );
		}
		break;

	case CQL_TIME :
		{
			TimeValue& tval = dynamic_cast< TimeValue& >( value );
			bindColumn( _columnNumber, tval, tval.nullflag(), true );
		}
		break;

	case CQL_TIMESTAMP :
		{
			TimestampValue& tval = dynamic_cast< TimestampValue& >( value );
			bindColumn( _columnNumber, tval, tval.nullflag(), true );
		}
		break;
	}
}


ConditionPredicate *AbstractTable::setConditionAV( US _columnNumber, const AbstractValue& avalue, ConditionalOperators op, bool freeable )
{
	AbstractValue& value = const_cast< AbstractValue& >( avalue );

	switch( value.columnType().typeType() )
	{
	case CQL_COLUMN_UNDEFINED_TYPE :
		break;

	case CQL_CHAR :
		{
			CharValue& cval = dynamic_cast< CharValue& >( value );
			return setCondition( _columnNumber, cval.value(), cval.nullflag(), op );
		}

	case CQL_VARCHAR :
		{
			VarcharValue& vval = dynamic_cast< VarcharValue& >( value );
			return setCondition( _columnNumber,
								 vval.rBuffer(),
								 vval.rLength(),
								 vval.nullflag(),
								 op,
								 freeable );
		}

	case CQL_DECIMAL :
		{
			DecimalValue& dval = dynamic_cast< DecimalValue& >( value );
			return setCondition( _columnNumber, dval, dval.nullflag(), op );
		}

	case CQL_SMALLINT :
		{
			SmallintValue& sval = dynamic_cast< SmallintValue& >( value );
			return setCondition( _columnNumber, sval.pvalue(), sval.nullflag(), op );
		}

	case CQL_INTEGER :
		{
			IntegerValue& ival = dynamic_cast< IntegerValue& >( value );
			return setCondition( _columnNumber, ival.pvalue(), ival.nullflag(), op );
		}

	case CQL_REAL :
		{
			RealValue& rval = dynamic_cast< RealValue& >( value );
			return setCondition( _columnNumber, rval.pvalue(), rval.nullflag(), op );
		}

	case CQL_FLOAT :
		{
			FloatValue& fval = dynamic_cast< FloatValue& >( value );
			return setCondition( _columnNumber, fval.pvalue(), fval.nullflag(), op );
		}

	case CQL_LONGVARCHAR :
		{
			LongvarcharValue& lval = dynamic_cast< LongvarcharValue& >( value );
			return setCondition( _columnNumber,
								 lval.rBuffer(),
								 lval.rLength(),
								 lval.nullflag(),
								 op,
								 freeable );
		}

	case CQL_BIT :
		{
			BitValue& bval = dynamic_cast< BitValue& >( value );
			return setCondition( _columnNumber, bval.rPvalue(), bval.nullflag(), op );
		}

	case CQL_TINYINT :
		{
			TinyintValue& tval = dynamic_cast< TinyintValue& >( value );
			return setCondition( _columnNumber, tval.rPvalue(), tval.nullflag(), op );
		}

	case CQL_BIGINT :
		{
			BigintValue& bval = dynamic_cast< BigintValue& >( value );
			return setCondition( _columnNumber, bval, bval.nullflag(), op );
		}

	case CQL_BINARY :
		{
			BinaryValue& bval = dynamic_cast< BinaryValue& >( value );
			return setCondition( _columnNumber,
								 bval.rBuffer(),
								 bval.rLength(),
								 bval.nullflag(),
								 op,
								 freeable );
		}

	case CQL_VARBINARY :
		{
			VarbinaryValue& vval = dynamic_cast< VarbinaryValue& >( value );
			return setCondition( _columnNumber,
								 vval.rBuffer(),
								 vval.rLength(),
								 vval.nullflag(),
								 op,
								 freeable );
		}

	case CQL_LONGVARBINARY :
		{
			LongvarbinaryValue& lval = dynamic_cast< LongvarbinaryValue& >( value );
			return setCondition( _columnNumber,
								 lval.rBuffer(),
								 lval.rLength(),
								 lval.nullflag(),
								 op,
								 freeable );
		}

	case CQL_DATE :
		{
			DateValue& dval = dynamic_cast< DateValue& >( value );
			return setCondition( _columnNumber, dval, dval.nullflag(), op );
		}

	case CQL_TIME :
		{
			TimeValue& tval = dynamic_cast< TimeValue& >( value );
			return setCondition( _columnNumber, tval, tval.nullflag(), op );
		}

	case CQL_TIMESTAMP :
		{
			TimestampValue& tval = dynamic_cast< TimestampValue& >( value );
			return setCondition( _columnNumber, tval, tval.nullflag(), op );
		}

	case CQL_CHARUC :
		{
			CharUCValue& cval = dynamic_cast< CharUCValue& >( value );
			return setCondition( _columnNumber, cval.value(), cval.nullflag(), op );
		}
	}

	throw InternalErrorException( __FILE__, __LINE__ );
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return 0;  //  stupid compiler
#endif
}


void AbstractValue::absoluteValue( void )
{
	//  this is the default method called if not redefined for type.  Throws exception
	throw IllegalOperationException( __FILE__, __LINE__ );
}


void AbstractValue::expand( UL )
{
	//  default method called for fixed length types
	throw IllegalOperationException( __FILE__, __LINE__ );
}


void AbstractValue::releaseMemory( void )
{
	//  Default method for types that don't have memory to release
}


//  For types not able to be displayed as a string
const CqlString AbstractValue::asString( bool ) const
{
	throw IllegalOperationException( __FILE__, __LINE__ );

	//  for stupid compilers
#if defined( _MSC_VER ) && _MSC_VER != 1200
	return CqlString();
#endif
}


void AbstractValue::columnType( CqlColumnTypes& t )
{
	typeLength( t.typeLength() );
	typeType( t.typeType() );
	initialize();
}


//  Default method for classes which don't need to allocate a buffer
void AbstractValue::initialize( void )
{
}


AbstractValue& AbstractValue::operator = ( const AbstractValue& )
{
	return *this;
}


Accessor::Accessor( const AccessorTypes atype, const US _keyNumber )
	: AccessorListElement(),
	  AccessorTypes( atype ),
	  keyNumber_( _keyNumber ),
	  numberOfSegments_( 0 ),
	  segments_()
{
}


Accessor::~Accessor( void )
{
}


Accessor& Accessor::operator = ( Accessor& other )
{
	keyNumber_ = other.keyNumber_;
	numberOfSegments_ = other.numberOfSegments_;

	AbstractSegmentDescriptor *asd;
	for( asd = segments_.first(); asd; asd = segments_.next() )
	{
		AbstractSegmentDescriptor *newAsd = AbstractSegmentDescriptor::createObject( asd->segmentNumber(), asd->segmentType() );
		*newAsd = *asd;
		segments_.add( newAsd );
	}

	return *this;
}
