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
	// ���� �������� Ÿ��
	ATileMap* UpperTileMap = nullptr;
	// �Ʒ��� �򸱼��� �ִ� Ÿ��
	ATileMap* LowerTileMap = nullptr;

	FIntPoint Scale;
	std::string CurSprite;
	FIntPoint CurIndex;
	Tile* CurTile = nullptr;

	ELogicType F;
	EVLogicType S;
	ELogicType T;


	// ������ Ÿ��
	std::vector<ELogicType> MoveTiles;

	// �����Ӹ��� Tick�� ���鼭 Ȯ���ؾ��ϴ�(ex. Flag Is Win/Baba Is You�� �� �ٹٰ� ��߿� ��ҳ� Ȯ��)
	std::function<void()> UpdateLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	// BeginPlayó�� �غ�ܰ�
	std::function<void()> StartLogic[static_cast<int>(ELogicType::MAX)][static_cast<int>(EVLogicType::MAX)][static_cast<int>(ELogicType::MAX)] =
	{ nullptr };

	std::list<std::function<void()>> TileCombine;
};

