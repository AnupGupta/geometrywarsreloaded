/**********************************************
*  Classes:   LoaderBmpGL
*  Desc:      Loads .bmp files and creates
*		      TextureProperties
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#include "LoaderBmpGL.h"
#include "Texture.h"
#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>
#include <gl/glaux.h>
//-----------------------------------------------
/**
* Ctor
*/
LoaderBmpGL::LoaderBmpGL()
{
}
//-----------------------------------------------
/**
* Dtor
*/
LoaderBmpGL::~LoaderBmpGL()
{
}
//-----------------------------------------------
/**
* Loads a bmp file and converts it to a TextureProperty
*/
Texture* LoaderBmpGL::Load(const char* filename,
								   bool bUseMipMaps)
{
	if (!filename) return 0;

	
	FILE *File=fopen(filename,"r");									

	AUX_RGBImageRec* rec[1];
	memset(rec,0,sizeof(void *)*1);
	// Does The File Exist?
	if (File)
	{
		// Close The Handle
		fclose(File);									
		// Load The Bitmap And Return A Pointer
		rec[0] = auxDIBImageLoad(filename);				
	}

	if (!rec[0]) return 0;

	unsigned int texId = Texture::GetNewTextureId();
	if (!texId) return 0;
	
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texId);
	if (bUseMipMaps)
	{
		// build our texture mipmaps
		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, rec[0]->sizeX, rec[0]->sizeY,
			GL_RGB, GL_UNSIGNED_BYTE, rec[0]->data );

		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_NEAREST );
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
			rec[0]->sizeX, rec[0]->sizeY, 
			0, GL_RGB, GL_UNSIGNED_BYTE, rec[0]->data);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		
	}
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	// If Texture Exists
	if (rec[0])									
	{
		// If Texture Image Exists
		if (rec[0]->data)							
		{
			// Free The Texture Image Memory
			free(rec[0]->data);					
		}

		// Free The Image Structure
		free(rec[0]);								
	}

	return new Texture(texId ,Texture::FILETYPE_BMP);
}
//-----------------------------------------------
/**
* Unloads a texture
*/
void LoaderBmpGL::Unload(Texture* texture)
{
	if (texture)
	{
		unsigned int id = texture->GetId();
		glDeleteTextures(1, &id);
		delete texture;
	}
}
