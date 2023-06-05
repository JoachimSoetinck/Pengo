#include "CollisionComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "CollisionManager.h"

dae::CollisionComponent::CollisionComponent(dae::GameObject* go, const SDL_Rect& rect) :BaseComponent(go),
m_Rect{0,0,rect.w, rect.h}, m_Info{new HitInfo()}
{
	
	CollisionManager::GetInstance().AddComponent(this);
}

dae::CollisionComponent::~CollisionComponent()
{
	CollisionManager::GetInstance().RemoveComponent(this);

	delete m_Info;
	m_Info = nullptr;
}

void dae::CollisionComponent::Initialize()
{
	
}

void dae::CollisionComponent::Update()
{
	
}

void dae::CollisionComponent::Render() const
{
	if (m_IsEnabled)
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 0);
		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &m_Rect);
	}
	
}

void dae::CollisionComponent::FixedUpdate()
{
	const auto pos = GetGameObject()->GetLocalPosition();
	m_Rect.x =  static_cast<int>(pos.x);
	m_Rect.y = static_cast<int>(pos.y);

	auto collisions = CollisionManager::GetInstance().GetCollisionsBoxes();

	for (auto collision : collisions)
	{
		if (collision->m_IsEnabled)
		{
			//skipping same collision
			if (collision == this)
				continue;

			if (HandleCollision(collision))
			{

				m_Info->gameObject = collision->GetGameObject();
				OnTrigger(m_Info);
			}
		}
		
	}
}

void dae::CollisionComponent::SetCollisionCallback(CollisionCallback callback)
{
	m_CollisionCallback = callback;
}

void dae::CollisionComponent::OnTrigger(HitInfo* hit)
{
	if (m_CollisionCallback)
	{
		m_CollisionCallback(hit);
	}
}

bool dae::CollisionComponent::HandleCollision(CollisionComponent* other)
{
	if (m_IsEnabled == false)
		return false;

	if ((m_Rect.x + m_Rect.w) <= other->m_Rect.x || (other->m_Rect.x + other->m_Rect.w) <= m_Rect.x)
	{
		return false;
	}

	if (m_Rect.y >= (other->m_Rect.y + other->m_Rect.h) || other->m_Rect.y >= (m_Rect.y + m_Rect.h))
	{
		return false;
	}

	return true;
}
