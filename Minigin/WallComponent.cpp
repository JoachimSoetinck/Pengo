#include "WallComponent.h"
#include "GameObject.h"
#include "SpriteCompenent.h"
#include "WallManagers.h"
#include "RigidBody.h"
#include "CollisionComponent.h"
#include "Helpers.h"


dae::WallComponent::WallComponent(dae::GameObject* go, int nr, WallType wallType) : BaseComponent(go),
m_WallType{ wallType }, m_SpriteComp{ nullptr }, m_Nr{ nr }
{

}

void dae::WallComponent::Initialize()
{
	SDL_Rect src = { 0,0,30,30 };
	dae::WallManager::GetInstance().AddComponent(this);

	auto  collision = m_pGameObject->GetComponent<CollisionComponent>();
	if (m_WallType == WallType::Ground)
		collision->Disable();


	if (m_pGameObject->GetComponent<SpriteComponent>())
	{
		m_SpriteComp = m_pGameObject->GetComponent<SpriteComponent>();

		switch (m_WallType)
		{
		case WallType::Border:
		{
			src = { 0,0,16,24 };
			m_SpriteComp->SetSprite(Sprite("Wall.png", 1, 1, src));
			break;
		}
		case WallType::MoveableWall:
		{
			src = { 0,0,30,30 };
			m_SpriteComp->SetSprite(Sprite("Blocks.png", 1, 1, src));

			break;
		}

		case WallType::EnemySpawn:
		{
			break;
		}
		case WallType::Ground:
		{

			m_SpriteComp->SetVisibility(false);
			break;
		}
		default:
			break;
		}
	}

	CollisionComponent::CollisionCallback callback = [&](HitInfo* hit) { this->OnHit(hit); };
	GetGameObject()->GetComponent<CollisionComponent>()->SetCollisionCallback(callback);

	m_Center = m_pGameObject->GetLocalPosition();
}

void dae::WallComponent::Update()
{
	m_Center = m_pGameObject->GetLocalPosition();
}

void dae::WallComponent::Render() const
{

}

void dae::WallComponent::FixedUpdate()
{
	HandleMovement();
}

void dae::WallComponent::HandleMovement()
{
	SDL_Rect pushblock = { m_pGameObject->GetLocalPosition().x, m_pGameObject->GetLocalPosition().y - 3 , 20,20 };

	auto w = dae::WallManager::GetInstance().FindCollisionWithWall(this);


	if (m_IsMoving && m_pGameObject->GetComponent<RigidBody>())
	{
		switch (m_pushDirection)
		{
		case dae::MovementDirection::Left:
			//pushblock = { m_pGameObject->GetLocalPosition().x - 25, m_pGameObject->GetLocalPosition().y };
			m_pGameObject->GetComponent<RigidBody>()->Move({ -1,0 });
			break;
		case dae::MovementDirection::Right:
			//pushblock = { m_pGameObject->GetLocalPosition().x + 25, m_pGameObject->GetLocalPosition().y };
			m_pGameObject->GetComponent<RigidBody>()->Move({ 1,0 });
			break;
		case dae::MovementDirection::Up:
			//pushblock = { m_pGameObject->GetLocalPosition().x , m_pGameObject->GetLocalPosition().y +25};
			m_pGameObject->GetComponent<RigidBody>()->Move({ 0,-1 });
			break;
		case dae::MovementDirection::Down:
			//pushblock = { m_pGameObject->GetLocalPosition().x + 25, m_pGameObject->GetLocalPosition().y -25 };
			m_pGameObject->GetComponent<RigidBody>()->Move({ 0,1 });
			break;
		default:
			break;
		}
	}

	//if (m_IsMoving)
	//{
	//	if (w && w->GetType() == WallType::MoveableWall )
	//	{
	//		this->m_IsMoving == false;
	//		m_pGameObject->SetPosition(w->GetCenter().x, w->GetCenter().y);
	//	}
	//}

}



bool dae::WallComponent::IsPointInWall(glm::ivec2 p)
{

	SDL_Rect rect = { m_pGameObject->GetLocalPosition().x,m_pGameObject->GetLocalPosition().y,
		m_SpriteComp->GetDestRect().w,m_SpriteComp->GetDestRect().x };



	if (p.x > rect.x && p.x < rect.x + rect.w && p.y > rect.y && p.y < rect.y + rect.h)
		return true;

	return false;

}

void dae::WallComponent::EnableMovement(MovementDirection directio)
{
	m_IsMoving = true;
	m_pushDirection = directio;
}

void dae::WallComponent::OnHit(HitInfo* hit)
{
	DisableMovement();

	

}
