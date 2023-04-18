
#pragma once
#include "BaseComponent.h"

namespace dae {
	class GameObject;

	class CollisionComponent final : public  BaseComponent
	{
	public:
		CollisionComponent(dae::GameObject* go, const SDL_Rect& rect);

		~CollisionComponent() override = default;

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

	private:
		bool m_IsEnabled = true;
		SDL_Rect m_Rect;
	};

}

