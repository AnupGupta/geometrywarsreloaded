/**********************************************
*  Namespace: mth
*  Classes:   Transform
*  Desc:      Rotation and translation math
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"
#include "Matrix.h"

namespace mth
{
	// a 3d transformation
	class Transform
	{
	public:
	
		// ctors
		Transform() 
		{
			Identity();
		}

		Transform(const Matrix33& r, const Vector3& t)
			: m_rotation(r), m_translation(t)
		{
			
		}

		// copy ctor
		Transform (const Transform& t)
			: m_rotation(t.m_rotation), 
			  m_translation(t.m_translation)
		{

		}

		// dtor
		~Transform()
		{}

		// operators

		// equality		
		bool operator==(const Transform& rhs) const
		{
			return (m_rotation == rhs.m_rotation) &&
				(m_translation == rhs.m_translation);
		}

		// inequality		
		bool operator!=(const Transform& rhs) const
		{
			return (m_rotation != rhs.m_rotation) ||
				(m_translation != rhs.m_translation);
		}

		// assignment
		Transform& operator=(const Transform& rhs)
		{
			if (this != &rhs)
			{
				m_rotation = rhs.m_rotation;
				m_translation = rhs.m_translation;
			}

			return *this;
		}

		// multiplication
		Transform operator*(const Transform& rhs) const
		{			
			return Transform(m_rotation*rhs.m_rotation,
				m_rotation*rhs.m_translation + m_translation);
		}
		
		// postmultiply with vector
		Vector3 operator*(const Vector3& rhs) const
		{
			return m_rotation*rhs + m_translation;		
		}

		// premultiply with vector
		friend Vector3 operator*(const Vector3& lhs, const Transform& rhs) 
		{
			return lhs * rhs.m_rotation + rhs.m_translation;	
		}

		// functions

		// makes this a transform with an identity matrix
		// and no translation
		void Identity()
		{			
			m_rotation.Identity();
			m_translation = Vector3();
		}
		
		// returns inverse
		Transform Inverse() const
		{
			return Transform(m_rotation.Transpose(),
				             -m_translation);

		}


		const Matrix33& GetRotation() const
		{
			return m_rotation;
		}

		const Vector3& GetTranslation() const
		{
			return m_translation;
		}

	private:

		// data
		Matrix33 m_rotation;
		Vector3  m_translation;
	};	
}

#endif // end of namespace mth