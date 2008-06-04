/**********************************************
*  Namespace: mth
*  Classes:   Vector2, Vector3
*  Desc:      2D and 3D Vector math classes
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <assert.h>

namespace mth
{
	// returns inverse square root
	// (by John Carmack)
	static float InvSqrt (float x)
	{
		float xhalf = 0.5f*x;
		int i = *(int*)&x;
		i = 0x5f3759df - (i >> 1);
		x = *(float*)&i;
		x = x*(1.5f - xhalf*x*x);
		return x;
	}

	static float Sqrt(float x)
	{
		return 1.0f / InvSqrt(x);
	}

	// 2D math
	class Vector2
	{
	public:

		// data
		float x;
		float y;

		// ctors
		Vector2() : x(0.0f), y(0.0f)
		{}

		Vector2(float _x, float _y) : x(_x),
									  y(_y)
		{}

		// copy ctor
		Vector2(const Vector2& v) :   x(v.x),
									  y(v.y)
		{}

		// dtor
		~Vector2()
		{}

		// operators

		// array indexing
		float& operator[](unsigned int i)
		{
			assert(i<2);	
			return *(&x + i);
		}

		float operator[](unsigned int i) const
		{
			assert(i<2);
			return *(&x + i);
		}

		// equality
		bool operator==(const Vector2& rhs) const
		{
			return (x == rhs.x) &&
				   (y == rhs.y);
		}

		// inequality
		bool operator!=(const Vector2& rhs) const
		{
			return (x != rhs.x) ||
				   (y != rhs.y);
		}

		//! negation
		Vector2 operator -(void) const
		{	
			return Vector2(-x, -y);
		}

		// assignment
		Vector2& operator=(const Vector2& rhs)
		{
			if (this != &rhs)
			{
				x = rhs.x;
				y = rhs.y;
			}

			return *this;
		}

		// addition
		Vector2 operator+(const Vector2& rhs) const
		{
			return Vector2(x+rhs.x, y+rhs.y);
		}

		Vector2& operator+=(const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		// subtraction
		Vector2 operator-(const Vector2& rhs) const
		{
			return Vector2(x-rhs.x, y-rhs.y);
		}

		Vector2& operator-=(const Vector2& rhs) 
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		// dot product		
		friend float operator*(const Vector2& lhs, 
							   const Vector2& rhs) 
		{
			return lhs.x*rhs.x + lhs.y*rhs.y;
		}


		// scalar multiplication
		friend Vector2 operator*(const Vector2& lhs, float rhs) 
		{
			return Vector2(lhs.x*rhs, lhs.y*rhs);
		}

		friend Vector2 operator*(float lhs, const Vector2& rhs) 
		{
			return Vector2(lhs*rhs.x, lhs*rhs.y);
		}

		Vector2& operator*=(const Vector2& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		Vector2& operator*=(const float rhs)
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}

		// division with vector
		Vector2 operator/(const Vector2& rhs) const
		{
			if (rhs.x != 0.0f && rhs.y != 0.0f)
			{
				return Vector2(x/rhs.x, y/rhs.y);
			}
			

			return Vector2(0.0f, 0.0f);			
		}

		// scalar division
		Vector2 operator/(float rhs) const
		{
			if (rhs != 0.0f)
				return Vector2(x/rhs, y/rhs);
			else
				return Vector2(0.0f, 0.0f);
		}

		Vector2& operator/=(const Vector2& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		Vector2& operator/=(const float rhs)
		{
			x /= rhs;
			y /= rhs;
			return *this;
		}

		// functions
		
		// inner product
		Vector2 Inner(const Vector2& rhs) const
		{
			return Vector2(x*rhs.x, y*rhs.y);
		}

		// finds length
		float Length() const
		{
			return sqrt(x*x + y*y);			
		}

		// finds length (faster with error)
		float LengthFast() const
		{
			return 1.0f / InvSqrt(x*x + y*y);
		}

		// finds inverse length
		float InverseLengthFast() const
		{
			return InvSqrt(x*x + y*y);
		}

		// finds length squared
		float LengthSquared() const
		{
			return x*x + y*y;
		}
	
		// normalizes vec
		void Normalize()
		{
			float len = Length();
			if (len > 0.0f)
			{
				*this = *this / len;				
			}
		}

		// normalizes vector (fast with error)
		void NormalizeFast()
		{
			*this *= InverseLengthFast();					
		}

		// returns normalized vector
		Vector2 Normalized() const
		{						
			float len = Length();
			if (len > 0.0f)		
				return *this / len;							
			else
				return *this;				
		}

		// returns normalized vector (fast with error)
		Vector2 NormalizedFast() const
		{
			return *this * InverseLengthFast();			
		}

		// returns rotates vector by radians
		void Rotate(float radians)
		{
			float length = Length();
			Normalize();
			float rotation = atan2(y, x);
			rotation += radians;
			x = cos(rotation)*length;
			y = sin(rotation)*length;
			
		}

		// projects this vector onto v
		void Project(const Vector2 &v)
		{			
			*this = v * (*this * v) / (v*v);			
		}

		// returns this vector projected onto v		
		Vector2 Projected(const Vector2 &v) const
		{ 
			return v * (*this * v)/(v*v);	
		}

		// reflects this vector about n
		void Reflect(const Vector2 &n)
		{
			Vector2 orig(*this);
			Project(n);
			*this = *this*2.0f - orig;
		}

		// computes the angle between 2 arbitrary vectors
		static inline float Angle(const Vector2 &v1, 
			                      const Vector2 &v2) 
		{			
			return acosf((v1*v2) / (v1.Length()*v2.Length()));  
		}

		// computes the angle between 2 normalized arbitrary vectors
		static inline float AngleNormalized(const Vector2 &v1, 
										    const Vector2 &v2) 
		{   
			return acosf(v1*v2); 
		}
	
		
	};

	// 3D math
	class Vector3
	{
	public:

		// data
		float x;
		float y;
		float z;
		
		// ctors
		Vector3() : x(0.0f), y(0.0f), z(0.0f)
		{}

		Vector3(float _x, float _y, float _z) 
			: x(_x),
			  y(_y),
			  z(_z)
			 
		{}

		// copy ctor
		Vector3(const Vector3& v) :   x(v.x),
									  y(v.y),
									  z(v.z)
									  
		{}

		// dtor
		~Vector3()
		{}

		// operators

		// array indexing
		float& operator[](unsigned int i)
		{
			assert(i<3);	
			return *(&x + i);
		}

		float operator[](unsigned int i) const
		{
			assert(i<3);
			return *(&x + i);
		}

		
		// equality
		bool operator==(const Vector3& rhs) const
		{
		
			return (x == rhs.x) &&
				   (y == rhs.y)&&
				   (z == rhs.z);
		}

		// inequality
		bool operator!=(const Vector3& rhs) const
		{
			return (x != rhs.x) ||
				   (y != rhs.y) ||
				   (z != rhs.z);
		}

		//! negation
		Vector3 operator -(void) const
		{	
			return Vector3(-x, -y, -z);
		}

		// assignment
		Vector3& operator=(const Vector3& rhs)
		{		
			if (this != &rhs)
			{
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
			}

			return *this;
		}

		// addition
		Vector3 operator+(const Vector3& rhs) const
		{
			return Vector3(x+rhs.x, y+rhs.y, z+rhs.z);
		}

		Vector3& operator+=(const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		// subtraction
		Vector3 operator-(const Vector3& rhs) const
		{
			return Vector3(x-rhs.x, y-rhs.y, z-rhs.z);
		}

		Vector3& operator-=(const Vector3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		// dot product		
		friend float operator*(const Vector3& lhs, const Vector3& rhs)
		{
			return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
		}

		// scalar multiplication
		friend Vector3 operator*(const Vector3& lhs, float rhs)
		{
			return Vector3(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs);
		}

		friend Vector3 operator*(float lhs, const Vector3& rhs)
		{
			return Vector3(lhs*rhs.x, lhs*rhs.y, lhs*rhs.z);
		}

		Vector3& operator*=(const Vector3& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		}

		Vector3& operator*=(const float rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}

		// division with vector
		Vector3 operator/(const Vector3& rhs) const
		{
			if (rhs.x != 0.0f && 
				rhs.y != 0.0f && 
				rhs.z != 0.0f)
			{
				return Vector3(x/rhs.x, y/rhs.y, z/rhs.z);
			}
			

			return Vector3(0.0f, 0.0f, 0.0f);			
		}

		// scalar division
		Vector3 operator/(float rhs) const
		{
			if (rhs != 0.0f)
				return Vector3(x/rhs, y/rhs, z/rhs);
			else
				return Vector3(0.0f, 0.0f, 0.0f);
		}

		Vector3& operator/=(const Vector3& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			return *this;
		}

		Vector3& operator/=(const float rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}

		// functions
		
		// inner product
		Vector3 Inner(const Vector3& rhs) const
		{
			return Vector3(x*rhs.x, y*rhs.y, z*rhs.z);
		}

		// cross product
		Vector3 Cross(const Vector3& rhs) const
		{
			return Vector3(y*rhs.z - z*rhs.y, 
				           z*rhs.x - x*rhs.z,
						   x*rhs.y - y*rhs.x);
		}

		// finds length
		float Length() const
		{
			return sqrt(x*x + y*y + z*z);		
			
			
		}

		// finds length (faster with error)
		float LengthFast() const
		{
			return 1.0f / InvSqrt(x*x + y*y + z*z);
		}

		// finds inverse length
		float InverseLengthFast() const
		{
			return InvSqrt(x*x + y*y + z*z);
		}

		// finds length squared
		float LengthSquared() const
		{
			return x*x + y*y + z*z;
		}
	
		// normalizes vec
		void Normalize()
		{
			float len = Length();
			if (len > 0.0f)
			{
				*this = *this / len;				
			}
		}

		// normalizes vector (fast with error)
		void NormalizeFast()
		{
			*this *= InverseLengthFast();					
		}

		// returns normalized vector
		Vector3 Normalized() const
		{						
			float len = Length();
			if (len > 0.0f)		
				return *this / len;							
			else
				return *this;				
		}

		// returns normalized vector (fast with error)
		Vector3 NormalizedFast() const
		{
			return *this * InverseLengthFast();			
		}

		// projects this vector onto v
		void Project(const Vector3 &v)
		{			
			*this = v * (*this * v) / (v*v);			
		}

		// returns this vector projected onto v		
		Vector3 Projected(const Vector3 &v) const
		{ 
			return v * (*this * v)/(v*v);	
		}

		// reflects this vector about n
		void Reflect(const Vector3 &n)
		{
			Vector3 orig(*this);
			Project(n);
			*this = *this*2.0f - orig;
		}

		// computes the angle between 2 arbitrary vectors
		static inline float Angle(const Vector3 &v1, 
			                      const Vector3 &v2)
		{			
			return acosf((v1*v2) / (v1.Length()*v2.Length()));  
		}

		// computes the angle between 2 normalized arbitrary vectors
		static inline float AngleNormalized(const Vector3 &v1, 
										    const Vector3 &v2)
		{   
			return acosf(v1*v2); 
		}

	};

}

#endif // end of namespace mth