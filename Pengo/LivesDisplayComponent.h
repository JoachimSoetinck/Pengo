#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae {
	class GameObject;
	class TextComponent;

	class LivesDisplayComponent final : public  BaseComponent, public Observer
	{
	public:
		LivesDisplayComponent(dae::GameObject* go);

		~LivesDisplayComponent() ;

		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) noexcept = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		void OnNotify(Event event, GameObject* go) override;

	private:
		TextComponent* m_TextComponent;
		std::string m_Text;
	};

}