#include "PreCompile.h"
#include <Baba_Is_You/ContentsCore.h>


#include <EngineCore/EngineAPICore.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "Baba_Is_You.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	ContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}