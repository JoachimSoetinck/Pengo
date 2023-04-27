#pragma once
#include "BaseComponent.h"

namespace dae {
	class GameObject;
	class SpriteComponent;

	
	class WallComponent final : public  BaseComponent
	{
	public:
		enum class WallType {
			Border,
			MoveableWall,
			EnemySpawn,
			Ground
		};

		WallComponent(dae::GameObject* go, WallType wallType=WallType::MoveableWall);

		~WallComponent() override = default;

		WallComponent(const WallComponent& other) = delete;
		WallComponent(WallComponent&& other) noexcept = delete;
		WallComponent& operator=(const WallComponent& other) = delete;
		WallComponent& operator=(WallComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		WallType GetType() const { return m_WallType; };

	private:
		WallType m_WallType;
		SpriteComponent* m_SpriteComp;

		
	};

}
