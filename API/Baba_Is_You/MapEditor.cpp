#include "PreCompile.h"
#include "MapEditor.h"
#include "TileMap.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>

AMapEditor::AMapEditor()
{
}

AMapEditor::~AMapEditor()
{
}

void AMapEditor::BeginPlay()
{
	Super::BeginPlay();

	Scale = { 33, 18 };
	CreateStageInit(Scale);
}

void AMapEditor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('O'))
	{
		if (Scale.X > 33 || Scale.X <= 1 || Scale.Y > 18 || Scale.Y <= 1)
		{
			return;
		}

		Scale = Scale - FIntPoint(1, 0);
		CreateStageInit(Scale, true);
	}

	if (true == UEngineInput::GetInst().IsDown('P'))
	{
		if (Scale.X > 33 || Scale.X <= 1 || Scale.Y > 18 || Scale.Y <= 1)
		{
			return;
		}

		Scale = Scale + FIntPoint(1, 0);
		CreateStageInit(Scale, true);
	}
}