#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineSerializer.h>

#include "ContentsEnum.h"


class Tile : public ISerializObject
{
public:
	USpriteRenderer* SpriteRenderer;
	bool IsMove = true;
	int TileType = -1;

	FVector2D Scale;
	FVector2D Pivot;
	FVector2D SpriteLocation;

	std::string SpriteName;
	int SpriteIndex;

	ELogicType FLogicType = ELogicType::NONE;
	EVLogicType SLogicType = EVLogicType::NONE;
	ELogicType TLogicType = ELogicType::NONE;

	void Serialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		if (nullptr != SpriteRenderer)
		{
			SpriteName = SpriteRenderer->GetCurSpriteName();
		}
		_Ser << SpriteName;
		_Ser << IsMove;
		_Ser << TileType;
		_Ser << Scale;
		_Ser << Pivot;
		_Ser << SpriteIndex;
	}

	void DeSerialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		_Ser >> SpriteName;
		_Ser >> IsMove;
		_Ser >> TileType;
		_Ser >> Scale;
		_Ser >> Pivot;
		_Ser >> SpriteIndex;
	}
};

class ATileMap : public AActor, public ISerializObject
{
public:
	ATileMap();
	~ATileMap();

	ATileMap(const ATileMap& _Other) = delete;
	ATileMap(ATileMap&& _Other) noexcept = delete;
	ATileMap& operator=(const ATileMap& _Other) = delete;
	ATileMap& operator=(ATileMap&& _Other) noexcept = delete;

	void Create(FIntPoint _Count, FVector2D _TileSize);

	void SetTileLocation(std::string_view _Sprite, FVector2D _Location, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType);

	void SetTileIndex(std::string_view _Sprite, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType = ELogicType::NONE, EVLogicType _SLogicType = EVLogicType::NONE, ELogicType _TLogicType = ELogicType::NONE);
	void SetTileIndex(std::string_view _Sprite, FIntPoint _Index, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType = ELogicType::NONE, EVLogicType _SLogicType = EVLogicType::NONE, ELogicType _TLogicTyp = ELogicType::NONE);

	std::vector<FIntPoint> FindMoveTile(ELogicType _FLogicType);

	FIntPoint TileMove(FIntPoint _CurIndex, FIntPoint _MoveIndex, std::vector<ELogicType> _Tiles);
	bool TileMoveCheck(FIntPoint _NextIndex, FIntPoint _MoveIndex, std::vector<ELogicType> _Tiles);

	Tile* GetTileRef(FIntPoint _Index, int _FloorOrder);
	Tile* GetTileRef(FVector2D _Location, int _FloorOrder);

	FVector2D IndexToTileLocation(FIntPoint _Index);
	FIntPoint LocationToIndex(FVector2D _Location);

	bool IsIndexOver(FIntPoint _Index);

	void Serialize(UEngineSerializer& _Ser);
	void DeSerialize(UEngineSerializer& _Ser);

protected:

private:
	FIntPoint TileCount;
	FVector2D TileSize;

	////     Y         X            Ãþ
	std::vector<std::vector<std::map<int, Tile>>> AllTiles;
};

