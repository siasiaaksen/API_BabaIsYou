#include "PreCompile.h"
#include "Buttons.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include "ContentsEnum.h"

AButtons::AButtons()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BUTTON);
		SpriteRenderer->SetSprite("StartButton589_76.png");

		FVector2D StartBtnScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation({ 960, 570 });
	}
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
	FVector2D ButtonPos = SpriteRenderer->GetComponentLocation();
	FVector2D ButtonScale = SpriteRenderer->GetComponentScale();
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
