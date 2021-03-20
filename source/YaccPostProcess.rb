#!/usr/local/bin/ruby

ifile = File.open( ARGV.shift )
ofile = File.open( ARGV.shift, "w" )

lines = <<END_OF_STRING

/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
END_OF_STRING

elines = Regexp.escape( lines )
reLines = Regexp.new( elines, Regexp::MULTILINE )

reYyError = /yyerror\s*\(/
reDefine = /\#\s*define\s+YYLEX\s+yylex\s*\(\)/
reUseAlloca = /\#\s*if\s*YYSTACK_USE_ALLOCA/
reYYMAXDEPTH = /\#if YYMAXDEPTH == 0/
reGnucMinor = /^\#if defined \(__GNUC_MINOR__\).*$/
reParseParam = /yyparse \(void \*YYPARSE_PARAM\)/
reIntLen = /int len;$/
contents = ifile.read
contents =~ reLines
con2 = "#{$`}int yyparse(SqlHandle *dbsql)#{$'}"

require "tempfile"
tf = Tempfile.new( "x" )
tempname = tf.path
tf.write( con2 )
tf.open
lines = tf.readlines
lines.each do |line|
	line = line.sub( reYyError, 'yyerror ( dbsql, ' )
	line = line.sub( reDefine, '' )
	line = line.sub( reUseAlloca, '#ifdef YYSTACK_USE_ALLOCA' )
	line = line.sub( reYYMAXDEPTH, "#ifndef YYMAXDEPTH\n#define YYMAXDEPTH 0\n#endif\n#if YYMAXDEPTH == 0" )
	line = line.sub( reGnucMinor, '#if 0' )
	line = line.sub( reParseParam, 'yyparse( SqlHandle *dbsql )' )
	line = line.sub( reIntLen, 'int localLen;' )
	ofile.write( line )
end
#printf( "before=\n%s\n\n", $` )
#printf( "match=\n%s\n\n", $& )
#printf( "after=\n%s\n\n", $' )

