#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int rt;
	struct pr *next;
}*head=NULL,*headf=NULL,*headm=NULL;

///////////////////////////// CREATE THE LINKED LIST ///////////////////////////////

struct pr* create(struct pr *head,int i)
{
	struct pr *nn,*temp;
	temp = head;
	nn = (struct pr *) malloc(1 * sizeof(struct pr));
	nn->next=NULL;
	printf("Enter the name of process %d :",i+1);
	scanf("%s",&(nn->pname));
	printf("Enter the arrival time (in ms) of process %d :",i+1);
	scanf("%d",&(nn->arrt));
	printf("Enter the burst time (in ms) of process %d :",i+1);
	scanf("%d",&(nn->burt));
	
	if(head==NULL)
	{
		head = nn;
	}
	else
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nn;
	}
	return head;
}

//////////////////////////////////////DISPLAY/////////////////////////////////////////

void display(struct pr *head)
{
	struct pr *temp;
	temp = head;
	int i=0;
	while(temp != NULL)
	{
		gotoxy(0,3+i);
		printf("%s",temp->pname);
		gotoxy(25,3+i);
		printf("%d",temp->arrt);
		gotoxy(57,3+i);
		printf("%d",temp->burt);
		gotoxy(0,3+i+1);
		temp = temp->next;
		i++;
	}
}

////////////////////////////////////// SORT //////////////////////////////////////////

struct pr* sort(struct pr* head)
{
	struct pr *temp,*temp1;
	int a;
	char t[5];
	temp = head;
	temp1 = head;
	do			
	{
		temp1 = head;
		while(temp1->next!=NULL)
		{
			if(temp1->arrt > (temp1->next)->arrt)
			{
				a = temp1->arrt;
				temp1->arrt = (temp1->next)->arrt;
				(temp1->next)->arrt = a;
				
				a = temp1->burt;
				temp1->burt = (temp1->next)->burt;
				(temp1->next)->burt = a;
				
				strcpy(t,temp1->pname);
				strcpy(temp1->pname, (temp1->next)->pname);
				strcpy((temp1->next)->pname, t);
			}
			temp1 = temp1->next;
		}
		temp = temp->next;
	}
	while(temp!=NULL);
	return head;
}
////////////////////////////////////// FCFS //////////////////////////////////////////

void fcfs(struct pr* head,int n)
{	
	struct pr *temp;
	temp = head;
	int time=0,total_wait=0,total_turn=0;
	printf("\nThe scheduling as per FCFS is:\t");
	while(temp != NULL)
	{
		time += temp->burt;
        temp->turnt = time - temp->arrt;
        total_turn += temp->turnt;
        
        temp->wtime = temp->turnt - temp->burt;
        total_wait += temp->wtime;
        
		printf("-> %s ",temp->pname);
		temp=temp->next;
	}
	
	printf("\nAvg. Waiting Time= %f",(total_wait * 1.0)/n); 
    printf("\nAvg. Turnaround Time = %f",(total_turn * 1.0)/n);  
}

/////////////////////////////////////// CREATE EMPTY //////////////////////////////////////////

struct pr* createe(struct pr *head, int arr, int burr, char* pn, int wtime1, int ttime, int stat1)
{
	struct pr *nn,*temp;
	temp = head;
	nn = (struct pr *) malloc(1 * sizeof(struct pr));
	nn->next=NULL;
	strcpy(nn->pname,pn);
	nn->arrt = arr;
	nn->burt = burr;
	nn->wtime = wtime1;
	nn->turnt = ttime;
	nn->stat = stat1;
	if(head==NULL)
	{
		head = nn;
	}
	else
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nn;
	}
	return head;
}

/////////////////////////////////////// SORT BY BURST //////////////////////////////////////////

struct pr* sortb(struct pr* head)
{
	struct pr *temp,*temp1;
	int a;
	char t[5];
	temp = head;
	temp1 = head;
	do			
	{
		temp1 = head;
		while(temp1->next!=NULL)
		{
			if(temp1->burt > (temp1->next)->burt)
			{
				a = temp1->arrt;
				temp1->arrt = (temp1->next)->arrt;
				(temp1->next)->arrt = a;
				
				a = temp1->burt;
				temp1->burt = (temp1->next)->burt;
				(temp1->next)->burt = a;
				
				strcpy(t,temp1->pname);
				strcpy(temp1->pname, (temp1->next)->pname);
				strcpy((temp1->next)->pname, t);
				
				a = temp1->wtime;
				temp1->wtime = (temp1->next)->wtime;
				(temp1->next)->wtime = a;
				
				a = temp1->turnt;
				temp1->turnt = (temp1->next)->turnt;
				(temp1->next)->turnt = a;
				
				a = temp1->stat;
				temp1->stat = (temp1->next)->stat;
				(temp1->next)->stat = a;
				
				a = temp1->rt;
				temp1->rt = (temp1->next)->rt;
				(temp1->next)->rt = a;
			}
			temp1 = temp1->next;
		}
		temp = temp->next;
	}
	while(temp!=NULL);
	return head;
}
	 
