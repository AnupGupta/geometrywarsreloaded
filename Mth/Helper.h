/**********************************************
*  Namespace: mth
*  Classes:   Helper
*  Desc:      Various helper functions and constants
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/
#ifndef HELPER_H
#define HELPER_H

#include <stdlib.h>
#include "Vector.h"


namespace mth
{
	const float M_PI = 3.14159265358979323846f;
	const float M_PI_2 = 6.28318530717958647692f;
	const float TO_DEG = 57.2957795f;
	const float TO_RAD = 0.0174532925f;
	const float INFINITY = 999999999999999999999.0f;
	
	class  Helper
	{
	public:
		
		// limits an angle between minV and maxV
		 static float ClampAngle(float radians, float minV, float maxV) ;
		

		// returns random number between -1 and 1
		static float RandomBinomial();

		// returns a float as a vector2
		static Vector2 AsVector(float value);

	
	private:
		Helper();
		~Helper();
	};


}



#endif // end of namespace mth