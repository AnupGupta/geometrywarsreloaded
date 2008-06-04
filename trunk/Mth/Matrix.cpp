/**********************************************
*  Namespace: mth
*  Classes:   Matrix33
*  Desc:      3x3 rotation matrix operations
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#include "Matrix.h"

namespace mth
{
	//--------------------------------------------------
	/**
	* Ctor
	*
	**/
	Matrix33::Matrix33() 
	{
		Identity();
	}

	//--------------------------------------------------
	/**
	* Ctor
	*
	**/
	Matrix33::Matrix33(float m[3][3])
	{
		memcpy(v,m,sizeof(float)*9);
	}

	//--------------------------------------------------
	/**
	* Ctor
	*
	**/
	Matrix33::Matrix33(const Vector3& col1,
		const Vector3& col2,
		const Vector3& col3)
	{
		v[0][0] = col1[0]; v[0][1] = col2[0]; v[0][2] = col3[0];
		v[1][0] = col1[1]; v[1][1] = col2[1]; v[1][2] = col3[1];
		v[2][0] = col1[2]; v[2][1] = col2[2]; v[2][2] = col3[2];
	}

	//--------------------------------------------------
	/**
	* Copy Ctor
	*
	**/
	Matrix33::Matrix33 (const Matrix33& m)
	{
		memcpy(v, m.v, sizeof(float)*9);
	}

	//--------------------------------------------------
	/**
	* Dtor
	*
	**/
	Matrix33::~Matrix33()
	{}

	/*********************************
	*            operators           *
	*********************************/

	//--------------------------------------------------
	/**
	* Array indexing
	*
	**/
	float& Matrix33::operator()(unsigned int i,unsigned int j)
	{			
		assert(i<3 && j<3);
		return v[i][j];
	}

	float Matrix33::operator()(unsigned int i,unsigned int j) const
	{			
		assert(i<3 && j<3);
		return v[i][j];
	}

	//--------------------------------------------------
	/**
	* Equality
	*
	**/
	bool Matrix33::operator==(const Matrix33& rhs) const
	{
		for (unsigned int i=0; i<3; ++i)
		{
			for (unsigned int j=0; j<3; ++j)
			{
				if (v[i][j] != rhs(i,j))
					return false;
			}
		}
		return true;
	}

	//--------------------------------------------------
	/**
	* Inequality
	*
	**/	
	bool Matrix33::operator!=(const Matrix33& rhs) const
	{
		for (unsigned int i=0; i<3; ++i)
		{
			for (unsigned int j=0; j<3; ++j)
			{
				if (v[i][j] != rhs(i,j))
					return true;
			}
		}
		return false;
	}

	//--------------------------------------------------
	/**
	* Assignment
	*
	**/
	Matrix33& Matrix33::operator=(const Matrix33& rhs)
	{
		if (this != &rhs)
		{
			memcpy(v, rhs.v, sizeof(float)*9);
		}

		return *this;
	}

	//--------------------------------------------------
	/**
	* Addition
	*
	**/
	Matrix33 Matrix33::operator+(const Matrix33& rhs) const
	{
		Matrix33 res;
		for (unsigned int i=0; i<3; ++i)
		{
			for (unsigned int j=0; j<3; ++j)
			{
				res(i,j) = v[i][j] + rhs(i,j);
			}
		}

		return res;			
	}

	//--------------------------------------------------
	/**
	* Subtraction
	*
	**/
	Matrix33 Matrix33::operator-(const Matrix33& rhs) const
	{
		Matrix33 res;
		for (unsigned int i=0; i<3; ++i)
		{
			for (unsigned int j=0; j<3; ++j)
			{
				res(i,j) = v[i][j] - rhs(i,j);
			}
		}

		return res;			
	}

	//--------------------------------------------------
	/**
	* Multiplication
	*
	**/
	Matrix33 Matrix33::operator*(const Matrix33& rhs) const
	{
		Matrix33 res;
		res(0,0) = v[0][0]*rhs(0,0) + 
			v[0][1]*rhs(1,0) +
			v[0][2]*rhs(2,0);
		res(0,1) = v[0][0]*rhs(0,1) + 
			v[0][1]*rhs(1,1) +
			v[0][2]*rhs(2,1);
		res(0,2) = v[0][0]*rhs(0,2) + 
			v[0][1]*rhs(1,2) +
			v[0][2]*rhs(2,2);

		res(1,0) = v[1][0]*rhs(0,0) + 
			v[1][1]*rhs(1,0) +
			v[1][2]*rhs(2,0);
		res(1,1) = v[1][0]*rhs(0,1) + 
			v[1][1]*rhs(1,1) +
			v[1][2]*rhs(2,1);
		res(1,2) = v[1][0]*rhs(0,2) + 
			v[1][1]*rhs(1,2) +
			v[1][2]*rhs(2,2);

		res(2,0) = v[2][0]*rhs(0,0) + 
			v[2][1]*rhs(1,0) +
			v[2][2]*rhs(2,0);
		res(2,1) = v[2][0]*rhs(0,1) + 
			v[2][1]*rhs(1,1) +
			v[2][2]*rhs(2,1);
		res(2,2) = v[2][0]*rhs(0,2) + 
			v[2][1]*rhs(1,2) +
			v[2][2]*rhs(2,2);

		return res;			
	}

	//--------------------------------------------------
	/**
	*  postmultiply with vector
	*
	**/
	Vector3 Matrix33::operator*(const Vector3& rhs) const
	{
		Vector3 res;
		res[0]   = v[0][0]*rhs[0] + 
			v[0][1]*rhs[1] +
			v[0][2]*rhs[2];
		res[1]   = v[1][0]*rhs[0] + 
			v[1][1]*rhs[1] +
			v[1][2]*rhs[2];
		res[2]   = v[2][0]*rhs[0] + 
			v[2][1]*rhs[1] +
			v[2][2]*rhs[2];

		return res;			
	}

	//--------------------------------------------------
	/**
	* premultiply with vector	
	**/ 
	Vector3 operator*(const Vector3& lhs, const Matrix33& rhs) 
	{
		Vector3 res;

		res[0]   = rhs(0,0)*lhs[0] + 
			rhs(1,0)*lhs[1] +
			rhs(2,0)*lhs[2];
		res[1]   = rhs(0,1)*lhs[0] + 
			rhs(1,1)*lhs[1] +
			rhs(2,1)*lhs[2];
		res[2]   = rhs(0,2)*lhs[0] + 
			rhs(1,2)*lhs[1] +
			rhs(2,2)*lhs[2];


		return res;			
	}

	/*********************************
	*            functions           *
	*********************************/

	//--------------------------------------------------
	/**
	* makes this matrix the Identity matrix
	*
	**/	
	void Matrix33::Identity()
	{			
		v[0][0] = 1.0f; v[0][1] = 0.0f; v[0][2] = 0.0f;
		v[1][0] = 0.0f; v[1][1] = 1.0f; v[1][2] = 0.0f;
		v[2][0] = 0.0f; v[2][1] = 0.0f; v[2][2] = 1.0f;
	}

	//--------------------------------------------------
	/**
	* returns transpose
	*
	**/	
	Matrix33 Matrix33::Transpose() const
	{
		Matrix33 res;
		res(0,0) = v[0][0]; res(0,1) = v[1][0]; res(0,2) = v[2][0];
		res(1,0) = v[0][1]; res(1,1) = v[1][1]; res(1,2) = v[2][1];
		res(2,0) = v[0][2]; res(2,1) = v[1][2]; res(2,2) = v[2][2];
		return res;
	}

	//--------------------------------------------------
	/**
	* returns inverse (which is the transpose in rotation matrices)
	*
	**/
	Matrix33 Matrix33::Inverse() const
	{
		return Transpose();
	}

	//--------------------------------------------------
	/**
	* makes this a rotation matrix around
	* the x axis, with a certain angle (RADIANS)
	*
	**/
	void Matrix33::MakeXRot(float radians)
	{
		float cosr = cos(radians);
		float sinr = sin(radians);
		v[0][0] = 1.0f; v[0][1] = 0.0f; v[0][2] = 0.0f;
		v[1][0] = 0.0f; v[1][1] = cosr; v[1][2] = -sinr;
		v[2][0] = 0.0f; v[2][1] = sinr; v[2][2] = cosr;
	}

	//--------------------------------------------------
	/**
	* makes this a rotation matrix around
	* the y axis, with a certain angle (RADIANS)
	*
	**/
	void Matrix33::MakeYRot(float radians)
	{
		float cosr = cos(radians);
		float sinr = sin(radians);
		v[0][0] = cosr; v[0][1] = 0.0f; v[0][2] = -sinr;
		v[1][0] = 0.0f; v[1][1] = 1.0f; v[1][2] = 0.0f;
		v[2][0] = sinr; v[2][1] = 0.0f; v[2][2] = cosr;
	}

	//--------------------------------------------------
	/**
	* makes this a rotation matrix around
	* the z axis, with a certain angle (RADIANS)
	*
	**/
	void Matrix33::MakeZRot(float radians)
	{
		float cosr = cos(-radians);
		float sinr = sin(-radians);
		v[0][0] = cosr; v[0][1] = sinr; v[0][2] = 0.0f;
		v[1][0] = -sinr; v[1][1] = cosr; v[1][2] = 0.0f;
		v[2][0] = 0.0f; v[2][1] = 0.0f; v[2][2] = 1.0f;
	}

	//--------------------------------------------------
	/**
	* creates rotation from euler angles XYZ
	*
	**/
	void Matrix33::FromEulerXYZ(float x, float y, float z)
	{
		float c1 = cos(x); float c2 = cos(y); float c3 = cos(z);
		float s1 = sin(x); float s2 = sin(y); float s3 = sin(z);

		v[0][0] = c2*c3; v[0][1] = c3*s1*s2-c1*s3; v[0][2] = c1*c3*s2+s1*s3;
		v[1][0] = c2*s3; v[1][1] = c1*c3+s1*s2*s3; v[1][2] = c1*s2*s3-c3*s1;
		v[2][0] = -s2; v[2][1] = c2*s1; v[2][2] = c1*c2;
	}


	//--------------------------------------------------
	/**
	* creates rotation from euler angles YZX 
	*
	**/
	void Matrix33::FromEulerYZX(float x, float y, float z)
	{
		float c1 = cos(x); float c2 = cos(y); float c3 = cos(z);
		float s1 = sin(x); float s2 = sin(y); float s3 = sin(z);

		v[0][0] = c1*c2; v[0][1] = -s2; v[0][2] = c2*s1;
		v[1][0] = c1*c3*s2 + s1*s3; v[1][1] = c2*c3; v[1][2] = c3*s1*s2-c1*s3;
		v[2][0] = c1*s2*s3-c3*s1; v[2][1] = c2*s3; v[2][2] = c1*c3 + s1*s2*s3;
	}

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

	//--------------------------------------------------
	/**
	* return a column from the rotation matrix
	*
	**/
	Vector3 Matrix33::GetColumn(unsigned int i) const
	{
		if (i<3)
		{
			return Vector3(v[0][i], v[1][i], v[2][i]);
		}

		return Vector3(); 
	}

	//--------------------------------------------------
	/**
	* return a row from the rotation matrix
	*
	**/	
	Vector3 Matrix33::GetRow(unsigned int i) const
	{
		if (i<3)
		{
			return Vector3(v[i][0], v[i][1], v[i][2]);
		}

		return Vector3(); 
	}
}
