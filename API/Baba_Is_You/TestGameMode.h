#pragma once
#include <EngineCore/GameMode.h>
#include <string>

#include <EngineCore/SpriteRenderer.h>

#include "TileMap.h"


class ATestGameMode : public AGameMode
{
public:
	ATestGameMode();
	~ATestGameMode();

	ATestGameMode(const ATestGameMode& _Other) = delete;
	ATestGameMode(ATestGameMode&& _Other) noexcept = delete;
	ATestGameMode& operator=(const ATestGameMode& _Other) = delete;
	ATestGameMode& operator=(ATestGameMode&& _Other) noexcept = delete;

	void MakeTileMap(ATileMap* _TileName, int _Index = 2);
	void DestroyTileMap(ATileMap* _TileName);

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* IsTile = nullptr;
	USpriteRenderer* YouTile = nullptr;
	USpriteRenderer* WinTile = nullptr;
	USpriteRenderer* StopTile = nullptr;
	USpriteRenderer* PushTile = nullptr;
	USpriteRenderer* SinkTile = nullptr;
	USpriteRenderer* MeltTile = nullptr;
	USpriteRenderer* HotTile = nullptr;

	USpriteRenderer* BabaTile = nullptr;
	USpriteRenderer* FlagTile = nullptr;
	USpriteRenderer* WallTile = nullptr;
	USpriteRenderer* RockTile = nullptr;
	USpriteRenderer* WaterTile = nullptr;
	USpriteRenderer* SkullTile = nullptr;
	USpriteRenderer* LavaTile = nullptr;
	USpriteRenderer* GrassTile = nullptr;
};

