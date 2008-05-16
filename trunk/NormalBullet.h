#ifndef NORMALBULLET_H
#define NORMALBULLET_H

#include "Movable.h"
#include "Helper.h"

class Timer;

class NormalBullet : public Movable
{
public:

	NormalBullet();
	~NormalBullet();

	bool Init();
	void Update();
	void UpdateTimeDependent(float dt);
	void Shutdown();

	void Reset();

	ObjectType GetType() const
	{
		return kObjectNormalBullet;
	}

	void Shoot (const Vector2& initialPosition,
		float rotation, float velocity)
	{
		m_vPosition = initialPosition;
		m_fRotation = rotation;
		m_vVelocity = Helper::AsVector(m_fRotation) * velocity;
		m_bShot = true;
	};

	bool IsShot() const
	{
		return m_bShot;
	}
	

private:

	float m_fVelocity;
	bool  m_bShot;
	Timer* m_pLifeTimer;

	
};

#endif