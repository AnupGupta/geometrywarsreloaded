#ifndef REMOVERENDERABLEEVENT_H
#define REMOVERENDERABLEEVENT_H

#include "Event.h"

class Renderable;

class RemoveRenderableEvent : public Event
{
public:

	RemoveRenderableEvent(Renderable* object);
	~RemoveRenderableEvent();

	Renderable* m_pRenderableObject;

};

#endif