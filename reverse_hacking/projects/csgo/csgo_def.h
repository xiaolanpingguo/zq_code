#pragma once


#include <vector>


// 人物数组基址
// 特征码：EB ?? 8B4B ?? 83F9 FF 74 ?? 0FB7C1C1E0 ?? 05 ??
#define TEAMS_BASE				0x4DDD91C

// 人物数组，每个人物元素的间隔是0x10个字节
#define PLAYERS_ARRAY_OFFSET	0x10

// 人物结构体
#define PLAYER_HP													0x100	// 血量偏移,DWORD
#define PLAYER_POS													0xA0	// 坐标偏移，float
#define PLAYER_TEAM_FLAG											0xf4	// team标志位，DWORD
#define PLAYER_MIRRO												0x31f4	// 是否开镜, DWORD, 大狙一倍镜是40，二倍镜是10，默认是0或者90
#define PLAYER_COMMAND												0x300C	// 动作类型(开枪，攻击，跳跃等，32位，每一位代表一个类型，第一位是攻击)
#define PLAYER_PITCH												0x12C	// 俯仰角, float, 往上-89度-往下89度(不能修改)
#define PLAYER_YAW													0x130	// 偏航角，float, 角度，0-360度(不能修改)
#define PLAYER_SKELETON_BASE										0x26a8	// 骨骼地址偏移
#define PLAYER_SKELETON_HEAD_X										0x18c	// 骨骼头x坐标
#define PLAYER_SKELETON_HEAD_Y (PLAYER_SKELETON_HEAD_X + 0x10)				// 骨骼头y坐标
#define PLAYER_SKELETON_HEAD_Z (PLAYER_SKELETON_HEAD_Y + 0x10)				// 骨骼头z坐标


#define ENGINE_VISUAL_ANGLE_BASE		0x58CFDC	// 角度偏移base
#define ENGINE_VISUAL_VIEW_ANGLE		0x4d90		// pitch,yaw float[2]
#define ENGINE_CAMERA_MATRIX			0x4DCF234	// 摄像机view-projection矩阵基址
#define LOCAL_PLAYER					0x5286084



namespace GameSignature
{
	struct OffsetSignature
	{
		std::vector<std::uint8_t> signature;// p1{ 0xEB, '?', 0x8B, 0x4B, '?', 0x83, 0xF9, 0xFF, 0x74,'?', 0x0F, 0xB7, 0xC1 ,0xC1 ,0xE0 ,'?', 0x05, '?' };
		int offset;
		bool flag;
	};

	inline OffsetSignature g_teamBaseSignature
	{
		{ 0xEB, '?', 0x8B, 0x4B, '?', 0x83, 0xF9, 0xFF, 0x74,'?', 0x0F, 0xB7, 0xC1 ,0xC1 ,0xE0 ,'?', 0x05, '?' },
		17,
		true
	};
}