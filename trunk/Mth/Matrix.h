/**********************************************
*  Namespace: mth
*  Classes:   Matrix33
*  Desc:      3x3 rotation matrix operations
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/
#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <memory.h>
#include "Vector.h"

namespace mth
{
	// 3x3 Matrix
	class Matrix33
	{
	public:
	
		// ctors
		Matrix33() ;

		Matrix33(float m[3][3]);

		Matrix33(const Vector3& col1,
			     const Vector3& col2,
				 const Vector3& col3);

		// copy ctor
		Matrix33 (const Matrix33& m);

		// dtor
		~Matrix33();

		// operators

		// array indexing
		float& operator()(unsigned int i,unsigned int j);

		float operator()(unsigned int i,unsigned int j) const;

		// equality		
		bool operator==(const Matrix33& rhs) const;

		// inequality		
		bool operator!=(const Matrix33& rhs) const;

		// assignment
		Matrix33& operator=(const Matrix33& rhs);

		// addition
		Matrix33 operator+(const Matrix33& rhs) const;

		// subtraction
		Matrix33 operator-(const Matrix33& rhs) const;

		// multiplication
		Matrix33 operator*(const Matrix33& rhs) const;

		// postmultiply with vector
		Vector3 operator*(const Vector3& rhs) const;

		// premultiply with vector
		friend Vector3 operator*(const Vector3& lhs, const Matrix33& rhs) ;

		// functions

		// makes this matrix the Identity matrix
		void Identity();
		
		// returns transpose
		Matrix33 Transpose() const;

		// returns inverse (which is the transpose in rotation matrices)
		Matrix33 Inverse() const;

		// makes this a rotation matrix around
		// the x axis, with a certain angle (RADIANS)
		void MakeXRot(float radians);

		// makes this a rotation matrix around
		// the y axis, with a certain angle (RADIANS)
		void MakeYRot(float radians);

		// makes this a rotation matrix around
		// the z axis, with a certain angle (RADIANS)
		void MakeZRot(float radians);

		// creates rotation from euler angles XYZ
		void FromEulerXYZ(float x, float y, float z);


		// creates rotation from euler angles YZX
		void FromEulerYZX(float x, float y, float z);

		/*
		// creates rotation from euler angles YZX
		void FromEulerYZX(float x, float y, float z)
		{
			float c1 = cos(x); float c2 = cos(y); float c3 = cos(z);
			float s1 = sin(x); float s2 = sin(y); float s3 = sin(z);

			v[0][0] = ; v[0][1] = ; v[0][2] = ;
			v[1][0] = ; v[1][1] = ; v[1][2] = ;
			v[2][0] = ; v[2][1] = ; v[2][2] = ;
		}
		*/

		// return a column from the rotation matrix
		Vector3 GetColumn(unsigned int i) const;

		// return a row from the rotation matrix
		Vector3 GetRow(unsigned int i) const;

	private:

		// data
		float v[3][3];
	};	
}

#endif // end of namespace mth