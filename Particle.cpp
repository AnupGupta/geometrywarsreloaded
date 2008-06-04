#include "Particle.h"
#include <stdio.h>
#include "Movable.h"

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
	Init();
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
* Initializes particle
*
**/
bool Particle::Init()
{
	m_pMovable = new Movable(*this);
	return m_pMovable != 0;
}

//--------------------------------------------------
/**
* Update
*
**/
void Particle::Update()
{

}

//--------------------------------------------------
/**
* Updates particle
*
**/
void Particle::UpdateTimeDependent(float dt)
{
	if (m_bAlive && m_fTotalEnergy > 0.0f)
	{
		m_fEnergy -= dt;	
		m_bAlive = m_fEnergy > 0.0f;
		m_color.SetAlpha(m_fEnergy * m_fInvTotalEnergy);
	
		GameObject::UpdateTimeDependent(dt);
	}
	else
	{
		m_color.SetAlpha(0.0f);
	}
}

//--------------------------------------------------
/**
* Resets particle
*
**/
void Particle::Reset()
{

}

//--------------------------------------------------
/**
* Shuts down particle
*
**/
void Particle::Shutdown()
{

}