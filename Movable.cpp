#include "Movable.h"

//--------------------------------------------------
/**
* Ctor
*
**/
Movable::Movable()
: m_fAngularVelocity(0.0f),
  m_fAngularAcceleration(0.0f),
  m_fMass(1.0f),
  m_fInertia(1.0f),
  m_fTorque(0.0f)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
Movable::~Movable()
{

}

//--------------------------------------------------
/**
* Moves the object
*
**/
void Movable::UpdateTimeDependent(float dt)
{
	m_vAcceleration = m_vForce / m_fMass;
	m_vVelocity += m_vAcceleration * dt;
	m_vPosition += m_vVelocity * dt;

	m_fAngularAcceleration = m_fTorque / m_fInertia;
	m_fAngularVelocity += m_fAngularAcceleration * dt;
	m_fRotation += m_fAngularVelocity * dt;

}

//--------------------------------------------------
/**
* Resets everything
*
**/
void Movable::Reset()
{
	GameObject::Reset();

	m_vAcceleration = Vector2(0.0f, 0.0f);
	m_vForce = Vector2(0.0f, 0.0f);
	m_vVelocity = Vector2(0.0f, 0.0f);

	m_fAngularAcceleration = 0.0f;
	m_fAngularVelocity = 0.0f;
	m_fRotation = 0.0f;
}