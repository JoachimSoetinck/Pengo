#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	class Observer;
	class GameObject;

	class Subject
	{
	public:
		Subject() = default;
		~Subject();
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(Event eventType, GameObject* object);

	private:
		std::vector<Observer*> m_Observers;
	};
}