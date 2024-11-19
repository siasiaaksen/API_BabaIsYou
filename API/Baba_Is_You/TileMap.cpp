#include "PreCompile.h"
#include "TileMap.h"

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineString.h>
#include "TestGameMode.h"


ATileMap::ATileMap()
{
}

ATileMap::~ATileMap()
{
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

// �� �ε����� Ÿ���� �̷��� �Ӽ��� ���� ����
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

	// �ش� �ε����� Ÿ���� ������ �����
	if (nullptr == NewTilePtr)
	{
		NewTilePtr = GetWorld()->SpawnActor<Tile>();
		AllTiles[_Index.Y][_Index.X][_FloorOrder] = NewTilePtr;
		NewTilePtr->SpriteRenderer = NewTilePtr->CreateDefaultSubObject<USpriteRenderer>();
		NewTilePtr->SpriteRenderer->SetComponentScale(TileSize);
	}

	// Ÿ���� ��������Ʈ ������ ã�Ƽ� ��������Ʈ ����
	USpriteRenderer* FindSprite = NewTilePtr->SpriteRenderer;
	FindSprite->SetSprite(_Sprite, _SpriteIndex);
	FindSprite->SetComponentScale(_SpriteScale);
	FindSprite->SetOrder(_FloorOrder);

	// Ÿ���� ��ġ, �Ǻ�, ������, ��������Ʈ �ε��� ��� ����
	FVector2D TileLocation = IndexToTileLocation(_Index);
	//                                                                    ���ͱ������ �ٲ�鼭 Ÿ�� ������ ��ġ�� ���������
	NewTilePtr->SetActorLocation(TileLocation + TileSize.Half() + _Pivot + GetActorLocation() );

	FVector2D CurTileLocation = NewTilePtr->GetActorLocation();

	NewTilePtr->FLogicType = _FLogicType;
	NewTilePtr->SLogicType = _SLogicType;
	NewTilePtr->TLogicType = _TLogicType;
	NewTilePtr->FloorOrder = _FloorOrder;
	NewTilePtr->Pivot = _Pivot;
	NewTilePtr->Scale = _SpriteScale;
	NewTilePtr->SpriteIndex = _SpriteIndex;
	NewTilePtr->SpriteLocation = CurTileLocation;
	std::string UpperName = UEngineString::ToUpper(_Sprite);
	NewTilePtr->SpriteName = UpperName;
}

std::vector<FIntPoint> ATileMap::FindMoveTile(ELogicType _FLogicType)
{
	std::vector<FIntPoint> LogicTiles;
	FIntPoint Index;

	for (int x = 0; x < TileCount.X; ++x)
	{
		for (int y = 0; y < TileCount.Y; ++y)
		{
			for (int a = 0; a < static_cast<int>(EFloorOrder::MAX); a++)
			{
				if (AllTiles[y][x][a]->FLogicType == _FLogicType)
				{
					Index.X = x;
					Index.Y = y;
					LogicTiles.push_back(Index);
				}

				continue;
			}
		}
	}

	return LogicTiles;
}

// �ε��� 0, 0���� EMoveType::YOU�� Ÿ�� ã��
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
	CurHistories.clear();

	std::vector<FIntPoint> YouTiles = FindMoveTile();

	for (size_t i = 0; i < YouTiles.size(); i++)
	{
		TileMove(YouTiles[i], _MoveDir);
	}

	// �̵��� Ÿ���� ������
	if (0 != CurHistories.size())
	{
		LastHistories = CurHistories;

		Histories.push_back(CurHistories);

		ATestGameMode* TGameMode = GetWorld()->GetGameMode<ATestGameMode>();
		TGameMode->SetState(EGameState::ACTION);
		ActionTime = 0.0f;
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

	// ��� Ÿ������ ���鼭
	for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	{
		// CurMap�� i���� Ÿ���� �־�?
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

		// ���� Ÿ���� ����־�?
		bool IsEmpty = IsVoid(NextIndex);

		if (true == IsEmpty)
		{
			History NewH;
			NewH.Tile = CurTile;
			NewH.Prev = _CurIndex;
			NewH.Next = NextIndex;

			CurHistories.push_back(NewH);
			// FVector2D NextPos = IndexToTileLocation(NextIndex);
			// CurSprite->SetComponentLocation(NextPos + TileSize.Half());
			
			// �� �κ� ���� : Undo�� �� ���� ��Ȳ �߻��� �� ����
			// ���� �ű�� �� �ƴ϶� �̵��ϸ鼭 �Ű�����
			{
				// ���� �ϴ� �Ű��
				NextMap[i] = CurMap[i];

				// ���� ������ �����Ǵ°�
				std::map<int, Tile*>::iterator FindIter = CurMap.find(i);
				CurMap.erase(FindIter);
			}

			// ����� ���ؼ� ��������
			// �����ͳ� �������� ��ȭ���� �� �����־�
		}
		else
		{
			//TileMove(NextIndex, _MoveIndex);

			//for (int j = 0; j < static_cast<int>(EFloorOrder::MAX); j++)
			//{
			//	if (EMoveType::YOU == CurMap[i].MoveType && EStateType::DEFEAT == NextMap[j].StateType)
			//	{
			//		CurMap[i].DeathState = EDeathState::DEATH;
			//		DeathTile();
			//		ATestGameMode* TGameMode = GetWorld()->GetGameMode<ATestGameMode>();
			//		TGameMode->SetState(EGameState::DEATH);
			//		return;
			//	}
			//	else if (static_cast<int>(EFloorOrder::TEXT) != CurMap[i].FloorOrder && EStateType::SINK == NextMap[j].StateType)
			//	{
			//		CurMap[i].DeathState = EDeathState::DEATH;
			//		DeathTile();

			//		if (EMoveType::YOU == CurMap[i].MoveType)
			//		{
			//			ATestGameMode* TGameMode = GetWorld()->GetGameMode<ATestGameMode>();
			//			TGameMode->SetState(EGameState::DEATH);
			//		}

			//		return;
			//	}
			//	else if (EStateType::MELT == CurMap[i].StateType && EStateType::HOT == NextMap[j].StateType)
			//	{
			//		CurMap[i].DeathState = EDeathState::DEATH;
			//		DeathTile();
			//		ATestGameMode* TGameMode = GetWorld()->GetGameMode<ATestGameMode>();
			//		TGameMode->SetState(EGameState::DEATH);
			//		return;
			//	}
			//	else if (EMoveType::YOU == CurMap[i].MoveType && EStateType::WIN == NextMap[j].StateType)
			//	{
			//		FVector2D NextPos = IndexToTileLocation(NextIndex);
			//		CurSprite->SetComponentLocation(NextPos + TileSize.Half());
			//		CurTileToNextTile(CurTile, NextTile);

			//		UEngineDebug::OutPutString("���� Ŭ����");
			//		ATestGameMode* TGameMode = GetWorld()->GetGameMode<ATestGameMode>();
			//		TGameMode->SetState(EGameState::DEATH);
			//		return;
			//	}

			//	continue;
			//}

			//FVector2D NextPos = IndexToTileLocation(NextIndex);
			//CurSprite->SetComponentLocation(NextPos + TileSize.Half());
			//CurTileToNextTile(CurTile, NextTile);
		}
	}

	return;
}

