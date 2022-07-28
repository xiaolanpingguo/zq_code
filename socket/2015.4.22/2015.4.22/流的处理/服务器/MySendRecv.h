#ifndef _MY_SEND_RECV_H_
#define _MY_SEND_RECV_H_

#include <Winsock2.h>
#include <vector>

struct _NET_EVENT //网络事件结构体
{
	int type; //事件类型：0表示连接断开，1表示收到数据
	void* data; //当事件类型为1的时候，本成员表示数据的首地址
	int size; //当事件类型为1的时候，本成员表示数据的长度
};

class CMySendRecv
{
	SOCKET m_Socket; //套接字
	
	struct _SEND_DATA //发送数据结构体
	{
		int allsize; //数据包总大小
		char* data; //数据
		int sendsize; //已经发送的大小
	};
	struct _RECV_DATA //接收数据结构体
	{
		int allsize; //数据总长度
		//在网络传输中有可能连上面的总长度都一次性收不
		//完，我们用本成员表示上面的总长度中有几个字节
		//有效，只有当本成员为4的时候那么上面的总长度才
		//是完整地收完了
		int allsize_bytes; //数据总长度的有效字节
		char* data; //数据
		int recv_size; //已经收到的数据长度
	};
	std::vector<_SEND_DATA> sdlist; //发送表
	_RECV_DATA recv_data; //接收
	std::vector<_NET_EVENT> nelist; //网络事件表
	void _Send();
	void _Recv();
public:
	CMySendRecv(SOCKET Socket);
	void SendData(const void* Data, int Size);
	bool GetNetEvent(_NET_EVENT* pNetEvent);
	void Run();
	void Close();
};

#endif