#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <string>


class AButtons : public AActor
{
public:
	AButtons();
	~AButtons();

	AButtons(const AButtons& _Other) = delete;
	AButtons(AButtons&& _Other) noexcept = delete;
	AButtons& operator=(const AButtons& _Other) = delete;
	AButtons& operator=(AButtons&& _Other) noexcept = delete;

	void SetButtonPos(FVector2D _Pos)
	{
		ButtonPos = _Pos;
	}

	void SetButtonScale(FVector2D _Scale)
	{
		ButtonScale = _Scale;
	}

	void SetButton(std::string_view _SpriteName, FVector2D _Location);
	bool IsOverPos();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer;
	FVector2D ButtonPos;
	FVector2D ButtonScale;
};

