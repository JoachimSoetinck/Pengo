#include "EnemyManager.h"
#include "SnoBeeCompontent.h"

dae::EnemyManager::EnemyManager() :m_Snobees(std::vector<dae::SnoBeeCompontent*>())
{
}

void dae::EnemyManager::AddComponent(SnoBeeCompontent* snobee) 
{


	m_Snobees.push_back(snobee); 
}

void dae::EnemyManager::RemoveComponent(SnoBeeCompontent* snobee)
{
	auto it = std::find(m_Snobees.begin(), m_Snobees.end(), snobee);


	if (it != m_Snobees.end())
	{
		m_Snobees.erase(it);
	}
}

const std::vector<dae::SnoBeeCompontent*>& dae::EnemyManager::GetEnemies() const
{
	// TODO: insert return statement here
	return m_Snobees;
}
