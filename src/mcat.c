/*************************************************************************
    > File Name: src/mcat.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月10日 星期二 09时04分05秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define LEN 1024

void copy (int fd_in,int fd_out)
{
	char buff[LEN] = {"\0"};
	int size;
	while((size = read(fd_in,buff,LEN)) > 0){
		//读取成功写入fd_out
		if(write(fd_out,buff,size) != size){
		//写入错误
		fprintf(stderr,"write,%s\n",strerror(errno));
		exit(1);
		}
	}
	if(size < 0){
		fprintf(stderr,"read,%s\n",strerror(errno));
		exit(1);
	}
}
int main(int argc,char** argv)
{
	if(argc == 1){
		//不包括后续参数，则直接从标准输入读，写到标准输出
		copy(STDIN_FILENO,STDOUT_FILENO);
	}else{
		int fd;
		int i = 1;
		for(;i < argc;i++){
			fd = open(argv[i],O_RDONLY);
			if(fd < 0){
				fprintf(stderr,"read error %s\n",strerror(errno));
			 	continue;
			}
			copy(fd,STDOUT_FILENO);
			close(fd);
		}
	}
	return 0;
}







