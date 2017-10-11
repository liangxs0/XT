/*************************************************************************
    > File Name: src/hole.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月10日 星期二 09时53分01秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main (int argc,char **argv)
{
	int fd;
	if((fd = creat("./doc/c.txt",0644)) < 0){
		fprintf(stderr,"creat error %s\n",strerror(errno));
		exit(1);
	}
	if(write(fd,buf1,10) != 10){
		fprintf(stderr,"write error",strerror(errno));
		exit(1);
	}
	if(lseek(fd,10L,SEEK_CUR) < 0){
		fprintf(stderr,"lseek error %s\n",strerror(errno));
		exit(1);
	}
	if(write(fd,buf2,10) != 10){
		fprintf(stderr,"write error %s\n",strerror(errno));
		exit(1);
	}
	return 0;
}
