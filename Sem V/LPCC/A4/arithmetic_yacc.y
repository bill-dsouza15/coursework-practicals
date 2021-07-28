%{
	#include<stdio.h>
    #include<stdlib.h>
	int yylex();
	int yyerror(char *s);
%}

%token num

%%

Statement: exp 							{ printf("\n= %d\n",$$); return 0; }

exp: exp '+' exp 						{ $$ = $1 + $3; }
 |	exp '-' exp 						{ $$ = $1 - $3; }
 |	exp '*' exp 						{ $$ = $1 * $3; }
 |	exp '/' exp 						{ $$ = $1 / $3; }
 |	exp '%' exp 						{ $$ = $1 % $3; }
 |	num 								{ $$ = $1; }
;
%%

void main()
{
    printf("\nExpression : ");
    yyparse();
}

int yyerror(char* s)
{
   printf("\nInvalid Arithmetic Expression!\n\n");
}
