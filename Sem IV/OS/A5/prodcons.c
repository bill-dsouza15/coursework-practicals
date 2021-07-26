#include<stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define TRUE 1											//Since C does not have default boolean true and false 
#define BUFFER_SIZE 5									//The maximum size of the buffer
#define PCDIV 1000000000								//The divisor for calculating random time for producer-consumer threads to sleep
#define MAINDIV 100000000								//The divisor for calculating random time for main thread to sleep 

pthread_mutex_t mutex;									//mutex lock for synchronising the access to global variables
sem_t full,empty;										//semaphores for signaling the threads

int buffer[BUFFER_SIZE];								//The buffer on which item is placed and from which item is consumed
int counter = 0;										//Counter to check number of items in buffer

// Insert item in buffer //
int insert_item(int item)
{
	if(counter < BUFFER_SIZE)
	{
		buffer[counter] = item;
		counter++;
		return 1;
	}
	else
	{
		return 0;
	}
}

// Remove item from buffer //
int remove_item()
{
	if(counter > 0)
	{
		counter--;
		return 1;
	}
	else
	{
		return 0;
	}
}

// Producer thread function //
void* producer(void* p)
{
	int tidp = *((int*)p);
	int item;
	int time;
	
	while(TRUE)
	{
		time = rand()/PCDIV;
		sleep(time);
		
		sem_wait(&empty);
		
		pthread_mutex_lock(&mutex);
		item = rand();
		if(insert_item(item))
		{
			printf("Producer %d - Item successfully produced \n",tidp);
		}
		else
		{
			printf("BUFFER IS FULL\n");
		}
		pthread_mutex_unlock(&mutex);
		
		sem_post(&full);
	}
}

// Consumer thread function //
void* consumer(void* c)
{
	int tidc = *((int*)c);
	int time;
	while(TRUE)
	{
		time = rand()/PCDIV;
		sleep(time);
		
		sem_wait(&full);
		
		pthread_mutex_lock(&mutex);
		if(remove_item())
		{
			printf("Consumer %d - Item successfully consumed\n",tidc);
		}
		else
		{
			printf("BUFFER IS EMPTY\n");
		}
		pthread_mutex_unlock(&mutex);
		
		sem_post(&empty);
	}
}

int main()
{
	//Initialize the semaphores & mutex locks//
	sem_init(&full,0,0);								 	
	sem_init(&empty,0,BUFFER_SIZE );
	pthread_mutex_init(&mutex,NULL);
	
	//Enter number of producers and consumers//
	int prod,cons;
	printf("Enter the number of producers : "); ;
	scanf("%d",&prod);
	printf("Enter the number of consumers : "); ;
	scanf("%d",&cons);
	
	//Creating producer-consumer threads//
	pthread_t tidp[prod],tidc[cons];
	int p[prod],c[cons];
	for(int i=0;i<prod;i++)
	{
		p[i] = i+1;
		pthread_create(&tidp[i],NULL,producer,(void**)&p[i]);
	}
	for(int i=0;i<cons;i++)
	{
		c[i] = i+1;
		pthread_create(&tidc[i],NULL,consumer,(void**)&c[i]);
	}
	
	//Make main thread sleep for random time// 
    int randsleep = rand()/MAINDIV;
    sleep(randsleep);
    
    //Destroy the locks//
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
   
	return 0;
}
	
