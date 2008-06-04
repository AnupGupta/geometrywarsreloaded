#ifndef RENDERER_H
#define RENDERER_H

class Renderable;

#include "EventListener.h"
#include <list>
#include <map>
#include <string>

class Texture;

class Renderer : public EventListener
{
public:

	static Renderer* GetInstance();
	static void Destroy();

	bool Init();
	void Render();
	void Resize(int width, int height);

	bool AddRenderable(Renderable* renderable);
	void RemoveRenderable(Renderable* renderable);
	
	bool IsVBOExtensionSupported();

	Texture* GetTexture(const std::string& name);

	void BindRenderableToTexture(Texture* texture, Renderable* renderable);
	void UnbindRenderableFromTexture(Texture* texture, Renderable* renderable);

private:
	typedef std::list<Renderable*> RenderableList;
	typedef std::map<std::string, Texture*> TextureMap;
	typedef std::map<Texture*, RenderableList*> SortedMap;
	

	static Renderer* ms_pInstance;
	RenderableList m_renderables;
	TextureMap m_textures;
	SortedMap m_sorted;

	Renderer();
	~Renderer();

	Texture* LoadTextures();
	void SetInterested();
	void HandleEvent(Event* const e);
};

#endif