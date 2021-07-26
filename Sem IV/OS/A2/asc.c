#include <stdio.h>
#include <stdlib.h>

void main (int argc,char *argv[])
{
	int temp,*ar;
	int n = atoi(argv[0]);
	ar = (int *) malloc (n * sizeof(int));
	
	for(int i=1;i<=atoi(argv[0]);i++)
	{
		ar[i] = atoi(argv[i]);
	}
	
	for(int i=1;i<=atoi(argv[0]);i++)
	{
		for(int j=1;j<=atoi(argv[0]);j++)
		{
			if(ar[j]<ar[j-1])
			{
				temp = ar[j];
				ar[j] = ar[j-1];
				ar[j-1] = temp;
			}
		}
	}
	printf("\nThe sorted ascending array is: ");
	for(int i = 1;i<=atoi(argv[0]);i++)
	{
	 	printf("%d\t",ar[i]);
	}
	printf("\n");
}
