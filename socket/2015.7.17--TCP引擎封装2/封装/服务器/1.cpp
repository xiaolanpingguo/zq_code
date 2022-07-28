#include <iostream>
#include "TcpServer.h"

void main()
{
	CTcpServer ts;

	ts.Init(12345, 256, 10, 5);

	//std::vector<SOCEKT> v;

	while (ts.Continue())
	{
		ts.Run();

		_SNET_EVENT ne;
		while (ts.GetNetEvent(&ne))
		{
			//处理网络事件
			char ip[16];

			switch (ne.type)
			{
			case _SNE_CONNECTED:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"连接到服务器"<<std::endl;
					//v.push_back(ne.s);
					break;
				}
			case _SNE_DATA:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"连接到服务器"<<std::endl;
					break;
				}
			case _SNE_DISCONNECTED_C:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"断开（客户端主动）"<<std::endl;
					break;
				}
			case _SNE_DISCONNECTED_S:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"断开（服务器主动)"<<std::endl;
					break;
				}
			case _SNE_DISCONNECTED_E:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"断开（错误）"<<std::endl;
					break;
				}
			}

			ts.ReleaseNetEvent(&ne);
		}

		if (GetAsyncKeyState(VK_ESCAPE))
			ts.Stop();
	}

	ts.End();

	system("pause");
}