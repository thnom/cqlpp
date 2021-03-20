//
//  Copyright (C) 1994-1999  Seth Kurtzberg
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


#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

void Clib::getCurrentTimestamp( short& year,
								unsigned short& month,
								unsigned short& day,
								unsigned short& hour,
								unsigned short& minute,
								unsigned short& second,
								unsigned long& fraction )
{
	struct tm *currentTime;
	struct timeval tv;

	gettimeofday( &tv, NULL );
	currentTime = localtime( (time_t *) &tv.tv_sec );
	if( !currentTime )
		throw ClibraryException( __FILE__, __LINE__ );

	year = static_cast< short >( currentTime->tm_year + 1900 );
	month = static_cast< unsigned short >( currentTime->tm_mon + 1 );
	day = static_cast< unsigned short >( currentTime->tm_mday );
	hour = static_cast< unsigned short >( currentTime->tm_hour );
	minute = static_cast< unsigned short >( currentTime->tm_min );
	second = static_cast< unsigned short >( currentTime->tm_sec );
	fraction = 0;
}


char Clib::convertCharToUppercase( char c )
{
	if( c >= 'a' && c <= 'z' )
		c -= 0x20;

	return c;
}


void Clib::getEnvironmentVariableValue( CqlString& result, const char *variableName, const char *defaultValue )
{
	char *value = getenv( variableName );
	if( !value )
		result = defaultValue;
	else
		result = value;
}


//************************************************************************
//**  This is basically the same as the old C library strncpy function, **
//**  except that it terminates the copied string, so that if source is **
//**  too long, the number of characters copied is one less and there   **
//**  is a terminating zero.                                            **
//************************************************************************

void Clib::cqlStrncpy( pNC dest, pNC source, UNI len )
{
	strncpy( dest, source, len );
	dest[ len - 1 ] = 0;
}

#if (__GNUC__ > 2 ) && defined(_GNU_SOURCE)

char *currentDirectory( void )
{
	return get_current_dir_name();
}

char *Clib::sCurrentDirectory( void )
{
	return get_current_dir_name();
}

#else

static char dnamebuf[1024];

char *currentDirectory( void )
{
	return getcwd( dnamebuf, sizeof( dnamebuf ) );
}

char *Clib::sCurrentDirectory( void )
{
	return getcwd( dnamebuf, sizeof( dnamebuf ) );
}

#endif

void Clib::cqlMemoryClear( void *v, unsigned int sz )
{
	memset( &v, 0, sz );
}

D clibArcCosine( D arg )
{
	return acos( arg );
}


D clibArcSin( D arg )
{
	return asin( arg );
}


D clibArcTangent( D arg )
{
	return atan( arg );
}


D clibCosine( D arg )
{
	return cos( arg );
}


D clibTangent( D arg )
{
	return tan( arg );
}


D clibExponential( D arg )
{
	return exp( arg );
}


D clibLogorithm( D arg )
{
	return log( arg );
}


D clibSin( D arg )
{
	return sin( arg );
}


D clibSquareRoot( D arg )
{
	return sqrt( arg );
}


void ClibConnection::acceptConnection( SOCKET_TYPE acceptSocket, SOCKET_ADDRESS_TYPE& socketAddress )
{
	size_t addrlen = sizeof( socketAddress );

	socketDescriptor_ = accept( acceptSocket, ((struct sockaddr *)&socketAddress), &addrlen );
	if( socketDescriptor_ == -1 )
		throw ClibraryException( __FILE__, __LINE__ );
}


void ClibConnection::initiateConnection( SOCKET_TYPE connectSocket, SOCKET_ADDRESS_TYPE& socketAddress )
{
	int addrlen = sizeof( socketAddress );


	socketDescriptor_ = connectSocket;
	if( connect( socketDescriptor_, ((struct sockaddr *)&socketAddress), addrlen ) == -1 )
		throw ClibraryException( __FILE__, __LINE__ );
}


void ClibConnection::releaseConnection( void )
{
	close( socketDescriptor_ );
	socketDescriptor_ = -1;
}


