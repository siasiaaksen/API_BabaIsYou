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
	int ClickNum = 0; // 버튼이 눌려있을 때 마우스 클릭할 때마다 횟수를 늘려서 인덱스 변경하기
	std::string_view SpriteName;

	FIntPoint Scale;
	ATileMap* TileMap = nullptr;
	FIntPoint MouseIndex;
};

