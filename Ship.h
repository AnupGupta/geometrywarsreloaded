#ifndef SHIP_H
#define SHIP_H

#include "EventListener.h"
#include "GameObject.h"

class Ship : public GameObject, public EventListener
{
public:

	Ship();
	virtual ~Ship();

	virtual bool Init();
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