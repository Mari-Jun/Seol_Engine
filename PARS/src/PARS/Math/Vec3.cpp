#include "stdafx.h"
#include "PARS/Math/MathFunc.h"
#include "PARS/Math/Vec3.h"
#include "PARS/Math/Mat4.h"
#include "PARS/Math/Quaternion.h"

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

	void Vec3::Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	Vec3 Vec3::Normalize(const Vec3& vec)
	{
		Vec3 result(vec);
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

	float Vec3::Dot(const Vec3& vec1, const Vec3& vec2)
	{
		return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
	}

	Vec3 Vec3::Cross(const Vec3& vec1, const Vec3& vec2, bool normalize)
	{
		Vec3 result(
			vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x);
		if (normalize)
		{
			result.Normalize();
		}
		return result;
	}

	Vec3 Vec3::Reflect(const Vec3& v, const Vec3& n)
	{
		return v - 2.0f * Vec3::Dot(v, n) * n;
	}

	Vec3 Vec3::Lerp(const Vec3& vec1, const Vec3& vec2, float f)
	{
		return Vec3(vec1 + f * (vec2 - vec1));
	}

	void Vec3::Transform(const Mat4& mat, float w)
	{
		x = x * mat.mat[0][0] + y * mat.mat[1][0] + z * mat.mat[2][0] + w * mat.mat[3][0];
		y = x * mat.mat[0][1] + y * mat.mat[1][1] + z * mat.mat[2][1] + w * mat.mat[3][1];
		z = x * mat.mat[0][2] + y * mat.mat[1][2] + z * mat.mat[2][2] + w * mat.mat[3][2];
	}

	Vec3 Vec3::Transform(const Vec3& vec, const Mat4& mat, float w)
	{
		auto result(vec);
		result.Transform(mat, w);
		return result;
	}

	void Vec3::Transform(const Quaternion& q)
	{
		Vec3 qv(q.x, q.y, q.z);
		*this += 2.0f * Vec3::Cross(qv, Vec3::Cross(qv, *this, false) + q.w * *this, false);
	}

	Vec3 Vec3::Transform(const Vec3& vec, const Quaternion& q)
	{
		auto result(vec);
		result.Transform(q);
		return result;
	}

	std::string Vec3::ToString() const
	{
		std::stringstream result;
		result << "Vec3 : {" << x << ", " << y << ", " << z << "}";
		return result.str();
	}

	const Vec3 Vec3::Zero{ 0.0f, 0.0f, 0.0f };
	const Vec3 Vec3::One{ 1.0f, 1.0f, 1.0f };
	const Vec3 Vec3::AxisX{ 1.0f, 0.0f, 0.0f };
	const Vec3 Vec3::AxisY{ 0.0f, 1.0f, 0.0f };
	const Vec3 Vec3::AxisZ{ 0.0f, 0.0f, 1.0f };
	const Vec3 Vec3::NegAxisX{ -1.0f, 0.0f, 0.0f };
	const Vec3 Vec3::NegAxisY{ 0.0f, -1.0f, 0.0f };
	const Vec3 Vec3::NegAxisZ{ 0.0f, 0.0f, -1.0f };
}