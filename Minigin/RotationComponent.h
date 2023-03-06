#pragma once
#include "BaseComponent.h"

namespace dae {
	class GameObject;
	class TextComponent;

	class RotationComponent final : public  BaseComponent
	{
	public:
		RotationComponent(dae::GameObject* go);

		~RotationComponent() override = default;

		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) noexcept = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

	private:
		double m_CurrentAngle;
		float m_RotationSpeed{ 20.0f };
	};

}
