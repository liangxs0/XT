/*************************************************************************
    > File Name: src/ls_l.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月11日 星期三 19时05分40秒
 ************************************************************************/

#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

void ls_R(char *filename)
{
	printf("%s\n",realpath(filename,NULL));
	//判断是目录还是文件
	struct stat st;
	memset(&st,0,sizeof(st));
	if(lstat(filename,&st) < 0){
		fprintf(stderr,"lstat,%s\n",strerror(errno));
		exit(1);
	}
	if(!S_ISDIR(st.st_mode))
		return ;
	DIR* dp = opendir(filename);
	if(dp == NULL){
		fprintf(stderr,"opdir error:%s\n",strerror(errno));
		return ;
	}
	chdir(filename);
	printf("a");
	struct dirent *dtp = NULL;
	while(dtp = readdir(dp) != NULL){
		//跳过.和..的处理
		if(!strcmp(dtp->d_name,".") || !strcmp(dtp->d_name,".."))
			continue;
		ls_R(dtp->d_name);//递归
	}
	chdir("..");
	closedir(dp);
}


int main (int argc,char** argv)
{
	if(argc < 2){
		fprintf(stderr,"%s[dirname]\n",strerror(errno));
		exit(1);
	}
	ls_R(argv[1]);

	return 0;
	
}









