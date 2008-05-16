#include "Particle.h"


//--------------------------------------------------
/**
* Ctor
*
**/
Particle::Particle()
: m_bAlive(false),
  m_fEnergy(0.0f)
{

}
//--------------------------------------------------
/**
* Dtor
*
**/
Particle::~Particle()
{

}

//--------------------------------------------------
/**
* Updates particle
*
**/
void Particle::Update(float dt)
{
	if (m_bAlive)
	{
		m_fEnergy -= dt;
		m_vPosition += m_vVelocity * dt;
		m_bAlive = m_fEnergy > 0.0f;
	}
	
}