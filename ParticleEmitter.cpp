#include "ParticleEmitter.h"
#include "EventManager.h"
#include "RemoveObjectEvent.h"
#include "Helper.h"
#include "Particle.h"
#include "ParticleSystemRenderable.h"
#include "RemoveRenderableEvent.h"
#include "AddRenderableEvent.h"
#include "Texture.h"
#include <omp.h>

using namespace mth;
//--------------------------------------------------
/**
* Ctor
*
**/
ParticleEmitter::ParticleEmitter(float emitRate, 
								 unsigned int particlesPerTick,
								 float particleLife,
								 float particleSize,
								 Texture* particleTexture,
								 float systemLife)
: m_pParticleCreateTimer(0),
  m_pLifeTimer(0),
  m_fEmitRate(emitRate),
  m_fParticleLife(particleLife),
  m_fSystemLife(systemLife),
  m_uiNumParticles(0),
  m_uiParticlesPerTick(particlesPerTick),
  m_pParticles(0),
  m_bKillSystem(false),
  m_bEmit(true),
  m_bKeepAlive(false),
  m_pParticleTexture(particleTexture),
  m_fParticleSize(particleSize),
  m_bIsRendered(false)
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
		m_uiNumParticles = (unsigned int)(m_uiParticlesPerTick * m_fParticleLife / m_fEmitRate) + 1;
		m_pParticles = new Particle[m_uiNumParticles];
		
	}
	else
	{
		return false;
	}
	 
	m_pRenderable = new ParticleSystemRenderable(*this, m_uiNumParticles);
	if (m_pParticleTexture)
	{
		m_pRenderable->SetTexture(m_pParticleTexture);
	}

	(static_cast<ParticleSystemRenderable*>(m_pRenderable))->SetParticleSize(m_fParticleSize);

	m_bIsRendered = true;

	return m_bInitialized = InitCustomized();
}

//--------------------------------------------------
/**
* Updates particle emitter
*
**/
void ParticleEmitter::Update()
{
	if (m_bKillSystem)
	{
		if (AreAllParticlesDead())
		{
			if (m_bIsRendered)
			{
				EventManager::GetInstance()->AddEvent(new RemoveRenderableEvent(m_pRenderable));
				m_bIsRendered = false;
			}
			
			if (!m_bKeepAlive)
				Shutdown();
		}
	}
	else if (!m_bEmit)
	{
		if (m_bIsRendered)
		{
			if (AreAllParticlesDead())
			{
				EventManager::GetInstance()->AddEvent(new RemoveRenderableEvent(m_pRenderable));
				m_bIsRendered = false;
			}
		}
	}

	UpdateCustomized();
}


//--------------------------------------------------
/**
* Updates particles
*
**/
void ParticleEmitter::UpdateTimeDependent(float dt)
{
	Movable::UpdateTimeDependent(dt);

	if (!m_bKillSystem && m_bEmit)
	{
		m_pParticleCreateTimer->Update(dt);

		if (m_pParticleCreateTimer->Tick())
		{
			ShootParticles();
		}
	}
	
	int i=0; int numParticles = m_uiNumParticles;
	
	#pragma omp parallel for
	for (i=0; i<numParticles; i++)
	{
		UpdateVelocity(dt, m_pParticles[i]);
		m_pParticles[i].Update(dt);
	}

	if (m_fSystemLife > 0.0f)
	{
		m_pLifeTimer->Update(dt);
		if (m_pLifeTimer->Tick())
		{
			m_bKillSystem = true;
			
		}
	}
	

	UpdateTimeDependentCustomized(dt);
	

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
	m_bIsRendered = true;
}
//--------------------------------------------------
/**
* Checks if all particles in the system are dead
*
**/
bool ParticleEmitter::AreAllParticlesDead()
{
	for (unsigned int i=0; i<m_uiNumParticles; i++)
	{
		if (!m_pParticles[i].Dead())
		{
			return false;
		}
	}

	return true;
}

//--------------------------------------------------
/**
* Shoots particles
*
**/
void ParticleEmitter::ShootParticles()
{
	if (!m_bIsRendered)
	{
		EventManager::GetInstance()->AddEvent(new AddRenderableEvent(m_pRenderable));
		m_bIsRendered = true;
	}
	
	unsigned int generated = 0;
	for (unsigned int i=0; i<m_uiNumParticles && generated < m_uiParticlesPerTick; i++)
	{
		if (m_pParticles[i].Dead())
		{
			m_pParticles[i].SetPosition(m_vPosition);
			m_pParticles[i].SetTotalEnergy(m_fParticleLife);
			SetInitialVelocity(m_pParticles[i]);
			m_pParticles[i].MakeAlive();
			generated++;
		}
	}
	
}

//--------------------------------------------------
/**
* Sets new particle texture
*
**/
void ParticleEmitter::SetParticleTexture(Texture* texture)
{
	m_pParticleTexture = texture;

	if (texture && m_pRenderable)
	{
		m_pRenderable->SetTexture(texture);
	}
}