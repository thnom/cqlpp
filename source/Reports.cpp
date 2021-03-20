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


#include "CqlSqlInclude.h"


Report::Report( SqlHandle& sqlh )
	: OutputBuffer( sqlh.aHandle() ),
	  advance_( 0 ),
	  bodies(),
	  continuation(),
	  currentBody( 0 ),
	  currentField( 0 ),
	  date_(),
	  datePattern(),
	  dbsql_( sqlh ),
	  formFeed( 0 ),
	  header(),
	  indent( 0 ),
	  initialization(),
	  lineBuffer(),
	  outputLength( 0 ),
	  pause( 0 ),
	  rowsPerPage( 0 ),
	  skipTest( 0 ),
	  subtotal(),
	  subtotalTest( 0 ),
	  termination(),
	  title(),
	  ttitle(),
	  blockCalled( false ),
	  lines( false ),
	  ready( false ),
	  virgin( true )
{
}


Report::~Report( void )
{
}


Report& Report::operator = ( const Report& other )
{
	advance_ = other.advance_;
	bodies = other.bodies;
	continuation = other.continuation;
	date_ = other.date_;
	currentBody = other.currentBody;
	currentField = other.currentField;
	datePattern = other.datePattern;
	formFeed = other.formFeed;
	header = other.header;
	indent = other.indent;
	initialization = other.initialization;
	lineBuffer = other.lineBuffer;
	outputLength = other.outputLength;
	pause = other.pause;
	rowsPerPage = other.rowsPerPage;
	skipTest = other.skipTest;
	subtotal = other.subtotal;
	subtotalTest = other.subtotalTest;
	termination= other.termination;
	title = other.title;
	ttitle = other.ttitle;
	userParameter = other.userParameter;
	blockCalled = other.blockCalled;
	lines = other.lines;
	ready = other.ready;
	virgin = other.virgin;
	return *this;
}


NI Report::Initialize( SqlHandle *_dbsql )
{
	pReportWindow repWindow;

	outputLength = 0;
	if( !virgin )
		return CQL_SUCCESS;
	virgin = false;

	header.initialize();
	subtotal.initialize();
	continuation.initialize();

	for( repWindow = bodies.first(); repWindow; repWindow = bodies.next() )
		repWindow->initialize();
	bodies.first();

	for( repWindow = termination.first(); repWindow; repWindow = termination.next() )
		repWindow->initialize();

	if( rowsPerPage == 0 )
		rowsPerPage = CQL_DEFAULT_ROWS_PER_PAGE;

	if( indent == 0 )
		indent = CQL_DEFAULT_INDENT;

	if( OutputBuffer::initialize() == CQL_FAILURE )
		return _dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );

	ready = true;
	return CQL_SUCCESS;
}


NI Report::Process( SqlHandle *_dbsql )
{
	CqlString strIndent;

	if( indent )
	{
		strIndent.setString( indent );
		strIndent.fill( ' ' );
	}

	if( virgin && Initialize( _dbsql ) == CQL_FAILURE )
		return CQL_FAILURE;

	blockCalled = false;
	*this << initialization;
	lines = true;
	return CQL_SUCCESS;
}


NI Report::Run( SqlHandle *_dbsql )
{
	NI headerFlag = CQL_NO, skip;
	pReportWindow repWindow;

	lineBuffer.reset();

	if( lines && Process( _dbsql ) == CQL_FAILURE )
		return CQL_FAILURE;

	*this << "\n";
	GenerateTopOfPage();

	generateWindow( header, CQL_YES );

	for( ;; )
	{
		if( skipTest == ((UserReportFunction)0) || (*skipTest)( this ) == CQL_SUCCESS )
			generateWindow( *bodies.current() );

		if( currentRow() > rowsPerPage )
		{
			generateWindow( continuation );

			//
			//  is there a partial line to write?
			//
			if( lineBuffer.length() )
			{
				*this << lineBuffer;
				lineBuffer.reset();
			}

			if( pause )
				( *pause )( this );
			else if( formFeed )
				( *formFeed )( this );

			headerFlag = CQL_YES;
		}

		if( ((*advance_)( userParameter )) == CQL_FAILURE )
		{
			//
			//  end of report
			//
			if( headerFlag == CQL_YES )
				skip = CQL_YES;
			else
				skip = CQL_NO;

			if( subtotalTest )
			{
				generateWindow( subtotal );
				skip = CQL_NO;
			}

			if( termination.size() )
			{
				for( repWindow = termination.first(); repWindow; repWindow = termination.next() )
					generateWindow( *repWindow );

				skip = CQL_NO;
			}

			if( skip == CQL_NO )
			{
				if( pause )
					( *pause )( this );
				else if( formFeed )
					( *formFeed )( this );
			}

			break;
		}

		if( headerFlag )
		{

			GenerateTopOfPage();
			generateWindow( header );
			headerFlag = CQL_NO;
		}

		if( subtotalTest && ( *subtotalTest )( this ) == CQL_SUCCESS )
			generateWindow( subtotal );
	}

	return CQL_SUCCESS;
}


