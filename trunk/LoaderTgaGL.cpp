#include "LoaderTgaGL.h"
#include "Texture.h"
#include <windows.h>
#include <gl/glut.h>
#include <gl/glaux.h>
#include <stdio.h>
//-----------------------------------------------
/**
* Ctor
*/
LoaderTgaGL::LoaderTgaGL()
{
}
//-----------------------------------------------
/**
* Dtor
*/
LoaderTgaGL::~LoaderTgaGL()
{
}
//-----------------------------------------------
/**
* Loads a bmp file and converts it to a TextureProperty
*/
Texture* LoaderTgaGL::Load(const char* filename,
								   bool bUseMipMaps)
{
	if (!filename) return 0;

	// Uncompressed TGA Header
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	
	// Used To Compare TGA Header
	GLubyte		TGAcompare[12];								
	// First 6 Useful Bytes From The Header
	GLubyte		header[6];									
	// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		bytesPerPixel;								
	// Used To Store The Image Size When Setting Aside Ram
	GLuint		imageSize;									
	// Temporary Variable
	GLuint		temp;										
	// Set The Default GL Mode To RBGA (32 BPP)
	GLuint		type=GL_RGBA;								

	// Open The TGA File
	FILE *file = fopen(filename, "rb");						

	// Does File Even Exist?
	if(	!file ||										
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	
		fread(header,1,sizeof(header),file)!=sizeof(header))				
	{
		if (!file)									
			return 0;									
		else
		{
			fclose(file);									
			return 0;									
		}
	}

	TextureImage texture;
	texture.width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture.height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	texture.width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture.height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return 0;										// Return False
	}

	texture.bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture.bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture.width*texture.height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture.imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if(	!texture.imageData ||							// Does The Storage Memory Exist?
		fread(texture.imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture.imageData)						// Was Image Data Loaded
			free(texture.imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return 0;										// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture.imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture.imageData[i] = texture.imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture.imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

	// Build A Texture From The Data
	texture.texID = Texture::GetNewTextureId();	

	glBindTexture(GL_TEXTURE_2D, texture.texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	
	if (texture.bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 
		0, type, texture.width, 
		texture.height, 0, type, 
		GL_UNSIGNED_BYTE, texture.imageData);

	return new Texture(texture.texID, 
		Texture::FILETYPE_TGA);											
}
//-----------------------------------------------
/**
* Unloads a texture
*/
void LoaderTgaGL::Unload(Texture* texture)
{
	if (texture)
	{
		unsigned int id = texture->GetId();
		glDeleteTextures(1, &id);
		delete texture;
	}
}