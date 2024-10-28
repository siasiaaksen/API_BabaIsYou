#include "PreCompile.h"
#include "BabaContentsCore.h"
#include <EngineCore/EngineAPICore.h>

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
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("API_BabaIsYou");

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void BabaContentsCore::Tick()
{
}

