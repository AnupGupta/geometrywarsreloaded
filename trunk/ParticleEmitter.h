#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "GameObject.h"
#include "Timer.h"

class Particle;
class Texture;

class ParticleEmitter : public GameObject
{
public:

	ParticleEmitter(float emitRate, unsigned int particlesPerTick,
		float particleLife, float particleSize = 20.0f, 
		Texture* particleTexture = 0, float systemLife = -1.0f);

	virtual ~ParticleEmitter();

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

	void StopEmitting()
	{
		m_bEmit = false;
	}

	void StartEmitting()
	{
		m_bEmit = true;
	}

	void SetParticleTexture(Texture* texture);

	void SetSystemLife(float systemLife)
	{
		m_fSystemLife = systemLife;
		m_pLifeTimer->SetTickInterval(systemLife);
		m_bKillSystem = false;
	}

	void SetKeepAlive (bool value)
	{
		m_bKeepAlive = value;
	}

protected:

	Timer* m_pParticleCreateTimer;
	Timer* m_pLifeTimer;

	float        m_fEmitRate;
	float        m_fParticleLife;
	unsigned int m_uiNumParticles;
	unsigned int m_uiParticlesPerTick;
	float        m_fSystemLife;
	bool         m_bKillSystem;
	bool         m_bEmit;
	bool         m_bKeepAlive;
	Particle*    m_pParticles;
	Texture*     m_pParticleTexture;
	float        m_fParticleSize;
	bool         m_bIsRendered;

	bool AreAllParticlesDead();
	void ShootParticles();

	virtual bool InitCustomized() { return true; }
	virtual void UpdateCustomized(){}
	virtual void UpdateTimeDependentCustomized(float dt){}
	virtual void SetInitialVelocity(Particle& particle) = 0;
	virtual void UpdateVelocity(float dt, Particle& particle) = 0;
	
};

#endif