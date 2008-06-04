#include "MainShip.h"
#include "GameApp.h"
#include "InputManager.h"
#include "EventManager.h"
#include "MainShipRenderable.h"
#include "NormalBullet.h"
#include "AddObjectEvent.h"
#include "AddRenderableEvent.h"
#include "RemoveRenderableEvent.h"
#include "RemoveObjectEvent.h"
#include "TargetArrow.h"
#include "MainShipTrailEmitter.h"
#include <windows.h>
#include "Renderer.h"
#include "Timer.h"
#include "Movable.h"
#include <gl\glut.h>
//--------------------------------------------------
/**
* Ctor
*
**/
MainShip::MainShip()
:
  m_bMoveUp(false),
  m_bMoveDown(false),
  m_bMoveRight(false),
  m_bMoveLeft(false),
  m_bStopMoveUp(false),
  m_bStopMoveDown(false),
  m_bStopMoveLeft(false),
  m_bStopMoveRight(false),
  m_bAlive(true),
  m_fPrevMouseX(0.0f),
  m_fPrevMouseY(0.0f),
  m_numBullets(10),
  m_pTargetArrow(0),
  m_pTrail(0),
  m_pShootTimer(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
MainShip::~MainShip()
{
	if (m_pShootTimer)
		delete m_pShootTimer;
}

//--------------------------------------------------
/**
* Initializes main ship
*
**/
bool MainShip::Init()
{
	Ship::Init();

	m_pRenderable = new MainShipRenderable(*this);
	m_pRenderable->SetTexture(Renderer::GetInstance()->GetTexture("ship"));
	
	for (unsigned int i=0; i<m_numBullets; i++)
	{	
		NormalBullet* bullet = new NormalBullet;
		if (!bullet->Init())
		{
			return false;
		}
		m_bullets.push_back(bullet);
		EventManager::GetInstance()->AddEvent(new AddObjectEvent(bullet));
		EventManager::GetInstance()->AddEvent(new RemoveRenderableEvent(bullet->GetRenderable()));
	
	}

	m_pTargetArrow = new TargetArrow();
	if (!m_pTargetArrow->Init())
		return false;

	EventManager::GetInstance()->AddEvent(new AddObjectEvent(m_pTargetArrow));

	m_pTargetArrow->SetParentShip(this);

	m_pTrail = new MainShipTrailEmitter(this, 0.02, 3, 0.5);

	EventManager::GetInstance()->AddEvent(new AddObjectEvent(m_pTrail));

	m_pShootTimer = new Timer(0.2f, true);

	return m_bInitialized = true;
}



//--------------------------------------------------
/**
* Updates main ship
*
**/
void MainShip::Update()
{

	m_pTrail->SetPosition(m_vPosition - Vector2(0.0f, 2.0f));
	float shipSpeed = 10.0f;
	const Vector2& velocity = m_pMovable->GetVelocity();

	if (m_bMoveUp && !m_bStopMoveUp)
	{
		m_pMovable->SetVelocity(Vector2(velocity.x, shipSpeed));
	}
	else if (m_bMoveDown && !m_bStopMoveDown)
	{
		m_pMovable->SetVelocity(Vector2(velocity.x, -shipSpeed));
	}
	else
	{
		m_pMovable->SetVelocity(Vector2(velocity.x, 0.0f));
	}

	if (m_bMoveLeft && !m_bStopMoveLeft)
	{
		m_pMovable->SetVelocity(Vector2(-shipSpeed, velocity.y));
	}
	else if (m_bMoveRight && !m_bStopMoveRight)
	{
		m_pMovable->SetVelocity(Vector2(shipSpeed, velocity.y));
	}
	else
	{
		m_pMovable->SetVelocity(Vector2(0.0f, velocity.y));
	}

	if (velocity.Length() < 0.01f)
	{
		m_pTrail->StopEmitting();
	}
	else
	{
		m_pTrail->StartEmitting();
	}

	Vector2 m_vDir = velocity.Normalized();
	m_fRotation = atan2(m_vDir.y, m_vDir.x)*mth::TO_DEG;

}

//--------------------------------------------------
/**
* Updates timers
*
**/
void MainShip::UpdateTimeDependent(float dt)
{
	
	Ship::UpdateTimeDependent(dt);

	m_pShootTimer->Update(dt);
	if (m_pShootTimer->Tick())
	{
		//ShootNormal();
	}
}
//--------------------------------------------------
/**
* Resets main ship
*
**/
void MainShip::Reset()
{
	Ship::Reset();

	m_bMoveUp = false;
	m_bMoveLeft = false;
	m_bMoveRight = false;
	m_bMoveDown = false;
	m_bStopMoveUp = false;
	m_bStopMoveDown = false;
	m_bStopMoveLeft = false;
	m_bStopMoveRight = false;
	m_bAlive = true;
}

//--------------------------------------------------
/**
* Shuts down ship
*
**/
void MainShip::Shutdown()
{

	EventManager::GetInstance()->Unregister(this);

	m_bullets.clear();

	EventManager::GetInstance()->AddEvent(new RemoveObjectEvent(this));
	

}
//--------------------------------------------------
/**
* Sets interested events
*
**/
void MainShip::SetInterested()
{
	Ship::SetInterested();
	
}

//--------------------------------------------------
/**
* Handles events
*
**/
void MainShip::HandleEvent(Event* const e)
{
	// handle event here

	// then let ship handle it
	Ship::HandleEvent(e);
}

//--------------------------------------------------
/**
* Fires normal weapon
*
**/
void MainShip::ShootNormal()
{
	BulletList::iterator bulletIt = m_bullets.begin();

	for (; bulletIt != m_bullets.end(); ++bulletIt)
	{
		NormalBullet* bullet = (*bulletIt);
		if (!bullet->IsShot())
		{
			EventManager::GetInstance()->AddEvent(new AddRenderableEvent(bullet->GetRenderable()));
			bullet->Shoot(m_vPosition, m_fTargetRotation, 40.0f);
			return;
		}

	}
	
};

//--------------------------------------------------
/**
* Moves target arrow
*
**/
void MainShip::TargetChange(int x, int y)
{
	double modelview[16];
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	double projection[16];
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	int viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );
	
	float winX = (float)x;
	float winY = (float)viewport[3] - (float)y;

	double posX, posY, posZ;
	gluUnProject( winX, winY, 0.980981f, modelview, projection, viewport, &posX, &posY, &posZ);

	Vector2 pos(Vector2(posX, posY) - m_vPosition);
	pos.Normalize();
	m_fTargetRotation = atan2(pos.y, pos.x) - 1.57079633f;

	m_fPrevMouseX = x;
	m_fPrevMouseY = y;
}