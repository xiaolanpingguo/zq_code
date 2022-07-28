#include <iostream>
#include <windows.h>
#include "fmod.h"
#pragma comment(lib, "fmodvc.lib")

//音频引擎很多，常见的有Fmod、Bass、OpenAL等，这些
//引擎往往都是跨平台的付费引擎，音频的数字存储过程
//是需要进行声音样本的采集的，同一个时间段内采集的
//声音样本越多，那么这个音频就越接近真实的声音，采
//集的样本越少失真也就越多

//音乐播放：同一时间只能播放一个，FMOD中音乐播放是流式
//          播放，也就是说不会把音频文件载入内存，而是
//          每次要播放的时候，就去打开的那个文件中读取
//          一点要播放的内容，所以音乐的播放每次只能处
//          理一个
//音效播放：同一时间可以播放多个（由FSOUND_Init第二个参
//          数决定），FMOD中音效是需要将文件都载入到内存
//          中的（样本播放），可以同时播放多个

void main()
{
	//初始化
	//1）音频播放级别
	//2）最大声道数量
	//3）标志
	FSOUND_Init(44100, 16, 0);

	//打开音频流
	FSOUND_STREAM* stream = FSOUND_Stream_Open(
		"LoopyMusic.wav",
		FSOUND_LOOP_NORMAL,
		0,
		0);
	
	//播放音频流，返回值得到播放本音频流的声道下标
	int sd = FSOUND_Stream_Play(FSOUND_FREE, stream);

	//得到指定声道的音量
	int v = FSOUND_GetVolume(sd);

	//加载音频样本
	FSOUND_SAMPLE* sample1 = FSOUND_Sample_Load(FSOUND_FREE, "Windows XP 惊叹号.wav", FSOUND_LOOP_OFF, 0, 0);
	FSOUND_SAMPLE* sample2 = FSOUND_Sample_Load(FSOUND_FREE, "Windows XP 默认值.wav", FSOUND_LOOP_OFF, 0, 0);

	while (1)
	{
		if (GetAsyncKeyState(VK_UP) & 1)
		{
			v += 10;
			FSOUND_SetVolume(sd, v);
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			v -= 10;
			FSOUND_SetVolume(sd, v);
		}
		if (GetAsyncKeyState(VK_RETURN) & 1)
		{
			FSOUND_Stream_Stop(stream);
		}

		if (GetAsyncKeyState(VK_F1) & 1)
			FSOUND_PlaySound(FSOUND_FREE, sample1);
		if (GetAsyncKeyState(VK_F2) & 1)
			FSOUND_PlaySound(FSOUND_FREE, sample2);

		Sleep(33);
	}

	//卸载音频样本
	FSOUND_Sample_Free(sample1);
	FSOUND_Sample_Free(sample2);
	
	//关闭音频流
	FSOUND_Stream_Close(stream);

	//关闭
	FSOUND_Close();

	system("pause");
}