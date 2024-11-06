#include "PreCompile.h"
#include "Map.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

AMap::AMap()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::WORLDMAP);
		SpriteRenderer->SetSprite("WorldMap3564_649.png");
		SpriteRenderer->CreateAnimation("WorldMap", "WorldMap3564_649.png", 0, 2, 0.3f);
		SpriteRenderer->ChangeAnimation("WorldMap");
		SpriteRenderer->SetComponentScale({ 1188, 649 });
		SpriteRenderer->SetComponentLocation({ 640, 360 });
	}
}

AMap::~AMap()
{
}

