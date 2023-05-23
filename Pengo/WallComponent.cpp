#include "WallComponent.h"
#include "GameObject.h"
#include "SpriteCompenent.h"
#include "WallManagers.h"
#include "RigidBody.h"
#include "CollisionComponent.h"
#include "Helpers.h"
#include "GameInfo.h"
#include "WallStates.h"
#include "StateMachine.h"
#include "BaseState.h"


dae::WallComponent::WallComponent(dae::GameObject* go, int nr, WallType wallType) : BaseComponent(go),
m_WallType{ wallType }, m_SpriteComp{ nullptr }, m_Nr{ nr },
m_StateMachine{ new StateMachine(new WallState()) }, m_IsSpawner{ false }
{
	m_Center = m_pGameObject->GetLocalPosition();
}

dae::WallComponent::~WallComponent()
{
	delete m_StateMachine;
	m_StateMachine = nullptr;
}

void dae::WallComponent::Initialize()
{
	m_StateMachine->Initialize(m_pGameObject);

	dae::WallManager::GetInstance().AddComponent(this);


	if (m_pGameObject->GetComponent<SpriteComponent>())
	{
		m_SpriteComp = m_pGameObject->GetComponent<SpriteComponent>();

		switch (m_WallType)
		{
		case WallType::Border:
		{
			m_StateMachine->SetState(m_pGameObject, new BorderState());
			break;
		}
		case WallType::MoveableWall:
		{
			m_StateMachine->SetState(m_pGameObject, new WallState());
			break;
		}

		case WallType::EnemySpawn:
		{
			m_StateMachine->SetState(m_pGameObject, new EnemySpawnStartState());
			break;
		}
		case WallType::Ground:
		{
			m_StateMachine->SetState(m_pGameObject, new GroundState());
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
	m_StateMachine->Update(m_pGameObject);
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

	if (m_IsMoving && m_pGameObject->GetComponent<RigidBody>())
	{
		switch (m_PushDirection)
		{
		case dae::MovementDirection::Left:
			m_pGameObject->GetComponent<RigidBody>()->Move({ -1,0 });
			break;
		case dae::MovementDirection::Right:
			m_pGameObject->GetComponent<RigidBody>()->Move({ 1,0 });
			break;
		case dae::MovementDirection::Up:
			m_pGameObject->GetComponent<RigidBody>()->Move({ 0,-1 });
			break;
		case dae::MovementDirection::Down:
			m_pGameObject->GetComponent<RigidBody>()->Move({ 0,1 });
			break;
		case dae::MovementDirection::None:
			m_pGameObject->GetComponent<RigidBody>()->Move({ 0,0 });
		default:
			break;
		}
	}
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
	m_PushDirection = directio;
}

void dae::WallComponent::OnHit(HitInfo* hit)
{
	if (!m_IsMoving)
		return;

	


	m_SpriteComp->SetVisibility(false);
	m_pGameObject->GetComponent<CollisionComponent>()->Disable();

	glm::ivec2 previousWallPos = { hit->gameObject->GetLocalPosition().x, hit->gameObject->GetLocalPosition().y };

	dae::GameInfo::GetInstance().GetPlayerSize().w;
	switch (m_PushDirection)
	{
	case dae::MovementDirection::Left:
		previousWallPos.x += dae::GameInfo::GetInstance().GetPlayerSize().w;;
		break;
	case dae::MovementDirection::Right:
		previousWallPos.x -= dae::GameInfo::GetInstance().GetPlayerSize().w;;
		break;
	case dae::MovementDirection::Up:
		previousWallPos.y += dae::GameInfo::GetInstance().GetPlayerSize().w;;
		break;
	case dae::MovementDirection::Down:
		previousWallPos.y -= dae::GameInfo::GetInstance().GetPlayerSize().w;;
		break;
	default:
		break;
	}

	auto w = WallManager::GetInstance().FindWall(previousWallPos);

	if (w)
	{

		if (m_IsSpawner)
		{
			w->m_IsSpawner = m_IsSpawner;
		}
		w->m_StateMachine->SetState(w->m_pGameObject, new WallState());
		w->m_pGameObject->GetComponent<CollisionComponent>()->Enable();
		w->m_WallType = WallType::MoveableWall;





	}




}

void dae::WallComponent::MakeSpawner()
{
	m_IsSpawner = true;
	m_WallType = WallType::EnemySpawn;
	m_StateMachine->SetState(m_pGameObject, new EnemySpawnStartState());
}

void dae::WallComponent::BreakWall()
{
	m_StateMachine->SetState(m_pGameObject, new BreakingState());
}



