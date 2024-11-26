#pragma once
#include <EngineCore/Actor.h>


class ASelectBox : public AActor
{
public:
	ASelectBox();
	~ASelectBox();

	ASelectBox(const ASelectBox& _Other) = delete;
	ASelectBox(ASelectBox&& _Other) noexcept = delete;
	ASelectBox& operator=(const ASelectBox& _Other) = delete;
	ASelectBox& operator=(ASelectBox&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
};

