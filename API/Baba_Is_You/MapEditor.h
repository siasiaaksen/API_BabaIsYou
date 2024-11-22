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

	template <typename DataType>
	void MapTileEdit(DataType _Key, std::string_view _Sprite, int _SpriteIndex, EFloorOrder _FloorOrder, ERenderOrder _RenderOrder, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

		if (MousePos.iX() < TileMap->GetActorLocation().iX() ||
			MousePos.iY() < TileMap->GetActorLocation().iY())
		{
			return;
		}

		FIntPoint MouseIndex = TileMap->LocationToIndex(MousePos - TileMap->GetActorLocation());

		if (true == UEngineInput::GetInst().IsPress(_Key))
		{
			TileMap->SetTile(_Sprite, MouseIndex, _SpriteIndex, static_cast<int>(_FloorOrder), _RenderOrder, _FLogicType, _SLogicType, _TLogicType);
		}
	}

	void KeyBind();
	void MapMaker();

protected:

private:
	FIntPoint Scale;
	ATileMap* TileMap = nullptr;
};

