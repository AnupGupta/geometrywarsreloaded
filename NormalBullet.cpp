#include "NormalBullet.h"
#include "NormalBulletRenderable.h"
#include "EventManager.h"
#include "RemoveRenderableEvent.h"
#include "RemoveObjectEvent.h"
#include "AddObjectEvent.h"
#include "CircleExplosionEmitter.h"
#include "RandomExplosionEmitter.h"
#include "Renderer.h"
#include "Timer.h"
//--------------------------------------------------
/**
* Ctor
*
**/
NormalBullet::NormalBullet()
: m_fVelocity(0.0f),
m_bShot(false),
m_pLifeTimer(0),
m_pExplosionEmitter(0)
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
	m_pRenderable->SetTexture(Renderer::GetInstance()->GetTexture("laser"));
	m_pExplosionEmitter = new RandomExplosionEmitter(0.1f, 4, 0.5f);
	m_pExplosionEmitter->StopEmitting();
	EventManager::GetInstance()->AddEvent(new AddObjectEvent(m_pExplosionEmitter));
	return m_bInitialized = true;
}


//--------------------------------------------------
/**
* Updates normal bullet
*
**/
void NormalBullet::Update()
{
	m_pExplosionEmitter->SetPosition(m_vPosition);	

}

//--------------------------------------------------
/**
* Updates timer
*
**/
void NormalBullet::UpdateTimeDependent(float dt)
{
	if (m_bShot)
	{
		m_pLifeTimer->Update(dt);

		if (m_pLifeTimer->Tick())
		{
			m_pExplosionEmitter->SetSystemLife(0.5f);	
			m_pExplosionEmitter->SetKeepAlive(true);
			CircleExplosionEmitter* emitter = new CircleExplosionEmitter();
			emitter->SetPosition(m_vPosition);
			EventManager::GetInstance()->AddEvent(new AddObjectEvent(emitter));
			EventManager::GetInstance()->AddEvent(new RemoveRenderableEvent(m_pRenderable));
			Reset();
		}
		else
		{
			Movable::UpdateTimeDependent(dt);
		}
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

//--------------------------------------------------
/**
* Shoots bullet
*
**/
void NormalBullet::Shoot (const Vector2& initialPosition,
			float rotation, float velocity)
{
	m_vPosition = initialPosition;
	m_fRotation = rotation;
	m_vVelocity = Helper::AsVector(m_fRotation) * velocity;
	m_bShot = true;
	m_pExplosionEmitter->StartEmitting();
	m_pExplosionEmitter->SetSystemLife(-1.0f);
};