#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include <memory>

namespace dae {

	class TextComponent final : public  BaseComponent
	{
	public:
		TextComponent(dae::GameObject* go, const std::string& text, const std::shared_ptr<Font>& font);
		TextComponent(dae::GameObject* go);
		~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		SDL_Point GetDimensions() const {
			int width, height;
			SDL_QueryTexture(m_TextTexture->GetSDLTexture(), NULL, NULL, &width, &height);
			return{ width, height };
		}

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		void SetPosition(glm::vec3 location);
		void SetColor(SDL_Color color)
		{
			m_Color = color;
			m_NeedsUpdate = true;
		};

		glm::ivec2 GetPosition() const { return { m_Transform.GetLocalPosition().x, m_Transform.GetLocalPosition().y }; }

		std::shared_ptr<Texture2D> GetTexture() const;
		SDL_Color GetColor() const { return m_Color; }

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		SDL_Color m_Color;
		std::shared_ptr<Texture2D> m_TextTexture;

		Transform m_Transform;

	};
}


