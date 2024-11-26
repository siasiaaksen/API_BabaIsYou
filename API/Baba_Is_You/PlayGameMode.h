#pragma once
#include <string>

#include "BabaMapGameMode.h"
#include "TileMap.h"
#include "ContentsEnum.h"
#include "StagePath.h"


enum class EGameState
{
	NONE,
	SELECT, // 유저가 뭔가를 하려는 단계
	ACTION, // 유저가 선택한게 이루어지는 단계 이루어지면서 기록도 한다.
	UNDO,
	MAX,
};

class APlayGameMode : public ABabaMapGameMode
{
public:
	APlayGameMode();
	~APlayGameMode();

	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

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
	void ChangeSpriteCheck(FIntPoint _Index, int _Order);

	void SetState(EGameState _State)
	{
		State = _State;
	}

	EGameState GetState() const
	{
		return State;
	}

	void BeginPlay() override;

	void Action(float _DeltaTime);
	void Undo(float _DeltaTime);

	void GameState(float _DeltaTime);
	static StagePath StagePathValue;

protected:
	void Tick(float _DeltaTime) override;

private:
	ATileMap* TileMap = nullptr;

	FIntPoint Scale;

	ELogicType F;
	EVLogicType S;
	ELogicType T;

	std::function<void()> UpdateLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	std::function<void()> StartLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	std::list<std::function<void()>> TileCombine;

	EGameState State;
};

