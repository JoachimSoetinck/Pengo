#include "CollisionComponent.h"
#include "Renderer.h"
#include "GameObject.h"

dae::CollisionComponent::CollisionComponent(dae::GameObject* go, const SDL_Rect& rect) :BaseComponent(go),
m_Rect{0,0,rect.w, rect.h}
{

}

void dae::CollisionComponent::Update()
{
}

void dae::CollisionComponent::Render() const
{
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),255, 255, 255, 0);
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &m_Rect);
}

void dae::CollisionComponent::FixedUpdate()
{
	const auto pos = GetGameObject()->GetLocalPosition();
	m_Rect.x =  static_cast<int>(pos.x);
	m_Rect.y = static_cast<int>(pos.y);
}
