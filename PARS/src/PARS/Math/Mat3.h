#pragma once
#include "stdafx.h"

namespace PARS
{
	class Vec2;

	class Mat3
	{
	public:
		float mat[3][3];

		Mat3();
		Mat3(float* mat);
		Mat3(float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33);

		friend Mat3 operator*(const Mat3& lhs, const Mat3& rhs);
		Mat3& operator*=(const Mat3& mat);

		friend std::ostream& operator<<(std::ostream& os, const Mat3& mat);

		static Mat3 CreateScale(float x, float y);
		static Mat3 CreateScale(float scale);
		static Mat3 CreateScale(const Vec2& vec);
		static Mat3 CreateRotation(float angle);
		static Mat3 CreateTranslation(float x, float y);
		static Mat3 CreateTranslation(const Vec2& vec);

		std::string ToString() const;

		static const Mat3 Identity;
	};
}