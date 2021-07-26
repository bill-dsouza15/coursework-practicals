%{
FILE* yyin;
%}

DATATYPE "void"|"int"|"float"|"double"|"String"
SPECIFIER "public"|"private"|"protected"
KEYWORD "main"|"class"|"static"
CLASSN "System"
OBJN "in"|"out" 
MEMF "println"
DIGIT [0-9]
TEXT [A-Za-z]
IDENTIFIER {TEXT}({DIGIT}|{TEXT}|"_")*
QUOTE \"
STR {QUOTE}({IDENTIFIER}("."|"!"|"?")){QUOTE}
ARR ({IDENTIFIER}"[""]")

%%

[ \n\t]+ ;

{DATATYPE}		{printf("%s\t\t -> Datatype\n",yytext); fprintf(yyout,"Datatype\t\t\t   :: %s\n",yytext);}

{SPECIFIER}		{printf("%s\t\t -> Access specifier\n",yytext); fprintf(yyout,"Access specifier\t   :: %s\n",yytext);}

{KEYWORD} 		{printf("%s\t\t -> Keyword\n",yytext); fprintf(yyout,"Keyword \t\t\t   :: %s\n",yytext);}

{CLASSN}		{printf("%s\t\t -> Class name\n",yytext) ; fprintf(yyout,"Class name\t\t\t   :: %s\n",yytext);}

{OBJN}			{printf("%s\t\t -> Object name\n",yytext) ; fprintf(yyout,"Object name\t\t\t   :: %s\n",yytext);}

{MEMF} 			{printf("%s\t\t -> Member function\n",yytext) ; fprintf(yyout,"Member function\t\t   :: %s\n",yytext);}

{STR} 			{printf("%s\t -> String\n",yytext); fprintf(yyout,"String\t\t\t\t   :: %s\n",yytext);} 

{ARR} 			{printf("%s\t\t -> Array\n",yytext); fprintf(yyout,"Array\t\t\t\t   :: %s\n",yytext);} 

{IDENTIFIER} 	{printf("%s\t\t -> Identifier\n",yytext); fprintf(yyout,"Identifier\t\t\t   :: %s\n",yytext);} 

"("				{printf("%s\t\t -> Opening paranthesis\n",yytext) ; fprintf(yyout,"Opening paranthesis    :: %s\n",yytext);}

")"				{printf("%s\t\t -> Closing paranthesis\n",yytext) ; fprintf(yyout,"Closing paranthesis    :: %s\n",yytext);}

";"				{printf("%s\t\t -> Semicolon\n",yytext) ; fprintf(yyout,"Semicolon\t\t\t   :: %s\n",yytext);}

"{"				{printf("%s\t\t -> Opening block\n",yytext) ; fprintf(yyout,"Opening block\t\t   :: %s\n",yytext);}

"}"				{printf("%s\t\t -> Closing block\n",yytext) ; fprintf(yyout,"Closing block\t\t   :: %s\n",yytext);}

"."  			{printf("%s\t\t -> Membership operator\n",yytext) ; fprintf(yyout,"Membership operator\t   :: %s\n",yytext);}

%%

int yywrap()
{
	return 1;
}

void main()
{
	yyin = fopen("source.java","r");
	yyout = fopen("output.txt","w");
	yylex();
	yywrap();
}	
