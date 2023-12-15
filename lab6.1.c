#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

void* thread_routine(char* str)
{
	// if the string is empty
    if (!str) {
        return;
    }
    // pointer to start and end at the string
    int i = 0;
    int j = strlen(str) - 1;
 
    // reversing string
    while (i < j) {
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
        i++;
        j--;
    }
    
    return str;

}

int main(int argc, char ** argv[])
{
	char * rez;
	pthread_t pui;
	pthread_create (&pui, NULL, thread_routine, argv[1]);
	pthread_join(pui, &rez);
	printf("%s ",rez);

	return 0;
}
