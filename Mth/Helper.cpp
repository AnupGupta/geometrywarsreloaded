/**********************************************
*  Namespace: mth
*  Classes:   Helper
*  Desc:      Various helper functions and constants
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#include "Helper.h"

namespace mth
{
	//------------------------------------------------------------------------
	/**
	* Limits an angle between minV and maxV
	*
	**/
	float Helper::ClampAngle(float radians, float minV, float maxV) 
	{
		while (radians > maxV)
		{
			radians -= M_PI_2;
		}
		while (radians < minV)
		{
			radians += M_PI_2;
		}

		return radians;
	}

	//------------------------------------------------------------------------
	/**
	* returns random number between -1 and 1
	*
	**/
	float Helper::RandomBinomial() 
	{
		return (float)(rand()%100 - rand()%100) / 100.0f;
	}

	//------------------------------------------------------------------------
	/**
	* returns a float as a vector2
	*
	**/
	Vector2 Helper::AsVector(float value) 
	{
		return Vector2(sin(-value), cos(value));
	}
}