/////////////////////////////////////// SJF //////////////////////////////////////////

void sjf(struct pr* head,int n)
{
	int time=0,n1=n;
	float wait_time=0,turn_time=0;
		
	struct pr *temp,*tempm,*tempf,*p;
	temp = head;
	
	//Making the stat = 0//
	for(int i=0;i<n;i++)			
	{
		temp->stat = 0;
		temp = temp->next;
	}
	
	temp = head;
	
	//Scheduling procedure begins//
	time += temp->burt;
	temp->stat = -1;
	temp->turnt = time - temp->arrt; 
	temp->wtime = temp->turnt - temp->burt;
	wait_time += temp->wtime;
	turn_time += temp->turnt;
	
	headf = createe(headf, temp->arrt, temp->burt, temp->pname, temp->wtime, temp->turnt, temp->stat);
	tempf = headf;
	
	while(n1>1)
	{
		while(temp!=NULL)
		{
			if((temp->arrt <= tempf->burt) && temp->stat == 0)
			{
				temp->stat = -1;
				headm = createe(headm, temp->arrt, temp->burt, temp->pname, temp->wtime, temp->turnt, temp->stat);					
			}
			temp = temp->next;
		}
		temp = head;
		
		headm = sortb(headm);
		headf = createe(headf, headm->arrt, headm->burt, headm->pname, headm->wtime, headm->turnt, headm->stat);
		tempf = tempf->next;
		time += tempf->burt;
		tempf->turnt = time - tempf->arrt;								//Calculating turnaround time for each process//
		turn_time += tempf->turnt; 													
		tempf->wtime = tempf->turnt - tempf->burt;						//Calculating wait time for each process//
		wait_time += tempf->wtime;
		
		p = headm;
		headm = p->next;
		p->next = NULL;
		free(p);
		n1--;			
	}
	
	tempf = headf;
	printf("\nThe scheduling as per SJF is:\t");
	while(tempf!=NULL)
	{
		printf("-> %s\t",tempf->pname);
		tempf = tempf->next;
	}
	
	printf("\nAvg. Waiting Time= %f",(wait_time * 1.0)/n); 		
    printf("\nAvg. Turnaround Time = %f",(turn_time * 1.0)/n);  

}

///////////////////////////////////////// RR /////////////////////////////////////////////

void rr(struct pr* head,int n)
{
	 struct pr *temp;
	 temp = head;
     int time=0,flag=0,qt=0; 
     float wait_time=0,turn_time=0;
     int rem=n; 
     printf("Enter Time Quantum: "); 
     scanf("%d",&qt); 
     
     while(temp!=NULL)
     {
     	temp->rt = temp->burt;
     	temp = temp->next;
     }
     temp = head;
     printf("\nThe scheduling as per RR is:\t"); 
     while(temp!=NULL && rem!=0) 
     { 
          if((temp->rt) <= qt && (temp->rt)>0 ) 						//If time remaining is less than time slice and is greater than 0//
          { 
               time += temp->rt;
               printf("-> %s ",temp->pname); 
               temp->rt=0; 
               flag=1; 
          } 
          else if(temp->rt>0) 											//If time remaining is greater than 0//
          { 
               temp->rt-=qt; 
               time+=qt; 
               printf("-> %s ",temp->pname); 
          } 
          if(temp->rt==0 && flag==1) 									//If time remaining is equal to 0//
          { 
               rem--;  
               wait_time += time-temp->arrt-temp->burt; 
               turn_time += time-temp->arrt; 
               temp->wtime = wait_time;
               temp->turnt = turn_time;
               flag=0; 
          } 
          if(temp->next!=NULL && (temp->next)->arrt <= time)
               temp = temp->next; 
          else 
               temp = head; 
     }
     printf("\nAvg. Waiting Time= %f",(wait_time * 1.0)/n); 
     printf("\nAvg. Turnaround Time = %f",(turn_time * 1.0)/n);  
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	system("clear");
	int n;
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		head = create(head,i);
	}

	system("clear");
	printf("The process list is as follows!\n");
	printf("Process list\t\tArrival time(in ms)\t\tBurst time(in ms)");
	display(head);
	
	head = sort(head);

	int ch;
	printf("The choice of scheduling policies are: 1. FCFS  2. SJF  3. Round Robin");
	printf("\nEnter your choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			fcfs(head,n);
			printf("\n");
			break;
			
		case 2:
			sjf(head,n);
			printf("\n");
			break;
			
		case 3:
    		rr(head,n);
    		printf("\n");
    		break;
		
		default:
			printf("\nThe choice is invalid!\n");
			
	}
	return 0;
}
