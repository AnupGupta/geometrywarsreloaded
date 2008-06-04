#include "GameApp.h"
#include "Renderer.h"
#include "InputManager.h"
#include "EventManager.h"
#include "AddObjectEvent.h"
#include "RemoveObjectEvent.h"
#include "Callback.h"
#include "GameObject.h"
#include "MainShip.h"
#include "Renderable.h"
#include "ParticleEmitter.h"
#include "MultiExplosionEmitter.h"
#include "CircleExplosionEmitter.h"
#include <windows.h>
#include <time.h>

GameApp* GameApp::ms_pInstance = 0;

//--------------------------------------------------
/**
* Ctor
*
**/
GameApp::GameApp() : 
m_pRenderer(0),
m_pInputManager(0),
m_pEventManager(0),
m_bQuit(false),
m_fDeltaTime(0.0f),
m_fcTimeStep(0.01f),
m_bPerfTimer(false),
m_PerfFreq(0),
m_fPerfFreq(0.0f),
m_NextTime(0),
m_fNextTime(0.0),
m_LastTime(0),
m_fLastTime(0.0f),
m_fTimeAccum(0.0f),
m_fcMaxDT(1.0f),
m_fTotalTime(0.0f),
m_pPlayerShip(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
GameApp::~GameApp()
{
	Shutdown();
}


//--------------------------------------------------
/**
* Gets instance
*
**/
GameApp* GameApp::GetInstance()
{
	return ms_pInstance ? ms_pInstance :
		ms_pInstance = new GameApp;
}

//--------------------------------------------------
/**
* Destroys instance
*
**/
void GameApp::Destroy()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = 0;
	}
}

//--------------------------------------------------
/**
* Initializes game
*
**/
bool GameApp::Init()
{

	m_pRenderer = Renderer::GetInstance();

	if (!m_pRenderer->Init())
		return false;

	m_pInputManager = InputManager::GetInstance();
	m_pEventManager = EventManager::GetInstance();

	m_pEventManager->Register(this);

	InitializeTimers();

	SetMainShip(new MainShip());

	AssignKeys();

	AddObject(m_pPlayerShip);

	//AddObject(new MultiExplosionEmitter());
	return true;
}
//--------------------------------------------------
/**
* Updates everything
*
**/
bool GameApp::Update()
{
	m_pInputManager->ProcessInput();
	m_pEventManager->DispatchEvents();

	if (m_bQuit)
	{
		return false;
	}

	UpdateTime();

	float tempAccum;
	float tempTotalTime;

	ObjectList::iterator objectIt = m_objects.begin();
	for (; objectIt != m_objects.end(); ++objectIt)
	{
		GameObject* object = (*objectIt);
		object->Update();

		// update the entities using a fixed timestep
		
		tempAccum = m_fTimeAccum;
		tempTotalTime = m_fTotalTime;
		
		while (tempAccum >= m_fcTimeStep)
		{
			object->UpdateTimeDependent(m_fcTimeStep);

			// increase total time
			tempTotalTime += m_fcTimeStep;
			// decrease time accumulator
			tempAccum -= m_fcTimeStep;		
		}
	}

	m_fTimeAccum = tempAccum;
	m_fTotalTime = tempTotalTime;

	

	
	return true;
}

//--------------------------------------------------
/**
* Resets game
*
**/
void GameApp::Reset()
{
	ObjectList::iterator it = m_objects.begin();
	for (; it != m_objects.end(); ++it)
	{
		GameObject* object = (*it);
		object->Reset();
	}
}

//-----------------------------------------------------
/*
* Updates Time Step
*/
void GameApp::UpdateTime()
{
	// if there is a performance counter use it
	if (m_bPerfTimer)
	{
		QueryPerformanceCounter((LARGE_INTEGER *) &m_NextTime);
		m_fNextTime = m_NextTime* m_fPerfFreq;
	}
	else
	{
		m_NextTime = timeGetTime();
		m_fNextTime = (float)m_NextTime / 1000.0f;
	}

	// calculate and damp delta time
	m_fDeltaTime = (float)(m_fNextTime - m_fLastTime);
	if (m_fDeltaTime > m_fcMaxDT)
	{
		m_fDeltaTime = m_fcMaxDT;
	}
	// update last time and time accumulator
	m_LastTime = m_NextTime;
	m_fLastTime = m_fNextTime;
	m_fTimeAccum += m_fDeltaTime;

}

