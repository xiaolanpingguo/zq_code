#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include <Winsock2.h>
#include "MemoryPool.h"
#include "SqQueue.h"

//端口号最小值
#define _MIN_PORT 1025

//客户端网络事件（Client Net Event）
#define _CNE_CONNECT_OK 0 //连接服务器成功
#define _CNE_CONNECT_FAIL 1 //连接服务器失败
#define _CNE_DATA 2 //服务器发送过来数据
#define _CNE_DISCONNECTED_C 3 //客户端主动断开
#define _CNE_DISCONNECTED_S 4 //服务器主动断开
#define _CNE_DISCONNECTED_E 5 //因为错误断开
struct _CNET_EVENT
{
	int type; //类型（0~4）
	char* data; //数据
	int len; //数据长度
};

class CTcpClient
{
	//发送结构体
	struct _SEND_DATA
	{
		char* data; //数据
		int all_size; //数据总长
		int send_size; //已发送数据长度
	};

	//接收结构体
	struct _RECV_DATA
	{
		char* data; //数据
		int len_valid_bytes; //数据总长有效字节数
		int all_len; //数据总长
		int recv_len; //已接收数据长度

		//清空数据
		void Clear()
		{
			data = 0;
			len_valid_bytes = 0;
			all_len = 0;
			recv_len = 0;
		}
	};

	SOCKET m_Socket; //套接字
	int m_State; //状态
	CSqQueue<_SEND_DATA> m_SDQueue; //发送数据队列
	_RECV_DATA m_RD; //接收数据

	//网络事件队列
	CSqQueue<_CNET_EVENT> m_CNetEvent;

	//内存池
	CMemoryPool m_MP;

	//心跳包启动时间和间隔时间
	int m_BeginKA;
	int m_IntervalKA;

	//等待连接时间
	int m_Wait;
	
	//当前时间
	int m_ConnectTime;

	//关闭套接字及其所有相关资源
	void _CloseSocket(int t);

	//发送数据
	void _Send();

	//接收数据
	void _Recv();

	//处理接收到的数据
	void _RecvData(char* buf, int r);

public:

	//构造析构
	CTcpClient();
	~CTcpClient();

	//IP地址连接
	bool ConnectIP(
		const char* ip, //服务器ip地址
		unsigned short port, //服务器端口号
		int wait, //连接等待时间
		int beginka, //心跳包启动时间（秒）
		int intervalka); //心跳包间隔时间（秒）

	//域名连接
	//域名是一个internet上面的服务，一般来说由专门
	//的域名服务器（DNS）来做这个工作，所谓域名其实
	//就是对ip地址的一种重命名手段，用一个比较容易
	//记忆的名称来替代相对难以记忆的ip地址，在各个
	//域名服务器中都有相应的域名表（通过域名来查找
	//ip地址），在具体的程序中只需要将域名转换为ip
	//ip地址进行连接即可
	bool ConnectName(
		const char* name, //服务器域名
		unsigned short port, //服务器端口号
		int wait, //连接等待时间
		int beginka, //心跳包启动时间（秒）
		int intervalka); //心跳包间隔时间（秒）

	//得到网络事件
	bool GetNetEvent(_CNET_EVENT* ne);

	//释放网络事件
	void ReleaseNetEvent(_CNET_EVENT* ne);

	//发送数据
	bool SendData(const void* data, int len);

	//断开连接
	bool Disconnect();

	//运行
	void Run();
};

#endif