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
	pid_t pid = fork();
	
	if(pid < 0)
		return errno;
	else if( pid == 0)
	{
		//cod copil
		printf("%d: %d ", atoi(args[1]), atoi(args[1]));
		colatz(atoi(args[1]));
		printf("\n");
	}
	else
	{
		//cod parinte
		pid_t p = wait(NULL);
		printf("Child %d finished \n", p);
		
	}


	return 0;
}
