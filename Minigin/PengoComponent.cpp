#include "PengoComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"

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
}

void dae::PengoComponent::Update()
{
}

void dae::PengoComponent::Render() const
{
}

void dae::PengoComponent::FixedUpdate()
{
	if (m_RigidBody)
	{
		if (m_direction != glm::ivec2{ 0,0 })
			m_RigidBody->Move(m_direction);
	}

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


	switch (m_currentState)
	{
	case PengoState::Idle:
	{
		m_direction = { 0,0 };

		break;
	}

	case PengoState::Left:
	{
		m_direction = { -1,0 };

		break;
	}

	case PengoState::Right:
	{
		m_direction = { 1,0 };


		break;
	}

	case PengoState::Up:
	{
		m_direction = { 0,-1 };
		break;
	}

	case PengoState::Down:
	{
		m_direction = { 0,1 };
		break;
	}
	case PengoState::Pushing:
	{

		break;
	}
	default:
		break;
	}
}
