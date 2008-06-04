#ifndef LOADERBMPGL_H
#define LOADERBMPGL_H

class Texture;

class LoaderBmpGL
{
public:

	
	static Texture* Load(const char *filename, bool bUseMipMaps);

	// unloads a texture
	static void Unload(Texture* texture);

private:
	LoaderBmpGL();
	~LoaderBmpGL();

	

	
};

#endif
