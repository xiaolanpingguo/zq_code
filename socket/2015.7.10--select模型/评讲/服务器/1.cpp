#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);
	sockaddr_in si_c;
	int len = sizeof(si_c);
	SOCKET s_client = accept(s_listen, (sockaddr*)&si_c, &len);
	std::cout<<inet_ntoa(si_c.sin_addr)<<"连接到服务器"<<std::endl;

	int fn = 0;

	//业务循环
	while (1)
	{
		//得到文件长度
		int fs;
		recv(s_client, (char*)&fs, sizeof(int), 0);

		//接收文件数据
		char* fd = (char*)malloc(fs);
		int recv_byte = 0;
		while (recv_byte < fs)
		{
			int r = recv(s_client, fd + recv_byte, fs - recv_byte, 0);
			recv_byte += r;
		}

		//写入文件
		char filename[32];
		sprintf_s(filename, 32, "%d", ++fn);
		FILE* pf = 0;
		fopen_s(&pf, filename, "wb");
		fwrite(fd, 1, fs, pf);
		fclose(pf);
		free(fd);
	}

	//关闭套接字
	closesocket(s_client);
	closesocket(s_listen);

	//关闭网络环境
	WSACleanup();

	system("pause");
}