#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	//argv[1] = numele fisierului sursa
	//argv[2] = numele fisierului destinatie
	int sursa, destinatie;
	sursa = open(argv[1], O_RDONLY);
	destinatie = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU);
	
	struct stat st;
	if(stat(argv[1], &st))
	{
		perror(argv[1]);
		return errno;
	}
	
	int dim = st.st_size;
	
	//printf("%d dim totala \n", dim);
	
	int total_bytes = 0;
	int buf_dim = 64 * sizeof(int);
	
	while(total_bytes < dim)
	{
		int * buf = malloc(buf_dim);
	
		int read_bytes = read(sursa, buf, buf_dim);
		printf("%d bytes cititi \n", read_bytes);
		int write_bytes = 0;
		
		while(write_bytes < read_bytes)
		{
			int current_write_bytes = write(destinatie, buf, read_bytes);
			write_bytes += current_write_bytes;
			printf("%d bytes scrisi \n", current_write_bytes);
		}
		
		free(buf);
		total_bytes += read_bytes;
	}
	
	//int r = read(sursa, buf, dim);
	//int w = write(destinatie, buf, dim);
	//printf("%d %d \n",r, w);

	//free(buf);
	close(sursa);
	close(destinatie);

	return 0;
}
