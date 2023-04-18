#include "RotationComponent.h"
#include "GameObject.h"
#include "Timer.h"

dae::RotationComponent::RotationComponent(dae::GameObject* go) :BaseComponent(go),
m_CurrentAngle{ go->GetRotation()}
{
	
}

void dae::RotationComponent::Initialize()
{
}

void dae::RotationComponent::Update()
{
	m_CurrentAngle += m_RotationSpeed * Time::GetDeltaTime();

	m_pGameObject->SetRotation(m_CurrentAngle);
}

void dae::RotationComponent::Render() const
{
	
}

void dae::RotationComponent::FixedUpdate()
{
	
}
