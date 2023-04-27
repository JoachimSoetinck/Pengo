#include "WallManagers.h"
#include "WallComponent.h"
#include "GameObject.h"

dae::WallManager::WallManager() :
	m_GroundPieces(std::vector<WallComponent*>())
{
}


void dae::WallManager::AddComponent(WallComponent* wall)
{
	auto it = std::find(m_GroundPieces.begin(), m_GroundPieces.end(), wall);
	{
		m_GroundPieces.push_back(wall);
	}
} 

void dae::WallManager::RemoveComponent(WallComponent* wall)
{
	auto it = std::find(m_GroundPieces.begin(), m_GroundPieces.end(), wall);

	//if collision is there, remove it
	if (it != m_GroundPieces.end())
	{
		m_GroundPieces.erase(it);
	}
}

dae::WallComponent* dae::WallManager::FindWall(int nr)
{
	for (auto comp : m_GroundPieces)
	{
		if (comp->GetNr() == nr)
		{
			return comp;
		}
	}

	return nullptr;
}

dae::WallComponent* dae::WallManager::FindWall(glm::ivec2 pos)
{
	for (auto comp : m_GroundPieces)
	{
		if (comp->GetCenter() == pos)
		{
			return comp;
		}
	}

	return nullptr;
}

const std::vector<dae::WallComponent*>& dae::WallManager::GetGroundPieces() const
{
	return m_GroundPieces;
}

bool dae::WallManager::IsPointInWall(glm::ivec2 p)
{
	bool r =false;
	for (auto w : m_GroundPieces)
	{
		 r = w->IsPointInWall(p);
		 
		 if (r == true)
			 break;
	}

	return r;
}
