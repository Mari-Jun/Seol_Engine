#pragma once
#include "stdafx.h"

namespace PARS
{
	class Vec3
	{
	public:
		float x;
		float y;
		float z;

		Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vec3(float inX, float inY, float inZ)
			: x(inX), y(inY), z(inZ) {}

		friend Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
		friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
		friend Vec3 operator*(const Vec3& lhs, const Vec3& rhs);
		friend Vec3 operator*(const Vec3& lhs, float scalar);
		friend Vec3 operator*(float scalar, const Vec3& rhs);

		Vec3& operator+=(const Vec3& rhs);
		Vec3& operator-=(const Vec3& rhs);
		Vec3& operator*=(const Vec3& rhs);
		Vec3& operator*=(float scalar);

		friend bool operator==(const Vec3& lhs, const Vec3& rhs);
		friend bool operator!=(const Vec3& lhs, const Vec3& rhs);
		friend bool operator<(const Vec3& lhs, const Vec3& rhs);
		friend bool operator<=(const Vec3& lhs, const Vec3& rhs);
		friend bool operator>(const Vec3& lhs, const Vec3& rhs);
		friend bool operator>=(const Vec3& lhs, const Vec3& rhs);

		friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);

		void NormalizeSelf();
		Vec3 Normalize() const;

		float LengthSq() const;
		float Length() const;

		float Dot(const Vec3& vec) const;
		Vec3 Cross(const Vec3& vec, bool normalize = true) const;
		Vec3 Reflect(const Vec3 n) const;

		std::string ToString() const;



		static const Vec3 Zero;
		static const Vec3 AxisX;
		static const Vec3 AxisY;
		static const Vec3 AxisZ;
		static const Vec3 NegAxisX;
		static const Vec3 NegAxisY;
		static const Vec3 NegAxisZ;
	};	
}

