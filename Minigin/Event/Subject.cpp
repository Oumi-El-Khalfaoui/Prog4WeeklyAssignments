#include "Subject.h"
#include <algorithm>

void Subject::AddObserver(IObserver* observer)
{
	m_observers.push_back(observer);
}

void Subject::RemoveObserver(IObserver* observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void Subject::NotifyObservers(unsigned int event)
{
	for (auto* observer : m_observers)
	{
		observer->Notify(event);
	}
}
