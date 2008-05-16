#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"

class Particle 
{
public:

	Particle();
	~Particle();

	void Update(float dt);

	void SetEnergy(float energy)
	{
		m_fEnergy = energy;
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

private:

	mth::Vector2 m_vVelocity;
	mth::Vector2 m_vPosition;
	float m_fEnergy;
	bool  m_bAlive;

};

#endif