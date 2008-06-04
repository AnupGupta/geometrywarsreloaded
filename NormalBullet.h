#ifndef NORMALBULLET_H
#define NORMALBULLET_H

#include "Helper.h"
#include "GameObject.h"

class Timer;
class RandomExplosionEmitter;

class NormalBullet : public GameObject
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

	void Shoot (const mth::Vector2& initialPosition,
		float rotation, float velocity);

	bool IsShot() const
	{
		return m_bShot;
	}
	

private:

	float m_fVelocity;
	bool  m_bShot;
	Timer* m_pLifeTimer;
	RandomExplosionEmitter* m_pExplosionEmitter;

	
};

#endif