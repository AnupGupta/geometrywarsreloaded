#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector.h"
class Renderable;

using namespace mth;

class GameObject
{

public:

	enum ObjectType
	{
		kObjectNone = 0,
		kObjectMovable,
		kObjectShip,
		kObjectMainShip,
		kObjectNormalBullet,
		kObjectTargetArrow,
		kObjectParticleEmitter,
		kObjectParticle

	};

	GameObject();
	virtual ~GameObject();

	virtual bool Init() = 0;

	virtual void Update() = 0;

	virtual void UpdateTimeDependent(float dt) = 0;

	virtual void Shutdown() = 0;

	virtual void Reset();

	virtual ObjectType GetType() const = 0;

	const Vector2& GetPosition() const
	{
		return m_vPosition;
	}

	float GetRotation() const
	{
		return m_fRotation;
	}

	void SetPosition(const Vector2& position)
	{
		m_vPosition = position;
	}

	bool InheritsFromMovable()
	{
		ObjectType t = GetType();
		return  (t == kObjectMovable ||
			t == kObjectShip ||
			t == kObjectMainShip ||
			t == kObjectNormalBullet ||
			t == kObjectTargetArrow ||
			t == kObjectParticleEmitter ||
			t == kObjectParticle);
	}
	
	Renderable* GetRenderable() const
	{
		return m_pRenderable;
	}

	bool IsInitialized() const
	{
		return m_bInitialized;
	}

protected:

	Vector2 m_vPosition;
	float   m_fRotation;
	bool    m_bInitialized;

	Renderable* m_pRenderable;


};

#endif