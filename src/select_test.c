/*************************************************************************
    > File Name: src/select_test.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月10日 星期二 11时08分08秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>

int main(int argc,char** argv)
{
	//定义一个描述符集
	fd_set rset;
	//先清空
	FD_ZERO(&rset);
	//把需要监听的文件描述符添加进去
	FD_SET(STDIN_FILENO,&rset);
	//准备监听时间
	struct timeval t;
	t.tv_sec = 3;
	t.tv_usec = 0;
	//监听的描述符的最大值
	int maxFD = STDIN_FILENO + 1;
	int num;
	//循环监听，如果监听过程出现错误，跳出循环
	while((num = select(maxFD,&rset,NULL,NULL,&t)) >= 0){
		if(0 == num){
			//超时
			printf("timeout\n");
		}else{
			//有num个文件描述符准备好了
			if(FD_ISSET(STDIN_FILENO,&rset)){
				char buff[100] = {"\0"};
				int size;
				if((size = read(STDIN_FILENO,buff,100)) < 0){
					fprintf(stderr,"read %s\n",strerror(errno));
					exit(1);
				}else if(size == 0){
					printf("read eof\n");break;
				}else{
					write(STDOUT_FILENO,buff,size);
				}
			}else{
				printf("STDIN not ready\n");
			}
		}
		//重新定制rset和时间
		FD_ZERO(&rset);
		FD_SET(STDIN_FILENO,&rset);
		printf("tv_sec: %ld,tv_usec:%ld\n",t.tv_sec,t.tv_usec);
		t.tv_sec = 3;
		t.tv_usec = 0;
	}
	return 0;
}


