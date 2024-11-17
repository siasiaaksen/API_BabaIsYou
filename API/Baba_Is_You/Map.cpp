#include "PreCompile.h"
#include "Map.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

AMap::AMap()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::WORLDMAP);
		SpriteRenderer->SetSprite("WorldMap1188_650.png");
		SpriteRenderer->CreateAnimation("WorldMap", "WorldMap1188_650.png", 0, 2, 0.3f);
		SpriteRenderer->ChangeAnimation("WorldMap");
		SpriteRenderer->SetComponentScale({ 1188, 650 });
		SpriteRenderer->SetComponentLocation({ 640, 360 });
	}
}

AMap::~AMap()
{
}

