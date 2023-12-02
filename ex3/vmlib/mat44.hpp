#ifndef MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
#define MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA

#include <cmath>
#include <cassert>
#include <cstdlib>

#include "vec3.hpp"
#include "vec4.hpp"

/** Mat44f: 4x4 matrix with floats
 *
 * See vec2f.hpp for discussion. Similar to the implementation, the Mat44f is
 * intentionally kept simple and somewhat bare bones.
 *
 * The matrix is stored in row-major order (careful when passing it to OpenGL).
 *
 * The overloaded operator () allows access to individual elements. Example:
 *    Mat44f m = ...;
 *    float m12 = m(1,2);
 *    m(0,3) = 3.f;
 *
 * The matrix is arranged as:
 *
 *   ⎛ 0,0  0,1  0,2  0,3 ⎞
 *   ⎜ 1,0  1,1  1,2  1,3 ⎟
 *   ⎜ 2,0  2,1  2,2  2,3 ⎟
 *   ⎝ 3,0  3,1  3,2  3,3 ⎠
 */
struct Mat44f
{
	float v[16];

	constexpr
	float& operator() (std::size_t aI, std::size_t aJ) noexcept
	{
		assert( aI < 4 && aJ < 4 );
		return v[aI*4 + aJ];
	}
	constexpr
	float const& operator() (std::size_t aI, std::size_t aJ) const noexcept
	{
		assert( aI < 4 && aJ < 4 );
		return v[aI*4 + aJ];
	}
};

// Identity matrix
constexpr Mat44f kIdentity44f = { {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
} };

// Common operators for Mat44f.
// Note that you will need to implement these yourself.

constexpr
Mat44f operator*( Mat44f const& aLeft, Mat44f const& aRight ) noexcept
{
	// Initialize the returning matrix with the identity matrix
	Mat44f mxmresult = kIdentity44f;  

	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			mxmresult(i, j) = 0.0f;
			for (std::size_t k = 0; k < 4; ++k)
			{
				// Assining the result of the calculation
				mxmresult(i, j) += aLeft(i, k) * aRight(k, j);
			}
		}
	}

	return mxmresult;
}

constexpr
Vec4f operator*( Mat44f const& aLeft, Vec4f const& aRight ) noexcept
{
	// Initialize the returning vector
	Vec4f mxvresult = { 0.0f, 0.0f, 0.0f, 0.0f };

	for (std::size_t i = 0; i < 4; ++i)
	{
		mxvresult[i] = 0.0f;
		for (std::size_t j = 0; j < 4; ++j)
		{
			// Assigning the result of the calculation
			mxvresult[i] += aLeft(i, j) * aRight[j];
		}
	}
	
	return mxvresult;
}

// Functions:

inline
Mat44f make_rotation_x( float aAngle ) noexcept
{
	// Assigning the cost and sin of the angle to variables
	float cosA = std::cos(aAngle);
	float sinA = std::sin(aAngle);

	// Returining the resulting matrix
	return {
		cosA, -sinA, 0.f, 0.f,
		sinA, cosA, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}


inline
Mat44f make_rotation_y( float aAngle ) noexcept
{
	// Assigning the cos and sin of the angle to variables
	float cosA = std::cos(aAngle);
	float sinA = std::sin(aAngle);

	// Returning the resulting matrix
	return {
		cosA, 0.f, sinA, 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sinA, 0.f, cosA, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

inline
Mat44f make_rotation_z( float aAngle ) noexcept
{
	// Assigning the cos and sin of the angle to variables
	float cosA = std::cos(aAngle);
	float sinA = std::sin(aAngle);

	// Returning the resulting matrix
	return {
		cosA, -sinA, 0.f, 0.f,
		sinA, cosA, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

inline
Mat44f make_translation( Vec3f aTranslation ) noexcept
{
	// Returning the required trnaslated matrix
	return {
		1.f, 0.f, 0.f, aTranslation.x,
		0.f, 1.f, 0.f, aTranslation.y,
		0.f, 0.f, 1.f, aTranslation.z,
		0.f, 0.f, 0.f, 1.f
	};
}

inline
Mat44f make_perspective_projection( float aFovInRadians, float aAspect, float aNear, float aFar ) noexcept
{
	// Assigning the half of the passed in angle as tangent
	float tanHalfFov = std::tan(aFovInRadians * 0.5f);

	// Calculating the range which is near - far
	float range = aNear - aFar;

	// Returning the requried matrix
	return {
		1.f / (tanHalfFov * aAspect), 0.f, 0.f, 0.f,
		0.f, 1.f / tanHalfFov, 0.f, 0.f,
		0.f, 0.f, (aNear + aFar) / range, 2.f * aNear * aFar / range,
		0.f, 0.f, -1.f, 0.f
	};
}



#endif // MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
