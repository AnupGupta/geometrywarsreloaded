#ifndef ARROWRENDERABLE_H
#define ARROWRENDERABLE_H

#include "Renderable.h"

class ArrowRenderable : public Renderable
{

public:

	ArrowRenderable(const GameObject& parent);
	~ArrowRenderable();

	bool Init();
	void Render();


private:

	unsigned int m_uiDL;

	void Shutdown();
};

#endif