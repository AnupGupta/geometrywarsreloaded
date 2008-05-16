#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Movable.h"

class Particle;
class Timer;

class ParticleEmitter : public Movable
{
public:

	ParticleEmitter(float emitRate,
		float particleLife, float systemLife);

	~ParticleEmitter();

	bool Init();
	void Update();
	void UpdateTimeDependent(float dt);
	void Shutdown();
	void Reset();

	ObjectType GetType() const
	{
		return kObjectParticleEmitter;
	}

	Particle* GetParticles() const
	{
		return m_pParticles;
	}

private:

	Timer* m_pParticleCreateTimer;
	Timer* m_pLifeTimer;

	float        m_fEmitRate;
	float        m_fParticleLife;
	unsigned int m_uiNumParticles;
	float        m_fSystemLife;
	Particle*    m_pParticles;

	void ShootParticles();
	virtual void SetInitialVelocity(Particle& particle);
	virtual void UpdateVelocity(float dt, Particle& particle);
	
};

#endif