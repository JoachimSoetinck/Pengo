#include "SnoBeeCompontent.h"
#include "SpriteCompenent.h"
#include "WallManagers.h"
#include "WallComponent.h"
#include "RigidBody.h"
#include "GameInfo.h"
#include "CollisionComponent.h"

dae::SnoBeeCompontent::SnoBeeCompontent(GameObject* gameObject, int startBlock) :BaseComponent(gameObject),
m_RigidBody{ GetGameObject()->GetComponent<RigidBody>() },
m_PlayerSize{ GetGameObject()->GetComponent<SpriteComponent>()->GetDestRect().w,GetGameObject()->GetComponent<SpriteComponent>()->GetDestRect().h },
m_StartBlock{ startBlock }
{
	m_PlayerSubject = std::make_unique<Subject>();
}

dae::SnoBeeCompontent::~SnoBeeCompontent()
{
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


	auto w = dae::WallManager::GetInstance().FindWall(pushblock);



	if (w && w->GetType() == WallComponent::WallType::MoveableWall)
	{
		w->BreakWall();
	}
}

void dae::SnoBeeCompontent::SetState(SnobeeState state)
{
	m_CurrentState = state;
}

void dae::SnoBeeCompontent::Move(SnobeeState state)
{
	glm::ivec2 newPos = { m_pGameObject->GetLocalPosition().x, m_pGameObject->GetLocalPosition().y };
	SetState(state);
	SDL_Rect src{ 0,0,16,16 };

	int startHeight = m_pGameObject->GetComponent<SpriteComponent>()->GetSprite().SrcRect.y;
	switch (state)
	{
	case dae::SnoBeeCompontent::SnobeeState::Left:
		src = { 32,startHeight,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		newPos.x -= dae::GameInfo::GetInstance().GetPlayerSize().w;;
		break;

	case dae::SnoBeeCompontent::SnobeeState::Right:
		src = { 96,startHeight,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		newPos.x += dae::GameInfo::GetInstance().GetPlayerSize().w;;
		break;
	case dae::SnoBeeCompontent::SnobeeState::Up:
		src = { 64,startHeight,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		newPos.y -= dae::GameInfo::GetInstance().GetPlayerSize().w;;

		break;
	case dae::SnoBeeCompontent::SnobeeState::Down:
	{
		src = { 0,startHeight,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
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
