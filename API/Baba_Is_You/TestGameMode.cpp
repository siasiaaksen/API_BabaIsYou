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

	CreateStageInit({ 18, 33 });

	{
		TextTileMap = GetWorld()->SpawnActor<ATileMap>();
		TextTileMap->Create({ 34, 19 }, { 36, 36 });
		TextTileMap->SetTileIndex("BabaText.png", { 6, 3 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("Is.png", { 7, 3 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("You.png", { 8, 3 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("FlagText.png", { 12, 3 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("Win.png", { 18, 3 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("RockText.png", { 24, 3 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("Push.png", { 30, 3 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("WallText.png", { 6, 6 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("GrassText.png", { 12, 6 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("Stop.png", { 18, 6 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("SkullText.png", { 24, 6 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("Defeat.png", { 30, 6 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("LavaText.png", { 6, 9 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("Hot.png", { 12, 9 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("Melt.png", { 18, 9 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("WaterText.png", { 24, 9 }, 1, static_cast<int>(ERenderOrder::TILE));
		TextTileMap->SetTileIndex("Sink.png",{ 30, 9 }, 1, static_cast<int>(ERenderOrder::TILE));
	}

	{
		ObjectTileMap = GetWorld()->SpawnActor<ATileMap>();
		ObjectTileMap->Create({ 34, 19 }, { 36, 36 });
		ObjectTileMap->SetTileIndex("BabaObject.png", { 3, 3 }, 0, static_cast<int>(ERenderOrder::PLAYER));
		ObjectTileMap->SetTileIndex("FlagObject.png", { 6, 14 }, 0, static_cast<int>(ERenderOrder::TILE));
		ObjectTileMap->SetTileIndex("RockObject.png", { 10, 14 }, 0, static_cast<int>(ERenderOrder::TILE));
		ObjectTileMap->SetTileIndex("WallObject.png", { 14, 14 }, 0, static_cast<int>(ERenderOrder::TILE));
		ObjectTileMap->SetTileIndex("GrassObject.png", { 18, 14 }, 0, static_cast<int>(ERenderOrder::TILE));
		ObjectTileMap->SetTileIndex("SkullObject.png", { 22, 14 }, 0, static_cast<int>(ERenderOrder::TILE));
		ObjectTileMap->SetTileIndex("LavaObject.png", { 26, 14 }, 0, static_cast<int>(ERenderOrder::TILE));
		ObjectTileMap->SetTileIndex("WaterObject.png", { 30, 14 }, 0, static_cast<int>(ERenderOrder::TILE));
	}

	BabaIndex = { 3, 3 };
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FIntPoint TileIndex = ObjectTileMap->FindTileIndex("WaterObject.png");

	if (true == UEngineInput::GetInst().IsDown('W'))
	{
		BabaIndex = ObjectTileMap->TileMove(TileIndex, { 0, -1 }) ;
	}
	
	if (true == UEngineInput::GetInst().IsDown('A'))
	{
		BabaIndex = ObjectTileMap->TileMove(TileIndex, { -1, 0 });
	}
	
	if (true == UEngineInput::GetInst().IsDown('S'))
	{
		BabaIndex = ObjectTileMap->TileMove(TileIndex, { 0, 1 });
	}

	if (true == UEngineInput::GetInst().IsDown('D'))
	{
		BabaIndex = ObjectTileMap->TileMove(TileIndex, { 1, 0 });
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