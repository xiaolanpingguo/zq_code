#include "MySendRecv.h"

#pragma comment(lib, "Ws2_32.lib")

#define _RECV_BUF (64 * 1024)

void CMySendRecv::_Send()
{
	//发送
	while (sdlist.size() > 0)
	{
		//得到当前要发送的数据包
		_SEND_DATA sd = sdlist[0];

		//本次数据包发送的结果,0、1、2分别表示发送完毕、暂不能发、出错
		int result = 0;

		//循环发送
		while (sd.sendsize < sd.allsize)
		{
			int r = send(m_Socket, sd.data + sd.sendsize, sd.allsize - sd.sendsize, 0);

			if (SOCKET_ERROR == r)
			{
				if (WSAEWOULDBLOCK == WSAGetLastError())
					result = 1;
				else
					result = 2;
				break;
			}
			else
				sd.sendsize += r;
		}

		switch (result)
		{
		case 0:
			{
				//发送完毕当前数据包就把它从发送表中删除
				free(sd.data);
				sdlist.erase(sdlist.begin());
				break;
			}
				//暂时不能发送的话就什么都不做
		case 1: break;

		case 2:
			{
				//设置错误事件
				_NET_EVENT ne = {0};
				nelist.push_back(ne);
				break;
			}
		}
	}
}

void CMySendRecv::_Recv()
{
	char buf[_RECV_BUF];
	int r = recv(m_Socket, buf, _RECV_BUF, 0);

	//出错
	if (r == SOCKET_ERROR)
	{
		//真的出错了
		if (WSAEWOULDBLOCK != WSAGetLastError())
		{
			//设置错误事件
			_NET_EVENT ne = {0};
			nelist.push_back(ne);
		}
	}
	//优雅断开
	else if (r == 0)
	{
		//设置错误事件
		_NET_EVENT ne = {0};
		nelist.push_back(ne);
	}
	else
	{
		//当前分析下标
		int cur_i = 0;
		while (cur_i < r)
		{
			//当前接收长度部分
			if (recv_data.allsize_bytes < 4)
			{
				//当前不能收完长度部分
				if (4 - recv_data.allsize_bytes > r - cur_i)
				{
					//将字节拷贝到数据总长中
					memcpy(&recv_data.allsize, buf + cur_i, r - cur_i);

					//数字总长的有效字节数递增
					recv_data.allsize_bytes += r - cur_i;

					//当前分析下标递增
					cur_i += r - cur_i;
				}
				//当前可以收完长度部分
				else
				{
					//将字节拷贝到数据总长中
					memcpy(&recv_data.allsize, buf + cur_i, 4 - recv_data.allsize_bytes);

					//当前分析下标递增
					cur_i += 4 - recv_data.allsize_bytes;

					//数字总长的有效字节数设置为4
					recv_data.allsize_bytes = 4;

					//开辟堆内存
					recv_data.data = (char*)malloc(recv_data.allsize);
				}
			}
			//当前接收数据部分
			else
			{
				//当前不能接收完数据
				if (recv_data.allsize - recv_data.recv_size > r - cur_i)
				{
					//拷贝剩下的所有字节到数据中
					memcpy(recv_data.data + recv_data.recv_size, buf + cur_i, r - cur_i);

					//当前已经接收的数据长度递增
					recv_data.recv_size += r - cur_i;

					//当前分析下标递增
					cur_i += r - cur_i;
				}
				else
				{
					//拷贝当前完整包需要的字节到数据中
					memcpy(recv_data.data + recv_data.recv_size, buf + cur_i, recv_data.allsize - recv_data.recv_size);
					
					//当前分析下标递增
					cur_i += recv_data.allsize - recv_data.recv_size;

					//设置收数据事件
					_NET_EVENT ne = {1, recv_data.data, recv_data.allsize};
					nelist.push_back(ne);

					//清空接收
					recv_data.allsize = 0;
					recv_data.allsize_bytes = 0;
					recv_data.data = 0;
					recv_data.recv_size = 0;
				}
			}
		}
	}
}

CMySendRecv::CMySendRecv(SOCKET Socket)
{
	m_Socket = Socket;

	//清空接收
	recv_data.allsize = 0;
	recv_data.allsize_bytes = 0;
	recv_data.data = 0;
	recv_data.recv_size = 0;
}

void CMySendRecv::SendData(const void* Data, int Size)
{
	//填充一个发送数据结构体
	_SEND_DATA sd;
	sd.allsize = sizeof(int) + Size;
	sd.data = (char*)malloc(sd.allsize);
	*((int*)sd.data) = Size;
	memcpy(sd.data + 4, Data, Size);
	sd.sendsize = 0;

	//将发送数据结构体推入发送表中
	sdlist.push_back(sd);
}

bool CMySendRecv::GetNetEvent(_NET_EVENT* pNetEvent)
{
	if (nelist.size() > 0)
	{
		*pNetEvent = nelist[0];
		nelist.erase(nelist.begin());
		return true;
	}
	else
		return false;
}

void CMySendRecv::Run()
{
	_Send();
	_Recv();
}

void CMySendRecv::Close()
{
	for (int i = 0; i < (int)sdlist.size(); ++i)
		free(sdlist[i].data);

	if (recv_data.data)
		free(recv_data.data);

	for (int i = 0; i < (int)nelist.size(); ++i)
	{
		if (nelist[i].type == 1)
			free(nelist[i].data);
	}
}