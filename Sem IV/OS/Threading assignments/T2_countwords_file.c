#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

//Function Declaration
void * count_words(void *);
void * count_vowels(void *);
void * count_lines(void *);

// variables shared by all threads
int words=0;
int vowels=0;
int consonents=0;
int lines=0;

FILE *fp,*fp1,*fp2;
char path[50]="testfile"; //path of the file;
char datatoread[50];
char ch;

int main(){
	pthread_t t1,t2,t3;
	
	printf("\n ************ WELCOME *************** \n");
	printf("This is thread program with files..\n");
		
	//open a FILE in read mode
	fp=fopen(path,"r");
	fp1=fopen(path,"r");
	fp2=fopen(path,"r");

	//Check for file opening error	
	if( fp==NULL) {
		printf("\nERROR while opening File.\n");
		exit(1);
	}
	//Create a Thread
	pthread_create(&t1,NULL,&count_words,fp);
	pthread_create(&t2,NULL,&count_vowels,fp1);
	pthread_create(&t3,NULL,&count_lines,fp2);

	//Join the threads
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);

	//Print the Output
	printf("\nThe Number of Words: %d",words);
	printf("\nThe Number of vowels: %d",vowels);
	printf("\nThe Number of consonents: %d",consonents);
	printf("\nThe Number of Lines: %d",lines);
	
	//Closing the File
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	printf("\n Done. Thank You!!!\n");
	
return 0;
}

//Function to count words
void * count_words(void *fptr) {
	FILE *newptr; //define new variable as FILE datatype
	newptr=(FILE *)fptr; //Assigne file pointer
	
	ch = fgetc(newptr);
	while(ch!=EOF) {
		if( ch==' ' || ch=='\t' || ch=='\n')
			words++;	
		ch=fgetc(newptr);
	}
	pthread_exit(0);
}

//Function to count words
void * count_vowels(void *fptr1) {
	FILE *newptr1; //define new variable as FILE datatype
	newptr1=(FILE *)fptr1; //Assigne file pointer
	
	ch = fgetc(newptr1);
	while(ch!=EOF) {
		if( ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u' || ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U')
			vowels++;	
		else
			consonents++;
	ch=fgetc(newptr1);
	}
	pthread_exit(0);
}

//Function to count number of lines
void * count_lines(void *fptr2) {
	FILE *newptr2; //define new variable as FILE datatype
	newptr2=(FILE *)fptr2; //Assigne file pointer
	
	ch = fgetc(newptr2);
	while(ch!=EOF) {
		if( ch=='\n')
			lines++;	
		ch=fgetc(newptr2);
	}
	pthread_exit(0);
}

