#pragma once
#include "stdafx.h"

namespace PARS
{
	using Vec2 = XMFLOAT2;

	inline Vec2 operator+=(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	inline Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
	{
		auto result(lhs);
		result += rhs;
		return result;
	}

	inline Vec2 operator-=(const Vec2 & lhs, const Vec2 & rhs)
	{
		return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	inline Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
	{
		auto result(lhs);
		result -= rhs;
		return result;
	}

	inline Vec2 operator*=(const Vec2& lhs, float scalar)
	{
		return Vec2(lhs.x * scalar, lhs.y * scalar);
	}

	inline Vec2 operator*(const Vec2& lhs, float scalar)
	{
		return lhs *= scalar;
	}

	inline Vec2 operator*(float scalar, const Vec2& rhs)
	{
		return rhs *= scalar;
	}

	inline bool operator==(const Vec2& lhs, const Vec2& rhs)
	{
		return Math::NearZero(lhs.x - rhs.x) && Math::NearZero(lhs.y - rhs.y);
	}

	inline bool operator!=(const Vec2& lhs, const Vec2& rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator<(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.x < rhs.x && lhs.y < rhs.y;
	}

	inline bool operator<=(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.x <= rhs.x && lhs.y <= rhs.y;
	}

	inline bool operator>(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.x > rhs.x && lhs.y > rhs.y;
	}

	inline bool operator>=(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.x >= rhs.x && lhs.y >= rhs.y;
	}

	namespace VEC2
	{
		static constexpr Vec2 Zero{ 0.0f, 0.0f };
		static constexpr Vec2 AxisX{ 1.0f, 0.0f };
		static constexpr Vec2 AxisY{ 0.0f, 1.0f };
		static constexpr Vec2 NegAxisX{ -1.0f, 0.0f };
		static constexpr Vec2 NegAxisY{ 0.0f, -1.0f };

		inline Vec2 Normalize(const Vec2& vec)
		{
			Vec2 result;
			XMStoreFloat2(&result, XMVector2Normalize(XMLoadFloat2(&vec)));
			return result;
		}

		inline float LengthSq(const Vec2& vec)
		{
			return (vec.x * vec.x + vec.y * vec.y);
		}

		inline float Length(const Vec2& vec)
		{
			return (Math::Sqrt(LengthSq(vec)));
		}

		inline float Dot(const Vec2& vec1, const Vec2& vec2)
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y);
		}

		inline Vec2 Reflect(const Vec2 v, const Vec2 n)
		{
			return v - 2.0f * VEC2::Dot(v, n) * n;
		}

		inline std::string ToString(const Vec2& vec)
		{
			std::stringstream result;
			result << "Vec2 : {" << vec.x << ", " << vec.y << "}";
			return result.str();
		}
	}

	inline std::ostream& operator<<(std::ostream& os, const Vec2& vec)
	{
		return os << VEC2::ToString(vec);
	}
}

