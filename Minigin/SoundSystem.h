#pragma once
#include "ISoundSystem.h"
#include <condition_variable>
#include <queue>

namespace dae
{
	class Sound;
	enum class SoundType {
		Effect, Music
	};

	struct SoundToPlay {
		SoundType Type;
		std::string file; 
	};
	class SoundSystem final : public ISoundSystem
	{
	public:
		SoundSystem();
		virtual ~SoundSystem();

		void Update() override;
		void PlaySound(const std::string& soundName) override;
		void PlayMusic(const std::string& musicName) override;
		void PauseSound() override;
		void UnpauseSound() override;
		void IncreaseVolume() override;
		void DecreaseVolume() override;

		SoundSystem(const SoundSystem&) = delete;
		SoundSystem(SoundSystem&&) = delete;
		SoundSystem& operator= (const SoundSystem&) = delete;
		SoundSystem& operator= (const SoundSystem&&) = delete;

	private:
		int m_Volume;
		std::queue<SoundToPlay> m_SoundQueue;
		std::condition_variable m_ConditionVariable;
		
		std::mutex m_Mutex;
		std::thread m_Thread;
		
		bool m_IsDone = false;
	};
}


