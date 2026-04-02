#pragma once

class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void Notify(unsigned int event) = 0; 
};