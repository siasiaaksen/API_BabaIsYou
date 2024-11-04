#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


APlayMap::APlayMap()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("Background_Black.png");
		SpriteRenderer->SetComponentScale({ 1782, 972 });
		SpriteRenderer->SetComponentLocation({960, 500});
	}
}

APlayMap::~APlayMap()
{
}

