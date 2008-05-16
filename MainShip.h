#ifndef MAINSHIP_H
#define MAINSHIP_H

#include "Ship.h"
#include <list>

class NormalBullet;
class TargetArrow;

class MainShip : public Ship
{
public:

	MainShip();
	~MainShip();

	bool Init();
	void Update();
	void Reset();
	void Shutdown();

	ObjectType GetType() const
	{
		return kObjectMainShip;
	}

	void MoveUp()
	{
		m_bMoveUp = true;
		m_bStopMoveDown = m_bMoveDown;
		m_bStopMoveUp = false;
	}

	void MoveDown()
	{
		m_bMoveDown = true;
		m_bStopMoveUp = m_bMoveUp;
		m_bStopMoveDown = false;
	}

	void MoveLeft()
	{
		m_bMoveLeft = true;
		m_bStopMoveRight = m_bMoveRight;
		m_bStopMoveLeft = false;
	}

	void MoveRight()
	{
		m_bMoveRight = true;
		m_bStopMoveLeft = m_bMoveLeft;
		m_bStopMoveRight = false;
		
	}

	void StopMoveUp()
	{
		m_bMoveUp = false;
		m_bStopMoveDown = false;
		
	}

	void StopMoveDown()
	{
		m_bMoveDown = false;
		m_bStopMoveUp = false;
	}

	void StopMoveRight()
	{
		m_bMoveRight = false;
		m_bStopMoveLeft = false;
	}

	void StopMoveLeft()
	{
		m_bMoveLeft = false;
		m_bStopMoveRight = false;
	}


	bool IsAlive() const
	{
		return m_bAlive;
	}

	void SetAlive (bool value)
	{
		m_bAlive = value;
	}

	void ShootNormal();

private:

	typedef std::list<NormalBullet*> BulletList;

	bool m_bMoveUp;
	bool m_bMoveLeft;
	bool m_bMoveRight;
	bool m_bMoveDown;
	bool m_bStopMoveUp;
	bool m_bStopMoveLeft;
	bool m_bStopMoveRight;
	bool m_bStopMoveDown;

	bool m_bAlive;

	const unsigned int m_numBullets;
	BulletList m_bullets;

	TargetArrow* m_pTargetArrow;

	void SetInterested();
	void HandleEvent(Event* const e);

	
};
#endif