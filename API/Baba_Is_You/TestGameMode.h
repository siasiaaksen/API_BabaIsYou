#pragma once
#include "BabaMapGameMode.h"
#include <string>
#include <EnginePlatform/EngineSound.h>

#include "TileMap.h"
#include "ContentsEnum.h"


enum class EGameState
{
	NONE,
	SELECT, // ������ ������ �Ϸ��� �ܰ�
	ACTION, // ������ �����Ѱ� �̷������ �ܰ� �̷�����鼭 ��ϵ� �Ѵ�.
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

	void MoveCheck();

	bool IsLogicResult();

	void TileCheck();
	void NextTileCheck(FIntPoint _Index, FIntPoint _Dir, int _Order);
	void LastTileCheck(FIntPoint _Index, int _Order);

	void SetState(EGameState _State)
	{
		State = _State;
	}

	void BeginPlay() override;

	void Action(float _DeltaTime);
	void Undo(float _DeltaTime);

protected:
	void Tick(float _DeltaTime) override;

private:
	ATileMap* TileMap = nullptr;

	FIntPoint Scale;

	ELogicType F;
	EVLogicType S;
	ELogicType T;

	// �����Ӹ��� Tick�� ���鼭 Ȯ���ؾ��ϴ�(ex. Flag Is Win/Baba Is You�� �� �ٹٰ� ��߿� ��ҳ� Ȯ��)
	std::function<void()> UpdateLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	// BeginPlayó�� �غ�ܰ�
	std::function<void()> StartLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	std::list<std::function<void()>> TileCombine;

	EGameState State;
	// ���� �׽�Ʈ
	//USoundPlayer BGMPlayer;
};

