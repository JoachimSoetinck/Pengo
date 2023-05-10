#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include "Sound.h"
#include <iostream>


dae::SDLSoundSystem::SDLSoundSystem() :m_Sounds{}, m_SoundsToDelete{}
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHANNELS);
	m_thread = std::thread([this] { this->Update(); });
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	for (auto s: m_SoundsToDelete)
	{
		delete s;
		s = nullptr;
	}
	m_Continue = true;
	m_Cv.notify_one();
	Mix_CloseAudio();
	m_thread.join();
}



void dae::SDLSoundSystem::Update()
{
	while (!m_Continue) {
		std::unique_lock<std::mutex> lock(m_mutex);

		// Wait untile queue is not empty
		m_Cv.wait(lock, [&] {
			return m_Sounds.size() > 0 || m_Continue;
			});

		// If the audio thread should be killed skip condition variable and break the loop
		if (m_Continue)
			break;


		Sound* sound = m_Sounds.front();
		m_SoundsToDelete.push_back(sound);
		m_Sounds.pop();


		m_Cv.notify_all();

		if (sound->IsLoaded()) {
			sound->Play();
		}
	}

}

void dae::SDLSoundSystem::PlaySound(const std::string& p)
{
	auto s = new Sound(p);
	std::lock_guard<std::mutex> mLock{ m_mutex };
	s->Load();
	m_Sounds.push(s);
	m_Cv.notify_one();

	
}

void dae::SDLSoundSystem::PlayMusic(const std::string& p)
{
	PlaySound(p);
}

void dae::SDLSoundSystem::PauseSound()
{
}

void dae::SDLSoundSystem::UnpauseSound()
{
}

void dae::SDLSoundSystem::IncreaseVolume()
{
}

void dae::SDLSoundSystem::DecreaseVolume()
{
}
