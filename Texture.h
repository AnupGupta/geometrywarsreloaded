#ifndef TEXTURE_H
#define TEXTURE_H


class Texture
{
	
public:

	enum EnvironmentState
	{
		STATE_MODULATE,
		STATE_DECAL,
		STATE_BLEND,
		STATE_REPLACE

	};

	enum TextureFileType
	{
		FILETYPE_BMP,
		FILETYPE_TGA,
		FILETYPE_JPG,
		FILETYPE_PNG
	};

	Texture(unsigned int id,
					TextureFileType kFileType);
	~Texture();


	TextureFileType GetFileType() const
	{
		return m_eFileType;
	}

	unsigned int GetId() const
	{
		return m_uiTexId;
	}

	// sets texture environment state
	void SetEnvironmentState(EnvironmentState state);

	static unsigned int GetNewTextureId();

private:

	unsigned int m_uiTexId;
	EnvironmentState m_eEnvState;
	TextureFileType m_eFileType;
	
};


#endif