// ���� �ε����� Ÿ���� ������?
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
		USpriteRenderer* NextSprite = NextMap[i]->SpriteRenderer;

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

// ���� �ε����� Ÿ���� ������?
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

// ��� Ÿ���� MoveType ����
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

				CurTile->DeathState = EDeathState::ALIVE;
			}
		}
	}
}

// ��� Ÿ���� StateType ����
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

				CurTile->DeathState = EDeathState::ALIVE;
			}
		}
	}
}

// �ϼ��� ���� ���� ���ǿ� ���� �ش� Ÿ���� MoveType ����
void  ATileMap::ChangeMoveMode(ELogicType _FLogicType, EMoveType _MoveType)
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

// �ϼ��� ���� ���� ���ǿ� ���� �ش� Ÿ���� StateType ����
void  ATileMap::ChangeStateMode(ELogicType _FLogicType, EStateType _StateType)
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

				if (_FLogicType != CurTile->FLogicType)
				{
					continue;
				}

				CurTile->StateType = _StateType;
			}
		}
	}
}

void ATileMap::DeathTileToAlive()
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

				if (CurTile->DeathState == EDeathState::DEATH)
				{
					// ATestGameMode* TGameMode = GetWorld()->GetGameMode<ATestGameMode>();
					// TGameMode->SetState(EGameState::INGAME);
					// CurTile->DeathState = EDeathState::ALIVE;
					// CurTile->SpriteRenderer->SetActive(true);
				}
			}
		}
	}
}

void ATileMap::DeathTile()
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

				if (CurTile->DeathState == EDeathState::DEATH)
				{
					CurTile->SpriteRenderer->SetActive(false);
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
	ActionTime += _DeltaTime * 4.0f;

	if (1.0f <= ActionTime)
	{
		ActionTime = 1.0f;
		LastHistories.clear();
	}

	std::list<History>::iterator StartIter = LastHistories.begin();
	std::list<History>::iterator EndIter = LastHistories.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		History& History = *StartIter;
		Tile* CurTIle = History.Tile;

		if (nullptr == CurTIle)
		{
			MSGASSERT("���� �ȵǴ� ��Ȳ�Դϴ�.");
		}

		//                   1.0
		FVector2D StartPos = History.Prev.ConvertToVector() ;
		FVector2D EndPos = History.Next.ConvertToVector();
		StartPos *= TileSize;
		EndPos *= TileSize;

		StartPos += GetActorLocation() + TileSize.Half();
		EndPos += GetActorLocation() + TileSize.Half();

		// ActionTime ���� StartPos���� EndPos�� �̵�
		FVector2D CurPos = FVector2D::Lerp(StartPos, EndPos, ActionTime);
		CurTIle->SetActorLocation(CurPos);

		//{
		//	// ���� �ϴ� �Ű��
		//	NextMap[i] = CurMap[i];

		//	// ���� ������ �����Ǵ°�
		//	std::map<int, Tile*>::iterator FindIter = CurMap.find(i);
		//	CurMap.erase(FindIter);
		//}
	}
}

void ATileMap::Undo(float _DeltaTime)
{
	ActionTime += _DeltaTime * 4.0f;

	if (1.0f <= ActionTime)
	{
		ActionTime = 1.0f;
		LastHistories.clear();
	}

	std::list<History>::iterator StartIter = LastHistories.end();
	std::list<History>::iterator EndIter = LastHistories.begin();

	for (; StartIter != EndIter;)
	{
		--StartIter;

		History& History = *StartIter;
		Tile* CurTIle = History.Tile;

		if (nullptr == CurTIle)
		{
			MSGASSERT("���� �ȵǴ� ��Ȳ�Դϴ�.");
		}
		
		FVector2D StartPos = History.Next.ConvertToVector();
		FVector2D EndPos = History.Prev.ConvertToVector();
		StartPos *= TileSize;
		EndPos *= TileSize;

		StartPos += GetActorLocation() + TileSize.Half();
		EndPos += GetActorLocation() + TileSize.Half();

		FVector2D CurPos = FVector2D::Lerp(StartPos, EndPos, ActionTime);
		CurTIle->SetActorLocation(CurPos);

		StartIter = LastHistories.erase(StartIter);
	}
}