//-----------------------------------------------------
/*
* Initializes timers
*/
void GameApp::InitializeTimers()
{
	// is a performance counter available
	if (QueryPerformanceFrequency((LARGE_INTEGER *) &m_PerfFreq)) 
	{		
		m_bPerfTimer = true;       
		m_fPerfFreq = 1.0f / (float)m_PerfFreq;
		QueryPerformanceCounter((LARGE_INTEGER *) &m_LastTime);
		m_fLastTime = (float)m_LastTime*m_fPerfFreq;
		m_fNextTime = m_fLastTime;


	}
	else {

		// no performance counter, read in using timeGetTime
		m_LastTime = timeGetTime();
		m_fLastTime = (float)m_LastTime / 1000.0f;

	}
}
//--------------------------------------------------
/**
* Assigns keys to functions
*
**/
void GameApp::AssignKeys()
{
	m_pInputManager->AssignFuncKeyUp
		(VK_ESCAPE, BindFunc(GameApp, SendQuitEvent, this));

	m_pInputManager->AssignFuncKeyUp
		('r', BindFunc(GameApp, Reset, this));

	m_pInputManager->AssignFuncKeyDown
		('w', BindFunc(MainShip, MoveUp, m_pPlayerShip));

	m_pInputManager->AssignFuncKeyDown
		('s', BindFunc(MainShip, MoveDown, m_pPlayerShip));

	m_pInputManager->AssignFuncKeyDown
		('a', BindFunc(MainShip, MoveLeft, m_pPlayerShip));

	m_pInputManager->AssignFuncKeyDown
		('d', BindFunc(MainShip, MoveRight, m_pPlayerShip));

	m_pInputManager->AssignFuncKeyUp
		('w', BindFunc(MainShip, StopMoveUp, m_pPlayerShip));

	m_pInputManager->AssignFuncKeyUp
		('s', BindFunc(MainShip, StopMoveDown, m_pPlayerShip));

	m_pInputManager->AssignFuncKeyUp
		('a', BindFunc(MainShip, StopMoveLeft, m_pPlayerShip));

	m_pInputManager->AssignFuncKeyUp
		('d', BindFunc(MainShip, StopMoveRight, m_pPlayerShip));

	m_pInputManager->AssignFuncKeyUp
		(' ', BindFunc(MainShip, ShootNormal, m_pPlayerShip));

	m_pInputManager->AssignMousePassiveMotion(
		BindFuncTwoArg(MainShip, TargetChange, m_pPlayerShip));
}

//--------------------------------------------------
/**
* Sets events for this GameApp to handle
*
**/
void GameApp::SetInterested()
{
	m_interestedEvents.insert(std::make_pair(Event::EVENT_QUIT, (Event*)0));
	m_interestedEvents.insert(std::make_pair(Event::EVENT_ADD_OBJECT, (Event*)0));
	m_interestedEvents.insert(std::make_pair(Event::EVENT_DESTROY_OBJECT, (Event*)0));
}


//--------------------------------------------------
/**
* Handles events
*
**/
void GameApp::HandleEvent(Event* const e)
{
	switch (e->GetCode())
	{
	case Event::EVENT_QUIT:
		m_bQuit = true;
		break;

	case Event::EVENT_ADD_OBJECT:
		{
			AddObjectEvent* const pAddEvent = static_cast<AddObjectEvent*>(e);
			if (pAddEvent->m_pGameObject)
			{
				AddObject(pAddEvent->m_pGameObject);
			}

		}
		break;

	case Event::EVENT_DESTROY_OBJECT:
		{
			RemoveObjectEvent* const pAddEvent = static_cast<RemoveObjectEvent*>(e);
			if (pAddEvent->m_pGameObject)
			{
				RemoveObject(pAddEvent->m_pGameObject);
			}

		}
		break;

	default:

		return;

	}
}

//--------------------------------------------------
/**
* Sends quit event
*
**/
void GameApp::SendQuitEvent()
{
	
	m_pEventManager->AddEvent(new Event(Event::EVENT_QUIT));
}

//--------------------------------------------------
/**
* Shuts down game
*
**/
void GameApp::Shutdown()
{
	ObjectList::iterator objIt = m_objects.begin();
	for (; objIt != m_objects.end(); ++objIt)
	{
		GameObject* object = (*objIt);

		if (object)
		{
			object->Shutdown();
		}

	}


	m_pEventManager->DispatchEvents();

	Renderer::Destroy();
	InputManager::Destroy();
	EventManager::Destroy();

	m_pRenderer = 0;
	m_pInputManager = 0;
	m_pEventManager = 0;

	
	m_objects.clear();

	m_pPlayerShip = 0;
}
//--------------------------------------------------
/**
* Adds an object to the list
*
**/
bool GameApp::AddObject(GameObject* object)
{
	if (object)
	{
		if (!object->IsInitialized())
		{
			if (!object->Init())
				return false;
		}

		m_objects.push_back(object);
		Renderable* renderable = object->GetRenderable();
		if (renderable)
		{
			if (m_pRenderer->AddRenderable(renderable))
			{
				return true;
			}
		}

		return true;
	}

	return false;
}

//--------------------------------------------------
/**
* Removes an object from the list
*
**/
void GameApp::RemoveObject(GameObject* object)
{
	if (object)
	{
		ObjectList::iterator objIt = m_objects.begin();
		for (; objIt != m_objects.end(); ++objIt)
		{
			GameObject* cur = (*objIt);
			if (cur == object)
			{
				m_objects.erase(objIt);

				Renderable* renderable = cur->GetRenderable();
				if (renderable)
				{
					m_pRenderer->RemoveRenderable(renderable);
					delete renderable;
				}

				
				delete cur;

				return;
			}
		}
	}
}
//--------------------------------------------------
/**
* Sets the main ship
*
**/
void GameApp::SetMainShip(MainShip* ship)
{
	if (ship)
	{
		if (m_pPlayerShip)
		{

			m_pEventManager->Unregister(m_pPlayerShip);
		}

		m_pPlayerShip = ship;
	
		m_pEventManager->Register(m_pPlayerShip);
	}


}