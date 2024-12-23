
#include "PreCompile.h"
#include "TileMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineString.h>
#include <EngineBase/EngineFile.h>

#include "TestGameMode.h"
#include "PlayGameMode.h"
#include "MapGameMode.h"
#include "BabaMapGameMode.h"


ATileMap::ATileMap()
{
}

ATileMap::~ATileMap()
{
	for (int y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];

		for (int x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile*>& VectorX = VectorY[x];

			std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile* CurTile = StartLeftIter->second;

				if (nullptr == CurTile)
				{
					continue;
				}

				CurTile->Destroy();
			}
		}
	}
}

void ATileMap::BeginPlay()
{
	Super::BeginPlay();

	Fade = GetWorld()->SpawnActor<AFade>();
	Winning = GetWorld()->SpawnActor<ACongratulations>();
	Winning->SetActive(false);
}

void ATileMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (int y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];

		for (int x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile*>& VectorX = VectorY[x];

			std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile* CurTile = StartLeftIter->second;

				if (nullptr == CurTile)
				{
					continue;
				}

				if (EMoveType::YOU == CurTile->MoveType)
				{
					int CurTileX = CurTile->GetActorLocation().iX() - TileSize.iX();
					int CurTileY = CurTile->GetActorLocation().iY() - TileSize.iY();
					FIntPoint CurTileIndex = LocationToIndex(FVector2D(CurTileX, CurTileY));
					//UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
					//UEngineDebug::CoreOutPutString("YouTilePos : " + CurTileIndex.ToString());
				}
			}
		}
	}

	if (true == UEngineInput::GetInst().IsDown('Q'))
	{
		UEngineDebug::SwitchIsDebug();
	}

	if (IsWinAnimed)
	{
		WinAfterFade();
	}

	if (IsFadeAnimed)
	{
		MoveMapLevel();
	}
}

void ATileMap::Create(FIntPoint _Count, FVector2D _TileSize)
{
	TileSize = _TileSize;
	TileCount = _Count;

	AllTiles.resize(_Count.Y);

	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		AllTiles[y].resize(_Count.X);
	}
}

FVector2D ATileMap::IndexToTileLocation(FIntPoint _Index)
{
	return FVector2D(_Index.X * TileSize.X, _Index.Y * TileSize.Y);
}

FIntPoint ATileMap::LocationToIndex(FVector2D _Location)
{
	FVector2D Location = _Location / TileSize;

	return FIntPoint(Location.iX(), Location.iY());
}

