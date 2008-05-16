#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "EventListener.h"
#include "Callback.h"
#include <list>
#include <windows.h>

class Renderer;
class InputManager;
class EventManager;
class GameObject;
class MainShip;

class GameApp : public EventListener
{
public:

	static GameApp* GetInstance();
	static void Destroy();

	bool Init();
	bool Update();
	
	
	Renderer* GetRenderer() const
	{
		return m_pRenderer;
	}

	InputManager* GetInputManager() const
	{
		return m_pInputManager;
	}

	MainShip* GetMainShip() const
	{
		return m_pPlayerShip;
	}

private:

	typedef std::list<GameObject*> ObjectList;


	static GameApp* ms_pInstance;


	Renderer* m_pRenderer;
	InputManager* m_pInputManager;
	EventManager* m_pEventManager;

	ObjectList m_objects;

	// delta time
	float m_fDeltaTime;
	// const time step for physics
	const float m_fcTimeStep;

	// is a performance timer available
	bool m_bPerfTimer;
	//performance timer frequency
	LONGLONG m_PerfFreq;
	float m_fPerfFreq;
	// time to render next frame
	LONGLONG m_NextTime;
	float m_fNextTime;
	// last time
	LONGLONG m_LastTime;
	float m_fLastTime;	
	// time accumulator
	float m_fTimeAccum;
	// max delta time
	const float m_fcMaxDT;
	// total time
	float m_fTotalTime;

	bool m_bQuit;

	MainShip* m_pPlayerShip;

	void InitializeTimers();

	void UpdateTime();

	void AssignKeys();

	void SetInterested();

	void HandleEvent(Event* const e);

	void Shutdown();

	void Reset();

	bool AddObject(GameObject* object);
	void RemoveObject(GameObject* object);
	void SetMainShip(MainShip* ship);
	void SendQuitEvent();


	GameApp();
	~GameApp();
};

#endif