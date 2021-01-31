#include "stdafx.h"
#include "PARS/Math/MathFunc.h"
#include "PARS/Math/Vec2.h"
#include "PARS/Math/Mat3.h"

namespace PARS
{
	Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
	{
		auto result(lhs);
		result += rhs;
		return result;
	}

	Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
	{
		auto result(lhs);
		result -= rhs;
		return result;
	}

	Vec2 operator*(const Vec2& lhs, const Vec2& rhs)
	{
		auto result(lhs);
		result *= rhs;
		return result;
	}

	Vec2 operator*(const Vec2& lhs, float scalar)
	{
		auto result(lhs);
		result *= scalar;
		return result;
	}

	Vec2 operator*(float scalar, const Vec2& rhs)
	{
		auto result(rhs);
		result *= scalar;
		return result;
	}

	Vec2& Vec2::operator+=(const Vec2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	Vec2& Vec2::operator-=(const Vec2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	Vec2& Vec2::operator*=(const Vec2& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}

	Vec2& Vec2::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	bool operator==(const Vec2& lhs, const Vec2& rhs)
	{
		return Math::NearZero(lhs.x - rhs.x)
			&& Math::NearZero(lhs.y - rhs.y);
	}

	bool operator!=(const Vec2& lhs, const Vec2& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.x < rhs.x&& lhs.y < rhs.y;
	}

	bool operator<=(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.x <= rhs.x && lhs.y <= rhs.y;
	}

	bool operator>(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.x > rhs.x && lhs.y > rhs.y;
	}

	bool operator>=(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.x >= rhs.x && lhs.y >= rhs.y;
	}

	std::ostream& operator<<(std::ostream& os, const Vec2& vec)
	{
		return os << vec.ToString();
	}

	void Vec2::Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	Vec2 Vec2::Normalize(const Vec2& vec)
	{
		Vec2 result(vec);
		result.Normalize();
		return result;
	}

	float Vec2::LengthSq() const
	{
		return (x * x + y * y);
	}

	float Vec2::Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	float Vec2::Dot(const Vec2& vec1, const Vec2& vec2)
	{
		return (vec1.x * vec2.x + vec1.y * vec2.y);
	}

	Vec2 Vec2::Lerp(const Vec2& vec1, const Vec2& vec2, float f)
	{
		return Vec2(vec1 + f * (vec2 - vec1));
	}

	Vec2 Vec2::Reflect(const Vec2& v, const Vec2& n)
	{
		return v - 2.0f * Vec2::Dot(v, n) * n;
	}

	void Vec2::Transform(const Mat3& mat, float w)
	{
		x = x * mat.mat[0][0] + y * mat.mat[1][0] + w * mat.mat[2][0];
		y = x * mat.mat[0][1] + y * mat.mat[1][1] + w * mat.mat[2][1];
	}

	Vec2 Vec2::Transform(const Vec2& vec, const Mat3& mat, float w)
	{
		Vec2 result(vec);
		result.Transform(mat, w);
		return result;
	}

	std::string Vec2::ToString() const
	{
		std::stringstream result;
		result << "Vec2 : {" << x << ", " << y << "}";
		return result.str();
	}

	const Vec2 Vec2::Zero{ 0.0f, 0.0f };
	const Vec2 Vec2::AxisX{ 1.0f, 0.0f };
	const Vec2 Vec2::AxisY{ 0.0f, 1.0f };
	const Vec2 Vec2::NegAxisX{ -1.0f, 0.0f };
	const Vec2 Vec2::NegAxisY{ 0.0f, -1.0f };
}