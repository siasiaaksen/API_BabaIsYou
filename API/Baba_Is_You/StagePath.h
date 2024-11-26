#pragma once


class StagePath
{
public:
	StagePath();
	~StagePath();

	StagePath(const StagePath& _Other) = delete;
	StagePath(StagePath&& _Other) noexcept = delete;
	StagePath& operator=(const StagePath& _Other) = delete;
	StagePath& operator=(StagePath&& _Other) noexcept = delete;

	void SetPath(int _StageNum)
	{
		switch (_StageNum)
		{
		case 0:
			Path = ".\\..\\BabaResources\\Data\\Level00.MData";
			break;
		case 1:
			Path = ".\\..\\BabaResources\\Data\\Level01.MData";
			break;
		case 2:
			Path = ".\\..\\BabaResources\\Data\\Level02.MData";
			break;
		case 3:
			Path = ".\\..\\BabaResources\\Data\\Level03.MData";
			break;
		case 4:
			Path = ".\\..\\BabaResources\\Data\\Level04.MData";
			break;
		case 5:
			Path = ".\\..\\BabaResources\\Data\\Level05.MData";
			break;
		case 6:
			Path = ".\\..\\BabaResources\\Data\\Level06.MData";
			break;
		case 7:
			Path = ".\\..\\BabaResources\\Data\\Level07.MData";
			break;
		default:
			break;
		}
	}

	std::string GetPath()
	{
		return Path;
	}

protected:

private:
	std::string Path;
};

