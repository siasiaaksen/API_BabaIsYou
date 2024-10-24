#pragma once
#include <EngineCore/EngineAPICore.h>


class ContentsCore : public UContentsCore
{
public:
	ContentsCore();
	~ContentsCore();

	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:
	ULevel* TitleLevel;
};