void ATileMap::SetTileLocation(std::string_view _Sprite, FVector2D _Location, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
{
	FVector2D TilePos = _Location - GetActorLocation();

	FIntPoint Point = LocationToIndex(TilePos);

	if (true == IsIndexOver(Point))
	{
		return;
	}

	SetTile(_Sprite, Point, _SpriteIndex, _FloorOrder, _Order, _FLogicType, _SLogicType, _TLogicType);
}

bool ATileMap::IsIndexOver(FIntPoint _Index)
{
	if (0 > _Index.X)
	{
		return true;
	}

	if (0 > _Index.Y)
	{
		return true;
	}

	if (TileCount.X - 1 < _Index.X)
	{
		return true;
	}

	if (TileCount.Y - 1 < _Index.Y)
	{
		return true;
	}

	return false;
}

// 이 인덱스의 타일은 이러한 속성을 갖게 해줘
void ATileMap::SetTile(std::string_view _Sprite, FIntPoint _Index, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
{
	SetTile(_Sprite, _Index, { 0, 0 }, TileSize, _SpriteIndex, _FloorOrder, _Order, _FLogicType, _SLogicType, _TLogicType);
}

void ATileMap::SetTile(std::string_view _Sprite, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	Tile* NewTilePtr = AllTiles[_Index.Y][_Index.X][_FloorOrder];

	// 해당 인덱스에 타일이 없으면 만들어
	if (nullptr == NewTilePtr)
	{
		NewTilePtr = GetWorld()->SpawnActor<Tile>();
		AllTiles[_Index.Y][_Index.X][_FloorOrder] = NewTilePtr;
		NewTilePtr->SpriteRenderer = NewTilePtr->CreateDefaultSubObject<USpriteRenderer>();
		NewTilePtr->SpriteRenderer->SetComponentScale(TileSize);
	}

	if (nullptr == NewTilePtr->SpriteRenderer)
	{
		NewTilePtr->SpriteRenderer = NewTilePtr->CreateDefaultSubObject<USpriteRenderer>();
		NewTilePtr->SpriteRenderer->SetComponentScale(TileSize);
	}

	// 타일의 스프라이트 랜더러 찾아서 스프라이트 세팅
	USpriteRenderer* FindSprite = NewTilePtr->SpriteRenderer;
	FindSprite->SetSprite(_Sprite, _SpriteIndex);
	FindSprite->SetComponentScale(_SpriteScale);
	FindSprite->SetOrder(_FloorOrder);

	// 타일의 위치, 피봇, 스케일, 스프라이트 인덱스 등등 지정
	FVector2D TileLocation = IndexToTileLocation(_Index);
	//                                                                    액터기반으로 바뀌면서 타일 각자의 위치를 더해줘야함
	NewTilePtr->SetActorLocation(TileLocation + TileSize.Half() + _Pivot + GetActorLocation());

	FVector2D CurTileLocation = NewTilePtr->GetActorLocation();
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FIntPoint MouseIndex = LocationToIndex(MousePos - GetActorLocation());

	NewTilePtr->FLogicType = _FLogicType;
	NewTilePtr->SLogicType = _SLogicType;
	NewTilePtr->TLogicType = _TLogicType;
	NewTilePtr->FloorOrder = _FloorOrder;
	NewTilePtr->Pivot = _Pivot;
	NewTilePtr->Scale = _SpriteScale;
	NewTilePtr->SpriteIndex = _SpriteIndex;
	NewTilePtr->Location = CurTileLocation;
	NewTilePtr->Index = MouseIndex;
	std::string UpperName = UEngineString::ToUpper(_Sprite);
	NewTilePtr->SpriteName = UpperName;
}

std::string_view ATileMap::FindSpriteName(ELogicType _FLogicType)
{
	FIntPoint Index;

	switch (_FLogicType)
	{
	case ELogicType::NONE:
		return "NONE";
		break;
	case ELogicType::BABA:
		return "BabaText.png";
		break;
	case ELogicType::FLAG:
		return "FlagText.png";
		break;
	case ELogicType::ROCK:
		return "RockText.png";
		break;
	case ELogicType::WALL:
		return "WallText.png";
		break;
	case ELogicType::GRASS:
		return "GrassText.png";
		break;
	case ELogicType::SKULL:
		return "SkullText.png";
		break;
	case ELogicType::LAVA:
		return "LavaText.png";
		break;
	case ELogicType::WATER:
		return "WaterText.png";
		break;
	case ELogicType::YOU:
		return "You.png";
		break;
	case ELogicType::WIN:
		return "Win.png";
		break;
	case ELogicType::PUSH:
		return "Push.png";
		break;
	case ELogicType::STOP:
		return "Stop.png";
		break;
	case ELogicType::DEFEAT:
		return "Defeat.png";
		break;
	case ELogicType::HOT:
		return "Hot.png";
		break;
	case ELogicType::MELT:
		return "Melt.png";
		break;
	case ELogicType::SINK:
		return "Sink.png";
		break;
	case ELogicType::MAX:
		return "MAX";
		break;
	case ELogicType::BABAOBJECT:
		return "BabaObject.png";
		break;
	case ELogicType::FLAGOBJECT:
		return "FlagObject.png";
		break;
	case ELogicType::ROCKOBJECT:
		return "RockObject.png";
		break;
	case ELogicType::WALLOBJECT:
		return "WallObject.png";
		break;
	case ELogicType::GRASSOBJECT:
		return "GrassObject.png";
		break;
	case ELogicType::SKULLOBJECT:
		return "SkullObject.png";
		break;
	case ELogicType::LAVAOBJECT:
		return "LavaObject.png";
		break;
	case ELogicType::WATEROBJECT:
		return "WaterObject.png";
		break;
	default:
		break;
	}
}

// 인덱스 0, 0부터 EMoveType::YOU인 타일 찾기
std::vector<FIntPoint> ATileMap::FindMoveTile()
{
	std::vector<FIntPoint> MoveTiles;

	for (int y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];

		for (int x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile*>& VectorX = VectorY[x];

			std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile* CurTile = StartLeftIter->second;

				if (nullptr == CurTile)
				{
					continue;
				}

				FIntPoint Index = FIntPoint(x, y);

				if (EMoveType::YOU != CurTile->MoveType)
				{
					continue;
				}

				MoveTiles.push_back(Index);
			}
		}
	}

	return MoveTiles;
}