unsigned int ClibConnection::read( void *ptr, unsigned int len )
{
	int rc, errorCode;
	int amountReceived = 0, originalLength = len;
	char *localPtr = reinterpret_cast< char* >( ptr );

	do
	{
		rc = recv( socketDescriptor_, localPtr, static_cast< int >( len ), 0 );
		if( rc == -1 )
		{
			errorCode = errno;
			if( errorCode != EAGAIN )
				throw ClibraryException( __FILE__, __LINE__ );

			rc = 0;
		}

		amountReceived += rc;

		if( rc < static_cast< int >( len ) )
		{
			localPtr += rc;
			len -= rc;
		}
	} while( amountReceived < originalLength );

	return static_cast< unsigned int >( amountReceived );
}


void ClibConnection::write( void *ptr, const unsigned int len )
{
	int rc = send( socketDescriptor_, ((pNC)ptr), ((NI)len), 0 );
	if( rc == -1 )
		throw ClibraryException( __FILE__, __LINE__, errno );

	if( rc != static_cast< int >( len ) )
		throw ClibraryException( __FILE__, __LINE__ );
}


ClibConnectionManager::ClibConnectionManager( void )
{
	socketDescriptor_ = socket( PF_INET, SOCK_STREAM, 0 );
	if( socketDescriptor_ == -1 )
		throw CommunicationsException( __FILE__, __LINE__, errno );

	int bufsize = 1;
	if( setsockopt( socketDescriptor_, SOL_SOCKET, SO_REUSEADDR, &bufsize, sizeof( bufsize ) ) == -1 )
	{
		close( socketDescriptor_ );
		throw CommunicationsException( __FILE__, __LINE__, errno );
	}

	for( unsigned int loop = 0; loop < CQL_MAXIMUM_USERS + 1; loop++ )
		activeSockets_[ loop ] = -1;

	activeSockets_[ 0 ] = socketDescriptor_;
}


ClibConnectionManager::~ClibConnectionManager( void )
{
}


void ClibConnectionManager::registerConnection( SOCKET_TYPE socket )
{
	unsigned int loop;

	for( loop = 0; loop < CQL_MAXIMUM_USERS + 1; loop++ )
	{
		if( activeSockets_[ loop ] == -1 )
		{
			activeSockets_[ loop ] = socket;
			return;
		}
	}

	throw UserLimitExceededException( __FILE__, __LINE__ );
}


void ClibConnectionManager::removeConnection( SOCKET_TYPE socket )
{
	for( unsigned int loop = 0; loop < CQL_MAXIMUM_USERS + 1; loop++ )
	{
		if( activeSockets_[ loop ] == socket )
		{
			activeSockets_[ loop ] = -1;
			return;
		}
	}

	throw InternalErrorException( __FILE__, __LINE__ );
}


void ClibConnectionManager::findBusySockets( void )
{
	NI rc, loop2;
	UNI loop, loop3;
	fd_set readfds, writefds, exceptfds;
	struct timeval timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	FD_ZERO( &readfds );
	FD_ZERO( &writefds );
	FD_ZERO( &exceptfds );

	for( loop = 0; loop < CQL_MAXIMUM_USERS; loop++ )
	{
		busySockets_[ loop ] = -1;
		if( activeSockets_[ loop ] != -1 )
			FD_SET( activeSockets_[ loop ], &readfds );
	}

	rc = select( 256, &readfds, &writefds, &exceptfds, &timeout );
	if( rc == -1 )
		throw ClibraryException( __FILE__, __LINE__ );
	else if( !rc )
	{
		//  nothing waiting, busySockets all already set to -1, so return
		return;
	}

	for( loop = loop3 = 0, loop2 = 0; loop < CQL_MAXIMUM_USERS && loop2 < rc; loop++ )
		if( activeSockets_[ loop ] != -1 )
			if( FD_ISSET( activeSockets_[ loop ], &readfds ) )
				busySockets_[ loop3++ ] = activeSockets_[ loop ];
}


SOCKET_TYPE ClibConnectionManager::firstBusySocket( void )
{
	currentBusySocket_ = 0;
	return busySockets_[ currentBusySocket_++ ];
}


SOCKET_TYPE ClibConnectionManager::nextBusySocket( void )
{
	return busySockets_[ currentBusySocket_++ ];
}


