%{
#include "y.tab.h"
#include <stdio.h>
%}

%%
[\t ]+

void |
int |
char |
float |
double |
String 				return Datatype;

[a-z]		   		{ return sAlpha; }

[A-Z]				{ return cAlpha; }

\;					return Sc;

[0-9]+				{ yylval = atoi(yytext); return Num; }

\,					return Comma;

\=					return Eq;

[\n]    			return Terminator;

%%

int yywrap()
{
	return 1;
}
	
	
