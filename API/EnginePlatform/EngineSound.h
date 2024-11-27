#pragma once
#include <EngineBase/EngineResources.h>
#include <map>

#include "ThirdParty/FMOD/inc/fmod.hpp"
#include "math.h"


class USoundPlayer
{
public:
	friend class UEngineSound;

	void On()
	{
		Control->setPaused(false);
	}

	void Off()
	{
		Control->setPaused(true);
	}

	void Stop()
	{
		Control->stop();
	}

	void SetVolume(float _Volume)
	{
		_Volume = UEngineMath::Clamp(_Volume, 0.0f, 1.0f);

		Control->setVolume(_Volume);
	}

	void OnOffSwtich()
	{
		bool Check = false;
		Control->getPaused(&Check);

		if (true == Check)
		{
			Control->setPaused(false);
		}
		else
		{
			Control->setPaused(true);
		}
	}

	void SetPosition(unsigned int _Value)
	{
		Control->setPosition(_Value, FMOD_TIMEUNIT_MS);
	}

	void Loop(int Count = -1)
	{
		Control->setLoopCount(Count);
	}

	void ReStart()
	{
		SetPosition(0);
	}

	unsigned int LengthMs()
	{
		unsigned int ResultLength = 0;
		SoundHandle->getLength(&ResultLength, FMOD_TIMEUNIT_MS);
		return ResultLength;
	}

private:
	FMOD::Channel* Control = nullptr;
	FMOD::Sound* SoundHandle = nullptr;;
};

class UEngineSound : public UEngineResources
{
public:
	UEngineSound();
	~UEngineSound();

	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	static void Load(std::string_view _Path);
	static void Load(std::string_view _Name, std::string_view _Path);

	static USoundPlayer Play(std::string_view _Name);
	static UEngineSound* Find(std::string_view _Name);

	static void Release();
	static void Update();

protected:

private:
	static std::map<std::string, UEngineSound*> Sounds;

	FMOD::Sound* SoundHandle;

	bool ResLoad(std::string_view _Path);
};

