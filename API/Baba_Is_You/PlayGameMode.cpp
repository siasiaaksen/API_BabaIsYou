#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineString.h>

#include "ContentsEnum.h"
#include "TileMap.h"

StagePath APlayGameMode::StagePathValue;

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	State = EGameState::SELECT;

	TileMap = GetWorld()->SpawnActor<ATileMap>();
	TileMap->TileMapLoad(StagePathValue.GetPath());
	CreateStageInit(TileMap->GetTileCount(), true);
	Scale = TileMap->GetTileCount();

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

void APlayGameMode::OO_IS_ATTMoveSetting(ELogicType _FLogicType, ELogicType _TLogicType, ELogicType _CurObject, EMoveType _MoveType)
{
	StartLogic[static_cast<int>(_FLogicType)][static_cast<int>(EVLogicType::IS)][static_cast<int>(_TLogicType)]
		= [this, _FLogicType, _TLogicType, _CurObject, _MoveType]()
		{
			this->TileMap->ChangeMoveMode(_CurObject, _MoveType);
		};
}

void APlayGameMode::OO_IS_ATTStateSetting(ELogicType _FLogicType, ELogicType _TLogicType, ELogicType _CurObject, EStateType _StateType)
{
	StartLogic[static_cast<int>(_FLogicType)][static_cast<int>(EVLogicType::IS)][static_cast<int>(_TLogicType)]
		= [this, _FLogicType, _TLogicType, _CurObject, _StateType]()
		{
			this->TileMap->ChangeStateMode(_CurObject, _StateType);
		};
}

void APlayGameMode::MM_IS_NNSetting(ELogicType _FLogicType, ELogicType _TLogicType, ELogicType _CurObject, ELogicType _ChangeObject)
{
	StartLogic[static_cast<int>(_FLogicType)][static_cast<int>(EVLogicType::IS)][static_cast<int>(_TLogicType)]
		= [this, _FLogicType, _TLogicType, _CurObject, _ChangeObject]()
		{
			this->TileMap->SpriteChange(_CurObject, _ChangeObject);
			History NewH;
			NewH.PrevSprite = _CurObject;
			NewH.NextSprite = _ChangeObject;
			this->TileMap->PushHistory(NewH);
		};
}

bool APlayGameMode::IsMove()
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

void APlayGameMode::MoveCheck()
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

void APlayGameMode::UndoCheck()
{
	if (true == UEngineInput::GetInst().IsDown('Z'))
	{
		State = EGameState::UNDO;
		TileMap->SetActionTime(0.0f);
	}
}

bool APlayGameMode::IsLogicResult()
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

void APlayGameMode::TileCheck()
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
					ChangeSpriteCheck(CurIndex, i);

					NextTileCheck(CurIndex, FIntPoint{ 1, 0 }, i);
					NextTileCheck(CurIndex, FIntPoint{ 0, 1 }, i);
				}
			}
		}
	}
}

void APlayGameMode::NextTileCheck(FIntPoint _Index, FIntPoint _Dir, int _Order)
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
		//ChangeSpriteCheck(_Index, _Order);
		LastTileCheck(_Index + _Dir + _Dir, _Order);
	}

	return;
}

void APlayGameMode::LastTileCheck(FIntPoint _Index, int _Order)
{
	Tile* CurTile = TileMap->GetTileRef(_Index, _Order);

	if (nullptr == CurTile)
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
		}

		if (nullptr != UpdateLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)])
		{
			TileCombine.push_back(UpdateLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)]);
		}

		//ChangeSpriteCheck(_Index, _Order);
	}

	return;
}

