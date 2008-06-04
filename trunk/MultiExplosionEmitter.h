#ifndef MULTIEXPLOSIONEMITTER_H
#define MULTIEXPLOSIONEMITTER_H

#include "ParticleEmitter.h"

class Timer;

class MultiExplosionEmitter : public ParticleEmitter
{
public:

	MultiExplosionEmitter();
	~MultiExplosionEmitter();

private:

	Timer* m_pFirstWaveEnd;
	Timer* m_pSecondWaveEnd;
	unsigned int m_uiWave;

	bool InitCustomized();
	void UpdateTimeDependentCustomized(float dt);
	void SetInitialVelocity(Particle& particle);
	void UpdateVelocity(float dt, Particle& particle);
};

#endif