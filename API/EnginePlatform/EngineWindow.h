#pragma once
// os
#include <Windows.h>

// std
#include <map>
#include <string>
#include <functional>

// user
#include <EngineBase/EngineDelegate.h>


class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);

	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);

	UEngineWindow();
	~UEngineWindow();

	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	void Open(std::string_view _TitleName = "Window");

	inline HDC GetBackBuffer()
	{
		return BackBuffer;
	}

	inline void SetWindowTitle(std::string_view Text)
	{
		SetWindowTextA(WindowHandle, Text.data());
	}

protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	HDC BackBuffer = nullptr;
	HWND WindowHandle = nullptr;
};


