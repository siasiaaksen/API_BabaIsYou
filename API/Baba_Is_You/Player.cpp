#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

#include <EnginePlatform/EngineInput.h>

APlayer::APlayer()
{
	SetActorLocation({ 100, 100 });
	//SetActorScale({ 64, 64 }); // <= 여기도 사이즈에 맞춰 변경

	// 이름 넣기
	//SetSprite("Baba.png");
	
	// 수정해야됨
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Baba.png");
		SpriteRenderer->SetComponentScale({ 100, 100 });

		SpriteRenderer->CreateAnimation("Run_Right", "Baba.png", 0, 3, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Right", "Baba.png", { 18, 40, 62 }, 0.1f);
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}

	{
		//USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
		//Renderer->SetSprite("Baba.png");
		//Renderer->SetComponentLocation({ 0, 0 });
		//Renderer->SetComponentScale({ 54, 54 });
	}
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
}

// 수정해야됨
void APlayer::Tick(float _DeltaTime)
{
	Super::BeginPlay();

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
		UEngineDebug::SwitchIsDebug();
	}

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}
	
	if (false == UEngineInput::GetInst().IsPress('A') && 
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}
}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}