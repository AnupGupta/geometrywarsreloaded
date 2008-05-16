/**********************************************
*  Classes:   EventManager
*  Desc:      Singleton class. Holds listeners 
*			  and events. It also dispatches
*			  events to the registered
*			  listeners.
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#include "EventManager.h"
#include "EventListener.h"

//----------------------------------------------------
EventManager* EventManager::m_spInstance = 0;
//----------------------------------------------------
/**
* Ctor
*/
EventManager::EventManager()
{
}
//----------------------------------------------------
/**
* Dtor
*/
EventManager::~EventManager()
{
	Reset();
}
//----------------------------------------------------
/**
* Gets instance
*/
EventManager* EventManager::GetInstance()
{
	if (!m_spInstance)
	{
		m_spInstance = new EventManager();
	}

	return m_spInstance;

}
//----------------------------------------------------
/**
* Destroys instance
*/
void EventManager::Destroy()
{
	if (m_spInstance)
	{
		delete m_spInstance;
		m_spInstance = 0;
	}
}
//----------------------------------------------------
/**
* Initializes manager
*/
bool EventManager::Init()
{
	return true;
}
//----------------------------------------------------
/**
* Resets manager
*/
void EventManager::Reset()
{
	while (!m_stEvents.empty())
	{
		delete m_stEvents.front();
		m_stEvents.pop();
	}
	
	/*
	ListenerList::iterator it = m_lListeners.begin();
	for (; it != m_lListeners.end(); ++it)
	{
		if (*it) delete (*it);
	}
	*/
	m_lListeners.clear();
}
//----------------------------------------------------
/**
*  Registers listener with the manager
*/
void EventManager::Register(EventListener *listener)
{
	if (listener)
		m_lListeners.push_back(listener);
}
//----------------------------------------------------
/**
*  Removes listener from the list
*/
void EventManager::Unregister(EventListener *listener)
{
	if (listener)
	{
		ListenerList::iterator it = m_lListeners.begin();
		for (; it != m_lListeners.end(); ++it)
		{
			EventListener* l = (*it);
			if (l == listener)
			{
				m_lListeners.erase(it);
				return;
			}
		}
		
	}
}

//----------------------------------------------------
/**
*  Dispatches events to listeners
*/
void EventManager::DispatchEvents()
{
	if (!m_lListeners.empty())
	{
		while(!m_stEvents.empty())
		{
			ListenerList::iterator liIt = m_lListeners.begin();
			Event* const e = m_stEvents.front();
			for (; 
				liIt != m_lListeners.end();
				++liIt)
			{
				(*liIt)->Notify(e);
			}
			delete m_stEvents.front();
			m_stEvents.pop();
		}
		
	}
}