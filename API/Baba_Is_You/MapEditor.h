#pragma once
#include "BabaMapGameMode.h"
#include <EnginePlatform/EngineInput.h>


class AMapEditor : public ABabaMapGameMode
{
public:
	AMapEditor();
	~AMapEditor();

	AMapEditor(const AMapEditor& _Other) = delete;
	AMapEditor(AMapEditor&& _Other) noexcept = delete;
	AMapEditor& operator=(const AMapEditor& _Other) = delete;
	AMapEditor& operator=(AMapEditor&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	bool BGSize();
	void TileMapSetting();
	void MapTileEdit(std::string_view _Sprite, int _SpriteIndex, int _MaxCount, EFloorOrder _FloorOrder, ERenderOrder _RenderOrder, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType);
	void MapMaker();

protected:

private:
	int ClickNum = 0; // ��ư�� �������� �� ���콺 Ŭ���� ������ Ƚ���� �÷��� �ε��� �����ϱ�
	std::string_view SpriteName;

	FIntPoint Scale;
	ATileMap* TileMap = nullptr;
	FIntPoint MouseIndex;
};

