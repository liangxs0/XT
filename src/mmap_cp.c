/*************************************************************************
    > File Name: src/mmap_cp.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月10日 星期二 19时15分55秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

void str_err(const char *name)
{
	fprintf(stderr,"%s %s",name,strerror(errno));
	exit(1);
}
int main(int argc,char** argv)
{
	if(argc < 3){
		str_err("usage error");
	}
	//先打开两个文件
	int fd1 = open(argv[1],O_RDONLY);
	if(fd1 < 0){
		str_err("open error:");
	}
	int fd2 = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0644);
	//获取文件大小
	struct stat filebuf;
	stat(argv[1],&filebuf);
	int size = filebuf.st_size;
	//跟打开的文件建立内存映射
	char* ptr1 = (char*)mmap(0,size,PROT_READ,MAP_SHARED,fd1,0);
	char* ptr2 = (char*)mmap(0,size,PROT_WRITE|PROT_READ,MAP_SHARED,fd2,0);
	//先扩充第二个文件的大小
	ftruncate(fd2,size);
	//通过内存映射转移数据
	memcpy(ptr2,ptr1,size);
	munmap(ptr1,size);
	munmap(ptr2,size);
	close(fd1);
	close(fd2);

	return 0;
}
