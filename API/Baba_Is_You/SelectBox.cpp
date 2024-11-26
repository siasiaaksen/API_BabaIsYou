#include "PreCompile.h"
#include "SelectBox.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


ASelectBox::ASelectBox()
{
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::UPPER);
	SpriteRenderer->SetSprite("SelectBox.png");
	SpriteRenderer->CreateAnimation("SelectBox", "SelectBox.png", 0, 2, 0.3f);
	SpriteRenderer->ChangeAnimation("SelectBox");
	SpriteRenderer->SetComponentScale({ 54, 54 });
	SpriteRenderer->SetComponentLocation({ 0, 0 });
}

ASelectBox::~ASelectBox()
{
}

void ASelectBox::BeginPlay()
{
	Super::BeginPlay();
}

void ASelectBox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

