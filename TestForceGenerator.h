#ifndef TESTFORCEGENERATOR_H
#define TESTFORCEGENERATOR_H

#include "ForceGenerator.h"

class TestForceGenerator : public ForceGenerator
{
public:

	TestForceGenerator();
	~TestForceGenerator();

	void UpdateForce(Movable* movable);
};

#endif