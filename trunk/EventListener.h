/**********************************************
*  Classes:   EventListener
*  Desc:      A listener for events. A listener
*			  is notified if an event has happened
*			  and processes the event only if it 
*			  is interested in it.
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "Event.h"
#include <map>

class EventListener
{
public:

	typedef std::map<Event::EventCode, Event*> EventMap;

	EventListener();
	virtual ~EventListener();

	// notify the listener that an event has happened
	void Notify(Event* const e);
	// did an event that the listener is interested in happen
	const bool IsAwake() const
	{
		return m_bAwake;
	}
	// we processed the event so sleep the listener
	void Sleep();

	// getters
	bool IsInterestedIn (Event::EventCode code)
	{
		return m_interestedEvents.find(code) != 
			m_interestedEvents.end();
	}

	const Event& GetCurEvent() const
	{
		return m_CurEvent;
	}
	
protected:

	// event codes that it is interested in
	EventMap m_interestedEvents;
	// an event has occured
	bool         m_bAwake;
	// the event that happened
	Event       m_CurEvent;

	// makes the listener interested in a number of events
	virtual void SetInterested() = 0;
	virtual void HandleEvent(Event* const e) = 0;

};

#endif