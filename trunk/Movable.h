#ifndef MOVABLE_H
#define MOVABLE_H

class GameObject;
#include "Vector.h"


class Movable 
{
public:
	
	Movable(GameObject& parent);
	virtual ~Movable();

	void Update(float dt);

	const mth::Vector2& GetPosition() const
	{
		return m_vPosition;
	}

	float GetRotation() const
	{
		return m_fRotation;
	}

	void SetPosition(const mth::Vector2& position)
	{
		m_vPosition = position;
	}

	const mth::Vector2& GetVelocity() const
	{
		return m_vVelocity;
	}

	const mth::Vector2& GetAcceleration() const
	{
		return m_vAcceleration;
	}

	const mth::Vector2& GetForce() const
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

	void SetAcceleration(const mth::Vector2& acc)
	{
		m_vAcceleration = acc;
	}

	void SetVelocity (const mth::Vector2& vel)
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

	void SetForce(const mth::Vector2& force)
	{
		m_vForce = force;
	}

	void SetTorque(float torque)
	{
		m_fTorque = torque;
	}


protected:

	mth::Vector2 m_vPosition;
	mth::Vector2 m_vVelocity;
	mth::Vector2 m_vAcceleration;
	mth::Vector2 m_vForce;
	float   m_fRotation;
	float m_fAngularVelocity;
	float m_fAngularAcceleration;
	float m_fMass;
	float m_fInertia;
	float m_fTorque;

	GameObject& m_rParent;

	
	void Integrate (float dt);
	
};

#endif