#pragma once
#include "BaseComponent.h"

namespace dae {
	class GameObject;
	class TextComponent;

	class FPSComponent final : public  BaseComponent
	{
	public:
		FPSComponent(dae::GameObject* go, TextComponent* tc);

		~FPSComponent() override = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

	private:
		TextComponent* pTextComponent;
		const float m_UpdateFPSInterval = 0.3f;
		float m_TimeSinceLastUpdate = 0.f;
		std::string m_text;
	};

}