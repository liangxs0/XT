/*************************************************************************
    > File Name: src/upcat.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月10日 星期二 10时09分58秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define LEN 1024
void copy(int fd_in,int fd_out)
{
	char buff[LEN] = {"\0"};
	int size;

	while((size = read(fd_in,buff,LEN)) > 0){
		if(write(fd_out,buff,size) != size){
			fprintf(stderr,"write error %s\n",strerror(errno));
			exit(1);
		}
	}
	if(size < 0){
		fprintf(stderr,"read error %s\n",strerror(errno));
		exit(1);
	}
}
int main(int argc,char** argv)
{
	if(argc == 1){
		copy(0,1);
	}else{
		int i = 1;
		for(;i < argc;i++){
			if(strcmp(argv[i],"+") == 0){
				int fd = open (argv[++i],O_RDONLY);
				if(fd < 0){
					fprintf(stderr,"open error %s\n",strerror(errno));
					exit(1);
				}
				if(dup2(fd,0) != 0){
					//将fd赋值给0号文件描述符，即将fd为标准输入
					fprintf(stderr,"dup2 error %s\n",strerror(errno));
					exit(1);
				}
				close(fd);
			}else if((strcmp(argv[i],"-") == 0)){
				int fd = open(argv[++i],O_WRONLY|O_CREAT|O_TRUNC,0644);
				if(fd < 0){
			 		fprintf(stderr,"open error %s\n",strerror(errno));
					exit(1);
				}
				if(dup2(fd,1) != 1){
					fprintf(stderr,"dup2 error %s\n",strerror(errno));
					exit(1);
				}
				close(fd);
			}		
		}
		copy(0,1);
	}
	return 0;
}

