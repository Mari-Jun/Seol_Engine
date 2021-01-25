#pragma once
#include "stdafx.h"

namespace PARS
{
	using Vec3 = XMFLOAT3;

	inline Vec3 operator+=(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
	{
		auto result(lhs);
		result += rhs;
		return result;
	}

	inline Vec3 operator-=(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
	{
		auto result(lhs);
		result -= rhs;
		return result;
	}

	inline Vec3 operator*=(const Vec3& lhs, float scalar)
	{
		return Vec3(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar);
	}

	inline Vec3 operator*(const Vec3& lhs, float scalar)
	{
		return lhs *= scalar;
	}

	inline Vec3 operator*(float scalar, const Vec3& rhs)
	{
		return rhs *= scalar;
	}

	inline bool operator==(const Vec3& lhs, const Vec3& rhs)
	{
		return Math::NearZero(lhs.x - rhs.x)
			&& Math::NearZero(lhs.y - rhs.y)
			&& Math::NearZero(lhs.z - rhs.z);
	}

	inline bool operator!=(const Vec3& lhs, const Vec3& rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator<(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z;
	}

	inline bool operator<=(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x <= rhs.x && lhs.y <= rhs.y && lhs.z <= rhs.z;
	}

	inline bool operator>(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z;
	}

	inline bool operator>=(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x >= rhs.x && lhs.y >= rhs.y && lhs.z >= rhs.z;
	}

	namespace VEC3
	{
		static constexpr Vec3 Zero{ 0.0f, 0.0f, 0.0f};
		static constexpr Vec3 AxisX{ 1.0f, 0.0f, 0.0f };
		static constexpr Vec3 AxisY{ 0.0f, 1.0f, 0.0f };
		static constexpr Vec3 AxisZ{ 0.0f, 0.0f, 1.0f };
		static constexpr Vec3 NegAxisX{ -1.0f, 0.0f, 0.0f };
		static constexpr Vec3 NegAxisY{ 0.0f, -1.0f, 0.0f };
		static constexpr Vec3 NegAxisZ{ 0.0f, 0.0f, -1.0f };

		inline Vec3 Normalize(const Vec3& vec)
		{
			Vec3 result;
			XMStoreFloat3(&result, XMVector3Normalize(XMLoadFloat3(&vec)));
			return result;
		}

		inline float LengthSq(const Vec3& vec)
		{
			return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		}

		inline float Length(const Vec3& vec)
		{
			return (Math::Sqrt(LengthSq(vec)));
		}

		inline float Dot(const Vec3& vec1, const Vec3& vec2)
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
		}

		inline Vec3 Cross(const Vec3& vec1, const Vec3& vec2, bool normalize = true)
		{
			Vec3 result;
			XMStoreFloat3(&result, XMVector3Cross(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2)));
			if (normalize)
			{
				result = VEC3::Normalize(result);
			}
			return result;
		}

		inline Vec3 Reflect(const Vec3 v, const Vec3 n)
		{
			return v - 2.0f * VEC3::Dot(v, n) * n;
		}

		inline std::string ToString(const Vec3& vec)
		{
			std::stringstream result;
			result << "Vec3 : {" << vec.x << ", " << vec.y << ", " << vec.z << "}";
			return result.str();
		}
	}

	inline std::ostream& operator<<(std::ostream& os, const Vec3& vec)
	{
		return os << VEC3::ToString(vec);
	}
}

