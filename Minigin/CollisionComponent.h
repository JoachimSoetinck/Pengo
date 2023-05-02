#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include <functional>

namespace dae {
	class GameObject;

	struct HitInfo {
		GameObject* gameObject;
	};

	class CollisionComponent final : public  BaseComponent
	{
	public:

		typedef std::function<void(HitInfo* hit)> CollisionCallback;

		CollisionComponent(dae::GameObject* go, const SDL_Rect& rect);

		~CollisionComponent() override;

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		

		void Disable() { m_IsEnabled = false; };
		void Enable() { m_IsEnabled = true; };

		void SetCollisionCallback(CollisionCallback callback);
		void OnTrigger(HitInfo* hit);

	private:
		bool m_IsEnabled = true;
		SDL_Rect m_Rect;

		HitInfo* m_Info;
		CollisionCallback m_CollisionCallback;

		bool HandleCollision(CollisionComponent* other);
		
	};

}

