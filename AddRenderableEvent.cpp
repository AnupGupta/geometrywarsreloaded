#include "AddRenderableEvent.h"
#include "Renderable.h"

//--------------------------------------------------
/**
* Ctor
*
**/
AddRenderableEvent::AddRenderableEvent(Renderable* object)
: Event(EVENT_ADD_RENDERABLE), 
  m_pRenderableObject(object)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
AddRenderableEvent::~AddRenderableEvent()
{

}