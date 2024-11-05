#include "PreCompile.h"
#include "MapGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include "Background.h"
#include "Map.h"


AMapGameMode::AMapGameMode()
{
}

AMapGameMode::~AMapGameMode()
{
}

void AMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	ABackground* BG = GetWorld()->SpawnActor<ABackground>();
	AMap* WorldMap = GetWorld()->SpawnActor<AMap>();
}

void AMapGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	if (true == UEngineInput::GetInst().IsDown('F'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Play");
	}
}