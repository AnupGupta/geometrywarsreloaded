#include "TestForceGenerator.h"
#include "Movable.h"

using namespace mth;

//--------------------------------------------------
/**
* Ctor
*
**/
TestForceGenerator::TestForceGenerator()
{

}

//--------------------------------------------------
/**
* Dtor
*
**/
TestForceGenerator::~TestForceGenerator()
{

}

//--------------------------------------------------
/**
* Updates force
*
**/
void TestForceGenerator::UpdateForce(Movable *movable)
{
	movable->SetForce(Vector2(20.0f, 0.0f));
}