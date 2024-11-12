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
		AllTiles[y].resize(_Count.X);;
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

void ATileMap::SetTileLocation(std::string_view _Sprite, FVector2D _Location, int _SpriteIndex, ERenderOrder _Order, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
{
	FVector2D TilePos = _Location - GetActorLocation();

	FIntPoint Point = LocationToIndex(TilePos);

	if (true == IsIndexOver(Point))
	{
		return;
	}

	SetTileIndex(_Sprite, Point, _SpriteIndex, _Order, _FLogicType,_SLogicType, _TLogicType);
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

void ATileMap::SetTileIndex(std::string_view _Sprite, FIntPoint _Index, int _SpriteIndex, ERenderOrder _Order, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
{
	SetTileIndex(_Sprite, _Index, { 0, 0 }, TileSize, _SpriteIndex, _Order, _FLogicType, _SLogicType, _TLogicType);
}

void ATileMap::SetTileIndex(std::string_view _Sprite, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, ERenderOrder _Order, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	// AllTiles[_Index.Y][_Index.X]�� ��������Ʈ ������ ����
	if (nullptr == AllTiles[_Index.Y][_Index.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		NewSpriteRenderer->SetComponentScale(TileSize);
		AllTiles[_Index.Y][_Index.X].SpriteRenderer = NewSpriteRenderer;
	}

	// AllTiles[_Index.Y][_Index.X]�� ��������Ʈ ������ ã�Ƽ� ��������Ʈ ����
	USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
	FindSprite->SetSprite(_Sprite, _SpriteIndex);
	FindSprite->SetComponentScale(_SpriteScale);
	FindSprite->SetOrder(_Order);

	// AllTiles[_Index.Y][_Index.X]�� ��ġ, �Ǻ�, ������, ��������Ʈ �ε��� ����
	FVector2D TileLocation = IndexToTileLocation(_Index);
	AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);

	FVector2D CurTileLocation = AllTiles[_Index.Y][_Index.X].SpriteRenderer->GetComponentLocation();

	AllTiles[_Index.Y][_Index.X].FLogicType = _FLogicType;
	AllTiles[_Index.Y][_Index.X].SLogicType = _SLogicType;
	AllTiles[_Index.Y][_Index.X].TLogicType = _TLogicType;
	AllTiles[_Index.Y][_Index.X].TileType = static_cast<int>(_Order);
	AllTiles[_Index.Y][_Index.X].Pivot = _Pivot;
	AllTiles[_Index.Y][_Index.X].Scale = _SpriteScale;
	AllTiles[_Index.Y][_Index.X].SpriteIndex = _SpriteIndex;
	AllTiles[_Index.Y][_Index.X].SpriteLocation = CurTileLocation;
	std::string UpperName = UEngineString::ToUpper(_Sprite);
	AllTiles[_Index.Y][_Index.X].SpriteName = UpperName;
}

FIntPoint ATileMap::FindTileIndex(std::string_view _Name)
{
	FIntPoint Index;
	std::string UpperName = UEngineString::ToUpper(_Name);

	for (int x = 0; x < TileCount.X; ++x)
	{
		for (int y = 0; y < TileCount.Y; ++y)
		{
			if (nullptr == AllTiles[y][x].SpriteRenderer)
			{
				continue;
			}

			if (AllTiles[y][x].SpriteRenderer->GetCurSpriteName() == UpperName)
			{
				Index.X = x;
				Index.Y = y;
				return Index;
			}

			continue;
		}
	}
}

FIntPoint ATileMap::TileMove(FIntPoint _CurIndex, FIntPoint _MoveIndex)
{
	FIntPoint NextIndex = _CurIndex + _MoveIndex;

	if (false == TileMoveCheck(_CurIndex, _MoveIndex))
	{
		return _CurIndex;
	}

	USpriteRenderer* CurSprite = AllTiles[_CurIndex.Y][_CurIndex.X].SpriteRenderer;
	USpriteRenderer* NextSprite = AllTiles[NextIndex.Y][NextIndex.X].SpriteRenderer;

	if (nullptr != NextSprite)
	{
		FIntPoint LastIndex = TileMove(NextIndex, _MoveIndex);

		FVector2D NextPos = IndexToTileLocation(NextIndex);
		CurSprite->SetComponentLocation(NextPos + TileSize.Half());

		AllTiles[NextIndex.Y][NextIndex.X].SpriteRenderer = CurSprite;
		AllTiles[_CurIndex.Y][_CurIndex.X].SpriteRenderer = nullptr;

		return LastIndex;
	}

	FVector2D NextPos = IndexToTileLocation(NextIndex);
	CurSprite->SetComponentLocation(NextPos + TileSize.Half());

	AllTiles[NextIndex.Y][NextIndex.X].SpriteRenderer = CurSprite;
	AllTiles[_CurIndex.Y][_CurIndex.X].SpriteRenderer = nullptr;

	return NextIndex;
}

bool ATileMap::TileMoveCheck(FIntPoint _CurIndex, FIntPoint _MoveIndex)
{
	FIntPoint NextIndex = _CurIndex + _MoveIndex;

	if (true == IsIndexOver(NextIndex))
	{
		return false;
	}

	USpriteRenderer* CurSprite = AllTiles[_CurIndex.Y][_CurIndex.X].SpriteRenderer;
	USpriteRenderer* NextSprite = AllTiles[NextIndex.Y][NextIndex.X].SpriteRenderer;

	if (nullptr != NextSprite)
	{
		return TileMoveCheck(NextIndex, _MoveIndex);
	}

	return true;
}

Tile* ATileMap::GetTileRef(FVector2D _Location)
{
	FIntPoint Point = LocationToIndex(_Location);

	return GetTileRef(Point);
}

Tile* ATileMap::GetTileRef(FIntPoint _Index)
{
	if (true == IsIndexOver(_Index))
	{
		return nullptr;
	}

	return &AllTiles[_Index.Y][_Index.X];
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