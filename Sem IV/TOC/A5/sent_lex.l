%{
#include "y.tab.h"
#include <stdio.h>
%}

%%
[\t ]+

The |
the |
A	|
a   |
An 	|
an				return Article;

Bill     | 
Ram	     |
Ishan    |
Aditya   | 
Purujeet |
Atharve 			return Subject;

is		   |
"has been" 			return Present;

walking  |
running	 |
writing	 |
swimming |
playing 			return Verb;

quickly |
slowly	|
easily	|
badly	|
closely				return Adverb;

book    |
ball	|
pen 				return Object;

and |
but |
or  |
for	|
nor |
yet |
so					return Conjunction;

he  |
she |
it 					return Pronoun;

with |
between |
at |
in 					return Preposition;

[a-z]				{ yylval = atoi(yytext); return sAlpha; }

[A-Z]				{ yylval = atoi(yytext); return cAlpha; }

[0-9]+				{ yylval = atoi(yytext); return Num; }

\,					return Comma;

[\n]    			return Terminator;

%%

int yywrap()
{
	return 1;
}
	
	
