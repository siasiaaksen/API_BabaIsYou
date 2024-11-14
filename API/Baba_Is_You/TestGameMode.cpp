#include "PreCompile.h"
#include "TestGameMode.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineString.h>

#include "ContentsEnum.h"
#include "TileMap.h"


ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	Scale = { 33, 18 };

	CreateStageInit(Scale);

	TileMap = GetWorld()->SpawnActor<ATileMap>();
	TileMap->Create(Scale, { 36, 36 });
	TileMap->SetActorLocation(CenterPivot);

	// TextTileMap
	{
		TileMap->SetTileIndex("BabaText.png", { 0, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::BABA, EVLogicType::NONE, ELogicType::BABA);
		TileMap->SetTileIndex("Is.png", { 1, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTileIndex("You.png", { 2, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::YOU);
		TileMap->SetTileIndex("You.png", { 1, 4 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::YOU);
		TileMap->SetTileIndex("FlagText.png", { 12, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::FLAG, EVLogicType::NONE, ELogicType::FLAG);
		TileMap->SetTileIndex("Win.png", { 18, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::WIN);
		TileMap->SetTileIndex("RockText.png", { 1, 2 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::ROCK, EVLogicType::NONE, ELogicType::ROCK);
		TileMap->SetTileIndex("Push.png", { 32, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::PUSH);
		TileMap->SetTileIndex("WallText.png", { 6, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::WALL, EVLogicType::NONE, ELogicType::WALL);
		TileMap->SetTileIndex("GrassText.png", { 12, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::GRASS, EVLogicType::NONE, ELogicType::GRASS);
		TileMap->SetTileIndex("Stop.png", { 18, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::STOP);
		TileMap->SetTileIndex("SkullText.png", { 24, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::SKULL, EVLogicType::NONE, ELogicType::SKULL);
		TileMap->SetTileIndex("Defeat.png", { 30, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::DEFEAT);
		TileMap->SetTileIndex("LavaText.png", { 6, 9 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::LAVA, EVLogicType::NONE, ELogicType::LAVA);
		TileMap->SetTileIndex("Hot.png", { 11, 14 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::HOT);
		TileMap->SetTileIndex("Melt.png", { 18, 9 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::MELT);
		TileMap->SetTileIndex("WaterText.png", { 24, 9 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::WATER, EVLogicType::NONE, ELogicType::WATER);
		TileMap->SetTileIndex("Sink.png", { 30, 9 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::SINK);
	}

	// ObjectTileMap
	{
		TileMap->SetTileIndex("BabaObject.png", { 3, 3 }, 0, static_cast<int>(EFloorOrder::BABAOBJECT), ERenderOrder::UPPER, ELogicType::BABAOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTileIndex("FlagObject.png", { 6, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::FLAGOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTileIndex("RockObject.png", { 10, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::ROCKOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTileIndex("WallObject.png", { 14, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::WALLOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTileIndex("GrassObject.png", { 18, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::GRASSOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTileIndex("SkullObject.png", { 22, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::SKULLOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTileIndex("LavaObject.png", { 26, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::LAVAOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTileIndex("WaterObject.png", { 30, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::WATEROBJECT, EVLogicType::NONE, ELogicType::NONE);
	}

	// LogicCombine
	{
		// StartLogic >> 00 IS YOU
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->YouTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->YouTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->YouTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->YouTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->YouTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->YouTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->YouTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->YouTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS WIN
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					this->WinTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					this->WinTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					this->WinTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					this->WinTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					this->WinTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					this->WinTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					this->WinTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					this->WinTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS PUSH
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->PushTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->PushTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->PushTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->PushTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->PushTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->PushTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->PushTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->PushTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS STOP
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->StopTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->StopTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->StopTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->StopTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->StopTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->StopTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->StopTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->StopTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS DEFEAT
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					this->DefeatTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					this->DefeatTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					this->DefeatTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					this->DefeatTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					this->DefeatTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					this->DefeatTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					this->DefeatTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					this->DefeatTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS HOT
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					this->HotTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					this->HotTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					this->HotTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					this->HotTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					this->HotTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					this->HotTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					this->HotTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					this->HotTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS MELT
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					this->MeltTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					this->MeltTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					this->MeltTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					this->MeltTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					this->MeltTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					this->MeltTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					this->MeltTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					this->MeltTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS SINK
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					this->SinkTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					this->SinkTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					this->SinkTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					this->SinkTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					this->SinkTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					this->SinkTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					this->SinkTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					this->SinkTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> BABA IS 00
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::FLAG)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::ROCK)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WALL)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::GRASS)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SKULL)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::LAVA)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WATER)]
				= [this]()
				{
				};
		}

		// StartLogic >> 00 IS BABA
		{
			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::BABA)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::BABA)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::BABA)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::BABA)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::BABA)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::BABA)]
				= [this]()
				{
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::BABA)]
				= [this]()
				{
				};
		}

		// UpdateLogic
		{
			UpdateLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
				};
		}
	}

	TileCheck();
}

void ATestGameMode::Move()
{
	if (YouTiles.empty())
	{
		return;
	}

	std::vector<FIntPoint> AllLogicTiles;


	for (int i = 0; i < YouTiles.size(); i++)
	{
		std::vector<FIntPoint> FindLogicTile = TileMap->FindMoveTile(YouTiles[i]);

		for (size_t i = 0; i < FindLogicTile.size(); i++)
		{
			AllLogicTiles.push_back(FindLogicTile[i]);
		}
	}

	if (true == UEngineInput::GetInst().IsDown('W') || true == UEngineInput::GetInst().IsDown(VK_UP))
	{
		//UpperTileMap->GetTileRef(CurIndex)->SpriteRenderer->SetSprite(CurSprite, 4);
		for (size_t i = 0; i < AllLogicTiles.size(); i++)
		{
			TileMap->TileMove(AllLogicTiles[i], FIntPoint::UP, PushTiles);
		}
	}

	if (true == UEngineInput::GetInst().IsDown('A') || true == UEngineInput::GetInst().IsDown(VK_LEFT))
	{
		//UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 8);
		for (size_t i = 0; i < AllLogicTiles.size(); i++)
		{
			TileMap->TileMove(AllLogicTiles[i], FIntPoint::LEFT, PushTiles);
		}
	}

	if (true == UEngineInput::GetInst().IsDown('S') || true == UEngineInput::GetInst().IsDown(VK_DOWN))
	{
		//UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 12);
		for (size_t i = 0; i < AllLogicTiles.size(); i++)
		{
			TileMap->TileMove(AllLogicTiles[i], FIntPoint::DOWN, PushTiles);
		}
	}

	if (true == UEngineInput::GetInst().IsDown('D') || true == UEngineInput::GetInst().IsDown(VK_RIGHT))
	{
		//UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 0);
		for (size_t i = 0; i < AllLogicTiles.size(); i++)
		{
			TileMap->TileMove(AllLogicTiles[i], FIntPoint::RIGHT, PushTiles);
		}
	}
}

bool ATestGameMode::IsLogicResult()
{
	if (F > ELogicType::MAX)
	{
		return false;
	}

	if (S > EVLogicType::MAX)
	{
		return false;
	}

	if (T > ELogicType::MAX)
	{
		return false;
	}

	return true;
}

void ATestGameMode::TileCheck()
{
	for (int x = 0; x < Scale.X; x++)
	{
		for (int y = 0; y < Scale.Y; y++)
		{
			FIntPoint CurIndex = { x, y };

			for (int a = 0; a < 11; a++)
			{
				Tile* CurTile = TileMap->GetTileRef(CurIndex, a);
				F = CurTile->FLogicType;
				if (F != ELogicType::NONE)
				{
					NextTileCheck(CurIndex, FIntPoint{ 1, 0 }, a);
					NextTileCheck(CurIndex, FIntPoint{ 0, 1 }, a);
				}
			}
		}
	}
}

void ATestGameMode::NextTileCheck(FIntPoint _Index, FIntPoint _Dir, int _Order)
{
	Tile* CurTile = TileMap->GetTileRef(_Index + _Dir, _Order);

	if (true == TileMap->IsIndexOver(_Index + _Dir))
	{
		return; 
	}

	S = CurTile->SLogicType;
	if (S != EVLogicType::NONE)
	{
		LastTileCheck(_Index + _Dir + _Dir, _Order);
	}

	return;
}

void ATestGameMode::LastTileCheck(FIntPoint _Index, int _Order)
{
	Tile* CurTile = TileMap->GetTileRef(_Index, _Order);

	if (true == TileMap->IsIndexOver(_Index))
	{
		return;
	}

	T = CurTile->TLogicType;
	if (T != ELogicType::NONE && true == IsLogicResult())
	{
		if (nullptr != StartLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)])
		{
			StartLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)]();
		}

		if (nullptr != UpdateLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)])
		{
			TileCombine.push_back(UpdateLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)]);
		}
	}

	return;
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 만약 규칙이 깨진 타일이 생길 경우
	// 따로 제거하지 않고
	// 매 프레임마다 clear되고
	YouTiles.clear();
	TileCombine.clear();

	// 다시 모든 TileCheck
	TileCheck();

	std::list<std::function<void()>>::iterator StartIter = TileCombine.begin();
	std::list<std::function<void()>>::iterator EndIter = TileCombine.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter;
	}

	Move();
}


