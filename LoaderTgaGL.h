#ifndef LOADERTGAGL_H
#define LOADERTGAGL_H

class Texture;

class LoaderTgaGL
{
public :
	static Texture* Load(const char *filename, bool bUseMipMaps);

	// unloads a texture
	static void Unload(Texture* texture);


private:
	LoaderTgaGL();
	~LoaderTgaGL();

	typedef struct												
	{
		unsigned char *imageData;	// Image Data (Up To 32 Bits)
		unsigned int bpp;		// Image Color Depth In Bits Per Pixel.
		unsigned int width;		// Image Width
		unsigned int height;		// Image Height
		unsigned int texID;		// Texture ID Used To Select A Texture
	} TextureImage;			
	
};

#endif
