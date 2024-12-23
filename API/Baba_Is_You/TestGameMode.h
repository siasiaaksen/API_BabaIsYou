#pragma once
#include "BabaMapGameMode.h"
#include <string>
#include <EnginePlatform/EngineSound.h>

#include "TileMap.h"
#include "ContentsEnum.h"


enum class ETestGameState
{
	NONE,
	SELECT, // 유저가 뭔가를 하려는 단계
	ACTION, // 유저가 선택한게 이루어지는 단계 이루어지면서 기록도 한다.
	UNDO,
	MAX,
};

class ATestGameMode : public ABabaMapGameMode
{
public:
	ATestGameMode();
	~ATestGameMode();

	ATestGameMode(const ATestGameMode& _Other) = delete;
	ATestGameMode(ATestGameMode&& _Other) noexcept = delete;
	ATestGameMode& operator=(const ATestGameMode& _Other) = delete;
	ATestGameMode& operator=(ATestGameMode&& _Other) noexcept = delete;

	bool IsMove();

	void MoveCheck();
	void UndoCheck();

	void OO_IS_ATTMoveSetting(ELogicType _FLogicType, ELogicType _TLogicType, ELogicType _CurObject, EMoveType _MoveType);
	void OO_IS_ATTStateSetting(ELogicType _FLogicType, ELogicType _TLogicType, ELogicType _CurObject, EStateType _StateType);
	void MM_IS_NNSetting(ELogicType _FLogicType, ELogicType _TLogicType, ELogicType _CurObject, ELogicType _ChangeObject);

	bool IsLogicResult();

	void TileCheck();
	void NextTileCheck(FIntPoint _Index, FIntPoint _Dir, int _Order);
	void LastTileCheck(FIntPoint _Index, int _Order);

	void SetState(ETestGameState _State)
	{
		State = _State;
	}

	ETestGameState GetState() const
	{
		return State;
	}

	void BeginPlay() override;

	void Action(float _DeltaTime);
	void Undo(float _DeltaTime);

	void GameState(float _DeltaTime);

protected:
	void Tick(float _DeltaTime) override;

private:
	ATileMap* TileMap = nullptr;

	FIntPoint Scale;

	ELogicType F;
	EVLogicType S;
	ELogicType T;

	bool IsFirstCombine = false;
	bool IsSecondCombine = false;

	// 프레임마다 Tick이 돌면서 확인해야하는(ex. Flag Is Win/Baba Is You일 때 바바가 깃발에 닿았나 확인)
	std::function<void()> UpdateLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	// BeginPlay처럼 준비단계
	std::function<void()> StartLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	std::list<std::function<void()>> TileCombine;

	ETestGameState State;
};

