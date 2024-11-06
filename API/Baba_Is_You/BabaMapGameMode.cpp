#include "PreCompile.h"
#include "BabaMapGameMode.h"
#include "ContentsEnum.h"


ABabaMapGameMode::ABabaMapGameMode()
{
	{
		Background = CreateDefaultSubObject<USpriteRenderer>();
		Background->SetOrder(ERenderOrder::BACKGROUND);
		Background->SetSprite("Background_Gray.png");

		FVector2D MapScale = Background->SetSpriteScale(1.0f);
		Background->SetComponentLocation(MapScale.Half());
	}
}

ABabaMapGameMode::~ABabaMapGameMode()
{
}

void ABabaMapGameMode::CreateStageInit(FIntPoint _Scale)
{
	int PivotY = (1280 - (_Scale.Y * 36)) / 2;
	int PivotX = (720 - (_Scale.X * 36)) / 2;

	int a = 0;
	BackgroundMap = GetWorld()->SpawnActor<ATileMap>();
	BackgroundMap->Create({ 100, 100 }, {36, 36});
	for (int y = 0; y < _Scale.Y; y++)
	{
		for (int x = 0; x < _Scale.X; x++)
		{
			BackgroundMap->SetTileIndex("Background_Black36.png", { y, x }, { PivotY, PivotX }, { 36, 36 }, 0, static_cast<int>(ERenderOrder::STAGEBG));
		}
	}
}
