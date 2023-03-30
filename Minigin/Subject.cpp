#include "Subject.h"
#include "GameObject.h"


dae::Subject::~Subject()
{
	
}

void dae::Subject::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	for (size_t i = 0; i < m_Observers.size(); ++i) {

		if (m_Observers[i] == observer) {
			m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer));
		}
	}
}

void dae::Subject::Notify(Event eventType, GameObject* object)
{
	for (auto observer : m_Observers) {
		observer->OnNotify(eventType, object);
	}
}
