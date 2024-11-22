#pragma once
#include "BabaMapGameMode.h"


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

protected:

private:
	FIntPoint Scale;
	ATileMap* TileMap = nullptr;
};

