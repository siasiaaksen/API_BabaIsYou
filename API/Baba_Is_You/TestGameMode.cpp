#include "PreCompile.h"
#include "TestGameMode.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

#include "ContentsEnum.h"
#include "TileMap.h"


ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	FIntPoint Scale = { 33, 18 };

	CreateStageInit(Scale);

	{
		UpperTileMap = GetWorld()->SpawnActor<ATileMap>();
		UpperTileMap->Create(Scale, { 36, 36 });
		UpperTileMap->SetActorLocation(CenterPivot);

		UpperTileMap->SetTileIndex("BabaObject.png", { 11, 3 }, 0, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("BabaText.png", { 5, 3 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("Is.png", { 6, 3 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("You.png", { 7, 3 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("FlagText.png", { 12, 3 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("Win.png", { 18, 3 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("RockText.png", { 24, 3 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("Push.png", { 32, 3 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("WallText.png", { 6, 6 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("GrassText.png", { 12, 6 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("Stop.png", { 18, 6 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("SkullText.png", { 24, 6 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("Defeat.png", { 30, 6 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("LavaText.png", { 6, 9 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("Hot.png", { 12, 9 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("Melt.png", { 18, 9 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("WaterText.png", { 24, 9 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
		UpperTileMap->SetTileIndex("Sink.png",{ 30, 9 }, 1, static_cast<int>(ERenderOrder::UPPERTILE));
	}

	{
		LowerTileMap = GetWorld()->SpawnActor<ATileMap>();
		LowerTileMap->Create(Scale, { 36, 36 });
		LowerTileMap->SetActorLocation(CenterPivot);

		LowerTileMap->SetTileIndex("FlagObject.png", { 6, 14 }, 0, static_cast<int>(ERenderOrder::LOWERTILE));
		LowerTileMap->SetTileIndex("RockObject.png", { 10, 14 }, 0, static_cast<int>(ERenderOrder::LOWERTILE));
		LowerTileMap->SetTileIndex("WallObject.png", { 14, 14 }, 0, static_cast<int>(ERenderOrder::LOWERTILE));
		LowerTileMap->SetTileIndex("GrassObject.png", { 18, 14 }, 0, static_cast<int>(ERenderOrder::LOWERTILE));
		LowerTileMap->SetTileIndex("SkullObject.png", { 22, 14 }, 0, static_cast<int>(ERenderOrder::LOWERTILE));
		LowerTileMap->SetTileIndex("LavaObject.png", { 26, 14 }, 0, static_cast<int>(ERenderOrder::LOWERTILE));
		LowerTileMap->SetTileIndex("WaterObject.png", { 30, 14 }, 0, static_cast<int>(ERenderOrder::LOWERTILE));
	}
 }

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CurTileIndex = UpperTileMap->FindTileIndex("BabaObject.png");

	if (true == UEngineInput::GetInst().IsDown('W') || true == UEngineInput::GetInst().IsDown(VK_UP))
	{
		CurTileIndex = UpperTileMap->TileMove(CurTileIndex, FIntPoint::UP);
	}
	
	if (true == UEngineInput::GetInst().IsDown('A') || true == UEngineInput::GetInst().IsDown(VK_LEFT))
	{
		CurTileIndex = UpperTileMap->TileMove(CurTileIndex, FIntPoint::LEFT);
	}
	
	if (true == UEngineInput::GetInst().IsDown('S') || true == UEngineInput::GetInst().IsDown(VK_DOWN))
	{
		CurTileIndex = UpperTileMap->TileMove(CurTileIndex, FIntPoint::DOWN);
	}

	if (true == UEngineInput::GetInst().IsDown('D') || true == UEngineInput::GetInst().IsDown(VK_RIGHT))
	{
		CurTileIndex = UpperTileMap->TileMove(CurTileIndex, FIntPoint::RIGHT);
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

//void ATestGameMode::MakeTileMap(ATileMap* _TileName, int _Index/* = 2*/)
//{
//}
//
//void ATestGameMode::DestroyTileMap(ATileMap* _TileName)
//{
//	if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
//	{
//		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
//		Tile* Tile = _TileName->GetTileRef(MousePos);
//		if (nullptr != Tile->SpriteRenderer)
//		{
//			Tile->SpriteRenderer->Destroy();
//			Tile->SpriteRenderer = nullptr;
//		}
//	}
//}