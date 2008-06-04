#ifndef RENDERABLE_H
#define RENDERABLE_H

class GameObject;

#include "Color.h"
#include <map>
#include <list>
#include "Vector.h"
using namespace mth;

class Texture;

class Renderable
{
public:

	Renderable(const GameObject& parent);
	virtual ~Renderable();

	virtual bool Init() = 0;
	void RenderDefault();
	
	float GetScale() const
	{
		return m_fScale;
	}

	void SetScale(float scale)
	{
		m_fScale = scale;
	}

	void SetColor(const Color& color)
	{
		m_color = color;
	}

	bool IsInitialized() const
	{
		return m_bInitialized;
	}

	const Color& GetColor() const
	{
		return m_color;
	}

	void SetTexture(Texture* texture);

	Texture* const GetTexture() const
	{
		return m_pTexture;
	}

protected:

	const GameObject& m_rParent;
	bool m_bInitialized;
	float m_fScale;
	Color m_color;
	Texture* m_pTexture;

	

	virtual void Render() = 0;
	virtual void Shutdown() = 0;
};

#endif