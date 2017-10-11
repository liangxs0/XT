/*************************************************************************
    > File Name: src/mcp.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月10日 星期二 08时41分57秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 1024
void str_err(const char *name)
{
	fprintf(stderr,"%s:%s",name,strerror(errno));
	exit(1);
}

int main(int argc,char** argv)
{
	if(argc < 3){
		str_err("usage error");
	}
	//打开俩个文件
	int fd_in = open(argv[1],O_RDONLY);
	if(fd_in < 0){
		str_err("open,error");
	}
	int fd_out = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT,0644);
	if(fd_out < 0){
		str_err("open error");
	}
	//准备缓冲区
	char buff[SIZE] = {"\0"};
	memset(buff,0,SIZE);
	int size;
	//循环读到文件末尾
	while((size = read(fd_in,buff,SIZE)) > 0){
		if(write(fd_out,buff,size) != size){
			//如果数据写入不等于读到的长度说明出错
			str_err("write error");
		}
	}
	if(size < 0){
		//读错误
		str_err("read error");
	}
	close(fd_in);
	close(fd_out);

	return 0;
}










