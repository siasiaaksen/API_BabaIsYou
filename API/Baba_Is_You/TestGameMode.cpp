#include "PreCompile.h"
#include "TestGameMode.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineString.h>

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

		UpperTileMap->SetTileIndex("BabaObject.png", { 3, 3 }, 0, ERenderOrder::UPPER, ELogicType::BABAOBJECT, EVLogicType::NONE, ELogicType::NONE);
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

		LowerTileMap->SetTileIndex("FlagObject.png", { 6, 14 }, 0, ERenderOrder::LOWER, ELogicType::FLAGOBJECT, EVLogicType::NONE, ELogicType::NONE);
		LowerTileMap->SetTileIndex("RockObject.png", { 10, 14 }, 0, ERenderOrder::LOWER, ELogicType::ROCKOBJECT, EVLogicType::NONE, ELogicType::NONE);
		LowerTileMap->SetTileIndex("WallObject.png", { 14, 14 }, 0, ERenderOrder::LOWER, ELogicType::WALLOBJECT, EVLogicType::NONE, ELogicType::NONE);
		LowerTileMap->SetTileIndex("GrassObject.png", { 18, 14 }, 0, ERenderOrder::LOWER, ELogicType::GRASSOBJECT, EVLogicType::NONE, ELogicType::NONE);
		LowerTileMap->SetTileIndex("SkullObject.png", { 22, 14 }, 0, ERenderOrder::LOWER, ELogicType::SKULLOBJECT, EVLogicType::NONE, ELogicType::NONE);
		LowerTileMap->SetTileIndex("LavaObject.png", { 26, 14 }, 0, ERenderOrder::LOWER, ELogicType::LAVAOBJECT, EVLogicType::NONE, ELogicType::NONE);
		LowerTileMap->SetTileIndex("WaterObject.png", { 30, 14 }, 0, ERenderOrder::LOWER, ELogicType::WATEROBJECT, EVLogicType::NONE, ELogicType::NONE);
	}

	{
		StartLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
				this->MoveTiles.push_back(ELogicType::BABAOBJECT);
			};

		StartLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
				this->MoveTiles.push_back(ELogicType::FLAGOBJECT);
			};

		StartLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
				this->MoveTiles.push_back(ELogicType::ROCKOBJECT);
			};

		StartLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
				this->MoveTiles.push_back(ELogicType::WALLOBJECT);
			};

		StartLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
				this->MoveTiles.push_back(ELogicType::GRASSOBJECT);
			};

		StartLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
				this->MoveTiles.push_back(ELogicType::SKULLOBJECT);
			};

		StartLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
				this->MoveTiles.push_back(ELogicType::LAVAOBJECT);
			};

		StartLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
				this->MoveTiles.push_back(ELogicType::WATEROBJECT);
			};
	}

	{
		UpdateLogic[static_cast<int>(ELogicType::BABA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
			};

		UpdateLogic[static_cast<int>(ELogicType::FLAG)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
			};

		UpdateLogic[static_cast<int>(ELogicType::ROCK)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
			};

		UpdateLogic[static_cast<int>(ELogicType::WALL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
			};

		UpdateLogic[static_cast<int>(ELogicType::GRASS)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
			};

		UpdateLogic[static_cast<int>(ELogicType::SKULL)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
			};

		UpdateLogic[static_cast<int>(ELogicType::LAVA)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
			};

		UpdateLogic[static_cast<int>(ELogicType::WATER)][static_cast<int>(EVLogicType::IS)][static_cast<int>(ELogicType::YOU)]
			= [this]()
			{
			};
	}

	TileCheck();
 }

void ATestGameMode::Move(std::vector<ELogicType> _MoveTiles)
{
	if (!_MoveTiles.size())
	{
		return;
	}

	for (int i = 0; i < _MoveTiles.size(); i++)
	{
		_MoveTiles[i];
	}

	if (true == UEngineInput::GetInst().IsDown('W') || true == UEngineInput::GetInst().IsDown(VK_UP))
	{
		//UpperTileMap->GetTileRef(CurIndex)->SpriteRenderer->SetSprite(CurSprite, 4);
		//CurIndex = UpperTileMap->TileMove(CurIndex, FIntPoint::UP);
	}

	if (true == UEngineInput::GetInst().IsDown('A') || true == UEngineInput::GetInst().IsDown(VK_LEFT))
	{
		//UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 8);
		//CurIndex = UpperTileMap->TileMove(CurIndex, FIntPoint::LEFT);
	}

	if (true == UEngineInput::GetInst().IsDown('S') || true == UEngineInput::GetInst().IsDown(VK_DOWN))
	{
		//UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 12);
		//CurIndex = UpperTileMap->TileMove(CurIndex, FIntPoint::DOWN);
	}

	if (true == UEngineInput::GetInst().IsDown('D') || true == UEngineInput::GetInst().IsDown(VK_RIGHT))
	{
		//UpperTileMap->GetTileRef(CurTileIndex)->SpriteRenderer->SetSprite(_CurSprite, 0);
		//CurIndex = UpperTileMap->TileMove(CurIndex, FIntPoint::RIGHT);
	}
}

void ATestGameMode::TileCheck()
{
	for (int x = 0; x < Scale.X; x++)
	{
		for (int y = 0; y < Scale.Y; y++)
		{
			FIntPoint CurIndex = { x, y };
			Tile* CurTile = UpperTileMap->GetTileRef(CurIndex);
			F = CurTile->FLogicType;
			if (F != ELogicType::NONE)
			{
				NextTileCheck(CurIndex, FIntPoint{ 1, 0 });
				NextTileCheck(CurIndex, FIntPoint{ 0, 1 });
			}
		}
	}
}

void ATestGameMode::NextTileCheck(FIntPoint _Index, FIntPoint _Dir)
{
	Tile* CurTile = UpperTileMap->GetTileRef(_Index + _Dir);
	S = CurTile->SLogicType;
	if (S != EVLogicType::NONE)
	{
		LastTileCheck(_Index + _Dir + _Dir);
	}

	return;
}

void ATestGameMode::LastTileCheck(FIntPoint _Index)
{
	Tile* CurTile = UpperTileMap->GetTileRef(_Index);
	T = CurTile->TLogicType;
	if (T != ELogicType::NONE)
	{
		//F; S; T;
		StartLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)]();

		TileCombine.push_back(UpdateLogic[static_cast<int>(F)][static_cast<int>(S)][static_cast<int>(T)]);
	}

	return;
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 만약 규칙이 깨진 타일이 생길 경우
	// 따로 제거하지 않고
	// 매 프레임마다 clear되고
	MoveTiles.clear();
	TileCombine.clear();

	// 다시 모든 TileCheck
	TileCheck();

	std::list<std::function<void()>>::iterator StartIter = TileCombine.begin();
	std::list<std::function<void()>>::iterator EndIter = TileCombine.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter;
	}
}
