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
	{
		AButtons* StartBtn = GetWorld()->SpawnActor<AButtons>();
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BUTTON);
		SpriteRenderer->SetSprite("StartButton784_51.png");

		FVector2D StartBtnScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation({ 640, 450 });

		StartBtn->SetButtonPos({ 640, 367 });
		StartBtn->SetButtonScale(StartBtnScale);
	}

	{
		AButtons* SettingsBtn = GetWorld()->SpawnActor<AButtons>();
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BUTTON);
		SpriteRenderer->SetSprite("SettingButton786_51.png");

		FVector2D SettingsBtnScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation({ 640, 530 });

		SettingsBtn->SetButtonPos({ 640, 467 });
		SettingsBtn->SetButtonScale(SettingsBtnScale);
	}

	{
		AButtons* ExitBtn = GetWorld()->SpawnActor<AButtons>();
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BUTTON);
		SpriteRenderer->SetSprite("ExitButton786_51.png");

		FVector2D ExitBtnScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation({ 640, 610 });

		ExitBtn->SetButtonPos({ 640, 567 });
		ExitBtn->SetButtonScale(ExitBtnScale);
	}

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}