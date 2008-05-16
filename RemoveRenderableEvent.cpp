#include "RemoveRenderableEvent.h"
#include "Renderable.h"

//--------------------------------------------------
/**
* Ctor
*
**/
RemoveRenderableEvent::RemoveRenderableEvent(Renderable* object)
: Event(EVENT_DESTROY_RENDERABLE), 
m_pRenderableObject(object)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
RemoveRenderableEvent::~RemoveRenderableEvent()
{

}