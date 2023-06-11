#include "SnoBeeCompontent.h"
#include "SpriteCompenent.h"
#include "WallManagers.h"
#include "WallComponent.h"
#include "RigidBody.h"
#include "GameInfo.h"
#include "CollisionComponent.h"
#include "EnemyManager.h"
#include "SimpleAIComponent.h"
#include <ServiceLocator.h>

dae::SnoBeeCompontent::SnoBeeCompontent(GameObject* gameObject, int startBlock) :BaseComponent(gameObject),
m_RigidBody{ GetGameObject()->GetComponent<RigidBody>() },
m_PlayerSize{ GetGameObject()->GetComponent<SpriteComponent>()->GetDestRect().w,GetGameObject()->GetComponent<SpriteComponent>()->GetDestRect().h },
m_StartBlock{ startBlock }
{
	m_PlayerSubject = std::make_unique<Subject>();
	EnemyManager::GetInstance().AddComponent(this);


	if (m_pGameObject->GetComponent<CollisionComponent>())
	{
		CollisionComponent::CollisionCallback callback = [&](HitInfo* hit) { this->OnHit(hit); };
		GetGameObject()->GetComponent<CollisionComponent>()->SetCollisionCallback(callback);
	}
}

dae::SnoBeeCompontent::~SnoBeeCompontent()
{
	EnemyManager::GetInstance().RemoveComponent(this);
}

void dae::SnoBeeCompontent::AddObserver(Observer* obj)
{
	for (auto o : m_PlayerSubject->GetObservers())
	{
		m_PlayerSubject->RemoveObserver(o);
	}
}

void dae::SnoBeeCompontent::Initialize()
{
	Sleep(1000);
	auto startblock = dae::WallManager::GetInstance().FindWall(m_StartBlock);

	if (startblock)
		m_pGameObject->SetPosition(startblock->GetCenter().x, startblock->GetCenter().y);

	m_CurrentBlock = m_StartBlock;




}

void dae::SnoBeeCompontent::Update()
{
}

void dae::SnoBeeCompontent::Render() const
{
}

void dae::SnoBeeCompontent::FixedUpdate()
{
}

void dae::SnoBeeCompontent::Start()
{
}

void dae::SnoBeeCompontent::Die()
{

}

void dae::SnoBeeCompontent::Push()
{
	glm::ivec2 pushblock = { m_pGameObject->GetLocalPosition().x , m_pGameObject->GetLocalPosition().y };

	switch (m_CurrentState)
	{
	case dae::SnoBeeCompontent::SnobeeState::Left:
	{
		pushblock.x -= dae::GameInfo::GetInstance().GetPlayerSize().w;
		break;
	}
	case dae::SnoBeeCompontent::SnobeeState::Right:
		pushblock.x += dae::GameInfo::GetInstance().GetPlayerSize().w;
		break;
	case dae::SnoBeeCompontent::SnobeeState::Up:
		pushblock.y -= dae::GameInfo::GetInstance().GetPlayerSize().w;
		break;
	case dae::SnoBeeCompontent::SnobeeState::Down:
	{
		pushblock.y += dae::GameInfo::GetInstance().GetPlayerSize().w;
		break;
	}
	default:
		break;
	}

	WallComponent* w;

	if (m_pGameObject->GetComponent<SimpleAIComponent>())
		w = dae::WallManager::GetInstance().FindWallAI(pushblock);
	else
		w = dae::WallManager::GetInstance().FindWall(pushblock);

	if (w && w->GetType() == WallComponent::WallType::MoveableWall)
	{
		w->BreakWall();
	}
}

void dae::SnoBeeCompontent::SetState(SnobeeState state)
{
	m_CurrentState = state;
	SDL_Rect src{ 0,0,16,16 };
	int startHeight = m_pGameObject->GetComponent<SpriteComponent>()->GetSprite().SrcRect.y;

	switch (state)
	{
	case dae::SnoBeeCompontent::SnobeeState::Left:
		src = { 32,startHeight,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		break;

	case dae::SnoBeeCompontent::SnobeeState::Right:
		src = { 96,startHeight,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		break;
	case dae::SnoBeeCompontent::SnobeeState::Up:
		src = { 64,startHeight,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));

		break;
	case dae::SnoBeeCompontent::SnobeeState::Down:
	{
		src = { 0,startHeight,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		break;
	}
	default:
		break;
	}
}

void dae::SnoBeeCompontent::Move(SnobeeState state)
{
	glm::ivec2 newPos = { m_pGameObject->GetLocalPosition().x, m_pGameObject->GetLocalPosition().y };

	SetState(state);

	switch (state)
	{
	case dae::SnoBeeCompontent::SnobeeState::Left:
		newPos.x -= dae::GameInfo::GetInstance().GetPlayerSize().w;;
		break;

	case dae::SnoBeeCompontent::SnobeeState::Right:

		newPos.x += dae::GameInfo::GetInstance().GetPlayerSize().w;;
		break;
	case dae::SnoBeeCompontent::SnobeeState::Up:

		newPos.y -= dae::GameInfo::GetInstance().GetPlayerSize().w;;

		break;
	case dae::SnoBeeCompontent::SnobeeState::Down:
	{
		newPos.y += dae::GameInfo::GetInstance().GetPlayerSize().w;;
		break;
	}
	default:
		break;
	}


	auto w = dae::WallManager::GetInstance().FindWall(newPos);

	if (w && w->GetType() == WallComponent::WallType::Ground)
		m_pGameObject->SetPosition(newPos.x, newPos.y);


}

void dae::SnoBeeCompontent::OnHit(HitInfo* hit)
{
	if (m_pGameObject->GetComponent<SimpleAIComponent>() && hit->gameObject->GetComponent<WallComponent>())
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		auto currentPos = m_pGameObject->GetLocalPosition();
		int offset = 2;

		switch (m_CurrentState)
		{
		case dae::SnoBeeCompontent::SnobeeState::Left:
			m_pGameObject->SetPosition(currentPos.x + offset, currentPos.y);
			break;
		case dae::SnoBeeCompontent::SnobeeState::Right:
			m_pGameObject->SetPosition(currentPos.x - offset, currentPos.y);
			break;
		case dae::SnoBeeCompontent::SnobeeState::Up:
			m_pGameObject->SetPosition(currentPos.x, currentPos.y - offset);
			break;
		case dae::SnoBeeCompontent::SnobeeState::Down:
			m_pGameObject->SetPosition(currentPos.x, currentPos.y + offset);
			break;
		default:
			break;
		}

		int randomNumber = std::rand() % 4;
		int pushnumber = std::rand() % 3;

		if (pushnumber == 1 && hit->gameObject->GetComponent<WallComponent>()->GetType() == dae::WallComponent::WallType::MoveableWall)
		{
			hit->gameObject->GetComponent<WallComponent>()->BreakWall();
			dae::ServiceLocator::GetSoundSystem()->PlaySound(4);
		}


		m_CurrentState = (SnobeeState)randomNumber;
	}
}
