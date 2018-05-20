%{
/* Declarations section */
#include <stdio.h>
#include "output.hpp"

typedef enum tokens_e
{
	VOID,
	INT,
	BYTE,
	B,
	BOOL,
	AND,
	OR,
	NOT,
	TRUE,
	FALSE,
	RETURN,
	IF,
	ELSE,
	WHILE,
	BREAK,
	SC,
	COMMA,
	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,
	LBRACK,
	RBRACK,
	ASSIGN,
	RELOP,
	BINOP,
	ID,
	NUM,
	STRING,
	EOF1
} tokens;

enum tokens showToken(our_tokens t);
void errorHandler();
void errorHandlerUnclosed();
void errorHandlerEscaped();

#define MAX_STR_CONST 1025

%}

%option yylineno
%option noyywrap

digit 			([0-9])
letter 			([a-zA-Z])
digitletter 	([a-zA-Z0-9])
whitespace 		([\t\n ])
cr				(\x0d)
lf				(\x0a)
linebreak		(\x0d\x0a|\x0d|\x0a)


%x str1
%x str2

%%

{linebreak}						;
{whitespace}					;
void							return VOID;
int								return INT;
byte							return BYTE;
b								return B;
bool							return BOOL;
and								return AND;
or								return OR;
not								return NOT;
true							return TRUE;
false							return FALSE;
return							return RETURN;
if								return IF;
else							return ELSE;
while							return WHILE;
break							return BREAK;
;								return SC;
,								return COMMA;
(								return LPAREN;
)								return RPAREN;
\{								return LBRACE;
\}								return RBRACE;
\[								return LBRACK;
\]								return RBRACK;
=								return ASSIGN;
==|!=|<|>|<=|>=					return RELOP;
+|-|*|/							return BINOP;
{letter}{digitletter}*			return ID;
0|[1-9][0-9]*					return NUM;
"([^\n\r\"\\]|\\[rnt"\\])+"		return STRING;
<<EOF>>							return EOF1;
.								errorLex(yylineno);

%%
