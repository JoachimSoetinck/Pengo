#pragma once
#include "ISoundSystem.h"
#include <queue>
#include <memory>
#include <thread>
#include <condition_variable>
#include <map>
#include <SDL_mixer.h>
#include <unordered_map>

namespace dae
{
	class SDLSoundSystem final : public ISoundSystem
	{

	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem() override;
		void Update() override;
		void PlaySound(int soundID) override;
		void PauseSound() override;
		void UnpauseSound() override;
		void IncreaseVolume() override;
		void DecreaseVolume() override;

		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&&) = delete;
		void AddSound(const std::string& filename) override;

	private:
		enum class SoundType {
			Sound,
			Music

		};

		struct Event {
			SoundType type;
			int soundId;
		};

		std::unordered_map<int, Mix_Chunk*> m_SoundList;
		std::vector<Mix_Chunk*> m_playingSounds;
		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::queue<Event> m_eventQueue;
		bool m_quit = false;
		std::jthread m_Thread;

		int m_volume;
	};
}