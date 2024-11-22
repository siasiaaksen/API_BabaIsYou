#include "PreCompile.h"
#include "TileMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineString.h>
#include "TestGameMode.h"


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
					UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
					UEngineDebug::CoreOutPutString("YouTilePos : " + CurTileIndex.ToString());
				}
			}
		}
	}

	if (true == UEngineInput::GetInst().IsDown('Q'))
	{
		UEngineDebug::SwitchIsDebug();
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

	NewTilePtr->FLogicType = _FLogicType;
	NewTilePtr->SLogicType = _SLogicType;
	NewTilePtr->TLogicType = _TLogicType;
	NewTilePtr->FloorOrder = _FloorOrder;
	NewTilePtr->Pivot = _Pivot;
	NewTilePtr->Scale = _SpriteScale;
	NewTilePtr->SpriteIndex = _SpriteIndex;
	NewTilePtr->Location = CurTileLocation;
	NewTilePtr->Index = LocationToIndex(CurTileLocation - TileSize);
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

	ATestGameMode* TGameMode = GetWorld()->GetGameMode<ATestGameMode>();

	// 이동한 타일이 있으면
	if (0 != LastHistories->size())
	{
		TGameMode->SetState(EGameState::ACTION);
		ActionTime = 0.0f;
	}
	else {
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

	// 모든 타일층을 돌면서
	for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	{
		// CurMap의 i층에 타일이 있어?
		if (false == CurMap.contains(i))
		{
			continue;
		}

		Tile* CurTile = CurMap[i];

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

		if (true == IsEmpty)
		{
			History NewH;
			NewH.Tile = CurTile;
			NewH.Prev = _CurIndex;
			NewH.Next = NextIndex;

			LastHistories->push_back(NewH);
		}
		else
		{
			TileMove(NextIndex, _MoveIndex);

			int a = 0;

			for (int j = 0; j < static_cast<int>(EFloorOrder::MAX); j++)
			{
				if (false == NextMap.contains(j))
				{
					continue;
				}

				if ((EMoveType::YOU == CurMap[i]->MoveType && EStateType::DEFEAT == NextMap[j]->StateType) ||
					(EStateType::SINK == NextMap[j]->StateType) ||
					(EStateType::MELT == CurMap[i]->StateType && EStateType::HOT == NextMap[j]->StateType) ||
					(EMoveType::YOU == CurMap[i]->MoveType && EStateType::WIN == NextMap[j]->StateType))
				{
					History NewH;
					NewH.Tile = CurTile;
					NewH.Prev = _CurIndex;
					NewH.Next = NextIndex;

					LastHistories->push_back(NewH);

					return;
				}

				continue;
			}

			History NewH;
			NewH.Tile = CurTile;
			NewH.Prev = _CurIndex;
			NewH.Next = NextIndex;

			LastHistories->push_back(NewH);
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
			return false;
		}

		for (int j = 0; j < static_cast<int>(EFloorOrder::MAX); j++)
		{
			if (false == NextMap.contains(j))
			{
				continue;
			}

			if (EMoveType::STOP == NextMap[j]->MoveType)
			{
				return false;
			}
		}

		if (IsVoid(NextIndex) == false)
		{
			return TileMoveCheck(NextIndex, _MoveIndex);
		}
	}

	return true;
}

// 다음 인덱스에 타일이 존재해?
bool ATileMap::IsVoid(FIntPoint _NextIndex)
{
	std::map<int, Tile*>& NextMap = AllTiles[_NextIndex.Y][_NextIndex.X];

	return NextMap.empty();
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
					int SpriteIndex = CurTile->SpriteIndex;
					std::string_view SpriteName = FindSpriteName(_ChangeSprite);
					std::string UpperName = UEngineString::ToUpper(SpriteName);
					CurTile->FLogicType = _ChangeSprite;
					CurTile->SpriteRenderer->SetSprite(UpperName, SpriteIndex);
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

void ATileMap::Serialize(UEngineSerializer& _Ser)
{
	//_Ser << TileCount;
	//_Ser << TileSize;
	//_Ser << SpriteName;
	//_Ser << AllTiles;
}

void ATileMap::DeSerialize(UEngineSerializer& _Ser)
{
	//_Ser >> TileCount;
	//_Ser >> TileSize;
	//_Ser >> SpriteName;

	//std::vector<std::vector<Tile>> LoadTiles;
	//_Ser >> LoadTiles;

	//Create(SpriteName, TileCount, TileSize);

	//for (int y = 0; y < LoadTiles.size(); y++)
	//{
	//	for (int x = 0; x < LoadTiles[y].size(); x++)
	//	{
	//		SetTileIndex({ x, y }, LoadTiles[y][x].Pivot, LoadTiles[y][x].Scale, LoadTiles[y][x].SpriteIndex);
	//	}
	//}
}

void ATileMap::Action(float _DeltaTime)
{
	std::list<History>& Last = Histories.back();

	LastHistories = &Last;

	ActionTime += _DeltaTime * 10.0f;

	// ActionTime이 끝난 후
	if (1.0f <= ActionTime)
	{
		std::list<History>::iterator StartIter = LastHistories->begin();
		std::list<History>::iterator EndIter = LastHistories->end();

		for (; StartIter != EndIter; ++StartIter)
		{
			History& History = *StartIter;

			Tile* CurTile = History.Tile;
			int CurFloorOrder = CurTile->FloorOrder;

			History.Prev; // 지워
			History.Next; // 생성

			if (CurTile->MoveType != EMoveType::NONE)
			{
				AllTiles[History.Next.Y][History.Next.X][CurFloorOrder] = AllTiles[History.Prev.Y][History.Prev.X][CurFloorOrder];

				std::map<int, Tile*>::iterator FindIter = AllTiles[History.Prev.Y][History.Prev.X].find(CurFloorOrder);
				AllTiles[History.Prev.Y][History.Prev.X].erase(FindIter);
			}

			for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
			{
				std::map<int, Tile*> OtherTile = AllTiles[History.Next.Y][History.Next.X];

				if (false == OtherTile.contains(i))
				{
					continue;
				}

				// DEFEAT
				if (EMoveType::YOU == CurTile->MoveType && EStateType::DEFEAT == OtherTile[i]->StateType)
				{
					History.State = EState::DEACTIVEONE;
					CurTile->SpriteRenderer->SetActive(false);
				}
				// SINK
				else if (EStateType::SINK == OtherTile[i]->StateType)
				{
					History.State = EState::DEACTIVEBOTH;

					if (OtherTile[i]->StateType == EStateType::SINK)
					{
						CurTile->SpriteRenderer->SetActive(false);
						OtherTile[i]->SpriteRenderer->SetActive(false);
					}
				}
				// HOT
				else if (EStateType::MELT == CurTile->StateType && EStateType::HOT == OtherTile[i]->StateType)
				{
					History.State = EState::DEACTIVEONE;
					CurTile->SpriteRenderer->SetActive(false);
				}
				// WIN
				else if (EMoveType::YOU == CurTile->MoveType && EStateType::WIN == OtherTile[i]->StateType)
				{
					History.State = EState::DEACTIVEONE;
					// 맵 이동
					UEngineAPICore::GetCore()->OpenLevel("Map");
				}
			}
		}

		ActionTime = 1.0f;
		return;
	}

	// ActionTime동안 이동하면서 벌어지는

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
		
		if (CurTile->MoveType == EMoveType::YOU)
		{
			std::map<int, Tile*>& CurrentLayer = AllTiles[History.Prev.Y][History.Prev.X];
			
			if (CurrentLayer.contains(static_cast<int>(EFloorOrder::TEXT)))
			{
				Tile* CurTextTile = CurrentLayer[static_cast<int>(EFloorOrder::TEXT)];
				
				if (CurTextTile != nullptr && CurTextTile->MoveType != EMoveType::NONE)
				{
					CurTextTile->IsMove = false;
					CurTextTile->MoveType = EMoveType::NONE;
					int a = 0;
				}
			}
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
			FVector2D CurTilePos = CurTile->GetActorLocation();
			CurTile->Location = CurTilePos;
			FIntPoint TileIndex = LocationToIndex(CurTilePos - TileSize);
			CurTile->Index = TileIndex;
		}
	}
}

void ATileMap::Undo(float _DeltaTime)
{
	ActionTime += _DeltaTime * 10.0f;

	if (1.0f <= ActionTime)
	{
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
							Tile* CurTile = StartLeftIter->second;

							if (nullptr == CurTile)
							{
								continue;
							}

							FIntPoint Index = FIntPoint(x, y);

							if (CurTile->FLogicType == History.NextSprite && CurTile->IsChange == true)
							{
								int SpriteIndex = CurTile->SpriteIndex;
								std::string_view SpriteName = FindSpriteName(History.PrevSprite);
								std::string UpperName = UEngineString::ToUpper(SpriteName);
								CurTile->FLogicType = History.PrevSprite;
								CurTile->SpriteRenderer->SetSprite(UpperName, SpriteIndex);
								CurTile->IsChange = false;
							}
						}
					}
				}
			}

			if (nullptr == CurTile)
			{
				continue;
			}

			int CurFloorOrder = CurTile->FloorOrder;

			History.Next; // 지워
			History.Prev; // 생성


			AllTiles[History.Prev.Y][History.Prev.X][CurFloorOrder] = AllTiles[History.Next.Y][History.Next.X][CurFloorOrder];

			std::map<int, Tile*>::iterator FindIter = AllTiles[History.Next.Y][History.Next.X].find(CurFloorOrder);
			AllTiles[History.Next.Y][History.Next.X].erase(FindIter);


			for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
			{
				std::map<int, Tile*> OtherTile = AllTiles[History.Next.Y][History.Next.X];

				if (false == OtherTile.contains(i))
				{
					continue;
				}

				// DEFEAT, HOT
				if (History.State == EState::DEACTIVEONE)
				{
					if (false == CurTile->SpriteRenderer->IsActive())
					{
						CurTile->SpriteRenderer->SetActive(true);
					}

					CurTile->IsMove = true;
				}
				// SINK
				else if (History.State == EState::DEACTIVEBOTH)
				{
					CurTile->SpriteRenderer->SetActive(true);
					CurTile->IsMove = true;
					OtherTile[i]->SpriteRenderer->SetActive(true);
				}
			}
		}

		ActionTime = 1.0f;
		LastHistories.clear();
		Histories.pop_back();
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

