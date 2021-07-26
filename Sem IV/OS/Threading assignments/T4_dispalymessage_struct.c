/*This program creates thread and each thread print separate messgaes*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define limit 6

char *message[limit];
void *runner(void *param);

struct data{
	int total;
	char *m;
	long sum1;
	long mul1;
}str[limit];


int main(int argc,char *argv[]) {
	int i;
	pthread_t tid[limit];
	
	int number=atoi(argv[1]);

	message[0] = "Hello from salman..message 0";
	message[1] = "Hello from sharukh..message 1";
	message[2] = "Hello from Amir..message 2";
	message[3] = "Hello from Amrish puri..message 3";
	message[4] = "Hello from pran..message 4";
	message[5] = "Hello from prem chopra..message 5";
	

	for(i=0;i<limit;i++)  {
		str[i].total = number;
		str[i].m=message[i];
		str[i].sum1 = 0;
		str[i].mul1 = 1;
	}
	
	for(i=0;i<limit;i++)
		pthread_create(&tid[i], NULL, runner,(void *)&str[i]);

	for(i=0;i<limit;i++)
		pthread_join(tid[i], NULL);
	
	printf(" Thank You...\n");
	
return 0;
}

void *runner(void *param)  {
	struct data *newstr;
	int i,addition,multiplication;
	newstr=(struct data *)param;
	
	for (i=0;i<newstr->total;i++) {
		newstr->sum1 += i;
	}
	for (i=1;i<=newstr->total;i++) {
		newstr->mul1 *= i;
	}
	printf("Message:  %s\n",newstr->m);
	printf("Sum is:  %ld\n",newstr->sum1);
	printf("Multiplication is :  %ld\n",newstr->mul1);


	pthread_exit(NULL);
}
