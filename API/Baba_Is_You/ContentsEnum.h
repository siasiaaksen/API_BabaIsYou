#pragma once


enum class ERenderOrder
{
	BACKGROUND = -2000,
	TITLELOGO = -100,
	STAGEBG = -50,
	WORLDMAP = -20,
	BUTTON = -11,
	LOWER = -10,
	UPPER = -9,
	PLAYER = 1000,
};

enum class ELogicType
{
	NONE,
	BABA,
	YOU,
	FLAG,
	WIN,
	ROCK,
	PUSH,
	WALL,
	GRASS,
	STOP,
	SKULL,
	DEFEAT,
	LAVA,
	HOT,
	MELT,
	WATER,
	SINK,
};


enum class EVLogicType
{
	NONE,
	IS,
};



