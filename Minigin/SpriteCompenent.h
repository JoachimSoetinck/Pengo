#pragma once
#include "BaseComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Texture2D.h"

namespace dae {
	class SpriteComponent : public dae::BaseComponent
	{
	public:


		SpriteComponent(dae::GameObject* pGameObject, const Sprite& spriteInfo, const SDL_Rect& dstRect, float animationTime = 1, bool isFlipped = false);
		~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetFlip(bool flip);
		void SetVisibility(bool isVisible) { m_isVisible = isVisible; };

		void SetRotation(float angle);
		float GetRotation() const { return m_Rotation; }

		void ResetSprite();
		void SetSprite(Sprite sprite) { m_Sprite = sprite; m_curTimer = 0; m_currentCol = 1; m_currentRow = 1; };
		void SetTimer(float t) { m_AnimationTime = t; };

		Sprite GetSprite()const { return m_Sprite; }
		SDL_Rect GetDestRect() const { return m_DstRect; }
	private:
		void UpdateFrame();

		SDL_Rect m_DstRect{};
		float m_AnimationTime{ 1 };
		bool m_Flip{ false };
		float m_Rotation{};

		Sprite m_Sprite{};

		float m_curTimer{ 0 };
		int m_currentCol{ 1 }, m_currentRow{ 1 };
		bool m_HasEnded{ false };
		bool m_isVisible{ true };
	};

}

