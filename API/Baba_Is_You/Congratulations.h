#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>


class ACongratulations : public AActor
{
public:
	ACongratulations();
	~ACongratulations();

	ACongratulations(const ACongratulations& _Other) = delete;
	ACongratulations(ACongratulations&& _Other) noexcept = delete;
	ACongratulations& operator=(const ACongratulations& _Other) = delete;
	ACongratulations& operator=(ACongratulations&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Winning();

	USpriteRenderer* GetSRenderer()
	{
		return SpriteRenderer;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
};

