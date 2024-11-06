#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Background.h"


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	ABackground* BG = GetWorld()->SpawnActor<ABackground>();
	APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	if (true == UEngineInput::GetInst().IsDown('F'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Map");
	}
}
