#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ATitleLogo::ATitleLogo()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::TITLELOGO);
		SpriteRenderer->SetSprite("TitleLogo370.png");
		SpriteRenderer->CreateAnimation("Logo", "TitleLogo370.png", 0, 2, 0.1f);
		SpriteRenderer->ChangeAnimation("Logo");

		FVector2D LogoScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation({960, 340});
	}
}

ATitleLogo::~ATitleLogo()
{
}

