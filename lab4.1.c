#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>


int main()
{

	pid_t pid = fork ();
	
	if ( pid < 0)
		return errno ;
	else if ( pid == 0)
	{
		/* child instructions */
		printf("My PID %d, Child PID %d \n", getppid(), getpid());
		
		char * argv [] = {" ls " , NULL };
		execve("/bin/ls" , argv , NULL );
		perror(NULL);
	}
	else
	{
		pid_t child_pid = wait(NULL);
		printf("Child %d finished \n", child_pid);
	
	}

	return 0;
}
