#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 3

struct matrix
{
	int r;
	int c;
};

void *runner(void *);

int A[SIZE][SIZE],B[SIZE][SIZE],C[SIZE][SIZE];

struct matrix *data1,*data2;

int sum1 = 0;												/*While passing value from a thread to join function we cannot pass a local variable*/
int sum2 = 0;

int main() 
{
    int row,col,i,j,k;
	pthread_t tid;
	void *arg;

	//Loop to enter random numbers in Matrix A and B	
	for(row=0;row<SIZE;row++) 
	{
		for(col=0;col<SIZE;col++) 
		{
			A[row][col] = rand()%100 + 1;
			B[row][col] = rand()%100 + 2;
		}
	}
	
	//printing matrix A and B
	printf("Matrix A \n");
	for(row=0;row<SIZE;row++)
	{
		for(col=0;col<SIZE;col++) 
		{
			printf("%d\t",A[row][col]);
		}
		printf("\n");
	}
	
	printf("Matrix B\n");
	for(row=0;row<SIZE;row++) 
	{
		for(col=0;col<SIZE;col++) 
		{
			printf("%d\t",B[row][col]);
		}
		printf("\n");
	}
	
	//create threads and join in the loop
	for(i=0;i<SIZE;i++)  
	{
		for(j=0;j<SIZE;j++) 
		{
			data1 = (struct matrix *)malloc(sizeof(struct matrix));
			data1->r = i;
			data1->c = j;
			
			pthread_create(&tid,NULL,runner,data1);
			pthread_join(tid,&arg);	
		
			k= *((int *)arg);
			sum2 = sum2 + k;
			C[data1->r][data1->c] = k;
		}		
	}
	
	//Loop to print c	
	printf("\nMatrix c\n");
	for(row=0;row<SIZE;row++) 
	{
		for(col=0;col<SIZE;col++) 
		{
			printf("%d \t",C[row][col]);
		}
		printf("\n");
	}	 
}

void *runner(void *param) 
{
	sum1 = 0;
	data2 = (struct matrix*) param;
	int i;
	
	for(i=0;i<SIZE;i++) 
	{
		sum1 += A[data2->r][i] * B[i][data2->c];
	}
	
	printf("\nprinting sum of each thread: %d",sum1); 
	pthread_exit(&sum1);
}

