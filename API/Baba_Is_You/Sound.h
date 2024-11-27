#pragma once


class Sound
{
public:
	Sound();
	~Sound();

	Sound(const Sound& _Other) = delete;
	Sound(Sound&& _Other) noexcept = delete;
	Sound& operator=(const Sound& _Other) = delete;
	Sound& operator=(Sound&& _Other) noexcept = delete;

protected:

private:

};

