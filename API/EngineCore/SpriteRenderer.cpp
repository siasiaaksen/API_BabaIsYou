#include "PreCompile.h"
#include "SpriteRenderer.h"
#include "ImageManager.h"

#include "EngineAPICore.h"
#include <EngineBase/EngineString.h>


USpriteRenderer::USpriteRenderer()
{
}

USpriteRenderer::~USpriteRenderer()
{
}

void USpriteRenderer::Render(float _DeltaTime)
{
	if (nullptr == Sprite)
	{
		MSGASSERT("��������Ʈ�� ���õ��� ���� ���͸� �������� �Ҽ� �����ϴ�.");
		return;
	}

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	FTransform Trans = GetActorTransform();

	ULevel* Level = GetActor()->GetWorld();

	if (true == IsCameraEffect)
	{
		Trans.Location = Trans.Location - (Level->CameraPos * CameraEffectScale);
	}

	FVector2D PivotRealScale;
	PivotRealScale.X = std::floorf((0.5f - Pivot.X) * Trans.Scale.X);
	PivotRealScale.Y = std::floorf((0.5f - Pivot.Y) * Trans.Scale.Y);

	Trans.Location += PivotRealScale;

	if (Alpha == 255)
	{
		CurData.Image->CopyToTrans(BackBufferImage, Trans, CurData.Transform);
	}
	else
	{
		CurData.Image->CopyToAlpha(BackBufferImage, Trans, CurData.Transform, Alpha);
	}
}

void USpriteRenderer::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();

	Level->ChangeRenderOrder(this, this->GetOrder());
}

void USpriteRenderer::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);

	// �ִϸ��̼� ����
	if (nullptr != CurAnimation)
	{
		CurAnimation->IsEnd = false;
		std::vector<int>& Indexs = CurAnimation->FrameIndex;
		std::vector<float>& Times = CurAnimation->FrameTime;

		Sprite = CurAnimation->Sprite;
		
		CurAnimation->CurTime += _DeltaTime * CurAnimationSpeed;

		float CurFrameTime = Times[CurAnimation->CurIndex];

		if (CurAnimation->CurTime > CurFrameTime)
		{
			CurAnimation->CurTime -= CurFrameTime;
			++CurAnimation->CurIndex;

			if (CurAnimation->Events.contains(CurIndex))
			{
				CurAnimation->Events[CurIndex]();
			}

			// �ִϸ��̼� �ص�
			if (CurAnimation->CurIndex >= Indexs.size())
			{
				CurAnimation->IsEnd = true;
			}
			else 
			{
				CurAnimation->IsEnd = false;
			}

			if (CurAnimation->CurIndex >= Indexs.size())
			{
				if (true == CurAnimation->Loop)
				{
					CurAnimation->CurIndex = 0;

					if (CurAnimation->Events.contains(CurIndex))
					{
						CurAnimation->Events[CurIndex]();
					}
					else
					{
						CurAnimation->IsEnd = true;
						--CurAnimation->CurIndex;
					}
				}
			}
		}

		CurIndex = Indexs[CurAnimation->CurIndex];
	}
}

void USpriteRenderer::SetSprite(std::string_view _Name, int _CurIndex /*= 0*/)
{
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("�ε����� ���� ��������Ʈ�� ����Ϸ��� �߽��ϴ�" + std::string(_Name));
		return;
	}

	CurIndex = _CurIndex;
}

void USpriteRenderer::SetOrder(int _Order)
{
	int PrevOrder = Order;

	Order = _Order;

	if (PrevOrder == Order)
	{
		return;
	}

	ULevel* Level = GetActor()->GetWorld();

	if (nullptr != Level)
	{
		Level->ChangeRenderOrder(this, PrevOrder);
	}
}

