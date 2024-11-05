#include "PreCompile.h"
#include "Map.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

AMap::AMap()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::WORLDMAP);
		SpriteRenderer->SetSprite("WorldMap650.png");
		SpriteRenderer->CreateAnimation("WorldMap", "WorldMap650.png", 0, 2, 0.3f);
		SpriteRenderer->ChangeAnimation("WorldMap");
		SpriteRenderer->SetComponentScale({ 1782, 972 });
		SpriteRenderer->SetComponentLocation({ 960, 540 });
	}
}

AMap::~AMap()
{
}

