#pragma once

namespace dae
{
	class BaseState;
	class GameObject;

	class StateMachine final
	{
	public:
		StateMachine(BaseState* startState);
		~StateMachine();

		void Initialize(GameObject* gameObject);
		void Update(GameObject* gameobject);
		void SetState(GameObject* gameobject,BaseState* state);
	private:
		BaseState* m_state;
	};

}


