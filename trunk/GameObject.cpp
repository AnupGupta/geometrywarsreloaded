#include "GameObject.h"
#include "Renderable.h"
#include "Movable.h"

//--------------------------------------------------
/**
* Ctor
*
**/
GameObject::GameObject()
: m_pRenderable(0),
  m_pMovable(0),
  m_fRotation(0.0f),
  m_bInitialized(false)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
GameObject::~GameObject()
{
	if (m_pMovable)
		delete m_pMovable;
}

//--------------------------------------------------
/**
* Resets position and orientation
*
**/
void GameObject::Reset()
{

}

//--------------------------------------------------
/**
* Updates movables
*
**/
void GameObject::UpdateTimeDependent(float dt)
{
	if (m_pMovable)
	{
		m_pMovable->Update(dt);
	}
}
