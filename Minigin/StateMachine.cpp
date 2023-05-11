
#include "StateMachine.h"
#include "MiniginPCH.h"
#include "StateMachine.h"
#include "GameObject.h"
#include "BaseState.h"

dae::StateMachine::StateMachine(BaseState* startState) : m_state(startState)
{
}

dae::StateMachine::~StateMachine()
{
	delete m_state;
	m_state = nullptr;
}

void dae::StateMachine::Initialize(GameObject* gameObject)
{
	m_state->Enter(gameObject);
}

void dae::StateMachine::Update(GameObject* gameobject)
{
	BaseState* state = m_state->Update(gameobject);

	if (state != nullptr)
	{
		m_state->Exit(gameobject);
		delete m_state;

		m_state = state;
		m_state->Enter(gameobject);
	}
}

void dae::StateMachine::SetState(GameObject* gameobject, BaseState* state)
{
	m_state->Exit(gameobject);
	delete m_state;
	m_state = state;
	state->Enter(gameobject);
}
