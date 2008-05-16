/**********************************************
*  Classes:   Event
*  Desc:      An event that happens in the game. It
*			  could be anything from collision to 
*			  a change of a specific value. Used by 
*			  the EventManager.
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#ifndef EVENT_H
#define EVENT_H

class Event
{
public:

	enum EventCode
	{
		EVENT_NOEVENT = 1,
		EVENT_QUIT,
		EVENT_DESTROY_OBJECT,
		EVENT_ADD_OBJECT,
		EVENT_DESTROY_RENDERABLE,
		EVENT_ADD_RENDERABLE
	};

	Event() : m_EventCode(EVENT_NOEVENT)
	{}

	Event(EventCode code) : m_EventCode(code)
	{

	}
	Event(const Event& e) : m_EventCode(e.m_EventCode)
	{}

	virtual ~Event()
	{}

	// sets the event to the default one
	void Reset()
	{
		m_EventCode = EVENT_NOEVENT;
	}

	// getters
	const EventCode GetCode() const
	{
		return m_EventCode;
	}

	// operators
	Event& operator=(const Event& rhs)
	{
		if (this != &rhs)
		{
			m_EventCode = rhs.m_EventCode;
		}

		return *this;
	}
protected:

	// the event's code
	EventCode m_EventCode;
};

#endif