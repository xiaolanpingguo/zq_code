//流式传输协议，一端一次性发送多少数据，另一端不一定一次可以
//收这么多数据，比如A、B连接成功，A一次发送了1000个字节到B，但
//是B有可能一次收不了1000个字节，有可能是先收到200个字节，下一
//次再调用recv的时候再受到800个字节，还有可能是A一次发送了100个
//字节，然后很快又发送了200个字节，那么B有可能一次收到300个字节

//int send(SOCKET s, const char* buf, 100, int flags);
//如果没有错误发生，那么send返回本次发送的字节数，这个数字
//有可能是小于我们填入的形参len的，当有错误发生的时候，本
//函数的返回值是SOCKET_ERROR

//int recv(SOCKET s, char* buf, int len, int flags);
//如果没有错误发生，返回值就是本次收到的总字节数，如果当前
//连接被优雅断开，那么返回值是0，若发生错误则返回值是
//SOCKET_ERROR，注意本函数的len是告知操作系统本次接收
//数据的上限，比如len填写为4，而此时已经到来了9个字节
//，那么本次也只会得到这9个字节中的前4个，后面5个是得
//不到的，但是可以下一次再调用recv得到后面的5个字节

#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	bind(sListen, (sockaddr*)&si, sizeof(si));

	listen(sListen, 8);

	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET sClient = accept(sListen, (sockaddr*)&ci, &ci_len);

	char* c_name = inet_ntoa(ci.sin_addr);
	std::cout<<c_name<<"连接到服务器"<<std::endl;

	//7）业务循环
	while (1)
	{
		int all_bytes;
		int r = recv(sClient, (char*)&all_bytes, 4, 0);
		if (r == 0 || r == SOCKET_ERROR)
			break;

		//接收文件循环
		int cur_bytes = 0;
		char* p = new char[all_bytes];
		while (cur_bytes < all_bytes)
		{
			r = recv(sClient, p + cur_bytes, all_bytes - cur_bytes, 0);
			if (r == 0 || r == SOCKET_ERROR)
				exit(0);
			else
				cur_bytes += r;
		}

		FILE* pf = 0; 
		fopen_s(&pf, p, "wb");
		int fn_len = strlen(p);
		fwrite(p + fn_len + 1, all_bytes - (fn_len + 1), 1, pf);
		fclose(pf);

		delete [] p;
	}

	closesocket(sClient);
	closesocket(sListen);
	WSACleanup();

	system("pause");
}