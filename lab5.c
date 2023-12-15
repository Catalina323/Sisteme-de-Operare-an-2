#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

void colatz(int n, int * v)
{	
	int k = 0;
	v[k++] = INT_MAX;
	v[k++] = n;

	while(n > 1)
	{
		if(n % 2 == 0)
		{
			n /= 2;
			v[k++] = n;
		}
		else
		{
			n = 3 * n + 1;
			v[k++] = n;
		}
	}
	v[k++] = INT_MAX;
}

int main(int argc, char ** args)
{
	printf("starting parent %d \n", getpid());
	
	char shm_name[] = "mem_part";
	int shm_fd ;

	shm_fd = shm_open (shm_name , O_CREAT | O_RDWR , S_IRUSR | S_IWUSR);
	
	if ( shm_fd < 0) 
	{
		perror ( NULL );
		return errno ;
	}
	
	size_t page_size = getpagesize();
	size_t shm_size = (argc-1) * page_size;
	
	if ( ftruncate ( shm_fd , shm_size ) == -1) 
	{
		perror ( NULL );
		shm_unlink ( shm_name );
		return errno ;
	}
	
	int * shm_ptr_parent = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	
	for(int i=1;i<=argc;i++)
	{
		pid_t pid = fork();
		
		if(pid < 0)
			return errno;
		else if( pid == 0)
		{
			//cod copil
			int * shm_ptr;
		shm_ptr = (int*)mmap(0, page_size, PROT_WRITE, MAP_SHARED, shm_fd, (i-1)*page_size);
			
			
			if ( shm_ptr == MAP_FAILED ) 
			{
				perror ( NULL );
				shm_unlink ( shm_name );
				return errno ;
			}
			
			//functia colatz
			colatz(atoi(args[i]), shm_ptr);
			
			printf("Done parent %d, ME %d \n", getppid(), getpid());
			return 0;
		}
		else
		{
			//cod parinte
			pid_t p = wait(NULL);	
		}
	
	}
	
	int k = 0;
	int i = 1;
	int * v = (int*) shm_ptr_parent;
	while(k < shm_size)
	{
		
		if(v[k] == INT_MAX)
		{
			printf("%d: ", atoi(args[i]));
		
			while(v[++k] != INT_MAX)
			{
				printf("%d ", v[k]);
			}
			
			printf("\n");
			i++;
		}
		
		k++;
		if(i == argc)
			break;
	
	}
	
	printf("Done parent %d, ME %d \n", getppid(), getpid());
	
	shm_unlink(shm_name);
	munmap (shm_ptr_parent , shm_size);

	return 0;
}
