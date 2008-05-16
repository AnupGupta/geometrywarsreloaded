#include "GameObject.h"
#include "Renderable.h"

//--------------------------------------------------
/**
* Ctor
*
**/
GameObject::GameObject()
: m_fRotation(0.0f),
  m_pRenderable(0),
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

}

//--------------------------------------------------
/**
* Resets position and orientation
*
**/
void GameObject::Reset()
{
	m_vPosition = Vector2(0.0f, 0.0f);
	m_fRotation = 0.0f;
}

