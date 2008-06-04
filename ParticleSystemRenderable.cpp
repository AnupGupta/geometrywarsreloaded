#include "ParticleSystemRenderable.h"
#include "Particle.h"
#include "GameObject.h"
#include "ParticleEmitter.h"
#include "Texture.h"
#include <gl\glut.h>
#include <gl\glext.h>

//--------------------------------------------------
/**
* Ctor
*
**/
ParticleSystemRenderable::ParticleSystemRenderable(const GameObject& parent,
												   unsigned int numParticles)
: Renderable(parent),
  m_uiVBO(0),
  m_uiVBOColors(0),
  m_uiNumParticles(numParticles),
  m_pParticlePositions(0),
  m_pParticleColors(0),
  m_fMaxParticleSize(1.0f)
{

	// Query for the max point size supported by the hardware
	glGetFloatv( GL_POINT_SIZE_MAX_ARB, &m_fMaxParticleSize );
}

//--------------------------------------------------
/**
* Dtor
*
**/
ParticleSystemRenderable::~ParticleSystemRenderable()
{
	Shutdown();
}

//--------------------------------------------------
/**
* Initializes renderable
*
**/
bool ParticleSystemRenderable::Init()
{
	if (m_uiNumParticles == 0) return false;

	// VBO Function Pointers
	glDeleteBuffersARB = 
		(PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");

	glBindBufferARB = 
		((PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB"));

	glGenBuffersARB = 
		((PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB"));

	glBufferDataARB = 
		((PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB"));

	glMapBufferARB = 
		((PFNGLMAPBUFFERARBPROC) wglGetProcAddress("glMapBufferARB"));

	glUnmapBufferARB = 
		((PFNGLUNMAPBUFFERARBPROC) wglGetProcAddress("glUnmapBufferARB"));

	glBufferSubData = 
		(PFNGLBUFFERSUBDATAPROC) wglGetProcAddress("glBufferSubData");

	glPointParameterfARB  = 
		(PFNGLPOINTPARAMETERFARBPROC)wglGetProcAddress("glPointParameterfARB");

	glPointParameterfvARB = 
		(PFNGLPOINTPARAMETERFVARBPROC)wglGetProcAddress("glPointParameterfvARB");

	
	m_pParticlePositions = new float[m_uiNumParticles * 2];
	if (!m_pParticlePositions) return false;

	glGenBuffersARB(1, &m_uiVBO);
	if (!m_uiVBO) return false;

	// bind VBO in order to use
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBO);

	// upload data to VBO
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_uiNumParticles * 2 * sizeof(float), m_pParticlePositions, GL_STATIC_DRAW_ARB);

	delete [] m_pParticlePositions;

	m_pParticleColors = new float[m_uiNumParticles * 4];
	if (!m_pParticleColors) return false;
  	for (int i=0; i<m_uiNumParticles * 4; i+=4)
	{
		m_pParticleColors[i] = 1.0f;
		m_pParticleColors[i+1] = 1.0f;
		m_pParticleColors[i+2] = 1.0f;
		m_pParticleColors[i+3] = 1.0f;
	}

	glGenBuffersARB(1, &m_uiVBOColors);
	if (!m_uiVBOColors) return false;

	// bind VBO in order to use
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBOColors);

	// upload data to VBO
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_uiNumParticles * 4 * sizeof(float), m_pParticleColors, GL_STATIC_DRAW_ARB);
	
	delete [] m_pParticleColors;

	
	return m_bInitialized = true;
}
//--------------------------------------------------
/**
* Updates VBO positions
*
**/
void ParticleSystemRenderable::UpdateParticlePositions()
{
	Particle* particles = (static_cast<const ParticleEmitter*>(&m_rParent))->GetParticles();
	if (particles)
	{
		// bind then map the VBO
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBO);
		m_pParticlePositions = (float*)glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
		
		// if the pointer is valid(mapped), update VBO
		if(m_pParticlePositions)
		{
			for (unsigned int i=0; i<m_uiNumParticles; i++)
			{
				const mth::Vector2& pos = particles[i].GetPosition();

				int index = 2*i;
				m_pParticlePositions[index] = pos.x;
				m_pParticlePositions[index + 1] = pos.y;

			}

			glUnmapBufferARB(GL_ARRAY_BUFFER_ARB); // unmap it after use
		}
	}
}
//--------------------------------------------------
/**
* Updates VBO colors
*
**/
void ParticleSystemRenderable::UpdateParticleColors()
{
	Particle* particles = (static_cast<const ParticleEmitter*>(&m_rParent))->GetParticles();
	if (particles)
	{
		// bind then map the VBO
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBOColors);
		m_pParticleColors = (float*)glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);

		// if the pointer is valid(mapped), update VBO
		if(m_pParticleColors)
		{
			for (unsigned int i=0; i<m_uiNumParticles; i++)
			{
				int index = 4*i;
				const Color& color = particles[i].GetColor();
				const float* const colorVals = color.GetColor();
				m_pParticleColors[index] = colorVals[0];
				m_pParticleColors[index+1] = colorVals[1];
				m_pParticleColors[index+2] = colorVals[2];
				m_pParticleColors[index+3] = colorVals[3];

			}

			glUnmapBufferARB(GL_ARRAY_BUFFER_ARB); // unmap it after use
		}
	}
}
//--------------------------------------------------
/**
* Renders ParticleSystem
*
**/
void ParticleSystemRenderable::Render()
{
	UpdateParticlePositions();
	UpdateParticleColors();

	//glColor3f(1.0f, 1.0f, 1.0f);
	// bind VBOs for vertex array and index array
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBO);         // for vertex coordinates

	// do same as vertex array except pointer
	glEnableClientState(GL_VERTEX_ARRAY);                 // activate vertex coords array
	glVertexPointer( 2, GL_FLOAT, 0, (char *) 0 );

	glEnableClientState(GL_COLOR_ARRAY);                 // activate vertex coords array
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_uiVBOColors );
	glColorPointer( 4, GL_FLOAT, 0, (char *) 0 );		// Set The TexCoord Pointer To The TexCoord Buffer

	glEnable(GL_POINT_SPRITE_ARB);
	glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	glPointSize(m_fParticleSize);

	glDrawArrays( GL_POINTS, 0, m_uiNumParticles );	
	glDisable(GL_POINT_SPRITE_ARB);
	//glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_NV);
	glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_FALSE);
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	glDisableClientState(GL_COLOR_ARRAY);                // deactivate vertex array
	glDisableClientState(GL_VERTEX_ARRAY);                // deactivate vertex array

	// bind with 0, so, switch back to normal pointer operation
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}
//--------------------------------------------------
/**
* Sets the particle size
*
**/


//--------------------------------------------------
/**
* Shuts down renderable
*
**/
void ParticleSystemRenderable::Shutdown()
{
	if (m_uiVBO)
		glDeleteBuffersARB(1, &m_uiVBO);

	if (m_uiVBOColors)
		glDeleteBuffersARB(1, &m_uiVBOColors);


	
}