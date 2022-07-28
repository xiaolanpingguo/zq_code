/*
 ============================================================================
 Name        : sock.c
 Author      : zhujy
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int arg, char *args[])
{
	if (arg < 2)
	{
		return -1;
	}

	int port = atoi(args[1]);
	int st = socket(AF_INET, SOCK_STREAM, 0);//初始化socket


	int on = 1;
	if (setsockopt(st, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
	{
		printf("setsockopt failed %s\n", strerror(errno));
		return EXIT_FAILURE;
	}


	struct sockaddr_in addr;//定义一个IP地址结构
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;//将addr结构的属性定位为TCP/IP地址
	addr.sin_port = htons(port);//将本地字节顺序转化为网络字节顺序。
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY代表这个server上所有的地址

	//将IP与server程序绑定
	if (bind(st, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		printf("bind failed %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	//server端开始listen，
	if (listen(st, 20) == -1)
	{
		printf("listen failed %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	char s[1024];
	int client_st = 0;//client端socket
	//socklen_t len = 0;
	struct sockaddr_in client_addr;//表示client端的IP地址
	//void *p = &client_addr;
	int i;
	for (i = 0; i < 5; i++)
	{
		memset(&client_addr, 0, sizeof(client_addr));
		socklen_t len = sizeof(client_addr);
		//accept会阻塞，直到有客户端连接过来，accept返回client的socket描述符
		client_st = accept(st, (struct sockaddr *)&client_addr , &len);
		if (client_st == -1)
		{
			printf("accept failed %s\n", strerror(errno));
			return EXIT_FAILURE;
		}

		printf("accept by %s\n", inet_ntoa(client_addr.sin_addr));
		while(1)
		{
			memset(s, 0, sizeof(s));
			int rc = recv(client_st, s, sizeof(s), 0);//recv是阻塞调用，
			if (rc > 0)//接收来自client的消息
			{
				printf("revc is %s\n", s);
				memset(s, 0, sizeof(s));
				read(STDIN_FILENO, s, sizeof(s));
				send(client_st, s, strlen(s), 0);
			}else
			{
				if (rc == 0)
				{
					printf("client socket closed\n");
				}else
					printf("recv failed %s\n", strerror(errno));
				break;
			}
		}
		close(client_st);//关闭client端socket
	}
	close(st);//关闭server端listen的socket
	return EXIT_SUCCESS;
}
