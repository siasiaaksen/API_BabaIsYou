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
	UEngineDebug::CoreOutPutString("CurTileIndex : " + MouseIndex.ToString());

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

void AMapEditor::MapTileEdit(std::string_view _Sprite, int _SpriteIndex, int _MaxCount, EFloorOrder _FloorOrder, 
	ERenderOrder _RenderOrder, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (MousePos.iX() < TileMap->GetActorLocation().iX() ||
		MousePos.iY() < TileMap->GetActorLocation().iY())
	{
		return;
	}

	MouseIndex = TileMap->LocationToIndex(MousePos - TileMap->GetActorLocation());

	TileMap->SetTile(_Sprite, MouseIndex, _SpriteIndex, static_cast<int>(_FloorOrder), _RenderOrder, _FLogicType, _SLogicType, _TLogicType);
}

void AMapEditor::MapMaker()
{
	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		for (int Key = 'A'; Key <= 'Z'; ++Key)
		{
			if (true == UEngineInput::GetInst().IsPress(Key))
			{
				switch (Key)
				{
				case 'Q':
					MapTileEdit("BabaObject.png", 0, 20, EFloorOrder::BABAOBJECT, ERenderOrder::UPPER, ELogicType::BABAOBJECT, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case 'W':
					MapTileEdit("FlagObject.png", 0, 1, EFloorOrder::FLAGOBJECT, ERenderOrder::LOWER, ELogicType::FLAGOBJECT, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case 'E':
					MapTileEdit("RockObject.png", 0, 1, EFloorOrder::ROCKOBJECT, ERenderOrder::LOWER, ELogicType::ROCKOBJECT, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case 'R':
					MapTileEdit("WallObject.png", 0, 16, EFloorOrder::WALLOBJECT, ERenderOrder::LOWER, ELogicType::WALLOBJECT, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case 'T':
					MapTileEdit("GrassObject.png", 0, 16, EFloorOrder::GRASSOBJECT, ERenderOrder::LOWER, ELogicType::GRASSOBJECT, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case 'Y':
					MapTileEdit("SkullObject.png", 0, 4, EFloorOrder::SKULLOBJECT, ERenderOrder::LOWER, ELogicType::SKULLOBJECT, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case 'U':
					MapTileEdit("LavaObject.png", 0, 16, EFloorOrder::LAVAOBJECT, ERenderOrder::LOWER, ELogicType::LAVAOBJECT, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case 'I':
					MapTileEdit("WaterObject.png", 0, 16, EFloorOrder::WATEROBJECT, ERenderOrder::LOWER, ELogicType::WATEROBJECT, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case 'O':
					MapTileEdit("BabaText.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::BABA, EVLogicType::NONE, ELogicType::BABA);
					return;
					break;
				case 'P':
					MapTileEdit("FlagText.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::FLAG, EVLogicType::NONE, ELogicType::FLAG);
					return;
					break;
				case 'A':
					MapTileEdit("RockText.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::ROCK, EVLogicType::NONE, ELogicType::ROCK);
					return;
					break;
				case 'S':
					MapTileEdit("WallText.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::WALL, EVLogicType::NONE, ELogicType::WALL);
					return;
					break;
				case 'D':
					MapTileEdit("GrassText.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::GRASS, EVLogicType::NONE, ELogicType::GRASS);
					return;
					break;
				case 'F':
					MapTileEdit("SkullText.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::SKULL, EVLogicType::NONE, ELogicType::SKULL);
					return;
					break;
				case 'G':
					MapTileEdit("LavaText.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::LAVA, EVLogicType::NONE, ELogicType::LAVA);
					return;
					break;
				case 'H':
					MapTileEdit("WaterText.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::WATER, EVLogicType::NONE, ELogicType::WATER);
					return;
					break;
				case 'J':
					MapTileEdit("Is.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
					return;
					break;
				case 'K':
					MapTileEdit("You.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::YOU);
					return;
					break;
				case 'L':
					MapTileEdit("Win.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::WIN);
					return;
					break;
				case 'Z':
					MapTileEdit("Push.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::PUSH);
					return;
					break;
				case 'X':
					MapTileEdit("Stop.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::STOP);
					return;
					break;
				case 'C':
					MapTileEdit("Defeat.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::DEFEAT);
					return;
					break;
				case 'V':
					MapTileEdit("Hot.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::HOT);
					return;
					break;
				case 'B':
					MapTileEdit("Melt.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::MELT);
					return;
					break;
				case 'N':
					MapTileEdit("Sink.png", 1, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::SINK);
					return;
					break;
				default:
					break;
				}
			}
		}

		for (int Key = '0'; Key <= '9'; ++Key)
		{
			if (true == UEngineInput::GetInst().IsPress(Key))
			{
				switch (Key)
				{
				case '1':
					MapTileEdit("TileObject.png", 0, 1, EFloorOrder::NONE, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case '2':
					MapTileEdit("BrickObject.png", 0, 16, EFloorOrder::NONE, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case '3':
					MapTileEdit("FlowerObject.png", 0, 1, EFloorOrder::NONE, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				default:
					break;
				}
			}
		}
	}

	if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

		if (MousePos.iX() < TileMap->GetActorLocation().iX() ||
			MousePos.iY() < TileMap->GetActorLocation().iY())
		{
			return;
		}

		MouseIndex = TileMap->LocationToIndex(MousePos - TileMap->GetActorLocation());

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
			}
		}
	}
}