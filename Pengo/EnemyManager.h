#pragma once
#include "Singleton.h"
#include <vector>
#include "MiniginPCH.h"

namespace dae
{
	class SnoBeeCompontent;

	class EnemyManager final : public Singleton<EnemyManager>
	{
	public:
		EnemyManager();
		~EnemyManager() = default;
		void AddComponent(SnoBeeCompontent* snobee);
		void RemoveComponent(SnoBeeCompontent* snobee);


		const std::vector<SnoBeeCompontent*>& GetEnemies() const;

		

	private:
		std::vector<SnoBeeCompontent*> m_Snobees{};
		
		int m_NrOfEnemiesDefeatedP{ 0 };
	};

}