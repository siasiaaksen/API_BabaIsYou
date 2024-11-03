#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

TitleLogo::TitleLogo()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::TITLELOGO);
		SpriteRenderer->SetSprite("TitleLogo370.png");
		SpriteRenderer->CreateAnimation("Logo", "TitleLogo370.png", 0, 2, 0.1f);
		SpriteRenderer->ChangeAnimation("Logo");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half() * 2.0f);
	}
}

TitleLogo::~TitleLogo()
{
}

