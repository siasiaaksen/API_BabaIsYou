#include "PreCompile.h"
#include "Fade.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


AFade::AFade()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::FADE);
	SpriteRenderer->SetSprite("Fade");
	SpriteRenderer->CreateAnimation("FadeIn", "Fade", 34, 0, 0.03f, false);
	SpriteRenderer->CreateAnimation("FadeOut", "Fade", 0, 34, 0.03f, false);
	FVector2D LogoScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation({ 640, 360 });
}

AFade::~AFade()
{
}

void AFade::BeginPlay()
{
	Super::BeginPlay();
}

void AFade::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFade::FadeIn()
{
	SpriteRenderer->ChangeAnimation("FadeIn");
}

void AFade::FadeOut()
{
	SpriteRenderer->ChangeAnimation("FadeOut");
}

void AFade::FadeDestroy()
{
	SpriteRenderer->Destroy();
}

