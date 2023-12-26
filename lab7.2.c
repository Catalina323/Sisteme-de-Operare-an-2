#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>

int nthrs = 5;

sem_t sem;
pthread_mutex_t mutex;
int count = 0;

void barrier_point()
{
	pthread_mutex_lock(&mutex);
	count++;
	pthread_mutex_unlock(&mutex);

	if(count == 5)
	{
		sem_post (& sem );
	}
	if(count < 5)
	{
		sem_wait(& sem );	
		sem_post (& sem );
	}
	
}


void * tfun ( void * v )
{
	int * tid = ( int *) v ;
	printf ("%d reached the barrier \n", * tid );
	barrier_point ();
	printf ("%d passed the barrier \n", * tid );
	free ( tid );
	return NULL ;
}


int main(int argc, char ** args)
{
	sem_init(&sem, 0, 0);
	
	pthread_t threads[nthrs];

	for(int i=0;i<nthrs;i++)
	{
		int* v = malloc(sizeof(int));
		(*v) = i;
		pthread_create(&threads[i], NULL, tfun, v);
	}	

	for(int i=0; i<nthrs; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	sem_destroy(&sem);
	pthread_mutex_destroy(&mutex);

	return 0;
}