void Report::generateWindow( ReportWindow& win, NI doubleSpace )
{
	pReportField repField;
	UNI targetColumn;

	for( repField = win.fields().first(); repField; repField = win.fields().next() )
	{
		if( !skipTest || ( *skipTest )( this ) == CQL_FAILURE )
		{
			targetColumn = repField->ColumnNumber() + indent;
			horizontalCatchup( targetColumn );

			repField->generateOutput();
			*this << repField->Output();
		}
	}

	*this << "\n";

	if( doubleSpace == CQL_YES )
		*this << "\n";
}


void Report::GenerateTopOfPage( void )
{
	CqlString tbuf;

	date_.encode( tbuf );

	*this << tbuf;
	*this << ttitle;
	*this << title;

	if( tbuf.length() || ttitle.length() || title.length() )
		*this << "\n\n";
}


void Report::horizontalCatchup( UNI targetColumn )
{
	CqlString tstring;

	tstring = " ";

	while( currentColumn() < targetColumn )
		*this << tstring;
}


NI Report::Cleanup( void )
{
	return CQL_SUCCESS;
}


ReportField::ReportField( void )
	: ReportFieldListElement(),
	  col( ((pColumn)0) ),
	  columnNumber( 0 ),
	  cqlTemplate(),
	  output(),
	  pattern(),
	  type( CQL_COLUMN_UNDEFINED_TYPE ),
	  variableLength( 0 ),
	  initialized( CQL_NO ),
	  justify( CQL_NO ),
	  noZero( CQL_NO ),
	  skip( CQL_NO ),
	  wrap( CQL_NO )
{
}


ReportField::~ReportField( void )
{
}


NI ReportField::Assign( SqlHandle *_dbsql, ReportField& other )
{
	if( other.col )
	{
		col = new Column( *_dbsql );
		if( !col )
			return _dbsql->returnError( ALLOCATION, __FILE__, __LINE__ );
		*col = *other.col;
	}
	else
		col = ((pColumn)0);

	columnNumber = other.columnNumber;

	cqlTemplate = other.cqlTemplate;
	output = other.output;
	pattern = other.pattern;
	type = other.type;
	variableLength = other.variableLength;
	initialized = other.initialized;
	justify = other.justify;
	noZero = other.noZero;
	skip = other.skip;
	wrap = other.wrap;

	return CQL_SUCCESS;
}


void ReportField::generateOutput( void )
{
	if( col )
	{
		if( col->ReportValue()->nullflag() )
			output = "?";
		else
			col->encode( output );
	}
}


ReportWindow::ReportWindow( void )
	: ReportWindowListElement(),
	  currentField_( 0 ),
	  fields_(),
	  numberOfFields_( 0 ),
	  ready_( false ),
	  virgin_( true )
{
}


ReportWindow::~ReportWindow( void )
{
}


ReportWindow& ReportWindow::operator = ( const ReportWindow& other )
{
	currentField_ = other.currentField_;
	fields_ = other.fields_;
	numberOfFields_ = other.numberOfFields_;
	ready_ = other.ready_;
	virgin_ = other.virgin_;
	return *this;
}


void ReportWindow::initialize( void )
{
	ready_ = false;
	virgin_ = true;
	currentField_ = 0;
}
