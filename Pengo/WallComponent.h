#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

namespace dae {
	class GameObject;
	class SpriteComponent;
	class StateMachine;
	class BaseState;

	struct HitInfo;
	
	class WallComponent final : public  BaseComponent
	{
	public:
		enum class WallType {
			Border,
			MoveableWall,
			EnemySpawn,
			Ground,
			IndestructableWall
		};

		WallComponent(dae::GameObject* go,  int nr, WallType wallType=WallType::MoveableWall);

		~WallComponent() override;

		WallComponent(const WallComponent& other) = delete;
		WallComponent(WallComponent&& other) noexcept = delete;
		WallComponent& operator=(const WallComponent& other) = delete;
		WallComponent& operator=(WallComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		void HandleMovement();


		WallType GetType() const { return m_WallType; };
		int GetNr() const { return m_Nr; };
		glm::ivec2 GetCenter() const { return m_Center; };

		bool IsPointInWall(glm::ivec2 p);
		bool IsMoving() const { return m_IsMoving; };
		void EnableMovement(MovementDirection direction);
		void DisableMovement() { m_IsMoving = false;  };
		void OnHit(HitInfo* hit);

		void SetWallType(WallType type) { m_WallType = type; };
		void MakeSpawner();
		
		void BreakWall();

		bool IsSpawner()const { return m_IsSpawner; };

	private:
		bool m_IsSpawner;
		WallType m_WallType;
		SpriteComponent* m_SpriteComp;
		int m_Nr;

		StateMachine* m_stateMachine;

		glm::ivec2 m_Center{};

		MovementDirection m_pushDirection{};
		bool m_IsMoving{ false };

		
		
	};

	

}
