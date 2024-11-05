#include "PreCompile.h"
#include "Buttons.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include "ContentsEnum.h"

AButtons::AButtons()
{
}

AButtons::~AButtons()
{
}

void AButtons::BeginPlay()
{
	Super::BeginPlay();
}

void AButtons::Tick(float _DeltaTime)
{
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FVector2D ButtonPos = _ButtonPos;
	FVector2D ButtonScale = _ButtonScale;
	FVector2D ButtonRangeMin = { ButtonPos.X - ButtonScale.Half().X, ButtonPos.Y - ButtonScale.Half().Y };
	FVector2D ButtonRangeMax = { ButtonPos.X + ButtonScale.Half().X, ButtonPos.Y + ButtonScale.Half().Y };

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		if (MousePos.X > ButtonRangeMin.X &&
			MousePos.Y > ButtonRangeMin.Y &&
			MousePos.X < ButtonRangeMax.X &&
			MousePos.Y < ButtonRangeMax.Y)
		{
			UEngineAPICore::GetCore()->OpenLevel("Map");
		}
	}
}
