#ifndef _NET_WORK_H_
#define _NET_WORK_H_

#include <Winsock2.h>
#include <vector>

//本结构体是使用CNetWork类的人会用到的，所以写在外面
struct _RECV_DATA
{
	char* data;
	int len;
};

class CNetWork
{
	SOCKET m_socket;

	//发送结构体
	struct SD
	{
		char* data; //要发送的数据
		int all_len; //要发送数据的总长度
		int send_len; //已经发送数据的长度
	};
	std::vector<SD> sd_list; //发送表

	//接收结构体
	struct RD
	{
		int len_valid_bytes; //长度有效字节（必须到4那么长度才算接收完毕）
		int all_len; //要接收数据的总长度
		char* data; //要接收的数据
		int recv_len; //已经接收数据的长度
	};
	RD rd; //接收
	std::vector<_RECV_DATA> rd_list; //完整的收到的数据表

	//如果正常情况就返回真，反之出错就返回假
	bool _SendData();
	bool _RecvData();

public:

	//构造
	CNetWork(SOCKET s);

	//发送数据
	void SendData(const void* data, int len);

	//接收数据、释放数据
	bool GetRecvDate(_RECV_DATA* recv_data);
	void ReleaseRecvData(_RECV_DATA* recv_data);

	//运行
	bool Run();
};

#endif

//main()
//{
//	while (1)
//	{
//		//发送数据
//
//		//收数据
//		_RECV_DATA rd;
//		while (CNetWork.GetRecvDate(&rd))
//		{
//			//处理数据包
//
//			CNetWork.ReleaseRecvData(&rd);
//			free(&rd);
//		}
//	}
//}