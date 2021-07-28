%{
	#include<stdio.h>
    #include<stdlib.h>
	int yylex();
	int yyerror(char *s);
    char threeAddress(char op1,char op2,char op);
    void printAddress();

    struct table{
        char op1;
        char op2;
        char sign;
        char result;
    };

    int i = 0;
    char lop = 'A'-1;
%}

%union{
    char symbol;
}

%left '+' '-'
%left '/' '*'

%token <symbol> NUMBER LETTER
%type <symbol> exp

%%

Statement: LETTER '=' exp   			{ threeAddress((char)$1, (char)$3, '='); }

exp: exp '+' exp 						{ $$ = threeAddress((char)$1, (char)$3, '+'); }
 |	exp '-' exp 						{ $$ = threeAddress((char)$1, (char)$3, '-'); }
 |	exp '*' exp 						{ $$ = threeAddress((char)$1, (char)$3, '*'); }
 |	exp '/' exp 						{ $$ = threeAddress((char)$1, (char)$3, '/'); }
 |	exp '%' exp 						{ $$ = threeAddress((char)$1, (char)$3, '%'); }
 |	'('exp')' 							{ $$ = (char)$2; }
 |  '-' exp                             { $$ = threeAddress((char)$2,' ', '-'); }
 |  NUMBER                              { $$ = (char)$1; }
 |  LETTER                              { (char)$1; }
;
%%

struct table addressTable[10];

char threeAddress(char op1,char op2,char sign){
    lop++;
    if(sign == '='){
        addressTable[i].result = op1;
        addressTable[i].op1 = op2;
        addressTable[i].sign = ' ';
        addressTable[i].op2 = ' ';
    }
    else if(sign=='-' && op2==' '){
        addressTable[i].result = lop;
        addressTable[i].op1 = ' ';
        addressTable[i].sign = sign;
        addressTable[i].op2 = op1;
    }
    else{
        addressTable[i].result = lop;
        addressTable[i].op1 = op1;
        addressTable[i].sign = sign;
        addressTable[i].op2 = op2;
    }
    i++;
    return lop;
}

void printAddress(){
    int j = 0;
    while(j<i){
        printf("%c := %c %c %c\n",addressTable[j].result, addressTable[j].op1, addressTable[j].sign, addressTable[j].op2);
        j++;
    }
}

void main()
{
    printf("\nExpression : ");
    yyparse();
    printAddress();
}

int yyerror(char* s)
{
   printf("\nInvalid Arithmetic Expression!\n\n");
}
