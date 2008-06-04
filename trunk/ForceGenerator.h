#ifndef FORCEGENERATOR_H
#define FORCEGENERATOR_H

class Movable;

class ForceGenerator
{
public:

	ForceGenerator()
	{

	}
	virtual ~ForceGenerator()
	{

	}

	virtual void UpdateForce (Movable* movable) = 0;


};

#endif