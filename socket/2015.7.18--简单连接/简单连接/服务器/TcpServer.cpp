#include "TcpServer.h"
#include <MSTcpIP.h>
#pragma comment(lib, "Ws2_32.lib")

#define _CS_CONNECTED			0 //客户端状态：连接
#define _CS_PREPARE_DISCONNECT	1 //客户端状态：准备主动断开
#define _CS_BE_DISCONNECTED		2 //客户端状态：被动断开
#define _CS_WAIT_FINISH			3 //客户端状态：等待对方结束

bool CTcpServer::_Accept()
{
	//必须持续标志为真且当前最客户端数量未到最大连接数
	if (m_Continue && m_Client.Size() < m_MaxClient)
	{
		sockaddr_in ci;
		int ci_len = sizeof(ci);
		SOCKET s = accept(m_Listen, (sockaddr*)&ci, &ci_len);
		if (s == INVALID_SOCKET)
		{
			//发生真正的错误
			if (WSAGetLastError() != WSAEWOULDBLOCK)
				return false;
		}
		else
		{
			//初始化客户数据
			_CLIENT client;
			client.state = _CS_CONNECTED;
			client.ip = ci.sin_addr.S_un.S_addr;
			client.rd.Clear();

			//设置心跳包及其时间
			BOOL b = TRUE;
			setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (const char*)&b, sizeof(b));
			DWORD dw;
			tcp_keepalive tka = {1, m_BeginKA, m_IntervalKA};
			WSAIoctl(s, SIO_KEEPALIVE_VALS, &tka, sizeof(tka), 0, 0, &dw, 0, 0);

			//装入客户表
			m_Client.Insert(s, client);

			//投递连接事件
			_SNET_EVENT ne = {_SNE_CONNECTED, s, client.ip, 0, 0};
			m_SNetEvent.Push(ne);
		}
	}

	return true;
}

void CTcpServer::_Send()
{
	//循环每个玩家进行发送
	for (int i = 0; i < m_Client.Size(); ++i)
	{
		CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.At(i);

		//当客户状态不是等待对方结束状态的情况下才可以发送数据
		if (pair->data.state != _CS_WAIT_FINISH)
		{
			//退出下面的循环时的情况
			//0：表示没有要发送的数据了
			//1：表示暂时不能发送
			//2：表示发送错误
			int quit_state = 0;

			//当队列不为空
			while (!pair->data.sd_queue.Empty())
			{
				//得到要发送的数据
				_SEND_DATA sd;
				pair->data.sd_queue.Front(&sd);

				//循环发送
				while (sd.send_size < sd.all_size)
				{
					int r = send(pair->key, sd.data + sd.send_size, sd.all_size - sd.send_size, 0);
					if (r == SOCKET_ERROR)
					{
						//真的出错
						if (WSAEWOULDBLOCK != WSAGetLastError())
							quit_state = 2;
						else
							quit_state = 1;
						break;
					}
					else
						sd.send_size += r;
				}

				//根据退出上面循环的状态进行讨论
				if (0 == quit_state)
				{
					m_MP.Free(sd.data);
					pair->data.sd_queue.Pop();
				}
				else
					break;
			}

			switch (quit_state)
			{
			case 0: //没有要发送的数据了
				{
					if (pair->data.state == _CS_PREPARE_DISCONNECT)
					{
						shutdown(pair->key, SD_SEND);
						pair->data.state = _CS_WAIT_FINISH;
					}
					else if (pair->data.state == _CS_BE_DISCONNECTED)
					{
						shutdown(pair->key, SD_SEND);
						_CloseClient(pair->key, &pair->data, _SNE_DISCONNECTED_C);
						--i;
					}
					break;
				}
			case 1: //暂时不能发送
				{
					break;
				}
			case 2: //出错发送
				{
					_CloseClient(pair->key, &pair->data, _SNE_DISCONNECTED_E);
					--i;
					break;
				}
			}
		}
	}
}

