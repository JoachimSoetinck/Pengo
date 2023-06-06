#pragma once
#include "BaseComponent.h"

#include "Subject.h"

namespace dae
{
	class RigidBody;
	struct HitInfo;
	class SnoBeeCompontent final : public dae::BaseComponent
	{
	public:
		
		enum class SnobeeState
		{
			Left =0, Right =1, Up=2, Down=3, Pushing, Idle
		};

		SnoBeeCompontent(GameObject* gameObject, int startBlock = 100);
		~SnoBeeCompontent() override;
		SnoBeeCompontent(const SnoBeeCompontent& other) = delete;
		SnoBeeCompontent(SnoBeeCompontent&& other) noexcept = delete;
		SnoBeeCompontent& operator=(const SnoBeeCompontent& other) = delete;
		SnoBeeCompontent& operator=(SnoBeeCompontent&& other) noexcept = delete;

		void AddObserver(Observer* obj);

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		int GetLives() const { return m_NrOfLives; };
		int GetScore() const { return m_Score; };
		SnobeeState GetState() const { return m_CurrentState; };
		
		void Start();
		void Die();
		void Push();



		void SetState(SnobeeState state);

		void Move(SnobeeState state);

		void OnHit(HitInfo* hit);


	private:
		SnobeeState m_CurrentState;
		glm::ivec2 m_Direction{ 0,0 };

		dae::RigidBody* m_RigidBody;

		int m_NrOfLives{ 3 };
		int m_Score{ 0 };

		std::unique_ptr<Subject> m_PlayerSubject;

		int m_StartBlock = 120;
		int m_CurrentBlock{};



		bool m_IsMoving;
		glm::ivec2 m_PlayerSize{};


	};
}
