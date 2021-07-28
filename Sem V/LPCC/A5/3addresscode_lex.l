%{
	#include<stdio.h>
	#include "y.tab.h"
	extern char yyval;
%}

%%

[0-9]+			{ yylval.symbol = (char)(yytext[0]); return NUMBER; }
[a-z]+			{ yylval.symbol = (char)(yytext[0]); return LETTER; }
[\t] 			;
[\n] 			return 0;
. 			return yytext[0];

%%

int yywrap()
{
	return 1;
}
