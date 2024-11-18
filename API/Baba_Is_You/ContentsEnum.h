#pragma once


// 누가 먼저 랜더되는지
enum class ERenderOrder
{
	BACKGROUND = -2000,
	TITLELOGO = -100,
	WORLDMAP = -20,
	BUTTON = -11,
	STAGEBG = -1,
	LOWER = 0,
	UPPER = 1,
	PLAYER = 1000,
};

enum class EMoveType
{
	NONE,
	YOU,
	PUSH,
	STOP,
	Max,
};

enum class EStateType
{
	NONE,
	WIN,
	DEFEAT,
	HOT,
	MELT,
	SINK,
	Max,
};

enum class ELogicType
{
	NONE,
	BABA,
	FLAG,
	ROCK,
	WALL,
	GRASS,
	SKULL,
	LAVA,
	WATER,
	YOU,
	WIN,
	PUSH,
	STOP,
	DEFEAT,
	HOT,
	MELT,
	SINK,
	MAX,
	BABAOBJECT,
	FLAGOBJECT,
	ROCKOBJECT,
	WALLOBJECT,
	GRASSOBJECT,
	SKULLOBJECT,
	LAVAOBJECT,
	WATEROBJECT,
};

enum class EVLogicType
{
	NONE,
	IS,
	MAX,
};

enum class EFloorOrder
{
	NONE,
	GRASSOBJECT,
	SKULLOBJECT,
	LAVAOBJECT,
	WATEROBJECT,
	WALLOBJECT,
	ROCKOBJECT,
	FLAGOBJECT,
	TEXT,
	BABAOBJECT,
	MAX,
};







