#pragma once
#include <string>
#include <EnginePlatform/EngineSound.h>

#include "BabaMapGameMode.h"
#include "TileMap.h"
#include "ContentsEnum.h"
#include "StagePath.h"
#include "Fade.h"


enum class EGameState
{
	NONE,
	SELECT, // ������ ������ �Ϸ��� �ܰ�
	ACTION, // ������ �����Ѱ� �̷������ �ܰ� �̷�����鼭 ��ϵ� �Ѵ�.
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
	void BabaIndexChange();
	void MoveSound();

	void SetState(EGameState _State)
	{
		State = _State;
	}

	EGameState GetState() const
	{
		return State;
	}

	USoundPlayer GetBGMPlayer() const
	{
		return BGMPlayer;
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
	int Index;

	ELogicType F;
	EVLogicType S;
	ELogicType T;

	std::function<void()> UpdateLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	std::function<void()> StartLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	std::list<std::function<void()>> TileCombine;

	EGameState State;

	USoundPlayer BGMPlayer;
	USoundPlayer MovePlayer;
	AFade* Fade = nullptr;
	bool IsAnimEnd = false;
	bool IsAnimed = false;
};

