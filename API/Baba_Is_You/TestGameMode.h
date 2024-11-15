#pragma once
#include "BabaMapGameMode.h"
#include <string>
#include <EnginePlatform/EngineSound.h>

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

	bool IsLogicResult();

	void TileCheck();
	void NextTileCheck(FIntPoint _Index, FIntPoint _Dir, int _Order);
	void LastTileCheck(FIntPoint _Index, int _Order);

	void BeginPlay() override;

protected:
	void Tick(float _DeltaTime) override;

private:
	ATileMap* TileMap = nullptr;

	FIntPoint Scale;

	ELogicType F;
	EVLogicType S;
	ELogicType T;

	// 프레임마다 Tick이 돌면서 확인해야하는(ex. Flag Is Win/Baba Is You일 때 바바가 깃발에 닿았나 확인)
	std::function<void()> UpdateLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	// BeginPlay처럼 준비단계
	std::function<void()> StartLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	std::list<std::function<void()>> TileCombine;

	// 사운드 테스트
	//USoundPlayer BGMPlayer;
};

