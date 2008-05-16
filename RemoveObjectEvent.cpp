#include "RemoveObjectEvent.h"
#include "GameObject.h"

//--------------------------------------------------
/**
* Ctor
*
**/
RemoveObjectEvent::RemoveObjectEvent(GameObject* object)
: Event(EVENT_DESTROY_OBJECT), 
m_pGameObject(object)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
RemoveObjectEvent::~RemoveObjectEvent()
{

}