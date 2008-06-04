#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector.h"

class Renderable;
class Movable;

class GameObject
{

public:

	enum ObjectType
	{
		kObjectNone = 0,
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

	virtual void UpdateTimeDependent(float dt);

	virtual void Shutdown() = 0;

	virtual void Reset();

	virtual ObjectType GetType() const = 0;

	Renderable* GetRenderable() const
	{
		return m_pRenderable;
	}

	Movable* GetMovable() const
	{
		return m_pMovable;
	}

	bool IsInitialized() const
	{
		return m_bInitialized;
	}

	const mth::Vector2& GetPosition() const
	{
		return m_vPosition;
	}

	float GetRotation() const
	{
		return m_fRotation;
	}

	void SetPosition (const mth::Vector2& pos)
	{
		m_vPosition = pos;
	}

	void SetRotation (float rotation)
	{
		m_fRotation = rotation;
	}

protected:

	bool    m_bInitialized;

	mth::Vector2 m_vPosition;
	float        m_fRotation;

	Renderable* m_pRenderable;
	Movable* m_pMovable;
};

#endif