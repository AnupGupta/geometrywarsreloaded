#ifndef RENDERER_H
#define RENDERER_H

class Renderable;

#include "EventListener.h"
#include <list>

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

private:
	typedef std::list<Renderable*> RenderableList;

	static Renderer* ms_pInstance;
	RenderableList m_renderables;

	Renderer();
	~Renderer();

	void SetInterested();
	void HandleEvent(Event* const e);
};

#endif