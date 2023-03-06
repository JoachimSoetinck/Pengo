#pragma once
#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "GameObject.h"
#include <memory.h>
#include <string>

#include "SDL_rect.h"


namespace dae
{
	class RenderComponent final : public BaseComponent
	{
	public:
		//Render Needs file to load

		RenderComponent(dae::GameObject* go, const std::string& file, bool isVisible = true);



		virtual ~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;
		void FixedUpdate()  override;

		void SetTexture(const std::string& file);
		void SetVisibility(bool isVisible) { m_isVisible = isVisible; }
		int GetWidth() const;
		int GetHeight() const;

		Texture2D* GetTexture() const { return m_Texture; }
		SDL_Rect GetSRCRect() const { return m_srcRect; }

		void SetRect(const SDL_Rect& rect);

		

	private:
		Texture2D* m_Texture;

		bool m_isVisible{ true };
		int m_Width{};
		int m_Height{};
		float rotationAngle = 0.0f;

		SDL_Rect m_srcRect;

	};
}

