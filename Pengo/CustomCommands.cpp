#include "CustomCommands.h"
#include <ServiceLocator.h>


dae::MoveCommand::MoveCommand(std::shared_ptr<GameObject> obj, PengoComponent::PengoState movingDirection) : m_pObject{ obj }, m_PlayerState{ movingDirection }
{
}

void dae::MoveCommand::Execute()
{
	if (m_pObject->GetComponent<dae::PengoComponent>())
		m_pObject->GetComponent<dae::PengoComponent>()->Move(m_PlayerState);
}



dae::PushCommand::PushCommand(std::shared_ptr<GameObject> obj) : m_pObject{ obj }
{
}

void dae::PushCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem()->PlaySound(0);
	if (m_pObject->GetComponent<dae::PengoComponent>())
		m_pObject->GetComponent<dae::PengoComponent>()->Push();
}

dae::DieCommand::DieCommand(std::shared_ptr<GameObject> obj) : m_pObject{ obj }
{
}

void dae::DieCommand::Execute()
{
	m_pObject->GetComponent<PengoComponent>()->Die();
}

dae::GivePointsCommand::GivePointsCommand(std::shared_ptr<GameObject> obj, int NrOfPoints) : m_pObject{ obj }
{

}

void dae::GivePointsCommand::Execute()
{
	m_pObject->GetComponent<PengoComponent>()->GivePoints(100);
}
