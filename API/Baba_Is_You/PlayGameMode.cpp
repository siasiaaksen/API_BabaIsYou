#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Background.h"


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	ABackground* BG = GetWorld()->SpawnActor<ABackground>();
	APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();

	{
		GroundTileMap = GetWorld()->SpawnActor<ATileMap>();
		GroundTileMap->Create("Tile.png", { 10, 10 }, { 54, 54 });

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				GroundTileMap->SetTileIndex({ y,x }, 0);
			}
		}
	}
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
