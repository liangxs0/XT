/*************************************************************************
    > File Name: src/ptread_exit.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月11日 星期三 11时07分50秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

struct foo{
	
	long int a,b,c,d;
};

struct foo g_foo;

void printfoo(const char* s,const struct foo *fp)
{
	printf("%s",s);
	printf("  structure at 0x%lx\n",(unsigned long)fp);
	printf("  \n");
	printf("  foo.a = %ld\n",fp->a);
	printf("  foo.b = %ld\n",fp->b);
	printf("  foo.c = %ld\n",fp->c);
	printf("  foo.d = %ld\n",fp->d);
}

void *thr_fn1(void* arg)
{
	g_foo.a = 1;
	g_foo.b = 2;
	g_foo.c = 3;
	g_foo.d = 4;
	// struct foo foo = {1,2,3,4};
	printfoo("thread 1:\n",&g_foo);
	pthread_exit((void*)&g_foo);
}
void *thr_fn2(void* arg)
{
	printf("thread 2 :ID is %lu\n",(unsigned long)pthread_self());
	pthread_exit((void*)0);
}
int main(int argc,char** argv)
{
	int err;
	pthread_t tid1,tid2;
	struct foo *fp = &g_foo;

	err = pthread_create(&tid1,NULL,thr_fn1,NULL);
	if(err != 0)
		fprintf(stderr,"thread 1 create faile %s\n",strerror(errno));
	sleep(1);
	printf("parent starting second thread\n");
	err = pthread_create(&tid2,NULL,thr_fn2,NULL);
	if(err != 0)
		fprintf(stderr,"thread 2 create faile %s\n",strerror(errno));
	sleep(1);
	printfoo("parent:\n",fp);
	return 0;
}



