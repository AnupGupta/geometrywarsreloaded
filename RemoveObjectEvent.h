#ifndef REMOVEOBJECTEVENT_H
#define REMOVEOBJECTEVENT_H

#include "Event.h"

class GameObject;

class RemoveObjectEvent : public Event
{
public:

	RemoveObjectEvent(GameObject* object);
	~RemoveObjectEvent();

	GameObject* m_pGameObject;

};

#endif