#include "CollisionComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "CollisionManager.h"

dae::CollisionComponent::CollisionComponent(dae::GameObject* go, const SDL_Rect& rect) :BaseComponent(go),
m_Rect{0,0,rect.w, rect.h}
{
	

}

dae::CollisionComponent::~CollisionComponent()
{
	CollisionManager::GetInstance().RemoveComponent(this);
}

void dae::CollisionComponent::Initialize()
{
	CollisionManager::GetInstance().AddComponent(this);
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

	auto collisions = CollisionManager::GetInstance().GetCollisionsBoxes();

	for (auto collision : collisions)
	{
		//skipping same collision
		if (collision == this)
			continue;

		if (HandleCollision(collision))
		{
			std::cout << "Hit";

		
		}
	}
}

bool dae::CollisionComponent::HandleCollision(CollisionComponent* other)
{
	if (m_IsEnabled == false)
		return false;

	if ((m_Rect.x + m_Rect.w) < other->m_Rect.x || (other->m_Rect.x + other->m_Rect.w) < m_Rect.x)
	{
		return false;
	}

	if (m_Rect.y > (other->m_Rect.y + other->m_Rect.h) || other->m_Rect.y > (m_Rect.y + m_Rect.h))
	{
		return false;
	}

	return true;
}
