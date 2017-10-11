/*************************************************************************
    > File Name: src/ptread_creat.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月11日 星期三 09时40分54秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <signal.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char* s)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long)pid,\
							(unsigned long)tid,(unsigned long)tid);
}
void* thr_fn(void* arg)
{
	printids("new thread:");
	return (void*)0;
}
int main(int argc,char** argv)
{
	int err;
	err = pthread_create(&ntid,NULL,thr_fn,NULL);
	if(err != 0)
		fprintf(stderr,"can't create thread %s\n",strerror(errno));
	printids("main thread");
	sleep(1);
	return 0;
}













