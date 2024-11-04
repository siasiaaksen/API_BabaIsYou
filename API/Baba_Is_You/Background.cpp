#include "PreCompile.h"
#include "Background.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


ABackground::ABackground()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("Background_Gray.png");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}
}

ABackground::~ABackground()
{
}

