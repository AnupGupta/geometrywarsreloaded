#include "Movable.h"
#include "GameObject.h"

//--------------------------------------------------
/**
* Ctor
*
**/
Movable::Movable(GameObject& parent)
: m_fRotation(0.0f),
  m_fAngularVelocity(0.0f),
  m_fAngularAcceleration(0.0f),
  m_fMass(1.0f),
  m_fInertia(1.0f),
  m_fTorque(0.0f),
  m_rParent(parent)
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
* Inegrator
*
**/
void Movable::Integrate(float dt)
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
* Moves the object
*
**/
void Movable::Update(float dt)
{
	m_vPosition = m_rParent.GetPosition();
	m_fRotation = m_rParent.GetRotation();

	Integrate(dt);

	m_rParent.SetPosition(m_vPosition);
	m_rParent.SetRotation(m_fRotation);
}

