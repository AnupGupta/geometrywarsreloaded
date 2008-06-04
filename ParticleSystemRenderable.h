#ifndef PARTICLESYSTEMRENDERABLE_H
#define PARTICLESYSTEMRENDERABLE_H

#include "Renderable.h"
#include <gl/glut.h>
#include <gl/glext.h>

class Particle;

class ParticleSystemRenderable : public Renderable
{

public:

	ParticleSystemRenderable(const GameObject& parent,
		unsigned int numParticles);
	~ParticleSystemRenderable();

	bool Init();
	void Render();
	
	void SetParticleSize(float size)
	{
		if (size <= m_fMaxParticleSize)
			m_fParticleSize = size;
	}

	
private:

	unsigned int m_uiVBO;
	unsigned int m_uiVBOColors;

	unsigned int m_uiNumParticles;
	float*       m_pParticlePositions;
	float*       m_pParticleColors;
	float        m_fMaxParticleSize;
	float        m_fParticleSize;


	// VBO Extension Function Pointers
	// VBO Name Generation Procedure
	PFNGLGENBUFFERSARBPROC glGenBuffersARB;	
	// VBO Bind Procedure
	PFNGLBINDBUFFERARBPROC glBindBufferARB;			
	// VBO Data Loading Procedure
	PFNGLBUFFERDATAARBPROC glBufferDataARB;		
	// VBO Deletion Procedure
	PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
	// VBO map procedure
	PFNGLMAPBUFFERARBPROC glMapBufferARB;
	// VBO unmap procedure
	PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;
	// VBO subdata
	PFNGLBUFFERSUBDATAPROC glBufferSubData;
	PFNGLPOINTPARAMETERFARBPROC  glPointParameterfARB;
	PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB;
	
	void UpdateParticlePositions();
	void UpdateParticleColors();
	void Shutdown();

};

#endif