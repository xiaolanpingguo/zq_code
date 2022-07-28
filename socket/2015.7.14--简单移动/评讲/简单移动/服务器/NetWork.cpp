#include "NetWork.h"
#pragma comment(lib, "Ws2_32.lib")

#define _BUF_MAX 65536

bool CNetWork::_SendData()
{
	//如果有数据就发送当前数据
	while (sd_list.size() > 0)
	{
		//得到要发送的数据包
		SD sd = sd_list.front();

		while (sd.send_len < sd.all_len)
		{
			int r = send(m_socket, sd.data + sd.send_len, sd.all_len - sd.send_len, 0);
			if (r == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
					return false;
				else
					return true;
			}
			else
				sd.send_len += r;
		}

		//当前包发送完毕，那么释放存储的数据
		free(sd.data);

		//将其从发送表中删除
		sd_list.erase(sd_list.begin());
	}

	return true;
}

bool CNetWork::_RecvData()
{
	char buf[_BUF_MAX];
	int r = recv(m_socket, buf, _BUF_MAX, 0);
	if (r == SOCKET_ERROR)
		//如果发生真正的错误就返回假
		//如果当前没有数据可读就返回真
		return WSAGetLastError() == WSAEWOULDBLOCK;
		//如果是优雅断开就返回假
	else if (r == 0)
		return false;
	else
	{
		//初始化分析的位置
		int cur = 0;

		//循环分析所有数据
		while (cur < r)
		{
			//当前没有收完长度
			if (rd.len_valid_bytes < 4)
			{
				//当前不能收完长度
				if (4 - rd.len_valid_bytes > r - cur)
				{
					//拷贝可以收的长度字节到总长度中
					memcpy(
						(char*)&rd.all_len + rd.len_valid_bytes,
						buf + cur,
						r - cur);

					//长度的有效字节数更新
					rd.len_valid_bytes += r - cur;

					//分析的位置递增（将导致退出循环分析所有数据）
					cur += r - cur;
				}
				//当前可以收完长度
				else
				{
					//拷贝可以收的长度字节到总长度中
					memcpy(
						(char*)&rd.all_len + rd.len_valid_bytes,
						buf + cur,
						4 - rd.len_valid_bytes);

					//分析的位置递增
					cur += 4 - rd.len_valid_bytes;

					//长度的有效字节数更新
					rd.len_valid_bytes = 4;

					//开辟接收数据的内存
					rd.data = (char*)malloc(rd.all_len);
				}
			}
			//当前收完了长度应该收数据
			else
			{
				//当前不能收完数据
				if (rd.all_len - rd.recv_len > r - cur)
				{
					//拷贝可以收的数据到总数据中
					memcpy(
						rd.data + rd.recv_len,
						buf + cur,
						r - cur);

					//已经接收的数据更新
					rd.recv_len += r - cur;

					//分析的位置递增（将导致退出循环分析所有数据）
					cur += r - cur;
				}
				//当前可以收完数据
				else
				{
					//拷贝可以收的数据到总数据中
					memcpy(
						rd.data + rd.recv_len,
						buf + cur,
						rd.all_len - rd.recv_len);

					//分析的位置递增
					cur += rd.all_len - rd.recv_len;

					//完成了一个包的分析
					_RECV_DATA recv_data = {rd.data, rd.all_len};
					rd_list.push_back(recv_data);

					//清空
					rd.len_valid_bytes = 0;
					rd.all_len = 0;
					rd.data = 0;
					rd.recv_len = 0;
				}
			}
		}
	}

	return true;
}

CNetWork::CNetWork()
:
m_socket(INVALID_SOCKET)
{
	rd.len_valid_bytes = 0;
	rd.all_len = 0;
	rd.data = 0;
	rd.recv_len = 0;
}

CNetWork::CNetWork(SOCKET s)
:
m_socket(s)
{
	rd.len_valid_bytes = 0;
	rd.all_len = 0;
	rd.data = 0;
	rd.recv_len = 0;
}

void CNetWork::SetSocket(SOCKET s)
{
	m_socket = s;
}

void CNetWork::SendData(const void* data, int len)
{
	//准备发送数据包
	SD sd;
	sd.all_len = sizeof(int) + len;
	sd.data = (char*)malloc(sd.all_len);
	sd.send_len = 0;
	
	//填充长度和数据
	*((int*)sd.data) = len;
	memcpy(sd.data + sizeof(int), data, len);

	//装入发送表中
	sd_list.push_back(sd);
}

bool CNetWork::GetRecvDate(_RECV_DATA* recv_data)
{
	if (rd_list.size() > 0)
	{
		*recv_data = rd_list.front();
		rd_list.erase(rd_list.begin());
		return true;
	}
	else
		return false;
}

void CNetWork::ReleaseRecvData(_RECV_DATA* recv_data)
{
	if (recv_data->data)
		free(recv_data->data);
}

bool CNetWork::Run()
{
	bool r1 = _RecvData();
	bool r2 = _SendData();
	return r1 && r2;
}

void CNetWork::End()
{
	for (int i = 0; i < rd_list.size(); ++i)
		free(rd_list[i].data);
	if (rd.data)
		free(rd.data);
	for (int i = 0; i < sd_list.size(); ++i)
		free(sd_list[i].data);
}