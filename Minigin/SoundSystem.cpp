#include "SoundSystem.h"
#include <iostream>
namespace dae {
#include "audio.c"
}



dae::SoundSystem::SoundSystem():m_Volume{100}
{
	initAudio();
	m_Thread = std::thread([this]() { this->Update(); });
}

dae::SoundSystem::~SoundSystem()
{
	m_ConditionVariable.notify_one();
	endAudio();
	m_Thread.join();
}

void dae::SoundSystem::Update()
{
	do
	{
		std::unique_lock<std::mutex> mLock{ m_Mutex };
		if (m_IsDone)
		{
			break;
		}

		if (!m_SoundQueue.empty())
		{
			auto s = m_SoundQueue.front();
			m_SoundQueue.pop();

			switch (s.Type)
			{
			case SoundType::Effect:
				playSound(s.file.c_str(), m_Volume);
				break;
			case SoundType::Music:
				playMusic(s.file.c_str(), m_Volume);
				break;
			default:
				break;
			}
		}

		if (m_SoundQueue.empty())
			m_ConditionVariable.wait(mLock);

	} while (!m_SoundQueue.empty());
}

void dae::SoundSystem::PlaySound(const std::string& soundName)
{
	SoundToPlay s;
	s.file = soundName;
	s.Type = SoundType::Effect;
	std::lock_guard<std::mutex> mLock{ m_Mutex };
	m_SoundQueue.push(s);
	m_ConditionVariable.notify_one();
}

void dae::SoundSystem::PlayMusic(const std::string& musicName)
{
	SoundToPlay s;
	s.file = musicName;
	s.Type = SoundType::Music;
	std::lock_guard<std::mutex> mLock{ m_Mutex };
	m_SoundQueue.push(s);
	m_ConditionVariable.notify_one();
}

void dae::SoundSystem::PauseSound()
{

}

void dae::SoundSystem::UnpauseSound()
{
}

void dae::SoundSystem::IncreaseVolume()
{
	m_Volume += 10;
	if (m_Volume > 100)
		m_Volume = 100;
}

void dae::SoundSystem::DecreaseVolume()
{
	m_Volume -= 10;
	if (m_Volume < 0)
		m_Volume = 0;
}