void ATileMap::AllTileMoveCheck(FIntPoint _MoveDir)
{
	Histories.push_back(std::list<History>());
	LastHistories = &Histories.back();

	std::vector<FIntPoint> YouTiles = FindMoveTile();

	for (size_t i = 0; i < YouTiles.size(); i++)
	{
		TileMove(YouTiles[i], _MoveDir);
	}

	APlayGameMode* PGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	ATestGameMode* TGameMode = GetWorld()->GetGameMode<ATestGameMode>();

	// 이동한 타일이 있으면
	if (0 != LastHistories->size())
	{
		if (nullptr != PGameMode)
		{
			PGameMode->SetState(EGameState::ACTION);
		}

		if (nullptr != TGameMode)
		{
			TGameMode->SetState(ETestGameState::ACTION);
		}

		ActionTime = 0.0f;
	}
	else
	{
		Histories.pop_back();
	}
}

void ATileMap::TileMove(FIntPoint _CurIndex, FIntPoint _MoveIndex)
{
	FIntPoint NextIndex = _CurIndex + _MoveIndex;

	if (false == TileMoveCheck(_CurIndex, _MoveIndex))
	{
		return;
	}

	std::map<int, Tile*>& CurMap = AllTiles[_CurIndex.Y][_CurIndex.X];
	std::map<int, Tile*>& NextMap = AllTiles[NextIndex.Y][NextIndex.X];

	IsRecord = true;

	// 모든 타일층을 돌면서
	for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	{
		// CurMap의 i층에 타일이 있어?
		if (false == CurMap.contains(i))
		{
			continue;
		}

		Tile* CurTile = CurMap[i];

		if (nullptr == CurTile)
		{
			continue;
		}
		else
		{
			EStateType CurStateType = CurTile->StateType;
			EMoveType CurMoveType = CurTile->MoveType;
			USpriteRenderer* CurSprite = CurTile->SpriteRenderer;

			if (CurMoveType != EMoveType::YOU && CurMoveType != EMoveType::PUSH)
			{
				continue;
			}

			if (nullptr == CurSprite)
			{
				continue;
			}

			// 다음 타일이 비어있어?
			bool IsEmpty = IsVoid(NextIndex);

			if (IsEmpty)
			{
				if (IsRecord)
				{
					History NewH;
					NewH.Tile = CurTile;
					NewH.Prev = _CurIndex;
					NewH.Next = NextIndex;
					NewH.PrevSpriteIndex = CurTile->SpriteIndex;
					NewH.NextSpriteIndex = ChangeSpriteIndex;

					LastHistories->push_back(NewH);
				}
			}
			else
			{
				for (int j = 0; j < static_cast<int>(EFloorOrder::MAX); j++)
				{
					if (!NextMap.contains(j))
					{
						continue;
					}

					Tile* NextTile = NextMap[j];

					if (nullptr == NextTile)
					{
						continue;
					}

					if (EMoveType::PUSH == NextTile->MoveType)
					{
						// 내가 그녀석을 조사해줘야 한다.
						TileMove(NextIndex, _MoveIndex);
					}
				}

				if (IsRecord)
				{
					History NewH;
					NewH.Tile = CurTile;
					NewH.Prev = _CurIndex;
					NewH.Next = NextIndex;
					NewH.PrevSpriteIndex = CurTile->SpriteIndex;
					NewH.NextSpriteIndex = ChangeSpriteIndex;

					LastHistories->push_back(NewH);

					IsRecord = true;
				}
			}
		}
	}

	return;
}

// 다음 인덱스에 타일이 존재해?
bool ATileMap::TileMoveCheck(FIntPoint _CurIndex, FIntPoint _MoveIndex)
{
	FIntPoint NextIndex = _CurIndex + _MoveIndex;

	if (true == IsIndexOver(NextIndex))
	{
		return false;
	}

	if (IsVoid(NextIndex) == true)
	{
		return true;
	}

	std::map<int, Tile*>& CurMap = AllTiles[_CurIndex.Y][_CurIndex.X];
	std::map<int, Tile*>& NextMap = AllTiles[NextIndex.Y][NextIndex.X];

	if (true == NextMap.empty())
	{
		return true;
	}

	for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	{
		if (false == CurMap.contains(i))
		{
			continue;
		}

		Tile* CurTile = CurMap[i];

		if (nullptr != CurTile && ELogicType::NONE != CurTile->FLogicType)
		{
			USpriteRenderer* CurSprite = CurMap[i]->SpriteRenderer;

			if (nullptr == CurSprite)
			{
				continue;
			}

			if (EMoveType::YOU != CurMap[i]->MoveType && EMoveType::PUSH != CurMap[i]->MoveType)
			{
				continue;
			}

			if (EMoveType::STOP == CurMap[i]->MoveType)
			{
				IsRecord = false;
				return false;
			}

			for (int j = 0; j < static_cast<int>(EFloorOrder::MAX); j++)
			{
				if (false == NextMap.contains(j))
				{
					continue;
				}

				Tile* FindTile = NextMap[j];

				if (nullptr != FindTile)
				{
					if (EMoveType::STOP == NextMap[j]->MoveType)
					{
						IsRecord = false;
						return false;
					}

					if (EMoveType::NONE == NextMap[j]->MoveType)
					{
						return true;
					}
				}
			}

			if (IsVoid(NextIndex) == false)
			{
				return TileMoveCheck(NextIndex, _MoveIndex);
			}
		}
	}

	return true;
}

