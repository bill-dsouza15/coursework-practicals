%{
#include<stdio.h>
%}

%%
[\t ]+

The |
the |
A	|
a   |
An 	|
an					{ printf("%s - Article\n",yytext); }

Bill     | 
Ram	     |
Ishan    |
Aditya   | 
Purujeet |
Atharve 			{ printf("%s - Noun\n",yytext); }

is		   |
"has been" 			{ printf("%s - Auxillary Verb\n",yytext); }

ran		 |
walking  |
running	 |
writing	 |
swimming |
playing 			{ printf("%s - Main Verb\n",yytext); }

quickly |
slowly	|
easily	|
badly	|
closely				{ printf("%s - Adverb\n",yytext); }

book    |
ball	|
pen 				{ printf("%s - Object\n",yytext); }

and |
but |
or  |
for	|
nor |
yet |
so					{ printf("%s - Conjunction\n",yytext); }

he  |
she |
it 					{ printf("%s - Pronoun\n",yytext); }

with |
between |
at |
in 					{ printf("%s - Preposition\n",yytext); }

[\n]    			;

%%

int yywrap()
{
	return 1;
}
	
void main()
{
	yylex();
}
	
