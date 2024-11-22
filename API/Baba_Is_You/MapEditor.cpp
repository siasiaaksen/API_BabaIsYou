#include "PreCompile.h"
#include "MapEditor.h"
#include "TileMap.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>

AMapEditor::AMapEditor()
{
}

AMapEditor::~AMapEditor()
{
}

void AMapEditor::BeginPlay()
{
	Super::BeginPlay();

	Scale = { 33, 18 };
	CreateStageInit(Scale);
}

void AMapEditor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("BGTileSize : " + Scale.ToString());

	bool IsSizeChange = BGSize();

	if (nullptr == TileMap || IsSizeChange)
	{
		TileMapSetting();
	}

	MapMaker();
}

bool AMapEditor::BGSize()
{
	if (true == UEngineInput::GetInst().IsDown(VK_END))
	{
		Scale = Scale - FIntPoint(1, 0);

		if (Scale.X <= 1)
		{
			Scale.X = 1;
		}

		CreateStageInit(Scale, true);

		return true;
	}

	if (true == UEngineInput::GetInst().IsDown(VK_HOME))
	{
		Scale = Scale + FIntPoint(1, 0);

		if (Scale.X > 33)
		{
			Scale.X = 33;
		}

		CreateStageInit(Scale, true);

		return true;
	}

	if (true == UEngineInput::GetInst().IsDown(VK_NEXT))
	{
		Scale = Scale - FIntPoint(0, 1);

		if (Scale.Y <= 1)
		{
			Scale.Y = 1;
		}

		CreateStageInit(Scale, true);

		return true;
	}

	if (true == UEngineInput::GetInst().IsDown(VK_PRIOR))
	{
		Scale = Scale + FIntPoint(0, 1);

		if (Scale.Y > 18)
		{
			Scale.Y = 18;
		}

		CreateStageInit(Scale, true);
		
		return true;
	}

	return false;
}

void AMapEditor::TileMapSetting()
{
	if (nullptr != TileMap)
	{
		TileMap->Destroy();
	}

	TileMap = GetWorld()->SpawnActor<ATileMap>();
	TileMap->Create(Scale, { 36, 36 });
	TileMap->SetActorLocation(CenterPivot);
}

void AMapEditor::KeyBind()
{
	// Object
	MapTileEdit('Q', "BabaObject.png", 0, EFloorOrder::BABAOBJECT, ERenderOrder::UPPER, ELogicType::BABAOBJECT, EVLogicType::NONE, ELogicType::NONE);
	MapTileEdit('W', "FlagObject.png", 0, EFloorOrder::FLAGOBJECT, ERenderOrder::LOWER, ELogicType::FLAGOBJECT, EVLogicType::NONE, ELogicType::NONE);
	MapTileEdit('E', "RockObject.png", 0, EFloorOrder::ROCKOBJECT, ERenderOrder::LOWER, ELogicType::ROCKOBJECT, EVLogicType::NONE, ELogicType::NONE);
	MapTileEdit('R', "WallObject.png", 0, EFloorOrder::WALLOBJECT, ERenderOrder::LOWER, ELogicType::WALLOBJECT, EVLogicType::NONE, ELogicType::NONE);
	MapTileEdit('T', "GrassObject.png", 0, EFloorOrder::GRASSOBJECT, ERenderOrder::LOWER, ELogicType::GRASSOBJECT, EVLogicType::NONE, ELogicType::NONE);
	MapTileEdit('Y', "SkullObject.png", 0, EFloorOrder::SKULLOBJECT, ERenderOrder::LOWER, ELogicType::SKULLOBJECT, EVLogicType::NONE, ELogicType::NONE);
	MapTileEdit('U', "LavaObject.png", 0, EFloorOrder::LAVAOBJECT, ERenderOrder::LOWER, ELogicType::LAVAOBJECT, EVLogicType::NONE, ELogicType::NONE);
	MapTileEdit('I', "WaterObject.png", 0, EFloorOrder::WATEROBJECT, ERenderOrder::LOWER, ELogicType::WATEROBJECT, EVLogicType::NONE, ELogicType::NONE);

	// ObjectText
	MapTileEdit('O', "BabaText.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::BABA, EVLogicType::NONE, ELogicType::BABA);
	MapTileEdit('P', "FlagText.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::FLAG, EVLogicType::NONE, ELogicType::FLAG);
	MapTileEdit('A', "RockText.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::ROCK, EVLogicType::NONE, ELogicType::ROCK);
	MapTileEdit('S', "WallText.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::WALL, EVLogicType::NONE, ELogicType::WALL);
	MapTileEdit('D', "GrassText.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::GRASS, EVLogicType::NONE, ELogicType::GRASS);
	MapTileEdit('F', "SkullText.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::SKULL, EVLogicType::NONE, ELogicType::SKULL);
	MapTileEdit('G', "LavaText.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::LAVA, EVLogicType::NONE, ELogicType::LAVA);
	MapTileEdit('H', "WaterText.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::WATER, EVLogicType::NONE, ELogicType::WATER);

	// Text
	MapTileEdit('J', "Is.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
	MapTileEdit('K', "You.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::YOU);
	MapTileEdit('L', "Win.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::WIN);
	MapTileEdit('Z', "Push.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::PUSH);
	MapTileEdit('X', "Stop.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::STOP);
	MapTileEdit('C', "Defeat.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::DEFEAT);
	MapTileEdit('V', "Hot.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::HOT);
	MapTileEdit('B', "Melt.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::MELT);
	MapTileEdit('N', "Sink.png", 1, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::SINK);

	// BG
	MapTileEdit('1', "TileObject.png", 0, EFloorOrder::NONE, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
	MapTileEdit('2', "BrickObject.png", 0, EFloorOrder::NONE, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
	MapTileEdit('3', "FlowerObject.png", 0, EFloorOrder::NONE, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
}

void AMapEditor::MapMaker()
{
	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		KeyBind();
	}

	if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

		if (MousePos.iX() < TileMap->GetActorLocation().iX() ||
			MousePos.iY() < TileMap->GetActorLocation().iY())
		{
			return;
		}

		FIntPoint MouseIndex = TileMap->LocationToIndex(MousePos - TileMap->GetActorLocation());

		for (int i = 0; i < static_cast<int>(EFloorOrder::MAX); i++)
		{
			Tile* Tile = TileMap->GetTileRef(MouseIndex, i);

			if (nullptr == Tile)
			{
				continue;
			}

			if (nullptr != Tile->SpriteRenderer)
			{
				Tile->SpriteRenderer->Destroy();
				Tile->SpriteRenderer = nullptr;
				int a = 0;
			}
		}
	}
}