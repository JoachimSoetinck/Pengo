#include "MiniginPCH.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

std::unique_ptr<dae::NullSoundSystem> dae::ServiceLocator::ss_nullService{};
std::unique_ptr<dae::ISoundSystem> dae::ServiceLocator::ss_service{ std::move(ss_nullService) };