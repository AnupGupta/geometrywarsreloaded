/**********************************************
*  Classes:   EventListener
*  Desc:      A listener for events. A listener
*			  is notified if an event has happened
*			  and processes the event only if it 
*			  is interested in it.
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#include "EventListener.h"


//-------------------------------------------------
/**
* Ctor
*/
EventListener::EventListener()
: m_bAwake(false)
{
	
}
//-------------------------------------------------
/**
* Dtor
*/
EventListener::~EventListener()
{
	EventMap::iterator it = m_interestedEvents.begin();
	for (; it != m_interestedEvents.end(); ++it)
	{
		if (it->second) delete it->second;
	}
	m_interestedEvents.clear();
}
//-------------------------------------------------
/**
* Notify the listener that an event has happened.
* The listener's state changes only if it is interested
* in the event
*/
void EventListener::Notify(Event* const e)
{
	if (e)
	{
		m_bAwake = (IsInterestedIn(e->GetCode()));	
		m_CurEvent = *e;

		HandleEvent(e);
	}
	
}
//-------------------------------------------------
/**
* Sleeps the listener
*/
void EventListener::Sleep()
{
	m_bAwake = false;
	m_CurEvent.Reset();
}
	