#include "PreCompile.h"
#include "MapEditor.h"

#include <EngineCore/Level.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EnginePath.h>

#include "TitleGameMode.h"
#include "TileMap.h"


AMapEditor::AMapEditor()
{
}

AMapEditor::~AMapEditor()
{
}

void AMapEditor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	Scale = { 33, 18 };
	CreateStageInit(Scale);
}

void AMapEditor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("BGTileSize : " + Scale.ToString());
	UEngineDebug::CoreOutPutString("CurTileIndex : " + MouseIndex.ToString());
	UEngineDebug::CoreOutPutString("ClickNum : " + std::to_string(ClickNum - 1));
	UEngineDebug::CoreOutPutString("CurTile : " + std::string(SpriteName));

	bool IsSizeChange = BGSize();

	if (nullptr == TileMap || IsSizeChange)
	{
		TileMapSetting();
	}

	MapMaker();
	CurTileSprite();
	MapReset();

	MapSave();
	MapLoad();

	if (true == UEngineInput::GetInst().IsDown('P'))
	{
		UEngineAPICore::GetCore()->ResetLevel<ATitleGameMode, AActor>("Title");
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}
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
	TileMap->Create(Scale, {36, 36});
	TileMap->SetActorLocation(CenterPivot);
}

void AMapEditor::MapTileEdit(std::string_view _Sprite, int _SpriteIndex, int _MaxCount, EFloorOrder _FloorOrder, 
	ERenderOrder _RenderOrder, ELogicType _FLogicType, EVLogicType _SLogicType, ELogicType _TLogicType, FVector2D _SpriteScale)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	if (MousePos.iX() < TileMap->GetActorLocation().iX() ||
		MousePos.iY() < TileMap->GetActorLocation().iY())
	{
		return;
	}

	MouseIndex = TileMap->LocationToIndex(MousePos - TileMap->GetActorLocation());

	TileMap->SetTile(_Sprite, MouseIndex, { 0, 0 }, _SpriteScale, _SpriteIndex, static_cast<int>(_FloorOrder), _RenderOrder, _FLogicType, _SLogicType, _TLogicType);
}

