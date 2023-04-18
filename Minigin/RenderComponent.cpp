#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include <memory.h>


dae::RenderComponent::RenderComponent(dae::GameObject* go, const std::string& file, bool isVisible) :BaseComponent(go)
{
	SetTexture(file);
}

void dae::RenderComponent::Initialize()
{
}

void dae::RenderComponent::Update()
{

}

void dae::RenderComponent::Render() const
{
	if (m_isVisible)
	{
		const glm::vec3 pos = m_pGameObject->GetLocalPosition();
		//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);

		if (m_srcRect.h <= 0 || m_srcRect.w <= 0)
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_pGameObject->GetRotation());
		}

		else
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, m_srcRect, pos.x, pos.y, m_pGameObject->GetRotation());
		}
	}

}

void dae::RenderComponent::FixedUpdate()
{
}

void dae::RenderComponent::SetTexture(const std::string& file)
{
	if (file.size() > 0)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(file);

		//setting Width and height
		if (m_Texture != nullptr)
		{
			Uint32 format;
			int access;

			SDL_QueryTexture(m_Texture->GetSDLTexture(), &format, &access, &m_Width, &m_Height);
		}
	}


}

int dae::RenderComponent::GetWidth() const
{
	return m_Width;
}

int dae::RenderComponent::GetHeight() const
{
	return m_Height;
}

void dae::RenderComponent::SetRect(const SDL_Rect& rect)
{
	m_srcRect = rect;
}