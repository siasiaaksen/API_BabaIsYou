#pragma once


// 누가 먼저 랜더되는지
enum class ERenderOrder
{
	BACKGROUND = -2000,
	TITLELOGO = -100,
	WORLDMAP = -20,
	BUTTON = -11,
	BABASELECT = -9,
	STAGEBG = -2,
	BGOBJECT = -1,
	LOWER = 0,
	UPPER = 1,
	PLAYER = 1000,
	FADE = 2000,
};

enum class EMoveType
{
	NONE,
	YOU,
	PUSH,
	STOP,
	MAX,
};

enum class EStateType
{
	NONE,
	WIN,
	DEFEAT,
	HOT,
	MELT,
	SINK,
	MAX,
};

enum class ELinkSprite
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
	MAX,
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

enum class EMapOrder
{
	NONE,
	BGCIRCLE,
	LINE,
	NUMBER,
	SELECTBOX,
	MAX,
};







