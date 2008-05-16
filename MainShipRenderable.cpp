#include "MainShipRenderable.h"
#include "GameObject.h"
#include <gl\glut.h>
//--------------------------------------------------
/**
* Ctor
*
**/
MainShipRenderable::MainShipRenderable(const GameObject& parent)
: Renderable(parent),
  m_uiDL(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
MainShipRenderable::~MainShipRenderable()
{
	Shutdown();
}

//--------------------------------------------------
/**
* Initializes renderable
*
**/
bool MainShipRenderable::Init()
{
	m_uiDL = glGenLists(1);
	glNewList(m_uiDL, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glEnd();
	glEndList();

	return m_bInitialized = m_uiDL > 0;
}
//--------------------------------------------------
/**
* Renders mainship
*
**/
void MainShipRenderable::Render()
{
	const Vector2& position = m_rParent.GetPosition();
	float rotation = m_rParent.GetRotation();

	glColor3f(1.0f, 1.0f, 1.0f);
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
void MainShipRenderable::Shutdown()
{
	glDeleteLists(m_uiDL, 1);
}