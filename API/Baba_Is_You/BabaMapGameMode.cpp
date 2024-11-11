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
	FVector2D BackScale = { _Scale.X * 36, _Scale.Y * 36 };

    CenterPivot.X = (1280 - (_Scale.X * 36)) / 2;
    CenterPivot.Y = (720 - (_Scale.Y * 36)) / 2;

	BackgroundMap = GetWorld()->SpawnActor<ATileMap>();
	BackgroundMap->Create(_Scale, {36, 36});
	BackgroundMap->SetActorLocation(CenterPivot);
	for (int y = 0; y < _Scale.Y; y++)
	{
		for (int x = 0; x < _Scale.X; x++)
		{
			BackgroundMap->SetTileIndex("Background_Black36.png", { x, y }, {0, 0}, { 36, 36 }, 0, ERenderOrder::STAGEBG);
		}
	}
}
