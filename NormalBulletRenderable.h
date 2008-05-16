#ifndef NORMALBULLETRENDERABLE_H
#define NORMALBULLETRENDERABLE_H

#include "Renderable.h"

class NormalBulletRenderable : public Renderable
{
public:

	NormalBulletRenderable(const GameObject& parent);
	~NormalBulletRenderable();

	bool Init();
	void Render();


private:

	unsigned int m_uiDL;

	void Shutdown();
};

#endif