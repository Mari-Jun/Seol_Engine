#pragma once

namespace PARS
{
	class Mat4;
	class Quaternion;

	class Vec3
	{
	public:
		float x, y, z;

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

		void Normalize();
		static Vec3 Normalize(const Vec3& vec);

		float LengthSq() const;
		float Length() const;

		static float Dot(const Vec3& vec1, const Vec3& vec2);
		static Vec3 Cross(const Vec3& vec1, const Vec3& vec2, bool normalize = true);
		static Vec3 Reflect(const Vec3& v, const Vec3& n);
		static Vec3 Lerp(const Vec3& vec1, const Vec3& vec2, float f);

		void Transform(const Mat4& mat, float w = 1.0f);
		static Vec3 Transform(const Vec3& vec, const Mat4& mat, float w = 1.0f);
		void Transform(const Quaternion& q);
		static Vec3 Transform(const Vec3& vec, const Quaternion& q);

		std::string ToString() const;

		static const Vec3 Zero;
		static const Vec3 One;
		static const Vec3 AxisX;
		static const Vec3 AxisY;
		static const Vec3 AxisZ;
		static const Vec3 NegAxisX;
		static const Vec3 NegAxisY;
		static const Vec3 NegAxisZ;
	};	
}

