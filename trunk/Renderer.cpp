#include "Renderer.h"
#include <windows.h>
#include "Renderable.h"
#include "AddRenderableEvent.h"
#include "RemoveRenderableEvent.h"
#include "EventManager.h"
#include "Texture.h"
//#include "TextureLoader.h"
#include "LoaderBmpGL.h"
#include "LoaderTgaGL.h"
#include <stdlib.h>
#include <stdio.h>
#include <gl\glut.h>
#include <assert.h>

using namespace std;

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

	SortedMap::iterator sortedIt = m_sorted.begin();
	for (; sortedIt != m_sorted.end(); ++sortedIt)
	{
		RenderableList* renderList = sortedIt->second;
		renderList->clear();
		delete renderList;
	}
	m_sorted.clear();

	m_renderables.clear();
	TextureMap::iterator it = m_textures.begin();
	for (; it != m_textures.end(); ++it)
	{
		Texture* texture = it->second;
		if (texture->GetFileType() == Texture::FILETYPE_BMP)
		{
			LoaderBmpGL::Unload(texture);
		}
		else if (texture->GetFileType() == Texture::FILETYPE_TGA)
		{
			LoaderTgaGL::Unload(texture);
		}

	}
	m_textures.clear();
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

	LoadTextures();

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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glEnable(GL_TEXTURE_2D);
	SortedMap::iterator sortedIt = m_sorted.begin();
	for (; sortedIt != m_sorted.end(); ++sortedIt)
	{
		RenderableList* renderList = sortedIt->second;
		glBindTexture(GL_TEXTURE_2D, sortedIt->first->GetId());

		RenderableList::iterator it = renderList->begin();
		for (; it != renderList->end(); ++it)
		{
			(*it)->RenderDefault();
		}
	}
	glDisable(GL_TEXTURE_2D);

	RenderableList::iterator it = m_renderables.begin();
	for (; it != m_renderables.end(); ++it)
	{
		Renderable* renderable = (*it);
		if (!renderable->GetTexture())
		{
			renderable->RenderDefault();
		}

	}

	glDisable(GL_DEPTH_TEST);
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
		
		Texture* texture = renderable->GetTexture();
		if (texture)
		{
			BindRenderableToTexture(texture, renderable);
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
	assert (renderable);

	RenderableList::iterator it = m_renderables.begin();
	for (; it != m_renderables.end(); ++it)
	{
		Renderable* r = (*it);
		if (r == renderable)
		{
			Texture* texture = r->GetTexture();
			if (texture)
			{
				UnbindRenderableFromTexture(texture, r);
			}
			m_renderables.erase(it);
			return;
		}
	}
}

//--------------------------------------------------
/**
* Gets a texture by name
*
**/
Texture* Renderer::GetTexture(const std::string& name)
{
	TextureMap::iterator it = m_textures.find(name);
	if (it != m_textures.end())
	{
		return it->second;
	}
	
	return 0;
}

//--------------------------------------------------
/**
* Loads all textures from the textures folder
*
**/
Texture* Renderer::LoadTextures()
{
	// get all textures from textures directory
	WIN32_FIND_DATA fd;
	DWORD dwAttr = FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_HIDDEN;
	HANDLE hFind = FindFirstFile( "Assets/Textures/*.bmp*", &fd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		int count = 0;
		do
		{
			if( !(fd.dwFileAttributes & dwAttr))
			{
				string longName("Assets/Textures/");
				longName += fd.cFileName;
				Texture* t = LoaderBmpGL::Load(longName.c_str(), false);
				if (t)
				{
					string shortName(fd.cFileName);
					
					m_textures.insert(make_pair(shortName.substr(0, shortName.length() - 4), t));
				}
			}
			
		}while( FindNextFile( hFind, &fd));
		FindClose( hFind);

	}
	hFind = FindFirstFile( "Assets/Textures/*.tga*", &fd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		int count = 0;
		do
		{
			if( !(fd.dwFileAttributes & dwAttr))
			{
				string longName("Assets/Textures/");
				longName += fd.cFileName;
				Texture* t = LoaderTgaGL::Load(longName.c_str(), false);
				if (t)
				{
					string shortName(fd.cFileName);

					m_textures.insert(make_pair(shortName.substr(0, shortName.length() - 4), t));
				}
			}

		}while( FindNextFile( hFind, &fd));
		FindClose( hFind);

	}

	return 0;
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

//--------------------------------------------------
/**
* Pairs a renderable with a texture for sorting
*
**/
void Renderer::BindRenderableToTexture(Texture* texture, 
									   Renderable* renderable)
{
	assert(texture);
	assert(renderable);

	SortedMap::iterator it = m_sorted.find(texture);
	if (it != m_sorted.end())
	{
		RenderableList* renderList = it->second;
		RenderableList::iterator renderIt = renderList->begin();
		for (; renderIt != renderList->end(); ++renderIt)
		{
			if (renderable == (*renderIt))
				return;
		}

		renderList->push_back(renderable);
	}
	else
	{
		RenderableList* renderList = new RenderableList();
		renderList->push_back(renderable);
		m_sorted.insert(make_pair(texture, renderList));
	}
}

//--------------------------------------------------
/**
* Removes a renderable from its texture
*
**/
void Renderer::UnbindRenderableFromTexture(Texture* texture, 
									   Renderable* renderable)
{
	assert(texture);
	assert(renderable);

	SortedMap::iterator it = m_sorted.find(texture);
	if (it != m_sorted.end())
	{
		it->second->remove(renderable);
	}
}