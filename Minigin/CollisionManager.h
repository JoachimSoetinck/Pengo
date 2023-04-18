#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{
	class CollisionComponent;
	
	class CollisionManager final: public Singleton<CollisionManager>
	{
	public:
		CollisionManager();
		~CollisionManager() = default;
		void AddComponent(CollisionComponent* collision);
		void RemoveComponent(CollisionComponent* collision);
		const std::vector<CollisionComponent*>& GetCollisionsBoxes() const;

	private:
		std::vector<CollisionComponent*> m_CollisionBoxes;
	};

}

