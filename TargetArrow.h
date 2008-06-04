#ifndef TARGETARROW_H
#define TARGETARROW_H

#include "GameObject.h"


class Ship;

class TargetArrow : public GameObject
{
public:

	TargetArrow();
	~TargetArrow();

	bool Init();
	void Update();
	void Shutdown();

	void Reset();

	ObjectType GetType() const
	{
		return kObjectTargetArrow;
	}

	void SetParentShip (Ship* parent)
	{
		m_pParentShip = parent;
	}

private:

	Ship* m_pParentShip;

};

#endif