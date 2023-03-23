#include "MiniginPCH.h"
#include "RigidBody.h"

#include "GameObject.h"
#include "Timer.h"

dae::RigidBody::RigidBody(dae::GameObject* object, const glm::vec2& speed) :
	BaseComponent(object),
	m_MovementSpeed{ speed }
{
}

void dae::RigidBody::Render() const
{

}

void dae::RigidBody::Move(const glm::vec2& direction)
{
	if(direction != glm::vec2{0,0})
	{
		m_Velocity.x = direction.x * dae::Time::GetInstance().GetDeltaTime() * m_MovementSpeed.x;
		m_Velocity.y = direction.y * dae::Time::GetInstance().GetDeltaTime() * m_MovementSpeed.y;

		auto newPos = GetGameObject()->GetLocalPosition();
		newPos.x += m_Velocity.x;
		newPos.y += m_Velocity.y;


		GetGameObject()->SetPosition(newPos.x, newPos.y);
	}

}
