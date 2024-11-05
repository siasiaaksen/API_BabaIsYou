#include "PreCompile.h"
#include "BabaContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "MapGameMode.h"
#include "PlayGameMode.h"
#include "Player.h"

BabaContentsCore::BabaContentsCore()
{
}

BabaContentsCore::~BabaContentsCore()
{
}

void BabaContentsCore::BeginPlay()
{
	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("BabaResources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
		UEngineDebug::OutPutString(FilePath);
	}

	// 이름, 사이즈 넣어주기
	UImageManager::GetInst().CuttingSprite("Baba.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("TitleLogo370.png", { 900, 370 });
	UImageManager::GetInst().CuttingSprite("Tile.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("StartButton589_76.png", { 589, 76 });
	UImageManager::GetInst().CuttingSprite("ExitButton589_76.png", { 589, 76 });
	UImageManager::GetInst().CuttingSprite("WorldMap650.png", { 1190, 650 });

	// 이름, 사이즈 넣어주기
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("API_BabaIsYou");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1920, 1080 });

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AMapGameMode, AActor>("Map");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void BabaContentsCore::Tick()
{
}

