/*************************************************************************
    > File Name: src/f_lock.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月10日 星期二 18时56分19秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
	//准备锁
	struct flock lc;
	lc.l_type = F_RDLCK;//锁类型
	lc.l_start = 0;//锁的起始位置
	lc.l_whence = 0;//便宜量
	lc.l_len = 0;//长度 0 为默认全文
	//执行加锁操作
	int fd = open(argv[1],O_RDONLY);
	if(fcntl(fd,F_SETLK,&lc) < 0){
		fprintf(stderr,"lock error %s\n",strerror(errno));
		close(fd);
		exit(0);
	}
	sleep(2);
	//解锁
	lc.l_type = F_UNLCK;
	if(fcntl(fd,F_SETLK,&lc) < 0){
		fprintf(stderr,"unlock error %s\n",strerror(errno));
		close(fd);
		exit(1);
	} 
	return 0;
}

