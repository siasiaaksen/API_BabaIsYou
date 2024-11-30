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

	GetWorld()->SetCameraToMainPawn(false);

	State = ETestGameState::SELECT;

	Scale = { 33, 18 };
	CreateStageInit(Scale);

	TileMap = GetWorld()->SpawnActor<ATileMap>();
	TileMap->Create(Scale, { 36, 36 });
	TileMap->SetActorLocation(CenterPivot);

	// TextTileMap
	{
		TileMap->SetTile("BabaText.png", { 1, 3 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::BABA, EVLogicType::NONE, ELogicType::BABA);
		TileMap->SetTile("Is.png", { 2, 3 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTile("Is.png", { 17, 6 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTile("Is.png", { 16, 7 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTile("Is.png", { 1, 4 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTile("Is.png", { 13, 3 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTile("Is.png", { 7, 9 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTile("Is.png", { 13, 2 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		//TileMap->SetTile("Is.png", { 17, 6 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		TileMap->SetTile("You.png", { 3, 3 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::YOU);
		TileMap->SetTile("FlagText.png", { 10, 2 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::FLAG, EVLogicType::NONE, ELogicType::FLAG);
		TileMap->SetTile("Win.png", { 14, 3 }, 1, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::WIN);
		TileMap->SetTile("RockText.png", { 12, 2 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::ROCK, EVLogicType::NONE, ELogicType::ROCK);
		//TileMap->SetTile("Push.png", { 14, 3 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::PUSH);
		TileMap->SetTile("Push.png", { 14, 2 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::PUSH);
		TileMap->SetTile("WallText.png", { 1, 2 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::WALL, EVLogicType::NONE, ELogicType::WALL);
		TileMap->SetTile("GrassText.png", { 16, 6 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::GRASS, EVLogicType::NONE, ELogicType::GRASS);
		TileMap->SetTile("Stop.png", { 18, 6 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::STOP);
		TileMap->SetTile("SkullText.png", { 24, 6 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::SKULL, EVLogicType::NONE, ELogicType::SKULL);
		TileMap->SetTile("Defeat.png", { 26, 6 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::DEFEAT);
		TileMap->SetTile("LavaText.png", { 6, 9 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::LAVA, EVLogicType::NONE, ELogicType::LAVA);
		TileMap->SetTile("Hot.png", { 8, 9 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::HOT);
		TileMap->SetTile("Melt.png", { 1, 5 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::MELT);
		TileMap->SetTile("WaterText.png", { 22, 15 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::WATER, EVLogicType::NONE, ELogicType::WATER);
		TileMap->SetTile("Sink.png", { 16, 8 }, 0, static_cast<int>(EFloorOrder::TEXT), ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::SINK);
	}

	// ObjectTileMap
	{
		// TileMap->SetTile("BabaObject.png", { 7, 14 }, 0, static_cast<int>(EFloorOrder::BABAOBJECT), ERenderOrder::UPPER, ELogicType::BABAOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("BabaObject.png", { 4, 15 }, 0, static_cast<int>(EFloorOrder::BABAOBJECT), ERenderOrder::UPPER, ELogicType::BABAOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("FlagObject.png", { 13, 14 }, 0, static_cast<int>(EFloorOrder::FLAGOBJECT), ERenderOrder::LOWER, ELogicType::FLAGOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("FlagObject.png", { 13, 15 }, 0, static_cast<int>(EFloorOrder::FLAGOBJECT), ERenderOrder::LOWER, ELogicType::FLAGOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("RockObject.png", { 2, 15 }, 0, static_cast<int>(EFloorOrder::ROCKOBJECT), ERenderOrder::LOWER, ELogicType::ROCKOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("RockObject.png", { 3, 15 }, 0, static_cast<int>(EFloorOrder::ROCKOBJECT), ERenderOrder::LOWER, ELogicType::ROCKOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("WallObject.png", { 1, 6 }, 0, static_cast<int>(EFloorOrder::WALLOBJECT), ERenderOrder::LOWER, ELogicType::WALLOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("GrassObject.png", { 1, 15 }, 0, static_cast<int>(EFloorOrder::GRASSOBJECT), ERenderOrder::LOWER, ELogicType::GRASSOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("SkullObject.png", { 22, 14 }, 0, static_cast<int>(EFloorOrder::SKULLOBJECT), ERenderOrder::LOWER, ELogicType::SKULLOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("LavaObject.png", { 26, 14 }, 0, static_cast<int>(EFloorOrder::LAVAOBJECT), ERenderOrder::LOWER, ELogicType::LAVAOBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("WaterObject.png", { 30, 14 }, 0, static_cast<int>(EFloorOrder::WATEROBJECT), ERenderOrder::LOWER, ELogicType::WATEROBJECT, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("TileObject.png", { 2, 15 }, 0, static_cast<int>(EFloorOrder::BG), ERenderOrder::LOWER, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
		TileMap->SetTile("TileObject.png", { 3, 15 }, 0, static_cast<int>(EFloorOrder::BG), ERenderOrder::LOWER, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
	}

	// LogicCombine
	{
		// 이러한 로직 조합일 때 이것을 준비해줘
		// 00 IS ATT
		{
			// StartLogic >> 00 IS YOU
			{
				OO_IS_ATTMoveSetting(ELogicType::BABA, ELogicType::YOU, ELogicType::BABAOBJECT, EMoveType::YOU);
				OO_IS_ATTMoveSetting(ELogicType::FLAG, ELogicType::YOU, ELogicType::FLAGOBJECT, EMoveType::YOU);
				OO_IS_ATTMoveSetting(ELogicType::ROCK, ELogicType::YOU, ELogicType::ROCKOBJECT, EMoveType::YOU);
				OO_IS_ATTMoveSetting(ELogicType::WALL, ELogicType::YOU, ELogicType::WALLOBJECT, EMoveType::YOU);
				OO_IS_ATTMoveSetting(ELogicType::GRASS, ELogicType::YOU, ELogicType::GRASSOBJECT, EMoveType::YOU);
				OO_IS_ATTMoveSetting(ELogicType::SKULL, ELogicType::YOU, ELogicType::SKULLOBJECT, EMoveType::YOU);
				OO_IS_ATTMoveSetting(ELogicType::LAVA, ELogicType::YOU, ELogicType::LAVAOBJECT, EMoveType::YOU);
				OO_IS_ATTMoveSetting(ELogicType::WATER, ELogicType::YOU, ELogicType::WATEROBJECT, EMoveType::YOU);
			}

			// StartLogic >> 00 IS WIN
			{
				OO_IS_ATTStateSetting(ELogicType::BABA, ELogicType::WIN, ELogicType::BABAOBJECT, EStateType::WIN);
				OO_IS_ATTStateSetting(ELogicType::FLAG, ELogicType::WIN, ELogicType::FLAGOBJECT, EStateType::WIN);
				OO_IS_ATTStateSetting(ELogicType::ROCK, ELogicType::WIN, ELogicType::ROCKOBJECT, EStateType::WIN);
				OO_IS_ATTStateSetting(ELogicType::WALL, ELogicType::WIN, ELogicType::WALLOBJECT, EStateType::WIN);
				OO_IS_ATTStateSetting(ELogicType::GRASS, ELogicType::WIN, ELogicType::GRASSOBJECT, EStateType::WIN);
				OO_IS_ATTStateSetting(ELogicType::SKULL, ELogicType::WIN, ELogicType::SKULLOBJECT, EStateType::WIN);
				OO_IS_ATTStateSetting(ELogicType::LAVA, ELogicType::WIN, ELogicType::LAVAOBJECT, EStateType::WIN);
				OO_IS_ATTStateSetting(ELogicType::WATER, ELogicType::WIN, ELogicType::WATEROBJECT, EStateType::WIN);
			}

			// StartLogic >> 00 IS PUSH
			{
				OO_IS_ATTMoveSetting(ELogicType::BABA, ELogicType::PUSH, ELogicType::BABAOBJECT, EMoveType::PUSH);
				OO_IS_ATTMoveSetting(ELogicType::FLAG, ELogicType::PUSH, ELogicType::FLAGOBJECT, EMoveType::PUSH);
				OO_IS_ATTMoveSetting(ELogicType::ROCK, ELogicType::PUSH, ELogicType::ROCKOBJECT, EMoveType::PUSH);
				OO_IS_ATTMoveSetting(ELogicType::WALL, ELogicType::PUSH, ELogicType::WALLOBJECT, EMoveType::PUSH);
				OO_IS_ATTMoveSetting(ELogicType::GRASS, ELogicType::PUSH, ELogicType::GRASSOBJECT, EMoveType::PUSH);
				OO_IS_ATTMoveSetting(ELogicType::SKULL, ELogicType::PUSH, ELogicType::SKULLOBJECT, EMoveType::PUSH);
				OO_IS_ATTMoveSetting(ELogicType::LAVA, ELogicType::PUSH, ELogicType::LAVAOBJECT, EMoveType::PUSH);
				OO_IS_ATTMoveSetting(ELogicType::WATER, ELogicType::PUSH, ELogicType::WATEROBJECT, EMoveType::PUSH);
			}

			// StartLogic >> 00 IS STOP
			{

				OO_IS_ATTMoveSetting(ELogicType::BABA, ELogicType::STOP, ELogicType::BABAOBJECT, EMoveType::STOP);
				OO_IS_ATTMoveSetting(ELogicType::FLAG, ELogicType::STOP, ELogicType::FLAGOBJECT, EMoveType::STOP);
				OO_IS_ATTMoveSetting(ELogicType::ROCK, ELogicType::STOP, ELogicType::ROCKOBJECT, EMoveType::STOP);
				OO_IS_ATTMoveSetting(ELogicType::WALL, ELogicType::STOP, ELogicType::WALLOBJECT, EMoveType::STOP);
				OO_IS_ATTMoveSetting(ELogicType::GRASS, ELogicType::STOP, ELogicType::GRASSOBJECT, EMoveType::STOP);
				OO_IS_ATTMoveSetting(ELogicType::SKULL, ELogicType::STOP, ELogicType::SKULLOBJECT, EMoveType::STOP);
				OO_IS_ATTMoveSetting(ELogicType::LAVA, ELogicType::STOP, ELogicType::LAVAOBJECT, EMoveType::STOP);
				OO_IS_ATTMoveSetting(ELogicType::WATER, ELogicType::STOP, ELogicType::WATEROBJECT, EMoveType::STOP);
			}

			// StartLogic >> 00 IS DEFEAT
			{
				OO_IS_ATTStateSetting(ELogicType::BABA, ELogicType::DEFEAT, ELogicType::BABAOBJECT, EStateType::DEFEAT);
				OO_IS_ATTStateSetting(ELogicType::FLAG, ELogicType::DEFEAT, ELogicType::FLAGOBJECT, EStateType::DEFEAT);
				OO_IS_ATTStateSetting(ELogicType::ROCK, ELogicType::DEFEAT, ELogicType::ROCKOBJECT, EStateType::DEFEAT);
				OO_IS_ATTStateSetting(ELogicType::WALL, ELogicType::DEFEAT, ELogicType::WALLOBJECT, EStateType::DEFEAT);
				OO_IS_ATTStateSetting(ELogicType::GRASS, ELogicType::DEFEAT, ELogicType::GRASSOBJECT, EStateType::DEFEAT);
				OO_IS_ATTStateSetting(ELogicType::SKULL, ELogicType::DEFEAT, ELogicType::SKULLOBJECT, EStateType::DEFEAT);
				OO_IS_ATTStateSetting(ELogicType::LAVA, ELogicType::DEFEAT, ELogicType::LAVAOBJECT, EStateType::DEFEAT);
				OO_IS_ATTStateSetting(ELogicType::WATER, ELogicType::DEFEAT, ELogicType::WATEROBJECT, EStateType::DEFEAT);
			}

			// StartLogic >> 00 IS HOT
			{
				OO_IS_ATTStateSetting(ELogicType::BABA, ELogicType::HOT, ELogicType::BABAOBJECT, EStateType::HOT);
				OO_IS_ATTStateSetting(ELogicType::FLAG, ELogicType::HOT, ELogicType::FLAGOBJECT, EStateType::HOT);
				OO_IS_ATTStateSetting(ELogicType::ROCK, ELogicType::HOT, ELogicType::ROCKOBJECT, EStateType::HOT);
				OO_IS_ATTStateSetting(ELogicType::WALL, ELogicType::HOT, ELogicType::WALLOBJECT, EStateType::HOT);
				OO_IS_ATTStateSetting(ELogicType::GRASS, ELogicType::HOT, ELogicType::GRASSOBJECT, EStateType::HOT);
				OO_IS_ATTStateSetting(ELogicType::SKULL, ELogicType::HOT, ELogicType::SKULLOBJECT, EStateType::HOT);
				OO_IS_ATTStateSetting(ELogicType::LAVA, ELogicType::HOT, ELogicType::LAVAOBJECT, EStateType::HOT);
				OO_IS_ATTStateSetting(ELogicType::WATER, ELogicType::HOT, ELogicType::WATEROBJECT, EStateType::HOT);
			}

			// StartLogic >> 00 IS MELT
			{
				OO_IS_ATTStateSetting(ELogicType::BABA, ELogicType::MELT, ELogicType::BABAOBJECT, EStateType::MELT);
				OO_IS_ATTStateSetting(ELogicType::FLAG, ELogicType::MELT, ELogicType::FLAGOBJECT, EStateType::MELT);
				OO_IS_ATTStateSetting(ELogicType::ROCK, ELogicType::MELT, ELogicType::ROCKOBJECT, EStateType::MELT);
				OO_IS_ATTStateSetting(ELogicType::WALL, ELogicType::MELT, ELogicType::WALLOBJECT, EStateType::MELT);
				OO_IS_ATTStateSetting(ELogicType::GRASS, ELogicType::MELT, ELogicType::GRASSOBJECT, EStateType::MELT);
				OO_IS_ATTStateSetting(ELogicType::SKULL, ELogicType::MELT, ELogicType::SKULLOBJECT, EStateType::MELT);
				OO_IS_ATTStateSetting(ELogicType::LAVA, ELogicType::MELT, ELogicType::LAVAOBJECT, EStateType::MELT);
				OO_IS_ATTStateSetting(ELogicType::WATER, ELogicType::MELT, ELogicType::WATEROBJECT, EStateType::MELT);
			}

			// StartLogic >> 00 IS SINK
			{
				OO_IS_ATTStateSetting(ELogicType::BABA, ELogicType::SINK, ELogicType::BABAOBJECT, EStateType::SINK);
				OO_IS_ATTStateSetting(ELogicType::FLAG, ELogicType::SINK, ELogicType::FLAGOBJECT, EStateType::SINK);
				OO_IS_ATTStateSetting(ELogicType::ROCK, ELogicType::SINK, ELogicType::ROCKOBJECT, EStateType::SINK);
				OO_IS_ATTStateSetting(ELogicType::WALL, ELogicType::SINK, ELogicType::WALLOBJECT, EStateType::SINK);
				OO_IS_ATTStateSetting(ELogicType::GRASS, ELogicType::SINK, ELogicType::GRASSOBJECT, EStateType::SINK);
				OO_IS_ATTStateSetting(ELogicType::SKULL, ELogicType::SINK, ELogicType::SKULLOBJECT, EStateType::SINK);
				OO_IS_ATTStateSetting(ELogicType::LAVA, ELogicType::SINK, ELogicType::LAVAOBJECT, EStateType::SINK);
				OO_IS_ATTStateSetting(ELogicType::WATER, ELogicType::SINK, ELogicType::WATEROBJECT, EStateType::SINK);
			}
		}


		// StartLogic >> MM IS NN
		{
			// StartLogic >> BABA IS 00
			{
				MM_IS_NNSetting(ELogicType::BABA, ELogicType::FLAG, ELogicType::BABAOBJECT, ELogicType::FLAGOBJECT);
				MM_IS_NNSetting(ELogicType::BABA, ELogicType::ROCK, ELogicType::BABAOBJECT, ELogicType::ROCKOBJECT);
				MM_IS_NNSetting(ELogicType::BABA, ELogicType::WALL, ELogicType::BABAOBJECT, ELogicType::WALLOBJECT);
				MM_IS_NNSetting(ELogicType::BABA, ELogicType::GRASS, ELogicType::BABAOBJECT, ELogicType::GRASSOBJECT);
				MM_IS_NNSetting(ELogicType::BABA, ELogicType::SKULL, ELogicType::BABAOBJECT, ELogicType::SKULLOBJECT);
				MM_IS_NNSetting(ELogicType::BABA, ELogicType::LAVA, ELogicType::BABAOBJECT, ELogicType::LAVAOBJECT);
				MM_IS_NNSetting(ELogicType::BABA, ELogicType::WATER, ELogicType::BABAOBJECT, ELogicType::WATEROBJECT);
			}

			// StartLogic >> 00 IS BABA
			{
				MM_IS_NNSetting(ELogicType::FLAG, ELogicType::BABA, ELogicType::FLAGOBJECT, ELogicType::BABAOBJECT);
				MM_IS_NNSetting(ELogicType::ROCK, ELogicType::BABA, ELogicType::ROCKOBJECT, ELogicType::BABAOBJECT);
				MM_IS_NNSetting(ELogicType::WALL, ELogicType::BABA, ELogicType::WALLOBJECT, ELogicType::BABAOBJECT);
				MM_IS_NNSetting(ELogicType::GRASS, ELogicType::BABA, ELogicType::GRASSOBJECT, ELogicType::BABAOBJECT);
				MM_IS_NNSetting(ELogicType::SKULL, ELogicType::BABA, ELogicType::SKULLOBJECT, ELogicType::BABAOBJECT);
				MM_IS_NNSetting(ELogicType::LAVA, ELogicType::BABA, ELogicType::LAVAOBJECT, ELogicType::BABAOBJECT);
				MM_IS_NNSetting(ELogicType::WATER, ELogicType::BABA, ELogicType::WATEROBJECT, ELogicType::BABAOBJECT);
			}

			// StartLogic >> FLAG IS 00
			{
				MM_IS_NNSetting(ELogicType::FLAG, ELogicType::ROCK, ELogicType::FLAGOBJECT, ELogicType::ROCKOBJECT);
				MM_IS_NNSetting(ELogicType::FLAG, ELogicType::WALL, ELogicType::FLAGOBJECT, ELogicType::WALLOBJECT);
				MM_IS_NNSetting(ELogicType::FLAG, ELogicType::GRASS, ELogicType::FLAGOBJECT, ELogicType::GRASSOBJECT);
				MM_IS_NNSetting(ELogicType::FLAG, ELogicType::SKULL, ELogicType::FLAGOBJECT, ELogicType::SKULLOBJECT);
				MM_IS_NNSetting(ELogicType::FLAG, ELogicType::LAVA, ELogicType::FLAGOBJECT, ELogicType::LAVAOBJECT);
				MM_IS_NNSetting(ELogicType::FLAG, ELogicType::WATER, ELogicType::FLAGOBJECT, ELogicType::WATEROBJECT);
			}

			// StartLogic >> ROCK IS 00
			{
				MM_IS_NNSetting(ELogicType::ROCK, ELogicType::FLAG, ELogicType::ROCKOBJECT, ELogicType::FLAGOBJECT);
				MM_IS_NNSetting(ELogicType::ROCK, ELogicType::WALL, ELogicType::ROCKOBJECT, ELogicType::WALLOBJECT);
				MM_IS_NNSetting(ELogicType::ROCK, ELogicType::GRASS, ELogicType::ROCKOBJECT, ELogicType::GRASSOBJECT);
				MM_IS_NNSetting(ELogicType::ROCK, ELogicType::SKULL, ELogicType::ROCKOBJECT, ELogicType::SKULLOBJECT);
				MM_IS_NNSetting(ELogicType::ROCK, ELogicType::LAVA, ELogicType::ROCKOBJECT, ELogicType::LAVAOBJECT);
				MM_IS_NNSetting(ELogicType::ROCK, ELogicType::WATER, ELogicType::ROCKOBJECT, ELogicType::WATEROBJECT);
			}

			// StartLogic >> WALL IS 00
			{
				MM_IS_NNSetting(ELogicType::WALL, ELogicType::FLAG, ELogicType::WALLOBJECT, ELogicType::FLAGOBJECT);
				MM_IS_NNSetting(ELogicType::WALL, ELogicType::ROCK, ELogicType::WALLOBJECT, ELogicType::ROCKOBJECT);
				MM_IS_NNSetting(ELogicType::WALL, ELogicType::GRASS, ELogicType::WALLOBJECT, ELogicType::GRASSOBJECT);
				MM_IS_NNSetting(ELogicType::WALL, ELogicType::SKULL, ELogicType::WALLOBJECT, ELogicType::SKULLOBJECT);
				MM_IS_NNSetting(ELogicType::WALL, ELogicType::LAVA, ELogicType::WALLOBJECT, ELogicType::LAVAOBJECT);
				MM_IS_NNSetting(ELogicType::WALL, ELogicType::WATER, ELogicType::WALLOBJECT, ELogicType::WATEROBJECT);
			}

			// StartLogic >> GRASS IS 00
			{
				MM_IS_NNSetting(ELogicType::GRASS, ELogicType::FLAG, ELogicType::GRASSOBJECT, ELogicType::FLAGOBJECT);
				MM_IS_NNSetting(ELogicType::GRASS, ELogicType::ROCK, ELogicType::GRASSOBJECT, ELogicType::ROCKOBJECT);
				MM_IS_NNSetting(ELogicType::GRASS, ELogicType::WALL, ELogicType::GRASSOBJECT, ELogicType::WALLOBJECT);
				MM_IS_NNSetting(ELogicType::GRASS, ELogicType::SKULL, ELogicType::GRASSOBJECT, ELogicType::SKULLOBJECT);
				MM_IS_NNSetting(ELogicType::GRASS, ELogicType::LAVA, ELogicType::GRASSOBJECT, ELogicType::LAVAOBJECT);
				MM_IS_NNSetting(ELogicType::GRASS, ELogicType::WATER, ELogicType::GRASSOBJECT, ELogicType::WATEROBJECT);
			}

			// StartLogic >> SKULL IS 00
			{
				MM_IS_NNSetting(ELogicType::SKULL, ELogicType::FLAG, ELogicType::SKULLOBJECT, ELogicType::FLAGOBJECT);
				MM_IS_NNSetting(ELogicType::SKULL, ELogicType::ROCK, ELogicType::SKULLOBJECT, ELogicType::ROCKOBJECT);
				MM_IS_NNSetting(ELogicType::SKULL, ELogicType::WALL, ELogicType::SKULLOBJECT, ELogicType::WALLOBJECT);
				MM_IS_NNSetting(ELogicType::SKULL, ELogicType::GRASS, ELogicType::SKULLOBJECT, ELogicType::GRASSOBJECT);
				MM_IS_NNSetting(ELogicType::SKULL, ELogicType::LAVA, ELogicType::SKULLOBJECT, ELogicType::LAVAOBJECT);
				MM_IS_NNSetting(ELogicType::SKULL, ELogicType::WATER, ELogicType::SKULLOBJECT, ELogicType::WATEROBJECT);
			}

			// StartLogic >> LAVA IS 00
			{
				MM_IS_NNSetting(ELogicType::LAVA, ELogicType::FLAG, ELogicType::LAVAOBJECT, ELogicType::FLAGOBJECT);
				MM_IS_NNSetting(ELogicType::LAVA, ELogicType::ROCK, ELogicType::LAVAOBJECT, ELogicType::ROCKOBJECT);
				MM_IS_NNSetting(ELogicType::LAVA, ELogicType::WALL, ELogicType::LAVAOBJECT, ELogicType::WALLOBJECT);
				MM_IS_NNSetting(ELogicType::LAVA, ELogicType::GRASS, ELogicType::LAVAOBJECT, ELogicType::GRASSOBJECT);
				MM_IS_NNSetting(ELogicType::LAVA, ELogicType::SKULL, ELogicType::LAVAOBJECT, ELogicType::SKULLOBJECT);
				MM_IS_NNSetting(ELogicType::LAVA, ELogicType::WATER, ELogicType::LAVAOBJECT, ELogicType::WATEROBJECT);
			}

			// StartLogic >> WATER IS 00
			{
				MM_IS_NNSetting(ELogicType::WATER, ELogicType::FLAG, ELogicType::WATEROBJECT, ELogicType::FLAGOBJECT);
				MM_IS_NNSetting(ELogicType::WATER, ELogicType::ROCK, ELogicType::WATEROBJECT, ELogicType::ROCKOBJECT);
				MM_IS_NNSetting(ELogicType::WATER, ELogicType::WALL, ELogicType::WATEROBJECT, ELogicType::WALLOBJECT);
				MM_IS_NNSetting(ELogicType::WATER, ELogicType::GRASS, ELogicType::WATEROBJECT, ELogicType::GRASSOBJECT);
				MM_IS_NNSetting(ELogicType::WATER, ELogicType::SKULL, ELogicType::WATEROBJECT, ELogicType::SKULLOBJECT);
				MM_IS_NNSetting(ELogicType::WATER, ELogicType::LAVA, ELogicType::WATEROBJECT, ELogicType::LAVAOBJECT);
			}
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

void ATestGameMode::OO_IS_ATTMoveSetting(ELogicType _FLogicType, ELogicType _TLogicType, ELogicType _CurObject, EMoveType _MoveType)
{
	StartLogic[static_cast<int>(_FLogicType)][static_cast<int>(EVLogicType::IS)][static_cast<int>(_TLogicType)]
		= [this, _CurObject, _MoveType]()
		{
			this->TileMap->ChangeMoveMode(_CurObject, _MoveType);
		};
}

void ATestGameMode::OO_IS_ATTStateSetting(ELogicType _FLogicType, ELogicType _TLogicType, ELogicType _CurObject, EStateType _StateType)
{
	StartLogic[static_cast<int>(_FLogicType)][static_cast<int>(EVLogicType::IS)][static_cast<int>(_TLogicType)]
		= [this, _CurObject, _StateType]()
		{
			this->TileMap->ChangeStateMode(_CurObject, _StateType);
		};
}

void ATestGameMode::MM_IS_NNSetting(ELogicType _FLogicType, ELogicType _TLogicType, ELogicType _CurObject, ELogicType _ChangeObject)
{
	StartLogic[static_cast<int>(_FLogicType)][static_cast<int>(EVLogicType::IS)][static_cast<int>(_TLogicType)]
		= [this, _CurObject, _ChangeObject]()
		{
			this->TileMap->SpriteChange(_CurObject, _ChangeObject);
			History NewH;
			NewH.PrevSprite = _CurObject;
			NewH.NextSprite = _ChangeObject;
			this->TileMap->PushHistory(NewH);
		};
}

bool ATestGameMode::IsMove()
{
	for (int y = 0; y < Scale.Y; y++)
	{
		for (int x = 0; x < Scale.X; x++)
		{
			FIntPoint Index = FIntPoint(x, y);

			for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
			{
				Tile* CurTile = TileMap->GetTileRef(Index, i);

				if (nullptr == CurTile)
				{
					continue;
				}

				if (EMoveType::YOU == CurTile->MoveType)
				{
					return true == CurTile->IsMove;
				}
			}
		}
	}

	return false;
}

void ATestGameMode::MoveCheck()
{
	if (false == IsMove())
	{
		return;
	}
	
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

void ATestGameMode::UndoCheck()
{
	if (true == UEngineInput::GetInst().IsDown('Z'))
	{
		State = ETestGameState::UNDO;
		TileMap->SetActionTime(0.0f);
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

				if (nullptr == CurTile)
				{
					continue;
				}

				F = CurTile->FLogicType;
				if (F != ELogicType::NONE)
				{
					NextTileCheck(CurIndex, FIntPoint{ 1, 0 }, i);
					NextTileCheck(CurIndex, FIntPoint{ 0, 1 }, i);

					if (CurTile->FloorOrder == static_cast<int>(EFloorOrder::TEXT) && true == IsFirstCombine)
					{
						CurTile->SpriteRenderer->SetSprite(CurTile->SpriteName, 1);

						IsFirstCombine = false;
					}
				}
			}
		}
	}
}

void ATestGameMode::NextTileCheck(FIntPoint _Index, FIntPoint _Dir, int _Order)
{
	Tile* CurTile = TileMap->GetTileRef(_Index + _Dir, _Order);

	if (nullptr == CurTile)
	{
		return;
	}

	if (true == TileMap->IsIndexOver(_Index + _Dir))
	{
		return; 
	}

	S = CurTile->SLogicType;
	if (S != EVLogicType::NONE)
	{
		LastTileCheck(_Index + _Dir + _Dir, _Order);

		if (CurTile->FloorOrder == static_cast<int>(EFloorOrder::TEXT) && true == IsSecondCombine)
		{
			CurTile->SpriteRenderer->SetSprite(CurTile->SpriteName, 1);

			IsFirstCombine = true;
			IsSecondCombine = false;
		}
	}

	return;
}

void ATestGameMode::LastTileCheck(FIntPoint _Index, int _Order)
{
	Tile* CurTile = TileMap->GetTileRef(_Index, _Order);

	if (nullptr ==CurTile)
	{
		return;
	}

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

			if (CurTile->FloorOrder == static_cast<int>(EFloorOrder::TEXT))
			{
				CurTile->SpriteRenderer->SetSprite(CurTile->SpriteName, 1);
				
				IsSecondCombine = true;
			}
		}

		if (nullptr != UpdateLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)])
		{
			TileCombine.push_back(UpdateLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)]);
		}
	}

	return;
}

void ATestGameMode::Action(float _DeltaTime)
{
	TileMap->Action(_DeltaTime);

	if (true == TileMap->IsActionEnd())
	{
		State = ETestGameState::SELECT;
	}
}

void ATestGameMode::Undo(float _DeltaTime)
{
	TileMap->Undo(_DeltaTime);

	if (true == TileMap->IsActionEnd())
	{
		State = ETestGameState::SELECT;
	}
}

void ATestGameMode::GameState(float _DeltaTime)
{
	switch (State)
	{
	case ETestGameState::SELECT:
		// 타일 모든 상태 체크, 데이터 옮겨짐

			// 만약 규칙이 깨진 타일이 생길 경우
			// 따로 제거하지 않고
			// 매 프레임마다 clear되고
			//YouTiles.clear();
		TileCombine.clear();

		TileMap->MoveTileTypeReset();
		TileMap->MoveTileStateReset();

		TileMap->ResetAllTextSprite();

		// 다시 모든 TileCheck
		TileCheck();

		MoveCheck();
		UndoCheck();

		break;
	case ETestGameState::ACTION:
		// 액터, 랜더러 이동(눈에 보이는 것)
		Action(_DeltaTime);
		break;
	case ETestGameState::UNDO:
		// 되돌리기
		Undo(_DeltaTime);
		break;
	default:
		break;
	}
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	GameState(_DeltaTime);
}


