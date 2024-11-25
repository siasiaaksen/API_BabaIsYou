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
		// NumBG
		TileMap->SetTile("WorldMapNumberBack36.png", { 9, 15 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 10, 13 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 11, 13 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 10, 12 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 11, 12 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 12, 12 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 10, 11 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		TileMap->SetTile("WorldMapNumberBack36.png", { 11, 11 }, 0, static_cast<int>(EMapOrder::BGCIRCLE), ERenderOrder::LOWER);
		
		// Line
		TileMap->SetTile("Line.png", { 10, 15 }, 8, static_cast<int>(EMapOrder::LINE), ERenderOrder::LOWER);
		TileMap->SetTile("Line.png", { 10, 14 }, 12, static_cast<int>(EMapOrder::LINE), ERenderOrder::LOWER);
		TileMap->SetTile("Line.png", { 12, 13 }, 8, static_cast<int>(EMapOrder::LINE), ERenderOrder::LOWER);
		TileMap->SetTile("Line.png", { 12, 11 }, 14, static_cast<int>(EMapOrder::LINE), ERenderOrder::LOWER);
		
		// SelectBox
		TileMap->SetTile("SelectBox.png", { 9, 15 }, { 0, 0 }, { 54, 54 }, 0, static_cast<int>(EMapOrder::SELECTBOX), ERenderOrder::UPPER);
		
		// NUMBER
		TileMap->SetTile("LevelNum.png", { 9, 15 }, 0, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		TileMap->SetTile("LevelNum.png", { 10, 13 }, 1, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		TileMap->SetTile("LevelNum.png", { 10, 12 }, 2, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		TileMap->SetTile("LevelNum.png", { 11, 13 }, 3, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		TileMap->SetTile("LevelNum.png", { 11, 12 }, 4, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		TileMap->SetTile("LevelNum.png", { 10, 11 }, 5, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		TileMap->SetTile("LevelNum.png", { 12, 12 }, 6, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
		TileMap->SetTile("LevelNum.png", { 11, 11 }, 7, static_cast<int>(EMapOrder::NUMBER), ERenderOrder::UPPER);
	}
}

void AMapGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("BGTileSize : " + Scale.ToString());

	//if (true == UEngineInput::GetInst().IsDown('R'))
	//{
	//	UEngineAPICore::GetCore()->OpenLevel("Title");
	//}

	//if (true == UEngineInput::GetInst().IsDown('F'))
	//{
	//	UEngineAPICore::GetCore()->OpenLevel("Play");
	//}

	BoxMove();
}

void AMapGameMode::BoxMove()
{
	if (true == UEngineInput::GetInst().IsDown('W') || true == UEngineInput::GetInst().IsDown(VK_UP))
	{
	}

	if (true == UEngineInput::GetInst().IsDown('S') || true == UEngineInput::GetInst().IsDown(VK_DOWN))
	{
	}

	if (true == UEngineInput::GetInst().IsDown('A') || true == UEngineInput::GetInst().IsDown(VK_LEFT))
	{
	}

	if (true == UEngineInput::GetInst().IsDown('D') || true == UEngineInput::GetInst().IsDown(VK_RIGHT))
	{
	}
}

void AMapGameMode::IsMovable()
{
}