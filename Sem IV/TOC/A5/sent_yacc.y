%{
	#include<stdio.h>
	void yyerror(char *s);
	int yylex();    
%}

%token Article Subject Present Verb Adverb Object Conjunction Pronoun Preposition Num sAlpha cAlpha Sc Comma Terminator

%%

process: process start
	   | start
	   ;  	
	   
start:	sentence Terminator								{printf("Simple sentence\n\n");}
	 |	sentence Conjunction sentence Terminator		{printf("Compound sentence\n\n");}
	 |	error Terminator								{yyerrok;}
	 ;

sentence : Subject Present Verb Adverb
		 | Subject Present Verb Article Object
		 | Subject Present Verb Preposition Article Object
		 | Pronoun Present Verb Adverb
		 | Pronoun Present Verb Preposition Article Object
		 | Article Subject Present Verb Adverb
		 | Article Subject Present Verb Preposition Article Object  
		 ;
	  
%%

void yyerror(char *s)
{
	printf("yyerror : %s\n\n",s);
	return;
}

int main()
{
	yyparse();
	return 1;
}
