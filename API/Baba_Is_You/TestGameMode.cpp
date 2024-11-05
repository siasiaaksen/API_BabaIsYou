#include "PreCompile.h"
#include "TestGameMode.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

#include "Background.h"


ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	ABackground* BG = GetWorld()->SpawnActor<ABackground>();

	{
		BabaTile = GetWorld()->SpawnActor<USpriteRenderer>();

		FlagTile = GetWorld()->SpawnActor<USpriteRenderer>();

		WallTile = GetWorld()->SpawnActor<USpriteRenderer>();

		RockTile = GetWorld()->SpawnActor<USpriteRenderer>();

		WaterTile = GetWorld()->SpawnActor<USpriteRenderer>();

		SkullTile = GetWorld()->SpawnActor<USpriteRenderer>();

		LavaTile = GetWorld()->SpawnActor<USpriteRenderer>();

		GrassTile = GetWorld()->SpawnActor<USpriteRenderer>();
	}

	{
		IsTile = GetWorld()->SpawnActor<USpriteRenderer>();

		YouTile = GetWorld()->SpawnActor<USpriteRenderer>();

		WinTile = GetWorld()->SpawnActor<USpriteRenderer>();

		StopTile = GetWorld()->SpawnActor<USpriteRenderer>();

		PushTile = GetWorld()->SpawnActor<USpriteRenderer>();

		SinkTile = GetWorld()->SpawnActor<USpriteRenderer>();

		MeltTile = GetWorld()->SpawnActor<USpriteRenderer>();

		HotTile = GetWorld()->SpawnActor<USpriteRenderer>();
	}
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsPress('N'))
	{
		UEngineSerializer _Ser;
		BabaTile->Serialize(_Ser);

		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("BabaResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Data");

		std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
		UEngineFile NewFile = SaveFilePath;
		NewFile.FileOpen("wb");
		NewFile.Write(_Ser);
	}

	if (true == UEngineInput::GetInst().IsPress('M'))
	{
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("BabaResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Data");

		std::string SaveFilePath = Dir.GetPathToString() + "\\TestMapData.Data";
		UEngineFile NewFile = SaveFilePath;
		NewFile.FileOpen("rb");

		UEngineSerializer Ser;
		NewFile.Read(Ser);


		BabaTile->DeSerialize(Ser);
	}
}

void ATestGameMode::MakeTileMap(ATileMap* _TileName, int _Index/* = 2*/)
{
	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
		_TileName->SetTileLocation(MousePos, _Index);
	}
}

void ATestGameMode::DestroyTileMap(ATileMap* _TileName)
{
	if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
		Tile* Tile = _TileName->GetTileRef(MousePos);
		if (nullptr != Tile->SpriteRenderer)
		{
			Tile->SpriteRenderer->Destroy();
			Tile->SpriteRenderer = nullptr;
		}
	}
}