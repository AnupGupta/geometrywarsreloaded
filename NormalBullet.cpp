#include "NormalBullet.h"
#include "NormalBulletRenderable.h"
#include "EventManager.h"
#include "RemoveRenderableEvent.h"
#include "RemoveObjectEvent.h"
#include "AddObjectEvent.h"
#include "ParticleEmitter.h"
#include "Timer.h"
//--------------------------------------------------
/**
* Ctor
*
**/
NormalBullet::NormalBullet()
: m_fVelocity(0.0f),
m_bShot(false),
m_pLifeTimer(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
NormalBullet::~NormalBullet()
{
	if (m_pLifeTimer)
		delete m_pLifeTimer;	
}

//--------------------------------------------------
/**
* Initializes normal bullet
*
**/
bool NormalBullet::Init()
{
	m_pLifeTimer = new Timer(0.5f);
	m_pRenderable = new NormalBulletRenderable(*this);
	return m_bInitialized = true;
}

//--------------------------------------------------
/**
* Updates normal bullet
*
**/
void NormalBullet::Update()
{
	if (m_pLifeTimer->Tick())
	{
		ParticleEmitter* p = new ParticleEmitter(0.1f, 1.0f, 1.0f);
		p->SetPosition(m_vPosition);
		p->SetVelocity(m_vVelocity);
		EventManager::GetInstance()->AddEvent(new AddObjectEvent(p));
		EventManager::GetInstance()->AddEvent(new RemoveRenderableEvent(m_pRenderable));
		Reset();
	}

}

//--------------------------------------------------
/**
* Updates timer
*
**/
void NormalBullet::UpdateTimeDependent(float dt)
{
	Movable::UpdateTimeDependent(dt);

	if (m_bShot)
	{
		m_pLifeTimer->Update(dt);
	}
}

//--------------------------------------------------
/**
* Shuts down normal bullet
*
**/
void NormalBullet::Shutdown()
{
	EventManager::GetInstance()->AddEvent(new RemoveObjectEvent(this));
}

//--------------------------------------------------
/**
* Resets normal bullet
*
**/
void NormalBullet::Reset()
{
	m_pLifeTimer->Reset();
	m_fVelocity = 0.0f;
	m_bShot = false;
}