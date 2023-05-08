#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae {
	class GameObject;
	class TextComponent;

	class ScoreDisplayComponent final : public  BaseComponent, public Observer
	{
	public:
		ScoreDisplayComponent(dae::GameObject* go);

		~ScoreDisplayComponent() override = default;

		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) noexcept = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		void OnNotify(Event event, GameObject* go) override;

	private:
		TextComponent* pTextComponent;
		std::string m_text;
	};

}

