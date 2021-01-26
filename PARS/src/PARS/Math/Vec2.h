#pragma once

namespace PARS
{
	class Mat3;

	class Vec2
	{
	public:
		float x, y;

		Vec2() : x(0.0f), y(0.0f) {}
		Vec2(float inX, float inY)
			: x(inX), y(inY) {}

		friend Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
		friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
		friend Vec2 operator*(const Vec2& lhs, const Vec2& rhs);
		friend Vec2 operator*(const Vec2& lhs, float scalar);
		friend Vec2 operator*(float scalar, const Vec2& rhs);

		Vec2& operator+=(const Vec2& rhs);
		Vec2& operator-=(const Vec2& rhs);
		Vec2& operator*=(const Vec2& rhs);
		Vec2& operator*=(float scalar);

		friend bool operator==(const Vec2& lhs, const Vec2& rhs);
		friend bool operator!=(const Vec2& lhs, const Vec2& rhs);
		friend bool operator<(const Vec2& lhs, const Vec2& rhs);
		friend bool operator<=(const Vec2& lhs, const Vec2& rhs);
		friend bool operator>(const Vec2& lhs, const Vec2& rhs);
		friend bool operator>=(const Vec2& lhs, const Vec2& rhs);

		friend std::ostream& operator<<(std::ostream& os, const Vec2& vec);

		void Normalize();
		static Vec2 Normalize(const Vec2& vec);

		float LengthSq() const;
		float Length() const;

		static float Dot(const Vec2& vec1, const Vec2& vec2);
		static Vec2 Reflect(const Vec2& v, const Vec2& n);
		static Vec2 Lerp(const Vec2& vec1, const Vec2& vec2, float f);

		void Transform(const Mat3& mat, float w = 1.0f);
		static Vec2 Transform(const Vec2& vec, const Mat3& mat, float w = 1.0f);
		
		std::string ToString() const;

		static const Vec2 Zero;
		static const Vec2 AxisX;
		static const Vec2 AxisY;
		static const Vec2 NegAxisX;
		static const Vec2 NegAxisY;
	};
}

