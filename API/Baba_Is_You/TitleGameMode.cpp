#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"
#include "TitleLogo.h"
#include "TitleBackground.h"
#include "MapGameMode.h"


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
	AButtons* Btn = GetWorld()->SpawnActor<AButtons>();
	Fade = GetWorld()->SpawnActor<AFade>();

	// Buttons
	{
		// StartBtn
		Btn->SetButton("StartButton784_51.png", { 640, 450 });
		Btns.push_back(Btn);

		// SettingsBtn
		Btn->SetButton("SettingButton786_51.png", { 640, 530 });
		Btns.push_back(Btn);

		// ExitBtn
		Btn->SetButton("ExitButton786_51.png", { 640, 610 });
		Btns.push_back(Btn);
	}

	// Baba
	{
		// StartBtn
		{
			USpriteRenderer* BabaSprite = CreateDefaultSubObject<USpriteRenderer>();;
			BabaSprite->SetOrder(ERenderOrder::BABASELECT);
			BabaSprite->SetSprite("BabaObject.png");
			BabaSprite->CreateAnimation("TitleBaba", "BabaObject.png", { 2, 22, 42 }, 0.2f);
			BabaSprite->ChangeAnimation("TitleBaba");
			FVector2D BabaSpriteScale = BabaSprite->SetSpriteScale(1.0f);
			BabaSprite->SetComponentLocation({ 425, 450 });
			Babas.push_back(BabaSprite);
			BabaSprite->SetActive(true);
		}
		// SettingsBtn
		{
			USpriteRenderer* BabaSprite = CreateDefaultSubObject<USpriteRenderer>();;
			BabaSprite->SetOrder(ERenderOrder::BABASELECT);
			BabaSprite->SetSprite("BabaObject.png");
			BabaSprite->CreateAnimation("TitleBaba", "BabaObject.png", { 2, 22, 42 }, 0.2f);
			BabaSprite->ChangeAnimation("TitleBaba");
			FVector2D BabaSpriteScale = BabaSprite->SetSpriteScale(1.0f);
			BabaSprite->SetComponentLocation({ 425, 530 });
			Babas.push_back(BabaSprite);
			BabaSprite->SetActive(false);
		}
		// ExitBtn
		{
			USpriteRenderer* BabaSprite = CreateDefaultSubObject<USpriteRenderer>();;
			BabaSprite->SetOrder(ERenderOrder::BABASELECT);
			BabaSprite->SetSprite("BabaObject.png");
			BabaSprite->CreateAnimation("TitleBaba", "BabaObject.png", { 2, 22, 42 }, 0.2f);
			BabaSprite->ChangeAnimation("TitleBaba");
			FVector2D BabaSpriteScale = BabaSprite->SetSpriteScale(1.0f);
			BabaSprite->SetComponentLocation({ 425, 610 });
			Babas.push_back(BabaSprite);
			BabaSprite->SetActive(false);
		}
	}
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	BtnSelect();

	if (IsAnimed)
	{
		MoveMapLevel();
	}
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

		OptionSound = UEngineSound::Play("OptionCursorSound.ogg");
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

		OptionSound = UEngineSound::Play("OptionCursorSound.ogg");
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		if (CurBtnIndex == 0)
		{
			SelectSound = UEngineSound::Play("OptionSelect.ogg");
			BGMPlayer.Off();
			Fade->FadeOut();
			IsAnimed = true;
		}
	}
}

void ATitleGameMode::MoveMapLevel()
{
	IsAnimEnd = Fade->GetSRenderer()->IsCurAnimationEnd();

	if (IsAnimEnd)
	{
		UEngineAPICore::GetCore()->OpenLevel("Map");
	}
}
