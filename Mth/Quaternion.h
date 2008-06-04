/**********************************************
*  Namespace: mth
*  Class:     Quaternion
*  Desc:      Quaternion math for 3D rotations
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/
#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"
#include "Matrix.h"

namespace mth
{
	class Quaternion
	{
	public:
		// ctors
		Quaternion() : x(0.0f),
					   y(0.0f),
					   z(0.0f),
					   w(1.0f)
		{}


		Quaternion(float _w, 
			       float _x,
				   float _y,
				   float _z):  x(_x),
							   y(_y),
				    		   z(_z),
							   w(_w)
		{}

		Quaternion(float _w, const Vector3& v): 
											x(v.x),
										    y(v.y),
										    z(v.z),
										    w(_w)
		{}

		// copy ctor
		Quaternion(const Quaternion& q) : x(q.x),
										  y(q.y),
										  z(q.z),
										  w(q.w)
		{}
		
		// dtor
		~Quaternion()
		{}

		// functions

		//  normalizes quaternion
		void Normalize()
		{
			
			float square = x*x + y*y + z*z + w*w;			
			float dist = square > 0.0f ? 1.0f/(float)sqrt(square) : 1.0f;
				
		
			x *= dist;
			y *= dist;
			z *= dist;
			w *= dist;			
			
		}

		//  normalizes quaternion (faster with error)
		void NormalizeFast()
		{
			float square = x*x + y*y + z*z + w*w;			
			float dist = square > 0.0f ? InvSqrt(square) : 1.0f;
						
			x *= dist;
			y *= dist;
			z *= dist;
			w *= dist;			
		}


		//  returns normalized quaternion
		Quaternion Normalized() const
		{
			Quaternion q(*this);
			q.Normalize();
			return q;			
		}

		//  returns normalized quaternion (faster with error)
		Quaternion NormalizedFast() const
		{
			Quaternion q(*this);
			q.NormalizeFast();
			return q;
			
		}

		// converts quaternion to 3x3 rotation matrix
		Matrix33 ToMatrix() const
		{
			float m[3][3];
			float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

			x2 = x + x;    y2 = y + y;    z2 = z + z;
			xx = x * x2;   xy = x * y2;   xz = x * z2;
			yy = y * y2;   yz = y * z2;   zz = z * z2;
			wx = w * x2;   wy = w * y2;   wz = w * z2;

			m[0][0] = 1.0f - (yy + zz);
			m[0][1] = xy - wz;
			m[0][2] = xz + wy;			
		 
			m[1][0] = xy + wz;
			m[1][1] = 1.0f - (xx + zz);
			m[1][2] = yz - wx;	

			m[2][0] = xz - wy;
			m[2][1] = yz + wx;
			m[2][2] = 1.0f - (xx + yy);			

			return Matrix33(m);
		}

		// constructs quaternion from euler angles
		void FromEuler(float roll, float pitch, float yaw)
		{
			float cr, cp, cy, sr, sp, sy, cpcy, spsy;

			cr = cos(roll/2);
			cp = cos(pitch/2);
			cy = cos(yaw/2);

			sr = sin(roll/2);
			sp = sin(pitch/2);
			sy = sin(yaw/2);
			
			cpcy = cp * cy;
			spsy = sp * sy;

			w = cr * cpcy + sr * spsy;
			x = sr * cpcy - cr * spsy;
			y = cr * sp * cy + sr * cp * sy;
			z = cr * cp * sy - sr * sp * cy;
		}

		// constructs quaternion from 3x3 rotation matrix
		void FromMatrix(const Matrix33& m)
		{
			float  tr, s;
			float  q[4];
		    int    i, j, k;

		    int nxt[3] = {1, 2, 0};

		    tr = m(0,0) + m(1,1) + m(2,2);

			// check the diagonal

			if (tr > 0.0f) 
			{
				s = sqrt (tr + 1.0f);

				w = s / 2.0f;
		    
				s = 0.5f / s;

				x = (m(2,1) - m(1,2)) * s;
				y = (m(0,2) - m(2,0)) * s;
				z = (m(1,0) - m(0,1)) * s;

			} 
			else 
			{		
			  
				// diagonal is negative
		    
				i = 0;

				if (m(1,1) > m(0,0)) i = 1;
				if (m(2,2) > m(i,i)) i = 2;
		    
				j = nxt[i];
				k = nxt[j];

				s = sqrt ((m(i,i) - (m(j,j) + m(k,k))) + 1.0f);
		      
				q[i] = s * 0.5f;

				if (s != 0.0f) s = 0.5f / s;

				q[3] = (m(k,j) - m(j,k)) * s;
				q[j] = (m(j,i) + m(i,j)) * s;
				q[k] = (m(k,i) + m(i,k)) * s;

				x = q[0];
				y = q[1];
				z = q[2];
				w = q[3];
			}
		}

		// Constructs quaternion to rotate from one direction vector to 
		// another
		void FromAxisDelta(const Vector3& axis1,
						   const Vector3& axis2)
		{
			float tx, ty, tz, temp, dist;
			float ax1 = axis1.x;
			float ay1 = axis1.y;
			float az1 = axis1.z;
			float ax2 = axis2.x;
			float ay2 = axis2.y;
			float az2 = axis2.z;

			float	cost, len, ss;

			// get dot product of two vectors
			cost = ax1 * ax2 + ay1 * ay2 + az1 * az2;

			// check if parallel
			if (cost > 0.99999f) 
			{
				x = y = z = 0.0f;
				w = 1.0f;
				return;
			}
			else if (cost < -0.99999f) 
			{		// check if opposite

				// check if we can use cross product of from vector with [1, 0, 0]
				tx = 0.0;
				ty = ax1;
				tz = -ay1;

				len = sqrt(ty*ty + tz*tz);

				if (len < 0.00001f)
				{
					// nope! we need cross product of from vector with [0, 1, 0]
					tx = -az1;
					ty = 0.0;
					tz = ax1;
				}

				// normalize
				temp = tx*tx + ty*ty + tz*tz;

				dist = (float)(1.0f / sqrt(temp));

				tx *= dist;
				ty *= dist;
				tz *= dist;
				
				x = tx;
				y = ty;
				z = tz;
				w = 0.0;

				return;
			}

			// ... else we can just cross two vectors

			tx = ay1 * az2 - az1 * ay2;
			ty = az1 * ax2 - ax1 * az2;
			tz = ax1 * ay2 - ay1 * ax2;

			temp = tx*tx + ty*ty + tz*tz;

			dist = (float)(1.0f / sqrt(temp));

			tx *= dist;
			ty *= dist;
			tz *= dist;


			// we have to use half-angle formulae 
			// (sin^2 t = ( 1 - cos (2t) ) /2)
			
			ss = (float)sqrt(0.5f * (1.0f - cost));

			tx *= ss;
			ty *= ss;
			tz *= ss;

			// scale the axis to get the normalized quaternion
			x = tx;
			y = ty;
			z = tz;

			// cos^2 t = ( 1 + cos (2t) ) / 2
			// w part is cosine of half the rotation angle
			w = (float)sqrt(0.5f * (1.0f + cost));
		}

		// constructs quaternion from an axis and an angle (RADIANS)
		void FromAxisAngle (float ax, float ay, float az, float radians)
		{			
			float sina = sin(radians/2.0f);
			x = ax * sina;
			y = ay * sina;
			z = az * sina;
			w = (float)cos(radians / 2.0f);
		}

		void FromAxisAngle (const Vector3& axis, float radians)
		{			
			float sina = sin(radians/2.0f);
			x = axis.x * sina;
			y = axis.y * sina;
			z = axis.z * sina;
			w = (float)cos(radians / 2.0f);
		}

		// Disassembles quaternion to an axis and an angle (RADIANS)
		void GetAxisAngle(Vector3& axis, 
						  float& radians) const
		{
			float	len;
			float   tx, ty, tz;

			// cache variables
			tx = x;
			ty = y;
			tz = z;

			len = tx * tx + ty * ty + tz * tz;

			if (len > 0.00001f) 
			{
				float invl = 1.0f / len;
				axis.x = tx * invl;
				axis.y = ty * invl;
				axis.z = tz * invl;			
				radians = float(2.0f * acos(w));
			}

			else {
				axis.x = 0.0f;
				axis.y = 0.0f;
				axis.z = 1.0f;
				radians = 0.0f;
			}
		}

		// Scales the rotation angle of a quaternion
		void ScaleAngle(float scale)
		{	
			Vector3 axis;	// axis
			float angle;  // and angle

			GetAxisAngle(axis, angle);
			FromAxisAngle(axis, (angle * scale));
		}

		// Inverts quaternion's rotation
		void Invert()
		{
			float norm, invNorm;

			norm = x * x + y * y + z * z
							   + w * w;
			
			invNorm = 1.0f / norm;
			
			x = -x * invNorm;
			y = -y * invNorm;
			z = -z * invNorm;
			w =  w * invNorm;
		}

		// Square quaternion
		void Square()
		{
			float  tt;
			tt = 2 * w;
			w = w * w - x * x - y * y - z * z;
			x = tt * x;
			y = tt * y;
			z = tt * z;			
		}

		// Square root of quaternion
		Quaternion Sqrt() const
		{
			float  length, m, r1, r2;
			Quaternion r;

			length = sqrt (w * w + x * x + y * y);
			if (length != 0.0f) 
				length = 1.0f / length; 
			else length = 1.0f;

			r.x = x * length;
			r.y = z * length;
			r.z = 0.0f;
			r.w = w * length;

			m = 1.0f / sqrt (r.w * r.w + r.x * r.x);
			r1 = sqrt ((1.0f + r.y) * 0.5f);
			r2 = sqrt ((1.0f - r.y) * 0.5f);

			Quaternion res;
			res.x = sqrt (length) * r2 * r.x * m;
			res.y = sqrt (length) * r1;
			res.z = z;
			res.w = sqrt (length) * r1 * r.w * m;
			return res;
		}

		// Dot product between quaternions
		const float Dot(const Quaternion& rhs) const
		{
			return (float)(w * rhs.w + 
						   x * rhs.x + 
						   y * rhs.y + 
						   z * rhs.z);
		}

		// Length of quaternion
		const float Length() const
		{
			return sqrt 
				(w * w + x * x + y * y + z * z);
		}

		// Length of quaternion  (faster with error)
		const float LengthFast() const
		{
			return 1.0f / InvSqrt(w * w + x * x + y * y + z * z);
		}

		// Negates vector part of quaternion
		void Negate()
		{
			Normalize();
			x = -x;
			y = -y;
			z = -z;
		}

		// calculates exponent of quaternion
		Quaternion ToExponent() const
		{
			float  len1, len2;

			len1 = Length();
			if (len1 > 0.0f) 
				len2 = (float)sin(len1) / len1; 
			else 
				len2 = 1.0f;

			Quaternion res;
			res.x = x*len2;
			res.y = y*len2;
			res.z = z*len2;
			res.w = cos (len1);
			return res;
		}

		Vector3 ToVector3() const
		{
			return Vector3(x, y, z);
		}

		// calculates natural logarithm of a quaternion
		Quaternion ToLogarithm() const
		{
			float  length = Length();
			float pi = 3.14159265f;

			//make sure we do not divide by 0
			if (w != 0.0f) 
				length = atan (length / w); 
			else length = pi/2.0f;

			Quaternion res;
			res.w = 0.0f;
			res.x = x*length;
			res.y *= y*length;
			res.z *= z*length;
			return res;
		}

		// SLERP: Smoothly (spherically, shortest path on a 
		// quaternion sphere) interpolates between two UNIT 
		// quaternion positions
		void Slerp(const Quaternion& from, const Quaternion& to, float t) 
		{
			float   to1[4];
			double  omega, cosom, sinom;
			double  scale0, scale1;

			// calc cosine
			cosom = from.x * to.x + from.y * to.y + from.z * to.z
					   + from.w * to.w;


			// adjust signs (if necessary)
			if ( cosom < 0.0 )
			{
				cosom = -cosom;

				to1[0] = - to.x;
				to1[1] = - to.y;
				to1[2] = - to.z;
				to1[3] = - to.w;

			} else  {

				to1[0] = to.x;
				to1[1] = to.y;
				to1[2] = to.z;
				to1[3] = to.w;

			}

			// calculate coefficients

			if ( (1.0 - cosom) > 0.00001 ) 
			{
					// standard case (slerp)
					omega = acos(cosom);
					sinom = sin(omega);
					scale0 = sin((1.0 - t) * omega) / sinom;
					scale1 = sin(t * omega) / sinom;

			} else {        
					// "from" and "to" quaternions are very close 
					//  ... so we can do a linear interpolation

					scale0 = 1.0 - t;
					scale1 = t;
			}
			
			// calculate final values
			x = (float)scale0 * from.x + (float)scale1 * to1[0];
			y = (float)scale0 * from.y + (float)scale1 * to1[1];
			z = (float)scale0 * from.z + (float)scale1 * to1[2];
			w = (float)scale0 * from.w + (float)scale1 * to1[3];	
		}

		// Linearly interpolates between two quaternion positions
		void Lerp(const Quaternion& from, const Quaternion& to, float t) 
		{
			float   to1[4];
			double  cosom;
			double  scale0, scale1;

			// calc cosine
			cosom = from.x * to.x + from.y * to.y + from.z * to.z
					   + from.w * to.w;

			// adjust signs (if necessary)
			if ( cosom < 0.0 )
			{
				to1[0] = - to.x;
				to1[1] = - to.y;
				to1[2] = - to.z;
				to1[3] = - to.w;

			} else  {

				to1[0] = to.x;
				to1[1] = to.y;
				to1[2] = to.z;
				to1[3] = to.w;

			}

	 
			// interpolate linearly
			scale0 = 1.0 - t;
			scale1 = t;
	 
			// calculate final values
			x = (float)scale0 * from.x + (float)scale1 * to1[0];
			y = (float)scale0 * from.y + (float)scale1 * to1[1];
			z = (float)scale0 * from.z + (float)scale1 * to1[2];
			w = (float)scale0 * from.w + (float)scale1 * to1[3];		

		}
		
		// Rotates a vector v and returns the result
		Vector3 Rotate(const Vector3& v) const
		{
			Quaternion qv(0.0f, v);
			Quaternion qconj(*this);
			qconj.Negate();
			Quaternion qr = *this * qv * qconj;
			return Vector3(qr.x, qr.y, qr.z);
		}


		// operators
		// assignment
		Quaternion& operator=(const Quaternion &rhs) 
		{			
			if (this != &rhs)
			{
				x = rhs.x;		
				y = rhs.y;
				z = rhs.z;
				w = rhs.w;
			}

			return *this;
		 }

		// mul
		Quaternion operator*(const Quaternion &rhs) const 
		{			
			Quaternion res;
			res.x = w * rhs.x +
				    x * rhs.w + 
					y * rhs.z - 
					z * rhs.y;
			res.y = w * rhs.y +
				    y * rhs.w + 
					z * rhs.x - 
					x * rhs.z;
			res.z = w * rhs.z +
				    z * rhs.w + 
					x * rhs.y - 
					y * rhs.x;
			res.w = w * rhs.w -
				    x * rhs.x - 
					y * rhs.y - 
					z * rhs.z;

			//res.Normalize();
			return res;
		}

		Quaternion& operator*=(const Quaternion &rhs)
		{			
			float _x = x;
			float _y = y;
			float _z = z;
			float _w = w;
			x = _w * rhs.x +
				_x * rhs.w + 
				_y * rhs.z - 
				_z * rhs.y;
			y = _w * rhs.y +
				_y * rhs.w + 
				_z * rhs.x - 
				_x * rhs.z;
			z = _w * rhs.z +
				_z * rhs.w + 
			    _x * rhs.y - 
				_y * rhs.x;
			w = _w * rhs.w -
				_x * rhs.x - 
			    _y * rhs.y - 
				_z * rhs.z;

			//Normalize();
			return *this;
		}

		// add
		Quaternion operator+(const Quaternion &rhs) const 
		{			
			Quaternion res;
			res.x = x + rhs.x;
			res.y = y + rhs.y;
			res.z = z + rhs.z;
			res.w = w + rhs.w;
			//res.Normalize();
			return res;
		}

		// sub
		Quaternion operator-(const Quaternion &rhs) const 
		{			
			Quaternion res;
			res.x = x - rhs.x;
			res.y = y - rhs.y;
			res.z = z - rhs.z;
			res.w = w - rhs.w;
			//res.Normalize();
			return res;
		}

		// div
		Quaternion operator/(const Quaternion &rhs) const 
		{			
			Quaternion q(rhs);
			q.x = -q.x;
			q.y = -q.y;
			q.z = -q.z;

			Quaternion r(*this*q);
			Quaternion s(q*q);

			Quaternion res;
			res.x = r.x / s.w;
			res.y = r.y / s.w;
			res.z = r.z / s.w;
			res.w = r.w / s.w;
			
			return res;
		}

	private:

		// vector part
		float x;
		float y;
		float z;
		// scalar part
		float w;

	};
}

#endif // end of namespace mth