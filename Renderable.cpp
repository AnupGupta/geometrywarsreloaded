#include "Renderable.h"
#include "LoaderTgaGL.h"
#include "Texture.h"
#include "Renderer.h"
#include <gl/glut.h>
//--------------------------------------------------
/**
* Ctor
*
**/
Renderable::Renderable(const GameObject& parent) : 
m_rParent(parent),
m_fScale(1.0f),
m_bInitialized(false),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_pTexture(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
Renderable::~Renderable()
{
}

//--------------------------------------------------
/**
* Default render
*
**/
void Renderable::RenderDefault()
{
	const float* const color = m_color.GetColor();
	glColor4f(color[0], color[1], color[2], color[3]);
	

	Render();

	
}

//--------------------------------------------------
/**
* Sets texture
*
**/
void Renderable::SetTexture(Texture* texture)
{
	if (m_pTexture)
	{
		Renderer::GetInstance()->
			UnbindRenderableFromTexture(texture, this);
	}

	m_pTexture = texture;

}