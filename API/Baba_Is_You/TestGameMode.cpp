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
		BabaTileMap = GetWorld()->SpawnActor<ATileMap>();
		BabaTileMap->Create("Baba.png", { 33, 18 }, { 54, 54 });
		BabaTileMap->SetTileIndex({ 2, 2 }, 2);
	}

	{
		BabaTextTileMap = GetWorld()->SpawnActor<ATileMap>();
		BabaTextTileMap->Create("Baba.png", { 33, 18 }, { 54, 54 });
		BabaTextTileMap->SetTileIndex({ 4, 2 }, 1);
	}

	{
		IsTileMap = GetWorld()->SpawnActor<ATileMap>();
		IsTileMap->Create("Is.png", { 33, 18 }, { 54, 54 });
		IsTileMap->SetTileIndex({ 6, 2 }, 1);
	}

	{
		YouTileMap = GetWorld()->SpawnActor<ATileMap>();
		YouTileMap->Create("You.png", { 33, 18 }, { 54, 54 });
		YouTileMap->SetTileIndex({ 8, 2 }, 1);
	}

	{
		FlagTileMap = GetWorld()->SpawnActor<ATileMap>();
		FlagTileMap->Create("Flag.png", { 33, 18 }, { 54, 54 });
		FlagTileMap->SetTileIndex({ 10, 2 }, 2);
	}

	{
		FlagTextTileMap = GetWorld()->SpawnActor<ATileMap>();
		FlagTextTileMap->Create("Flag.png", { 33, 18 }, { 54, 54 });
		FlagTextTileMap->SetTileIndex({ 12, 2 }, 1);
	}

	{
		WinTileMap = GetWorld()->SpawnActor<ATileMap>();
		WinTileMap->Create("Win.png", { 33, 18 }, { 54, 54 });
		WinTileMap->SetTileIndex({ 14, 2 }, 1);
	}

	{
		WallTileMap = GetWorld()->SpawnActor<ATileMap>();
		WallTileMap->Create("Wall.png", { 33, 18 }, { 54, 54 });
		WallTileMap->SetTileIndex({ 16, 2 }, 2);
	}

	{
		WallTextTileMap = GetWorld()->SpawnActor<ATileMap>();
		WallTextTileMap->Create("Wall.png", { 33, 18 }, { 54, 54 });
		WallTextTileMap->SetTileIndex({ 18, 2 }, 1);
	}

	{
		RockTileMap = GetWorld()->SpawnActor<ATileMap>();
		RockTileMap->Create("Rock.png", { 33, 18 }, { 54, 54 });
		RockTileMap->SetTileIndex({ 20, 2 }, 2);
	}

	{
		RockTextTileMap = GetWorld()->SpawnActor<ATileMap>();
		RockTextTileMap->Create("Rock.png", { 33, 18 }, { 54, 54 });
		RockTextTileMap->SetTileIndex({ 22, 2 }, 1);
	}

	{
		GrassTileMap = GetWorld()->SpawnActor<ATileMap>();
		GrassTileMap->Create("Grass.png", { 33, 18 }, { 54, 54 });
		GrassTileMap->SetTileIndex({ 24, 2 }, 2);
	}

	{
		GrassTextTileMap = GetWorld()->SpawnActor<ATileMap>();
		GrassTextTileMap->Create("Grass.png", { 33, 18 }, { 54, 54 });
		GrassTextTileMap->SetTileIndex({ 26, 2 }, 1);
	}

	{
		StopTileMap = GetWorld()->SpawnActor<ATileMap>();
		StopTileMap->Create("Stop.png", { 33, 18 }, { 54, 54 });
		StopTileMap->SetTileIndex({ 2, 6 }, 1);
	}

	{
		PushTileMap = GetWorld()->SpawnActor<ATileMap>();
		PushTileMap->Create("Push.png", { 33, 18 }, { 54, 54 });
		PushTileMap->SetTileIndex({ 4, 6 }, 1);
	}

	{
		WaterTileMap = GetWorld()->SpawnActor<ATileMap>();
		WaterTileMap->Create("Water.png", { 33, 18 }, { 54, 54 });
		WaterTileMap->SetTileIndex({ 6, 6 }, 2);
	}

	{
		WaterTextTileMap = GetWorld()->SpawnActor<ATileMap>();
		WaterTextTileMap->Create("Water.png", { 33, 18 }, { 54, 54 });
		WaterTextTileMap->SetTileIndex({ 8, 6 }, 1);
	}

	{
		SinkTileMap = GetWorld()->SpawnActor<ATileMap>();
		SinkTileMap->Create("Sink.png", { 33, 18 }, { 54, 54 });
		SinkTileMap->SetTileIndex({ 10, 6 }, 1);
	}

	{
		SkullTileMap = GetWorld()->SpawnActor<ATileMap>();
		SkullTileMap->Create("Skull.png", { 33, 18 }, { 54, 54 });
		SkullTileMap->SetTileIndex({ 12, 6 }, 2);
	}

	{
		SkullTextTileMap = GetWorld()->SpawnActor<ATileMap>();
		SkullTextTileMap->Create("Skull.png", { 33, 18 }, { 54, 54 });
		SkullTextTileMap->SetTileIndex({ 14, 6 }, 1);
	}

	{
		DefeatTileMap = GetWorld()->SpawnActor<ATileMap>();
		DefeatTileMap->Create("Defeat.png", { 33, 18 }, { 54, 54 });
		DefeatTileMap->SetTileIndex({ 16, 6 }, 1);
	}

	{
		LavaTileMap = GetWorld()->SpawnActor<ATileMap>();
		LavaTileMap->Create("Lava.png", { 33, 18 }, { 54, 54 });
		LavaTileMap->SetTileIndex({ 18, 6 }, 2);
	}

	{
		LavaTextTileMap = GetWorld()->SpawnActor<ATileMap>();
		LavaTextTileMap->Create("Lava.png", { 33, 18 }, { 54, 54 });
		LavaTextTileMap->SetTileIndex({ 20, 6 }, 1);
	}

	{
		MeltTileMap = GetWorld()->SpawnActor<ATileMap>();
		MeltTileMap->Create("Melt.png", { 33, 18 }, { 54, 54 });
		MeltTileMap->SetTileIndex({ 22, 6 }, 1);
	}

	{
		HotTileMap = GetWorld()->SpawnActor<ATileMap>();
		HotTileMap->Create("Hot.png", { 33, 18 }, { 54, 54 });
		HotTileMap->SetTileIndex({ 24, 6 }, 1);
	}
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('W'))
	{
		BabaTileMap->AddActorLocation(FVector2D::UP * 54);
	}
	
	if (true == UEngineInput::GetInst().IsDown('A'))
	{
		BabaTileMap->AddActorLocation(FVector2D::LEFT * 54);
	}
	
	if (true == UEngineInput::GetInst().IsDown('S'))
	{
		BabaTileMap->AddActorLocation(FVector2D::DOWN * 54);
	}

	if (true == UEngineInput::GetInst().IsDown('D'))
	{
		BabaTileMap->AddActorLocation(FVector2D::RIGHT * 54);
	}

	//if (true == UEngineInput::GetInst().IsPress('N'))
	//{
	//	UEngineSerializer _Ser;
	//	BabaTile->Serialize(_Ser);

	//	UEngineDirectory Dir;

	//	if (false == Dir.MoveParentToDirectory("BabaResources"))
	//	{
	//		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
	//		return;
	//	}

	//	Dir.Append("Data");

	//	std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
	//	UEngineFile NewFile = SaveFilePath;
	//	NewFile.FileOpen("wb");
	//	NewFile.Write(_Ser);
	//}

	//if (true == UEngineInput::GetInst().IsPress('M'))
	//{
	//	UEngineDirectory Dir;

	//	if (false == Dir.MoveParentToDirectory("BabaResources"))
	//	{
	//		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
	//		return;
	//	}

	//	Dir.Append("Data");

	//	std::string SaveFilePath = Dir.GetPathToString() + "\\TestMapData.Data";
	//	UEngineFile NewFile = SaveFilePath;
	//	NewFile.FileOpen("rb");

	//	UEngineSerializer Ser;
	//	NewFile.Read(Ser);


	//	BabaTile->DeSerialize(Ser);
	//}
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