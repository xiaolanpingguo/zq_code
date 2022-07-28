#include "TcpServer.h"
#include <MSTcpIP.h>
#pragma comment(lib, "Ws2_32.lib")

#define _CS_CONNECTED 0 //连接状态
#define _CS_PREPARE_DISCONNECT 1 //服务器准备主动断开状态
#define _CS_BE_DISCONNECTED 2 //服务器被动断开状态
#define _CS_WAIT_FINISH 3 //服务器等待结束状态

int CTcpServer::_AcceptClient()
{
	if (!m_Continue || m_Client.Length() == m_MaxClient)
		return 0;

	//接收客户端连接
	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET c = accept(m_Listen, (sockaddr*)&ci, &ci_len);

	//发送错误
	if (INVALID_SOCKET == c)
	{
		if (WSAEWOULDBLOCK == WSAGetLastError())
			return 1;
		else
			return -1;
	}
	//正常连接
	else
	{
		//设置心跳包
		BOOL b = TRUE;
		setsockopt(c, SOL_SOCKET, SO_KEEPALIVE, (const char*)&b, sizeof(b));
		tcp_keepalive tk = {1, m_StartKAYime, m_IntervalKAYime};
		DWORD w;
		WSAIoctl(c, SIO_KEEPALIVE_VALS, &tk, sizeof(tk), 0, 0, &w, 0, 0);

		//装入客户映射
		CLIENT client;
		client.state = _CS_CONNECTED;
		client.ip = ci.sin_addr.S_un.S_addr;
		client.rd.allsize = 0;
		client.rd.allsize_bytes = 0;
		client.rd.data = 0;
		client.rd.recvsize = 0;
		m_Client.Insert(c, client);

		//网络事件入队列
		_TS_NET_EVENT tne = {_TSNE_CONNECT, c, client.ip};
		m_TSNetEvent.Enter(tne);

		return 2;
	}
}

void CTcpServer::_OperateData(const char* buf, int r, SOCKET s, unsigned long ip, _RECV_DATA* rd)
{
	//当前分析下标
	int cur_i = 0;
	while (cur_i < r)
	{
		//当前接收长度部分
		if (rd->allsize_bytes < 4)
		{
			//当前不能收完长度部分
			if (4 - rd->allsize_bytes > r - cur_i)
			{
				//将字节拷贝到数据总长中
				memcpy(&rd->allsize, buf + cur_i, r - cur_i);

				//数字总长的有效字节数递增
				rd->allsize_bytes += r - cur_i;

				//当前分析下标递增
				cur_i += r - cur_i;
			}
			//当前可以收完长度部分
			else
			{
				//将字节拷贝到数据总长中
				memcpy(&rd->allsize, buf + cur_i, 4 - rd->allsize_bytes);

				//当前分析下标递增
				cur_i += 4 - rd->allsize_bytes;

				//数字总长的有效字节数设置为4
				rd->allsize_bytes = 4;

				//开辟堆内存
				rd->data = (char*)m_MP.Allocate(rd->allsize);
			}
		}
		//当前接收数据部分
		else
		{
			//当前不能接收完数据
			if (rd->allsize - rd->recvsize > r - cur_i)
			{
				//拷贝剩下的所有字节到数据中
				memcpy(rd->data + rd->recvsize, buf + cur_i, r - cur_i);

				//当前已经接收的数据长度递增
				rd->recvsize += r - cur_i;

				//当前分析下标递增
				cur_i += r - cur_i;
			}
			else
			{
				//拷贝当前完整包需要的字节到数据中
				memcpy(rd->data + rd->recvsize, buf + cur_i, rd->allsize - rd->recvsize);

				//当前分析下标递增
				cur_i += rd->allsize - rd->recvsize;

				//设置收数据事件
				_TS_NET_EVENT tne = {_TSNE_DATA, s, ip, rd->data, rd->allsize};
				m_TSNetEvent.Enter(tne);

				//清空接收
				rd->allsize = 0;
				rd->allsize_bytes = 0;
				rd->data = 0;
				rd->recvsize = 0;
			}
		}
	}
}

