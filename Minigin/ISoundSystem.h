#pragma once
#include <string>

namespace dae {
	class ISoundSystem
	{
	public:
		ISoundSystem() = default;
		virtual ~ISoundSystem() = default;

		virtual void Update() = 0;
		virtual void PlaySound(int soundID) = 0;
		virtual void PauseSound() = 0;
		virtual void UnpauseSound() = 0;
		virtual void IncreaseVolume() = 0;
		virtual void DecreaseVolume() = 0;
		virtual void AddSound(const std::string& filename) = 0;

		ISoundSystem(const ISoundSystem&) = delete;
		ISoundSystem(ISoundSystem&&) = delete;
		ISoundSystem& operator= (const ISoundSystem&) = delete;
		ISoundSystem& operator= (const ISoundSystem&&) = delete;
	};
}


