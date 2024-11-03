#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"


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

	APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();
}
