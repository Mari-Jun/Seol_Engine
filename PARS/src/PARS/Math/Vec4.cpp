#include "stdafx.h"
#include "PARS/Math/MathFunc.h"
#include "PARS/Math/Vec4.h"

namespace PARS
{
	Vec4 operator+(const Vec4& lhs, const Vec4& rhs)
	{
		auto result(lhs);
		result += rhs;
		return result;
	}

	Vec4 operator-(const Vec4& lhs, const Vec4& rhs)
	{
		auto result(lhs);
		result -= rhs;
		return result;
	}

	Vec4 operator*(const Vec4& lhs, const Vec4& rhs)
	{
		auto result(lhs);
		result *= rhs;
		return result;
	}

	Vec4 operator*(const Vec4& lhs, float scalar)
	{
		auto result(lhs);
		result *= scalar;
		return result;
	}

	Vec4 operator*(float scalar, const Vec4& rhs)
	{
		auto result(rhs);
		result *= scalar;
		return result;
	}

	Vec4& Vec4::operator+=(const Vec4& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		this->w += rhs.w;
		return *this;
	}

	Vec4& Vec4::operator-=(const Vec4& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		this->w -= rhs.w;
		return *this;
	}

	Vec4& Vec4::operator*=(const Vec4& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		this->w *= rhs.w;
		return *this;
	}

	Vec4& Vec4::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		this->w *= scalar;
		return *this;
	}

	bool operator==(const Vec4& lhs, const Vec4& rhs)
	{
		return Math::NearZero(lhs.x - rhs.x)
			&& Math::NearZero(lhs.y - rhs.y)
			&& Math::NearZero(lhs.z - rhs.z)
			&& Math::NearZero(lhs.w - rhs.w);
	}

	bool operator!=(const Vec4& lhs, const Vec4& rhs)
	{
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, const Vec4& vec)
	{
		return os << vec.ToString();
	}

	std::string Vec4::ToString() const
	{
		std::stringstream result;
		result << "Vec4 : {" << x << ", " << y << ", " << z << ", " << w << "}";
		return result.str();
	}

	const Vec4 Vec4::Zero{ 0.0f, 0.0f, 0.0f, 0.0f };
}