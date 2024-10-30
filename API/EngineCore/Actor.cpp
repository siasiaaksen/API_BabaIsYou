#include "PreCompile.h"
#include "Actor.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

#include "EngineSprite.h"
#include "ImageManager.h"


AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::Render()
{
	if (nullptr == Sprite)
	{
		MSGASSERT("��������Ʈ�� ���õ��� ���� ���͸� �������� �Ҽ� �����ϴ�.");
		return;
	}

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();


	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image;
	CurData.Transform;
	CurData.Image->CopyToTrans(BackBufferImage, Transform, CurData.Transform);

	//FVector2D LeftTop = Transform.Location - Transform.Scale.Half();
	//FVector2D RightBot = Transform.Location + Transform.Scale.Half();

	//UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	//UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	//HDC BackBufferDC = BackBufferImage->GetDC();
	//Rectangle(BackBufferDC, LeftTop.iX(), LeftTop.iY(), RightBot.iX(), RightBot.iY());
}

void AActor::SetSprite(std::string_view _Name, int _CurIndex /*= 0*/)
{
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("�ε����� ���� ��������Ʈ�� ����Ϸ��� �߽��ϴ�" + std::string(_Name));
		return;
	}

	CurIndex = _CurIndex;
}