void CTcpServer::_Recv()
{
	//接收数据的缓冲
	char buf[65536];

	//循环每个玩家进行接收
	for (int i = 0; i < m_Client.Size(); ++i)
	{
		//得到当前玩家信息
		CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.At(i);

		//若玩家状态不为被动断开的时候可以进行接收
		if (pair->data.state != _CS_BE_DISCONNECTED)
		{
			//接收数据
			int r = recv(pair->key, buf, 65536, 0);

			//分情况讨论
			if (r == SOCKET_ERROR)
			{
				//真的出错
				if (WSAEWOULDBLOCK != WSAGetLastError())
				{
					_CloseClient(pair->key, &pair->data, _SNE_DISCONNECTED_E);
					--i;
				}
			}
			//对方调用了shutdown
			else if (r == 0)
			{
				//如果状态是连接状态和准备主动断开状态，则只需转换状态到被动断开
				if (pair->data.state == _CS_CONNECTED || pair->data.state == _CS_PREPARE_DISCONNECT)
					pair->data.state = _CS_BE_DISCONNECTED;
				//如果状态是等待对方结束状态，则关闭套接字
				else
				{
					_CloseClient(pair->key, &pair->data, _SNE_DISCONNECTED_S);
					--i;
				}
			}
			else
				_RecvClient(buf, r, pair->key, &pair->data);
		}
	}
}

void CTcpServer::_RecvClient(char* buf, int r, SOCKET s, _CLIENT* c)
{
	//初始化分析的位置
	int cur = 0;

	//循环分析所有数据
	while (cur < r)
	{
		//当前没有收完长度
		if (c->rd.len_valid_bytes < 4)
		{
			//当前不能收完长度
			if (4 - c->rd.len_valid_bytes > r - cur)
			{
				//拷贝可以收的长度字节到总长度中
				memcpy(
					(char*)&c->rd.all_len + c->rd.len_valid_bytes,
					buf + cur,
					r - cur);

				//长度的有效字节数更新
				c->rd.len_valid_bytes += r - cur;

				//分析的位置递增（将导致退出循环分析所有数据）
				cur += r - cur;
			}
			//当前可以收完长度
			else
			{
				//拷贝可以收的长度字节到总长度中
				memcpy(
					(char*)&c->rd.all_len + c->rd.len_valid_bytes,
					buf + cur,
					4 - c->rd.len_valid_bytes);

				//分析的位置递增
				cur += 4 - c->rd.len_valid_bytes;

				//长度的有效字节数更新
				c->rd.len_valid_bytes = 4;

				//开辟接收数据的内存
				c->rd.data = (char*)m_MP.Allocate(c->rd.all_len);
			}
		}
		//当前收完了长度应该收数据
		else
		{
			//当前不能收完数据
			if (c->rd.all_len - c->rd.recv_len > r - cur)
			{
				//拷贝可以收的数据到总数据中
				memcpy(
					c->rd.data + c->rd.recv_len,
					buf + cur,
					r - cur);

				//已经接收的数据更新
				c->rd.recv_len += r - cur;

				//分析的位置递增（将导致退出循环分析所有数据）
				cur += r - cur;
			}
			//当前可以收完数据
			else
			{
				//拷贝可以收的数据到总数据中
				memcpy(
					c->rd.data + c->rd.recv_len,
					buf + cur,
					c->rd.all_len - c->rd.recv_len);

				//分析的位置递增
				cur += c->rd.all_len - c->rd.recv_len;

				//完成了一个包的分析投递接收数据网络事件
				_SNET_EVENT ne = {_SNE_DATA, s, c->ip, c->rd.data, c->rd.all_len};
				m_SNetEvent.Push(ne);

				//清空
				c->rd.Clear();
			}
		}
	}
}

