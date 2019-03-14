#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc,const char *argv[])
{
	const char filename[8] = "ex1.txt";
	int fd = open("ex1.txt",O_RDWR);
	struct stat mystat;
	int status = fstat(fd,&mystat);
	off_t mysize = mystat.st_size;

	char* map = (char*) mmap(NULL,mysize,PROT_READ|PROT_WRITE,MAP_SHARED,fd, 0);

	map[10] = 'n';
	map[11] = 'i';
	map[12] = 'c';
	map[13] = 'e';

	return 0;
}