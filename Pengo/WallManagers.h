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

		const std::vector<WallComponent*>& GetGroundPieces() const;
		bool IsPointInWall(glm::ivec2 p);

		WallComponent* FindCollisionWithWall(WallComponent* wall);

	private:
		std::vector<WallComponent*> m_GroundPieces;
	};

}

