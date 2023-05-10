#include "SDLSoundSystem.h"
#include <iostream>


dae::SDLSoundSystem::SDLSoundSystem() :m_SoundList{}, m_eventQueue{}
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHANNELS);

	m_Thread = std::jthread(&SDLSoundSystem::Update, this);
	std::cout << "Sound system initialized.\n";
}

dae::SDLSoundSystem::~SDLSoundSystem()
{

	m_quit = true;
	m_cv.notify_one();
	
	//removing added sounds
	for (auto& sound : m_SoundList) {
		Mix_FreeChunk(sound.second);
		sound.second = nullptr;
	}

	Mix_CloseAudio();
	Mix_Quit();

}



void dae::SDLSoundSystem::Update()
{
	while (!m_quit) {
		//threaded
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cv.wait(lock, [this]() { return !m_eventQueue.empty() || m_quit; });
		if (m_quit) {
			break;
		}

		//getting first sound
		auto event = m_eventQueue.front();
		m_eventQueue.pop();

		//handling correct soundType
		switch (event.type) {
		case SoundType::Sound:
			if (m_SoundList.count(event.soundId)) {
				auto chunk = m_SoundList[event.soundId];
				Mix_PlayChannel(-1, chunk, 0);
				m_playingSounds.push_back(chunk);
			}
			break;
		default:
			break;
		}
	}

}

void dae::SDLSoundSystem::PlaySound(int soundId)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_eventQueue.push(Event{ SoundType::Sound, soundId });
	m_cv.notify_one();


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

void dae::SDLSoundSystem::AddSound(const std::string& filename)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
	if (sound != nullptr) {
		int soundId = static_cast<int>(m_SoundList.size());
		m_SoundList[soundId] = sound;
	}
}
