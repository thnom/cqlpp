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


#ifndef __CqlCommonInclude_h
#define __CqlCommonInclude_h


#define __CQL_LIBRARY

void environmentSpecificInitialization( void );

#include "ForwardReference.h"
#include "CqlMachine.h"
#include "CqlDefines.h"
#include "CqlOptions.h"
#include "CqlConstants.h"
#include "PredicateTypes.h"
#include "CqlString.h"
#include "CqlFixedLengthString.h"
#include "CqlStringWithPosition.h"
#include "ListElement.h"
#include "ListBase.h"
#include "List.h"
#include "StackList.h"
#include "CqlTableConstants.h"
#include "CqlException.h"
#include "Clib.h"
#include "ClibFileManager.h"
#include "ClibConnection.h"
#include "ClibConnectionManager.h"
#include "AbstractValue.h"
#include "AbstractType.h"
#include "InstructionConstants.h"
#include "FunctionConstants.h"
#include "SetComparisonConstants.h"
#include "TempBuffer.h"
#include "OutputBuffer.h"
#include "BoundColumn.h"
#include "AbstractColumnDescriptor.h"
#include "AbstractColumnDescriptorList.h"
#include "AbstractSegmentDescriptor.h"
#include "Accessor.h"
#include "Condition.h"
#include "AbstractTable.h"
#include "AbstractLogger.h"
#include "AbstractErrorManager.h"
#include "AbstractDatabaseHandle.h"
#include "AbstractSystemConfigurationManager.h"
#include "AbstractEnvironmentHandle.h"
#include "MemoryIndexConstants.h"
#include "MemoryIndexNode.h"
#include "MemoryIndex.h"
#include "ErrorManager.h"
#include "Logger.h"
#include "CqlCommonGlobal.h"
#include "UserConfigurationManager.h"
#include "SystemConfigurationManager.h"
#include "Connection.h"
#include "ConnectionManager.h"
#include "IdentifierConstants.h"
#include "AbstractObject.h"
#include "MessageIdentifiers.h"
#include "AbstractMessage.h"

#endif  //  __CqlCommonInclude_h
