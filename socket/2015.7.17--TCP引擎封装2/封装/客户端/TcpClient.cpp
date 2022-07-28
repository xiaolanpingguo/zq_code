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
{}

void CTcpClient::_Recv()
{}

CTcpClient::CTcpClient()
:
m_Socket(INVALID_SOCKET),
m_State(_CS_NO_CONNECTED)
{}

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
	if (m_RD.data)
		m_MP.Free(m_RD.data);

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