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
		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);
		void Notify(Event eventType, GameObject* object);

	private:
		std::vector<std::shared_ptr<Observer>> m_Observers;
	};
}