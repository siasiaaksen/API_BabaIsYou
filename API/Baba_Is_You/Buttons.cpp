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
	Super::Tick(_DeltaTime);
}

void AButtons::SetButton(std::string_view _SpriteName, FVector2D _Location)
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BUTTON);
	SpriteRenderer->SetSprite(_SpriteName);

	FVector2D StartBtnScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(_Location);

	SetButtonPos(_Location);
	SetButtonScale(StartBtnScale);
}

bool AButtons::IsOverPos()
{
	//FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	//FVector2D ButtonRangeMin = { ButtonPos.X - ButtonScale.Half().X, ButtonPos.Y - ButtonScale.Half().Y };
	//FVector2D ButtonRangeMax = { ButtonPos.X + ButtonScale.Half().X, ButtonPos.Y + ButtonScale.Half().Y };

	//if (MousePos.X > ButtonRangeMin.X &&
	//	MousePos.Y > ButtonRangeMin.Y &&
	//	MousePos.X < ButtonRangeMax.X &&
	//	MousePos.Y < ButtonRangeMax.Y)
	//{
	//	return false;
	//}

	return true;
}
