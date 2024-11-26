#include "PreCompile.h"
#include "MapGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include "Background.h"
#include "Map.h"
#include "StagePath.h"
#include "PlayGameMode.h"


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

	Scale = { 33, 18 };
	FVector2D CenterPivot;
	CenterPivot.X = (1280 - (Scale.X * 36)) / 2;
	CenterPivot.Y = (720 - (Scale.Y * 36)) / 2;

	ABackground* BG = GetWorld()->SpawnActor<ABackground>();
	AMap* WorldMap = GetWorld()->SpawnActor<AMap>();
	SelectBox = GetWorld()->SpawnActor<ASelectBox>();
	SelectBox->SetActorLocation(CenterPivot + FVector2D((9 * 36) + 18, (15 * 36) + 18));

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
		// TileMap->SetTile("SelectBox.png", { 9, 15 }, { 0, 0 }, { 54, 54 }, 0, static_cast<int>(EMapOrder::SELECTBOX), ERenderOrder::UPPER);
		
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

	FIntPoint SelectBoxIndex = TileMap->LocationToIndex(SelectBox->GetActorLocation());
	UEngineDebug::CoreOutPutString("SelectBoxIndex : " + SelectBoxIndex.ToString());

	BoxMove(_DeltaTime);
	SelectStage();
}

void AMapGameMode::BoxMove(float _DeltaTime)
{
	ActionTime += _DeltaTime * 10.0f;

	if (true == UEngineInput::GetInst().IsDown('W') || true == UEngineInput::GetInst().IsDown(VK_UP))
	{
		MoveCheck(FVector2D::UP);
	}

	if (true == UEngineInput::GetInst().IsDown('S') || true == UEngineInput::GetInst().IsDown(VK_DOWN))
	{
		MoveCheck(FVector2D::DOWN);
	}

	if (true == UEngineInput::GetInst().IsDown('A') || true == UEngineInput::GetInst().IsDown(VK_LEFT))
	{
		MoveCheck(FVector2D::LEFT);
	}

	if (true == UEngineInput::GetInst().IsDown('D') || true == UEngineInput::GetInst().IsDown(VK_RIGHT))
	{
		MoveCheck(FVector2D::RIGHT);
	}
}

bool AMapGameMode::IsMovable(FVector2D _NextPos)
{
	FIntPoint NextIndex = TileMap->LocationToIndex(_NextPos - FVector2D(36, 36));

	for (int i = 0; i < static_cast<int>(EMapOrder::MAX); i++)
	{
		Tile* NextTile = TileMap->GetTileRef(NextIndex, i);

		if (nullptr == NextTile)
		{
			continue;
		}

		if (2 == NextTile->FloorOrder || 3 == NextTile->FloorOrder)
		{
			return true;
		}
	}

	return false;
}

void AMapGameMode::MoveCheck(FVector2D _Dir)
{
	FVector2D StartPos = SelectBox->GetActorLocation();
	EndPos = StartPos + (_Dir * 36);

	if (false == IsMovable(EndPos))
	{
		return;
	}

	FVector2D CurPos = FVector2D::Lerp(StartPos, EndPos, ActionTime);
	SelectBox->SetActorLocation(CurPos);
}

bool AMapGameMode::IsSelectable()
{
	FIntPoint CurIndex = TileMap->LocationToIndex(SelectBox->GetActorLocation() - FVector2D(36, 36));

	for (int i = 0; i < static_cast<int>(EMapOrder::MAX); i++)
	{
		Tile* CurTile = TileMap->GetTileRef(CurIndex, i);

		if (nullptr == CurTile)
		{
			continue;
		}

		if (3 == CurTile->FloorOrder)
		{
			return true;
		}
	}

	return false;
}

void AMapGameMode::SelectStage()
{
	if (false == IsSelectable())
	{
		return;
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		FIntPoint CurIndex = TileMap->LocationToIndex(SelectBox->GetActorLocation() - FVector2D(36, 36));
		Tile* CurTile = TileMap->GetTileRef(CurIndex, 3);
		SpriteIndex = CurTile->SpriteIndex;

		StagePath& StagePathValue = APlayGameMode::StagePathValue;

		// 스테이지 경로
		switch (SpriteIndex)
		{
		case 0:
			StagePathValue.SetPath(0);
			break;
		case 1:
			StagePathValue.SetPath(1);
			break;
		case 2:
			StagePathValue.SetPath(2);
			break;
		case 3:
			StagePathValue.SetPath(3);
			break;
		case 4:
			StagePathValue.SetPath(4);
			break;
		case 5:
			StagePathValue.SetPath(5);
			break;
		case 6:
			StagePathValue.SetPath(6);
			break;
		case 7:
			StagePathValue.SetPath(7);
			break;
		default:
			break;
		}

		// 페이드 인/아웃 필요

		UEngineAPICore::GetCore()->ResetLevel<APlayGameMode, AActor>("Play");
		UEngineAPICore::GetCore()->OpenLevel("Play");
	}
}