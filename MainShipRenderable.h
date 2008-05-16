#ifndef MAINSHIPRENDERABLE_H
#define MAINSHIPRENDERABLE_H

#include "Renderable.h"

class MainShipRenderable : public Renderable
{
public:

	MainShipRenderable(const GameObject& parent);
	~MainShipRenderable();

	bool Init();
	void Render();
	

private:

	unsigned int m_uiDL;

	void Shutdown();
};

#endif