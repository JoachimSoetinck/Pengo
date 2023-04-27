#include "PengoComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "SpriteCompenent.h"
#include "WallManagers.h"
#include "WallComponent.h"
#include "GameInfo.h"
#include "GameObject.h"

dae::PengoComponent::PengoComponent(GameObject* gameObject) : BaseComponent(gameObject),
m_RigidBody{ GetGameObject()->GetComponent<RigidBody>() }
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
	std::cout << "Push \m";
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

	switch (state)
	{
	case dae::PengoComponent::PengoState::Left:
		newPos.x -= 25;
		break;

	case dae::PengoComponent::PengoState::Right:
		newPos.x += 25;
		break;
	case dae::PengoComponent::PengoState::Up:
		newPos.y -= 25;

		break;
	case dae::PengoComponent::PengoState::Down:
	{

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
