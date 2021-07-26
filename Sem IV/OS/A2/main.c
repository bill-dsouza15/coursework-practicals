#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void descending(int *a,int n)
{
	int temp;
	for(int i=0;i<n;i++)
    {
    	for(int j=1;j<n;j++)
        {
        	if(a[j]>a[j-1])
        	{
        		temp = a[j];
        		a[j] = a[j-1];
        		a[j-1] = temp;
        	}
        }
    }
    printf("\nThe sorted descending array is: ");
	for(int i=0;i<n;i++)
	{
	 	printf("%d\t",a[i]);
	}
	printf("\n");
}

int main(void)
{
    pid_t childPID;
   	int n;
   	int *a;
   	printf("Enter the number of elements = ");
   	scanf("%d",&n);
   	a = (int*) malloc (n * sizeof(int));
   	printf("Enter the array: ");
	for(int i=0;i<n;i++)
	{
	 	scanf("%d",&a[i]);
	}
	
	
	///////////////////////////////////////////////////////
	
	char *args[n+2];
	
	char k[sizeof(int)];   
    sprintf(k, "%d", n);
    args[0] = k;
    
    
    char b[n][sizeof(int)];
	for (int i=0; i < n; i++)
    {  
        sprintf(b[i], "%d", a[i]);
        args[i+1] = b[i];
    }   
    args[n+1] = NULL;
    
    ///////////////////////////////////////////////////////
    
	childPID = fork();
    if(childPID >= 0) 			//fork was successful
    {
        if(childPID == 0) 		//child process
        {
        	printf("\nThis is CHILD process. PId = %d,PPID = %d\n",getpid(),getppid());
            execv("asc",args);
        }
	    else  					//Parent process
	    {
	    	sleep(5);
	    	printf("\n------------------------------------------------------------------\n");
	    	printf("\nThis is PARENT process. PId = %d,PPID = %d\n",getpid(),getppid());
	    	descending(a,n);
		}
	}
    else 						//fork failed
    {
        printf("\n Fork failed!\n");
        return 1;
    }
    return 0;
}
