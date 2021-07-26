%{
	#include<stdio.h>
	void yyerror(char *s);
	int yylex();    
%}

%token Datatype Eq Num sAlpha cAlpha Sc Comma Terminator

%%

process: process start
	   | start
	   ;  	
	   
start:  Datatype Var Sc Terminator						{printf("Valid identifier\n\n");}
	 |	Datatype Terminator								{printf("Invalid identifier\n\n");}
	 |	Datatype Var Terminator							{printf("Invalid identifier\n\n");}
	 |	Datatype Sc Terminator							{printf("Invalid identifier\n\n");}
	 |	Datatype Ident Eq Terminator					{printf("Invalid identifier\n\n");}
	 ;


Var	: Ident Comma Var
	| Ident Eq Num Comma Var
	| Ident 	
	| Ident Eq Num 
	;

Ident : sAlpha Ident
	  | cAlpha Ident
	  |	sAlpha
	  | cAlpha
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