void ClibConnectionManager::bind( CqlString& hostName, CqlString& serviceName )
{
	struct servent *serviceEntry;
	struct hostent *hostEntry;

	hostEntry = gethostbyname( hostName.text() );
	if( !hostEntry )
		throw ClibraryException( __FILE__, __LINE__ );

	serviceEntry = getservbyname( serviceName.text(), "tcp" );
	if( !serviceEntry )
		throw ClibraryException( __FILE__, __LINE__ );

	memset( reinterpret_cast< void* >( &socketAddress_ ), 0, sizeof( socketAddress_ ) );
	socketAddress_.sin_port = serviceEntry->s_port;
	socketAddress_.sin_family = AF_INET;
	socketAddress_.sin_addr.s_addr = *((long*)hostEntry->h_addr_list[0]);

	if( ::bind( socketDescriptor_, ((struct sockaddr *)&socketAddress_), sizeof( socketAddress_ ) ) == -1 )
		throw ClibraryException( __FILE__, __LINE__ );
}


void ClibConnectionManager::setPort( CqlString& hostName, CqlString& serviceName )
{
	struct servent *serviceEntry;
	struct hostent *hostEntry;

	hostEntry = gethostbyname( hostName.text() );
	if( !hostEntry )
		throw ClibraryException( __FILE__, __LINE__ );

	serviceEntry = getservbyname( serviceName.text(), "tcp" );
	if( !serviceEntry )
		throw ClibraryException( __FILE__, __LINE__ );

	memset( ((void*)&socketAddress_), 0, sizeof( sockaddr ) );
	socketAddress_.sin_port = serviceEntry->s_port;
	socketAddress_.sin_family = AF_INET;
	socketAddress_.sin_addr.s_addr = *((long*)hostEntry->h_addr_list[0]);
}


void ClibConnectionManager::listen( void )
{
	if( ::listen( socketDescriptor_, CQL_LISTEN_BACKLOG ) == -1 )
		throw ClibraryException( __FILE__, __LINE__ );
}


ClibFileManager::ClibFileManager( void )
{
	str_ = new std::fstream;
	if( !str_ )
		throw ClibFileSystemException( __FILE__, __LINE__ );
}


ClibFileManager::~ClibFileManager( void )
{
	//  This used to cause a problem.  If it does, see the cql81 version for workaround.
	if( str_ )
	{
		delete str_;
		str_ = 0;
	}
}