// 다음 인덱스에 타일이 존재해?
bool ATileMap::IsVoid(FIntPoint _NextIndex)
{
	std::map<int, Tile*>& NextMap = AllTiles[_NextIndex.Y][_NextIndex.X];

	for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	{
		if (nullptr == NextMap[i])
		{
			continue;
		}

		return NextMap.empty();
	}
}

Tile* ATileMap::GetTileRef(FVector2D _Location, int _FloorOrder)
{
	FIntPoint Point = LocationToIndex(_Location);

	return GetTileRef(Point, _FloorOrder);
}

Tile* ATileMap::GetTileRef(FIntPoint _Index, int _FloorOrder)
{
	if (true == IsIndexOver(_Index))
	{
		return nullptr;
	}

	if (false == AllTiles[_Index.Y][_Index.X].contains(_FloorOrder))
	{
		return nullptr;
	}

	return AllTiles[_Index.Y][_Index.X][_FloorOrder];
}

void ATileMap::ResetAllTextSprite()
{
	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];
		for (size_t x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile*>& VectorX = VectorY[x];

			std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile* CurTile = StartLeftIter->second;

				if (nullptr == CurTile)
				{
					continue;
				}

				if (CurTile->FloorOrder == static_cast<int>(EFloorOrder::TEXT))
				{
					CurTile->SpriteRenderer->SetSprite(CurTile->SpriteName, 0);
				}
			}
		}
	}
}

// 모든 타일의 MoveType 리셋
void ATileMap::MoveTileTypeReset()
{
	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];
		for (size_t x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile*>& VectorX = VectorY[x];

			std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile* CurTile = StartLeftIter->second;

				if (nullptr == CurTile)
				{
					continue;
				}

				if (CurTile->FloorOrder != static_cast<int>(EFloorOrder::TEXT))
				{
					CurTile->MoveType = EMoveType::NONE;
				}
				else
				{
					CurTile->MoveType = EMoveType::PUSH;
				}
			}
		}
	}
}

// 모든 타일의 StateType 리셋
void ATileMap::MoveTileStateReset()
{
	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];
		for (size_t x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile*>& VectorX = VectorY[x];

			std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile* CurTile = StartLeftIter->second;

				if (nullptr == CurTile)
				{
					continue;
				}

				CurTile->StateType = EStateType::NONE;
			}
		}
	}
}

// MM의 타일 스프라이트 -> NN의 타일 스프라이트로 교체
void ATileMap::SpriteChange(ELogicType _CurSprite, ELogicType _ChangeSprite)
{
	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];
		for (size_t x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile*>& VectorX = VectorY[x];

			std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile* CurTile = StartLeftIter->second;

				if (nullptr == CurTile)
				{
					continue;
				}

				if (CurTile->FLogicType == _CurSprite)
				{
					CurTile->IsChange = true;
					int SpriteIndex = 0;
					std::string_view SpriteName = FindSpriteName(_ChangeSprite);
					std::string UpperName = UEngineString::ToUpper(SpriteName);
					CurTile->SpriteName = UpperName;
					CurTile->FLogicType = _ChangeSprite;
					CurTile->SpriteRenderer->SetSprite(UpperName, SpriteIndex);
					CurTile->SpriteIndex = SpriteIndex;
				}
			}
		}
	}
}

// 완성된 로직 조합 조건에 따른 해당 타일의 MoveType 변경
void ATileMap::ChangeMoveMode(ELogicType _FLogicType, EMoveType _MoveType)
{
	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];
		for (size_t x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile*>& VectorX = VectorY[x];

			std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile* CurTile = StartLeftIter->second;

				if (nullptr == CurTile)
				{
					continue;
				}

				if (false == CurTile->SpriteRenderer->IsActive())
				{
					continue;
				}

				if (_FLogicType != CurTile->FLogicType)
				{
					continue;
				}

				if (EMoveType::PUSH == CurTile->MoveType)
				{
					continue;
				}

				CurTile->MoveType = _MoveType;
			}
		}
	}
}