void CTcpServer::_CloseClient(SOCKET s, _CLIENT* c, int t)
{
	//释放接收数据
	if (c->rd.data)
		m_MP.Free(c->rd.data);

	//释放发送数据
	while (!c->sd_queue.Empty())
	{
		_SEND_DATA sd;
		c->sd_queue.Front(&sd);
		c->sd_queue.Pop();
		m_MP.Free(sd.data);
	}

	//关闭套接字
	closesocket(s);

	//从客户表中删除
	m_Client.Erase(s);

	//投递事件
	_SNET_EVENT ne = {t, s, c->ip, 0, 0};
	m_SNetEvent.Push(ne);
}

CTcpServer::CTcpServer()
:
m_Listen(INVALID_SOCKET),
m_MaxClient(0),
m_BeginKA(0),
m_IntervalKA(0),
m_Continue(false)
{}

CTcpServer::~CTcpServer()
{}

bool CTcpServer::Init(unsigned short port,
					  int maxclient,
					  int beginka,
					  int intervalka)
{
	//参数检查
	if (port < _MIN_PORT || maxclient < 1 || beginka < 1 || intervalka < 1)
		return false;

	//得到参数
	m_MaxClient = maxclient;
	m_BeginKA = beginka * 1000;
	m_IntervalKA = intervalka * 1000;

	//启动网络环境
	WSADATA wd;
	WSAStartup(0x0101, &wd);

	//创建监听套接字并设置为非阻塞模式
	m_Listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(m_Listen, FIONBIO, &no_blocking);

	//填充地址信息结构体
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	//绑定套接字和地址信息结构体
	bind(m_Listen, (sockaddr*)&si, sizeof(si));

	//设置套接字为监听模式
	listen(m_Listen, 8);

	//设置持续标志为真
	m_Continue = true;

	return true;
}

void CTcpServer::Run()
{
	_Accept();
	_Send();
	_Recv();
}

void CTcpServer::Stop()
{
	//设置持续标志为假
	m_Continue = false;

	//对所有已经连接的客户进行优雅断开
	for (int i = 0; i < m_Client.Size(); ++i)
	{
		CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.At(i);
		if (pair->data.state == _CS_CONNECTED)
			pair->data.state = _CS_PREPARE_DISCONNECT;
	}
}

bool CTcpServer::Continue()
{
	//必须调用了Stop并且没有连接的玩家了才返回假
	return m_Continue || m_Client.Size() > 0;
}

void CTcpServer::End()
{
	closesocket(m_Listen);
	WSACleanup();
}

bool CTcpServer::GetNetEvent(_SNET_EVENT* ne)
{
	if (!m_SNetEvent.Empty())
	{
		m_SNetEvent.Front(ne);
		m_SNetEvent.Pop();
		return true;
	}
	else
		return false;
}

void CTcpServer::ReleaseNetEvent(_SNET_EVENT* ne)
{
	if (ne->type == _SNE_DATA)
		m_MP.Free(ne->data);
}

bool CTcpServer::SendData(SOCKET s, const void* data, int len)
{
	CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.Find(s);

	//首先套接字有效，且状态必须为连接状态，最后数据也必须有效
	if (pair && pair->data.state == _CS_CONNECTED && data && len > 0)
	{
		_SEND_DATA _send_data;

		//填充发送结构体对象
		_send_data.all_size = sizeof(int) + len;
		_send_data.data = (char*)m_MP.Allocate(_send_data.all_size);
		*((int*)_send_data.data) = len;
		memcpy(_send_data.data + sizeof(int), data, len);
		_send_data.send_size = 0;

		//装入发送队列
		pair->data.sd_queue.Push(_send_data);

		return true;
	}
	else
		return false;
}

bool CTcpServer::Disconnect(SOCKET s)
{
	CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.Find(s);

	//首先套接字有效，且状态必须为连接状态
	if (pair && pair->data.state == _CS_CONNECTED)
	{
		pair->data.state = _CS_PREPARE_DISCONNECT;
		return true;
	}
	else
		return false;
}

char* CTcpServer::ulong_str(unsigned long ip, char* buf)
{
	in_addr ia;
	ia.S_un.S_addr = ip;
	char* p = inet_ntoa(ia);
	memcpy(buf, p, strlen(p) + 1);
	return buf;
}