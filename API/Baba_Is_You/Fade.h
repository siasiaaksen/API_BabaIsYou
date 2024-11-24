#pragma once
#include <EngineCore/Actor.h>


class AFade : public AActor
{
public:
	AFade();
	~AFade();

	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void FadeIn();
	void FadeOut();

	USpriteRenderer* GetSRenderer()
	{
		return SpriteRenderer;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
};

