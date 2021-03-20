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


template< class T >
ConcreteColumnDescriptor< T >::ConcreteColumnDescriptor( void )
: ColumnDescriptor()
{
}


template< class T >
ConcreteColumnDescriptor< T >::ConcreteColumnDescriptor( US _columnNumber, bool _descending )
: ColumnDescriptor( _columnNumber, _descending )
{
}


template< class T >
ConcreteColumnDescriptor< T >::~ConcreteColumnDescriptor( void )
{
}


template< class T >
void ConcreteColumnDescriptor< T >::clearNullflag( void )
{
	value_.clearNullflag();
}


template< class T >
bool ConcreteColumnDescriptor< T >::isNull( void )
{
	if( value_.nullflag() )
		return true;

	return false;
}


template< class T >
void ConcreteColumnDescriptor< T >::setNullflag( void )
{
	value_.setNullflag();
}


template< class T >
CqlConstants::CompareResult ConcreteColumnDescriptor< T >::compare( pUC& key1, pUC& key2, bool _descending )
{
	T val1( value().avalue() ), val2( value().avalue() );
	val1 << key1;
	val2 << key2;

	if( val1.nullflag() || val2.nullflag() )
	{
		if( val1.nullflag() && !val2.nullflag() )
			return THIS_LESS_THAN_OTHER;
		else if( !val1.nullflag() && val2.nullflag() )
			return THIS_GREATER_THAN_OTHER;
		else
			return THIS_EQUAL_TO_OTHER;
	}
	else if( val1 < val2 )
	{
		if( _descending )
			return THIS_GREATER_THAN_OTHER;
		else
			return THIS_LESS_THAN_OTHER;
	}
	else if( val1 > val2 )
	{
		if( _descending )
			return THIS_LESS_THAN_OTHER;
		else
			return THIS_GREATER_THAN_OTHER;
	}
	else
		return THIS_EQUAL_TO_OTHER;
}


template< class T >
UL ConcreteColumnDescriptor< T >::copyLength( void )
{
	if( value_.nullflag() )
		return 0;

	return value_.length();
}


template< class T >
bool ConcreteColumnDescriptor< T >::operator == ( BoundColumn *_bc )
{
	return value_ == _bc;
}


template< class T >
bool ConcreteColumnDescriptor< T >::operator != ( BoundColumn *_bc )
{
	if( value_ == _bc )
		return false;
	else
		return true;
}


template< class T >
bool ConcreteColumnDescriptor< T >::operator > ( BoundColumn *_bc )
{
	return value_ > _bc;
}


template< class T >
bool ConcreteColumnDescriptor< T >::operator >= ( BoundColumn *_bc )
{
	return value_ >= _bc;
}


template< class T >
bool ConcreteColumnDescriptor< T >::operator < ( BoundColumn *_bc )
{
	return value_ < _bc;
}


template< class T >
bool ConcreteColumnDescriptor< T >::operator <= ( BoundColumn *_bc )
{
	return value_ <= _bc;
}


template< class T >
void ConcreteColumnDescriptor< T >::operator << ( BoundColumn *_bc )
{
	value_ << _bc;
}


template< class T >
void ConcreteColumnDescriptor< T >::operator >> ( BoundColumn *_bc )
{
	value_ >> _bc;
}


template< class T >
void ConcreteColumnDescriptor< T >::operator << ( pUC& buf )
{
	value_ << buf;
}


template< class T >
void ConcreteColumnDescriptor< T >::operator >> ( pUC& buf )
{
	value_ >> buf;
}


template< class T >
void ConcreteColumnDescriptor< T >::operator << ( BinaryValue& bv )
{
	value_ << bv;
}


template< class T >
void ConcreteColumnDescriptor< T >::operator >> ( BinaryValue& bv )
{
	value_ >> bv;
}


template< class T >
void ConcreteColumnDescriptor< T >::operator << ( TempBuffer& tb )
{
	value_ << tb;
}


template< class T >
void ConcreteColumnDescriptor< T >::operator >> ( TempBuffer& tb )
{
	value_ >> tb;
}
