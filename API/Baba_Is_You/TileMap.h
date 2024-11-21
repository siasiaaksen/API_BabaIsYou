#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineSerializer.h>

#include "ContentsEnum.h"


class Tile : public AActor, public ISerializObject
{
public:
	USpriteRenderer* SpriteRenderer;
	bool IsMove = true;
	bool IsChange = false;
	int FloorOrder = -1;

	FVector2D Scale;
	FVector2D Pivot;
	FVector2D Location;
	FIntPoint Index;

	std::string SpriteName;
	int SpriteIndex;

	ELogicType CurObjectType = ELogicType::NONE;

	EMoveType MoveType = EMoveType::NONE;
	EStateType StateType = EStateType::NONE;
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
		_Ser << FloorOrder;
		_Ser << Scale;
		_Ser << Pivot;
		_Ser << SpriteIndex;
	}

	void DeSerialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		_Ser >> SpriteName;
		_Ser >> IsMove;
		_Ser >> FloorOrder;
		_Ser >> Scale;
		_Ser >> Pivot;
		_Ser >> SpriteIndex;
	}
};

enum class EState
{
	NONE,
	DEACTIVEONE,
	DEACTIVEBOTH,
};

class History
{
public:
	Tile* Tile;
	FIntPoint Prev;
	FIntPoint Next;

	EState State = EState::NONE;

	ELogicType PrevSprite = ELogicType::NONE;
	ELogicType NextSprite = ELogicType::NONE;
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

	void SetTile(std::string_view _Sprite, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType = ELogicType::NONE, EVLogicType _SLogicType = EVLogicType::NONE, ELogicType _TLogicType = ELogicType::NONE);
	void SetTile(std::string_view _Sprite, FIntPoint _Index, int _SpriteIndex, int _FloorOrder, ERenderOrder _Order, ELogicType _FLogicType = ELogicType::NONE, EVLogicType _SLogicType = EVLogicType::NONE, ELogicType _TLogicTyp = ELogicType::NONE);

	std::string_view FindSpriteName(ELogicType _FLogicType);
	std::vector<FIntPoint> FindMoveTile();

	void AllTileMoveCheck(FIntPoint _MoveIndex);

	void TileMove(FIntPoint _CurIndex, FIntPoint _MoveIndex);
	bool TileMoveCheck(FIntPoint _NextIndex, FIntPoint _MoveIndex);

	// 다음 인덱스의 스프라이트가 있어? 모든 FloorOrder 체크
	bool IsVoid(FIntPoint _NextIndex);

	Tile* GetTileRef(FIntPoint _Index, int _FloorOrder);
	Tile* GetTileRef(FVector2D _Location, int _FloorOrder);

	FVector2D IndexToTileLocation(FIntPoint _Index);
	FIntPoint LocationToIndex(FVector2D _Location);

	bool IsIndexOver(FIntPoint _Index);

	void Serialize(UEngineSerializer& _Ser);
	void DeSerialize(UEngineSerializer& _Ser);

	void MoveTileTypeReset();
	void MoveTileStateReset();

	void ChangeMoveMode(ELogicType _FLogicType, EMoveType _MoveType);
	void ChangeStateMode(ELogicType _FLogicType, EStateType _StateType);
	void SpriteChange(ELogicType _CurSprite, ELogicType _ChangeSprite);

	void Action(float _DeltaTime);
	void Undo(float _DeltaTime);

	bool IsActionEnd()
	{
		return ActionTime >= 1.0f;
	}

	void SetActionTime(float _ActionTime)
	{
		ActionTime = _ActionTime;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void PushHistory(History _History)
	{
		Histories.back().push_back(_History);
	}

protected:

private:
	FIntPoint TileCount;
	FVector2D TileSize;

	////     Y         X            층
	std::vector<std::vector<std::map<int, Tile*>>> AllTiles;

	std::list<std::list<History>> Histories;

	std::list<History>* LastHistories;

	float ActionTime = 0.0f;

	std::vector<Tile*> DeactiveObject;
};

