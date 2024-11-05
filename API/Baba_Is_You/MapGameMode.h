#pragma once
#include <EngineCore/GameMode.h>

class AMapGameMode : public AGameMode
{
public:
	AMapGameMode();
	~AMapGameMode();

	AMapGameMode(const AMapGameMode& _Other) = delete;
	AMapGameMode(AMapGameMode&& _Other) noexcept = delete;
	AMapGameMode& operator=(const AMapGameMode& _Other) = delete;
	AMapGameMode& operator=(AMapGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:

};

