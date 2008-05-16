/**********************************************
*  Classes:   EventManager
*  Desc:      Singleton class. Holds listeners 
*			  and events. It also dispatches
*			  events to the registered
*			  listeners.
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>
#include <queue>
#include "Event.h"

class EventListener;

class EventManager
{
public:

	// gets single instance
	static EventManager* GetInstance();
	// destroys instance
	static void Destroy();
	// initializes the manager
	bool Init();
	// resets the manager
	void Reset();
	// adds an event to the stack
	void AddEvent (Event* const e)
	{
		m_stEvents.push(e);
	}
	// registers listener with the manager
	void Register(EventListener* listener);
	// removes listener from list
	void Unregister(EventListener* listener);
	// dispatches events to listeners
	void DispatchEvents();

private:

	typedef std::list<EventListener*> ListenerList;
	typedef std::queue<Event* const> EventQueue;
	// single instance
	static EventManager* m_spInstance;
	// queue of events
	EventQueue m_stEvents;
	// list of listeners
	ListenerList m_lListeners;
	// private ctor / dtor
	EventManager();
	~EventManager();
};

#endif