// 완성된 로직 조합 조건에 따른 해당 타일의 StateType 변경
void ATileMap::ChangeStateMode(ELogicType _FLogicType, EStateType _StateType)
{
	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];
		for (size_t x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile*>& VectorX = VectorY[x];

			std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile* CurTile = StartLeftIter->second;

				if (nullptr == CurTile)
				{
					continue;
				}

				if (false == CurTile->SpriteRenderer->IsActive())
				{
					continue;
				}

				if (_FLogicType != CurTile->FLogicType)
				{
					continue;
				}

				if (EMoveType::PUSH == CurTile->MoveType)
				{
					CurTile->StateType = EStateType::NONE;
				}
				else
				{
					CurTile->StateType = _StateType;
				}

			}
		}
	}
}

void ATileMap::RemoveTile(FIntPoint _Index)
{
	std::map<int, Tile*>& CurMap = AllTiles[_Index.Y][_Index.X];

	for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	{
		std::map<int, Tile*>::iterator StartIter = CurMap.find(i);

		if (false == CurMap.contains(i))
		{
			continue;
		}
		else
		{
			Tile* Tile = StartIter->second;
			Tile->Destroy();
			CurMap.erase(StartIter);
		}
	}
}

void ATileMap::RemoveAllTile()
{
	for (int y = 0; y < AllTiles.size(); y++)
	{
		for (int x = 0; x < AllTiles[y].size(); x++)
		{
			for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
			{
				if (false == AllTiles[y][x].contains(i))
				{
					continue;
				}
				else
				{
					AllTiles[y][x][i]->Destroy();
					AllTiles[y][x].erase(i);
				}
			}
		}
	}
}

void ATileMap::Serialize(UEngineSerializer& _Ser)
{
	//_Ser << TileCount;
	//_Ser << TileSize;
	//_Ser << AllTiles;
}

void ATileMap::DeSerialize(UEngineSerializer& _Ser)
{
	//_Ser >> TileCount;
	//_Ser >> TileSize;

	//std::vector<std::vector<std::map<int, Tile*>>> LoadTiles;
	//_Ser >> LoadTiles;

	//Create(TileCount, TileSize);

	//for (int y = 0; y < LoadTiles.size(); y++)
	//{
	//	for (int x = 0; x < LoadTiles[y].size(); x++)
	//	{
	//		for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	//		{
	//			Tile* CurTile = LoadTiles[y][x][i];
	//			ERenderOrder Order = ERenderOrder::NONE;

	//			if (CurTile->FloorOrder == 8 || CurTile->FloorOrder == 9)
	//			{
	//				Order = ERenderOrder::UPPER;
	//			}
	//			else
	//			{
	//				Order = ERenderOrder::LOWER;
	//			}

	//			//SetTile(CurTile->SpriteRenderer, CurTile->Index, CurTile->SpriteIndex, CurTile->FloorOrder, Order,
	//			//	static_cast<ELogicType>(CurTile->FLogicType), static_cast<EVLogicType>(CurTile->SLogicType),
	//			//	static_cast<ELogicType>(CurTile->TLogicType));
	//		}
	//	}
	//}
}

