#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	WSAStartup(0x0101, &wd);
	SOCKET s_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	char server_ip[256];
	std::cout<<"请输入服务器ip地址：";
	std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip);
	if (SOCKET_ERROR == connect(s_server, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"无法连接服务器，";
		system("pause");
		closesocket(s_server);
		WSACleanup();
		return;
	}
	std::cout<<"成功连接服务器！"<<std::endl;

	//业务循环
	while (1)
	{
		//输入要发送的文件名称
		std::cout<<"请输入要发送的文件路径：";
		char filename[256];
		std::cin>>filename;
		FILE* pf = 0;
		fopen_s(&pf, filename, "rb");
		if (!pf)
		{
			std::cout<<"无法打开指定文件，";
			system("pause");
			continue;
		}
		fseek(pf, 0, SEEK_END);
		int fs = ftell(pf);
		rewind(pf);
		char* fd = (char*)malloc(fs);
		fread(fd, 1, fs, pf);
		fclose(pf);

		//将长度发送到服务器，一般来说
		//发送4字节这样较小的数据是没有
		//问题，基本上都可以发送成功，但
		//是如果要发送较大的数据，我们还
		//是需要检查send的返回值以确定发
		//送的实际字节数
		send(s_server, (const char*)&fs, sizeof(int), 0);

		//发送文件内容
		int send_byte = 0; //已发送字节数
		while (send_byte < fs)
		{
			//send返回真正发送的数据字节数
			int r = send(
				s_server,
				fd + send_byte,
				(fs - send_byte) > 8192 ? 8192 : fs - send_byte,
				0);
			send_byte += r;
			std::cout<<"当前已经发送了"<<send_byte<<"个字节";
		}

		free(fd);
	}

	closesocket(s_server);
	WSACleanup();

	system("pause");
}