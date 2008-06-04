#include "ArrowRenderable.h"
#include "GameObject.h"
#include <gl\glut.h>
//--------------------------------------------------
/**
* Ctor
*
**/
ArrowRenderable::ArrowRenderable(const GameObject& parent)
: Renderable(parent),
m_uiDL(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
ArrowRenderable::~ArrowRenderable()
{
	Shutdown();
}

//--------------------------------------------------
/**
* Initializes renderable
*
**/
bool ArrowRenderable::Init()
{
	m_uiDL = glGenLists(1);
	glNewList(m_uiDL, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glEnd();
	glEndList();

	m_fScale = 0.5f;

	return m_bInitialized = m_uiDL > 0;
}
//--------------------------------------------------
/**
* Renders Arrow
*
**/
void ArrowRenderable::Render()
{
	const Vector2& position = m_rParent.GetPosition();
	float rotation = m_rParent.GetRotation();

	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	glScalef(m_fScale, m_fScale, m_fScale);
	glCallList(m_uiDL);
	glPopMatrix();
}

//--------------------------------------------------
/**
* Shuts down renderable
*
**/
void ArrowRenderable::Shutdown()
{
	glDeleteLists(m_uiDL, 1);
}