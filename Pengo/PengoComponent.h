#pragma once
#include "BaseComponent.h"
#include "RigidBody.h"
#include "Subject.h"
#include "CollisionComponent.h"

namespace dae
{
	class WallComponent;
	class PengoComponent final : public dae::BaseComponent
	{
	public:
		enum class PengoState
		{
			Left, Right, Up, Down, Pushing, Idle
		};

		PengoComponent(GameObject* gameObject, int startBlock = 0);
		~PengoComponent() override ;
		PengoComponent(const PengoComponent& other) = delete;
		PengoComponent(PengoComponent&& other) noexcept = delete;
		PengoComponent& operator=(const PengoComponent& other) = delete;
		PengoComponent& operator=(PengoComponent&& other) noexcept = delete;

		void AddObserver(Observer* obj);

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		int GetLives() const { return m_NrOfLives; };
		int GetScore() const { return m_Score; };
		void Start();
		void Die();
		void GivePoints(int score);
		void Push();

		void OnHit(HitInfo* hit);

		void SetState(PengoState state);

		void Move(PengoState state);
	

	private:
		PengoState m_CurrentState;
		glm::ivec2 m_Direction{ 0,0 };

	
		dae::RigidBody* m_RigidBody;

		int m_NrOfLives{ 3 };
		int m_Score{ 0 };

		std::unique_ptr<Subject> m_PlayerSubject;

		int m_StartBlock = 0;
		WallComponent* m_CurrentBlock;
	
	
		
		bool m_IsMoving;
		bool m_IsSpawned{ false };
		glm::ivec2 m_PlayerSize{};

	
	};
}