void ATileMap::Action(float _DeltaTime)
{
	std::list<History>& Last = Histories.back();

	LastHistories = &Last;

	// Action 맨 처음
	if (0.0f == ActionTime)
	{
		ActionAllTile.clear();

		for (int y = 0; y < AllTiles.size(); y++)
		{
			std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];

			for (int x = 0; x < VectorY.size(); x++)
			{
				std::map<int, Tile*>& VectorX = VectorY[x];

				std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
				std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

				for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
				{
					Tile* CurTile = StartLeftIter->second;
					if (nullptr == CurTile)
					{
						continue;
					}

					ActionAllTile.push_back(CurTile);
				}

				VectorX.clear();
			}
		}
	}

	ActionTime += _DeltaTime * 10.0f;

	// ActionTime이 끝난 후
	if (1.0f <= ActionTime)
	{
		for (size_t i = 0; i < ActionAllTile.size(); i++)
		{
			Tile* CurTile = ActionAllTile[i];

			if (nullptr == CurTile)
			{
				continue;
			}

			FIntPoint thisPoint = LocationToIndex(GetActorLocation());
			FIntPoint Point = LocationToIndex(CurTile->GetActorLocation() - GetActorLocation());

			AllTiles[Point.Y][Point.X][CurTile->FloorOrder] = CurTile;
		}

		std::list<History>::iterator StartIter = LastHistories->begin();
		std::list<History>::iterator EndIter = LastHistories->end();

		for (; StartIter != EndIter; ++StartIter)
		{
			History& History = *StartIter;

			Tile* CurTile = History.Tile;

			if (nullptr == CurTile)
			{
				continue;
			}

			if (EMoveType::YOU == CurTile->MoveType && ELogicType::BABAOBJECT == CurTile->FLogicType)
			{
				for (int y = 0; y < AllTiles.size(); y++)
				{
					std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];

					for (int x = 0; x < VectorY.size(); x++)
					{
						std::map<int, Tile*>& VectorX = VectorY[x];

						std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
						std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

						for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
						{
							FIntPoint Index = FIntPoint(x, y);

							if (CurTile->SpriteIndex == History.PrevSpriteIndex)
							{
								CurTile->SpriteIndex = History.NextSpriteIndex;
								CurTile->SpriteRenderer->SetSprite(CurTile->SpriteName, CurTile->SpriteIndex);
							}
						}
					}
				}
			}

			for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
			{
				std::map<int, Tile*> OtherTile = AllTiles[History.Next.Y][History.Next.X];

				if (!OtherTile.contains(i))
				{
					continue;
				}
				else
				{
					Tile* FindTile = OtherTile[i];

					if (nullptr != FindTile)
					{
						if (EStateType::DEFEAT == FindTile->StateType)
						{
							// DEFEAT
							if (EMoveType::YOU == CurTile->MoveType)
							{
								History.State = EState::DEACTIVEONE;
								
								SoundPlayer = UEngineSound::Play("DefeatDeadSound.ogg");

								CurTile->SpriteRenderer->SetActive(false);
								CurTile->IsMove = false;
							}
						}
						// SINK
						else if (EStateType::SINK == FindTile->StateType)
						{
							History.State = EState::DEACTIVEBOTH;

							if (FindTile->StateType == EStateType::SINK)
							{
								SoundPlayer = UEngineSound::Play("WaterSinkDead.ogg");

								CurTile->SpriteRenderer->SetActive(false);
								FindTile->SpriteRenderer->SetActive(false);
								CurTile->IsMove = false;
								FindTile->IsMove = false;
							}
						}
						// HOT
						else if (EStateType::MELT == CurTile->StateType && EStateType::HOT == FindTile->StateType)
						{
							History.State = EState::DEACTIVEONE;

							SoundPlayer = UEngineSound::Play("LavaMeltSound.ogg");

							CurTile->SpriteRenderer->SetActive(false);
							CurTile->IsMove = false;
						}
						// WIN
						else if (EStateType::WIN == FindTile->StateType)
						{
							if (EMoveType::YOU == CurTile->MoveType)
							{
								History.State = EState::DEACTIVEONE;
								CurTile->IsMove = false;

								SoundPlayer = UEngineSound::Play("Win.ogg");

								Winning->SetActive(true);
								Winning->Winning();
								
								APlayGameMode* PGameMode = GetWorld()->GetGameMode<APlayGameMode>();
								if (nullptr != PGameMode)
								{
									PGameMode->GetBGMPlayer().Off();
								}

								IsWinAnimed = true;
							}
						}
					}
				}
			}
		}

		ActionTime = 1.0f;
		return;
	}

	// ActionTime동안 이동하면서 벌어지는
	{
		std::list<History>::iterator StartIter = LastHistories->begin();
		std::list<History>::iterator EndIter = LastHistories->end();

		for (; StartIter != EndIter; ++StartIter)
		{
			History& History = *StartIter;
			Tile* CurTile = History.Tile;

			if (nullptr == CurTile)
			{
				MSGASSERT("말도 안되는 상황입니다.");
			}

			if (CurTile->MoveType != EMoveType::NONE)
			{
				FVector2D StartPos = History.Prev.ConvertToVector();
				FVector2D EndPos = History.Next.ConvertToVector();
				StartPos *= TileSize;
				EndPos *= TileSize;

				StartPos += GetActorLocation() + TileSize.Half();
				EndPos += GetActorLocation() + TileSize.Half();

				// ActionTime 동안 StartPos에서 EndPos로 이동
				FVector2D CurPos = FVector2D::Lerp(StartPos, EndPos, ActionTime);
				CurTile->SetActorLocation(CurPos);
			}
		}
	}
}

