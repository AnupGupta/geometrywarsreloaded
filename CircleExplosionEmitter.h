#ifndef CIRCLEEXPLOSIONEMITTER_H
#define CIRCLEEXPLOSIONEMITTER_H

#include "ParticleEmitter.h"

class Timer;

class CircleExplosionEmitter : public ParticleEmitter
{
public:

	CircleExplosionEmitter();
	~CircleExplosionEmitter();

private:

	int m_iCurrentParticle;

	bool InitCustomized();
	void UpdateTimeDependentCustomized(float dt);
	void SetInitialVelocity(Particle& particle);
	void UpdateVelocity(float dt, Particle& particle);
};

#endif