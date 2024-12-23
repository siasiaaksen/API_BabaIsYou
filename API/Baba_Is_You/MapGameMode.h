#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include "TileMap.h"
#include "SelectBox.h"
#include "Fade.h"


class AMapGameMode : public AGameMode
{
public:
	AMapGameMode();
	~AMapGameMode();

	AMapGameMode(const AMapGameMode& _Other) = delete;
	AMapGameMode(AMapGameMode&& _Other) noexcept = delete;
	AMapGameMode& operator=(const AMapGameMode& _Other) = delete;
	AMapGameMode& operator=(AMapGameMode&& _Other) noexcept = delete;

	void BoxMove(float _DeltaTime);
	bool IsMovable(FVector2D _NextPos);
	void MoveCheck(FVector2D _Dir);
	bool IsSelectable();
	void SelectStage();
	void VisibleStageName();

	void MoveSound();
	void MovePlayLevel();
	void MoveTitleLevel();
	void ChangeTitleLevel();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	ATileMap* TileMap = nullptr;

	FIntPoint Scale;
	FIntPoint MouseIndex;
	FVector2D EndPos;

	ASelectBox* SelectBox = nullptr;
	AFade* Fade = nullptr;

	USpriteRenderer* SpriteRenderer;

	float ActionTime = 0.0f;
	int SpriteIndex = 0;

	USoundPlayer BGMPlayer;
	USoundPlayer MovePlayer;
	USoundPlayer SelectSound;

	bool IsAnimEnd = false;
	bool IsAnimed = false;
	bool IsTitleAnimed = false;
};