void ATileMap::Undo(float _DeltaTime)
{
	if (0.0f == ActionTime)
	{
		ActionAllTile.clear();

		for (int y = 0; y < AllTiles.size(); y++)
		{
			std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];

			for (int x = 0; x < VectorY.size(); x++)
			{
				std::map<int, Tile*>& VectorX = VectorY[x];

				std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
				std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

				for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
				{
					Tile* CurTile = StartLeftIter->second;
					if (nullptr == CurTile)
					{
						continue;
					}
					ActionAllTile.push_back(CurTile);
				}

				VectorX.clear();
			}
		}
	}

	ActionTime += _DeltaTime * 10.0f;

	// ActionTime이 끝난 후
	if (1.0f <= ActionTime)
	{
		for (size_t i = 0; i < ActionAllTile.size(); i++)
		{
			Tile* CurTile = ActionAllTile[i];

			if (nullptr == CurTile)
			{
				continue;
			}

			FIntPoint thisPoint = LocationToIndex(GetActorLocation());
			FIntPoint Point = LocationToIndex(CurTile->GetActorLocation() - GetActorLocation());

			AllTiles[Point.Y][Point.X][CurTile->FloorOrder] = CurTile;
		}

		std::list<std::list<History>>::iterator BeginIter = Histories.end();

		if (Histories.empty())
		{
			return;
		}

		--BeginIter;

		std::list<History> LastHistories = Histories.back();
		std::list<History>::iterator StartIter = LastHistories.end();
		std::list<History>::iterator EndIter = LastHistories.begin();

		for (; StartIter != EndIter;)
		{
			--StartIter;

			History& History = *StartIter;
			Tile* CurTile = History.Tile;

			if (ELogicType::NONE != History.PrevSprite || ELogicType::NONE != History.NextSprite)
			{
				for (int y = 0; y < AllTiles.size(); y++)
				{
					std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];

					for (int x = 0; x < VectorY.size(); x++)
					{
						std::map<int, Tile*>& VectorX = VectorY[x];

						std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
						std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

						for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
						{
							Tile* CurSpriteTile = StartLeftIter->second;

							if (nullptr == CurSpriteTile)
							{
								continue;
							}

							FIntPoint Index = FIntPoint(x, y);

							if (CurSpriteTile->FLogicType == History.NextSprite && CurSpriteTile->IsChange == true)
							{
								int SpriteIndex = 0;
								std::string_view SpriteName = FindSpriteName(History.PrevSprite);
								std::string UpperName = UEngineString::ToUpper(SpriteName);
								CurSpriteTile->SpriteName = UpperName;
								CurSpriteTile->FLogicType = History.PrevSprite;
								CurSpriteTile->SpriteRenderer->SetSprite(UpperName, 0);
								CurSpriteTile->IsChange = false;
							}
						}
					}
				}
			}

			if (nullptr == CurTile)
			{
				continue;
			}

			if (EMoveType::YOU == CurTile->MoveType && ELogicType::BABAOBJECT == CurTile->FLogicType)
			{
				for (int y = 0; y < AllTiles.size(); y++)
				{
					std::vector<std::map<int, Tile*>>& VectorY = AllTiles[y];

					for (int x = 0; x < VectorY.size(); x++)
					{
						std::map<int, Tile*>& VectorX = VectorY[x];

						std::map<int, Tile*>::iterator StartLeftIter = VectorX.begin();
						std::map<int, Tile*>::iterator EndLeftIter = VectorX.end();

						for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
						{
							FIntPoint Index = FIntPoint(x, y);

							if (CurTile->SpriteIndex == History.NextSpriteIndex)
							{
								CurTile->SpriteIndex = History.PrevSpriteIndex;
								CurTile->SpriteRenderer->SetSprite(CurTile->SpriteName, CurTile->SpriteIndex);
							}
						}
					}
				}
			}

			int CurFloorOrder = CurTile->FloorOrder;

			for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
			{
				std::map<int, Tile*> OtherTile = AllTiles[History.Next.Y][History.Next.X];

				if (false == OtherTile.contains(i))
				{
					continue;
				}

				Tile* FindTile = OtherTile[i];

				if (nullptr != FindTile)
				{
					// DEFEAT, HOT
					if (History.State == EState::DEACTIVEONE)
					{
						if (false == CurTile->SpriteRenderer->IsActive())
						{
							CurTile->SpriteRenderer->SetActive(true);

							GameOverSound.Off();

							APlayGameMode* PGameMode = GetWorld()->GetGameMode<APlayGameMode>();
							if (nullptr != PGameMode)
							{
								PGameMode->GetBGMPlayer().On();
							}
						}

						CurTile->IsMove = true;
					}
					// SINK
					else if (History.State == EState::DEACTIVEBOTH)
					{
						CurTile->SpriteRenderer->SetActive(true);
						CurTile->IsMove = true;
						FindTile->SpriteRenderer->SetActive(true);
						FindTile->IsMove = true;

						GameOverSound.Off();

						APlayGameMode* PGameMode = GetWorld()->GetGameMode<APlayGameMode>();
						if (nullptr != PGameMode)
						{
							PGameMode->GetBGMPlayer().On();
						}
					}
				}
			}
		}

		ActionTime = 1.0f;
		if (!Histories.empty())
		{
			Histories.pop_back();
		}
		return;
	}

	std::list<std::list<History>>::iterator StartIter = Histories.end();
	std::list<std::list<History>>::iterator EndIter = Histories.begin();

	if (!Histories.empty())
	{
		--StartIter;

		std::list<History>& InnerList = *StartIter;

		std::list<History>::iterator InnerStartIter = InnerList.end();
		std::list<History>::iterator InnerEndIter = InnerList.begin();

		for (; InnerStartIter != InnerEndIter;)
		{
			--InnerStartIter;

			History& History = *InnerStartIter;
			Tile* CurTile = History.Tile;

			if (ELogicType::NONE != History.PrevSprite || ELogicType::NONE != History.NextSprite)
			{
				continue;
			}

			if (nullptr == CurTile)
			{
				MSGASSERT("말도 안되는 상황입니다.");
			}

			FVector2D StartPos = History.Next.ConvertToVector();
			FVector2D EndPos = History.Prev.ConvertToVector();
			StartPos *= TileSize;
			EndPos *= TileSize;

			StartPos += GetActorLocation() + TileSize.Half();
			EndPos += GetActorLocation() + TileSize.Half();

			FVector2D CurPos = FVector2D::Lerp(StartPos, EndPos, ActionTime);
			CurTile->SetActorLocation(CurPos);
			FVector2D CurTilePos = CurTile->GetActorLocation();
			CurTile->Location = CurTilePos;
			FIntPoint TileIndex = LocationToIndex(CurTilePos - TileSize);
			CurTile->Index = TileIndex;
			int a = 0;
		}
	}
}

