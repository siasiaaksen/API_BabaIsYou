#pragma once
#include <EngineCore/GameMode.h>
#include "Buttons.h"


class ATitleGameMode : public AGameMode
{
public:
	ATitleGameMode();
	~ATitleGameMode();

	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

	void BtnSelect();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int CurBtnIndex;
	std::vector<AButtons*> Btns;
	std::vector<USpriteRenderer*> Babas;
};

