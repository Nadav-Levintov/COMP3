%{
/* Declarations section */
#include <stdio.h>
#include "output.hpp"
#include "parser.hpp"
#include "parser.tab.hpp"

	using namespace output;
	using namespace std;

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

%x str

%%

{linebreak}						;
{whitespace}					;
"void"							return VOID;
"int"							return INT;
"byte"							return BYTE;
"b"								return B;
"bool"							return BOOL;
"and"							return AND;
"or"							return OR;
"not"							return NOT;
"true"							return TRUE;
"false"							return FALSE;
"return"						return RETURN;
"if"							return IF;
"else"							return ELSE;
"while"							return WHILE;
"break"							return BREAK;
";"								return SC;
","								return COMMA;
"("								return LPAREN;
")"								return RPAREN;
"{"								return LBRACE;
"}"								return RBRACE;
"["								return LBRACK;
"]"								return RBRACK;
"="								return ASSIGN;
"=="|"!="|"<"|">"|"<="|">="		return RELOP;
"+"|"-"|"*"|"/"					return BINOP;
{letter}{digitletter}*			{
									yylval = new Node(yytext);
									return ID;
								}
"0"|[1-9][0-9]*					{
									yylval = new Node(atoi(yytext),yytext);
									return NUM;
}
\"								BEGIN(str);
<str>\"							BEGIN(INITIAL);return STRING;
<str>([^\n\r\"\\]|\\[rnt"\\])+  ;
"//"[^\r\n]*[\r|\n|\r\n]?		;
.								output::errorLex(yylineno); return 0;

%%
