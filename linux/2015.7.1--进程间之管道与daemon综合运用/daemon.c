#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

//信号回调函数
int signal1(int signo, void(*func)(int))
{
	//定义两个sigaction 结构指针
	struct sigaction act, oact;
	//指向了回调函数
	act.sa_handler = func;
	//用这个函数把该值清空
	sigemptyset(&act.sa_mask);
	//初始化这个结构
	act.sa_flags = 0;
	//返回之前的状态
	return sigaction(signo, &act, &oact);
}

//守护进程
void setdaemon()
{
	pid_t pid,sid;
	pid = fork();
	if (pid == -1)
	{
		printf("fork error!%s\n",strerror(errno) );
		exit(EXIT_FAILURE);
	}
	if ((sid = setsid()) < 0)
	{
		printf("fork error!%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
		exit(EXIT_SUCCESS);
}

//监听管道
void listenfifo()
{
	const char* sfifoname = "fifo1";
	int len = 0;
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int fd = open(sfifoname, O_RDONLY);
	if (fd == -1)
	{
		printf("file open error!%s\n", strerror(errno));
		return;
	}
	len = read(fd, buf, sizeof(buf));
	if (len > 0)
	{
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		close(STDOUT_FILENO);
		open(buf, O_WRONLY);
	}
	close(fd);
}

//捕捉信号
void catch_Signal(int sign)
{
	switch (sign)
	{
	case SIGINT:
		listenfifo();
		break;
	}
}

int main(int arg, char* args[])
{
	//把进程设为daemon状态
	setdaemon();
	//捕捉SIGINT信号
	signal1(SIGINT, catch_Signal);
	while (1)
	{
		puts("hello world!");
		sleep(1);
	}
	return 0;
}