#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


//Defining the struct node
struct node
{
	int ti;
	int jobno;
	struct node*nxtq;
};	

//Function to add nodes at the end of the queue
void enqueue(struct node**front,struct node**rear,int tim,int jobnum)//front and rear pointing at the respective nodes in the queue
{
	struct node*temp=NULL;
	temp=(struct node*)malloc(sizeof(struct node));//Creating the node
	temp->ti=tim;
	temp->jobno=jobnum;
	temp->nxtq=NULL;
	if(*rear==NULL&&*front==NULL)//if queue is empty
	{
		*front=temp;
		*rear=temp;
	}
	else
	{
		struct node*p=*rear;//changing the rear pointer
		p->nxtq=temp;
		*rear=temp;
	}
}

//Function to delete the node from the front of the queue		
void dequeue(struct node**front,struct node**rear)//front and rear pointing at the respective nodes in the queue

{
	if(*front==NULL&&*rear==NULL)//if queue is empty
	return;
	else
	{
		struct node*temp=*front;
		struct node*o=*front;
	    *front=o->nxtq;//Changing the front pointer
	    o->nxtq=NULL;
	    if(*front==NULL)//if queue becomes empty
	    *rear=NULL;
	    free(temp);//deallocating the memory
	    
	 }   
	
}

//Function to display the queue
void display(struct node**front)//Front pointer of the queue as the argument
{
	struct node	*temp=*front;
	if(*front==NULL)//if queue is empty
	return;
		
	else
	{
		
	  while(temp!=NULL)
	  {
		  printf("J%d:%d",temp->jobno,temp->ti);
		  if(temp->nxtq!=NULL)
		  printf(",");
		  temp=temp->nxtq;//traversing  through the queue
	  }
	}  
}

//Function to dequeue and enqueue the job when the time needed for the job is less than or equal to the quantum time
void opqueue1(struct node**front,struct node**rear)
{
	struct node*temp=*front;
	int coll=temp->ti;//Storing the time 
	int prev=0;
	
	while(coll<=50&&*front!=NULL)//dequeuing the nodes until the collective time crosses quantum time or we reach the end of the queue
	{
		dequeue(front,rear);
		temp=*front;//Moving to the next node
		prev=coll;//Storing the time that was present in the dequeued job
		if(temp==NULL)//Break the loop on reaching the end of the queue
		break;
		coll=coll+temp->ti;//Adding the time of the next job
	}
	if(temp==NULL)//if queue is empty
	return;
	else
	{
		temp->ti=temp->ti-(50-prev);//Reducing the time of the job
		if(temp->ti==0)//If the time of the job is the quantum time
		dequeue(front,rear);
		else
		{
			//Reducing the time of the job,dequeuing and enqueuing the job
			enqueue(front,rear,temp->ti,temp->jobno);
			dequeue(front,rear);
		}
	}	
}		

//Function to dequeue and enqueue the job  when the time needed is more than the quantum time
void opqueue2(struct node**front,struct node**rear)
{
	struct node*temp=*front;
	int ty=temp->ti-50;//Reducing the time by quantum time
	int jb=temp->jobno;
	
	//dequeing and enqueuing the job
	dequeue(front,rear);
    enqueue(front,rear,ty,jb);	
}

//To produce a delay of required microseconds			
void delay(int microseconds)	
{
	int milliseconds=microseconds/1000;
	clock_t start_time=clock();
	while(clock() < start_time + milliseconds) 
        ; 
}		
		
//The final function	  			
void createqueue()
{
	struct node*front=NULL;//Creating front and rear pointers
	struct node*rear=NULL;
	int i;
	srand(time(0));
	for(i=0;i<10;i++)//Creating 100 jobs
	{
		int tim;
		
		tim=rand()%301;//A random integer between 0 and 300
		enqueue(&front,&rear,tim,i+1);//adding the job to the queue
	}
	printf("Initial Queue\n");
	display(&front);//printing the initial queue
	int timeadd=50;//to keep track of amount of time passed
	int jobadd;
	while(front!=NULL)//until all the jobs are dequeued
	{
		
		struct node*temp=front;
		//delay(50);
		if(temp->ti<=50)//if the time for the job at the front is less than quantum time
	   {
		  opqueue1(&front,&rear);
		  printf("\n");
		  printf("\nQueue after %dus\n",timeadd);
		  display(&front);//resultant queue after quantum time
	   }
	   else 
	   {
		 opqueue2(&front,&rear);
		 printf("\n");
		 printf("\nQueue after %dus\n",timeadd);
		 display(&front);//resultant queue after quantum time
	   }
	   
	  
		if(timeadd==200)//when time passed is 200us
		{
			for(jobadd=1;jobadd<65;jobadd++)//adding 64 jobs
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+100);
			}
			printf("\n\n*****200us have passed,64 jobs added****\n");
			
		}
		 if(timeadd==400)//when time passed is 400us
		{
			for(jobadd=1;jobadd<33;jobadd++)//adding 32 jobs
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+164);
			}
			printf("\n\n****400us have passed,32 jobs added****\n");
					
		}
		if(timeadd==600)//when time passed is 600us
		{
			for(jobadd=1;jobadd<17;jobadd++)//adding 16 jobs
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+196);
			}
			printf("\n\n****600us have passed,16 jobs added****\n");
						
		}
		if(timeadd==800)//when time passed is 800us
		{
			for(jobadd=1;jobadd<9;jobadd++)//adding 8 jobs
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+212);
			}
			printf("\n\n****800us have passed,8 jobs added****\n");
					
		}	
		if(timeadd==1000)//when time passed is 1000us
		{											
			for(jobadd=1;jobadd<5;jobadd++)
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+220);
			}
			printf("\n\n****1000us have passed,4 jobs added****\n");
					
		}
		if(timeadd==1200)//when time passed is 1200us
		{
			
			for(jobadd=1;jobadd<3;jobadd++)//adding 4 jobs
			{
				int tim;
				tim=rand()%301;
				enqueue(&front,&rear,tim,jobadd+224);
			}
			printf("\n\n****1200us have passed,2 jobs added****\n");
					
		}	
		if(timeadd==1400)//when time passed is 1400us
		{
			int tim;
			tim =rand()%301;
			enqueue(&front,&rear,tim,227);//adding one job
			printf("\n\n****1400us have passed,1 job added****\n");
		}	   
	    timeadd=timeadd+50;//adding 50us after every dequeueing and/or enqueuing the queue
	   
	} 
	if(front==NULL)//when the queue becomes empty
	printf("Empty\n");	
	
	
	
}	

//main function		
int main()
{
	createqueue();
	return 0;
}	
			
		
	
