#include "PreCompile.h"
#include "TileMap.h"

#include <EngineBase/EngineString.h>


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

		for (size_t x = 0; x < AllTiles[y].size(); x++)
		{
		}
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

	// AllTiles[_Index.Y][_Index.X][static_cast<int>(_Order)]에 스프라이트 랜더러 장착
	if (nullptr == AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		NewSpriteRenderer->SetComponentScale(TileSize);
		AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteRenderer = NewSpriteRenderer;
	}

	// AllTiles[_Index.Y][_Index.X][static_cast<int>(_Order)]의 스프라이트 랜더러 찾아서 스프라이트 세팅
	USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteRenderer;
	FindSprite->SetSprite(_Sprite, _SpriteIndex);
	FindSprite->SetComponentScale(_SpriteScale);
	FindSprite->SetOrder(_FloorOrder);

	// AllTiles[_Index.Y][_Index.X][static_cast<int>(_Order)]의 위치, 피봇, 스케일, 스프라이트 인덱스 지정
	FVector2D TileLocation = IndexToTileLocation(_Index);
	AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);

	FVector2D CurTileLocation = AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteRenderer->GetComponentLocation();

	AllTiles[_Index.Y][_Index.X][_FloorOrder].FLogicType = _FLogicType;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].SLogicType = _SLogicType;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].TLogicType = _TLogicType;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].FloorOrder = _FloorOrder;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].Pivot = _Pivot;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].Scale = _SpriteScale;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteIndex = _SpriteIndex;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteLocation = CurTileLocation;
	std::string UpperName = UEngineString::ToUpper(_Sprite);
	AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteName = UpperName;
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
				if (AllTiles[y][x][a].FLogicType == _FLogicType)
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

std::vector<FIntPoint> ATileMap::FindMoveTile()
{
	std::vector<FIntPoint> MoveTiles;

	for (int y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile>>& VectorY = AllTiles[y];

		for (int x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile>& VectorX = VectorY[x];

			std::map<int, Tile>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile& CurTile = StartLeftIter->second;
				FIntPoint Index = FIntPoint(x, y);

				if (EMoveType::YOU != CurTile.MoveType)
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
	std::vector<FIntPoint> YouTiles = FindMoveTile();

	for (size_t i = 0; i < YouTiles.size(); i++)
	{
		TileMove(YouTiles[i], _MoveDir);
	}
}

void ATileMap::TileMove(FIntPoint _CurIndex, FIntPoint _MoveIndex)
{
	FIntPoint NextIndex = _CurIndex + _MoveIndex;

	if (false == TileMoveCheck(_CurIndex, _MoveIndex))
	{
		return;
	}

	std::map<int, Tile>& CurMap = AllTiles[_CurIndex.Y][_CurIndex.X];
	std::map<int, Tile>& NextMap = AllTiles[NextIndex.Y][NextIndex.X];

	for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	{
		Tile& CurTile = CurMap[i];
		Tile& NextTile = NextMap[i];
		
		EMoveType CurMoveType = CurTile.MoveType;

		if (CurMoveType != EMoveType::YOU && CurMoveType != EMoveType::PUSH)
		{
			continue;
		}

		USpriteRenderer* CurSprite = CurTile.SpriteRenderer;
		ELogicType CurFLogicType = CurTile.FLogicType;
		EVLogicType CurSLogicType = CurTile.SLogicType;
		ELogicType CurTLogicType = CurTile.TLogicType;
		int CurOrder = CurTile.FloorOrder;

		if (nullptr == CurSprite)
		{
			continue;
		}

		bool IsEmpty = IsVoid(NextIndex);

		if (true == IsEmpty)
		{
			FVector2D NextPos = IndexToTileLocation(NextIndex);
			CurSprite->SetComponentLocation(NextPos + TileSize.Half());
			CurTileToNextTile(CurTile, NextTile);
		}
		else
		{
			TileMove(NextIndex, _MoveIndex);
			
			FVector2D NextPos = IndexToTileLocation(NextIndex);
			CurSprite->SetComponentLocation(NextPos + TileSize.Half());
			CurTileToNextTile(CurTile, NextTile);
		}
	}

	return;
}

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

	std::map<int, Tile>& CurMap = AllTiles[_CurIndex.Y][_CurIndex.X];
	std::map<int, Tile>& NextMap = AllTiles[NextIndex.Y][NextIndex.X];

	for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	{
		USpriteRenderer* CurSprite = CurMap[i].SpriteRenderer;
		USpriteRenderer* NextSprite = NextMap[i].SpriteRenderer;

		if (nullptr == CurSprite)
		{
			continue;
		}

		if (EMoveType::YOU != CurMap[i].MoveType && EMoveType::PUSH != CurMap[i].MoveType)
		{
			continue;
		}

		if (EMoveType::STOP == CurMap[i].MoveType)
		{
			return false;
		}

		for (int j = 0; j < static_cast<int>(EFloorOrder::MAX); j++)
		{
			if (EMoveType::STOP == NextMap[j].MoveType)
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

bool ATileMap::IsVoid(FIntPoint _NextIndex)
{
	std::map<int, Tile>& NextMap = AllTiles[_NextIndex.Y][_NextIndex.X];

	for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
	{
		USpriteRenderer* NextSprite = NextMap[i].SpriteRenderer;

		if (nullptr == NextSprite)
		{
			continue;
		}

		return false;
	}

	return true;
}

void ATileMap::CurTileToNextTile(Tile& _CurTile, Tile& _NextTile)
{
	_NextTile = _CurTile;
	_CurTile.MoveType = EMoveType::NONE;
	_CurTile.SpriteRenderer = nullptr;
	_CurTile.FLogicType = ELogicType::NONE;
	_CurTile.SLogicType = EVLogicType::NONE;
	_CurTile.TLogicType = ELogicType::NONE;
	_CurTile.FloorOrder = -1;
	_CurTile.SpriteLocation = FVector2D::ZERO;
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

	return &AllTiles[_Index.Y][_Index.X][_FloorOrder];
}

void ATileMap::MoveTileTypeReset()
{
	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile>>& VectorY = AllTiles[y];
		for (size_t x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile>& VectorX = VectorY[x];

			std::map<int, Tile>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile& CurTile = StartLeftIter->second;

				if (CurTile.FloorOrder != static_cast<int>(EFloorOrder::TEXT))
				{
					CurTile.MoveType = EMoveType::NONE;
				}
				else
				{
					CurTile.MoveType = EMoveType::PUSH;
				}
			}
		}
	}
}

void  ATileMap::ChangeMoveMode(ELogicType _FLogicType, EMoveType _MoveType)
{
	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		std::vector<std::map<int, Tile>>& VectorY = AllTiles[y];
		for (size_t x = 0; x < VectorY.size(); x++)
		{
			std::map<int, Tile>& VectorX = VectorY[x];

			std::map<int, Tile>::iterator StartLeftIter = VectorX.begin();
			std::map<int, Tile>::iterator EndLeftIter = VectorX.end();

			for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
			{
				Tile& CurTile = StartLeftIter->second;

				if (_FLogicType != CurTile.FLogicType)
				{
					continue;
				}

				CurTile.MoveType = _MoveType;
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