int CTcpServer::_RecvData()
{
	const int len = 1024 * 64;
	char buf[len];

	for (int i = 0; i < m_Client.Length(); ++i)
	{
		//如果不是被动断开状态那么对套接字进行接收数据
		if (m_Client.At(i)->data.state != _CS_BE_DISCONNECTED)
		{
			//接收数据
			int r = recv(m_Client.At(i)->key, buf, len, 0);

			//出错
			if (r == SOCKET_ERROR)
			{
				//真的出错了
				if (WSAEWOULDBLOCK != WSAGetLastError())
				{
					//因为错误删除当前客户端及其一切相关资源
					_Close(i, m_Client.At(i)->key, &m_Client.At(i)->data, _TSNE_E_DISCONNECT);
					--i;
				}
			}
			//优雅断开
			else if (r == 0)
			{
				//服务器等待结束状态
				if (m_Client.At(i)->data.state == _CS_WAIT_FINISH)
				{
					//因为服务器主动断开删除当前客户端及其一切相关资源
					_Close(i, m_Client.At(i)->key, &m_Client.At(i)->data, _TSNE_S_DISCONNECT);
					--i;
				}
				//连接状态或服务器准备主动断开状态
				else
					m_Client.At(i)->data.state = _CS_BE_DISCONNECTED;
			}
			//收到数据了
			else
				_OperateData(buf, r, m_Client.At(i)->key, m_Client.At(i)->data.ip, &m_Client.At(i)->data.rd);
		}
	}

	return 1;
}

int CTcpServer::_SendData()
{
	for (int i = 0; i < m_Client.Length(); ++i)
	{
		//如果不是等待结束状态那么对套接字进行发送数据
		if (m_Client.At(i)->data.state != _CS_WAIT_FINISH)
		{
			//跳出下面循环时候的标记
			//0表示本客户的所有数据正常发送完毕
			//1表示暂时不能发送
			//2表示出错
			int flag1 = 0;

			//发送队头数据
			_SEND_DATA sd;
			while (m_Client.At(i)->data.sd_queue.Length() > 0)
			{
				//得到队头数据
				m_Client.At(i)->data.sd_queue.GetHead(&sd);

				//跳出下面循环时候的标记
				//0表示本数据包正常发送完毕
				//1表示暂时不能发送
				//2表示出错
				int flag2 = 0;

				//循环发送队头数据
				while (sd.sendsize < sd.allsize)
				{
					//发送
					int r = send(
						m_Client.At(i)->key,
						sd.data + sd.sendsize,
						sd.allsize - sd.sendsize,
						0);

					//出错
					if (SOCKET_ERROR == r)
					{
						//当前暂不能发
						if (WSAEWOULDBLOCK == WSAGetLastError())
							flag2 = 1;
						//当前出错
						else
							flag2 = 2;
						break;
					}
					else
						sd.sendsize += r;
				}

				if (flag2 == 0)
				{
					m_MP.Free(sd.data);
					m_Client.At(i)->data.sd_queue.Quit(&sd);
				}
				else
				{
					flag1 = flag2;
					break;
				}
			}

			//根据状态值进行处理

			//当前客户没有待发送的数据了
			if (flag1 == 0)
			{
				switch (m_Client.At(i)->data.state)
				{
				case _CS_CONNECTED: break;
				case _CS_PREPARE_DISCONNECT:
					{
						shutdown(m_Client.At(i)->key, SD_SEND);
						m_Client.At(i)->data.state = _CS_WAIT_FINISH;
						break;
					}
				case _CS_BE_DISCONNECTED:
					{
						shutdown(m_Client.At(i)->key, SD_SEND);
						//因为客户端主动断开删除当前客户端及其一切相关资源
						_Close(i, m_Client.At(i)->key, &m_Client.At(i)->data, _TSNE_C_DISCONNECT);
						--i;
					}
				}
			}
			//暂时不能发的话就换下一个人
			else if (flag1 == 1)
				;
			//出错那么删除该客户
			else
			{
				//因为错误删除当前客户端及其一切相关资源
				_Close(i, m_Client.At(i)->key, &m_Client.At(i)->data, _TSNE_E_DISCONNECT);
				--i;
			}
		}
	}

	return 1;
}

