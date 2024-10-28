#pragma once
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>


class BabaContentsCore : public UContentsCore
{
public:
	BabaContentsCore();
	~BabaContentsCore();

	BabaContentsCore(const BabaContentsCore& _Other) = delete;
	BabaContentsCore(BabaContentsCore&& _Other) noexcept = delete;
	BabaContentsCore& operator=(const BabaContentsCore& _Other) = delete;
	BabaContentsCore& operator=(BabaContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:
	ULevel* TitleLevel;
};

