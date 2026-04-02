#pragma once

#include "IObserver.h"
#include <vector>

class Subject
{
public:
	void AddObserver(IObserver* observer);
	void RemoveObserver(IObserver* observer);
	void NotifyObservers(unsigned int event);

private:
	std::vector<IObserver*> m_observers;
};