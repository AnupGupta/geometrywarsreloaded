#ifndef RENDERABLE_H
#define RENDERABLE_H

class GameObject;

class Renderable
{
public:

	Renderable(const GameObject& parent) : 
	  m_rParent(parent),
	  m_fScale(1.0f),
	  m_bInitialized(false)
	{

	}
	virtual ~Renderable()
	{
	}

	virtual bool Init() = 0;
	virtual void Render() = 0;
	
	float GetScale() const
	{
		return m_fScale;
	}

	void SetScale(float scale)
	{
		m_fScale = scale;
	}

	bool IsInitialized() const
	{
		return m_bInitialized;
	}

protected:

	const GameObject& m_rParent;
	bool m_bInitialized;
	float m_fScale;

	virtual void Shutdown() = 0;
};

#endif