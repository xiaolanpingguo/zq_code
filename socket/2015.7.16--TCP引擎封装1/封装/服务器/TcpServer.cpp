#include "TcpServer.h"
#pragma comment(lib, "Ws2_32.lib")

#define _CS_CONNECTED			0 //客户端状态：连接
#define _CS_PREPARE_DISCONNECT	1 //客户端状态：准备主动断开
#define _CS_BE_DISCONNECTED		2 //客户端状态：被动断开
#define _CS_WAIT_FINISH			3 //客户端状态：等待对方结束

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
	m_BeginKA = beginka;
	m_IntervalKA = intervalka;

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
	
}

bool CTcpServer::GetNetEvent(_NET_EVENT* ne)
{
	if (!m_NetEvent.Empty())
	{
		m_NetEvent.Front(ne);
		m_NetEvent.Pop();
		return true;
	}
	else
		return false;
}

void CTcpServer::ReleaseNetEvent(_NET_EVENT* ne)
{
	if (ne->type == _NE_DATA)
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