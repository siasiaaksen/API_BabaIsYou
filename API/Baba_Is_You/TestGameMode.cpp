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

	//BGMPlayer = UEngineSound::Play("baba.ogg");

	Scale = { 33, 18 };

	CreateStageInit(Scale);

	TileMap = GetWorld()->SpawnActor<ATileMap>();
	TileMap->Create(Scale, { 36, 36 });
	TileMap->SetActorLocation(CenterPivot);

	// TextTileMap
	{
		TileMap->SetTile("BabaText.png", { 0, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::BABA, EVLogicType::NONE, ELogicType::BABA);
		TileMap->SetTile("Is.png", { 1, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTile("Is.png", { 7, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTile("You.png", { 2, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::YOU);
		TileMap->SetTile("You.png", { 1, 4 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::YOU);
		TileMap->SetTile("FlagText.png", { 12, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::FLAG, EVLogicType::NONE, ELogicType::FLAG);
		TileMap->SetTile("Win.png", { 18, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::WIN);
		TileMap->SetTile("RockText.png", { 1, 2 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::ROCK, EVLogicType::NONE, ELogicType::ROCK);
		TileMap->SetTile("Push.png", { 8, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::PUSH);
		TileMap->SetTile("WallText.png", { 6, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::WALL, EVLogicType::NONE, ELogicType::WALL);
		TileMap->SetTile("GrassText.png", { 12, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::GRASS, EVLogicType::NONE, ELogicType::GRASS);
		TileMap->SetTile("Stop.png", { 18, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::STOP);
		TileMap->SetTile("SkullText.png", { 24, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::SKULL, EVLogicType::NONE, ELogicType::SKULL);
		TileMap->SetTile("Defeat.png", { 30, 6 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::DEFEAT);
		TileMap->SetTile("LavaText.png", { 6, 9 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::LAVA, EVLogicType::NONE, ELogicType::LAVA);
		TileMap->SetTile("Hot.png", { 11, 14 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::HOT);
		TileMap->SetTile("Melt.png", { 18, 9 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::MELT);
		TileMap->SetTile("WaterText.png", { 24, 9 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::WATER, EVLogicType::NONE, ELogicType::WATER);
		TileMap->SetTile("Sink.png", { 30, 9 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::SINK);
	}

	// ObjectTileMap
	{
		TileMap->SetTile("BabaObject.png", { 13, 14 }, 0, static_cast<int>(EFloorOrder::BABAOBJECT), ERenderOrder::UPPER, ELogicType::BABAOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("FlagObject.png", { 6, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::FLAGOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("RockObject.png", { 10, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::ROCKOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("WallObject.png", { 14, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::WALLOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("GrassObject.png", { 18, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::GRASSOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("SkullObject.png", { 22, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::SKULLOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("LavaObject.png", { 26, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::LAVAOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("WaterObject.png", { 30, 14 }, 0, static_cast<int>(EFloorOrder::NONE), ERenderOrder::LOWER, ELogicType::WATEROBJECT, EVLogicType::NONE, ELogicType::NONE);
	}

	// LogicCombine
	{
		// 이러한 로직 조합일 때 이것을 준비해줘
		// StartLogic >> 00 IS YOU
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::BABAOBJECT, EMoveType::YOU);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::FLAGOBJECT, EMoveType::YOU);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::ROCKOBJECT, EMoveType::YOU);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::WALLOBJECT, EMoveType::YOU);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::GRASSOBJECT, EMoveType::YOU);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::SKULLOBJECT, EMoveType::YOU);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::YOU);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::WATEROBJECT, EMoveType::YOU);
				};
		}

		// StartLogic >> 00 IS WIN
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					//this->WinTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					//this->WinTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					//this->WinTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					//this->WinTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					//this->WinTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					//this->WinTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					//this->WinTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::WIN)]
				= [this]()
				{
					//this->WinTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS PUSH
		{
			//PushTiles.push_back(ELogicType::NONE);
			//PushTiles.push_back(ELogicType::BABA);
			//PushTiles.push_back(ELogicType::YOU);
			//PushTiles.push_back(ELogicType::FLAG);
			//PushTiles.push_back(ELogicType::WIN);
			//PushTiles.push_back(ELogicType::ROCK);
			//PushTiles.push_back(ELogicType::PUSH);
			//PushTiles.push_back(ELogicType::WALL);
			//PushTiles.push_back(ELogicType::GRASS);
			//PushTiles.push_back(ELogicType::STOP);
			//PushTiles.push_back(ELogicType::SKULL);
			//PushTiles.push_back(ELogicType::DEFEAT);
			//PushTiles.push_back(ELogicType::LAVA);
			//PushTiles.push_back(ELogicType::HOT);
			//PushTiles.push_back(ELogicType::MELT);
			//PushTiles.push_back(ELogicType::WATER);
			//PushTiles.push_back(ELogicType::SINK);
			//PushTiles.push_back(EVLogicType::IS);

			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::BABAOBJECT, EMoveType::PUSH);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::FLAGOBJECT, EMoveType::PUSH);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::ROCKOBJECT, EMoveType::PUSH);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::WALLOBJECT, EMoveType::PUSH);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::GRASSOBJECT, EMoveType::PUSH);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::SKULLOBJECT, EMoveType::PUSH);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::PUSH);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::PUSH)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::WATEROBJECT, EMoveType::PUSH);
				};
		}

		// StartLogic >> 00 IS STOP
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::STOP);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::STOP);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()

				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::STOP);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::STOP);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::STOP);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::STOP);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::STOP);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::STOP)]
				= [this]()
				{
					this->TileMap->ChangeMoveMode(ELogicType::LAVAOBJECT, EMoveType::STOP);
				};
		}

		// StartLogic >> 00 IS DEFEAT
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					//this->DefeatTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					//this->DefeatTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					//this->DefeatTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					//this->DefeatTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					//this->DefeatTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					//this->DefeatTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					//this->DefeatTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::DEFEAT)]
				= [this]()
				{
					//this->DefeatTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS HOT
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					//this->HotTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					//this->HotTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					//this->HotTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					//this->HotTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					//this->HotTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					//this->HotTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					//this->HotTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::HOT)]
				= [this]()
				{
					//this->HotTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS MELT
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					//this->MeltTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					//this->MeltTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					//this->MeltTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					//this->MeltTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					//this->MeltTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					//this->MeltTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					//this->MeltTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::MELT)]
				= [this]()
				{
					//this->MeltTiles.push_back(ELogicType::WATEROBJECT);
				};
		}

		// StartLogic >> 00 IS SINK
		{
			StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					//this->SinkTiles.push_back(ELogicType::BABAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					//this->SinkTiles.push_back(ELogicType::FLAGOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					//this->SinkTiles.push_back(ELogicType::ROCKOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					//this->SinkTiles.push_back(ELogicType::WALLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					//this->SinkTiles.push_back(ELogicType::GRASSOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					//this->SinkTiles.push_back(ELogicType::SKULLOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					//this->SinkTiles.push_back(ELogicType::LAVAOBJECT);
				};

			StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::SINK)]
				= [this]()
				{
					//this->SinkTiles.push_back(ELogicType::WATEROBJECT);
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

		TileCheck();
	}
}

void ATestGameMode::Move()
{
	if (true == UEngineInput::GetInst().IsDown('W') || true == UEngineInput::GetInst().IsDown(VK_UP))
	{
		TileMap->AllTileMoveCheck(FIntPoint::UP);
	}

	if (true == UEngineInput::GetInst().IsDown('A') || true == UEngineInput::GetInst().IsDown(VK_LEFT))
	{
		TileMap->AllTileMoveCheck(FIntPoint::LEFT);
	}

	if (true == UEngineInput::GetInst().IsDown('S') || true == UEngineInput::GetInst().IsDown(VK_DOWN))
	{
		TileMap->AllTileMoveCheck(FIntPoint::DOWN);
	}

	if (true == UEngineInput::GetInst().IsDown('D') || true == UEngineInput::GetInst().IsDown(VK_RIGHT))
	{
		TileMap->AllTileMoveCheck(FIntPoint::RIGHT);
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

			for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
			{
				Tile* CurTile = TileMap->GetTileRef(CurIndex, i);
				F = CurTile->FLogicType;
				if (F != ELogicType::NONE)
				{
					NextTileCheck(CurIndex, FIntPoint{ 1, 0 }, i);
					NextTileCheck(CurIndex, FIntPoint{ 0, 1 }, i);
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
	//YouTiles.clear();
	TileCombine.clear();


	TileMap->MoveTileTypeReset();

	// 다시 모든 TileCheck
	TileCheck();

	std::list<std::function<void()>>::iterator StartIter = TileCombine.begin();
	std::list<std::function<void()>>::iterator EndIter = TileCombine.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter;
	}

	Move();

	// 사운드 테스트
	//if (true == UEngineInput::GetInst().IsDown(VK_F3))
	//{
	//	BGMPlayer.OnOffSwtich();
	//}
}


