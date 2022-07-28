#include <iostream>
#include <string>
#include <map>
#include "TcpServer.h"
#include "..\\XY.h"

#define _CLIENT_INFO_FILE "玩家信息"

void GetIDPasswordFromFile(const char* fn,
						   std::map<std::string, std::string>* m);
void SaveFile(const char* fn, std::map<std::string, std::string>* m);

void main()
{
	//从文件中读取账号和密码
	std::map<std::string, std::string> m_ID_Password;
	GetIDPasswordFromFile(_CLIENT_INFO_FILE, &m_ID_Password);

	//当前玩家表<套接字、账号>
	std::map<SOCKET, std::string> m_Clients;

	//创建服务器
	CTcpServer ts;
	ts.Init(12345, 256, 10, 5);

	//业务循环
	while (ts.Continue())
	{
		//服务区运行
		ts.Run();

		//网络事件处理
		_SNET_EVENT ne;
		while (ts.GetNetEvent(&ne))
		{
			//处理网络事件
			char ip[16];

			switch (ne.type)
			{
			case _SNE_CONNECTED:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"连接到服务器"<<std::endl;

					//装入套接字和空账号
					m_Clients.insert(std::pair<SOCKET, std::string>(ne.s, ""));

					break;
				}
			case _SNE_DATA:
				{
					_XY* xy = (_XY*)ne.data;
					switch (xy->type)
					{
					case 0:
						{
							CS_DL* dl = (CS_DL*)ne.data;

							//无此玩家
							std::map<std::string, std::string>::iterator it = m_ID_Password.find(dl->id);
							if (it == m_ID_Password.end())
							{
								SC_NO_ID no_id;
								ts.SendData(ne.s, &no_id, sizeof(no_id));
								ts.Disconnect(ne.s);
							}
							else
							{
								//密码是否正确
								if (strcmp(it->second.c_str(), dl->pw) != 0)
								{
									SC_PW_ERROR pw_error;
									ts.SendData(ne.s, &pw_error, sizeof(pw_error));
									ts.Disconnect(ne.s);
								}
								else
								{
									//将账号装入当前玩家表，最初的当前玩家表的账号是空
									std::map<SOCKET, std::string>::iterator it = m_Clients.find(ne.s);
									it->second = dl->id;

									//注意3号消息的长度是根据当前玩家的个数不同而不同的

									//1）计算3号消息的长度
									int _3_len = sizeof(SC_DL_OK);
									for (it = m_Clients.begin(); it != m_Clients.end(); ++it)
									{
										if (it->first != ne.s && it->second.length() > 0)
											_3_len += it->second.length() + 1;
									}

									//2）设置3号消息
									SC_DL_OK* dl_ok = (SC_DL_OK*)malloc(_3_len);
									dl_ok->type = 3;
									dl_ok->num = 0; //其它玩家个数
									char* p = (char*)(dl_ok + 1);
									for (it = m_Clients.begin(); it != m_Clients.end(); ++it)
									{
										if (it->first != ne.s && it->second.length() > 0)
										{
											memcpy(p, it->second.c_str(), it->second.length() + 1);
											p += strlen(p) + 1;
											dl_ok->num += 1;
										}
									}

									//3）发送3号消息
									ts.SendData(ne.s, dl_ok, _3_len);
									free(dl_ok);

									//4）发送4号消息
									SC_NEW_CLIENT new_client;
									strcpy_s(new_client.id, 32, dl->id);
									for (it = m_Clients.begin(); it != m_Clients.end(); ++it)
									{
										if (it->first != ne.s && it->second.length() > 0)
										{
											ts.SendData(it->first, &new_client, sizeof(new_client));
										}
									}
								}
							}

							break;
						}
					case 5:
						{
							CS_ZC* zc = (CS_ZC*)ne.data;
							
							//判断是否已经有了该账号
							if (m_ID_Password.find(zc->id) != m_ID_Password.end())
							{
								//发送注册失败
								SC_ZC_FAIL zc_fail;
								ts.SendData(ne.s, &zc_fail, sizeof(zc_fail));
							}
							else
							{
								m_ID_Password.insert(std::pair<std::string, std::string>(zc->id, zc->pw));
								SaveFile(_CLIENT_INFO_FILE, &m_ID_Password);

								//发送注册成功
								SC_ZC_OK zc_ok;
								ts.SendData(ne.s, &zc_ok, sizeof(zc_ok));
							}

							ts.Disconnect(ne.s);

							break;
						}
					}
					break;
				}
			case _SNE_DISCONNECTED_C:
			case _SNE_DISCONNECTED_S:
			case _SNE_DISCONNECTED_E:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"断开"<<std::endl;
					break;
				}
			}

			ts.ReleaseNetEvent(&ne);
		}

		if (GetAsyncKeyState(VK_ESCAPE))
			ts.Stop();
	}

	ts.End();

	system("pause");
}

void GetIDPasswordFromFile(const char* fn, std::map<std::string, std::string>* m)
{
	//账号数量(4)
	//账号0、密码0
	//账号1、密码1
	//...
	//账号n、密码n

	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");

	//如果没有文件就新建文件
	if (!pf)
	{
		fopen_s(&pf, fn, "wb");
		fclose(pf);
		m->clear();
		return;
	}
	
	//读取文件内容
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* fd = (char*)malloc(fs);
	fread(fd, 1, fs, pf);
	fclose(pf);

	//得到数量
	int num = *((int*)fd);

	//得到所有玩家信息
	char* p = fd + 4;
	for (int i = 0; i < num; ++i)
	{
		std::string id = p;
		p += strlen(p) + 1;
		std::string pw = p;
		p += strlen(p) + 1;
		m->insert(std::pair<std::string, std::string>(id, pw));
	}

	//释放
	free(fd);
}

void SaveFile(const char* fn, std::map<std::string, std::string>* m)
{
	FILE* pf = 0;
	fopen_s(&pf, fn, "wb");

	int num = (int)m->size();
	fwrite(&num, 1, 4, pf);

	std::map<std::string, std::string>::iterator it;
	for (it = m->begin(); it !=  m->end(); ++it)
	{
		fwrite(it->first.c_str(), 1, it->first.length() + 1, pf);
		fwrite(it->second.c_str(), 1, it->second.length() + 1, pf);
	}

	fclose(pf);
}