FVector2D USpriteRenderer::SetSpriteScale(float _Ratio /*= 1.0f*/, int _CurIndex /*= 0*/)
{
	if (nullptr == Sprite)
	{
		MSGASSERT("��������Ʈ�� �������� �ʰ� ��������Ʈ ũ��� ������ ũ�⸦ �����Ҽ� �����ϴ�.");
		return FVector2D::ZERO;
	}

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(_CurIndex);

	FVector2D Scale = CurData.Transform.Scale * _Ratio;

	SetComponentScale(CurData.Transform.Scale * _Ratio);

	return Scale;
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time /*= 0.1f*/, bool _Loop /*= true*/)
{
	int Inter = 0;

	std::vector<int> Indexs;
	std::vector<float> Times;

	if (_Start < _End)
	{
		Inter = (_End - _Start) + 1;
		for (size_t i = 0; i < Inter; i++)
		{
			Indexs.push_back(_Start);
			Times.push_back(Time);
			++_Start;
		}
	}
	else
	{
		Inter = (_Start - _End) + 1;
		for (size_t i = 0; i < Inter; i++)
		{
			Indexs.push_back(_End);
			Times.push_back(Time);
			++_End;
		}
	}

	CreateAnimation(_AnimationName, _SpriteName, Indexs, Times, _Loop);
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop /* = true*/)
{
	std::vector<float> Times;

	for (size_t i = 0; i < _Indexs.size(); i++)
	{
		Times.push_back(_Frame);
	}

	CreateAnimation(_AnimationName, _SpriteName, _Indexs, Times, _Loop);
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop /*= true*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (_Frame.size() != _Indexs.size())
	{
		MSGASSERT(UpperName + "�� ����� ������ �����ϴ� �����Ӱ� Ÿ���� ī��Ʈ�� ���� �ٸ��ϴ�");
		return;
	}

	if (FrameAnimations.contains(UpperName))
	{
		return;
	}

	UEngineSprite* FindSprite = UImageManager::GetInst().FindSprite(_SpriteName);

	if (nullptr == FindSprite)
	{
		MSGASSERT("�ε����� ���� ��������Ʈ�� �ִϸ��̼� ������ ����Ϸ��� �߽��ϴ�" + std::string(UpperName));
		return;
	}

	FrameAnimation NewAnimation;
	NewAnimation.Sprite = FindSprite;
	NewAnimation.FrameIndex = _Indexs;
	NewAnimation.FrameTime = _Frame;
	NewAnimation.Loop = _Loop;
	NewAnimation.Reset();

	FrameAnimations.insert({ UpperName ,NewAnimation });
}

void USpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT("�������� ���� �ִϸ��̼����� �����Ϸ��� �߽��ϴ�. = " + UpperName);
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	if (CurAnimation == ChangeAnimation && false == _Force)
	{
		return;
	}

	CurAnimation = &FrameAnimations[UpperName];
	CurAnimation->Reset();
	CurIndex = CurAnimation->FrameIndex[CurAnimation->CurIndex];

	if (CurAnimation->Events.contains(CurAnimation->CurIndex))
	{
		CurAnimation->Events[CurAnimation->CurIndex]();
	}

	Sprite = CurAnimation->Sprite;
}

void USpriteRenderer::SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT("�������� ���� �ִϸ��̼����� �����Ϸ��� �߽��ϴ�. = " + UpperName);
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	bool Check = false;

	for (size_t i = 0; i < ChangeAnimation->FrameIndex.size(); i++)
	{
		if (_Frame == ChangeAnimation->FrameIndex[i])
		{
			Check = true;
			break;
		}
	}

	if (false == Check)
	{
		MSGASSERT("�������� �ʴ� �����ӿ� �̺�Ʈ�� �����Ϸ��� �߽��ϴ�" + std::string(_AnimationName));
		return;
	}

	ChangeAnimation->Events[_Frame] += _Function;
}

void USpriteRenderer::SetCameraEffectScale(float _Effect)
{
	CameraEffectScale = _Effect;
}

void USpriteRenderer::SetPivotType(PivotType _Type)
{
	if (PivotType::Center == _Type)
	{
		Pivot = FVector2D::ZERO;
		return;
	}

	if (nullptr == Sprite)
	{
		MSGASSERT("�̹����� ��������� �Ǻ������� ��������Ʈ�� ���õ��� ���� ���¿����� ȣ���Ҽ� �����ϴ�");
		return;
	}

	//UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	switch (_Type)
	{
	case PivotType::Center:
		Pivot.X = 0.5f;
		Pivot.Y = 0.5f;
		break;
	case PivotType::Bot:
		Pivot.X = 0.5f;
		Pivot.Y = 1.0f;
		break;
	case PivotType::Top:
		Pivot.X = 0.5f;
		Pivot.Y = 0.0f;
		break;
	case PivotType::LeftTop:
		Pivot.X = 0.0f;
		Pivot.Y = 0.0f;
		break;
	default:
		break;
	}
}

void USpriteRenderer::SetPivotValue(FVector2D _Value)
{
	Pivot = _Value;
}