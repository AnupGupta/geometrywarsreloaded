#include "Particle.h"
#include <stdio.h>


//--------------------------------------------------
/**
* Ctor
*
**/
Particle::Particle()
: m_bAlive(false),
  m_fEnergy(0.0f),
  m_fTotalEnergy(0.0f),
  m_fInvTotalEnergy(1.0f),
  m_color(1.0f, 1.0f, 1.0f, 0.0f)
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
	if (m_bAlive && m_fTotalEnergy > 0.0f)
	{
		m_fEnergy -= dt;	
		m_vPosition += m_vVelocity * dt;
		m_bAlive = m_fEnergy > 0.0f;
		m_color.SetAlpha(m_fEnergy * m_fInvTotalEnergy);
	
	}
	else
	{
		m_color.SetAlpha(0.0f);
	}

	
	
}