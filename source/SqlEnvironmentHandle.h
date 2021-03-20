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


#ifndef __SqlEnvironmentHandle_h
#define __SqlEnvironmentHandle_h


class SqlEnvironmentHandle : public ErrorConstants
{
	AbstractEnvironmentHandle *aHandle_;
	NI currentAnonymousCursorNumber_;

	BFT initFailed : 1;
	BFT interactiveMode : 1;

public :

	SqlEnvironmentHandle( char* /*initial directory*/ );
	~SqlEnvironmentHandle( void );

	operator AbstractEnvironmentHandle&() { return *aHandle_; }

	void allocateBuffers( UL );
	NC ConvertCharToUppercase( NC );
	const CqlString& optionCurrentDirectory( void ) { return *aHandle_->optionCurrentDirectory(); }
	bool fileExists( const CqlString& /*file name*/ );
	CqlString *anonymousCursorName( void );
	NI InitFailed( void ) { return ((NI)initFailed); }
	NI InteractiveMode( void ) { return interactiveMode; }
	UNI MaxBufferPages( void );
	void SetInteractiveMode( void ) { interactiveMode = CQL_YES; }
	NI setSystemConfiguration( void );
};

typedef SqlEnvironmentHandle *pSqlEnvironmentHandle;


inline NC SqlEnvironmentHandle::ConvertCharToUppercase( NC ch )
{
	return aHandle_->convertCharToUppercase( ch );
}


inline bool SqlEnvironmentHandle::fileExists( const CqlString& name )
{
	return aHandle_->fileExists( name );
}


inline UNI SqlEnvironmentHandle::MaxBufferPages( void )
{
	return aHandle_->maxBufferPages();
}


#endif  //  __SqlEnvironmentHandle_h
