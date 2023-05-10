#pragma once
class Sound final
{
public:
	Sound(const std::string& path, bool isLooping = false);
	~Sound();
	Sound(const Sound& other) = delete;
	Sound(Sound&& other) noexcept = delete;
	Sound& operator=(const Sound& other) = delete;
	Sound& operator=(Sound&& other) noexcept = delete;

	void Load();
	bool Play();

	void SetVolume(int volume);
	int GetVolume() const;
	bool IsLoaded() const;
	bool IsPlaying() const;


private:

	class SoundImpl;
	SoundImpl* pImpl{};
};