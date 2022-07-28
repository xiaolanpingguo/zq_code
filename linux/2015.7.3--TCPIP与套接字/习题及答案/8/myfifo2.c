#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void *writefifo(void *arg) //写fifo1文件
{
	const char *sfifoname = "fifo1";

	int fd = open(sfifoname, O_WRONLY);
	if (fd == -1)
	{
		printf("open %s failed, %s\n", sfifoname, strerror(errno));
		return NULL;
	}
	char buf[128];

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(STDIN_FILENO, buf, sizeof(buf));//从键盘读取用户输入，
		write(fd, buf, strlen(buf));//将buf写入管道文件fifo2。
	}
	close(fd);
	return NULL;
}


void *readfifo(void *arg) //读取fifo2文件
{
	const char *sfifoname = "fifo2";

	int fd = open(sfifoname, O_RDONLY);
	if (fd == -1)
	{
		printf("open %s failed, %s\n", sfifoname, strerror(errno));
		return NULL;
	}

	int len = 0;
	char buf[128];

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		len = read(fd, buf, sizeof(buf));//read函数阻塞，一直到接收到数据就返回。
		if (len > 0)
		{
			printf("%s\n", buf);//将从fifo1管道读到的数据打印到屏幕
		} else
		{
			break;//如果read返回<=0，代表管道被关闭，循环退出.
		}
	}
	close(fd);
	return NULL;
}


int main(int arg, char *args[])
{
	pthread_t thr_d1, thr_d2;
	pthread_create(&thr_d1, NULL, readfifo, NULL);
	pthread_create(&thr_d2, NULL, writefifo, NULL);
	pthread_join(thr_d1, NULL);//主线程挂起，等待thr_d1退出
	pthread_join(thr_d1, NULL);//主线程挂起，等待thr_d2退出
	return 0;
}

