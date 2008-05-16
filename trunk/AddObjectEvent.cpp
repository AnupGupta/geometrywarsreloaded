#include "AddObjectEvent.h"
#include "GameObject.h"

//--------------------------------------------------
/**
* Ctor
*
**/
AddObjectEvent::AddObjectEvent(GameObject* object)
: Event(EVENT_ADD_OBJECT), 
  m_pGameObject(object)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
AddObjectEvent::~AddObjectEvent()
{

}