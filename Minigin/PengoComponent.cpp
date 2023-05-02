#include "PengoComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "SpriteCompenent.h"
#include "WallManagers.h"
#include "WallComponent.h"
#include "GameInfo.h"
#include "GameObject.h"
#include "CollisionComponent.h"

dae::PengoComponent::PengoComponent(GameObject* gameObject) : BaseComponent(gameObject),
m_RigidBody{ GetGameObject()->GetComponent<RigidBody>() },
m_playerSize{ GetGameObject()->GetComponent<SpriteComponent>()->GetDestRect().w,GetGameObject()->GetComponent<SpriteComponent>()->GetDestRect().h }
{
	m_PlayerSubject = std::make_unique<Subject>();

}

dae::PengoComponent::~PengoComponent()
{
	for (auto o : m_PlayerSubject->GetObservers())
	{
		m_PlayerSubject->RemoveObserver(o);
	}
}




void dae::PengoComponent::Push()
{

	//center of player
	glm::ivec2 pushblock = { m_pGameObject->GetLocalPosition().x , m_pGameObject->GetLocalPosition().y };
	MovementDirection direction{};
	switch (m_currentState)
	{
	case dae::PengoComponent::PengoState::Left:
		pushblock.x -= 25;
		direction = MovementDirection::Left;
		break;
	case dae::PengoComponent::PengoState::Right:
		direction = MovementDirection::Right;
		pushblock.x += 25;
		break;
	case dae::PengoComponent::PengoState::Up:
		direction = MovementDirection::Up;
		pushblock.y -= 25;
		break;
	case dae::PengoComponent::PengoState::Down:
	{
		direction = MovementDirection::Down;
		pushblock.y += 25;
		break;
	}
	default:
		break;
	}

	auto w = dae::WallManager::GetInstance().FindWall(pushblock);
	if (w && w->GetType() == WallComponent::WallType::MoveableWall)
	{
		auto go = std::make_shared<dae::GameObject>();
		go = std::make_shared<dae::GameObject>();
		go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Wall.png", 1, 1, {0,0,0,0}), dae::GameInfo::GetInstance().GetPlayerSize(), 0.8f));
		go->AddComponent(new dae::WallComponent(go.get(), dae::WallManager::GetInstance().GetGroundPieces().size(), dae::WallComponent::WallType::Ground));
		go->AddComponent(new dae::CollisionComponent(go.get(), dae::GameInfo::GetInstance().GetCollisionSize()));
		go->SetPosition(pushblock.x, pushblock.y);
		dae::GameInfo::GetInstance().GetGridObj()->AddChild(go); 
		go->Initalize();
		w->EnableMovement(direction);
	}

}



void dae::PengoComponent::AddObserver(Observer* obj)
{
	m_PlayerSubject->AddObserver(obj);
}

void dae::PengoComponent::Initialize()
{
	auto startblock = dae::WallManager::GetInstance().FindWall(m_StartBlock);

	m_pGameObject->SetPosition(startblock->GetCenter().x, startblock->GetCenter().y);
	m_currentBlock = m_StartBlock;
}

void dae::PengoComponent::Update()
{

}

void dae::PengoComponent::Render() const
{
}

void dae::PengoComponent::FixedUpdate()
{


}

void dae::PengoComponent::Start()
{
	m_PlayerSubject->Notify(Event::PlayerStart, this->GetGameObject());
}

void dae::PengoComponent::Die()
{
	if (m_nrOfLives > 0)
		--m_nrOfLives;
	m_PlayerSubject->Notify(Event::PlayerDied, this->GetGameObject());
}

void dae::PengoComponent::GivePoints(int score)
{
	m_score += score;
	m_PlayerSubject->Notify(Event::GivePoints, this->GetGameObject());
}

void dae::PengoComponent::SetState(PengoState state)
{
	m_currentState = state;
}

void dae::PengoComponent::Move(PengoState state)
{
	glm::ivec2 newPos = { m_pGameObject->GetLocalPosition().x, m_pGameObject->GetLocalPosition().y };
	SetState(state);
	SDL_Rect src{ 0,0,16,16 };
	switch (state)
	{
	case dae::PengoComponent::PengoState::Left:
		src = { 32,0,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		newPos.x -= 25;
		break;

	case dae::PengoComponent::PengoState::Right:
		src = { 96,0,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		newPos.x += 25;
		break;
	case dae::PengoComponent::PengoState::Up:
		src = { 64,0,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		newPos.y -= 25;

		break;
	case dae::PengoComponent::PengoState::Down:
	{
		src = { 0,0,16,16 };
		m_pGameObject->GetComponent<SpriteComponent>()->SetSprite(Sprite("Pengo.png", 2, 1, src));
		newPos.y += 25;
		break;
	}
	default:
		break;
	}


	auto w = dae::WallManager::GetInstance().FindWall(newPos);
	if (w && w->GetType() == WallComponent::WallType::Ground)
		m_pGameObject->SetPosition(newPos.x, newPos.y);



}
