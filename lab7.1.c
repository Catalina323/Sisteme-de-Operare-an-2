#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

# define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;

pthread_mutex_t mutex;

int decrease_count ( int count )
{
	pthread_mutex_lock(&mutex);
	if ( available_resources < count )
		return -1;
	else
	{	//printf("av res: %d  count: %d \n", available_resources, count);
		
		available_resources -= count;
		
	}
	pthread_mutex_unlock(&mutex);
	return 0;
}

int increase_count ( int count )
{
	//printf("av res: %d  count: %d \n", available_resources, count);
	
	pthread_mutex_lock(&mutex);
	available_resources += count;
	pthread_mutex_unlock(&mutex);
	
	return 0;
}

void * routine(void * args)
{
	int a = *(int*)(args);
	
	if(a < available_resources)
	{
	decrease_count(a);

	printf("got %d resoruces %d remaining \n", a, available_resources);

	increase_count(a);
	
	printf("Released %d resources %d remaining \n", a, available_resources);
	}

}

int main(int args, char ** argv)
{

	pthread_t threads[5];
	pthread_mutex_init(&mutex, NULL);
	int nr_resurse[] = {2,2,1,3,2};
	
	for(int i=0; i<5; i++)
	{
		pthread_create(&threads[i], NULL, routine, &nr_resurse[i]);	
	}
	
	for(int i=0;i<5;i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	pthread_mutex_destroy(&mutex);
	
	return 0;
}
