#include "MainShipTrailEmitter.h"
#include "Renderer.h"
#include "Particle.h"
#include "Helper.h"
#include "MainShip.h"
//--------------------------------------------------
/**
* Ctor
*
**/
MainShipTrailEmitter::MainShipTrailEmitter(MainShip* parentShip, 
										   float emitRate,
										   unsigned int particlesPerTick,
										float particleLife, float systemLife)
: ParticleEmitter(emitRate, particlesPerTick, particleLife, 18.0f,
  Renderer::GetInstance()->GetTexture("trail"), m_fSystemLife),
  m_pParentShip(parentShip), 
  m_iParticleWave(0)
{
}

//--------------------------------------------------
/**
* Dtor
*
**/
MainShipTrailEmitter::~MainShipTrailEmitter()
{

}


//--------------------------------------------------
/**
* Sets initial velocity for a particle
*
**/
void MainShipTrailEmitter::SetInitialVelocity(Particle& particle)
{
	
	if (m_pParentShip)
	{
		mth::Vector2 velocity = -m_pParentShip->GetVelocity();
		float rotation = velocity.Length();
		
		switch (m_iParticleWave)
		{
		case 0:
			{	
				velocity.Rotate(0.1f);
			}
			break;
		case 1:
			{
				velocity.Rotate(0.3f);
			}
			break;
		case 2:
			{
				velocity.Rotate(-0.1f);
			}
			break;
		case 3:
			{
				velocity.Rotate(-0.3f);
			}
			break;
		}

		

		m_iParticleWave = m_iParticleWave == 3 ?
			0 : m_iParticleWave + 1;

		particle.SetVelocity(Vector2(velocity.x, velocity.y));
	}
	
}

//--------------------------------------------------
/**
* Updates velocities for particles
*
**/
void MainShipTrailEmitter::UpdateVelocity(float dt, Particle& particle)
{

}