#include "PreCompile.h"
#include "TestGameMode.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>

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

	Scale = { 33, 18 };

	CreateStageInit(Scale);

	{
		UpperTileMap = GetWorld()->SpawnActor<ATileMap>();
		UpperTileMap->Create(Scale, { 36, 36 });
		UpperTileMap->SetActorLocation(CenterPivot);

		UpperTileMap->SetTileIndex("BabaObject.png", { 3, 3 }, 0, ERenderOrder::UPPER);
		UpperTileMap->SetTileIndex("BabaText.png", { 0, 3 }, 1, ERenderOrder::UPPER, ELogicType::BABA, EVLogicType::NONE, ELogicType::BABA);
		UpperTileMap->SetTileIndex("Is.png", { 1, 3 }, 1, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
		UpperTileMap->SetTileIndex("You.png", { 2, 3 }, 1, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::YOU);
		UpperTileMap->SetTileIndex("FlagText.png", { 12, 3 }, 1, ERenderOrder::UPPER, ELogicType::FLAG, EVLogicType::NONE, ELogicType::FLAG);
		UpperTileMap->SetTileIndex("Win.png", { 18, 3 }, 1, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::WIN);
		UpperTileMap->SetTileIndex("RockText.png", { 24, 3 }, 1, ERenderOrder::UPPER, ELogicType::ROCK, EVLogicType::NONE, ELogicType::ROCK);
		UpperTileMap->SetTileIndex("Push.png", { 32, 3 }, 1, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::PUSH);
		UpperTileMap->SetTileIndex("WallText.png", { 6, 6 }, 1, ERenderOrder::UPPER, ELogicType::WALL, EVLogicType::NONE, ELogicType::WALL);
		UpperTileMap->SetTileIndex("GrassText.png", { 12, 6 }, 1, ERenderOrder::UPPER, ELogicType::GRASS, EVLogicType::NONE, ELogicType::GRASS);
		UpperTileMap->SetTileIndex("Stop.png", { 18, 6 }, 1, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::STOP);
		UpperTileMap->SetTileIndex("SkullText.png", { 24, 6 }, 1, ERenderOrder::UPPER, ELogicType::SKULL, EVLogicType::NONE, ELogicType::SKULL);
		UpperTileMap->SetTileIndex("Defeat.png", { 30, 6 }, 1, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::DEFEAT);
		UpperTileMap->SetTileIndex("LavaText.png", { 6, 9 }, 1, ERenderOrder::UPPER, ELogicType::LAVA, EVLogicType::NONE, ELogicType::LAVA);
		UpperTileMap->SetTileIndex("Hot.png", { 12, 9 }, 1, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::HOT);
		UpperTileMap->SetTileIndex("Melt.png", { 18, 9 }, 1, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::MELT);
		UpperTileMap->SetTileIndex("WaterText.png", { 24, 9 }, 1, ERenderOrder::UPPER, ELogicType::WATER, EVLogicType::NONE, ELogicType::WATER);
		UpperTileMap->SetTileIndex("Sink.png",{ 30, 9 }, 1, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::SINK);
	}

	{
		LowerTileMap = GetWorld()->SpawnActor<ATileMap>();
		LowerTileMap->Create(Scale, { 36, 36 });
		LowerTileMap->SetActorLocation(CenterPivot);

		LowerTileMap->SetTileIndex("FlagObject.png", { 6, 14 }, 0, ERenderOrder::LOWER);
		LowerTileMap->SetTileIndex("RockObject.png", { 10, 14 }, 0, ERenderOrder::LOWER);
		LowerTileMap->SetTileIndex("WallObject.png", { 14, 14 }, 0, ERenderOrder::LOWER);
		LowerTileMap->SetTileIndex("GrassObject.png", { 18, 14 }, 0, ERenderOrder::LOWER);
		LowerTileMap->SetTileIndex("SkullObject.png", { 22, 14 }, 0, ERenderOrder::LOWER);
		LowerTileMap->SetTileIndex("LavaObject.png", { 26, 14 }, 0, ERenderOrder::LOWER);
		LowerTileMap->SetTileIndex("WaterObject.png", { 30, 14 }, 0, ERenderOrder::LOWER);
	}
 }

void ATestGameMode::Move(std::string _CurSprite)
{
	if (true == UEngineInput::GetInst().IsDown('W') || true == UEngineInput::GetInst().IsDown(VK_UP))
	{
		UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 4);
		CurTileIndex = UpperTileMap->TileMove(LowerTileMap, CurTileIndex, FIntPoint::UP);
	}

	if (true == UEngineInput::GetInst().IsDown('A') || true == UEngineInput::GetInst().IsDown(VK_LEFT))
	{
		UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 8);
		CurTileIndex = UpperTileMap->TileMove(LowerTileMap, CurTileIndex, FIntPoint::LEFT);
	}

	if (true == UEngineInput::GetInst().IsDown('S') || true == UEngineInput::GetInst().IsDown(VK_DOWN))
	{
		UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 12);
		CurTileIndex = UpperTileMap->TileMove(LowerTileMap, CurTileIndex, FIntPoint::DOWN);
	}

	if (true == UEngineInput::GetInst().IsDown('D') || true == UEngineInput::GetInst().IsDown(VK_RIGHT))
	{
		UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 0);
		CurTileIndex = UpperTileMap->TileMove(LowerTileMap, CurTileIndex, FIntPoint::RIGHT);
	}
}

void ATestGameMode::TileCheck()
{
	for (int y = 0; y < Scale.Y; y++)
	{
		for (int x = 0; x < Scale.X; x++)
		{
			ELogicType FLogicType = UpperTileMap->GetTileRef(FIntPoint(x, y))->FLogicType;
			EVLogicType SLogicType = UpperTileMap->GetTileRef(FIntPoint(x, y))->SLogicType;
			ELogicType TLogicType = UpperTileMap->GetTileRef(FIntPoint(x, y))->TLogicType;

			switch (FLogicType)
			{
			case ELogicType::NONE:
				break;
			case ELogicType::BABA:
				break;
			case ELogicType::YOU:
				break;
			case ELogicType::FLAG:
				break;
			case ELogicType::WIN:
				break;
			case ELogicType::ROCK:
				break;
			case ELogicType::PUSH:
				break;
			case ELogicType::WALL:
				break;
			case ELogicType::GRASS:
				break;
			case ELogicType::STOP:
				break;
			case ELogicType::SKULL:
				break;
			case ELogicType::DEFEAT:
				break;
			case ELogicType::LAVA:
				break;
			case ELogicType::HOT:
				break;
			case ELogicType::MELT:
				break;
			case ELogicType::WATER:
				break;
			case ELogicType::SINK:
				break;
			default:
				break;
			}
		}
	}
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CurTileIndex = UpperTileMap->FindTileIndex("BabaObject.png");
	CurSprite = UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->GetCurSpriteName();

	Move(CurSprite);

	TileCheck();

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