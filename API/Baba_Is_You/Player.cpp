#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/EngineDirectory.h>

#include "ContentsEnum.h"


APlayer::APlayer()
{
	SetActorLocation({ 162, 162 });
	
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("BabaObject.png", 18);
		SpriteRenderer->SetOrder(ERenderOrder::PLAYER);
		SpriteRenderer->SetComponentScale({ 36, 36 });
		std::string Name = SpriteRenderer->GetCurSpriteName();
	}
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	if (true == UEngineInput::GetInst().IsDown('Q'))
	{
		UEngineDebug::SwitchIsDebug();
	}

	Move();
}

void APlayer::Move()
{
	if (true == UEngineInput::GetInst().IsDown('D'))
	{
		AddActorLocation(FVector2D::RIGHT * 54);
	}
	if (true == UEngineInput::GetInst().IsDown('A'))
	{
		AddActorLocation(FVector2D::LEFT * 54);
	}
	if (true == UEngineInput::GetInst().IsDown('S'))
	{
		AddActorLocation(FVector2D::DOWN * 54);
	}
	if (true == UEngineInput::GetInst().IsDown('W'))
	{
		AddActorLocation(FVector2D::UP * 54);
	}

	if (true == UEngineInput::GetInst().IsDown('A') ||
		true == UEngineInput::GetInst().IsDown('D') ||
		true == UEngineInput::GetInst().IsDown('W') ||
		true == UEngineInput::GetInst().IsDown('S'))
	{
		if (2 >= BabaIndex)
		{
			BabaIndex = 2;
		}

		if (5 < BabaIndex)
		{
			BabaIndex = 2;
		}

		SpriteRenderer->SetSprite("Baba.png", BabaIndex);
		++BabaIndex;
	}

	//if (false == UEngineInput::GetInst().IsPress('A') &&
	//	false == UEngineInput::GetInst().IsPress('D') &&
	//	false == UEngineInput::GetInst().IsPress('W') &&
	//	false == UEngineInput::GetInst().IsPress('S'))
	//{
	//	//SpriteRenderer->ChangeAnimation("Idle_Right");
	//	SpriteRenderer->SetSprite("Baba.png", 18);
	//}
}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}