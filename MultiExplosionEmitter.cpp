#include "MultiExplosionEmitter.h"
#include "Renderer.h"
#include "Particle.h"
#include "EventManager.h"
#include "AddObjectEvent.h"
#include "RandomExplosionEmitter.h"
#include "CircleExplosionEmitter.h"
#include "Renderer.h"
#include "Texture.h"
#include "Renderable.h"
#include "Movable.h"
//--------------------------------------------------
/**
* Ctor
*
**/
MultiExplosionEmitter::MultiExplosionEmitter()
: ParticleEmitter(0.1f, 4, 1.0f, 20.0f,
  Renderer::GetInstance()->GetTexture("firePoint"), -1.0f),
  m_pFirstWaveEnd(0),
  m_pSecondWaveEnd(0),
  m_uiWave(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
MultiExplosionEmitter::~MultiExplosionEmitter()
{
	if (m_pFirstWaveEnd)
		delete m_pFirstWaveEnd;

	if (m_pSecondWaveEnd)
		delete m_pSecondWaveEnd;
}

//--------------------------------------------------
/**
* Initializes emitter
*
**/
bool MultiExplosionEmitter::InitCustomized()
{
	m_pFirstWaveEnd = new Timer(1.0f);
	m_pSecondWaveEnd = new Timer(3.0f);

	return true;
}

//--------------------------------------------------
/**
* Updates timers etc.
*
**/
void MultiExplosionEmitter::UpdateTimeDependentCustomized(float dt)
{
	switch (m_uiWave)
	{
	case 0:
		{
			m_pFirstWaveEnd->Update(dt);
			if (m_pFirstWaveEnd->Tick())
			{
				StopEmitting();
				EventManager::GetInstance()->AddEvent(new AddObjectEvent(new RandomExplosionEmitter(0.01f, 4, 1.0f, 2.0f)));
				m_uiWave = 1;
			}
			break;
		}
	case 1:
		{
			m_pSecondWaveEnd->Update(dt);
			if (m_pSecondWaveEnd->Tick())
			{
				EventManager::GetInstance()->AddEvent(new AddObjectEvent(new CircleExplosionEmitter()));
				m_uiWave = 2;
			}
			break;
		}
	case 2:
		{
			return;
		}
		break;
	}

	
}

//--------------------------------------------------
/**
* Sets initial velocity for a particle
*
**/
void MultiExplosionEmitter::SetInitialVelocity(Particle& particle)
{


	float vx = (float)(rand()%10 - 5);
	float vy = (float)(rand()%10 - 5);

	particle.GetMovable()->SetVelocity(Vector2(vx, vy));
}

//--------------------------------------------------
/**
* Updates velocities for particles
*
**/
void MultiExplosionEmitter::UpdateVelocity(float dt, Particle& particle)
{

}