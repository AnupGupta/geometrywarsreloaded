
#include "Texture.h"
#include <gl/glut.h>

//------------------------------------------------
/**
* Ctor
*/
Texture::Texture(unsigned int id,
				    			 TextureFileType kFileType)
: m_uiTexId(id),
  m_eFileType(kFileType)
{
}
//------------------------------------------------
/**
* Dtor
*/
Texture::~Texture()
{
}

//------------------------------------------------
/**
* Sets texture environment state
*/
void Texture::SetEnvironmentState(EnvironmentState state)
{
	//CdnRenderer::GetInstance()->SetTextureEnvState(m_uiTexId, state);
}

//--------------------------------------------------
/**
* Creates a new texture id
*
**/
unsigned int Texture::GetNewTextureId()
{
	unsigned int id;
	glGenTextures(1, &id);
	return id;
}