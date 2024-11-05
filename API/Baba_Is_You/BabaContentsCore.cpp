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
#include "TestGameMode.h"
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
		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
		UEngineDebug::OutPutString(FilePath);
	}

	// �̸�, ������ �־��ֱ�
	UImageManager::GetInst().CuttingSprite("Baba.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Flag.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Grass.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Lava.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Rock.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Skull.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Wall.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Water.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Defeat.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Hot.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Is.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Melt.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Push.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Sink.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Stop.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("Win.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("You.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("TitleLogo370.png", { 900, 370 });
	UImageManager::GetInst().CuttingSprite("Tile.png", { 54, 54 });
	UImageManager::GetInst().CuttingSprite("StartButton589_76.png", { 589, 76 });
	UImageManager::GetInst().CuttingSprite("SettingButton589_76.png", { 589, 76 });
	UImageManager::GetInst().CuttingSprite("ExitButton589_76.png", { 589, 76 });
	UImageManager::GetInst().CuttingSprite("WorldMap650.png", { 1190, 650 });

	// �̸�, ������ �־��ֱ�
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("API_BabaIsYou");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1920, 1080 });

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AMapGameMode, AActor>("Map");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATestGameMode, AActor>("Test");
	UEngineAPICore::GetCore()->OpenLevel("Test");
}

void BabaContentsCore::Tick()
{
}

