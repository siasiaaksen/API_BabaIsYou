#pragma once
#include <EngineCore/Actor.h>


class ABackground : public AActor
{
public:
	ABackground();
	~ABackground();

	ABackground(const ABackground& _Other) = delete;
	ABackground(ABackground&& _Other) noexcept = delete;
	ABackground& operator=(const ABackground& _Other) = delete;
	ABackground& operator=(ABackground&& _Other) noexcept = delete;

protected:

private:

};

