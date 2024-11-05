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
		SpriteRenderer->SetSprite("StartButton589_76.png");

		FVector2D StartBtnScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation({ 960, 570 });

		StartBtn->SetButtonPos({ 960, 570 });
		StartBtn->SetButtonScale(StartBtnScale);
	}

	{
		AButtons* SettingsBtn = GetWorld()->SpawnActor<AButtons>();
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BUTTON);
		SpriteRenderer->SetSprite("SettingButton589_76.png");

		FVector2D SettingsBtnScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation({ 960, 670 });

		SettingsBtn->SetButtonPos({ 960, 670 });
		SettingsBtn->SetButtonScale(SettingsBtnScale);
	}

	{
		AButtons* ExitBtn = GetWorld()->SpawnActor<AButtons>();
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BUTTON);
		SpriteRenderer->SetSprite("ExitButton589_76.png");

		FVector2D ExitBtnScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation({ 960, 770 });

		ExitBtn->SetButtonPos({ 960, 770 });
		ExitBtn->SetButtonScale(ExitBtnScale);
	}

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}