#include <stdio.h>
#include <stdlib.h>

void gotoxy(int x,int y)   
{
	printf("%c[%d;%df",0x1B,y,x);
}

struct pr
{
	char pname[5];
	int arrt;
	int burt;
	int wtime;
	int turnt;
	int stat;
};

struct ht //For sjb : acts as hash table
{
	int data;
	int key;
	int stat;
};

////////////////////////////////////// FCFS //////////////////////////////////////////

void fcfs(struct pr* p,int n)
{	
	int time=0,total_wait=0,total_turn=0;
	printf("\nThe scheduling as per FCFS is:\t");
	for(int i=0;i<n;i++)
	{
		time += p[i].burt;
        p[i].turnt = time - p[i].arrt;
        total_turn += p[i].turnt;
        
        p[i].wtime = p[i].turnt - p[i].burt;
        total_wait += p[i].wtime;
        
		printf("-> %s ",p[i].pname);
	}
	
	printf("\nAvg. Waiting Time= %f",(total_wait * 1.0)/n); 
    printf("\nAvg. Turnaround Time = %f",(total_turn * 1.0)/n);  
}

/////////////////////////////////////// SJF //////////////////////////////////////////

void sjf(struct pr* p,int n)
{
	int n1=0,prev=0,k=1,time=0;
	float wait_time=0,turn_time=0;
	struct ht temp1,*hash;
	hash = (struct ht*) malloc (n * sizeof(struct ht));
	
	//Making the stat = 0//
	for(int i=0;i<n;i++)			
	{
		hash[i].stat = 0;
		p[i].stat = 0;
	}
	
	//Scheduling procedure begins//
	time += p[0].burt;
	printf("\nThe scheduling as per SJF is :\t-> %s ",p[0].pname);
	p[0].stat = -1;
	p[0].turnt = time - p[0].arrt; 
	p[0].wtime = p[0].turnt - p[0].burt;
	wait_time += p[0].wtime;
	turn_time += p[0].turnt;
	
	while(k<n)
	{
		for(int i=0;i<n;i++)
		{
			if(p[i].arrt <= p[prev].burt && p[i].stat !=-1)
			{
				hash[n1].data = i;									//Storing index of all the arrival times less than the burst time of the previous completed process//
				hash[n1].key = p[i].burt; 							//Storing burst time as key of hash table//
				hash[n1].stat = 1;
				p[i].stat =-1;
				n1++;
			}
		}
		
		for(int i=0;i<n1;i++)										//Sorting hash table//
		{
			for(int j=0;j<n1-1;j++)
			{
				if(hash[j].key > hash[j+1].key)
				{
					temp1 = hash[j];
					hash[j] = hash[j+1];
					hash[j+1] = temp1;
				}
			}
		}
		
		int prev1 = prev; 
		for(int i=0;i <=n1;i++)
		{
			if(hash[i].stat == 1)
			{
				int x = hash[i].data;
				printf("-> %s ",p[x].pname);
				
				time += p[x].burt;
				p[x].turnt = time - p[x].arrt;							//Calculating turnaround time for each process//
				turn_time += p[x].turnt; 						
										
				
				p[x].wtime = p[x].turnt - p[x].burt;					//Calculating wait time for each process//
				wait_time += p[x].wtime;

				prev = x;
				hash[i].stat = 0;
				break;
			}
		}
		k++;
	}
	printf("\nAvg. Waiting Time= %f",(wait_time * 1.0)/n); 		
    printf("\nAvg. Turnaround Time = %f",(turn_time * 1.0)/n);  
    free(hash);
	
}

///////////////////////////////////////// RR /////////////////////////////////////////////

void rr(struct pr* p,int n)
{
     int j,time=0,flag=0,qt=0; 
     int *rt = (int*) malloc (sizeof(int) * n); 
     float wait_time=0,turn_time=0;
     int rem=n; 
     printf("Enter Time Quantum: "); 
     scanf("%d",&qt); 
     
     for(int i=0;i<n;i++)											//Storing burst time in an array which will be storing time remaining for process completion //
     {
     	rt[i] = p[i].burt;
     }
     
     printf("\nThe scheduling as per RR is:\t"); 
     for(int i=0;rem!=0;) 
     { 
          if(rt[i]<=qt && rt[i]>0) 									//If time remaining is less than time slice and is greater than 0//
          { 
               time+=rt[i];
               printf("-> %s ",p[i].pname); 
               rt[i]=0; 
               flag=1; 
          } 
          else if(rt[i]>0) 											//If time remaining is greater than 0//
          { 
               rt[i]-=qt; 
               time+=qt; 
               printf("-> %s ",p[i].pname); 
          } 
          if(rt[i]==0 && flag==1) 									//If time remaining is equal to 0//
          { 
               rem--;  
               wait_time += time-p[i].arrt-p[i].burt; 
               turn_time += time-p[i].arrt; 
               p[i].wtime = wait_time;
               p[i].turnt = turn_time;
               flag=0; 
          } 
          if(p[i+1].arrt<=time)
               i++; 
          else 
               i=0; 
     }
     printf("\nAvg. Waiting Time= %f",(wait_time * 1.0)/n); 
     printf("\nAvg. Turnaround Time = %f",(turn_time * 1.0)/n);  
     free(rt);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	system("clear");
	int n;
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	struct pr *p,temp;
	p = (struct pr*) malloc (n * sizeof(struct pr));
	for(int i=0;i<n;i++)
	{
		printf("Enter the name of process %d :",i+1);
		scanf("%s",p[i].pname);
		printf("Enter the arrival time (in ms) of process %d :",i+1);
		scanf("%d",&(p[i].arrt));
		printf("Enter the burst time (in ms) of process %d :",i+1);
		scanf("%d",&(p[i].burt));
	}
	system("clear");
	printf("The process list is as follows!\n");
	printf("Process list\t\tArrival time(in ms)\t\tBurst time(in ms)");
	for(int i=0;i<n;i++)
	{
		gotoxy(0,3+i);
		printf("%s",p[i].pname);
		gotoxy(25,3+i);
		printf("%d",p[i].arrt);
		gotoxy(57,3+i);
		printf("%d",p[i].burt);
		gotoxy(0,3+i+1);
	}
	
	//Sorting according to arrival time//
	for(int i=0;i<n;i++)			
	{
		for(int j=0;j<n-1;j++)
		{
			if(p[j].arrt > p[j+1].arrt)
			{
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
	
	int ch;
	printf("The choice of scheduling policies are: 1. FCFS  2. SJF  3. Round Robin");
	printf("\nEnter your choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			fcfs(p,n);
			printf("\n");
			break;
			
		case 2:
			sjf(p,n);
			printf("\n");
			break;
			
		case 3:
    		rr(p,n);
    		printf("\n");
    		break;
		
		default:
			printf("\nThe choice is invalid!\n");
			
	}
	return 0;
}
