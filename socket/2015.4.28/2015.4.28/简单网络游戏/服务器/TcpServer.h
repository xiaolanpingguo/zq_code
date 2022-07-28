#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <Winsock2.h>
#include "Map.h"
#include "Queue.h"
#include "MemoryPool.h"

#define _TSNE_CONNECT 0
#define _TSNE_S_DISCONNECT 1
#define _TSNE_C_DISCONNECT 2
#define _TSNE_E_DISCONNECT 3
#define _TSNE_DATA 4

struct _TS_NET_EVENT
{
	//0：有客户端来连接
	//1：服务器作为主动方的断开
	//2：客户端作为主动方的断开
	//3：因为错误的断开
	//4：收到来自客户端的数据
	int type; //事件类型
	SOCKET s; //客户标识
	unsigned long ip; //客户ip地址
	char* data; //数据
	int len; //数据长度
};

class CTcpServer
{
	unsigned short m_Port; //端口号
	int m_MaxClient; //最大连接数
	int m_StartKAYime; //心跳包启动时间
	int m_IntervalKAYime; //心跳包间隔时间
	bool m_Continue; //循环标记
	SOCKET m_Listen; //监听套接字
	CQueue<_TS_NET_EVENT> m_TSNetEvent; //网络事件队列
	struct _SEND_DATA //发送数据结构体
	{
		int allsize; //数据包总大小
		char* data; //数据
		int sendsize; //已经发送的大小
	};
	struct _RECV_DATA //接收数据结构体
	{
		int allsize; //数据总长度
		int allsize_bytes; //数据总长度的有效字节
		char* data; //数据
		int recvsize; //已经收到的数据长度
	};
	struct CLIENT
	{
		int state; //状态：连接、准备主动断开、被动断开、等待结束
		unsigned long ip; //ip地址
		CQueue<_SEND_DATA> sd_queue; //发送数据队列
		_RECV_DATA rd; //接收数据
	};
	CMap<SOCKET, CLIENT> m_Client; //客户端映射
	CMemoryPool m_MP; //内存池

	int _AcceptClient();
	void _OperateData(const char* buf, int r, SOCKET s, unsigned long ip, _RECV_DATA* rd);
	int _RecvData();
	int _SendData();
	void _Close(int index, SOCKET s, CLIENT* c, int type);

public:

	//初始化
	bool Init(
		unsigned short port, //端口号
		int max_client, //最大连接数
		int start_ka_time, //心跳包启动时间（秒）
		int interval_ka_time); //心跳包间隔时间（秒）

	//终止
	void Stop();

	//循环标志
	bool Continue();

	//结束
	void End();

	//运行
	//1）接收连接
	//2）接收数据
	//3）发送数据
	void Run();

	//得到网络事件
	bool GetTSNetEvent(_TS_NET_EVENT* ptne);

	//释放网络事件中使用的内存
	void ReleaseTSNetEvent(_TS_NET_EVENT* ptne);

	//断开连接
	int Disconnect(SOCKET s);

	//发送数据
	int SendData(SOCKET s, const char* data, int len);

	//整数ip地址转字符串ip地址
	static void GetStrIP(unsigned long ul_ip, char* str_ip);

	//得到当前内存使用情况
	float GetUseMemoryMB();
};

#endif