void AMapEditor::MapMaker()
{
	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
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
					MapTileEdit("SkullObject.png", 3, 4, EFloorOrder::SKULLOBJECT, ERenderOrder::LOWER, ELogicType::SKULLOBJECT, EVLogicType::NONE, ELogicType::NONE);
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
					MapTileEdit("BabaText.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::BABA, EVLogicType::NONE, ELogicType::BABA);
					return;
					break;
				case 'P':
					MapTileEdit("FlagText.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::FLAG, EVLogicType::NONE, ELogicType::FLAG);
					return;
					break;
				case 'A':
					MapTileEdit("RockText.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::ROCK, EVLogicType::NONE, ELogicType::ROCK);
					return;
					break;
				case 'S':
					MapTileEdit("WallText.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::WALL, EVLogicType::NONE, ELogicType::WALL);
					return;
					break;
				case 'D':
					MapTileEdit("GrassText.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::GRASS, EVLogicType::NONE, ELogicType::GRASS);
					return;
					break;
				case 'F':
					MapTileEdit("SkullText.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::SKULL, EVLogicType::NONE, ELogicType::SKULL);
					return;
					break;
				case 'G':
					MapTileEdit("LavaText.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::LAVA, EVLogicType::NONE, ELogicType::LAVA);
					return;
					break;
				case 'H':
					MapTileEdit("WaterText.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::WATER, EVLogicType::NONE, ELogicType::WATER);
					return;
					break;
				case 'J':
					MapTileEdit("Is.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::IS, ELogicType::NONE);
					return;
					break;
				case 'K':
					MapTileEdit("You.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::YOU);
					return;
					break;
				case 'L':
					MapTileEdit("Win.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::WIN);
					return;
					break;
				case 'Z':
					MapTileEdit("Push.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::PUSH);
					return;
					break;
				case 'X':
					MapTileEdit("Stop.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::STOP);
					return;
					break;
				case 'C':
					MapTileEdit("Defeat.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::DEFEAT);
					return;
					break;
				case 'V':
					MapTileEdit("Hot.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::HOT);
					return;
					break;
				case 'B':
					MapTileEdit("Melt.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::MELT);
					return;
					break;
				case 'N':
					MapTileEdit("Sink.png", 0, 2, EFloorOrder::TEXT, ERenderOrder::UPPER, ELogicType::NONE, EVLogicType::NONE, ELogicType::SINK);
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
					MapTileEdit("TileObject.png", 0, 1, EFloorOrder::BG, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case '2':
					MapTileEdit("BrickObject.png", 0, 16, EFloorOrder::BG, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case '3':
					MapTileEdit("FlowerObject.png", 0, 1, EFloorOrder::BG, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE);
					return;
					break;
				case '4':
					MapTileEdit("MoveButton116_116.png", 0, 1, EFloorOrder::BG, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE, {116, 116});
					return;
					break;
				case '5':
					MapTileEdit("PauseButton116_77.png", 0, 1, EFloorOrder::BG, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE, {116, 77});
					return;
					break;
				case '6':
					MapTileEdit("UndoButton116_77.png", 0, 1, EFloorOrder::BG, ERenderOrder::BGOBJECT, ELogicType::NONE, EVLogicType::NONE, ELogicType::NONE, {116, 77});
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

		TileMap->RemoveTile(MouseIndex);
	}
}

void AMapEditor::CurTileSprite()
{
	for (int Key = 'A'; Key <= 'Z'; ++Key)
	{
		if (true == UEngineInput::GetInst().IsPress(Key))
		{
			switch (Key)
			{
			case 'Q':
				SpriteName = "BabaObject.png";
				return;
				break;
			case 'W':
				SpriteName = "FlagObject.png";
				return;
				break;
			case 'E':
				SpriteName = "RockObject.png";
				return;
				break;
			case 'R':
				SpriteName = "WallObject.png";
				return;
				break;
			case 'T':
				SpriteName = "GrassObject.png";
				return;
				break;
			case 'Y':
				SpriteName = "SkullObject.png";
				return;
				break;
			case 'U':
				SpriteName = "LavaObject.png";
				return;
				break;
			case 'I':
				SpriteName = "WaterObject.png";
				return;
				break;
			case 'O':
				SpriteName = "BabaText.png";
				return;
				break;
			case 'P':
				SpriteName = "FlagText.png";
				return;
				break;
			case 'A':
				SpriteName = "RockText.png";
				return;
				break;
			case 'S':
				SpriteName = "WallText.png";
				return;
				break;
			case 'D':
				SpriteName = "GrassText.png";
				return;
				break;
			case 'F':
				SpriteName = "SkullText.png";
				return;
				break;
			case 'G':
				SpriteName = "LavaText.png";
				return;
				break;
			case 'H':
				SpriteName = "WaterText.png";
				return;
				break;
			case 'J':
				SpriteName = "Is.png";
				return;
				break;
			case 'K':
				SpriteName = "You.png";
				return;
				break;
			case 'L':
				SpriteName = "Win.png";
				return;
				break;
			case 'Z':
				SpriteName = "Push.png";
				return;
				break;
			case 'X':
				SpriteName = "Stop.png";
				return;
				break;
			case 'C':
				SpriteName = "Defeat.png";
				return;
				break;
			case 'V':
				SpriteName = "Hot.png";
				return;
				break;
			case 'B':
				SpriteName = "Melt.png";
				return;
				break;
			case 'N':
				SpriteName = "Sink.png";
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
				SpriteName = "TileObject.png";
				return;
				break;
			case '2':
				SpriteName = "BrickObject.png";
				return;
				break;
			case '3':
				SpriteName = "FlowerObject.png";
				return;
				break;
			default:
				break;
			}
		}
	}
}

void AMapEditor::MapReset()
{
	if (true == UEngineInput::GetInst().IsDown(VK_F3))
	{
		TileMap->RemoveAllTile();
	}
}

void AMapEditor::MapSave()
{
	if (true == UEngineInput::GetInst().IsDown(VK_F1))
	{
		OPENFILENAME OFN;
		char filePathName[100] = "";
		char lpstrFile[100] = "";

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OFN);
		OFN.hwndOwner = nullptr;
		OFN.lpstrFile = lpstrFile;
		OFN.lpstrFile[0] = '\0';
		OFN.nMaxFile = sizeof(lpstrFile);
		OFN.lpstrFilter = "Map Data (*.MData)\0*.MData\0";
		OFN.nFilterIndex = 1;
		OFN.lpstrFileTitle = NULL;
		OFN.nMaxFileTitle = 0;
		OFN.lpstrInitialDir = ".\\..\\BabaResources\\Data";

		if (GetSaveFileNameA(&OFN) != 0)
		{
			char* ptr = OFN.lpstrFile;
			TileMap->TileMapSave(ptr);
		}
	}
}

void AMapEditor::MapLoad()
{
	if (true == UEngineInput::GetInst().IsDown(VK_F2))
	{
		OPENFILENAME OFN;
		char filePathName[100] = "";
		char lpstrFile[100] = "";
		static char filter[] = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = nullptr;
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrInitialDir = ".\\..\\BabaResources\\Data";

		if (GetOpenFileNameA(&OFN) != 0) 
		{
			char* ptr = OFN.lpstrFile;
			TileMap->TileMapLoad(ptr);
			CreateStageInit(TileMap->GetTileCount(), true);
		}
	}
}