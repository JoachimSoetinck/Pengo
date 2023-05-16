#pragma once
#include "BaseComponent.h"
#include "RigidBody.h"
#include "Subject.h"

namespace dae
{
	class SnoBeeCompontent final : public dae::BaseComponent
	{
	public:
		enum class SnobeeState
		{
			Left, Right, Up, Down, Pushing, Idle
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

		int GetLives() const { return m_nrOfLives; };
		int GetScore() const { return m_score; };
		
		void Start();
		void Die();
		void Push();



		void SetState(SnobeeState state);

		void Move(SnobeeState state);


	private:
		SnobeeState m_currentState;
		glm::ivec2 m_direction{ 0,0 };

		dae::RigidBody* m_RigidBody;

		int m_nrOfLives{ 3 };
		int m_score{ 0 };

		std::unique_ptr<Subject> m_PlayerSubject;

		int m_StartBlock = 120;
		int m_currentBlock{};



		bool m_isMoving;
		glm::ivec2 m_playerSize{};


	};
}
