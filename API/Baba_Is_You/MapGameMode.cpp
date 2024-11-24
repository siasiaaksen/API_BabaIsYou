#include "PreCompile.h"
#include "MapGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include "Background.h"
#include "Map.h"


AMapGameMode::AMapGameMode()
{
}

AMapGameMode::~AMapGameMode()
{
}

void AMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	ABackground* BG = GetWorld()->SpawnActor<ABackground>();
	AMap* WorldMap = GetWorld()->SpawnActor<AMap>();

	Scale = { 33, 18 };
	FVector2D CenterPivot;
	CenterPivot.X = (1280 - (Scale.X * 36)) / 2;
	CenterPivot.Y = (720 - (Scale.Y * 36)) / 2;
	TileMap = GetWorld()->SpawnActor<ATileMap>();
	TileMap->Create(Scale, { 36, 36 });
	TileMap->SetActorLocation(CenterPivot);

	{
		TileMap->SetTile("WorldMapNumberBack36.png", { 9, 15 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 11, 12 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 11, 11 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 12, 12 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 12, 11 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 10, 10 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 13, 11 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 12, 10 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		
		TileMap->SetTile("Line.png", { 11, 14 }, 8, static_cast<int>(EMapOrder::LINE), ERenderOrder::LOWER);
		TileMap->SetTile("Line.png", { 11, 13 }, 12, static_cast<int>(EMapOrder::LINE), ERenderOrder::LOWER);
		TileMap->SetTile("Line.png", { 13, 12 }, 8, static_cast<int>(EMapOrder::LINE), ERenderOrder::LOWER);
		TileMap->SetTile("Line.png", { 13, 10 }, 14, static_cast<int>(EMapOrder::LINE), ERenderOrder::LOWER);
		
		//TileMap->SetTile("SelectBox.png", { 10, 14 }, { 36, 36 }, { 72, 72 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::UPPER);
		
		// NUMBER
		//TileMap->SetTile("00.png", { 10, 14 }, 1, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		//TileMap->SetTile("01.png", { 11, 12 }, 1, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		//TileMap->SetTile("02.png", { 11, 11 }, 1, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		//TileMap->SetTile("03.png", { 12, 12 }, 1, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		//TileMap->SetTile("04.png", { 12, 11 }, 1, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		//TileMap->SetTile("05.png", { 10, 11 }, 1, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		//TileMap->SetTile("06.png", { 13, 11 }, 1, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		//TileMap->SetTile("07.png", { 12, 10 }, 1, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
	}
}

void AMapGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("BGTileSize : " + Scale.ToString());
	UEngineDebug::CoreOutPutString("CurTileIndex : " + MouseIndex.ToString());

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	if (true == UEngineInput::GetInst().IsDown('F'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Play");
	}

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

		if (MousePos.iX() < TileMap->GetActorLocation().iX() ||
			MousePos.iY() < TileMap->GetActorLocation().iY())
		{
			return;
		}

		MouseIndex = TileMap->LocationToIndex(MousePos - TileMap->GetActorLocation());
	}
}