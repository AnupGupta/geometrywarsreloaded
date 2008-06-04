/**********************************************
*  Namespace: mth
*  Classes:   Plane3d
*  Desc:      Plane operations
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#ifndef PLANE3_H
#define PLANE3_H

#include "Vector.h"


namespace mth
{
	class Plane3
	{
	public:

		enum PlaneSide
		{
			BEHIND,
			FRONT,
			INTERSECT
		};

		Plane3() : A(0.0f),
				  B(0.0f),
				  C(0.0f),
				  D(0.0f)
		{}

		Plane3(float _A,
		     float _B,
			 float _C,
			 float _D)
			 : A(_A),
			   B(_B),
			   C(_C),
			   D(_D)
		{}

		Plane3(const mth::Vector3& p1,
			  const mth::Vector3& p2,
		      const mth::Vector3& p3)
			  : A(p1.y*(p2.z-p3.z)
			      + p2.y*(p3.z-p1.z)
				  + p3.y*(p1.z-p2.z)),
			    B(p1.z*(p2.x-p3.x)
			      + p2.z*(p3.x-p1.x)
				  + p3.z*(p1.x-p2.x)),
			    C(p1.x*(p2.y-p3.y)
			      + p2.x*(p3.y-p1.y)
				  + p3.x*(p1.y-p2.y)),
			    D(-(p1.x*(p2.y*p3.z-p3.y*p2.z)
				  + p2.x*(p3.y*p1.z-p1.y*p3.z)
				  + p3.x*(p1.y*p2.z-p2.y*p1.z)))

		{}

		Plane3(const Plane3& p)
			: A(p.A),
			  B(p.B),
			  C(p.C),
			  D(p.D)
		{}

		~Plane3()
		{}

		// returns plane normal
		const mth::Vector3 GetNormal() const
		{
			return mth::Vector3(A,B,C).Normalized();
		}

		
		
		// get the side that point p lies with respect to
		// the plane. 1 is at direction of normal, 0 is on
		// the plane and -1 at opposite side of normal
		PlaneSide GetSide(const mth::Vector3& p) const
		{
			float res = A*p.x + B*p.y + C*p.z + D;
			if (res > 0.0f) return FRONT;
			else if (res < 0.0f) return BEHIND;
			else return INTERSECT;
		}
		
		// normalize plane
		void Normalize()
		{
			float mag = sqrt(A*A + B*B + C*C);
			A /= mag;
			B /= mag;
			C /= mag;
			D /= mag;
			
		}

		// calculates distance of point from plane
		float GetDistance(const mth::Vector3 v) const
		{
			return A * v.x + B * v.y + C * v.z + D;
		}

	private:

		float A;
		float B;
		float C;
		float D;
	};

}

#endif