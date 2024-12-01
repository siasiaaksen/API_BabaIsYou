#include "PreCompile.h"
#include "MapGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include "Background.h"
#include "Map.h"
#include "StagePath.h"
#include "PlayGameMode.h"
#include "TitleGameMode.h"


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

	Fade = GetWorld()->SpawnActor<AFade>();
	Fade->FadeIn();

	BGMPlayer = UEngineSound::Play("map.ogg");

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

	VisibleStageName();

	MoveTitleLevel();

	if (IsAnimed)
	{
		MovePlayLevel();
	}

	if (IsTitleAnimed)
	{
		ChangeTitleLevel();
	}
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
			MoveSound();
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

		SelectSound = UEngineSound::Play("StageEnterSound.ogg");
		BGMPlayer.Off();
		Fade->FadeOut();
		IsAnimed = true;
	}
}

void AMapGameMode::VisibleStageName()
{
	int LastSpriteIndex = -1;
	USpriteRenderer* LastSpriteRenderer = nullptr;

	if (false == IsSelectable())
	{
		if (nullptr != LastSpriteRenderer)
		{
			if (true == LastSpriteRenderer->IsActive())
			{
				LastSpriteRenderer->SetActive(false);
				LastSpriteIndex = -1;
				LastSpriteRenderer = nullptr;
			}
		}
		else
		{
			SpriteRenderer->SetActive(false);
		}

		return;
	}

	FIntPoint CurIndex = TileMap->LocationToIndex(SelectBox->GetActorLocation() - FVector2D(36, 36));
	Tile* CurTile = TileMap->GetTileRef(CurIndex, 3);

	if (nullptr == CurTile)
	{
		if (true == LastSpriteRenderer->IsActive())
		{
			LastSpriteRenderer->SetActive(false);
			LastSpriteIndex = -1;
			LastSpriteRenderer = nullptr;
		}

		return;
	}

	SpriteIndex = CurTile->SpriteIndex;

	if (SpriteIndex == LastSpriteIndex)
	{
		return;
	}

	if (nullptr != LastSpriteRenderer)
	{
		if (true == LastSpriteRenderer->IsActive())
		{
			LastSpriteRenderer->SetActive(false);
			LastSpriteIndex = -1;
		}
	}

	if (nullptr == SpriteRenderer)
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::STAGENAME);
	}


	FVector2D LocationOffset = FVector2D::ZERO;

	switch (SpriteIndex)
	{
	case 0:
		SpriteRenderer->SetSprite("Title00.png");
		LocationOffset = FVector2D(36 + 80, 18);
		break;
	case 1:
		SpriteRenderer->SetSprite("Title01.png");
		LocationOffset = FVector2D(36 + 103, 18);
		break;
	case 2:
		SpriteRenderer->SetSprite("Title02.png");
		LocationOffset = FVector2D(36 + 126, 18);
		break;
	case 3:
		SpriteRenderer->SetSprite("Title03.png");
		LocationOffset = FVector2D(36 + 88, 18);
		break;
	case 4:
		SpriteRenderer->SetSprite("Title04.png");
		LocationOffset = FVector2D(36 + 133, 18);
		break;
	case 5:
		SpriteRenderer->SetSprite("Title05.png");
		LocationOffset = FVector2D(36 + 51, 18);
		break;
	case 6:
		SpriteRenderer->SetSprite("Title06.png");
		LocationOffset = FVector2D(36 + 72, 18);
		break;
	case 7:
		SpriteRenderer->SetSprite("Title07.png");
		LocationOffset = FVector2D(36 + 73, 18);
		break;
	default:
		SpriteRenderer->SetActive(false);
		LastSpriteIndex = -1;
		LastSpriteRenderer = nullptr;
		break;
	}

	SpriteRenderer->SetActive(true);
	FVector2D LogoScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(LocationOffset);

	LastSpriteIndex = SpriteIndex;
	LastSpriteRenderer = SpriteRenderer;
}

void AMapGameMode::MoveSound()
{
	MovePlayer = UEngineSound::Play("Move.ogg");
	MovePlayer.SetVolume(30.0f);
}

void AMapGameMode::MovePlayLevel()
{
	IsAnimEnd = Fade->GetSRenderer()->IsCurAnimationEnd();

	if (IsAnimEnd)
	{
		UEngineAPICore::GetCore()->ResetLevel<APlayGameMode, AActor>("Play");
		UEngineAPICore::GetCore()->OpenLevel("Play");

		IsAnimed = false;
	}
}

void AMapGameMode::MoveTitleLevel()
{
	if (true == UEngineInput::GetInst().IsDown('P'))
	{
		BGMPlayer.Off();
		Fade->FadeOut();
		IsTitleAnimed = true;
	}
}

void AMapGameMode::ChangeTitleLevel()
{
	IsAnimEnd = Fade->GetSRenderer()->IsCurAnimationEnd();

	if (IsAnimEnd)
	{
		UEngineAPICore::GetCore()->ResetLevel<ATitleGameMode, AActor>("Title");
		UEngineAPICore::GetCore()->OpenLevel("Title");

		IsTitleAnimed = false;
	}
}

