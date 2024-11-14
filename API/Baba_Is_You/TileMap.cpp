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
			//AllTiles[y][x].resize(2);
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

	SetTileIndex(_Sprite, Point, _SpriteIndex, _FloorOrder, _Order, _FLogicType,_SLogicType, _TLogicType);
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

void ATileMap::SetTileIndex(std::string_view _Sprite, FIntPoint _Index, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
{
	SetTileIndex(_Sprite, _Index, { 0, 0 }, TileSize, _SpriteIndex, static_cast<int>(EFloorOrder::NONE), _Order, _FLogicType, _SLogicType, _TLogicType);
}

void ATileMap::SetTileIndex(std::string_view _Sprite, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
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
	FindSprite->SetOrder(_Order);

	// AllTiles[_Index.Y][_Index.X][static_cast<int>(_Order)]의 위치, 피봇, 스케일, 스프라이트 인덱스 지정
	FVector2D TileLocation = IndexToTileLocation(_Index);
	AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);

	FVector2D CurTileLocation = AllTiles[_Index.Y][_Index.X][_FloorOrder].SpriteRenderer->GetComponentLocation();

	AllTiles[_Index.Y][_Index.X][_FloorOrder].FLogicType = _FLogicType;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].SLogicType = _SLogicType;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].TLogicType = _TLogicType;
	AllTiles[_Index.Y][_Index.X][_FloorOrder].TileType = _FloorOrder;
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
			for (int a = 0; a < 11; a++)
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

FIntPoint ATileMap::TileMove(FIntPoint _CurIndex, FIntPoint _MoveIndex, std::vector<ELogicType> _Tiles)
{
	FIntPoint NextIndex = _CurIndex + _MoveIndex;

	if (false == TileMoveCheck(_CurIndex, _MoveIndex, _Tiles))
	{
		return _CurIndex;
	}

	for (int i = 0; i < _Tiles.size(); i++)
	{
		USpriteRenderer* CurSprite = AllTiles[_CurIndex.Y][_CurIndex.X][i].SpriteRenderer;
		USpriteRenderer* NextSprite = AllTiles[NextIndex.Y][NextIndex.X][i].SpriteRenderer;

		ELogicType CurFLogicType = AllTiles[_CurIndex.Y][_CurIndex.X][i].FLogicType;
		ELogicType NextFLogicType = AllTiles[NextIndex.Y][NextIndex.X][i].FLogicType;
		EVLogicType CurSLogicType = AllTiles[_CurIndex.Y][_CurIndex.X][i].SLogicType;
		EVLogicType NextSLogicType = AllTiles[NextIndex.Y][NextIndex.X][i].SLogicType;
		ELogicType CurTLogicType = AllTiles[_CurIndex.Y][_CurIndex.X][i].TLogicType;
		ELogicType NextTLogicType = AllTiles[NextIndex.Y][NextIndex.X][i].TLogicType;

		int CurOrder = AllTiles[_CurIndex.Y][_CurIndex.X][i].TileType;
		int NextOrder = AllTiles[NextIndex.Y][NextIndex.X][i].TileType;

		if (nullptr != NextSprite)
		{
			FIntPoint LastIndex = TileMove(NextIndex, _MoveIndex, _Tiles);

			FVector2D NextPos = IndexToTileLocation(NextIndex);
			CurSprite->SetComponentLocation(NextPos + TileSize.Half());

			AllTiles[NextIndex.Y][NextIndex.X][i].SpriteRenderer = CurSprite;
			AllTiles[_CurIndex.Y][_CurIndex.X][i].SpriteRenderer = nullptr;

			AllTiles[NextIndex.Y][NextIndex.X][i].FLogicType = CurFLogicType;
			AllTiles[_CurIndex.Y][_CurIndex.X][i].FLogicType = ELogicType::NONE;
			AllTiles[NextIndex.Y][NextIndex.X][i].SLogicType = CurSLogicType;
			AllTiles[_CurIndex.Y][_CurIndex.X][i].SLogicType = EVLogicType::NONE;
			AllTiles[NextIndex.Y][NextIndex.X][i].TLogicType = CurTLogicType;
			AllTiles[_CurIndex.Y][_CurIndex.X][i].TLogicType = ELogicType::NONE;

			AllTiles[NextIndex.Y][NextIndex.X][i].TileType = CurOrder;
			AllTiles[_CurIndex.Y][_CurIndex.X][i].TileType = -1;

			return LastIndex;
		}

		FVector2D NextPos = IndexToTileLocation(NextIndex);
		CurSprite->SetComponentLocation(NextPos + TileSize.Half());

		AllTiles[NextIndex.Y][NextIndex.X][i].SpriteRenderer = CurSprite;
		AllTiles[_CurIndex.Y][_CurIndex.X][i].SpriteRenderer = nullptr;

		AllTiles[NextIndex.Y][NextIndex.X][i].FLogicType = CurFLogicType;
		AllTiles[_CurIndex.Y][_CurIndex.X][i].FLogicType = ELogicType::NONE;
		AllTiles[NextIndex.Y][NextIndex.X][i].SLogicType = CurSLogicType;
		AllTiles[_CurIndex.Y][_CurIndex.X][i].SLogicType = EVLogicType::NONE;
		AllTiles[NextIndex.Y][NextIndex.X][i].TLogicType = CurTLogicType;
		AllTiles[_CurIndex.Y][_CurIndex.X][i].TLogicType = ELogicType::NONE;

		AllTiles[NextIndex.Y][NextIndex.X][i].TileType = CurOrder;
		AllTiles[_CurIndex.Y][_CurIndex.X][i].TileType = -1;
	}

	return NextIndex;
}

bool ATileMap::TileMoveCheck(FIntPoint _CurIndex, FIntPoint _MoveIndex, std::vector<ELogicType> _Tiles)
{
	FIntPoint NextIndex = _CurIndex + _MoveIndex;

	if (true == IsIndexOver(NextIndex))
	{
		return false;
	}

	for (int i = 0; i < _Tiles.size(); i++)
	{
		USpriteRenderer* CurSprite = AllTiles[_CurIndex.Y][_CurIndex.X][i].SpriteRenderer;
		USpriteRenderer* NextSprite = AllTiles[NextIndex.Y][NextIndex.X][i].SpriteRenderer;

		if (nullptr != NextSprite)
		{
			return TileMoveCheck(NextIndex, _MoveIndex, _Tiles);
		}
	}

	return true;
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