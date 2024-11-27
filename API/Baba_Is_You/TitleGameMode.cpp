#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"
#include "TitleLogo.h"
#include "TitleBackground.h"
#include "Fade.h"


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

	BGMPlayer = UEngineSound::Play("menu.ogg");

	ATitleBackground* NewBG = GetWorld()->SpawnActor<ATitleBackground>();
	ATitleLogo* NewTitleLogo = GetWorld()->SpawnActor<ATitleLogo>();

	// Buttons
	{
		// StartBtn
		AButtons* StartBtn = GetWorld()->SpawnActor<AButtons>();
		StartBtn->SetButton("StartButton784_51.png", { 640, 450 });
		Btns.push_back(StartBtn);

		// SettingsBtn
		AButtons* SettingsBtn = GetWorld()->SpawnActor<AButtons>();
		SettingsBtn->SetButton("SettingButton786_51.png", { 640, 530 });
		Btns.push_back(SettingsBtn);

		// ExitBtn
		AButtons* ExitBtn = GetWorld()->SpawnActor<AButtons>();
		ExitBtn->SetButton("ExitButton786_51.png", { 640, 610 });
		Btns.push_back(ExitBtn);
	}

	// Baba
	{
		// StartBtn
		{
			USpriteRenderer* StartBabaSprite = CreateDefaultSubObject<USpriteRenderer>();;
			StartBabaSprite->SetOrder(ERenderOrder::BABASELECT);
			StartBabaSprite->SetSprite("BabaObject.png");
			FVector2D StartBtnScale = StartBabaSprite->SetSpriteScale(1.0f);
			StartBabaSprite->SetComponentLocation({ 425, 450 });
			Babas.push_back(StartBabaSprite);
			StartBabaSprite->SetActive(true);
		}
		// SettingsBtn
		{
			USpriteRenderer* SettingsBabaSprite = CreateDefaultSubObject<USpriteRenderer>();;
			SettingsBabaSprite->SetOrder(ERenderOrder::BABASELECT);
			SettingsBabaSprite->SetSprite("BabaObject.png");
			FVector2D StartBtnScale = SettingsBabaSprite->SetSpriteScale(1.0f);
			SettingsBabaSprite->SetComponentLocation({ 425, 530 });
			Babas.push_back(SettingsBabaSprite);
			SettingsBabaSprite->SetActive(false);
		}
		// ExitBtn
		{
			USpriteRenderer* ExitBabaSprite = CreateDefaultSubObject<USpriteRenderer>();;
			ExitBabaSprite->SetOrder(ERenderOrder::BABASELECT);
			ExitBabaSprite->SetSprite("BabaObject.png");
			FVector2D StartBtnScale = ExitBabaSprite->SetSpriteScale(1.0f);
			ExitBabaSprite->SetComponentLocation({ 425, 610 });
			Babas.push_back(ExitBabaSprite);
			ExitBabaSprite->SetActive(false);
		}
	}
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	BtnSelect();
}

void ATitleGameMode::BtnSelect()
{
	if (true == UEngineInput::GetInst().IsDown(VK_UP) || true == UEngineInput::GetInst().IsDown('W'))
	{
		--CurBtnIndex;

		if (CurBtnIndex < 0)
		{
			CurBtnIndex = Btns.size() - 1;
		}

		for (int i = 0; i < Babas.size(); i++)
		{
			if (i == CurBtnIndex)
			{
				Babas[i]->SetActive(true);
			}
			else
			{
				Babas[i]->SetActive(false);
			}
		}
	}

	if (true == UEngineInput::GetInst().IsDown(VK_DOWN) || true == UEngineInput::GetInst().IsDown('S'))
	{
		++CurBtnIndex;

		if (CurBtnIndex > Btns.size() - 1)
		{
			CurBtnIndex = 0;
		}

		for (int i = 0; i < Babas.size(); i++)
		{
			if (i == CurBtnIndex)
			{
				Babas[i]->SetActive(true);
			}
			else
			{
				Babas[i]->SetActive(false);
			}
		}
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		if (CurBtnIndex == 0)
		{
			//AFade* Fade = GetWorld()->SpawnActor<AFade>();
			//Fade->FadeOut();

			// 페이드 아웃 프레임 끝에서 오픈 레벨
			UEngineAPICore::GetCore()->OpenLevel("Map");
		}
	}
}
