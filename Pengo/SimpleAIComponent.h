#pragma once
#include "BaseComponent.h"

namespace dae
{
	class RigidBody;
	class SnoBeeCompontent;

	class SimpleAIComponent final : public dae::BaseComponent
	{
	public:

		SimpleAIComponent(GameObject* gameObject);
		~SimpleAIComponent() override;
		SimpleAIComponent(const SimpleAIComponent& other) = delete;
		SimpleAIComponent(SimpleAIComponent&& other) noexcept = delete;
		SimpleAIComponent& operator=(const SimpleAIComponent& other) = delete;
		SimpleAIComponent& operator=(SimpleAIComponent&& other) noexcept = delete;

	
		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

	

	private:
		SnoBeeCompontent* m_Snobee;
		RigidBody* m_RigidBody;
	};
}

