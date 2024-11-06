#include "PreCompile.h"
#include "TileMap.h"

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

void ATileMap::SetTileLocation(std::string_view _Sprite, FVector2D _Location, int _SpriteIndex, int _Order)
{
	FVector2D TilePos = _Location - GetActorLocation();

	FIntPoint Point = LocationToIndex(TilePos);

	if (true == IsIndexOver(Point))
	{
		return;
	}

	SetTileIndex(_Sprite, Point, _SpriteIndex, _Order);
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

void ATileMap::SetTileIndex(std::string_view _Sprite, FIntPoint _Index, int _SpriteIndex, int _Order)
{
	SetTileIndex(_Sprite, _Index, { 0,0 }, TileSize, _SpriteIndex, _Order);
}

void ATileMap::SetTileIndex(std::string_view _Sprite, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, int _Order)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	if (nullptr == AllTiles[_Index.Y][_Index.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		NewSpriteRenderer->SetComponentScale(TileSize);
		AllTiles[_Index.Y][_Index.X].SpriteRenderer = NewSpriteRenderer;
	}

	USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
	FindSprite->SetSprite(_Sprite, _SpriteIndex);

	FVector2D TileLocation = IndexToTileLocation(_Index);
	FindSprite->SetComponentScale(_SpriteScale);
	FindSprite->SetOrder(_Order);

	AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);
	AllTiles[_Index.Y][_Index.X].Pivot = _Pivot;
	AllTiles[_Index.Y][_Index.X].Scale = _SpriteScale;
	AllTiles[_Index.Y][_Index.X].SpriteIndex = _SpriteIndex;
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