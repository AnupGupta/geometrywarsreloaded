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
	

private:

	unsigned int m_uiVBO;
	unsigned int m_uiVBOColors;

	unsigned int m_uiNumParticles;
	float*       m_pParticlePositions;
	float*       m_pParticleColors;

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
	
	void UpdateParticlePositions();
	void UpdateParticleColors();
	void Shutdown();

};

#endif