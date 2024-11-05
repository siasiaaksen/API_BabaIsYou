#pragma once
#include <EngineCore/Actor.h>


class AMap : public AActor
{
public:
	AMap();
	~AMap();

	AMap(const AMap& _Other) = delete;
	AMap(AMap&& _Other) noexcept = delete;
	AMap& operator=(const AMap& _Other) = delete;
	AMap& operator=(AMap&& _Other) noexcept = delete;

protected:

private:

};

