#include "CollisionManager.h"
#include "CollisionComponent.h"

dae::CollisionManager::CollisionManager():
	m_CollisionBoxes(std::vector<CollisionComponent*>())
{
}

void dae::CollisionManager::AddComponent(CollisionComponent* collision)
{
	//Dont add duplicate collisionBoxes
	auto it = std::find(m_CollisionBoxes.begin(), m_CollisionBoxes.end(), collision);
	if (it == m_CollisionBoxes.end())
	{
		m_CollisionBoxes.push_back(collision);
	}
}

void dae::CollisionManager::RemoveComponent(CollisionComponent* collision)
{
	//Searching for collision
	auto it = std::find(m_CollisionBoxes.begin(), m_CollisionBoxes.end(), collision);
	
	//if collision is there, remove it
	if (it != m_CollisionBoxes.end())
	{
		m_CollisionBoxes.erase(it);
	}
}

const std::vector<dae::CollisionComponent*>& dae::CollisionManager::GetCollisionsBoxes() const
{
	return m_CollisionBoxes;
}
