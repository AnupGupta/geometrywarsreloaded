#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"
#include "Color.h"


class Particle 
{
public:

	Particle();
	~Particle();

	void Update(float dt);

	void SetTotalEnergy(float energy)
	{
		if (energy > 0.0f)
		{
			m_fTotalEnergy = energy;
			m_fInvTotalEnergy = 1.0f / m_fTotalEnergy;
			m_fEnergy = energy;
		}
		else
		{
			m_fTotalEnergy = 1.0f;
			m_fInvTotalEnergy = 1.0f;
			m_fEnergy = 0.0f;
		}
		
	}

	void SetVelocity (const mth::Vector2& vel)
	{
		m_vVelocity = vel;
	}

	void SetPosition (const mth::Vector2& pos)
	{
		m_vPosition = pos;
	}

	bool Dead() const
	{
		return !m_bAlive;
	}

	void MakeAlive()
	{
		m_bAlive = true;
	}

	const mth::Vector2& GetPosition() const
	{
		return m_vPosition;
	}

	const mth::Vector2& GetVelocity() const
	{
		return m_vVelocity;
	}

	void SetColor(const Color& color);
	const Color& GetColor() const
	{
		return m_color;
	}

private:

	mth::Vector2 m_vVelocity;
	mth::Vector2 m_vPosition;
	float m_fEnergy;
	float m_fTotalEnergy;
	float m_fInvTotalEnergy;
	bool  m_bAlive;
	Color m_color;


};

#endif