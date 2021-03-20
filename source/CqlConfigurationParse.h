//
//  Copyright (C) 1994-2003  Seth Kurtzberg
//
typedef union {
	char name[ 128 ];
	int number;
} YYSTYPE;
#define	BUFFER	258
#define	EQUALS	259
#define	CQL_FILE	260
#define	FILES	261
#define	HOST	262
#define	ID	263
#define	INTEGER	264
#define	ISAM	265
#define	LOG	266
#define	MACHINE	267
#define	MAX	268
#define	NAME	269
#define	NUMBER	270
#define	OF	271
#define	PAGE	272
#define	PAGES	273
#define	SERVICE	274
#define	CQL_SIZE	275
#define	SQL	276
#define	STRING	277
#define	USERS	278


extern YYSTYPE configlval;
