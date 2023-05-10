#pragma once
#include "ISoundSystem.h"
#include "Sound.h"

#include <queue>
#include <memory>
#include <thread>
#include <condition_variable>

namespace dae
{
	class SDLSoundSystem final: public ISoundSystem
	{
	
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem() override;

		void Update() override;
		void PlaySound(const std::string&) override;
		void PlayMusic(const std::string&) override;
		void PauseSound() override;
		void UnpauseSound() override;
		void IncreaseVolume() override;
		void DecreaseVolume() override;

		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&&) = delete;

	private:
		
		std::queue<Sound*> m_Sounds;
		std::vector<Sound*> m_SoundsToDelete;
		std::thread m_thread;
		std::condition_variable m_Cv;
		std::mutex m_mutex;
		bool m_Continue = false;
	};
}