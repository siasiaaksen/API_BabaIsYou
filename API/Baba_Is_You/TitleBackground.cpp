#include "PreCompile.h"
#include "TitleBackground.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


ATitleBackground::ATitleBackground()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("Background_Gray.png");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}
}

ATitleBackground::~ATitleBackground()
{
}