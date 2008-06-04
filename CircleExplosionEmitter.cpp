#include "CircleExplosionEmitter.h"
#include "Renderer.h"
#include "Particle.h"
#include "EventManager.h"
#include "AddObjectEvent.h"
#include "RandomExplosionEmitter.h"
#include "Renderer.h"
#include "Texture.h"
#include "Renderable.h"
#include "Helper.h"
//--------------------------------------------------
/**
* Ctor
*
**/
CircleExplosionEmitter::CircleExplosionEmitter()
: ParticleEmitter(1.0f, 18, 1.0f, 20.5f,
				  Renderer::GetInstance()->GetTexture("explosion"), 0.5f),
  m_iCurrentParticle(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
CircleExplosionEmitter::~CircleExplosionEmitter()
{
	
}

//--------------------------------------------------
/**
* Initializes emitter
*
**/
bool CircleExplosionEmitter::InitCustomized()
{
	
	return true;
}

//--------------------------------------------------
/**
* Updates timers etc.
*
**/
void CircleExplosionEmitter::UpdateTimeDependentCustomized(float dt)
{
	


}

//--------------------------------------------------
/**
* Sets initial velocity for a particle
*
**/
void CircleExplosionEmitter::SetInitialVelocity(Particle& particle)
{

	float angle = m_iCurrentParticle * mth::M_PI_2 / m_uiParticlesPerTick;
	m_iCurrentParticle++;
	if (m_iCurrentParticle == m_uiParticlesPerTick-1)
		m_iCurrentParticle = 0;

	Vector2 vel = mth::Helper::AsVector(angle);
	particle.SetVelocity(vel * 10.0f);
}

//--------------------------------------------------
/**
* Updates velocities for particles
*
**/
void CircleExplosionEmitter::UpdateVelocity(float dt, Particle& particle)
{

}