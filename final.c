#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void create_tree(pid_t pid,int even, int odd, int level);
void measure_time(int sig);
int main(int argc, char *argv[])
{
	int even, odd,level;
	int id;
	printf("Enter even, odd, levels\n");
	scanf("%d",&even);
	scanf("%d",&odd);
	scanf("%d",&level);
	id = getpid();
	printf("%d\n",id);
	create_tree(id,even,odd,level);		
}
void create_tree(int id,int even,int odd, int level)
{
	level = level-1;	
	if(id%2==0&&level>=0)
	{	int ar[even];
		for(int i=0;i<even;i++)
		{
			int status = fork();
			if(status==0)
			{
				printf("%d\t%d\n",getpid(),id);
				signal(SIGUSR1,measure_time);
				exit(1);
			}
			else if(status>0)
			{
				ar[i]=status;
				int s;
        			int corpse = wait(&s);
        printf("Child %d exited with status 0x%.4X\n", corpse, s);
		
			}
		}
		for(int i=0;i<even;i++)
		{
			kill(ar[i],SIGUSR1);
		}
		for(int i=0;i<even;i++)
		{
		if(level>=0)
		create_tree(ar[i],even,odd,level);
		}
	}


	else if(id%2!=0&&level>=0)
	{
		int ar[odd];
		for(int i=0;i<odd;i++)
		{
			int status = fork();
			if(status==0)
			{
				printf("%d\t%d\n",getpid(),id);
				signal(SIGUSR1,measure_time);
				exit(2);
			}
			else if(status>0)
			{	
				printf("%d\n",status);
				ar[i]=status;
				int s;
				int corpse = wait(&s);
        printf("Child %d exited with status 0x%.4X\n", corpse, s);
				
			}
		}
		for(int i=0;i<odd;i++)
		{
			kill(ar[i],SIGUSR1);
		}
		
		for(int i=0;i<odd;i++)
		{	
			if(level>=0)
			{
			create_tree(ar[i],even,odd,level);
			}
		}
	}
}
void measure_time(int sig)
{
	printf("%d",sig);
}
		
		
		
		
