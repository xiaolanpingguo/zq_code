#include "TcpClient.h"
#include <MSTcpIP.h>
#include <ctime>
#pragma comment(lib, "Ws2_32.lib")

#define _CS_NO_CONNECTED		0 //客户端状态：未连接
#define _CS_TRY_CONNECT			1 //客户端状态：尝试连接
#define _CS_CONNECTED			2 //客户端状态：连接
#define _CS_PREPARE_DISCONNECT	3 //客户端状态：准备主动断开
#define _CS_BE_DISCONNECTED		4 //客户端状态：被动断开
#define _CS_WAIT_FINISH			5 //客户端状态：等待对方结束

void CTcpClient::_Send()
{
	//当客户状态不是等待对方结束状态的情况下才可以发送数据
	if (m_State != _CS_NO_CONNECTED && m_State != _CS_TRY_CONNECT && m_State != _CS_WAIT_FINISH)
	{
		//退出下面的循环时的情况
		//0：表示没有要发送的数据了
		//1：表示暂时不能发送
		//2：表示发送错误
		int quit_state = 0;

		//当队列不为空
		while (!m_SDQueue.Empty())
		{
			//得到要发送的数据
			_SEND_DATA sd;
			m_SDQueue.Front(&sd);

			//循环发送
			while (sd.send_size < sd.all_size)
			{
				int r = send(m_Socket, sd.data + sd.send_size, sd.all_size - sd.send_size, 0);
				if (r == SOCKET_ERROR)
				{
					//真的出错
					if (WSAEWOULDBLOCK != WSAGetLastError())
						quit_state = 2;
					//暂时不能发送了
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
				m_SDQueue.Pop();
			}
			else
				break;
		}

		switch (quit_state)
		{
		case 0: //没有要发送的数据了
			{
				if (m_State == _CS_PREPARE_DISCONNECT)
				{
					shutdown(m_Socket, SD_SEND);
					m_State = _CS_WAIT_FINISH;
				}
				else if (m_State == _CS_BE_DISCONNECTED)
				{
					shutdown(m_Socket, SD_SEND);
					_CloseSocket(_CNE_DISCONNECTED_S);
				}
				break;
			}
		case 1: //暂时不能发送
			{
				break;
			}
		case 2: //出错发送
			{
				_CloseSocket(_CNE_DISCONNECTED_E);
				break;
			}
		}
	}
}

void CTcpClient::_Recv()
{
	char buf[65536];

	//若玩家状态不为被动断开的时候可以进行接收
	if (m_State != _CS_NO_CONNECTED && m_State != _CS_TRY_CONNECT && m_State != _CS_BE_DISCONNECTED)
	{
		//接收数据
		int r = recv(m_Socket, buf, 65536, 0);

		//分情况讨论
		if (r == SOCKET_ERROR)
		{
			//真的出错
			if (WSAEWOULDBLOCK != WSAGetLastError())
				_CloseSocket(_CNE_DISCONNECTED_E);
		}
		//对方调用了shutdown
		else if (r == 0)
		{
			//如果状态是连接状态和准备主动断开状态，则只需转换状态到被动断开
			if (m_State == _CS_CONNECTED || m_State == _CS_PREPARE_DISCONNECT)
				m_State = _CS_BE_DISCONNECTED;
			//如果状态是等待对方结束状态，则关闭套接字
			else
				_CloseSocket(_CNE_DISCONNECTED_C);
		}
		else
			_RecvData(buf, r);
	}
}

void CTcpClient::_RecvData(char* buf, int r)
{
	//初始化分析的位置
	int cur = 0;

	//循环分析所有数据
	while (cur < r)
	{
		//当前没有收完长度
		if (m_RD.len_valid_bytes < 4)
		{
			//当前不能收完长度
			if (4 - m_RD.len_valid_bytes > r - cur)
			{
				//拷贝可以收的长度字节到总长度中
				memcpy(
					(char*)&m_RD.all_len + m_RD.len_valid_bytes,
					buf + cur,
					r - cur);

				//长度的有效字节数更新
				m_RD.len_valid_bytes += r - cur;

				//分析的位置递增（将导致退出循环分析所有数据）
				cur += r - cur;
			}
			//当前可以收完长度
			else
			{
				//拷贝可以收的长度字节到总长度中
				memcpy(
					(char*)&m_RD.all_len + m_RD.len_valid_bytes,
					buf + cur,
					4 - m_RD.len_valid_bytes);

				//分析的位置递增
				cur += 4 - m_RD.len_valid_bytes;

				//长度的有效字节数更新
				m_RD.len_valid_bytes = 4;

				//开辟接收数据的内存
				m_RD.data = (char*)m_MP.Allocate(m_RD.all_len);
			}
		}
		//当前收完了长度应该收数据
		else
		{
			//当前不能收完数据
			if (m_RD.all_len - m_RD.recv_len > r - cur)
			{
				//拷贝可以收的数据到总数据中
				memcpy(
					m_RD.data + m_RD.recv_len,
					buf + cur,
					r - cur);

				//已经接收的数据更新
				m_RD.recv_len += r - cur;

				//分析的位置递增（将导致退出循环分析所有数据）
				cur += r - cur;
			}
			//当前可以收完数据
			else
			{
				//拷贝可以收的数据到总数据中
				memcpy(
					m_RD.data + m_RD.recv_len,
					buf + cur,
					m_RD.all_len - m_RD.recv_len);

				//分析的位置递增
				cur += m_RD.all_len - m_RD.recv_len;

				//完成了一个包的分析投递接收数据网络事件
				_CNET_EVENT ne = {_CNE_DATA, m_RD.data, m_RD.all_len};
				m_CNetEvent.Push(ne);

				//清空
				m_RD.Clear();
			}
		}
	}
}

CTcpClient::CTcpClient()
:
m_Socket(INVALID_SOCKET),
m_State(_CS_NO_CONNECTED)
{
	m_RD.Clear();
}

CTcpClient::~CTcpClient()
{}

bool CTcpClient::ConnectIP(const char* ip,
						   unsigned short port,
						   int wait,
						   int beginka,
						   int intervalka)
{
	//参数检查
	if (m_State != _CS_NO_CONNECTED || !ip || port < _MIN_PORT || wait < 1 || beginka < 1 || intervalka < 1)
		return false;

	//得到数据
	m_BeginKA = beginka;
	m_IntervalKA = intervalka;
	m_Wait = wait;

	//初始化网络环境
	WSADATA wd;
	WSAStartup(0x0101, &wd);

	//创建套接字并设置非阻塞模式
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(m_Socket, FIONBIO, &no_blocking);

	//填充地址信息结构体
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.S_un.S_addr = inet_addr(ip);

	//因为connect一定返回失败所以此处不检查
	connect(m_Socket, (sockaddr*)&si, sizeof(si));

	//记录当前时间
	m_ConnectTime = (int)time(0);

	//修改状态为尝试连接状态
	m_State = _CS_TRY_CONNECT;

	return true;
}

bool CTcpClient::ConnectName(const char* name,
							 unsigned short port,
							 int wait,
							 int beginka,
							 int intervalka)
{
	//参数检查
	if (m_State != _CS_NO_CONNECTED || !name || port < _MIN_PORT || wait < 1 || beginka < 1 || intervalka < 1)
		return false;

	//得到数据
	m_BeginKA = beginka;
	m_IntervalKA = intervalka;
	m_Wait = wait;

	//初始化网络环境
	WSADATA wd;
	WSAStartup(0x0101, &wd);

	//根据域名得到IP地址，gethostbyname就是从
	//网络上面的DNS服务器中根据传入的域名去得
	//到IP地址
	hostent* h = gethostbyname(name);
	if (0 == h)
	{
		//未联网
		WSACleanup();
		return false;
	}
	char* ip = inet_ntoa(*(in_addr*)h->h_addr_list[0]);
	//没有这个域名的服务器或者服务器未开启
	if (0 == ip || 0 == strcmp(ip, "0.0.0.0"))
	{
		WSACleanup();
		return false;
	}

	//创建套接字并设置非阻塞模式
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(m_Socket, FIONBIO, &no_blocking);

	//填充地址信息结构体
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.S_un.S_addr = inet_addr(ip);

	//因为connect一定返回失败所以此处不检查
	connect(m_Socket, (sockaddr*)&si, sizeof(si));

	//记录当前时间
	m_ConnectTime = (int)time(0);

	//修改状态为尝试连接状态
	m_State = _CS_TRY_CONNECT;

	return true;
}

void CTcpClient::Run()
{
	switch (m_State)
	{
	case _CS_NO_CONNECTED: break;
	case _CS_TRY_CONNECT:
		{
			fd_set fs;
			FD_ZERO(&fs);
			FD_SET(m_Socket, &fs);
			timeval t = {0, 0};
			select(0, 0, &fs, 0, &t);

			//具备可读性就意味着连接成功
			if (1 == fs.fd_count)
			{
				//设置状态为连接状态
				m_State = _CS_CONNECTED;

				//设置心跳包及其时间
				BOOL b = TRUE;
				setsockopt(m_Socket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&b, sizeof(b));
				DWORD dw;
				tcp_keepalive tka = {1, m_BeginKA, m_IntervalKA};
				WSAIoctl(m_Socket, SIO_KEEPALIVE_VALS, &tka, sizeof(tka), 0, 0, &dw, 0, 0);

				//投递连接成功事件
				_CNET_EVENT ne = {_CNE_CONNECT_OK, 0, 0};
				m_CNetEvent.Push(ne);
			}
			//不具备可读性就意味着还没有连接成功
			else
			{
				//连接超时
				if (time(0) - m_ConnectTime > m_Wait)
					_CloseSocket(_CNE_CONNECT_FAIL);
			}

			break;
		}
	case _CS_CONNECTED:
	case _CS_PREPARE_DISCONNECT:
	case _CS_BE_DISCONNECTED:
	case _CS_WAIT_FINISH:
		{
			_Send();
			_Recv();
			break;
		}
	}
}

void CTcpClient::_CloseSocket(int t)
{
	//释放接收数据
	if (m_RD.data)
		m_MP.Free(m_RD.data);

	//释放发送数据
	while (!m_SDQueue.Empty())
	{
		_SEND_DATA sd;
		m_SDQueue.Front(&sd);
		m_SDQueue.Pop();
		m_MP.Free(sd.data);
	}

	//关闭套接字
	closesocket(m_Socket);
	m_Socket = INVALID_SOCKET;

	//关闭网络环境
	WSACleanup();

	//设置状态为未连接状态
	m_State = _CS_NO_CONNECTED;

	//投递事件
	_CNET_EVENT ne = {t, 0, 0};
	m_CNetEvent.Push(ne);
}

bool CTcpClient::GetNetEvent(_CNET_EVENT* ne)
{
	if (!m_CNetEvent.Empty())
	{
		m_CNetEvent.Front(ne);
		m_CNetEvent.Pop();
		return true;
	}
	else
		return false;
}

void CTcpClient::ReleaseNetEvent(_CNET_EVENT* ne)
{
	if (ne->type == _CNE_DATA)
		m_MP.Free(ne->data);
}

bool CTcpClient::SendData(const void* data, int len)
{
	//且状态必须为连接状态，最后数据也必须有效
	if (m_State == _CS_CONNECTED && data && len > 0)
	{
		_SEND_DATA _send_data;

		//填充发送结构体对象
		_send_data.all_size = sizeof(int) + len;
		_send_data.data = (char*)m_MP.Allocate(_send_data.all_size);
		*((int*)_send_data.data) = len;
		memcpy(_send_data.data + sizeof(int), data, len);
		_send_data.send_size = 0;

		//装入发送队列
		m_SDQueue.Push(_send_data);

		return true;
	}
	else
		return false;
}

bool CTcpClient::Disconnect()
{
	//状态必须为连接状态
	if (m_State == _CS_CONNECTED)
	{
		m_State = _CS_PREPARE_DISCONNECT;
		return true;
	}
	else
		return false;
}