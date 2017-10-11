/*************************************************************************
    > File Name: src/ptread_join.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月11日 星期三 10时13分06秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

void* thr_fn1(void *arg)
{
	printf("thread 1 returning\n");
	return ((void*)1);
}
void* thr_fn2(void *arg)
{
	printf("thread 2 returning\n");
	pthread_exit((void*)2);
}
int main(int argc,char** argv)
{
	int err;
	pthread_t tid1,tid2;
	void* tret;
	err = pthread_create(&tid1,NULL,thr_fn1,NULL);
	if(err != 0)
		fprintf(stderr,"can't create thread 1%s\n",strerror(errno));
	err = pthread_join(tid1,&tret);
	if(err != 0)
		fprintf(stderr,"can`t join with thread 1%s\n",strerror(errno));
	printf("thread 1 exit code %ld\n",(long)tret);
	err = pthread_create(&tid2,NULL,thr_fn2,NULL);
	if(err != 0)
		fprintf(stderr,"can't create thread 2%s\n",strerror(errno));
	err = pthread_join(tid2,&tret);
	if(err != 0)
		fprintf(stderr,"can`t join with thraed 2%s\n",strerror(errno));
	printf("thread 2 exit code %ld\n",(long)tret);

	return 0;
}







