#include "RandomExplosionEmitter.h"
#include "Renderer.h"
#include "Particle.h"
//--------------------------------------------------
/**
* Ctor
*
**/
RandomExplosionEmitter::RandomExplosionEmitter(float emitRate, unsigned int particlesPerTick,
											   float particleLife, float systemLife)
: ParticleEmitter(emitRate, particlesPerTick, particleLife, 20.0f,
				  Renderer::GetInstance()->GetTexture("firePoint"), systemLife)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
RandomExplosionEmitter::~RandomExplosionEmitter()
{

}


//--------------------------------------------------
/**
* Sets initial velocity for a particle
*
**/
void RandomExplosionEmitter::SetInitialVelocity(Particle& particle)
{
	

	float vx = (float)(rand()%10 - 5);
	float vy = (float)(rand()%10 - 5);

	particle.SetVelocity(Vector2(vx, vy));
}

//--------------------------------------------------
/**
* Updates velocities for particles
*
**/
void RandomExplosionEmitter::UpdateVelocity(float dt, Particle& particle)
{
	
}