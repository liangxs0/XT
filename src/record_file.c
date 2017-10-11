/*************************************************************************
    > File Name: src/record_file.c
    > Author: L-Rmos
    > .....
    > Created Time: 2017年10月10日 星期二 19时58分16秒
 ************************************************************************/

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int type[7] = {0};
//判断是否是目录文件 并记录文件类型个数
int count_type(char *pathname)
{
	struct stat s;
	memset(&s,0,sizeof(s));
	//lstat获取文件属性保存在 s 结构体中
	if(lstat(pathname,&s) < 0){
		fprintf(stderr,"lseek error %s\n",strerror(errno));
		exit(1);
	}
	//7大文件类型
	if(S_ISDIR(s.st_mode)){
		type[1]++;//目录文件
		return 1;
	}else if(S_ISREG(s.st_mode)){
		type[0]++;//普通文件
	}else if(S_ISCHR(s.st_mode)){
		type[2]++;//字符设备文件
	}else if(S_ISBLK(s.st_mode)){
		type[3]++;//块设备文件
	}else if(S_ISSOCK(s.st_mode)){
		type[4]++;//网络设备（套接字）
	}else if(S_ISFIFO(s.st_mode)){
		type[5]++;//管道文件
	}else{
		type[6]++;//S_ISLNK 符号链接文件
	}
	return 0;
}
void count_file(char *dir)
{
	//0-file 1-dir 2-c 3-d 4-s 5-p 6-l
	if(count_type(dir) == 0){
		return;
	}
	DIR *dp = opendir(dir);
	if(dp == NULL){
		fprintf(stderr,"opendir error %s\n",strerror(errno));
		exit(1);
	}
	//进入到目录的操作
	if(chdir(dir) < 0){
		fprintf(stderr,"change dir %s\n",strerror(errno));
		exit(1);
	}
	struct dirent *ent = NULL;
	while(ent = readdir(dp) != NULL){
	if(strcmp(ent->d_name,".") == 0) continue;
		if(strcmp(ent->d_name,"..") == 0) continue;
		//判断是否是目录，再次统计
		count_file(ent->d_name);
	}
	chdir("..");
	closedir(dp);
}

int main(int argc,char **argv)
{
	if(argc < 2){
		fprintf(stderr,"usage:%s\n",strerror(errno));
		exit(1);
	}
	count_file(argv[1]);
	int i = 0;
	for(;i < 7;i++){
		printf("%d\n",type[i]);
	}
	return 0;
}


