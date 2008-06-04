#ifndef FORCEGENERATOR_H
#define FORCEGENERATOR_H

#include "Vector.h"

class ForceGenerator
{
public:

	ForceGenerator()
	{

	}
	virtual ~ForceGenerator()
	{

	}

	virtual void UpdateForce (mth::Vector2& force,
		const mth::V) = 0;


};

#endif