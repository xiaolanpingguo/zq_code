#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888

void main()
{
	WORD wVer = MAKEWORD(SOCK_VERH, SOCK_VERL);
	WSADATA wd;
	int err = ::WSAStartup(wVer, &wd);
	if (0 != err)
	{
		cout << "无法初始化Socket2系统环境!" << endl;
		return;
	}
	if (LOBYTE(wd.wVersion) != SOCK_VERH ||
		HIBYTE(wd.wVersion) != SOCK_VERL)
	{
		cout << "无法初始化"<<SOCK_VERH<<"."<<SOCK_VERL<<"版本的Socket环境!" << endl;
		WSACleanup();
		return;
	}
	//监听套接字
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	bind(sListen, (sockaddr*)&si, sizeof(si));

	listen(sListen, 8);

	cout << "服务器已经启动！正在监听。。。" << endl;

	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET sClient = accept(sListen, (sockaddr*)&ci, &ci_len);
	cout << inet_ntoa(ci.sin_addr) << "连接到服务器,套接字为：" << sClient << endl;

	while (1)
	{
		int sum;
		int r = recv(sClient, (char*)&sum, 4, 0);
		if (0 == r || SOCKET_ERROR == r)
			break;
		char* p = new char[sum];
		int bytes = 0;

		while (bytes < sum)
		{
			r = recv(sClient, p + bytes, sum - bytes, 0);
			if (0 == r || SOCKET_ERROR == r)
				exit(0);
			else
				bytes += r;
		}

		FILE* pf = NULL;
		fopen_s(&pf, p, "wb");
		int fn_len = strlen(p);
		fwrite(p + fn_len + 1, sum - (fn_len + 1), 1, pf);
		fclose(pf);
		delete[] p;
		cout << "已成功接收文件！" << endl;
	}
	closesocket(sListen);
	closesocket(sClient);
	WSACleanup();
	system("pause");
}

