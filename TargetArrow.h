#ifndef TARGETARROW_H
#define TARGETARROW_H

#include "Movable.h"


class Ship;

class TargetArrow : public Movable
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