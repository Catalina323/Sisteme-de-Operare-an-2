#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

const int n = 2;
const int m = 2;
const int p = 2;
int m1[2][2] = {{1,2}, {3,4}};
int m2[2][2] = {{1,2}, {3,4}};
int rez[2][2];

typedef struct str{
	int linie;
	int coloana;
	int nr_elem;
}str;

void* thread_routine(void * argvs)
{
	str* arg = (str*)argvs;
	int sum = 0;
	for(int t=0;t<arg->nr_elem;t++)
	{
		sum += m1[arg->linie][t] * m2[t][arg->coloana];
	}
	free(arg);
	return sum;
}

int main(int argc, char ** argv)
{
	
	pthread_t threads[m * p];
	int k = 0;
	
	for(int i=0;i<m;i++)
	{
		for(int j=0; j<p; j++)
		{
			
			str* arg = malloc(sizeof(str));
			
			arg->linie = i;
			arg->coloana = j;
			arg->nr_elem = p;
			
			pthread_create (&threads[k], NULL, thread_routine, arg);
			k++;
			
		}
	}
	k = 0;
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<p;j++)
		{
			int *val;
			pthread_join(threads[k++], &val);
			rez[i][j] = val;
		}
	}

	for(int i=0;i<n;i++)
		{	for(int j=0;j<n;j++)
				printf("%d ", rez[i][j]);
			printf("\n");
		}

	return 0;
}
