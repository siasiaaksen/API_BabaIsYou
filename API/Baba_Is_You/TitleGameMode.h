#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include "Buttons.h"
#include "Fade.h"


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
	void MoveMapLevel();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int CurBtnIndex = 0;
	std::vector<AButtons*> Btns;
	std::vector<USpriteRenderer*> Babas;
	USoundPlayer BGMPlayer;
	USoundPlayer OptionSound;
	USoundPlayer SelectSound;
	AFade* Fade = nullptr;
	bool IsAnimEnd = false;
	bool IsAnimed = false;
};

