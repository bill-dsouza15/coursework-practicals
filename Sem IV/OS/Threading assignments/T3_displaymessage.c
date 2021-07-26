/*This program creates thread and each thread separate messgaes*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define limit 6
char *message[limit];
void *runner(void *param);

int main() {
	int i;
	pthread_t tid[limit];

	message[0] = "Hello from salman..message 0";
	message[1] = "Hello from sharukh..message 1";
	message[2] = "Hello from Amir..message 2";
	message[3] = "Hello from Amrish puri..message 3";
	message[4] = "Hello from pran..message 4";
	message[5] = "Hello from prem chopra..message 5";
	
	for(i=0;i<limit;i++)
		pthread_create(&tid[i], NULL, runner,(void *)message[i]);

	for(i=0;i<limit;i++)
		pthread_join(tid[i], NULL);

	printf(" Thnak You...\n");
	
return 0;
}

void *runner(void *param)  {
	printf("%s\n",(char *)param);
	pthread_exit(NULL);
}
