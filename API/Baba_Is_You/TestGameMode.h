#pragma once
#include "BabaMapGameMode.h"
#include <string>

#include "TileMap.h"
#include "ContentsEnum.h"


class ATestGameMode : public ABabaMapGameMode
{
public:
	ATestGameMode();
	~ATestGameMode();

	ATestGameMode(const ATestGameMode& _Other) = delete;
	ATestGameMode(ATestGameMode&& _Other) noexcept = delete;
	ATestGameMode& operator=(const ATestGameMode& _Other) = delete;
	ATestGameMode& operator=(ATestGameMode&& _Other) noexcept = delete;

	void Move();
	void TileCheck();
	void NextTileCheck(FIntPoint _Index, FIntPoint _Dir);
	void LastTileCheck(FIntPoint _Index);

	void BeginPlay() override;

protected:
	void Tick(float _DeltaTime) override;

private:
	// 위에 겹쳐지는 타일
	ATileMap* UpperTileMap = nullptr;
	// 아래에 깔릴수도 있는 타일
	ATileMap* LowerTileMap = nullptr;

	FIntPoint Scale;
	std::string CurSprite;
	FIntPoint CurIndex;
	Tile* CurTile = nullptr;

	ELogicType F;
	EVLogicType S;
	ELogicType T;


	// 움직일 타일
	std::vector<ELogicType> MoveTiles;

	// 프레임마다 Tick이 돌면서 확인해야하는(ex. Flag Is Win/Baba Is You일 때 바바가 깃발에 닿았나 확인)
	std::function<void()> UpdateLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	// BeginPlay처럼 준비단계
	std::function<void()> StartLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	std::list<std::function<void()>> TileCombine;
};