void ClibFileManager::read( void * const destination, const unsigned int amount )
{
	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::read\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::read\n", __FILE__, __LINE__ );
#endif

	int readLength = static_cast< int >( amount );
	str_->read( reinterpret_cast< char * >( destination ), readLength );
	if( !str_->bad() && str_->eof() && readLength != str_->gcount() )
	{
		throw EofException( __FILE__, __LINE__ );
	}
	else if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( CqlString("read"),
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


void ClibFileManager::write( const void * const source, unsigned int amount )
{
	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::write\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::write\n", __FILE__, __LINE__ );
#endif

	str_->write( reinterpret_cast<const char*>(source), amount );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( CqlString("write"),
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
	flush();
}


void ClibFileManager::checkError( const char * const fname, const int lineNumber )
{
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( "checkError",
											 fileName(),
											 fname,
											 lineNumber,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


ClibFileManager& ClibFileManager::operator << ( const char *text )
{
	*str_ << text;
	checkError( __FILE__, __LINE__ );
	return *this;
}


ClibFileManager& ClibFileManager::operator << ( const int val )
{
	*str_ << val;
	checkError( __FILE__, __LINE__ );
	return *this;
}


ClibFileManager& ClibFileManager::operator << ( const unsigned int val )
{
	*str_ << val;
	checkError( __FILE__, __LINE__ );
	return *this;
}


ClibFileManager& ClibFileManager::operator << ( const RECID rid )
{
	*str_ << rid;
	checkError( __FILE__, __LINE__ );
	return *this;
}


ClibFileManager& ClibFileManager::operator << ( const void *pointer )
{
	char buffer[ 100 ];
	sprintf( buffer, "%lx", reinterpret_cast< unsigned long >( pointer ) );
	*str_ << buffer;
	checkError( __FILE__, __LINE__ );
	return *this;
}


ClibFileManager& ClibFileManager::operator << ( const unsigned long val )
{
	*str_ << val;
	checkError( __FILE__, __LINE__ );
	return *this;
}


ClibFileManager& ClibFileManager::operator << ( const CqlString& val )
{
	*str_ << val.text();
	checkError( __FILE__, __LINE__ );
	return *this;
}


void ClibFileManager::open( const CqlString& name, RECID& endPosition )
{
	fileName( name );

	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::open\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::open\n", __FILE__, __LINE__ );
#endif

#ifdef __CQL_NEW_C_PLUS_PLUS_HEADERS
	std::ios_base::openmode mode = std::ios::in | std::ios::out | std::ios::ate;
#else
	int mode = std::ios::in | std::ios::out | std::ios::ate | std::ios::nocreate;
#endif

	str_->open( name.text(), mode );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( name,
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}

	endPosition = str_->tellp();

	str_->seekp( 0 );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( name,
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


void ClibFileManager::open( const CqlString& name, bool positionToBeginning = false )
{
	fileName( name );

	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::open\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::open\n", __FILE__, __LINE__ );
#endif

#ifdef __CQL_NEW_C_PLUS_PLUS_HEADERS
	std::ios_base::openmode mode = std::ios::in | std::ios::out;
#else
	int mode = std::ios::in | std::ios::out | std::ios::nocreate;
#endif

	if( positionToBeginning )
		mode |= std::ios::app;
	else
		mode |= std::ios::ate;

	str_->open( name.text(), mode );

	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( name,
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


void ClibFileManager::openForAppend( const CqlString& name, RECID& endPosition )
{
	fileName( name );

	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::openForAppend\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::openForAppend\n", __FILE__, __LINE__ );
#endif

	str_->open( name.text(), std::ios::in | std::ios::out | std::ios::ate );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( name,
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}

	endPosition = str_->tellp();
}


void ClibFileManager::openForAppend( const CqlString& name )
{
	fileName( name );

	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::openForAppend\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::openForAppend\n", __FILE__, __LINE__ );
#endif

	str_->open( name.text(), std::ios::in | std::ios::out | std::ios::ate );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( name,
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


void ClibFileManager::openOrCreate( const CqlString& name )
{
	fileName(name);

	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::openOrCreate\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::openOrCreate\n", __FILE__, __LINE__ );
#endif

	str_->open( name.text(), std::ios::in | std::ios::out | std::ios::ate );
	if( !str_->good() )
	{
		str_->clear();
		str_->open( name.text(), std::ios::out );
		if( !str_->good() )
		{
			bool good = str_->good();
			bool bad = str_->bad();
			bool fail = str_->fail();
			str_->clear();
			throw ClibFileSystemDetailException( name,
												 fileName(),
												 __FILE__,
												 __LINE__,
												 good,
												 bad,
												 fail,
												 errno );
		}
		str_->close();
		str_->open( name.text(), std::ios::in | std::ios::out );
		if( !str_->good() )
		{
			bool good = str_->good();
			bool bad = str_->bad();
			bool fail = str_->fail();
			str_->clear();
			throw ClibFileSystemDetailException( name,
												 fileName(),
												 __FILE__,
												 __LINE__,
												 good,
												 bad,
												 fail,
												 errno );
		}
	}
}


void ClibFileManager::close( void )
{
	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::close\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::close\n", __FILE__, __LINE__ );
#endif

	if( str_ )
	{
		str_->close();
		bool res = str_->good();
		delete str_;
		str_ = 0;
		if( !res )
			throw ClibFileSystemDetailException( "close",
												 fileName(),
												 __FILE__,
												 __LINE__,
												 str_->good(),
												 str_->bad(),
												 str_->fail(),
												 errno );
	}
}


void ClibFileManager::create( const CqlString& name )
{
	fileName(name);

	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::create\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::create\n", __FILE__, __LINE__ );
#endif

	str_->open( name.text(), std::ios::out );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( name,
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
	str_->close();

	str_->open( name.text(), std::ios::in | std::ios::out );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( name,
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


void ClibFileManager::deleteFile( const CqlString& name )
{
	unlink( name.text() );
}


// nolog is to stop flush from logging a call from the logger
void ClibFileManager::flush( bool nolog )
{
	if( !nolog && hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::flush\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::flush\n", __FILE__, __LINE__ );
#endif

	str_->sync();

	if( !nolog )
	{
		RECID vtellg = str_->tellg();
		RECID vtellp = str_->tellp();
		if( hAEnv && hAEnv->cppLibraryTrace() )
			hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::flush, tellg=%lx, tellp=%lx\n",
							  __FILE__,
							  __LINE__,
							  vtellg,
							  vtellp );
#ifdef __CQL_STARTUP_DEBUGGING
		else
			fprintf( stderr, "%s:%d ClibFileManager::flush, tellg=%lx, tellp=%lx\n",
					__FILE__,
					__LINE__,
					vtellg,
					vtellp );
#endif

		str_->seekp( 0, std::ios::end );
		vtellg = str_->tellg();

		if( hAEnv && hAEnv->cppLibraryTrace() )
			hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::flush, tellg relative to end, 0=%lx\n",
							  __FILE__,
							  __LINE__,
							  vtellg );
#ifdef __CQL_STARTUP_DEBUGGING
		else
			fprintf( stderr, "%s:%d ClibFileManager::flush, tellg relative to end, 0=%lx\n",
					__FILE__,
					__LINE__,
					vtellg );
#endif
	}

	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( CqlString("Flush"),
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


void ClibFileManager::outputSeek( const RECID location )
{
	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::outputSeek\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::outputSeek\n", __FILE__, __LINE__ );
#endif

	str_->seekp( location );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( CqlString("outputSeek"),
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


void ClibFileManager::seekToEnd( void )
{
	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::seekToEnd\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::seekToEnd\n", __FILE__, __LINE__ );
#endif

	str_->seekp( 0, std::ios::end );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( CqlString("seekToEnd"),
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


void ClibFileManager::inputSeek( const RECID location )
{
	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::inputSeek, location=%lx, good=%d, bad=%d, fail=%d, eof=%d\n",
						  __FILE__,
						  __LINE__,
						  location,
						  str_->good(),
						  str_->bad(),
						  str_->fail(),
						  str_->eof() );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::inputSeek, location=%lx, good=%d, bad=%d, fail=%d, eof=%d\n",
				__FILE__,
				__LINE__,
				location,
				str_->good(),
				str_->bad(),
				str_->fail(),
				str_->eof() );
#endif
	RECID vtellg = str_->tellg();
	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::inputSeek, tellg=%lx\n",
						  __FILE__,
						  __LINE__,
						  vtellg );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::inputSeek, tellg=%lx\n",
				 __FILE__,
				 __LINE__,
				 vtellg );
#endif

	str_->seekg( location, std::ios::beg );
	if( !str_->good() )
	{
		bool good = str_->good();
		bool bad = str_->bad();
		bool fail = str_->fail();
		str_->clear();
		throw ClibFileSystemDetailException( CqlString("inputSeek"),
											 fileName(),
											 __FILE__,
											 __LINE__,
											 good,
											 bad,
											 fail,
											 errno );
	}
}


void ClibFileManager::temporaryName( CqlString& nm )
{
	NC tname[ CQL_MAXIMUM_FILE_NAME_LENGTH ];

	if( !tmpnam( tname ) )
		throw ClibraryException( __FILE__, __LINE__ );

	nm = tname;
}


void ClibFileManager::rename( const CqlString& newName, const CqlString& oldName )
{
	::rename( oldName.text(), newName.text() );
}


ClibFileManager& ClibFileManager::operator = ( const ClibFileManager& other )
{
	//  Copy the fstream, don't duplicate it
	str_ = other.str_;
	return *this;
}


bool ClibFileManager::clibFileExists( const CqlString& name )
{
	if( hAEnv && hAEnv->cppLibraryTrace() )
		hAEnv->logPrintf(AbstractLogger::TRACEALL, "%s:%d ClibFileManager::clibFileExists\n", __FILE__, __LINE__ );
#ifdef __CQL_STARTUP_DEBUGGING
	else
		fprintf( stderr, "%s:%d ClibFileManager::clibFileExists\n", __FILE__, __LINE__ );
#endif

#ifdef __CQL_NEW_C_PLUS_PLUS_HEADERS
	std::ios_base::openmode mode = std::ios::in | std::ios::out | std::ios::ate;
#else
	int mode = std::ios::in | std::ios::out | std::ios::ate | std::ios::nocreate;
#endif

	str_->open( name.text(), mode );
	if( !str_->good() )
		return false;

	str_->close();
	return true;
}
