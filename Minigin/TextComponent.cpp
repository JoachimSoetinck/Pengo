#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include <SDL_ttf.h>

#include "GameObject.h"
#include "ResourceManager.h"

dae::TextComponent::TextComponent(dae::GameObject* pGO, const std::string& text, const std::shared_ptr<Font>& font)
	:BaseComponent(pGO)
	, m_NeedsUpdate(true), m_Text(text), m_Font(font), m_TextTexture(nullptr), m_Color({ 255,255,255 })
	, m_Transform(pGO)
{
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_TextTexture = std::make_shared<Texture2D>(texture);
	m_NeedsUpdate = false;
}

dae::TextComponent::TextComponent(dae::GameObject* pGO)
	: BaseComponent(pGO)
	, m_NeedsUpdate(true), m_Text(" "), m_Font(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)), m_TextTexture(nullptr), m_Color({ 255,255,255 })
	, m_Transform(pGO)
{
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_TextTexture = std::make_shared<Texture2D>(texture);
	m_NeedsUpdate = false;
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = m_pGameObject->GetLocalPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y,m_pGameObject->GetRotation());
	}
}

void dae::TextComponent::FixedUpdate()
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_Font = font;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(glm::vec3 location)
{
	m_Transform.SetLocalPosition(location.x, location.y, 0.0f);
}

std::shared_ptr<dae::Texture2D> dae::TextComponent::GetTexture() const
{
	int width, height;
	SDL_QueryTexture(m_TextTexture->GetSDLTexture(), NULL, NULL, &width, &height);

	return m_TextTexture;
}
