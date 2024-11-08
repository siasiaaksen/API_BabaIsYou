#pragma once
#include <EngineCore/GameMode.h>

#include <EngineCore/SpriteRenderer.h>
#include "TileMap.h"

class ABabaMapGameMode : public AGameMode
{
public:
	ABabaMapGameMode();
	~ABabaMapGameMode();

	ABabaMapGameMode(const ABabaMapGameMode& _Other) = delete;
	ABabaMapGameMode(ABabaMapGameMode&& _Other) noexcept = delete;
	ABabaMapGameMode& operator=(const ABabaMapGameMode& _Other) = delete;
	ABabaMapGameMode& operator=(ABabaMapGameMode&& _Other) noexcept = delete;

	void CreateStageInit(FIntPoint _Scale);

protected:
	FVector2D CenterPivot;
private:
	ATileMap* BackgroundMap = nullptr;
	USpriteRenderer* Background = nullptr;

};

