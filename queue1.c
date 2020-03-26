#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct node
{
	int ti;
	int jobno;
	struct node*nxtq;
};	

void enqueue(struct node**front,struct node**rear,int tim,int jobnum)
{
	struct node*temp=NULL;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->ti=tim;
	temp->jobno=jobnum;
	temp->nxtq=NULL;
	if(*rear==NULL&&*front==NULL)
	{
		*front=temp;
		*rear=temp;
	}
	else
	{
		struct node*p=*rear;
		p->nxtq=temp;
		*rear=temp;
	}
}

		
void dequeue(struct node**front,struct node**rear)
{
	if(*front==NULL&&*rear==NULL)
	return;
	else
	{
		struct node*temp=*front;
		struct node*o=*front;
	    *front=o->nxtq;
	    o->nxtq=NULL;
	    if(*front==NULL)
	    *rear=NULL;
	    free(temp);
	    
	 }   
	
}

void display(struct node**front)
{
	struct node	*temp=*front;
	if(*front==NULL)
	return;
		
	else
	{
		
	  while(temp!=NULL)
	  {
		  printf("J%d:%d",temp->jobno,temp->ti);
		  if(temp->nxtq!=NULL)
		  printf(",");
		  temp=temp->nxtq;
	  }
	}  
}

void opqueue1(struct node**front,struct node**rear)
{
	struct node*temp=*front;
	int coll=temp->ti;
	int prev=0;
	
	while(coll<=50&&*front!=NULL)
	{
		dequeue(front,rear);
		temp=*front;
		
		prev=coll;
		if(temp==NULL)
		break;
		coll=coll+temp->ti;
	}
	if(temp==NULL)
	return;
	else
	{
		temp->ti=temp->ti-(50-prev);
		if(temp->ti==0)
		dequeue(front,rear);
		else
		{
			
			enqueue(front,rear,temp->ti,temp->jobno);
			dequeue(front,rear);
		}
	}	
}		
	
	
	
	
	
		
  
void opqueue2(struct node**front,struct node**rear)
{
	struct node*temp=*front;
	int ty=temp->ti-50;
	int jb=temp->jobno;
	
	
	dequeue(front,rear);
    enqueue(front,rear,ty,jb);	
}			

void delay(int microseconds)	
{
	int milliseconds=microseconds/1000;
	clock_t start_time=clock();
	while(clock() < start_time + milliseconds) 
        ; 
}		
		
	  			
void createqueue()
{
	struct node*front=NULL;
	struct node*rear=NULL;
	int i;
	srand(time(0));
	for(i=0;i<100;i++)
	{
		int tim;
		
		tim=rand()%301;
		enqueue(&front,&rear,tim,i+1);
	}
	printf("Initial Queue\n");
	display(&front);
	//printf("\n%d",front->ti);
	
	int timeadd=50;
	int jobadd;
	while(front!=NULL)
	{
		
		struct node*temp=front;
		//delay(50);
		

																				
	
		
		
				
	    if(temp->ti<=50)
	   {
		  opqueue1(&front,&rear);
		  printf("\n");
		  printf("\nQueue after %dus\n",timeadd);
		  display(&front);
	   }
	   else
	   {
		 opqueue2(&front,&rear);
		 printf("\n");
		 printf("\nQueue after %dus\n",timeadd);
		 display(&front);
	   }
	   
	  
		if(timeadd==200)
		{
			for(jobadd=1;jobadd<65;jobadd++)
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+100);
			}
			printf("\n\n*****200us have passed,64 jobs added****\n");
			
		}
		 if(timeadd==400)
		{
			for(jobadd=1;jobadd<33;jobadd++)
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+164);
			}
			printf("\n\n****400us have passed,32 jobs added****\n");
					
		}
		if(timeadd==600)
		{
			for(jobadd=1;jobadd<17;jobadd++)
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+196);
			}
			printf("\n\n****600us have passed,16 jobs added****\n");
						
		}
		if(timeadd==800)
		{
			for(jobadd=1;jobadd<9;jobadd++)
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+212);
			}
			printf("\n\n****800us have passed,8 jobs added****\n");
					
		}	
		if(timeadd==1000)
		{											
			for(jobadd=1;jobadd<5;jobadd++)
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+220);
			}
			printf("\n\n****1000us have passed,4 jobs added****\n");
					
		}
		if(timeadd==1200)
		{
			
			for(jobadd=1;jobadd<3;jobadd++)
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+224);
			}
			printf("\n\n****1200us have passed,2 jobs added****\n");
					
		}	
		if(timeadd==1400)
		{
			int tim;
			tim =rand()%301;
			enqueue(&front,&rear,tim,227);
			printf("\n\n****1400us have passed,1 job added****\n");
		}	   
	    timeadd=timeadd+50;
	   
	} 
	if(front==NULL)
	printf("Empty\n");	
	
	
	
}	

 		
			
		
		
		
int main()
{
	createqueue();
	return 0;
}	
			
		
	
