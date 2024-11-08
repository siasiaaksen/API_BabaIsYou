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
	SetTileIndex(_Sprite, _Index, { 0, 0 }, TileSize, _SpriteIndex, _Order);
}

void ATileMap::SetTileIndex(std::string_view _Sprite, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, int _Order)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	// AllTiles[_Index.Y][_Index.X]에 스프라이트 랜더러 장착
	if (nullptr == AllTiles[_Index.Y][_Index.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		NewSpriteRenderer->SetComponentScale(TileSize);
		AllTiles[_Index.Y][_Index.X].SpriteRenderer = NewSpriteRenderer;
		//LocationToIndex();
	}

	// AllTiles[_Index.Y][_Index.X]의 스프라이트 랜더러 찾아서 스프라이트 세팅
	USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
	FindSprite->SetSprite(_Sprite, _SpriteIndex);
	FindSprite->SetComponentScale(_SpriteScale);
	FindSprite->SetOrder(_Order);

	// AllTiles[_Index.Y][_Index.X]의 위치, 피봇, 스케일, 스프라이트 인덱스 지정
	FVector2D TileLocation = IndexToTileLocation(_Index);
	AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);

	FVector2D CurTileLocation = AllTiles[_Index.Y][_Index.X].SpriteRenderer->GetComponentLocation();

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

	if (true == IsIndexOver(NextIndex))
	{
		return _CurIndex;
	}

	USpriteRenderer* CurSprite = AllTiles[_CurIndex.Y][_CurIndex.X].SpriteRenderer;
	USpriteRenderer* NextSprite = AllTiles[NextIndex.Y][NextIndex.X].SpriteRenderer;

	FVector2D NextPos = IndexToTileLocation(NextIndex);
	CurSprite->SetComponentLocation(NextPos + TileSize.Half());

	if (nullptr != NextSprite)
	{
		return TileMove(NextIndex, _MoveIndex);
	}

	AllTiles[NextIndex.Y][NextIndex.X].SpriteRenderer = CurSprite;
	AllTiles[_CurIndex.Y][_CurIndex.X].SpriteRenderer = NextSprite;

	return NextIndex;
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