#include "SimpleAIComponent.h"
#include "GameObject.h"
#include "SnoBeeCompontent.h"
#include "RigidBody.h"

dae::SimpleAIComponent::SimpleAIComponent(GameObject* gameObject) : BaseComponent(gameObject), m_Snobee{nullptr},m_RigidBody{nullptr}
{
	if (m_pGameObject->GetComponent<RigidBody>())
		m_RigidBody = m_pGameObject->GetComponent<RigidBody>();

	if (m_pGameObject->GetComponent<SnoBeeCompontent>())
		m_Snobee = m_pGameObject->GetComponent<SnoBeeCompontent>();
}

dae::SimpleAIComponent::~SimpleAIComponent()
{
}

void dae::SimpleAIComponent::Initialize()
{
}

void dae::SimpleAIComponent::Update()
{
	if (m_Snobee == nullptr)
		return;

	switch (m_Snobee->GetState())
	{
	case dae::SnoBeeCompontent::SnobeeState::Down:
		m_RigidBody->Move({ 0,-1 });
		break;

	case dae::SnoBeeCompontent::SnobeeState::Up:
		m_RigidBody->Move({ 0,1 });
		break;

	case dae::SnoBeeCompontent::SnobeeState::Left:
		m_RigidBody->Move({ -1,0 });
		break;

	case dae::SnoBeeCompontent::SnobeeState::Right:
		m_RigidBody->Move({ 1,0 });
		break;

	case dae::SnoBeeCompontent::SnobeeState::Pushing:
		m_RigidBody->Move({ 0,0 });
		break;
	case dae::SnoBeeCompontent::SnobeeState::Idle:

		m_Snobee->SetState(SnoBeeCompontent::SnobeeState::Left);
			break;
	default:
		break;
	}
}

void dae::SimpleAIComponent::Render() const
{
}

void dae::SimpleAIComponent::FixedUpdate()
{
}
