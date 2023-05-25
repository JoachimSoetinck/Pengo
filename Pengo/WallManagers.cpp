#include "WallManagers.h"
#include "WallComponent.h"
#include "GameObject.h"
#include "SpriteCompenent.h"

dae::WallManager::WallManager() :
	m_GroundPieces(std::vector<WallComponent*>())
{
}


void dae::WallManager::AddComponent(WallComponent* wall)
{
	auto it = std::find(m_GroundPieces.begin(), m_GroundPieces.end(), wall);

	m_GroundPieces.push_back(wall);

}

void dae::WallManager::RemoveComponent(WallComponent* wall)
{
	auto it = std::find(m_GroundPieces.begin(), m_GroundPieces.end(), wall);


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

void dae::WallManager::AddSpawner(WallComponent* spawner)
{


	if (std::find(m_Spawners.begin(), m_Spawners.end(), spawner) != m_Spawners.end())

	{
		return;
	}

	else
	{
		if (spawner->IsSpawner() )
			m_Spawners.push_back(spawner);
	}
}

void dae::WallManager::RemoveSpawner(WallComponent* spawner)
{
	auto it = std::find(m_Spawners.begin(), m_Spawners.end(), spawner);


	if (it != m_Spawners.end())
	{
		m_Spawners.erase(it);
	}
}

const std::vector<dae::WallComponent*>& dae::WallManager::GetGroundPieces() const
{
	return m_GroundPieces;
}

const std::vector<dae::WallComponent*>& dae::WallManager::GetSpawners() const
{
	// TODO: insert return statement here
	return m_Spawners;
}

bool dae::WallManager::IsPointInWall(glm::ivec2 p)
{
	bool r = false;
	for (auto w : m_GroundPieces)
	{
		r = w->IsPointInWall(p);

		if (r == true)
			break;
	}

	return r;
}

dae::WallComponent* dae::WallManager::FindCollisionWithWall(WallComponent* wall)
{
	for (auto comp : m_GroundPieces)
	{
		if (comp->GetType() == dae::WallComponent::WallType::MoveableWall && comp->IsMoving() && comp != wall)
		{

			SDL_Rect r1 = { wall->GetGameObject()->GetLocalPosition().x,
							wall->GetGameObject()->GetLocalPosition().y,
							20,
							20 };
			SDL_Rect other = { comp->GetGameObject()->GetLocalPosition().x,
							comp->GetGameObject()->GetLocalPosition().y,
							comp->GetGameObject()->GetComponent<SpriteComponent>()->GetDestRect().w,
							comp->GetGameObject()->GetComponent<SpriteComponent>()->GetDestRect().h };

			if ((r1.x + r1.w) < other.x || (other.x + other.w) < r1.x)
			{
				return nullptr;
			}

			if (r1.y > (other.y + other.h) || other.y > (r1.y + r1.h))
			{
				return nullptr;
			}

			return comp;
		}


	}

	return nullptr;
}
