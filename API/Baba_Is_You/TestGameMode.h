#pragma once
#include "BabaMapGameMode.h"
#include <string>

#include "TileMap.h"


class ATestGameMode : public ABabaMapGameMode
{
public:
	ATestGameMode();
	~ATestGameMode();

	ATestGameMode(const ATestGameMode& _Other) = delete;
	ATestGameMode(ATestGameMode&& _Other) noexcept = delete;
	ATestGameMode& operator=(const ATestGameMode& _Other) = delete;
	ATestGameMode& operator=(ATestGameMode&& _Other) noexcept = delete;

	void Move(std::string _CurSprite);

	//void MakeTileMap(ATileMap* _TileName, int _Index = 2);
	//void DestroyTileMap(ATileMap* _TileName);

	void BeginPlay() override;

protected:

	void Tick(float _DeltaTime) override;

private:
	// 위에 겹쳐지는 타일
	ATileMap* UpperTileMap = nullptr;
	// 아래에 깔릴수도 있는 타일
	ATileMap* LowerTileMap = nullptr;
	FIntPoint CurTileIndex;
};

