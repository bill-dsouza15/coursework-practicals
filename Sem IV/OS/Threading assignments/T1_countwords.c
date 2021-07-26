#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

int vowels=0;
int words=0;
int consonents=0;

char message[50];

void * count_vowels(void *);
void * count_words(void *);

int main() {
	pthread_t t1,t2;
	printf("\n Enter the string:");
	fgets(message,sizeof(message),stdin);
	printf("\n message: ");	
	puts(message);

	// Creating thread1 & thread2
	pthread_create(&t1,NULL,&count_words,(void *)message);
	pthread_create(&t2,NULL,&count_vowels,(void *)message);
		
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);


	printf("The No of words in the string are: %d\n",words);
	printf("The No of vowles in the string are: %d\n",vowels);
	printf("The No of consonents in the string are: %d\n",consonents);

	printf("Thank You..\n");

	return 0;
}

void * count_words(void *ptr) 	{
	char *msg;
	msg=(char *)ptr;
	printf("\n Prinitng message in thread1: ");
	puts(ptr);

	while(*msg != '\0')	{
		if (*msg == '\n' || *msg ==' ' || *msg == '\t') 
			words++;
		*msg++;
	}
	pthread_exit(0);
}

void * count_vowels(void *ptr) 	{
	char *m;
	m=(char *)ptr;
	printf("\n Prinitng message in thread2: ");
	puts(ptr);

	while(*m != '\0')	{
		if( (*m>=65 && *m <=90) || (*m>=97 && *m <=122) )	{
			if (*m=='a' || *m=='e' || *m=='i' || *m=='o' || *m=='u' || *m=='A' || *m=='E' || *m=='I' || *m=='O' || *m=='U' ) 
			vowels++;
		else
			consonents++;
		}
	*m++;		
	}
	pthread_exit(0);
}
