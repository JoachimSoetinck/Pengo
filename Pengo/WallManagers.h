#pragma once
#include "Singleton.h"
#include <vector>
#include "MiniginPCH.h"

namespace dae
{
	class WallComponent;

	class WallManager final : public Singleton<WallManager>
	{
	public:
		WallManager();
		~WallManager() = default;
		void AddComponent(WallComponent* collision);
		void RemoveComponent(WallComponent* collision);
		
		WallComponent* FindWall(int nr);
		WallComponent* FindWall(glm::ivec2 pos);

		void AddSpawner(WallComponent* spawner);
		void RemoveSpawner(WallComponent* spawner);

		const std::vector<WallComponent*>& GetGroundPieces() const;
		const std::vector<WallComponent*>& GetSpawners() const;
		bool IsPointInWall(glm::ivec2 p);

		WallComponent* FindCollisionWithWall(WallComponent* wall);

		void ClearWalls() { m_GroundPieces.clear(); };

	private:
		std::vector<WallComponent*> m_GroundPieces;
		std::vector<WallComponent*> m_Spawners;
	};

}

