#ifndef ADDRENDERABLEEVENT_H
#define ADDRENDERABLEEVENT_H

#include "Event.h"

class Renderable;

class AddRenderableEvent : public Event
{
public:

	AddRenderableEvent(Renderable* object);
	~AddRenderableEvent();

	Renderable* m_pRenderableObject;

};

#endif