void CTcpServer::_Close(int index, SOCKET s, CLIENT* c, int type)
{
	//删除该客户的发送数据
	while (c->sd_queue.Length() > 0)
	{
		_SEND_DATA sd;
		c->sd_queue.Quit(&sd);
		m_MP.Free(sd.data);
	}

	//删除该客户的接收数据
	if (c->rd.data)
		m_MP.Free(c->rd.data);

	//关闭套接字
	closesocket(s);

	//投递网络事件
	_TS_NET_EVENT tne = {type, s, c->ip};
	m_TSNetEvent.Enter(tne);

	//将客户从客户映射中删除
	m_Client.Erase(index);
}

bool CTcpServer::Init(unsigned short port,
					  int max_client,
					  int start_ka_time,
					  int interval_ka_time)
{
	//参数检查
	if (port <= 1024 || max_client < 1 || start_ka_time < 1 || start_ka_time < 1)
		return false;

	//得到传入的参数
	m_Port = port;
	m_MaxClient = max_client;
	m_StartKAYime = start_ka_time * 1000;
	m_IntervalKAYime = interval_ka_time * 1000;

	//设置循环标志为真
	m_Continue = true;

	//启动网络环境
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);

	//创建监听套接字并设置为非阻塞模式
	m_Listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	unsigned long nonblocking = 1;
	ioctlsocket(m_Listen, FIONBIO, &nonblocking);

	//填充地址信息结构体
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(m_Port);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	//绑定监听套接字与地址信息结构体
	bind(m_Listen, (sockaddr*)&si, sizeof(si));

	//设置监听模式
	listen(m_Listen, 8);

	return true;
}

void CTcpServer::Stop()
{
	for (int i = 0; i < m_Client.Length(); ++i)
	{
		if (m_Client.At(i)->data.state == _CS_CONNECTED)
			m_Client.At(i)->data.state = _CS_PREPARE_DISCONNECT;
	}
	m_Continue = false;
}

bool CTcpServer::Continue()
{
	return m_Continue || m_Client.Length() > 0;
}

void CTcpServer::End()
{
	closesocket(m_Listen);
	WSACleanup();
}

void CTcpServer::Run()
{
	_AcceptClient();
	_RecvData();
	_SendData();
}

bool CTcpServer::GetTSNetEvent(_TS_NET_EVENT* ptne)
{
	return m_TSNetEvent.Quit(ptne);
}

void CTcpServer::ReleaseTSNetEvent(_TS_NET_EVENT* ptne)
{
	if (_TSNE_DATA == ptne->type)
		m_MP.Free(ptne->data);
}

int CTcpServer::Disconnect(SOCKET s)
{
	CMap<SOCKET, CLIENT>::PAIR* pair = m_Client.Find(s);
	if (0 == pair)
		return 0;
	else
	{
		if (pair->data.state != _CS_CONNECTED)
			return -1;
		else
		{
			pair->data.state = _CS_PREPARE_DISCONNECT;
			return 1;
		}
	}
}

int CTcpServer::SendData(SOCKET s, const char* data, int len)
{
	CMap<SOCKET, CLIENT>::PAIR* pair = m_Client.Find(s);
	if (0 == pair)
		return 0;
	else
	{
		if (pair->data.state != _CS_CONNECTED)
			return -1;
		else
		{
			//准备发送数据
			_SEND_DATA sd;
			sd.allsize = sizeof(int) + len;
			sd.data = (char*)m_MP.Allocate(sd.allsize);
			*((int*)sd.data) = len;
			memcpy(sd.data + sizeof(int), data, len);
			sd.sendsize = 0;

			//发送数据入队列
			pair->data.sd_queue.Enter(sd);

			return 1;
		}
	}
}

void CTcpServer::GetStrIP(unsigned long ul_ip, char* str_ip)
{
	in_addr ia;
	ia.S_un.S_addr = ul_ip;
	char* str = inet_ntoa(ia);
	memcpy(str_ip, str, strlen(str) + 1);
}

float CTcpServer::GetUseMemoryMB()
{
	return m_MP.GetUseMemory();
}