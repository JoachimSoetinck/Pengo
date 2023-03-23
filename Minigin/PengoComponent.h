#pragma once
#include "BaseComponent.h"
#include "RigidBody.h"

namespace dae
{
	class PengoComponent final : public dae::BaseComponent
	{
	public:
		enum class PengoState
		{
			Left, Right, Up, Down, Pushing, Idle
		};

		PengoComponent(GameObject* gameObject);
		~PengoComponent() override = default;
		PengoComponent(const PengoComponent& other) = delete;
		PengoComponent(PengoComponent&& other) noexcept = delete;
		PengoComponent& operator=(const PengoComponent& other) = delete;
		PengoComponent& operator=(PengoComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		void SetState(PengoState state);
	

	private:
		PengoState m_currentState;
		glm::ivec2 m_direction{ 0,0 };
	
		dae::RigidBody* m_RigidBody;

		int m_nrOfLives{ 3 };
		int m_score{ 0 };

		void Push();

	
	};
}
