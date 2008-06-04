#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	Color(float r, float g, float b, float a)
	{
		SetColor(r,g,b,a);
	}
	~Color()
	{

	}

	void SetColor(float r, float g, float b)
	{
		m_color[0] = r;
		m_color[1] = g;
		m_color[2] = b;
		
	}
	void SetColor(float r, float g, float b, float a)
	{
		m_color[0] = r;
		m_color[1] = g;
		m_color[2] = b;
		m_color[3] = a;
	}
	void SetAlpha(float a)
	{
		m_color[3] = a;
	}

	const float* const GetColor() const
	{
		return m_color;
	}

private:

	float m_color[4];
};

#endif