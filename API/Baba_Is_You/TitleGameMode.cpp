#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

#include "TitleLogo.h"
#include "TitleBackground.h"
#include "Buttons.h"


ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	ATitleLogo* NewTitleLogo = GetWorld()->SpawnActor<ATitleLogo>();
	ATitleBackground* NewBG = GetWorld()->SpawnActor<ATitleBackground>();
	AButtons* StartBtn = GetWorld()->SpawnActor<AButtons>();
	AButtons* ExitBtn = GetWorld()->SpawnActor<AButtons>();
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//if (true == UEngineInput::GetInst().IsDown('R'))
	//{
	//	UEngineAPICore::GetCore()->OpenLevel("Play");
	//}
}