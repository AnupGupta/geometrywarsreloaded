#include "TargetArrow.h"
#include "Ship.h"
#include "ArrowRenderable.h"
#include "EventManager.h"
#include "RemoveObjectEvent.h"
#include "Helper.h"

//--------------------------------------------------
/**
* Ctor
*
**/
TargetArrow::TargetArrow()
: m_pParentShip(0)
{

}
//--------------------------------------------------
/**
* Dtor
*
**/
TargetArrow::~TargetArrow()
{

}

//--------------------------------------------------
/**
* Initializes target arrow
*
**/
bool TargetArrow::Init()
{
	m_pRenderable = new ArrowRenderable(*this);
	return m_bInitialized = true;
}

//--------------------------------------------------
/**
* Updates target arrow
*
**/
void TargetArrow::Update()
{
	float offset = 1.0f;
	if (m_pParentShip)
	{
		m_vPosition = m_pParentShip->GetPosition() + Helper::AsVector(m_pParentShip->GetTargetRotation()) * offset;
	}
}

//--------------------------------------------------
/**
* Shuts down target arrow
*
**/
void TargetArrow::Shutdown()
{
	EventManager::GetInstance()->AddEvent(new RemoveObjectEvent(this));
}

//--------------------------------------------------
/**
* Resets target arrow
*
**/
void TargetArrow::Reset()
{
	m_pParentShip = 0;
}