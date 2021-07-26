%{
#include<stdio.h>
int lines=0, words=0,sletters=0,cletters=0, num=0, splch=0,total=0;
%}


%%

\n 			{lines++; words++;}
[\t ' '] 	words++;
[A-Z] 		cletters++;
[a-z] 		sletters++;
[0-9] 		num++;
. 			splch++;

%%





void main(void)
{
	yyin= fopen("text.txt","r");
	yylex();
	total = sletters + cletters + num + splch;
	printf("This File contains ...");
	printf("\nLines = %d", lines);
	printf("\nWords = %d",words);
	printf("\nSmall letters = %d", sletters);
	printf("\nCapital letters = %d",cletters);
	printf("\nDigits = %d", num);
	printf("\nSpecial characters = %d",splch);
	printf("\nTotal characters = %d\n",total);
}
 
int yywrap()
{
return(1);
}
