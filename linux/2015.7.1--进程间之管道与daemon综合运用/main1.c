#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

//写有名管道
void writefifo()
{
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int fd = open("/home/zhangqi/helloworld/fifo1", O_WRONLY);
	if (fd == -1)
	{
		printf("file open error!%s\n", strerror(errno));
		return;
	}
	while (1)
	{	
		memset(buf, 0 ,sizeof(buf));
		scanf("%s", buf);
		write(fd, buf, sizeof(buf));
	}
	close(fd);
}


int main(int arg, char* args[])
{
	writefifo();
	return 0;
}
