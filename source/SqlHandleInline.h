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


#ifndef __SqlHandleInline_h
#define __SqlHandleInline_h


inline void SqlHandle::beginTransaction( void )
{
	aHandle_->beginTransaction();
}


inline ErrorConstants::ErrorCodes SqlHandle::errorCode( void )
{
	return aHandle_->aErrorMan().errorCode();
}


inline CqlString& SqlHandle::errorFile( void )
{
	return aHandle_->aErrorMan().errorFile();
}


inline NI SqlHandle::errorLine( void )
{
	return aHandle_->aErrorMan().errorLine();
}


inline bool SqlHandle::fileExists( const CqlString& name )
{
	return dbSqlEnv->fileExists( name );
}


inline const char * const SqlHandle::getErrorText( ErrorCodes ec )
{
	return aHandle_->aErrorMan().errorText( ec );
}


inline const char * const SqlHandle::getSqlstate( ErrorCodes ec )
{
	return aHandle_->aErrorMan().sqlstate( ec );
}


inline TableIdList *SqlHandle::getTableIds( const CqlString& owner )
{
	return mainDict_->getTableIds( owner );
}


inline bool SqlHandle::interactiveMode( void )
{
	if( dbSqlEnv->InteractiveMode() )
		return true;
	else
		return false;
}


inline bool SqlHandle::noError( void )
{
	if( aHandle_->aErrorMan().noError() )
		return true;
	else
		return false;
}


inline AbstractTable *SqlHandle::openAbstractTable( const char * const name, TableType tt )
{
	return aHandle_->openAbstractTable( name, tt );
}


inline NI SqlHandle::osError( void )
{
	return aHandle_->aErrorMan().osError();
}


inline void SqlHandle::resetError( void )
{
	aHandle_->aErrorMan().resetError();
}


inline NI SqlHandle::returnError( ErrorCodes ec, const char * const fname, NI lineNo, NI osErr )
{
	return aHandle_->returnError( ec, fname, lineNo, osErr );
}


inline NI SqlHandle::returnNormal( ErrorCodes errCode, pNC fname, NI lineNo )
{
	return aHandle_->aErrorMan().returnNormal( errCode, fname, lineNo );
}


inline NI SqlHandle::returnNormalOrError( void )
{
	return aHandle_->aErrorMan().returnNormalOrError();
}


inline ColumnMetadataList *SqlHandle::getColumnMetadata( TableId * tid )
{
	return mainDict_->getColumnMetadata( tid );
}


#endif  //  __SqlHandleInline_h
