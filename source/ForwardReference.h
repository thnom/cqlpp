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


#ifndef __ForwardReference_h
#define __ForwardReference_h


//****************************************************************************
//**  These declarations are for forward references.                        **
//****************************************************************************

class AbstractColumnDescriptor;
class AbstractDatabaseHandle;
class AbstractEnvironmentHandle;
class AbstractErrorManager;
class AbstractLogger;
class AbstractMessage;
class AbstractSegmentDescriptor;
class AbstractTable;
class AbstractValue;
class Accessor;
class BigintValue;
class BinaryValue;
class BoundColumn;
class BufferManager;
class CharValue;
class Clib;
class ClibFileManager;
class ColumnDescriptor;
class Condition;
class ConnectionManager;
class CqlBinary;
class CqlString;
class DatabaseHandle;
class DateValue;
class DecimalValue;
class EnvironmentHandle;
class ErrorManager;
class FileManager;
class FloatValue;
class Index;
class IndexKeyDescriptor;
class IndexSegmentDescriptor;
class IntegerValue;
class Logger;
class LongvarbinaryValue;
class LongvarcharValue;
class MemoryIndex;
class NodeElement;
class OpenFileManager;
class Parser;
class RealValue;
class SmallintValue;
class StringList;
class TempBuffer;
class TimeValue;
class TimestampValue;
class TinyintValue;
class TransactionPageIndexNode;
class TransactionStack;
class UserConfigurationManager;
class UserManager;
class VarbinaryValue;
class VarcharValue;


//  TempBuffer has a pointer to this object.
class SqlHandle;


#endif  //  __ForwardReference_h
