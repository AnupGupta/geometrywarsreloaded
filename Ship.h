#ifndef SHIP_H
#define SHIP_H

#include "Movable.h"
#include "EventListener.h"


class Ship : public Movable, public EventListener
{
public:

	Ship();
	virtual ~Ship();

	virtual bool Init() = 0;
	virtual void Shutdown() = 0;
	virtual void Reset();
	virtual void Update() = 0;
	
	virtual ObjectType GetType() const
	{
		return kObjectShip;
	}

	float GetTargetRotation() const
	{
		return m_fTargetRotation;
	}

	void SetTargetRotation(float rotation)
	{
		m_fTargetRotation = rotation;
	}

protected:

	float m_fTargetRotation;

	virtual void SetInterested();
	virtual void HandleEvent(Event* const e);



};

#endif