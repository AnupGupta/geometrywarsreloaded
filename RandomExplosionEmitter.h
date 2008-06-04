#ifndef RANDOMEXPLOSIONEMITTER_H
#define RANDOMEXPLOSIONEMITTER_H

#include "ParticleEmitter.h"

class RandomExplosionEmitter : public ParticleEmitter
{
public:

	RandomExplosionEmitter(float emitRate, unsigned int particlesPerTick,
		float particleLife, float systemLife = -1.0f);
	~RandomExplosionEmitter();

private:

	
	void SetInitialVelocity(Particle& particle);
	void UpdateVelocity(float dt, Particle& particle);
};

#endif