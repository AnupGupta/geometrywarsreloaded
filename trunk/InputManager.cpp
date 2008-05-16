/* 
* Singleton class. Processes keyboard
* and mouse input
*/

#include "InputManager.h"

using namespace std;
//------------------------------------------------------
InputManager* InputManager::m_pInstance = 0;
//------------------------------------------------------
/*
* Ctor
*/
InputManager::InputManager() : m_bHasEvents(false)
{
	memset(m_bKeys, false, sizeof(bool)*256);
}
//------------------------------------------------------
/*
* Dtor
*/
InputManager::~InputManager()
{
	m_lEvents.clear();
	m_CallbacksKDown.clear();
	m_CallbacksKUp.clear();
}
//------------------------------------------------------
/*
* Creates instance
*/
InputManager* InputManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new InputManager();
	}

	return m_pInstance;
}
//------------------------------------------------------
/*
* Destroys instance
*/
void InputManager::Destroy()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = 0;
	}
}
//------------------------------------------------------
/*
* Processes user input
*/
void InputManager::ProcessInput()
{
	if (m_bHasEvents)
	{
		m_bHasEvents = false;

		// keyboard
		
		unsigned int keyUpMask = 0x04000000;
		unsigned int keyDownMask = 0x80000000;
		
		EventList::iterator eventIt = m_lEvents.begin();

		while (eventIt != m_lEvents.end())
		{
			EventList::iterator next = eventIt;
			++next;  

			unsigned int e = *eventIt;
			m_lEvents.erase(eventIt);
			eventIt = next;
			
			InputCallback c = 0;

			 // check for key down
			if (e & keyDownMask)
			{
				//get the key code
				unsigned int code = 255 & e;
				//find the callback function
				CallbackMap::iterator
					callbackIt = m_CallbacksKDown.find(code);
				if (callbackIt != m_CallbacksKDown.end())
				{
					c = callbackIt->second;				
				}	
			}
			// check for key up
			else if (e & keyUpMask)
			{
				//get the key code
				unsigned int code = 255 & e;
				//find the callback function
				CallbackMap::iterator
					callbackIt = m_CallbacksKUp.find(code);
				if (callbackIt != m_CallbacksKUp.end())
				{
					c = callbackIt->second;				
				}	
			}			

			// call the function
			if (c) c();
		}


		// mouse
	}
}
//------------------------------------------------------
/*
* Processes key down
*/
void InputManager::KeyDown(unsigned int key, bool bExecuteImmediately)
{
	if (!bExecuteImmediately)
	{
		unsigned int event_key = 0x80000000 | key;
		m_lEvents.push_back(event_key);
		m_bHasEvents = true;
	}
	else
	{
		CallbackMap::iterator
		callbackIt = m_CallbacksKDown.find(key);
		if (callbackIt != m_CallbacksKDown.end())
		{
			callbackIt->second();			
		}
	}

	m_bKeys[key] = true;
}
//------------------------------------------------------
/*
* Processes key up
*/
void InputManager::KeyUp(unsigned int key, bool bExecuteImmediately)
{
	if (!bExecuteImmediately)
	{
		unsigned int event_key = 0x04000000 | key;
		m_lEvents.push_back(event_key);
		m_bHasEvents = true;
	}
	else
	{
		CallbackMap::iterator
			callbackIt = m_CallbacksKUp.find(key);
		if (callbackIt != m_CallbacksKUp.end())
		{
			callbackIt->second();				
		}
	}
	
	m_bKeys[key] = false;
}
//------------------------------------------------------
/*
* Resets the manager
*/
void InputManager::Reset()
{
	
	m_bHasEvents = false;
}
//------------------------------------------------------
/*
* Assigns a function to a certain key / event pair
*/
void InputManager::AssignFuncKeyUp(unsigned int keyCode,
							  InputCallback callback)
{
	m_CallbacksKUp.insert(make_pair(keyCode, callback));
}
//------------------------------------------------------
/*
* Assigns a function to a certain key / event pair
*/
void InputManager::AssignFuncKeyDown(unsigned int keyCode,
							  InputCallback callback)
{
	m_CallbacksKDown.insert(make_pair(keyCode, callback));
}