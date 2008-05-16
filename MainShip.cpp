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
#include <windows.h>
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
  m_numBullets(10),
  m_pTargetArrow(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
MainShip::~MainShip()
{

}

//--------------------------------------------------
/**
* Initializes main ship
*
**/
bool MainShip::Init()
{
	m_pRenderable = new MainShipRenderable(*this);

	
	for (int i=0; i<m_numBullets; i++)
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

	return m_bInitialized = true;
}



//--------------------------------------------------
/**
* Updates main ship
*
**/
void MainShip::Update()
{
	float shipSpeed = 10.0f;
	if (m_bMoveUp && !m_bStopMoveUp)
	{
		SetVelocity(Vector2(m_vVelocity.x, shipSpeed));
	}
	else if (m_bMoveDown && !m_bStopMoveDown)
	{
		SetVelocity(Vector2(m_vVelocity.x, -shipSpeed));
	}
	else
	{
		SetVelocity(Vector2(m_vVelocity.x, 0.0f));
	}

	if (m_bMoveLeft && !m_bStopMoveLeft)
	{
		SetVelocity(Vector2(-shipSpeed, m_vVelocity.y));
	}
	else if (m_bMoveRight && !m_bStopMoveRight)
	{
		SetVelocity(Vector2(shipSpeed, m_vVelocity.y));
	}
	else
	{
		SetVelocity(Vector2(0.0f, m_vVelocity.y));
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