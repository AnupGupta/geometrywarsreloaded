#include "Renderer.h"
#include <windows.h>
#include "Renderable.h"
#include "AddRenderableEvent.h"
#include "RemoveRenderableEvent.h"
#include "EventManager.h"
#include <gl\glut.h>


Renderer* Renderer::ms_pInstance = 0;
//--------------------------------------------------
/**
* Ctor
*
**/
Renderer::Renderer()
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
Renderer::~Renderer()
{

	m_renderables.clear();
}


//--------------------------------------------------
/**
* Gets instance
*
**/
Renderer* Renderer::GetInstance()
{
	return ms_pInstance ? ms_pInstance :
		ms_pInstance = new Renderer;
}

//--------------------------------------------------
/**
* Destroys instance
*
**/
void Renderer::Destroy()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = 0;
	}
}

//--------------------------------------------------
/**
* Initializes renderer
*
**/
bool Renderer::Init()
{
	EventManager::GetInstance()->Register(this);

	return IsVBOExtensionSupported();
}
//--------------------------------------------------
/**
* Renders scene
*
**/
void Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	RenderableList::iterator it = m_renderables.begin();
	for (; it != m_renderables.end(); ++it)
	{
		Renderable* renderable = (*it);
		renderable->Render();
	}

	glutSwapBuffers();
}

//--------------------------------------------------
/**
* Resizes window and perspective
*
**/
void Renderer::Resize(int width, int height)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(height == 0)
		height = 1;

	float ratio = 1.0* width / height;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,50.0, 
		0.0,0.0,0.0,
		0.0f,1.0f,0.0f);
}

//--------------------------------------------------
/**
* Adds a renderable object to the list
*
**/
bool Renderer::AddRenderable(Renderable *renderable)
{
	if (renderable)
	{
		if (!renderable->IsInitialized())
		{
			if (!renderable->Init())
				return false;
		}
		
		m_renderables.push_back(renderable);
		return true;
		
	}

	return false;
}

//--------------------------------------------------
/**
* Remove a renderable object from the list
*
**/
void Renderer::RemoveRenderable(Renderable *renderable)
{
	if(renderable)
	{
		RenderableList::iterator it = m_renderables.begin();
		for (; it != m_renderables.end(); ++it)
		{
			Renderable* r = (*it);
			if (r == renderable)
			{
				m_renderables.erase(it);
				return;
			}
		}
	}
}

//--------------------------------------------------
/**
* Sets interested events
*
**/
void Renderer::SetInterested()
{
	m_interestedEvents.insert(std::make_pair(Event::EVENT_ADD_RENDERABLE, (Event*)0));
	m_interestedEvents.insert(std::make_pair(Event::EVENT_DESTROY_OBJECT, (Event*)0));
}

//--------------------------------------------------
/**
* Handles events
*
**/
void Renderer::HandleEvent(Event *const e)
{
	switch (e->GetCode())
	{
	case Event::EVENT_ADD_RENDERABLE:
		{
			AddRenderableEvent* const pAddEvent = static_cast<AddRenderableEvent*>(e);
			if (pAddEvent->m_pRenderableObject)
			{
				AddRenderable(pAddEvent->m_pRenderableObject);
			}
		}
		break;

	case Event::EVENT_DESTROY_RENDERABLE:
		{
			RemoveRenderableEvent* const pAddEvent = static_cast<RemoveRenderableEvent*>(e);
			if (pAddEvent->m_pRenderableObject)
			{
				RemoveRenderable(pAddEvent->m_pRenderableObject);
			}
		}
		break;

	default:
		return;
	}
}

//----------------------------------------------
/**
* Opengl.Org code: checks if VBO's are supported
*/
bool Renderer::IsVBOExtensionSupported()
{
	const unsigned char *pszExtensions = NULL;
	const unsigned char *pszStart;
	char* szTargetExtension = "GL_ARB_vertex_buffer_object";
	unsigned char *pszWhere, *pszTerminator;

	// Extension names should not have spaces
	pszWhere = (unsigned char *) strchr( szTargetExtension, ' ' );
	if( pszWhere || *szTargetExtension == '\0' )
		return false;

	// Get Extensions String
	pszExtensions = glGetString( GL_EXTENSIONS );

	// Search The Extensions String For An Exact Copy
	pszStart = pszExtensions;
	for(;;)
	{
		pszWhere = (unsigned char *) strstr( (const char *) pszStart, szTargetExtension );
		if( !pszWhere )
			break;
		pszTerminator = pszWhere + strlen( szTargetExtension );
		if( pszWhere == pszStart || *( pszWhere - 1 ) == ' ' )
			if( *pszTerminator == ' ' || *pszTerminator == '\0' )
				return true;
		pszStart = pszTerminator;
	}
	return false;
}
