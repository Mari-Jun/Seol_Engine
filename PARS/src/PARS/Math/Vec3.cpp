#include "stdafx.h"
#include "PARS/Math/Vec3.h"

namespace PARS
{
	Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
	{
		auto result(lhs);
		result += rhs;
		return result;
	}

	Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
	{
		auto result(lhs);
		result -= rhs;
		return result;
	}

	Vec3 operator*(const Vec3& lhs, const Vec3& rhs)
	{
		auto result(lhs);
		result *= rhs;
		return result;
	}

	Vec3 operator*(const Vec3& lhs, float scalar)
	{
		auto result(lhs);
		result *= scalar;
		return result;
	}

	Vec3 operator*(float scalar, const Vec3& rhs)
	{
		auto result(rhs);
		result *= scalar;
		return result;
	}

	Vec3& Vec3::operator+=(const Vec3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}

	Vec3& Vec3::operator-=(const Vec3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}

	Vec3& Vec3::operator*=(const Vec3& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		return *this;
	}

	Vec3& Vec3::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	bool operator==(const Vec3& lhs, const Vec3& rhs)
	{
		return Math::NearZero(lhs.x - rhs.x)
			&& Math::NearZero(lhs.y - rhs.y)
			&& Math::NearZero(lhs.z - rhs.z);
	}

	bool operator!=(const Vec3& lhs, const Vec3& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x < rhs.x&& lhs.y < rhs.y&& lhs.z < rhs.z;
	}

	bool operator<=(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x <= rhs.x && lhs.y <= rhs.y && lhs.z <= rhs.z;
	}

	bool operator>(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z;
	}

	bool operator>=(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x >= rhs.x && lhs.y >= rhs.y && lhs.z >= rhs.z;
	}

	std::ostream& operator<<(std::ostream& os, const Vec3& vec)
	{
		return os << vec.ToString();
	}

	void Vec3::NormalizeSelf()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	Vec3 Vec3::Normalize() const
	{
		Vec3 result(*this);
		result.Normalize();
		return result;
	}

	float Vec3::LengthSq() const
	{
		return (x * x + y * y + z * z);
	}

	float Vec3::Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	float Vec3::Dot(const Vec3& vec) const
	{
		return (x * vec.x + y * vec.y + z * vec.z);
	}

	Vec3 Vec3::Cross(const Vec3& vec, bool normalize) const
	{
		Vec3 result(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x);
		if (normalize)
		{
			result.Normalize();
		}
		return result;
	}

	Vec3 Vec3::Reflect(const Vec3 n) const
	{
		return *this - 2.0f * (*this).Dot(n) * n;
	}

	std::string Vec3::ToString() const
	{
		std::stringstream result;
		result << "Vec3 : {" << x << ", " << y << ", " << z << "}";
		return result.str();
	}

	const Vec3 Vec3::Zero{ 0.0f, 0.0f, 0.0f };
	const Vec3 Vec3::AxisX{ 1.0f, 0.0f, 0.0f };
	const Vec3 Vec3::AxisY{ 0.0f, 1.0f, 0.0f };
	const Vec3 Vec3::AxisZ{ 0.0f, 0.0f, 1.0f };
	const Vec3 Vec3::NegAxisX{ -1.0f, 0.0f, 0.0f };
	const Vec3 Vec3::NegAxisY{ 0.0f, -1.0f, 0.0f };
	const Vec3 Vec3::NegAxisZ{ 0.0f, 0.0f, -1.0f };
}