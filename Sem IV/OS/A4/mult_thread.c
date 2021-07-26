/* Matrix Multiplication using pthread in C
   This program creates "THREAD_NO" number of threads
   and divides the M loop into "THREAD_NO" parts.  */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*Here number of threads is 3 as my processor has only 2 cores (2-3 threads improves performance)
 which gives better threading results.
 Increasing this slightly beyond core count usually decreases performance*/
#define THREAD_NO 3													

//Only M must have value greater than THREAD_NO for better performance & M,N,K >= 1 (also time difference is noticeable at large values)
#define M 100
#define K 100
#define N 100

//define global variables for matrices. NOTE: INPUTS TO MATRICES ARE RANDOMIZED USING inbuilt rand() function
int A[M][K];
int B[K][N];
int C[M][N];
unsigned long long int sum = 0,count=0;
pthread_t tid[THREAD_NO]; 

//mutex lock to prevent data race (threads trying to modify shared data) and to enable synchronization
pthread_mutex_t lock;

//Threading Function
void* mult(void *arg)
{
	pthread_mutex_lock(&lock);

 	for(int i=((count) * M/THREAD_NO);i<((count+1) * M/THREAD_NO);i++)
  	{
  		for(int j=0;j<N;j++)
  		{
  			C[i][j] = 0;
  			for(int n = 0; n < K; n++)
	   		{
				C[i][j] += A[i][n] * B[n][j];							//Sum of product of row element of A and column element of B
	   		}
	   		sum+=C[i][j];
	   	}
	}
	count++;
	
	pthread_mutex_unlock(&lock);
	pthread_exit(&sum); 												//return the value calculated by thread to main thread for total sum
}

//Printing matrix C
void printC()														
{
	printf("\nThe matrix C is: \n");
	for(int i = 0; i < M; i++)
	{
    	for(int j = 0; j < N; j++)
    	{
        	printf("%d\t", C[i][j]);
      	}
      	printf("\n");
   	}
}


int main(int argc, char *argv[])
{     
   	unsigned long long int sum1;
   	clock_t start;
   	clock_t end;
   	
/*********************************************MATRIX CREATION*********************************************/
   	
	//Creating matrix A using rand() function
	printf("The matrix A is: \n"); 
	for(int i = 0; i < M; i++)
   	{
    	for(int j = 0; j < K; j++)
    	{
    		A[i][j] = (0+(int)(10.0*rand()/(RAND_MAX+0.0)));			//Generates random number between 0 to 10
    		printf("%d\t",A[i][j]);
    	}
    	printf("\n");
    }
    
    printf("\n");
    
    //Creating matrix B using rand() function
	printf("The matrix B is: \n"); 
	for(int i = 0; i < K; i++)
   	{
    	for(int j = 0; j < N; j++)
    	{
    		B[i][j] = (0+(int)(10.0*rand()/(RAND_MAX+0.0)));			//Generates random number between 0 to 10
    		printf("%d\t",B[i][j]);
    	}
    	printf("\n");
    }
    
    

/***********************************PARALLEL EXECUTION (WITH THREADING)***********************************/
	
	printf("\n/************************WITH THREADING************************/\n"); 
	sum1 = 0;
	start = clock();
   	for(int i = 0; i < THREAD_NO; i++)
   	{
    	pthread_create(&tid[i], NULL, &mult, NULL); 					//Creating THREAD_NO number of threads
	}
	end = clock() - start;
	
	for(int i = 0; i < THREAD_NO; i++)
   	{
   		int *rg[1];
    	pthread_join(tid[i], (void**)&rg[0]);						 	//wait for completion of each thread in main thread
    	int res = *rg[0];
    	sum1 = sum1 + res;												//Calculate total sum (is negative for large M,N,K since the total sum cannot be stored)
    }
  
	printC();
 	printf("\nSum is %d\n ", sum1/THREAD_NO);   
 	printf("\nTime taken (for parallel) = %f seconds\n",((double)end)/CLOCKS_PER_SEC); 
 	
 	
   	
/*********************************SEQUENTIAL EXECUTION (WITHOUT THREADING)********************************/
	
   	printf("\n/************************WITHOUT THREADING************************/\n"); 
   	sum1 = 0;
   	start = clock();
   	for(int i = 0; i < M; i++)
   	{
    	for(int j = 0; j < N; j++)
    	{
    		C[i][j] = 0;
        	for(int n = 0; n < K; n++)
		   	{
				C[i][j] += A[i][n] * B[n][j];							//Calculation of element of matrix C for corresponding i & j
		   	}
		   	sum1 += C[i][j];
	 	}
   	}
   	end = clock() - start;
   
	printC();
 	printf("\nSum is %d\n ", sum1);   
 	printf("\nTime taken (for sequential) = %f seconds\n",((double)end)/CLOCKS_PER_SEC); 
 	
}