void APlayGameMode::ChangeSpriteCheck(FIntPoint _Index, int _Order)
{
	Tile* CurTile = TileMap->GetTileRef(_Index, _Order);

	if (nullptr == CurTile || ELogicType::NONE == CurTile->FLogicType)
	{
		return;
	}

	if (ELogicType::WALLOBJECT == CurTile->FLogicType ||
		ELogicType::GRASSOBJECT == CurTile->FLogicType ||
		ELogicType::LAVAOBJECT == CurTile->FLogicType ||
		ELogicType::WATEROBJECT == CurTile->FLogicType)
	{
		bool Left = false;
		bool Right = false;
		bool Up = false;
		bool Down = false;

		if (nullptr != TileMap->GetTileRef(_Index + FIntPoint::LEFT, _Order))
		{
			Left = (!TileMap->IsIndexOver(_Index + FIntPoint::LEFT) &&
				TileMap->GetTileRef(_Index + FIntPoint::LEFT, _Order)->FLogicType == CurTile->FLogicType);
		}
		if (nullptr != TileMap->GetTileRef(_Index + FIntPoint::RIGHT, _Order))
		{
			Right = (!TileMap->IsIndexOver(_Index + FIntPoint::RIGHT) &&
				TileMap->GetTileRef(_Index + FIntPoint::RIGHT, _Order)->FLogicType == CurTile->FLogicType);
		}
		if (nullptr != TileMap->GetTileRef(_Index + FIntPoint::UP, _Order))
		{
			Up = (!TileMap->IsIndexOver(_Index + FIntPoint::UP) &&
				TileMap->GetTileRef(_Index + FIntPoint::UP, _Order)->FLogicType == CurTile->FLogicType);
		}
		if (nullptr != TileMap->GetTileRef(_Index + FIntPoint::DOWN, _Order))
		{
			Down = (!TileMap->IsIndexOver(_Index + FIntPoint::DOWN) &&
				TileMap->GetTileRef(_Index + FIntPoint::DOWN, _Order)->FLogicType == CurTile->FLogicType);
		}

		// 인덱스 찾기
		{
			if (false == Left && false == Right && false == Up && false == Down)
			{
				CurTile->SpriteIndex = 0;
			}
			else if (false == Left && true == Right && false == Up && false == Down)
			{
				CurTile->SpriteIndex = 1;
			}
			else if (false == Left && false == Right && true == Up && false == Down)
			{
				CurTile->SpriteIndex = 2;
			}
			else if (false == Left && true == Right && true == Up && false == Down)
			{
				CurTile->SpriteIndex = 3;
			}
			else if (true == Left && false == Right && false == Up && true == Down)
			{
				CurTile->SpriteIndex = 4;
			}
			else if (true == Left && true == Right && false == Up && false == Down)
			{
				CurTile->SpriteIndex = 5;
			}
			else if (true == Left && false == Right && true == Up && false == Down)
			{
				CurTile->SpriteIndex = 6;
			}
			else if (true == Left && true == Right && true == Up && false == Down)
			{
				CurTile->SpriteIndex = 7;
			}
			else if (false == Left && false == Right && false == Up && true == Down)
			{
				CurTile->SpriteIndex = 8;
			}
			else if (false == Left && true == Right && false == Up && true == Down)
			{
				CurTile->SpriteIndex = 9;
			}
			else if (false == Left && false == Right && true == Up && true == Down)
			{
				CurTile->SpriteIndex = 10;
			}
			else if (false == Left && true == Right && true == Up && true == Down)
			{
				CurTile->SpriteIndex = 11;
			}
			else if (true == Left && false == Right && false == Up && true == Down)
			{
				CurTile->SpriteIndex = 12;
			}
			else if (true == Left && true == Right && false == Up && true == Down)
			{
				CurTile->SpriteIndex = 13;
			}
			else if (true == Left && false == Right && true == Up && true == Down)
			{
				CurTile->SpriteIndex = 14;
			}
			else if (true == Left && true == Right && true == Up && true == Down)
			{
				CurTile->SpriteIndex = 15;
			}
		}

		CurTile->SpriteRenderer->SetSprite(CurTile->SpriteName, CurTile->SpriteIndex);
	}
}

void APlayGameMode::Action(float _DeltaTime)
{
	TileMap->Action(_DeltaTime);

	if (true == TileMap->IsActionEnd())
	{
		State = EGameState::SELECT;
	}
}

void APlayGameMode::Undo(float _DeltaTime)
{
	TileMap->Undo(_DeltaTime);

	if (true == TileMap->IsActionEnd())
	{
		State = EGameState::SELECT;
	}
}

void APlayGameMode::GameState(float _DeltaTime)
{
	switch (State)
	{
	case EGameState::SELECT:
		TileCombine.clear();

		TileMap->MoveTileTypeReset();
		TileMap->MoveTileStateReset();

		TileCheck();

		MoveCheck();
		UndoCheck();

		break;
	case EGameState::ACTION:
		Action(_DeltaTime);
		break;
	case EGameState::UNDO:
		Undo(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	GameState(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('P'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Map");
	}
}





