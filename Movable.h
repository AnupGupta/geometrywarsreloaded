#ifndef MOVABLE_H
#define MOVABLE_H

#include "GameObject.h"

class Movable : public GameObject
{
public:
	
	Movable();
	virtual ~Movable();

	virtual bool Init() = 0;
	
	virtual void Shutdown() = 0;

	virtual void Reset();

	virtual void Update() = 0;

	virtual void UpdateTimeDependent(float dt);

	virtual ObjectType GetType() const
	{
		return kObjectMovable;
	}

	const Vector2& GetVelocity() const
	{
		return m_vVelocity;
	}

	const Vector2& GetAcceleration() const
	{
		return m_vAcceleration;
	}

	const Vector2& GetForce() const
	{
		return m_vForce;
	}

	float GetTorque() const
	{
		return m_fTorque;
	}

	float GetAngularAcceleration() const
	{
		return m_fAngularAcceleration;
	}

	float GetAngularVelocity() const
	{
		return m_fAngularVelocity;
	}

	float GetMass() const
	{
		return m_fMass;
	}

	float GetInertia() const
	{
		return m_fInertia;
	}

	void SetMass (float mass)
	{
		m_fMass = mass;
	}

	void SetInertia (float inertia)
	{
		m_fInertia = inertia;
	}

	void SetAcceleration(const Vector2& acc)
	{
		m_vAcceleration = acc;
	}

	void SetVelocity (const Vector2& vel)
	{
		m_vVelocity = vel;
	}

	void SetAngularAcceleration(float angAcc)
	{
		m_fAngularAcceleration = angAcc;
	}
	void SetAngularVelocity (float angVel)
	{
		m_fAngularVelocity = angVel;
	}

	void SetForce(const Vector2& force)
	{
		m_vForce = force;
	}

	void SetTorque(float torque)
	{
		m_fTorque = torque;
	}


protected:

	Vector2 m_vVelocity;
	Vector2 m_vAcceleration;
	Vector2 m_vForce;
	float m_fAngularVelocity;
	float m_fAngularAcceleration;
	float m_fMass;
	float m_fInertia;
	float m_fTorque;

	
};

#endif