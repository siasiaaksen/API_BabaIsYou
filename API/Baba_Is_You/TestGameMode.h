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
	ATileMap* IsTileMap = nullptr;
	ATileMap* YouTileMap = nullptr;
	ATileMap* WinTileMap = nullptr;
	ATileMap* StopTileMap = nullptr;
	ATileMap* PushTileMap = nullptr;
	ATileMap* SinkTileMap = nullptr;
	ATileMap* DefeatTileMap = nullptr;
	ATileMap* MeltTileMap = nullptr;
	ATileMap* HotTileMap = nullptr;

	ATileMap* BabaTileMap = nullptr;
	ATileMap* FlagTileMap = nullptr;
	ATileMap* WallTileMap = nullptr;
	ATileMap* RockTileMap = nullptr;
	ATileMap* WaterTileMap = nullptr;
	ATileMap* SkullTileMap = nullptr;
	ATileMap* LavaTileMap = nullptr;
	ATileMap* GrassTileMap = nullptr;

	ATileMap* BabaTextTileMap = nullptr;
	ATileMap* FlagTextTileMap = nullptr;
	ATileMap* WallTextTileMap = nullptr;
	ATileMap* RockTextTileMap = nullptr;
	ATileMap* WaterTextTileMap = nullptr;
	ATileMap* SkullTextTileMap = nullptr;
	ATileMap* LavaTextTileMap = nullptr;
	ATileMap* GrassTextTileMap = nullptr;
};

