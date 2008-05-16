#ifndef ADDOBJECTEVENT_H
#define ADDOBJECTEVENT_H

#include "Event.h"

class GameObject;

class AddObjectEvent : public Event
{
public:

	AddObjectEvent(GameObject* object);
	~AddObjectEvent();

	GameObject* m_pGameObject;

};

#endif