#pragma once
#include <vector>
#include "EnginePath.h"


class UEngineDirectory : public UEnginePath
{
public:
	UEngineDirectory();
	UEngineDirectory(std::string_view _Path);
	UEngineDirectory(std::filesystem::path _Path);
	~UEngineDirectory();

	//UEngineDirectory(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	//UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

	std::vector<class UEngineFile> GetAllFile(bool _IsRecursive = true);
	std::vector<class UEngineDirectory> GetAllDirectory();

protected:

private:
	void GetAllFileRecursive(std::filesystem::path _Path, std::vector<class UEngineFile>& _Result);
};

