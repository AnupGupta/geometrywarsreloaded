#include "ParticleEmitter.h"
#include "EventManager.h"
#include "RemoveObjectEvent.h"
#include "Helper.h"
#include "Timer.h"
#include "Particle.h"
#include "ParticleSystemRenderable.h"

using namespace mth;
//--------------------------------------------------
/**
* Ctor
*
**/
ParticleEmitter::ParticleEmitter(float emitRate, 
								 float particleLife,
								 float systemLife)
: m_pParticleCreateTimer(0),
  m_pLifeTimer(0),
  m_fEmitRate(emitRate),
  m_fParticleLife(particleLife),
  m_fSystemLife(systemLife),
  m_uiNumParticles(0),
  m_pParticles(0)
{

}
//--------------------------------------------------
/**
* Dtor
*
**/
ParticleEmitter::~ParticleEmitter()
{
	if (m_pParticleCreateTimer) delete m_pParticleCreateTimer;
	if (m_pLifeTimer) delete m_pLifeTimer;
	if (m_pParticles) delete [] m_pParticles;
	
}

//--------------------------------------------------
/**
* Initializes particle emitter
*
**/
bool ParticleEmitter::Init()
{
	m_pParticleCreateTimer = new Timer(m_fEmitRate, true);
	m_pLifeTimer = new Timer(m_fSystemLife);

	if (m_fEmitRate > 0.0f)
	{
		m_uiNumParticles = (unsigned int)(m_fParticleLife / m_fEmitRate) + 1;
		m_pParticles = new Particle[m_uiNumParticles];
		
	}
	else
	{
		return false;
	}
	 
	m_pRenderable = new ParticleSystemRenderable(*this, m_uiNumParticles);
	return m_bInitialized = true;
}

//--------------------------------------------------
/**
* Updates particle emitter
*
**/
void ParticleEmitter::Update()
{
	
}


//--------------------------------------------------
/**
* Updates particles
*
**/
void ParticleEmitter::UpdateTimeDependent(float dt)
{
	Movable::UpdateTimeDependent(dt);

	m_pLifeTimer->Update(dt);
	if (m_pLifeTimer->Tick())
	{
		Shutdown();
		return;
	}

	m_pParticleCreateTimer->Update(dt);

	if (m_pParticleCreateTimer->Tick())
	{
		ShootParticles();
	}

	for (unsigned int i=0; i<m_uiNumParticles; i++)
	{
		UpdateVelocity(dt, m_pParticles[i]);
		m_pParticles[i].Update(dt);
	}
}

//--------------------------------------------------
/**
* Shuts down particle emitter
*
**/
void ParticleEmitter::Shutdown()
{
	EventManager::GetInstance()->AddEvent(new RemoveObjectEvent(this));
}

//--------------------------------------------------
/**
* Resets particle emitter
*
**/
void ParticleEmitter::Reset()
{
	m_pParticleCreateTimer->Reset();
	m_pLifeTimer->Reset();
}

//--------------------------------------------------
/**
* Shoots particles
*
**/
void ParticleEmitter::ShootParticles()
{
	for (unsigned int i=0; i<m_uiNumParticles; i++)
	{
		if (m_pParticles[i].Dead())
		{
			m_pParticles[i].SetPosition(m_vPosition);
			m_pParticles[i].SetEnergy(m_fParticleLife);
			SetInitialVelocity(m_pParticles[i]);
			m_pParticles[i].MakeAlive();
			return;
		}
	}
}

//--------------------------------------------------
/**
* Sets initial velocity for a particle
*
**/
void ParticleEmitter::SetInitialVelocity(Particle& particle)
{
	float v = (float)(rand()%5);
	particle.SetVelocity(m_vVelocity + Vector2(v, v));
}

//--------------------------------------------------
/**
* Updates velocities for particles
*
**/
void ParticleEmitter::UpdateVelocity(float dt, Particle& particle)
{
	const Vector2& vel = particle.GetVelocity();
	particle.SetVelocity(vel + Vector2(0.0, -90.8*dt));
}