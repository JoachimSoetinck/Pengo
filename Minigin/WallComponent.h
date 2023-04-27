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

		WallComponent(dae::GameObject* go,  int nr, WallType wallType=WallType::MoveableWall);

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
		int GetNr() const { return m_Nr; };
		glm::ivec2 GetCenter() const { return m_Center; };

		bool IsPointInWall(glm::ivec2 p);

	private:
		WallType m_WallType;
		SpriteComponent* m_SpriteComp;
		int m_Nr;

		glm::ivec2 m_Center{};

		
	};

}
