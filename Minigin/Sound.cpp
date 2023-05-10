#include "MiniginPCH.h"
#include "Sound.h"
#include <SDL_mixer.h>

class Sound::SoundImpl
{
	Mix_Chunk* m_pChunk{};
	std::string m_Path;
	bool m_isLooping;

public:
	SoundImpl(const std::string& path, bool isLooping)
		:m_Path(path),
		m_isLooping(isLooping)
	{
	}

	~SoundImpl()
	{
		if (m_pChunk)
			Mix_FreeChunk(m_pChunk);
	}

	bool IsPlaying() const
	{
		return Mix_Playing;
	}
	void Load()
	{
		m_pChunk = Mix_LoadWAV(m_Path.c_str());
		m_pChunk->volume = 100;
		if (m_pChunk == nullptr)
		{
			std::cout << "could not find path: " << m_Path << "\n";
		}
		else
		{
			std::cout << "found path: " << m_Path << "\n";
		}
	}

	bool IsLoaded() const
	{
		if (m_pChunk == nullptr)
			return false;

		return true;
	}

	bool Play()
  	{
		if (!IsLoaded())
			return false;

		int channel{};
		if (m_isLooping)
		{
			channel = Mix_PlayChannel(-1, m_pChunk, -1);
			
		}

		else
		{
			channel = Mix_PlayChannel(-1, m_pChunk,0);
			auto p = Mix_Playing(-1);
			std::cout << p << std::endl;
		}

		return channel == -1 ? false : true;
	}

	void SetVolume(int volume)
	{
		if (IsLoaded())
		{
			Mix_Volume(-1, volume);
		}
	}

	int GetVolume() const
	{
		if (IsLoaded())
		{
			return Mix_VolumeChunk(m_pChunk, -1);
		}
		return 0;
	}
};

Sound::Sound(const std::string& path, bool isLooping)
{
	pImpl = new SoundImpl(path, isLooping);
}

Sound::~Sound()
{
	delete pImpl;
}

void Sound::Load()
{
	pImpl->Load();
}

bool Sound::Play()
{
	return pImpl->Play();
}

void Sound::SetVolume(int volume)
{
	pImpl->SetVolume(volume);
}

bool Sound::IsLoaded() const
{
	return pImpl->IsLoaded();
}

bool Sound::IsPlaying() const
{
	return pImpl->IsPlaying();
}

int Sound::GetVolume() const
{
	return pImpl->GetVolume();
}
