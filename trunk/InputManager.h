/**********************************************
*  Classes:   InputManager
*  Desc:      Singleton class. Handles user input
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>
#include <list>
#include "Callback.h"

class InputManager
{
public:

	// input event codes
	enum InputEvent
	{
		KEY_UP,
		KEY_DOWN
	};

	// callback function for input events
	typedef Callback(void (void)) InputCallback;

	// typedef for map<unsigned int, InputCallback>
	typedef std::map<unsigned int, InputCallback> CallbackMap;

	// typedef for std::list<unsigned int>
	typedef std::list<unsigned int> EventList;
	
	// singleton class
	static InputManager* GetInstance();
	static void          Destroy();

	void ProcessInput();
	void Reset();
	void AssignFuncKeyUp(unsigned int keyCode,					
					InputCallback callback);
	void AssignFuncKeyDown(unsigned int keyCode,					
					InputCallback callback);

	void KeyDown (unsigned int key, bool bExecuteImmediately = true);

	void KeyUp   (unsigned int key, bool bExecuteImmediately = true);
	
	const bool IsKeyDown (unsigned int key) const
	{
		return m_bKeys[key];
	}

	
private:

	// single instance
	static InputManager* m_pInstance;

	//Array Used For The Keyboard Routine
	bool m_bKeys[256];


	// indicates if any keys have been pressed
	bool m_bHasEvents;

	// map of callbacks for key down
	CallbackMap m_CallbacksKDown;

	// map of callbacks for key up
	CallbackMap m_CallbacksKUp;

	// list that records input events
	EventList m_lEvents;

	InputManager();
	~InputManager();

	
};

#endif