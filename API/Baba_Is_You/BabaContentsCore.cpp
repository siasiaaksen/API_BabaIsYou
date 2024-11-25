#include "PreCompile.h"
#include "BabaContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>
#include <EnginePlatform/EngineSound.h>

#include "TitleGameMode.h"
#include "MapGameMode.h"
#include "PlayGameMode.h"
#include "TestGameMode.h"
#include "MapEditor.h"
#include "Player.h"


BabaContentsCore::BabaContentsCore()
{
}

BabaContentsCore::~BabaContentsCore()
{
}

void BabaContentsCore::BeginPlay()
{
	// 이미지 로드 및 컷팅
	{
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("BabaResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Image");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UImageManager::GetInst().Load(FilePath);
			UEngineDebug::OutPutString(FilePath);
		}

		// 스프라이트 컷팅/이름, 사이즈 넣어주기
		{
			UImageManager::GetInst().CuttingSprite("BabaObject.png", { 36, 36 });
			UImageManager::GetInst().CuttingSprite("FlagObject.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("RockObject.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("WallObject.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("GrassObject.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("SkullObject.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("LavaObject.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("WaterObject.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("TileObject.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("BrickObject.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("FlowerObject.png", { 36,36 });

			UImageManager::GetInst().CuttingSprite("BabaText.png", { 36, 36 });
			UImageManager::GetInst().CuttingSprite("Is.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("You.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("FlagText.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("Win.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("RockText.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("Push.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("WallText.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("GrassText.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("Stop.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("SkullText.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("Defeat.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("LavaText.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("Hot.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("Melt.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("WaterText.png", { 36,36 });
			UImageManager::GetInst().CuttingSprite("Sink.png", { 36,36 });

			UImageManager::GetInst().CuttingSprite("TitleLogo1800_247.png", { 600, 247 });
			UImageManager::GetInst().CuttingSprite("TileObject.png", { 36, 36 });
			UImageManager::GetInst().CuttingSprite("StartButton784_51.png", { 392, 51 });
			UImageManager::GetInst().CuttingSprite("SettingButton786_51.png", { 393, 51 });
			UImageManager::GetInst().CuttingSprite("ExitButton786_51.png", { 393, 51 });
			UImageManager::GetInst().CuttingSprite("WorldMap1188_648.png", { 1188, 648 });
			UImageManager::GetInst().CuttingSprite("SelectBox.png", { 54, 54 });
			UImageManager::GetInst().CuttingSprite("WorldMapNumberBack36.png", { 36, 36 });
			UImageManager::GetInst().CuttingSprite("Line.png", { 36, 36 });
			UImageManager::GetInst().CuttingSprite("LevelNum.png", { 36, 36 });
		}
	}

	// Fade 스프라이트 로드
	{
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("BabaResources//Image//Global"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Fade");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}

	// 사운드 로드
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("BabaResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Sound");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	// 이름, 사이즈 넣어주기
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("API_BabaIsYou");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AMapGameMode, AActor>("Map");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, AActor>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATestGameMode, AActor>("Test");
	UEngineAPICore::GetCore()->CreateLevel<AMapEditor, AActor>("Editor");
	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void BabaContentsCore::Tick()
{
}

