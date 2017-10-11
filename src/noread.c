/*************************************************************************
    > File Name: src/noread.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月10日 星期二 18时37分50秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
int set_fl(int fd,int flag)
{
	int val = fcntl(fd,F_GETFL);
	if(val < 0){
		return -1;
	}
	//将要是设置的属性“或”到变量中
	val |= flag;
	if(fcntl(fd,F_SETFL,val) < 0){
		return -1;
	}
	return 0;
}
int main(int argc,char** argv)
{
	//1.添加非阻塞标志
	if(set_fl(STDIN_FILENO,O_NONBLOCK) < 0){
		fprintf(stderr,"set_fl error %s\n",strerror(errno));
		exit(1);
	}
	//2.休眠一段时间，用户从键盘输入，输入数据
	sleep(5);
	//3.
	char buff[100] = {'\0'};
	int size = read(STDIN_FILENO,buff,100);
	if(size < 0){
		fprintf(stderr,"read error %s\n",strerror(errno));
		exit(1);
	}else if(size == 0){
		printf("read eof\n");
	}else{
		printf("read buff: %s\n",buff);
	}
	return 0;
}


