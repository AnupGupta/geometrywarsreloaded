#ifndef PARTICLE_H
#define PARTICLE_H

#include "GameObject.h"
#include "Color.h"

class Particle : public GameObject
{
public:

	Particle();
	~Particle();

	bool Init();
	void Update();
	void UpdateTimeDependent(float dt);
	void Shutdown();
	void Reset();

	ObjectType GetType() const
	{
		return kObjectParticle;
	}

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

	bool Dead() const
	{
		return !m_bAlive;
	}

	void MakeAlive()
	{
		m_bAlive = true;
	}

	void SetColor(const Color& color);
	const Color& GetColor() const
	{
		return m_color;
	}

private:

	float m_fEnergy;
	float m_fTotalEnergy;
	float m_fInvTotalEnergy;
	bool  m_bAlive;
	Color m_color;


};

#endif