#include "Ship.h"
#include "Movable.h"
//--------------------------------------------------
/**
* Ctor
*
**/
Ship::Ship()
: m_fTargetRotation(0.0f)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
Ship::~Ship()
{

}

//--------------------------------------------------
/**
* Sets interested events
*
**/
void Ship::SetInterested()
{
	
}

//--------------------------------------------------
/**
* Handles events
*
**/
void Ship::HandleEvent(Event* const e)
{
	
	
}

//--------------------------------------------------
/**
* Initializes ship
*
**/
bool Ship::Init()
{
	m_pMovable = new Movable(*this);
	return m_pMovable != 0;

}
//--------------------------------------------------
/**
* Resets ship
*
**/
void Ship::Reset()
{
	GameObject::Reset();
}