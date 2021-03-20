#!/usr/bin/python

import sys
import re
import os
import xreadlines

import misutils

if len(sys.argv) != 3 :
	sys.exit( 'command line error' )

infile = file( sys.argv[1], 'r' )
ofile = file( sys.argv[2], 'w' )

reStackUsed = re.compile( r'^\#if YY_STACK_USED$' );
reProto = re.compile( r'^static int yy_get_next_buffer YY_PROTO\(\( void \)\)' );
reGetNextDeclaration = re.compile( r'static int yy_get_next_buffer\(\)' )
reGetNext = re.compile( r'yy_get_next_buffer\(\)' )
reyyinput = re.compile( r'^static int yyinput\(\)$' )
reReturnYyinput = re.compile( r'return yyinput\(\);$' )
reunistd = re.compile( '^\#include \<unistd\.h\>$' )
reAlwaysInteractive = re.compile( r'\#if YY_ALWAYS_INTERACTIVE' )
reNeverInteractive = re.compile( r'\#if YY_NEVER_INTERACTIVE' )
reyymain = re.compile( r'\#if YY_MAIN' )

for li in xreadlines.xreadlines(infile) :
	li = misutils.stripcrlf( li )
	li = reStackUsed.sub( r'#ifdef YY_STACK_USED', li )
	li = reProto.sub( r'', li )
	li = reGetNextDeclaration.sub( r'static int yy_get_next_buffer( SqlHandle *dbsql )',
								   li );
	li = reGetNext.sub( r'yy_get_next_buffer( dbsql )',
						li )
	li = reyyinput.sub( r'static int yyinput( SqlHandle *dbsql )', li )
	li = reReturnYyinput.sub( r'return yyinput( dbsql );', li )
	li = reunistd.sub( r'#ifndef _MSC_VER' + '\n' + r'#include <unistd.h>'
					   + '\n' + r'#endif', li )
	li = reAlwaysInteractive.sub( r'#ifdef YY_ALWAYS_INTERACTIVE', li )
	li = reNeverInteractive.sub( r'#ifdef YY_NEVER_INTERACTIVE', li )
	li = reyymain.sub( r'#ifdef YY_MAIN', li )

	ofile.write( li + '\n' )
