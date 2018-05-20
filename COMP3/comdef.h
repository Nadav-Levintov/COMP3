#ifndef COMDEF_H
#define COMDEF_H

typedef bool constAttribute;

typedef struct
{
	bool isConst;
	bool value;
} expAttribute;

typedef union
{
	constAttribute constVal;
	expAttribute exp;
} STYPE;

#define YYSTYPE STYPE	// Tell Bison to use STYPE as the stack type

#endif COMDEF_H