void ATileMap::TileMapSave(const std::string Path)
{
	UEngineSerializer Ser;

	Ser << TileSize;
	Ser << TileCount;

	std::vector<TileData> TileDatas;

	for (int y = 0; y < AllTiles.size(); y++)
	{
		for (int x = 0; x < AllTiles[y].size(); x++)
		{
			for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
			{
				if (false == AllTiles[y][x].contains(i))
				{
					continue;
				}

				Tile* TilePtr = AllTiles[y][x][i];

				TileData Data = TilePtr->GetTileData();
				TileDatas.push_back(Data);
			}
		}
	}

	Ser << TileDatas;

	UEngineFile FIle = Path;
	FIle.FileOpen("wb");
	FIle.Write(Ser);
}

void ATileMap::TileMapLoad(const std::string Path)
{
	RemoveAllTile();

	UEngineFile FIle = Path;
	FIle.FileOpen("rb");

	UEngineSerializer Ser;
	FIle.Read(Ser);

	Ser >> TileSize;
	Ser >> TileCount;

	// Create
	Create(TileCount, TileSize);

	FVector2D CenterPivot;
	CenterPivot.X = (1280 - (TileCount.X * 36)) / 2;
	CenterPivot.Y = (720 - (TileCount.Y * 36)) / 2;
	SetActorLocation(CenterPivot);

	std::vector<TileData> TileDatas;
	Ser >> TileDatas;

	// N개의 타일 데이터
	// SetTile
	for (int i = 0; i < TileDatas.size(); i++)
	{
		TileData& TData = TileDatas[i];
		SetTile(TData.Sprite, TData.Index, TData.Pivot = {0, 0}, TData.SpriteScale, TData.SpriteIndex, TData.FloorOrder, TData.Order,
			TData.FLogicType, TData.SLogicType, TData.TLogicType);
	}
}

void ATileMap::WinAfterFade()
{
	IsWinAnimEnd = Winning->GetSRenderer()->IsCurAnimationEnd();

	if (IsWinAnimEnd)
	{
		Fade->FadeOut();
		IsFadeAnimed = true;

		IsWinAnimed = false;
	}
}

void ATileMap::MoveMapLevel()
{
	IsFadeAnimEnd = Fade->GetSRenderer()->IsCurAnimationEnd();

	if (IsFadeAnimEnd)
	{
		// 맵 이동
		UEngineAPICore::GetCore()->ResetLevel<AMapGameMode, AActor>("Map");
		UEngineAPICore::GetCore()->OpenLevel("Map");

		IsFadeAnimed = false;
	}
}

