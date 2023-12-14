#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>

void colatz(int n)
{
	while(n > 1)
	{
		
		if(n % 2 == 0)
		{
			n /= 2;
			printf("%d ", n);
		}
		else
		{
			n = 3 * n + 1;
			printf("%d ", n);
		}
	}
}

int main(int argc, char ** args)
{
	printf("starting parent %d \n", getpid());
	
	for(int i=1;i<=argc;i++)
	{
		pid_t pid = fork();
		
		if(pid < 0)
			return errno;
		else if( pid == 0)
		{
			//cod copil
			printf("%d: %d ", atoi(args[i]), atoi(args[i]));
			colatz(atoi(args[i]));
			printf("\n");
			printf("Done parent %d, ME %d \n", getppid(), getpid());
			return 0;
		}
		else
		{
			//cod parinte
			pid_t p = wait(NULL);	
		}
	}
	
	printf("Done parent %d, ME %d \n", getppid(), getpid());

	return 0;
}
