#ifndef MAINSHIPTRAILEMITTER_H
#define MAINSHIPTRAILEMITTER_H

#include "ParticleEmitter.h"

class MainShip;

class MainShipTrailEmitter : public ParticleEmitter
{
public:

	MainShipTrailEmitter( MainShip* parentShip,
		float emitRate, 
		unsigned int particlesPerTick,
		float particleLife,
		float systemLife = -1.0f);
	~MainShipTrailEmitter();

private:

	MainShip* m_pParentShip;

	int m_iParticleWave;

	void SetInitialVelocity(Particle& particle);
	void UpdateVelocity(float dt, Particle& particle);
};

#endif