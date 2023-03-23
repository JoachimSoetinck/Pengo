#include "Command.h"
#include "MiniginPCH.h"
#include "GameObject.h"



dae::TestCommand::TestCommand()
{
}

void dae::TestCommand::Execute()
{
	std::cout << "test\n";
}



dae::MoveCommand::MoveCommand(std::shared_ptr<GameObject> obj, PengoComponent::PengoState movingDirection): m_pObject{obj}, m_PlayerState{movingDirection}
{
}

void dae::MoveCommand::Execute()
{
	if(m_pObject->GetComponent<dae::PengoComponent>())
	m_pObject->GetComponent<dae::PengoComponent>()->SetState(m_PlayerState);
}