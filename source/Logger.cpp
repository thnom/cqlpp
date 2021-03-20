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


Logger::Logger( const CqlString& initialDirectory )
	: AbstractEnvironmentHandle( initialDirectory )
{
}


Logger::~Logger( void )
{
}

AbstractLogger& Logger::operator << ( ErrorCodes ec )
{
	UNI err = ((UNI)ec);
	file() << err;
	return *this;
}


AbstractLogger& Logger::operator << ( const char * const str )
{
	file() << str;
	return *this;
}


AbstractLogger& Logger::operator << ( NI ni )
{
	file() << ni;
	return *this;
}


AbstractLogger& Logger::operator << ( UNI uni )
{
	file() << uni;
	return *this;
}


AbstractLogger& Logger::operator << ( RECID rid )
{
	file() << rid;
	return *this;
}


AbstractLogger& Logger::operator << ( void* ptr )
{
	file() << ptr;
	return *this;
}


AbstractLogger& Logger::operator << ( UL ul )
{
	file() << ul;
	return *this;
}


AbstractLogger& Logger::operator << ( const CqlString& str )
{
	file() << str.text();
	return *this;
}


AbstractLogger& Logger::operator << ( CqlException& cqlex )
{
	cqlex.output( *this );
	return *this;
}
