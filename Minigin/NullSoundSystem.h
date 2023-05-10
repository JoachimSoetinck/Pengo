#pragma once
#include "ISoundSystem.h"

namespace dae
{
	class NullSoundSystem : public ISoundSystem
	{
	public:
		NullSoundSystem();
		 ~NullSoundSystem() = default;

		void Update() override;
		void PlaySound(int soundId) override;
		void PauseSound() override;
		void UnpauseSound() override;
		void IncreaseVolume() override;
		void DecreaseVolume() override;

		NullSoundSystem(const NullSoundSystem&) = delete;
		NullSoundSystem(NullSoundSystem&&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&&) = delete;
	};
}


