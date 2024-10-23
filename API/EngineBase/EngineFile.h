#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>


const int MAXPATH = 256;

class UEngineFile
{
public:
	UEngineFile();
	~UEngineFile();

	inline void SetPath(const char* _Path)
	{
		strcpy_s(Path, _Path);
	}

	void Write(const void* _Ptr, size_t _Size);
	void Read(void* _Ptr, size_t _Size);

	void FileOpen(const char* _Mode);
	bool IsExits();
	void Close();

private:
	char Path[MAXPATH] = "";
	FILE* File = nullptr;
};

