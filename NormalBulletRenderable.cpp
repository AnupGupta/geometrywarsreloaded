#include "NormalBulletRenderable.h"
#include "GameObject.h"
#include "Texture.h"
#include "LoaderBmpGL.h"
#include <gl\glut.h>
//--------------------------------------------------
/**
* Ctor
*
**/
NormalBulletRenderable::NormalBulletRenderable(const GameObject& parent)
: Renderable(parent),
  m_uiDL(0)
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
NormalBulletRenderable::~NormalBulletRenderable()
{
	Shutdown();
}

//--------------------------------------------------
/**
* Initializes renderable
*
**/
bool NormalBulletRenderable::Init()
{
	m_uiDL = glGenLists(1);
	glNewList(m_uiDL, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	glEndList();

	m_fScale = 1.5f;



	return m_bInitialized = m_uiDL > 0;
}
//--------------------------------------------------
/**
* Renders NormalBullet
*
**/
void NormalBulletRenderable::Render()
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
void NormalBulletRenderable::Shutdown()
{
	glDeleteLists(m_uiDL, 1);
}