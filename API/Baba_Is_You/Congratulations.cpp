#include "PreCompile.h"
#include "Congratulations.h"
#include "ContentsEnum.h"


ACongratulations::ACongratulations()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::CONGRA);
	SpriteRenderer->SetSprite("CongratulationsUI.bmp");
	SpriteRenderer->CreateAnimation("Winning", "CongratulationsUI.bmp", 0, 36, 0.03f, false);
	FVector2D LogoScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation({ 640, 360 });
}

ACongratulations::~ACongratulations()
{
}

void ACongratulations::BeginPlay()
{
	Super::BeginPlay();
}

void ACongratulations::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACongratulations::Winning()
{
	SpriteRenderer->ChangeAnimation("Winning");
}

